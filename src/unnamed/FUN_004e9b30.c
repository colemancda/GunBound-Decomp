/* FUN_004e9b30 - 0x004e9b30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): the whole function is one forwarded call --
 * `call 0x4f3150` is its first instruction -- so ECX, EDX and EAX all pass
 * straight through from its caller, which is an uncarved function at
 * 0x540e49.  EDX is an INPUT here (the object being constructed); Ghidra had
 * named it `regEdx` as though the callee produced it.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_004e9b30(undefined4 regEcx,undefined4 *regEdx,undefined4 regEax)

{
  float fVar1;
  
  FUN_004f3150(regEcx,regEdx,regEax);
  fVar1 = _DAT_00588f54 / _DAT_00588f50;
  *regEdx = &PTR_FUN_00557300;
  regEdx[0xbd] = 0x3fa4bc6a;
  regEdx[0xbf] = 0x3f800000;
  regEdx[0xc0] = 0x447a0000;
  regEdx[0xbe] = 0x3f24bc6a;
  regEdx[0xc1] = fVar1;
  return regEdx;
}

