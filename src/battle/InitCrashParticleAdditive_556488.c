/* InitCrashParticleAdditive_556488 - 0x0049e420 in the original binary.
 *
 * Constructor of a CrashTexture additive particle class, key 0x2e644,
 * vtable 0x00556488. NAME: the usual class-key suffix is not usable
 * here, because InitCrashEffect stamps the same key 0x2e644 but installs
 * vtable 0x00555ccc and initialises +0x48/+0x4c to 0x40/0xc4 against
 * this one's 0x20/0x100; the two are different classes in the same blend
 * group, so the vtable address is the suffix. Evidence from outside the
 * body: its sole caller, SpawnCrashParticleAdditive_556488 (0x00436b6c), calls it right after
 * operator_new(0x50) with the allocation in EAX and takes the returned
 * EAX as the object (mov edi,eax) to place at +0x38/+0x3c and register;
 * FUN_00450c20 lists key 0x2e644 in the blend-mode-2 (SRCALPHA / ONE)
 * group. LIKELY: the role beyond class, texture and blend mode is not
 * established.  The object arrives in EAX (Ghidra's in_EAX), promoted to
 * regEax and returned; the sole call site now passes the allocation and
 * assigns the return.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashParticleAdditive_556488(undefined4 *regEax)

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
  *regEax = &PTR_FUN_00556488;
  regEax[0x10] = 0;
  regEax[0x12] = 0x20;
  regEax[0x13] = 0x100;
  return regEax;
}

