/* FUN_005013c0 - 0x005013c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint * __thiscall FUN_005013c0(int *param_1,undefined4 *param_2)

{
  uint *puVar1;
  uint *in_EAX;
  uint *puVar2;
  uint *puVar3;
  uint *unaff_ESI;
  uint unaff_EDI;
  
  *in_EAX = unaff_EDI;
  *unaff_ESI = unaff_EDI % (uint)param_1[2];
  if (*param_1 != 0) {
    *param_2 = 0;
    puVar1 = *(uint **)(*param_1 + *unaff_ESI * 4);
    if (puVar1 != (uint *)0x0) {
      puVar3 = (uint *)0x0;
      do {
        puVar2 = puVar1;
        if ((puVar2[4] == *in_EAX) && (*puVar2 == unaff_EDI)) {
          *param_2 = puVar3;
          return puVar2;
        }
        puVar1 = (uint *)puVar2[3];
        puVar3 = puVar2;
      } while ((uint *)puVar2[3] != (uint *)0x0);
    }
  }
  return (uint *)0x0;
}

