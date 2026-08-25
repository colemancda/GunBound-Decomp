/* FUN_004ef820 - 0x004ef820 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ef820(undefined4 *regEax)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = regEax + 2;
  *regEax = &PTR_LAB_005574e0;
  *(undefined1 *)(regEax + 4) = 0;
  SetEvent((HANDLE)regEax[2]);
  if ((HANDLE)regEax[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEax[1],1000);
  }
  iVar2 = 2;
  do {
    CloseHandle((HANDLE)*puVar1);
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

