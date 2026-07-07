/* FUN_004f2e40 - 0x004f2e40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f2e40(void)

{
  undefined4 *puVar1;
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_FUN_00557534;
  puVar1 = operator_new(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[1] = 0xffffffff;
    puVar1[2] = 0xffffffff;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *(undefined1 *)(puVar1 + 5) = 0;
    *puVar1 = &PTR_FUN_00557530;
    *(undefined1 *)((int)puVar1 + 0x15) = 1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  unaff_ESI[1] = puVar1;
  puVar1[3] = puVar1;
  *(undefined4 *)(unaff_ESI[1] + 0x10) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x18) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x1c) = unaff_ESI[1];
  return;
}

