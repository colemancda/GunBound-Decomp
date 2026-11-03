/* FindTornadoHazardAt - 0x00451030 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the layer key 500 is the one
 * SpawnTornadoHazard stamps and RenderWeatherHazards maps to the tornado
 * texture. EAX is the projectile registry (&DAT_006a7f88 +
 * g_clientContext) at every call site; callers (the Simulate*Bullet* and
 * SimulateProjectileFrame family, plus the hazard spawner) pass a
 * coordinate and get the matching hazard object or NULL; the match is a
 * window around the object's guarded position cell.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both off iVar4,
 * the list node found by the 0x1f5-id walk above (`mov esi,[eax+0x10]`
 * = the C's own `iVar4 = *(int *)(iVar4 + 0x10)`), at +0x38 and +0x25c
 * - the FUN_004510f0/FUN_004511b0 twins read the same node at
 * +0x3c/+0x260, i.e. the neighbouring cells.
 */
#include "ghidra_types.h"


int FindTornadoHazardAt(int param_1,int regEax)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while( true ) {
    if (500 < uVar1) {
      return 0;
    }
    if (uVar1 == 500) break;
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  iVar4 = *(int *)(iVar4 + 0x10);
  if (*(char *)(iVar4 + 0x15) != '\0') {
    return 0;
  }
  while( true ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(iVar4 + 0x38));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(iVar4 + 0x25c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
    if ((iVar2 - iVar3 < param_1) && (param_1 < iVar2 + iVar3)) break;
    iVar4 = *(int *)(iVar4 + 0x10);
    if (*(char *)(iVar4 + 0x15) != '\0') {
      return 0;
    }
  }
  return iVar4;
}

