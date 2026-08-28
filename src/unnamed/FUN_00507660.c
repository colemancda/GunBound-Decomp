/* FUN_00507660 - 0x00507660 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00507660(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char *pcStack_14; /* DROPPED-REG FIX 2026-08-28: the CString handle at
                       entry-0x14, in the sub-esp,8 hole; written only by
                       the FUN_004055b0 call, read back as puVar5 */
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005407d8) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  (**(code **)(DAT_005b1444 + 0xc))();
  uStack_4 = 0;
  if (param_2 == 0) {
    if ((param_3 < 9) && (*(uint *)(g_clientContext + 0x41340) != param_3)) {
      FUN_00507cc0(0,*(uint *)(g_clientContext + 0x41340),param_1);
      iVar2 = g_connectionContextA;
      *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
      *(undefined2 *)(iVar2 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar2 + 0x4d6) = (undefined2)param_3;
      *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 2;
      SendOutgoingPacket(iVar2);
    }
  }
  else if (param_2 == 0x1000) {
    uVar6 = Widget_FindChildIndex();
    if (uVar6 != 0xffffffff) {
      cVar3 = PacketChecksumNotEquals(g_clientContext + 0x449c4,1);
      if (cVar3 != '\0') {
        if (*(uint *)(param_1 + 0x10) <= uVar6) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        /* DROPPED-REG FIX 2026-08-28: the text is the found child
           widget's +0x38 buffer (`mov edx,[ecx+esi*4] / add edx,0x38` at
           0x507722), and the handle is an 8-byte frame hole at
           entry-0x14 that Ghidra never declared (`lea edi,[esp+0x10]`
           at 0x50772b, depth 0x24). The code after the call reads the
           string back from that slot and its length from the CString
           header at -0xc - which resolves this file's long-standing
           use-before-set puVar4: it is the header base, string - 0x10,
           and puVar5 the string itself. Both are now assigned here
           instead of the floating `puVar5 = puVar4 + 4` Ghidra hoisted
           to the top of the function. */
        FUN_004055b0(0,(char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar6 * 4) + 0x38),
                     (int)&pcStack_14);
        puVar4 = (undefined4 *)(pcStack_14 + -0x10);
        puVar5 = (undefined4 *)pcStack_14;
        if ((puVar4[1] != 0) && (cVar3 = ParseChatSlashCommand(g_clientContext,puVar5), cVar3 == '\0')) {
          cVar3 = CheckChatWordFilter(puVar5);
          if (cVar3 == '\x01') {
            iVar2 = *(int *)g_gameStateVTableArray[3];
            uVar9 = 6;
            uVar8 = 2;
            uVar7 = GetLocalizedString(&g_localizedStringTable,0x202);
            (**(code **)(iVar2 + 0x28))(uVar7,uVar8,uVar9);
          }
          else {
            cVar3 = FUN_00415230();
            iVar2 = g_connectionContextA;
            if (cVar3 == '\0') {
              *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
              *(undefined2 *)(iVar2 + 0x4d4) = 0x2010;
              *(char *)(iVar2 + 0x4d6) = (char)puVar4[1];
              *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
              /* FIXED (2026-07-15): dropped `self`/`count` args - disasm-
               * confirmed at 0x5077e8. self=EAX=g_connectionContextA (=iVar2
               * above). count=EDX=[ebx-0xc] where ebx is the string reloaded
               * at 0x50775a - that same [ptr-0xc] field is exactly
               * puVar4[1], read just above for the length-prefix byte.
               * (The "use-before-set puVar4" this note used to flag was
               * resolved 2026-08-28: puVar4 is the CString header base,
               * assigned from the recovered FUN_004055b0 handle above.) */
              AppendPacketBytes(0,iVar2,(uint)puVar4[1],puVar5);
              EncodePacketBody(0,iVar2);
              SendOutgoingPacket(iVar2);
              FUN_00425700(g_clientContext);
            }
            else {
              iVar2 = *(int *)g_gameStateVTableArray[3];
              uVar9 = 6;
              uVar8 = 2;
              uVar7 = GetLocalizedString(&g_localizedStringTable,0x205);
              (**(code **)(iVar2 + 0x28))(uVar7,uVar8,uVar9);
            }
          }
        }
      }
      if (*(uint *)(param_1 + 0x10) <= uVar6) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      FUN_00506f30(*(int *)(*(int *)(param_1 + 0xc) + uVar6 * 4));
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(g_clientContext + 0x3b97c) = param_4;
  }
  Widget_OnCommandDefault(param_2,param_3,param_4);
  uStack_4 = 0xffffffff;
  piVar1 = puVar4 + 3;
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar4 + 4))(puVar4);
  }
  return;
}

