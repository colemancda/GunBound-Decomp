/* AvatarStorePanel_OnMouseDown - 0x0050a1b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_0050a1b0). The word at
 * 0x557eb8+0x8 is 0x50a1b0, and vtable 0x557eb8 is stored only by
 * BuildAvatarStorePanel (at 0x509ea5); slots 4, 7 and 8 there are the
 * already-named AvatarStorePanel_HitTest / _OnCommand / _Draw. Slot 2
 * is CWidget::OnMouseDown(x, y) in src/cxx/Widget.h, and the body's
 * direct `call 0x505430` at 0x50a290 reaches the base CPanel::OnMouseDown
 * non-virtually, as an override of that slot would.
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
 *
 * GUARD CELLS RECOVERED (2026-10-30): the two PeekPacketChecksumBool
 * (0x4065a0) calls take their cell in EAX: `lea eax,[ebx+0x32c54]` at
 * 0x50a1f5 and `lea eax,[ebx+0x32e63]` at 0x50a208, EBX = puVar1. The two
 * QueueOutgoingPacketField (0x40a470) calls likewise take their cell in
 * EAX = ebx+0x228 (0x50a259, 0x50a2a7); the port passed only the value.
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
char PeekPacketChecksumBool(unsigned char *cell);
/* Row-at-point helper; x/y recovered 2026-08-28 - see
 * AvatarListRowHitTest.c (was FUN_0050cdb0.c). It is __fastcall there
 * (ECX widget, EDX x, ESI y at 0x50cdb0-0x50cdd0), so this declaration
 * must be too: a cdecl one names _AvatarListRowHitTest, which nothing
 * defines, instead of @AvatarListRowHitTest@12. */
int __fastcall AvatarListRowHitTest(int widget, int x, int y);
unsigned int QueueOutgoingPacketField(void *cell, unsigned int value);
void RefreshConnectionStatusLabel(void *this_);
void RadioGroup_RefreshEnableStates(int param_1, char regBl);
unsigned char __fastcall Widget_HitTestSelf(int param_1, int regEsi, int regEdi);
}

extern "C" unsigned int AvatarStorePanel_OnMouseDown(CPanel *this_, int x, int y)

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
    /* 0x50a1f5/0x50a208: lea eax,[ebx+0x32c54] / [ebx+0x32e63], ebx =
     * [0x5b3414] (puVar1) from 0x50a1b4. */
    uVar5 = (unsigned char)PeekPacketChecksumBool(puVar1 + 0x32c54);
    if ((char)uVar5 != '\x01') {
      uVar5 = (unsigned char)PeekPacketChecksumBool(puVar1 + 0x32e63);
      if ((char)uVar5 != '\x01' && (uVar5 = g_stateChangeInProgress, g_stateChangeInProgress == 0)) {
        iVar4 = AvatarListRowHitTest((int)this_, x, y);
        if (iVar4 != -1 &&
            (unsigned int)(*(int *)(puVar1 + 0x454) + iVar4) < *(unsigned int *)(g_clientContext + 0x44e24)) {
          /* 0x50a258-0x50a25f: push eax (row), lea eax,[ebx+0x228]. */
          QueueOutgoingPacketField(puVar1 + 0x228, iVar4);
          self[0x90] = 1;
          RefreshConnectionStatusLabel(this_);
          /* 0x50a271-0x50a274: push ebp (this), mov bl,1. */
          RadioGroup_RefreshEnableStates((int)this_, 1);
        }
        cVar2 = (char)Widget_HitTestSelf((int)this_, x, y);
        /* `call 0x505430` at 0x50a290: CPanel::OnMouseDown called
         * directly, not through the vtable. A virtual call would re-enter
         * CAvatarStorePanel::OnMouseDown, which forwards here. */
        cVar3 = this_->CPanel::OnMouseDown(x, y);
        if (cVar2 == '\0' && cVar3 == '\0') {
          /* 0x50a2a5-0x50a2ad: push -1, lea eax,[ebx+0x228]. */
          QueueOutgoingPacketField(puVar1 + 0x228, 0xffffffff);
          /* 0x50a2b2-0x50a2b5: push ebp (this), xor bl,bl. */
          RadioGroup_RefreshEnableStates((int)this_, 0);
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
