/* FUN_00425700 - 0x00425700 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED: ESI is g_clientContext.  Its sole call site,
 * at 0x00507801, loads it directly -- `mov esi,[0x5b3484]` immediately before
 * the call - but the function also proves it internally: it reaches the same
 * arena through BOTH spellings, `g_clientContext + 0x23313` on one line and
 * `&DAT_0067e3c8 + regEsi` on the next.  Two idioms for one base, in one
 * body, is stronger evidence than the call site alone.
 */
#include "ghidra_types.h"


void FUN_00425700(int regEsi)

{
  int iVar1;
  DWORD DVar2;
  
  iVar1 = __stricmp((char *)(g_clientContext + 0x23313),&DAT_00551e24);
  if (iVar1 != 0) {
    iVar1 = __stricmp((char *)(g_clientContext + 0x23313),&DAT_00552c68);
    if ((iVar1 != 0) && (*(int *)(&DAT_0067e3c8 + regEsi) < 0x20)) {
      DVar2 = GetTickCount();
      *(DWORD *)(&DAT_0067e348 + *(int *)(&DAT_0067e3c8 + regEsi) * 4 + regEsi) =
           DVar2 + 10000;
      *(int *)(&DAT_0067e3c8 + regEsi) = *(int *)(&DAT_0067e3c8 + regEsi) + 1;
    }
  }
  return;
}

