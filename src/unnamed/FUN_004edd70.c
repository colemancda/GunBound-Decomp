/* FUN_004edd70 - 0x004edd70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004edd70(int param_1)

{
  /* BRING-UP WORKAROUND: skip DirectInput keyboard-device acquisition.
   *
   * Ghidra's decompile at THIS call site is unusable as-is: InitGame.c calls
   * FUN_004edd70(param_1) passing its OWN param_1 (the window handle), but
   * the original disassembly (0x40ecb0-0x40ecb5) shows the real caller
   * loads ECX with a FIXED GLOBAL STRUCT ADDRESS (0xe52810) instead - Ghidra
   * gave both unrelated values the same "param_1" name. That struct's field
   * at +8 holds a REFGUID (recovered as an argument to
   * IDirectInput8::CreateDevice at vtbl+0xc, per 0x4edd7e-0x4edd89) that in
   * turn needs its own runtime constructor (FUN_004edce0 called from
   * WinMain-level startup, 0x4100ab/0x4100b0) to populate correctly, and the
   * whole thing chains into more vtable calls (SetCooperativeLevel-style at
   * +0x2c, SetDataFormat-style at +0x34, SetProperty-style at +0x18) whose
   * struct layouts aren't recovered yet either.
   *
   * None of this blocks reaching the logo/menu states (they're 2-D sprite
   * blits; DirectInput device binding only matters once real keyboard/mouse
   * input needs processing), so skip it for bring-up. Revisit once the
   * 0xe52810 struct's real field layout is understood. */
  return 0;
}

