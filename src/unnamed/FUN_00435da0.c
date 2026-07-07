/* FUN_00435da0 - 0x00435da0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00435da0(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053aed4;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    iVar2 = (int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2;
    for (iVar6 = (param_2 - iVar2) + -5; iVar6 <= iVar2 + 5 + param_2; iVar6 = iVar6 + 1) {
      iVar3 = FUN_004511b0(iVar6);
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(param_4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (param_3 < iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          param_3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField((param_3 * 0xf) / 10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = FUN_0040a5f0(iVar3 + 0x3c,local_230,param_2);
        local_4 = 0;
        FUN_0040a8c0(uVar5,local_454,2);
        local_4._0_1_ = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar5);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = (uint)local_4._1_3_ << 8;
        if (local_440 != 0) {
          FUN_0040a240();
          FUN_0040b540(local_45c);
        }
        local_4 = 0xffffffff;
        if (local_21c != 0) {
          FUN_0040a240();
          FUN_0040b540(local_45c);
        }
        goto LAB_0043604a;
      }
    }
    pvVar4 = operator_new(0x6ac);
    local_4 = 2;
    if (pvVar4 == (void *)0x0) {
      iVar6 = 0;
    }
    else {
      iVar6 = FUN_0046dde0(pvVar4);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(iVar6 + 0x484) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject();
  }
LAB_0043604a:
  *unaff_FS_OFFSET = local_c;
  return;
}

