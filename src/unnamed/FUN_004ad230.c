/* FUN_004ad230 - 0x004ad230 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ad230(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int *piVar6;
  code *pcVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_238 [8];
  undefined1 local_230 [20];
  int local_21c;
  undefined4 uStack_14;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df6b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined4 *)(param_1 + 0x3fa0) = 0;
  EncodeChecksumPairSum(param_1 + 0xf54,local_230,param_1 + 0x1178);
  pcVar7 = (code *)EnterCriticalSection;
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3f9c) = uVar2;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_238);
    pcVar7 = (code *)EnterCriticalSection;
  }
  (*pcVar7)(&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar7)(&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar5 = operator_new(0x54);
    if (pvVar5 == (void *)0x0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)FUN_0047e940();
    }
    piVar6[0xe] = iVar4;
    piVar6[0xf] = iVar3;
    piVar6[0x11] = 0;
    *(undefined1 *)(piVar6 + 0x14) = 0;
    piVar6[6] = 0x206f;
    iVar3 = FindPreloadedTextureByName(s_ssflame4_00555170);
    piVar6[7] = iVar3;
    (**(code **)(*piVar6 + 4))(s_flame_00553d2c);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = uStack_14;
  return;
}

