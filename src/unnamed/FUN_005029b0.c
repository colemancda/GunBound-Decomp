/* FUN_005029b0 - 0x005029b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * UNRESOLVED (2026-09-20): the FUN_00502b70(unaff_EDI,param_2,1) call is
 * missing FUN_00502b70's own leading `this` (ECX) arg - orig 0x5029f7:
 * `mov ecx,[esp+0x18]` right before the 3 pushes, i.e. this function's
 * OWN third stack argument. That argument isn't represented anywhere in
 * this function's current (buggy, 2-param plus `unaff_EDI`) signature,
 * so it can't be threaded through without also fixing this function's
 * own parameter list, which is a separate, out-of-scope bug. See
 * FUN_00502b70.c's own header for the full reconstruction.
 */
#include "ghidra_types.h"


int * FUN_005029b0(int *param_1,int param_2)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x12 != 0) {
      iVar1 = (param_2 - iVar1) / 0x12;
      goto LAB_005029f7;
    }
  }
  iVar1 = 0;
LAB_005029f7:
  FUN_00502b70(/* TODO: unresolved argument - see file header */ (undefined4 *)0,unaff_EDI,
               param_2,1);
  *param_1 = *(int *)(unaff_EDI + 4) + iVar1 * 0x12;
  return param_1;
}

