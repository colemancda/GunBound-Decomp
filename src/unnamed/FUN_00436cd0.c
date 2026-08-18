/* FUN_00436cd0 - 0x00436cd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: &DAT_00e9ba40 then &DAT_00e9bed8 (emitter family).
 */
#include "ghidra_types.h"


void __thiscall FUN_00436cd0(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    iVar2 = _rand();
    if ((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3 - iVar2 % 200 != 0 &&
        iVar2 % 200 <= (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3)) {
      pvVar3 = operator_new(0x50);
      if (pvVar3 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = FUN_004892c0();
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x38) = (iVar5 % 0x15 - iVar4) + param_2;
      iVar4 = _rand();
      *(int *)(iVar2 + 0x3c) = param_1 - iVar4 % 0x15;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x44) = iVar5 % iVar4;
      RegisterActiveObject(0, 0, (undefined4 *)0);
    }
  }
  return;
}

