/* DropOldestChatLogEntry - 0x0041b840 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): its only two callers are in
 * AppendChatLogEntry (0x41b958, 0x41bb8d), both guarded by
 * `if (99 < ctx[0x3b980])` - the line counter has reached the 100-line
 * capacity - and both pass EAX = ebp = the context (AppendChatLogEntry's
 * param_1).  Afterwards AppendChatLogEntry writes the new line at index
 * ctx[0x3b980] again, so this is what makes room.  The body agrees with the
 * array layout ClearChatLog zeroes: each parallel array (9-byte names at
 * +0x3b984, 20-byte nicknames at +0x3bd08, kind bytes at +0x3c4d8, 0x80-byte
 * text at +0x3c53c, words at +0x3f73c) is moved down by one record (the
 * copy sources are the arrays plus 9/20/1/0x80/2), and the counter at
 * +0x3b980 is set to 99.
 */
#include "ghidra_types.h"


void DropOldestChatLogEntry(int regEax)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(regEax + 0x3b98d);
  puVar3 = (undefined4 *)(regEax + 0x3b984);
  for (iVar1 = 0xde; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
  *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)puVar2 + 2);
  puVar2 = (undefined4 *)(regEax + 0x3bd1c);
  puVar3 = (undefined4 *)(regEax + 0x3bd08);
  for (iVar1 = 0x1ef; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = (undefined4 *)(regEax + 0x3c4d9);
  puVar3 = (undefined4 *)(regEax + 0x3c4d8);
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
  *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)puVar2 + 2);
  puVar2 = (undefined4 *)(regEax + 0x3c5bc);
  puVar3 = (undefined4 *)(regEax + 0x3c53c);
  for (iVar1 = 0xc60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = (undefined4 *)(regEax + 0x3f73e);
  puVar3 = (undefined4 *)(regEax + 0x3f73c);
  for (iVar1 = 0x31; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
  *(undefined4 *)(regEax + 0x3b980) = 99;
  return;
}

