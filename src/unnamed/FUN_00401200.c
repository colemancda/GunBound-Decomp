/* FUN_00401200 - 0x00401200 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00401200(int param_1)

{
  int iVar1;
  int iVar2;
  sockaddr local_40 [2];
  undefined1 local_20 [32];
  
  iVar1 = DAT_007934e8;
  if (DAT_007934e8 != 0) {
    iVar2 = *(int *)(DAT_007934e8 + 0x84ec) + 1;
    *(int *)(DAT_007934e8 + 0x84ec) = iVar2;
    if (0x1d < iVar2) {
      *(undefined2 *)(iVar1 + 0x4d4) = 0;
      *(undefined4 *)(iVar1 + 0x44d0) = 6;
      FUN_004d2680();
      *(undefined4 *)(DAT_007934e8 + 0x84ec) = 0;
    }
    if ((*(char *)(param_1 + 0x10) != '\0') && (DAT_00e9af60 = DAT_00e9af60 + 1, 0xb < DAT_00e9af60)
       ) {
      Replay_AppendEvent(0x9001);
      Replay_FlushEvent();
      DAT_00e9af60 = 0;
    }
  }
  if ((DAT_00e55a54 != '\0') && (DAT_00e55a58 < 0x1e)) {
    BuildSystemInfoBlob(local_20);
    if (DAT_00e55a64 != (int *)0x0) {
      (**(code **)(*DAT_00e55a64 + 0xc))(&DAT_005b1c70,DAT_005b33f4,local_20,local_40);
    }
    DAT_00e55a58 = DAT_00e55a58 + 1;
  }
  if (DAT_007934f8 != '\0') {
    while (DAT_00e55cf4 != 0xffffffff) {
      local_40[0].sa_family = 2;
      local_40[0].sa_data[2] = (undefined1)DAT_005b2b54;
      local_40[0].sa_data[3] = SUBFIELD(DAT_005b2b54,1,undefined1);
      local_40[0].sa_data[4] = SUBFIELD(DAT_005b2b54,2,undefined1);
      local_40[0].sa_data[5] = SUBFIELD(DAT_005b2b54,3,undefined1);
      local_40[0].sa_data[0] = (undefined1)DAT_005b343c;
      local_40[0].sa_data[1] = SUBFIELD(DAT_005b343c,1,undefined1);
      if (DAT_005b2b54 == -1) {
        return;
      }
      if (DAT_005b343c == -1) {
        return;
      }
      iVar1 = sendto(DAT_00e55cf4,&DAT_0054b460,1,0,local_40,0x10);
      if (iVar1 != -1) {
        return;
      }
      ShowErrorDialog(1);
      WSAGetLastError();
    }
  }
  return;
}

