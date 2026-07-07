/* FUN_00507e30 - 0x00507e30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00507e30(void)

{
  if (DAT_007933b8 == '\0') {
    SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xc5,DAT_007933bc,0);
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),(LPCSTR)&DAT_007933c0);
    if (*(char *)(DAT_007934e4 + 8) != '\0') {
      SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xb1,DAT_007933bc,DAT_007933bc);
    }
    DAT_007933b8 = 1;
    return;
  }
  DAT_007933b8 = 1;
  return;
}

