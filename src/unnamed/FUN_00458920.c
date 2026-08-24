/* FUN_00458920 - 0x00458920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EAX is the caller's STEP COUNT --
 * param_2 of every __thiscall Simulate* caller (stepDelta in the C++ port).
 * The body uses it as the multiplier in `accum - slope * regEax`, and the
 * callers multiply the same slope by the same param_2 themselves
 * (`local_1588 * param_2`), which is what pins the role.
 *
 * Found by frame arithmetic rather than by name.  Every site loads EAX from
 * [esp + 0x15f4..0x1600] -- a slot ABOVE a 0x15b8-byte __chkstk frame, the
 * SEH triple and four callee-saved pushes, at exactly +4 past the return
 * address once the pending argument pushes are subtracted.  +4 is the first
 * stack parameter.  Twenty of 24 sites gave +4 directly; the other four gave
 * +0 (the return address, which cannot be read as an argument) because a
 * `push` on an unrelated branch between the previous call and this one was
 * counted by the linear walk -- e.g. `push 0xf002 / jmp` at 0x004567b9.
 */
#include "ghidra_types.h"


void FUN_00458920(int *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,char param_8,char param_9,int regEax)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_4 != 0) {
    param_7 = param_7 - param_6 * regEax;
    iVar4 = param_4 - regEax;
    if (iVar4 < param_4) {
      param_3 = iVar4 * param_5 + param_3;
      iVar2 = g_clientContext;
      while( true ) {
        param_7 = param_7 + param_6;
        iVar3 = param_7 >> 0x10;
        if (((((param_8 != '\0') && (-1 < param_3)) && (param_3 < *(int *)(&g_nCameraBoundX + iVar2)))
            && ((-1 < iVar3 && (iVar3 < *(int *)(&g_nCameraBoundY + iVar2))))) &&
           (*(char *)(*(int *)(&g_nCameraBoundX + iVar2) * iVar3 + *(int *)(&DAT_006a773c + iVar2) +
                     param_3) != '\0')) {
          *param_1 = param_3;
          *param_2 = iVar3;
          return;
        }
        if ((param_9 != '\0') && (cVar1 = FUN_00450e10(iVar3), iVar2 = g_clientContext, cVar1 != '\0'))
        break;
        iVar4 = iVar4 + 1;
        param_3 = param_3 + param_5;
        if (param_4 <= iVar4) {
          return;
        }
      }
      *param_1 = param_3;
      *param_2 = iVar3;
    }
  }
  return;
}

