/* DecodeXFSEntryBlock - 0x004f03f0 in the original binary.
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


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

/* Promoted: `readState` (the caller's XFS read cursor) arrived in ECX
 * (__fastcall this); Ghidra already recovered it as param_1. */
bool DecodeXFSEntryBlock(void *readState)

{
  int param_1 = (int)readState;
  DWORD DVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  DWORD local_200c;
  DWORD local_2008;
  int local_2004;
  undefined1 local_2000 [8188];
  undefined4 uStack_4;
  
  uStack_4 = 0x4f03fa;
  iVar4 = 0;
  DVar1 = SetFilePointer(*(HANDLE *)(param_1 + 0x1000),*(LONG *)(param_1 + 0x1010),(PLONG)0x0,0);
  if (DVar1 == 0xffffffff) {
    return false;
  }
  ReadFile(*(HANDLE *)(param_1 + 0x1000),&local_2008,4,&local_200c,(LPOVERLAPPED)0x0);
  if (local_200c == 4) {
    ReadFile(*(HANDLE *)(param_1 + 0x1000),&local_2004,4,&local_200c,(LPOVERLAPPED)0x0);
    if (local_200c == 4) {
      ReadFile(*(HANDLE *)(param_1 + 0x1000),local_2000,local_2008,&local_200c,(LPOVERLAPPED)0x0);
      if (local_200c == local_2008) {
        DecodeLZHUFBlock(*(undefined4 *)(param_1 + 0x101c),param_1,local_2000,local_2008,0x1000);
        *(undefined4 *)(param_1 + 0x100c) = 0;
        *(DWORD *)(param_1 + 0x1010) = *(int *)(param_1 + 0x1010) + local_2008 + 8;
        if (*(char *)(param_1 + 0x1020) != '\0') {
          piVar2 = (int *)(param_1 + 8);
          iVar3 = 0x100;
          do {
            iVar4 = iVar4 + piVar2[-2] + piVar2[-1] + piVar2[1] + *piVar2;
            piVar2 = piVar2 + 4;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          if (iVar4 != local_2004) {
            DAT_00793640 = 1;
          }
          return iVar4 == local_2004;
        }
        return true;
      }
    }
  }
  return false;
}

