/* BuildSizedSpriteQuad - 0x004ecc70 in the original binary.
 *
 * Rotated textured-quad emitter drawn to an explicit width x height (params w,h) with a horizontal-flip flag; rotates the corners via g_sineTable360 and appends two triangles to g_spriteVertexBuffer. See ARCHITECTURE.md rendering section. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-27): the original takes TWO register
 * arguments, not one. EAX is the sprite rotation angle in degrees -
 * `mov edi,eax` at 0x004ecc82 is the last prologue instruction, before
 * anything writes EAX, and EDI is then used only as (angle+0x5a)%0x168
 * and angle%0x168 to index g_sineTable360 at 0x54c240. EBX is the
 * texture-cache record whose +0x80/+0x84 floats are the UV origin and
 * +0x88 the UV size; it is never pushed and never written in the body,
 * first read at 0x004ecde9 (`fld dword ptr [ebx+0x80]`). Both are
 * read-before-write, so both are real arguments; Ghidra emitted them as
 * the unassigned locals in_EAX and unaff_EBX - the EBX one a live wild
 * read. They are now the trailing regEax/regEbx parameters, with the
 * body keeping the old names via initialisers.
 *
 * Unlike its sibling BuildScaledSpriteQuad this is an APPEND, not a
 * re-slot. The function ends in a bare `ret` (not `ret N`) after
 * `add esp,0x14` (its own frame) and every call site cleans up with
 * `add esp,0x18`, so the binary passes exactly 6 cdecl stack arguments
 * - the 6 already declared. ECX is not a `this` here: it is param_5,
 * loaded from [esp+0x28] at 0x004ecc73; the re-slot that hit
 * BuildScaledSpriteQuad was forced by ITS ECX being param_1, and there
 * is no such register-borne parameter in this one.
 *
 * All 16 ported call sites were recovered. Eight were fully argless in
 * the decompile and two more were short (1 and 4 args), because at
 * those sites Ghidra had modelled some or all of the pushes as stores
 * to stack locals sitting immediately above the call. The remaining six
 * sites already passed all 6 stack arguments and needed only the two
 * register ones. At 0x4c52ef - one of the argless eight - the
 * fabricated stores were pcStack_a04 (param_3) / uStack_a08 (param_2) /
 * piStack_a0c (param_1) plus pcStack_a10 = 0x4c52f4, which is that
 * call's OWN return address, not data. At 0x4c5b85 the whole
 * pcStack_a28 / piStack_a2c / piStack_a30 / pcStack_a34 / uStack_a38
 * group is fabricated, leaving only param_1 emitted; at 0x4c5da9 only
 * pcStack_a34 (param_6) and uStack_a38 (param_5) are, the other four
 * pushes having been emitted as real arguments. Every such fabricated
 * assignment was deleted and turned back into an argument, after
 * checking that each slot is rewritten before any read.
 *
 * Caution for the two Rayon loops: they sit at DIFFERENT modelled stack
 * depths, so the same push index lands on differently named slots.
 * 0x4c5b85's frame base is 0xc higher than 0x4c5da9's - the loop
 * counter is read from [esp+0x18] in both yet is piStack_a0c in one and
 * piStack_a18 in the other, and the texture record is read from
 * [esp+0x28] in both yet is iVar6 in one and uStack_a08 in the other.
 * Both sites were therefore resolved from their push VALUES (-1, 0x20,
 * 0x20, setne, y, x), never from the slot names.
 *
 * The 17th binary call site, 0x0049e532, has no ported caller: it is
 * inside an unported __thiscall renderer at 0x0049e4c0 that falls in
 * the PROGRESS.csv address gap 0x0049e4bb..0x0049e540. It confirms both
 * register meanings independently - `mov eax,[ebp+0x44]` (the object's
 * angle field) into EAX, and EBX = the FindTextureCacheEntryByName
 * result for the name at 0x555b80.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuildSizedSpriteQuad(int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
                          int regEax,int regEbx)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int in_EAX = regEax;
  int iVar8;
  int iVar9;
  int iVar10;
  int unaff_EBX = regEbx;
  undefined4 *puVar11;
  undefined4 *puVar12;
  
  fVar3 = (float)(param_4 / 2 + -1);
  fVar4 = (float)(param_5 / 2 + -1);
  iVar10 = (in_EAX + 0x5a) % 0x168;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar10 * 4);
  iVar10 = in_EAX % 0x168;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar10 * 4);
  fVar6 = fVar1 * (float)-(param_4 / 2);
  _DAT_00ea0e50 = fVar1 * (float)-(param_5 / 2);
  _DAT_00ea0e98 = -(fVar2 * (float)-(param_4 / 2));
  _DAT_00ea0e4c = fVar2 * (float)-(param_5 / 2);
  fVar7 = fVar1 * fVar3;
  fVar1 = fVar1 * fVar4;
  _DAT_00ea0e94 = (float)param_1;
  DAT_00ea0e28 = _DAT_00ea0e94 + _DAT_00ea0e4c + fVar6;
  fVar5 = (float)param_2;
  DAT_00ea0e2c = fVar5 + _DAT_00ea0e98 + _DAT_00ea0e50;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar7 + _DAT_00ea0e4c;
  fVar3 = fVar5 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar3 + _DAT_00ea0e50;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar7;
  DAT_00ea0e74 = fVar3 + fVar1;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar6;
  _DAT_00ea0e98 = fVar5 + fVar1 + _DAT_00ea0e98;
  DAT_00ea0ea8 = *(float *)(unaff_EBX + 0x80);
  if (param_3 == '\0') {
    _DAT_00ea0e84 = *(float *)(unaff_EBX + 0x88) + *(float *)(unaff_EBX + 0x80);
  }
  else {
    _DAT_00ea0e84 = DAT_00ea0ea8;
    DAT_00ea0ea8 = *(float *)(unaff_EBX + 0x88) + *(float *)(unaff_EBX + 0x80);
  }
  _DAT_00ea0e40 = *(undefined4 *)(unaff_EBX + 0x84);
  iVar8 = g_spriteVertexCount * 0x6c;
  iVar10 = g_spriteVertexCount * 0x1b;
  g_spriteVertexCount = g_spriteVertexCount + 2;
  _DAT_00ea0e88 =
       *(float *)(unaff_EBX + 0x88) / ((float)param_4 / (float)param_5) +
       *(float *)(unaff_EBX + 0x84);
  _DAT_00ea0ea4 = param_6;
  _DAT_00ea0e80 = param_6;
  _DAT_00ea0e5c = param_6;
  _DAT_00ea0e38 = param_6;
  puVar11 = &DAT_00ea0e28;
  puVar12 = &g_spriteVertexBuffer + iVar10;
  _DAT_00ea0e3c = DAT_00ea0ea8;
  _DAT_00ea0e60 = _DAT_00ea0e84;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar9 = 0x1b; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar11 = &DAT_00ea0e70;
  puVar12 = (undefined4 *)(&DAT_006ba1fc + iVar8);
  for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar11 = &DAT_00ea0e28;
  puVar12 = (undefined4 *)(&DAT_006ba244 + iVar8);
  for (iVar10 = 9; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  return;
}

