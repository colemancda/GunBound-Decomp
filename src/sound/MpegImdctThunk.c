/* MpegImdctThunk - 0x00517d10 in the original binary.
 *
 * Thin 7-stack-argument wrapper that calls the Layer III IMDCT body at
 * 0x51b667.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x517d10: re-pushes all seven of its stack arguments
 * (loads from [esp+0x14..0x1c] in turn), does call 0x51b667, add esp,0x1c,
 * ret. It is not a bare jmp and it is ordinary cdecl. The target at
 * 0x51b667 is a mid-function body (push ebp / lea ebp,[esp+8] / pushal).
 * That body multiplies by the window table at 0xf25b00 (see
 * GetMpegImdctWindowTable), indexed by block type times 0x24 floats, and
 * adds the previous overlap buffer: the windowed IMDCT and overlap-add
 * stage. Five call sites, in four hybrid-synthesis variants: 0x514d76 (the
 * variant at 0x514cc0), 0x514bd9 (0x514b60), 0x514c89 (0x514c10) and
 * 0x514ea1 / 0x514f11 (0x514de0). The ones that reach their tail call
 * MpegFrequencyInversionThunk and then the synthesis callback, which is
 * the ISO order IMDCT, frequency inversion, polyphase. LIKELY: the 0x51b667
 * target itself is not yet renamed.
 */
#include "ghidra_types.h"


void MpegImdctThunk(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  FUN_0051b667(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

