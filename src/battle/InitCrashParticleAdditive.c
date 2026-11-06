/* InitCrashParticleAdditive - 0x0048dcc0 in the original binary.
 *
 * Constructor of the additive CrashTexture particle that
 * SpawnCrashParticleAdditive (0x00436dc0) spawns, class key 0x2e633.
 * Evidence is from the caller: the spawner calls it at 0x00436e08 right
 * after operator_new(0x50) with the new object still in EAX and uses the
 * returned EAX as the object (mov edi,eax) to position and register.  It
 * stamps class key 0x2e633 at +4 and installs vtable 0x00556308; the
 * spawner's note ties 0x2e633 to the additive group (SRCALPHA / ONE) of
 * the class-id switch in FUN_00450c20.  Sole caller.  Note that
 * SpawnCrashParticleBurst builds another class under the same key 0x2e633
 * with a different vtable (0x555ce0), so the key alone does not identify
 * this constructor; the vtable does.
 *
 * The object arrives in EAX (Ghidra's in_EAX), promoted to the regEax
 * parameter and returned; the one call site now passes the allocation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashParticleAdditive(undefined4 *regEax)

{
  regEax[1] = 0x2e633;
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
  *regEax = &PTR_FUN_00556308;
  regEax[0x10] = 0;
  regEax[0x12] = 0x10;
  regEax[0x13] = 0x80;
  return regEax;
}

