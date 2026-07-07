/* FUN_005246e0 - 0x005246e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


HCRYPTPROV * __fastcall FUN_005246e0(HCRYPTPROV *param_1)

{
  BOOL BVar1;
  
  param_1[5] = 0;
  param_1[3] = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[9] = 0;
  param_1[0xe] = 0;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  param_1[8] = 0;
  param_1[0x11] = 0;
  param_1[4] = 0;
  BVar1 = CryptAcquireContextA
                    (param_1,(LPCSTR)0x0,s_Microsoft_Base_Cryptographic_Pro_0056ae50,1,0xf0000000);
  if (BVar1 == 0) {
    *param_1 = 0;
  }
  return param_1;
}

