/* ProcessIncomingWhisper - 0x00402300 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Sole call site is DispatchDirectLinkMessengerPacket's opcode-0xa100 arm
 * (the direct-link messenger/buddy connection's chat-line-relay opcode per
 * that function's own header), passing the direct-link messenger context
 * object (&DAT_00e53e88), the payload length, and the payload pointer.
 * The body copies a 12-byte sender-name record out of the payload, checks
 * it against FindMuteListIndex (the chat mute list) and the local
 * nickname, records it in the recent-whisper dedup table via
 * FindRecentWhisperIndex (FUN_004023b0 below) when not already present,
 * and unconditionally hands the sender name and message text to
 * DisplayIncomingWhisper - whose own already-committed header already
 * names this function ("FUN_00402300 (the 0xa100 path)") as the second of
 * its two real callers showing a received private message.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-24, workflow-analysed, hand-verified).
 * `ret 4`: param_1 is ECX (this), param_2 the one stack argument, and EAX
 * (`mov esi,eax` at entry) the payload pointer.  Sole call site 0x00411e46, a
 * cold block entered only by `je 0x411e3e` at 0x411b72 (the in_AX == 0xa100
 * case): ecx = &DAT_00e53e88, push esi = caller's EDX = its param_2 (the
 * length), eax = ebx = caller's ECX = its param_1 (the payload).  The port
 * had passed the length as `this`.
 */
#include "ghidra_types.h"


void __thiscall ProcessIncomingWhisper(int param_1,int param_2,int regEax)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_10 = *(undefined4 *)(regEax + 0x10);
  local_c = *(undefined4 *)(regEax + 0x14);
  local_8 = *(undefined4 *)(regEax + 0x18);
  local_4 = 0;
  iVar2 = FindMuteListIndex(&local_10, g_clientContext);
  if (iVar2 == -1) {
    iVar2 = __stricmp((char *)(param_1 + 0x1bb0),(char *)&local_10);
    if (iVar2 != 0) {
      iVar2 = FindRecentWhisperIndex(param_1,&local_10);
      if (iVar2 == -1) {
        pcVar3 = (char *)&local_10;
        pcVar4 = (char *)(*(int *)(param_1 + 0x15a8) * 0xd + 0xf28 + param_1);
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        *(int *)(param_1 + 0x15a8) = *(int *)(param_1 + 0x15a8) + 1;
      }
    }
    /* DROPPED-REG FIX 2026-08-28: the name is this function's own local
       record - `lea eax,[esp+0x18]` at 0x40239a, three pending pushes
       deep, reaches the local_10 the copy above just filled. */
    DisplayIncomingWhisper(param_1,regEax + 0x20,param_2 + -0x20,(char *)&local_10);
  }
  return;
}

