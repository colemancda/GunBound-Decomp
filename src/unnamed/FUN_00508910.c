/* FUN_00508910 - 0x00508910 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x5089e4/0x508a0f/0x508a2c
 * EBX = the new panel (`mov ebx,eax` after operator new at 0x508955, `xor ebx,ebx` on failure at 0x50898f), puVar5 here;
 * each call now passes it as regEbx.
 *
 * SEH ARTIFACT STRIPPED (2026-10-30): 0x508910-0x50891e links a C++ EH
 * frame (push -1 / push 0x53795b / mov eax,fs:[0] / push eax /
 * mov fs:[0],esp) and both exits unlink it (0x508980-0x508984 and
 * 0x508a39-0x508a3f). Ghidra rendered that as writes through an
 * uninitialised unaff_FS_OFFSET; the handler LAB_0053795b is not part of
 * this decompile, so the link, the unlink and the try-state local are
 * removed, as in 7d662190.
 *
 * SetFocus `this` RECOVERED (2026-10-30): 0x5089ef-0x5089f5 is
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


void FUN_00508910(int regEdi)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;

  puVar2 = *(undefined4 **)(regEdi + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      if (puVar2 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        Panel_BaseConstructor(puVar2);
        *puVar2 = &PTR_LAB_00557dc8;
        puVar5 = puVar2;
      }
      puVar5[9] = 2;
      puVar5[0x13] = 0;
      puVar5[0x11] = 0x2714;
      puVar5[0x12] = 0;
      puVar5[10] = 0xf3;
      puVar5[0xb] = 0xca;
      puVar5[0xc] = 0x139;
      puVar5[0xd] = 0xa0;
      puVar3 = (undefined4 *)CreateTextEntryWidget(0,99,0x38,0xbe,0xc,4);
      Widget_AddChild((int)puVar3,(int)puVar5);
      PanelManager_ClearAllFocus(regEdi);
      ((WidgetSetFocusFn)(*(void ***)puVar3)[0])(puVar3, 0, 1);
      uVar4 = CreateLabelWidget(0,0x5dd,0xd5,0x76,0x52,0x22);
      Widget_AddChild(uVar4,(int)puVar5);
      uVar4 = CreateLabelWidget(1,0x5dc,0x80,0x76,0x52,0x22);
      Widget_AddChild(uVar4,(int)puVar5);
      /* 0x508a31-0x508a34: push ebx (the panel), mov eax,edi (the manager). */
      PanelManager_Register((void *)regEdi,(int)puVar5);
      return;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 2));
  /* 0x508978-0x50897a: ECX = edi (the manager), EDX = the matched node's
   * panel, loaded by `mov edx,[ecx+8]` at 0x508935. */
  PanelManager_BringToFront(regEdi,*piVar1);
  return;
}

