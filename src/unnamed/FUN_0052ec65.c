/* FUN_0052ec65 - 0x0052ec65 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __ms_p5_test_fdiv
   
   Library: Visual Studio 2003 Release */

undefined4 __ms_p5_test_fdiv(void)

{
  if (_DAT_00544e38 < _DAT_005456b0 - (_DAT_005456b0 / _DAT_005456b8) * _DAT_005456b8) {
    return 1;
  }
  return 0;
}

