/* FUN_004e76d0 - 0x004e76d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS ANALYSED, NOT APPLIED.  `ret 4` gives one stack argument;
 * param_1 (ECX), param_2 (EDX) and ESI, EAX, EDI are all read before being
 * written.  At the sole call site (0x004e0371):
 *
 *   ecx = [esp + 0x38]        <- caller stack local
 *   edx = [esp + 0x32]        <- caller stack local (unaligned: a word)
 *   push [esp + 0x10]         <- caller stack local
 *   esi = 0xe55ce0            -> &g_replayContext
 *   eax = [ecx + 0x23330]
 *
 * Only ESI is expressible.  The port passes one argument, &uStack_f0, which
 * lands in param_1; whether that is even the right VALUE cannot be settled
 * while the three spill slots are unnamed.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e76d0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x4520c) = param_1;
  *(undefined2 *)(unaff_ESI + 0x45210) = param_2;
  *(undefined4 *)(unaff_ESI + 0x45212) = *param_3;
  iVar2 = (unaff_ESI + 0x4521b) - (int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[iVar2] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_ESI + 0x45208) = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  SendUdpDatagram(*(int *)(unaff_ESI + 0x4520c),(int)*(short *)(unaff_ESI + 0x45210),
                  (char *)(unaff_ESI + 0x45212),4,unaff_ESI);
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  return;
}

