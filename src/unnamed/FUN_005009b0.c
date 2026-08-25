/* FUN_005009b0 - 0x005009b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): a thin wrapper over the map find that
 * keeps all three of the find's out-slots in one 12-byte scratch local and
 * throws the result away.  The map arrives in EBX (`mov ecx,ebx` at 0x5009c1);
 * the key falls through from its caller.
 */
#include "ghidra_types.h"


undefined4 FUN_005009b0(int *regEbx,uint regEdi)

{
  int iVar1;
  int local_c [3];
  
  local_c[0] = 0;
  iVar1 = FUN_005013c0(regEbx,(undefined4 *)local_c,(uint *)(local_c + 1),(uint *)(local_c + 2),
               regEdi);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c[0] == 0) {
    *(undefined4 *)(*regEbx + (*(uint *)(iVar1 + 0x10) % (uint)regEbx[2]) * 4) =
         *(undefined4 *)(iVar1 + 0xc);
    FUN_00501360();
    return 1;
  }
  *(undefined4 *)(local_c[0] + 0xc) = *(undefined4 *)(iVar1 + 0xc);
  FUN_00501360();
  return 1;
}

