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


/* DROPPED-REGISTER FIX: `conn` (the connection object, ESI) and `hostName`
 * (the hostname string to copy in, EDI) both arrive via dropped registers,
 * which Ghidra emitted as uninitialised `unaff_ESI`/`unaff_EDI`. Both are
 * genuinely read-before-written in the callee: ESI at 0x4e5a50
 * (`mov eax,[esi+0x24]`, the very first instruction) and EDI at 0x4e5a86
 * (`mov eax,edi`). Promoted to explicit parameters.
 *
 * Re-verified (2026-07-19) by angr CFG sweep - 100% agreement across both
 * call sites:
 *   ESI: 0x40de77 (WinMain)             `mov esi, [eax+0x2004]`, eax=DAT_007934f4
 *        0x4d24cd (BeginServerConnect)  `mov esi, [ebx+0x84e0]`
 *   EDI: 0x40de82 (WinMain)             `mov edi, 0x551e38` -> "localhost"
 *        0x4d24c9 (BeginServerConnect)  `mov edi, [esp+0x10]` -> its host arg
 * Both reach `call 0x4e5a50` at 0x40de8b / 0x4d24d4 respectively.
 *
 * NOTE: BeginServerConnect is the live caller; WinMain's call is currently
 * commented out as a bring-up hack (see src/entry/WinMain.c). */
void SignalConnectRequest(int conn, char *hostName, int param_1)

{
  char cVar1;
  int iVar2;
  int unaff_ESI = conn;
  char *unaff_EDI = hostName;

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

