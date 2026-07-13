/* FUN_004b3e00 - 0x004b3e00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Dropped register argument fix: Ghidra emitted the object pointer as
 * uninitialized `in_EAX` instead of a real parameter. Disassembly of the
 * only call site (GameTick, 0x413302-0x413307: `mov eax,0xe9b4e8` then
 * `call 0x4b3e00`) shows EAX is loaded with the address of global
 * DAT_00e9b4e8 immediately before the call - the same global whose address
 * is passed explicitly to the sibling function FUN_004b3e60 a few lines
 * later in GameTick.c (FUN_004b3e60(&DAT_00e9b4e8)), and FUN_004b3e60 uses
 * the identical byte offsets (0x322/0x328) into that struct. Promoted
 * in_EAX to a real `void *param_1` parameter and updated the call site.
 */
#include "ghidra_types.h"


void FUN_004b3e00(void *param_1)

{
  int iVar1;

  if (*(char *)((int)param_1 + 0x322) != '\0') {
    iVar1 = *(int *)((int)param_1 + 0x328) + *(int *)((int)param_1 + 0x324);
    *(int *)((int)param_1 + 0x328) = iVar1;
    if ((iVar1 == 600) && (*(int *)((int)param_1 + 0x324) == -10)) {
      *(undefined4 *)((int)param_1 + 0x324) = 0;
    }
    if ((*(int *)((int)param_1 + 0x328) == 800) && (*(int *)((int)param_1 + 0x324) == 10)) {
      *(undefined4 *)((int)param_1 + 0x324) = 0;
      *(undefined1 *)((int)param_1 + 0x322) = 0;
    }
  }
  return;
}

