/* TallyRoomTeamStats - 0x004db570 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall TallyRoomTeamStats(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  
  iVar2 = g_clientContext;
  *(undefined4 *)(param_1 + 0x490) = 0;
  *(undefined4 *)(param_1 + 0x494) = 0;
  *(undefined2 *)(param_1 + 0x4ce) = 0;
  *(undefined2 *)(param_1 + 0x4d0) = 0;
  iVar3 = 0;
  psVar4 = (short *)(iVar2 + 0x4591e);
  do {
    if (*(char *)(iVar2 + 0x45914 + iVar3) != '\0') {
      cVar1 = *(char *)(iVar2 + 0x4590c + iVar3);
      if (cVar1 == '\x01') {
        *(int *)(param_1 + 0x494) = *(int *)(param_1 + 0x494) + 1;
        *(short *)(param_1 + 0x4d0) = *(short *)(param_1 + 0x4d0) + psVar4[-1];
      }
      else if (cVar1 == '\0') {
        *(int *)(param_1 + 0x490) = *(int *)(param_1 + 0x490) + 1;
        *(short *)(param_1 + 0x4ce) = *(short *)(param_1 + 0x4ce) + psVar4[-1];
      }
    }
    if (*(char *)(iVar2 + 0x45915 + iVar3) != '\0') {
      cVar1 = *(char *)(iVar2 + 0x4590d + iVar3);
      if (cVar1 == '\x01') {
        *(int *)(param_1 + 0x494) = *(int *)(param_1 + 0x494) + 1;
        *(short *)(param_1 + 0x4d0) = *(short *)(param_1 + 0x4d0) + *psVar4;
      }
      else if (cVar1 == '\0') {
        *(int *)(param_1 + 0x490) = *(int *)(param_1 + 0x490) + 1;
        *(short *)(param_1 + 0x4ce) = *(short *)(param_1 + 0x4ce) + *psVar4;
      }
    }
    if (*(char *)(iVar2 + 0x45916 + iVar3) != '\0') {
      cVar1 = *(char *)(iVar2 + 0x4590e + iVar3);
      if (cVar1 == '\x01') {
        *(int *)(param_1 + 0x494) = *(int *)(param_1 + 0x494) + 1;
        *(short *)(param_1 + 0x4d0) = *(short *)(param_1 + 0x4d0) + psVar4[1];
      }
      else if (cVar1 == '\0') {
        *(int *)(param_1 + 0x490) = *(int *)(param_1 + 0x490) + 1;
        *(short *)(param_1 + 0x4ce) = *(short *)(param_1 + 0x4ce) + psVar4[1];
      }
    }
    if (*(char *)(iVar2 + 0x45917 + iVar3) != '\0') {
      cVar1 = *(char *)(iVar2 + 0x4590f + iVar3);
      if (cVar1 == '\x01') {
        *(int *)(param_1 + 0x494) = *(int *)(param_1 + 0x494) + 1;
        *(short *)(param_1 + 0x4d0) = *(short *)(param_1 + 0x4d0) + psVar4[2];
      }
      else if (cVar1 == '\0') {
        *(int *)(param_1 + 0x490) = *(int *)(param_1 + 0x490) + 1;
        *(short *)(param_1 + 0x4ce) = *(short *)(param_1 + 0x4ce) + psVar4[2];
      }
    }
    iVar3 = iVar3 + 4;
    psVar4 = psVar4 + 4;
  } while (iVar3 < 8);
  if (*(int *)(param_1 + 0x490) == 0) {
    *(undefined2 *)(param_1 + 0x4ce) = 0xffff;
  }
  else {
    *(short *)(param_1 + 0x4ce) =
         (short)(((uint)((longlong)(ulonglong)*(ushort *)(param_1 + 0x4ce) /
                        (longlong)*(int *)(param_1 + 0x490)) & 0xffff) / 5);
  }
  if (*(int *)(param_1 + 0x494) != 0) {
    *(short *)(param_1 + 0x4d0) =
         (short)(((uint)((longlong)(ulonglong)*(ushort *)(param_1 + 0x4d0) /
                        (longlong)*(int *)(param_1 + 0x494)) & 0xffff) / 5);
    return;
  }
  *(undefined2 *)(param_1 + 0x4d0) = 0xffff;
  return;
}

