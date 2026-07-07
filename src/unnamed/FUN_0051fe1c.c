/* FUN_0051fe1c - 0x0051fe1c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: void __thiscall ATL::CSimpleArray<struct HINSTANCE__ *,class
   ATL::CSimpleArrayEqualHelper<struct HINSTANCE__ *> >::RemoveAll(void)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release, Visual Studio 2008 Release,
   Visual Studio 2010 Release */

void __thiscall
ATL::CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_>::RemoveAll
          (CSimpleArray<HINSTANCE__*,ATL::CSimpleArrayEqualHelper<HINSTANCE__*>_> *this)

{
  if (*(void **)this != (void *)0x0) {
    _free(*(void **)this);
    *(undefined4 *)this = 0;
  }
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  return;
}

