/* FUN_004430c0 - 0x004430c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004430c0(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short *psVar4;
  ushort *puVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = (uint)*(byte *)(g_clientContext + 0x475c4) * 2 + 1;
  uVar2 = *(uint *)(iVar6 + 4);
  while (uVar2 < 0x2712) {
    if (uVar2 == 0x2711) {
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar2 = *(uint *)(iVar6 + 8);
      goto joined_r0x00443104;
    }
    iVar6 = *(int *)(iVar6 + 0x1c);
    uVar2 = *(uint *)(iVar6 + 4);
  }
  iVar6 = 0;
LAB_00443118:
  iVar8 = 0;
  piVar7 = (int *)(param_1 + 300);
  puVar5 = (ushort *)(g_clientContext + 0x49a2c);
  do {
    if (*(char *)(g_clientContext + 0x45914 + iVar8) != '\0') {
      iVar3 = *(int *)(&DAT_006a7720 + g_clientContext);
      if (iVar3 < 1) {
        iVar3 = 1;
      }
      iVar3 = (int)((longlong)(ulonglong)((uint)*puVar5 * 0x2ec) / (longlong)iVar3);
      piVar7[-8] = iVar3;
      if (iVar6 == 0) {
        *piVar7 = 0x7a;
      }
      else {
        psVar4 = (short *)(*(int *)(iVar6 + 0x34) + iVar3 * 2);
        iVar3 = 0;
        do {
          if (*psVar4 != 0) break;
          iVar3 = iVar3 + 1;
          psVar4 = psVar4 + 0x2ec;
        } while (iVar3 < 0xd1);
        *piVar7 = iVar3 + 0x12;
      }
    }
    iVar8 = iVar8 + 1;
    puVar5 = puVar5 + 1;
    piVar7 = piVar7 + 1;
    if (7 < iVar8) {
      return;
    }
  } while( true );
joined_r0x00443104:
  if (uVar1 < uVar2) goto LAB_00443112;
  if (uVar2 == uVar1) goto LAB_00443118;
  iVar6 = *(int *)(iVar6 + 0x10);
  uVar2 = *(uint *)(iVar6 + 8);
  goto joined_r0x00443104;
LAB_00443112:
  iVar6 = 0;
  goto LAB_00443118;
}

