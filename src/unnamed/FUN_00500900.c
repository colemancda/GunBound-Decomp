/* FUN_00500900 - 0x00500900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ECX and EDI PROMOTED (2026-08-25) on top of the already-recovered EBX: the
 * map and the key, both falling through from this wrapper's own caller.  The
 * find's three out-slots share the 12-byte local_c.
 */
#include "ghidra_types.h"


undefined4 FUN_00500900(undefined4 *regEbx,int *regEcx,uint regEdi)

{
  int iVar1;
  undefined1 local_c [12];
  
  iVar1 = IntMap_Find_14(regEcx,(undefined4 *)local_c,(uint *)(local_c + 4),(uint *)(local_c + 8),
               regEdi);
  if (iVar1 == 0) {
    return 0;
  }
  *regEbx = *(undefined4 *)(iVar1 + 4);
  regEbx[1] = *(undefined4 *)(iVar1 + 8);
  return 1;
}

