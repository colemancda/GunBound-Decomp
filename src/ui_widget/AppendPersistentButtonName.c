/* AppendPersistentButtonName - 0x00401740 in the original binary.
 *
 * in_EAX (the button name string, e.g. "b_gamelist_buddyup") arrives via
 * a dropped EAX register - every caller in ChangeGameState.c already
 * has a distinct literal loaded into EAX right before its own call
 * (orig 0x41236f/0x412386/.../0x412421), recovered per call site and
 * promoted to an explicit parameter here.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * FIXED (2026-07-13): the original's second string copy and its
 * following "scan to the terminator, then append 5 bytes" walk both
 * operate on a SINGLE stack buffer at `[ESP+0x10]` - confirmed via
 * objdump at 0x401740 (`lea edx,[esp+0x10]` for the copy, `lea
 * edi,[esp+0x10]` for the scan, same address). The raw port instead
 * declared THREE separate locals (`local_80[4]`, `local_7c[124]`, and a
 * synthetic `stack0xffffff7f` Ghidra couldn't even name) and relied on
 * them landing contiguously in that order - the same
 * declared-separately-but-must-be-contiguous bug class already fixed in
 * `State05_Logo1_OnExit.c`, except here MSVC isn't guaranteed to place
 * `stack0xffffff7f` right after the other two at all, so the "append
 * after the terminator" step could write into any other local or
 * scribble past the real buffer. Fixed by using one real 112-byte
 * array for the whole sequence. (`LoadButtonDefinitionFromXFS`'s own
 * dropped-EBX-output-buffer parameter, computed just after this in the
 * original but never carried across in this raw port, is a separate,
 * already-documented bring-up stub - see that file's header - so this
 * fix doesn't attempt to wire it up.)
 */
#include "ghidra_types.h"
#include <windows.h>


void AppendPersistentButtonName(int *param_1, char *in_EAX)

{
  char cVar1;
  char *pcVar4;
  int *piVar5;
  char *pcVar6;
  char nameBuf [112];

  piVar5 = param_1 + *param_1 * 0x20 + 1;
  pcVar4 = in_EAX;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *(char *)piVar5 = cVar1;
    piVar5 = (int *)((int)piVar5 + 1);
  } while (cVar1 != '\0');
  pcVar4 = in_EAX;
  pcVar6 = nameBuf;
  do {
    cVar1 = *pcVar4;
    *pcVar6 = cVar1;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  pcVar6 = nameBuf - 1;
  do {
    pcVar6 = pcVar6 + 1;
  } while (pcVar6[1] != '\0');
  *(undefined4 *)(pcVar6 + 1) = DAT_00551cac;
  *(undefined1 *)(pcVar6 + 5) = DAT_00551cb0;
  LoadButtonDefinitionFromXFS();
  *param_1 = *param_1 + 1;
  return;
}

