/* FUN_0044fcb0 - 0x0044fcb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0044fcb0(int *param_1)

{
  int iVar1;
  
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] != '\0') {
    iVar1 = _rand();
    if ((iVar1 % 10 != 0) && ((char)param_1[0x232] == '\0')) {
      (**(code **)(*param_1 + 4))(s_normal_00552230);
      return;
    }
    (**(code **)(*param_1 + 4))(&DAT_00555b4c);
    *(undefined1 *)(param_1 + 0x232) = 0;
  }
  return;
}

