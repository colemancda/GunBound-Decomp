/* FUN_00436ec0 - 0x00436ec0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls (4 C : 4 orig,
 * goto-free zip) - all plain globals.
 */
#include "ghidra_types.h"


void FUN_00436ec0(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    if (iVar3 % iVar2 < (int)(uint)(byte)(&DAT_005f2f54)[g_clientContext]) {
      pvVar4 = operator_new(0x50);
      if (pvVar4 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        FUN_00481e30();
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x38) = (iVar5 % 0x15 - iVar3) + param_1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x3c) = (iVar5 % 0x15 - iVar3) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x44) = iVar5 % iVar3;
      RegisterActiveObject(0, 0, (undefined4 *)0);
    }
  }
  return;
}

