/* FUN_00425770 - 0x00425770 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT: Ghidra failed to resolve the real parameter
 * and emitted every use of it as unaff_ESI, an uninitialized local. The
 * disassembly at the call site in GameTick (0x4133d6, `mov esi,
 * ds:0x5b3484` immediately before `call 0x425770` at 0x4133ee, with
 * nothing else touching esi in between) shows the caller passes
 * g_clientContext (was DAT_005b3484) in ESI - the same base used with
 * this exact &DAT_0067e3c8 offset elsewhere in GameTick.c. Promoted to a
 * real int parameter and the one call site updated to pass it.
 */
#include "ghidra_types.h"


void FUN_00425770(int clientContext)

{
  int iVar1;
  DWORD DVar2;
  uint *puVar3;
  int iVar4;

  puVar3 = (uint *)(&DAT_0067e348 + clientContext);
  DVar2 = GetTickCount();
  if ((*puVar3 <= DVar2) && (iVar1 = *(int *)(&DAT_0067e3c8 + clientContext), iVar1 != 0)) {
    iVar4 = 0;
    if (iVar1 != 1 && -1 < iVar1 + -1) {
      do {
        *puVar3 = puVar3[1];
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar4 < *(int *)(&DAT_0067e3c8 + clientContext) + -1);
    }
    *(int *)(&DAT_0067e3c8 + clientContext) = *(int *)(&DAT_0067e3c8 + clientContext) + -1;
  }
  return;
}

