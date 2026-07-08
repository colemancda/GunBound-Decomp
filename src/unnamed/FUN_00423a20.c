/* FUN_00423a20 - 0x00423a20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00423a20(int param_1)

{
  int *piVar1;
  void *_Dst;
  byte bVar2;
  uint uVar3;
  byte in_AL;
  char cVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  undefined1 local_8 [8];
  
  cVar4 = FUN_0041c190();
  if (cVar4 != '\0') {
    *(undefined4 *)(&DAT_006a7670 + (uint)in_AL * 8 + param_1) = 0;
    *(undefined4 *)((int)(&DAT_006a7670 + (uint)in_AL * 8 + param_1) + 4) = 0;
    Replay_AppendEvent(0xc303);
    (&g_replayEventBuffer)[g_replayEventCursor] = in_AL;
    g_replayEventCursor = g_replayEventCursor + 1;
    if (in_AL == 0xe) {
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        iVar7 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = _rand();
        *(byte *)(iVar7 + 0x8bab) = (byte)iVar5;
        iVar5 = _rand();
        bVar2 = *(byte *)(iVar7 + 0x8bab);
        *(byte *)(iVar7 + 0x8bac) = (byte)iVar5;
        bVar8 = '\x01' << (bVar2 & 7);
        bVar8 = ~bVar8 & (byte)iVar5 | bVar8;
        *(byte *)(iVar7 + 0x8bac) = bVar8;
        *(byte *)(iVar7 + 0x8bad) = bVar8 + bVar2 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) =
           *(undefined2 *)(&DAT_006aab04 + param_1);
      g_replayEventCursor = g_replayEventCursor + 2;
      FUN_0041f200(0);
    }
    Replay_FlushEvent();
    uVar3 = *(uint *)(&DAT_006a76f8 + g_clientContext);
    uVar6 = 0;
    iVar7 = g_clientContext;
    if (uVar3 != 0) {
      do {
        if (uVar3 <= uVar6) {
LAB_00423b89:
                    /* WARNING: Subroutine does not return */
          FUN_004010c0(0x80070057);
        }
        if (*(uint *)(*(int *)(&DAT_006a76f4 + g_clientContext) + uVar6 * 4) == (uint)in_AL) {
          piVar1 = (int *)(&DAT_006a76f8 + g_clientContext);
          if (*(uint *)(&DAT_006a76f8 + g_clientContext) < uVar6 + 1) goto LAB_00423b89;
          iVar7 = (*(uint *)(&DAT_006a76f8 + g_clientContext) - uVar6) + -1;
          if (iVar7 != 0) {
            _Dst = (void *)(*(int *)(&DAT_006a76f4 + g_clientContext) + uVar6 * 4);
            _memmove(_Dst,(void *)((int)_Dst + 4),iVar7 * 4);
          }
          iVar7 = g_clientContext;
          *piVar1 = *piVar1 + -1;
          break;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar3);
    }
    (&DAT_006aa624)[iVar7] = 0xff;
    if (*(int *)(&DAT_006a76f8 + iVar7) == 0) {
      FUN_004e86f0(local_8);
    }
  }
  return;
}

