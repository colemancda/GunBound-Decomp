/* ClearChatLog - 0x0041b7e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): AppendChatLogEntry (the writer of
 * these arrays) keeps the chat log as parallel per-line arrays hung off the
 * client context: +0x3b980 = line count, +0x3b97c = scroll/top line, +0x3b984
 * (9-byte sender-name slots), +0x3bd08 (20-byte nickname slots), +0x3c4d8
 * (one colour/kind byte per line), +0x3c53c (0x80-byte text lines), +0x3f73c
 * (one word per line).  This clears exactly those: the fills are 900, 2000,
 * 100, 12800 and 200 bytes = 100 lines x 9/20/1/128/2, and the two counters.
 * Callers are the lobby/room entry resets in
 * State03_GameRoomList_ProcessPacket (0x4271d3, 0x427a8f, each directly
 * beside ResetReplayContext) and WriteReplayEventRecord (0x410ddf, packet
 * 0x2001), i.e. a fresh room starts with an empty chat log.
 *
 * Calling convention: __fastcall with a phantom ECX and the context in EDX
 * (`mov edx,[0x5b3484] / call 0x41b7e0`; at 0x410ddf EDX is still edi =
 * g_clientContext, 0x41c230 does not touch it).  The three call sites used
 * to pass nothing; they now pass (0, g_clientContext).
 */
#include "ghidra_types.h"


void __fastcall ClearChatLog(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)(param_2 + 0x3b97c) = 0;
  *(undefined4 *)(param_2 + 0x3b980) = 0;
  puVar2 = (undefined4 *)(param_2 + 0x3b984);
  for (iVar1 = 0xe1; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3bd08);
  for (iVar1 = 500; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3c4d8);
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3c53c);
  for (iVar1 = 0xc80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x3f73c);
  for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

