/* DispatchDirectLinkMessengerPacket - 0x00411b40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. The 0xa2xx-family opcode handler for the
 * direct-link messenger/buddy connection: dispatches on the opcode word
 * (in_AX) across 0x1fff/0xa001/0xa100/0xa101/0xa250/0xa2f0/0xa2f1/0xa300,
 * covering buddy-socket teardown, local profile sync, channel-roster
 * bulk-fill, chat-line relay and per-buddy status updates. UpdateBuddyStatus's
 * own already-committed header already calls this function "the 0xa2xx-opcode
 * messenger handler" by name, and its sibling DispatchDirectLinkPacket (the
 * 0x1xxx/0x2xxx-opcode dispatcher on the same direct-link connection) is
 * named with the identical Dispatch...Packet pattern. DrainDirectLinkActionRing's
 * header already predicted this exact function as its own opcode-dispatch
 * target for the ring entries it does not resolve inline.
 *
 * OPCODE IN AX RECOVERED (2026-10-30): the prologue is `movzx eax,ax /
 * cmp eax,0xa250` (0x411b4d), with ECX = the payload (`mov ebx,ecx`,
 * 0x411b57) and EDX = its length (`mov esi,edx`, 0x411b59). Ghidra kept
 * ECX/EDX as the __fastcall pair and read the opcode from an
 * uninitialised in_AX. It is promoted to a trailing stack parameter,
 * regAx, and both call sites in DrainDirectLinkActionRing (0x405af5,
 * 0x405b0c) now pass all three: `mov ax,[ecx]` / `add ecx,2` at
 * 0x405ab5-0x405abb (the opcode word and the payload after it) and
 * `lea edx,[esi-2]` with esi = [conn + index*4 + 0x24640] (0x405a90),
 * the slot's length minus the opcode.
 *
 * SPLIT STACK STRINGS COALESCED (2026-10-30): the frame (0x154 bytes,
 * three pushes) holds five byte buffers that Ghidra split into dword
 * locals. Their names are their offsets, and every path fills them with
 * dword moves and then stores a NUL byte at the end:
 *   esp+0x10  local_158..local_14c  12 chars + NUL [esp+0x1c]  (name)
 *   esp+0x20  local_148..local_140   8 chars + NUL [esp+0x28]
 *   esp+0x2c  local_13c..local_12c  16 chars + NUL [esp+0x3c]  (id)
 *   esp+0x48  local_120..local_10e  18 chars + NUL [esp+0x5a]
 *   esp+0x60  local_108             0x100 bytes: the 0xa101 line buffer
 *             (zeroed as 1+0x3f*4+2+1 bytes, 0x411e5f-0x411e78) and the
 *             0x80-byte 0xff fill (0x411c6a, 0x4120c6)
 * Each is passed by address as a string (StringMap_SetAt_CString,
 * FUN_00508d00, UpsertDirectLinkBuddyNode, UpdateBuddyStatus, ...), so
 * separate locals that MSVC may reorder are wrong. local_108 was even
 * declared as 3 bytes and then written for 0x100. Each is now one char
 * array, named after its first Ghidra local. The `x & 0xffffff` on the
 * second dword of local_148 is byte 7 of that string: when byte 7 has its
 * high bit set and byte 6 does not (0x411d05-0x411d20, 0x412094-0x4120c1),
 * byte 7 is cut. That is a DBCS lead-byte truncation, and it is now
 * written as one.
 *
 * Fixed with the coalesce: the 0xa2f1 path passed &local_150 (name+8) to
 * RemoveDirectLinkBuddyNode. 0x41200a is `lea eax,[esp+0x14]` after one
 * push, which is esp+0x10, the start of the name, as its stores at
 * 0x412013/0x412017 (also after the push) and 0x412001 (before it) show.
 */
#include "ghidra_types.h"


void __fastcall DispatchDirectLinkMessengerPacket(uint *param_1,int param_2,ushort regAx)

{
  int iVar1;
  int iVar2;
  char cVar3;
  ushort in_AX = regAx;
  char *puVar4;
  char cVar5;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  char *puVar9;
  char *pcVar10;
  char local_158[0x10];      /* esp+0x10: 12-char name + NUL */
  char local_148[0xc];       /* esp+0x20: 8 chars + NUL */
  char local_13c[0x14];      /* esp+0x2c: 16-char id + NUL */
  int local_128;
  uint local_124;
  char local_120[0x18];      /* esp+0x48: 18 chars + NUL */
  char local_108[0x100];     /* esp+0x60: line / record buffer */

  iVar7 = g_clientContext;
  if (in_AX < 0xa251) {
    if (in_AX == 0xa250) {
      /* 0x411ee5-0x411f35 */
      *(uint *)(local_13c + 0) = param_1[0];
      *(uint *)(local_13c + 4) = param_1[1];
      *(uint *)(local_13c + 8) = param_1[2];
      *(uint *)(local_13c + 0xc) = param_1[3];
      *(uint *)(local_158 + 0) = param_1[4];
      *(uint *)(local_158 + 8) = param_1[6];
      *(uint *)(local_158 + 4) = param_1[5];
      local_13c[0x10] = 0;
      local_158[0xc] = 0;
      StringMap_SetAt_CString(local_158,&DAT_006aa41c + g_clientContext,local_13c);
      StringMap_SetAt_CString(local_13c,&DAT_006aa44c + iVar7,local_158);
      /* 0x411f59: lea edi,[esp+0x14] after the push is the same slot the
       * second StringMap call took as [esp+0x10] (0x411f3f), i.e. the
       * 12-byte name. */
      FUN_00508d00((int)&g_uiPanelManager,(uchar *)local_158);
      return;
    }
    if (in_AX < 0xa101) {
      if (in_AX == 0xa100) {
        ProcessIncomingWhisper((int)&DAT_00e53e88,param_2,(int)param_1);
        return;
      }
      if (in_AX == 0x1fff) {
        if (g_directLinkConnection != 0) {
          CloseDirectLinkSocket((int)g_directLinkConnection);
          return;
        }
      }
      else if (in_AX == 0xa001) {
        FUN_00405b20();
        SetGuardedBool(*(char *)((int)param_1 + 2) == '\x01',GB_GUARD_UNRECOVERED);
        iVar7 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x3b96b) = *(undefined4 *)((int)param_1 + 3);
        *(undefined4 *)(iVar7 + 0x3b96f) = *(undefined4 *)((int)param_1 + 7);
        *(undefined4 *)(iVar7 + 0x3b973) = *(undefined4 *)((int)param_1 + 0xb);
        *(undefined4 *)(iVar7 + 0x3b977) = *(undefined4 *)((int)param_1 + 0xf);
        /* 0x411bde-0x411c10: the 12-char name, NUL-terminated, copied to
         * g_clientContext + 0x23330. */
        *(uint *)(local_158 + 0) = *(uint *)((int)param_1 + 0x13);
        *(uint *)(local_158 + 4) = *(uint *)((int)param_1 + 0x17);
        *(uint *)(local_158 + 8) = *(uint *)((int)param_1 + 0x1b);
        local_158[0xc] = 0;
        puVar4 = local_158;
        pcVar10 = (char *)(iVar7 + 0x23330);
        do {
          cVar5 = *puVar4;
          *pcVar10 = cVar5;
          puVar4 = puVar4 + 1;
          pcVar10 = pcVar10 + 1;
        } while (cVar5 != '\0');
        local_124 = (uint)*(ushort *)((int)param_1 + 0x29);
        param_1 = (uint *)((int)param_1 + 0x2b);
        local_128 = 0;
        if (local_124 != 0) {
          do {
            /* 0x411c30-0x411c5d: a 20-char group name + NUL. */
            *(uint *)(local_108 + 0) = param_1[0];
            *(uint *)(local_108 + 4) = param_1[1];
            *(uint *)(local_108 + 8) = param_1[2];
            *(uint *)(local_108 + 0xc) = param_1[3];
            *(uint *)(local_108 + 0x10) = param_1[4];
            local_108[0x14] = 0;
            puVar8 = (undefined4 *)(param_1 + 5);
            FUN_00401cb0(local_108,(int)&DAT_00e53e88);
            {
              undefined4 *puFill = (undefined4 *)local_108;
              for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
                *puFill = 0xffffffff;
                puFill = puFill + 1;
              }
            }
            param_1 = (uint *)((int)param_1 + 0x16);
            iVar7 = g_clientContext;
            for (uVar5 = (uint)*(ushort *)puVar8; g_clientContext = iVar7, uVar5 != 0; uVar5 = uVar5 - 1)
            {
              /* 0x411c96-0x411cda: 12 chars of the 16-char id (its last
               * dword is not written on this path), then the name. */
              *(uint *)(local_13c + 0) = param_1[0];
              *(uint *)(local_13c + 4) = param_1[1];
              *(uint *)(local_13c + 8) = param_1[2];
              *(uint *)(local_158 + 0) = param_1[4];
              *(uint *)(local_158 + 4) = param_1[5];
              *(uint *)(local_158 + 8) = param_1[6];
              local_13c[0x10] = 0;
              local_158[0xc] = 0;
              StringMap_SetAt_CString(local_158,&DAT_006aa41c + iVar7,local_13c);
              StringMap_SetAt_CString(local_13c,&DAT_006aa44c + iVar7,local_158);
              *(uint *)(local_148 + 4) = param_1[8];
              *(uint *)(local_148 + 0) = param_1[7];
              local_148[8] = 0;
              if ((local_148[7] < '\0') && (-1 < local_148[6])) {
                local_148[7] = 0;
              }
              puVar8 = (undefined4 *)(param_1 + 9);
              param_1 = (uint *)((int)param_1 + 0x26);
              UpsertDirectLinkBuddyNode(local_148,(int)&DAT_00e53e88,1,local_128,*(short *)puVar8,
                           (undefined4 *)local_108,local_13c,local_158);
              iVar7 = g_clientContext;
            }
            local_128 = local_128 + 1;
          } while (local_128 < (int)local_124);
        }
        cVar3 = CheckGuardedBoolAnd(g_currentGameState == 2);
        iVar7 = DAT_007934f0;
        if ((cVar3 != '\0') && (*(char *)(DAT_007934f0 + 0x84e5) == '\x01')) {
          *(undefined4 *)(DAT_007934f0 + 0x44d0) = 6;
          *(undefined2 *)(iVar7 + 0x4d4) = 0x1100;
          *(undefined1 *)(iVar7 + 0x4d6) = 0;
          iVar1 = *(int *)(iVar7 + 0x44d0);
          *(int *)(iVar7 + 0x44d0) = iVar1 + 1;
          iVar2 = g_clientContext;
          *(undefined1 *)(iVar1 + 0x4d1 + iVar7) = 0;
          iVar1 = *(int *)(iVar7 + 0x44d0);
          *(int *)(iVar7 + 0x44d0) = iVar1 + 1;
          *(ushort *)(iVar1 + 0x4d1 + iVar7) = *(ushort *)(iVar2 + 0x3b96b) / 10;
          *(int *)(iVar7 + 0x44d0) = *(int *)(iVar7 + 0x44d0) + 2;
          SendOutgoingPacket(iVar7);
          return;
        }
      }
    }
    else if (in_AX == 0xa101) {
      /* 0x411e5d-0x411e78: the whole 0x100-byte line buffer zeroed. */
      for (iVar7 = 0; iVar7 < 0x100; iVar7 = iVar7 + 1) {
        local_108[iVar7] = 0;
      }
      param_2 = param_2 + -4;
      iVar7 = 0;
      uVar6 = 4;
      if (0 < param_2) {
        param_1 = param_1 + 1;
        do {
          cVar3 = (char)*param_1;
          if (cVar3 == '\n') {
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                      (g_gameStateVTableArray[g_currentGameState],local_108,3,uVar6);
            uVar6 = 0;
            puVar8 = (undefined4 *)local_108;
            for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar8 = 0;
              puVar8 = puVar8 + 1;
            }
            iVar7 = 0;
          }
          else if (cVar3 != '\r') {
            local_108[iVar7] = cVar3;
            iVar7 = iVar7 + 1;
          }
          param_1 = (uint *)((int)param_1 + 1);
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(g_gameStateVTableArray[g_currentGameState],local_108,3,uVar6);
      return;
    }
  }
  else if (in_AX == 0xa2f0) {
    /* 0x41202c-0x4120b1 */
    *(uint *)(local_13c + 0) = param_1[0];
    *(uint *)(local_13c + 4) = param_1[1];
    *(uint *)(local_13c + 8) = param_1[2];
    *(uint *)(local_13c + 0xc) = param_1[3];
    *(uint *)(local_158 + 0) = param_1[4];
    *(uint *)(local_158 + 4) = param_1[5];
    *(uint *)(local_158 + 8) = param_1[6];
    *(uint *)(local_120 + 0) = param_1[7];
    *(uint *)(local_120 + 4) = param_1[8];
    *(uint *)(local_120 + 8) = param_1[9];
    *(uint *)(local_120 + 0xc) = param_1[10];
    *(undefined2 *)(local_120 + 0x10) = (undefined2)param_1[0xb];
    *(undefined4 *)(local_148 + 0) = *(undefined4 *)((int)param_1 + 0x2e);
    *(uint *)(local_148 + 4) = *(uint *)((int)param_1 + 0x32);
    local_13c[0x10] = 0;
    local_158[0xc] = 0;
    local_120[0x12] = 0;
    local_148[8] = 0;
    if ((local_148[7] < '\0') && (-1 < local_148[6])) {
      local_148[7] = 0;
    }
    puVar8 = (undefined4 *)local_108;
    for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = 0xffffffff;
      puVar8 = puVar8 + 1;
    }
    uVar5 = (uint)*(ushort *)((int)param_1 + 0x36);
    puVar4 = local_13c;
    puVar9 = local_108;
    uVar6 = FUN_00401ce0((int)&DAT_00e53e88,(byte *)local_120);
    UpsertDirectLinkBuddyNode(local_148,(int)&DAT_00e53e88,1,uVar6,(short)uVar5,
                 (undefined4 *)puVar9,puVar4,local_158);
    UpdateBuddyStatus((int)&DAT_00e53e88,local_13c,(undefined1 *)((int)param_1 + 0x38));
  }
  else {
    if (in_AX == 0xa2f1) {
      /* 0x411fd8-0x412020 */
      *(uint *)(local_13c + 0) = param_1[0];
      *(uint *)(local_13c + 4) = param_1[1];
      *(uint *)(local_13c + 8) = param_1[2];
      *(uint *)(local_13c + 0xc) = param_1[3];
      *(uint *)(local_158 + 0) = param_1[4];
      *(uint *)(local_158 + 8) = param_1[6];
      *(uint *)(local_158 + 4) = param_1[5];
      local_13c[0x10] = 0;
      local_158[0xc] = 0;
      /* 0x41200a: lea eax,[esp+0x14] after the push = the name at esp+0x10. */
      RemoveDirectLinkBuddyNode((int)&DAT_00e53e88,local_158);
      return;
    }
    if (in_AX == 0xa300) {
      /* 0x411f80-0x411fcc */
      *(uint *)(local_13c + 0) = param_1[0];
      *(uint *)(local_13c + 4) = param_1[1];
      *(uint *)(local_13c + 8) = param_1[2];
      *(uint *)(local_13c + 0xc) = param_1[3];
      *(uint *)(local_158 + 0) = param_1[4];
      *(uint *)(local_158 + 4) = param_1[5];
      *(uint *)(local_158 + 8) = param_1[6];
      local_13c[0x10] = 0;
      local_158[0xc] = 0;
      UpdateBuddyStatus((int)&DAT_00e53e88,local_158,(undefined1 *)((int)param_1 + 0x1c));
      return;
    }
  }
  return;
}
