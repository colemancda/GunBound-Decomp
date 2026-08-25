/* FUN_004fed40 - 0x004fed40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SHORT DEFINITION + EAX (2026-08-25).  `ret 8` is two stack parameters and
 * Ghidra declared one.  The second is read on both exit paths -- 0x4fed98
 * `mov edx,[esp+0x20]` (esp = E-24) and 0x4fedb2 `mov edx,[esp+0x1c]`
 * (esp = E-20), both = E+8 -- and handed to FUN_004ff240 as its EDX, the
 * source of a 0x1758-byte struct copy.  Ghidra dropped it because it
 * decompiles FUN_004ff240 argless, which makes those two loads dead.  The
 * caller was already passing it (src/unnamed/FUN_004fe110.c:156).
 * param_2 is therefore declared but not yet USED here: forwarding it to the
 * two FUN_004ff240 calls needs that callee's own registers, a separate item.
 *
 * EAX is the record key, `local_2ecc[6]` at the one call site.
 *
 * STILL OPEN in this body: FUN_00500840's second argument.  The binary pushes
 * [esp+0x18] = E+4 -- the incoming param_1 SLOT, which FUN_005002a0 has by
 * then overwritten with the key -- so the value is regEax, not param_1.  It is
 * left as Ghidra wrote it until FUN_005002a0's own out-pointers are recovered.
 */
#include "ghidra_types.h"


int FUN_004fed40(int *param_1,undefined1 *param_2,undefined4 regEax)

{
  char cVar1;
  int iVar2;
  undefined1 local_4 [4];
  
  iVar2 = FUN_005002a0(local_4);
  if (iVar2 != 0) {
    FUN_004ff240();
    return iVar2;
  }
  if (*param_1 == 0) {
    cVar1 = FUN_00500c00(param_1,param_1[2],1);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar2 = FUN_00500840(regEax,param_1);
  FUN_004ff240();
  return iVar2;
}

