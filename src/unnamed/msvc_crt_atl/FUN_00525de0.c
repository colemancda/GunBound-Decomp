/* FUN_00525de0 - 0x00525de0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: __thiscall exception::exception(class exception const &)
   
   Library: Visual Studio 2003 Release */

exception * __thiscall exception::exception(exception *this,exception *param_1)

{
  int iVar1;
  size_t sVar2;
  void *pvVar3;
  
  *(undefined ***)this = &PTR_FUN_00544c50;
  iVar1 = *(int *)(param_1 + 8);
  *(int *)(this + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(this + 4) = *(undefined4 *)(param_1 + 4);
  }
  else {
    sVar2 = _strlen(*(char **)(param_1 + 4));
    pvVar3 = _malloc(sVar2 + 1);
    *(void **)(this + 4) = pvVar3;
    if (pvVar3 != (void *)0x0) {
      FUN_0052baa0(pvVar3,*(undefined4 *)(param_1 + 4));
    }
  }
  return this;
}

