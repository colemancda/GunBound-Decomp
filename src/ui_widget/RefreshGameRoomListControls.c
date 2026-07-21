/* RefreshGameRoomListControls - 0x0042a090 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * PARTIALLY FIXED (2026-07-13): InvokeWidget's own dropped widgetId
 * argument fixed at all 11 call sites here (an angr CFG backward-scan
 * gave the exact per-site id: 0, 1, 3, 4, 5, 0xa, 0xb, 0xc, 0xd, 0xe,
 * 0xf in program order).
 *
 * FIXED (2026-07-20): the remaining `unaff_EBX`/`unaff_EDI` - this
 * function's own two incoming register arguments - are now real
 * parameters. Both were uninitialised local reads; `unaff_EDI` was the
 * worse of the two, since it was DEREFERENCED at +4, +0x118 and +0x120.
 *
 * EBX = a 0/1 "controls enabled" flag. A byte-scan of the original for
 * `call 0x42a090` found 14 call sites, and every one sets BL immediately
 * before the call: `mov bl,1` at 0x426d44, 0x426d8a, 0x428a41, 0x42ad95;
 * `xor bl,bl` at 0x4286c7, 0x4287b3, 0x42884b, 0x428929, 0x428a9d,
 * 0x428af4, 0x429bb7, 0x429c6c, 0x429ea2, 0x42a00f.
 *
 * EDI = the State03/GameRoomList state object (g_gameStateVTableArray[3]),
 * threaded through the call chain as a C++ `this`. Traced back: the two
 * callers of 0x429fd0 both do `mov eax,edi` (0x428623, 0x428ade) and it
 * does `mov edi,eax`; the chain terminates at 0x4285ca `mov edi,ecx` in
 * the method at 0x4285c0, which is slot 4 of the class vtable at
 * 0x553674-0x5536b4 (all slots land in the 0x428xxx-0x429xxx lobby
 * range). That is the same pointer FUN_0042a680 receives as param_1 via
 * `FUN_0042a680(g_gameStateVTableArray[3])` (src/unnamed/FUN_005078f0.c),
 * and it is allocated `operator_new(0x294)` in InitGame.c, so the +0x124
 * accesses are well inside the object - no sizing issue.
 *
 * Symptom this fixes: garbage EBX made `g_serverWaitTicks` come out
 * nonzero, leaving the lobby's PLEASE WAIT spinner up forever.
 */
#include "ghidra_types.h"

/* Vtable slot 1 of the real C++ CButtonWidget is SetState(const char*), a
 * genuine __thiscall (this in ECX). ghidra_types.h erases __thiscall, so the
 * raw dispatch below compiled as __cdecl - `this` went on the stack and ECX
 * held garbage, and SetState faulted reading this+0x1c (observed live with
 * ECX=2). Reproduce __thiscall with the project's __fastcall+dummy-EDX idiom,
 * exactly as State02_ServerSelect_ProcessPacket.c / ConnectToSelectedServer.c
 * already do for the same slot. */
typedef void (__fastcall *WidgetSetModeNameFn)(void *thisPtr, int edxDummy, const char *modeName);


/* WARNING: Removing unreachable block (ram,0x0042a0d2) */
/* WARNING: Removing unreachable block (ram,0x0042a0dc) */

void RefreshGameRoomListControls(undefined4 controlsEnabled,int stateObj)

{
  int *piVar1;
  uint uVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint3 uVar6;
  char cVar7;
  undefined4 unaff_EBX = controlsEnabled;
  int unaff_EDI = stateObj;

  cVar7 = (char)unaff_EBX;
  g_serverWaitTicks = (cVar7 != '\x01') - 1;
  InvokeWidget(0,unaff_EBX);
  InvokeWidget(1,unaff_EBX);
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar1[2];
    while (uVar2 < 3) {
      if (uVar2 == 2) {
        (*(WidgetSetModeNameFn *)(*piVar1 + 4))(piVar1, 0, s_disable_00551e68);
        break;
      }
      piVar1 = (int *)piVar1[4];
      uVar2 = piVar1[2];
    }
  }
  if (cVar7 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 != 1) {
      uVar5 = 1;
      goto LAB_0042a13e;
    }
  }
  uVar5 = 0;
LAB_0042a13e:
  InvokeWidget(3,uVar5);
  InvokeWidget(4,unaff_EBX);
  if ((*(int *)(unaff_EDI + 4) == -1) || (cVar7 == '\0')) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  InvokeWidget(5,uVar5);
  InvokeWidget(10,unaff_EBX);
  InvokeWidget(11,unaff_EBX);
  uVar6 = (uint3)((uint)*(int *)(unaff_EDI + 0x118) >> 8);
  if ((*(int *)(unaff_EDI + 0x118) < 1) || (cVar7 == '\0')) {
    iVar4 = (uint)uVar6 << 8;
  }
  else {
    iVar4 = CONCAT31(uVar6,1);
  }
  InvokeWidget(12,iVar4);
  if ((*(char *)(unaff_EDI + 0x120) == '\0') || (cVar7 == '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  InvokeWidget(13,uVar3);
  InvokeWidget(14,unaff_EBX);
  InvokeWidget(15,unaff_EBX);
  return;
}

