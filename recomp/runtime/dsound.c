/* dsound.dll: DirectSound 8 on a software mixer.
 *
 * A sound buffer's samples live in guest memory, so Lock hands out pointers
 * into the buffer itself. Playing buffers are resampled (linear interpolation)
 * and mixed into one 44.1 kHz stereo stream with DirectSound's volume and pan
 * rules (attenuation in hundredths of a decibel). The stream is pulled either
 * by SDL's audio device or, without one (headless, no audio device, built
 * without SDL), by a thread that follows the guest clock, so that play cursors
 * advance the same way and the game's own streaming keeps working. That thread
 * can also write the mix to a WAV file (--dump-audio).
 *
 * Not implemented: 3D buffers, effects, capture, position notifications
 * (IDirectSoundNotify: QueryInterface refuses, the game polls the cursor).
 */
#define _GNU_SOURCE
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "com.h"
#include "rt.h"

#ifndef RT_NO_SDL
#include <SDL.h>
#endif

#define DS_OK 0u
#define DSERR_NODRIVER 0x88780078u
#define DSERR_INVALIDPARAM 0x80070057u
#define DSERR_INVALIDCALL 0x88780032u
#define DSERR_BADFORMAT 0x88780064u
#define DSERR_OUTOFMEMORY 0x8007000Eu
#define DSERR_CONTROLUNAVAIL 0x8878001Eu

#define DSBCAPS_PRIMARYBUFFER 0x1u
#define DSBPLAY_LOOPING 0x1u
#define DSBSTATUS_PLAYING 0x1u
#define DSBSTATUS_LOOPING 0x4u
#define DSBLOCK_FROMWRITECURSOR 0x1u
#define DSBLOCK_ENTIREBUFFER 0x2u

#define MAGIC_DSOUND 0x44534F00u /* "DSO" */
#define MAGIC_DSBUF 0x44534200u  /* "DSB" */

#define MIX_RATE 44100
#define MAX_BUFFERS 128

typedef struct DsBuffer {
    int used, refs, primary;
    uint32_t flags;
    uint32_t data, bytes;      /* guest address and size of the sample data (0 for the primary buffer) */
    int channels, bits, align; /* sample format */
    uint32_t rate;             /* playback frequency, Hz */
    int32_t volume, pan;       /* hundredths of a decibel */
    int playing, looping;
    uint64_t pos;              /* play position: frames << 32 */
    float gain_l, gain_r;
} DsBuffer;

static DsBuffer bufs[MAX_BUFFERS];
static pthread_mutex_t ds_mu = PTHREAD_MUTEX_INITIALIZER;
static uint32_t vt_dsound, vt_buffer, dsound_obj;
static float master_gain = 1.0f;
static int mixer_started;
static uint64_t frames_mixed;
static int16_t peak;

/* ------------------------------------------------------------------ mixer */
static float db_gain(int32_t hundredths) {
    if (hundredths <= -10000) return 0.0f;
    if (hundredths >= 0) return 1.0f;
    return powf(10.0f, (float)hundredths / 2000.0f);
}

/* Under ds_mu. */
static void update_gain(DsBuffer *b) {
    float g = db_gain(b->volume);
    b->gain_l = g * (b->pan > 0 ? db_gain(-b->pan) : 1.0f);
    b->gain_r = g * (b->pan < 0 ? db_gain(b->pan) : 1.0f);
}

static inline void fetch(const DsBuffer *b, uint32_t frame, int *l, int *r) {
    const uint8_t *p = G(b->data + frame * (uint32_t)b->align);
    if (b->bits == 16) {
        int16_t s[2];
        memcpy(s, p, b->channels == 2 ? 4 : 2);
        *l = s[0];
        *r = b->channels == 2 ? s[1] : s[0];
    } else {
        *l = ((int)p[0] - 128) << 8;
        *r = b->channels == 2 ? ((int)p[1] - 128) << 8 : *l;
    }
}

/* Mixes `frames` stereo frames into out. Called by whoever drives the audio clock. */
static void mix(int16_t *out, int frames) {
    static float acc[2 * 4096];
    while (frames > 0) {
        int n = frames > 4096 ? 4096 : frames;
        memset(acc, 0, sizeof(float) * 2 * (size_t)n);
        pthread_mutex_lock(&ds_mu);
        for (int i = 0; i < MAX_BUFFERS; i++) {
            DsBuffer *b = &bufs[i];
            if (!b->used || b->primary || !b->playing || !b->data || !b->rate) continue;
            uint32_t total = b->bytes / (uint32_t)b->align;
            if (!total) continue;
            uint64_t step = ((uint64_t)b->rate << 32) / MIX_RATE, end = (uint64_t)total << 32;
            float gl = b->gain_l, gr = b->gain_r;
            for (int k = 0; k < n; k++) {
                if (b->pos >= end) {
                    if (!b->looping) {
                        b->playing = 0;
                        b->pos = 0;
                        break;
                    }
                    b->pos %= end;
                }
                uint32_t f0 = (uint32_t)(b->pos >> 32), f1 = f0 + 1;
                if (f1 >= total) f1 = b->looping ? 0 : f0;
                float t = (float)(uint32_t)b->pos * (1.0f / 4294967296.0f);
                int l0, r0, l1, r1;
                fetch(b, f0, &l0, &r0);
                fetch(b, f1, &l1, &r1);
                acc[2 * k] += gl * ((float)l0 + t * (float)(l1 - l0));
                acc[2 * k + 1] += gr * ((float)r0 + t * (float)(r1 - r0));
                b->pos += step;
            }
        }
        float mg = master_gain;
        pthread_mutex_unlock(&ds_mu);
        for (int k = 0; k < 2 * n; k++) {
            float v = acc[k] * mg;
            int16_t s = v > 32767.0f ? 32767 : v < -32768.0f ? -32768 : (int16_t)lrintf(v);
            out[k] = s;
            int16_t m = s < 0 ? (int16_t)(s == -32768 ? 32767 : -s) : s;
            if (m > peak) peak = m;
        }
        frames_mixed += (uint64_t)n;
        out += 2 * n;
        frames -= n;
    }
}

/* ---- WAV output (--dump-audio). The header is rewritten as the file grows, so
 * that the file is valid whenever the process stops. */
static FILE *wav;
static uint32_t wav_bytes;

static void wav_header(void) {
    uint8_t h[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 2, 0};
    uint32_t v;
    v = 36 + wav_bytes;
    memcpy(h + 4, &v, 4);
    v = MIX_RATE;
    memcpy(h + 24, &v, 4);
    v = MIX_RATE * 4;
    memcpy(h + 28, &v, 4);
    h[32] = 4;
    h[34] = 16;
    memcpy(h + 36, "data", 4);
    memcpy(h + 40, &wav_bytes, 4);
    long at = ftell(wav);
    fseek(wav, 0, SEEK_SET);
    fwrite(h, 1, 44, wav);
    fseek(wav, at < 44 ? 44 : at, SEEK_SET);
    fflush(wav);
}

/* The audio clock without a device: mix as much as guest time has advanced. */
static void *clock_main(void *arg) {
    (void)arg;
    static int16_t chunk[2 * 4096];
    uint64_t start = rt_mono_ns(), done = 0, since_header = 0;
    for (;;) {
        struct timespec ts = {0, 5 * 1000 * 1000};
        nanosleep(&ts, NULL);
        uint64_t due = (rt_mono_ns() - start) / 1000 * MIX_RATE / 1000000;
        while (done < due) {
            int n = due - done > 4096 ? 4096 : (int)(due - done);
            mix(chunk, n);
            done += (uint64_t)n;
            if (wav) {
                fwrite(chunk, 4, (size_t)n, wav);
                wav_bytes += (uint32_t)n * 4;
                since_header += (uint64_t)n;
            }
        }
        if (wav && since_header >= MIX_RATE / 4) {
            wav_header();
            since_header = 0;
        }
    }
    return NULL;
}

#ifndef RT_NO_SDL
static void sdl_audio_cb(void *user, Uint8 *stream, int len) {
    (void)user;
    mix((int16_t *)stream, len / 4);
}
#endif

static void mixer_start(void) {
    if (mixer_started) return;
    mixer_started = 1;
    if (g_opt.dump_audio[0]) {
        wav = fopen(g_opt.dump_audio, "wb");
        if (wav) wav_header();
        else rt_log("recomp: cannot write %s; the sound is not recorded\n", g_opt.dump_audio);
    }
#ifndef RT_NO_SDL
    if (!g_opt.headless && !wav) {
        SDL_AudioSpec want, have;
        memset(&want, 0, sizeof want);
        want.freq = MIX_RATE;
        want.format = AUDIO_S16SYS;
        want.channels = 2;
        want.samples = 1024;
        want.callback = sdl_audio_cb;
        SDL_AudioDeviceID dev = 0;
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
        if (dev) {
            SDL_PauseAudioDevice(dev, 0);
            rt_log("recomp: sound on SDL audio driver %s, %d Hz, %u-frame buffer\n", SDL_GetCurrentAudioDriver(),
                   have.freq, (unsigned)have.samples);
            return;
        }
        rt_log("recomp: no SDL audio device (%s); sound is mixed but not heard\n", SDL_GetError());
    }
#endif
    pthread_t pt;
    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
    pthread_create(&pt, &at, clock_main, NULL);
    pthread_attr_destroy(&at);
    if (wav) rt_log("recomp: sound is written to %s (%d Hz stereo)\n", g_opt.dump_audio, MIX_RATE);
}

void rt_audio_report(void) {
    if (!mixer_started) return;
    rt_log("sound: %.1f s mixed, peak %d of 32767\n", (double)frames_mixed / MIX_RATE, (int)peak);
    if (wav) wav_header();
}

/* ------------------------------------------------------ IDirectSoundBuffer */
static DsBuffer *buf_of(uint32_t obj) {
    int i = rt_com_index(obj, MAGIC_DSBUF);
    if (i < 0 || i >= MAX_BUFFERS || !bufs[i].used) return NULL;
    return &bufs[i];
}

/* WAVEFORMATEX at guest address p into b; 0 if it is not PCM this mixer can play. */
static int read_format(DsBuffer *b, uint32_t p) {
    unsigned tag = ld16(p), ch = ld16(p + 2), bits = ld16(p + 14);
    uint32_t rate = ld32(p + 4);
    if (tag != 1 || (ch != 1 && ch != 2) || (bits != 8 && bits != 16) || rate < 100 || rate > 200000) return 0;
    b->channels = (int)ch;
    b->bits = (int)bits;
    b->align = (int)(ch * bits / 8);
    b->rate = rate;
    return 1;
}

H(dsb_QueryInterface) {
    UNUSED;
    char g[40];
    if (g_opt.verbose) rt_log("[dsound] IDirectSoundBuffer::QueryInterface(%s): not provided\n", rt_guid_str(a[1], g));
    if (a[2]) st32(a[2], 0);
    return E_NOINTERFACE;
}

H(dsb_AddRef) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    uint32_t n = b ? (uint32_t)++b->refs : 0;
    pthread_mutex_unlock(&ds_mu);
    return n;
}

H(dsb_Release) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (!b) {
        pthread_mutex_unlock(&ds_mu);
        return 0;
    }
    if (--b->refs > 0) {
        uint32_t n = (uint32_t)b->refs;
        pthread_mutex_unlock(&ds_mu);
        return n;
    }
    uint32_t data = b->data;
    memset(b, 0, sizeof *b);
    pthread_mutex_unlock(&ds_mu);
    if (data) rt_heap_free(data);
    rt_com_free(a[0]);
    return 0;
}

/* GetCaps(this, DSBCAPS *) */
H(dsb_GetCaps) {
    UNUSED;
    DsBuffer *b = buf_of(a[0]);
    if (!b || !a[1] || ld32(a[1]) < 20) return DSERR_INVALIDPARAM;
    st32(a[1] + 4, b->flags);
    st32(a[1] + 8, b->bytes);
    st32(a[1] + 12, 0);
    st32(a[1] + 16, 0);
    return DS_OK;
}

/* GetCurrentPosition(this, &play, &write): byte offsets. The write cursor leads
 * the play cursor by 15 ms, about what DirectSound's software mixer reports. */
H(dsb_GetCurrentPosition) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (!b) {
        pthread_mutex_unlock(&ds_mu);
        return DSERR_INVALIDPARAM;
    }
    uint32_t play = 0, write = 0;
    if (b->bytes && b->align) {
        uint32_t total = b->bytes / (uint32_t)b->align;
        uint32_t frame = (uint32_t)(b->pos >> 32) % total;
        play = frame * (uint32_t)b->align;
        write = b->playing ? ((frame + b->rate * 15 / 1000) % total) * (uint32_t)b->align : play;
    }
    pthread_mutex_unlock(&ds_mu);
    if (a[1]) st32(a[1], play);
    if (a[2]) st32(a[2], write);
    return DS_OK;
}

/* GetFormat(this, WAVEFORMATEX *, size, &written) */
H(dsb_GetFormat) {
    UNUSED;
    DsBuffer *b = buf_of(a[0]);
    if (!b) return DSERR_INVALIDPARAM;
    uint8_t f[18];
    memset(f, 0, sizeof f);
    uint16_t w;
    uint32_t d;
    w = 1, memcpy(f, &w, 2);
    w = (uint16_t)b->channels, memcpy(f + 2, &w, 2);
    d = b->rate, memcpy(f + 4, &d, 4);
    d = b->rate * (uint32_t)b->align, memcpy(f + 8, &d, 4);
    w = (uint16_t)b->align, memcpy(f + 12, &w, 2);
    w = (uint16_t)b->bits, memcpy(f + 14, &w, 2);
    uint32_t n = a[2] < 18 ? a[2] : 18;
    if (a[1]) memcpy(G(a[1]), f, n);
    if (a[3]) st32(a[3], a[1] ? n : 18);
    return DS_OK;
}

H(dsb_GetVolume) { UNUSED; DsBuffer *b = buf_of(a[0]); if (!b || !a[1]) return DSERR_INVALIDPARAM; st32(a[1], (uint32_t)b->volume); return DS_OK; }
H(dsb_GetPan) { UNUSED; DsBuffer *b = buf_of(a[0]); if (!b || !a[1]) return DSERR_INVALIDPARAM; st32(a[1], (uint32_t)b->pan); return DS_OK; }
H(dsb_GetFrequency) { UNUSED; DsBuffer *b = buf_of(a[0]); if (!b || !a[1]) return DSERR_INVALIDPARAM; st32(a[1], b->rate); return DS_OK; }

H(dsb_GetStatus) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    uint32_t st = b && b->playing ? DSBSTATUS_PLAYING | (b->looping ? DSBSTATUS_LOOPING : 0) : 0;
    pthread_mutex_unlock(&ds_mu);
    if (!b || !a[1]) return DSERR_INVALIDPARAM;
    st32(a[1], st);
    return DS_OK;
}

H(dsb_Initialize) { UNUSED; return 0x8878000Au; /* DSERR_ALREADYINITIALIZED */ }

/* Lock(this, offset, bytes, &ptr1, &bytes1, &ptr2, &bytes2, flags) */
H(dsb_Lock) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (!b || b->primary || !b->bytes || !a[3] || !a[4]) {
        pthread_mutex_unlock(&ds_mu);
        return DSERR_INVALIDPARAM;
    }
    uint32_t off = a[1], len = a[2];
    if (a[7] & DSBLOCK_FROMWRITECURSOR) {
        uint32_t total = b->bytes / (uint32_t)b->align;
        off = (((uint32_t)(b->pos >> 32) + (b->playing ? b->rate * 15 / 1000 : 0)) % total) * (uint32_t)b->align;
    }
    if (a[7] & DSBLOCK_ENTIREBUFFER) len = b->bytes;
    uint32_t data = b->data, size = b->bytes;
    pthread_mutex_unlock(&ds_mu);
    if (off >= size || len > size || len == 0) return DSERR_INVALIDPARAM;
    uint32_t first = len < size - off ? len : size - off;
    st32(a[3], data + off);
    st32(a[4], first);
    if (a[5]) st32(a[5], len > first ? data : 0);
    if (a[6]) st32(a[6], len - first);
    return DS_OK;
}

/* Play(this, reserved, priority, flags) */
H(dsb_Play) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (b) {
        b->playing = 1;
        b->looping = (a[3] & DSBPLAY_LOOPING) != 0;
    }
    pthread_mutex_unlock(&ds_mu);
    return b ? DS_OK : DSERR_INVALIDPARAM;
}

H(dsb_SetCurrentPosition) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    int ok = b && !b->primary && b->align && a[1] < b->bytes;
    if (ok) b->pos = (uint64_t)(a[1] / (uint32_t)b->align) << 32;
    pthread_mutex_unlock(&ds_mu);
    return ok ? DS_OK : DSERR_INVALIDPARAM;
}

/* SetFormat(this, WAVEFORMATEX *): the primary buffer only. The mixer's own
 * output format does not depend on it. */
H(dsb_SetFormat) {
    UNUSED;
    DsBuffer *b = buf_of(a[0]);
    if (!b || !a[1]) return DSERR_INVALIDPARAM;
    if (!b->primary) return DSERR_INVALIDCALL;
    DsBuffer f = *b;
    if (!read_format(&f, a[1])) return DSERR_BADFORMAT;
    if (g_opt.verbose) rt_log("[dsound] primary format: %u Hz, %d bits, %d channels\n", f.rate, f.bits, f.channels);
    pthread_mutex_lock(&ds_mu);
    b->channels = f.channels, b->bits = f.bits, b->align = f.align, b->rate = f.rate;
    pthread_mutex_unlock(&ds_mu);
    return DS_OK;
}

H(dsb_SetVolume) {
    UNUSED;
    int32_t v = (int32_t)a[1];
    if (v > 0 || v < -10000) return DSERR_INVALIDPARAM;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (b) {
        b->volume = v;
        if (b->primary) master_gain = db_gain(v);
        else update_gain(b);
    }
    pthread_mutex_unlock(&ds_mu);
    return b ? DS_OK : DSERR_INVALIDPARAM;
}

H(dsb_SetPan) {
    UNUSED;
    int32_t v = (int32_t)a[1];
    if (v > 10000 || v < -10000) return DSERR_INVALIDPARAM;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (b) {
        b->pan = v;
        update_gain(b);
    }
    pthread_mutex_unlock(&ds_mu);
    return b ? DS_OK : DSERR_INVALIDPARAM;
}

/* SetFrequency(this, hz): 0 restores the buffer's own rate, which this
 * implementation does not keep separately; the game does not use it. */
H(dsb_SetFrequency) {
    UNUSED;
    if (a[1] != 0 && (a[1] < 100 || a[1] > 200000)) return DSERR_INVALIDPARAM;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (b && a[1]) b->rate = a[1];
    pthread_mutex_unlock(&ds_mu);
    return b ? DS_OK : DSERR_INVALIDPARAM;
}

H(dsb_Stop) {
    UNUSED;
    pthread_mutex_lock(&ds_mu);
    DsBuffer *b = buf_of(a[0]);
    if (b) b->playing = 0;
    pthread_mutex_unlock(&ds_mu);
    return b ? DS_OK : DSERR_INVALIDPARAM;
}

/* Unlock(this, ptr1, bytes1, ptr2, bytes2): the data was written in place. */
H(dsb_Unlock) { UNUSED; return buf_of(a[0]) ? DS_OK : DSERR_INVALIDPARAM; }
H(dsb_Restore) { UNUSED; return DS_OK; }

static const ComMethod buffer_methods[] = {
    {"QueryInterface", dsb_QueryInterface, 3}, {"AddRef", dsb_AddRef, 1}, {"Release", dsb_Release, 1},
    {"GetCaps", dsb_GetCaps, 2}, {"GetCurrentPosition", dsb_GetCurrentPosition, 3}, {"GetFormat", dsb_GetFormat, 4},
    {"GetVolume", dsb_GetVolume, 2}, {"GetPan", dsb_GetPan, 2}, {"GetFrequency", dsb_GetFrequency, 2},
    {"GetStatus", dsb_GetStatus, 2}, {"Initialize", dsb_Initialize, 3}, {"Lock", dsb_Lock, 8},
    {"Play", dsb_Play, 4}, {"SetCurrentPosition", dsb_SetCurrentPosition, 2}, {"SetFormat", dsb_SetFormat, 2},
    {"SetVolume", dsb_SetVolume, 2}, {"SetPan", dsb_SetPan, 2}, {"SetFrequency", dsb_SetFrequency, 2},
    {"Stop", dsb_Stop, 1}, {"Unlock", dsb_Unlock, 5}, {"Restore", dsb_Restore, 1},
    {"SetFX", NULL, 4}, {"AcquireResources", NULL, 4}, {"GetObjectInPath", NULL, 5},
};

/* ------------------------------------------------------------ IDirectSound8 */
H(ds_QueryInterface) { UNUSED; if (a[2]) st32(a[2], 0); return E_NOINTERFACE; }
H(ds_AddRef) { UNUSED; uint32_t n = ld32(a[0] + 12) + 1; st32(a[0] + 12, n); return n; }
H(ds_Release) { UNUSED; uint32_t n = ld32(a[0] + 12); if (n) st32(a[0] + 12, --n); return n; }

/* CreateSoundBuffer(this, DSBUFFERDESC *, IDirectSoundBuffer **, outer)
 * DSBUFFERDESC: size, flags, buffer bytes, reserved, WAVEFORMATEX *, 3D algorithm GUID. */
H(ds_CreateSoundBuffer) {
    UNUSED;
    uint32_t desc = a[1];
    if (!desc || !a[2] || ld32(desc) < 20) return DSERR_INVALIDPARAM;
    uint32_t flags = ld32(desc + 4), bytes = ld32(desc + 8), fmt = ld32(desc + 16);
    DsBuffer nb;
    memset(&nb, 0, sizeof nb);
    nb.used = 1;
    nb.refs = 1;
    nb.flags = flags;
    nb.channels = 2, nb.bits = 16, nb.align = 4, nb.rate = 22050;
    if (flags & DSBCAPS_PRIMARYBUFFER) {
        if (bytes || fmt) return DSERR_INVALIDPARAM;
        nb.primary = 1;
    } else {
        if (!fmt || !read_format(&nb, fmt)) return DSERR_BADFORMAT;
        if (bytes < 4 || bytes > 0x0FFFFFFF) return DSERR_INVALIDPARAM;
        bytes -= bytes % (uint32_t)nb.align;
        nb.bytes = bytes;
        nb.data = rt_heap_alloc(bytes, 0);
        if (!nb.data) return DSERR_OUTOFMEMORY;
        memset(G(nb.data), nb.bits == 8 ? 0x80 : 0, bytes); /* silence */
    }
    update_gain(&nb);
    pthread_mutex_lock(&ds_mu);
    int i;
    for (i = 0; i < MAX_BUFFERS; i++)
        if (!bufs[i].used) break;
    if (i < MAX_BUFFERS) bufs[i] = nb;
    pthread_mutex_unlock(&ds_mu);
    if (i == MAX_BUFFERS) {
        if (nb.data) rt_heap_free(nb.data);
        return DSERR_OUTOFMEMORY;
    }
    if (g_opt.verbose)
        rt_log("[dsound] buffer %d: %s, flags %#x, %u bytes, %u Hz, %d bits, %d channels\n", i,
               nb.primary ? "primary" : "secondary", flags, nb.bytes, nb.rate, nb.bits, nb.channels);
    st32(a[2], rt_com_object(vt_buffer, (uint32_t)i, MAGIC_DSBUF));
    return DS_OK;
}

/* GetCaps(this, DSCAPS *): a software device that plays everything. */
H(ds_GetCaps) {
    UNUSED;
    if (!a[1] || ld32(a[1]) < 96) return DSERR_INVALIDPARAM;
    uint32_t size = ld32(a[1]);
    memset(G(a[1]), 0, size);
    st32(a[1], size);
    st32(a[1] + 4, 0x00000F5Fu);   /* primary and secondary, mono/stereo, 8/16 bit, continuous rate, emulated driver */
    st32(a[1] + 8, 100);           /* dwMinSecondarySampleRate */
    st32(a[1] + 12, 200000);       /* dwMaxSecondarySampleRate */
    st32(a[1] + 16, 1);            /* dwPrimaryBuffers */
    return DS_OK;
}

H(ds_SetCooperativeLevel) { UNUSED; return a[2] >= 1 && a[2] <= 4 ? DS_OK : DSERR_INVALIDPARAM; }
H(ds_Compact) { UNUSED; return DS_OK; }
H(ds_GetSpeakerConfig) { UNUSED; if (!a[1]) return DSERR_INVALIDPARAM; st32(a[1], 4 /* DSSPEAKER_STEREO */); return DS_OK; }
H(ds_SetSpeakerConfig) { UNUSED; return DS_OK; }
H(ds_Initialize) { UNUSED; return 0x8878000Au; }

static const ComMethod dsound_methods[] = {
    {"QueryInterface", ds_QueryInterface, 3}, {"AddRef", ds_AddRef, 1}, {"Release", ds_Release, 1},
    {"CreateSoundBuffer", ds_CreateSoundBuffer, 4}, {"GetCaps", ds_GetCaps, 2}, {"DuplicateSoundBuffer", NULL, 3},
    {"SetCooperativeLevel", ds_SetCooperativeLevel, 3}, {"Compact", ds_Compact, 1},
    {"GetSpeakerConfig", ds_GetSpeakerConfig, 2}, {"SetSpeakerConfig", ds_SetSpeakerConfig, 2},
    {"Initialize", ds_Initialize, 2}, {"VerifyCertification", NULL, 2},
};

/* DirectSoundCreate8(device GUID, IDirectSound8 **, outer) */
H(ds_DirectSoundCreate8) {
    UNUSED;
    if (!a[1]) return DSERR_INVALIDPARAM;
    if (g_opt.no_sound) {
        static int said;
        if (!__atomic_exchange_n(&said, 1, __ATOMIC_SEQ_CST))
            rt_log("recomp: DirectSoundCreate8: --no-sound, reporting no sound device\n");
        st32(a[1], 0);
        return DSERR_NODRIVER;
    }
    pthread_mutex_lock(&ds_mu);
    if (!vt_dsound) {
        vt_dsound = rt_com_vtable("dsound.dll", "IDirectSound8", dsound_methods, RT_COUNTOF(dsound_methods));
        vt_buffer = rt_com_vtable("dsound.dll", "IDirectSoundBuffer8", buffer_methods, RT_COUNTOF(buffer_methods));
        dsound_obj = rt_com_object(vt_dsound, 0, MAGIC_DSOUND);
        st32(dsound_obj + 12, 0);
    }
    st32(dsound_obj + 12, ld32(dsound_obj + 12) + 1);
    mixer_start();
    pthread_mutex_unlock(&ds_mu);
    st32(a[1], dsound_obj);
    return DS_OK;
}

static const ImportDef defs[] = {
    {"dsound.dll", "DirectSoundCreate8", ds_DirectSoundCreate8, 3, 0},
};
RT_EXPORT_IMPORTS(rt_imports_dsound, defs);
