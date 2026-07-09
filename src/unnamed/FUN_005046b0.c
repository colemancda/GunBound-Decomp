/* FUN_005046b0 - 0x005046b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_005046b0(undefined4 param_1,undefined4 *param_2,undefined4 *param_3)

{
  byte bVar1;
  undefined4 *in_EAX;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (; param_2 != param_3; param_2 = (undefined4 *)((int)param_2 + 0x1e)) {
    if (in_EAX != (undefined4 *)0x0) {
      bVar1 = *(byte *)((int)param_2 + 0x11);
      *(byte *)((int)in_EAX + 0x11) = bVar1;
      puVar3 = param_2;
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
      *(undefined1 *)((int)in_EAX + (uint)bVar1) = 0;
      bVar1 = *(byte *)((int)param_2 + 0x1b);
      *(byte *)((int)in_EAX + 0x1b) = bVar1;
      puVar3 = (undefined4 *)((int)param_2 + 0x12);
      puVar4 = (undefined4 *)((int)in_EAX + 0x12);
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
      *(undefined1 *)(bVar1 + 0x12 + (int)in_EAX) = 0;
      *(undefined2 *)(in_EAX + 7) = *(undefined2 *)(param_2 + 7);
    }
    in_EAX = (undefined4 *)((int)in_EAX + 0x1e);
  }
  return;
}

