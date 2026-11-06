/* SpawnStageDecoration - 0x004e4f50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e4f50 mean this function.)
 *
 * Evidence (LIKELY; the verb is solid, the noun comes from the caller).
 * The sole caller is LoadStageDecorationSet (orig 0x4e3fe1), which loops
 * index 1.. over a per-stage sprite set loaded with LoadSpriteSet and, for
 * each index, calls this with (stage = ctx+0x6a7708, index, texture name
 * built by sprintf from the stage record). The stage object is the one
 * TickStage, LoadStageLandFile and ReleaseStageResources operate on. This
 * function allocates a fresh 0x38-byte object (vtable 0x556558), stores
 * the index at +8, resolves the named texture into +0x1c with
 * FindPreloadedTextureByName, sets the state name "normal" through
 * vtable slot 1, and links it into the sorted registry at stage+0x85c
 * (RegisterActiveObject keys on the +4 and +8 fields), the registry
 * TickStage ticks and ReleaseStageResources clears. So it creates one
 * object per decoration image and hands it to the stage, hence Spawn.
 * What the object looks like on screen is not established here.
 *
 * DROPPED-REGISTER FIX: the port called RegisterActiveObject(0,0,NULL).
 * Orig 0x4e4fbe-0x4e4fc8: `mov edx,[esp+0xc]` (the stage, first stack
 * argument after two pushes) / `add edx,0x85c` / call 0x4f2fb0 with the
 * new object still in EDI, so the call is (0, stage + 0x85c, object).
 */
#include "ghidra_types.h"


void SpawnStageDecoration(undefined4 param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = operator_new(0x38);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = param_2;
    piVar1[1] = 0;
    piVar1[3] = 0;
    piVar1[4] = 0;
    *(undefined1 *)(piVar1 + 5) = 0;
    *(undefined1 *)((int)piVar1 + 0x15) = 0;
    piVar1[6] = -1;
    piVar1[7] = 0;
    *(undefined1 *)(piVar1 + 8) = 0;
    piVar1[10] = 0;
    piVar1[0xb] = 0;
    piVar1[9] = -1;
    *piVar1 = (int)&PTR_FUN_00556558;
  }
  iVar2 = FindPreloadedTextureByName(param_3);
  piVar1[7] = iVar2;
  (**(code **)(*piVar1 + 4))(s_normal_00552230);
  RegisterActiveObject(0,(int)param_1 + 0x85c,(undefined4 *)piVar1);
  return;
}

