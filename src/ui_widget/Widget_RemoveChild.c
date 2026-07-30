/* Widget_RemoveChild - 0x0050e6c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGS FIX (2026-07-30): this whole function took no parameters
 * in the raw port, reading its real inputs as `unaff_ESI` (the parent
 * widget's child array, +0xc=data/+0x10=count) and `unaff_EDI` (the
 * specific child to remove) - both live-in registers at function entry
 * (confirmed via objdump, orig 0x50e6c0: `mov ecx,[esi+0x10]` is the
 * very first instruction, no prior write to esi or edi). Its sole
 * caller (RefreshConnectionStatusLabel.c, both call sites) resolves the
 * child pointer from `param_1[3][index]` and passes `param_1` itself as
 * the array (orig 0x50cf3d-0x50cf45: `mov ecx,[ebp+0xc]; mov
 * edi,[ecx+eax*4]; mov esi,ebp; call 0x50e6c0`). The inner
 * `WidgetChildArray_Destroy()` call was ALSO dropping its own arg -
 * `this`=the child being removed (`mov ecx,edi; call 0x50e560` at orig
 * 0x50e71e-0x50e720), not the parent array.
 */
#include "ghidra_types.h"


void Widget_RemoveChild(int *thisArray,void *child)

{
  void *_Dst;
  uint uVar1;
  uint uVar2;
  int iVar3;
  int unaff_ESI = (int)thisArray;
  void *unaff_EDI = child;

  uVar1 = *(uint *)(unaff_ESI + 0x10);
  uVar2 = 0;
  if (uVar1 == 0) {
    return;
  }
  do {
    if (uVar1 <= uVar2) {
LAB_0050e6ed:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    if (*(void **)(*(int *)(unaff_ESI + 0xc) + uVar2 * 4) == unaff_EDI) {
      if (uVar2 + 1 <= *(uint *)(unaff_ESI + 0x10)) {
        iVar3 = (*(uint *)(unaff_ESI + 0x10) - uVar2) + -1;
        if (iVar3 != 0) {
          _Dst = (void *)(*(int *)(unaff_ESI + 0xc) + uVar2 * 4);
          _memmove(_Dst,(void *)((int)_Dst + 4),iVar3 * 4);
        }
        *(int *)(unaff_ESI + 0x10) = *(int *)(unaff_ESI + 0x10) + -1;
        if (unaff_EDI == (void *)0x0) {
          return;
        }
        WidgetChildArray_Destroy((undefined4 *)unaff_EDI);
        _free(unaff_EDI);
        return;
      }
      goto LAB_0050e6ed;
    }
    uVar2 = uVar2 + 1;
    if (uVar1 <= uVar2) {
      return;
    }
  } while( true );
}
