/* DrawFlameEffect - 0x00471d00 in the original binary.
 *
 * CFlameEffect's vtable slot 3 (Draw; vtable 0x555ef0 - see
 * src/cxx/Effects.h).  NEW CARVE (2026-08-18): Ghidra never carved this
 * range as a function - it is reachable only through the effect vtable -
 * so this port is hand-derived instruction-by-instruction from the
 * capstone disassembly of 0x471d00..0x471dbd (no decompile existed).
 *
 * What it does: publishes this flame's state into the per-slot flame
 * tables inside the client context - active byte at ctx+0x21644+id,
 * {x, y, phase} triple at ctx+0x21654+id*12 - then blits the flame's
 * current cell.  The sprite sheet and frame stride live per GROUP of four
 * flames (ctx+0x21624+(id>>2)*4 / ctx+0x21634+(id>>2)*4), and the cell
 * within the sheet is picked by the flame's index within its group:
 * ((q/2)*stride + (q%2)*2) * 128 bytes, q = id & 3 (signed / and % - the
 * original uses cdq/sar and the sign-preserving and-0x80000001 idiom, kept
 * here as plain signed C which generates the same values for the small
 * non-negative ids involved).
 *
 * The phase written (and blitted) is m_animPhase when the fast-forward
 * byte ctx+0x45578 is set OR the object's own m_flags byte (+0x50, the
 * spawner's randomize toggle) is set; otherwise 0.
 *
 * __thiscall (this in ECX); erased to cdecl-with-this-arg like every raw
 * C port of a C++ method (the ghidra_types.h convention).
 */
#include "ghidra_types.h"


void __thiscall DrawFlameEffect(int param_1)

{
  int id;
  int ctx;
  int sheet;
  int stride;
  int phase;
  int q;
  int cell;

  id = *(int *)(param_1 + 8);
  ctx = g_clientContext;
  sheet = *(int *)(ctx + (id >> 2) * 4 + 0x21624);
  if (sheet == 0) {
    return;
  }
  *(char *)(ctx + id + 0x21644) = 1;
  *(int *)(ctx + id * 0xc + 0x21654) = *(int *)(param_1 + 0x38);
  *(int *)(ctx + id * 0xc + 0x21658) = *(int *)(param_1 + 0x3c);
  if (*(char *)(ctx + 0x45578) != 0) {
    phase = *(int *)(param_1 + 0x44);
  }
  else if (*(char *)(param_1 + 0x50) != 0) {
    phase = *(int *)(param_1 + 0x44);
  }
  else {
    phase = 0;
  }
  *(int *)(ctx + id * 0xc + 0x2165c) = phase;
  stride = *(int *)(ctx + (id >> 2) * 4 + 0x21634);
  q = id & 3;
  cell = ((q / 2) * stride + (q % 2) * 2) << 7;
  FUN_00471b40(*(uint *)(param_1 + 0x30), *(uint *)(param_1 + 0x18),
               sheet + cell, stride);
  return;
}
