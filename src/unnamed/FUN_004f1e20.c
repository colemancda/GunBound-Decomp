/* FUN_004f1e20 - 0x004f1e20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1e20(int param_1)

{
  void *pvVar1;
  void *pvVar2;
  void *_Memory;
  
  _Memory = *(void **)(param_1 + 0x15c);
  if (_Memory == (void *)0x0) {
    *(undefined4 *)(param_1 + 0x15c) = 0;
    return;
  }
  do {
    pvVar1 = *(void **)((int)_Memory + 0x150);
    pvVar2 = *(void **)((int)_Memory + 0x15c);
    if (pvVar1 != (void *)0x0) {
      _eh_vector_destructor_iterator_(pvVar1,0x160,*(int *)((int)pvVar1 + -4),FUN_004f1d40);
      _free((void *)((int)pvVar1 + -4));
    }
    *(undefined4 *)((int)_Memory + 0x150) = 0;
    _free(_Memory);
    _Memory = pvVar2;
  } while (pvVar2 != (void *)0x0);
  *(undefined4 *)(param_1 + 0x15c) = 0;
  return;
}

