/* IntMap_SetAt_1768 - 0x004fed40 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::SetAt(key, value) for the
 * 0x1768-node int-keyed maps - the same routine as IntMap_SetAt_14
 * (0x500940), instruction for instruction up to the value store: GetNode
 * is IntMap_Find_1768 (0x4fed5b), the table init is HashMap_InitHashTable
 * with the same E_OUTOFMEMORY throw, CreateNode is IntMap_Insert_1768
 * (0x4fed93), and the value assignment is the 0x1758-byte record copy
 * IntMap_CopyValue_1768 (0x4feda1 / 0x4fedb9) into node+4.  Returns the
 * node (`mov eax,esi`), i.e. SetAt's POSITION.
 *
 * The one binary caller, FUN_004fe110 at 0x4fe33c, passes the map at
 * peer-record+0x50 (`lea ecx,[ebx+0x50]`, pushed), the key from the
 * record's +0x18 field in EAX, and a value record it has just built
 * (FUN_004fe590 into the 0x1768-byte stack buffer).  That is the map
 * IntMap_RemoveKey_1768 and IntMap_LookupPair_1768 work on.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * SHORT DEFINITION + EAX (2026-08-25).  `ret 8` is two stack parameters and
 * Ghidra declared one.  The second is read on both exit paths -- 0x4fed98
 * `mov edx,[esp+0x20]` (esp = E-24) and 0x4fedb2 `mov edx,[esp+0x1c]`
 * (esp = E-20), both = E+8 -- and handed to IntMap_CopyValue_1768 as its EDX, the
 * source of a 0x1758-byte struct copy.  Ghidra dropped it because it
 * decompiles IntMap_CopyValue_1768 argless, which makes those two loads dead.  The
 * caller was already passing it (src/unnamed/FUN_004fe110.c:156).
 * param_2 is therefore declared but not yet USED here: forwarding it to the
 * two IntMap_CopyValue_1768 calls needs that callee's own registers, a separate item.
 *
 * EAX is the record key, `local_2ecc[6]` at the one call site.
 *
 * THE FIND'S OUT-SLOTS (2026-08-25).  local_8 is the bucket index -- the find
 * writes it through ESI (`lea esi,[esp+0x10]` at 0x4fed55) -- and it is what
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


int IntMap_SetAt_1768(int *param_1,undefined1 *param_2,undefined4 regEax)

{
  char cVar1;
  int iVar2;
  uint local_key;
  uint local_8;
  undefined1 local_4 [4];
  
  iVar2 = IntMap_Find_1768(param_1,(undefined4 *)local_4,&local_key,&local_8,regEax);
  if (iVar2 != 0) {
    IntMap_CopyValue_1768(0,(undefined4 *)param_2,(undefined4 *)(iVar2 + 4));
    return iVar2;
  }
  if (*param_1 == 0) {
    cVar1 = HashMap_InitHashTable(param_1,param_1[2],1);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar2 = IntMap_Insert_1768(regEax,regEax,local_8,param_1);
  IntMap_CopyValue_1768(0,(undefined4 *)param_2,(undefined4 *)(iVar2 + 4));
  return iVar2;
}

