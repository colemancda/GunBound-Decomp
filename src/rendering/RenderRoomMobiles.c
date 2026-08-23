/* RenderRoomMobiles - 0x004dc820 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: one entry of the 0x448-stride per-slot table at g_clientContext+0x477ec (the same table FUN_004cfd20/FUN_00442e00 read).  The index register is a folded-away cursor - frame[0x20], zeroed at entry and stepped 0x448 in the loop tail at 0x4dca46, in lockstep with local_10 - so it is local_10 * 0x448.
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
  undefined4 uAttachOwner;
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
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x477ec + local_10 * 0x448));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
      /* RECOVERED (2026-08-19): the dropped EDX and EAX arguments, and
       * param_1 = the phantom ECX.  EDX is branch-dependent - orig
       * 0x4dc9ab `mov edx,[ecx+0x30]` with ecx = *local_14 on the attached
       * path, 0x4dc9d0 `or edx,-1` on the iVar2 == -1 path - and EAX is
       * 0x4dc99e/0x4dc9c8 `lea eax,[edx-0x186a0]` off the 0x4dc985
       * `add edx,0x493e0`, i.e. local_10 + 0x30d40.  See
       * src/rendering/BlitSpriteAttached.c. */
      if (iVar2 == -1) {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar4 = -1;
        uAttachOwner = 0xffffffff;
      }
      else {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar4 = iVar2 + 5000;
        uAttachOwner = *(undefined4 *)(*local_14 + 0x30);
      }
      BlitSpriteAttached(0,uAttachOwner,iVar4,uVar7,
                   (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(iVar5 + 0x1fe44 + uVar1 * 4),iVar8,
                   local_10 + 0x30d40);
      iVar8 = *(int *)(iVar5 + 0x1fe5c + uVar1 * 4);
      /* same pair, orig 0x4dca08 / 0x4dca21 and 0x4dca24-0x4dca28
       * (`add eax,0x493e0`). */
      if (iVar2 == -1) {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar2 = -1;
        uAttachOwner = 0xffffffff;
      }
      else {
        uVar7 = *(undefined4 *)(local_14[1] + 0x30);
        iVar2 = iVar2 + 5000;
        uAttachOwner = *(undefined4 *)(*local_14 + 0x30);
      }
      BlitSpriteAttached(0,uAttachOwner,iVar2,uVar7,
                   (uVar6 * iVar8 + iVar3) * 0x80 + *(int *)(iVar5 + 0x1fe54 + uVar1 * 4),iVar8,
                   local_10 + 0x493e0);
    }
    local_8 = local_8 + 2;
    local_10 = local_10 + 1;
    local_14 = local_14 + 2;
  } while (local_8 < 0x4590c);
  return;
}

