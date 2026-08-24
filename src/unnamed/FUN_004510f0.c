/* FUN_004510f0 - 0x004510f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both off iVar4 = *(param_1+0x10) (the [eax+0x10] record the resolver shows), at +0x3c and +0x260.
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EAX is the projectile registry,
 * &DAT_006a7f88 + g_clientContext, at all 19 binary call sites -- 13 as
 * `add eax, 0x6a7f88` after loading [0x5b3484], 6 as `lea eax,[ctx+0x6a7f88]`
 * with the base register traced to the same global.  Its siblings
 * FUN_00451030 / FUN_004511b0 / FUN_00450810 / bd0 / dd0 were recovered to the
 * identical value earlier, and the body walks it the same way they do
 * (*(regEax+4) -> +0x1c chain).  Six of the lea sites have a branch between
 * the load and the call; accepted because every alternative path in those
 * callers that reaches this call also passes through the same ctx load.
 */
#include "ghidra_types.h"


int FUN_004510f0(int param_1,int regEax)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while( true ) {
    if (0x1f5 < uVar1) {
      return 0;
    }
    if (uVar1 == 0x1f5) break;
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

