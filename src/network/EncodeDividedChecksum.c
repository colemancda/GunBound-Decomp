/* EncodeDividedChecksum - 0x0040ab20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): the EncodeOutgoingPacketField call dropped self -
 * angr-confirmed (tools/encodeoutgoingpacketfield_sites.json, func_addr
 * 0x40ab20): `mov edi,ecx` immediately before the call, and param_1 is
 * this __fastcall function's own ECX arg - self is param_1 directly.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): BOTH operands were
 * dropped registers.  Ghidra kept the cell (0x40ab20's `mov edi,ecx` is this
 * __fastcall's param_1) but not the divisor, which arrives in EAX - hence the
 * `int in_EAX` artifact this file used to declare and read uninitialised.  The
 * divisor is now a real parameter and the peek names param_1.  All 9 call
 * sites pass both; note they are consecutive runs over six 0x224-stride cells
 * of the same object, which is a strong cross-check on the offsets.
 */
#include "ghidra_types.h"


undefined4 __fastcall EncodeDividedChecksum(undefined4 param_1,int divisor)

{
  int iVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState(param_1);
  if (divisor == 0) {
    divisor = 1;
  }
  EncodeOutgoingPacketField(param_1, iVar1 / divisor);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return param_1;
}

