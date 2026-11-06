/* InitCrashEffect - 0x00464200 in the original binary.
 *
 * Constructor of the effect object SpawnCrashEffect (0x00436ac0) builds,
 * class key 0x2e644.  Evidence is from the caller: the spawner calls it at
 * 0x00436ae4 straight after operator_new(0x50), with the new object still
 * in EAX, and takes the returned EAX as the object (mov edi,eax) to fill
 * in +0x38/+0x3c/+0x18/+0x44 and register.  The constructor stamps class
 * key 0x2e644 at +4 and installs vtable 0x00555ccc; both are the values the
 * spawner's note and Effects.h tie to this effect.  Same constructor shape
 * as InitRiderEffect (0x004a2780), the sole-caller constructor beside it.
 *
 * The object arrives in EAX (Ghidra's in_EAX); it is promoted to the
 * regEax parameter and returned, and the one call site now passes the
 * allocation and keeps the result instead of dropping it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashEffect(undefined4 *regEax)

{
  regEax[1] = 0x2e644;
  regEax[2] = 0xffffffff;
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
  *regEax = &PTR_FUN_00555ccc;
  regEax[0x10] = 0;
  regEax[0x12] = 0x40;
  regEax[0x13] = 0xc4;
  return regEax;
}

