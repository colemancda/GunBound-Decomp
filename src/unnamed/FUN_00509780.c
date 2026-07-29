/* FUN_00509780 - 0x00509780 in the original binary. Reached from
 * State03_GameRoomList_OnCommand's AVATAR button case when the inventory-
 * loaded checksum is already set: finds (or builds) a small "please wait /
 * loading" style panel (key 50000) and registers it.
 *
 * DROPPED-`ESI` FIX (2026-07-29): `unaff_ESI` was an uninitialised
 * register - confirmed via objdump at the sole call site
 * (State03_GameRoomList_OnCommand.c's case 3, orig 0x4286b5: `mov
 * esi,0xe53c40` = &g_uiPanelManager immediately before `call 0x509780`).
 * Promoted to an explicit parameter.
 *
 * SEH-PROLOGUE ARTIFACT FIX: same bug class as WidgetChildArray_Destroy.c/
 * FUN_00443c20.c - `unaff_FS_OFFSET` was an uninitialised pointer the body
 * wrote through (`*unaff_FS_OFFSET = &local_c;`), faulting on the very
 * first real statement after the dropped-ESI read - this was the crash
 * reproduced live the moment the AVATAR button's "already loaded" path
 * fired. Stripped per the entry/InitGame.c idiom (no __try/__except
 * frames), along with the (write-only, SEH-unwind-only) `local_4` marker.
 *
 * DROPPED-ARGUMENT FIX: `PanelManager_Register(puVar2)` only forwarded the
 * panel, dropping the manager. Orig 0x5098c5-0x5098c8: `push ebx` (=
 * puVar2, the panel) / `mov eax,esi` (= the same &g_uiPanelManager this
 * function's own now-recovered parameter holds) / `call 0x50eea0` -
 * manager and panel, matching PanelManager_Register's real two-parameter
 * signature (see that file's own header for the EAX/stack recovery).
 */
#include "ghidra_types.h"


void FUN_00509780(int esiArg)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;

  puVar2 = *(undefined4 **)(esiArg + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        Panel_BaseConstructor(puVar2);
        *puVar2 = &PTR_LAB_00557d78;
      }
      uVar4 = 0xffff;
      puVar2[9] = 50000;
      puVar2[0x13] = 0;
      puVar2[0x11] = 10000;
      puVar2[0x12] = 0x12;
      puVar2[10] = 0x115;
      puVar2[0xb] = 0xac;
      puVar2[0xc] = 0xf8;
      puVar2[0xd] = 0xf9;
      uVar3 = GetLocalizedString(&g_localizedStringTable,0x15e);
      uVar3 = CreateStaticTextWidget(0x14,0xf,0xd2,0xf,uVar3,uVar4);
      Widget_AddChild(uVar3);
      uVar4 = 0xffff;
      uVar3 = GetLocalizedString(&g_localizedStringTable,0x15f);
      uVar3 = CreateStaticTextWidget(0x14,0x32,0xce,0x8a,uVar3,uVar4);
      Widget_AddChild(uVar3);
      uVar3 = CreateLabelWidget(0,0x640,0x48,0xd0,0x51,0x21);
      Widget_AddChild(uVar3);
      uVar3 = CreateLabelWidget(1,0x641,0x9d,0xd0,0x51,0x21);
      Widget_AddChild(uVar3);
      PanelManager_Register((void *)esiArg, (int)puVar2);
      break;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 50000));
  return;
}

