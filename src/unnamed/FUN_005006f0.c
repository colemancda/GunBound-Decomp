/* FUN_005006f0 - 0x005006f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): a thin wrapper over the map find that
 * keeps all three of the find's out-slots in one 12-byte scratch local and
 * throws the result away.  Neither the map (ECX) nor the key (EDI) is set here:
 * both fall straight through from its own caller.
 */
#include "ghidra_types.h"


undefined4 FUN_005006f0(int *regEcx,uint regEdi)

{
  undefined1 local_c [12];
  
  FUN_005002a0(regEcx,(undefined4 *)local_c,(uint *)(local_c + 4),(uint *)(local_c + 8),
               regEdi);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

