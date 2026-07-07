/* FUN_00524360 - 0x00524360 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00524360(int param_1)

{
  DWORD DVar1;
  
  if (DAT_0056adf0 == (HANDLE)0xffffffff) {
    return 0;
  }
  FUN_00523fc0(0x8b1,0x610,0);
  if (DAT_005b1630 != (HANDLE)0x0) {
    SetEvent(DAT_005b1630);
  }
  if (*(HANDLE *)(param_1 + 0x18) != (HANDLE)0x0) {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x18),100);
    if (DVar1 == 0x102) {
      TerminateThread(*(HANDLE *)(param_1 + 0x18),0);
    }
    CloseHandle(*(HANDLE *)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  if (DAT_0056adf0 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_0056adf0);
    DAT_0056adf0 = (HANDLE)0xffffffff;
  }
  if (DAT_0056adf4 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_0056adf4);
    DAT_0056adf4 = (HANDLE)0xffffffff;
  }
  return 1;
}

