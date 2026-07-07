/* FUN_004f6f10 - 0x004f6f10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f6f10(void)

{
  void *pvVar1;
  undefined4 unaff_ESI;
  
  pvVar1 = operator_new(0x210);
  if (pvVar1 != (void *)0x0) {
    *(undefined1 *)((int)pvVar1 + 0x208) = 0;
    *(undefined4 *)((int)pvVar1 + 0x20c) = unaff_ESI;
    return;
  }
  uRam0000020c = unaff_ESI;
  return;
}

