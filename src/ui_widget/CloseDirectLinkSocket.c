/* CloseDirectLinkSocket - 0x004059a0 in the original binary.
 *
 * PROMOTED (2026-07-14): closes the whisper/direct-link connection's socket
 * and marks it disconnected - param_1 is DAT_007934f4 (the direct-link
 * object), whose +0x2004 sub-object holds the socket/session state (same
 * "connection sub-object at +0x2004" idiom documented in WinMain.c/
 * Shutdown.c/SignalConnectRequest.c for this same global). Called from
 * ShowErrorDialog/ShowMessageDialog/ShowErrorDialogFmt/FUN_00411b40, every
 * site already gated on `DAT_007934f4 != 0` - only the call itself dropped
 * the argument.
 *
 * DROPPED-ARGUMENT FIX: Ghidra typed this function void() and read the
 * object as unaff_EDI, which every call site left ungrouped (zero pushed
 * args), so it read whatever garbage register happened to be in EDI -
 * faulting at param_1+0x2004 with param_1 == unrelated (often 0) garbage.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void CloseDirectLinkSocket(int param_1)

{
  int iVar1;

  iVar1 = *(int *)(param_1 + 0x2004);
  *(undefined4 *)(iVar1 + 0x22c) = 1;
  if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(iVar1 + 0x24));
  }
  *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
  *(undefined1 *)(iVar1 + 0x22a) = 0;
  *(undefined1 *)(param_1 + 0x2009) = 0;
  return;
}
