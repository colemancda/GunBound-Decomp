/* FUN_005311ac - 0x005311ac in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    void * __cdecl AdjustPointer(void *,struct PMD const &)
   
   Library: Visual Studio 2003 Release */

void * __cdecl AdjustPointer(void *param_1,PMD *param_2)

{
  int in_EAX;
  void *pvVar1;
  int *in_ECX;
  
  pvVar1 = (void *)(*in_ECX + in_EAX);
  if (-1 < in_ECX[1]) {
    pvVar1 = (void *)((int)pvVar1 + *(int *)(*(int *)(in_ECX[1] + in_EAX) + in_ECX[2]) + in_ECX[1]);
  }
  return pvVar1;
}

