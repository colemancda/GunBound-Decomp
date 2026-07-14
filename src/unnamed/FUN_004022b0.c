/* FUN_004022b0 - 0x004022b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Dropped register argument: Ghidra read the object base as an
 * uninitialized `unaff_ESI` local instead of a real parameter. Called
 * unconditionally every GameTick from an otherwise argument-free call
 * site - confirmed via objdump at that call site (orig 0x4132c8-0x4132cd):
 * `mov esi,0xe53e88` immediately before `call 0x4022b0`, no other ESI
 * write in between. `&DAT_00e53e88` is the same object base already
 * used (opaquely, via wrapper calls) by ~25 other files (ParseChatSlashCommand.c,
 * WriteReplayEventRecord.c, State02/03/07/09/11's ProcessPacket.c, etc.) -
 * this function walks a `+4`-rooted sentinel list (matching the active-
 * object-registry LIST_ENTRY idiom used elsewhere) counting flagged nodes,
 * then writes the count to `+0xf24`. Promoted to an explicit `objBase`
 * parameter; see globals.c for the corresponding DAT_00e53e88 resize.
 */
#include "ghidra_types.h"


void FUN_004022b0(void *objBase)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar4 = 0;
  for (iVar2 = *(int *)(*(int *)((int)objBase + 4) + 0x1c); iVar2 != *(int *)((int)objBase + 4);
      iVar2 = *(int *)(iVar2 + 0x1c)) {
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (*(char *)(iVar3 + 0x30) != '\0') {
        iVar4 = iVar4 + 1;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
  *(int *)((int)objBase + 0xf24) = iVar4;
  return;
}

