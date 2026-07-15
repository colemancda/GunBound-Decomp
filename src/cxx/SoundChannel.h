/* CSoundChannel / CPrimaryStreamChannel - promoted from the raw C ports
 * src/unnamed/FUN_004ef7e0.c (shared base construction),
 * src/unnamed/FUN_004ef3a0.c (secondary-channel ctor),
 * src/unnamed/FUN_004ef5b0.c (secondary-channel stop),
 * src/unnamed/FUN_004eebe0.c (primary-channel ctor), and
 * src/unnamed/FUN_004eef00.c (primary-channel stop). See SoundChannel.cpp
 * and src/cxx/README.md.
 *
 * CONFIRMED: the object sizes (0x50/0xb8, matching each raw ctor's own
 * `operator_new` call size at its sole caller, InitDirectSound.c), the
 * 3-stage vtable-swap construction sequence (e0 transient -> e8 -> cc for
 * the primary channel; e0 transient -> e8 permanent for the secondary
 * channel - see globals.c's PTR_LAB_005574e0/e8/cc comments), and every
 * field offset a known method actually touches.
 *
 * NOT YET REAL C++ VIRTUAL DISPATCH: both vtables (globals.c's
 * PTR_LAB_005574cc[7]/PTR_LAB_005574e8[5]) still have 2-3 slots pointing
 * at un-cross-referenced addresses (0x4eed10, 0x4ef4c0, 0x4ef610) that
 * haven't been decompiled/ported yet - a class can't safely declare
 * `virtual` methods for slots it has no implementation for. `vtable` is
 * therefore kept as a plain `void *` data member, written explicitly
 * (same non-virtual style as ValueGuard.h/CValueGuard) rather than
 * relying on the compiler to generate one. Revisit once those 3
 * functions are identified - see PollSoundBufferPosition.c and
 * DecodeSoundBufferChunk.c for the sibling slots that ARE already named.
 *
 * GUESSED: several field purposes (m_unk14/m_unk9c/etc - zeroed by a
 * ctor but never read by any currently-known method) are kept as opaque
 * gaps until traced.
 */
#ifndef GB_CXX_SOUNDCHANNEL_H
#define GB_CXX_SOUNDCHANNEL_H

#include "gb_common.h"
#include <windows.h>

/* CSoundChannel - 0x50-byte object, `secondary` DirectSound streaming
 * buffer (InitDirectSound's DSBUFFERDESC-less secondary channel). Also
 * the shared first stage of CPrimaryStreamChannel's construction - the
 * secondary channel simply IS this class fully constructed (no further
 * specialization), matching FUN_004ef3a0 doing nothing beyond the
 * shared setup FUN_004ef7e0/FUN_004ef3a0 both perform.
 */
class CSoundChannel {
public:
    /* FUN_004ef7e0 + FUN_004ef3a0's shared setup, combined (both always
     * ran back-to-back at every real call site - see FUN_004ef3a0.c).
     * Leaves vtable = PTR_LAB_005574e8 (the "channel fully constructed,
     * no primary-only extras" state). */
    CSoundChannel();

    /* FUN_004ef5b0 (vtable slot 3, "stop/release channel"). NOT virtual
     * (see class header note) - CPrimaryStreamChannel provides its own
     * Stop() that hides this one, matching each class's real vtable
     * slot 3 pointing at a different function. */
    void Stop();

    void   *vtable;                    /* +0x00 */
    void   *m_threadHandle;            /* +0x04: _beginthread() return, or 0 on failure */
    HANDLE  m_event1;                  /* +0x08 */
    HANDLE  m_event2;                  /* +0x0c */
    u8      m_running;                 /* +0x10: 1 if the worker thread started, else 0 */
    u8      m_pad11[3];
    u32     m_unk14;                   /* +0x14: zeroed by the ctor, untraced */
    u32     m_unk18;                   /* +0x18: untraced gap */
    u32     m_unk1c;                   /* +0x1c: untraced gap */
    CRITICAL_SECTION m_lock;           /* +0x20..+0x37 (24 bytes) */
    s32     m_bufferIndex;             /* +0x38: index into DAT_00793558's registry; -1 = none */
    u32     m_unk3c[4];                /* +0x3c..+0x4b: untraced gap */
    u8      m_decoding;                /* +0x4c: cleared by Stop() */
    u8      m_pad4d[3];
};
GB_STATIC_ASSERT(sizeof(CSoundChannel) == 0x50, CSoundChannel_size);

/* CPrimaryStreamChannel - 0xb8-byte object, the `primary` DirectSound
 * buffer. Same first 0x50 bytes as CSoundChannel (built the same way),
 * then adds double-buffering fields and swaps to its own vtable
 * (PTR_LAB_005574cc) at the end of construction. */
class CPrimaryStreamChannel : public CSoundChannel {
public:
    /* FUN_004eebe0: runs CSoundChannel's shared setup (inline, not via
     * the base ctor, matching the original's flat non-virtual-base
     * layout), then the primary-only extras, then swaps vtable to
     * PTR_LAB_005574cc. */
    CPrimaryStreamChannel();

    /* FUN_004eef00 (vtable slot 3 in PTR_LAB_005574cc) - hides
     * CSoundChannel::Stop(), not an override (see class header note). */
    void Stop();

    u32     m_streamActive;            /* +0x50: gates Stop()'s buffer teardown */
    u8      m_unk54[0x44];             /* +0x54..+0x97: untraced gap (68 bytes) */
    void   *m_buffer1;                 /* +0x98: freed by Stop() */
    u32     m_unk9c;                   /* +0x9c: zeroed by the ctor, untraced */
    u32     m_timeoutMs;               /* +0xa0: ctor sets 20000 */
    u32     m_unka4;                   /* +0xa4: zeroed by the ctor and by Stop() */
    void   *m_buffer2;                 /* +0xa8: freed by Stop() */
    u32     m_unkac;                   /* +0xac: zeroed by the ctor and by Stop() */
    u32     m_defaultVolume;           /* +0xb0: ctor sets DAT_00588f44 */
    s32     m_unkb4;                   /* +0xb4: ctor sets -1 */
};
GB_STATIC_ASSERT(sizeof(CPrimaryStreamChannel) == 0xb8, CPrimaryStreamChannel_size);

#endif /* GB_CXX_SOUNDCHANNEL_H */
