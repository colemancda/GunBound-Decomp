/* FUN_004eebe0 - 0x004eebe0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004eebe0(void)

{
  undefined4 uVar1;
  uintptr_t uVar2;
  undefined4 *unaff_ESI;
  
  FUN_004ef7e0();
  *unaff_ESI = &PTR_LAB_005574e8;
  unaff_ESI[5] = 0;
  unaff_ESI[0xe] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x13) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 8));
  *(undefined1 *)(unaff_ESI + 4) = 1;
  uVar2 = __beginthread(FUN_004ef870,0,unaff_ESI);
  unaff_ESI[1] = uVar2;
  if (uVar2 == 0) {
    *(undefined1 *)(unaff_ESI + 4) = 0;
  }
  uVar1 = DAT_00588f44;
  unaff_ESI[0x14] = 0;
  unaff_ESI[0x26] = 0;
  unaff_ESI[0x27] = 0;
  unaff_ESI[0x29] = 0;
  unaff_ESI[0x2a] = 0;
  unaff_ESI[0x2b] = 0;
  *unaff_ESI = &PTR_LAB_005574cc;
  unaff_ESI[0x28] = 20000;
  unaff_ESI[0x2c] = uVar1;
  unaff_ESI[0x2d] = 0xffffffff;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

