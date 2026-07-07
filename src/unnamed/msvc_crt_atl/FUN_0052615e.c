/* FUN_0052615e - 0x0052615e in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _fclose
   
   Library: Visual Studio 2003 Release */

int __cdecl _fclose(FILE *_File)

{
  int local_20;
  
  local_20 = -1;
  if ((_File->_flag & 0x40) == 0) {
    __lock_file(_File);
    local_20 = __fclose_lk(_File);
    FUN_005261a7();
  }
  else {
    _File->_flag = 0;
  }
  return local_20;
}

