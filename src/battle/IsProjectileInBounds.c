/* IsProjectileInBounds - 0x00458850 in the original binary.
 *
 * CProjectile's vtable slot 7 (see src/cxx/Projectile.h) and the single
 * highest-leverage uncarved slot in the tree: FORTY vtables reference it.
 * NEW CARVE (2026-08-19): Ghidra never carved this range as a function - it
 * is reachable only through the projectile vtables - so this port is
 * hand-derived instruction-by-instruction from the capstone disassembly of
 * 0x458850..0x458910 (no decompile existed).
 *
 * What it does: a world-bounds test on the projectile's guarded position,
 * short-circuit ANDed, returning true only while the projectile is still
 * inside the play area.  Two distinct exits confirm the bool return
 * (`mov al,1; ret` at 0x458904 / `xor al,al; ret` at 0x45890c); 0 stack args
 * with `this` in ECX.
 *
 *   x = Peek(this + 0xf54)                        the X position cell
 *   if (x <  Peek(ctx + 0x6a9b78)) return false;   left bound
 *   if (x >= Peek(ctx + 0x6a9d9c)) return false;   right bound
 *   y-cell = this + 0x1178                        the Y position cell
 *   if (y >= Peek(ctx + 0x6aa1e4)) return false;   bottom bound (FUN_0040b450
 *                                                  is the two-cell >= test)
 *   if (y <  -1000)                return false;   top bound, a literal
 *   return true;
 *
 * RESOLVES A GAP the 2026-07-15 angr pass left open.  Projectile.h's slot-7
 * note recorded "cell targets not resolvable" for the first two comparisons
 * and called the role GUESSED.  Both targets are plain g_clientContext
 * offsets - 0x6a9b78 and 0x6a9d9c - and the decisive detail is that they,
 * 0x6a9fc0 and 0x6aa1e4 are CONSECUTIVE 0x224-byte CValueGuard cells
 * (0x6a9d9c - 0x6a9b78 = 0x224, 0x6aa1e4 - 0x6a9d9c = 0x448).  A guarded
 * quadruple of world bounds compared against the projectile's own X and Y
 * cells makes the role a bounds test rather than a guess.
 *
 * The two object cells match what DetonateProjectile already uses on the same
 * object (+0xf54 X, +0x1178 Y - the pair ApplyBlastDamage and the terrain
 * column scans read), which cross-confirms the identification.
 *
 * Raw/near-verbatim hand port - not hand-verified against a running client.
 * See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"
#include <windows.h>


bool __fastcall IsProjectileInBounds(int param_1)

{
  int iVar1;
  int iVar2;

  /* orig 0x458863-0x45889e: both peeks inside one critical section, then
   * `cmp ebx,eax / setl bl` and a jump to the false exit when set. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x6a9b78));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 < iVar2) {
    return false;
  }
  /* orig 0x4588a0-0x4588d1: same shape, `setge bl` this time. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x6a9d9c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 <= iVar1) {
    return false;
  }
  /* orig 0x4588d3-0x4588ff: the Y cell against a bound cell and a literal. */
  if (FUN_0040b450(param_1 + 0x1178,g_clientContext + 0x6aa1e4) != false) {
    return false;
  }
  if (PacketChecksumLessThan((void *)(param_1 + 0x1178),-1000) != '\0') {
    return false;
  }
  return true;
}
