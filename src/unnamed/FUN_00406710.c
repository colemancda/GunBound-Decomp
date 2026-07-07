/* FUN_00406710 - 0x00406710 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00406710(void)

{
  char cVar1;
  byte *in_EAX;
  char cVar2;
  byte *unaff_EDI;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((*in_EAX + in_EAX[1]) - 0x34) == in_EAX[2]) {
    cVar2 = '\x01' - ((in_EAX[1] >> (*in_EAX & 7) & 1) != 1);
  }
  else {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar2 = '\0';
  }
  if ((byte)((*unaff_EDI + unaff_EDI[1]) - 0x34) == unaff_EDI[2]) {
    cVar1 = '\x01' - ((unaff_EDI[1] >> (*unaff_EDI & 7) & 1) != 1);
  }
  else {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = '\0';
  }
  if ((cVar2 != '\0') && (cVar1 != '\0')) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return 1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return 0;
}

