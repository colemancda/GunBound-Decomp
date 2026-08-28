/* CommEngineRecv - 0x004ff4a0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004ff4a0).  The FD_READ half of the comm engine:
 * recv() with WSAGetLastError handling, called from
 * CommEngineNotifyWndProc.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall CommEngineRecv(int *param_1,int param_2,undefined4 *regEdi)

{
  int iVar1;
  int *piVar2;
  undefined4 *unaff_EDI = regEdi;
  char local_1770 [5996];
  undefined4 uStack_4;
  
  uStack_4 = 0x4ff4aa;
  if (param_2 == 0) {
    iVar1 = recv(param_1[2],local_1770,6000,0);
    if (iVar1 == 0) {
      FUN_004fe6a0(0,(int *)unaff_EDI,param_1);
      return;
    }
    if (iVar1 != -1) {
      (**(code **)*unaff_EDI)(0,param_1,local_1770,iVar1);
      return;
    }
    param_2 = WSAGetLastError();
    if (param_2 == 0) {
      return;
    }
  }
  if (param_2 != 0x2733) {
    (**(code **)*unaff_EDI)(param_2,param_1,0,0);
    piVar2 = (int *)unaff_EDI[1];
    if (piVar2 != (int *)0x0) {
      while (param_1 != piVar2) {
        piVar2 = (int *)*piVar2;
        if (piVar2 == (int *)0x0) {
          return;
        }
      }
      FUN_004fdda0((int *)unaff_EDI,(int)param_1);
    }
  }
  return;
}

