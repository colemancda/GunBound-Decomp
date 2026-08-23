/* RenderJewel - 0x0047a960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls (5 C : 5 orig,
 * goto-free zip).  All five hang off the live-in ECX object (param_1):
 * +0x25c/+0x480/+0xaf0, then +0x38 twice.  Note the offsets differ from
 * the usual mobile-cell family - this object is a different class.
 */
#include "ghidra_types.h"


void __fastcall RenderJewel(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(g_clientContext + 0x23270);
  uVar3 = *(uint *)(param_1 + 8);
  iVar1 = *(int *)(g_clientContext + 0x23274);
  *(undefined1 *)(uVar3 + 0x23278 + g_clientContext) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x25c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)((*(int *)(param_1 + 8) + 9000) * 0x10 + g_clientContext) = uVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x480));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(*(int *)(param_1 + 8) * 0x10 + 0x23284 + g_clientContext) = uVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0xaf0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined4 *)(*(int *)(param_1 + 8) * 0x10 + 0x23288 + g_clientContext) = uVar2;
  uVar3 = uVar3 & 0x80000003;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
  }
  iVar4 = ((*(uint *)(param_1 + 8) >> 2) * iVar1 + uVar3 * 2) * 0x40 + iVar4;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_1 + 0x38));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FUN_004784a0(iVar4,iVar1);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_1 + 0x38));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FUN_004784a0(iVar1 * 0x80 + iVar4,iVar1);
  return;
}

