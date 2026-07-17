/* ProcessBattleFrame - 0x004dcbe0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ProcessBattleFrame(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_338 [7];
  undefined4 uStack_331;
  undefined1 local_32c [124];
  char local_2b0 [128];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df6b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar6 = g_clientContext + 0x475c8;
  *(int *)(param_1 + 0x740) = *(int *)(param_1 + 0x740) + 1;
  EncodeChecksumDeltaMul(iVar6,local_230,0xb);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = *(byte *)(g_clientContext + 0x475c4);
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_338);
  }
  switch(*(undefined4 *)(param_1 + 0x740)) {
  case 2:
    iVar5 = (uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28;
    LoadStageDecorationSet(&DAT_006a7708 + g_clientContext,iVar5 + 0x1a1ec8 + g_clientContext);
    FUN_004dfce0(param_1);
    _sprintf((char *)((int)&uStack_331 + 1),(char *)&PTR_DAT_00555500,
             iVar5 + 0x1a1ec8 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    uVar4 = FindPreloadedTextureByName((int)&uStack_331 + 1);
    *(undefined4 *)(&DAT_006a7f70 + g_clientContext) = uVar4;
    puVar2 = &uStack_331;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = DAT_005554f8;
    *(undefined1 *)((int)puVar7 + 5) = DAT_005554fc;
    LoadSpriteSet(&DAT_00ea0e18,0x1e14);
    DAT_00793634 = PeekChecksumStateUnderLock(((uint)bVar1 + iVar6) * 0x7d28 + 0x1a328c + g_clientContext);
    break;
  case 3:
    FUN_004e4010((uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a1ec8 + g_clientContext);
    break;
  case 4:
    FUN_004e3c50(&DAT_006a7708 + g_clientContext);
    if (*(ushort *)(&DAT_006aa660 + g_clientContext) != 0xffff) {
      _sprintf(local_2b0,s_event14__d_img_005554e8,*(ushort *)(&DAT_006aa660 + g_clientContext) + 1);
      LoadSpriteSet(&DAT_00ea0e18,0x271a);
    }
    break;
  case 5:
    cVar3 = CheckRoomSlotActive(g_clientContext,0);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,5000);
      LoadSpriteSet(&DAT_00ea0e18,0x13ec);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 6:
    cVar3 = CheckRoomSlotActive(g_clientContext,0);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,6000);
        LoadSpriteSet(&DAT_00ea0e18,0x1771);
        LoadSpriteSet(&DAT_00ea0e18,0x17d4);
        LoadSpriteSet(&DAT_00ea0e18,0x17d5);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a2c);
      LoadSpriteSet(&DAT_00ea0e18,0x1a2d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 7:
    cVar3 = CheckRoomSlotActive(g_clientContext,0);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,8000);
        LoadSpriteSet(&DAT_00ea0e18,0x1f41);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2008);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x206c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 8:
    cVar3 = CheckRoomSlotActive(g_clientContext,1);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1389);
      LoadSpriteSet(&DAT_00ea0e18,0x13ed);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 9:
    cVar3 = CheckRoomSlotActive(g_clientContext,1);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1772);
        LoadSpriteSet(&DAT_00ea0e18,0x1773);
        LoadSpriteSet(&DAT_00ea0e18,0x17d6);
        LoadSpriteSet(&DAT_00ea0e18,0x17d7);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a2e);
      LoadSpriteSet(&DAT_00ea0e18,0x1a2f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 10:
    cVar3 = CheckRoomSlotActive(g_clientContext,1);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f42);
        LoadSpriteSet(&DAT_00ea0e18,0x1f43);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2009);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x206d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0xb:
    cVar3 = CheckRoomSlotActive(g_clientContext,2);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138a);
      LoadSpriteSet(&DAT_00ea0e18,0x13ee);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0xc:
    cVar3 = CheckRoomSlotActive(g_clientContext,2);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1774);
        LoadSpriteSet(&DAT_00ea0e18,0x1775);
        LoadSpriteSet(&DAT_00ea0e18,0x17d8);
        LoadSpriteSet(&DAT_00ea0e18,0x17d9);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a30);
      LoadSpriteSet(&DAT_00ea0e18,0x1a31);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0xd:
    cVar3 = CheckRoomSlotActive(g_clientContext,2);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f44);
        LoadSpriteSet(&DAT_00ea0e18,0x1f45);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x200a);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x206e);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0xe:
    cVar3 = CheckRoomSlotActive(g_clientContext,3);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138b);
      LoadSpriteSet(&DAT_00ea0e18,0x13ef);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0xf:
    cVar3 = CheckRoomSlotActive(g_clientContext,3);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1776);
        LoadSpriteSet(&DAT_00ea0e18,0x1777);
        LoadSpriteSet(&DAT_00ea0e18,0x17da);
        LoadSpriteSet(&DAT_00ea0e18,0x17db);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a32);
      LoadSpriteSet(&DAT_00ea0e18,0x1a33);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x10:
    cVar3 = CheckRoomSlotActive(g_clientContext,3);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f46);
        LoadSpriteSet(&DAT_00ea0e18,0x1f47);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x200b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x206f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x11:
    cVar3 = CheckRoomSlotActive(g_clientContext,4);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138c);
      LoadSpriteSet(&DAT_00ea0e18,0x13f0);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x12:
    cVar3 = CheckRoomSlotActive(g_clientContext,4);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1778);
        LoadSpriteSet(&DAT_00ea0e18,0x1779);
        LoadSpriteSet(&DAT_00ea0e18,0x17dc);
        LoadSpriteSet(&DAT_00ea0e18,0x17dd);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a34);
      LoadSpriteSet(&DAT_00ea0e18,0x1a35);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x13:
    cVar3 = CheckRoomSlotActive(g_clientContext,4);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f48);
        LoadSpriteSet(&DAT_00ea0e18,0x1f49);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x200c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2070);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x14:
    cVar3 = CheckRoomSlotActive(g_clientContext,5);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138d);
      LoadSpriteSet(&DAT_00ea0e18,0x13f1);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x15:
    cVar3 = CheckRoomSlotActive(g_clientContext,5);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x177a);
        LoadSpriteSet(&DAT_00ea0e18,0x177b);
        LoadSpriteSet(&DAT_00ea0e18,0x17de);
        LoadSpriteSet(&DAT_00ea0e18,0x17df);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a36);
      LoadSpriteSet(&DAT_00ea0e18,0x1a37);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x16:
    cVar3 = CheckRoomSlotActive(g_clientContext,5);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f4a);
        LoadSpriteSet(&DAT_00ea0e18,0x1f4b);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x200d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2071);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x17:
    cVar3 = CheckRoomSlotActive(g_clientContext,6);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138e);
      LoadSpriteSet(&DAT_00ea0e18,0x13f2);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x18:
    cVar3 = CheckRoomSlotActive(g_clientContext,6);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x177c);
        LoadSpriteSet(&DAT_00ea0e18,0x177d);
        LoadSpriteSet(&DAT_00ea0e18,0x17e0);
        LoadSpriteSet(&DAT_00ea0e18,0x17e1);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a38);
      LoadSpriteSet(&DAT_00ea0e18,0x1a39);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x17d2);
      LoadSpriteSet(&DAT_00ea0e18,0x17d3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x17ca);
      LoadSpriteSet(&DAT_00ea0e18,0x17cb);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      LoadSpriteSet(&DAT_00ea0e18,0x17d2);
      LoadSpriteSet(&DAT_00ea0e18,0x17d3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x17ca);
      LoadSpriteSet(&DAT_00ea0e18,0x17cb);
    }
    break;
  case 0x19:
    cVar3 = CheckRoomSlotActive(g_clientContext,6);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f4c);
        LoadSpriteSet(&DAT_00ea0e18,0x1f4d);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x200e);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2072);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1a:
    cVar3 = CheckRoomSlotActive(g_clientContext,7);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x138f);
      LoadSpriteSet(&DAT_00ea0e18,0x13f3);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1b:
    cVar3 = CheckRoomSlotActive(g_clientContext,7);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x177e);
        LoadSpriteSet(&DAT_00ea0e18,0x177f);
        LoadSpriteSet(&DAT_00ea0e18,0x17e2);
        LoadSpriteSet(&DAT_00ea0e18,0x17e3);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a3a);
      LoadSpriteSet(&DAT_00ea0e18,0x1a3b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1c:
    cVar3 = CheckRoomSlotActive(g_clientContext,7);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1f4f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x200f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2073);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1d:
    cVar3 = CheckRoomSlotActive(g_clientContext,8);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1390);
      LoadSpriteSet(&DAT_00ea0e18,0x13f4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1e:
    cVar3 = CheckRoomSlotActive(g_clientContext,8);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1780);
        LoadSpriteSet(&DAT_00ea0e18,0x1781);
        LoadSpriteSet(&DAT_00ea0e18,0x17e4);
        LoadSpriteSet(&DAT_00ea0e18,0x17e5);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a3c);
      LoadSpriteSet(&DAT_00ea0e18,0x1a3d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x1f:
    cVar3 = CheckRoomSlotActive(g_clientContext,8);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f50);
        LoadSpriteSet(&DAT_00ea0e18,0x1f51);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        LoadSpriteSet(&DAT_00ea0e18,0x17d0);
        LoadSpriteSet(&DAT_00ea0e18,0x17d1);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2010);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2074);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x20:
    cVar3 = CheckRoomSlotActive(g_clientContext,9);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1391);
      LoadSpriteSet(&DAT_00ea0e18,0x13f5);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x21:
    cVar3 = CheckRoomSlotActive(g_clientContext,9);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1782);
        LoadSpriteSet(&DAT_00ea0e18,0x1783);
        LoadSpriteSet(&DAT_00ea0e18,0x17e6);
        LoadSpriteSet(&DAT_00ea0e18,0x17e7);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a3e);
      LoadSpriteSet(&DAT_00ea0e18,0x1a3f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x22:
    cVar3 = CheckRoomSlotActive(g_clientContext,9);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f52);
        LoadSpriteSet(&DAT_00ea0e18,0x1f53);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2011);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2075);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    LoadSpriteSet(&DAT_00ea0e18,0x17ce);
    LoadSpriteSet(&DAT_00ea0e18,0x17cf);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x23:
    cVar3 = CheckRoomSlotActive(g_clientContext,10);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1392);
      LoadSpriteSet(&DAT_00ea0e18,0x13f6);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x24:
    cVar3 = CheckRoomSlotActive(g_clientContext,10);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1784);
        LoadSpriteSet(&DAT_00ea0e18,0x1785);
        LoadSpriteSet(&DAT_00ea0e18,0x17e8);
        LoadSpriteSet(&DAT_00ea0e18,0x17e9);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a40);
      LoadSpriteSet(&DAT_00ea0e18,0x1a41);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x25:
    cVar3 = CheckRoomSlotActive(g_clientContext,10);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f54);
        LoadSpriteSet(&DAT_00ea0e18,0x1f55);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2012);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2076);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x26:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xb);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1393);
      LoadSpriteSet(&DAT_00ea0e18,0x13f7);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x27:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xb);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1786);
        LoadSpriteSet(&DAT_00ea0e18,0x1787);
        LoadSpriteSet(&DAT_00ea0e18,0x17ea);
        LoadSpriteSet(&DAT_00ea0e18,0x17eb);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a42);
      LoadSpriteSet(&DAT_00ea0e18,0x1a43);
      LoadSpriteSet(&DAT_00ea0e18,0x1a8e);
      LoadSpriteSet(&DAT_00ea0e18,0x1a8f);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x28:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xb);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f56);
        LoadSpriteSet(&DAT_00ea0e18,0x1f57);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2013);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2077);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x29:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xc);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1394);
      LoadSpriteSet(&DAT_00ea0e18,0x13f8);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2a:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xc);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1788);
        LoadSpriteSet(&DAT_00ea0e18,0x1789);
        LoadSpriteSet(&DAT_00ea0e18,0x17ec);
        LoadSpriteSet(&DAT_00ea0e18,0x17ed);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a44);
      LoadSpriteSet(&DAT_00ea0e18,0x1a45);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2b:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xc);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f58);
        LoadSpriteSet(&DAT_00ea0e18,0x1f59);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2014);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x2078);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x2c:
    LoadSpriteSet(&DAT_00ea0e18,0x1395);
    LoadSpriteSet(&DAT_00ea0e18,0x13f9);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x2d:
    LoadSpriteSet(&DAT_00ea0e18,0x178a);
    LoadSpriteSet(&DAT_00ea0e18,0x178b);
    LoadSpriteSet(&DAT_00ea0e18,0x17ee);
    LoadSpriteSet(&DAT_00ea0e18,0x17ef);
    LoadSpriteSet(&DAT_00ea0e18,0x1a46);
    LoadSpriteSet(&DAT_00ea0e18,0x1a47);
    LoadSpriteSet(&DAT_00ea0e18,0x1a8c);
    LoadSpriteSet(&DAT_00ea0e18,0x1a8d);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x2e:
    LoadSpriteSet(&DAT_00ea0e18,0x1f5a);
    LoadSpriteSet(&DAT_00ea0e18,0x1f5b);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x2015);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x2079);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x2f:
    LoadSpriteSet(&DAT_00ea0e18,0x1396);
    LoadSpriteSet(&DAT_00ea0e18,0x13fa);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x30:
    LoadSpriteSet(&DAT_00ea0e18,0x178c);
    LoadSpriteSet(&DAT_00ea0e18,0x178d);
    LoadSpriteSet(&DAT_00ea0e18,0x17f0);
    LoadSpriteSet(&DAT_00ea0e18,0x17f1);
    LoadSpriteSet(&DAT_00ea0e18,0x1a48);
    LoadSpriteSet(&DAT_00ea0e18,0x1a49);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x19c8);
    LoadSpriteSet(&DAT_00ea0e18,0x19ca);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x31:
    LoadSpriteSet(&DAT_00ea0e18,0x1f5c);
    LoadSpriteSet(&DAT_00ea0e18,0x1f5d);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x19c9);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x2016);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x207a);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x17cc);
    LoadSpriteSet(&DAT_00ea0e18,0x17cd);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x32:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xf);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1397);
      LoadSpriteSet(&DAT_00ea0e18,0x13fb);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x33:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xf);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x178e);
        LoadSpriteSet(&DAT_00ea0e18,0x178f);
        LoadSpriteSet(&DAT_00ea0e18,0x17f2);
        LoadSpriteSet(&DAT_00ea0e18,0x17f3);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x1a4a);
      LoadSpriteSet(&DAT_00ea0e18,0x1a4b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x34:
    cVar3 = CheckRoomSlotActive(g_clientContext,0xf);
    if (cVar3 != '\0') {
      if (*(char *)(g_clientContext + 0x45578) == '\0') {
        LoadSpriteSet(&DAT_00ea0e18,0x1f5e);
        LoadSpriteSet(&DAT_00ea0e18,0x1f5f);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
        AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      }
      LoadSpriteSet(&DAT_00ea0e18,0x2017);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x207b);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x35:
    LoadSpriteSet(&DAT_00ea0e18,7000);
    LoadSpriteSet(&DAT_00ea0e18,0x1b59);
    LoadSpriteSet(&DAT_00ea0e18,0x1b5a);
    LoadSpriteSet(&DAT_00ea0e18,0x1bbc);
    if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      LoadSpriteSet(&DAT_00ea0e18,6000);
      LoadSpriteSet(&DAT_00ea0e18,0x17d4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,8000);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x36:
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1838);
      LoadSpriteSet(&DAT_00ea0e18,0x189c);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x1fa4);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x37:
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      LoadSpriteSet(&DAT_00ea0e18,0x1839);
      LoadSpriteSet(&DAT_00ea0e18,0x189d);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      LoadSpriteSet(&DAT_00ea0e18,0x1fa5);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x38:
    LoadSpriteSet(&DAT_00ea0e18,0x183a);
    LoadSpriteSet(&DAT_00ea0e18,0x189e);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x1fa6);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x1900);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x39:
    LoadSpriteSet(&DAT_00ea0e18,0x1fa7);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,9000);
    break;
  case 0x3a:
    LoadSpriteSet(&DAT_00ea0e18,0x1964);
    LoadSpriteSet(&DAT_00ea0e18,0x1965);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x1fa8);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x3b:
    LoadSpriteSet(&DAT_00ea0e18,4000);
    LoadSpriteSet(&DAT_00ea0e18,0x1194);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x1f4e);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x3c:
    if (*(char *)(g_clientContext + 0x5010d) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x3d:
    if (*(char *)(g_clientContext + 0x5010e) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x3e:
    if (*(char *)(g_clientContext + 0x5010f) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x3f:
    if (*(char *)(g_clientContext + 0x50110) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x40:
    if (*(char *)(g_clientContext + 0x50111) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x41:
    if (*(char *)(g_clientContext + 0x50112) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x42:
    if (*(char *)(g_clientContext + 0x50113) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x43:
    if (*(char *)(g_clientContext + 0x50114) != '\0') {
      LoadRoomSlotAvatar();
    }
    break;
  case 0x44:
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x14b4);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x14b5);
    LoadSpriteSet(&DAT_00ea0e18,0x14b6);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    LoadSpriteSet(&DAT_00ea0e18,0x2260);
    LoadSpriteSet(&DAT_00ea0e18,0x2261);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x45:
    LoadSpriteSet(&DAT_00ea0e18,0x2329);
    cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,3);
    if (cVar3 != '\0') {
      LoadSpriteSet(&DAT_00ea0e18,3000);
      LoadSpriteSet(&DAT_00ea0e18,0xbb9);
      LoadSpriteSet(&DAT_00ea0e18,0xbba);
      LoadSpriteSet(&DAT_00ea0e18,0xbbb);
      LoadSpriteSet(&DAT_00ea0e18,0xc1c);
      LoadSpriteSet(&DAT_00ea0e18,0xc1d);
      LoadSpriteSet(&DAT_00ea0e18,0xc1e);
      LoadSpriteSet(&DAT_00ea0e18,0xc1f);
      LoadSpriteSet(&DAT_00ea0e18,0xc80);
      LoadSpriteSet(&DAT_00ea0e18,0xc81);
      LoadSpriteSet(&DAT_00ea0e18,0xc82);
      LoadSpriteSet(&DAT_00ea0e18,0xc83);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
      AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    }
    break;
  case 0x46:
    LoadSpriteSet(&DAT_00ea0e18,1000);
    LoadSpriteSet(&DAT_00ea0e18,0x3e9);
    LoadSpriteSet(&DAT_00ea0e18,0x3ea);
    LoadSpriteSet(&DAT_00ea0e18,0x3eb);
    LoadSpriteSet(&DAT_00ea0e18,0x3ec);
    LoadSpriteSet(&DAT_00ea0e18,0x3ed);
    LoadSpriteSet(&DAT_00ea0e18,0x3ee);
    LoadSpriteSet(&DAT_00ea0e18,0x3ef);
    LoadSpriteSet(&DAT_00ea0e18,0x3f0);
    LoadSpriteSet(&DAT_00ea0e18,0x3f1);
    LoadSpriteSet(&DAT_00ea0e18,0x3f2);
    LoadSpriteSet(&DAT_00ea0e18,0x3f3);
    LoadSpriteSet(&DAT_00ea0e18,0x3f4);
    LoadSpriteSet(&DAT_00ea0e18,0x3f5);
    LoadSpriteSet(&DAT_00ea0e18,0x3f6);
    LoadSpriteSet(&DAT_00ea0e18,0x3f7);
    LoadSpriteSet(&DAT_00ea0e18,0x3f8);
    LoadSpriteSet(&DAT_00ea0e18,0x3f9);
    LoadSpriteSet(&DAT_00ea0e18,0x3fa);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    break;
  case 0x47:
    QueueBroadcastEvent(0x82ff);
    BroadcastQueuedEvent();
  }
  if (*(int *)(param_1 + 0x744) == -1) {
    iVar6 = 0;
    do {
      if ((*(char *)(g_clientContext + 0x45914 + iVar6) != '\0') &&
         (*(char *)(g_clientContext + 0x449ba + iVar6) == '\0')) goto LAB_004dfad9;
      iVar6 = iVar6 + 1;
    } while (iVar6 < 8);
    *(undefined4 *)(param_1 + 0x744) = 0x3c;
  }
LAB_004dfad9:
  if (*(int *)(param_1 + 0x744) % 0x14 == 0) {
    AcquireSoundChannel(0);
  }
  if ((0 < *(int *)(param_1 + 0x744)) &&
     (iVar6 = *(int *)(param_1 + 0x744) + -1, *(int *)(param_1 + 0x744) = iVar6, iVar6 == 0)) {
    *(undefined4 *)(param_1 + 0x744) = 0xfffffffe;
    g_pendingGameState = 0xb;
    g_stateChangeRequested = 0;
    DAT_0056d108 = 0;
    _DAT_007934d8 = 1;
    *(undefined1 *)(*(int *)(param_1 + 0x788) + 0x1e) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 == iVar5) {
      QueueBroadcastEvent(0x8600);
      BroadcastQueuedEvent();
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

