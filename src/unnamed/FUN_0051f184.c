/* FUN_0051f184 - 0x0051f184 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined8 __fastcall
FUN_0051f184(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  int iVar15;
  int iVar16;
  float fVar17;
  undefined4 in_EAX;
  int iVar18;
  int iVar19;
  char cVar20;
  int iVar21;
  char cVar23;
  char cVar24;
  char cVar25;
  char cVar26;
  char cVar27;
  char cVar28;
  char cVar29;
  char cVar30;
  char cVar31;
  undefined3 uVar32;
  float *pfVar33;
  float *pfVar34;
  undefined3 uVar22;
  
  uVar22 = (undefined3)((uint)param_4 >> 8);
  iVar21 = CONCAT31(uVar22,(char)param_4 + '\b');
  iVar18 = CONCAT31(uVar22,(char)param_4 + '\x18');
  iVar19 = -8;
  pfVar34 = (float *)&DAT_00568318;
  do {
    pfVar33 = pfVar34;
    iVar15 = iVar21 * 4;
    cVar23 = (char)iVar21;
    uVar22 = (undefined3)((uint)iVar21 >> 8);
    iVar16 = iVar18 * 4;
    cVar20 = (char)iVar18;
    uVar32 = (undefined3)((uint)iVar18 >> 8);
    iVar21 = CONCAT31(uVar22,cVar23 + '\x01');
    iVar18 = CONCAT31(uVar32,cVar20 + -1);
    DAT_00569344 = (int)ROUND((pfVar33[0xe] *
                               *(float *)(param_3 + CONCAT31(uVar22,cVar23 + -0x20) * 4) +
                              ((pfVar33[0xc] *
                                *(float *)(param_3 + CONCAT31(uVar22,cVar23 + -0x40) * 4) +
                               ((pfVar33[10] *
                                 *(float *)(param_3 + CONCAT31(uVar22,cVar23 + -0x60) * 4) +
                                ((pfVar33[8] *
                                  *(float *)(param_3 + CONCAT31(uVar22,cVar23 + -0x80) * 4) +
                                 ((pfVar33[6] *
                                   *(float *)(param_3 + CONCAT31(uVar22,cVar23 + '`') * 4) +
                                  ((pfVar33[4] *
                                    *(float *)(param_3 + CONCAT31(uVar22,cVar23 + '@') * 4) +
                                   ((pfVar33[2] *
                                     *(float *)(param_3 + CONCAT31(uVar22,cVar23 + ' ') * 4) +
                                    ((*pfVar33 * *(float *)(param_3 + iVar15) + 0.0) -
                                    pfVar33[1] * *(float *)(param_3 + iVar16))) -
                                   pfVar33[3] *
                                   *(float *)(param_3 + CONCAT31(uVar32,cVar20 + ' ') * 4))) -
                                  pfVar33[5] *
                                  *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '@') * 4))) -
                                 pfVar33[7] *
                                 *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '`') * 4))) -
                                pfVar33[9] *
                                *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x80) * 4))) -
                               pfVar33[0xb] *
                               *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x60) * 4))) -
                              pfVar33[0xd] *
                              *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x40) * 4))) -
                              pfVar33[0xf] *
                              *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x20) * 4));
    if (DAT_00569344 < 0x8000) {
      if (DAT_00569344 < -0x8000) {
        DAT_00569344 = -0x8000;
      }
    }
    else {
      DAT_00569344 = 0x7fff;
    }
    ((byte *)(param_5 + 8))[iVar19] = (byte)((uint)DAT_00569344 >> 8) ^ 0x80;
    iVar19 = iVar19 + 1;
    pfVar34 = pfVar33 + 0x20;
  } while (iVar19 != 0);
  cVar23 = cVar20 + -1;
  DAT_00569344 = (int)ROUND(pfVar33[0x27] *
                            *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x21) * 4) +
                            pfVar33[0x26] *
                            *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x41) * 4) +
                            pfVar33[0x25] *
                            *(float *)(param_3 + CONCAT31(uVar32,cVar20 + -0x61) * 4) +
                            pfVar33[0x24] *
                            *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '\x7f') * 4) +
                            pfVar33[0x23] * *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '_') * 4)
                            + pfVar33[0x22] *
                              *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '?') * 4) +
                              pfVar33[0x21] *
                              *(float *)(param_3 + CONCAT31(uVar32,cVar20 + '\x1f') * 4) +
                              pfVar33[0x20] * *(float *)(param_3 + iVar18 * 4) + 0.0);
  if (DAT_00569344 < 0x8000) {
    if (DAT_00569344 < -0x8000) {
      DAT_00569344 = -0x8000;
    }
  }
  else {
    DAT_00569344 = 0x7fff;
  }
  *(byte *)(param_5 + 8) = (byte)((uint)DAT_00569344 >> 8) ^ 0x80;
  pfVar34 = (float *)&DAT_005686d4;
  iVar19 = -7;
  do {
    cVar20 = (char)iVar21;
    uVar22 = (undefined3)((uint)iVar21 >> 8);
    cVar24 = cVar23 + '\x01';
    fVar17 = *pfVar34;
    pfVar33 = pfVar34 + -1;
    cVar25 = cVar23 + '!';
    pfVar1 = pfVar34 + -2;
    pfVar2 = pfVar34 + -3;
    cVar26 = cVar23 + 'A';
    pfVar3 = pfVar34 + -4;
    pfVar4 = pfVar34 + -5;
    cVar27 = cVar23 + 'a';
    pfVar5 = pfVar34 + -6;
    pfVar6 = pfVar34 + -7;
    cVar28 = cVar23 + -0x7f;
    pfVar7 = pfVar34 + -8;
    pfVar8 = pfVar34 + -9;
    cVar29 = cVar23 + -0x5f;
    pfVar9 = pfVar34 + -10;
    pfVar10 = pfVar34 + -0xb;
    cVar30 = cVar23 + -0x3f;
    pfVar11 = pfVar34 + -0xc;
    pfVar12 = pfVar34 + -0xd;
    cVar31 = cVar23 + -0x1f;
    pfVar13 = pfVar34 + -0xe;
    iVar21 = CONCAT31(uVar22,cVar20 + -1);
    pfVar14 = pfVar34 + -0xf;
    cVar23 = cVar23 + '\x01';
    pfVar34 = pfVar34 + -0x20;
    DAT_00569344 = (int)ROUND(*pfVar14 * *(float *)(param_3 + CONCAT31(uVar32,cVar31) * 4) +
                              *pfVar13 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + -0x21) * 4) +
                              *pfVar12 * *(float *)(param_3 + CONCAT31(uVar32,cVar30) * 4) +
                              *pfVar11 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + -0x41) * 4) +
                              *pfVar10 * *(float *)(param_3 + CONCAT31(uVar32,cVar29) * 4) +
                              *pfVar9 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + -0x61) * 4) +
                              *pfVar8 * *(float *)(param_3 + CONCAT31(uVar32,cVar28) * 4) +
                              *pfVar7 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + '\x7f') * 4) +
                              *pfVar6 * *(float *)(param_3 + CONCAT31(uVar32,cVar27) * 4) +
                              *pfVar5 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + '_') * 4) +
                              *pfVar4 * *(float *)(param_3 + CONCAT31(uVar32,cVar26) * 4) +
                              *pfVar3 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + '?') * 4) +
                              *pfVar2 * *(float *)(param_3 + CONCAT31(uVar32,cVar25) * 4) +
                              *pfVar1 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + '\x1f') * 4) +
                              *pfVar33 * *(float *)(param_3 + CONCAT31(uVar32,cVar24) * 4) +
                              fVar17 * *(float *)(param_3 + CONCAT31(uVar22,cVar20 + -1) * 4) + 0.0)
    ;
    if (DAT_00569344 < 0x8000) {
      iVar18 = DAT_00569344;
      if (DAT_00569344 < -0x8000) {
        iVar18 = -0x8000;
      }
    }
    else {
      iVar18 = 0x7fff;
    }
    *(byte *)(param_5 + 0x10 + iVar19) = (byte)((uint)iVar18 >> 8) ^ 0x80;
    iVar19 = iVar19 + 1;
  } while (iVar19 != 0);
  return CONCAT44(param_2,in_EAX);
}

