/* AppendChatBacklog - 0x00426120 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): all three callers feed it one already
 * formatted, NUL-terminated chat line.  AppendChatLogEntry (0x41b948)
 * builds "<name><separator><text>" in a local buffer for message kinds 0
 * and 7 and hands it here before logging the line;
 * DisplayIncomingWhisper (0x402497) formats "<sender>> <message>" and
 * appends it here (its header already calls the destination the rolling
 * chat backlog); FUN_004024f0 (0x40256d) does the same with its own
 * buffer.  The destination is a context-relative field, not a global: EAX
 * is the client context at the two named callers (`mov eax,[0x5b3484]` at
 * 0x402492, `mov eax,ebp` = AppendChatLogEntry's param_1 at 0x41b946) and
 * ClientContext_Constructor zeroes the same bytes (ctx+0x6aa47c, length
 * word ctx+0x6aa5fc) when it builds the context.  The text is copied to the
 * end of the 0x180-byte buffer, a '\n' is stored after it, and when
 * length + text would exceed 0x180 the oldest bytes are shifted out first
 * (a sliding buffer, not a ring, despite the older note in
 * DisplayIncomingWhisper).
 *
 * Known defect, not fixed here: the context arrives in EAX but the port
 * reads it through an uninitialised in_EAX and the prototype lists only
 * the text; FUN_004024f0's EAX at 0x40256d is not yet traced.
 */
#include "ghidra_types.h"


void AppendChatBacklog(char *param_1)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = pcVar2 + (1 - (int)(param_1 + 1));
  pcVar3 = pcVar2 + *(int *)(&DAT_006aa5fc + in_EAX);
  if (0x180 < (int)pcVar3) {
    uVar4 = 0x180 - (int)(pcVar3 + -0x180);
    pcVar6 = pcVar3 + in_EAX + 0x6aa2fc;
    pcVar7 = &DAT_006aa47c + in_EAX;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    *(int *)(&DAT_006aa5fc + in_EAX) = *(int *)(&DAT_006aa5fc + in_EAX) - (int)(pcVar3 + -0x180);
  }
  pcVar3 = &DAT_006aa47c + in_EAX + *(int *)(&DAT_006aa5fc + in_EAX);
  for (uVar5 = (uint)pcVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)param_1;
    param_1 = param_1 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar5 = (uint)pcVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar3 = *param_1;
    param_1 = param_1 + 1;
    pcVar3 = pcVar3 + 1;
  }
  (&DAT_006aa47b)[(int)(pcVar2 + in_EAX + *(int *)(&DAT_006aa5fc + in_EAX))] = 10;
  *(char **)(&DAT_006aa5fc + in_EAX) = pcVar2 + *(int *)(&DAT_006aa5fc + in_EAX);
  return;
}

