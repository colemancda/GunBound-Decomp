/* SendDirectLinkDeactivated - 0x00405b60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00405b60 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: The other
 * arm of the same WM_ACTIVATEAPP (0x1c) block in WndProc: called when
 * wParam == 0 on g_directLinkConnection, sending [len = 4 : u16][opcode
 * 0xa502 : u16] through SendSocketData under the same +0x2009 guard byte
 * as SendDirectLinkActivated (0x405b20, opcode 0xa500). Neither opcode is
 * in the reference server's Opcode.swift or include/opcodes.h, so the wire
 * meaning is inferred from the WM_ACTIVATEAPP arm only (focus lost). Note
 * the pair is 0xa500/0xa502, not consecutive. LIKELY.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely. Confirmed via
 * angr disassembly at 0x405b60-0x405b8d: ecx (param_1, this __fastcall
 * arg, never reassigned) is used directly as SendSocketData's "this" at
 * the call / `push edx` where edx=[ecx+0x2004] (connection object,
 * param_2) / `push 4` (length, param_3 - a literal, matching this file's
 * own `*(param_1+0x1000) = 4` write just above).
 */
#include "ghidra_types.h"


void __fastcall SendDirectLinkDeactivated(undefined2 *param_1)

{
  if (*(char *)((int)param_1 + 0x2009) != '\0') {
    *(undefined4 *)(param_1 + 0x1000) = 4;
    param_1[1] = 0xa502;
    *param_1 = param_1[0x1000];
    SendSocketData((char *)param_1,*(undefined4 *)(param_1 + 0x1002),4);
  }
  return;
}

