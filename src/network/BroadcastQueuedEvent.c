/* BroadcastQueuedEvent - 0x004e6fc0 in the original binary.
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


undefined4 BroadcastQueuedEvent(void)

{
  undefined2 *puVar1;
  uint *puVar2;
  int in_EAX;
  DWORD DVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  undefined4 *local_8;
  int *local_4;
  
  /* orig 0x4e6fc9 `mov ebx, esi` (ESI = this function's own dropped-EAX
   * context, set at 0x4e6fc6) - EncryptEventBroadcast's recovered EBX arg. */
  /* RECOVERED (2026-07-19): `in_EAX` is the broadcast/replay CONTEXT base,
   * a dropped register argument - and an uninitialised one here, which is a
   * live wild-write hazard now that EncryptEventBroadcast's RijndaelSetKey
   * calls are enabled (it is used as the base for stores at +0x44dec.. and
   * as the key-schedule context). Every resolvable call site in the original
   * passes the SAME global, &DAT_00e55ce0 = g_replayContext: of this
   * function's 82 direct call sites, 40 load it as an immediate
   * (`mov eax, 0xe55ce0`) and 26 more via `mov eax, esi` where ESI was itself
   * just set from that immediate - with NO call site contradicting it.
   * Promoting it to a real parameter would mean touching all of those call
   * sites for no behavioural difference, so it is bound to the global here
   * instead, with the evidence recorded. See tools/sweep_corroborate.py. */
  in_EAX = (int)&g_replayContext;
  EncryptEventBroadcast(in_EAX);
  *(undefined2 *)(in_EAX + 0x44dec) = *(undefined2 *)(in_EAX + 0x44fec);
  if ((*(byte *)(in_EAX + 0x44def) & 0x80) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x17c));
    uVar4 = 0;
    local_4 = (int *)(in_EAX + 0x38);
    local_8 = (undefined4 *)(in_EAX + 0x78);
    bVar7 = true;
    do {
      if (!bVar7) {
                    /* WARNING: Subroutine does not return */
        FUN_00426460();
      }
      uVar5 = 1 << ((byte)uVar4 & 0x1f);
      iVar6 = (uVar4 >> 5) * 4;
      if ((*(uint *)(iVar6 + 0x140 + in_EAX) & uVar5) != 0) {
        *(byte *)(in_EAX + 0x44df2) = (byte)uVar4;
        *(undefined4 *)(in_EAX + 0x44e01) = *local_8;
        *(undefined4 *)(in_EAX + 0x44e05) = local_8[1];
        *(undefined4 *)(in_EAX + 0x44e09) = local_8[2];
        if (*(char *)(uVar4 + 0x454e4 + in_EAX) == '\0') {
          puVar1 = (undefined2 *)(in_EAX + 0x44dec);
          SendUdpDatagram(*(int *)(in_EAX + 0x18 + uVar4 * 4),
                          (int)*(short *)(in_EAX + 0x58 + uVar4 * 2),(char *)puVar1,
                          (int)*(undefined2 *)(in_EAX + 0x44dec),in_EAX);
          if (*local_4 != -1) {
            SendUdpDatagram(*local_4,(int)*(short *)(in_EAX + 0x68 + uVar4 * 2),(char *)puVar1,
                            (int)*puVar1,in_EAX);
          }
        }
        else {
          FUN_004e8040(uVar4);
          puVar2 = (uint *)(iVar6 + 0x13c + in_EAX);
          *puVar2 = *puVar2 | uVar5;
        }
      }
      uVar4 = uVar4 + 1;
      local_8 = local_8 + 6;
      local_4 = local_4 + 1;
      bVar7 = uVar4 < 8;
    } while ((int)uVar4 < 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x17c));
    *(undefined4 *)(in_EAX + 0x45280) = 0;
    DVar3 = timeGetTime();
    *(DWORD *)(in_EAX + 0x4522c) = DVar3;
  }
  else {
    FUN_004e75e0(0xffffffff);
    SetEvent(*(HANDLE *)(in_EAX + 0x10));
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x198));
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

