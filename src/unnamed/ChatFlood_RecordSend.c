/* ChatFlood_RecordSend - 0x00425700 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00425700 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body:
 * LobbyChatPanel_OnCommand calls it right after SendOutgoingPacket for the
 * 0x2010 channel-chat packet (GB_OP channelChatCommand). It appends
 * GetTickCount()+10000 to a list of up to 0x20 timestamps at ctx+0x67e348
 * with the count at ctx+0x67e3c8, and does nothing when the sender's own
 * nickname (ctx+0x23313, as in MessengerNotify_OnWhisper) matches the
 * operator-team name DAT_00551e24 or the string at 0x552c68, so the exempt
 * names bypass it. GameTick reads the same count: more than 5 entries
 * shows localized string 0x141 (or ShowErrorDialog 0x1a) and clears the
 * count, and ChatFlood_ExpireOldest drops entries once their 10 s expire.
 * That is a 5-messages-per-10-seconds chat limiter, so 'flood' is an
 * inference from that consumer, not a string in the binary.
 *
 * DROPPED REGISTER RECOVERED: ESI is g_clientContext.  Its sole call site,
 * at 0x00507801, loads it directly -- `mov esi,[0x5b3484]` immediately before
 * the call - but the function also proves it internally: it reaches the same
 * arena through BOTH spellings, `g_clientContext + 0x23313` on one line and
 * `&DAT_0067e3c8 + regEsi` on the next.  Two idioms for one base, in one
 * body, is stronger evidence than the call site alone.
 */
#include "ghidra_types.h"


void ChatFlood_RecordSend(int regEsi)

{
  int iVar1;
  DWORD DVar2;
  
  iVar1 = __stricmp((char *)(g_clientContext + 0x23313),DAT_00551e24);
  if (iVar1 != 0) {
    iVar1 = __stricmp((char *)(g_clientContext + 0x23313),&DAT_00552c68);
    if ((iVar1 != 0) && (*(int *)(&DAT_0067e3c8 + regEsi) < 0x20)) {
      DVar2 = GetTickCount();
      *(DWORD *)(&DAT_0067e348 + *(int *)(&DAT_0067e3c8 + regEsi) * 4 + regEsi) =
           DVar2 + 10000;
      *(int *)(&DAT_0067e3c8 + regEsi) = *(int *)(&DAT_0067e3c8 + regEsi) + 1;
    }
  }
  return;
}

