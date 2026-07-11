/* FUN_00405ba0 - 0x00405ba0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405ba0(void)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff77;
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined2 *unaff_EBX;
  char *pcVar15;
  char *pcVar16;
  undefined4 *puVar17;
  undefined4 local_88;
  undefined4 local_84;
  
  iVar14 = g_clientContext;
  if (*(char *)((int)unaff_EBX + 0x2009) == '\0') {
    return;
  }
  uVar2 = *(undefined2 *)(g_clientContext + 0x44e60);
  uVar3 = *(undefined2 *)(g_clientContext + 0x3f804);
  uVar4 = *(undefined2 *)(g_clientContext + 0x41340);
  local_88 = CONCAT22(uVar4,uVar3);
  uVar5 = local_88;
  local_84 = CONCAT22(SUBFIELD(local_84,2,undefined2),uVar2);
  *(undefined4 *)(unaff_EBX + 0x1000) = 4;
  unaff_EBX[1] = 0xa510;
  SUBFIELD(local_88,2,undefined1) = (byte)uVar4;
  SUBFIELD(local_88,0,undefined1) = (byte)uVar3;
  *(undefined4 *)(unaff_EBX + 2) = uVar5;
  unaff_EBX[4] = uVar2;
  iVar8 = *(int *)(unaff_EBX + 0x1000);
  *(int *)(unaff_EBX + 0x1000) = iVar8 + 6;
  *(ushort *)(iVar8 + 6 + (int)unaff_EBX) =
       (ushort)(byte)((byte)((ushort)uVar2 >> 8) ^ 0x6b) + (ushort)(byte)((byte)uVar2 ^ 0x69) +
       (ushort)(byte)((byte)((ushort)uVar4 >> 8) ^ 0x73) + (ushort)(SUBFIELD(local_88,2,undefined1) ^ 0x6d) +
       (ushort)(byte)((byte)((ushort)uVar3 >> 8) ^ 0x6f) + (ushort)((byte)local_88 ^ 99);
  iVar8 = *(int *)(unaff_EBX + 0x1000);
  *(int *)(unaff_EBX + 0x1000) = iVar8 + 2;
  puVar13 = &local_88;
  local_88 = uVar5;
  for (iVar9 = 0x20; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  puVar13 = (undefined4 *)(iVar8 + 2 + (int)unaff_EBX);
  *puVar13 = local_88;
  puVar13[1] = local_84;
  *(int *)(unaff_EBX + 0x1000) = *(int *)(unaff_EBX + 0x1000) + 8;
  iVar8 = *(int *)(iVar14 + 0x3f804);
  if (iVar8 == -1) {
    pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0x334);
    pcVar7 = pcVar6;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar16 = &stack0xffffff77;
    do {
      pcVar15 = pcVar16 + 1;
      pcVar16 = pcVar16 + 1;
    } while (*pcVar15 != '\0');
    pcVar15 = pcVar6;
    for (uVar10 = (uint)((int)pcVar7 - (int)pcVar6) >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
      pcVar15 = pcVar15 + 4;
      pcVar16 = pcVar16 + 4;
    }
    for (uVar10 = (int)pcVar7 - (int)pcVar6 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
      *pcVar16 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      pcVar16 = pcVar16 + 1;
    }
  }
  else {
    iVar9 = *(int *)(iVar14 + 0x41340);
    if (iVar9 == -1) {
      iVar9 = *(int *)(iVar14 + 0x44e60) + 1;
      iVar8 = iVar8 + 1;
      pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x335);
    }
    else {
      if (iVar9 == -2) {
        iVar8 = iVar8 + 1;
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x336);
        _sprintf((char *)&local_88,pcVar7,iVar8);
        goto LAB_00405d5e;
      }
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 1;
      pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x337);
    }
    _sprintf((char *)&local_88,pcVar7,iVar8,iVar9);
  }
LAB_00405d5e:
  pcVar7 = (char *)&local_88;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  uVar10 = (int)pcVar7 - ((int)&local_88 + 1);
  uVar11 = ((int)uVar10 < 0) - 1 & uVar10;
  puVar13 = &local_88;
  puVar17 = (undefined4 *)(*(int *)(unaff_EBX + 0x1000) + (int)unaff_EBX);
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *puVar17 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar17 = puVar17 + 1;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined1 *)puVar17 = *(undefined1 *)puVar13;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
    puVar17 = (undefined4 *)((int)puVar17 + 1);
  }
  iVar14 = *(int *)(unaff_EBX + 0x1000) + uVar10;
  *(int *)(unaff_EBX + 0x1000) = iVar14;
  *unaff_EBX = (short)iVar14;
  SendSocketData(*(undefined4 *)(unaff_EBX + 0x1002),iVar14);
  return;
}

