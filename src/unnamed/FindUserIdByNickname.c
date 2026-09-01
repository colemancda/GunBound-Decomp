/* FindUserIdByNickname - 0x00426030 in the original binary.
 *
 * Looks the 12-char nickname up in the string map at ctx+0x6aa41c and,
 * on a hit, copies the mapped 16-char user id into param_1 and returns
 * 1.  Twin of FindNicknameByUserId (0x426090), which serves the reverse
 * map at ctx+0x6aa44c.  Which string is which is settled outside this
 * body:
 *
 * - Caller FUN_00402720's miss path sends opcode 0x1020
 *   (GB_OP 0x1020 = userRequest, the original SVC_USER_ID) whose whole
 *   payload is 12 bytes of this same key, and records an 'n'-prefixed
 *   pending entry (the FUN_004026a0 record family); its hit path writes
 *   the 16-byte value this returns into a direct-link 0xa110 frame as
 *   the recipient - the messenger addresses peers by the 16-char id
 *   (CBuddy2's rosters, strncpy 0x10 everywhere).
 * - The 0x1021 (GB_OP_USER_RESPONSE) handler FUN_00403000 reads
 *   [status:2][nickname:12][id:16], flushes the 'n'+nickname pendings
 *   with the id, and inserts both maps via FUN_00426620; the 0x1023
 *   list handler does the mirror with 'i'+id records.  The server's
 *   Username type fixes the nickname at 0xC bytes.
 * - ApplyBattleActionToContext's 0x8400 arm caches each synced player's
 *   16-byte (+0x23) and 12-byte (+0x33) strings into the same two maps.
 *
 * The interior StringMap_FindOrInsert_10 call (was FUN_004265c0); since the
 * preceding find already succeeded it only re-finds the node and yields
 * the value slot.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 FindUserIdByNickname(char *param_1,char *regEax,int regEcx)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_4,local_8,local_c,(int *)(regEcx + 0x6aa41c),(uchar *)regEax);
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)StringMap_FindOrInsert_10(regEax,(int *)(regEcx + 0x6aa41c));
    pcVar4 = (char *)*puVar3;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *param_1 = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
    return 1;
  }
  return 0;
}

