/* SignalConnectRequest - 0x004e5a50 in the original binary.
 *
 * Hands a new connect target to the connection object and wakes its
 * background worker thread. Marks state=connecting (conn+0x22c=1), closes
 * any existing socket, stores the target port (conn+0x228), copies the
 * hostname string (passed via register, not visible in the signature) into
 * conn+0x28, sets state=3 ("dial requested"), and SetEvent()s the worker's
 * event handle (conn+0x10). The actual socket()/connect() runs later on
 * the worker thread (ConnectSocketToTarget, via HandleSocketEvent op 2).
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* unaff_ESI (the connection object) and unaff_EDI (the hostname string to
 * copy in) both arrive via dropped registers in the original (orig
 * 0x40de77-0x40de82: `mov esi, [eax+0x2004]` where eax=DAT_007934f4, and
 * `mov edi, 0x551e38` -> the string "localhost", a hardcoded loopback
 * default). Promoted to explicit parameters; the sole caller (WinMain.c)
 * passes both directly. */
void SignalConnectRequest(int unaff_ESI, char *unaff_EDI, int param_1)

{
  char cVar1;
  int iVar2;

  *(undefined4 *)(unaff_ESI + 0x22c) = 1;
  if (*(SOCKET *)(unaff_ESI + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(unaff_ESI + 0x24));
  }
  *(undefined2 *)(unaff_ESI + 0x228) = param_1;
  *(undefined4 *)(unaff_ESI + 0x24) = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x22a) = 0;
  iVar2 = (unaff_ESI + 0x28) - (int)unaff_EDI;
  do {
    cVar1 = *unaff_EDI;
    unaff_EDI[iVar2] = cVar1;
    unaff_EDI = unaff_EDI + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_ESI + 0x22c) = 3;
                    /* WARNING: Could not recover jumptable at 0x004e5aab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SetEvent(*(HANDLE *)(unaff_ESI + 0x10));
  return;
}

