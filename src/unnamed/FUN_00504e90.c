/* FUN_00504e90 - 0x00504e90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00504e90(void)

{
  DWORD DVar1;
  DWORD DVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  if ((DAT_00f258a8 & 1) == 0) {
    DAT_00f258a8 = DAT_00f258a8 | 1;
    DVar1 = GetTickCount();
    DAT_00f25840 = DVar1 ^ 0x95f24dab;
    DVar1 = GetCurrentThreadId();
    DVar2 = GetTickCount();
    DAT_00f25844 = DVar1 ^ DVar2 ^ 0xb685215;
    DVar1 = GetCurrentProcessId();
    DVar2 = GetTickCount();
    DAT_00f25848 = DVar1 ^ DVar2 ^ 0xe76ccae7;
    uVar3 = FID_conflict___time32((__time32_t *)0x0);
    DVar1 = GetTickCount();
    DAT_00f2584c = uVar3 ^ DVar1 ^ 0xaf3ec239;
    DVar1 = GetVersion();
    DVar2 = GetTickCount();
    _DAT_00f258a0 = DVar1 ^ DVar2;
    DAT_00f25854 = DAT_00f25840 ^ 0x24a590ad;
    DAT_00f25858 = DAT_00f25844 ^ 0x69e4b5ef;
    DAT_00f2585c = DAT_00f25848 ^ 0xbf456141;
    DAT_00f25850 = _DAT_00f258a0 ^ 0x715fad23;
    DAT_00f25860 = DAT_00f2584c ^ 0x96bc1b7b;
    DAT_00f25864 = _DAT_00f258a0 ^ 0xd6e25506;
    DAT_00f25868 = DAT_00f25840 ^ 0xc1de75b7;
    DAT_00f2586c = DAT_00f25844 ^ 0x8858a9c9;
    DAT_00f25870 = DAT_00f25848 ^ 0x2da87693;
    DAT_00f25874 = DAT_00f2584c ^ 0xb657f9dd;
    DAT_00f25878 = _DAT_00f258a0 ^ 0x8e8327bc;
    DAT_00f2587c = DAT_00f25840 ^ 0x8121da71;
    DAT_00f25880 = DAT_00f25844 ^ 0x8b823ecb;
    _DAT_00f25884 = DAT_00f25848 ^ 0x885d05f5;
    _DAT_00f25888 = DAT_00f2584c ^ 0x4e20cd47;
    _DAT_00f2588c = _DAT_00f258a0 ^ 0x2bc578fa;
    _DAT_00f25890 = DAT_00f25840 ^ 0x512c0c03;
    _DAT_00f25894 = DAT_00f25844 ^ 0xea857ccd;
    _DAT_00f25898 = DAT_00f25848 ^ 0x4cc1d30f;
    _DAT_00f2589c = DAT_00f2584c ^ 0x8891a8a1;
    _DAT_00f258a0 = _DAT_00f258a0 ^ 0xd7e807f8;
  }
  if (DAT_00f258a4 == 0x19) {
    iVar4 = 0;
    do {
      (&DAT_00f25840)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f25840)[iVar4] & 1) * 4) ^ (&DAT_00f2585c)[iVar4] ^
           (&DAT_00f25840)[iVar4] >> 1;
      (&DAT_00f25844)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f25844)[iVar4] & 1) * 4) ^ (&DAT_00f25860)[iVar4] ^
           (&DAT_00f25844)[iVar4] >> 1;
      (&DAT_00f25848)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f25848)[iVar4] & 1) * 4) ^ (&DAT_00f25864)[iVar4] ^
           (&DAT_00f25848)[iVar4] >> 1;
      (&DAT_00f2584c)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f2584c)[iVar4] & 1) * 4) ^ (&DAT_00f25868)[iVar4] ^
           (&DAT_00f2584c)[iVar4] >> 1;
      (&DAT_00f25850)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f25850)[iVar4] & 1) * 4) ^ (&DAT_00f2586c)[iVar4] ^
           (&DAT_00f25850)[iVar4] >> 1;
      (&DAT_00f25854)[iVar4] =
           *(uint *)(&DAT_005a965c + ((&DAT_00f25854)[iVar4] & 1) * 4) ^ (&DAT_00f25870)[iVar4] ^
           (&DAT_00f25854)[iVar4] >> 1;
      iVar4 = iVar4 + 6;
    } while (iVar4 < 0x12);
    if (iVar4 < 0x19) {
      puVar5 = &DAT_00f25840 + iVar4;
      do {
        *puVar5 = *puVar5 >> 1 ^ *(uint *)(&DAT_005a965c + (*puVar5 & 1) * 4) ^ puVar5[-0x12];
        puVar5 = puVar5 + 1;
      } while ((int)puVar5 < 0xf258a4);
    }
    DAT_00f258a4 = 0;
  }
  uVar3 = (&DAT_00f25840)[DAT_00f258a4] ^ ((&DAT_00f25840)[DAT_00f258a4] & 0x56b64a) << 7;
  uVar3 = uVar3 ^ (uVar3 & 0xffffb716) << 0xf;
  DAT_00f258a4 = DAT_00f258a4 + 1;
  return uVar3 >> 0x10 ^ uVar3;
}

