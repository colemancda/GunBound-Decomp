/* CSoundChannel / CPrimaryStreamChannel methods - see SoundChannel.h. */
#include "SoundChannel.h"
#include <process.h>   /* for uintptr_t only - _beginthread's own decl is _MT-guarded, see below */

extern "C" {
extern void *PTR_LAB_005574e0[4];
extern void *PTR_LAB_005574e8[5];
extern void *PTR_LAB_005574cc[7];
extern int  *DAT_00793558;   /* registry of "stream reader" handles, indexed by m_bufferIndex */
extern u32   DAT_00588f44;   /* default volume/pan-ish constant poked into new primary channels */
void FUN_004ef870(void *arg);        /* __beginthread thunk -> AudioStreamThreadProc (0x4ef870) */
void CloseSpriteReadState(void);     /* shared stream-reader teardown, despite the sprite-ish name */
/* process.h's real declaration is guarded by `#ifdef _MT`, which this
 * project's build doesn't define - declared directly here instead,
 * matching the prototype every other __beginthread call site in this
 * codebase already relies on implicitly (K&R fallback in C, not legal
 * in C++). Decorates to `__beginthread` via ordinary __cdecl name
 * mangling, matching the raw C ports' literal `__beginthread(...)` call
 * spelling. */
uintptr_t __cdecl _beginthread(void (__cdecl *start_address)(void *), unsigned stack_size, void *arglist);
}

/* 0x4ef7e0 + 0x4ef3a0's shared setup. Every real call site ran both back
 * to back (see FUN_004ef3a0.c's header) - combined here since neither is
 * ever used standalone. */
CSoundChannel::CSoundChannel()
{
    vtable = &PTR_LAB_005574e0;   /* transient - overwritten below */
    m_threadHandle = 0;
    m_event1 = CreateEventA(0, 0, 0, 0);
    m_event2 = CreateEventA(0, 0, 0, 0);
    m_running = 0;

    vtable = &PTR_LAB_005574e8;
    m_unk14 = 0;
    m_bufferIndex = -1;
    m_decoding = 0;
    InitializeCriticalSection(&m_lock);
    m_running = 1;
    m_threadHandle = (void *)_beginthread(FUN_004ef870, 0, this);
    if (m_threadHandle == 0) {
        m_running = 0;
    }
}

/* 0x4ef5b0 (PTR_LAB_005574e8 vtable slot 3). */
void CSoundChannel::Stop()
{
    EnterCriticalSection(&m_lock);
    if (m_unk14 != 0) {
        int *reader = (int *)DAT_00793558[m_bufferIndex];
        (*(void (__stdcall **)(int *))(*(int *)reader + 0x48))(reader);
        CloseSpriteReadState();
        m_unk14 = 0;
        m_decoding = 0;
    }
    m_bufferIndex = -1;
    LeaveCriticalSection(&m_lock);
}

/* 0x4eebe0: runs the same CSoundChannel setup inline (matching the
 * original's flat, non-virtual-base object layout - there's no separate
 * CSoundChannel sub-object to construct, just the same field pokes at
 * the same offsets), then the primary-only extras, then swaps to
 * PTR_LAB_005574cc. */
CPrimaryStreamChannel::CPrimaryStreamChannel()
    : CSoundChannel()
{
    m_streamActive = 0;
    m_buffer1 = 0;
    m_unk9c = 0;
    m_unka4 = 0;
    m_buffer2 = 0;
    m_unkac = 0;
    vtable = &PTR_LAB_005574cc;
    m_timeoutMs = 20000;
    m_defaultVolume = DAT_00588f44;
    m_unkb4 = -1;
}

/* 0x4eef00 (PTR_LAB_005574cc vtable slot 3) - same shape as
 * CSoundChannel::Stop() plus the double-buffer teardown. */
void CPrimaryStreamChannel::Stop()
{
    EnterCriticalSection(&m_lock);
    if (m_streamActive != 0) {
        int *reader = (int *)DAT_00793558[m_bufferIndex];
        (*(void (__stdcall **)(int *))(*(int *)reader + 0x48))(reader);
        free(m_buffer1);
        free(m_buffer2);
        m_buffer1 = 0;
        m_unka4 = 0;
        m_buffer2 = 0;
        m_unkac = 0;
        CloseSpriteReadState();
        m_streamActive = 0;
        m_decoding = 0;
    }
    LeaveCriticalSection(&m_lock);
}
