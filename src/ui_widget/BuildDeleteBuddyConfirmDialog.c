/* BuildDeleteBuddyConfirmDialog - 0x00508ea0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_00508ea0). Its one caller is
 * BuddyPanel_OnCommand on the buddy panel's "Del" label, id 2 (call at
 * 0x505d90), with EDI = the selected buddy's name (roster entry +0x21).
 * The text it shows is localized string 0xfa5 (push at 0x508fcb),
 * sprintf'd with that name; the reference client's Language.txt (inside
 * graphics.xfs) gives 4005 as "You are about to remove '%s' from buddy
 * list.\nAre you sure?". In the original vtable this builder stores
 * (0x557e40), slot 7 is 0x506430: label 0 calls FUN_00402cf0 with the
 * stored name (0x506456) and closes, label 1 only closes.
 *
 * NOTE: the port still installs the placeholder `&PTR_LAB_00557e40` (a
 * lone null in globals.c) as the vtable, not the original's 10 slots.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x508f86/0x508fa3/0x509005
 * EBX = esi, the new panel (`mov ebx,esi` at 0x508f84 and again at 0x509003 after the strlen reuses EBX), puVar3 here;
 * each call now passes it as regEbx.
 *
 * DROPPED ARGUMENTS RECOVERED (2026-10-30): the inline strlen at
 * 0x508fa8-0x508fbf leaves the name's length in EAX and `mov ebx,eax` at
 * 0x508fc3 passes it to AssignStringBuffer (0x4056c0, `test ebx,ebx` as
 * its first instruction) as the dropped EBX length. `push edi` at
 * 0x508fca, before the GetLocalizedString pushes, is the third argument
 * of the sprintf at 0x508fe0 (`add esp,0xc` at 0x508fe5).
 *
 * SEH ARTIFACT STRIPPED (2026-10-30): 0x508ea0-0x508eb2 links a C++ EH
 * frame (mov eax,fs:[0] / push -1 / push 0x53cf6e / push eax /
 * mov fs:[0],esp), unlinked at 0x509017-0x509020. The handler
 * LAB_0053cf6e is not part of this decompile, so the writes through the
 * uninitialised unaff_FS_OFFSET and the try-state local are removed, as
 * BuildBuddyRequestDialog already had them removed.
 */
#include "ghidra_types.h"


void BuildDeleteBuddyConfirmDialog(int param_1,uchar *regEdi)

{
  uchar uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uchar *puVar5;
  char *_Format;
  uint uVar6;
  char local_8c [128];

  puVar3 = *(undefined4 **)(param_1 + 4);
joined_r0x00508ec8:
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = operator_new(0xa8);
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      Panel_BaseConstructor(puVar3);
      *puVar3 = &PTR_LAB_00557e40;
    }
    puVar3[9] = 0x2712;
    puVar3[0x13] = 0;
    puVar3[0x11] = 0x2c6;
    puVar3[0x12] = 2;
    puVar3[10] = 0x12d;
    puVar3[0xb] = 0xd9;
    puVar3[0xc] = 200;
    puVar3[0xd] = 0x8a;
    uVar4 = CreateLabelWidget(0,0x2ca,0x44,0x66,0x37,0x1a);
    Widget_AddChild(uVar4,(int)puVar3);
    uVar4 = CreateLabelWidget(1,0x2cb,0x82,0x66,0x37,0x1a);
    Widget_AddChild(uVar4,(int)puVar3);
    /* The inline strlen leaves the length in EAX (0 for a NULL name), and
     * `mov ebx,eax` hands it to AssignStringBuffer as its EBX length. */
    uVar6 = 0;
    puVar5 = regEdi;
    if (regEdi != (uchar *)0x0) {
      do {
        uVar1 = *puVar5;
        puVar5 = puVar5 + 1;
      } while (uVar1 != '\0');
      uVar6 = (uint)(puVar5 - (regEdi + 1));
    }
    AssignStringBuffer(puVar3 + 0x14,regEdi,uVar6);
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,0xfa5);
    /* The name (EDI) is pushed before the GetLocalizedString call, so it
     * is _sprintf's third argument. */
    _sprintf(local_8c,_Format,regEdi);
    uVar4 = CreateStaticTextWidget(0x17,0x2b,0x9a,0x33,local_8c,0xffff);
    Widget_AddChild(uVar4,(int)puVar3);
    /* 0x50900a-0x509012: mov eax,[esp+0x9c] (param_1), push esi (the panel). */
    PanelManager_Register((void *)param_1,(int)puVar3);
  }
  else {
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
    if ((((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0x2712)) ||
        (*(int *)(iVar2 + 0x4c) != 0)) ||
       (iVar2 = __mbsicmp(*(uchar **)(iVar2 + 0x50),regEdi), iVar2 != 0))
    goto joined_r0x00508ec8;
  }
  return;
}

