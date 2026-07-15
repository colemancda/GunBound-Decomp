/* State10_Loading_AppendChatLine - 0x00442240 in the original binary.
 *
 * Renamed with confidence: vtable_State10_Loading's slot 10 - already
 * documented in ARCHITECTURE.md's "State10_Loading's render slot"
 * section as "not itself a render call - it's a small string-forwarding
 * helper (computes a string's length then calls AppendChatLogEntry, a
 * generic widget/label-text setter)".
 *
 * No confirmed real name/purpose beyond the above. Raw/near-verbatim
 * port of Ghidra's decompiler output, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void State10_Loading_AppendChatLine(char *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;

  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  AppendChatLogEntry(g_clientContext,param_2,0,0,param_1,param_3,0);
  return;
}
