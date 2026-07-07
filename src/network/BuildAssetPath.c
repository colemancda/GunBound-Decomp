/* BuildAssetPath - 0x004b3da0 in the original binary.
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


void BuildAssetPath(int param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = 0;
  if (param_2 != (char *)0x0) {
    puVar4 = &param_2;
    do {
      if (0 < iVar3) {
        *(undefined1 *)(iVar3 + param_1) = 0x5c;
        iVar3 = iVar3 + 1;
        cVar2 = *param_2;
        while (cVar2 == '\\') {
          pcVar1 = param_2 + 1;
          param_2 = param_2 + 1;
          cVar2 = *pcVar1;
        }
      }
      cVar2 = *param_2;
      while (cVar2 != '\0') {
        *(char *)(iVar3 + param_1) = cVar2;
        pcVar1 = param_2 + 1;
        iVar3 = iVar3 + 1;
        param_2 = param_2 + 1;
        cVar2 = *pcVar1;
      }
      cVar2 = *(char *)(param_1 + -1 + iVar3);
      while (cVar2 == '\\') {
        pcVar1 = (char *)(param_1 + -2 + iVar3);
        iVar3 = iVar3 + -1;
        cVar2 = *pcVar1;
      }
      param_2 = (char *)puVar4[1];
      puVar4 = puVar4 + 1;
    } while (param_2 != (char *)0x0);
  }
  *(undefined1 *)(iVar3 + param_1) = 0;
  return;
}

