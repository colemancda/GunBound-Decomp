/* HashMap_Rehash_2c - 0x00405150 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::Rehash(nBins) for the 0x2c-node
 * map - the same member as StringMap_Rehash_10 (see that file for the
 * atlcoll.h statement-by-statement match), instruction for instruction,
 * with only the node offsets moved: the relink reads m_pNext at
 * node+0x24 (0x405218) and m_nHash at node+0x28 (0x405210), the
 * stride-8/stride-4 CNode tail of a 0x2c-byte node.  Map in [ebp+8],
 * nBins in [ebp+0xc], `ret 8`.
 *
 * The instantiation is fixed by its one binary caller,
 * HashMap_FreeNode_2c (0x4052c3), which pushes (PickSize result, map)
 * from FreeNode's rehash-threshold arm and links nodes through the same
 * +0x24.  The HashMap_ prefix is that family's, for the reason
 * HashMap_RemoveAll_2c records: nothing that survives touches the key,
 * so a key-claiming prefix would be invented.
 *
 * Promoted from a K&R prototype to (int *map, uint nBins) like
 * StringMap_Rehash_10; the one C site already passed those two values,
 * and its int-typed map register is cast.  The port carried
 * Ghidra's unaff_FS_OFFSET SEH-frame artifact (stripped below).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * SEH-PROLOGUE ARTIFACT STRIPPED (2026-10-29): the body registered an SEH
 * frame through Ghidra's `unaff_FS_OFFSET`, an uninitialised local pointer,
 * so every call read and wrote through garbage.  The original's
 * `push 0x537890` / `mov eax,fs:[0]` / `mov fs:[0],esp` (0x405155-0x405161) is
 * the compiler-generated EH registration, not program logic; stripped per
 * the ConstructStringFromText.c / StringMap_Insert_Int.c idiom, including
 * the unregister writes on each return path.
 */
#include "ghidra_types.h"


void HashMap_Rehash_2c(int *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537890) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 == 0) {
    param_2 = HashMap_PickSize();
  }
  if (param_2 != param_1[2]) {
    if (*param_1 == 0) {
      HashMap_InitHashTable(param_1,param_2,0);
      return;
    }
    local_8 = 0;
    puVar2 = operator_new(param_2 * 4);
    local_8 = 0xffffffff;
    uVar6 = param_2;
    puVar5 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    uVar6 = 0;
    if (param_1[2] != 0) {
      do {
        iVar3 = *(int *)(*param_1 + uVar6 * 4);
        while (iVar3 != 0) {
          uVar4 = *(uint *)(iVar3 + 0x28) % param_2;
          iVar1 = *(int *)(iVar3 + 0x24);
          *(undefined4 *)(iVar3 + 0x24) = puVar2[uVar4];
          puVar2[uVar4] = iVar3;
          iVar3 = iVar1;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < (uint)param_1[2]);
    }
    _free((void *)*param_1);
    *param_1 = (int)puVar2;
    param_1[2] = param_2;
    iVar3 = FloatToInt64();
    param_1[6] = iVar3;
    uVar6 = FloatToInt64();
    param_1[7] = uVar6;
    if (uVar6 < 0x11) {
      param_1[7] = 0;
    }
  }
  return;
}

