/* DisplayIncomingWhisper - 0x00402400 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28, verb LIKELY): shows a private message received
 * from a peer. Both ported callers are receive arms handing a sender
 * name plus message text - DispatchDirectLinkPacket's opcode-0x1000
 * arm and FUN_00402300 (the 0xa100 path). After the ignore-list check
 * (FUN_004259d0 == -1 means not ignored) it formats
 * "<sender>> <message>" - the separator DAT_00551e34/DAT_00551e36 is
 * the literal bytes "> \0" in .data - appends that line to the rolling
 * 0x180-byte chat backlog (FUN_00426120's ring at &DAT_006aa47c), and
 * routes the raw text into the sender's CChatLogPanel: the panel
 * looked up by PanelManager_FindByName is keyed 0x4e21 = 20001, which
 * is BuildChatLogPanel's class - "the whisper/direct-message window"
 * per docs/widgets.md - and the name it matches on is this function's
 * own EBX = the SENDER (`mov ebx,eax` at 0x402416, read-only through
 * both lookup sites at 0x402577/0x4025a4). When the panel does not
 * exist yet, FUN_004025e0 builds the peer record and the panel
 * (BuildChatLogPanel), and 0x505900 finally appends (text, len) to it.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the sender NAME string - handed
 * to FUN_004259d0 for the ignore-list check and strcpy'd into the
 * 512-byte scratch this function formats into. Two of the three binary
 * sites are ported: FUN_00402300 passes the address of its own local
 * name record (`lea eax,[esp+0x18]` at 0x40239a, three pending pushes
 * deep = its local_10, the 13-byte name it just copied out of its
 * regEax record); DispatchDirectLinkPacket passes its regEax name
 * record via EDI - `mov edi,eax` at 0x4032d2 dominates the 0x40353c
 * block, whose only inbound edge is the `je 0x40353c` at 0x4032f4 taken
 * straight out of the opcode-0x1000 compare, before either later EDI
 * write. The third site, 0x403c6a, is in an unported PROGRESS.csv gap.
 */
#include "ghidra_types.h"


void DisplayIncomingWhisper(undefined4 param_1,char *param_2,uint param_3,char *regEax)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffdff;
  char cVar1;
  undefined2 *puVar2;
  char *in_EAX = regEax;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  undefined2 *puVar7;
  char *pcVar8;
  char local_200 [512];
  
  iVar3 = FUN_004259d0(in_EAX, g_clientContext);
  if (iVar3 == -1) {
    pcVar4 = in_EAX;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)(local_200 + -(int)in_EAX)] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    puVar2 = (undefined2 *)&stack0xfffffdff;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined2 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined2 *)((int)puVar7 + 1) = DAT_00551e34;
    pcVar4 = local_200;
    *(undefined1 *)((int)puVar7 + 3) = DAT_00551e36;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    pcVar6 = param_2;
    pcVar8 = pcVar4 + (int)(local_200 + -(int)(local_200 + 1));
    for (uVar5 = param_3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = param_3 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    pcVar4[(int)(local_200 + (param_3 - (int)(local_200 + 1)))] = '\0';
    FUN_00426120(local_200);
    iVar3 = PanelManager_FindByName((int)&g_uiPanelManager);
    if (iVar3 == 0) {
      FUN_004025e0(param_1,in_EAX);
      iVar3 = PanelManager_FindByName((int)&g_uiPanelManager);
      if (iVar3 == 0) {
        return;
      }
    }
    FUN_00505900(param_2,param_3);
  }
  return;
}

