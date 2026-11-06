/* InitCrashParticleAdditive_2e634 - 0x00481e30 in the original binary.
 *
 * Constructor of the CrashTexture additive particle that
 * SpawnCrashParticleAdditive_2e634 (0x00436ec0) spawns, class key 0x2e634.
 * Evidence is from the caller: the spawner calls it at 0x00436f23 right
 * after operator_new(0x50) with the new object still in EAX and uses the
 * returned EAX as the object (mov edi,eax) to position and register.  It
 * stamps class key 0x2e634 at +4 and installs vtable 0x00556180; the
 * spawner's note lists 0x2e634 with 0x2e633 and 0x2e644 in the additive
 * group of the class-id switch in FUN_00450c20.  Sole caller.  The suffix
 * mirrors the spawner's, which separates it from InitCrashParticleAdditive
 * by class key.
 *
 * The object arrives in EAX (Ghidra's in_EAX), promoted to the regEax
 * parameter and returned; the one call site now passes the allocation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashParticleAdditive_2e634(undefined4 *regEax)

{
  regEax[1] = 0x2e634;
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
  *regEax = &PTR_FUN_00556180;
  regEax[0x10] = 0;
  regEax[0x12] = 0x10;
  regEax[0x13] = 0x80;
  return regEax;
}

