/* FindNicknameByUserId - 0x00426090 in the original binary.
 *
 * Looks the 16-char user id up in the string map at ctx+0x6aa44c and,
 * on a hit, copies the mapped 12-char nickname into param_1 and returns
 * 1.  Byte-for-byte twin of FindUserIdByNickname (0x426030), which
 * serves the forward map at ctx+0x6aa41c; the direction evidence -
 * which string is the id and which the nickname - is laid out in that
 * file's header.  This side's own half of it: caller FUN_00403ae0's
 * miss path records an 'i'-prefixed pending entry and sends opcode
 * 0x1022 (GB_OP_USER_NICKNAME_REQUEST, the original SVC_USER_NICK)
 * carrying this same 16-char key, and the 0x1023 response lists
 * (id:16, nickname:12) records that FUN_00403000 flushes by 'i'+id and
 * inserts into both maps.
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


undefined4 FindNicknameByUserId(char *param_1,char *regEax,int regEcx)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_4,local_8,local_c,(int *)(regEcx + 0x6aa44c),(uchar *)regEax);
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)StringMap_FindOrInsert_10(regEax,(int *)(regEcx + 0x6aa44c));
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

