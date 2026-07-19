/* State10_Loading_HandleChatInput - 0x0043e720 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void __thiscall State10_Loading_HandleChatInput(int *param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char acStack_80 [128];
  
  if (param_2 != 0x100) {
    return;
  }
  if (param_3 != 0xd) {
    return;
  }
  if (DAT_007933b8 != '\x01') {
    return;
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    FUN_0040c880();
    if ((acStack_80[0] != '\0') && (cVar2 = ParseChatSlashCommand(g_clientContext,acStack_80), cVar2 == '\0')) {
      cVar2 = CheckChatWordFilter(acStack_80);
      if (cVar2 == '\x01') {
        uVar4 = 0x202;
      }
      else {
        cVar2 = FUN_00415230();
        if (cVar2 == '\0') {
          QueueBroadcastEvent(1);
          pcVar3 = acStack_80;
          do {
            cVar2 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar2 != '\0');
          AppendBroadcastString(0,(int)pcVar3 - (int)acStack_80 - 1,(undefined4 *)acStack_80,
                                (int)&g_replayContext);
          BroadcastQueuedEvent();
          goto LAB_0043e820;
        }
        uVar4 = 0x205;
      }
      uVar6 = 6;
      uVar5 = 2;
      iVar1 = *param_1;
      uVar4 = GetLocalizedString(&g_localizedStringTable,uVar4);
      (**(code **)(iVar1 + 0x28))(uVar4,uVar5,uVar6);
    }
  }
  else {
    FUN_00426230();
  }
LAB_0043e820:
  SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
  return;
}

