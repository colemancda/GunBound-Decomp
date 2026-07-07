/* FUN_00525ae1 - 0x00525ae1 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __endthread
   
   Library: Visual Studio 2003 Release */

void __cdecl __endthread(void)

{
  _ptiddata _Ptd;
  
  if (PTR_FUN_0056bf88 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0056bf88)();
  }
  _Ptd = __getptd();
  if (_Ptd == (_ptiddata)0x0) {
    __amsg_exit(0x10);
  }
  if ((HANDLE)_Ptd->_thandle != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)_Ptd->_thandle);
  }
  __freeptd(_Ptd);
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}

