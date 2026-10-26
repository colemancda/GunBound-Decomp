/* FindMuteListIndex - 0x004259d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Linear __mbsicmp scan over the array at g_clientContext+0x67ec60 with
 * count at g_clientContext+0x67ec64 - AtlArray_RemoveAt_CString.c's own
 * header independently identifies this exact array/stride/reader triple
 * as the client-side chat mute list from three directions (constructor,
 * destructor, and this reader agree on a char* element). Used directly by
 * AddMuteListEntry's "mute" arm, RemoveMuteListEntry's "loud" arm, and
 * ProcessIncomingWhisper's (FUN_00402300) ignore-list check, plus seven
 * more sites in battle/room packet handlers that all pass g_clientContext
 * as this function's second argument - the same array, queried wherever
 * a chat-visible name needs a mute check.
 *
 * (FUN_00425840/FUN_004258e0/FUN_00425960 are now AddMuteListEntry/
 * RemoveMuteListEntry/ClearMuteList.)
 *
 * EDI RECOVERED (2026-08-26) at all 11 sites: the client context.  Nine sites
 * load it straight from g_clientContext; the other two arrive through
 * FUN_00425840 and FUN_004258e0, which forward their own dropped EAX, and
 * their single caller ParseChatSlashCommand passes its param_1 -- which every
 * one of ITS call sites fills with g_clientContext.  So the two indirect sites
 * carry the same value as the nine direct ones, by a longer road.
 */
#include "ghidra_types.h"


uint FindMuteListIndex(uchar *param_1,int regEdi)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(&DAT_0067ec64 + regEdi);
  uVar3 = 0;
  if (0 < iVar1) {
    do {
      if (*(uint *)(&DAT_0067ec64 + regEdi) <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      iVar2 = __mbsicmp(*(uchar **)(*(int *)(&DAT_0067ec60 + regEdi) + uVar3 * 4),param_1);
      if (iVar2 == 0) {
        return uVar3;
      }
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < iVar1);
  }
  return 0xffffffff;
}

