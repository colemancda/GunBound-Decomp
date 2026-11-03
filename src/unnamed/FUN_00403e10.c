/* FUN_00403e10 - 0x00403e10 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is a
 * VTABLE SLOT, 0x551cdc = slot 9 of 0x551cb8, the notify interface the
 * buddy/messenger object installs at +8 (`mov [ebp+8],0x551cb8` at
 * 0x401948) and hands to CreateCommP2POwner. The same table holds the
 * already-ported twins FUN_00403ae0 (slot 5), FUN_00403d20 (slot 7) and
 * FUN_00404330 (slot 12), and this body has their shape exactly.
 *
 * EXTENT: 0x403e10-0x403f24 (277 bytes): both exits are `ret 0xc`
 * (0x403e64, 0x403f22), followed by int3 padding up to FUN_00403f30.
 *
 * CONVENTION: __thiscall. `mov ebp,ecx` at 0x403e24 reads ECX before any
 * write, and EBP is then used only as an object base - `lea ebx,[ebp+
 * 0x1bdc]` (0x403e85, the owner's +0x1be4 pending-action list, since
 * `this` is owner+8) and `lea ebx,[ebp-8]` (0x403f11, the owner). `ret 0xc`
 * is three stack words: at depth 0x40 `mov edi,[esp+0x44]` (0x403e37) is
 * param_2, the sender's 16-byte user id, and at depth 0x48 `mov edx,
 * [esp+0x54]` (0x403ef2) is param_4, the request text; param_3 is never
 * read. As for the twins, the erased __thiscall makes `this` the first
 * cdecl argument.
 *
 * BODY, from the disassembly:
 *   0x403e10-0x403e30  __stricmp(ctx+0x23313 (own nickname), 0x551e24 (the
 *                      EUC-KR operator-team name)); equal -> return, so the
 *                      operator account never sees buddy requests.
 *   0x403e3b-0x403e4f  FindNicknameByUserId(local_20, EAX = user id,
 *                      ECX = ctx); on success (AL == 1):
 *   0x403e51-0x403e5a  BuildBuddyRequestDialog(&g_uiPanelManager, EDI =
 *                      local_20 - the resolved nickname), then return.
 *                      This is BuildBuddyRequestDialog's third caller.
 *   0x403e67-0x403e8b  otherwise build "i" + user id in local_38 and ask
 *                      FUN_00404b00 (EBX = this+0x1bdc) whether a lookup
 *                      is already pending; if not (EAX == 0), 0x403e94-
 *                      0x403eed sends 0x1022 [u16 1][16-byte user id]
 *                      through g_connectionContextA (SendOutgoingPacket).
 *   0x403ef2-0x403f16  FUN_004026a0(0x2000, text, strlen(text)+1, EAX = user
 *                      id, EBX = this-8, CL = 0 - the strlen loop's last
 *                      byte), parking the request as action 0x2000 so
 *                      DispatchDirectLinkPacket's 0x2000 arm can open the
 *                      dialog once the nickname arrives.
 * So: the incoming buddy-request notification for a sender known only by
 * user id. Left unnamed like its slot-5/7/12 twins.
 *
 * NOT YET WIRED: the 0x551cb8 table (PTR_LAB_00551cb8) is still a NULL
 * placeholder in src/globals.c, as it is for the twins.
 */
#include "ghidra_types.h"


void __thiscall FUN_00403e10(int param_1,char *param_2,undefined4 param_3,char *param_4)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined1 local_38;
  char local_37 [23];
  undefined1 local_20 [32];

  iVar5 = __stricmp((char *)(g_clientContext + 0x23313),DAT_00551e24);
  if (iVar5 == 0) {
    return;
  }
  cVar3 = FindNicknameByUserId((char *)local_20,param_2,(int)g_clientContext);
  if (cVar3 == '\x01') {
    BuildBuddyRequestDialog((int)&g_uiPanelManager,(uchar *)local_20);
    return;
  }
  local_38 = 0x69;
  pcVar4 = param_2;
  do {
    cVar3 = *pcVar4;
    pcVar4[(int)(local_37 + -(int)param_2)] = cVar3;
    pcVar4 = pcVar4 + 1;
  } while (cVar3 != '\0');
  iVar5 = (int)FUN_00404b00(&local_38,(int *)(param_1 + 0x1bdc));
  iVar2 = g_connectionContextA;
  if (iVar5 == 0) {
    *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
    *(undefined2 *)(iVar2 + 0x4d6) = 1;
    iVar5 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar5 + 2;
    puVar1 = (undefined4 *)(iVar5 + 0x4d2 + iVar2);
    *puVar1 = *(undefined4 *)param_2;
    puVar1[1] = *(undefined4 *)(param_2 + 4);
    puVar1[2] = *(undefined4 *)(param_2 + 8);
    puVar1[3] = *(undefined4 *)(param_2 + 0xc);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 0x10;
    SendOutgoingPacket(iVar2);
  }
  pcVar4 = param_4;
  do {
    cVar3 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar3 != '\0');
  FUN_004026a0(0x2000,(undefined4 *)param_4,(uint)(pcVar4 - param_4),param_2,param_1 + -8,'\0');
  return;
}
