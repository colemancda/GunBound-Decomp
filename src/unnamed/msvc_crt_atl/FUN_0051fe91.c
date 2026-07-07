/* FUN_0051fe91 - 0x0051fe91 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: __thiscall ATL::CAtlBaseModule::~CAtlBaseModule(void)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void __thiscall ATL::CAtlBaseModule::~CAtlBaseModule(CAtlBaseModule *this)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)(this + 0x18));
  CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_>::RemoveAll
            ((CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_> *)(this + 0x30)
            );
  return;
}

