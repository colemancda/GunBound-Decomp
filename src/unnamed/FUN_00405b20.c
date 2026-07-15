/* FUN_00405b20 - 0x00405b20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely. Confirmed via
 * angr disassembly at 0x405b20-0x405b4d: ecx (param_1, this __fastcall
 * arg, never reassigned) is used directly as SendSocketData's "this" at
 * the call / `push edx` where edx=[ecx+0x2004] (connection object,
 * param_2) / `push 4` (length, param_3 - a literal, matching this file's
 * own `*(param_1+0x1000) = 4` write just above).
 */
#include "ghidra_types.h"


void __fastcall FUN_00405b20(undefined2 *param_1)

{
  if (*(char *)((int)param_1 + 0x2009) != '\0') {
    *(undefined4 *)(param_1 + 0x1000) = 4;
    param_1[1] = 0xa500;
    *param_1 = param_1[0x1000];
    SendSocketData((char *)param_1,*(undefined4 *)(param_1 + 0x1002),4);
  }
  return;
}

