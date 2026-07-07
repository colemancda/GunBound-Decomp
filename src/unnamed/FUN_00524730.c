/* FUN_00524730 - 0x00524730 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00524730(HCRYPTPROV *param_1)

{
  if ((void *)param_1[1] != (void *)0x0) {
    _free((void *)param_1[1]);
  }
  if ((void *)param_1[5] != (void *)0x0) {
    _free((void *)param_1[5]);
  }
  if (param_1[3] != 0) {
    CryptDestroyHash(param_1[3]);
  }
  if (param_1[4] != 0) {
    CryptDestroyKey(param_1[4]);
  }
  if (param_1[0xf] != 0) {
    CryptDestroyKey(param_1[0xf]);
  }
  if (param_1[0x10] != 0) {
    CryptDestroyHash(param_1[0x10]);
  }
  if (*param_1 != 0) {
    CryptReleaseContext(*param_1,0);
  }
  return;
}

