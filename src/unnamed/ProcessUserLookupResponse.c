/* ProcessUserLookupResponse - 0x00403000 in the original binary.
 *
 * The messenger side of the two user-lookup responses: for each resolved
 * (nickname, user id) pair it flushes the direct-link packets that were
 * parked waiting for that lookup (FUN_00403170 over the RBTree at
 * messenger+0x1be4, which re-dispatches each through
 * DispatchDirectLinkPacket) and caches the pair in both
 * nickname<->user-id maps through StringMap_SetAt_CString.
 *
 * Its role comes from its callers and from the request side:
 * - Its only call sites are the 0x1021 and 0x1023 arms of the incoming-
 *   packet dispatcher (WriteReplayEventRecord, which ProcessIncomingPackets
 *   calls for every live packet - the replay write is a side job), at
 *   0x41072c and 0x41079c, with AX = the opcode and ECX = the payload.
 * - 0x1021 is GB_OP_USER_RESPONSE, the answer to the 0x1020 user-id
 *   request SendWhisperByNickname sends on a FindUserIdByNickname miss
 *   after parking an 'n'+nickname record; this function's 0x1021 arm
 *   reads [status:2][nickname:12][id:16] and flushes 'n'+nickname.
 * - 0x1023 is not in include/opcodes.h (the reference server has no
 *   packet for it), but it is the mirror: FindNicknameByUserId's caller
 *   parks 'i'+id records and sends 0x1022 (GB_OP_USER_NICKNAME_REQUEST);
 *   this arm walks a [count:2] list of (id:16, nickname:12) records and
 *   flushes 'i'+id.  (The dispatcher's own 0x1023 arm reads that same
 *   leading word as a status and caches one record only when it is 0 -
 *   the two disagree in the original too; ported as found.)  "Lookup" covers both directions; "UserResponse"
 *   alone would describe only the 0x1021 half.
 *
 * SIGNATURE RECOVERED (2026-10-29), with the rename.  `ret 4`:
 * ECX = the packet payload (`mov esi,ecx` at 0x40300d, then read as the
 * status/count word), one stack argument = the messenger object
 * (forwarded as FUN_00403170's first argument, which uses +0x1be4 of it),
 * and AX = the opcode (`movzx eax,ax; sub eax,0x1021` at 0x403003, read
 * before anything writes it) - promoted from Ghidra's in_AX to the
 * trailing regAx parameter.  Both call sites had passed only
 * &DAT_00e53e88, which landed in the PAYLOAD slot.  In the original both
 * are `mov eax,[ebp+0xc]` (the dispatcher's param_2, the opcode) /
 * `push 0xe53e88` / `mov ecx,esi` with ESI = `[ebp+0x10]` (its param_3,
 * the payload: loaded at 0x4105b9 and not rewritten on the path to
 * 0x41072c, reloaded at 0x41078f before 0x41079c).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __thiscall ProcessUserLookupResponse(ushort *param_1,undefined4 param_2,short regAx)

{
  int iVar1;
  short in_AX = regAx;
  uint uVar2;
  ushort *puVar3;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 uStack_30;
  undefined1 local_2f;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14;
  undefined1 local_13;
  
  if (in_AX == 0x1021) {
    if (*param_1 == 0) {
      local_40 = *(undefined4 *)(param_1 + 7);
      SUBFIELD(local_1c,1,undefined3) = (undefined3)*(undefined4 *)(param_1 + 3);
      local_1c = CONCAT31(SUBFIELD(local_1c,1,undefined3),(char)((uint)*(undefined4 *)(param_1 + 1) >> 0x18));
      uStack_3c = *(undefined4 *)(param_1 + 9);
      SUBFIELD(local_18,1,undefined3) = (undefined3)*(undefined4 *)(param_1 + 5);
      local_18 = CONCAT31(SUBFIELD(local_18,1,undefined3),(char)((uint)*(undefined4 *)(param_1 + 3) >> 0x18));
      local_14 = (undefined1)((uint)*(undefined4 *)(param_1 + 5) >> 0x18);
      uStack_38 = *(undefined4 *)(param_1 + 0xb);
      uStack_34 = *(undefined4 *)(param_1 + 0xd);
      local_20 = CONCAT31((int3)*(undefined4 *)(param_1 + 1),0x6e);
      local_13 = 0;
      uStack_30 = 0;
      FUN_00403170(param_2,&local_20,&local_40);
      iVar1 = g_clientContext;
      StringMap_SetAt_CString((int)&local_20 + 1,&DAT_006aa41c + g_clientContext,&local_40);
      StringMap_SetAt_CString(&local_40,&DAT_006aa44c + iVar1,(int)&local_20 + 1);
      return;
    }
  }
  else if (in_AX == 0x1023) {
    puVar3 = param_1 + 1;
    for (uVar2 = (uint)*param_1; uVar2 != 0; uVar2 = uVar2 - 1) {
      SUBFIELD(uStack_3c,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 2);
      uStack_3c = CONCAT31(SUBFIELD(uStack_3c,1,undefined3),(char)((uint)*(undefined4 *)puVar3 >> 0x18));
      SUBFIELD(uStack_38,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 4);
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),(char)((uint)*(undefined4 *)(puVar3 + 2) >> 0x18));
      local_20 = *(undefined4 *)(puVar3 + 8);
      SUBFIELD(uStack_34,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 6);
      uStack_34 = CONCAT31(SUBFIELD(uStack_34,1,undefined3),(char)((uint)*(undefined4 *)(puVar3 + 4) >> 0x18));
      uStack_30 = (undefined1)((uint)*(undefined4 *)(puVar3 + 6) >> 0x18);
      local_1c = *(undefined4 *)(puVar3 + 10);
      local_18 = *(undefined4 *)(puVar3 + 0xc);
      local_40 = CONCAT31((int3)*(undefined4 *)puVar3,0x69);
      local_2f = 0;
      local_14 = 0;
      puVar3 = puVar3 + 0xe;
      FUN_00403170(param_2,&local_40,&local_20);
      iVar1 = g_clientContext;
      StringMap_SetAt_CString(&local_20,&DAT_006aa41c + g_clientContext,(int)&local_40 + 1);
      StringMap_SetAt_CString((int)&local_40 + 1,&DAT_006aa44c + iVar1,&local_20);
    }
  }
  return;
}

