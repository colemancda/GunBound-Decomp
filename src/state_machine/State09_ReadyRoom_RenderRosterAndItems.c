/* State09_ReadyRoom_RenderRosterAndItems - 0x004d7db0 in the original binary,
 * was FUN_004d7db0. State09 (Ready Room) vtable slot 13.
 *
 * Combined player-roster + item-loadout renderer, traced this pass (see
 * ARCHITECTURE.md's Ready Room section): draws the turn/round-count label,
 * the 8-player ready roster (status icons + avatar previews, refreshing the
 * anti-cheat value-guard key table per slot), the paginated 3x3 item-loadout
 * grid (icons via the g_awItemIconTable shelf-icon table, decoded this pass too -
 * see ARCHITECTURE.md/FILEFORMATS.md), and reloads the Avata/Character/Effect
 * texture-cache family. Raw/near-verbatim port of Ghidra's decompiler output
 * otherwise, not hand-verified line-by-line. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall State09_ReadyRoom_RenderRosterAndItems(int param_1)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  char *pcVar14;
  undefined4 *puVar15;
  undefined4 *unaff_FS_OFFSET;
  uint local_a4c;
  int local_a38;
  int local_a34;
  int local_a30;
  int local_a2c;
  char local_a28 [16];
  undefined4 uStack_a18;
  undefined4 uStack_a04;
  undefined4 auStack_9a8 [4];
  undefined4 uStack_998;
  undefined4 uStack_984;
  char local_928 [128];
  undefined1 local_8a8 [20];
  int local_894;
  undefined1 local_684 [20];
  int local_670;
  undefined1 local_460 [20];
  int local_44c;
  undefined1 local_23c [20];
  int local_228;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  uint local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053becc;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  if (DAT_00793522 != '\0') {
    FUN_004eadb0();
  }
  if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
  _sprintf(local_928,(char *)&PTR_DAT_00551ecc,*(int *)(g_clientContext + 0x44e60) + 1);
  FUN_004ed9f0(0x46,local_928,3,0xb);
  FUN_004eadb0();
  iVar3 = g_clientContext;
  BlitRLESprite(0xf,0xffff);
  FUN_004eadb0();
  if (*(char *)(iVar3 + 0x44ee4) != '\0') {
    BlitRLESprite(0xf,0xffff);
  }
  _sprintf(local_928,s__d__s_00556ae8,*(int *)(iVar3 + 0x3f804) + 1,iVar3 + 0x3b8e8);
  BlitRLESprite(0xf,0xffff);
  local_a4c = 0;
  if (DAT_00793522 == '\0') {
LAB_004d81a0:
    uVar12 = local_a4c & 0x80000003;
    if ((int)uVar12 < 0) {
      uVar12 = (uVar12 - 1 | 0xfffffffc) + 1;
    }
    iVar13 = uVar12 * 0x25;
    iVar5 = iVar13 + 0x155;
    iVar3 = ((int)(local_a4c + ((int)local_a4c >> 0x1f & 3U)) >> 2) * 0x27 + 0xa4;
    if (*(char *)(g_clientContext + 0x44ef8) == '\0') {
      if (DAT_0079352c != 0) {
        iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar12 = *(uint *)(iVar6 + 4);
        while (uVar12 < 0x1f5) {
          if (uVar12 == 500) {
            iVar6 = *(int *)(iVar6 + 0x10);
            uVar12 = *(uint *)(iVar6 + 8);
            if (uVar12 < 0xb) goto LAB_004d821f;
            break;
          }
          iVar6 = *(int *)(iVar6 + 0x1c);
          uVar12 = *(uint *)(iVar6 + 4);
        }
      }
      goto LAB_004d8258;
    }
    uVar4 = 0x2000 << ((byte)local_a4c & 0x1f);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar12 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((uVar12 & uVar4) != uVar4) goto LAB_004d8264;
    if (local_a4c == 4) {
      if ((DAT_0079352c != 0) && (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar5,iVar3);
        }
        else {
          BlitSpriteClipped(10);
        }
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = iVar13 + 0x1c4;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar6 = iVar6 + 10;
    if (((DAT_0079352c != 0) && (-1 < iVar6)) && (iVar13 = FindSpriteFrame(), iVar13 != 0)) {
      if (*(char *)(iVar13 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar3);
        goto LAB_004d844e;
      }
      goto LAB_004d8442;
    }
    goto LAB_004d844e;
  }
LAB_004d7f30:
  uVar12 = local_a4c & 0x80000003;
  if ((int)uVar12 < 0) {
    uVar12 = (uVar12 - 1 | 0xfffffffc) + 1;
  }
  iVar13 = uVar12 * 0x25 + 0x155;
  iVar3 = ((int)(local_a4c + ((int)local_a4c >> 0x1f & 3U)) >> 2) * 0x27 + 0xa4;
  uVar11 = 0x2000 << ((byte)local_a4c & 0x1f);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar4 & uVar11) == uVar11) {
    if (local_a4c == 4) {
      if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
        if (*(char *)(iVar5 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar13,iVar3);
        }
        else {
          BlitSpriteClipped(10);
        }
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = uVar12 * 0x25 + 0x1c4;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar5 = iVar5 + 10;
    if (((DAT_0079352c != 0) && (-1 < iVar5)) && (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar13,iVar3);
      }
      else {
LAB_004d8173:
        BlitSpriteClipped(iVar5);
      }
    }
  }
  else if (DAT_0079352c != 0) {
    iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar12 = *(uint *)(iVar5 + 4);
    while (uVar12 < 0x1f5) {
      if (uVar12 == 500) {
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar12 = *(uint *)(iVar5 + 8);
        if (uVar12 < 0xb) goto LAB_004d8146;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar12 = *(uint *)(iVar5 + 4);
    }
  }
  goto LAB_004d817f;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar12 = *(uint *)(iVar6 + 8);
    if (10 < uVar12) break;
LAB_004d821f:
    if (uVar12 == 10) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar3);
      }
      else {
        BlitSpriteClipped(10);
      }
      break;
    }
  }
LAB_004d8258:
  if (local_a4c == 4) {
    iVar5 = iVar13 + 0x1c4;
LAB_004d8264:
    if ((DAT_0079352c != 0) && (iVar13 = FindSpriteFrame(), iVar13 != 0)) {
      if (*(char *)(iVar13 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar3);
      }
      else {
        iVar6 = 10;
LAB_004d8442:
        BlitSpriteClipped(iVar6);
      }
    }
  }
LAB_004d844e:
  local_a4c = local_a4c + 1;
  if (6 < (int)local_a4c) goto LAB_004d8460;
  goto LAB_004d81a0;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar12 = *(uint *)(iVar5 + 8);
    if (10 < uVar12) break;
LAB_004d8146:
    if (uVar12 == 10) {
      if (*(char *)(iVar5 + 0x18) != '\x01') {
        iVar5 = 10;
        goto LAB_004d8173;
      }
      BlitSprite16bpp(iVar13,iVar3);
      break;
    }
  }
LAB_004d817f:
  local_a4c = local_a4c + 1;
  if (6 < (int)local_a4c) goto LAB_004d8460;
  goto LAB_004d7f30;
LAB_004d8460:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar12 = (int)*(char *)(g_clientContext + 0x44ef8) + iVar3 * 0xb;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar12)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar3 + 4);
    while (uVar4 < 0x2712) {
      if (uVar4 == 0x2711) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar4 = *(uint *)(iVar3 + 8);
        if (uVar4 <= uVar12) goto LAB_004d84db;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar4 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_004d8518;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar4 = *(uint *)(iVar3 + 8);
    if (uVar12 < uVar4) break;
LAB_004d84db:
    if (uVar4 == uVar12) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x14c,0x33);
      }
      else {
        BlitSpriteClipped(uVar12);
      }
      break;
    }
  }
LAB_004d8518:
  iVar3 = 0;
  do {
    FUN_004dba80(iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  local_a4c = 0;
LAB_004d8540:
  iVar3 = local_a4c + *(int *)(param_1 + 0x620) * 9;
  if (iVar3 < *(int *)(param_1 + 0x61c)) {
    iVar3 = *(int *)(param_1 + 0x518 + iVar3 * 4);
    uVar1 = g_awItemIconTable[iVar3];
    iVar13 = (uVar1 & 0xff) * 2;
    uVar12 = iVar13 - 2;
    if ((*(char *)(iVar3 + 0x4d8 + param_1) == '\0') || (*(char *)(param_1 + 0x4cc) == '\x01')) {
      uVar12 = iVar13 - 1;
    }
    uVar4 = ((uVar1 & 0xff00) != 0) + 0x2713;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar12)) {
      iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar3 + 4);
      while (uVar11 <= uVar4) {
        if (uVar11 == uVar4) {
          iVar3 = *(int *)(iVar3 + 0x10);
          uVar4 = *(uint *)(iVar3 + 8);
          if (uVar4 <= uVar12) goto LAB_004d85fe;
          break;
        }
        iVar3 = *(int *)(iVar3 + 0x1c);
        uVar11 = *(uint *)(iVar3 + 4);
      }
    }
    goto LAB_004d862d;
  }
  goto LAB_004d867a;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar4 = *(uint *)(iVar3 + 8);
    if (uVar12 < uVar4) break;
LAB_004d85fe:
    if (uVar4 == uVar12) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(((int)local_a4c % 3) * 0x46 + 0x210,((int)local_a4c / 3) * 0x2d + 0x193);
      }
      else {
        BlitSpriteClipped(uVar12);
      }
      break;
    }
  }
LAB_004d862d:
  uVar7 = GetItemQuantityByIcon(g_clientContext,(uint)uVar1);
  _sprintf(local_a28,(char *)&PTR_DAT_00551ecc,uVar7);
  FUN_004ed9f0(0x7d,local_a28,3,5);
  local_a4c = local_a4c + 1;
  if (8 < (int)local_a4c) goto LAB_004d867a;
  goto LAB_004d8540;
LAB_004d867a:
  iVar3 = 0;
  local_a4c = 0x20b;
LAB_004d8685:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar13 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar13 != 0xff) {
      uVar7 = EncodeChecksumDeltaSub(g_clientContext + 0x39f30 + iVar3,local_23c,1);
      local_c = 2;
      EncodeChecksumDeltaMul(uVar7,local_684,2);
      local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),3);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar12 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((DAT_0079352c != 0) && (-1 < (int)uVar12)) {
        iVar13 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar4 = *(uint *)(iVar13 + 4);
        while (uVar4 < 0x2716) {
          if (uVar4 == 0x2715) {
            iVar13 = *(int *)(iVar13 + 0x10);
            uVar4 = *(uint *)(iVar13 + 8);
            if (uVar4 <= uVar12) goto LAB_004d892f;
            break;
          }
          iVar13 = *(int *)(iVar13 + 0x1c);
          uVar4 = *(uint *)(iVar13 + 4);
        }
      }
      goto LAB_004d896a;
    }
    uVar7 = EncodeChecksumDeltaSub(g_clientContext + 0x3a154 + iVar3,local_460,1);
    local_c = 0;
    EncodeChecksumDeltaMul(uVar7,local_8a8,2);
    local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar12 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((DAT_0079352c != 0) && (-1 < (int)uVar12)) {
      iVar13 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar4 = *(uint *)(iVar13 + 4);
      while (uVar4 < 0x2717) {
        if (uVar4 == 0x2716) {
          iVar13 = *(int *)(iVar13 + 0x10);
          uVar4 = *(uint *)(iVar13 + 8);
          if (uVar4 <= uVar12) goto LAB_004d8794;
          break;
        }
        iVar13 = *(int *)(iVar13 + 0x1c);
        uVar4 = *(uint *)(iVar13 + 4);
      }
    }
    goto LAB_004d87cf;
  }
  goto LAB_004d8a20;
  while( true ) {
    iVar13 = *(int *)(iVar13 + 0x10);
    uVar4 = *(uint *)(iVar13 + 8);
    if (uVar12 < uVar4) break;
LAB_004d892f:
    if (uVar4 == uVar12) {
      if (*(char *)(iVar13 + 0x18) == '\x01') {
        BlitSprite16bpp(local_a4c,0x16c);
      }
      else {
        BlitSpriteClipped(uVar12);
      }
      break;
    }
  }
LAB_004d896a:
  local_c = CONCAT31(SUBFIELD(local_c,1,undefined3),2);
  if (local_670 != 0) {
    iVar13 = local_670 << 4;
    iVar5 = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar13 + DAT_0079376c) = (char)iVar6;
      iVar13 = iVar13 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    FUN_0040b540(&local_a38);
  }
  local_c = 0xffffffff;
  if (local_228 != 0) {
    iVar13 = local_228 << 4;
    iVar5 = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar13 + DAT_0079376c) = (char)iVar6;
      iVar13 = iVar13 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    FUN_0040b540(&local_a38);
  }
  goto LAB_004d8a20;
  while( true ) {
    iVar13 = *(int *)(iVar13 + 0x10);
    uVar4 = *(uint *)(iVar13 + 8);
    if (uVar12 < uVar4) break;
LAB_004d8794:
    if (uVar4 == uVar12) {
      if (*(char *)(iVar13 + 0x18) == '\x01') {
        BlitSprite16bpp(local_a4c,0x16c);
      }
      else {
        BlitSpriteClipped(uVar12);
      }
      break;
    }
  }
LAB_004d87cf:
  local_c = local_c & 0xffffff00;
  if (local_894 != 0) {
    iVar13 = local_894 << 4;
    iVar5 = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar13 + DAT_0079376c) = (char)iVar6;
      iVar13 = iVar13 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    FUN_0040b540(&local_a38);
  }
  local_c = 0xffffffff;
  if (local_44c != 0) {
    iVar13 = local_44c << 4;
    iVar5 = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(iVar13 + DAT_0079376c) = (char)iVar6;
      iVar13 = iVar13 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    FUN_0040b540(&local_a38);
  }
  local_a4c = local_a4c + 0x24;
  iVar3 = iVar3 + 0x224;
LAB_004d8a20:
  local_a4c = local_a4c + 0x24;
  iVar3 = iVar3 + 0x224;
  if (0x2e2 < (int)local_a4c) goto code_r0x004d8a39;
  goto LAB_004d8685;
code_r0x004d8a39:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = (int)*(char *)(g_clientContext + 0x458fc + iVar3 * 2);
  if (iVar3 < 0x11) {
    if (0xc < iVar3) {
      iVar3 = iVar3 + 2;
    }
  }
  else {
    iVar3 = -1;
  }
  uVar12 = iVar3 + 1;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar12)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar3 + 4);
    while (uVar4 < 0x2713) {
      if (uVar4 == 0x2712) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar4 = *(uint *)(iVar3 + 8);
        if (uVar4 <= uVar12) goto LAB_004d8ac2;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar4 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_004d8b02;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar4 = *(uint *)(iVar3 + 8);
    if (uVar12 < uVar4) break;
LAB_004d8ac2:
    if (uVar4 == uVar12) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x17a,0x186);
      }
      else {
        BlitSpriteClipped(uVar12);
      }
      break;
    }
  }
LAB_004d8b02:
  iVar3 = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  local_a30 = iVar3;
  local_a2c = FindTextureCacheEntryByName(s_AvataTexture2_00556914);
  iVar13 = FindTextureCacheEntryByName(s_AvataEffectTexture1_00556900);
  iVar5 = FindTextureCacheEntryByName(s_AvataEffectTexture2_005568ec);
  iVar6 = FindTextureCacheEntryByName(s_CharacterTexture1_005568d8);
  iVar8 = FindTextureCacheEntryByName(s_CharacterTexture2_005568c4);
  local_a38 = FindTextureCacheEntryByName(s_CharEffectTexture1_005568a4);
  local_a34 = FindTextureCacheEntryByName(s_CharEffectTexture2_00556890);
  if (iVar3 != 0) {
    iVar3 = *(int *)(iVar3 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe44) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe4c) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe4c);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe44));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (local_a2c != 0) {
    iVar3 = *(int *)(local_a2c + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe48) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe50) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe50);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe48));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (iVar13 != 0) {
    iVar3 = *(int *)(iVar13 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe54) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe5c) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe5c);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe54));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (iVar5 != 0) {
    iVar3 = *(int *)(iVar5 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe58) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe60) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe60);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe58));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (iVar6 != 0) {
    iVar3 = *(int *)(iVar6 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe1c) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe24) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe24);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe1c));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (iVar8 != 0) {
    iVar3 = *(int *)(iVar8 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe20) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe28) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe28);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe20));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  if (local_a38 != 0) {
    iVar3 = *(int *)(local_a38 + 0x94);
    pcVar14 = local_a28;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar14[0] = '\0';
      pcVar14[1] = '\0';
      pcVar14[2] = '\0';
      pcVar14[3] = '\0';
      pcVar14 = pcVar14 + 4;
    }
    local_a28[0] = '|';
    local_a28[1] = '\0';
    local_a28[2] = '\0';
    local_a28[3] = '\0';
    piVar2 = *(int **)(iVar3 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,local_a28,0,0);
    iVar3 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe34) = uStack_a04;
    *(undefined4 *)(iVar3 + 0x1fe3c) = uStack_a18;
    iVar9 = 0;
    do {
      uVar12 = *(uint *)(iVar3 + 0x1fe3c);
      puVar15 = (undefined4 *)(iVar9 * uVar12 + *(int *)(iVar3 + 0x1fe34));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar9 = iVar9 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar9 < 0x100);
  }
  iVar3 = local_a34;
  if (local_a34 != 0) {
    iVar9 = *(int *)(local_a34 + 0x94);
    puVar15 = auStack_9a8;
    for (iVar10 = 0x1f; iVar10 != 0; iVar10 = iVar10 + -1) {
      *puVar15 = 0;
      puVar15 = puVar15 + 1;
    }
    auStack_9a8[0] = 0x7c;
    piVar2 = *(int **)(iVar9 + 0x110);
    (**(code **)(*piVar2 + 100))(piVar2,0,auStack_9a8,0,0);
    iVar9 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0x1fe38) = uStack_984;
    *(undefined4 *)(iVar9 + 0x1fe40) = uStack_998;
    iVar10 = 0;
    do {
      uVar12 = *(uint *)(iVar9 + 0x1fe40);
      puVar15 = (undefined4 *)(iVar10 * uVar12 + *(int *)(iVar9 + 0x1fe38));
      for (uVar4 = uVar12 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar10 = iVar10 + 1;
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined1 *)puVar15 = 0;
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
    } while (iVar10 < 0x100);
  }
  FUN_004dc820();
  if (local_a30 != 0) {
    piVar2 = *(int **)(*(int *)(local_a30 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (local_a2c != 0) {
    piVar2 = *(int **)(*(int *)(local_a2c + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (iVar13 != 0) {
    piVar2 = *(int **)(*(int *)(iVar13 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (iVar5 != 0) {
    piVar2 = *(int **)(*(int *)(iVar5 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (iVar6 != 0) {
    piVar2 = *(int **)(*(int *)(iVar6 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (iVar8 != 0) {
    piVar2 = *(int **)(*(int *)(iVar8 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (local_a38 != 0) {
    piVar2 = *(int **)(*(int *)(local_a38 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  if (iVar3 != 0) {
    piVar2 = *(int **)(*(int *)(iVar3 + 0x94) + 0x110);
    (**(code **)(*piVar2 + 0x80))(piVar2,0);
  }
  *unaff_FS_OFFSET = uStack_14;
  return;
}

