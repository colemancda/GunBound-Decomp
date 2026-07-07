/* FUN_0051d044 - 0x0051d044 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall
FUN_0051d044(undefined4 param_1,undefined4 param_2,float *param_3,undefined4 *param_4)

{
  undefined4 *puVar1;
  undefined4 in_EAX;
  int iVar2;
  int iVar3;
  
  DAT_0056881c = param_4;
  DAT_00568840 = *param_3 + param_3[0x3e];
  DAT_00568880 = (*param_3 - param_3[0x3e]) * DAT_00f25a40;
  DAT_00568844 = param_3[2] + param_3[0x3c];
  DAT_00568884 = (param_3[2] - param_3[0x3c]) * _DAT_00f25a44;
  DAT_00568848 = param_3[4] + param_3[0x3a];
  DAT_00568888 = (param_3[4] - param_3[0x3a]) * _DAT_00f25a48;
  DAT_0056884c = param_3[6] + param_3[0x38];
  DAT_0056888c = (param_3[6] - param_3[0x38]) * _DAT_00f25a4c;
  DAT_00568850 = param_3[8] + param_3[0x36];
  DAT_00568890 = (param_3[8] - param_3[0x36]) * _DAT_00f25a50;
  DAT_00568854 = param_3[10] + param_3[0x34];
  DAT_00568894 = (param_3[10] - param_3[0x34]) * _DAT_00f25a54;
  DAT_00568858 = param_3[0xc] + param_3[0x32];
  DAT_00568898 = (param_3[0xc] - param_3[0x32]) * _DAT_00f25a58;
  DAT_0056885c = param_3[0xe] + param_3[0x30];
  DAT_0056889c = (param_3[0xe] - param_3[0x30]) * _DAT_00f25a5c;
  DAT_00568860 = param_3[0x10] + param_3[0x2e];
  DAT_005688a0 = (param_3[0x10] - param_3[0x2e]) * _DAT_00f25a60;
  DAT_00568864 = param_3[0x12] + param_3[0x2c];
  _DAT_005688a4 = (param_3[0x12] - param_3[0x2c]) * _DAT_00f25a64;
  DAT_00568868 = param_3[0x14] + param_3[0x2a];
  _DAT_005688a8 = (param_3[0x14] - param_3[0x2a]) * _DAT_00f25a68;
  DAT_0056886c = param_3[0x16] + param_3[0x28];
  _DAT_005688ac = (param_3[0x16] - param_3[0x28]) * _DAT_00f25a6c;
  DAT_00568870 = param_3[0x18] + param_3[0x26];
  _DAT_005688b0 = (param_3[0x18] - param_3[0x26]) * _DAT_00f25a70;
  DAT_00568874 = param_3[0x1a] + param_3[0x24];
  _DAT_005688b4 = (param_3[0x1a] - param_3[0x24]) * _DAT_00f25a74;
  DAT_00568878 = param_3[0x1c] + param_3[0x22];
  DAT_005688b8 = (param_3[0x1c] - param_3[0x22]) * _DAT_00f25a78;
  DAT_0056887c = param_3[0x1e] + param_3[0x20];
  DAT_005688bc = (param_3[0x1e] - param_3[0x20]) * _DAT_00f25a7c;
  iVar3 = 0;
  iVar2 = 2;
  do {
    (&DAT_005688c0)[iVar3] = (&DAT_00568840)[iVar3] + (&DAT_0056887c)[iVar3];
    (&DAT_005688e0)[iVar3] = ((&DAT_00568840)[iVar3] - (&DAT_0056887c)[iVar3]) * DAT_00f25a80;
    (&DAT_005688c4)[iVar3] = (&DAT_00568844)[iVar3] + (&DAT_00568878)[iVar3];
    (&DAT_005688e4)[iVar3] = ((&DAT_00568844)[iVar3] - (&DAT_00568878)[iVar3]) * DAT_00f25a84;
    (&DAT_005688c8)[iVar3] = (&DAT_00568848)[iVar3] + (&DAT_00568874)[iVar3];
    (&DAT_005688e8)[iVar3] = ((&DAT_00568848)[iVar3] - (&DAT_00568874)[iVar3]) * DAT_00f25a88;
    (&DAT_005688cc)[iVar3] = (&DAT_0056884c)[iVar3] + (&DAT_00568870)[iVar3];
    (&DAT_005688ec)[iVar3] = ((&DAT_0056884c)[iVar3] - (&DAT_00568870)[iVar3]) * _DAT_00f25a8c;
    (&DAT_005688d0)[iVar3] = (&DAT_00568850)[iVar3] + (&DAT_0056886c)[iVar3];
    (&DAT_005688f0)[iVar3] = ((&DAT_00568850)[iVar3] - (&DAT_0056886c)[iVar3]) * _DAT_00f25a90;
    (&DAT_005688d4)[iVar3] = (&DAT_00568854)[iVar3] + (&DAT_00568868)[iVar3];
    (&DAT_005688f4)[iVar3] = ((&DAT_00568854)[iVar3] - (&DAT_00568868)[iVar3]) * _DAT_00f25a94;
    (&DAT_005688d8)[iVar3] = (&DAT_00568858)[iVar3] + (&DAT_00568864)[iVar3];
    (&DAT_005688f8)[iVar3] = ((&DAT_00568858)[iVar3] - (&DAT_00568864)[iVar3]) * _DAT_00f25a98;
    (&DAT_005688dc)[iVar3] = (&DAT_0056885c)[iVar3] + (&DAT_00568860)[iVar3];
    (&DAT_005688fc)[iVar3] = ((&DAT_0056885c)[iVar3] - (&DAT_00568860)[iVar3]) * _DAT_00f25a9c;
    iVar3 = iVar3 + 0x10;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar3 = 0;
  iVar2 = 4;
  do {
    (&DAT_00568840)[iVar3] = (float)(&DAT_005688c0)[iVar3] + (float)(&DAT_005688dc)[iVar3];
    (&DAT_00568850)[iVar3] =
         ((float)(&DAT_005688c0)[iVar3] - (float)(&DAT_005688dc)[iVar3]) * DAT_00f25aa0;
    (&DAT_00568844)[iVar3] = (float)(&DAT_005688c4)[iVar3] + (float)(&DAT_005688d8)[iVar3];
    (&DAT_00568854)[iVar3] =
         ((float)(&DAT_005688c4)[iVar3] - (float)(&DAT_005688d8)[iVar3]) * DAT_00f25aa4;
    (&DAT_00568848)[iVar3] = (float)(&DAT_005688c8)[iVar3] + (float)(&DAT_005688d4)[iVar3];
    (&DAT_00568858)[iVar3] =
         ((float)(&DAT_005688c8)[iVar3] - (float)(&DAT_005688d4)[iVar3]) * DAT_00f25aa8;
    (&DAT_0056884c)[iVar3] = (float)(&DAT_005688cc)[iVar3] + (float)(&DAT_005688d0)[iVar3];
    (&DAT_0056885c)[iVar3] =
         ((float)(&DAT_005688cc)[iVar3] - (float)(&DAT_005688d0)[iVar3]) * _DAT_00f25aac;
    iVar3 = iVar3 + 8;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar3 = 0;
  iVar2 = 8;
  do {
    (&DAT_005688c0)[iVar3] = (&DAT_00568840)[iVar3] + (&DAT_0056884c)[iVar3];
    (&DAT_005688c8)[iVar3] = ((&DAT_00568840)[iVar3] - (&DAT_0056884c)[iVar3]) * DAT_00f25ab0;
    (&DAT_005688c4)[iVar3] = (&DAT_00568844)[iVar3] + (&DAT_00568848)[iVar3];
    (&DAT_005688cc)[iVar3] = ((&DAT_00568844)[iVar3] - (&DAT_00568848)[iVar3]) * DAT_00f25ab4;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar3 = 0;
  iVar2 = 0x10;
  do {
    (&DAT_00568840)[iVar3] = (float)(&DAT_005688c0)[iVar3] + (float)(&DAT_005688c4)[iVar3];
    (&DAT_00568844)[iVar3] =
         ((float)(&DAT_005688c0)[iVar3] - (float)(&DAT_005688c4)[iVar3]) * _DAT_00f25ab8;
    iVar3 = iVar3 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = 0;
  iVar3 = 8;
  do {
    *(undefined4 *)((int)&DAT_005688c0 + iVar2) = *(undefined4 *)((int)&DAT_00568840 + iVar2);
    *(undefined4 *)((int)&DAT_005688c8 + iVar2) = *(undefined4 *)((int)&DAT_00568844 + iVar2);
    *(float *)((int)&DAT_005688c4 + iVar2) =
         *(float *)((int)&DAT_00568848 + iVar2) + *(float *)((int)&DAT_0056884c + iVar2);
    *(undefined4 *)((int)&DAT_005688cc + iVar2) = *(undefined4 *)((int)&DAT_0056884c + iVar2);
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar2 = 0;
  iVar3 = 4;
  do {
    *(undefined4 *)((int)&DAT_00568840 + iVar2) = *(undefined4 *)((int)&DAT_005688c0 + iVar2);
    *(undefined4 *)((int)&DAT_00568848 + iVar2) = *(undefined4 *)((int)&DAT_005688c4 + iVar2);
    *(undefined4 *)((int)&DAT_00568850 + iVar2) = *(undefined4 *)((int)&DAT_005688c8 + iVar2);
    *(undefined4 *)((int)&DAT_00568858 + iVar2) = *(undefined4 *)((int)&DAT_005688cc + iVar2);
    *(float *)((int)&DAT_00568844 + iVar2) =
         *(float *)((int)&DAT_005688d0 + iVar2) + *(float *)((int)&DAT_005688d4 + iVar2);
    *(float *)((int)&DAT_0056884c + iVar2) =
         *(float *)((int)&DAT_005688d4 + iVar2) + *(float *)((int)&DAT_005688d8 + iVar2);
    *(float *)((int)&DAT_00568854 + iVar2) =
         *(float *)((int)&DAT_005688d8 + iVar2) + *(float *)((int)&DAT_005688dc + iVar2);
    *(undefined4 *)((int)&DAT_0056885c + iVar2) = *(undefined4 *)((int)&DAT_005688dc + iVar2);
    iVar2 = iVar2 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar2 = 0;
  iVar3 = 2;
  do {
    *(undefined4 *)((int)&DAT_005688c0 + iVar2) = *(undefined4 *)((int)&DAT_00568840 + iVar2);
    *(undefined4 *)((int)&DAT_005688c8 + iVar2) = *(undefined4 *)((int)&DAT_00568844 + iVar2);
    *(undefined4 *)((int)&DAT_005688d0 + iVar2) = *(undefined4 *)((int)&DAT_00568848 + iVar2);
    *(undefined4 *)((int)&DAT_005688d8 + iVar2) = *(undefined4 *)((int)&DAT_0056884c + iVar2);
    *(undefined4 *)((int)&DAT_005688e0 + iVar2) = *(undefined4 *)((int)&DAT_00568850 + iVar2);
    *(undefined4 *)((int)&DAT_005688e8 + iVar2) = *(undefined4 *)((int)&DAT_00568854 + iVar2);
    *(undefined4 *)((int)&DAT_005688f0 + iVar2) = *(undefined4 *)((int)&DAT_00568858 + iVar2);
    *(undefined4 *)((int)&DAT_005688f8 + iVar2) = *(undefined4 *)((int)&DAT_0056885c + iVar2);
    *(float *)((int)&DAT_005688c4 + iVar2) =
         *(float *)((int)&DAT_00568860 + iVar2) + *(float *)((int)&DAT_00568864 + iVar2);
    *(float *)((int)&DAT_005688cc + iVar2) =
         *(float *)((int)&DAT_00568864 + iVar2) + *(float *)((int)&DAT_00568868 + iVar2);
    *(float *)((int)&DAT_005688d4 + iVar2) =
         *(float *)((int)&DAT_00568868 + iVar2) + *(float *)((int)&DAT_0056886c + iVar2);
    *(float *)((int)&DAT_005688dc + iVar2) =
         *(float *)((int)&DAT_0056886c + iVar2) + *(float *)((int)&DAT_00568870 + iVar2);
    *(float *)((int)&DAT_005688e4 + iVar2) =
         *(float *)((int)&DAT_00568870 + iVar2) + *(float *)((int)&DAT_00568874 + iVar2);
    *(float *)((int)&DAT_005688ec + iVar2) =
         *(float *)((int)&DAT_00568874 + iVar2) + *(float *)((int)&DAT_00568878 + iVar2);
    *(float *)((int)&DAT_005688f4 + iVar2) =
         *(float *)((int)&DAT_00568878 + iVar2) + *(float *)((int)&DAT_0056887c + iVar2);
    *(undefined4 *)((int)&DAT_005688fc + iVar2) = *(undefined4 *)((int)&DAT_0056887c + iVar2);
    puVar1 = DAT_0056881c;
    iVar2 = iVar2 + 0x40;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *DAT_0056881c = DAT_005688c0;
  puVar1[2] = DAT_005688c4;
  puVar1[4] = DAT_005688c8;
  puVar1[6] = DAT_005688cc;
  puVar1[8] = DAT_005688d0;
  puVar1[10] = DAT_005688d4;
  puVar1[0xc] = DAT_005688d8;
  puVar1[0xe] = DAT_005688dc;
  puVar1[0x10] = DAT_005688e0;
  puVar1[0x12] = DAT_005688e4;
  puVar1[0x14] = DAT_005688e8;
  puVar1[0x16] = DAT_005688ec;
  puVar1[0x18] = DAT_005688f0;
  puVar1[0x1a] = DAT_005688f4;
  puVar1[0x1c] = DAT_005688f8;
  puVar1[0x1e] = DAT_005688fc;
  puVar1[1] = DAT_00568900 + DAT_00568904;
  puVar1[3] = DAT_00568904 + DAT_00568908;
  puVar1[5] = DAT_00568908 + DAT_0056890c;
  puVar1[7] = DAT_0056890c + DAT_00568910;
  puVar1[9] = DAT_00568910 + DAT_00568914;
  puVar1[0xb] = DAT_00568914 + DAT_00568918;
  puVar1[0xd] = DAT_00568918 + DAT_0056891c;
  puVar1[0xf] = DAT_0056891c + DAT_00568920;
  puVar1[0x11] = DAT_00568920 + DAT_00568924;
  puVar1[0x13] = DAT_00568924 + DAT_00568928;
  puVar1[0x15] = DAT_00568928 + DAT_0056892c;
  puVar1[0x17] = DAT_0056892c + DAT_00568930;
  puVar1[0x19] = DAT_00568930 + DAT_00568934;
  puVar1[0x1b] = DAT_00568934 + DAT_00568938;
  puVar1[0x1d] = DAT_00568938 + DAT_0056893c;
  puVar1[0x1f] = DAT_0056893c;
  return CONCAT44(param_2,in_EAX);
}

