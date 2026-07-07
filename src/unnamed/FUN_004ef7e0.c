/* FUN_004ef7e0 - 0x004ef7e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ef7e0(void)

{
  HANDLE pvVar1;
  undefined4 *unaff_EBX;
  undefined4 *puVar2;
  int iVar3;
  
  *unaff_EBX = &PTR_LAB_005574e0;
  unaff_EBX[1] = 0;
  puVar2 = unaff_EBX + 2;
  iVar3 = 2;
  do {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *puVar2 = pvVar1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined1 *)(unaff_EBX + 4) = 0;
  return;
}

