/* RadioGroup_SelectHighChild - 0x00506890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-10-30): the radio panel arrives in EBX. 0x506890 never
 * writes EBX; it reads it at `mov ecx,ebx` (0x5068a5, the
 * Widget_FindChildIndex `this`) and for the [ebx+0x10]/[ebx+0xc]
 * child-array reads, and ends in ret 4 with param_1 as its only stack
 * word. Ghidra left it as unaff_EBX; it is now the trailing parameter
 * regEbx. Its only callers are the four calls each inside the uncarved
 * CCreateRoomDialog OnCommand body at 0x5065c0.
 */
#include "ghidra_types.h"


void RadioGroup_SelectHighChild(int param_1,int regEbx)

{
  uint uVar1;
  int unaff_EBX = regEbx;
  int iVar2;
  
  iVar2 = 4;
  do {
    uVar1 = Widget_FindChildIndex(unaff_EBX,iVar2,1);
    if (uVar1 != 0xffffffff) {
      if (*(uint *)(unaff_EBX + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      *(bool *)(*(int *)(*(int *)(unaff_EBX + 0xc) + uVar1 * 4) + 0x3a) = iVar2 == param_1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  return;
}

