/* FUN_005056c0 - 0x005056c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): this two-line wrapper was losing BOTH of
 * its inputs. It ends in `ret 4` at 0x5056f5, so it takes one stack
 * argument, and its single caller FUN_00507310 already passes one - but
 * the port declared `(void)`, so that argument landed nowhere. It is the
 * text, loaded at 0x5056e7 by `mov esi,[esp+0xc]` with esi and edi
 * pushed, i.e. entry+4, and handed straight to TextEntry_SetControlText.
 *
 * EBX is a second, register-borne input: it is read at 0x5056c9
 * (`mov ecx,ebx`, Widget_FindChildIndex's receiver) and again at
 * 0x5056e4 (`mov ecx,[ebx+0xc]`) before anything writes it. It is the
 * container widget, and the child array at its +0xc is what the found
 * index selects: `mov edi,[ecx+eax*4]` at 0x5056eb builds
 * TextEntry_SetControlText's receiver out of it.
 *
 * At the call site in FUN_00507310 (0x50741c) EBX is the widget the
 * preceding list walk found - `mov ebx,[ecx+8]` at 0x507388, which is
 * that function's own `*piVar1`.
 *
 * Widget_FindChildIndex's own arguments stay dropped: its ECX is this
 * EBX, and it also reads ESI and EDI (0 and 2 here), but all 25 of its
 * call sites are argless and it needs its own pass.
 */
#include "ghidra_types.h"


void FUN_005056c0(char *param_1,int regEbx)

{
  uint uVar1;
  int unaff_EBX = regEbx;
  
  uVar1 = Widget_FindChildIndex();
  if (uVar1 != 0xffffffff) {
    if (*(uint *)(unaff_EBX + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    TextEntry_SetControlText(param_1,*(int *)(*(int *)(unaff_EBX + 0xc) + uVar1 * 4));
  }
  return;
}

