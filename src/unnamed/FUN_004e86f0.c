/* FUN_004e86f0 - 0x004e86f0 in the original binary.
 *
 * A std::set<ushort>::insert over the turn-event set: param_2 is the set,
 * param_3 points at the 16-bit key, and param_1 is the out-slot - it writes
 * the node to *param_1 and the inserted flag to param_1[1], the usual
 * pair<iterator,bool> return.
 *
 * DROPPED-REGISTER-ARG FIX (2026-08-19).  The set arrived in EAX and the key
 * pointer in EBX, which Ghidra modelled as `in_EAX` / `unaff_EBX` - so every
 * insert ran against whatever those registers held.  Both are now real
 * parameters, passed explicitly at all 22 call sites.
 *
 * The call sites all share one shape (e.g. orig 0x423bcb-0x423be1):
 *     lea <r>,[esp+N] / push <r>      the out-slot
 *     lea ebx,[esp+N]                 &key, 4 bytes below the out-slot
 *     mov eax,0xe9af10                the set - the SAME one everywhere
 *     mov dword [esp+N],<code>        the key value
 * PostTurnEvent is the only site that computes the set rather than using the
 * literal, and its `param_1 + 0x45230` resolves to that same 0xe9af10.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond this - not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 * FUN_004e86f0(undefined4 *param_1,int param_2,ushort *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  bool bVar3;
  
  puVar1 = param_1;
  param_1 = *(undefined4 **)(param_2 + 4);
  bVar3 = true;
  if (*(char *)((int)param_1[1] + 0xf) == '\0') {
    puVar2 = (undefined4 *)param_1[1];
    do {
      param_1 = puVar2;
      bVar3 = *param_3 < *(ushort *)(param_1 + 3);
      if (bVar3) {
        puVar2 = (undefined4 *)*param_1;
      }
      else {
        puVar2 = (undefined4 *)param_1[2];
      }
    } while (*(char *)((int)puVar2 + 0xf) == '\0');
  }
  if (bVar3) {
    if (param_1 == (undefined4 *)**(int **)(param_2 + 4)) {
      puVar2 = (undefined4 *)FUN_004e8b10(&param_1,1,param_3);
      *puVar1 = *puVar2;
      *(undefined1 *)(puVar1 + 1) = 1;
      return puVar1;
    }
    FUN_004e8eb0();
  }
  if (*(ushort *)(param_1 + 3) < *param_3) {
    puVar2 = (undefined4 *)FUN_004e8b10(&param_1,bVar3,param_3);
    *puVar1 = *puVar2;
    *(undefined1 *)(puVar1 + 1) = 1;
    return puVar1;
  }
  *puVar1 = param_1;
  *(undefined1 *)(puVar1 + 1) = 0;
  return puVar1;
}

