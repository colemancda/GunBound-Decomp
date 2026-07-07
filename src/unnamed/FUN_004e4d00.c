/* FUN_004e4d00 - 0x004e4d00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004e4d69) */
/* WARNING: Removing unreachable block (ram,0x004e4d77) */
/* WARNING: Removing unreachable block (ram,0x004e4d61) */

void FUN_004e4d00(int param_1)

{
  ushort *puVar1;
  ushort uVar2;
  undefined4 uVar3;
  short sVar4;
  char cVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  ushort *puVar13;
  char *pcVar14;
  uint uVar15;
  int iVar16;
  ushort *local_1c;
  short *local_18;
  short *local_14;
  short local_c;
  int local_4;
  
  cVar5 = FUN_004065a0();
  if (cVar5 != '\x01') {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar15 = *(uint *)(iVar6 + 4);
    if (uVar15 < 0xea61) {
      while (uVar15 != 60000) {
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar15 = *(uint *)(iVar6 + 4);
        if (60000 < uVar15) {
          return;
        }
      }
      iVar6 = *(int *)(iVar6 + 0x10);
      if (*(int *)(iVar6 + 8) == 0) {
        local_1c = *(ushort **)(iVar6 + 0x34);
        local_18 = *(short **)(param_1 + 0x3c);
        local_4 = 0;
        if (0 < *(int *)(param_1 + 0x1c)) {
          do {
            pcVar12 = (char *)(*(int *)(param_1 + 0x18) * local_4 + *(int *)(param_1 + 0x34));
            psVar7 = local_18 + 2;
            local_c = 0;
            if ((local_4 < *(int *)(param_1 + 0x854)) || (*(int *)(param_1 + 0x858) < local_4)) {
              uVar2 = *local_1c;
              puVar13 = local_1c;
              psVar7 = local_18;
              for (uVar15 = (uint)(uVar2 >> 1); uVar15 != 0; uVar15 = uVar15 - 1) {
                *(undefined4 *)psVar7 = *(undefined4 *)puVar13;
                puVar13 = puVar13 + 2;
                psVar7 = psVar7 + 2;
              }
              for (iVar10 = (uVar2 & 1) << 1; iVar10 != 0; iVar10 = iVar10 + -1) {
                *(char *)psVar7 = (char)*puVar13;
                puVar13 = (ushort *)((int)puVar13 + 1);
                psVar7 = (short *)((int)psVar7 + 1);
              }
              uVar15 = (uint)*local_1c;
              local_18 = local_18 + uVar15;
            }
            else {
              iVar10 = 0;
              pcVar14 = pcVar12;
              local_14 = psVar7;
              sVar4 = 0;
              if (0 < *(int *)(param_1 + 0x18)) {
                do {
                  local_c = sVar4;
                  if (*pcVar14 == '\0') {
                    do {
                      if (*(int *)(param_1 + 0x18) <= iVar10) break;
                      iVar10 = iVar10 + 1;
                    } while (pcVar12[iVar10] == '\0');
                  }
                  pcVar14 = pcVar12 + iVar10;
                  iVar8 = 0;
                  if (*pcVar14 != '\0') {
                    do {
                      if (*(int *)(param_1 + 0x18) <= iVar10) break;
                      iVar8 = iVar8 + 1;
                      iVar10 = iVar10 + 1;
                      pcVar14 = pcVar12 + iVar10;
                    } while (pcVar12[iVar10] != '\0');
                    if (iVar8 != 0) {
                      local_c = local_c + 1;
                      *psVar7 = (short)iVar10 - (short)iVar8;
                      uVar15 = (uint)local_1c[3];
                      puVar13 = local_1c + 2;
                      iVar11 = local_1c[2] + uVar15;
                      while (iVar11 < iVar10 - iVar8) {
                        puVar1 = puVar13 + uVar15 + 2;
                        puVar13 = puVar13 + uVar15 + 2;
                        uVar15 = (uint)puVar13[1];
                        iVar11 = *puVar1 + uVar15;
                      }
                      iVar16 = (iVar10 - (uint)*puVar13) - iVar8;
                      iVar11 = (uint)puVar13[1] - iVar16;
                      if (iVar8 <= iVar11) {
                        iVar11 = iVar8;
                      }
                      local_14[1] = (short)iVar11;
                      uVar9 = (iVar11 * 2 < 0) - 1 & iVar11 * 2;
                      puVar13 = puVar13 + iVar16 + 2;
                      psVar7 = local_14;
                      for (uVar15 = uVar9 >> 2; psVar7 = psVar7 + 2, uVar15 != 0;
                          uVar15 = uVar15 - 1) {
                        *(undefined4 *)psVar7 = *(undefined4 *)puVar13;
                        puVar13 = puVar13 + 2;
                      }
                      for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
                        *(char *)psVar7 = (char)*puVar13;
                        puVar13 = (ushort *)((int)puVar13 + 1);
                        psVar7 = (short *)((int)psVar7 + 1);
                      }
                      psVar7 = local_14 + iVar11 + 2;
                      local_14 = psVar7;
                    }
                  }
                  sVar4 = local_c;
                } while (iVar10 < *(int *)(param_1 + 0x18));
              }
              local_18[1] = local_c;
              *local_18 = (short)((int)psVar7 - (int)local_18 >> 1);
              uVar15 = (uint)*local_1c;
              local_18 = psVar7;
            }
            local_1c = local_1c + uVar15;
            local_4 = local_4 + 1;
          } while (local_4 < *(int *)(param_1 + 0x1c));
        }
        uVar3 = *(undefined4 *)(iVar6 + 0x34);
        *(undefined4 *)(iVar6 + 0x34) = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(param_1 + 0x3c) = uVar3;
      }
    }
  }
  return;
}

