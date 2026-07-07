/* FUN_004ff550 - 0x004ff550 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff550(void)

{
  int *piVar1;
  int *piVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  size_t _Size;
  int unaff_EBX;
  char *buf;
  
  if (in_EAX == 0) {
    if (*(int *)(unaff_EBX + 0x28) != 0) {
      piVar1 = (int *)(unaff_EBX + 0x20);
      do {
        iVar4 = *piVar1;
        buf = (char *)(iVar4 + 8);
        while( true ) {
          iVar3 = send(*(SOCKET *)(unaff_EBX + 8),buf,*(int *)(iVar4 + 0x1778),0);
          if (iVar3 == -1) {
            iVar4 = WSAGetLastError();
            if (iVar4 == 0x2733) {
              return;
            }
            if ((*(SOCKET *)(unaff_EBX + 8) != 0xffffffff) &&
               (iVar4 = shutdown(*(SOCKET *)(unaff_EBX + 8),2), iVar4 != -1)) {
              return;
            }
            FUN_004fe6a0();
            return;
          }
          if (*(int *)(iVar4 + 0x1778) <= iVar3) break;
          _Size = *(int *)(iVar4 + 0x1778) - iVar3;
          *(size_t *)(iVar4 + 0x1778) = _Size;
          _memmove(buf,buf + iVar3,_Size);
        }
        piVar2 = (int *)*piVar1;
        iVar4 = *piVar2;
        *piVar1 = iVar4;
        if (iVar4 == 0) {
          *(undefined4 *)(unaff_EBX + 0x24) = 0;
        }
        else {
          *(undefined4 *)(iVar4 + 4) = 0;
        }
        *piVar2 = *(int *)(unaff_EBX + 0x30);
        iVar4 = *(int *)(unaff_EBX + 0x28) + -1;
        *(int **)(unaff_EBX + 0x30) = piVar2;
        *(int *)(unaff_EBX + 0x28) = iVar4;
        if (iVar4 == 0) {
          FUN_00501010();
        }
      } while (*(int *)(unaff_EBX + 0x28) != 0);
    }
  }
  else if ((*(SOCKET *)(unaff_EBX + 8) == 0xffffffff) ||
          (iVar4 = shutdown(*(SOCKET *)(unaff_EBX + 8),2), iVar4 == -1)) {
    FUN_004fe6a0();
    return;
  }
  return;
}

