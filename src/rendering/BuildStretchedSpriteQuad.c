/* BuildStretchedSpriteQuad - 0x004ec610 in the original binary.
 *
 * Another member of the 0x4eb-0x4ed quad-builder family, sitting
 * physically between its named siblings BuildRotatedSpriteQuad128
 * (0x4ec430) and BuildSquareSpriteQuad (0x4ec840) and sharing their
 * whole skeleton: the (angle+0x5a)%0x168 / angle%0x168 g_sineTable360
 * sin/cos pair, UVs from the record's +0x80/+0x84/+0x88, alpha<<24 |
 * 0xffffff vertex colour, staging at 0xea0e28 and the two-quad append
 * to g_spriteVertexBuffer with g_spriteVertexCount += 2.
 *
 * What discriminates it (a body-level diff against BuildSquareSpriteQuad
 * leaves exactly this): the quad is NOT square.  One axis spans
 * -(size/2)..size/2-1 as in the square sibling, but the perpendicular
 * axis spans -(8192/size)..8192/size-1 - the three constants involved
 * are 1.0f (0x557fb0), 8192.0f (0x558014) and -8192.0f (0x558018),
 * read from the binary's .data - so the rectangle is size x
 * (16384/size): constant area, one axis scaling with `size` and the
 * other inversely, i.e. the quad stretches longer and thinner as size
 * grows.  Signature: (record, x, y, size, alpha) on ECX+stack with the
 * angle in EAX.
 *
 * The one binary call site, 0x464308, is the crash effect's uncarved
 * Draw at 0x464280 (slot 3 of vtable 0x555ccc - the class
 * src/battle/SpawnCrashEffect.c documents): it looks up "CrashTexture",
 * writes the frame UVs, and passes size = the object's +0x48 and alpha
 * from +0x4c - the two fields that class's decay Tick (0x464250)
 * advances and shrinks each frame, which is what makes the stretch
 * visible at all.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall BuildStretchedSpriteQuad(int param_1,int param_2,int param_3,int param_4,int param_5,int regEax)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  iVar8 = (regEax + 0x5a) % 0x168;
  _DAT_00ea0e4c = _DAT_00558018 * (_DAT_00557fb0 / (float)param_4);
  fVar3 = (float)(param_4 / 2 + -1);
  fVar7 = (_DAT_00557fb0 / (float)param_4) * _DAT_00558014 - _DAT_00557fb0;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar8 * 4);
  iVar8 = regEax % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar8 * 4);
  fVar5 = fVar1 * (float)-(param_4 / 2);
  _DAT_00ea0e38 = (uint)param_5 << 0x18 | 0xffffff;
  _DAT_00ea0e50 = fVar1 * _DAT_00ea0e4c;
  _DAT_00ea0e98 = -(fVar2 * (float)-(param_4 / 2));
  _DAT_00ea0e4c = fVar2 * _DAT_00ea0e4c;
  fVar6 = fVar1 * fVar3;
  fVar1 = fVar1 * fVar7;
  _DAT_00ea0e94 = (float)param_2;
  DAT_00ea0e28 = _DAT_00ea0e94 + _DAT_00ea0e4c + fVar5;
  fVar4 = (float)param_3;
  DAT_00ea0e2c = fVar4 + _DAT_00ea0e98 + _DAT_00ea0e50;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar6 + _DAT_00ea0e4c;
  fVar3 = fVar4 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar3 + _DAT_00ea0e50;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar7;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar6;
  DAT_00ea0e74 = fVar3 + fVar1;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar5;
  _DAT_00ea0e98 = fVar4 + fVar1 + _DAT_00ea0e98;
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar8 = 0x1b; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar8 = 9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

