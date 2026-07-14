/* ShowErrorDialog - 0x004124a0 in the original binary.
 *
 * The shared in-game error/message dialog (~40 call sites). Shows a modal
 * popup with a word-wrapped localized message and a single OK button.
 *
 * Signature is `(char closeSockets)` in C, but the message id also arrives in
 * a register (EAX, invisible to Ghidra) -> stored into g_stateChangeInProgress.
 * Steps:
 *   1. Records the dialog as modal: DAT_0079350c = closeSockets, and
 *      g_stateChangeInProgress = message id. GameTick gates input/updates on
 *      these being nonzero (the popup blocks the screen underneath).
 *   2. Creates the OK button: CreateButtonWidget(list, 1000000, 1000000,
 *      0x385, "b_error_confirm", 0x1c6, 0x14b, 0x4a, 0x1a, 1, 0) -> at
 *      (454,331), 74x26; action code 0x385.
 *   3. Snaps the cursor onto the dialog (ClampCursorToRect -> SetCursorPos).
 *   4. Clears the text scratch buffer (DAT_005b1d70) and sets the dialog rect
 *      globals (_DAT_00e53c24..30 = {0xf9,0x229,0xc1,0x171}).
 *   5. Looks up the localized message string, GetLocalizedString(&g_localizedStringTable,
 *      msgId + 0xc7), and word-wraps it into DAT_005b1d70 via
 *      RenderWrappedText(buf, str, x=0x32, y=0x2b, wrapWidth=0x15e, 1).
 *   6. If closeSockets != 0: tears down all three connection objects
 *      (DAT_005b2b58 / DAT_005b2b5c / DAT_005b2b60 -> mark state 1, closesocket
 *      +0x24, clear connected flags +0x22a/+0x84e5), releases the COM object
 *      DAT_00e55a64 (vtable +4 = Release), closes the whisper/direct link if
 *      active (DAT_007934f4 -> FUN_004059a0), and SetEvent(DAT_00e55ce8).
 *
 * One of a three-overload family that differ only in the message source:
 *   ShowErrorDialog(closeSockets)          - localized string by id, verbatim.
 *   ShowErrorDialogFmt(closeSockets, value)   - localized string used as a printf
 *                                         format, sprintf'd with one value.
 *   ShowMessageDialog(text, closeSockets)    - a caller-supplied literal string.
 * All three build the same b_error_confirm OK button (action 0x385) and share
 * the modal/teardown logic above. See docs/screens/README.md "Error / message
 * dialog" and docs/screens/02_server_select.md "Errors" for the callers.
 *
 * Not renamed in-tree: ~40 call sites would each need touching.
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ShowErrorDialog(int param_1)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  DAT_0079350c = param_1;
  g_stateChangeInProgress = in_EAX;
  CreateButtonWidget(&DAT_00e9be90,1000000,1000000,0x385,s_b_error_confirm_00552238,0x1c6,0x14b,0x4a
                     ,0x1a,1,0);
  ClampCursorToRect();
  uVar8 = 1;
  uVar7 = 0x15e;
  uVar6 = 0x2b;
  puVar4 = (undefined4 *)DAT_005b1d70;
  for (iVar3 = 0x57; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  uVar5 = 0x32;
  _DAT_00e53c24 = 0xf9;
  _DAT_00e53c28 = 0x229;
  _DAT_00e53c2c = 0xc1;
  _DAT_00e53c30 = 0x171;
  *(undefined2 *)puVar4 = 0;
  uVar2 = GetLocalizedString(&g_localizedStringTable,in_EAX + 199);
  RenderWrappedText(DAT_005b1d70,uVar2,uVar5,uVar6,uVar7,uVar8);
  iVar3 = DAT_005b2b58;
  if (param_1 != '\0') {
    iVar1 = *(int *)(DAT_005b2b58 + 0x84e0);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x22c) = 1;
      if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar1 + 0x24));
      }
      *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar1 + 0x22a) = 0;
      *(undefined1 *)(iVar3 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b5c;
    iVar3 = *(int *)(DAT_005b2b5c + 0x84e0);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x22c) = 1;
      if (*(SOCKET *)(iVar3 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar3 + 0x24));
      }
      *(undefined4 *)(iVar3 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar3 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b60;
    iVar3 = *(int *)(DAT_005b2b60 + 0x84e0);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x22c) = 1;
      if (*(SOCKET *)(iVar3 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar3 + 0x24));
      }
      *(undefined4 *)(iVar3 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar3 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    if (DAT_00e55a64 != (int *)0x0) {
      (**(code **)(*DAT_00e55a64 + 4))();
    }
    DAT_00e55a64 = (int *)0x0;
    if (DAT_007934f4 != 0) {
      FUN_004059a0();
    }
    SetEvent(DAT_00e55ce8);
  }
  return;
}

