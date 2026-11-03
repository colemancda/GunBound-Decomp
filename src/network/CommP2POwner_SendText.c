/* CommP2POwner_SendText - 0x004fd510 in the original binary.
 *
 * NAMING (batch 22, was FUN_004fd510): Slot 4 of vtable 0x5575c8. Its
 * callers (SendWhisperByNickname and the other DispatchDirectLinkPacket
 * text senders) call it through the listener slot, and DispatchP2PMessage
 * receives the matching 0xc011 (mode 0) / 0xc018 (mode 1) types at
 * MessengerNotify_OnWhisper (notify slot 6).
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word 0x5575d8 = SLOT 4 of the CommP2P owner vtable 0x5575c8 (read
 * from the original .data). Extent 0x4fd510-0x4fd58c (127 bytes; the last
 * `ret 0xc` is at 0x4fd58c, then int3 padding to FUN_004fd590).
 *
 * __thiscall with THREE stack words (`ret 0xc` at all three exits). With
 * no pushes yet, `mov edx,[esp+8]` (0x4fd521) is the SECOND argument, a
 * mode selector tested by `sub edx,0` / `dec edx`; after the three
 * register saves (depth 0xc) `mov ebx,[esp+0x10]` (0x4fd548) is the first
 * argument and `mov esi,[esp+0x18]` (0x4fd538) the third, a NUL-terminated
 * text (the strlen loop at 0x4fd541). Body: if the session flag
 * this+0x1a70 is clear return 0; mode 0 relays message type 0xc011
 * (`mov edi,0xc011`, 0x4fd57e), mode 1 type 0xc018 (0xc018, 0x4fd54f),
 * any other mode returns 0; the relay is FUN_004fcf10(text, strlen,
 * type) with EAX = this and EBX = the first argument. This is the
 * target-user text sender its callers SendWhisperByNickname /
 * FUN_00402900 reach through `call [edx+0x10]` (args: user id, 0, text).
 * Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


char CommP2POwner_SendText(int param_1,undefined4 param_2,int param_3,char *param_4)

{
  char *pcVar1;
  uint uLen;
  uint uType;

  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  if (param_3 == 0) {
    uType = 0xc011;
  }
  else if (param_3 == 1) {
    uType = 0xc018;
  }
  else {
    return 0;
  }
  pcVar1 = param_4;
  while (*pcVar1 != '\0') {
    pcVar1 = pcVar1 + 1;
  }
  uLen = (uint)(pcVar1 - param_4);
  return (char)FUN_004fcf10(param_4,uLen,uType,(int *)param_1,param_2);
}
