/* FUN_004cfb20 - 0x004cfb20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004cfb20(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int unaff_ESI;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  char local_80 [128];
  
  iVar6 = g_clientContext;
  iVar4 = 0x1d4;
  if (*(int *)(unaff_ESI + 0x10cc) != -1) {
    iVar4 = 0x183;
  }
  FUN_004eb510(iVar4,0);
  BlitRLESprite(iVar4,0xffff);
  pcVar2 = (char *)(*(int *)(unaff_ESI + 0x10c4) * 0xd + 0x457f1 + iVar6);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0;
  GetLocalizedString(&g_localizedStringTable,0xc1c);
  BlitRLESprite(iVar4 + 1,uVar5);
  pcVar2 = (char *)(*(int *)(unaff_ESI + 0x10c4) * 0xd + 0x457f1 + g_clientContext);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0xffff;
  GetLocalizedString(&g_localizedStringTable,0xc1c);
  BlitRLESprite(iVar4,uVar5);
  iVar6 = *(int *)(unaff_ESI + 0x1114 + *(int *)(unaff_ESI + 0x10c4) * 4);
  iVar3 = 1;
  if (0 < iVar6) {
    iVar3 = iVar6;
  }
  iVar6 = *(int *)(unaff_ESI + 0x10d4 + *(int *)(unaff_ESI + 0x10c4) * 4);
  uVar5 = *(undefined4 *)(unaff_ESI + 0x10f4 + *(int *)(unaff_ESI + 0x10c4) * 4);
  iVar3 = iVar6 / iVar3;
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xc1d);
  _sprintf(local_80,pcVar2,iVar3,uVar5,iVar6);
  BlitRLESprite(iVar4 + 0x14,0);
  BlitRLESprite(iVar4 + 0x13,0xffff);
  iVar6 = *(int *)(unaff_ESI + 0x1174 + *(int *)(unaff_ESI + 0x10c4) * 4);
  iVar3 = 1;
  if (0 < iVar6) {
    iVar3 = iVar6;
  }
  iVar6 = *(int *)(unaff_ESI + 0x10c4);
  uVar5 = *(undefined4 *)(unaff_ESI + 0x1174 + iVar6 * 4);
  uVar7 = *(undefined4 *)(unaff_ESI + 0x1154 + iVar6 * 4);
  iVar3 = *(int *)(unaff_ESI + 0x1134 + iVar6 * 4) / iVar3;
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xc1e);
  _sprintf(local_80,pcVar2,iVar3,uVar7,uVar5);
  BlitRLESprite(iVar4 + 0x23,0);
  BlitRLESprite(iVar4 + 0x22,0xffff);
  return;
}

