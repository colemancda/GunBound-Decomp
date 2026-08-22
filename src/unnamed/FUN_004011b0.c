/* FUN_004011b0 - 0x004011b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004011b0(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_0054b458;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  *regEsi = &PTR_LAB_0054b450;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  if ((HANDLE)regEsi[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEsi[1],1000);
  }
  CloseHandle((HANDLE)regEsi[2]);
  return;
}

