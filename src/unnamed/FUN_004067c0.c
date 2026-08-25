/* FUN_004067c0 - 0x004067c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH REGISTERS RECOVERED (2026-08-25).  Checks two 3-byte guard cells --
 * EAX the first, EDI the second (byte0 + byte1 - 0x34 == byte2) -- and
 * returns 1 if either decoded bit is set.  Both sites in
 * UpdateMobileEmotionState pass the mobile's cells at +0xbfbe and +0xbfc1.
 */
#include "ghidra_types.h"


undefined4 FUN_004067c0(byte *regEax,byte *regEdi)

{
  char cVar1;
  char cVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)((*regEax + regEax[1]) - 0x34) == regEax[2]) {
    cVar2 = '\x01' - ((regEax[1] >> (*regEax & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar2 = '\0';
  }
  if ((byte)((*regEdi + regEdi[1]) - 0x34) == regEdi[2]) {
    cVar1 = '\x01' - ((regEdi[1] >> (*regEdi & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar1 = '\0';
  }
  if ((cVar2 == '\0') && (cVar1 == '\0')) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    return 0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return 1;
}

