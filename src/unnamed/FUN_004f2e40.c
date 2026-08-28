/* FUN_004f2e40 - 0x004f2e40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is `this`.  The first
 * thing the body does is stamp a vtable through it
 * (`*unaff_ESI = &PTR_FUN_00557534;`) before allocating and initialising the
 * 0x20-byte node it hangs off, so this is a constructor and ESI is the object
 * being constructed.
 *
 * Seven call sites across seven callers, one each, so nothing needed pairing:
 *   - FUN_00405f00, FUN_0040cd40, FUN_004f1750 and FUN_004f3940 are two-line
 *     thunks (`push esi / mov esi,eax / call`) that already declare the value
 *     as regEax, so they simply forward it.
 *   - FUN_00401910 uses `mov ebp,[esp+0x18]`, which under its SEH triple plus
 *     two saves is E+4 = param_1.
 *   - FUN_00415d40 does `lea esi,[ebp + 0x6a7f88]` with ebp from [esp+0x1c],
 *     E+4 = param_1 under its SEH triple plus three saves -- and 0x6a7f88 is
 *     the active-object list offset the weather-hazard spawners already name.
 *   - FUN_004e3810 does `lea esi,[edi + 0x85c]` with edi from [esp+0x1c],
 *     E+4 = param_1 under its SEH triple plus three saves.
 */
#include "ghidra_types.h"


void FUN_004f2e40(undefined4 *regEsi)

{
  undefined4 *puVar1;
  undefined4 *unaff_ESI = regEsi;
  
  *unaff_ESI = &PTR_FUN_00557534;
  puVar1 = operator_new(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[1] = 0xffffffff;
    puVar1[2] = 0xffffffff;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *(undefined1 *)(puVar1 + 5) = 0;
    *puVar1 = &PTR_FUN_00557530;
    *(undefined1 *)((int)puVar1 + 0x15) = 1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  unaff_ESI[1] = puVar1;
  puVar1[3] = puVar1;
  *(undefined4 *)(unaff_ESI[1] + 0x10) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x18) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x1c) = unaff_ESI[1];
  return;
}

