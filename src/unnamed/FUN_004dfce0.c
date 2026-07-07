/* FUN_004dfce0 - 0x004dfce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004dfce0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar7 + 4);
  while (uVar1 < 0x2719) {
    if (uVar1 == 0x2718) {
      iVar7 = *(int *)(iVar7 + 0x10);
      uVar1 = *(uint *)(iVar7 + 8);
      goto joined_r0x004dfd14;
    }
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar1 = *(uint *)(iVar7 + 4);
  }
  iVar7 = 0;
LAB_004dfd29:
  iVar9 = 0;
  piVar8 = (int *)(param_1 + 0x768);
  puVar6 = (ushort *)(DAT_005b3484 + 0x49a2c);
  iVar3 = DAT_005b3484;
  do {
    iVar5 = iVar3;
    if (*(char *)(iVar3 + 0x45914 + iVar9) != '\0') {
      iVar2 = (int)((longlong)(ulonglong)((uint)*puVar6 * 0x2ec) /
                   (longlong)*(int *)(&DAT_006a7720 + iVar3));
      piVar8[-8] = iVar2;
      iVar5 = DAT_005b3484;
      if (iVar7 == 0) {
        *piVar8 = 0x1e7;
        iVar5 = iVar3;
      }
      else {
        psVar4 = (short *)(*(int *)(iVar7 + 0x34) + iVar2 * 2);
        iVar3 = 0;
        do {
          if (*psVar4 != 0) break;
          iVar3 = iVar3 + 1;
          psVar4 = psVar4 + 0x2ec;
        } while (iVar3 < 0xd1);
        *piVar8 = iVar3 + 0x17f;
      }
    }
    iVar9 = iVar9 + 1;
    puVar6 = puVar6 + 1;
    piVar8 = piVar8 + 1;
    iVar3 = iVar5;
    if (7 < iVar9) {
      return;
    }
  } while( true );
joined_r0x004dfd14:
  if (1 < uVar1) goto LAB_004dfd23;
  if (uVar1 == 1) goto LAB_004dfd29;
  iVar7 = *(int *)(iVar7 + 0x10);
  uVar1 = *(uint *)(iVar7 + 8);
  goto joined_r0x004dfd14;
LAB_004dfd23:
  iVar7 = 0;
  goto LAB_004dfd29;
}

