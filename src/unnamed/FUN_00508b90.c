/* FUN_00508b90 - 0x00508b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x508c64/0x508c8c/0x508ca9/0x508cd4
 * EBX = the new panel (`mov ebx,eax` at 0x508bd5, `xor ebx,ebx` at 0x508c0f), puVar5 here;
 * each call now passes it as regEbx.
 *
 * SEH ARTIFACT STRIPPED (2026-10-30): 0x508b90-0x508b9e links a C++ EH
 * frame (push -1 / push 0x53795b / mov eax,fs:[0] / push eax /
 * mov fs:[0],esp) and both exits unlink it (0x508c00-0x508c04 and
 * 0x508ce1-0x508ce7). Ghidra rendered that as writes through an
 * uninitialised unaff_FS_OFFSET; the handler LAB_0053795b is not part of
 * this decompile, so the link, the unlink and the try-state local are
 * removed, as in 7d662190.
 *
 * SetFocus `this` RECOVERED (2026-10-30): 0x508c6f-0x508c75 is
 * `mov eax,[esi] / push 1 / mov ecx,esi / call [eax]`, ESI = the
 * CreateTextEntryWidget result. That is a one-argument __thiscall on slot
 * 0 of the new CEditBox (vtable 0x557c84, slot 0 = 0x506fb0, which ends
 * in ret 4). CEditBox is a C++ class, so the call goes through a
 * __fastcall pointer with a dummy EDX: ECX = this, the flag on the stack,
 * callee-clean.
 */
#include "ghidra_types.h"

/* Slot 0 (+0x00) of a CWidget: SetFocus(bool), a one-argument __thiscall,
 * dispatched as __fastcall with a dummy EDX - see the header. */
typedef void (__fastcall *WidgetSetFocusFn)(void *thisPtr, int dummyEDX, int active);


void FUN_00508b90(int regEdi)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;

  puVar2 = *(undefined4 **)(regEdi + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0xa8);
      if (puVar2 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        Panel_BaseConstructor(puVar2);
        *puVar2 = &PTR_LAB_00557e68;
        puVar5 = puVar2;
      }
      puVar5[9] = 10000;
      puVar5[0x13] = 0;
      puVar5[0x11] = 0x2c6;
      puVar5[0x12] = 1;
      puVar5[10] = 0x119;
      puVar5[0xb] = 0xce;
      puVar5[0xc] = 0xf1;
      puVar5[0xd] = 0x94;
      puVar3 = (undefined4 *)CreateTextEntryWidget(0,0x32,0x58,0x8c,0xc,0xc);
      Widget_AddChild((int)puVar3,(int)puVar5);
      PanelManager_ClearAllFocus(regEdi);
      ((WidgetSetFocusFn)(*(void ***)puVar3)[0])(puVar3, 0, 1);
      uVar4 = CreateLabelWidget(0,0x2c8,0x42,0x6b,0x4a,0x1a);
      Widget_AddChild(uVar4,(int)puVar5);
      uVar4 = CreateLabelWidget(1,0x2c9,0x97,0x6b,0x4a,0x1a);
      Widget_AddChild(uVar4,(int)puVar5);
      uVar6 = 0xffff;
      uVar4 = GetLocalizedString(&g_localizedStringTable,4000);
      uVar4 = CreateStaticTextWidget(0x15,0x2d,200,0x1e,uVar4,uVar6);
      Widget_AddChild(uVar4,(int)puVar5);
      /* 0x508cd9-0x508cdc: push ebx (the panel), mov eax,edi (the manager). */
      PanelManager_Register((void *)regEdi,(int)puVar5);
      return;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 10000));
  /* 0x508bf8-0x508bfa: ECX = edi (the manager), EDX = the matched node's
   * panel, loaded by `mov edx,[ecx+8]` at 0x508bb5. */
  PanelManager_BringToFront(regEdi,*piVar1);
  return;
}

