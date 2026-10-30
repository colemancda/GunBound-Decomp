/* RadioGroup_RefreshEnableStates - 0x0050cdf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-10-30): the body tests `bl` at 0x50ce1b with no
 * earlier write to EBX, and ends in ret 4 with only the panel on the
 * stack. BL is the "enable" flag: when it is nonzero and the panel's byte
 * +0x91 is clear, children 0, 2 and 3 are enabled; otherwise all four are
 * disabled. It is the trailing parameter regBl. The four callers load it
 * as `xor bl,bl` (0x50a0cd, 0x50a2b3), `mov bl,1` (0x50a272), or leave
 * the 0 from the failed `setne bl` test at 0x4476b7 (0x447724).
 */
#include "ghidra_types.h"


void RadioGroup_RefreshEnableStates(int param_1,char regBl)

{
  uint uVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    uVar1 = Widget_FindChildIndex(param_1,iVar3,1);
    if (uVar1 != 0xffffffff) {
      if (((*(char *)(param_1 + 0x91) == '\0') && (regBl != '\0')) && (iVar3 != 1)) {
        uVar2 = 1;
      }
      else {
        uVar2 = 0;
      }
      if (*(uint *)(param_1 + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      /* 0x50ce2f-0x50ce35: ECX = [ebp+0xc][eax*4], the found child. */
      Widget_SetEnabled(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4),uVar2);
    }
    iVar3 = iVar3 + 1;
    if (3 < iVar3) {
      return;
    }
  } while( true );
}

