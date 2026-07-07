/* FUN_004e9130 - 0x004e9130 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e9130(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int in_EAX;
  void *pvVar2;
  short *psVar3;
  short *psVar4;
  short sVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  uint uVar9;
  short *psVar10;
  int unaff_ESI;
  short *psVar11;
  int local_10;
  
  for (psVar11 = *(short **)(unaff_ESI + 0x100c + in_EAX * 4);
      (param_1 < *psVar11 || (psVar11[1] <= param_1)); psVar11 = *(short **)(psVar11 + 6)) {
  }
  if (0 < param_2) {
    do {
      bVar1 = *(byte *)(unaff_ESI + 0x200c);
      psVar4 = psVar11;
      if (bVar1 < *(byte *)(psVar11 + 2)) {
        do {
          if (param_2 <= psVar11[1]) break;
          psVar11 = *(short **)(psVar11 + 6);
        } while (*(byte *)(unaff_ESI + 0x200c) < *(byte *)(psVar11 + 2));
        psVar4 = psVar11;
        if (bVar1 < *(byte *)(psVar11 + 2)) {
          return;
        }
      }
      sVar5 = psVar4[1];
      psVar11 = psVar4;
      while ((sVar5 < param_2 && (*(byte *)(psVar11 + 2) <= bVar1))) {
        psVar11 = *(short **)(psVar11 + 6);
        sVar5 = psVar11[1];
      }
      iVar6 = (int)*psVar4;
      iVar8 = param_1;
      if (param_1 < iVar6) {
        iVar8 = iVar6;
      }
      if (bVar1 < *(byte *)(psVar11 + 2)) {
        local_10 = (int)*psVar11;
      }
      else {
        local_10 = (int)psVar11[1];
        if (param_2 <= local_10) {
          local_10 = param_2;
        }
      }
      sVar7 = (short)iVar8;
      sVar5 = (short)local_10;
      if (psVar4 == psVar11) {
        uVar9 = *(uint *)(unaff_ESI + 0x1000);
        iVar6 = (int)(uVar9 + ((int)uVar9 >> 0x1f & 0x3ffU)) >> 10;
        uVar9 = uVar9 & 0x800003ff;
        if ((int)uVar9 < 0) {
          uVar9 = (uVar9 - 1 | 0xfffffc00) + 1;
        }
        if (*(int *)(unaff_ESI + iVar6 * 4) == 0) {
          pvVar2 = operator_new(0x4000);
          *(void **)(unaff_ESI + iVar6 * 4) = pvVar2;
        }
        *(int *)(unaff_ESI + 0x1000) = *(int *)(unaff_ESI + 0x1000) + 1;
        psVar10 = (short *)(uVar9 * 0x10 + *(int *)(unaff_ESI + iVar6 * 4));
        *(undefined4 *)psVar10 = *(undefined4 *)psVar4;
        *(undefined4 *)(psVar10 + 2) = *(undefined4 *)(psVar4 + 2);
        *(undefined4 *)(psVar10 + 4) = *(undefined4 *)(psVar4 + 4);
        *(undefined4 *)(psVar10 + 6) = *(undefined4 *)(psVar4 + 6);
        psVar3 = psVar4;
        if (*psVar4 != param_1) {
          uVar9 = *(uint *)(unaff_ESI + 0x1000);
          iVar6 = (int)(((int)uVar9 >> 0x1f & 0x3ffU) + uVar9) >> 10;
          uVar9 = uVar9 & 0x800003ff;
          if ((int)uVar9 < 0) {
            uVar9 = (uVar9 - 1 | 0xfffffc00) + 1;
          }
          if (*(int *)(unaff_ESI + iVar6 * 4) == 0) {
            pvVar2 = operator_new(0x4000);
            *(void **)(unaff_ESI + iVar6 * 4) = pvVar2;
          }
          *(int *)(unaff_ESI + 0x1000) = *(int *)(unaff_ESI + 0x1000) + 1;
          psVar3 = (short *)(uVar9 * 0x10 + *(int *)(unaff_ESI + iVar6 * 4));
          psVar4[1] = sVar7;
          *(short **)(psVar4 + 6) = psVar3;
        }
        psVar3[1] = sVar5;
        *psVar3 = sVar7;
        *(undefined1 *)(psVar3 + 2) = *(undefined1 *)(unaff_ESI + 0x200c);
        *(short **)(psVar3 + 6) = psVar10;
        *(int *)(psVar3 + 4) = param_3 + (iVar8 - param_1) * 2;
        *psVar10 = sVar5;
        *(int *)(psVar10 + 4) = *(int *)(psVar10 + 4) + (local_10 - *psVar4) * 2;
      }
      else {
        if (iVar6 != iVar8) {
          uVar9 = *(uint *)(unaff_ESI + 0x1000);
          iVar6 = (int)(((int)uVar9 >> 0x1f & 0x3ffU) + uVar9) >> 10;
          uVar9 = uVar9 & 0x800003ff;
          if ((int)uVar9 < 0) {
            uVar9 = (uVar9 - 1 | 0xfffffc00) + 1;
          }
          if (*(int *)(unaff_ESI + iVar6 * 4) == 0) {
            pvVar2 = operator_new(0x4000);
            *(void **)(unaff_ESI + iVar6 * 4) = pvVar2;
          }
          *(int *)(unaff_ESI + 0x1000) = *(int *)(unaff_ESI + 0x1000) + 1;
          psVar3 = (short *)(uVar9 * 0x10 + *(int *)(unaff_ESI + iVar6 * 4));
          psVar4[1] = sVar7;
          *(short **)(psVar4 + 6) = psVar3;
          psVar4 = psVar3;
        }
        psVar4[1] = sVar5;
        *psVar4 = sVar7;
        *(undefined1 *)(psVar4 + 2) = *(undefined1 *)(unaff_ESI + 0x200c);
        *(int *)(psVar4 + 4) = param_3 + (iVar8 - param_1) * 2;
        *(short **)(psVar4 + 6) = psVar11;
        *(int *)(psVar11 + 4) = *(int *)(psVar11 + 4) + (local_10 - *psVar11) * 2;
        *psVar11 = sVar5;
      }
    } while (local_10 < param_2);
  }
  return;
}

