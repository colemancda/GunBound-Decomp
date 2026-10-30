/* DispatchP2PMessage - 0x00504970 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00504970).  Dispatches one inbound P2P message
 * to the session's handler.  Evidence:
 *   - it first calls the handler object's vtable slot 0 through
 *     [param_3 + 0x1ab0] as a filter/accept test, then switches on
 *     (param_6 & 0xffff) - 16-bit message type codes (0xc011, 0xc018, ...) -
 *     copying the payload into a local buffer and invoking vtable slot 6
 *     (+0x18) with it.
 *   - its only caller (CommP2POwner_ProcessPacket) is the receive loop: it walks a packet
 *     stream advancing by `*(ushort *)(rec + 0x26) + 0x28` per record and
 *     calls this once per record.
 *   - [ctx + 0x1ab0] is the same session object whose +0x1a70/+0x1a74 flags
 *     and +0x1a78 key schedule the P2P send path uses (SendP2PNamedMessage).
 *
 * ABI CAVEAT: genuinely __fastcall (ECX = payload length, EDX = payload) plus
 * ret 0x10 = 4 stack arguments.  The single call site passes only the 4 stack
 * arguments, so the length and payload are currently dropped - see the
 * fastcall-decls audit.
 * DISPATCH `this` RESTORED (2026-10-30): every one of the eight handler
 * virtual calls loads ECX with the handler [param_3 + 0x1ab0] (`mov
 * ecx,[eax+0x1ab0]` at 0x50498b for slot 0; `mov edx,[ecx]` / `mov
 * ecx,[ebx+0x1ab0]` before 0x5049fd, 0x504a3c, 0x504a90 (+0x18, +0x18,
 * +0x24) and 0x504aba, 0x504ae1, 0x504b1b, 0x504b33 (+0x28, +0x30,
 * +0x1c, +0x20)), and the port dropped it.  The handler is the
 * FUN_00401910 +8 sub-object with vtable 0x551cb8 (see
 * CommP2POwner_OnConnectionClosed); its ported slots 7, 8 and 12
 * (FUN_00403d20, FUN_00403f30, FUN_00404330) are raw-C erased
 * __thiscall, cdecl with `this` first, and the uncarved ones are taken
 * the same way, so each call now passes the handler as its first
 * argument.  (FUN_00403d20's (this, name, a, b) matches the +0x1c call's
 * three pushes exactly.)
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __fastcall
DispatchP2PMessage(uint param_1,char *param_2,int param_3,undefined4 param_4,undefined4 param_5,
            uint param_6)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffe868;
  int *piVar1;
  char cVar2;
  uint uVar3;
  ushort uVar4;
  char *pcVar5;
  char *pcVar6;
  char cVar7;
  char acStack_178c [6016];
  undefined4 uStack_c;
  
  uStack_c = 0x504980;
  uVar3 = param_6;
  cVar2 = (**(code **)**(undefined4 **)(param_3 + 0x1ab0))(*(undefined4 **)(param_3 + 0x1ab0),param_4,param_5,param_6,param_2,param_1);
  cVar7 = (char)uVar3;
  if (cVar2 != '\0') {
    switch(param_6 & 0xffff) {
    case 0xc011:
      pcVar5 = acStack_178c;
      for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *param_2;
        param_2 = param_2 + 1;
        pcVar5 = pcVar5 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1] = '\0';
      (**(code **)(*piVar1 + 0x18))(piVar1,param_4,0,acStack_178c,param_5);
      return;
    case 0xc018:
      pcVar5 = acStack_178c;
      for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *param_2;
        param_2 = param_2 + 1;
        pcVar5 = pcVar5 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1] = '\0';
      (**(code **)(*piVar1 + 0x18))(piVar1,param_4,1,acStack_178c,param_5);
      return;
    case 0xc041:
      pcVar5 = param_2 + 8;
      pcVar6 = acStack_178c;
      for (uVar3 = param_1 - 8 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar3 = param_1 - 8 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1 - 8] = '\0';
      (**(code **)(*piVar1 + 0x24))(piVar1,param_4,&stack0xffffe868,acStack_178c);
      return;
    case 0xc042:
      cVar2 = *param_2;
      acStack_178c[param_1 - 1] = '\0';
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x28))(*(int **)(param_3 + 0x1ab0),param_4,cVar2 != '\0');
      if (cVar7 != '\0') {
        FUN_004fcee0((char *)param_4,param_3);
        return;
      }
      break;
    case 0xc043:
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x30))(*(int **)(param_3 + 0x1ab0),param_4);
      SendBuddyNameMessage(0x3002,(char *)param_4,param_3);
      return;
    case 0xc051:
      uVar4 = (short)param_1 - 0x18;
      if (uVar4 < 0x81) {
        (param_2 + 0x18)[uVar4] = '\0';
        (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x1c))(*(int **)(param_3 + 0x1ab0),param_4,param_2,param_2 + 0x18);
        return;
      }
      break;
    case 0xc053:
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x20))(*(int **)(param_3 + 0x1ab0),param_4);
    }
  }
  return;
}

