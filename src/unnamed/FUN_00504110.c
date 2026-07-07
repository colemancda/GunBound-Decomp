/* FUN_00504110 - 0x00504110 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00504110(int param_1)

{
  byte bVar1;
  undefined4 *in_EAX;
  uint uVar2;
  undefined4 *unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (; param_1 != 0; param_1 = param_1 + -1) {
    if (in_EAX != (undefined4 *)0x0) {
      bVar1 = *(byte *)((int)unaff_EBX + 0x11);
      *(byte *)((int)in_EAX + 0x11) = bVar1;
      puVar3 = unaff_EBX;
      puVar4 = in_EAX;
      for (uVar2 = (uint)(bVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      for (uVar2 = bVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
      *(undefined1 *)((uint)bVar1 + (int)in_EAX) = 0;
    }
    in_EAX = (undefined4 *)((int)in_EAX + 0x12);
  }
  return;
}

