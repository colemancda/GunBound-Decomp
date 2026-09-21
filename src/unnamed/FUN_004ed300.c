/* FUN_004ed300 - 0x004ed300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG / EAX-FIRST FIX (2026-09-21). Disasm 0x4ed300-0x4ed322:
 * ECX and EAX are BOTH genuine incoming angle arguments feeding the
 * `(iVar6 + param_7 + 1) / 2` midpoint math (ECX=param_1, EAX=Ghidra's
 * `in_EAX`, never assigned before use). `ret` at 0x4ed591 is bare (no
 * operand) despite ECX carrying real data, matching this tree's
 * __thiscall-erased-to-plain-C convention exactly (caller cleans the 5
 * stack dwords, `add esp,0x14` at every call site) - so EAX is promoted
 * to a real trailing parameter (`param_7`), same idiom as
 * InitTextBoxWidget/BlitSpriteAttached (6e574c4a).
 *
 * All 4 call sites (State11_InBattle_Render.c) pass a min/max ANGLE pair
 * into ECX/EAX, computed from two just-clamped angle locals right before
 * the call (orig 0x4c73c8-0x4c7401 / 0x4c7788-0x4c7796 /
 * 0x4c82ca-0x4c82ec / 0x4c85b0-0x4c85d2: `cmp/mov/jg/mov/jl` computing
 * eax=max, ecx=min of the pair, both flags off ONE `cmp`). The buggy
 * 5-argument calls never computed this pair at all - instead they fed a
 * stale, unrelated local (a running screen-space Y accumulator: "iVar6"
 * at the first two sites, "iVar19" at the last two - both last assigned
 * several statements earlier as `<base> + <accumulator>`, then spilled
 * to a stack slot and reloaded at the real param_3 push, orig
 * 0x4c73f4/0x4c7796.."mov edx,[esp+0x30]"-style reload) into the ECX/
 * this slot. That stale value is exactly what param_3 (`DAT_00ea0e74 =
 * (float)param_3`, the Y coordinate) needs - it was simply plugged into
 * the wrong argument slot. Fixed at every site: param_1/param_7 are now
 * the freshly-computed min/max of the two clamped angle locals in scope
 * at each call, and the old first argument moved to param_3 (with
 * param_4/param_5/param_6 shifted out to their real positions - orig
 * push order confirms param_4=the +0x80/+0x84/+0x88 float-record
 * pointer, param_5=the 0x40 constant, param_6=the color/flag word).
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_004ed300(int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
            int param_7)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float local_8;
  
  iVar6 = param_1 + 1;
  iVar4 = (iVar6 + param_7 + 1) / 2;
  iVar5 = (iVar4 - iVar6) % 0x168;
  iVar3 = iVar5;
  if (iVar5 < 0) {
    iVar3 = iVar5 + 0x168;
  }
  fVar2 = (float)param_5;
  fVar1 = fVar2 * *(float *)(&g_sineTable360 + iVar3 * 4) *
          fVar2 * *(float *)(&g_sineTable360 + iVar3 * 4) + (float)(param_5 * param_5);
  if (fVar1 == 0.0) {
    local_8 = 0.0;
  }
  else {
    local_8 = (float)(((int)fVar1 + 0xc0800000U >> 1) + 0x3f800000 & 0x7f800000 |
                     DAT_006790c0[(uint)fVar1 >> 8 & 0xffff]);
  }
  iVar4 = iVar4 % 0x168;
  iVar3 = (iVar4 + 0x5a) % 0x168;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x168;
  }
  iVar4 = iVar4 % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  DAT_00ea0e70 = (float)param_2;
  DAT_00ea0e28 = *(float *)(&g_sineTable360 + iVar3 * 4) * local_8 + DAT_00ea0e70;
  DAT_00ea0e74 = (float)param_3;
  iVar3 = (param_1 + 0x5b) % 0x168;
  DAT_00ea0e2c = DAT_00ea0e74 - local_8 * *(float *)(&g_sineTable360 + iVar4 * 4);
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x168;
  }
  iVar6 = iVar6 % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  _DAT_00ea0e4c = fVar2 * *(float *)(&g_sineTable360 + iVar3 * 4) + DAT_00ea0e70;
  iVar3 = (param_7 + 0x5b) % 0x168;
  _DAT_00ea0e50 = DAT_00ea0e74 - fVar2 * *(float *)(&g_sineTable360 + iVar6 * 4);
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x168;
  }
  iVar4 = (param_7 + 1) % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  _DAT_00ea0e94 = fVar2 * *(float *)(&g_sineTable360 + iVar3 * 4) + DAT_00ea0e70;
  _DAT_00ea0e98 = DAT_00ea0e74 - fVar2 * *(float *)(&g_sineTable360 + iVar4 * 4);
  _DAT_00ea0e3c = *(undefined4 *)(param_4 + 0x80);
  _DAT_00ea0e84 = *(float *)(param_4 + 0x88) + *(float *)(param_4 + 0x80);
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0x168;
  }
  _DAT_00ea0e40 =
       _DAT_00557fb0 - *(float *)(&g_sineTable360 + iVar5 * 4) * *(float *)(param_4 + 0x88);
  DAT_00ea0e64 = *(float *)(param_4 + 0x84) + *(float *)(param_4 + 0x88);
  _DAT_00ea0ea4 = param_6;
  _DAT_00ea0e80 = param_6;
  _DAT_00ea0e5c = param_6;
  _DAT_00ea0e38 = param_6;
  puVar7 = &DAT_00ea0e28;
  puVar8 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e60 = _DAT_00ea0e3c;
  _DAT_00ea0e88 = DAT_00ea0e64;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = DAT_00ea0e64;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = &DAT_00ea0e70;
  puVar8 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar7 = &DAT_00ea0e28;
  puVar8 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

