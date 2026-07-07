/* FUN_004e5bb0 - 0x004e5bb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004e5bb0(undefined4 *param_1)

{
  HANDLE pvVar1;
  undefined4 *puVar2;
  int iVar3;
  
  *param_1 = &PTR_LAB_005572e0;
  param_1[1] = 0;
  puVar2 = param_1 + 2;
  iVar3 = 4;
  do {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *puVar2 = pvVar1;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined1 *)(param_1 + 6) = 0;
  return param_1;
}

