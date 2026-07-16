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
 */
#include "ghidra_types.h"


undefined4 __fastcall EncodeDividedChecksum(undefined4 param_1)

{
  int in_EAX;
  int iVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  if (in_EAX == 0) {
    in_EAX = 1;
  }
  EncodeOutgoingPacketField(param_1, iVar1 / in_EAX);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return param_1;
}

