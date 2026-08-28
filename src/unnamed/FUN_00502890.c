/* FUN_00502890 - 0x00502890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-25): `lea esi,[esp+0x38]` at 0x501e1e in
 * FUN_00501770 = &local_4958 under that function's -0x4990 frame constant.
 * ESI is the vector; ECX (param_1) is the 8-byte element pushed onto it.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502890(undefined4 param_1,int regEsi)

{
  int iVar1;
  
  iVar1 = *(int *)(regEsi + 4);
  if ((iVar1 != 0) &&
     ((uint)(*(int *)(regEsi + 8) - iVar1 >> 3) < (uint)(*(int *)(regEsi + 0xc) - iVar1 >> 3))
     ) {
    iVar1 = *(int *)(regEsi + 8);
    Vector_UninitFillN_8(iVar1,param_1);
    *(int *)(regEsi + 8) = iVar1 + 8;
    return;
  }
  Vector_InsertN_8(regEsi,*(undefined4 *)(regEsi + 8),1);
  return;
}

