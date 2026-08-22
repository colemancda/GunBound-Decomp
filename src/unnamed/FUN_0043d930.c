/* FUN_0043d930 - 0x0043d930 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d930(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_00554000;
  *(undefined1 *)(regEsi + 4) = 0;
  SetEvent((HANDLE)regEsi[2]);
  FUN_0043d9b0();
  return;
}

