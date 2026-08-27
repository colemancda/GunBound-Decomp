/* FUN_004259d0 - 0x004259d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EDI RECOVERED (2026-08-26) at all 11 sites: the client context.  Nine sites
 * load it straight from g_clientContext; the other two arrive through
 * FUN_00425840 and FUN_004258e0, which forward their own dropped EAX, and
 * their single caller ParseChatSlashCommand passes its param_1 -- which every
 * one of ITS call sites fills with g_clientContext.  So the two indirect sites
 * carry the same value as the nine direct ones, by a longer road.
 */
#include "ghidra_types.h"


uint FUN_004259d0(uchar *param_1,int regEdi)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(&DAT_0067ec64 + regEdi);
  uVar3 = 0;
  if (0 < iVar1) {
    do {
      if (*(uint *)(&DAT_0067ec64 + regEdi) <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      iVar2 = __mbsicmp(*(uchar **)(*(int *)(&DAT_0067ec60 + regEdi) + uVar3 * 4),param_1);
      if (iVar2 == 0) {
        return uVar3;
      }
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < iVar1);
  }
  return 0xffffffff;
}

