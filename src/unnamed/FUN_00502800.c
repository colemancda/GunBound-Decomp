/* FUN_00502800 - 0x00502800 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): `lea eax,[esp+0xa0]` at 0x5019e1 in
 * FUN_00501770, no push pending.  That caller's frame constant is -0x4990,
 * pinned by three independent slots (esp+0x18 -> local_4978, esp+0x38 ->
 * local_4958, esp+0xa0 -> local_48f0), so EAX is the address of local_48f0,
 * the 0x34-byte element being appended.  ECX (param_1) is the vector.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502800(int param_1,undefined4 regEax)

{
  int iVar1;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x34) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x34))) {
    iVar1 = *(int *)(param_1 + 8);
    FUN_00504160(param_1);
    *(int *)(param_1 + 8) = iVar1 + 0x34;
    return;
  }
  FUN_00502a20(&local_4,*(undefined4 *)(param_1 + 8),regEax);
  return;
}

