/* FUN_004fe500 - 0x004fe500 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25) by promotion: it is the map object, passed
 * straight through to the find helper (`mov esi,eax` at the entry, `mov
 * eax,esi` before the call) and then used to rewrite the bucket head.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004fe500(undefined4 param_1,undefined4 param_2)

{
  int *regEax;   /* the map; see the header note */
  int iVar1;
  int local_c;
  undefined1 local_8 [8];
  
  local_c = 0;
  iVar1 = FUN_004ff130((char *)param_2,(uint *)local_8,(undefined4 *)&local_c,regEax,
                       (uint *)(local_8 + 4));
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c == 0) {
    *(undefined4 *)(*regEax + (*(uint *)(iVar1 + 0x18) % (uint)regEax[2]) * 4) =
         *(undefined4 *)(iVar1 + 0x14);
    FUN_00500650(iVar1,(int)regEax);
    return 1;
  }
  *(undefined4 *)(local_c + 0x14) = *(undefined4 *)(iVar1 + 0x14);
  FUN_00500650(iVar1,(int)regEax);
  return 1;
}

