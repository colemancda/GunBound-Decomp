/* WriteRegistryDword - 0x0040c550 in the original binary.
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


void __fastcall WriteRegistryDword(undefined4 param_1,undefined4 param_2,int param_3)

{
  BYTE BVar1;
  int iVar2;
  LSTATUS LVar3;
  BYTE *pBVar4;
  int iVar5;
  HKEY local_d4;
  BYTE local_d0 [16];
  undefined4 local_c0 [16];
  char local_80 [128];
  
  _sprintf(local_80,s_modes__d__d__d_00552030,param_2,param_1);
  __itoa(param_3,(char *)local_d0,10);
  iVar2 = FUN_0040c250(s_display_00552028,local_c0,0x10,0);
  iVar5 = 0;
  if (0 < iVar2) {
    do {
      LVar3 = RegOpenKeyExA((HKEY)local_c0[iVar5],local_80,0,2,&local_d4);
      if (LVar3 == 0) {
        pBVar4 = local_d0;
        do {
          BVar1 = *pBVar4;
          pBVar4 = pBVar4 + 1;
        } while (BVar1 != '\0');
        RegSetValueExA(local_d4,s_RefreshRate_0055201c,0,1,local_d0,
                       (DWORD)(pBVar4 + (1 - (int)(local_d0 + 1))));
        RegCloseKey(local_d4);
      }
      RegCloseKey((HKEY)local_c0[iVar5]);
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar2);
  }
  return;
}

