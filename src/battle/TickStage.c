/* TickStage - 0x004e39b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY, the verb is Tick, the object is the stage). Its only
 * caller is State11_InBattle_OnTick, which calls it as the last step of the
 * per-frame tick with the stage object (ctx+0x6a7708) in ESI (a register
 * argument; the parameter keeps the tree's regEsi name). Callee-side, the
 * final call is TickActiveObjectLayers on stage+0x85c, the registry that
 * ReleaseStageResources clears on exit, so this is the stage's per-frame
 * tick and the same stage object LoadStageLandFile fills.
 * Field roles come from other functions' use of the same cells, not from
 * this body. Stage +0x10/+0x14 (ctx+0x6a7718/0x6a771c, g_nCameraScrollX/Y)
 * are written by the Detonate* and Explode* bodies with a point clamped to
 * the land width and height less 400, i.e. a requested view position;
 * this routine eases the current position at +0/+4 toward it and mirrors
 * it to +8/+0xc (ctx+0x6a7710/14, g_nCameraX/Y). The divisor is 4; when
 * the byte at +0x2d and the one at +0x864 are both set it is 8, or 6
 * once either axis gap exceeds 200. The counters at +0x48/+0x4c
 * (ctx+0x6a7750/54) are bumped by the same detonators; while both are
 * nonzero both are decremented each tick and, when the byte at +0x50 is
 * set, a random offset of +-half the second counter is added to +8/+0xc:
 * a screen shake. Camera is only part of the job, hence Stage rather than
 * Camera in the name.
 */
#include "ghidra_types.h"


void TickStage(int *regEsi)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = regEsi[4] - *regEsi;
  uVar3 = regEsi[5] - regEsi[1];
  iVar5 = 4;
  if (((*(char *)((int)regEsi + 0x2d) != '\0') && ((char)regEsi[0x219] != '\0')) &&
     ((200 < (int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) ||
      (iVar5 = 8, 200 < (int)((uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f)))))) {
    iVar5 = 6;
  }
  if ((int)uVar1 < 0) {
    iVar2 = uVar1 + (1 - iVar5);
  }
  else {
    iVar2 = (uVar1 - 1) + iVar5;
  }
  if ((int)uVar3 < 0) {
    iVar4 = uVar3 + (1 - iVar5);
  }
  else {
    iVar4 = (uVar3 - 1) + iVar5;
  }
  iVar2 = *regEsi + iVar2 / iVar5;
  regEsi[2] = iVar2;
  *regEsi = iVar2;
  iVar5 = regEsi[1] + iVar4 / iVar5;
  regEsi[3] = iVar5;
  regEsi[1] = iVar5;
  if ((regEsi[0x12] != 0) && (iVar5 = regEsi[0x13], iVar5 != 0)) {
    iVar2 = iVar5;
    if ((char)regEsi[0x14] != '\0') {
      iVar4 = _rand();
      iVar2 = regEsi[0x13];
      regEsi[2] = regEsi[2] + (iVar4 % iVar5 - iVar5 / 2);
      iVar5 = _rand();
      regEsi[3] = regEsi[3] + (iVar5 % iVar2 - iVar2 / 2);
    }
    regEsi[0x12] = regEsi[0x12] + -1;
    regEsi[0x13] = iVar2 + -1;
  }
  TickActiveObjectLayers((int)regEsi + 0x85c);
  return;
}

