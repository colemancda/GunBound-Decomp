/* FindFreeScreenshotFilename - 0x00412e00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00412e00 mean this function.)
 *
 * NAMED (batch 48), HIGH. Its only caller is SaveScreenshotBmp, which
 * hands it g_screenPath and a 1 KB buffer and then opens the result for
 * writing. It sprintf()s %s%s%07d.bmp (0x552220) for counters 1 up to
 * 999999, fopen()s each in read mode (0x55221c, the file's own r string)
 * and returns 1 on the first one that does not exist, leaving that name in
 * the buffer, or 0 after exhausting the range. The binary's sprintf pushes
 * three arguments (directory, EBX = the literal GunBound at 0x552748 as
 * prefix, ESI = the counter); the port's call passes only the first, the
 * other two being dropped register/local values.
 */
#include "ghidra_types.h"


uint FindFreeScreenshotFilename(undefined4 param_1,char *regEdi)

{
  FILE *_File;
  uint uVar1;
  int iVar2;
  
  iVar2 = 1;
  do {
    _sprintf(regEdi,s__s_s_07d_bmp_00552220,param_1);
    _File = (FILE *)FUN_00525fac();
    if (_File == (FILE *)0x0) {
      return 1;
    }
    uVar1 = _fclose(_File);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 1000000);
  return uVar1 & 0xffffff00;
}

