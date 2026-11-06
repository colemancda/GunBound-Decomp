/* Stage_Construct - 0x004e3810 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e3810 mean this function.)
 *
 * Evidence (LIKELY, from the object's identity). Its only caller is
 * ClientContext_Constructor (orig 0x416845), which passes ctx+0x6a7708
 * by the arena offset; that is the stage object TickStage (0x4e39b0),
 * LoadStageLandFile and ReleaseStageResources take as their object. This
 * body initialises the cells those functions use: the camera position
 * pairs at +0..+0xc that TickStage eases, the flag byte at +0x2d that
 * it tests, the counters at +0x48/+0x4c and flag at +0x50, and the
 * buffer pointers at +0x34/+0x38/+0x3c/+0x44 that ReleaseStageResources
 * frees (+0x34/+0x38 are the ones LoadStageLandFile allocates). All are
 * zeroed here, and the embedded registry at +0x85c that TickStage ticks
 * is built (ActiveObjectRegistry_BaseConstructor). It is the
 * constructor, not a loader: it allocates only the 0x308-byte scene-node
 * member stored at +0x30 and no stage data. The twin is Stage_Destruct
 * (0x4e38f0). The name follows the Foo_Construct form used by the other
 * Construct functions in the tree.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * Stage_Construct(undefined4 *param_1)

{
  float fVar1;
  void *pvVar2;
  undefined4 *extraout_EDX;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053776e;
  *unaff_FS_OFFSET = &local_c;
  ActiveObjectRegistry_BaseConstructor((undefined4 *)((int)param_1 + 0x85c));
  param_1[0x217] = &PTR_FUN_00555b7c;
  local_4 = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[8] = 0;
  pvVar2 = operator_new(0x308);
  if (pvVar2 == (void *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    FUN_004f3150(0,(undefined4 *)pvVar2,0);
    fVar1 = _DAT_00588f54 / _DAT_00588f50;
    *extraout_EDX = &PTR_FUN_00557300;
    extraout_EDX[0xbd] = 0x3fa4bc6a;
    extraout_EDX[0xbf] = 0x3f800000;
    extraout_EDX[0xc0] = 0x447a0000;
    extraout_EDX[0xbe] = 0x3f24bc6a;
    extraout_EDX[0xc1] = fVar1;
    puVar3 = extraout_EDX;
  }
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x11] = 0;
  param_1[0x10] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  *(undefined1 *)(param_1 + 0xb) = 0;
  *(undefined1 *)((int)param_1 + 0x2d) = 0;
  *(undefined1 *)(param_1 + 0x219) = 0;
  param_1[0xc] = puVar3;
  *(undefined1 *)(param_1 + 0x14) = 1;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

