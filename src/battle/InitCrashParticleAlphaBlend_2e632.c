/* InitCrashParticleAlphaBlend_2e632 - 0x004892c0 in the original binary.
 *
 * Constructor of a third CrashTexture ordinary-alpha particle class, key
 * 0x2e632, vtable 0x00556250, next to InitCrashParticleAlphaBlend (key
 * 0x2e631). Evidence from outside the body: its sole caller,
 * FUN_00436cd0 (0x00436d1a), calls it right after operator_new(0x50)
 * with the allocation still in EAX and takes the returned EAX as the
 * object (mov edi,eax) to position at +0x38/+0x3c and register.
 * FUN_00450c20, the CrashTexture draw pass, lists 0x2e632 with 0x2e631
 * and 0x2e635 in the blend-mode-1 (SRCALPHA / INVSRCALPHA) group, so it
 * is an alpha particle, not an additive one. A byte scan of the image
 * finds no other site stamping 0x2e632, so the key is unique and is used
 * as the suffix. LIKELY: the role beyond class, texture and blend mode
 * is not established.  The object arrives in EAX (Ghidra's in_EAX),
 * promoted to regEax and returned; the sole call site now passes the
 * allocation and assigns the return.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * InitCrashParticleAlphaBlend_2e632(undefined4 *regEax)

{
  regEax[1] = 0x2e632;
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
  *regEax = &PTR_FUN_00556250;
  regEax[0x10] = 0;
  regEax[0x12] = 0x10;
  regEax[0x13] = 0x80;
  return regEax;
}

