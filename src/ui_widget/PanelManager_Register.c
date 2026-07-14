/* PanelManager_Register - 0x0050eea0 in the original binary.
 *
 * __stdcall confirmed by the original's epilogue (`ret 0x4` on every
 * return path, callee cleans up its one 4-byte argument) - a plain
 * declaration here would default to __cdecl and leave a caller-side
 * stack-cleanup mismatch.
 *
 * FIXED (2026-07-14): `in_EAX` (the manager object) recovered for the
 * Panel.cpp call sites - confirmed via objdump at BuildWorldListPanel's
 * real call (orig 0x509ac4-0x509ac6: `mov eax,ebp` where ebp was loaded
 * from that function's OWN incoming `manager` argument at entry,
 * `mov ebp,[esp+0x18]`) - i.e. every C++ panel builder simply forwards
 * its own manager parameter through. Since this codebase has exactly one
 * panel-manager singleton (g_uiPanelManager), Panel.cpp's other 8 call
 * sites (whose own builder signatures don't currently thread a manager
 * parameter through - BuildChannelUserListPanel etc.) were updated to
 * pass `&g_uiPanelManager` directly rather than re-deriving it via each
 * builder's own params. The 8 separate raw-C callers under
 * src/ui_widget/ and src/unnamed/ (BuildItemTooltipPanel.c and
 * siblings) are NOT part of this g_uiPanelManager system and are left
 * unfixed/deferred - functions.h's K&R-empty declaration means they
 * keep under-supplying this new parameter exactly as they already did
 * for the object itself.
 */
#include "ghidra_types.h"


void __stdcall PanelManager_Register(void *manager,int param_1)

{
  int *piVar1;
  int in_EAX;
  int iVar2;

  in_EAX = (int)manager;
  piVar1 = (int *)(in_EAX + 4);
  if (*(char *)(param_1 + 5) == '\0') {
    iVar2 = PanelManager_PrependNode(piVar1,&param_1,*(undefined4 *)(in_EAX + 8),0);
    if (*(int **)(in_EAX + 8) != (int *)0x0) {
      **(int **)(in_EAX + 8) = iVar2;
      *(int *)(in_EAX + 8) = iVar2;
      return;
    }
    *piVar1 = iVar2;
    *(int *)(in_EAX + 8) = iVar2;
    return;
  }
  iVar2 = PanelManager_PrependNode(piVar1,&param_1,0,*piVar1);
  if (*piVar1 != 0) {
    *(int *)(*piVar1 + 4) = iVar2;
    *piVar1 = iVar2;
    return;
  }
  *(int *)(in_EAX + 8) = iVar2;
  *piVar1 = iVar2;
  return;
}

