/* StringMap_Insert_CString - 0x00426960 in the original binary.
 *
 * ATL7 CAtlMap::NewNode for the CStringA->CStringA instantiation with
 * 0x10-byte nodes whose find is StringMap_Find_10 (0x426780): pop a node
 * off the free list at map+0x2c (refilling it from a fresh
 * `_malloc(map[9] * 0x10 + 4)` block chained at +0x28 when empty),
 * construct it through FUN_00426a60, link it at the head of bin[ECX],
 * bump the count at +4, and rehash via FUN_00500e30 (PickSize) /
 * FUN_00409e20 when it passes +0x18 with the lock at +0x20 clear.
 * Stack: map, key, hash (ECX = the bucket index the find wrote).
 *
 * WHY _CString AND NOT _10.  The image has a second insert with the
 * byte-identical 0x10 stride and free-list code: FUN_00409d10, the
 * insert ParseChooseEventLine (0x409cb0) runs for the ChooseEvent.txt
 * table.  What separates them is the node constructor.  Here
 * FUN_00426a60 builds the key CStringA at node+0 (`call 0x405510`) AND
 * a second, nil CStringA at node+4 (0x426a88-0x426a9c: GetNilString
 * + 0x10 stored to [esi+4]); 0x409d10 runs only the key constructor and
 * stores the hash, leaving +4 a 4-byte POD that its caller writes.  So
 * the suffix names the VALUE type, matching StringMap_FreeNode_CString
 * and StringMap_RemoveAll_CString, which serve these same maps (see the
 * former's header for the destructor-side version of this argument).
 *
 * Callers: StringMap_SetAt_CString (0x426687), StringMap_FindOrInsert_10
 * (0x42660a) and FUN_00404410 (0x404552), each after a
 * StringMap_Find_10 miss.
 *
 * DROPPED-KEY FIX (2026-10-29): the FUN_00426a60 call used to pass only
 * (node, hash) and dropped the key, which the original passes in ECX
 * (`mov ecx,[ebp+0xc]` at 0x4269df = param_3), so every ported node was
 * built with no key string.  It now passes (key, node, hash), matching
 * that callee's recovered signature.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int __thiscall StringMap_Insert_CString(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a75) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2[0xb] == 0) {
    piVar1 = _malloc(param_2[9] * 0x10 + 4);
    if (piVar1 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar1 = param_2[10];
    param_2[10] = (int)piVar1;
    iVar3 = param_2[9];
    piVar1 = piVar1 + iVar3 * 4 + -3;
    if (-1 < iVar3 + -1) {
      do {
        piVar1[2] = param_2[0xb];
        param_2[0xb] = (int)piVar1;
        piVar1 = piVar1 + -4;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  iVar3 = param_2[0xb];
  param_2[0xb] = *(int *)(iVar3 + 8);
  local_8 = 1;
  FUN_00426a60((char *)param_3,(int *)iVar3,param_4);
  local_8 = 0xffffffff;
  param_2[1] = param_2[1] + 1;
  *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(*param_2 + param_1 * 4);
  *(int *)(*param_2 + param_1 * 4) = iVar3;
  if (((uint)param_2[6] < (uint)param_2[1]) && (param_2[8] == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(param_2,uVar2);
  }
  return iVar3;
}

