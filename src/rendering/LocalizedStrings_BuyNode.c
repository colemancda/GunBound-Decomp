/* LocalizedStrings_BuyNode - 0x0043e150 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043e150 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the only
 * caller is LocalizedStrings_LinkNode, which takes the returned node and
 * links it in. It lazily mallocs the nil sentinel into map+0x14, refills
 * the pool with blocks of map+0x10 (= 10, stored by
 * LocalizedStrings_InitHeader) 0x18-byte nodes (malloc(10*0x18+4), block
 * chain at map+0xc, free list at map+8), constructs the CString value at
 * node+4 with ConstructStringFromText, and bumps the count at map+4. It is
 * the pool-allocator _Buynode of this map, a sibling of Tree_Buynode_18
 * and RBTree_BuyNode for a different node layout.
 *
 * DEFINITION COMPLETED AND ESI RECOVERED (2026-08-25).  `ret 8`: two stack
 * arguments -- the node key and value FUN_0043e0f0 already pushed -- against
 * a definition declaring one.  ESI is the map object, FUN_0043e0f0's own ECX
 * parameter, unchanged between that function's entry `mov esi,ecx` and this
 * call.
 */
#include "ghidra_types.h"


undefined4 * LocalizedStrings_BuyNode(undefined4 param_1,undefined4 param_2,undefined4 *regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  if (regEsi[2] == 0) {
    if (regEsi[5] == 0) {
      puVar1 = _malloc(0x18);
      regEsi[5] = puVar1;
      if (puVar1 == (undefined4 *)0x0) goto LAB_0043e189;
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[5] = 0;
      *(undefined4 *)(regEsi[5] + 8) = 1;
      *(undefined4 *)(regEsi[5] + 0x10) = regEsi[5];
      *(undefined4 *)(regEsi[5] + 0xc) = *(undefined4 *)(regEsi[5] + 0x10);
      *(undefined4 *)(regEsi[5] + 0x14) = *(undefined4 *)(regEsi[5] + 0xc);
      *regEsi = regEsi[5];
    }
    puVar1 = _malloc(regEsi[4] * 0x18 + 4);
    if (puVar1 == (undefined4 *)0x0) {
LAB_0043e189:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = regEsi[3];
    regEsi[3] = puVar1;
    iVar2 = regEsi[4];
    puVar1 = puVar1 + iVar2 * 6 + -5;
    if (-1 < iVar2 + -1) {
      do {
        puVar1[3] = regEsi[2];
        regEsi[2] = puVar1;
        puVar1 = puVar1 + -6;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  puVar1 = (undefined4 *)regEsi[2];
  local_4 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    ConstructStringFromText(puVar1 + 1);
    puVar1[2] = 1;
    puVar1[5] = 0;
  }
  regEsi[2] = *(undefined4 *)(regEsi[2] + 0xc);
  puVar1[2] = 0;
  puVar1[3] = regEsi[5];
  puVar1[4] = regEsi[5];
  puVar1[5] = regEsi[5];
  regEsi[1] = regEsi[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

