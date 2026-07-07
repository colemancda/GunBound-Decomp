/* FUN_004fddd0 - 0x004fddd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fddd0(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  DWORD DVar5;
  int iVar6;
  DWORD DVar7;
  int *unaff_EBX;
  tagMSG local_1c;
  
  if ((char)unaff_EBX[9] == '\0') {
    *(undefined1 *)(unaff_EBX + 9) = 1;
    DVar5 = GetTickCount();
    while( true ) {
      iVar6 = PeekMessageA(&local_1c,(HWND)unaff_EBX[8],0,0,1);
      while (iVar6 != 0) {
        TranslateMessage(&local_1c);
        DispatchMessageA(&local_1c);
        iVar6 = PeekMessageA(&local_1c,(HWND)unaff_EBX[8],0,0,1);
      }
      if (unaff_EBX[3] == 0) {
        return;
      }
      DVar7 = GetTickCount();
      if (DVar5 + param_1 <= DVar7) break;
      Sleep(100);
    }
    piVar1 = unaff_EBX + 1;
    piVar2 = (int *)unaff_EBX[1];
joined_r0x004fde6a:
    piVar4 = piVar2;
    if (piVar4 != (int *)0x0) {
      piVar2 = (int *)*piVar4;
      (**(code **)(*unaff_EBX + 8))(0,piVar4);
      for (piVar3 = (int *)*piVar1; piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
        if (piVar4 == piVar3) {
          if (piVar4[2] != 0xffffffff) {
            closesocket(piVar4[2]);
          }
          if (piVar4 == (int *)*piVar1) {
            *piVar1 = *piVar4;
          }
          else {
            *(int *)piVar4[1] = *piVar4;
          }
          if (piVar4 == (int *)unaff_EBX[2]) {
            unaff_EBX[2] = piVar4[1];
          }
          else {
            *(int *)(*piVar4 + 4) = piVar4[1];
          }
          FUN_00500f90();
          *piVar4 = unaff_EBX[5];
          iVar6 = unaff_EBX[3];
          unaff_EBX[5] = (int)piVar4;
          unaff_EBX[3] = iVar6 + -1;
          if (iVar6 + -1 == 0) {
            FUN_004ff6d0();
          }
          break;
        }
      }
      goto joined_r0x004fde6a;
    }
  }
  return;
}

