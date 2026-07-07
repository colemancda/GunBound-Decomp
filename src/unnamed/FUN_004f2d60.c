/* FUN_004f2d60 - 0x004f2d60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f2d60(void)

{
  void *pvVar1;
  void *_Memory;
  int unaff_EBX;
  
  _Memory = *(void **)(unaff_EBX + 0x3d8);
  while (_Memory != (void *)0x0) {
    pvVar1 = *(void **)((int)_Memory + 0x3d8);
    FUN_004f2a10();
    _free(_Memory);
    _Memory = pvVar1;
  }
  *(undefined4 *)(unaff_EBX + 0x3d8) = 0;
  return;
}

