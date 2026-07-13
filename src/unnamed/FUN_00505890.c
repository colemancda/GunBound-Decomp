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
  int iVar2;

  if (*(char *)(param_1 + 0x1e) == '\0') {
    Widget_DrawSelf(param_1);
    iVar1 = 0x2a;
    iVar2 = 0;
    do {
      int iVar3;
      int index;
      iVar3 = *(int *)(param_1 + 0x1048);
      /* BlitRLESprite's dropped args recovered via objdump at 0x5058b0-
       * 0x5058dd (this function is at 0x00505890): ECX at the call is
       * `*(int*)(param_1+0x28) + 0x11` (the widget's own x field, +0x28,
       * per Widget_DrawSelf.c's identical field use, plus a fixed 0x11
       * offset) - constant across loop iterations, unlike RenderRoomLabel's
       * advancing cursor. EAX (rleData) is a pointer into a 40(0x28)-byte-
       * stride array based at param_1+0xa8, indexed by
       * (iVar3<0 ? iVar3 : 0) + iVar2 (iVar2 being this loop's running
       * iteration count, iVar3 read from param_1+0x1048 - a widget field
       * also touched by sibling FUN_00505900.c as a scroll/index bias). */
      index = (iVar3 < 0 ? iVar3 : 0) + iVar2;
      BlitRLESprite(*(int *)(param_1 + 0x28) + 0x11,*(int *)(param_1 + 0x2c) + iVar1,0xffff,
                    (byte *)(param_1 + 0xa8 + index * 0x28));
      iVar1 = iVar1 + 0xe;
      iVar2 = iVar2 + 1;
    } while (iVar1 < 0xfc);
  }
  return;
}

