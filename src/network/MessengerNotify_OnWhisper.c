/* MessengerNotify_OnWhisper - 0x00403c00 in the original binary.
 *
 * NAMING (batch 22, was FUN_00403c00): Slot 6 (+0x18) of the notify
 * interface 0x551cb8; DispatchP2PMessage calls it for types 0xc011 (mode
 * 0) and 0xc018 (mode 1), and it ends in DisplayIncomingWhisper or parks
 * the whisper as action 0x1000.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551cd0, SLOT 6 of the messenger's notify interface
 * 0x551cb8 (neighbours: slot 5 FUN_00403ae0, slot 7 FUN_00403d20). Extent
 * 0x403c00-0x403d0e (`ret 0x10` at 0x403c75 and 0x403d0e, then int3).
 *
 * __thiscall, FOUR stack words (`ret 0x10`): `mov ebx,ecx` (0x403c14) =
 * this (the interface at ctx+8; `add ebx,-8` at 0x403c62/0x403c78 gives
 * the context). Frame depth 0x24 at 0x403c26: `mov eax,[esp+0x2c]` is
 * entry+8 = param_3 (must be 0 or the function returns, 0x403c2c);
 * depth 0x2c at 0x403c34: `mov edi,[esp+0x30]` is entry+4 = param_2, the
 * sender's 16-byte user id; `mov edx,[esp+0x38]` (0x403c4e) is entry+0xc =
 * param_4, the text; the fourth word is never read.
 *
 * BODY:
 *   0x403c0e-0x403c20  __stricmp(own nickname ctx+0x23313, 0x551e24 the
 *                      operator-team name); equal -> return.
 *   0x403c26-0x403c2c  param_3 != 0 -> return.
 *   0x403c3c-0x403c4c  FindNicknameByUserId(local, EAX = id, ECX = ctx);
 *   0x403c4e-0x403c6a  on success DisplayIncomingWhisper(ctx, text,
 *                      strlen(text), EAX = the nickname)  [call 0x402400];
 *   0x403c78-0x403c85  otherwise HasPendingDirectLinkRecord(ctx, CL = 0,
 *                      EAX = id)  [call 0x403270, `push ebx` the context];
 *   0x403c89-0x403ce2  if none pending, queue 0x1022 [u16 1][16-byte id]
 *                      through g_connectionContextA (the same send as
 *                      FUN_00403d20 / FUN_00403e10);
 *   0x403ce7-0x403d03  park the whisper: FUN_004026a0(0x1000, text,
 *                      strlen(text)+1, EAX = id, EBX = ctx, CL = 0).
 * So: the incoming whisper notification for a sender known only by user
 * id. Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void MessengerNotify_OnWhisper(int param_1,char *param_2,int param_3,char *param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  undefined1 local_20 [32];

  iVar5 = __stricmp((char *)(g_clientContext + 0x23313),DAT_00551e24);
  if (iVar5 == 0) {
    return;
  }
  if (param_3 != 0) {
    return;
  }
  cVar3 = FindNicknameByUserId((char *)local_20,param_2,(int)g_clientContext);
  if (cVar3 == '\x01') {
    pcVar4 = param_4;
    do {
      cVar3 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar3 != '\0');
    DisplayIncomingWhisper(param_1 + -8,param_4,(uint)(pcVar4 - (param_4 + 1)),(char *)local_20);
    return;
  }
  if (!HasPendingDirectLinkRecord(param_1 + -8,0,param_2)) {
    iVar2 = g_connectionContextA;
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
  uVar6 = (uint)(pcVar4 - param_4);
  FUN_004026a0(0x1000,(undefined4 *)param_4,uVar6,param_2,param_1 + -8,'\0');
  return;
}
