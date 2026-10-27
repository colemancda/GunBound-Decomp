/* TokenizeChatCommandLine - 0x00421820 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. CopyChatCommandToken.c's own already-committed
 * header names this exact address directly (quoting that note): "The
 * chain is built in place by FUN_00421820 (0x421820), which overwrites
 * the leading '/' and every separating space with the length of the
 * token that follows." Confirmed by reading the body: it walks the
 * string in place converting each leading '/' or separating ' ' into
 * the byte-length of the token that follows ("/kick someone" becomes
 * [4]"kick"[7]"someone"), and returns the token count, which
 * ParseChatSlashCommand.c then uses as an argc.
 */
#include "ghidra_types.h"


int TokenizeChatCommandLine(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  
  cVar4 = '\0';
  iVar6 = 0;
  iVar2 = 1;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar5 = 1;
  if (1 < (int)pcVar3 - (int)(param_1 + 1)) {
    do {
      if (param_1[iVar5] == ' ') {
        param_1[iVar6] = cVar4;
        cVar4 = '\0';
        iVar2 = iVar2 + 1;
        iVar6 = iVar5;
      }
      else {
        cVar4 = cVar4 + '\x01';
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < (int)pcVar3 - (int)(param_1 + 1));
  }
  param_1[iVar6] = cVar4;
  return iVar2;
}

