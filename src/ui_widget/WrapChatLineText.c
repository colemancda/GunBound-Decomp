/* WrapChatLineText - 0x0041b410 in the original binary.
 *
 * Renamed with confidence: this is the word-wrap helper ARCHITECTURE.md's
 * chat-pipeline writeup describes ("Word-wraps the message text into a
 * large scratch stack buffer before storing it") - called from both
 * AppendChatLogEntry.c (lobby/room chat) and FUN_0041ef90.c (in-battle
 * "AddChatLine"). Copies source text into `param_2`'s dest buffer one
 * character at a time, treating any high-bit-set byte as the lead byte
 * of a 2-byte DBCS/EUC-KR sequence (copied atomically), stripping bare
 * '\r'/'\n', and stopping once either the character budget (param_4) or
 * the byte-width budget (param_5, relative to the already-used offset
 * param_3) is exhausted - matching the "split across two history lines"
 * behavior AddChatLine's caller-side logic depends on (see below).
 *
 * Signature/purpose confirmed by behavior; still a raw/near-verbatim
 * Ghidra port otherwise - not yet hand-verified, and the source-text
 * pointer is dropped as `in_EAX` here (this project's dropped-register
 * class of bug, same as EncodeOutgoingPacketField/DrawHLine) - tracked
 * as part of the "13 confirmed calling-convention mismatches" cleanup;
 * not yet promoted to an explicit parameter. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall WrapChatLineText(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  char *in_EAX;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  uVar3 = 0;
  iVar4 = param_3 + 1;
  iVar2 = 0;
  while ((iVar4 < param_5 && (iVar2 < param_4))) {
    cVar1 = *in_EAX;
    pcVar5 = in_EAX + 1;
    iVar6 = iVar2 + 1;
    if (cVar1 == '\0') {
      *(undefined1 *)(uVar3 + param_2) = 0;
      return 0;
    }
    if (cVar1 < '\0') {
      if (param_5 < (int)(uVar3 + 2 + param_3)) {
        *(undefined1 *)(uVar3 + param_2) = 0;
        return uVar3;
      }
      *(char *)(uVar3 + param_2) = cVar1;
      *(char *)(uVar3 + 1 + param_2) = *pcVar5;
      uVar3 = uVar3 + 2;
      iVar4 = iVar4 + 2;
      iVar2 = iVar2 + 2;
      in_EAX = in_EAX + 2;
    }
    else {
      iVar2 = iVar6;
      in_EAX = pcVar5;
      if ((cVar1 != '\r') && (cVar1 != '\n')) {
        *(char *)(uVar3 + param_2) = cVar1;
        uVar3 = uVar3 + 1;
        iVar4 = iVar4 + 1;
      }
    }
  }
  *(undefined1 *)(uVar3 + param_2) = 0;
  return uVar3 & (param_4 <= iVar2) - 1;
}

