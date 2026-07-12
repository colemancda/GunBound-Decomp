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
 */
#include "ghidra_types.h"
#include <windows.h>


void AppendPersistentButtonName(int *param_1, char *in_EAX)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff7f;
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int *piVar5;
  undefined4 *puVar6;
  char local_80 [4];
  undefined1 local_7c [124];

  piVar5 = param_1 + *param_1 * 0x20 + 1;
  pcVar4 = in_EAX;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *(char *)piVar5 = cVar1;
    piVar5 = (int *)((int)piVar5 + 1);
  } while (cVar1 != '\0');
  iVar2 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_80 + iVar2)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  puVar3 = (undefined4 *)&stack0xffffff7f;
  do {
    puVar6 = puVar3;
    puVar3 = (undefined4 *)((int)puVar6 + 1);
  } while (*(char *)((int)puVar6 + 1) != '\0');
  *(undefined4 *)((int)puVar6 + 1) = DAT_00551cac;
  *(undefined1 *)((int)puVar6 + 5) = DAT_00551cb0;
  LoadButtonDefinitionFromXFS();
  *param_1 = *param_1 + 1;
  return;
}

