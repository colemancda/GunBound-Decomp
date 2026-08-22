/* FUN_0040d1c0 - 0x0040d1c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040d1c0(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_005520a4;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  if ((HANDLE)regEsi[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEsi[1],1000);
  }
  CloseHandle((HANDLE)regEsi[2]);
  return;
}

