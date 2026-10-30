/* CreateCommP2POwner - 0x004fd090 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_004fd090).  The heap factory for
 * the CommP2POwner composite: `push 0x2028; call 0x52022d`
 * (operator_new, 0x4fd0a6-0x4fd0ab), then on success
 * `push ecx; push eax; call 0x4fd0f0` - ConstructCommP2POwner(new
 * object, this function's one stack argument) - and returns its result;
 * NULL when the allocation fails.  0x2028 is the object size
 * ConstructCommP2POwner's header documents, and that constructor has no
 * other caller.  Its own sole caller, FUN_00401910 (0x401a26), passes
 * its +8 sub-object and stores the returned owner at +0x1bdc
 * (param_1[0x6f7]).  "CommP2POwner" is the tree's working handle - see
 * ConstructCommP2POwner.c; "Create" is the factory verb, against that
 * file's Construct and DestroyCommP2POwner's Destroy.
 */
#include "ghidra_types.h"


undefined4 CreateCommP2POwner(undefined4 param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  pvVar1 = operator_new(0x2028);
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    uVar2 = ConstructCommP2POwner(pvVar1,param_1);
    *unaff_FS_OFFSET = local_c;
    return uVar2;
  }
  *unaff_FS_OFFSET = local_c;
  return 0;
}

