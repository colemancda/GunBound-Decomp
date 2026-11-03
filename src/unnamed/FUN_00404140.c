/* FUN_00404140 - 0x00404140 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551ce4, SLOT 11 of the messenger's notify interface
 * 0x551cb8 (between slot 10 FUN_00403ff0 and slot 12 FUN_00404330).
 * Extent 0x404140-0x404324 (`ret 4` at 0x404324, then int3 padding).
 *
 * __thiscall, ONE stack word (`ret 4`): `mov ebp,ecx` (0x404154) = this
 * (the interface at ctx+8: `lea edx,[ebp-8]` is the context, `ebp+0x1bdc`
 * the pending list, `[ebp+0x1bd4]` the CommP2P owner = ctx+0x1bdc);
 * `mov edi,[esp+0x74]` (0x40417a, depth 0x70) is entry+4 = param_2, the
 * 16-byte user id.
 *
 * BODY - upserts a buddy record and reports it to the owner, with the
 * 0x12 check record of FUN_00404700:
 *   0x404156-0x404160  __stricmp(own nickname, 0x551e24); equal -> return.
 *   0x404166-0x40418a  a 24-byte record of six 0xffffffff words
 *                      (esp+4..esp+0x18 at depth 0x70... the same shape
 *                      DispatchDirectLinkPacket's 0x1003 arm builds);
 *   0x404193-0x40419a  FindNicknameByUserId(local_nick, EAX = id,
 *                      ECX = ctx); on success 0x40419c-0x4041b8
 *                      UpsertDirectLinkBuddyNode(ECX = id+0x28,
 *                      stack: ctx, 1, 0, WORD id+0x32, &record, id,
 *                      EAX = the nickname);
 *   0x4041c2-0x404278  otherwise overwrite the record's first 10 bytes
 *                      with id+0x28 / id+0x2c / id+0x32 (dword, dword,
 *                      word), build "i"+id, FUN_00404b00 on this+0x1bdc,
 *                      send 0x1022 [u16 1][id] unless pending, then
 *                      FUN_004026a0(0x1003, &record, 0xa, EAX = id,
 *                      EBX = ctx, CL = 0);
 *   0x40427e-0x404306  both paths: the same 0x12 / port-checksum record
 *                      FUN_00404700 builds (words from ctx+0x3f804,
 *                      +0x41340, +0x44e60 and the xor-sum at +0x2e),
 *   0x404308-0x40431c  and, if the owner at this+0x1bd4 is set,
 *                      owner slot 6 (+0x18): (owner, id, &record, "").
 * Left unnamed. Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"

typedef char (*DLNoticeFn)(int self,void *userId,void *blob,char *text);

void FUN_00404140(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined4 local_rec [6];
  undefined2 local_50 [4];
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  short local_42;
  undefined1 local_38;
  char local_37 [23];
  char local_20 [32];

  iVar5 = __stricmp((char *)(g_clientContext + 0x23313),DAT_00551e24);
  if (iVar5 == 0) {
    return;
  }
  local_rec[0] = 0xffffffff;
  local_rec[1] = 0xffffffff;
  local_rec[2] = 0xffffffff;
  local_rec[3] = 0xffffffff;
  local_rec[4] = 0xffffffff;
  local_rec[5] = 0xffffffff;
  cVar3 = FindNicknameByUserId(local_20,param_2,(int)g_clientContext);
  if (cVar3 == '\x01') {
    UpsertDirectLinkBuddyNode(param_2 + 0x28,param_1 + -8,1,0,*(ushort *)(param_2 + 0x32),local_rec,
                              param_2,local_20);
  }
  else {
    local_rec[0] = *(undefined4 *)(param_2 + 0x28);
    local_rec[1] = *(undefined4 *)(param_2 + 0x2c);
    *(undefined2 *)(local_rec + 2) = *(undefined2 *)(param_2 + 0x32);
    local_38 = 0x69;
    pcVar4 = param_2;
    do {
      cVar3 = *pcVar4;
      pcVar4[(int)(local_37 + -(int)param_2)] = cVar3;
      pcVar4 = pcVar4 + 1;
    } while (cVar3 != '\0');
    iVar5 = (int)FUN_00404b00(&local_38,(int *)(param_1 + 0x1bdc));
    iVar2 = g_connectionContextA;
    if (iVar5 == 0) {
      *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
      *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
      *(undefined2 *)(iVar2 + 0x4d6) = 1;
      iVar5 = *(int *)(iVar2 + 0x44d0);
      *(int *)(iVar2 + 0x44d0) = iVar5 + 2;
      puVar1 = (undefined4 *)(iVar5 + 0x4d2 + iVar2);
      *puVar1 = *(undefined4 *)param_2;
      puVar1[1] = *(undefined4 *)(param_2 + 4);
      puVar1[2] = *(undefined4 *)(param_2 + 8);
      puVar1[3] = *(undefined4 *)(param_2 + 0xc);
      *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 0x10;
      SendOutgoingPacket(iVar2);
    }
    FUN_004026a0(0x1003,local_rec,10,param_2,param_1 + -8,'\0');
  }
  local_48 = *(undefined2 *)(g_clientContext + 0x3f804);
  local_46 = *(undefined2 *)(g_clientContext + 0x41340);
  local_44 = *(undefined2 *)(g_clientContext + 0x44e60);
  local_50[0] = 0x12;
  local_42 = (ushort)(byte)((byte)((ushort)local_44 >> 8) ^ 0x6b) + (ushort)((byte)local_44 ^ 0x69)
             + (ushort)(byte)((byte)((ushort)local_46 >> 8) ^ 0x73) +
             (ushort)((byte)local_46 ^ 0x6d) + (ushort)(byte)((byte)((ushort)local_48 >> 8) ^ 0x6f)
             + (ushort)((byte)local_48 ^ 99);
  if (*(int *)(param_1 + 0x1bd4) != 0) {
    (*(DLNoticeFn *)(**(int **)(param_1 + 0x1bd4) + 0x18))
              (*(int *)(param_1 + 0x1bd4),param_2,local_50,(char *)&DAT_00551cb1);
  }
  return;
}
