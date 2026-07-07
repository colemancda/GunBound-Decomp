/* FUN_004f4750 - 0x004f4750 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004f4750(undefined4 *param_1)

{
  char *pcVar1;
  int in_EAX;
  int iVar2;
  char unaff_BL;
  int unaff_ESI;
  
  pcVar1 = *(char **)(in_EAX + 0x114);
  do {
    if (pcVar1 == (char *)0x0) {
      return -1;
    }
    if ((unaff_ESI == *(int *)(pcVar1 + 4)) && (unaff_BL == *pcVar1)) {
      iVar2 = 0;
      if (0 < *(int *)(pcVar1 + 0x10c)) {
        do {
          if (pcVar1[iVar2 + 0xc] == '\0') {
            if (iVar2 != -1) {
              *param_1 = pcVar1;
              return iVar2;
            }
            break;
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(pcVar1 + 0x10c));
      }
    }
    pcVar1 = *(char **)(pcVar1 + 0x114);
  } while( true );
}

