/* FUN_00530885 - 0x00530885 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __set_errno
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl __set_errno(int _Value)

{
  undefined4 *puVar1;
  
  if (_Value == 1) {
    _Value = FUN_0052b6d4();
    *(undefined4 *)_Value = 0x21;
  }
  else if ((1 < _Value) && (_Value < 4)) {
    puVar1 = (undefined4 *)FUN_0052b6d4();
    *puVar1 = 0x22;
    return (errno_t)puVar1;
  }
  return _Value;
}

