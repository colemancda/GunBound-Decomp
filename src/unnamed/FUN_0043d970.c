/* FUN_0043d970 - 0x0043d970 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d970(undefined4 *regEbx)

{
  HANDLE pvVar1;
  undefined4 *puVar2;
  int iVar3;
  
  *regEbx = &PTR_LAB_00553ff8;
  regEbx[1] = 0;
  puVar2 = regEbx + 2;
  iVar3 = 2;
  do {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *puVar2 = pvVar1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined1 *)(regEbx + 4) = 0;
  return;
}

