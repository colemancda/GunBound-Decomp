/* FUN_004260f0 - 0x004260f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25) by uniformity: every call site in the original
 * loads the same value into it (`mov eax,[0x5b3484]`), so no site pairing is
 * needed -- there is nothing to match up, and the answer cannot be corrupted
 * by Ghidra's block reordering.  All 2 sites.  ESI and EDI here stay open.
 *
 * ESI and EDI RECOVERED (2026-08-25).  Both sites are in
 * WriteReplayEventRecord and they SWAP the two registers, so this one could
 * not be filled without pairing binary site to source line.  The witness is
 * the byte store immediately above each call: 0x410652 writes [esp+0x54] and
 * 0x410778/0x410785 write [esp+0x40] and [esp+0x50].  Under that function's
 * -0xd88 frame constant -- pinned independently by [esp+0x4c] = local_d3c and
 * [esp+0x50] = local_d38, which the two source lines above the first call
 * assign -- those are local_d34 for the first site and local_d48 for the
 * second, exactly the assignments the two source blocks make.
 *
 * So the first call gets ESI = &local_d44, EDI = &local_d58 and the second
 * gets them the other way round.
 */
#include "ghidra_types.h"


void FUN_004260f0(int regEax,undefined4 regEsi,undefined4 regEdi)

{
  
  FUN_00426620(regEdi,&DAT_006aa41c + regEax,regEsi);
  FUN_00426620(regEsi,&DAT_006aa44c + regEax,regEdi);
  return;
}

