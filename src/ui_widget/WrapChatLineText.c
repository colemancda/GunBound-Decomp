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
 * Ghidra port otherwise - not yet hand-verified. See src/README.md's
 * "Raw/verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the source-text pointer is EAX
 * (`mov esi,eax` at 0x41b41c), now the trailing regEax parameter, and
 * the four call sites were a RE-SLOT, not an append. The declared list
 * itself was right all along: param_1 is a PHANTOM (ECX's first touch
 * is the write `mov ecx,[esp+4]` at 0x41b410 - the same instruction
 * that reads param_3, whose +1 is the `inc ecx` the C models), param_2
 * is EDX = the DESTINATION (the per-row 0x80-stride message field),
 * and the three stack slots are offset / char budget / byte budget -
 * [esp+4] at entry, [esp+0x18] and [esp+0x1c] four saves deep, with
 * `ret 0xc` confirming exactly three. But the two AppendChatLogEntry
 * sites passed their three values as arguments ONE to THREE, so the
 * position expression landed in the phantom, the budget in the
 * destination, and the width in the offset; the two FUN_0041ef90 sites
 * passed nothing at all.
 *
 * The pairing witness is the split itself: at both callers the second
 * call's text is the first call's text plus its RETURN (the characters
 * consumed), and its char budget is the original minus the same value -
 * `add eax,edx` / `sub ebx,edx` at 0x41bbef/0x41bbe9 and
 * `lea eax,[esi+edx]` / `sub ebx,esi` at 0x41f187/0x41f181.
 */
#include "ghidra_types.h"


uint __fastcall WrapChatLineText(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,
                                 char *regEax)

{
  char cVar1;
  int iVar2;
  char *in_EAX = regEax;
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

