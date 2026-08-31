/* FUN_00443610 - 0x00443610 in the original binary.
 *
 * An RB-tree (VC7 STL map) _Init: allocates the sentinel head node via
 * FUN_00443b60, marks it nil (+0x15 = 1), self-links its parent/left/
 * right to itself, stores it at this+4 and zeroes the size at this+8.
 *
 * DROPPED-REG FIX (2026-08-31): this arrives in ESI, promoted to
 * regEsi. Its only two binary callers are CRT static-initializer
 * thunks (0x541330 and 0x541350: `push esi / mov esi,<obj> / call /
 * atexit`), constructing two static map objects at 0xe9ca2c and
 * 0xe9ca38 that NO ported code references - so there is no C call
 * site to create and nothing to wire into the startup hook until a
 * consumer of those maps is ported.
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


void FUN_00443610(int regEsi)

{
  int iVar1;
  
  iVar1 = FUN_00443b60();
  *(int *)(regEsi + 4) = iVar1;
  *(undefined1 *)(iVar1 + 0x15) = 1;
  *(int *)(*(int *)(regEsi + 4) + 4) = *(int *)(regEsi + 4);
  *(undefined4 *)*(undefined4 *)(regEsi + 4) = *(undefined4 *)(regEsi + 4);
  *(int *)(*(int *)(regEsi + 4) + 8) = *(int *)(regEsi + 4);
  *(undefined4 *)(regEsi + 8) = 0;
  return;
}

