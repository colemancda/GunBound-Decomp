/* FUN_00537456 - 0x00537456 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __memicmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __memicmp(void *_Buf1,void *_Buf2,size_t _Size)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0056c48c) {
    ptVar2 = ___updatetlocinfo();
  }
  if (ptVar2->lc_category[0].wlocale == (wchar_t *)0x0) {
    local_8 = ___ascii_memicmp(_Buf1,_Buf2,_Size);
  }
  else {
    while ((_Size != 0 && (_Size = _Size - 1, local_8 == local_c))) {
      local_8 = ___tolower_mt(ptVar2,*(undefined1 *)_Buf1);
      _Buf1 = (void *)((int)_Buf1 + 1);
      local_c = ___tolower_mt(ptVar2,*(undefined1 *)_Buf2);
      _Buf2 = (void *)((int)_Buf2 + 1);
    }
    local_8 = local_8 - local_c;
  }
  return local_8;
}

