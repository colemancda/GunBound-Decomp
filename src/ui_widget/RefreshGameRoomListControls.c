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
 * 0xf in program order). `unaff_EBX`/`unaff_EDI` (this function's OWN
 * incoming arguments, driving the "enabled" bool passed to every one
 * of those InvokeWidget calls) are a SEPARATE, still-unfixed bug -
 * confirmed via angr that this function has 14 callers across 7 files
 * with inconsistent EBX/EDI setup (some inherit unchanged, some
 * recompute EDI=EBP, at least one doesn't touch either register at
 * all before the call) - resolving that is its own investigation, not
 * attempted here so it doesn't block the InvokeWidget threading pass.
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

void RefreshGameRoomListControls(void)

{
  int *piVar1;
  uint uVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint3 uVar6;
  char cVar7;
  undefined4 unaff_EBX;
  int unaff_EDI;

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

