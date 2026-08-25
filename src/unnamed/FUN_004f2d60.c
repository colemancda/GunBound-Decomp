/* FUN_004f2d60 - 0x004f2d60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25): `mov esi,eax; mov ebx,esi` at 0x4f2d42 in
 * FUN_004f2d40, so EBX is that forwarder's own incoming EAX.
 */
#include "ghidra_types.h"


void FUN_004f2d60(int regEbx)

{
  void *pvVar1;
  void *_Memory;
  
  _Memory = *(void **)(regEbx + 0x3d8);
  while (_Memory != (void *)0x0) {
    pvVar1 = *(void **)((int)_Memory + 0x3d8);
    FUN_004f2a10();
    _free(_Memory);
    _Memory = pvVar1;
  }
  *(undefined4 *)(regEbx + 0x3d8) = 0;
  return;
}

