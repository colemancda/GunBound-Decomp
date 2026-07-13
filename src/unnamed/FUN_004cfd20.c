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
  undefined4 uVar10;
  uint local_84;
  char local_80 [128];
  
  iVar3 = g_clientContext;
  DrawFontString(0x1ba,0);
  /* BlitRLESprite's dropped args (0x4cfd70): objdump shows ECX=0x21d
   * (param_1) and EAX loaded right before the call with the same pointer
   * expression the C computes below into pcVar2 ((in_EAX+0x10cc)*0xd +
   * 0x457f1 + iVar3, iVar3 == g_clientContext snapshot taken at function
   * entry) - the compiler hoisted this computation ahead of the call in
   * the original binary. Same pattern as sibling FUN_004cfb20's first
   * BlitRLESprite call site. */
  BlitRLESprite(0x21d,0x1ba,0xffff,
                (byte *)(*(int *)(in_EAX + 0x10cc) * 0xd + 0x457f1 + iVar3));
  pcVar2 = (char *)(*(int *)(in_EAX + 0x10cc) * 0xd + 0x457f1 + iVar3);
  iVar4 = (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar9 = 0;
  uVar10 = (undefined4)GetLocalizedString(&g_localizedStringTable,3000);
  /* BlitRLESprite's dropped args (0x4cfdbb): objdump shows ECX =
   * strlen(pcVar2)*6 + 0x224 (strlen from the do-while loop just above -
   * the compiler's `edi` holds the string length as a pointer difference)
   * and EAX left over from the GetLocalizedString call immediately above
   * (no intervening EAX write), i.e. its return value. Same pattern as
   * sibling FUN_004cfb20's second BlitRLESprite call site. */
  BlitRLESprite((int)(pcVar2 - (char *)iVar4 - 1) * 6 + 0x224,0x1bb,uVar9,(byte *)uVar10);
  pcVar2 = (char *)(*(int *)(in_EAX + 0x10cc) * 0xd + 0x457f1 + g_clientContext);
  iVar4 = (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar9 = 0xffff;
  uVar10 = (undefined4)GetLocalizedString(&g_localizedStringTable,3000);
  /* BlitRLESprite's dropped args (0x4cfe0e): objdump shows ECX =
   * strlen(pcVar2)*6 + 0x223 (same strlen pattern as above, different
   * base pointer/offset) and EAX left over from the GetLocalizedString
   * call immediately above (its return value). Same pattern as sibling
   * FUN_004cfb20's third BlitRLESprite call site. */
  BlitRLESprite((int)(pcVar2 - (char *)iVar4 - 1) * 6 + 0x223,0x1ba,uVar9,(byte *)uVar10);
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
  /* BlitRLESprite's dropped args (0x4cfe80/0x4cfe98): objdump shows both
   * calls' ECX as fixed constants (0x21e, 0x21d) and EAX loaded right
   * before each call as &local_80 (the buffer just sprintf'd above) -
   * same pattern as State03_GameRoomList_RenderRoomLabel's already-fixed
   * sites and sibling FUN_004cfb20's local_80-buffer call pairs. */
  BlitRLESprite(0x21e,0x1ce,0,(byte *)local_80);
  BlitRLESprite(0x21d,0x1cd,0xffff,(byte *)local_80);
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
  /* BlitRLESprite's dropped args (0x4d0043/0x4d005b): same pattern as the
   * pair above - objdump shows ECX = 0x21e/0x21d and EAX = &local_80 (the
   * buffer just sprintf'd above) at each call. */
  BlitRLESprite(0x21e,0x1dd,0,(byte *)local_80);
  BlitRLESprite(0x21d,0x1dc,0xffff,(byte *)local_80);
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
  /* BlitRLESprite's dropped args (0x4d01c0/0x4d01d8): same pattern as
   * above - objdump shows ECX = 0x21e/0x21d and EAX = &local_80 (the
   * buffer just sprintf'd above) at each call. */
  BlitRLESprite(0x21e,0x1ec,0,(byte *)local_80);
  BlitRLESprite(0x21d,0x1eb,0xffff,(byte *)local_80);
  uVar7 = *(uint *)(g_clientContext + 0x4735c + *(int *)(in_EAX + 0x10cc) * 4);
  uVar8 = 1;
  if (uVar7 != 0) {
    uVar8 = uVar7;
  }
  uVar8 = *(uint *)(g_clientContext + 0x4733c + *(int *)(in_EAX + 0x10cc) * 4) / uVar8;
  pcVar2 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbc);
  _sprintf(local_80,pcVar2,uVar8);
  /* BlitRLESprite's dropped args (0x4d0237/0x4d024f): same pattern as
   * above - objdump shows ECX = 0x21e/0x21d and EAX = &local_80 (the
   * buffer just sprintf'd above) at each call. */
  BlitRLESprite(0x21e,0x1fb,0,(byte *)local_80);
  BlitRLESprite(0x21d,0x1fa,0xffff,(byte *)local_80);
  return;
}

