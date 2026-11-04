/* FreeButtonDefinition - 0x00401650 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_00401650 in the notes below is this function's old symbol, now FreeButtonDefinition.)
 *
 * NAMED (2026-11-04), CERTAIN. Frees the 6-int button animation-state
 * descriptor that LoadButtonDefinitionFromXFS (0x401440) fills. That file
 * documents the layout from the original's allocations - entry[0] state
 * count, [1] malloc'd name pointers, [2] loop flags, [3] step counts, [4]
 * and [5] per-state frame and duration tables - and this body frees
 * exactly those: each name string and each per-state table, then the
 * arrays, zeroing the pointers. The five callers (the OnExit handlers of
 * states 2, 3, 7, 9 and 11) walk the flat slot array at client context +
 * 0x20004 with stride 0x18 (six ints) and call it once per slot before
 * zeroing the slot count, which is the lifetime pairing with the loader.
 * Memory is released and not otherwise destroyed, hence Free.
 *
 * FIXED (2026-07-13): `unaff_ESI` is a genuine incoming "this" register
 * (a flat-ButtonWidget slot record, 0x18 bytes), not garbage - confirmed
 * via objdump at every one of the 5 callers (each screen's OnExit),
 * e.g. State02_ServerSelect_OnExit at 0x4e18e7-0x4e18fe: `lea
 * esi,[ebp+0x20004]` then `call 0x401650` inside a loop that does `add
 * esi,0x18` each iteration - a genuinely per-iteration-varying pointer,
 * not a fixed global. This was completely dropped at the ALREADY-
 * PROMOTED C++ call site (src/cxx/State02_ServerSelect.cpp's OnExit),
 * which called `FUN_00401650()` with zero args on every loop iteration
 * - undefined behavior on every exit from the server-list screen
 * (freeing whatever garbage happened to be in ESI, repeatedly, instead
 * of each slot's own allocations). Promoted to an explicit parameter;
 * all 5 callers updated to pass the correct per-slot pointer.
 */
#include "ghidra_types.h"


void FreeButtonDefinition(int *slot)

{
  int iVar1;

  if (slot[1] != 0) {
    iVar1 = 0;
    if (0 < *slot) {
      do {
        _free(*(void **)(slot[1] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *slot);
    }
    _free((void *)slot[1]);
    slot[1] = 0;
  }
  if ((void *)slot[2] != (void *)0x0) {
    _free((void *)slot[2]);
  }
  slot[2] = 0;
  if ((void *)slot[3] != (void *)0x0) {
    _free((void *)slot[3]);
  }
  slot[3] = 0;
  if (slot[4] != 0) {
    iVar1 = 0;
    if (0 < *slot) {
      do {
        _free(*(void **)(slot[4] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *slot);
    }
    _free((void *)slot[4]);
    slot[4] = 0;
  }
  if (slot[5] != 0) {
    iVar1 = 0;
    if (0 < *slot) {
      do {
        _free(*(void **)(slot[5] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *slot);
    }
    _free((void *)slot[5]);
    slot[5] = 0;
  }
  return;
}

