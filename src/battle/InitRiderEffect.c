/* InitRiderEffect - 0x004a2780 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004a2780).  Constructor for the RIDER effect:
 * stamps class id 100007 at object +0x4 and installs vtable 0x5564bc, which
 * src/cxx/Effects.h already documents as CRiderEffect (0x48 bytes).  Its only
 * caller is SpawnRiderEffect.  Note it takes its object in EAX (Ghidra's
 * `in_EAX`), not a normal parameter.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 __fastcall InitRiderEffect(undefined4 param_1)

{
  undefined4 *in_EAX;
  
  in_EAX[2] = param_1;
  in_EAX[1] = 0x186a7;
  in_EAX[3] = 0;
  in_EAX[4] = 0;
  *(undefined1 *)(in_EAX + 5) = 0;
  *(undefined1 *)((int)in_EAX + 0x15) = 0;
  in_EAX[6] = 0xffffffff;
  in_EAX[7] = 0;
  *(undefined1 *)(in_EAX + 8) = 0;
  in_EAX[10] = 0;
  in_EAX[0xb] = 0;
  in_EAX[9] = 0xffffffff;
  *in_EAX = &PTR_FUN_005564bc;
  in_EAX[0xf] = 0;
  in_EAX[0xe] = 0;
  *(undefined1 *)(in_EAX + 0x10) = 0;
  in_EAX[0x11] = 1000;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

