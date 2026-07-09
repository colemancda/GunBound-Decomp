/* WndProc - 0x00410040 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT __stdcall WndProc(HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  char cVar1;
  LRESULT LVar2;
  uint uVar3;
  uint uVar4;
  
  cVar1 = '\x01';
  FUN_0040d020(&DAT_00e9c0fc);
  if (param_2 < 0x106) {
    if (param_2 == 0x105) {
      if (param_3 == 0x79) {
        BuildBuddyPanel();
      }
    }
    else if (param_2 < 0x21) {
      if (param_2 == 0x20) {
        SetCursor((HCURSOR)(&DAT_005b1c4c)[DAT_00793510]);
        return 1;
      }
      if (param_2 == 2) {
        PostQuitMessage(0);
        return 0;
      }
      if (param_2 == 7) {
        if (DAT_007934e4 != 0) {
          SetFocus(*(HWND *)(DAT_007934e4 + 4));
        }
      }
      else if (param_2 == 0x1c) {
        InterlockedExchange((LONG *)&DAT_00e9c348,param_3);
        FUN_004edce0();
        FUN_004edce0();
        if (DAT_007934f4 != 0) {
          if (param_3 == 1) {
            FUN_00405b20();
          }
          else {
            FUN_00405b60();
          }
        }
        DAT_007934cc = param_3 == 1;
        return 0;
      }
    }
    else if (param_2 == 0x100) {
      if (DAT_007934c4 == '\0') {
        cVar1 = FUN_0050f230(param_3);
        goto LAB_00410384;
      }
    }
    else if (param_2 == 0x101) {
      if (DAT_007934c4 == '\0') {
        cVar1 = FUN_0050f260(param_3);
        cVar1 = '\x01' - (cVar1 != '\0');
      }
      uVar4 = DAT_0056d10c;
      uVar3 = DAT_0056d110;
      if (param_3 == 0x7a) {
        DAT_00793520 = 1;
      }
      goto LAB_0041038c;
    }
    goto switchD_004101d3_caseD_113;
  }
  switch(param_2) {
  case 0x112:
    if (param_3 == 0xf060) {
      if ((g_currentGameState != 7) && (g_currentGameState != 0xb)) {
        g_pendingGameState = 0xf;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        _DAT_007934d8 = 1;
      }
      return 0;
    }
    break;
  case 0x200:
    uVar4 = param_4 & 0xffff;
    uVar3 = param_4 >> 0x10;
    cVar1 = FUN_0050f020(uVar4,uVar3);
    cVar1 = cVar1 == '\0';
    if ((bool)cVar1) {
      FUN_004061e0();
    }
    DAT_00e536c0 = DAT_00e536c0 + (uVar4 - DAT_0056d10c);
    DAT_00e536c4 = DAT_00e536c4 + (uVar3 - DAT_0056d110);
    if ((DAT_00e53c3c == '\0') && ((DAT_0056d10c != uVar4 || (DAT_0056d110 != uVar3)))) {
      SetCursorPos(DAT_0056d10c,DAT_0056d110);
      uVar4 = DAT_0056d10c;
      uVar3 = DAT_0056d110;
    }
    goto LAB_0041038c;
  case 0x201:
    cVar1 = FUN_00507ea0(param_4 & 0xffff,param_4 >> 0x10);
    if (cVar1 != '\0') {
      DAT_00e9bea4 = 1;
      FUN_00406120();
      DAT_00e9bea4 = 0;
      goto LAB_004103ac;
    }
    FUN_00406120();
    FUN_0040ce50(&DAT_00e9c0fc);
    break;
  case 0x202:
    DAT_00e9bea4 = FUN_0050f1b0(param_4 & 0xffff,param_4 >> 0x10);
    cVar1 = DAT_00e9bea4 != '\x01';
    FUN_00406170();
    DAT_00e9bea4 = 0;
    uVar4 = DAT_0056d10c;
    uVar3 = DAT_0056d110;
    goto LAB_0041038c;
  case 0x203:
    cVar1 = FUN_0050f1f0(param_4 & 0xffff,param_4 >> 0x10);
    goto LAB_00410384;
  case 0x204:
    cVar1 = FUN_0050f150(param_4 & 0xffff,param_4 >> 0x10);
LAB_00410384:
    cVar1 = '\x01' - (cVar1 != '\0');
    uVar4 = DAT_0056d10c;
    uVar3 = DAT_0056d110;
LAB_0041038c:
    DAT_0056d110 = uVar3;
    DAT_0056d10c = uVar4;
    if (cVar1 == '\0') goto LAB_004103ac;
  }
switchD_004101d3_caseD_113:
  if ((g_currentGameState != 0) && ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0)
     ) {
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x18))
              (param_2,param_3,param_4);
  }
LAB_004103ac:
  if ((0x200 < param_2) && (param_2 < 0x203)) {
    return 0;
  }
  LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar2;
}

