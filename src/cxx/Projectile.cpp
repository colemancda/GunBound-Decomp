/* CProjectile methods - promoted from the raw C ports under src/battle/
 * (DestroyProjectile 0x455570, AnimateProjectileTick 0x48f1c0). See
 * Projectile.h and src/cxx/README.md.
 *
 * Only these two methods are promoted so far - SimulateProjectileFrame
 * (0x455cc0, ~660 lines) and DetonateProjectile (0x4572b0, ~610 lines)
 * are large enough to be their own follow-up unit of work, and
 * InitProjectile (0x454dc0) is the ~29-guard-cell constructor body,
 * whose individual field offsets are not yet mapped to real names (see
 * Projectile.h's "left as padding" note) - promoting it faithfully means
 * preserving the exact same raw offsets, not inventing a cleaner layout.
 *
 * Both ports below keep the SAME register-passed-cell-pointer gap the
 * raw C already had: DestroyProjectile's ScrambleChecksumGuardBytes/
 * TreeLowerBound calls and AnimateProjectileTick's PeekPacketChecksumBool/
 * PeekPacketChecksumState/EncodeOutgoingPacketField calls never show a
 * cell argument in Ghidra's decompile (the real cell pointer arrives via
 * a register Ghidra didn't resolve, same class of issue as Widget.cpp's
 * asm-capture shims) - rather than invent an unverified register capture,
 * these stay exactly as free-function calls with the same argument shape
 * the raw port had. Byte-verify before trusting this beyond "same
 * behavior as the raw C, now living on the class."
 *
 * score.sh status (2026-07-12):
 *  - AnimateProjectileTick: 3200/4500 - a real but partial match, likely
 *    limited by the same unresolved cell-pointer gap above.
 *  - ~CProjectile (dtor): 39655/39600 (worse than max - essentially no
 *    byte match). Root cause found: DestroyProjectile.c's `local_4`
 *    (written before every one of the 29 checks, never read in the
 *    visible C) plus the `unaff_FS_OFFSET`/`puStack_8` frame push at the
 *    top is real MSVC SEH scaffolding (a `_except_handler3`-style
 *    exception-registration record with `local_4` as the per-block
 *    unwind-state marker) - the original genuinely wraps this destructor
 *    body in `__try`/`__finally`. This port strips that scaffolding
 *    entirely (same accepted tradeoff as other SEH-bearing functions in
 *    this tree - see src/README.md), which accounts for a real size gap
 *    (compiled here: 0x340 bytes vs. the original's 0x5e8) on top of the
 *    already-known cell-pointer gap. Reproducing real `__try`/`__finally`
 *    to close this is unstarted follow-up work, not attempted here. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "Projectile.h"

extern "C" {
void ScrambleChecksumGuardBytes(void);
void TreeLowerBound(void *scratch);
void AdvanceSpriteAnimation(void);
void FUN_004585e0(void);
char PeekPacketChecksumBool(void);
int PeekPacketChecksumState(void);
void EncodeOutgoingPacketField(unsigned int value);
extern CRITICAL_SECTION DAT_005a9068; /* the guard family's shared lock, defined in ValueGuard.cpp */
}

/* 0x455570 DestroyProjectile, vtable slot 0. Releases the object's 29
 * CValueGuard/GuardedBool cells whose registry handle is still live (scans
 * the same field offsets InitProjectile wrote), highest offset first, then
 * swaps in the "being destroyed" vtable. Field offsets AND control-flow
 * shape are copied verbatim from the raw port (29 unrolled if-blocks, not
 * a loop) - MSVC 7.1 does not codegen a hand-written loop the same as its
 * own unrolled original, so a loop+table version scored essentially zero
 * match (39480/39600) before this rewrite. `scratch` is a fresh 8-byte
 * stack buffer, exactly like the raw port's `local_14` - NOT `this`. */
CProjectile::~CProjectile()
{
    unsigned int *self = reinterpret_cast<unsigned int *>(this);
    unsigned char scratch[8];

    if (self[0xf60] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xed7] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xe4d] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xd80] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xcf7] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xc6b] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xbe2] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xb59] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xad0] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xa47] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x9be] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x935] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x8ac] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x823] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x79a] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x710] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x687] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x5fe] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x575] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x4ec] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x463] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x3da] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x34b] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x2c2] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x239] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x1b0] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x127] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x9e]  != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x15]  != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
}

/* 0x48f1c0 AnimateProjectileTick, vtable slot 2. Per-frame animate tick:
 * dispatch DetonateProjectile (was a manual vtable-slot-6 call in the raw
 * port - now a real virtual call, the same operation), advance the sprite
 * animation, then bump the +0x3b44 frame counter and fire a replay event
 * (EncodeOutgoingPacketField) once it reaches 5. */
void CProjectile::AnimateProjectileTick()
{
    DetonateProjectile();
    FUN_004585e0();
    AdvanceSpriteAnimation();
    if (PeekPacketChecksumBool() != 0) {
        EnterCriticalSection(&DAT_005a9068);
        EncodeOutgoingPacketField(PeekPacketChecksumState() + 1);
        LeaveCriticalSection(&DAT_005a9068);
    }
    unsigned int *frameCounter = reinterpret_cast<unsigned int *>(
        reinterpret_cast<char *>(this) + 0x3b44);
    unsigned int next = *frameCounter + 1;
    *frameCounter = next;
    if (next == 5) {
        EnterCriticalSection(&DAT_005a9068);
        EncodeOutgoingPacketField(PeekPacketChecksumState());
        LeaveCriticalSection(&DAT_005a9068);
    }
}
