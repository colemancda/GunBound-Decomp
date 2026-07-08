/* CreateScrollListWidget - 0x005080a0 in the original binary.
 *
 * Constructs a generic scroll-list widget (0x58-byte object, class vtable
 * PTR_LAB_00557e90) - the reusable scrollable list used by the server-select
 * WORLD LIST and the lobby buddy panel. Stores position/size and an item
 * count (passed in a register), and auto-creates its own two scroll-arrow
 * child buttons (18x18, above and below the track). Scroll state lives at
 * widget+0x38 (content total), +0x3c (page size), +0x40 (scroll position);
 * scrollbar drag is handled by ScrollListWidget_OnMouseDown/_OnMouseUp and the
 * mouse-move slot, arrow steps by the widget's scroll-step slot (FUN_0050f7c0,
 * not yet ported), all firing a 0x2000+position callback to the parent panel.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 *
CreateScrollListWidget(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            ,undefined4 param_6)

{
  int in_EAX;
  undefined4 *puVar1;
  undefined4 uVar2;
  int unaff_EDI;
  
  puVar1 = operator_new(0x58);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    *(undefined1 *)(puVar1 + 1) = 0;
    puVar1[2] = 0;
    *(undefined1 *)(puVar1 + 7) = 1;
    *(undefined1 *)((int)puVar1 + 0x1d) = 0;
    *(undefined1 *)((int)puVar1 + 0x1e) = 0;
    puVar1[8] = 4;
    puVar1[0xe] = 0xffffffff;
    puVar1[0xf] = 0;
    puVar1[0x10] = 0;
    *(undefined1 *)(puVar1 + 0x11) = 0;
    *(undefined1 *)((int)puVar1 + 0x45) = 0;
    *puVar1 = &PTR_LAB_00557e90;
  }
  puVar1[0xb] = param_3;
  puVar1[10] = param_2;
  puVar1[0xc] = param_4;
  puVar1[9] = 0;
  puVar1[0xd] = param_5;
  puVar1[0x15] = (in_EAX * 5 + 300) * 2;
  uVar2 = FUN_00507ee0(0,in_EAX * 10 + 0x259,0,0xffffffe4,0x12,0x12);
  FUN_0050e670(uVar2);
  uVar2 = FUN_00507ee0(1,in_EAX * 10 + 0x25a,0,param_5 + 10,0x12,0x12);
  FUN_0050e670(uVar2);
  puVar1[0xf] = param_6;
  puVar1[0xe] = unaff_EDI;
  if (unaff_EDI < 1) {
    FUN_0050e7d0(0);
    return puVar1;
  }
  FUN_0050e7d0(1);
  return puVar1;
}

