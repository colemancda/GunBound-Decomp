/* FUN_0043d9b0 - 0x0043d9b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d9b0(void)

{
  undefined4 *in_EAX;
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = in_EAX + 2;
  *in_EAX = &PTR_LAB_00553ff8;
  *(undefined1 *)(in_EAX + 4) = 0;
  SetEvent((HANDLE)in_EAX[2]);
  if ((HANDLE)in_EAX[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)in_EAX[1],1000);
  }
  iVar2 = 2;
  do {
    CloseHandle((HANDLE)*puVar1);
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

