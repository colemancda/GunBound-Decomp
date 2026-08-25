/* FUN_00500a20 - 0x00500a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-25): the map at +0x20 of the same 0x90-byte object
 * FUN_00500790 clears at +0x50 -- `add esi,0x20` at 0x4ff22e and
 * `lea esi,[esp+0x4c]` (frame -0x7c = -0x9c + 0x20) at 0x4fe988.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500aa3) */

void FUN_00500a20(int *regEsi)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint local_8;
  
  regEsi[8] = regEsi[8] + 1;
  if ((*regEsi != 0) && (local_8 = 0, regEsi[2] != 0)) {
    do {
      iVar6 = *(int *)(*regEsi + local_8 * 4);
      while (iVar6 != 0) {
        iVar2 = *(int *)(iVar6 + 0xc);
        *(int *)(iVar6 + 0xc) = regEsi[0xb];
        iVar3 = regEsi[1];
        regEsi[0xb] = iVar6;
        regEsi[1] = iVar3 - 1U;
        if ((iVar3 - 1U < (uint)regEsi[7]) && (regEsi[8] == 0)) {
          uVar5 = FloatToInt64();
          iVar6 = 0;
          if (0x11 < uVar5) {
            do {
              puVar1 = &DAT_00557664 + iVar6;
              iVar6 = iVar6 + 1;
            } while (*puVar1 < uVar5);
          }
          uVar7 = (&DAT_00557660)[iVar6];
          if ((&DAT_00557660)[iVar6] == 0xffffffff) {
            uVar7 = uVar5;
          }
          FUN_00501220(regEsi,uVar7);
        }
        iVar6 = iVar2;
        if (regEsi[1] == 0) {
          regEsi[0xb] = 0;
          piVar8 = (int *)regEsi[10];
          if ((int *)regEsi[10] != (int *)0x0) {
            do {
              piVar4 = (int *)*piVar8;
              _free(piVar8);
              piVar8 = piVar4;
            } while (piVar4 != (int *)0x0);
            regEsi[10] = 0;
          }
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < (uint)regEsi[2]);
  }
  _free((void *)*regEsi);
  *regEsi = 0;
  regEsi[1] = 0;
  if (regEsi[8] == 0) {
    uVar10 = 0;
    uVar9 = FUN_00500e30(0);
    HashMap_InitHashTable(regEsi,uVar9,uVar10);
  }
  regEsi[0xb] = 0;
  piVar8 = (int *)regEsi[10];
  if ((int *)regEsi[10] != (int *)0x0) {
    do {
      piVar4 = (int *)*piVar8;
      _free(piVar8);
      piVar8 = piVar4;
    } while (piVar4 != (int *)0x0);
    regEsi[10] = 0;
  }
  regEsi[8] = regEsi[8] + -1;
  return;
}

