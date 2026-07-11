/* FUN_004e54e0 - 0x004e54e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* unaff_ESI (the object being constructed) arrives via a dropped ESI
 * register in the original (`mov esi, eax` before the call in
 * FUN_004058c0) - promoted to an explicit first parameter. */
undefined4 FUN_004e54e0(undefined4 *unaff_ESI, undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;

  FUN_004e5bb0(unaff_ESI);
  *unaff_ESI = &PTR_FUN_005572e8;
  unaff_ESI[0x9290] = 0;
  unaff_ESI[0x9291] = 0;
  unaff_ESI[0x9292] = 0;
  unaff_ESI[0x9293] = 0;
  unaff_ESI[0x9295] = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x9296));
  unaff_ESI[0x8b] = 1;
  unaff_ESI[9] = 0xffffffff;
  puVar2 = unaff_ESI + 10;
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[7] = param_1;
  *(undefined2 *)(unaff_ESI + 0x8a) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x22a) = 0;
  unaff_ESI[0x908e] = 0;
  unaff_ESI[0x908d] = 0;
  unaff_ESI[0x908f] = 0;
  unaff_ESI[0x108c] = 0;
  unaff_ESI[8] = param_2;
  puVar2 = unaff_ESI + 0x8c;
  for (iVar1 = 0x1000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

