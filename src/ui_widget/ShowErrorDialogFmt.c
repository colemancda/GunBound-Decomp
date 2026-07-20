/* ShowErrorDialogFmt - 0x00412650 in the original binary.
 *
 * Error/message dialog variant: looks up a localized string by id and sprintf's it with one value, otherwise identical to ShowErrorDialog (same b_error_confirm OK button, modal flag DAT_0079350c, optional socket teardown). Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ShowErrorDialogFmt(int param_1,undefined4 param_2)

{
  int iVar1;
  int in_EAX;
  char *_Format;
  int iVar2;
  undefined4 *puVar3;
  char local_200 [512];
  
  DAT_0079350c = param_1;
  g_stateChangeInProgress = in_EAX;
  CreateButtonWidget(&DAT_00e9be90,1000000,1000000,0x385,s_b_error_confirm_00552238,0x1c6,0x14b,0x4a
                     ,0x1a,1,0);
  /* self/x/y dropped as ECX/EBX/EDI - confirmed via disassembly at
   * 0x4126ac: self is the DirectInput mouse device singleton
   * (g_mouseDeviceTimerBlock, 0xe53698), x/y are the literal constants
   * 0x1eb/0x158 (same 3 values for every dialog-open call site). */
  ClampCursorToRect((int)g_mouseDeviceTimerBlock,0x1eb,0x158);
  _DAT_00e53c24 = 0xf9;
  _DAT_00e53c28 = 0x229;
  _DAT_00e53c2c = 0xc1;
  _DAT_00e53c30 = 0x171;
  _Format = (char *)GetLocalizedString(&g_localizedStringTable,in_EAX + 199);
  _sprintf(local_200,_Format,param_2);
  puVar3 = (undefined4 *)DAT_005b1d70;
  for (iVar2 = 0x57; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  RenderWrappedText(DAT_005b1d70,local_200,0x32,0x2b,0x15e,1);
  iVar2 = DAT_005b2b58;
  if (param_1 != '\0') {
    iVar1 = *(int *)(DAT_005b2b58 + 0x84e0);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x22c) = 1;
      if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar1 + 0x24));
      }
      *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar1 + 0x22a) = 0;
      *(undefined1 *)(iVar2 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b5c;
    iVar2 = *(int *)(DAT_005b2b5c + 0x84e0);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x22c) = 1;
      if (*(SOCKET *)(iVar2 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar2 + 0x24));
      }
      *(undefined4 *)(iVar2 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar2 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b60;
    iVar2 = *(int *)(DAT_005b2b60 + 0x84e0);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x22c) = 1;
      if (*(SOCKET *)(iVar2 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar2 + 0x24));
      }
      *(undefined4 *)(iVar2 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar2 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    if (g_directLinkConnection != 0) {
      CloseDirectLinkSocket((int)g_directLinkConnection);
    }
    SetEvent(DAT_00e55ce8);
  }
  return;
}

