/* FUN_004fdaa0 - 0x004fdaa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT FUN_004fdaa0(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  double dVar1;
  LONG LVar2;
  __time32_t _Var3;
  LRESULT LVar4;
  
  LVar2 = GetWindowLongA(param_1,-0x15);
  if ((param_2 == 0x113) && (param_3 == *(WPARAM *)(LVar2 + 0x1ab8))) {
    if (*(char *)(LVar2 + 0x1a70) != '\0') {
      dVar1 = (double)(*(int *)(LVar2 + 0x1abc) + 600) - _DAT_00558048;
      _Var3 = FID_conflict___time32((__time32_t *)0x0);
      if (dVar1 < (double)_Var3) {
        FUN_005024a0(0);
      }
    }
    return 0;
  }
  LVar4 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar4;
}

