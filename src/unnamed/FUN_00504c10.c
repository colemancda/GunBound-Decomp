/* FUN_00504c10 - 0x00504c10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00504c10(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  DWORD DVar4;
  DWORD DVar5;
  uint uVar6;
  undefined4 *unaff_ESI;
  uint uVar7;
  
  *unaff_ESI = 0;
  DVar4 = GetTickCount();
  unaff_ESI[1] = DVar4 ^ 0x95f24dab;
  DVar4 = GetCurrentThreadId();
  DVar5 = GetTickCount();
  unaff_ESI[2] = DVar4 ^ DVar5 ^ 0xb685215;
  DVar4 = GetCurrentProcessId();
  DVar5 = GetTickCount();
  unaff_ESI[3] = DVar4 ^ DVar5 ^ 0xe76ccae7;
  uVar6 = FID_conflict___time32((__time32_t *)0x0);
  DVar4 = GetTickCount();
  unaff_ESI[4] = uVar6 ^ DVar4 ^ 0xaf3ec239;
  uVar6 = _clock();
  DVar4 = GetVersion();
  DVar5 = GetTickCount();
  uVar7 = uVar6 ^ DVar4 ^ DVar5;
  uVar6 = unaff_ESI[1];
  unaff_ESI[6] = uVar6 ^ 0x24a590ad;
  uVar1 = unaff_ESI[2];
  unaff_ESI[7] = uVar1 ^ 0x69e4b5ef;
  uVar2 = unaff_ESI[3];
  unaff_ESI[8] = uVar2 ^ 0xbf456141;
  uVar3 = unaff_ESI[4];
  unaff_ESI[9] = uVar3 ^ 0x96bc1b7b;
  unaff_ESI[10] = uVar7 ^ 0xd6e25506;
  unaff_ESI[0xb] = uVar6 ^ 0xc1de75b7;
  unaff_ESI[0xc] = uVar1 ^ 0x8858a9c9;
  unaff_ESI[0xd] = uVar2 ^ 0x2da87693;
  unaff_ESI[0xe] = uVar3 ^ 0xb657f9dd;
  unaff_ESI[0xf] = uVar7 ^ 0x8e8327bc;
  unaff_ESI[0x10] = uVar6 ^ 0x8121da71;
  unaff_ESI[0x11] = uVar1 ^ 0x8b823ecb;
  unaff_ESI[0x12] = uVar2 ^ 0x885d05f5;
  unaff_ESI[5] = uVar7 ^ 0x715fad23;
  unaff_ESI[0x13] = uVar3 ^ 0x4e20cd47;
  unaff_ESI[0x19] = uVar7 ^ 0xd7e807f8;
  unaff_ESI[0x14] = uVar7 ^ 0x2bc578fa;
  unaff_ESI[0x15] = uVar6 ^ 0x512c0c03;
  unaff_ESI[0x18] = uVar3 ^ 0x8891a8a1;
  unaff_ESI[0x16] = uVar1 ^ 0xea857ccd;
  unaff_ESI[0x17] = uVar2 ^ 0x4cc1d30f;
  unaff_ESI[0x1a] = 0;
  unaff_ESI[0x1b] = 0x8ebfd028;
  return;
}

