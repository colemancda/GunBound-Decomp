/* FUN_0045ea40 - 0x0045ea40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0045ea40(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  local_c = *unaff_FS_OFFSET;
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053ab71;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 != '\0') && (unaff_ESI[9] != 0xe)) {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 != '\0') {
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 != '\x01') {
        iVar3 = unaff_ESI[9];
        if ((((iVar3 != 5) && (iVar3 != 6)) && (iVar3 != 8)) && (iVar3 != 10)) {
          (**(code **)(*unaff_ESI + 4))(s_shock_00553b80);
        }
        FUN_00406500(0);
        cVar1 = PacketChecksumEquals(g_clientContext + 0x45354,3);
        if (cVar1 == '\0') {
          uVar2 = EncodeChecksumPairSum(unaff_ESI + 0x2cb8,auStack_454,unaff_ESI + 0x2c2f);
          uStack_4 = 0;
          iVar3 = PeekChecksumStateUnderLock(uVar2);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
          cVar1 = PeekPacketChecksumBool();
          if (cVar1 == '\x01') {
            iVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
            iVar3 = iVar3 + (iVar3 * 8) / iVar4;
          }
          uVar2 = EncodeChecksumDeltaSub(unaff_ESI + 0x1bf5,auStack_454,iVar3);
          uStack_4 = 1;
          iVar3 = PeekChecksumStateUnderLock(uVar2);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
          if (iVar3 < 1) {
            QueueOutgoingPacketField(0);
          }
          else {
            QueueOutgoingPacketField(iVar3);
            iVar3 = 0;
          }
          AddToPacketChecksum(iVar3);
          uVar2 = EncodeChecksumDeltaSub(unaff_ESI + 0x2cc,auStack_230,0xf);
          uStack_4 = 2;
          uVar2 = PeekChecksumStateUnderLock(uVar2);
          uVar5 = PeekChecksumStateUnderLock(unaff_ESI + 0x243);
          FUN_00436860(uVar5,uVar2);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

