/* BuildRotatedBeamQuad - 0x004ed0c0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004ed0c0).  Appends a rotated, texture-tiled
 * BEAM quad pair to the sprite vertex buffer - the rotated sibling of
 * BuildScaledSpriteQuad (0x4eb...) and distinct from BuildRotatedSpriteQuad
 * (0x4ebbc0), which emits a single plain quad.  Evidence:
 *   - the angle arrives in EAX and is reduced `% 0x168` (360) twice, once
 *     with a +0x5a (+90 degree) bias, and both indices look up
 *     g_sineTable360 - i.e. sin and cos of one angle.
 *   - param_6 is the beam LENGTH and param_7 its WIDTH: the four corners are
 *     (x, y) +/- the perpendicular half-width (param_7 / 2) offset by
 *     cos/sin * length.
 *   - the texture rect comes from param_2 + 0x80 / +0x84 / +0x88, and
 *     _DAT_00ea0e88 = uv_extent / (length / width) + v0 TILES the texture
 *     along the beam.
 *   - it appends to g_spriteVertexBuffer and does g_spriteVertexCount += 2.
 * Both call sites are in State11_InBattle_Render.
 *
 * ABI, AND WHAT IS STILL OPEN (2026-08-19 audit).  Ghidra marked this
 * __fastcall, but the prologue loads ECX from [esp+0x28] - a stack slot - so
 * param_1 is a PHANTOM.  The real shape is EAX (the angle, Ghidra's
 * `in_EAX`) + EDX (param_2, the texture record) + ret 0x14 = 5 stack
 * arguments (params 3-7 = x, y, flip, length, width).  Both call sites in
 * State11_InBattle_Render pass only the 5 stack arguments, so the angle and
 * the texture record are read from whatever is left in EAX and EDX.
 *
 * Site 0x4c8630 is fully resolved: param_3/param_4 are [esp+0x14]/[esp+0x2c]
 * (iVar19 / pcStack_a28), EDX = esi, and EAX = edi = the result of the
 * `PeekPacketChecksumState(*(int *)(g_clientContext + 0x621e4) + 0x4fb4)`
 * that the decompile discards on the line directly above the call.
 *
 * Site 0x4c7837 does NOT match that shape and is the open part: there the
 * discarded peek's result is stored to [esp+0x14] and becomes param_3, while
 * EAX comes from a DIFFERENT slot ([esp+0x10]) and EDX from [esp+0x28].
 * Resolving what feeds those two slots is the remaining step; until both
 * sites are known, NO prototype has been added to include/functions.h -
 * declaring it __fastcall while one site still passes 5 arguments would put
 * that site's x and y into ECX/EDX and make things worse, not better.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
BuildRotatedBeamQuad(undefined4 param_1,int param_2,int param_3,int param_4,char param_5,int param_6,
            int param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int in_EAX;
  int iVar7;
  int iVar8;
  undefined4 unaff_EBX;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  fVar3 = (float)param_6;
  fVar4 = (float)(param_7 / 2 + -1);
  iVar8 = (in_EAX + 0x5a) % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar8 * 4);
  iVar8 = in_EAX % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar8 * 4);
  _DAT_00ea0e50 = fVar1 * (float)-(param_7 / 2);
  _DAT_00ea0e4c = fVar2 * (float)-(param_7 / 2);
  fVar5 = fVar1 * fVar4;
  DAT_00ea0e28 = (float)param_3 + _DAT_00ea0e4c + fVar1 * _DAT_00557fb4;
  DAT_00ea0e2c = (float)param_4 + fVar2 * _DAT_00557fb4 + _DAT_00ea0e50;
  _DAT_00ea0e4c = (float)param_3 + fVar1 * fVar3 + _DAT_00ea0e4c;
  fVar6 = (float)param_4 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar6 + _DAT_00ea0e50;
  _DAT_00ea0e94 = (float)param_3 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * fVar3;
  DAT_00ea0e74 = fVar6 + fVar5;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * _DAT_00557fb4;
  _DAT_00ea0e98 = (float)param_4 + fVar5 + fVar2 * _DAT_00557fb4;
  DAT_00ea0ea8 = *(float *)(param_2 + 0x80);
  if (param_5 == '\0') {
    _DAT_00ea0e84 = *(float *)(param_2 + 0x88) + *(float *)(param_2 + 0x80);
  }
  else {
    _DAT_00ea0e84 = DAT_00ea0ea8;
    DAT_00ea0ea8 = *(float *)(param_2 + 0x88) + *(float *)(param_2 + 0x80);
  }
  _DAT_00ea0e40 = *(undefined4 *)(param_2 + 0x84);
  iVar8 = g_spriteVertexCount * 0x6c;
  _DAT_00ea0e88 = *(float *)(param_2 + 0x88) / (fVar3 / (float)param_7) + *(float *)(param_2 + 0x84)
  ;
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  g_spriteVertexCount = g_spriteVertexCount + 2;
  _DAT_00ea0e38 = unaff_EBX;
  _DAT_00ea0e3c = DAT_00ea0ea8;
  _DAT_00ea0e5c = unaff_EBX;
  _DAT_00ea0e60 = _DAT_00ea0e84;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = unaff_EBX;
  _DAT_00ea0ea4 = unaff_EBX;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + iVar8);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + iVar8);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  return;
}

