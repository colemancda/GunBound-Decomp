/* CFlameEffect::Tick - the one effect-family method whose raw port already
 * exists (src/battle/TickFlameEffect.c, renamed from FUN_00471c70.c
 * alongside this promotion; CSuperFlameEffect shares the same implementation as its own
 * slot 2).  Re-expressed here against the named CFlameEffect fields; the
 * raw C port stays the linking reference until this is byte-verified
 * (PLAN.md ground rules).
 *
 * Original 0x471c70, __fastcall(this):
 *   AdvanceSpriteAnimation(this)
 *   if (m_finished) m_dead = 1                 ; registry prunes it
 *   step = (ctx+0x45578 byte set) ? 5 : 2      ; fast-forward toggle
 *   div  = Peek(&DAT_00e9bed8)                 ; guarded frame divisor
 *   m_animPhase = (m_animPhase + step) % div
 *   return (m_animPhase + step) / div          ; whole frames advanced
 *
 * The other three slot-2/slot-3 bodies (flame Draw 0x471d00, super-flame
 * Draw 0x47ead0, rider Tick/Draw 0x4a2920/0x4a2a00) are UNPORTED - Ghidra
 * never carved them; they are only reachable through these vtables.
 */
#include "Effects.h"

extern "C" {
void AdvanceSpriteAnimation(int animObj);
int PeekPacketChecksumState(void *self);
extern unsigned char DAT_00e9bed8;      /* guarded frame-divisor cell */
extern int g_clientContext;
void EnterCriticalSection_shim(void *);  /* not used - see note below */
extern unsigned char DAT_005a9068[];     /* the guard critical section */
}

/* The raw port brackets both peeks with EnterCriticalSection/
 * LeaveCriticalSection(&DAT_005a9068) via windows.h; this TU avoids
 * dragging windows.h into the C++ tree the same way ValueGuard.cpp does -
 * the lock calls stay in the raw C port, which remains the linking
 * reference.  This body documents the logic against named fields. */
int CFlameEffect::Tick()
{
    AdvanceSpriteAnimation(reinterpret_cast<int>(this));
    if (m_finished != 0) {
        m_dead = 1;
    }
    int step = (*reinterpret_cast<char *>(g_clientContext + 0x45578) != 0) ? 5 : 2;
    int div = PeekPacketChecksumState(&DAT_00e9bed8);
    int next = m_animPhase + step;
    m_animPhase = next % div;
    return next / div;
}
