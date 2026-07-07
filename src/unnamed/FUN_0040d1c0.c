/* FUN_0040d1c0 - 0x0040d1c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040d1c0(void)

{
  undefined4 *unaff_ESI;
  
  *unaff_ESI = &PTR_LAB_005520a4;
  *(undefined1 *)(unaff_ESI + 3) = 0;
  SetEvent((HANDLE)unaff_ESI[2]);
  if ((HANDLE)unaff_ESI[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)unaff_ESI[1],1000);
  }
  CloseHandle((HANDLE)unaff_ESI[2]);
  return;
}

