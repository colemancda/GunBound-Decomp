/* FUN_00462900 - 0x00462900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00462a32) */

void __fastcall FUN_00462900(int param_1)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  char *pcVar12;
  uint uVar13;
  int iVar14;
  undefined4 *unaff_FS_OFFSET;
  bool bVar15;
  uint local_930;
  undefined4 local_928;
  char local_91c [128];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a146;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar6 = *(uint *)(param_1 + 8);
  uVar4 = uVar6 >> 2 & 1;
  iVar5 = *(int *)(DAT_005b3484 + 0x1fe1c + uVar4 * 4);
  iVar10 = *(int *)(DAT_005b3484 + 0x1fe24 + uVar4 * 4);
  cVar3 = FUN_004065a0();
  iVar8 = DAT_005b3484;
  if (cVar3 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 == 2) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((*(uint *)(param_1 + 8) & 7) == uVar6) {
        iVar5 = *(int *)(DAT_005b3484 + 0x1fe2c);
        iVar10 = *(int *)(DAT_005b3484 + 0x1fe30);
        if (iVar5 != 0) {
          FUN_0045b900(iVar5,iVar10);
          FUN_0045b900(iVar10 / 2 + iVar5,iVar10);
        }
      }
    }
  }
  else {
    uVar4 = *(uint *)(param_1 + 8) >> 2 & 1;
    uVar13 = (uVar6 & 3) / 2;
    iVar14 = (uVar6 & 1) * 2;
    if (*(int *)(param_1 + 0x24) == 0xe) {
      uVar7 = 0xffffffff;
    }
    else {
      uVar7 = *(undefined4 *)(param_1 + 0x18);
    }
    FUN_0045b730(uVar7,*(undefined4 *)(param_1 + 0x68),
                 (*(int *)(DAT_005b3484 + 0x1fe4c + uVar4 * 4) * uVar13 + iVar14) * 0x80 +
                 *(int *)(DAT_005b3484 + 0x1fe44 + uVar4 * 4),iVar10);
    uVar6 = *(uint *)(param_1 + 8) >> 2 & 1;
    if (*(int *)(param_1 + 0x24) == 0xe) {
      uVar7 = 0xffffffff;
    }
    else {
      uVar7 = *(undefined4 *)(param_1 + 0x18);
    }
    uVar6 = FUN_0045b730(uVar7,*(undefined4 *)(param_1 + 0x68),
                         (*(int *)(iVar8 + 0x1fe5c + uVar6 * 4) * uVar13 + iVar14) * 0x80 +
                         *(int *)(iVar8 + 0x1fe54 + uVar6 * 4),iVar10);
    *(uint *)(iVar8 + ((*(uint *)(param_1 + 8) & 7) + 0x154c) * 0x18) = uVar6 & 0xff;
    if (((iVar5 != 0) && (*(char *)(param_1 + 0xae14) == '\0')) &&
       (cVar3 = FUN_004065a0(), cVar3 != '\x01')) {
      cVar3 = FUN_004065a0();
      iVar8 = DAT_005b3484;
      if (cVar3 != '\0') {
        *(undefined1 *)((*(uint *)(param_1 + 8) & 7) + 0x1fe94 + DAT_005b3484) = 0;
      }
      *(undefined4 *)(iVar8 + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 1;
      if (*(int *)(param_1 + 0x24) == 0xe) {
        *(undefined4 *)(iVar8 + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 0;
      }
      cVar3 = FUN_004065a0();
      iVar8 = DAT_005b3484;
      if (cVar3 != '\0') {
        *(undefined4 *)(DAT_005b3484 + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 2;
      }
      iVar1 = param_1 + 0x90c;
      *(undefined1 *)((*(uint *)(param_1 + 8) & 7) + 0x1fe8c + iVar8) = 1;
      uVar7 = FUN_0040a4d0(iVar1);
      *(undefined4 *)(DAT_005b3484 + 0x1ff0c + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar7;
      uVar7 = FUN_0040a4d0(param_1 + 0xb30);
      *(undefined4 *)(DAT_005b3484 + 0x1ff10 + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar7;
      if (*(int *)(param_1 + 0x24) == 0xd) {
        iVar8 = 0;
      }
      else {
        iVar8 = FUN_0040a4d0(param_1 + 0x209c);
        iVar8 = -iVar8;
      }
      *(int *)(DAT_005b3484 + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18) = iVar8;
      uVar6 = PacketChecksumEquals(param_1 + 0x1c54,1);
      iVar8 = DAT_005b3484;
      *(uint *)(DAT_005b3484 + 0x1ff18 + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar6 & 0xff;
      if (*(int *)(iVar8 + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18) < 0) {
        piVar2 = (int *)(iVar8 + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18);
        iVar8 = FUN_0040a4d0(&DAT_00e9bed8);
        *piVar2 = *piVar2 + iVar8;
      }
      iVar9 = FUN_0040a4d0(param_1 + 0x1a2c);
      iVar8 = DAT_005b3484;
      *(undefined4 *)(DAT_005b3484 + 0x1ff1c + (*(uint *)(param_1 + 8) & 7) * 0x18) =
           *(undefined4 *)(&DAT_0056d468 + (iVar9 * 0x1e + *(int *)(param_1 + 0x24)) * 4);
      FUN_0045b900((uVar13 * iVar10 + iVar14) * 0x80 + iVar5,iVar10);
      if (*(int *)(iVar8 + 0x1fe34 + (*(uint *)(param_1 + 8) >> 2 & 1) * 4) != 0) {
        uVar6 = *(uint *)(param_1 + 8) >> 2 & 1;
        iVar5 = *(int *)(iVar8 + 0x1fe3c + uVar6 * 4);
        FUN_0045b900((iVar5 * uVar13 + iVar14) * 0x80 + *(int *)(iVar8 + 0x1fe34 + uVar6 * 4),iVar5)
        ;
      }
      cVar3 = FUN_00406610(*(int *)(param_1 + 0x24) != 0xe);
      iVar5 = DAT_005b3484;
      if (cVar3 != '\0') {
        *(undefined4 *)(DAT_005b3484 + 0x227a8) = 1;
        uVar7 = FUN_0040a500(param_1 + 0x62f8,local_89c);
        local_4 = 0;
        uVar7 = FUN_0040a5f0(uVar7,local_678,0x5a);
        local_4._0_1_ = 1;
        FUN_0040a4d0(uVar7);
        FUN_004ead90();
        uVar7 = FUN_0053753c();
        uVar7 = FUN_0040a5f0(iVar1,local_454,uVar7);
        local_4._0_1_ = 2;
        uVar7 = FUN_0040a4d0(uVar7);
        *(undefined4 *)(DAT_005b3484 + 0x227ac) = uVar7;
        local_4._0_1_ = 1;
        FUN_0040a2a0();
        local_4 = (uint)local_4._1_3_ << 8;
        FUN_0040a2a0();
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        uVar7 = FUN_0040a500(param_1 + 0x62f8,local_454);
        local_4 = 3;
        uVar7 = FUN_0040a5f0(uVar7,local_678,0x5a);
        local_4._0_1_ = 4;
        FUN_0040a4d0(uVar7);
        FUN_004ead70();
        uVar7 = FUN_0053753c();
        uVar7 = FUN_0040a6e0(param_1 + 0xb30,local_89c,uVar7);
        local_4._0_1_ = 5;
        uVar7 = FUN_0040a4d0(uVar7);
        *(undefined4 *)(DAT_005b3484 + 0x227b0) = uVar7;
        local_4._0_1_ = 4;
        FUN_0040a2a0();
        local_4 = CONCAT31(local_4._1_3_,3);
        FUN_0040a2a0();
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        iVar5 = DAT_005b3484;
        *(undefined4 *)(DAT_005b3484 + 0x227b4) = *(undefined4 *)(param_1 + 0xb094);
        *(int *)(iVar5 + 0x227b8) = *(int *)(param_1 + 0xb098) << 0x18;
        *(undefined4 *)(iVar5 + 0x227bc) = *(undefined4 *)(param_1 + 0xb0a0);
      }
      uVar7 = FUN_0040a6e0(iVar1,local_454,*(undefined4 *)(&DAT_006a7710 + iVar5));
      local_4 = 6;
      uVar7 = FUN_0040a5f0(uVar7,local_678,400);
      local_4._0_1_ = 7;
      uVar7 = FUN_0040a6e0(uVar7,local_89c,0x29);
      local_4._0_1_ = 8;
      iVar5 = FUN_0040a4d0(uVar7);
      local_4._0_1_ = 7;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,6);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar7 = FUN_0040a6e0(param_1 + 0xb30,local_454,*(undefined4 *)(&DAT_006a7714 + DAT_005b3484));
      local_4 = 9;
      uVar7 = FUN_0040a5f0(uVar7,local_678,0x10e);
      local_4._0_1_ = 10;
      uVar7 = FUN_0040a5f0(uVar7,local_89c,0x26);
      local_4._0_1_ = 0xb;
      iVar10 = FUN_0040a4d0(uVar7);
      local_4._0_1_ = 10;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,9);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      if (500 < iVar10) {
        iVar8 = FUN_0040a4d0(&DAT_00796aa0);
        iVar10 = iVar10 - iVar8;
      }
      if (((DAT_00793530 <= iVar5 + 0x53) && (iVar5 <= DAT_0056df30)) &&
         ((DAT_00793534 <= iVar10 + 0x1f && (iVar10 <= DAT_0056df34)))) {
        uVar7 = FUN_0040a6e0(iVar1,local_678,*(undefined4 *)(&DAT_006a7710 + DAT_005b3484));
        local_4 = 0xc;
        uVar7 = FUN_0040a5f0(uVar7,local_89c,400);
        local_4._0_1_ = 0xd;
        FUN_0040a4d0(uVar7);
        local_4 = CONCAT31(local_4._1_3_,0xc);
        FUN_0040a2a0();
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        if (*(char *)(DAT_005b3484 + 0x45122) == '\0') {
          iVar8 = FUN_0040a4d0(DAT_005b3484 + 0x3b49c);
          bVar15 = *(int *)(param_1 + 0xae2c) == iVar8;
        }
        else {
          bVar15 = *(uint *)(param_1 + 0xae2c) == (uint)*(byte *)(DAT_005b3484 + 0x3b6c0);
        }
        if ((*(int *)(param_1 + 0x24) != 0xe) &&
           (cVar3 = PacketChecksumNotEquals(DAT_005b3484 + 0x45354,3), cVar3 != '\0')) {
          FUN_004eb7a0(iVar5 + 1,0x4e,5);
          FUN_004eb800(0x4c,0x2965);
          iVar5 = param_1 + 0x6db0;
          iVar8 = param_1 + 0x6744;
          uVar7 = FUN_0040aba0(iVar8,local_230,iVar5);
          local_4 = 0xe;
          iVar14 = FUN_0040a4d0(uVar7);
          if (0 < iVar14) {
            uVar7 = FUN_0040aba0(iVar8,local_454,iVar5);
            local_4 = CONCAT31(local_4._1_3_,0xf);
            local_928 = FUN_0040a4d0(uVar7);
          }
          else {
            local_928 = 1;
          }
          uVar7 = FUN_0040a7d0(param_1 + 0x6968,local_678,0x4c);
          local_4 = 0x10;
          uVar7 = FUN_0040a8c0(uVar7,local_89c,local_928);
          local_4._0_1_ = 0x11;
          uVar7 = FUN_0040a4d0(uVar7);
          local_4._0_1_ = 0x10;
          FUN_0040a2a0();
          local_4 = CONCAT31(local_4._1_3_,0xf);
          FUN_0040a2a0();
          local_4 = 0xe;
          if (0 < iVar14) {
            FUN_0040a2a0();
          }
          local_4 = 0xffffffff;
          FUN_0040a2a0();
          uVar11 = FUN_0040aba0(iVar8,local_89c,iVar5);
          local_4 = 0x12;
          uVar11 = FUN_0040a8c0(uVar11,local_230,3);
          local_4._0_1_ = 0x13;
          cVar3 = FUN_0040b490(param_1 + 0x6968,uVar11);
          local_4 = CONCAT31(local_4._1_3_,0x12);
          FUN_0040a2a0();
          local_4 = 0xffffffff;
          FUN_0040a2a0();
          FUN_004eb800(uVar7,(-(uint)(cVar3 != '\0') & 0x5af7) + 0x65a9);
          uVar7 = FUN_0040aba0(iVar8,local_454,iVar5);
          local_4 = 0x14;
          iVar14 = FUN_0040a4d0(uVar7);
          if (0 < iVar14) {
            uVar7 = FUN_0040aba0(iVar8,local_678,iVar5);
            local_4 = CONCAT31(local_4._1_3_,0x15);
            uVar7 = FUN_0040a4d0(uVar7);
          }
          else {
            uVar7 = 1;
          }
          uVar11 = FUN_0040a7d0(param_1 + 0x6fd4,local_89c,0x4c);
          local_4 = 0x16;
          uVar7 = FUN_0040a8c0(uVar11,local_230,uVar7);
          uVar11 = 0x21d8;
          local_4._0_1_ = 0x17;
          uVar7 = FUN_0040a4d0(uVar7);
          FUN_004eb800(uVar7,uVar11);
          local_4._0_1_ = 0x16;
          FUN_0040a2a0();
          local_4 = CONCAT31(local_4._1_3_,0x15);
          FUN_0040a2a0();
          local_4 = 0x14;
          if (0 < iVar14) {
            FUN_0040a2a0();
          }
          local_4 = 0xffffffff;
          FUN_0040a2a0();
        }
        pcVar12 = (char *)(param_1 + 0xae22);
        if (*(char *)(param_1 + 0xae22) == '\0') {
          FUN_004eb890();
          BlitRLESprite(iVar10 + 10,0);
          BlitRLESprite(iVar10 + 9,(-(uint)bVar15 & 0x517) + 0xfae8);
        }
        else {
          do {
            cVar3 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar3 != '\0');
          iVar5 = *(int *)(param_1 + 0xae34);
          if (0x3e6 < iVar5) {
            iVar5 = 999;
          }
          iVar8 = *(int *)(param_1 + 0xae30);
          if (0x3e6 < iVar8) {
            iVar8 = 999;
          }
          _sprintf(local_91c,s___d__d__00555c88,iVar8,iVar5);
          pcVar12 = local_91c;
          local_930 = 0;
          do {
            cVar3 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar3 != '\0');
          if (pcVar12 != local_91c + 1) {
            do {
              FUN_004eb890();
              local_930 = local_930 + 1;
              pcVar12 = local_91c;
              do {
                cVar3 = *pcVar12;
                pcVar12 = pcVar12 + 1;
              } while (cVar3 != '\0');
            } while (local_930 < (uint)((int)pcVar12 - (int)(local_91c + 1)));
          }
          BlitRLESprite(iVar10 + 8,0);
          iVar5 = (-(uint)bVar15 & 0x517) + 0xfae8;
          BlitRLESprite(iVar10 + 7,iVar5);
          FUN_004eb890();
          BlitRLESprite(iVar10 + 0x15,0);
          BlitRLESprite(iVar10 + 0x14,iVar5);
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

