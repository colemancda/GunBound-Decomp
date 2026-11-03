/* FindLightningHazardAt - 0x004511b0 in the original binary.
 * (Historical notes below: FUN_004510f0 is now FindFirewallHazardAt.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the layer key 0x1f6 is the one
 * SpawnLightningHazard stamps and RenderWeatherHazards maps to the
 * lightning texture. EAX is the projectile registry (&DAT_006a7f88 +
 * g_clientContext) at every call site; callers (the Simulate*Bullet* and
 * SimulateProjectileFrame family, plus the hazard spawner) pass a
 * coordinate and get the matching hazard object or NULL; the match is a
 * window around the object's guarded position cell.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: FUN_004510f0's twin, same two cells.
 */
#include "ghidra_types.h"


int FindLightningHazardAt(int param_1,int regEax)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while( true ) {
    if (0x1f6 < uVar1) {
      return 0;
    }
    if (uVar1 == 0x1f6) break;
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  iVar4 = *(int *)(iVar4 + 0x10);
  if (*(char *)(iVar4 + 0x15) != '\0') {
    return 0;
  }
  while( true ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(iVar4 + 0x3c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(iVar4 + 0x260));
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

