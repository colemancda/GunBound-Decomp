/* ConnectSocketToTarget - 0x004e59b0 in the original binary.
 *
 * Worker-thread body of the actual connect. Creates a TCP socket
 * (AF_INET / SOCK_STREAM), builds a sockaddr_in from the stored target
 * port (conn+0x228, htons'd) and an address resolved by FUN_004e5480,
 * and calls connect(); on success sets the connected flag (conn+0x22a=1).
 * Returns that flag. Invoked from HandleSocketEvent's op 2.
 *
 * unaff_ESI (the connection object) arrives via a dropped ESI register;
 * the sole caller (HandleSocketEvent.c) already computes the right value
 * (param_1 + 0x28) but it was silently discarded against this function's
 * previous (void) signature. Promoted to an explicit parameter.
 *
 * __stdcall confirmed by the original's epilogue (`ret 0x4`, callee
 * cleans up its one 4-byte argument) - a plain declaration here would
 * default to __cdecl and leave a caller-side stack-cleanup mismatch.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * POSSIBLE BUG, NOT YET FIXED (2026-07-13): `FUN_004e5480()` is called
 * here with 0 args, but it's a real 2-param __fastcall function
 * (param_1/ECX unused in its body, param_2/EDX used as a null-
 * terminated hostname string - see that file). Objdump at this call
 * site (0x4e59dd, `mov edx,[esp+0x14]`) traces EDX back to this
 * function's OWN single stdcall argument - i.e. the connection object's
 * base address itself (`unaff_ESI`/`conn`), not `conn+0x28` where
 * SignalConnectRequest.c copies the hostname string. CONFIRMED via
 * angr symbolic execution (not just manual stack arithmetic): stepping
 * the real instruction sequence from this function's entry with a
 * sentinel value planted as the incoming stdcall argument shows EDX
 * holds that exact sentinel at the call to 0x4e5480 - so this is
 * mechanically certain, not a decompiler artifact (for what it's
 * worth, angr's own AIL decompiler misreads this call as reading from
 * the local sockaddr buffer instead - a known angr weakness around
 * stdcall stack-slot reuse, contradicted by both objdump and the
 * concrete trace). What's NOT yet confirmed is whether this is a real
 * bug: either the hostname really does start at `conn+0` (unlikely -
 * SignalConnectRequest.c copies it to +0x28, and offset 0 is far more
 * likely a vtable/list-node pointer in a C++ object), or this is a
 * genuine off-by-offset defect in the shipped binary. Needs a fuller
 * field map of the ~0x24a70-byte connection object (not currently
 * documented at offset 0) before committing to a fix - left as
 * `FUN_004e5480()` with no args (matching prior behavior) rather than
 * guessing.
 */
#include "ghidra_types.h"


undefined1 __stdcall ConnectSocketToTarget(int unaff_ESI)

{
  SOCKET SVar1;
  int iVar2;
  sockaddr local_10;

  SVar1 = socket(2,1,0);
  *(SOCKET *)(unaff_ESI + 0x24) = SVar1;
  if (SVar1 != 0xffffffff) {
    local_10.sa_family = 2;
    SUBFIELD(local_10.sa_data,0,undefined2) = htons(*(u_short *)(unaff_ESI + 0x228));
    SUBFIELD(local_10.sa_data,2,undefined4) = FUN_004e5480();
    iVar2 = connect(*(SOCKET *)(unaff_ESI + 0x24),&local_10,0x10);
    if (iVar2 == 0) {
      *(undefined1 *)(unaff_ESI + 0x22a) = 1;
    }
  }
  return *(undefined1 *)(unaff_ESI + 0x22a);
}

