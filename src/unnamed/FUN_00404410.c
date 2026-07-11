/* FUN_00404410 - 0x00404410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00404410(int param_1)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 uVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  int *piVar11;
  char *pcVar12;
  int local_18c;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined1 local_168 [4];
  undefined1 local_164 [4];
  undefined1 local_160 [4];
  undefined1 local_15c [4];
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined1 local_138;
  char acStack_137 [23];
  undefined1 local_120;
  char local_11f [31];
  int local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  
  uVar2 = *(undefined2 *)(g_clientContext + 0x3f804);
  uVar3 = *(undefined2 *)(g_clientContext + 0x41340);
  uVar4 = *(undefined2 *)(g_clientContext + 0x44e60);
  local_17c = CONCAT22(uVar3,uVar2);
  uVar6 = local_17c;
  local_184 = CONCAT22(SUBFIELD(local_184,2,undefined2),0x12);
  SUBFIELD(local_17c,2,undefined1) = (byte)uVar3;
  SUBFIELD(local_17c,0,undefined1) = (byte)uVar2;
  local_178 = CONCAT22((ushort)(byte)((byte)((ushort)uVar4 >> 8) ^ 0x6b) +
                       (ushort)(byte)((byte)uVar4 ^ 0x69) +
                       (ushort)(byte)((byte)((ushort)uVar3 >> 8) ^ 0x73) +
                       (ushort)(SUBFIELD(local_17c,2,undefined1) ^ 0x6d) +
                       (ushort)(byte)((byte)((ushort)uVar2 >> 8) ^ 0x6f) +
                       (ushort)((byte)local_17c ^ 99),uVar4);
  local_18c = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  local_17c = uVar6;
  if (local_18c != *(int *)(param_1 + 4)) {
    do {
      iVar5 = *(int *)(local_18c + 0x10);
      cVar7 = *(char *)(iVar5 + 0x15);
      iVar9 = g_clientContext;
      while (g_clientContext = iVar9, cVar7 == '\0') {
        if (*(char *)(iVar5 + 0x30) != '\0') {
          pcVar12 = (char *)(iVar5 + 0x21);
          piVar11 = (int *)(&DAT_006aa41c + iVar9);
          iVar8 = FUN_00426780(local_15c,local_160,local_168);
          if (iVar8 == 0) {
            local_138 = 0x69;
            iVar9 = 0;
            do {
              pcVar10 = (char *)((int)&local_158 + iVar9);
              acStack_137[iVar9] = *pcVar10;
              iVar9 = iVar9 + 1;
            } while (*pcVar10 != '\0');
            iVar8 = FUN_00404b00(&local_138);
            iVar9 = DAT_007934e8;
            if (iVar8 == 0) {
              *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
              *(undefined2 *)(iVar9 + 0x4d4) = 0x1022;
              *(undefined2 *)(iVar9 + 0x4d6) = 1;
              iVar8 = *(int *)(iVar9 + 0x44d0);
              *(int *)(iVar9 + 0x44d0) = iVar8 + 2;
              puVar1 = (undefined4 *)(iVar8 + 0x4d2 + iVar9);
              *puVar1 = local_158;
              puVar1[1] = local_154;
              puVar1[2] = local_150;
              puVar1[3] = local_14c;
              *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 0x10;
              FUN_004d2680();
            }
            local_120 = 0x69;
            iVar9 = -(int)pcVar12;
            do {
              cVar7 = *pcVar12;
              pcVar12[(int)(local_11f + iVar9)] = cVar7;
              pcVar12 = pcVar12 + 1;
            } while (cVar7 != '\0');
            local_100 = *(int *)(param_1 + 0x1be0);
            *(int *)(param_1 + 0x1be0) = local_100 + 1;
            local_f8 = local_184;
            local_f4 = local_180;
            local_ec = local_178;
            local_f0 = local_17c;
            local_e8 = local_174;
            local_fc = 0x2005;
            local_e4 = local_170;
            FUN_004049a0(&local_100);
          }
          else {
            iVar8 = FUN_00426780(local_164,&local_16c,local_168);
            if (iVar8 == 0) {
              if ((*piVar11 == 0) &&
                 (cVar7 = FUN_00500c00(piVar11,*(undefined4 *)(&DAT_006aa424 + iVar9),1),
                 cVar7 == '\0')) {
                    /* WARNING: Subroutine does not return */
                ThrowCxxException(0x8007000e);
              }
              iVar8 = FUN_00426960(piVar11,pcVar12,local_16c);
            }
            pcVar10 = *(char **)(iVar8 + 4);
            pcVar12 = (char *)&local_158;
            do {
              cVar7 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              *pcVar12 = cVar7;
              pcVar12 = pcVar12 + 1;
            } while (cVar7 != '\0');
            if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
              (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x18))
                        (&local_158,&local_184,&DAT_00551cb1);
            }
          }
        }
        iVar5 = *(int *)(iVar5 + 0x10);
        iVar9 = g_clientContext;
        cVar7 = *(char *)(iVar5 + 0x15);
      }
      local_18c = *(int *)(local_18c + 0x1c);
    } while (local_18c != *(int *)(param_1 + 4));
  }
  return;
}

