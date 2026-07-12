/* FUN_0050a030 - 0x0050a030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
unsigned int PeekPacketChecksumState();
void EncodeOutgoingPacketField(unsigned int field);
void RadioGroup_RefreshEnableStates(void *this_);
void ThrowCxxException(long hr);
unsigned int FUN_004240c0(unsigned int ctx, int a, int b, unsigned int c);
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
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(int *)(self + 0x94) = *(int *)(puVar1 + 0x454) + iVar3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RadioGroup_RefreshEnableStates(this_);
    if (*(unsigned int *)(g_clientContext + 0x44e24) <= *(unsigned int *)(self + 0x94)) {
      /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004240c0(g_clientContext, (uVar4 & 0x8000) == 0x8000, (int)uVar4 >> 0x10, uVar4 & 0x7fff);
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
