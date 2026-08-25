/* FUN_004154c0 - 0x004154c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the map object, from FUN_0040d160's `mov
 * eax,esi` (its `this`); ECX (param_1) is a phantom there and EDX (param_2)
 * is the literal 10, the initial bucket count.
 */
#include "ghidra_types.h"


void __fastcall FUN_004154c0(undefined4 param_1,undefined4 param_2,undefined4 *regEax)

{
  *regEax = 0;
  regEax[1] = 0;
  regEax[2] = 0;
  regEax[3] = 0;
  regEax[4] = param_2;
  regEax[5] = 0;
  return;
}

