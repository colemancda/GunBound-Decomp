/* FUN_00402cf0 - 0x00402cf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely - same bug as
 * FUN_00405ba0.c's own already-fixed SendSocketData call, which shares
 * this exact object shape (g_directLinkConnection, connObj at +0x2004, write
 * cursor at +0x2000). Confirmed via angr disassembly at 0x402d54-0x402d6a:
 * `mov ecx,eax` where eax was previously the object base (buffer, this) /
 * `push eax` where eax=[obj+0x2004] (connection object, param_2) / `push
 * eax` where eax=the just-computed new cursor (length, param_3 - already
 * held in iVar5).
 */
#include "ghidra_types.h"


void FUN_00402cf0(int param_1)

{
  undefined2 *puVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char *unaff_EDI;
  undefined1 local_38;
  char local_37 [23];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  cVar2 = FUN_00426030(&local_20);
  puVar1 = g_directLinkConnection;
  if (cVar2 != '\x01') {
    local_38 = 0x6e;
    pcVar3 = unaff_EDI;
    do {
      cVar2 = *pcVar3;
      pcVar3[(int)(local_37 + -(int)unaff_EDI)] = cVar2;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    iVar4 = FUN_00404b00(&local_38);
    iVar5 = DAT_007934e8;
    if (iVar4 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar5 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar5 + 0x4d6) = *(undefined4 *)unaff_EDI;
      *(undefined4 *)(iVar5 + 0x4da) = *(undefined4 *)(unaff_EDI + 4);
      *(undefined4 *)(iVar5 + 0x4de) = *(undefined4 *)(unaff_EDI + 8);
      iVar4 = *(int *)(iVar5 + 0x44d0);
      *(int *)(iVar5 + 0x44d0) = iVar4 + 0xc;
      *(undefined1 *)(iVar4 + 0x4dc + iVar5) = 0;
      *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 1;
      EncodePacketBody(0,iVar5);
      SendOutgoingPacket(iVar5);
    }
    FUN_004026a0(0x2004,&DAT_0054b460,0);
    return;
  }
  if (g_directLinkConnection != (undefined2 *)0x0) {
    *(undefined4 *)(g_directLinkConnection + 0x1000) = 4;
    puVar1[1] = 0xa210;
    *(undefined4 *)(puVar1 + 2) = local_20;
    *(undefined4 *)(puVar1 + 4) = local_1c;
    *(undefined4 *)(puVar1 + 6) = local_18;
    *(undefined4 *)(puVar1 + 8) = local_14;
    iVar5 = *(int *)(puVar1 + 0x1000) + 0x10;
    *(int *)(puVar1 + 0x1000) = iVar5;
    *puVar1 = (short)iVar5;
    SendSocketData((char *)puVar1,*(undefined4 *)((char *)puVar1 + 0x2004),iVar5);
    FUN_00401ee0(param_1);
    return;
  }
  if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x28))(&local_20);
  }
  FUN_00401ee0(param_1);
  return;
}

