/* InitFlameEffect - 0x00471af0 in the original binary.
 *
 * Constructor of CFlameEffect (0x54 bytes, vtable 0x00555ef0), as
 * src/cxx/Effects.h documents.  Sole caller is SpawnFlameEffect
 * (0x004372f0): at 0x00437323 it calls this straight after
 * operator_new(0x54) with the new object still in EAX, ECX holding the
 * signed remainder of its stack argument param_2 by 16 (the
 * and 0x8000000f / dec / or / inc idiom), and keeps the returned EAX as
 * the object (mov edi,eax).  The constructor stores ECX at +8, stamps
 * class key 190000 (0x2e630) at +4, installs vtable 0x00555ef0 and sets
 * the +0x48/+0x4c fields to 0x10 and 0x80.  Same constructor shape as
 * InitSuperFlameEffect and InitRiderEffect.
 *
 * Registers: ECX is param_1, the object arrives in EAX (Ghidra's
 * in_EAX) and is promoted to the trailing regEax parameter, returned;
 * EDX is not an input (param_2 is a placeholder keeping the __fastcall
 * slots in order).  The call site was dropping both and leaving the
 * object unset; it now passes (param_2 % 16, 0, allocation).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall InitFlameEffect(undefined4 param_1,undefined4 param_2,undefined4 *regEax)

{
  regEax[2] = param_1;
  regEax[1] = 190000;
  regEax[3] = 0;
  regEax[4] = 0;
  *(undefined1 *)(regEax + 5) = 0;
  *(undefined1 *)((int)regEax + 0x15) = 0;
  regEax[6] = 0xffffffff;
  regEax[7] = 0;
  *(undefined1 *)(regEax + 8) = 0;
  regEax[10] = 0;
  regEax[0xb] = 0;
  regEax[9] = 0xffffffff;
  *regEax = &PTR_FUN_00555ef0;
  regEax[0x10] = 0;
  regEax[0x12] = 0x10;
  regEax[0x13] = 0x80;
  regEax[0x11] = 0;
  return regEax;
}

