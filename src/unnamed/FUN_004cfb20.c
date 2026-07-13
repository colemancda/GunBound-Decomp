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
  DrawFontString(iVar4,0);
  /* BlitRLESprite's dropped args (0x4cfb7b): objdump shows ECX=0x21d
   * (param_1) and EAX loaded right before the call with the same
   * pointer expression the C computes below into pcVar2
   * (unaff_ESI+0x10c4)*0xd + 0x457f1 + iVar6, iVar6 == g_clientContext
   * snapshot taken at function entry) - the compiler hoisted this
   * computation ahead of the call in the original binary. */
  pcVar2 = (char *)(*(int *)(unaff_ESI + 0x10c4) * 0xd + 0x457f1 + iVar6);
  BlitRLESprite(0x21d,iVar4,0xffff,(byte *)pcVar2);
  iVar3 = (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0;
  uVar7 = GetLocalizedString(&g_localizedStringTable,0xc1c);
  /* BlitRLESprite's dropped args (0x4cfbc0): objdump shows ECX =
   * strlen(pcVar2)*6 + 0x224 (strlen from the do-while loop just above -
   * the compiler's `ebx` holds the string length as a pointer difference)
   * and EAX left over from the GetLocalizedString call immediately above
   * (no intervening EAX write), i.e. its return value. */
  BlitRLESprite((int)(pcVar2 - (char *)iVar3 - 1) * 6 + 0x224,iVar4 + 1,uVar5,
                (byte *)uVar7);
  pcVar2 = (char *)(*(int *)(unaff_ESI + 0x10c4) * 0xd + 0x457f1 + g_clientContext);
  iVar3 = (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0xffff;
  uVar7 = GetLocalizedString(&g_localizedStringTable,0xc1c);
  /* BlitRLESprite's dropped args (0x4cfc0a): objdump shows ECX =
   * strlen(pcVar2)*6 + 0x223 (same strlen pattern as above, different
   * base pointer/offset) and EAX left over from the GetLocalizedString
   * call immediately above (its return value). */
  BlitRLESprite((int)(pcVar2 - (char *)iVar3 - 1) * 6 + 0x223,iVar4,uVar5,
                (byte *)uVar7);
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
  /* BlitRLESprite's dropped args (0x4cfc71/0x4cfc85): objdump shows both
   * calls' ECX as fixed constants (0x21e, 0x21d) and EAX loaded right
   * before each call as &local_80 (the buffer just sprintf'd above) -
   * same pattern as State03_GameRoomList_RenderRoomLabel's already-fixed
   * sites. param_2 for both is this function's running row cursor
   * (edi, already folded into `iVar4 + 0x14`/`iVar4 + 0x13` below). */
  BlitRLESprite(0x21e,iVar4 + 0x14,0,(byte *)local_80);
  BlitRLESprite(0x21d,iVar4 + 0x13,0xffff,(byte *)local_80);
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
  /* BlitRLESprite's dropped args (0x4cfcf4/0x4cfd08): same pattern as the
   * pair above - objdump shows ECX = 0x21e/0x21d and EAX = &local_80 (the
   * buffer just sprintf'd above) at each call. */
  BlitRLESprite(0x21e,iVar4 + 0x23,0,(byte *)local_80);
  BlitRLESprite(0x21d,iVar4 + 0x22,0xffff,(byte *)local_80);
  return;
}

