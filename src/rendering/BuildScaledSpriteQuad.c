/* BuildScaledSpriteQuad - 0x004eca50 in the original binary.
 *
 * Rotated textured-quad emitter with independent X/Y scale (uses 4 distinct scale-constant globals vs BuildRotatedSpriteQuad's uniform 2), for non-1:1 sprites such as the Ready Room zoomed avatar preview. Appends two triangles to g_spriteVertexBuffer. See ARCHITECTURE.md rendering section. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-27): the original takes the sprite rotation
 * angle in EAX. `mov esi,eax` at 0x004eca54 is the first instruction
 * after the prologue, before anything writes EAX, and ESI is then used
 * only as (angle+0x5a)%0x168 and angle%0x168 to index g_sineTable360 at
 * 0x54c240 - a read-before-write, so a real argument. Ghidra emitted it
 * as an unassigned `in_EAX` local; it is now the trailing `regEax`
 * parameter, with the body keeping the old name via an initialiser.
 *
 * The function ends in a bare `ret` (not `ret N`) and every call site
 * cleans up with `add esp,0x14`, so the binary passes 5 cdecl stack
 * arguments plus ECX - param_1, the texture-cache record whose +0x80/
 * +0x84/+0x88 floats are the UV rect - which is exactly the 6 declared
 * parameters. The mis-slotting was all on the caller side: the 10 sites
 * in State09_ReadyRoom_RenderCharacterPreview.c and
 * State11_InBattle_RenderModeIcons.c passed five arguments into
 * param_1..param_5, shifting the texture record out and leaving param_6
 * undefined, and the 8 sites in State11_InBattle_Render.c passed
 * nothing at all. All 18 were re-slotted, not appended to.
 *
 * At four of the eight State11_InBattle_Render.c sites - the
 * motion-trail loops at 0x4c3507, 0x4c37a1, 0x4c39e1 and 0x4c3bfb -
 * param_5/param_6 are computed, not literal:
 * `neg/sbb/and 0xff808081/add 0xffffff` is
 * (trailIdx == 0) ? 0xffffff : 0x808080, and `shl al,4 / 0xff - al` is
 * (byte)(0xff - trailIdx * 0x10) - the ghost-trail fade ramp. The other
 * four (0x4c3ecd, 0x4c417b, 0x4c438f, 0x4c4553) push the literals
 * 0xff and 0xffffff.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
BuildScaledSpriteQuad(int param_1,int param_2,int param_3,char param_4,byte param_5,uint param_6,
                     int regEax)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX = regEax;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar4 = (in_EAX + 0x5a) % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar4 * 4);
  iVar4 = in_EAX % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar4 * 4);
  DAT_00ea0e28 = (float)param_2 + fVar2 * _DAT_0055800c + fVar1 * _DAT_00558010;
  DAT_00ea0e2c = (float)param_3 + fVar2 * _DAT_00558008 + fVar1 * _DAT_0055800c;
  _DAT_00ea0e4c = (float)param_2 + fVar1 * _DAT_00557fc4 + fVar2 * _DAT_0055800c;
  fVar3 = (float)param_3 + fVar2 * _DAT_00558004;
  _DAT_00ea0e50 = fVar3 + fVar1 * _DAT_0055800c;
  _DAT_00ea0e94 = (float)param_2 + fVar2 * _DAT_00557ff0;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * _DAT_00557fc4;
  DAT_00ea0e74 = fVar3 + fVar1 * _DAT_00557ff0;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * _DAT_00558010;
  _DAT_00ea0e98 = (float)param_3 + fVar1 * _DAT_00557ff0 + fVar2 * _DAT_00558008;
  DAT_00ea0ea8 = *(float *)(param_1 + 0x80);
  if (param_4 == '\0') {
    _DAT_00ea0e84 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  }
  else {
    _DAT_00ea0e84 = DAT_00ea0ea8;
    DAT_00ea0ea8 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  }
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x84);
  _DAT_00ea0e38 = (uint)param_5 << 0x18 | param_6;
  puVar5 = &DAT_00ea0e28;
  puVar6 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e3c = DAT_00ea0ea8;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  _DAT_00ea0e60 = _DAT_00ea0e84;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar4 = 0x1b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar5 = &DAT_00ea0e70;
  puVar6 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar5 = &DAT_00ea0e28;
  puVar6 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

