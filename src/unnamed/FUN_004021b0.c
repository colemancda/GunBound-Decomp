/* FUN_004021b0 - 0x004021b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004021b0(undefined4 param_1,int param_2,short param_3)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  undefined4 *puVar9;
  ushort *puVar10;
  
  *(undefined4 *)(param_2 + 0xe1c) = 0;
  puVar9 = (undefined4 *)(param_2 + 0xe20);
  for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = 0xffffffff;
    puVar9 = puVar9 + 1;
  }
  iVar6 = *(int *)(*(int *)(param_2 + 4) + 0x1c);
  if (iVar6 != *(int *)(param_2 + 4)) {
    do {
      iVar8 = *(int *)(iVar6 + 0x10);
      cVar1 = *(char *)(iVar8 + 0x15);
      while (cVar1 == '\0') {
        if (((*(char *)(iVar8 + 0x30) == '\x12') && (param_3 == *(short *)(iVar8 + 0x31))) &&
           (sVar2 = *(short *)(iVar8 + 0x35), sVar2 != -1)) {
          iVar4 = 0;
          if (0 < *(int *)(param_2 + 0xe1c)) {
            psVar7 = (short *)(param_2 + 0xe20);
            do {
              if (*psVar7 == sVar2) break;
              iVar4 = iVar4 + 1;
              psVar7 = psVar7 + 1;
            } while (iVar4 < *(int *)(param_2 + 0xe1c));
          }
          if (iVar4 == *(int *)(param_2 + 0xe1c)) {
            *(short *)(param_2 + 0xe20 + iVar4 * 2) = sVar2;
            *(int *)(param_2 + 0xe1c) = *(int *)(param_2 + 0xe1c) + 1;
          }
        }
        iVar8 = *(int *)(iVar8 + 0x10);
        cVar1 = *(char *)(iVar8 + 0x15);
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
    } while (iVar6 != *(int *)(param_2 + 4));
  }
  iVar6 = 0;
  if (*(int *)(param_2 + 0xe1c) != 1 && -1 < *(int *)(param_2 + 0xe1c) + -1) {
    puVar10 = (ushort *)(param_2 + 0xe20);
    do {
      puVar5 = puVar10;
      iVar8 = iVar6;
      if (iVar6 < *(int *)(param_2 + 0xe1c)) {
        do {
          uVar3 = *puVar10;
          if (*puVar5 < uVar3) {
            *puVar10 = *puVar5;
            *puVar5 = uVar3;
          }
          iVar8 = iVar8 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar8 < *(int *)(param_2 + 0xe1c));
      }
      iVar6 = iVar6 + 1;
      puVar10 = puVar10 + 1;
    } while (iVar6 < *(int *)(param_2 + 0xe1c) + -1);
  }
  return;
}

