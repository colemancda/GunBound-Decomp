/* FindMobileSlotAtPoint - 0x0043c550 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40). Walks the active-object layer for class 100001 (the
 * player mobiles, per HitTestMobilesAndJewels / FindActiveObjectLayer) and
 * returns the player slot (object +8, masked & 7) of the first mobile whose
 * per-object probe FUN_0045d640(x, y) accepts the point, or -1 for none.
 * It is the slot-returning twin of HitTestMobilesAndJewels, which runs the
 * same FUN_0045d640 probe over the same layer but returns only a hit flag.
 * Before probing, each mobile is gated on a guarded bit test (cells
 * +0x908/+0x909/+0x90a); what that bit means is not established here.
 *
 * Caller evidence: the sole caller, State11_InBattle_HandleMouseInput
 * (call at 0x4baa0d) passes the mouse position plus camera offset,
 * g_nCameraX - 400 + mouseX and g_nCameraY - 0x12a + mouseY, and uses the
 * result as an index into eight-entry per-slot tables in the client
 * context (+0x457a9 stride 9, +0x457f1 stride 0xd, +0x4591c stride 2,
 * +0x4593c / +0x4597c stride 4) to copy per-player strings out. Both
 * arguments are world coordinates; -1 is tested against by the caller.
 */
#include "ghidra_types.h"


uint FindMobileSlotAtPoint(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  
  iVar1 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (0x186a1 < uVar2) {
      return 0xffffffff;
    }
    if (uVar2 == 0x186a1) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  iVar4 = *(int *)(iVar1 + 0x10);
  if (iVar1 == iVar4) {
    return 0xffffffff;
  }
  while( true ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((byte)(*(byte *)(iVar4 + 0x908) + *(byte *)(iVar4 + 0x909) + -0x34) ==
        *(char *)(iVar4 + 0x90a)) {
      cVar3 = '\x01' - ((*(byte *)(iVar4 + 0x909) >> (*(byte *)(iVar4 + 0x908) & 7) & 1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      cVar3 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((cVar3 == '\x01') && (cVar3 = FUN_0045d640(param_1,param_2), cVar3 != '\0')) break;
    iVar4 = *(int *)(iVar4 + 0x10);
    if (iVar1 == iVar4) {
      return 0xffffffff;
    }
  }
  return *(uint *)(iVar4 + 8) & 7;
}

