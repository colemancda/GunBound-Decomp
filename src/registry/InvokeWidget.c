/* InvokeWidget - 0x00406300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13): `in_EAX` and `unaff_ESI` were dropped-register
 * arguments - this is a real 2-argument function
 * `InvokeWidget(widgetId, enabled)`, not the previous 3-`param`
 * `__fastcall` shape (`param_1`/ECX was scratch, never read as input;
 * `param_2`/EDX was always literal 0 at every one of the ~100 call
 * sites found via an angr CFG backward-scan of every caller). EAX
 * (`DAT_00e9be90`, the flat-ButtonWidget registry root) is ALSO
 * invariant across every site - hardcoded here. ESI is the one real
 * per-caller value (the target widget's id within that registry) -
 * promoted to an explicit parameter and threaded through every call
 * site (see git log for the accompanying per-file fixes).
 *
 * Also fixed the same dropped-`this`-and-string-argument tail-call bug
 * already found/fixed in State02_ServerSelect_ProcessPacket.c/
 * ChangeGameState.c's `WidgetSetModeNameFn` calls: the 3
 * `(**(code**)(*piVar3+4))()` calls here are the SAME widget vtable
 * slot 1 (mode-name setter), called via `this` in ECX + a string arg
 * pushed onto the stack for a tail-call `jmp [ecx+4]` - confirmed via
 * objdump at 0x40633d-0x406347/0x40635d-0x406367/0x40636a-0x406374,
 * all three reusing the exact same idiom with a different string
 * literal each time (0x551e68/"disable", 0x551e58/"active",
 * 0x551e80/"ready").
 */
#include "ghidra_types.h"

typedef void (__fastcall *WidgetSetModeNameFn)(void *thisPtr, const char *modeName);

void InvokeWidget(int widgetId, int enabled)

{
  int iVar1;
  uint uVar2;
  int *piVar3;

  iVar1 = *(int *)(*(int *)((int)&DAT_00e9be90 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (0 < uVar2) {
      return;
    }
    if (uVar2 == 0) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  piVar3 = *(int **)(iVar1 + 0x10);
  uVar2 = piVar3[2];
  if ((uint)widgetId < uVar2) {
    return;
  }
  while (uVar2 != (uint)widgetId) {
    piVar3 = (int *)piVar3[4];
    uVar2 = piVar3[2];
    if ((uint)widgetId < uVar2) {
      return;
    }
  }
  if (enabled != 0) {
    if ((piVar3[9] != 3) && (piVar3[9] != -1)) {
      return;
    }
    if ((char)piVar3[0x13] == '\x01') {
      (*(WidgetSetModeNameFn *)(*piVar3 + 4))(piVar3, s_active_00551e58);
      return;
    }
    (*(WidgetSetModeNameFn *)(*piVar3 + 4))(piVar3, s_ready_00551e80);
    return;
  }
  (*(WidgetSetModeNameFn *)(*piVar3 + 4))(piVar3, s_disable_00551e68);
  return;
}
