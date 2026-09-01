/* FUN_00404700 - 0x00404700 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-28): EDI is the 0x10-byte name record
 * this function sends and logs. It is read before it is ever written - in
 * fact the function contains no write to EDI at all - at 0x4047a0 (mov
 * eax,edi, feeding the still-dropped EAX argument of the FUN_00426030 call
 * at 0x4047a2), at 0x40481c-0x404831 (mov edx,edi, the source of the 12-byte
 * copy into the outgoing packet at +0x4d6) and at 0x404877 (mov eax,edi,
 * FUN_004026a0's EAX). ret 4 at 0x4047d3 and 0x404885 matches the single
 * declared stack parameter exactly, so this is a clean APPEND, not a
 * re-slot: param_1 stays entry_esp+4 (mov ebp,[esp+0x58] at 0x404747, with
 * sub esp,0x50 plus push ebp giving depth 0x54). Ghidra's local names
 * confirm the frame three independent ways: lea eax,[esp+0x34] at 0x40479b,
 * depth 0x54, is entry_esp-0x20 = local_20; lea ecx,[esp+0x20] at 0x4047ee,
 * depth 0x58 with the push ebx at 0x4047ed pending, is entry_esp-0x38 =
 * local_38; and lea eax,[esp+0xc] at 0x40486b, depth 0x5c with that push ebx
 * plus the pending push 0x18, is entry_esp-0x50 = local_50. The push esi at
 * 0x404802 is popped at 0x404868 and FUN_00404b00 cleans its own push (ret
 * 4), so neither disturbs that depth.
 *
 * All three call sites resolved, and they reconcile exactly: three direct
 * calls in the binary, three in the source (tools/count_call_args.py), and
 * no data reference to 0x404700 anywhere in the image.
 *
 * FUN_00402e60 at 0x402fe2: EDI is that caller's own regEax, set once by mov
 * edi,eax at 0x402e71 and never rewritten - 0x402e70 push edi and 0x402fe7
 * pop edi are the save pair - so it reaches the call on every path. The
 * guard cmp byte ptr [esp+0x50],1 at 0x402fda sits at depth 0x48 (sub
 * esp,0x38 plus four prologue pushes), i.e. entry_esp+8 = param_2, matching
 * the source's if ((char)param_2 == '\x01').
 *
 * FUN_00403ae0 at 0x403b36: lea edi,[esp+0x2c] at 0x403b32, at depth 0x4c
 * (sub esp,0x38, four prologue pushes, one pending push esi at 0x403b06), is
 * entry_esp-0x20 = local_20 - the buffer FUN_00426090 filled. The same
 * address is formed independently at 0x403aeb as lea eax,[esp+0x28] at depth
 * 0x48, with nothing pending, and passed to FUN_00426090; that is what the
 * source names local_20. The block also hands the same address to
 * FUN_00401bb0 in EBX by lea ebx,[esp+0x2c] at 0x403b07 - at the SAME depth
 * 0x4c, since the push esi at 0x403b06 is already pending there.
 *
 * DispatchDirectLinkPacket at 0x403648: EDI is that function's regEax, mov
 * edi,eax at 0x4032d2.
 *
 * That last site needed dominance, not proximity. The two later writes to
 * EDI - lea edi,[ecx+1] at 0x40334f and lea edi,[esi+8] at 0x4034bf - cannot
 * reach the call. The block holding it begins at 0x40361f and its ONLY
 * inbound edge in the whole function is je 0x40361f at 0x4032e3, taken
 * directly out of the opcode compare at 0x4032d7, which executes before
 * either write; the two writes sit in the opcode==2 and opcode==0 arms, each
 * of which returns through its own epilogue; and the 0x2000-0x2005 jump
 * table at 0x403868 holds 0x40366f, 0x403685, 0x4036c6, 0x403734, 0x4037b7
 * and 0x40383c, none of them inside 0x40361f-0x403648. So EDI at 0x403648 is
 * the entry EAX unconditionally.
 *
 * Still dropped at this address, tracked separately: FUN_00426030's EAX at
 * the 0x4047a2 call, and FUN_004026a0's EAX, EBX and CL at 0x40487b
 * (eax=regEdi, ebx=param_1 by mov ebx,ebp at 0x404879, cl=1 by mov cl,1 at
 * 0x404875).
 */
#include "ghidra_types.h"


void FUN_00404700(int param_1,undefined4 *regEdi)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_EDI = regEdi;
  undefined2 local_50 [4];
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  short local_42;
  undefined1 local_38;
  char acStack_37 [23];
  char local_20 [32];
  
  local_48 = *(undefined2 *)(g_clientContext + 0x3f804);
  local_46 = *(undefined2 *)(g_clientContext + 0x41340);
  local_44 = *(undefined2 *)(g_clientContext + 0x44e60);
  local_50[0] = 0x12;
  local_42 = (ushort)(byte)((byte)((ushort)local_44 >> 8) ^ 0x6b) + (ushort)((byte)local_44 ^ 0x69)
             + (ushort)(byte)((byte)((ushort)local_46 >> 8) ^ 0x73) +
             (ushort)((byte)local_46 ^ 0x6d) + (ushort)(byte)((byte)((ushort)local_48 >> 8) ^ 0x6f)
             + (ushort)((byte)local_48 ^ 99);
  cVar2 = FUN_00426030(local_20,(char *)regEdi,(int)g_clientContext);
  if (cVar2 == '\x01') {
    if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x18))(local_20,local_50,&DAT_00551cb1);
      return;
    }
  }
  else {
    local_38 = 0x69;
    iVar3 = 0;
    do {
      pcVar1 = local_20 + iVar3;
      acStack_37[iVar3] = *pcVar1;
      iVar3 = iVar3 + 1;
    } while (*pcVar1 != '\0');
    iVar4 = FUN_00404b00(&local_38,(int *)(param_1 + 0x1be4));
    iVar3 = g_connectionContextA;
    if (iVar4 == 0) {
      *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
      *(undefined2 *)(iVar3 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar3 + 0x4d6) = *unaff_EDI;
      *(undefined4 *)(iVar3 + 0x4da) = unaff_EDI[1];
      *(undefined4 *)(iVar3 + 0x4de) = unaff_EDI[2];
      iVar4 = *(int *)(iVar3 + 0x44d0);
      *(int *)(iVar3 + 0x44d0) = iVar4 + 0xc;
      *(undefined1 *)(iVar4 + 0x4dc + iVar3) = 0;
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
      EncodePacketBody(0,iVar3);
      SendOutgoingPacket(iVar3);
    }
    /* DROPPED-REG FIX 2026-08-28: FUN_004026a0's EAX/EBX/CL - see its header's site map. */
    FUN_004026a0(0x2005,local_50,0x18,(char *)regEdi,param_1,'\x01');
  }
  return;
}

