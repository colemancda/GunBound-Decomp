/* SendSocketData - 0x004e5ac0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint __thiscall SendSocketData(char *param_1,int param_2,uint param_3)

{
  uint len;
  int iVar1;
  uint uVar2;
  char *pcVar3;
  char local_4010 [16384];
  uint local_10;
  undefined4 uStack_c;
  
  uStack_c = 0x4e5ad0;
  len = param_3;
  if (*(char *)(param_2 + 0x22a) == '\0') {
    return 0xffffffff;
  }
  do {
    if ((int)len < 1) {
LAB_004e5b94:
      return param_3 - (((int)len < 0) - 1 & len);
    }
    iVar1 = send(*(SOCKET *)(param_2 + 0x24),param_1,len,0);
    if (iVar1 < 1) {
      iVar1 = WSAGetLastError();
      if (iVar1 == 0x2733) {
        pcVar3 = local_4010;
        for (uVar2 = len >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined4 *)pcVar3 = *(undefined4 *)param_1;
          param_1 = param_1 + 4;
          pcVar3 = pcVar3 + 4;
        }
        for (uVar2 = len & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar3 = *param_1;
          param_1 = param_1 + 1;
          pcVar3 = pcVar3 + 1;
        }
        local_10 = len;
        EnterCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x24a58));
        FUN_004e5c70(local_4010);
        LeaveCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x24a58));
        return param_3;
      }
      if ((*(int *)(param_2 + 0x22c) != 1) && (*(int *)(param_2 + 0x20) != 0)) {
        EnqueueInputEvent(0x65,*(undefined4 *)(param_2 + 0x1c),0);
      }
      goto LAB_004e5b94;
    }
    param_1 = param_1 + iVar1;
    len = len - iVar1;
  } while( true );
}

