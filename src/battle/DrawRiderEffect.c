/* DrawRiderEffect - 0x004a2a00 in the original binary.
 *
 * CRiderEffect's vtable slot 3 (Draw; vtable 0x5564bc - see
 * src/cxx/Effects.h).  NEW CARVE (2026-08-18): Ghidra never carved this
 * range - reachable only through the effect vtable - hand-derived from the
 * capstone disassembly of 0x4a2a00..0x4a2a6f.
 *
 * Publishes this rider into the eight-slot rider table (slot = id & 7):
 * active byte at ctx+0x20b0c+slot, then {x, y, facing} at
 * ctx + slot*0x10 + 0x20b14/0x20b18/0x20b1c.  The blit cell comes from a
 * 3-wide sheet whose row stride lives at ctx+0x1fe68 and whose base is
 * ctx+0x1fe64 (early-out when unset):
 *     cell = ((slot/3)*rowStride + (slot%3)*2) * 0x54 + base
 * blitted via FUN_004a27d0(spriteKey=+0x30, sortKey=0x14b4, cell,
 * rowStride) - the same key-walk blitter family as the flames', with the
 * rider's fixed 0x14b4 sort key instead of the flame's per-object
 * m_spriteBase.
 */
#include "ghidra_types.h"


void __thiscall DrawRiderEffect(int param_1)

{
  int ctx;
  int slot;
  int base;
  int rowStride;
  int cell;

  ctx = g_clientContext;
  slot = *(int *)(param_1 + 8) & 7;
  rowStride = *(int *)(ctx + 0x1fe68);
  base = *(int *)(ctx + 0x1fe64);
  if (base == 0) {
    return;
  }
  *(char *)(ctx + slot + 0x20b0c) = 1;
  *(int *)(ctx + slot * 0x10 + 0x20b14) = *(int *)(param_1 + 0x38);
  *(int *)(ctx + slot * 0x10 + 0x20b18) = *(int *)(param_1 + 0x3c);
  *(int *)(ctx + slot * 0x10 + 0x20b1c) = (uint)*(byte *)(param_1 + 0x40);
  cell = ((slot / 3) * rowStride + (slot % 3) * 2) * 0x54 + base;
  FUN_004a27d0(*(uint *)(param_1 + 0x30), 0x14b4, cell, rowStride);
  return;
}
