/* StringMap_SetAt_1c - 0x004fe490 in the original binary.
 *
 * ATL7 CAtlMap::SetAt for the 0x1c-node string-map instantiation whose
 * Find/Insert halves are already named StringMap_Find_1c (0x4ff130) /
 * StringMap_Insert_1c (0x500580): look the key up, and either
 * overwrite the found node's value or (init the hash table if still
 * empty, then) insert a fresh node and set its value.  Same upsert
 * shape, member for member, as the already-named StringMap_SetAt_28
 * (0x503e30) of the 0x28-node family.  The value of this instantiation
 * is the single byte at node+0x12, right after the 16-char key at +0
 * and its length byte at +0x11 - the layout StringMap_Insert_1c writes.
 *
 * The one binary call site, 0x4fdc1c, sits in an UNPORTED gap function
 * at 0x4fdba0 (between the PROGRESS.csv rows for 0x4fdb40 and 0x4fdc30):
 * a __thiscall flag setter over the engine's string map at this+0x1af0
 * which copies a 16-char id into a local and calls here with value 1,
 * or calls 0x4fe500 on its other branch.  Itself dead - 0x4fdba0 has no
 * callers - so there is no C call site to update.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void StringMap_SetAt_1c(int param_1,undefined4 regEdi,int *regEsi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = StringMap_Find_1c((char *)regEdi,(uint *)&local_c,(undefined4 *)local_4,regEsi,
                       (uint *)&local_8);
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 0x12) = param_1;
    return;
  }
  if (*regEsi == 0) {
    cVar1 = HashMap_InitHashTable(regEsi,regEsi[2],1);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar2 = StringMap_Insert_1c(local_8,local_c,(undefined4 *)regEdi,regEsi);
  *(undefined1 *)(iVar2 + 0x12) = param_1;
  return;
}

