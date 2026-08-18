/* DrawSuperFlameEffect - 0x0047ead0 in the original binary.
 *
 * CSuperFlameEffect's vtable slot 3 (Draw; vtable 0x5560bc - see
 * src/cxx/Effects.h).  NEW CARVE (2026-08-18): Ghidra never carved this
 * range - reachable only through the effect vtable - hand-derived from the
 * capstone disassembly of 0x47ead0..0x47eb5d.
 *
 * The SuperShot flame twin of DrawFlameEffect, publishing into the
 * SEPARATE super-flame table block: slot = 3 - id (four slots, reverse
 * order), active byte at ctx+0x21714+slot, {x, y} at ctx+0x21718+slot*12,
 * phase at ctx+0x21720+slot*12 (the original spells that store as
 * ((slot*3)+0x85c8)*4).  Sheet/stride are PER SLOT here
 * (ctx+0x21624+slot*4 / ctx+0x21634+slot*4 - the same tables the plain
 * flames index by id>>2), and the blit passes the whole sheet (no cell
 * offset - FUN_0047e990 differs from FUN_00471b40 in exactly that).
 *
 * Phase selection matches DrawFlameEffect (fast-forward byte ctx+0x45578,
 * else the object's m_flags randomize toggle, else 0) - only the
 * store-vs-select ordering differs in the original's codegen.
 */
#include "ghidra_types.h"


void __thiscall DrawSuperFlameEffect(int param_1)

{
  int ctx;
  int slot;
  int sheet;
  int phase;

  ctx = g_clientContext;
  slot = 3 - *(int *)(param_1 + 8);
  sheet = *(int *)(ctx + slot * 4 + 0x21624);
  if (sheet == 0) {
    return;
  }
  *(char *)(ctx + slot + 0x21714) = 1;
  *(int *)(ctx + slot * 0xc + 0x21718) = *(int *)(param_1 + 0x38);
  *(int *)(ctx + slot * 0xc + 0x2171c) = *(int *)(param_1 + 0x3c);
  if (*(char *)(ctx + 0x45578) != 0) {
    phase = *(int *)(param_1 + 0x44);
  }
  else if (*(char *)(param_1 + 0x50) != 0) {
    phase = *(int *)(param_1 + 0x44);
  }
  else {
    phase = 0;
  }
  *(int *)(ctx + slot * 0xc + 0x21720) = phase;
  FUN_0047e990(*(uint *)(param_1 + 0x30), *(uint *)(param_1 + 0x18), sheet,
               *(int *)(ctx + slot * 4 + 0x21634));
  return;
}
