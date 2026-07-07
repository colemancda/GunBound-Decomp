/* FUN_00412e00 - 0x00412e00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00412e00(undefined4 param_1)

{
  FILE *_File;
  uint uVar1;
  int iVar2;
  char *unaff_EDI;
  
  iVar2 = 1;
  do {
    _sprintf(unaff_EDI,s__s_s_07d_bmp_00552220,param_1);
    _File = (FILE *)FUN_00525fac();
    if (_File == (FILE *)0x0) {
      return 1;
    }
    uVar1 = _fclose(_File);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 1000000);
  return uVar1 & 0xffffff00;
}

