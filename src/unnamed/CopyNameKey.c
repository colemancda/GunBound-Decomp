/* CopyNameKey - 0x00503770 in the original binary.
 *
 * Copies one 0x11-byte name key: the length byte at +0x11 first, then that
 * many bytes of text.  The same key record HashStringNoCase hashes.
 */
#include "ghidra_types.h"


void __fastcall CopyNameKey(undefined4 param_1,undefined4 *param_2)

{
  byte bVar1;
  undefined4 *in_EAX;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
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
  *(undefined1 *)((uint)bVar1 + (int)in_EAX) = 0;
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
  *(undefined1 *)((uint)bVar1 + (int)in_EAX + 0x12) = 0;
  *(undefined2 *)(in_EAX + 7) = *(undefined2 *)(param_2 + 7);
  return;
}

