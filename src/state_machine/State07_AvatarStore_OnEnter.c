/* State07_AvatarStore_OnEnter - 0x00447760 in the original binary.
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


/* WARNING: Removing unreachable block (ram,0x00447efc) */
/* WARNING: Removing unreachable block (ram,0x00447f06) */

void __fastcall State07_AvatarStore_OnEnter(int param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  byte bVar6;
  undefined2 *puVar7;
  int iVar8;
  
  FUN_004f1790(&DAT_00ea0e18,10000);
  FUN_004f1790(&DAT_00ea0e18,0x2711);
  FUN_004f1790(&DAT_00ea0e18,0x2712);
  FUN_004f1790(&DAT_00ea0e18,0x2713);
  FUN_004f1790(&DAT_00ea0e18,0x2714);
  FUN_004f1790(&DAT_00ea0e18,1000);
  FUN_004f1790(&DAT_00ea0e18,0x3e9);
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
  FUN_004f1790(&DAT_00ea0e18,0x4b0);
  FUN_004f1790(&DAT_00ea0e18,0x4b1);
  FUN_004f1790(&DAT_00ea0e18,0x4b2);
  FUN_004f1790(&DAT_00ea0e18,0x4b3);
  FUN_004f1790(&DAT_00ea0e18,0x514);
  FUN_004f1790(&DAT_00ea0e18,0x515);
  FUN_004f1790(&DAT_00ea0e18,0x516);
  FUN_004f1790(&DAT_00ea0e18,0x517);
  FUN_004f1790(&DAT_00ea0e18,0x518);
  FUN_004f1790(&DAT_00ea0e18,0x519);
  FUN_004f1790(&DAT_00ea0e18,0x51a);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  FUN_004f43a0(&DAT_00eb1bd8,s_AvataTexture1_0055565c);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  uVar5 = FindPreloadedTextureByName(s_avata_00553fa8);
  *(undefined4 *)(param_1 + 0x30bd8) = uVar5;
  (**(code **)(*(int *)(param_1 + 0x30bbc) + 4))(s_normal_00552230);
  FUN_004eea30(1);
  *(undefined4 *)(DAT_005b3484 + 0x44e60) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x32f91) = 0;
  FUN_00429800();
  cVar3 = FUN_00419d30();
  if (cVar3 == '\0') {
    FUN_004124a0(1);
  }
  FUN_00423bf0();
  FUN_00449540(param_1,1);
  *(undefined4 *)(param_1 + 0x454) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0044b0b0(param_1);
  FUN_00424400();
  *(undefined1 *)(param_1 + 0x30bb8) = 0;
  FUN_004141b0(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = 0;
  puVar7 = (undefined2 *)(param_1 + 0x325a8);
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *puVar7 = uVar4;
    iVar8 = iVar8 + 0x224;
    puVar7 = puVar7 + 1;
  } while (iVar8 < 0x890);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32c54) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32c55) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32c54) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32c55) = bVar6;
  *(byte *)(param_1 + 0x32c56) = *(byte *)(param_1 + 0x32c54) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32e63) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32e64) = bVar6;
  *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(char *)(param_1 + 0x32ce0) = (char)iVar8;
  iVar8 = _rand();
  *(byte *)(param_1 + 0x32ce1) = (byte)iVar8;
  bVar6 = *(byte *)(param_1 + 0x32ce0) & 7;
  bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
  *(byte *)(param_1 + 0x32ce1) = bVar6;
  *(byte *)(param_1 + 0x32ce2) = *(byte *)(param_1 + 0x32ce0) + bVar6 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_1 + 0x32f90) = 1;
  FUN_0044b720(param_1);
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar1[2];
    while (uVar2 < 0xb) {
      if (uVar2 == 10) {
        *(undefined1 *)(piVar1 + 0x13) = 0;
        if (piVar1[9] != 3) {
          (**(code **)(*piVar1 + 4))(s_active_00551e58);
          *(undefined1 *)(piVar1 + 0x13) = 1;
        }
        break;
      }
      piVar1 = (int *)piVar1[4];
      uVar2 = piVar1[2];
    }
  }
  uVar5 = FUN_00509e60(&DAT_00e53c40);
  *(undefined4 *)(param_1 + 0x34784) = uVar5;
  FUN_00449250(param_1,1,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = DAT_005b3484;
  *(undefined1 *)(param_1 + 0x32f92) = 0;
  *(undefined4 *)(param_1 + 0x32f94) = 0x80000000;
  *(undefined4 *)(param_1 + 0x32f98) = 0x7fffffff;
  if (*(int *)(iVar8 + 0x44bec) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = _rand();
    *(char *)(param_1 + 0x32e63) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)(param_1 + 0x32e64) = (byte)iVar8;
    bVar6 = *(byte *)(param_1 + 0x32e63) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar8 | '\0' << bVar6;
    *(byte *)(param_1 + 0x32e64) = bVar6;
    *(byte *)(param_1 + 0x32e65) = *(byte *)(param_1 + 0x32e63) + bVar6 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0044b720(param_1);
  }
  else {
    FUN_0044b900(param_1);
  }
  *(undefined4 *)(param_1 + 0x34790) = 0;
  *(undefined1 *)(param_1 + 0x34814) = 0;
  *(undefined4 *)(param_1 + 0x32f9c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3478c) = 0xffffffff;
  return;
}

