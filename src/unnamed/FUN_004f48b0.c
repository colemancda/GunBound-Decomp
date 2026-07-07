/* FUN_004f48b0 - 0x004f48b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004f48b0(uint *param_1,uint param_2,byte param_3)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint *unaff_EDI;
  uint *local_8;
  
  if (((((param_2 & 7) == 0) && (0xf < param_2)) && (param_2 < 0x21)) && ((param_3 & 3) != 0)) {
    param_2 = param_2 >> 2;
    *(byte *)(unaff_EDI + 0x82) = (byte)unaff_EDI[0x82] ^ ((byte)unaff_EDI[0x82] ^ param_3) & 3;
    *unaff_EDI = param_2;
    uVar5 = param_2;
    if (param_2 < 5) {
      uVar5 = 4;
    }
    unaff_EDI[1] = uVar5 + 6;
    puVar1 = unaff_EDI + 2;
    *puVar1 = *param_1;
    unaff_EDI[3] = param_1[1];
    unaff_EDI[4] = param_1[2];
    unaff_EDI[5] = param_1[3];
    puVar3 = puVar1 + (((uVar5 + 6) * 4 + 4) - param_2);
    if (param_2 == 4) {
      puVar6 = &DAT_0054cb00;
      do {
        uVar5 = puVar1[3];
        uVar2 = (uint)(&PTR_DAT_0054f378)[uVar5 >> 0x18] ^
                *(uint *)(&DAT_0054ef78 + (uVar5 >> 0x10 & 0xff) * 4) ^
                *(uint *)(&DAT_0054eb78 + (uVar5 >> 8 & 0xff) * 4) ^
                *(uint *)(&DAT_0054f778 + (uVar5 & 0xff) * 4) ^ *puVar1 ^ *puVar6;
        uVar4 = puVar1[1] ^ uVar2;
        puVar1[4] = uVar2;
        uVar2 = puVar1[2] ^ uVar4;
        puVar1[6] = uVar2;
        puVar1[5] = uVar4;
        puVar1[7] = uVar2 ^ uVar5;
        puVar1 = puVar1 + 4;
        puVar6 = puVar6 + 1;
      } while (puVar1 < puVar3);
    }
    else if (param_2 == 6) {
      unaff_EDI[6] = param_1[4];
      unaff_EDI[7] = param_1[5];
      local_8 = &DAT_0054cb00;
      do {
        uVar5 = puVar1[5];
        uVar2 = *local_8;
        local_8 = local_8 + 1;
        uVar2 = (uint)(&PTR_DAT_0054f378)[uVar5 >> 0x18] ^
                *(uint *)(&DAT_0054ef78 + (uVar5 >> 0x10 & 0xff) * 4) ^
                *(uint *)(&DAT_0054eb78 + (uVar5 >> 8 & 0xff) * 4) ^
                *(uint *)(&DAT_0054f778 + (uVar5 & 0xff) * 4) ^ *puVar1 ^ uVar2;
        uVar4 = puVar1[1] ^ uVar2;
        uVar7 = puVar1[2] ^ uVar4;
        puVar1[6] = uVar2;
        puVar1[7] = uVar4;
        uVar4 = puVar1[3] ^ uVar7;
        uVar2 = puVar1[4] ^ uVar4;
        puVar1[10] = uVar2;
        puVar1[8] = uVar7;
        puVar1[9] = uVar4;
        puVar1[0xb] = uVar2 ^ uVar5;
        puVar1 = puVar1 + 6;
      } while (puVar1 < puVar3);
    }
    else if (param_2 == 8) {
      unaff_EDI[6] = param_1[4];
      unaff_EDI[7] = param_1[5];
      unaff_EDI[8] = param_1[6];
      unaff_EDI[9] = param_1[7];
      puVar6 = &DAT_0054cb00;
      do {
        uVar5 = puVar1[7];
        uVar4 = (uint)(&PTR_DAT_0054f378)[uVar5 >> 0x18] ^
                *(uint *)(&DAT_0054ef78 + (uVar5 >> 0x10 & 0xff) * 4) ^
                *(uint *)(&DAT_0054eb78 + (uVar5 >> 8 & 0xff) * 4) ^
                *(uint *)(&DAT_0054f778 + (uint)(byte)puVar1[7] * 4) ^ *puVar1 ^ *puVar6;
        uVar2 = puVar1[1] ^ uVar4;
        puVar1[8] = uVar4;
        uVar4 = puVar1[2] ^ uVar2;
        puVar1[9] = uVar2;
        puVar6 = puVar6 + 1;
        puVar1[10] = uVar4;
        uVar4 = puVar1[3] ^ uVar4;
        puVar1[0xb] = uVar4;
        uVar2 = *(uint *)(&DAT_0054f778 + (uVar4 >> 0x18) * 4) ^
                (uint)(&PTR_DAT_0054f378)[uVar4 >> 0x10 & 0xff] ^
                *(uint *)(&DAT_0054ef78 + (uVar4 >> 8 & 0xff) * 4) ^
                *(uint *)(&DAT_0054eb78 + (uint)(byte)puVar1[0xb] * 4) ^ puVar1[4];
        uVar4 = puVar1[5] ^ uVar2;
        puVar1[0xc] = uVar2;
        uVar2 = puVar1[6] ^ uVar4;
        puVar1[0xe] = uVar2;
        puVar1[0xd] = uVar4;
        puVar1[0xf] = uVar2 ^ uVar5;
        puVar1 = puVar1 + 8;
      } while (puVar1 < puVar3);
    }
    if ((unaff_EDI[0x82] & 3) != 1) {
      puVar3 = unaff_EDI + unaff_EDI[1] * 4 + 0x42;
      *puVar3 = unaff_EDI[2];
      puVar3[1] = unaff_EDI[3];
      puVar3[2] = unaff_EDI[4];
      puVar3[3] = unaff_EDI[5];
      uVar5 = 1;
      puVar1 = unaff_EDI + 6;
      puVar3 = puVar3 + -4;
      if (1 < unaff_EDI[1]) {
        do {
          uVar2 = *puVar1;
          *puVar3 = *(uint *)(&DAT_00551778 + (uVar2 >> 0x18) * 4) ^
                    *(uint *)(&DAT_00551378 + (uVar2 >> 0x10 & 0xff) * 4) ^
                    *(uint *)(&DAT_00550f78 + (uVar2 >> 8 & 0xff) * 4) ^
                    *(uint *)(&DAT_00550b78 + (uint)(byte)*puVar1 * 4);
          uVar2 = puVar1[1];
          puVar3[1] = *(uint *)(&DAT_00551778 + (uVar2 >> 0x18) * 4) ^
                      *(uint *)(&DAT_00551378 + (uVar2 >> 0x10 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550f78 + (uVar2 >> 8 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550b78 + (uint)(byte)puVar1[1] * 4);
          uVar2 = puVar1[2];
          puVar3[2] = *(uint *)(&DAT_00551778 + (uVar2 >> 0x18) * 4) ^
                      *(uint *)(&DAT_00551378 + (uVar2 >> 0x10 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550f78 + (uVar2 >> 8 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550b78 + (uint)(byte)puVar1[2] * 4);
          uVar2 = puVar1[3];
          puVar3[3] = *(uint *)(&DAT_00551778 + (uVar2 >> 0x18) * 4) ^
                      *(uint *)(&DAT_00551378 + (uVar2 >> 0x10 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550f78 + (uVar2 >> 8 & 0xff) * 4) ^
                      *(uint *)(&DAT_00550b78 + (uint)(byte)puVar1[3] * 4);
          puVar1 = puVar1 + 4;
          puVar3 = puVar3 + -4;
          uVar5 = uVar5 + 1;
        } while (uVar5 < unaff_EDI[1]);
      }
      *puVar3 = *puVar1;
      puVar3[1] = puVar1[1];
      puVar3[2] = puVar1[2];
      puVar1 = (uint *)puVar1[3];
      puVar3[3] = (uint)puVar1;
    }
    return CONCAT22((short)((uint)puVar1 >> 0x10),1);
  }
  if (param_2 == 0) {
    return (int)(short)((short)*unaff_EDI << 2);
  }
  *(byte *)(unaff_EDI + 0x82) = (byte)unaff_EDI[0x82] & 0xfc;
  return 0;
}

