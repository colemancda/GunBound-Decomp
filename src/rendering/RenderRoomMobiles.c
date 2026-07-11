/* RenderRoomMobiles - 0x004dc820 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004dc8ef) */

void __fastcall RenderRoomMobiles(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int *local_14;
  uint local_10;
  int local_8;
  
  local_14 = (int *)(param_1 + 0x6fc);
  local_10 = 0;
  local_8 = 0x458fc;
  iVar5 = g_clientContext;
  do {
    if ((*(char *)(local_10 + 0x45914 + iVar5) != '\0') && (*(int *)(*local_14 + 0x1c) != 0)) {
      uVar1 = local_10 / 4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
      if (g_bBattleSessionActive == '\0') {
        iVar2 = (int)*(char *)(local_8 + g_clientContext);
        if (iVar2 < 0x11) {
          if (0xc < iVar2) {
            iVar2 = iVar2 + 2;
          }
        }
        else {
          iVar2 = -1;
        }
      }
      iVar8 = *(int *)(g_clientContext + 0x1fe24 + uVar1 * 4);
      uVar6 = (local_10 % 4) / 2;
      iVar3 = (local_10 % 4 & 0x80000001) * 2;
      iVar4 = (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(g_clientContext + 0x1fe1c + uVar1 * 4);
      if (iVar2 != -1) {
        BlitMobilePart(iVar4,iVar8);
        iVar8 = *(int *)(iVar5 + 0x1fe3c + uVar1 * 4);
        iVar4 = (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(iVar5 + 0x1fe34 + uVar1 * 4);
      }
      BlitMobilePart(iVar4,iVar8);
      iVar8 = *(int *)(iVar5 + 0x1fe4c + uVar1 * 4);
      if (iVar2 == -1) {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar4 = -1;
      }
      else {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar4 = iVar2 + 5000;
      }
      BlitSpriteAttached(iVar4,uVar7,
                   (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(iVar5 + 0x1fe44 + uVar1 * 4),iVar8);
      iVar8 = *(int *)(iVar5 + 0x1fe5c + uVar1 * 4);
      if (iVar2 == -1) {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar2 = -1;
      }
      else {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar2 = iVar2 + 5000;
      }
      BlitSpriteAttached(iVar2,uVar7,
                   (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(iVar5 + 0x1fe54 + uVar1 * 4),iVar8);
    }
    local_8 = local_8 + 2;
    local_10 = local_10 + 1;
    local_14 = local_14 + 2;
  } while (local_8 < 0x4590c);
  return;
}

