/* FUN_0040ab20 - 0x0040ab20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_0040ab20(undefined4 param_1)

{
  int in_EAX;
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  if (in_EAX == 0) {
    in_EAX = 1;
  }
  EncodeOutgoingPacketField(iVar1 / in_EAX);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return param_1;
}

