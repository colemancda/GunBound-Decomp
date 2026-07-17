/* State02_ServerSelect_OnTopButton - 0x004e1200 in the original binary.
 *
 * State02_ServerSelect vtable slot 3 - click dispatcher for the top-level
 * button IDs (param_2 == 3: buddy-list-related request; param_2 == 4: some
 * other UI-state action involving the buddy-list widget mode name and a
 * random per-connection nonce). No confirmed real name/purpose beyond
 * that. Raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * FIXED (2026-07-13): `RET 0x8` at 0x4e1428/0x4e139c (2 stack dwords
 * beyond `this`, confirmed via objdump) but Ghidra's decompile only
 * showed 1 stack parameter (`param_2`) - a 3rd parameter is pushed by
 * every caller and popped on return but genuinely never read inside
 * this function's body (same "unused-but-ABI-real" shape as
 * State02_ServerSelect_HandleKeyInput's 3rd parameter). Added as `param_3` (unused) so the
 * generated `ret N` matches what vtable slot-3 callers actually push.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004e1232) */
/* WARNING: Removing unreachable block (ram,0x004e123c) */
/* WARNING: Removing unreachable block (ram,0x004e1290) */
/* WARNING: Removing unreachable block (ram,0x004e129a) */
/* WARNING: Removing unreachable block (ram,0x004e124a) */
/* WARNING: Removing unreachable block (ram,0x004e1254) */

void __thiscall State02_ServerSelect_OnTopButton(int param_1,int param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;

  iVar5 = DAT_007934ec;
  if (param_2 == 3) {
    *(undefined2 *)(DAT_007934ec + 0x4d4) = 0x2000;
    *(undefined4 *)(iVar5 + 0x44d0) = 6;
    cVar6 = PeekPacketChecksumBool();
    iVar5 = DAT_007934ec;
    if (((cVar6 == '\x01') && (sVar2 = *(short *)(g_clientContext + 0x3b96d), sVar2 != -1)) &&
       (sVar2 != -2)) {
      *(short *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec) = sVar2;
    }
    else {
      *(undefined2 *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec) = 0xffff;
    }
    *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 2;
    SendOutgoingPacket();
    FUN_0041c1e0();
  }
  else if (param_2 == 4) {
    DAT_0056d118 = 0xffffffff;
    if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
        (piVar3 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar3[2] == 0)) &&
       ((piVar3[9] == 3 || (piVar3[9] == -1)))) {
      if ((char)piVar3[0x13] == '\x01') {
        (**(code **)(*piVar3 + 4))(s_active_00551e58);
      }
      else {
        (**(code **)(*piVar3 + 4))(s_ready_00551e80);
      }
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar3 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar4 = piVar3[2];
      while (uVar4 < 2) {
        if (uVar4 == 1) {
          if ((piVar3[9] == 3) || (piVar3[9] == -1)) {
            if ((char)piVar3[0x13] == '\x01') {
              (**(code **)(*piVar3 + 4))(s_active_00551e58);
            }
            else {
              (**(code **)(*piVar3 + 4))(s_ready_00551e80);
            }
          }
          break;
        }
        piVar3 = (int *)piVar3[4];
        uVar4 = piVar3[2];
      }
    }
    InvokeWidget(2,*(int *)(param_1 + 8) != -1);
    ShowErrorDialog(0);
    *(undefined1 *)(param_1 + 6) = 1;
    cVar6 = PeekPacketChecksumBool();
    iVar5 = g_clientContext;
    if (cVar6 != '\0') {
      pbVar9 = (byte *)(g_clientContext + 0x3b968);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = _rand();
      *pbVar9 = (byte)iVar7;
      iVar7 = _rand();
      bVar1 = *pbVar9;
      *(byte *)(iVar5 + 0x3b969) = (byte)iVar7;
      bVar8 = bVar1 & 7;
      bVar8 = ~('\x01' << bVar8) & (byte)iVar7 | '\0' << bVar8;
      *(byte *)(iVar5 + 0x3b969) = bVar8;
      *(byte *)(iVar5 + 0x3b96a) = bVar8 + bVar1 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    FUN_004d24f0();
    return;
  }
  return;
}
