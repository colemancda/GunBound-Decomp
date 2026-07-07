/* FUN_00525da3 - 0x00525da3 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: __thiscall exception::exception(char const * const &)
   
   Library: Visual Studio 2003 Release */

exception * __thiscall exception::exception(exception *this,char **param_1)

{
  size_t sVar1;
  void *pvVar2;
  
  *(undefined ***)this = &PTR_FUN_00544c50;
  sVar1 = _strlen(*param_1);
  pvVar2 = _malloc(sVar1 + 1);
  *(void **)(this + 4) = pvVar2;
  if (pvVar2 != (void *)0x0) {
    FUN_0052baa0(pvVar2,*param_1);
  }
  *(undefined4 *)(this + 8) = 1;
  return this;
}

