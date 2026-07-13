/* FUN_0040cea0 - 0x0040cea0 in the original binary.
 *
 * Mouse-hit-test scan: walks the widget tree rooted at `widgetRoot`
 * looking for a leaf whose bounding box ([+0x38,+0x38+0x40) x
 * [+0x3c,+0x3c+0x44)) contains (mouseX, mouseY). Returns the matching
 * widget, or 0.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family
 * (FUN_0040cea0 + its 4 callers FUN_00406120/FUN_00406170/FUN_004061e0/
 * FUN_0040ce50, all under src/unnamed/ - see each file's own header).
 * Ghidra's decompile dropped THREE of this function's real inputs:
 * - `in_EAX` (the widget-tree root) - confirmed via objdump: the very
 *   first instruction (`mov ecx,[eax+4]`) reads EAX with no prior
 *   write, `ret` with no operand.
 * - `unaff_ESI` (mouseX) - same reasoning, ESI is live-in.
 * - the declared `param_1` (ECX, the fastcall's first slot) was never
 *   actually used anywhere in the body - dropped as dead.
 * `param_2` (EDX, mouseY) was the only one Ghidra got right.
 * All 4 callers were independently confirmed via their own disassembly
 * to receive (widgetRoot, mouseX, mouseY) as EAX/ESI-or-ECX/EDX at
 * their own entries and thread them straight through unmodified - see
 * each caller file's header for its own call-site trace. Promoted all
 * three to explicit stack parameters (dropping the always-unused
 * param_1/ECX slot) since MSVC 7.1 doesn't offer a >2-register fastcall
 * to preserve the original register shape - same approach used
 * throughout this session for other custom-register-convention drops.
 */
#include "ghidra_types.h"


int FUN_0040cea0(void *widgetRoot,int mouseX,int mouseY)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int in_EAX = (int)widgetRoot;

  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  do {
    if (iVar2 == *(int *)(in_EAX + 4)) {
      return 0;
    }
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if ((((*(int *)(iVar3 + 0x38) < mouseX) &&
           (mouseX < *(int *)(iVar3 + 0x40) + *(int *)(iVar3 + 0x38))) &&
          (*(int *)(iVar3 + 0x3c) < mouseY)) &&
         (mouseY < *(int *)(iVar3 + 0x44) + *(int *)(iVar3 + 0x3c))) {
        return iVar3;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
  } while( true );
}

