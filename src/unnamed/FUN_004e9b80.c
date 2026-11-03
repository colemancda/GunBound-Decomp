/* FUN_004e9b80 - 0x004e9b80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
  *
 * FIX (2026-11-03): ECX was dropped at the inner call. 0x4e9b81-0x4e9b83 is
 * `mov esi,ecx / call 0x4e9ba0` with ECX still `this`; slot 0 of vtable
 * 0x557300 (the 0x308-byte scene-node subclass). Now FUN_004e9ba0(this).
 */
#include "ghidra_types.h"


void * __thiscall FUN_004e9b80(void *param_1,int param_2)

{
  FUN_004e9ba0((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

