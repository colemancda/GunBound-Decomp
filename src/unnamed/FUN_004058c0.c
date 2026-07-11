/* FUN_004058c0 - 0x004058c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* unaff_EDI (the connection-manager object being constructed) arrives via a
 * dropped EDI register in the original (orig 0x40dc22: `mov edi, eax` before
 * the call) - promoted to an explicit first parameter; the sole caller
 * (WinMain.c) passes pvVar4 directly. */
void FUN_004058c0(void *unaff_EDI, undefined4 param_1,undefined4 param_2)

{
  void *pvVar1;
  uintptr_t uVar2;

  *(undefined1 *)((int)unaff_EDI + 0x2008) = 0;
  *(undefined1 *)((int)unaff_EDI + 0x2009) = 0;
  pvVar1 = operator_new(0x24a70);
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    /* FUN_004e54e0 also takes this new object via a dropped ESI register
     * (orig: `mov esi, eax` before the call) - see that file. */
    FUN_004e54e0(pvVar1,param_1,param_2);
  }
  *(void **)((int)unaff_EDI + 0x2004) = pvVar1;
  *(undefined1 *)((int)pvVar1 + 0x18) = 1;
  uVar2 = __beginthread(FUN_00405dc0,0,pvVar1);
  *(uintptr_t *)((int)pvVar1 + 4) = uVar2;
  if (uVar2 == 0) {
    *(undefined1 *)((int)pvVar1 + 0x18) = 0;
  }
  return;
}

