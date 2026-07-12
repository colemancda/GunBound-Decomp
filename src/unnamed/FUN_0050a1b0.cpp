/* FUN_0050a1b0 - 0x0050a1b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
extern unsigned char DAT_005a9068;
extern unsigned int g_stateChangeInProgress;
unsigned int PeekPacketChecksumState();
char PeekPacketChecksumBool();
int FUN_0050cdb0();
unsigned int QueueOutgoingPacketField(unsigned int field);
void RefreshConnectionStatusLabel(void *this_);
void RadioGroup_RefreshEnableStates(void *this_);
unsigned char FUN_005052b0();
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
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = iVar4 != 0;
  if (iVar4 == 0) {
    uVar5 = (unsigned char)PeekPacketChecksumBool();
    if ((char)uVar5 != '\x01') {
      uVar5 = (unsigned char)PeekPacketChecksumBool();
      if ((char)uVar5 != '\x01' && (uVar5 = g_stateChangeInProgress, g_stateChangeInProgress == 0)) {
        iVar4 = FUN_0050cdb0();
        if (iVar4 != -1 &&
            (unsigned int)(*(int *)(puVar1 + 0x454) + iVar4) < *(unsigned int *)(g_clientContext + 0x44e24)) {
          QueueOutgoingPacketField(iVar4);
          self[0x90] = 1;
          RefreshConnectionStatusLabel(this_);
          RadioGroup_RefreshEnableStates(this_);
        }
        cVar2 = (char)FUN_005052b0();
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
