/* CacheNicknameUserIdPair - 0x004260f0 in the original binary.
 *
 * Records one nickname <-> user-id pair in both lookup caches of the
 * client context: StringMap_SetAt_CString(key = EDI, ctx+0x6aa41c,
 * value = ESI) and StringMap_SetAt_CString(key = ESI, ctx+0x6aa44c,
 * value = EDI).  EDI is the 12-char nickname and ESI the 16-char user id
 * - the directions FindUserIdByNickname (reads +0x6aa41c) and
 * FindNicknameByUserId (reads +0x6aa44c) consume, i.e. the caches whose
 * misses trigger the 0x1020/0x1022 lookup requests.
 *
 * Which register holds which string comes from the call sites, both in
 * the incoming-packet dispatcher (WriteReplayEventRecord - the live
 * path that ProcessIncomingPackets runs every packet through, so this is
 * not replay-only): at 0x410657 (the 0x1021 arm) ESI = &[esp+0x44],
 * filled from payload+0xe and NUL-capped at +0x10 (0x410652), EDI =
 * &[esp+0x30], from payload+2 and capped at +0xc (0x410613) - the
 * [status][nickname:12][id:16] layout of GB_OP_USER_RESPONSE; at
 * 0x41078a (the 0x1023 arm, taken when the leading word is 0) the
 * record at payload+2 is [id:16][nickname:12] (caps at 0x410778 and
 * 0x410785) and the registers swap to match.  ProcessUserLookupResponse, called
 * from the same two arms, then repeats the same two upserts inline
 * while flushing the parked direct-link packets.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
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


void CacheNicknameUserIdPair(int regEax,undefined4 regEsi,undefined4 regEdi)

{
  
  StringMap_SetAt_CString(regEdi,&DAT_006aa41c + regEax,regEsi);
  StringMap_SetAt_CString(regEsi,&DAT_006aa44c + regEax,regEdi);
  return;
}

