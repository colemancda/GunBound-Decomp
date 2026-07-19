/* FUN_004e7140 - 0x004e7140 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e7140(uint param_1)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  short sVar3;
  byte bVar4;
  int in_EAX;
  
  /* orig 0x4e7144 `mov ebx, esi` (ESI = this function's own dropped-EAX
   * context, set at 0x4e7142) - EncryptEventBroadcast's recovered EBX arg. */
  /* RECOVERED (2026-07-19): `in_EAX` is the broadcast/replay CONTEXT base,
   * a dropped register argument - and an uninitialised one here, which is a
   * live wild-write hazard now that EncryptEventBroadcast's RijndaelSetKey
   * calls are enabled (it is used as the base for stores at +0x44dec.. and
   * as the key-schedule context). Every resolvable call site in the original
   * passes the SAME global, &DAT_00e55ce0 = g_replayContext: of this
   * function's 8 direct call sites, 4 load it as an immediate
   * (`mov eax, 0xe55ce0`) and 2 more via `mov eax, esi` where ESI was itself
   * just set from that immediate - with NO call site contradicting it.
   * Promoting it to a real parameter would mean touching all of those call
   * sites for no behavioural difference, so it is bound to the global here
   * instead, with the evidence recorded. See tools/sweep_corroborate.py. */
  in_EAX = (int)&g_replayContext;
  EncryptEventBroadcast(in_EAX);
  if ((int)param_1 < 8) {
    bVar4 = (byte)param_1;
    if (param_1 != 0xffffffff) {
      if (7 < param_1) {
                    /* WARNING: Subroutine does not return */
        FUN_00426460();
      }
      if ((*(uint *)(in_EAX + 0x140 + (param_1 >> 5) * 4) & 1 << (bVar4 & 0x1f)) == 0)
      goto LAB_004e717d;
    }
    *(undefined2 *)(in_EAX + 0x44dec) = *(undefined2 *)(in_EAX + 0x44fec);
    puVar2 = (undefined4 *)(in_EAX + (param_1 * 3 + 0xf) * 8);
    puVar1 = (undefined2 *)(in_EAX + 0x44dec);
    *(byte *)(in_EAX + 0x44df2) = bVar4;
    *(undefined4 *)(in_EAX + 0x44e01) = *puVar2;
    *(undefined4 *)(in_EAX + 0x44e05) = puVar2[1];
    *(undefined4 *)(in_EAX + 0x44e09) = puVar2[2];
    if ((*(byte *)(in_EAX + 0x44def) & 0x80) != 0) {
      FUN_004e75e0(param_1);
      SetEvent(*(HANDLE *)(in_EAX + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x198));
      return;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x17c));
    if (*(char *)(param_1 + 0x454e4 + in_EAX) == '\0') {
      SendUdpDatagram(*(int *)(in_EAX + 0x18 + param_1 * 4),
                      (int)*(short *)(in_EAX + 0x58 + param_1 * 2),(char *)puVar1,(int)*puVar1,
                      in_EAX);
      if (*(int *)(in_EAX + 0x38 + param_1 * 4) != -1) {
        SendUdpDatagram(*(int *)(in_EAX + 0x38 + param_1 * 4),
                        (int)*(short *)(in_EAX + 0x68 + param_1 * 2),(char *)puVar1,(int)*puVar1,
                        in_EAX);
      }
    }
    else {
      sVar3 = *(short *)(in_EAX + 0x44dee);
      if ((((sVar3 < 0) || (sVar3 == 0x4002)) || (sVar3 == 0x4003)) ||
         (((sVar3 == 0x4004 || (sVar3 == 1)) || (sVar3 == 0x307)))) {
        FUN_004e8040(param_1);
        if (7 < param_1) {
                    /* WARNING: Subroutine does not return */
          FUN_00426460();
        }
        *(uint *)(in_EAX + 0x13c + (param_1 >> 5) * 4) =
             *(uint *)(in_EAX + 0x13c + (param_1 >> 5) * 4) | 1 << (bVar4 & 0x1f);
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x17c));
    *(undefined4 *)(in_EAX + 0x45280) = 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x198));
    return;
  }
LAB_004e717d:
  LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x198));
  return;
}

