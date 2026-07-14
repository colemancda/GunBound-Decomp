/* ConnectSocketToTarget - 0x004e59b0 in the original binary.
 *
 * Worker-thread body of the actual connect. Creates a TCP socket
 * (AF_INET / SOCK_STREAM), builds a sockaddr_in from the stored target
 * port (conn+0x228, htons'd) and an address resolved by FUN_004e5480,
 * and calls connect(); on success sets the connected flag (conn+0x22a=1).
 * Returns that flag. Invoked from HandleSocketEvent's op 2.
 *
 * __stdcall confirmed by the original's epilogue (`ret 0x4`, callee
 * cleans up its one 4-byte argument) - a plain declaration here would
 * default to __cdecl and leave a caller-side stack-cleanup mismatch.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14), in two passes - the real bug turned out to involve
 * a stack argument whose ROLE was misidentified, which caused the first
 * pass to misidentify this function's real input entirely:
 *
 * Pass 1 found `FUN_004e5480()` called here with 0 args, but it's a real
 * 2-param __fastcall function (param_1/ECX unused in its body, param_2/
 * EDX used as a null-terminated hostname string, resolved via
 * inet_addr()/gethostbyname() - see that file). Live-reproduced via
 * WINEDEBUG=+winsock: with the zero-arg call, the connect() this
 * function issues targeted address 0.0.0.0 (garbage from FUN_004e5480's
 * own uninitialized EDX read).
 *
 * Pass 1 ALSO assumed this function's own incoming stack argument
 * (pushed at its call site as `lea eax,[param_1+0x28]` in
 * HandleSocketEvent.c) was its real "this"/connection-object pointer,
 * matching Ghidra's own `unaff_ESI` naming. angr-disassembling the FULL
 * function body (0x4e59b0-0x4e5a17) shows that's only half right:
 *   - `[esi+0x24]` (socket handle), `[esi+0x228]` (port) and
 *     `[esi+0x22a]` (connected flag) are all accessed via `esi`
 *     DIRECTLY, with no prior `mov esi,[esp+...]` reload anywhere in the
 *     body - `esi` here is simply inherited unchanged from the CALLER
 *     (register preservation across `call`), i.e. HandleSocketEvent's
 *     own unshifted `this`/param_1 - the same true connection base
 *     SignalConnectRequest.c and HandleSocketEvent.c's own other field
 *     accesses (WSAEventSelect's `[esi+0x24]`, etc.) already use
 *     consistently.
 *   - The pushed stack argument is NOT dead, though: angr shows
 *     `mov edx,[esp+0x14]` (0x4e59dd) DOES read it back, but only to
 *     feed FUN_004e5480's hostname argument - i.e. the original compiler
 *     emitted `esi+0x28` twice, once implicitly (this-pointer-relative,
 *     for the three fields above) and once explicitly (as a precomputed
 *     stack argument, just for this one sub-call).
 * Since both forms resolve to the same value (the caller's `esi`, plus
 * 0x28 for the hostname), passing the plain unshifted base as this
 * function's sole argument and re-deriving `conn+0x28` internally below
 * (rather than trying to receive a pre-shifted argument) reproduces the
 * original bit-for-bit while using one consistent "base pointer"
 * parameter instead of mixing an implicit-register-this with an
 * explicit-shifted-stack-arg the way MSVC's codegen happened to split
 * it. Confirmed live: after fixing HandleSocketEvent.c's call site to
 * pass its own `param_1` directly (not `param_1+0x28`) and reverting
 * this function's offsets to the plain, unshifted form below,
 * `gethostbyname("localhost")` correctly resolved to 127.0.0.1 with the
 * real port. See HandleSocketEvent.c's own header for the paired fix.
 */
#include "ghidra_types.h"


undefined1 __stdcall ConnectSocketToTarget(int conn)

{
  SOCKET SVar1;
  int iVar2;
  sockaddr local_10;

  SVar1 = socket(2,1,0);
  *(SOCKET *)(conn + 0x24) = SVar1;
  if (SVar1 != 0xffffffff) {
    local_10.sa_family = 2;
    SUBFIELD(local_10.sa_data,0,undefined2) = htons(*(u_short *)(conn + 0x228));
    SUBFIELD(local_10.sa_data,2,undefined4) = FUN_004e5480(0,(char *)(conn + 0x28));
    iVar2 = connect(*(SOCKET *)(conn + 0x24),&local_10,0x10);
    if (iVar2 == 0) {
      *(undefined1 *)(conn + 0x22a) = 1;
    }
  }
  return *(undefined1 *)(conn + 0x22a);
}
