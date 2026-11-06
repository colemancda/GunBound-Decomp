/* InitCrashParticleAlphaBlend - 0x004aa4d0 in the original binary.
 *
 * Constructor of the ordinary-alpha CrashTexture particle that
 * SpawnCrashParticleAlphaBlend (0x00436bd0) spawns, class key 0x2e631.
 * Evidence is from the caller: the spawner calls it at 0x00436c18 right
 * after operator_new(0x50) with the new object still in EAX and uses the
 * returned EAX as the object (mov edi,eax) to position and register.  It
 * stamps class key 0x2e631 at +4 and installs vtable 0x00556544; the
 * spawner's note ties 0x2e631 to the SRCALPHA / INVSRCALPHA group of the
 * class-id switch in FUN_00450c20.  Sole caller.
 *
 * The object arrives in EAX (Ghidra's in_EAX), promoted to the regEax
 * parameter and returned; the one call site now passes the allocation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashParticleAlphaBlend(undefined4 *regEax)

{
  regEax[1] = 0x2e631;
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
  *regEax = &PTR_FUN_00556544;
  regEax[0x10] = 0;
  regEax[0x12] = 0x10;
  regEax[0x13] = 0x80;
  return regEax;
}

