/* State09_ReadyRoom_OnEnter - 0x004d6810 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Removing unreachable block (ram,0x004d70a8) */
/* WARNING: Removing unreachable block (ram,0x004d70b2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State09_ReadyRoom_OnEnter(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  int *piVar11;
  int *piVar12;
  undefined4 *unaff_FS_OFFSET;
  char *pcStack_9c;
  undefined1 uStack_95;
  int iStack_94;
  void *pvStack_90;
  char acStack_8c [128];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053cf6e;
  *unaff_FS_OFFSET = &uStack_c;
  DAT_0079352a = 0;
  FUN_004f1790(&DAT_00ea0e18,10000);
  FUN_004f1790(&DAT_00ea0e18,0x2711);
  FUN_004f1790(&DAT_00ea0e18,0x2712);
  FUN_004f1790(&DAT_00ea0e18,0x2713);
  FUN_004f1790(&DAT_00ea0e18,0x2714);
  FUN_004f1790(&DAT_00ea0e18,0x2715);
  FUN_004f1790(&DAT_00ea0e18,0x2716);
  FUN_004f1790(&DAT_00ea0e18,0x2717);
  FUN_004f1790(&DAT_00ea0e18,0x2719);
  FUN_004f1790(&DAT_00ea0e18,1000);
  FUN_004f1790(&DAT_00ea0e18,0x3e9);
  FUN_004f1790(&DAT_00ea0e18,0x3ea);
  FUN_004f1790(&DAT_00ea0e18,0x3eb);
  FUN_004f1790(&DAT_00ea0e18,0x3ec);
  FUN_004f1790(&DAT_00ea0e18,0x3ed);
  FUN_004f1790(&DAT_00ea0e18,0x3ee);
  FUN_004f1790(&DAT_00ea0e18,0x3ef);
  FUN_004f1790(&DAT_00ea0e18,0x3f0);
  FUN_004f1790(&DAT_00ea0e18,0x3f2);
  FUN_004f1790(&DAT_00ea0e18,0x3f3);
  FUN_004f1790(&DAT_00ea0e18,0x3f4);
  FUN_004f1790(&DAT_00ea0e18,0x3f5);
  FUN_004f1790(&DAT_00ea0e18,0x3fc);
  FUN_004f1790(&DAT_00ea0e18,0x3fd);
  FUN_004f1790(&DAT_00ea0e18,0x3fe);
  FUN_004f1790(&DAT_00ea0e18,0x3ff);
  FUN_004f1790(&DAT_00ea0e18,0x406);
  FUN_004f1790(&DAT_00ea0e18,0x407);
  FUN_004f1790(&DAT_00ea0e18,0x408);
  FUN_004f1790(&DAT_00ea0e18,0x409);
  FUN_004f1790(&DAT_00ea0e18,0x410);
  FUN_004f1790(&DAT_00ea0e18,0x411);
  FUN_004f1790(&DAT_00ea0e18,0x412);
  FUN_004f1790(&DAT_00ea0e18,0x41a);
  FUN_004f1790(&DAT_00ea0e18,0x41b);
  FUN_004f1790(&DAT_00ea0e18,0x41c);
  FUN_004f1790(&DAT_00ea0e18,0x41d);
  FUN_004f1790(&DAT_00ea0e18,0x424);
  FUN_004f1790(&DAT_00ea0e18,0x425);
  FUN_004f1790(&DAT_00ea0e18,0x426);
  FUN_004f1790(&DAT_00ea0e18,0x42e);
  FUN_004f1790(&DAT_00ea0e18,0x42f);
  FUN_004f1790(&DAT_00ea0e18,0x44c);
  FUN_004f1790(&DAT_00ea0e18,0x44d);
  FUN_004f1790(&DAT_00ea0e18,0x44e);
  FUN_004f1790(&DAT_00ea0e18,0x44f);
  FUN_004f1790(&DAT_00ea0e18,0x450);
  FUN_004f1790(&DAT_00ea0e18,0x451);
  FUN_004f1790(&DAT_00ea0e18,0x452);
  FUN_004f1790(&DAT_00ea0e18,0x453);
  FUN_004f1790(&DAT_00ea0e18,0x454);
  FUN_004f1790(&DAT_00ea0e18,0x455);
  FUN_004f1790(&DAT_00ea0e18,0x456);
  FUN_004f1790(&DAT_00ea0e18,0x457);
  FUN_004f1790(&DAT_00ea0e18,0x458);
  FUN_004f1790(&DAT_00ea0e18,0x459);
  FUN_004f1790(&DAT_00ea0e18,0x45a);
  FUN_004f1790(&DAT_00ea0e18,0x4ba);
  FUN_004f1790(&DAT_00ea0e18,0x4bb);
  FUN_004f1790(&DAT_00ea0e18,0x514);
  FUN_004f1790(&DAT_00ea0e18,0x578);
  iVar4 = DAT_005b3484;
  puVar3 = &DAT_006a7f88 + DAT_005b3484;
  *(undefined4 *)(DAT_005b3484 + 0x449ba) = 0;
  *(undefined4 *)(iVar4 + 0x449be) = 0;
  FUN_004f3060(puVar3);
  FUN_004f43a0(&DAT_00eb1bd8,s_AvataTexture1_0055565c);
  FUN_004f43a0(&DAT_00eb1bd8,s_AvataTexture2_00556914);
  FUN_004f43a0(&DAT_00eb1bd8,s_AvataEffectTexture1_00556900);
  FUN_004f43a0(&DAT_00eb1bd8,s_AvataEffectTexture2_005568ec);
  FUN_004f43a0(&DAT_00eb1bd8,s_CharacterTexture1_005568d8);
  FUN_004f43a0(&DAT_00eb1bd8,s_CharacterTexture2_005568c4);
  FUN_004f43a0(&DAT_00eb1bd8,s_CharEffectTexture1_005568a4);
  FUN_004f43a0(&DAT_00eb1bd8,s_CharEffectTexture2_00556890);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 == iVar5) {
    CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_ready_startgame_005570d8,0x28f,0x227,0x6b,0x2d,1,
                       0);
  }
  else {
    CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_ready_ready_005570c8,0x28f,0x227,0x6b,0x2d,1,0);
  }
  CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_ready_changeteam_00556b60,0x214,0x227,0x6b,0x2d,1,0
                    );
  CreateButtonWidget(&DAT_00e9be90,0,3,0x3eb,s_b_ready_exit_00556b50,0x28,0x227,0x6b,0x2d,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,4,0x3ec,s_b_ready_scroll_00556b0c,0x144,0x61,0x13,0x13,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,5,0x3ed,s_b_ready_scroll_00556b0c,0x1c9,0x61,0x13,0x13,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,6,0x3ee,s_b_ready_scroll_00556b0c,0x2ef,0x195,0x10,0x30,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,7,0x3ef,s_b_ready_scroll_00556b0c,0x2ef,0x1e8,0x10,0x30,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,8,0x3f0,s_b_ready_button_00556afc,0x16b,10,0x15,0x15,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,500,0x578,s_b_ready_button_00556afc,0x25,0x16b,0x19,0x14,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,300,0x514,s_b_ready_buddy_00556b40,0xa3,0x227,0x6b,0x2d,0,0);
  iVar4 = 0;
  do {
    CreateButtonWidget(&DAT_00e9be90,0,iVar4 + 100,iVar4 + 0x44c,s_b_ready_character_00556b1c,
                       (iVar4 % 5) * 0x42 + 0x21,(iVar4 / 5) * 0x32 + 0x184,0x42,0x32,iVar4 != 0xd,0
                      );
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xf);
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar11 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar11[2];
    while (uVar2 < 0x73) {
      if (uVar2 == 0x72) {
        *(undefined1 *)(piVar11 + 0x13) = 0;
        if (piVar11[9] != 3) {
          (**(code **)(*piVar11 + 4))(s_active_00551e58);
          *(undefined1 *)(piVar11 + 0x13) = 1;
        }
        break;
      }
      piVar11 = (int *)piVar11[4];
      uVar2 = piVar11[2];
    }
  }
  iVar4 = 0;
  do {
    FUN_004dc6d0(iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  FUN_004f1790(&DAT_00ea0e18,0x14b4);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  iVar4 = DAT_005b3484;
  *(undefined4 *)(DAT_005b3484 + 0x1fe1c) = 0;
  *(undefined4 *)(iVar4 + 0x1fe20) = 0;
  *(undefined4 *)(iVar4 + 0x1fe34) = 0;
  *(undefined4 *)(iVar4 + 0x1fe38) = 0;
  iStack_94 = 0x458fc;
  puVar10 = (undefined4 *)(param_1 + 0x6fc);
  do {
    puVar6 = operator_new(0x38);
    iVar4 = 0;
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      puVar6[1] = 0;
      puVar6[2] = 0;
      puVar6[3] = 0;
      puVar6[4] = 0;
      *(undefined1 *)(puVar6 + 5) = 0;
      *(undefined1 *)((int)puVar6 + 0x15) = 0;
      puVar6[6] = 0xffffffff;
      puVar6[7] = 0;
      *(undefined1 *)(puVar6 + 8) = 0;
      puVar6[10] = 0;
      puVar6[0xb] = 0;
      puVar6[9] = 0xffffffff;
      *puVar6 = &PTR_FUN_00556a40;
    }
    *puVar10 = puVar6;
    pvStack_90 = operator_new(0x8cc);
    uStack_4 = 0;
    if (pvStack_90 == (void *)0x0) {
      uVar7 = 0;
    }
    else {
      uVar7 = FUN_0044fb40(pvStack_90);
    }
    iVar5 = DAT_005b3484;
    uStack_4 = 0xffffffff;
    piVar11 = (int *)(&DAT_0067ec70 + DAT_005b3484);
    puVar10[1] = uVar7;
    if (0 < *piVar11) {
      pcStack_9c = &DAT_0067ec74 + iVar5;
      do {
        iVar8 = __stricmp(s_avata_00553fa8,pcStack_9c);
        if (iVar8 == 0) {
          puVar3 = &DAT_0069ec74 + iVar4 * 0x18 + iVar5;
          goto LAB_004d722d;
        }
        iVar4 = iVar4 + 1;
        pcStack_9c = pcStack_9c + 0x80;
      } while (iVar4 < *piVar11);
    }
    puVar3 = (undefined *)0x0;
LAB_004d722d:
    iVar5 = iStack_94;
    iVar4 = DAT_005b3484;
    *(undefined **)(puVar10[1] + 0x1c) = puVar3;
    if (*(char *)(iStack_94 + iVar4) == -1) {
      (**(code **)(*(int *)*puVar10 + 4))(&DAT_00553f90);
    }
    else {
      (**(code **)(*(int *)*puVar10 + 4))(s_normal_00552230);
    }
    iStack_94 = iVar5 + 2;
    puVar10 = puVar10 + 2;
  } while (iStack_94 < 0x4590c);
  *(undefined1 *)(DAT_005b3484 + 0x45578) = *(undefined1 *)(DAT_005b3484 + 0x457a0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004daa60(param_1,*(undefined1 *)(DAT_005b3484 + 0x45124));
  *(undefined1 *)(param_1 + 0x4cc) = 0;
  FUN_004db920();
  iVar4 = DAT_007934e4;
  _DAT_00e9b1c4 = 0;
  _DAT_00e9b1cc = 0;
  _DAT_00e9b1c8 = 0;
  _DAT_00e9b1d0 = 0;
  _DAT_00e9b1d4 = 0;
  _DAT_00e55e28 = 0;
  *(undefined1 *)(DAT_007934e4 + 8) = 1;
  SetWindowTextA(*(HWND *)(iVar4 + 4),&DAT_00551cb1);
  SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,0x3c,0);
  FUN_004db570();
  FUN_004db720();
  FUN_004da460(param_1,1,0);
  FUN_004eea30(1);
  *(undefined4 *)(param_1 + 0x4d4) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x618) = 1;
  *(undefined4 *)(param_1 + 0x620) = 0;
  FUN_004dbd50(param_1,0);
  *(undefined4 *)(param_1 + 0x268) = 0;
  *(undefined4 *)(param_1 + 0x628) = 0xffffffff;
  _DAT_00e9af1c = 500;
  _DAT_00e9aac4 = 0;
  _DAT_00e9aac8 = 0;
  InterlockedExchange((LONG *)&DAT_00e9aac0,0);
  FUN_004dc200(0xffffffff);
  iVar4 = DAT_005b3484;
  *(undefined1 *)(param_1 + 0x62c) = 0;
  *(undefined4 *)(&DAT_0067e3c8 + iVar4) = 0;
  if (*(FILE **)(&g_replayFileHandle + iVar4) != (FILE *)0x0) {
    uStack_95 = 3;
    _fwrite(&uStack_95,1,1,*(FILE **)(&g_replayFileHandle + iVar4));
    _fclose(*(FILE **)(&g_replayFileHandle + DAT_005b3484));
    iVar4 = DAT_005b3484;
    *(undefined4 *)(&g_replayFileHandle + DAT_005b3484) = 0;
  }
  *(undefined1 *)(param_1 + 9) = *(undefined1 *)(iVar4 + 0x44ef8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = DAT_005b3484;
  *(undefined4 *)(param_1 + 0x25d) = *(undefined4 *)(DAT_005b3484 + 0x457a1);
  *(undefined4 *)(param_1 + 0x261) = *(undefined4 *)(iVar4 + 0x457a5);
  *(undefined1 *)(param_1 + 0x230) = *(undefined1 *)(iVar4 + 0x45124);
  pcVar9 = (char *)(iVar4 + 0x44e64);
  iVar5 = param_1 - (int)pcVar9;
  do {
    cVar1 = *pcVar9;
    pcVar9[iVar5 + 0x62d] = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  piVar11 = (int *)(param_1 + 0x6fc);
  *(undefined4 *)(param_1 + 0x6b0) = 0xffffffff;
  pvStack_90 = (void *)0x0;
  iStack_94 = 0x458fc;
  do {
    if (*(char *)(iVar4 + 0x45914 + (int)pvStack_90) != '\0') {
      FUN_004dc5c0();
      iVar4 = DAT_005b3484;
    }
    cVar1 = *(char *)(iStack_94 + iVar4);
    if ((cVar1 == -1) || ('\x10' < cVar1)) {
      iVar5 = 0;
      if (0 < *(int *)(&DAT_0067ec70 + iVar4)) {
        pcVar9 = &DAT_0067ec74 + iVar4;
        do {
          iVar8 = __stricmp(s_rider_00553f98,pcVar9);
          if (iVar8 == 0) {
            puVar3 = &DAT_0069ec74 + iVar5 * 0x18 + iVar4;
            goto LAB_004d7599;
          }
          iVar5 = iVar5 + 1;
          pcVar9 = pcVar9 + 0x80;
        } while (iVar5 < *(int *)(&DAT_0067ec70 + iVar4));
      }
      puVar3 = (undefined *)0x0;
LAB_004d7599:
      pcVar9 = &DAT_00553f90;
    }
    else {
      _sprintf(acStack_8c,s_tank_d_00553fa0,cVar1 + 1);
      iVar4 = DAT_005b3484;
      piVar12 = (int *)(&DAT_0067ec70 + DAT_005b3484);
      iVar5 = 0;
      if (0 < *(int *)(&DAT_0067ec70 + DAT_005b3484)) {
        pcStack_9c = &DAT_0067ec74 + DAT_005b3484;
        do {
          iVar8 = __stricmp(acStack_8c,pcStack_9c);
          if (iVar8 == 0) {
            puVar3 = &DAT_0069ec74 + iVar5 * 0x18 + iVar4;
            pcVar9 = s_normal_00552230;
            goto LAB_004d759e;
          }
          iVar5 = iVar5 + 1;
          pcStack_9c = pcStack_9c + 0x80;
        } while (iVar5 < *piVar12);
      }
      puVar3 = (undefined *)0x0;
      pcVar9 = s_normal_00552230;
    }
LAB_004d759e:
    *(undefined **)(*piVar11 + 0x1c) = puVar3;
    (**(code **)(*(int *)*piVar11 + 4))(pcVar9);
    (**(code **)(*(int *)piVar11[1] + 4))(s_normal_00552230);
    iStack_94 = iStack_94 + 2;
    pvStack_90 = (void *)((int)pvStack_90 + 1);
    piVar11 = piVar11 + 2;
    iVar4 = DAT_005b3484;
    if (0x4590b < iStack_94) {
      *(undefined4 *)(param_1 + 0x73c) = 0;
      iVar4 = FUN_005094f0(&DAT_00e53c40);
      *(int *)(param_1 + 0x788) = iVar4;
      *(undefined1 *)(iVar4 + 0x1e) = 1;
      *unaff_FS_OFFSET = uStack_c;
      return;
    }
  } while( true );
}

