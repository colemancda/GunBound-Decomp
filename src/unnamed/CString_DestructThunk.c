/* CString_DestructThunk - 0x00405300 in the original binary.
 *
 * Named above (a tail-jump thunk to CString_Destruct, 0x405320), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 *
 * Evidence: the binary has two 5-byte jmp thunks to 0x405320 (0x405300
 * and 0x405310). All four call sites of the thunk (RBTree_RemoveNode,
 * HashMap_FreeNode_2c, RBTree_EraseSubtree, HashTable_OnNodeRemoved) use
 * 0x405300; 0x405310 has no code caller.
 */
#include "ghidra_types.h"


void __fastcall CString_DestructThunk(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(*param_1 + -0x10);
  piVar1 = (int *)(*param_1 + -4);
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3);
  }
  return;
}

