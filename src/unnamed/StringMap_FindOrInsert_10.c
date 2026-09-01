/* StringMap_FindOrInsert_10 - 0x004265c0 in the original binary.
 *
 * The find-or-insert member (the map template's operator[] shape) of
 * the 0x10-node string-map instantiation: find the key, and if absent (init
 * the hash table if still empty, then) insert a fresh node; either way
 * return node+4, the value slot.  The stride comes from this
 * instantiation's own insert half, FUN_00426960, which carves nodes out
 * of `_malloc(map[9] * 0x10 + 4)` chunks - node layout +0 key CString
 * (built by FUN_00426a60), +4 value, +8 bucket chain, +0xc hash.  Same
 * member-for-member shape as the named StringMap_SetAt_1c/_28 upserts
 * of the 0x1c/0x28-node families minus their trailing value store, and
 * it shares the literal HashMap_InitHashTable (0x500c00, MFC
 * CMap::InitHashTable) with them.  FindOrInsert rather than SetAt
 * because the value is not written here - the callers do that through
 * the returned slot.  Both callers are the nickname<->user-id cache
 * twins FindUserIdByNickname (0x426030) / FindNicknameByUserId
 * (0x426090) over the maps at ctx+0x6aa41c/+0x6aa44c; the third member
 * of this instantiation, FUN_00426620, is the SetAt-shaped upsert the
 * response handlers use.
 *
 * RECOVERED (2026-09-01): the prerequisite caller promotions landed in
 * the same batch as this note - the regEax parameter below is live and
 * every site passes the verified value; see the commit for the chain.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int StringMap_FindOrInsert_10(char *regEax,int *regEsi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_8,&local_c,local_4,regEsi,(uchar *)regEax);
  if (iVar2 == 0) {
    if (*regEsi == 0) {
      cVar1 = HashMap_InitHashTable(regEsi,regEsi[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00426960(*(int *)local_8,regEsi,(undefined4)regEax,local_c);
  }
  return iVar2 + 4;
}

