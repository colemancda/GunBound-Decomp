/* IntMap_SetAt_14 - 0x00500940 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::SetAt(key, value) for the 0x14-node
 * int-keyed maps, member for member the upsert already named
 * StringMap_SetAt_1c / _28: GetNode (IntMap_Find_14 at 0x50095b; map
 * from the stack in ECX = EBP, key in EAX = EDI); on a miss, if m_ppBins
 * is still NULL run InitHashTable(m_nBins) (HashMap_InitHashTable,
 * 0x500971) and AtlThrow(E_OUTOFMEMORY) (0x8007000e) if that fails, then
 * CreateNode (IntMap_Insert_14, 0x500991); either way store the 8-byte
 * value at node+4/+8.  The original returns the node in EAX (POSITION);
 * the port returns void, which its one caller does not notice.
 *
 * The callers fix the value type.  The only binary site, FUN_004ff770 at
 * 0x4ffb2c, has just called GetSystemTimeAsFileTime and passes that
 * FILETIME (`lea ecx,[esp+0x48]`) as the value, the map at
 * peer-record+0x20 (ESI) and the key in EAX; it then reads the map's
 * m_nElements (record+0x24) and, past 0x100 entries, enumerates the map
 * and IntMap_RemoveKey_14s every key older than 60000 ms.  So this map
 * is key -> last-seen time, and SetAt refreshes it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * THE FIND'S OUT-SLOTS (2026-08-25).  local_8 is the bucket index -- the find
 * writes it through ESI (`lea esi,[esp+0x10]` at 0x500955) -- and it is what
 * the insert half then takes in EBX.  Ghidra dropped the parameter and the
 * local together, which is why the insert's argument had nowhere to come from.
 *
 * local_key is the slot the find stashes the key in through EAX.  In the
 * original that is `lea eax,[esp+0x1c]` = the incoming param_1 SLOT, reused
 * as scratch because param_1 has been cached in EBP by then.  Spelling that
 * as &param_1 in C would corrupt param_1, which the original keeps live in
 * the register, so it gets a local of its own -- and the value written there
 * is the key, which is why the insert's SECOND argument is regEax and not
 * param_1 as Ghidra had it.
 */
#include "ghidra_types.h"


void IntMap_SetAt_14(int *param_1,undefined4 *param_2,undefined4 regEax)

{
  char cVar1;
  int iVar2;
  uint local_key;
  uint local_8;
  undefined1 local_4 [4];
  
  iVar2 = IntMap_Find_14(param_1,(undefined4 *)local_4,&local_key,&local_8,regEax);
  if (iVar2 == 0) {
    if (*param_1 == 0) {
      cVar1 = HashMap_InitHashTable(param_1,param_1[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = IntMap_Insert_14(regEax,regEax,local_8,param_1);
  }
  *(undefined4 *)(iVar2 + 4) = *param_2;
  *(undefined4 *)(iVar2 + 8) = param_2[1];
  return;
}

