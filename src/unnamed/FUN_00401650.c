/* FUN_00401650 - 0x00401650 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


void FUN_00401650(int *slot)

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

