/* FUN_00437f70 - 0x00437f70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00437f70(undefined4 param_1,int param_2,int param_3,uint param_4,undefined4 param_5)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  FUN_0043c4f0();
  pvVar1 = operator_new(0x3fe4);
  piVar4 = (int *)0x0;
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    piVar4 = (int *)FUN_0047f9e0();
  }
  local_4 = 0xffffffff;
  piVar4[6] = 0x17ce;
  piVar4[0xe] = 0x17cf;
  piVar4[0xe25] = 0x1f4d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_4 = param_4 & 0x80000007;
  piVar4[0xfee] = param_3;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar4 + 0xf) = (char)param_4;
  piVar4[0xfea] = param_2;
  piVar4[0xfeb] = param_3 + 200;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = FindPreloadedTextureByName(s_laserion_00553be8);
  piVar4[7] = iVar2;
  (**(code **)(*piVar4 + 4))(s_normal_00552230);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = pvVar1;
  return;
}

