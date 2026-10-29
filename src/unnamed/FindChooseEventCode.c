/* FindChooseEventCode - 0x00409c70 in the original binary.
 *
 * Looks a string up in the ChooseEvent.txt table and returns its integer
 * code, or -1 when absent: StringMap_Find_10 over the map, then the POD
 * value at node+4.  Which table and what the value means are settled by
 * the two ends of that table:
 *
 * - The sole call site (ParseChatSlashCommand, 0x422b31) pushes
 *   0xe9bea8 - DAT_00e9bea8, the map InitGame hands to
 *   LoadChooseEventConfig - with EBX = the typed command word, and on a
 *   hit shifts the result into the top byte of the field it queues for
 *   a 0x3101 (GB_OP_ROOM_CHANGE_OPTION_COMMAND) packet.
 * - LoadChooseEventConfig reads ChooseEvent.txt as `<number>\t<text>`
 *   lines: the number before the tab goes through _atol (0x409c04,
 *   result kept in EDI at 0x409c0c) and is what ParseChooseEventLine
 *   stores at node+4 under the text.  (The port of that loop passes
 *   local_f710 instead of the _atol result - an open port bug in
 *   LoadChooseEventConfig.c, not fixed here.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_00426780 below is now StringMap_Find_10.)
 *
 * PROMOTED (2026-09-01): was `(void)` but the original is `ret 4` with one
 * stack param (the hash table - EAX=[esp+0x10]=entry+4 at 0x409c78 feeds
 * FUN_00426780's table register) plus EBX live-in (the key string). The
 * interior FUN_00426780 call gains both as its promoted trailing args.
 */
#include "ghidra_types.h"


undefined4 FindChooseEventCode(int *param_1,uchar *regEbx)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000004;
  int iVar1;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar1 = StringMap_Find_10(local_4,local_8,&stack0x00000004,param_1,regEbx);
  if (iVar1 != 0) {
    return *(undefined4 *)(iVar1 + 4);
  }
  return 0xffffffff;
}

