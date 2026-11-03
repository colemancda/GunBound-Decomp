/* FUN_004038c0 - 0x004038c0 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551cc4, SLOT 3 of the messenger's notify interface
 * 0x551cb8. Extent 0x4038c0-0x403add (`ret 0x14`, then int3 padding to
 * FUN_00403ae0). UpsertDirectLinkBuddyNode's header already lists the
 * `call 0x401d50` at 0x40396a as one of its "unported gap" sites.
 *
 * __thiscall, FIVE stack words (`ret 0x14`): `mov ebx,ecx` (0x4038d0) =
 * this (the interface at ctx+8; the context is this-8, `lea eax,[ebx-8]`
 * 0x40395d). `cmp word [esp+0x454],0` (0x4038c6, depth 0x450) is entry+4 =
 * param_2, a word that must be 0 (else straight to the epilogue, 0x4038d6);
 * `mov edi,[esp+0x46c]` (0x4038dd, depth 0x458) is entry+0x14 = param_6, a
 * vector {+4 begin, +8 end} of 0x34-byte records (count = (end-begin)/0x34,
 * the 0x4ec4ec4f reciprocal multiply at 0x4038f0, 0 if begin is NULL).
 * Words 3-5 (param_3..param_5) are never read.
 *
 * BODY, per record p (16-byte user id at p+0, 0x28/0x2c/0x32 = three
 * address fields), with a 24-byte record of six 0xffffffff words kept
 * across iterations (esp+0x10..0x24):
 *   FindNicknameByUserId(nick, EAX = p, ECX = ctx);
 *   found  -> UpsertDirectLinkBuddyNode(ECX = p+0x28, stack: ctx, 1, 0,
 *             WORD p+0x32, &record, p, EAX = nick)  [0x40396a];
 *   absent -> overwrite the record's first 10 bytes with p+0x28, p+0x2c,
 *             WORD p+0x32 (0x403974-0x403991), FUN_004026a0(0x1003,
 *             &record, 10, EAX = p, EBX = ctx, CL = 0)  [0x4039a0], and
 *             append the 16-byte id to a batch buffer; when the batch
 *             reaches 0x27 ids (`cmp esi,0x26 / jle`, 0x4039c4) send it as
 *             0x1022 [u16 count][ids] through g_connectionContextA and
 *             start over.
 * After the loop: byte [this+0x1bc4] = 0 (0x403a5e - the flag
 * FUN_00403890 sets) and the remaining batch, if any, is sent the same way.
 * Left unnamed. Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void FUN_004038c0(int param_1,short param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 local_rec [6];
  undefined4 batch [0x27 * 4];
  char local_nick [32];

  if (param_2 != 0) {
    return;
  }
  iVar5 = 0;
  if (param_6[1] != 0) {
    iVar5 = (param_6[2] - param_6[1]) / 0x34;
  }
  local_rec[0] = 0xffffffff;
  local_rec[1] = 0xffffffff;
  local_rec[2] = 0xffffffff;
  local_rec[3] = 0xffffffff;
  local_rec[4] = 0xffffffff;
  local_rec[5] = 0xffffffff;
  iVar3 = 0;
  iVar4 = 0;
  for (; iVar5 > 0; iVar5 = iVar5 + -1) {
    iVar1 = param_6[1] + iVar4;
    cVar6 = FindNicknameByUserId(local_nick,(char *)iVar1,(int)g_clientContext);
    iVar1 = param_6[1] + iVar4;
    if (cVar6 == '\x01') {
      UpsertDirectLinkBuddyNode((char *)(iVar1 + 0x28),param_1 + -8,1,0,*(ushort *)(iVar1 + 0x32),
                                local_rec,(char *)iVar1,local_nick);
    }
    else {
      local_rec[0] = *(undefined4 *)(iVar1 + 0x28);
      local_rec[1] = *(undefined4 *)(iVar1 + 0x2c);
      *(undefined2 *)(local_rec + 2) = *(undefined2 *)(iVar1 + 0x32);
      FUN_004026a0(0x1003,local_rec,10,(char *)iVar1,param_1 + -8,'\0');
      iVar1 = param_6[1] + iVar4;
      puVar7 = batch + iVar3 * 4;
      puVar7[0] = *(undefined4 *)iVar1;
      puVar7[1] = *(undefined4 *)(iVar1 + 4);
      puVar7[2] = *(undefined4 *)(iVar1 + 8);
      puVar7[3] = *(undefined4 *)(iVar1 + 0xc);
      iVar3 = iVar3 + 1;
      if (iVar3 > 0x26) {
        iVar2 = g_connectionContextA;
        *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
        *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
        *(undefined2 *)(iVar2 + 0x4d6) = (undefined2)iVar3;
        iVar1 = *(int *)(iVar2 + 0x44d0);
        *(int *)(iVar2 + 0x44d0) = iVar1 + 2;
        puVar8 = (undefined4 *)(iVar1 + 0x4d2 + iVar2);
        for (iVar1 = 0; iVar1 < iVar3 * 4; iVar1 = iVar1 + 1) {
          puVar8[iVar1] = batch[iVar1];
        }
        *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + iVar3 * 0x10;
        SendOutgoingPacket(iVar2);
        iVar3 = 0;
      }
    }
    iVar4 = iVar4 + 0x34;
  }
  *(undefined1 *)(param_1 + 0x1bc4) = 0;
  if (iVar3 != 0) {
    iVar2 = g_connectionContextA;
    *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
    *(undefined2 *)(iVar2 + 0x4d6) = (undefined2)iVar3;
    iVar1 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar1 + 2;
    puVar8 = (undefined4 *)(iVar1 + 0x4d2 + iVar2);
    for (iVar1 = 0; iVar1 < iVar3 * 4; iVar1 = iVar1 + 1) {
      puVar8[iVar1] = batch[iVar1];
    }
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + iVar3 * 0x10;
    SendOutgoingPacket(iVar2);
  }
  return;
}
