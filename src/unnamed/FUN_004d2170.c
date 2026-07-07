/* FUN_004d2170 - 0x004d2170 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 * FUN_004d2170(undefined4 *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *pvVar2;
  uintptr_t uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053910c;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0xa9) = 0;
  param_1[0x26] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x132) = 0;
  param_1[0xaf] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(local_4._1_3_,1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x133] = param_2;
  uVar1 = *(undefined4 *)(&DAT_0056dc30 + param_2 * 4);
  pvVar2 = operator_new(0x210);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    *(undefined1 *)((int)pvVar2 + 0x208) = 0;
  }
  *(undefined4 *)((int)pvVar2 + 0x20c) = uVar1;
  param_1[0x213a] = pvVar2;
  *(undefined1 *)(param_1 + 0x2139) = 0;
  *(undefined1 *)((int)param_1 + 0x84e5) = 0;
  *(undefined1 *)((int)param_1 + 0x84e6) = 0;
  *param_1 = 0;
  pvVar2 = operator_new(0x24a70);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    pvVar2 = (void *)FUN_004e54e0(param_2,param_3);
  }
  param_1[0x2138] = pvVar2;
  *(undefined1 *)((int)pvVar2 + 0x18) = 1;
  uVar3 = __beginthread(FUN_00405dc0,0,pvVar2);
  *(uintptr_t *)((int)pvVar2 + 4) = uVar3;
  if (uVar3 == 0) {
    *(undefined1 *)((int)pvVar2 + 0x18) = 0;
  }
  param_1[0x213b] = 0;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

