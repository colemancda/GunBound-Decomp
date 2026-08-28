/* Vector_UninitCopy_8 - 0x005045d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the uninitialised-copy member of the 8-byte
 * {CStringA, CStringA} pair vector - copy-construct [first, last) into
 * raw storage stepping 8, cloning both CString handles per element via
 * the 0x43de10 addref/clone, with the same EH state ladder as
 * Vector_UninitCopy_34 / _1e, between which it sits in the binary
 * (0x5045a0 / 0x5046b0). Vector_InsertN_8 calls it in all three of the
 * arms where Vector_InsertN_34 calls Vector_UninitCopy_34: realloc head
 * and tail, append-overlap tail, and the shift arm.
 */
#include "ghidra_types.h"


int * __thiscall Vector_UninitCopy_8(int param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_00537b7d;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 8) {
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
  return param_3;
}

