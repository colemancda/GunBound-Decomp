/* FUN_0050a030 - 0x0050a030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 4 argless sites.  EDI is set once before 0x50a073 to
 * puVar1 + 0x228 (puVar1 = g_gameStateVTableArray[7] = [0x5b3414], loaded
 * into EBX at 0x50a034) and is still live at 0x50a0a0, so C45 and C49 both
 * use it; C52 is `lea edi,[ebx + 4]` at 0x50a0b9, i.e. puVar1 + 4.  C60
 * (0x50a10f) is the store-catalog record idiom built at 0x50a0f2-0x50a0fe:
 * *(g_clientContext + 0x44e20) + <the selected index at self+0x94> * 0x450,
 * plus the in-record guard offset 0x22c.
 *
 * Because this is C++, the file-local extern declarations of
 * PeekPacketChecksumState / EncodeOutgoingPacketField had to gain the
 * `void *self` parameter as well -- an empty parameter list means "no
 * arguments" here, unlike in the .c ports.  Both remain __cdecl, so the
 * extra pushed argument is caller-cleaned and the behaviour is unchanged
 * until the guard-family prototype flip lands.
 *
 * Ported to C++ (2026-07-11) to call CWidget::MouseMoveChildren directly
 * instead of through the now-removed Widget_MouseMoveChildren shim - see
 * src/cxx/PLAN.md's "deduplicate C++-promoted functions" section. Same
 * pre-existing bug as FUN_0050d7a0.cpp: the raw C call site was passing
 * only 2 of the 3 real arguments (dropping `this`), tolerated only because
 * C's unprototyped calls don't check argument counts - passing `this_`
 * explicitly here is the correct behavior. Everything else (checksum
 * state, RadioGroup_RefreshEnableStates, FUN_004240c0) stays as plain
 * extern "C" calls into the existing .c tree.
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
unsigned int PeekPacketChecksumState(void *self);
void EncodeOutgoingPacketField(void *self, unsigned int field);
void RadioGroup_RefreshEnableStates(void *this_);
void ThrowCxxException(long hr);
unsigned int FUN_004240c0(unsigned int ctx, int a, int b, unsigned int c, int outRecord);
}

extern "C" int FUN_0050a030(CWidget *this_, int x, int y)

{
  unsigned char *puVar1;
  int iVar3;
  unsigned int uVar4;
  unsigned char *self = (unsigned char *)this_;

  puVar1 = (unsigned char *)g_gameStateVTableArray[7];
  if (*(char *)(self + 0x90) != '\0' && *(int *)(self + 0x94) == -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(puVar1 + 0x228));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(int *)(self + 0x94) = *(int *)(puVar1 + 0x454) + iVar3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(puVar1 + 0x228), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(puVar1 + 4), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RadioGroup_RefreshEnableStates(this_);
    if (*(unsigned int *)(g_clientContext + 0x44e24) <= *(unsigned int *)(self + 0x94)) {
      /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + *(int *)(self + 0x94) * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-08-11): dropped outRecord (ESI) - orig 0x50a13a-0x50a149
     * `mov esi,[esp+0x14]` (the state-7 object saved from EBX =
     * [0x5b3414] at 0x50a047, this C's puVar1) / `add esi,0x32fa0`. */
    FUN_004240c0(g_clientContext, (uVar4 & 0x8000) == 0x8000, (int)uVar4 >> 0x10, uVar4 & 0x7fff,
                 (int)(puVar1 + 0x32fa0));
  }
  bool consumed = this_->MouseMoveChildren(x, y);
  if (!consumed &&
      (this_->m_hidden != '\0' || x <= this_->m_x ||
       this_->m_width + this_->m_x <= x ||
       y <= this_->m_y || this_->m_height + this_->m_y <= y)) {
    return 0;
  }
  return 1;
}
