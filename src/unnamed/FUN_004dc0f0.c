/* FUN_004dc0f0 - 0x004dc0f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the per-slot array at ctx+0x39d0c indexed by the live-in EDI slot number the C models as unaff_EDI (`imul eax,edi,0x224` at 0x4dc0ff) - FUN_00420600's twin.
 */
#include "ghidra_types.h"


int FUN_004dc0f0(void)

{
  int iVar1;
  int iVar2;
  int unaff_EDI;
  
  if (unaff_EDI == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x39d0c + unaff_EDI * 0x224));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = unaff_EDI + -1;
  if (iVar1 != 0xff) {
    iVar2 = unaff_EDI;
  }
  return iVar2;
}

