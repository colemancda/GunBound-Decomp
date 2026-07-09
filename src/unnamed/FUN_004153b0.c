/* FUN_004153b0 - 0x004153b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004153b0(int param_1)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  
  if (*(uint *)(param_1 + 0x14) < 0xb) {
    DVar2 = timeGetTime();
    iVar1 = *(int *)(param_1 + 0x10);
    *(DWORD *)(param_1 + 0x10) = DVar2;
    if (iVar1 != -1) {
      uVar3 = DVar2 - iVar1;
      if ((uVar3 < 0x28b) && (0x15d < uVar3)) {
        *(undefined4 *)(param_1 + 0x14) = 0;
        return;
      }
      uVar3 = *(int *)(param_1 + 0x14) + 1;
      *(uint *)(param_1 + 0x14) = uVar3;
      if (10 < uVar3) {
        ShowErrorDialog(1);
      }
    }
  }
  return;
}

