/* ChatFlood_ExpireOldest - 0x00425770 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00425770 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: GameTick
 * calls it once per tick with g_clientContext, directly after the check
 * that reports a flood when the list count at ctx+0x67e3c8 exceeds 5
 * (string 0x141, or ShowErrorDialog 0x1a, then count = 0). It compares the
 * head timestamp at ctx+0x67e348 against GetTickCount, and once the head
 * has expired shifts the remaining entries down and decrements the count.
 * ChatFlood_RecordSend (0x425700) is the only writer that appends the
 * now+10000 timestamps, so this is the expiry side of that sliding window.
 * 'Flood' is inferred from the GameTick consumer.
 *
 * DROPPED REGISTER ARGUMENT: Ghidra failed to resolve the real parameter
 * and emitted every use of it as unaff_ESI, an uninitialized local. The
 * disassembly at the call site in GameTick (0x4133d6, `mov esi,
 * ds:0x5b3484` immediately before `call 0x425770` at 0x4133ee, with
 * nothing else touching esi in between) shows the caller passes
 * g_clientContext (was DAT_005b3484) in ESI - the same base used with
 * this exact &DAT_0067e3c8 offset elsewhere in GameTick.c. Promoted to a
 * real int parameter and the one call site updated to pass it.
 */
#include "ghidra_types.h"


void ChatFlood_ExpireOldest(int clientContext)

{
  int iVar1;
  DWORD DVar2;
  uint *puVar3;
  int iVar4;

  puVar3 = (uint *)(&DAT_0067e348 + clientContext);
  DVar2 = GetTickCount();
  if ((*puVar3 <= DVar2) && (iVar1 = *(int *)(&DAT_0067e3c8 + clientContext), iVar1 != 0)) {
    iVar4 = 0;
    if (iVar1 != 1 && -1 < iVar1 + -1) {
      do {
        *puVar3 = puVar3[1];
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar4 < *(int *)(&DAT_0067e3c8 + clientContext) + -1);
    }
    *(int *)(&DAT_0067e3c8 + clientContext) = *(int *)(&DAT_0067e3c8 + clientContext) + -1;
  }
  return;
}

