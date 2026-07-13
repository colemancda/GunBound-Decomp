/* FUN_00505890 - 0x00505890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00505890(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    Widget_DrawSelf(param_1);
    iVar1 = 0x2a;
    do {
      BlitRLESprite(0,*(int *)(param_1 + 0x2c) + iVar1,0xffff,(byte *)0);
      iVar1 = iVar1 + 0xe;
    } while (iVar1 < 0xfc);
  }
  return;
}

