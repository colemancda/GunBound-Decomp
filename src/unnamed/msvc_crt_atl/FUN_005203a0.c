/* FUN_005203a0 - 0x005203a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005203a0(undefined4 param_1)

{
  LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter;
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005376d4;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  if (DAT_005b15ac != (undefined1 *)0x0) {
    *unaff_FS_OFFSET = local_c;
    return 0;
  }
  lpTopLevelExceptionFilter = SetUnhandledExceptionFilter(FUN_005230f0);
  puVar1 = operator_new(0x114c);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *puVar1 = 0;
    puVar1[1] = 0;
    *(undefined4 *)(puVar1 + 4) = 0;
    *(undefined4 *)(puVar1 + 8) = 0;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    *(undefined4 *)(puVar1 + 0x10) = 0;
    *(undefined4 *)(puVar1 + 0x14) = 0;
    puVar1[0x18] = 0;
    *(undefined4 *)(puVar1 + 0x1c) = 0;
    puVar1[0x20] = 0;
    puVar1[0x21] = 0;
    puVar1[0x22] = 0;
    *(undefined4 *)(puVar1 + 0x24) = 0xffffffff;
    *(undefined4 *)(puVar1 + 0x105c) = 0;
    local_4._0_1_ = 1;
    local_4._1_3_ = 0;
    FUN_00524130();
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_005246e0();
    *(undefined4 *)(puVar1 + 0x10c4) = 0;
    *(undefined4 *)(puVar1 + 0x10e8) = 0;
    *(undefined4 *)(puVar1 + 0x10ec) = 0;
    puVar1[0x1130] = 0;
    puVar1[0x1131] = 0;
    *(undefined4 *)(puVar1 + 0x1134) = 1000;
    *(undefined4 *)(puVar1 + 0x1138) = 0;
    *(undefined4 *)(puVar1 + 0x113c) = 0;
    puVar1[0x1140] = 0;
    *(undefined4 *)(puVar1 + 0x1144) = 0;
    *(undefined4 *)(puVar1 + 0x1148) = 0;
  }
  local_4 = 0xffffffff;
  DAT_005b15ac = puVar1;
  uVar2 = FUN_005207d0(param_1);
  *(undefined4 *)(DAT_005b15ac + 0x10) = uVar2;
  if (lpTopLevelExceptionFilter != (LPTOP_LEVEL_EXCEPTION_FILTER)0x0) {
    SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
  }
  uVar2 = *(undefined4 *)(DAT_005b15ac + 0x10);
  *unaff_FS_OFFSET = local_c;
  return uVar2;
}

