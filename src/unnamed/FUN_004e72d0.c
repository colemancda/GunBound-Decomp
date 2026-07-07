/* FUN_004e72d0 - 0x004e72d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004e72d0(int param_1,int param_2,char *param_3,int param_4)

{
  int in_EAX;
  int iVar1;
  sockaddr local_10;
  
  if (*(SOCKET *)(in_EAX + 0x14) != 0xffffffff) {
    local_10.sa_family = 2;
    if ((param_1 != -1) && (param_2 != -1)) {
      local_10.sa_data._0_2_ = param_2;
      local_10.sa_data._2_4_ = param_1;
      iVar1 = sendto(*(SOCKET *)(in_EAX + 0x14),param_3,param_4,0,&local_10,0x10);
      if (iVar1 == -1) {
        FUN_004124a0(1);
        WSAGetLastError();
        return 0;
      }
    }
  }
  return 1;
}

