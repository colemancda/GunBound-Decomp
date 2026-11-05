/* FlushDirectLinkSendBuffer - 0x00405a20 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00405a20 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Stores the
 * fill cursor at buf + 0x2000 as the 16 bit length header at the start of
 * the buffer (*(u16 *)buf = buf[0x1000], i.e. the word at +0x2000) and
 * calls SendSocketData(buf, [buf + 0x2004], [buf + 0x2000]), sending
 * header plus appended payload to the socket stored at +0x2004. It is the
 * consumer of the buffer AppendDirectLinkSendBuffer (0x4059e0) fills, and
 * both are used only by DispatchDirectLinkPacket. LIKELY for the same
 * reason as the append half.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely. Confirmed via
 * angr disassembly at 0x405a20-0x405a38: ecx (param_1, this __fastcall
 * arg, never reassigned) is used directly as SendSocketData's "this" at
 * the call / `push eax` where eax=[ecx+0x2004] (connection object,
 * param_2) / `push edx` where edx=[ecx+0x2000] (length, param_3 - the
 * SAME value this file's existing code already read as its old,
 * mis-slotted 2nd argument).
 */
#include "ghidra_types.h"


void __fastcall FlushDirectLinkSendBuffer(undefined2 *param_1)

{
  *param_1 = param_1[0x1000];
  SendSocketData((char *)param_1,*(undefined4 *)(param_1 + 0x1002),
                 *(undefined4 *)(param_1 + 0x1000));
  return;
}

