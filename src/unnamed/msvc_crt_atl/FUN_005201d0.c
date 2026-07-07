/* FUN_005201d0 - 0x005201d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: virtual void * __thiscall _com_error::`scalar deleting destructor'(unsigned int)
   
   Library: Visual Studio 2003 Release */

void * __thiscall _com_error::_scalar_deleting_destructor_(_com_error *this,uint param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(this + 8);
  *(undefined ***)this = &PTR__scalar_deleting_destructor__00544b54;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  if (*(HLOCAL *)(this + 0xc) != (HLOCAL)0x0) {
    LocalFree(*(HLOCAL *)(this + 0xc));
  }
  if ((param_1 & 1) != 0) {
    _free(this);
  }
  return this;
}

