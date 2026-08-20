/* NoOpMethodArg1 - 0x004038b0 in the original binary.
 *
 * A do-nothing virtual that pops ONE stack argument, referenced by 14
 * vtables.  NEW CARVE (2026-08-19): Ghidra never carved it - it is reachable
 * only through those vtables - and the whole function is a single
 * instruction, `ret 4` (0x4038b3 onward is int3 padding).
 *
 * It is the one-argument counterpart of NoOpMethod (0x429800), which is a
 * bare `ret` with no arguments; the two are NOT interchangeable, since
 * getting the pop wrong unbalances the caller's stack.  Named for that
 * distinction rather than for any behaviour - there is none.
 *
 * Raw/near-verbatim hand port - not hand-verified against a running client.
 * See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void __fastcall NoOpMethodArg1(int param_1,undefined4 param_2)

{
  return;
}
