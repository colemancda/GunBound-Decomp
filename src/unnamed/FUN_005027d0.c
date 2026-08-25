/* FUN_005027d0 - 0x005027d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX and ESI RECOVERED (2026-08-25) from the single site 0x502278 in
 * FUN_00501770: `lea ebx,[esp+0x1c]` with one push pending = frame -0x4978 =
 * &local_4978, and `lea esi,[edi+0x17ac]` where EDI is that function's
 * param_1.  So this erases one 0x12-byte entry from the vector at
 * param_1 + 0x17ac and reports the removed key through EBX.
 */
#include "ghidra_types.h"


void FUN_005027d0(undefined4 param_1,undefined4 *regEbx,int regEsi)

{
  
  FUN_005040d0(param_1);
  *(int *)(regEsi + 8) = *(int *)(regEsi + 8) + -0x12;
  *regEbx = param_1;
  return;
}

