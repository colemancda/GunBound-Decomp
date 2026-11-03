/* FUN_00403ff0 - 0x00403ff0 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551ce0, SLOT 10 of the messenger's notify interface
 * 0x551cb8 (neighbours: slot 9 FUN_00403e10, slot 12 FUN_00404330).
 * DispatchP2PMessage dispatches it as `(listener,p4,cVar2 != 0)`. Extent
 * 0x403ff0-0x404136 (`ret 8` at 0x40407a-0x404080 and 0x404133, then int3).
 *
 * __thiscall, TWO stack words (`ret 8`): `mov ebp,ecx` (0x404007) = this
 * (the interface at ctx+8; `lea ebx,[ebp-8]` at 0x40411e is the context).
 * At depth 0x140 (sub 0x138 + push ebp + push edi) `mov edi,[esp+0x144]`
 * (0x40401a) is entry+4 = param_2, the 16-byte user id; at depth 0x144
 * (the pending push edx) `mov dl,[esp+0x14c]` (0x40403c) is entry+8 =
 * param_3, a flag byte.
 *
 * BODY:
 *   0x404001-0x404013  __stricmp(own nickname ctx+0x23313, 0x551e24);
 *                      equal -> return.
 *   0x404021-0x404035  FindNicknameByUserId(local_nick, EAX = id,
 *                      ECX = ctx); on success (AL == 1):
 *   0x404037-0x40407a  _sprintf(buf, GetLocalizedString(&g_localizedStringTable,
 *                      0xfa2 + (flag != 1)), nickname) then
 *                      BuildItemTooltipPanel(&g_uiPanelManager, buf)
 *                      (calls 0x43dc70, 0x5255de, 0x509030; the string ids
 *                      are 0xfa2/0xfa3, `setne al / add eax,0xfa2`);
 *   0x404083-0x404125  otherwise the unknown-sender path shared with
 *                      FUN_00403e10: build "i"+id, FUN_00404b00 on
 *                      this+0x1bdc, send 0x1022 [u16 1][id] through
 *                      g_connectionContextA unless already pending, then
 *                      FUN_004026a0(0x2001, &flag, 1, EAX = id,
 *                      EBX = ctx, CL = 0) - `push 1 / push &param_3 /
 *                      push 0x2001`, parking the flag byte as action
 *                      0x2001.
 * Purpose beyond this is not proven (the flag selects between two
 * localized strings 0xfa2/0xfa3). Left unnamed. Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void FUN_00403ff0(int param_1,char *param_2,char param_3)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined1 local_38;
  char local_37 [23];
  undefined1 local_20 [32];
  char local_buf [0xf0];

  iVar5 = __stricmp((char *)(g_clientContext + 0x23313),DAT_00551e24);
  if (iVar5 == 0) {
    return;
  }
  cVar3 = FindNicknameByUserId((char *)local_20,param_2,(int)g_clientContext);
  if (cVar3 == '\x01') {
    pcVar4 = (char *)GetLocalizedString(&g_localizedStringTable,(param_3 != '\x01') + 0xfa2);
    _sprintf(local_buf,pcVar4,local_20);
    BuildItemTooltipPanel(&g_uiPanelManager,local_buf);
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
  FUN_004026a0(0x2001,(undefined4 *)&param_3,1,param_2,param_1 + -8,'\0');
  return;
}
