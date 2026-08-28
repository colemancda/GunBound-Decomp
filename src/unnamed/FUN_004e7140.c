/* FUN_004e7140 - 0x004e7140 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CONTEXT PROMOTED TO A REAL PARAMETER (2026-08-27).  in_EAX was previously
 * BOUND to &g_replayContext inside this file, on the evidence that every
 * resolvable call site passed that global.  It is now a parameter, because
 * three sites do not pass a global at all -- they pass their OWN context
 * through (FUN_004e6160, FUN_004e6770 and FUN_004e7de0 each hand on their
 * param_1), and hard-binding the global made those three silently ignore it.
 *
 * Of those three chains only two are statically pinned back to the same
 * global: FUN_004e7de0's only caller, WriteReplayEventRecord, pushes the
 * literal 0xe55ce0 at 0x4119be.  FUN_004e6160's only caller is FUN_004e6770,
 * which has no direct call anywhere in the image -- its single reference is a
 * pointer at .data 0x5572f4, inside a vtable -- so its `this` is not
 * statically knowable.  Threading param_1 through is faithful to the original
 * at those sites whatever the dispatch resolves to, which is exactly why the
 * parameter is better than the binding it replaces.
 *
 * The register is genuine, not a phantom: 0x4e7142 `mov esi,eax` READS EAX,
 * and the first write to EAX anywhere in the function is 0x4e7168 `mov eax,1`.
 * EBX, ECX and EDX are all phantoms (each written before any read).
 *
 * Three of the nine sites were also SHORT, not merely missing the context --
 * they passed nothing at all, so param_1 had to be re-slotted rather than the
 * context appended; appending alone would have put the context into the slot
 * index.  The ninth reference is a tail `jmp 0x4e7140` at 0x4dc561 in
 * BroadcastBattleSnapshot, not a call, which is why callsite_regs.py reports
 * eight where count_call_args.py reports nine.
 */
#include "ghidra_types.h"


void FUN_004e7140(uint param_1,int regEax)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  short sVar3;
  byte bVar4;
  int in_EAX = regEax;
  
  /* orig 0x4e7144 `mov ebx, esi` (ESI = this function's own dropped-EAX
   * context, set at 0x4e7142) - EncryptEventBroadcast's recovered EBX arg. */
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
      FUN_004e75e0((ushort *)puVar1,(int)param_1,in_EAX);
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

