/* FUN_004e9af0 - 0x004e9af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e9af0(void)

{
  void *pvVar1;
  void *_Memory;
  undefined4 *unaff_EBX;
  
  _Memory = (void *)unaff_EBX[0x4c];
  while (_Memory != (void *)0x0) {
    pvVar1 = *(void **)((int)_Memory + 300);
    FUN_004e9520();
    _free(_Memory);
    _Memory = pvVar1;
  }
  unaff_EBX[0x4c] = 0;
  *unaff_EBX = 0;
  return;
}

