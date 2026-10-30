/* Widget_SetChildRange - 0x00505520 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-10-30): the panel arrives in EBX. Nothing in 0x505520
 * writes EBX before `mov ecx,ebx` at 0x50552e (the FindChildIndex
 * `this`) and the [ebx+0x10]/[ebx+0xc] child-array reads at
 * 0x50553a/0x50554b, and the body ends in ret 8 with only the two stack
 * words. Ghidra left it as unaff_EBX; it is now the trailing parameter
 * regEbx. The two Widget_SetEnabled calls (0x50555f/0x50556c, push 0 or
 * 1) take ECX = the child loaded at 0x50554e (`mov ecx,[ecx+eax*4]`),
 * iVar1 here, and now pass it as `this`.
 */
#include "ghidra_types.h"


void Widget_SetChildRange(int param_1,undefined4 param_2,int regEbx)

{
  int iVar1;
  uint uVar2;
  int unaff_EBX = regEbx;
  
  uVar2 = Widget_FindChildIndex(unaff_EBX,0,4);
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(unaff_EBX + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    iVar1 = *(int *)(*(int *)(unaff_EBX + 0xc) + uVar2 * 4);
    *(int *)(iVar1 + 0x38) = param_1;
    *(undefined4 *)(iVar1 + 0x3c) = param_2;
    if (param_1 < 1) {
      Widget_SetEnabled(iVar1,0);
      return;
    }
    Widget_SetEnabled(iVar1,1);
  }
  return;
}

