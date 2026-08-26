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
 *
 * RE-SLOTTED AND BOTH REGISTERS RECOVERED (2026-08-26).  The source passed
 * ONE argument to a three-parameter __fastcall, and it was passing it in the
 * wrong slot: `&uStack_f0` is the PUSHED argument, i.e. param_3, while
 * param_1 and param_2 arrive in ECX and EDX.
 *
 * The body says what they are -- param_1 is stored to +0x4520c and param_2 to
 * +0x45210, and SendUdpDatagram is then called with exactly those two as its
 * address and port.  The call site agrees: ECX is `mov ecx,[esp+0x38]` with one
 * push pending and EDX is `mov edx,[esp+0x32]` with none, which under the
 * caller's -0x100 frame are -0xcc and -0xce -- both INSIDE its
 * `sockaddr sStack_d0` (-0xd0, 16 bytes).  As sockaddr fields those are
 * sa_data+2 (the four address bytes) and sa_data+0 (the two port bytes), and
 * the line above the call is
 * `getpeername(..., &sStack_d0, &iStack_dc)`, which is what fills them.
 *
 * regEsi is &g_replayContext; regEax is (char *)(g_clientContext + 0x23330),
 * the NUL-terminated name the body copies to +0x4521b, set at 0x4e033b and
 * not rewritten before the call.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e76d0(undefined4 param_1,int param_2,undefined4 *param_3,char *regEax,
                             int regEsi)

{
  char cVar1;
  int iVar2;
  
  *(undefined4 *)(regEsi + 0x4520c) = param_1;
  *(undefined2 *)(regEsi + 0x45210) = param_2;
  *(undefined4 *)(regEsi + 0x45212) = *param_3;
  iVar2 = (regEsi + 0x4521b) - (int)regEax;
  do {
    cVar1 = *regEax;
    regEax[iVar2] = cVar1;
    regEax = regEax + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(regEsi + 0x45208) = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)(regEsi + 0x17c));
  SendUdpDatagram(*(int *)(regEsi + 0x4520c),(int)*(short *)(regEsi + 0x45210),
                  (char *)(regEsi + 0x45212),4,regEsi);
  LeaveCriticalSection((LPCRITICAL_SECTION)(regEsi + 0x17c));
  return;
}

