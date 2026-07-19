/* FlushEncodedSocketBuffer - 0x004d3530 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely. Confirmed via
 * angr disassembly at 0x4d3709-0x4d371b: `lea ecx,[ebp+0x44d4]` (buffer,
 * this - the field right after SendOutgoingPacket's own +0x44d0 length-
 * cursor) / `push edx` where edx=[ebp+0x84e0] (connection object, param_2)
 * / `push ecx` where ecx=[esp+0x10] (length, param_3 - already computed
 * here as local_5464).
 *
 * RECOVERED (2026-07-19): the EncodePacketBlocks call dropped BOTH of that
 * function's register args (input=ECX, inputLen=EAX) - the same bug already
 * fixed in EncodePacketBody.c, and the reason this file stopped compiling
 * once EncodePacketBlocks got its full prototype. Confirmed at orig
 * 0x4d35a8-0x4d35ca (the call is 0x4d35ca):
 *   0x4d35a8 push 0x5000                    ; capacity
 *   0x4d35ad lea eax,[esp+0x46c] / push eax ; output  = local_500c
 *   0x4d35c2 push edx                       ; opcode  = [ebp+0x44d8]
 *   0x4d35c9 push edx (=[ebp+0x84e8])       ; schedule
 *   0x4d35bb lea ecx,[ecx+ebp+0x44da]       ; ECX = INPUT, ebp = param_1 and
 *                                           ;   ecx = *(param_1+0x84dc)
 *   0x4d35b5 lea eax,[esi+esi*2] / shl eax,2; EAX = INPUTLEN = blocks*0xc,
 *                                           ;   esi = (iVar5+5)/0xc (from
 *                                           ;   0x4d358c-0x4d359d)
 * The input pointer is the very same address the copy-back loop below already
 * computes into puVar8, so the encode was writing over a buffer it had never
 * read - every flushed packet body was encrypted uninitialised scratch.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FlushEncodedSocketBuffer(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *unaff_FS_OFFSET;
  int local_5464;
  undefined1 local_545c [8];
  undefined1 local_5454 [548];
  undefined1 local_5230 [548];
  undefined4 local_500c [5119];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005390e6;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4d354f;
  local_5464 = *(int *)(param_1 + 0x84d8);
  if (local_5464 < *(int *)(param_1 + 0x84d4)) {
    local_5464 = *(int *)(param_1 + 0x84d4);
  }
  if (*(int *)(param_1 + 0x84dc) != -1) {
    iVar5 = local_5464 - *(int *)(param_1 + 0x84dc);
    EncodePacketBlocks((byte *)(*(int *)(param_1 + 0x84dc) + 0x44da + param_1),
                 ((iVar5 + 5) / 0xc) * 0xc,*(int *)(param_1 + 0x84e8),
                 *(ushort *)(param_1 + 0x44d8),(int)local_500c,0x5000);
    uVar6 = ((iVar5 + 5) / 0xc) * 0x10;
    puVar7 = local_500c;
    puVar8 = (undefined4 *)(*(int *)(param_1 + 0x84dc) + 0x44da + param_1);
    for (uVar3 = (((int)uVar6 < 0) - 1 & uVar6) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    local_5464 = local_5464 + (uVar6 - (iVar5 + -6));
  }
  *(short *)(param_1 + 0x44d4) = (short)local_5464;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4d3623
   * (`lea edi,[ebp+0x84]`, ebp = this file's own param_1) the cell is
   * param_1+0x84, the SAME cell already passed explicitly to
   * EncodeChecksumDeltaMul 2 lines below (same pattern as
   * SendOutgoingPacket.c's identical fix) - see
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x84, iVar5 + local_5464);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = EncodeChecksumDeltaMul(param_1 + 0x84,local_5454,0x343fd);
  local_4 = 0;
  EncodeChecksumDeltaAdd(uVar2,local_5230,0x269ec3);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  *(undefined2 *)(param_1 + 0x44d6) = uVar1;
  if ((*(int *)(local_5230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_545c);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_5454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_545c);
  }
  SendSocketData((char *)(param_1 + 0x44d4),*(undefined4 *)(param_1 + 0x84e0),local_5464);
  *(undefined4 *)(param_1 + 0x84ec) = 0;
  *unaff_FS_OFFSET = local_c;
  return;
}

