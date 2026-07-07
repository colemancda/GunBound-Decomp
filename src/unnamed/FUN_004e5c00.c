/* FUN_004e5c00 - 0x004e5c00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e5c00(void)

{
  undefined4 *in_EAX;
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = in_EAX + 2;
  *in_EAX = &PTR_LAB_005572e0;
  *(undefined1 *)(in_EAX + 6) = 0;
  SetEvent((HANDLE)in_EAX[2]);
  if ((HANDLE)in_EAX[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)in_EAX[1],1000);
  }
  iVar2 = 4;
  do {
    CloseHandle((HANDLE)*puVar1);
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

