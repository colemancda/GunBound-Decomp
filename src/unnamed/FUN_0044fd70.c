/* FUN_0044fd70 - 0x0044fd70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0044fd70(int param_1)

{
  undefined *puVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  bool bVar7;
  undefined1 local_678 [20];
  undefined4 local_664;
  undefined1 local_458;
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053abda;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar6 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar6;
  iVar6 = FUN_00450650(param_1,iVar6);
  if (iVar6 == *(int *)(param_1 + 0x2d4)) {
    *(int *)(param_1 + 0x2d8) = *(int *)(param_1 + 0x2d8) + 1;
  }
  else {
    *(undefined4 *)(param_1 + 0x2d8) = 0;
  }
  *(int *)(param_1 + 0x2d4) = iVar6;
  if (0x50 < *(int *)(param_1 + 0x2d8)) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  iVar6 = g_clientContext;
  puVar1 = g_gameStateVTableArray[9];
  if (g_currentGameState != 0xb) {
    *(undefined4 *)(param_1 + 0x38) =
         *(undefined4 *)(g_gameStateVTableArray[9] + *(int *)(param_1 + 8) * 8 + 0x6bc);
    *(int *)(param_1 + 0x3c) = *(int *)(puVar1 + *(int *)(param_1 + 8) * 8 + 0x6c0) + -0x3c;
    *unaff_FS_OFFSET = local_c;
    return;
  }
  if (*(uint *)(param_1 + 8) < 8) {
    iVar4 = FindSpriteFrame();
    if (iVar4 != 0) {
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar4 + 0x38);
      *(int *)(param_1 + 0x3c) = *(int *)(iVar4 + 0x3c) + -0x1e;
      goto LAB_0044fe4c;
    }
    iVar6 = GetPlayerRecordBySlot(iVar6);
    if ((iVar6 == 0) || (cVar2 = PeekPacketChecksumBool(), cVar2 != '\0')) {
      *(undefined1 *)(param_1 + 0x14) = 1;
    }
    uVar3 = PeekChecksumStateUnderLock(iVar6 + 0x90c);
    *(undefined4 *)(param_1 + 0x38) = uVar3;
    uVar3 = EncodeChecksumDeltaSub(iVar6 + 0xb30,local_230,0x3c);
    local_4 = 1;
    cVar2 = PacketChecksumLessThan(uVar3,*(undefined4 *)(&g_nCameraBoundY + g_clientContext));
    bVar7 = cVar2 == '\0';
    if (bVar7) {
      puVar5 = local_678;
      local_458 = 0;
      local_664 = 0;
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x44ff2e (`lea edi,[esp+0x18]`). Objdump of orig/GunBound.gme
       * traces the absolute stack address at that instruction back to
       * this file's own local_678 buffer (the same &local_678 used two
       * lines up via `puVar5 = local_678;`); tableHandle(+0x14) =
       * local_664 and activeFlag(+0x220) = local_458 - both zero-written
       * on the two lines immediately above, confirming this is the cell.
       * See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(local_678, *(undefined4 *)(&g_nCameraBoundY + g_clientContext));
      local_4 = 3;
    }
    else {
      puVar5 = (undefined1 *)EncodeChecksumDeltaSub(iVar6 + 0xb30,local_454,0x3c);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
    }
    uVar3 = PeekChecksumStateUnderLock(puVar5);
    *(undefined4 *)(param_1 + 0x3c) = uVar3;
    local_4 = 2;
    if (bVar7) {
      ScrubChecksumGuard();
    }
    local_4 = 1;
    if (!bVar7) {
      ScrubChecksumGuard();
    }
  }
  else {
    iVar6 = FindSpriteFrame();
    if (iVar6 == 0) {
      *(undefined1 *)(param_1 + 0x14) = 1;
      goto LAB_0044fe4c;
    }
    uVar3 = PeekChecksumStateUnderLock(iVar6 + 0x25c);
    *(undefined4 *)(param_1 + 0x38) = uVar3;
    uVar3 = EncodeChecksumDeltaSub(iVar6 + 0x480,local_678,0x1e);
    local_4 = 0;
    uVar3 = PeekChecksumStateUnderLock(uVar3);
    *(undefined4 *)(param_1 + 0x3c) = uVar3;
  }
  local_4 = 0xffffffff;
  ScrubChecksumGuard();
LAB_0044fe4c:
  *unaff_FS_OFFSET = local_c;
  return;
}

