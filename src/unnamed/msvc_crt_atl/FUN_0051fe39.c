/* FUN_0051fe39 - 0x0051fe39 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: struct HINSTANCE__ * & __thiscall ATL::CSimpleArray<struct HINSTANCE__ *,class
   ATL::CSimpleArrayEqualHelper<struct HINSTANCE__ *> >::operator[](int)
   
   Library: Visual Studio 2003 Release */

HINSTANCE__ ** __thiscall
ATL::CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_>::operator[]
          (CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_> *this,int param_1)

{
  code *pcVar1;
  HINSTANCE__ **ppHVar2;
  
  if ((-1 < param_1) && (param_1 < *(int *)(this + 4))) {
    return (HINSTANCE__ **)(*(int *)this + param_1 * 4);
  }
  RaiseException(0xc000008c,1,0,(ULONG_PTR *)0x0);
  pcVar1 = (code *)swi(3);
  ppHVar2 = (HINSTANCE__ **)(*pcVar1)();
  return ppHVar2;
}

