/* FUN_004382d0 - 0x004382d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004382d0(void)

{
  char cVar1;
  undefined4 *puVar2;
  void *pvVar3;
  int unaff_EBX;
  
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 == '\0') && (unaff_EBX != 0)) {
    puVar2 = (undefined4 *)FindSpriteFrame();
    if (puVar2 != (undefined4 *)0x0) {
      *(undefined4 *)(puVar2[3] + 0x10) = puVar2[4];
      *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
      (**(code **)*puVar2)(1);
    }
    pvVar3 = operator_new(0x46c);
    if (pvVar3 != (void *)0x0) {
      FUN_0044fd00();
    }
    FUN_00450600();
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

