/* FUN_004ff640 - 0x004ff640 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the twin of FUN_004fe6a0 for a
 * different notification - EAX is the NODE (`mov edi,eax` at 0x4ff642,
 * socket closed at +8, erased via FUN_004ff720 after `add esi,4` steps
 * to the raw list at engine+4). Its virtual through *param_1+4 was also
 * short: the binary pushes EDI then EBX (0x4ff648/0x4ff649), so it
 * receives (regEbx, node). The one call site is
 * CommEngineNotifyWndProc's 0x10 arm, where the node is the puVar1 the
 * dispatch walk just found - `mov eax,edi` at 0x4fe745 holds it in EAX
 * for every arm.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ff640(int *param_1,int regEbx,int *regEax)

{
  int *in_EAX = regEax;
  int *piVar1;
  
  (**(code **)(*param_1 + 4))(regEbx,in_EAX);
  if ((regEbx != 0) && (piVar1 = (int *)param_1[1], piVar1 != (int *)0x0)) {
    while (in_EAX != piVar1) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if (in_EAX[2] != 0xffffffff) {
      closesocket(in_EAX[2]);
    }
    FUN_004ff720(param_1 + 1,in_EAX);
  }
  return;
}

