/* FUN_0051fea7 - 0x0051fea7 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: struct HINSTANCE__ * __thiscall ATL::CAtlBaseModule::GetHInstanceAt(int)
   
   Library: Visual Studio 2003 Release */

HINSTANCE__ * __thiscall ATL::CAtlBaseModule::GetHInstanceAt(CAtlBaseModule *this,int param_1)

{
  HINSTANCE__ **ppHVar1;
  HINSTANCE__ *pHVar2;
  LPCRITICAL_SECTION local_c;
  CAtlBaseModule *local_8;
  
  local_c = (LPCRITICAL_SECTION)(this + 0x18);
  local_8 = this;
  EnterCriticalSection(local_c);
  local_8 = (CAtlBaseModule *)CONCAT31(local_8._1_3_,1);
  if ((*(int *)(this + 0x34) < param_1) || (param_1 < 0)) {
    pHVar2 = (HINSTANCE__ *)0x0;
  }
  else if (param_1 == *(int *)(this + 0x34)) {
    pHVar2 = *(HINSTANCE__ **)(this + 8);
  }
  else {
    ppHVar1 = CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_>::operator[]
                        ((CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_> *)
                         (this + 0x30),param_1);
    pHVar2 = *ppHVar1;
  }
  CComCritSecLock<ATL::CComCriticalSection>::~CComCritSecLock<ATL::CComCriticalSection>
            ((CComCritSecLock<ATL::CComCriticalSection> *)&local_c);
  return pHVar2;
}

