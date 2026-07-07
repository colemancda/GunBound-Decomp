/* ReadRegistryDword - 0x0040c470 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall ReadRegistryDword(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  LSTATUS LVar2;
  int iVar3;
  HKEY local_dc;
  DWORD local_d8;
  BYTE local_d4 [16];
  DWORD local_c4;
  undefined4 local_c0 [16];
  char local_80 [128];
  
  local_d4[1] = '\0';
  local_d4[2] = '\0';
  local_d4[3] = '\0';
  local_d4[4] = '\0';
  local_d4[5] = '\0';
  local_d4[6] = '\0';
  local_d4[7] = '\0';
  local_d4[8] = '\0';
  local_d4[9] = '\0';
  local_d4[10] = '\0';
  local_d4[0xb] = '\0';
  local_d4[0xc] = '\0';
  local_d4[0xd] = '\0';
  local_d4[0xe] = '\0';
  local_d4[0xf] = 0;
  local_d4[0] = '\0';
  _sprintf(local_80,s_modes__d__d__d_00552030,param_3,param_2,param_1);
  iVar1 = FUN_0040c250(s_display_00552028,local_c0,0x10,0);
  iVar3 = 0;
  if (0 < iVar1) {
    do {
      LVar2 = RegOpenKeyExA((HKEY)local_c0[iVar3],local_80,0,0x20019,&local_dc);
      if (LVar2 == 0) {
        local_d8 = 0x10;
        RegQueryValueExA(local_dc,s_RefreshRate_0055201c,(LPDWORD)0x0,&local_c4,local_d4,&local_d8);
        RegCloseKey(local_dc);
      }
      RegCloseKey((HKEY)local_c0[iVar3]);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
  }
  _atol((char *)local_d4);
  return;
}

