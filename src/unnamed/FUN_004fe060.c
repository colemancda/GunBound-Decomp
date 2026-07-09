/* FUN_004fe060 - 0x004fe060 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fe060(void)

{
  char cVar1;
  char *in_EAX;
  SOCKET SVar2;
  int iVar3;
  int unaff_ESI;
  sockaddr local_10;
  
  do {
    cVar1 = *in_EAX;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  FUN_005051e0();
  if (*(int *)(unaff_ESI + 0x288) != -1) {
    return 1;
  }
  SVar2 = socket(2,2,0);
  *(SOCKET *)(unaff_ESI + 0x288) = SVar2;
  if (SVar2 != 0xffffffff) {
    local_10.sa_family = 2;
    local_10.sa_data[0] = '\0';
    local_10.sa_data[1] = '\0';
    SUBFIELD(local_10.sa_data,2,undefined4) = htonl(0);
    iVar3 = bind(*(SOCKET *)(unaff_ESI + 0x288),&local_10,0x10);
    if ((iVar3 != -1) &&
       (iVar3 = WSAAsyncSelect(*(SOCKET *)(unaff_ESI + 0x288),*(HWND *)(unaff_ESI + 0x28c),0x54d,3),
       iVar3 != -1)) {
      return 1;
    }
  }
  return 0;
}

