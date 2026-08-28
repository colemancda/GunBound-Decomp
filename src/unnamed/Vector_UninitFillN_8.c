/* Vector_UninitFillN_8 - 0x00504190 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the uninitialised-fill member of the 8-byte
 * {CStringA, CStringA} pair vector - copy-construct n copies of the
 * value pair into raw storage, with the EH state ladder (0/1/2 per
 * member) that unwinds partially-constructed elements, exactly the
 * Vector_UninitFillN_34 / _1e shape at stride 8; it sits between those
 * two in the binary (0x504160 / 0x504270). Serves the same slot in
 * Vector_InsertN_8's realloc and append arms that the _34 member
 * serves in Vector_InsertN_34's, plus the push-back wrapper
 * FUN_00502890.
 */
#include "ghidra_types.h"


void __fastcall Vector_UninitFillN_8(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_00537abd;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_8 = 1;
    if (param_3 != (int *)0x0) {
      iVar1 = FUN_0043de10();
      *param_3 = iVar1 + 0x10;
      local_8 = 2;
      iVar1 = FUN_0043de10();
      param_3[1] = iVar1 + 0x10;
    }
    param_3 = param_3 + 2;
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

