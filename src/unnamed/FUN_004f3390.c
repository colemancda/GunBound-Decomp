/* FUN_004f3390 - 0x004f3390 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
  *
 * FIX (2026-11-03): 0x4f3391-0x4f3393 is `mov esi,ecx / call 0x4f33b0` with
 * ECX still `this`; the call dropped it. Now FUN_004f33b0(this).
 */
#include "ghidra_types.h"


void * __thiscall FUN_004f3390(void *param_1,int param_2)

{
  FUN_004f33b0((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

