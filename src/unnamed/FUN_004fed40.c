/* FUN_004fed40 - 0x004fed40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


int FUN_004fed40(int *param_1,undefined1 *param_2,undefined4 regEax)

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

