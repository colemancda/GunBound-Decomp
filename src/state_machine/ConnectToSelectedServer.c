/* ConnectToSelectedServer - 0x004e1bf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT: Ghidra emitted the server-index argument as
 * an uninitialized read of `unaff_EDI` instead of resolving it as a real
 * parameter. Confirmed at all 4 call sites in the original binary
 * (0x4e104e, 0x4e11b8, 0x4e14a2, 0x50d781 via objdump) - every one of
 * them sets EDI immediately before `call 0x4e1bf0` and separately
 * pushes param_1 on the stack (the callee's `ret 0x4` pops that one
 * stack slot). Promoted to a second formal parameter `serverIndex`;
 * all 4 call sites across src/ updated to pass it explicitly.
 *
 * CALLING-CONVENTION CAST MISMATCH: both `(**(code **)(*piVar1 + 4))
 * (s_disable_00551e68)` calls target the same widget mode-name-setter
 * vtable slot (`*piVar1 + 4`) already identified and fixed as
 * `__fastcall(thisPtr, modeName)` in State02_ServerSelect_ProcessPacket.c
 * (see that file's WidgetSetModeNameFn typedef/header comment). The raw
 * `code**` cdecl cast here was dropping `piVar1` (this) entirely instead
 * of passing it in ECX. Confirmed at the original 0x4e1ca6-0x4e1caf
 * (`mov edx,[eax]` / `push 0x551e68` / `mov ecx,eax` / `call [edx+4]`)
 * via objdump. Fixed using the same WidgetSetModeNameFn idiom.
 */
#include "ghidra_types.h"

/* __thiscall callee via __fastcall+dummy-EDX (see State02_ServerSelect_ProcessPacket.c): __thiscall is erased by ghidra_types.h, and a plain 2-arg __fastcall(this,name) puts name in EDX while the thiscall callee reads it off the stack and ret 4s - drifting ESP until a later ret jumps into heap garbage. The dummy EDX slot restores the ABI. */
typedef void (__fastcall *WidgetSetModeNameFn)(void *thisPtr, int edxDummy, const char *modeName);

/* WARNING: Removing unreachable block (ram,0x004e1c9a) */
/* WARNING: Removing unreachable block (ram,0x004e1ca4) */
/* WARNING: Removing unreachable block (ram,0x004e1c82) */
/* WARNING: Removing unreachable block (ram,0x004e1c8c) */
/* WARNING: Removing unreachable block (ram,0x004e1cc3) */
/* WARNING: Removing unreachable block (ram,0x004e1ccd) */

void ConnectToSelectedServer(int param_1, int serverIndex)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char local_80 [128];

  if ((serverIndex < 0x10) && (-2 < serverIndex)) {
    if (*(int *)(param_1 + 0x28 + serverIndex * 4) != 0) {
      ShowErrorDialog(0);
      return;
    }
    _sprintf(local_80,s__d__d__d__d_00557138,(uint)*(byte *)(g_clientContext + 0x4104a + serverIndex * 4)
             ,(uint)*(byte *)(g_clientContext + 0x4104b + serverIndex * 4),
             (uint)*(byte *)(g_clientContext + 0x4104c + serverIndex * 4),
             (uint)*(byte *)(g_clientContext + 0x4104d + serverIndex * 4));
    DAT_0056d118 = 0;
    if ((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
       (piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar1[2] == 0)) {
      (*(WidgetSetModeNameFn *)(*piVar1 + 4))(piVar1, 0, s_disable_00551e68);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar2 = piVar1[2];
      while (uVar2 < 2) {
        if (uVar2 == 1) {
          (*(WidgetSetModeNameFn *)(*piVar1 + 4))(piVar1, 0, s_disable_00551e68);
          break;
        }
        piVar1 = (int *)piVar1[4];
        uVar2 = piVar1[2];
      }
    }
    InvokeWidget(2,0);
    iVar4 = DAT_007934ec;
    iVar3 = g_clientContext;
    *(undefined1 *)(param_1 + 0x24) = 0;
    *(undefined1 *)(iVar4 + 0x84e6) = 0;
    /* CONFIRMED (2026-07-13) via objdump at 0x4e1d08-0x4e1d2e: `mov
     * eax,[0x7934ec]` loads DAT_007934ec, used for the +0x84e6 write above,
     * then `mov ebx,eax` right before `call 0x4d2480` (BeginServerConnect) -
     * the 3rd argument really is DAT_007934ec, not a guess. */
    BeginServerConnect(local_80,*(undefined2 *)(iVar3 + 0x4108a + serverIndex * 2),DAT_007934ec);
    *(undefined1 *)(param_1 + 4) = 1;
    *(int *)(param_1 + 0x68) = serverIndex;
  }
  return;
}

