/* FUN_0052534d - 0x0052534d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___onexitinit
   
   Library: Visual Studio 2003 Release */

undefined4 ___onexitinit(void)

{
  DAT_00f29688 = _malloc(0x80);
  if (DAT_00f29688 == (undefined4 *)0x0) {
    return 0x18;
  }
  *DAT_00f29688 = 0;
  DAT_00f29684 = DAT_00f29688;
  return 0;
}

