/* FUN_0045ec30 - 0x0045ec30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls (4 C : 4 orig,
 * goto-free zip).  All four hang off the live-in EAX object, which the
 * decompile already models as in_EAX and whose +0x4948/+0x292c cells
 * the existing CompareChecksumAtMost calls use.
 *
 * DROPPED-REG FIX (2026-08-28): that live-in EAX is now a real
 * parameter. It is the local player's MOBILE: every guard cell in the
 * function is an offset from it (+0x292c / +0x2708 / +0x2d74 / +0x2b50
 * and the +0x3604 / +0x33e0 / +0x3a4c / +0x3828 twin set, all compared
 * against +0x4948), the same object layout ComputeTurnDelay's EAX walks.
 *
 * Three binary sites, five source sites - the two extra are the C++ twin
 * CMobile::HandleFireInput in src/cxx/Mobile.cpp, which duplicates
 * State11_InBattle_HandleFireInput statement for statement and carries
 * its own file-local extern. In the binary the twins are one function,
 * which is why callsite_regs.py reports three.
 *
 * Both HandleFireInput sites pass EBP, and EBP is that function's
 * `this`: `mov ebp,ecx` at 0x45f93e is its only write to EBP anywhere in
 * 0x45f910..0x460fc4, and the function is __fastcall with param_1 in
 * ECX. State11_InBattle_HandleMouseInput passes
 * *(int *)(g_clientContext + 0x621e0) - `mov edx,[0x5b3484] / mov
 * eax,[edx+0x621e0]` at 0x4bb0ec - the same local-player mobile reached
 * another way.
 */
#include "ghidra_types.h"


undefined4 FUN_0045ec30(int regEax)

{
  char cVar1;
  int in_EAX = regEax;
  int iVar2;
  int iVar3;
  
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    cVar1 = PeekPacketChecksumBool();
    iVar2 = in_EAX + 0x4948;
    if (cVar1 == '\0') {
      cVar1 = CompareChecksumAtMost(in_EAX + 0x292c,iVar2);
      if ((cVar1 != '\0') && (cVar1 = CompareChecksumAtMost(iVar2,in_EAX + 0x2708), cVar1 != '\0')) {
        return 1;
      }
      cVar1 = CompareChecksumAtMost(in_EAX + 0x2d74,iVar2);
      if (cVar1 == '\0') {
        return 0;
      }
      iVar3 = in_EAX + 0x2b50;
    }
    else {
      cVar1 = CompareChecksumAtMost(in_EAX + 0x3604,iVar2);
      if ((cVar1 != '\0') && (cVar1 = CompareChecksumAtMost(iVar2,in_EAX + 0x33e0), cVar1 != '\0')) {
        return 1;
      }
      cVar1 = CompareChecksumAtMost(in_EAX + 0x3a4c,iVar2);
      if (cVar1 == '\0') {
        return 0;
      }
      iVar3 = in_EAX + 0x3828;
    }
    cVar1 = CompareChecksumAtMost(iVar2,iVar3);
    if (cVar1 == '\0') {
      return 0;
    }
    return 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(in_EAX + 0x42dc));
  iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x4948));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((iVar2 <= iVar3) && (cVar1 = CompareChecksumAtMost(in_EAX + 0x4948,in_EAX + 0x40b8), cVar1 != '\0')) {
    return 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(in_EAX + 0x4724));
  iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x4948));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((iVar2 <= iVar3) && (cVar1 = CompareChecksumAtMost(in_EAX + 0x4948,in_EAX + 0x4500), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

