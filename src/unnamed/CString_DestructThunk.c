/* CString_DestructThunk - 0x00405300 in the original binary.
 *
 * Named above (a tail-jump thunk in the chain 0x405300 -> 0x405310 -> CString_Destruct 0x405320), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 *
 * Evidence (CORRECTED 2026-11): the two 5-byte jmp thunks are CHAINED, not
 * parallel. Disasm: 0x405300 is `e9 0b 00 00 00` = jmp 0x405310 (0x405305
 * + 0xb), and 0x405310 is `e9 0b 00 00 00` = jmp 0x405320
 * (CString_Destruct). All four call sites of the entry thunk
 * (RBTree_RemoveNode, HashMap_FreeNode_2c, RBTree_EraseSubtree,
 * HashTable_OnNodeRemoved; calls at 0x404981, 0x405295, 0x4054eb, 0x409f65)
 * target 0x405300. 0x405310 has no CALL because its only referrer is the
 * jmp at 0x405300 (the xref the analysis shows is that jump, not a missing
 * code caller). A byte scan of the image finds no other reference to
 * 0x405310.
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

