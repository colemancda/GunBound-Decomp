/* FUN_004058c0 - 0x004058c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004058c0(undefined4 param_1,undefined4 param_2)

{
  void *pvVar1;
  uintptr_t uVar2;
  int unaff_EDI;
  
  *(undefined1 *)(unaff_EDI + 0x2008) = 0;
  *(undefined1 *)(unaff_EDI + 0x2009) = 0;
  pvVar1 = operator_new(0x24a70);
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)FUN_004e54e0(param_1,param_2);
  }
  *(void **)(unaff_EDI + 0x2004) = pvVar1;
  *(undefined1 *)((int)pvVar1 + 0x18) = 1;
  uVar2 = __beginthread(FUN_00405dc0,0,pvVar1);
  *(uintptr_t *)((int)pvVar1 + 4) = uVar2;
  if (uVar2 == 0) {
    *(undefined1 *)((int)pvVar1 + 0x18) = 0;
  }
  return;
}

