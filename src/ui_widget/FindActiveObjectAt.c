/* FindActiveObjectAt - 0x0040cea0 in the original binary.
 *
 * Mouse-hit-test scan: walks `registry` (one of the two flat
 * active-object registries, DAT_00e9be90/DAT_00e9c0fc - NOT the
 * unrelated CWidget/CPanel tree in Widget.h) looking for a registered
 * object whose bounding box ([+0x38,+0x38+0x40) x [+0x3c,+0x3c+0x44))
 * contains (mouseX, mouseY). Returns the matching object, or 0.
 * PROMOTED 2026-07-13 (see globals.c/RegisterActiveObject.c): these
 * offsets line up with CButtonWidget's m_x/+0x38 and m_y/+0x3c
 * (ButtonWidget.h) - NOTE the +0x40/+0x44 extents this function reads
 * don't obviously match that header's m_unk40=h/m_unk44=w labeling
 * (paired the other way round here); worth double-checking against
 * ButtonWidget.cpp's field-write order when that class gets its next
 * pass, not resolved here.
 *
 * FIXED (2026-07-13): part of the 5-function mouse-hit-test family
 * (FindActiveObjectAt + its 4 callers HandleActiveObjectMouseDown/
 * HandleActiveObjectMouseUp/HandleActiveObjectMouseMove/
 * HandleBackgroundActiveObjectMouseDown, all under src/ui_widget/ -
 * see each file's own header). Ghidra's decompile dropped THREE of
 * this function's real inputs:
 * - `in_EAX` (the widget-tree root) - confirmed via objdump: the very
 *   first instruction (`mov ecx,[eax+4]`) reads EAX with no prior
 *   write, `ret` with no operand.
 * - `unaff_ESI` (mouseX) - same reasoning, ESI is live-in.
 * - the declared `param_1` (ECX, the fastcall's first slot) was never
 *   actually used anywhere in the body - dropped as dead.
 * `param_2` (EDX, mouseY) was the only one Ghidra got right.
 * All 4 callers were independently confirmed via their own disassembly
 * to receive (registry, mouseX, mouseY) as EAX/ESI-or-ECX/EDX at
 * their own entries and thread them straight through unmodified - see
 * each caller file's header for its own call-site trace. Promoted all
 * three to explicit stack parameters (dropping the always-unused
 * param_1/ECX slot) since MSVC 7.1 doesn't offer a >2-register fastcall
 * to preserve the original register shape - same approach used
 * throughout this session for other custom-register-convention drops.
 */
#include "ghidra_types.h"


int FindActiveObjectAt(void *registry,int mouseX,int mouseY)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int in_EAX = (int)registry;

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

