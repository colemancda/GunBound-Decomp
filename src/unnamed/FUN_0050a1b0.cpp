/* FUN_0050a1b0 - 0x0050a1b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at the one argless PeekPacketChecksumState() call (0x50a1d2): it is
 * [0x5b3414] + 0x325b0, i.e. puVar1 + 0x325b0 with puVar1 the state-7
 * object this function already loads on the line above.  Being C++, the
 * file-local extern declaration had to gain the `void *self` parameter
 * too -- an empty parameter list means "no arguments" here.  Still
 * __cdecl, so the extra pushed argument is caller-cleaned and behaviour is
 * unchanged until the guard-family prototype flip lands.
 *
 * Ported to C++ (2026-07-11) to call CPanel::OnMouseDown directly instead
 * of through the now-removed RadioGroup_OnMouseDown shim - see
 * src/cxx/PLAN.md's "deduplicate C++-promoted functions" section. Same
 * pre-existing bug as the other ports in this batch: the raw C call site
 * was passing only 2 of the 3 real arguments (dropping `this`), tolerated
 * only because C's unprototyped calls don't check argument counts -
 * passing `this_` explicitly here is the correct behavior. Everything
 * else stays as plain extern "C" calls into the existing .c tree,
 * unchanged from the raw port. `extraout_EAX` (Ghidra's name for a
 * register read back after a call whose return value it's aliasing) is
 * preserved as best-effort - the actual value only survives into the
 * final `& 0xffffff00` return path, which masks off the bit this
 * function's own logic sets, so its exact contents were already
 * effectively unverified in the raw port too.
 */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "../cxx/Widget.h"

extern "C" {
extern char *g_gameStateVTableArray[16];
extern unsigned int g_clientContext;
extern unsigned char g_valueGuardLock;
extern unsigned int g_stateChangeInProgress;
unsigned int PeekPacketChecksumState(void *self);
char PeekPacketChecksumBool();
/* Row-at-point helper; x/y recovered 2026-08-28 - see
 * AvatarListRowHitTest.c (was FUN_0050cdb0.c). */
int AvatarListRowHitTest(int widget, int x, int y);
unsigned int QueueOutgoingPacketField(unsigned int field);
void RefreshConnectionStatusLabel(void *this_);
void RadioGroup_RefreshEnableStates(void *this_);
unsigned char __fastcall FUN_005052b0(int param_1, int regEsi, int regEdi);
}

extern "C" unsigned int FUN_0050a1b0(CPanel *this_, int x, int y)

{
  unsigned char *puVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned char *self = (unsigned char *)this_;

  puVar1 = (unsigned char *)g_gameStateVTableArray[7];
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(puVar1 + 0x325b0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = iVar4 != 0;
  if (iVar4 == 0) {
    uVar5 = (unsigned char)PeekPacketChecksumBool();
    if ((char)uVar5 != '\x01') {
      uVar5 = (unsigned char)PeekPacketChecksumBool();
      if ((char)uVar5 != '\x01' && (uVar5 = g_stateChangeInProgress, g_stateChangeInProgress == 0)) {
        iVar4 = AvatarListRowHitTest((int)this_, x, y);
        if (iVar4 != -1 &&
            (unsigned int)(*(int *)(puVar1 + 0x454) + iVar4) < *(unsigned int *)(g_clientContext + 0x44e24)) {
          QueueOutgoingPacketField(iVar4);
          self[0x90] = 1;
          RefreshConnectionStatusLabel(this_);
          RadioGroup_RefreshEnableStates(this_);
        }
        cVar2 = (char)FUN_005052b0((int)this_, x, y);
        cVar3 = this_->OnMouseDown(x, y);
        if (cVar2 == '\0' && cVar3 == '\0') {
          QueueOutgoingPacketField(0xffffffff);
          RadioGroup_RefreshEnableStates(this_);
        }
        if (0x239 < x && x < 0x275 && 0x2b < y && y < 0x67) {
          puVar1[0x31484] = 1;
        }
        if (cVar3 == '\0' && cVar2 == '\0') {
          return 0;
        }
        return 1;
      }
    }
  }
  return uVar5 & 0xffffff00;
}
