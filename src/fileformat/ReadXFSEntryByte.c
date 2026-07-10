/* ReadXFSEntryByte - 0x004f06c0 in the original binary.
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


/* Promoted: reads `count` bytes (was in EAX) from the XFS read cursor
 * `readState` (param_1) into `outBuf` (param_2), decoding blocks on
 * demand. Returns the byte count read (or an error sentinel). */
uint ReadXFSEntryByte(undefined4 *param_1,undefined4 *param_2,uint count)

{
  uint in_EAX = count;
  char *pcVar1;
  undefined4 *puVar2;
  char cVar3;
  DWORD DVar4;
  BOOL BVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar2 = param_1;
  pcVar1 = (char *)(param_1 + 0x406);
  param_1 = (undefined4 *)0x0;
  if (*pcVar1 == '\0') {
    return 0xffffffff;
  }
  iVar9 = puVar2[0x401];
  uVar7 = puVar2[0x405];
  uVar6 = *(uint *)(iVar9 + 0x78);
  if (uVar6 <= uVar7) {
    return 0;
  }
  if (uVar6 < uVar7 + in_EAX) {
    in_EAX = uVar6 - uVar7;
  }
  if (*(int *)(iVar9 + 0x70) == 1) {
    DVar4 = SetFilePointer((HANDLE)puVar2[0x400],*(int *)(iVar9 + 0x74) + uVar7,(PLONG)0x0,0);
    if ((DVar4 != 0xffffffff) &&
       (BVar5 = ReadFile((HANDLE)puVar2[0x400],param_2,in_EAX,(LPDWORD)&param_1,(LPOVERLAPPED)0x0),
       BVar5 != 0)) {
LAB_004f0884:
      puVar2[0x405] = puVar2[0x405] + (int)param_1;
      return (uint)param_1;
    }
  }
  else {
    iVar9 = puVar2[0x403];
    if (iVar9 + in_EAX < 0x1001) {
      uVar6 = ((int)in_EAX < 0) - 1 & in_EAX;
      puVar10 = (undefined4 *)(iVar9 + (int)puVar2);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *param_2 = *puVar10;
        puVar10 = puVar10 + 1;
        param_2 = param_2 + 1;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)param_2 = *(undefined1 *)puVar10;
        puVar10 = (undefined4 *)((int)puVar10 + 1);
        param_2 = (undefined4 *)((int)param_2 + 1);
      }
      puVar2[0x405] = puVar2[0x405] + in_EAX;
      puVar2[0x403] = puVar2[0x403] + in_EAX;
      return in_EAX;
    }
    uVar7 = 0x1000 - iVar9;
    uVar8 = ((int)uVar7 < 0) - 1 & uVar7;
    puVar10 = (undefined4 *)(iVar9 + (int)puVar2);
    puVar11 = param_2;
    for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar11 = *(undefined1 *)puVar10;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    cVar3 = DecodeXFSEntryBlock(puVar2);
    if (cVar3 != '\0') {
      param_1 = (undefined4 *)((int)param_1 + uVar7);
      param_2 = (undefined4 *)(uVar7 + (int)param_2);
      for (uVar7 = in_EAX - uVar7; 0x1000 < uVar7; uVar7 = uVar7 - 0x1000) {
        puVar10 = puVar2;
        puVar11 = param_2;
        for (iVar9 = 0x400; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar11 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar11 = puVar11 + 1;
        }
        cVar3 = DecodeXFSEntryBlock(puVar2);
        if (cVar3 == '\0') {
          return 0xfffffffe;
        }
        param_2 = param_2 + 0x400;
        param_1 = (undefined4 *)((int)param_1 + 0x1000);
      }
      uVar8 = ((int)uVar7 < 0) - 1 & uVar7;
      puVar10 = puVar2;
      for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *param_2 = *puVar10;
        puVar10 = puVar10 + 1;
        param_2 = param_2 + 1;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined1 *)param_2 = *(undefined1 *)puVar10;
        puVar10 = (undefined4 *)((int)puVar10 + 1);
        param_2 = (undefined4 *)((int)param_2 + 1);
      }
      puVar2[0x403] = uVar7;
      param_1 = (undefined4 *)((int)param_1 + uVar7);
      goto LAB_004f0884;
    }
  }
  return 0xffffffff;
}

