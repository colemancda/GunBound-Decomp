/* FUN_0050a320 - 0x0050a320 in the original binary.
 *
 * No confirmed real name/purpose - some CWidget-derived class's own
 * OnMouseUp override, tied to the Avatar Store state
 * (g_gameStateVTableArray[7]) via fields at this+0x90/+0x91/+0x94; not
 * yet attributed to a specific promoted C++ class or struct. Raw/near-
 * verbatim port of Ghidra's decompiler output, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * Ported to C++ (2026-07-11) to call CWidget::MouseUpChildren directly
 * instead of through the now-removed Widget_MouseUpChildren shim - see
 * src/cxx/PLAN.md's "deduplicate C++-promoted functions" section. Same
 * pre-existing bug as the other ports in this batch: the raw C call site
 * was passing only 2 of the 3 real arguments (dropping `this`), tolerated
 * only because C's unprototyped calls don't check argument counts -
 * passing `this_` explicitly here is the correct behavior. Everything
 * else is an unchanged, verbatim port of the raw C body (still using raw
 * offset arithmetic on `this_` for the not-yet-typed AvatarStore-specific
 * fields) - this function has no callers of its own in the raw C tree
 * (only reachable via vtable dispatch in the original), so no other files
 * needed touching.
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
int FUN_0050cdb0();
int FUN_00428550(void *buf);
void FUN_0044c740();
void FUN_0044c6a0(unsigned int ctx);
void FUN_0050cff0(unsigned int ctx, unsigned int idx, void *buf, int flag);
void FUN_0044b0b0(void *state);
void FUN_00426810(void *buf);
unsigned int PeekPacketChecksumState();
void EncodeOutgoingPacketField(unsigned int field);
void ThrowCxxException(long hr);
}

extern "C" int FUN_0050a320(CWidget *this_, int x, int y)

{
  unsigned int uVar1;
  char *puVar2;
  int iVar4;
  int iVar5;
  int iVar6;
  unsigned int uVar7;
  int uVar8;
  unsigned int local_468;
  unsigned char local_45c[1104];
  int local_4;
  unsigned char *self = (unsigned char *)this_;

  local_4 = -1;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053cf4d) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar2 = g_gameStateVTableArray[7];
  uVar7 = *(unsigned int *)(self + 0x94);
  if (uVar7 != 0xffffffff) {
    uVar1 = *(unsigned int *)(g_gameStateVTableArray[7] + 0x454);
    iVar4 = FUN_0050cdb0();
    local_468 = iVar4 + uVar1;
    if (local_468 == 0xffffffff &&
        ((*(int *)(self + 0x2c) + 0x68 <= y || (local_468 = uVar1, uVar1 == 0xffffffff)) &&
         (*(int *)(self + 0x2c) + 0x156 < y))) {
      local_468 = uVar1 + 0xe;
    }
    if (*(int *)(g_clientContext + 0x44e24) - 1U <= local_468) {
      local_468 = *(int *)(g_clientContext + 0x44e24) - 1;
    }
    if (local_468 != uVar7) {
      FUN_00428550(local_45c);
      local_4 = 0;
      if (*(unsigned int *)(g_clientContext + 0x44e24) <= *(unsigned int *)(self + 0x94)) {
        /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      FUN_0044c740();
      FUN_0044c6a0(g_clientContext + 0x44e20);
      FUN_0050cff0(g_clientContext + 0x44e20, local_468, local_45c, 1);
      FUN_0044b0b0(puVar2);
      iVar4 = 0;
      do {
        iVar6 = *(int *)(self + 0x94);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar5 == iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = local_468;
        LAB_0050a582:
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        } else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_468 < iVar6) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + 1);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          iVar6 = *(int *)(self + 0x94);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            uVar7 = iVar6 - 1;
            goto LAB_0050a582;
          }
        }
        iVar4 = iVar4 + 0x224;
      } while (iVar4 < 0x890);
      *(unsigned char *)(self + 0x91) = 1;
      local_4 = -1;
      FUN_00426810(local_45c);
    }
  }
  *(unsigned int *)(self + 0x94) = 0xffffffff;
  *(unsigned char *)(self + 0x90) = 0;
  bool consumed = this_->MouseUpChildren(x, y);
  if (!consumed &&
      (this_->m_hidden != '\0' || x <= this_->m_x ||
       this_->m_width + this_->m_x <= x ||
       y <= this_->m_y || this_->m_height + this_->m_y <= y)) {
    uVar8 = 0;
  } else {
    uVar8 = 1;
  }
  return uVar8;
}
