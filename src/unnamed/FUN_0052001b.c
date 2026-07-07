/* FUN_0052001b - 0x0052001b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: virtual void * __thiscall ATL::CWin32Heap::`scalar deleting destructor'(unsigned int)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void * __thiscall ATL::CWin32Heap::_scalar_deleting_destructor_(CWin32Heap *this,uint param_1)

{
  ~CWin32Heap(this);
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

