/* FUN_00513850 - 0x00513850 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00513850(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < DAT_00563b44) {
    do {
      if ((&DAT_005ab604)[iVar1] != 0) {
        if (DAT_005ab704 < 6) {
          for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
            DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
            DAT_005a9680 = DAT_005a9680 + 1;
          }
        }
        DAT_005ab704 = DAT_005ab704 + -6;
        _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
        *(float *)(PTR_DAT_00563b40 + iVar1 * 4) =
             (float)(&DAT_005a9888)[_DAT_005ab888] * (float)(&DAT_005a9684)[iVar1];
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < DAT_00563b44);
  }
  return;
}

