/* RescrambleGuardedBool - 0x00406530 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall RescrambleGuardedBool(undefined4 param_1)

{
  char cVar1;
  byte *in_EAX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((*in_EAX + in_EAX[1]) - 0x34) == in_EAX[2]) {
    cVar1 = '\x01' - ((in_EAX[1] >> (*in_EAX & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = '\0';
  }
  EncodeGuardedBool(cVar1,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return param_1;
}

