/* AtlArray_GrowBuffer - 0x0050ed30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NEWLY DISCOVERED, NOT YET FIXED (2026-07-13): `in_EAX` (the requested
 * size) and `unaff_ESI` (the array `this`) are both live incoming
 * arguments, custom-register family (`this` in ESI, arg in EAX) -
 * already independently confirmed in src/cxx/AtlArray.h's
 * `CAtlArray::GrowBuffer`, which this raw port duplicates for the 3
 * remaining raw callers that haven't migrated to that C++ template
 * (`FUN_00415bc0.c`, `FUN_004d2130.c`, `State11_InBattle_OnTick.c` -
 * `Widget_AddChild.c` already has, hence only 3 callers remain here).
 * Fixing this function alone isn't enough - its signature change must
 * land atomically with all 3 callers or the build breaks. Confirmed
 * via objdump that `FUN_00415bc0.c`'s call site is clean (`this` =
 * its own already-named `param_1`, size = `param_1[1] + 1`), but the
 * other two callers have their OWN dropped-register `this` on top:
 * `FUN_004d2130.c`'s `in_EAX` (its own array `this`, confirmed via
 * objdump - same "this in EAX" family) has only 2 callers, one of which
 * (`State11_InBattle_ProcessPacket.c`, ~500 lines) would need its own
 * dedicated trace through a large, unrelated battle-packet handler to
 * find what array `FUN_004d2130(iVar6)`'s call site actually targets.
 * Deferred as its own pass rather than guessing at battle-state array
 * identity to unblock an unrelated ui_widget bug-hunting pass.
 */
#include "ghidra_types.h"


undefined4 AtlArray_GrowBuffer(void)

{
  uint in_EAX;
  void *pvVar1;
  uint uVar2;
  int *unaff_ESI;
  
  if (in_EAX <= (uint)unaff_ESI[2]) {
    return 1;
  }
  uVar2 = unaff_ESI[3];
  if (*unaff_ESI == 0) {
    if (in_EAX < uVar2) {
      in_EAX = uVar2;
    }
    pvVar1 = _malloc(in_EAX * 4);
    *unaff_ESI = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      unaff_ESI[2] = in_EAX;
      return 1;
    }
  }
  else {
    if (uVar2 == 0) {
      uVar2 = (uint)unaff_ESI[1] >> 3;
      if (uVar2 < 4) {
        uVar2 = 4;
      }
      else if (0x400 < uVar2) {
        uVar2 = 0x400;
      }
    }
    uVar2 = uVar2 + unaff_ESI[2];
    if (uVar2 <= in_EAX) {
      uVar2 = in_EAX;
    }
    pvVar1 = _malloc(uVar2 * 4);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*unaff_ESI,unaff_ESI[1] << 2);
      _free((void *)*unaff_ESI);
      *unaff_ESI = (int)pvVar1;
      unaff_ESI[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

