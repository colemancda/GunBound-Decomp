/* FUN_004061e0 - 0x004061e0 in the original binary.
 *
 * Mouse-hit-test dispatcher: sole caller is WndProc's WM_MOUSEMOVE handler
 * (0x41023a-0x41023f: `mov edx,esi[mouseY]; mov ecx,edi[mouseX]; mov
 * eax,0xe9be90[widget root]; call 0x4061e0`), tracking which widget the
 * mouse is currently over for enter/leave callbacks.
 *
 * DROPPED REGISTER ARGUMENTS (pattern #1) - investigated, NOT fixed here:
 * this function reads `in_EAX` (should be the fixed widget-root
 * DAT_00e9be90, confirmed at the caller above) but ALSO silently drops its
 * own incoming ECX/EDX (mouseX/mouseY - Ghidra's decompile missed these
 * registers entirely, there's no `in_ECX`/`in_EDX` placeholder at all).
 * Both are threaded straight through, unmodified, into the
 * `FUN_0040cea0()` call (currently invoked with zero args) - which is
 * ITSELF a raw/unfixed dropped-register function (own header: `in_EAX`,
 * `unaff_ESI`) with 4 callers (FUN_00406120, FUN_00406170, FUN_004061e0,
 * FUN_0040ce50), each supplying its EAX/ECX/EDX/ESI inputs via a different
 * partial register-passthrough chain from ITS OWN caller. Fixing any one
 * of these 5 functions correctly requires fixing all of them together in
 * the same pass (same class of undertaking as FindSpriteFrame.c's/
 * BlitSpriteText.c's documented caller fan-out) - not attempted here.
 */
#include "ghidra_types.h"


undefined4 FUN_004061e0(void)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  int *piVar3;
  
  piVar3 = (int *)FUN_0040cea0();
  piVar1 = *(int **)(in_EAX + 8);
  if (piVar1 != piVar3) {
    if ((((piVar1 != (int *)0x0) && (iVar2 = piVar1[9], iVar2 != 3)) && (iVar2 != 4)) &&
       (iVar2 != 5)) {
      FUN_00405e30();
    }
    *(undefined4 *)(in_EAX + 8) = 0;
    if (piVar3 != (int *)0x0) {
      *(int **)(in_EAX + 8) = piVar3;
      if (((*(int **)(in_EAX + 0xc) == piVar3) && (piVar3[9] != 3)) && (piVar3[9] != 5)) {
        (**(code **)(*piVar3 + 4))(&DAT_00551e78);
      }
      if (((*(int *)(in_EAX + 0xc) == 0) && (iVar2 = piVar3[9], iVar2 != 3)) &&
         ((iVar2 != 4 && (iVar2 != 5)))) {
        (**(code **)(*piVar3 + 4))(s_mouse_00551e70);
        AcquireSoundChannel(0);
      }
      return 1;
    }
  }
  return 0;
}

