/* FUN_005266e0 - 0x005266e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _shortsort
   
   Library: Visual Studio 2003 Release */

void __cdecl shortsort(undefined1 *param_1,int param_2,code *param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined1 *in_EAX;
  int iVar3;
  undefined1 *puVar4;
  
  for (; puVar2 = param_1, puVar4 = param_1, param_1 < in_EAX; in_EAX = in_EAX + -param_2) {
    while (puVar4 = puVar4 + param_2, puVar4 <= in_EAX) {
      iVar3 = (*param_3)(puVar4,puVar2);
      if (0 < iVar3) {
        puVar2 = puVar4;
      }
    }
    if ((puVar2 != in_EAX) && (param_2 != 0)) {
      puVar4 = in_EAX;
      iVar3 = param_2;
      do {
        uVar1 = puVar4[(int)puVar2 - (int)in_EAX];
        puVar4[(int)puVar2 - (int)in_EAX] = *puVar4;
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}

