/* FUN_004f3020 - 0x004f3020 in the original binary.
 *
 * BRING-UP BYPASS (stubbed to a no-op): walks an intrusive-list-of-lists
 * rooted at unaff_EBX (a list-header struct: [1]=head sentinel used as
 * [4]/[7] fields' terminator) - for each outer node, walks its own inner
 * list at [4], calling each inner node's own first field as a 1-arg
 * function (notify(1)), then resets the outer node's [3]/[4] links to
 * self (empties the inner list) and advances via [7].
 *
 * unaff_EBX arrives via a dropped EBX register whose VALUE DIFFERS per
 * call site - orig 0x41231f: `mov ebx, 0xe9be90` before ChangeGameState's
 * first call, orig 0x41232b: `mov ebx, 0xe9c0fc` before its second. Both
 * globals (DAT_00e9be90, DAT_00e9c0fc) are currently 1-byte scalars but
 * this function indexes them as an 8-word (32-byte) struct - the real
 * fix is resizing both. DAT_00e9be90 alone is passed as the "registry"
 * first argument to CreateButtonWidget from 60+ call sites across the
 * whole state-machine tree, so resizing it safely requires auditing all
 * of them; deferred per the standing minimal-bypass policy for changes
 * that touch a widely-shared existing global. Not required to reach the
 * server list: this is a per-state-transition listener notification/
 * cleanup pass, not state or rendering data itself.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3020(int unaff_EBX)

{
  (void)unaff_EBX;
  return;
}

