/* FUN_0043d930 - 0x0043d930 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d930(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_00554000;
  *(undefined1 *)(unaff_ESI + 4) = 0;
  SetEvent((HANDLE)unaff_ESI[2]);
  FUN_0043d9b0();
  return;
}

