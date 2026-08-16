/* FUN_0041fd50 - 0x0041fd50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 9 argless PeekPacketChecksumState() calls and the 1-arg
 * EncodeOutgoingPacketField() calls.  param_1 is the CLIENT CONTEXT, not a
 * slot index - confirmed both from the caller (State09_ReadyRoom_Process-
 * Packet passes g_clientContext) and from this function's own prologue
 * (`mov ebp,[esp+0x20]` then `lea edi,[ebp+0x595d8]`, the same +0x595d8
 * arena BeginNewTurn indexes off g_clientContext).  The C then REUSES
 * param_1 as a loop counter (`param_1 = 0;` a few lines in), so the
 * incoming value is captured into the new iCtxBase local first and every
 * cell is spelled against that.  Cells: iCtxBase + 0x4111c / 0x475c8 /
 * 0x5af88 / 0x5b1ac / 0x5b3d0 / 0x5b5f4 / 0xeb854, the 0x224-stride
 * per-slot array + (idx & 7) * 0x224 + 0x595d8, the avatar-part cell
 * (P*0xb + b) * 0x7d28 + local_8 + 0x1a2390 (same arena-index idiom as
 * State09_ReadyRoom_RenderRosterAndItems), and the global 0xe9bed8.
 */
#include "ghidra_types.h"


void FUN_0041fd50(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iCtxBase;
  int local_14;
  int local_c;
  int local_8;
  
  iCtxBase = param_1;
  param_1 = 0;
  local_8 = 0xc;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iCtxBase + (0xc - local_8) * 0x224 + 0x595d8),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  local_c = 0;
  local_8 = 0;
  do {
    local_14 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState((void *)(iCtxBase + 0x475c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)((uVar6 * 0xb + *(byte *)(iCtxBase + 0x475c4)) * 0x7d28 + local_8 + iCtxBase + 0x1a2390));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar1) {
      do {
        if (7 < param_1) goto LAB_0041ff38;
        uVar5 = 0x2000 << ((byte)local_c & 0x1f);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState((void *)(iCtxBase + 0x4111c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        param_1 = param_1 + 1;
        if ((uVar2 & uVar5) == uVar5) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar1 = local_c;
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar1 = -1;
        }
        EncodeOutgoingPacketField((void *)(iCtxBase + (param_1 - 1) * 0x224 + 0x595d8),iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_14 = local_14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState((void *)(iCtxBase + 0x475c8));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)((uVar6 * 0xb + *(byte *)(iCtxBase + 0x475c4)) * 0x7d28 + local_8 + iCtxBase + 0x1a2390));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (local_14 < iVar1);
    }
    if (7 < param_1) break;
    local_8 = local_8 + 0x224;
    local_c = local_c + 1;
  } while (local_8 < 0xefc);
LAB_0041ff38:
  DAT_005b3488 = param_2;
  param_1 = 0x1f;
  do {
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    iVar1 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    uVar5 = iVar1 * 0x343fd + 0x5809315;
    DAT_005b3488 = iVar1 + (uVar5 * 0x61 + 0x61) % 0xf4241;
    if ((uVar2 & 7) != (uVar5 & 7)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState((void *)(iCtxBase + (uVar2 & 7) * 0x224 + 0x595d8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState((void *)(iCtxBase + (uVar5 & 7) * 0x224 + 0x595d8));
      EncodeOutgoingPacketField((void *)(iCtxBase + (uVar2 & 7) * 0x224 + 0x595d8),uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iCtxBase + (uVar5 & 7) * 0x224 + 0x595d8),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(iCtxBase + 0x4111c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar2 & 0x10000) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iCtxBase + 0x5af88),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0;
  }
  else {
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iCtxBase + 0x5af88),uVar2 % 0x1a);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = uVar2 % uVar5;
  }
  EncodeOutgoingPacketField((void *)(iCtxBase + 0x5b1ac),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
  DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(iCtxBase + 0x5b3d0),(uVar2 & 0xf) - 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
  DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(iCtxBase + 0x5b5f4),uVar2 % 0x50 - 0x28);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2 = 0x400;
  do {
    iVar1 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (iVar1 * 0x61 + 0x61U) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iCtxBase + (0x400 - param_2) * 0x224 + 0x62854),iVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(iCtxBase + 0xeb854),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

