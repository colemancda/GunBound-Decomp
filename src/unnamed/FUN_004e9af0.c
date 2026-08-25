/* FUN_004e9af0 - 0x004e9af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25): its one call site is `mov ebx,eax` at 0x4e9ad2,
 * i.e. FUN_004e9ad0's own incoming EAX -- and that is DAT_00f22518, supplied
 * by the CRT atexit thunk at 0x543940 (`mov eax,0xf22518; jmp 0x4e9ad0`).
 * This object's destructor, in other words.
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

