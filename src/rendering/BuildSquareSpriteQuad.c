/* BuildSquareSpriteQuad - 0x004ec840 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the original takes the quad's pixel size in
 * EAX. `mov esi,eax` at 0x004ec844 is the second instruction of the
 * function, before anything writes EAX, and ESI is then consumed only as
 * -(size/2) and size/2-1, the two corner offsets. Read before written, so a
 * real argument; Ghidra emitted it as the unassigned local in_EAX. It is now
 * the trailing regEax parameter, with the body keeping the old name via an
 * initialiser.
 *
 * Unlike its sibling BuildSizedSpriteQuad, EBX is NOT a second dropped
 * register here: neither ebx nor ebp appears anywhere in
 * 0x004ec840-0x004eca49. ESI and EDI are pushed and then immediately
 * written, so they are saves, not arguments.
 *
 * This is an APPEND, not a re-slot. The function ends in a bare `ret` and
 * every call site cleans up with `add esp,0xc`, so the binary passes three
 * stack arguments plus ECX and EDX, which is exactly the five declared
 * parameters. param_1 is ECX, the texture-cache record whose +0x80/+0x84
 * floats are the UV origin and +0x88 the UV size (`fld dword ptr [ecx+0x80]`
 * at 0x004ec992). param_2 is EDX, the rotation angle, used only as
 * (angle+0x5a)%0x168 and angle%0x168 to index g_sineTable360 at 0x54c240.
 * param_3/param_4 are the screen X/Y read with `fild dword ptr [esp+0x24]`
 * and `[esp+0x28]`, and param_5 is the alpha byte read with `movzx eax, byte
 * ptr [esp+0x2c]` and shifted into bits 24-31 of the 0xffffff-based vertex
 * colour.
 *
 * Frame model: `sub esp,0x18` then `push esi`, `push edi` puts the body at
 * entry_esp-0x20 with no later push or pop, so
 * [esp+0x24]/[esp+0x28]/[esp+0x2c] are the three stack arguments. Confirmed
 * twice: the six scratch slots actually used, [esp+8] through [esp+0x1c],
 * form exactly the 0x18-byte run carved by the `sub` once the two pushed
 * registers are accounted for; and on the caller side at 0x00464390 the
 * pushes are alpha, then Y ([esi+0x3c] - camera Y + 0x12a), then X
 * ([esi+0x38] - camera X + 0x190), whose roles match the X lanes, Y lanes
 * and colour lane the callee writes. The 0x24 and 0x28 slots are also reused
 * as float scratch after their incoming values are loaded (fst at
 * 0x004ec908, 0x004ec91a and 0x004ec958), which is harmless because each
 * fild precedes the first store to its slot.
 *
 * Structurally this is the uniform-size sibling of BuildRotatedSpriteQuad at
 * 0x4ebbc0: same 0xea0e28 vertex staging block, same g_sineTable360 corner
 * rotation, same two-triangle append into g_spriteVertexBuffer at
 * g_spriteVertexCount, but the half-extents come from the runtime EAX size
 * instead of the fixed 0x558028-0x55803c scale constants, and it carries a
 * per-call alpha.
 *
 * NO PORTED CALL SITES. count_call_args reports 0, and the only mentions of
 * the symbol in the tree are this definition and its prototype. All six
 * binary call sites sit in unported address gaps; their callers start at
 * 0x464390, 0x471240, 0x481ef0, 0x4894b0, 0x48dd80 and 0x4aa6c0, none of
 * which appear in PROGRESS.csv or under src/. Note that 0x481ef0 and
 * 0x48dd80 are each preceded in their gap by a separate per-frame update
 * function (0x481e80 ending at 0x481ee6, 0x48dd10 ending at 0x48dd7a) that
 * advances [esi+0x40]/[esi+0x44] but never calls this function. A scan of
 * the whole binary for the absolute dword 0x004ec840 found no occurrence, so
 * there is no vtable slot or data-borne reference that a call-only scan
 * could have missed. Each of the six callers is a small fade-out effect draw
 * with the same body: fetch the camera origin from [g_clientContext +
 * 0x6a7710] / [+ 0x6a7714], look up the "CrashTexture" record via
 * FindTextureCacheEntryByName (0x4f4650, name pointer 0x555b80, cache
 * 0xeb1bd8), stamp the scale floats into the record, then pass size in EAX,
 * [this+0x44] as the angle in EDX, and X, Y, 0xff-minus-a-fade-ramp on the
 * stack. The per-site sizes are recorded in the recovery notes.
 *
 * NAMED (2026-08-28): the single-side member of the quad-emitter family.
 * The half-extents are -(size/2) and size/2-1 and BOTH axes use that one
 * pair, so the quad is a square of side `size`, with `size` arriving at
 * run time in EAX rather than coming from the fixed float constants
 * BuildRotatedSpriteQuad and BuildRotatedSpriteQuad128 use.
 *
 * That is the axis the family is already named on - BuildSpriteQuad and
 * BuildRotatedSpriteQuad are fixed-extent, BuildScaledSpriteQuad has
 * independent X and Y scale constants, BuildSizedSpriteQuad takes a
 * runtime WIDTH and HEIGHT - so BuildSquareSpriteQuad is the one that
 * takes a runtime side. It is deliberately not named for its alpha: a
 * colour argument does not separate it from the family either, since
 * BuildScaledSpriteQuad and BuildSizedSpriteQuad both carry one.
 *
 * The size argument is corroborated on the caller side even though none
 * of the six call sites is ported: each is a small fade-out effect draw
 * that looks up the same "CrashTexture" cache record, stamps its scale
 * floats, and then passes a per-site literal size in EAX with the
 * object's own [this+0x44] as the angle in EDX - see the analysis above.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall BuildSquareSpriteQuad(int param_1,int param_2,int param_3,int param_4,int param_5,int regEax)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int in_EAX = regEax;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  fVar3 = (float)-(in_EAX / 2);
  fVar4 = (float)(in_EAX / 2 + -1);
  iVar7 = (param_2 + 0x5a) % 0x168;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar7 * 4);
  param_2 = param_2 % 0x168;
  if (param_2 < 0) {
    param_2 = param_2 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + param_2 * 4);
  _DAT_00ea0e38 = (uint)param_5 << 0x18 | 0xffffff;
  _DAT_00ea0e94 = (float)param_3;
  DAT_00ea0e28 = _DAT_00ea0e94 + fVar2 * fVar3 + fVar1 * fVar3;
  fVar6 = (float)param_4;
  DAT_00ea0e2c = fVar6 + -(fVar2 * fVar3) + fVar1 * fVar3;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar1 * fVar4 + fVar2 * fVar3;
  fVar5 = fVar6 + -(fVar2 * fVar4);
  _DAT_00ea0e50 = fVar5 + fVar1 * fVar3;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * fVar4;
  DAT_00ea0e74 = fVar5 + fVar1 * fVar4;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * fVar3;
  _DAT_00ea0e98 = fVar6 + fVar1 * fVar4 + -(fVar2 * fVar3);
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
  puVar8 = &DAT_00ea0e28;
  puVar9 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  puVar8 = &DAT_00ea0e70;
  puVar9 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  puVar8 = &DAT_00ea0e28;
  puVar9 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

