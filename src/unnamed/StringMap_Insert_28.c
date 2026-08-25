/* StringMap_Insert_28 - 0x00504480 in the original binary.
 *
 * The insert half of StringMap_Find_28: carve a node out of the chunk list (growing it by
 * 0x28 records at a time), link it at the head of its bucket, and stamp the
 * hash.  EBX is the bucket index the find just computed and ESI the map.
 *
 * EAX and EBX RECOVERED (2026-08-25): the third copy of the map insert (see
 * StringMap_Insert_1c and StringMap_Insert_ac).  EAX is the key -- `mov eax,ebp`, and EBP
 * holds the caller's param_1 as read at its ENTRY, before the find overwrote
 * that stack slot with the hash -- and EBX is the map object.
 */
#include "ghidra_types.h"


undefined4 * StringMap_Insert_28(int param_1,undefined4 param_2,undefined4 *regEax,int *regEbx)

{
  byte bVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  if (regEbx[0xb] == 0) {
    piVar3 = _malloc(regEbx[9] * 0x28 + 4);
    if (piVar3 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar3 = regEbx[10];
    regEbx[10] = (int)piVar3;
    iVar5 = regEbx[9];
    piVar3 = piVar3 + iVar5 * 10 + -9;
    if (-1 < iVar5 + -1) {
      do {
        piVar3[8] = regEbx[0xb];
        regEbx[0xb] = (int)piVar3;
        piVar3 = piVar3 + -10;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  puVar2 = (undefined4 *)regEbx[0xb];
  regEbx[0xb] = puVar2[8];
  bVar1 = *(byte *)((int)regEax + 0x11);
  *(byte *)((int)puVar2 + 0x11) = bVar1;
  puVar7 = puVar2;
  for (uVar6 = (uint)(bVar1 >> 2); uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar7 = *regEax;
    regEax = regEax + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = bVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)regEax;
    regEax = (undefined4 *)((int)regEax + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *(undefined1 *)((uint)bVar1 + (int)puVar2) = 0;
  puVar2[9] = param_2;
  regEbx[1] = regEbx[1] + 1;
  puVar2[8] = *(undefined4 *)(*regEbx + param_1 * 4);
  *(undefined4 **)(*regEbx + param_1 * 4) = puVar2;
  if (((uint)regEbx[6] < (uint)regEbx[1]) && (regEbx[8] == 0)) {
    uVar4 = FUN_00500e30();
    FUN_00500300(regEbx,uVar4);
  }
  return puVar2;
}

