/* FUN_004cfd20 - 0x004cfd20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004cfd20(void)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  uint local_84;
  char local_80 [128];
  
  iVar3 = g_clientContext;
  DrawFontString(0x1ba,0);
  BlitRLESprite(0x1ba,0xffff);
  pcVar2 = (char *)(*(int *)(in_EAX + 0x10cc) * 0xd + 0x457f1 + iVar3);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar9 = 0;
  GetLocalizedString(&g_localizedStringTable,3000);
  BlitRLESprite(0x1bb,uVar9);
  pcVar2 = (char *)(*(int *)(in_EAX + 0x10cc) * 0xd + 0x457f1 + g_clientContext);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar9 = 0xffff;
  GetLocalizedString(&g_localizedStringTable,3000);
  BlitRLESprite(0x1ba,uVar9);
  iVar3 = *(int *)(in_EAX + 0x10cc);
  uVar7 = *(uint *)(g_clientContext + 0x4599c + iVar3 * 4);
  if (999 < uVar7) {
    uVar7 = 999;
  }
  uVar8 = *(uint *)(g_clientContext + 0x4597c + iVar3 * 4);
  if (999 < uVar8) {
    uVar8 = 999;
  }
  uVar9 = *(undefined4 *)(g_clientContext + 0x4593c + iVar3 * 4);
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xbb9);
  _sprintf(local_80,pcVar2,uVar9,uVar8,uVar7);
  BlitRLESprite(0x1ce,0);
  BlitRLESprite(0x1cd,0xffff);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(int *)(g_clientContext + 0x4707c +
              ((uint)*(byte *)(g_clientContext + 0x475c4) + iVar3 * 0xb +
              *(int *)(in_EAX + 0x10cc) * 0x14) * 4) == 0) {
    local_84 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_84 = *(uint *)(g_clientContext + 0x4707c +
                        ((uint)*(byte *)(g_clientContext + 0x475c4) + iVar3 * 0xb +
                        *(int *)(in_EAX + 0x10cc) * 0x14) * 4);
  }
  uVar7 = 1;
  iVar3 = *(int *)(in_EAX + 0x10cc);
  if (*(int *)(g_clientContext + 0x4731c + iVar3 * 4) + *(int *)(g_clientContext + 0x472fc + iVar3 * 4) !=
      0) {
    uVar7 = *(int *)(g_clientContext + 0x4731c + iVar3 * 4) +
            *(int *)(g_clientContext + 0x472fc + iVar3 * 4);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_84 = (uint)(*(int *)(g_clientContext + 0x4667c +
                            (iVar3 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4) +
                            *(int *)(in_EAX + 0x10cc) * 0x14) * 4) * 100) / local_84;
  iVar3 = (iVar4 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4)) * 0x7d28 + 0x1a1e48 + g_clientContext
  ;
  uVar7 = (uint)(*(int *)(g_clientContext + 0x472fc + *(int *)(in_EAX + 0x10cc) * 4) * 100) / uVar7;
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xbba);
  _sprintf(local_80,pcVar2,uVar7,iVar3,local_84);
  BlitRLESprite(0x1dd,0);
  BlitRLESprite(0x1dc,0xffff);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = FUN_00420650(g_clientContext,*(undefined4 *)(in_EAX + 0x10cc),iVar4);
  iVar3 = iVar5 + *(int *)(in_EAX + 0x10cc) * 0x14;
  if (*(int *)(g_clientContext + 0x45c3c + iVar3 * 4) + *(int *)(g_clientContext + 0x459bc + iVar3 * 4) ==
      0) {
    uVar7 = 1;
  }
  else {
    iVar3 = iVar5 + *(int *)(in_EAX + 0x10cc) * 0x14;
    uVar7 = *(int *)(g_clientContext + 0x45c3c + iVar3 * 4) +
            *(int *)(g_clientContext + 0x459bc + iVar3 * 4);
  }
  iVar3 = iVar4 + *(int *)(in_EAX + 0x10cc) * 0x14;
  if (*(int *)(g_clientContext + 0x45c3c + iVar3 * 4) + *(int *)(g_clientContext + 0x459bc + iVar3 * 4) ==
      0) {
    uVar8 = 1;
  }
  else {
    iVar3 = iVar4 + *(int *)(in_EAX + 0x10cc) * 0x14;
    uVar8 = *(int *)(g_clientContext + 0x45c3c + iVar3 * 4) +
            *(int *)(g_clientContext + 0x459bc + iVar3 * 4);
  }
  uVar7 = (uint)(*(int *)(g_clientContext + 0x459bc + (iVar5 + *(int *)(in_EAX + 0x10cc) * 0x14) * 4) *
                100) / uVar7;
  uVar9 = GetLocalizedString(&g_localizedStringTable,iVar5 + 1000);
  uVar8 = (uint)(*(int *)(g_clientContext + 0x459bc + (iVar4 + *(int *)(in_EAX + 0x10cc) * 0x14) * 4) *
                100) / uVar8;
  uVar6 = GetLocalizedString(&g_localizedStringTable,iVar4 + 1000);
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbb);
  _sprintf(local_80,pcVar2,uVar6,uVar8,uVar9,uVar7);
  BlitRLESprite(0x1ec,0);
  BlitRLESprite(0x1eb,0xffff);
  uVar7 = *(uint *)(g_clientContext + 0x4735c + *(int *)(in_EAX + 0x10cc) * 4);
  uVar8 = 1;
  if (uVar7 != 0) {
    uVar8 = uVar7;
  }
  uVar8 = *(uint *)(g_clientContext + 0x4733c + *(int *)(in_EAX + 0x10cc) * 4) / uVar8;
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbc);
  _sprintf(local_80,pcVar2,uVar8);
  BlitRLESprite(0x1fb,0);
  BlitRLESprite(0x1fa,0xffff);
  return;
}

