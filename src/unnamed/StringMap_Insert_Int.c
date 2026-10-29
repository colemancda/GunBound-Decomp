/* StringMap_Insert_Int - 0x00409d10 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::NewNode for the 0x10-node string map
 * whose value is a POD int - the ChooseEvent.txt table at DAT_00e9bea8.
 * The role comes from its only caller, ParseChooseEventLine (0x409cb0):
 * on a StringMap_Find_10 miss it lazily runs HashMap_InitHashTable, calls
 * this (0x409cfa) and stores the line's _atol code through the returned
 * node at +4 (`mov [eax+4],edi` at 0x409cff), which is the value
 * FindChooseEventCode (0x409c70) reads back from node+4.  The body is
 * NewNode member for member, at the same stride and with the same
 * free-list refill as StringMap_Insert_CString (0x426960): pop the free
 * head at map+0x2c (refilling from `_malloc(map[9] * 0x10 + 4)` blocks
 * chained at +0x28), construct the node under an SEH state of 1
 * (0x409d8f-0x409d9e, NewNode's _ATLTRY), bump the count at +4, link into
 * bin[ECX], and rehash through FUN_00500e30 (PickSize) / StringMap_Rehash_10
 * (0x409e20) past the +0x18 threshold with the +0x20 lock clear.
 *
 * WHY _Int AND NOT _10.  The stride cannot separate it from
 * StringMap_Insert_CString; the node constructor can.  That one calls
 * StringMap_ConstructNode_CString, which also builds a nil CStringA
 * value at +4; this one inlines the construction, building only the key
 * (ConstructStringFromText, 0x409d96) and the hash (0x409da5), and
 * leaves +4 for the caller's int.  Same value-type rule as the _CString
 * members; StringMap_FreeNode_CString's header gives the destructor-side
 * version of the split.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes below that predate the name call this function FUN_00409d10.)
 *
 * (FUN_00426780 below is now StringMap_Find_10.)
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): __thiscall with 4 real params
 * (ECX=`this` + ret 0xc = 3 stack dwords, disasm 0x409d10-0x409deb); the
 * declared shape was already correct. The sole caller
 * (fileformat/ParseChooseEventLine.c) dropped `this` entirely (wrote only
 * the 3 stack args). See that file's own header for the call-site
 * reconstruction: `this` = the hash-bucket index FUN_00426780 wrote into
 * its caller's `local_8` out-param.
 *
 * DROPPED-KEY FIX (2026-10-29): the ConstructStringFromText(iVar3) call
 * dropped the key, which the original passes in ECX (`mov ecx,[ebp+0xc]`
 * at 0x409d8b = param_3, with the node pushed at 0x409d8e).  So every
 * ChooseEvent.txt node was built with no key string and
 * StringMap_Find_10 could never match one.  It now passes (key, node).
 * The same bug in the CString-valued twin is fixed in
 * StringMap_Insert_CString's node constructor
 * StringMap_ConstructNode_CString.  The SEH registration through the
 * uninitialised `unaff_FS_OFFSET`, which wrote
 * through a garbage pointer on every call, is stripped too, as in
 * ConstructStringFromText.c.
 */
#include "ghidra_types.h"


int __thiscall StringMap_Insert_Int(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;

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
  ConstructStringFromText((char *)param_3,(int *)iVar3);
  *(undefined4 *)(iVar3 + 0xc) = param_4;
  param_2[1] = param_2[1] + 1;
  *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(*param_2 + param_1 * 4);
  *(int *)(*param_2 + param_1 * 4) = iVar3;
  if (((uint)param_2[6] < (uint)param_2[1]) && (param_2[8] == 0)) {
    uVar2 = FUN_00500e30();
    StringMap_Rehash_10(param_2,uVar2);
  }
  return iVar3;
}

