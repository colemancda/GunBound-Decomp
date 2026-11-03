/* XFSArchive_ComputeChecksum - 0x004f1020 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): CloseXFSArchive (0x4f0d70) stores its
 * result at archive+0xc when the checksum flag at +0x10730 is set, and the
 * avatar verifier (VerifyAvatarArchiveIntegrity, 0x419d30) compares it
 * against the stored value at archive+0xc (ctx+0xf6f4). It rereads the
 * archive file from offset 0 and sums the first archive+0x10 bytes (the
 * data length, footer excluded) as dwords.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

int __fastcall XFSArchive_ComputeChecksum(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  DWORD local_1004;
  int local_1000 [1024];
  
  local_1000[0x3ff] = 0x4f102a;
  if (((*(char *)(param_1 + 0x1044) == '\0') &&
      (*(HANDLE *)(param_1 + 0x1040) != (HANDLE)0xffffffff)) &&
     (*(char *)(param_1 + 0x10730) != '\0')) {
    uVar7 = *(uint *)(param_1 + 0x10);
    iVar8 = 0;
    SetFilePointer(*(HANDLE *)(param_1 + 0x1040),0,(PLONG)0x0,0);
    for (uVar5 = uVar7 >> 0xc; uVar5 != 0; uVar5 = uVar5 - 1) {
      ReadFile(*(HANDLE *)(param_1 + 0x1040),local_1000,0x1000,&local_1004,(LPOVERLAPPED)0x0);
      iVar6 = 0;
      do {
        iVar2 = iVar6 + 2;
        iVar3 = iVar6 + 3;
        iVar4 = iVar6 + 1;
        piVar1 = local_1000 + iVar6;
        iVar6 = iVar6 + 4;
        iVar8 = iVar8 + local_1000[iVar3] + local_1000[iVar2] + local_1000[iVar4] + *piVar1;
      } while (iVar6 < 0x400);
    }
    uVar5 = uVar7 >> 2 & 0x3ff;
    if (uVar5 != 0) {
      ReadFile(*(HANDLE *)(param_1 + 0x1040),local_1000,uVar5 * 4,&local_1004,(LPOVERLAPPED)0x0);
      uVar7 = 0;
      if (uVar5 != 0) {
        do {
          iVar8 = iVar8 + local_1000[uVar7];
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar5);
      }
    }
    return iVar8;
  }
  return 0;
}

