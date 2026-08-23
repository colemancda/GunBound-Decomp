/* FUN_0045f840 - 0x0045f840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls - and both are
 * FOLDED TERNARIES.  Ghidra rendered each `cmp byte [rec+0x651c],1 /
 * jne` as an if/else whose two arms both call EnterCriticalSection and
 * then a single Peek, but in the binary each arm loads a DIFFERENT
 * cell into EAX before the shared call: equal -> &DAT_00796aa0 (first)
 * / &DAT_007949c8 (second), not-equal -> &DAT_00794e48 / &DAT_00e55ab8
 * (0x45f855-0x45f867, 0x45f8e0-0x45f8f8).  Written as the ternary on
 * the real `== 1` test.  Same idiom, same four cells, as the
 * FUN_0047c040/FUN_0047fad0 twins.
 */
#include "ghidra_types.h"


int FUN_0045f840(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  
  if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar2 = PeekPacketChecksumState((void *)(*(char *)(unaff_EBX + 0x651c) == '\x01' ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    iVar3 = PeekPacketChecksumState((void *)(*(char *)(unaff_EBX + 0x651c) == '\x01' ? (void *)&DAT_007949c8 : (void *)&DAT_00e55ab8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = iVar2 + iVar3;
  }
  return iVar2;
}

