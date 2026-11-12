/* dinput8.dll: the system keyboard and mouse as DirectInput 8 devices.
 *
 * Immediate state (GetDeviceState) and buffered events (GetDeviceData) are both
 * served from the raw input log that video.c keeps. No game controllers are
 * enumerated.
 */
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "com.h"
#include "rt.h"
#include "video.h"

#define DI_OK 0u
#define DI_BUFFEROVERFLOW 1u
#define DIERR_DEVICENOTREG 0x80040154u
#define DIERR_INVALIDPARAM 0x80070057u
#define DIERR_NOTACQUIRED 0x8007000Cu

#define MAGIC_DINPUT 0x44494E00u /* "DIN" */
#define MAGIC_DIDEV 0x44494400u  /* "DID" */

enum { DEV_KEYBOARD = 1, DEV_MOUSE };

typedef struct DiDevice {
    int used, kind, refs, acquired;
    uint32_t data_size;  /* from SetDataFormat: 256 keyboard, 16 or 20 mouse */
    uint32_t buffer_size;
    unsigned cursor;     /* position in the raw input log */
    uint32_t event;
} DiDevice;

static DiDevice devices[16];
static uint32_t vt_dinput, vt_device, dinput_obj;
static pthread_mutex_t di_mu = PTHREAD_MUTEX_INITIALIZER;

static const uint8_t GUID_SysMouse[16] = {0x60, 0x2B, 0x1D, 0x6F, 0xA0, 0xD5, 0xCF, 0x11,
                                           0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00};
static const uint8_t GUID_SysKeyboard[16] = {0x61, 0x2B, 0x1D, 0x6F, 0xA0, 0xD5, 0xCF, 0x11,
                                              0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00};

static DiDevice *dev_of(uint32_t obj) {
    int i = rt_com_index(obj, MAGIC_DIDEV);
    if (i < 0 || i >= (int)RT_COUNTOF(devices) || !devices[i].used) return NULL;
    return &devices[i];
}

/* ------------------------------------------------------ IDirectInputDevice8A */
H(did_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(did_AddRef) { UNUSED; DiDevice *d = dev_of(a[0]); return d ? (uint32_t)++d->refs : 0; }
H(did_Release) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d) return 0;
    if (--d->refs > 0) return (uint32_t)d->refs;
    d->used = 0;
    rt_com_free(a[0]);
    return 0;
}

/* GetCapabilities(this, DIDEVCAPS *) */
H(did_GetCapabilities) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[1]) return DIERR_INVALIDPARAM;
    uint32_t size = ld32(a[1]);
    if (size < 24 || size > 44) return DIERR_INVALIDPARAM;
    memset(G(a[1] + 4), 0, size - 4);
    st32(a[1] + 4, 1); /* DIDC_ATTACHED */
    st32(a[1] + 8, d->kind == DEV_KEYBOARD ? 0x00000403u : 0x00000112u); /* dwDevType */
    st32(a[1] + 12, d->kind == DEV_KEYBOARD ? 0 : 3);                     /* axes */
    st32(a[1] + 16, d->kind == DEV_KEYBOARD ? 256 : 3);                   /* buttons */
    return DI_OK;
}

/* SetProperty(this, property, DIPROPHEADER *): the buffer size is the one that matters. */
H(did_SetProperty) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d) return DIERR_INVALIDPARAM;
    if (a[1] == 1 && a[2]) d->buffer_size = ld32(a[2] + 16); /* DIPROP_BUFFERSIZE */
    return DI_OK;
}

H(did_GetProperty) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[2]) return DIERR_INVALIDPARAM;
    if (a[1] == 1) {
        st32(a[2] + 16, d->buffer_size);
        return DI_OK;
    }
    return DIERR_INVALIDPARAM;
}

H(did_Acquire) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d) return DIERR_INVALIDPARAM;
    if (!d->acquired) {
        int dx, dy, dz;
        d->acquired = 1;
        d->cursor = rt_input_position(); /* input from before the acquisition is not reported */
        if (d->kind == DEV_MOUSE) rt_mouse_take_motion(&dx, &dy, &dz);
    }
    return DI_OK;
}

H(did_Unacquire) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (d) d->acquired = 0;
    return DI_OK;
}

/* GetDeviceState(this, size, data) */
H(did_GetDeviceState) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[2]) return DIERR_INVALIDPARAM;
    if (!d->acquired) return DIERR_NOTACQUIRED;
    memset(G(a[2]), 0, a[1]);
    if (d->kind == DEV_KEYBOARD) {
        memcpy(G(a[2]), rt_dik_state, a[1] < 256 ? a[1] : 256);
    } else {
        int dx, dy, dz;
        rt_mouse_take_motion(&dx, &dy, &dz);
        if (a[1] >= 12) {
            st32(a[2], (uint32_t)dx);
            st32(a[2] + 4, (uint32_t)dy);
            st32(a[2] + 8, (uint32_t)dz);
        }
        for (uint32_t b = 0; b < 3 && 12 + b < a[1]; b++)
            st8(a[2] + 12 + b, (rt_mouse_buttons & (1u << b)) ? 0x80 : 0);
    }
    return DI_OK;
}

/* GetDeviceData(this, objectSize, data, &count, flags) */
H(did_GetDeviceData) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[3] || (a[1] != 16 && a[1] != 20)) return DIERR_INVALIDPARAM;
    if (!d->acquired) return DIERR_NOTACQUIRED;
    uint32_t want = ld32(a[3]), got = 0;
    unsigned cur = d->cursor;
    int overflow = 0;
    RtRawInput ev;
    while (got < want && rt_input_read(&cur, &ev, &overflow)) {
        uint32_t ofs;
        if (d->kind == DEV_KEYBOARD) {
            if (ev.kind != RT_RAW_KEY) continue;
            ofs = (uint32_t)ev.code;
        } else {
            if (ev.kind == RT_RAW_AXIS) ofs = (uint32_t)ev.code * 4;
            else if (ev.kind == RT_RAW_BUTTON) ofs = 12 + (uint32_t)ev.code;
            else continue;
        }
        if (a[2]) {
            uint32_t p = a[2] + got * a[1];
            st32(p, ofs);
            st32(p + 4, (uint32_t)ev.value);
            st32(p + 8, ev.time_ms);
            st32(p + 12, ev.seq);
            if (a[1] == 20) st32(p + 16, 0);
        }
        got++;
    }
    if (!(a[4] & 1)) d->cursor = cur; /* DIGDD_PEEK leaves the data in the buffer */
    st32(a[3], got);
    return overflow ? DI_BUFFEROVERFLOW : DI_OK;
}

/* SetDataFormat(this, DIDATAFORMAT *) */
H(did_SetDataFormat) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[1]) return DIERR_INVALIDPARAM;
    d->data_size = ld32(a[1] + 12);
    if (g_opt.verbose)
        rt_log("[dinput] %s data format: %u bytes, %u objects\n", d->kind == DEV_KEYBOARD ? "keyboard" : "mouse",
               d->data_size, ld32(a[1] + 16));
    return DI_OK;
}

H(did_SetEventNotification) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (d) d->event = a[1];
    return DI_OK;
}

H(did_SetCooperativeLevel) { UNUSED; return DI_OK; }
H(did_Poll) { UNUSED; return DI_OK; }

/* GetDeviceInfo(this, DIDEVICEINSTANCEA *) */
H(did_GetDeviceInfo) {
    UNUSED;
    DiDevice *d = dev_of(a[0]);
    if (!d || !a[1] || ld32(a[1]) < 0x244) return DIERR_INVALIDPARAM;
    memset(G(a[1] + 4), 0, 0x244 - 4);
    memcpy(G(a[1] + 4), d->kind == DEV_KEYBOARD ? GUID_SysKeyboard : GUID_SysMouse, 16);
    memcpy(G(a[1] + 20), d->kind == DEV_KEYBOARD ? GUID_SysKeyboard : GUID_SysMouse, 16);
    st32(a[1] + 36, d->kind == DEV_KEYBOARD ? 0x00000403u : 0x00000112u);
    strcpy((char *)G(a[1] + 40), d->kind == DEV_KEYBOARD ? "Keyboard" : "Mouse");
    strcpy((char *)G(a[1] + 40 + 260), d->kind == DEV_KEYBOARD ? "Keyboard" : "Mouse");
    return DI_OK;
}

static const ComMethod device_methods[] = {
    {"QueryInterface", did_QueryInterface, 3}, {"AddRef", did_AddRef, 1}, {"Release", did_Release, 1},
    {"GetCapabilities", did_GetCapabilities, 2}, {"EnumObjects", NULL, 4}, {"GetProperty", did_GetProperty, 3},
    {"SetProperty", did_SetProperty, 3}, {"Acquire", did_Acquire, 1}, {"Unacquire", did_Unacquire, 1},
    {"GetDeviceState", did_GetDeviceState, 3}, {"GetDeviceData", did_GetDeviceData, 5},
    {"SetDataFormat", did_SetDataFormat, 2}, {"SetEventNotification", did_SetEventNotification, 2},
    {"SetCooperativeLevel", did_SetCooperativeLevel, 3}, {"GetObjectInfo", NULL, 4},
    {"GetDeviceInfo", did_GetDeviceInfo, 2}, {"RunControlPanel", NULL, 3}, {"Initialize", NULL, 4},
    {"CreateEffect", NULL, 5}, {"EnumEffects", NULL, 4}, {"GetEffectInfo", NULL, 3},
    {"GetForceFeedbackState", NULL, 2}, {"SendForceFeedbackCommand", NULL, 2},
    {"EnumCreatedEffectObjects", NULL, 4}, {"Escape", NULL, 2}, {"Poll", did_Poll, 1},
    {"SendDeviceData", NULL, 5}, {"EnumEffectsInFile", NULL, 5}, {"WriteEffectToFile", NULL, 5},
    {"BuildActionMap", NULL, 4}, {"SetActionMap", NULL, 4}, {"GetImageInfo", NULL, 2},
};

/* ------------------------------------------------------------ IDirectInput8A */
H(di_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(di_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(di_Release) { UNUSED; uint32_t n = ld32(a[0] + 12); if (n) st32(a[0] + 12, --n); return n; }

/* CreateDevice(this, guid, &device, outer) */
H(di_CreateDevice) {
    UNUSED;
    char buf[40];
    if (!a[2]) return DIERR_INVALIDPARAM;
    int kind = rt_guid_eq(a[1], GUID_SysKeyboard) ? DEV_KEYBOARD : rt_guid_eq(a[1], GUID_SysMouse) ? DEV_MOUSE : 0;
    if (!kind) {
        rt_log("recomp: IDirectInput8::CreateDevice(%s): no such device\n", rt_guid_str(a[1], buf));
        st32(a[2], 0);
        return DIERR_DEVICENOTREG;
    }
    pthread_mutex_lock(&di_mu);
    int i;
    for (i = 0; i < (int)RT_COUNTOF(devices); i++)
        if (!devices[i].used) break;
    if (i == (int)RT_COUNTOF(devices)) {
        pthread_mutex_unlock(&di_mu);
        return E_OUTOFMEMORY;
    }
    memset(&devices[i], 0, sizeof devices[i]);
    devices[i].used = 1;
    devices[i].kind = kind;
    devices[i].refs = 1;
    pthread_mutex_unlock(&di_mu);
    st32(a[2], rt_com_object(vt_device, (uint32_t)i, MAGIC_DIDEV));
    if (g_opt.verbose) rt_log("[dinput] %s device created\n", kind == DEV_KEYBOARD ? "keyboard" : "mouse");
    return DI_OK;
}

/* EnumDevices(this, type, callback, context, flags): the keyboard and the mouse
 * exist; there are no game controllers. */
H(di_EnumDevices) {
    uint32_t type = a[1] & 0xFF;
    if (type == 4) return DI_OK; /* DI8DEVCLASS_GAMECTRL */
    uint32_t sp = ESP;
    uint32_t inst = rt_stack_alloc(c, 0x244);
    for (int kind = DEV_KEYBOARD; kind <= DEV_MOUSE; kind++) {
        if (type == 3 && kind != DEV_KEYBOARD) continue; /* DI8DEVCLASS_KEYBOARD */
        if (type == 2 && kind != DEV_MOUSE) continue;    /* DI8DEVCLASS_POINTER */
        if (type == 1) continue;                         /* DI8DEVCLASS_DEVICE */
        memset(G(inst), 0, 0x244);
        st32(inst, 0x244);
        memcpy(G(inst + 4), kind == DEV_KEYBOARD ? GUID_SysKeyboard : GUID_SysMouse, 16);
        memcpy(G(inst + 20), kind == DEV_KEYBOARD ? GUID_SysKeyboard : GUID_SysMouse, 16);
        st32(inst + 36, kind == DEV_KEYBOARD ? 0x00000403u : 0x00000112u);
        strcpy((char *)G(inst + 40), kind == DEV_KEYBOARD ? "Keyboard" : "Mouse");
        strcpy((char *)G(inst + 40 + 260), kind == DEV_KEYBOARD ? "Keyboard" : "Mouse");
        uint32_t args[2] = {inst, a[3]}, r = 0;
        if (!rt_call_guest(c, a[2], RT_STDCALL, 2, args, &r)) return 0;
        if (!r) break;
    }
    ESP = sp;
    return DI_OK;
}

H(di_GetDeviceStatus) {
    UNUSED;
    return rt_guid_eq(a[1], GUID_SysKeyboard) || rt_guid_eq(a[1], GUID_SysMouse) ? DI_OK : 1; /* DI_NOTATTACHED */
}

static const ComMethod dinput_methods[] = {
    {"QueryInterface", di_QueryInterface, 3}, {"AddRef", di_AddRef, 1}, {"Release", di_Release, 1},
    {"CreateDevice", di_CreateDevice, 4}, {"EnumDevices", di_EnumDevices, 5},
    {"GetDeviceStatus", di_GetDeviceStatus, 2}, {"RunControlPanel", NULL, 3}, {"Initialize", NULL, 3},
    {"FindDevice", NULL, 4}, {"EnumDevicesBySemantics", NULL, 6}, {"ConfigureDevices", NULL, 5},
};

/* DirectInput8Create(instance, version, iid, &out, outer) */
H(di_DirectInput8Create) {
    UNUSED;
    if (!a[3]) return DIERR_INVALIDPARAM;
    pthread_mutex_lock(&di_mu);
    if (!dinput_obj) {
        vt_dinput = rt_com_vtable("dinput8.dll", "IDirectInput8A", dinput_methods, RT_COUNTOF(dinput_methods));
        vt_device = rt_com_vtable("dinput8.dll", "IDirectInputDevice8A", device_methods, RT_COUNTOF(device_methods));
        dinput_obj = rt_com_object(vt_dinput, 0, MAGIC_DINPUT);
    }
    pthread_mutex_unlock(&di_mu);
    st32(dinput_obj + 12, ld32(dinput_obj + 12) + 1);
    st32(a[3], dinput_obj);
    return DI_OK;
}

static const ImportDef defs[] = {
    {"dinput8.dll", "DirectInput8Create", di_DirectInput8Create, 5, 0},
};
RT_EXPORT_IMPORTS(rt_imports_dinput, defs);
