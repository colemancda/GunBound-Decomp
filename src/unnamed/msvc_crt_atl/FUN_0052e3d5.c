/* FUN_0052e3d5 - 0x0052e3d5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __setenvp
   
   Library: Visual Studio 2003 Release */

int __cdecl __setenvp(void)

{
  undefined4 *puVar1;
  size_t sVar2;
  void *pvVar3;
  char *pcVar4;
  int iVar5;
  
  if (DAT_00f2968c == 0) {
    ___initmbctable();
  }
  iVar5 = 0;
  pcVar4 = DAT_005b1758;
  if (DAT_005b1758 != (char *)0x0) {
    for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + sVar2 + 1) {
      if (*pcVar4 != '=') {
        iVar5 = iVar5 + 1;
      }
      sVar2 = _strlen(pcVar4);
    }
    puVar1 = _malloc(iVar5 * 4 + 4);
    pcVar4 = DAT_005b1758;
    DAT_005b18e8 = puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      do {
        if (*pcVar4 == '\0') {
          _free(DAT_005b1758);
          DAT_005b1758 = (char *)0x0;
          *puVar1 = 0;
          DAT_00f29680 = 1;
          return 0;
        }
        sVar2 = _strlen(pcVar4);
        if (*pcVar4 != '=') {
          pvVar3 = _malloc(sVar2 + 1);
          *puVar1 = pvVar3;
          if (pvVar3 == (void *)0x0) {
            _free(DAT_005b18e8);
            DAT_005b18e8 = (undefined4 *)0x0;
            return -1;
          }
          FUN_0052baa0(pvVar3,pcVar4);
          puVar1 = puVar1 + 1;
        }
        pcVar4 = pcVar4 + sVar2 + 1;
      } while( true );
    }
  }
  return -1;
}

