/* FUN_0052009c - 0x0052009c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: virtual struct ATL::CStringData * __thiscall ATL::CAtlStringMgr::Allocate(int,int)
   
   Library: Visual Studio 2003 Release */

CStringData * __thiscall ATL::CAtlStringMgr::Allocate(CAtlStringMgr *this,int param_1,int param_2)

{
  CStringData *pCVar1;
  uint uVar2;
  
  uVar2 = param_1 + 8U & 0xfffffff8;
  pCVar1 = (CStringData *)(**(code **)**(undefined4 **)(this + 4))(uVar2 * param_2 + 0x10);
  if (pCVar1 != (CStringData *)0x0) {
    *(undefined4 *)(pCVar1 + 4) = 0;
    *(CAtlStringMgr **)pCVar1 = this;
    *(undefined4 *)(pCVar1 + 0xc) = 1;
    *(uint *)(pCVar1 + 8) = uVar2 - 1;
  }
  return pCVar1;
}

