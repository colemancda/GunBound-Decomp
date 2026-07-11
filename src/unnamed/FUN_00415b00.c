/* FUN_00415b00 - 0x00415b00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00415b00(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  size_t _Size;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  pcVar3 = param_1;
  do {
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  uVar6 = 0;
  if (DAT_00e9c9e0 != 0) {
    uVar7 = DAT_00e9c9e0;
    if (DAT_00e9c9e0 == 0) {
LAB_00415ba7:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      pcVar4 = *(char **)(DAT_00e9c9dc + uVar6 * 4);
      pcVar1 = pcVar4 + 1;
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar2 != '\0');
      _Size = (int)pcVar4 - (int)pcVar1;
      if (_Size != 0) {
        iVar8 = 0;
        if (-1 < (int)(pcVar3 + (-_Size - (int)(param_1 + 1)))) {
          do {
            if (uVar7 <= uVar6) goto LAB_00415ba7;
            iVar5 = __memicmp(param_1 + iVar8,*(void **)(DAT_00e9c9dc + uVar6 * 4),_Size);
            if (iVar5 == 0) {
              return 1;
            }
            if (param_1[iVar8] < '\0') {
              iVar8 = iVar8 + 1;
            }
            iVar8 = iVar8 + 1;
            uVar7 = DAT_00e9c9e0;
          } while (iVar8 <= (int)(pcVar3 + (-_Size - (int)(param_1 + 1))));
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar7);
  }
  return 0;
}

