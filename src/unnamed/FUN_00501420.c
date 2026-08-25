/* FUN_00501420 - 0x00501420 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and EBX RECOVERED (2026-08-25): this is the insert half of a hash map
 * (chained buckets, 0xac-byte nodes) and the two registers are the two halves
 * of the lookup its caller just performed -- EAX the new node's key/value
 * source, EBX the map object.  Its two stack parameters are the bucket index
 * and the hash, which the caller already passes.
 */
#include "ghidra_types.h"


undefined4 * FUN_00501420(int param_1,undefined4 param_2,undefined4 *regEax,int *regEbx)

{
  byte bVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  if (regEbx[0xb] == 0) {
    piVar3 = _malloc(regEbx[9] * 0xac + 4);
    if (piVar3 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar3 = regEbx[10];
    regEbx[10] = (int)piVar3;
    iVar5 = regEbx[9];
    piVar3 = piVar3 + iVar5 * 0x2b + -0x2a;
    if (-1 < iVar5 + -1) {
      do {
        piVar3[0x29] = regEbx[0xb];
        regEbx[0xb] = (int)piVar3;
        piVar3 = piVar3 + -0x2b;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  puVar2 = (undefined4 *)regEbx[0xb];
  regEbx[0xb] = puVar2[0x29];
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
  FUN_004ff1a0();
  puVar2[0x2a] = param_2;
  regEbx[1] = regEbx[1] + 1;
  puVar2[0x29] = *(undefined4 *)(*regEbx + param_1 * 4);
  *(undefined4 **)(*regEbx + param_1 * 4) = puVar2;
  if (((uint)regEbx[6] < (uint)regEbx[1]) && (regEbx[8] == 0)) {
    uVar4 = FUN_00500e30();
    FUN_00500ce0(regEbx,uVar4);
  }
  return puVar2;
}

