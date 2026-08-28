/* BuildRotatedSpriteQuad128 - 0x004ec430 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Recovered arguments. The original is __usercall: ECX carries the object
 * (Ghidra already models it as param_1 of a __thiscall), four dwords arrive
 * on the stack, and EAX carries a fifth value that Ghidra dropped as the
 * unassigned local in_EAX. EAX is read before it is written - 0x004ec434 mov
 * esi, eax - and is a rotation angle in degrees: 0x004ec436 lea eax,
 * [esi+0x5a] then idiv 0x168 gives the cosine index into g_sineTable360 at
 * 0x0054c240, and 0x004ec44f mov eax, esi then idiv 0x168 gives the sine
 * index. It is promoted here to the trailing parameter regEax.
 *
 * Frame model. The prologue is sub esp, 0x1c then push esi then push edi,
 * and no instruction in the body moves ESP again, so the depth is a constant
 * 0x24 and the return address sits at [esp+0x24]. The four argument slots
 * are therefore [esp+0x28] = param_2, the destination X converted by fild at
 * 0x004ec4c5; [esp+0x2c] = param_3, the destination Y converted by fild at
 * 0x004ec4db; [esp+0x30] = param_4, read as a single byte by movzx at
 * 0x004ec46a and shifted left 0x18; and [esp+0x34] = param_5, or'ed in at
 * 0x004ec59b. Together param_4 and param_5 form one packed ARGB tint. That
 * slot layout is confirmed a second, independent way by the callers: each of
 * the four sites pushes exactly four dwords and then does add esp, 0x10, and
 * 0x24 plus 0x10 is exactly 0x34, the highest offset the callee reads, so
 * the frame closes with no gap and no overrun. The function ends in a bare
 * ret, so the count could not be taken from a ret N and was derived from
 * these reads instead.
 *
 * EDX, ESI and EDI are phantoms. EDX's first touch is the write cdq at
 * 0x004ec43a; ESI's is mov esi, eax at 0x004ec434, the push before it being
 * a save and not a read; EDI's is mov edi, 0x168 at 0x004ec43b.
 * callsite_regs.py reports a uniform shr edx, 1 at all four sites, but that
 * is the caller's own index-over-two scratch for the V texture coordinate,
 * not an argument. EBX is never referenced by this function.
 *
 * Behaviour. The function fills the staging block at 0x00ea0e28 with two
 * rotated, tinted quads built from the object's U/V fields at +0x80, +0x84
 * and +0x88, then copies 0x1b dwords to g_spriteVertexBuffer plus
 * g_spriteVertexCount times 0x1b, 0x12 dwords to 0x006ba1fc plus count times
 * 0x6c, and 9 dwords to 0x006ba244 plus count times 0x6c, and advances
 * g_spriteVertexCount by two.
 *
 * Call sites. All four live in the four FlameTexture decoration loops of
 * State11_InBattle_Render, at 0x004c5458, 0x004c5624, 0x004c57c4 and
 * 0x004c5964. Each walks a four-entry array of twelve-byte records whose
 * third dword is the angle passed in EAX. Every site had all five declared
 * slots empty, so this is a re-slot and not an append, and the pushes had
 * been rendered as stores to stack locals above an argless call; those
 * fabrications, including the return-address stores 0x4c545d, 0x4c5629,
 * 0x4c57c9 and 0x4c5969, are folded back into real arguments.
 *
 * NAMED (2026-08-28): the fixed 128x128 member of the quad-emitter
 * family - BuildRotatedSpriteQuad's shape (same __thiscall texture
 * record in ECX, same X/Y, same angle in EAX, same 0xea0e28 staging
 * block and the same two-triangle append into g_spriteVertexBuffer) with
 * a 128-pixel square extent and a caller-supplied ARGB in place of that
 * one's hardcoded 0xffffffff and its horizontal-flip flag.
 *
 * THE 128 IS NOT READ OFF THIS BODY ALONE. The two float constants the
 * corners are built from are -64.0 at 0x558010 and 63.0 at 0x557fc4, so
 * the quad spans -64..63 on both axes; and each of the four call sites
 * independently brackets the same centre with a 0x80-wide box before it
 * calls, testing `x + 0x1d0` and `x + 0x150` against the clip rect while
 * passing `x + 0x190` as the quad's X, and `y + 0x16a` and `y + 0xea`
 * while passing `y + 0x12a` as its Y. Both are the centre plus or minus
 * 0x40. The caller says 128x128 in its own arithmetic.
 *
 * The suffix rather than a word like "Tinted": a colour argument does
 * NOT distinguish this function - BuildScaledSpriteQuad already takes
 * the identical `alpha << 0x18 | rgb` pair and BuildSizedSpriteQuad
 * takes a packed colour too, and all four ported call sites here pass
 * plain opaque white (0xff, 0xffffff). What does distinguish it is where
 * the extent comes from, which is the axis the rest of the family is
 * already named on: BuildSpriteQuad and BuildRotatedSpriteQuad are
 * fixed, BuildScaledSpriteQuad has independent X and Y scale constants,
 * BuildSizedSpriteQuad takes a runtime width and height, and
 * BuildSquareSpriteQuad takes a single runtime side.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall BuildRotatedSpriteQuad128(int param_1,int param_2,int param_3,int param_4,uint param_5,int regEax)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int in_EAX = regEax;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  iVar7 = (in_EAX + 0x5a) % 0x168;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0x168;
  }
  iVar8 = in_EAX % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar5 = *(float *)(&g_sineTable360 + iVar7 * 4) * _DAT_00558010;
  fVar2 = _DAT_00558010 * *(float *)(&g_sineTable360 + iVar8 * 4);
  fVar6 = *(float *)(&g_sineTable360 + iVar7 * 4) * _DAT_00557fc4;
  fVar3 = *(float *)(&g_sineTable360 + iVar8 * 4) * _DAT_00557fc4;
  _DAT_00ea0e94 = (float)param_2;
  DAT_00ea0e28 = _DAT_00ea0e94 + fVar2 + fVar5;
  fVar1 = (float)param_3;
  DAT_00ea0e2c = fVar1 + -fVar2 + fVar5;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar6 + fVar2;
  fVar4 = -fVar3 + fVar1;
  _DAT_00ea0e50 = fVar5 + fVar4;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar3;
  DAT_00ea0e70 = fVar6 + _DAT_00ea0e94;
  DAT_00ea0e74 = fVar4 + fVar6;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar5;
  _DAT_00ea0e98 = fVar1 + fVar6 + -fVar2;
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x80);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x84);
  _DAT_00ea0e38 = (uint)param_4 << 0x18 | param_5;
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

