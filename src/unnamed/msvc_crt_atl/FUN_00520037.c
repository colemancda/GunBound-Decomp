/* FUN_00520037 - 0x00520037 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: __thiscall ATL::CAtlStringMgr::CAtlStringMgr(struct ATL::IAtlMemMgr *)
   
   Library: Visual Studio 2003 Release */

void __thiscall ATL::CAtlStringMgr::CAtlStringMgr(CAtlStringMgr *this,IAtlMemMgr *param_1)

{
  *(IAtlMemMgr **)(this + 4) = param_1;
  *(undefined ***)this = &PTR_Allocate_00544b38;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0x14) = 2;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined2 *)(this + 0x18) = 0;
  *(undefined2 *)(this + 0x1a) = 0;
  *(CAtlStringMgr **)(this + 8) = this;
  return;
}

