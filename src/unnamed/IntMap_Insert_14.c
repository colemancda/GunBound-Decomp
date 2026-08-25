/* IntMap_Insert_14 - 0x00501560 in the original binary.
 *
 * The insert half of IntMap_Find_14: carve a node out of the chunk list (growing it by
 * 0x14 records at a time), link it at the head of its bucket, and stamp the
 * hash.  EBX is the bucket index the find just computed and ESI the map.
 *
 * EBX and ESI RECOVERED (2026-08-25): the insert half of the map.  EBX is the
 * bucket index the find just computed, ESI the map object.  Both stack
 * arguments carry the same value -- the key -- because the second is read
 * back out of the slot the find stashed it in.
 */
#include "ghidra_types.h"


undefined4 * IntMap_Insert_14(undefined4 param_1,undefined4 param_2,int regEbx,int *regEsi)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (regEsi[0xb] == 0) {
    piVar2 = _malloc(regEsi[9] * 0x14 + 4);
    if (piVar2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar2 = regEsi[10];
    regEsi[10] = (int)piVar2;
    iVar4 = regEsi[9];
    piVar2 = piVar2 + iVar4 * 5 + -4;
    if (-1 < iVar4 + -1) {
      do {
        piVar2[3] = regEsi[0xb];
        regEsi[0xb] = (int)piVar2;
        piVar2 = piVar2 + -5;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  puVar1 = (undefined4 *)regEsi[0xb];
  regEsi[0xb] = puVar1[3];
  puVar1[4] = param_2;
  *puVar1 = param_1;
  regEsi[1] = regEsi[1] + 1;
  puVar1[3] = *(undefined4 *)(*regEsi + regEbx * 4);
  *(undefined4 **)(*regEsi + regEbx * 4) = puVar1;
  if (((uint)regEsi[6] < (uint)regEsi[1]) && (regEsi[8] == 0)) {
    uVar3 = FUN_00500e30();
    FUN_00501220(regEsi,uVar3);
  }
  return puVar1;
}

