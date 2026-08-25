/* FUN_004e9af0 - 0x004e9af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25): its one call site is `mov ebx,eax` at 0x4e9ad2,
 * i.e. FUN_004e9ad0's own incoming EAX.  A batch proposal claimed the value
 * was &DAT_00f22518; that is not supportable here -- FUN_004e9ad0 is itself
 * unreferenced, so nothing in the image says what its EAX holds -- and the
 * argument is written as the forwarded register instead.
 */
#include "ghidra_types.h"


void FUN_004e9af0(undefined4 *regEbx)

{
  void *pvVar1;
  void *_Memory;
  
  _Memory = (void *)regEbx[0x4c];
  while (_Memory != (void *)0x0) {
    pvVar1 = *(void **)((int)_Memory + 300);
    FUN_004e9520();
    _free(_Memory);
    _Memory = pvVar1;
  }
  regEbx[0x4c] = 0;
  *regEbx = 0;
  return;
}

