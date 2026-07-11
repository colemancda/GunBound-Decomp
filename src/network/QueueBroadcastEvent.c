/* QueueBroadcastEvent - 0x004e6c90 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void QueueBroadcastEvent(int param_1)

{
  int iVar1;
  int unaff_ESI;
  undefined4 *puVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x198));
  puVar2 = (undefined4 *)(unaff_ESI + 0x44dec);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(char *)(unaff_ESI + 0x44df4) = *(char *)(unaff_ESI + 0x45204);
  *(char *)(unaff_ESI + 0x45204) = *(char *)(unaff_ESI + 0x45204) + '\x01';
  *(undefined2 *)(unaff_ESI + 0x44dee) = param_1;
  *(undefined1 *)(unaff_ESI + 0x44df1) = *(undefined1 *)(unaff_ESI + 0x14c);
  *(undefined4 *)(unaff_ESI + 0x44df5) = *(undefined4 *)(unaff_ESI + 0x15d);
  *(undefined4 *)(unaff_ESI + 0x44df9) = *(undefined4 *)(unaff_ESI + 0x161);
  *(undefined4 *)(unaff_ESI + 0x44dfd) = *(undefined4 *)(unaff_ESI + 0x165);
  *(undefined4 *)(unaff_ESI + 0x44fec) = 0x21;
  *(undefined1 *)(unaff_ESI + 0x44ff4) = 0;
  return;
}

