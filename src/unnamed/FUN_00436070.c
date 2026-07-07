/* FUN_00436070 - 0x00436070 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00436070(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  void *pvVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x4a8);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      FUN_00481fb0(pvVar2);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&DAT_006a7724 + DAT_005b3484) <= param_3) {
      param_3 = *(int *)(&DAT_006a7724 + DAT_005b3484);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject();
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

