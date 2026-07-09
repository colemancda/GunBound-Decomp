/* ClampCursorToRect - 0x004ee200 in the original binary.
 *
 * Clamps the mouse cursor into a rectangle stored on the target object (+0x58c..+0x5a0) via SetCursorPos - used e.g. to snap the pointer onto a modal dialog. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall ClampCursorToRect(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  int iVar3;
  int unaff_EDI;
  
  iVar2 = *(int *)(param_1 + 0x58c);
  iVar3 = iVar2;
  if (iVar2 <= unaff_EBX) {
    iVar3 = unaff_EBX;
  }
  iVar1 = *(int *)(param_1 + 0x590);
  if ((iVar3 <= iVar1) && (iVar1 = iVar2, iVar2 <= unaff_EBX)) {
    iVar1 = unaff_EBX;
  }
  *(int *)(param_1 + 0x59c) = iVar1;
  iVar2 = *(int *)(param_1 + 0x594);
  iVar3 = iVar2;
  if (iVar2 <= unaff_EDI) {
    iVar3 = unaff_EDI;
  }
  if (iVar3 <= *(int *)(param_1 + 0x598)) {
    if (iVar2 <= unaff_EDI) {
      iVar2 = unaff_EDI;
    }
    *(int *)(param_1 + 0x5a0) = iVar2;
    SetCursorPos(unaff_EBX,unaff_EDI);
    return;
  }
  *(int *)(param_1 + 0x5a0) = *(int *)(param_1 + 0x598);
  SetCursorPos(unaff_EBX,unaff_EDI);
  return;
}

