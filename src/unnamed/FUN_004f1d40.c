/* FUN_004f1d40 - 0x004f1d40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f1d40(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 0x150);
  if (pvVar1 != (void *)0x0) {
    _eh_vector_destructor_iterator_(pvVar1,0x160,*(int *)((int)pvVar1 + -4),FUN_004f1d40);
    _free((void *)((int)pvVar1 + -4));
  }
  *(undefined4 *)(param_1 + 0x150) = 0;
  return;
}

