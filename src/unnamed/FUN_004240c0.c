/* FUN_004240c0 - 0x004240c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-07-29): the stale `OpenXFSEntryStream(0)` (see
 * functions.h's "K&R-empty deliberately" note) resolves via objdump
 * (0x42419f-0x4241b7), the same shape as FUN_00423e20.c: `mov
 * edi,[esp+0x114]` (= this function's own param_1) / `add edi,0xf6e8`
 * (archive = param_1 + 0xf6e8) / `push 0x0` (insertFlag) / `mov cl,0x1`
 * (findExisting) / `lea eax,[esp+0x94]` (name = the just-built auStack_81
 * string) / `call 0x4f1390`.
 *
 * DROPPED-REGISTER RECOVERY (2026-08-11): this is the avatar-store
 * part-record loader - it seeks to record #param_4 of the per-gender
 * (param_2) / per-category (param_3) .dat table inside the avatar
 * archive, reads the 0x84-byte on-disk record, and stores its fields
 * into the 11 guarded cells of a 0x17a4-byte output record. Fixed
 * against the original disasm (0x4240c0-0x4243c0):
 *   - `outRecord` is the dropped ESI (Ghidra's `unaff_ESI`; callers do
 *     `lea esi,...` before `call 0x4240c0`) - added as a trailing 5th
 *     parameter, all 12 call sites updated in the same pass.
 *   - ReadXFSEntryByte counts were in EAX and dropped: `mov eax,4` at
 *     0x4241c8 (the record count) and `mov eax,0x84` at 0x424206 (the
 *     whole record).
 *   - The 0x84-byte record read forced the split-struct rule (stack
 *     twin of the LoginSha1 shaCtx coalesce): Ghidra carved the record
 *     into local_104/local_100[23]/local_e9/local_e8..local_c4/
 *     local_c0[63], which MSVC would scatter - coalesced into `rec`
 *     below; the Ghidra local numbers encode the offsets
 *     (offset = 0x104 - local_XXX).
 *   - The seek FUN_004f08a0 at 0x4241f4: `imul edx,edx,0x84` (edx =
 *     partIdx), stream in EAX (`mov eax,ebx` at 0x4241de); the
 *     `push ebp` before the call is a register save (popped 0x4243b5),
 *     not an argument.
 *   - The 11 one-arg EncodeOutgoingPacketField calls each dropped
 *     their cell (EDI): `lea edi,[esi+N]` per site, N = 0/0x23c/0x460/
 *     0x684/0x8a8/0xacc/0xcf0/0xf14/0x1138/0x135c/0x1580 (call addrs
 *     0x42422b/0x42428d/0x4242ab/0x4242c9/0x4242e7/0x424305/0x424323/
 *     0x424341/0x42435f/0x42437d/0x42439b). These are EXACTLY the 11
 *     cells FUN_00425350 (the record's guard-cell ctor - see
 *     src/unnamed/FUN_00425350.c's header) initializes at the same
 *     offsets.
 */
#include "ghidra_types.h"


uint FUN_004240c0(undefined4 param_1,int param_2,int param_3,int param_4,int outRecord)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff80;
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  int local_108;
  /* The 0x84-byte on-disk part record, filled by one
   * ReadXFSEntryByte(...,0x84) - MUST be contiguous (split-struct
   * rule). Field offsets = 0x104 - Ghidra local number; sizeof is
   * 0x84 under MSVC's natural alignment (131 bytes + 1 tail pad). */
  struct {
    int  id;        /* +0x00 local_104 - the guarded part id (cell 0) */
    char name[23];  /* +0x04 local_100 - copied to outRecord+0x224 */
    char flag;      /* +0x1b local_e9  - stored at outRecord+0x23b */
    int  attrs[10]; /* +0x1c local_e8..local_c4 - guard cells 1..10 */
    char desc[63];  /* +0x44 local_c0  - copied to outRecord+0x17a4 */
  } rec;
  undefined1 auStack_81 [2];
  undefined4 uStack_7f;
  
  puVar5 = &uStack_7f;
  for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = 0;
  *(undefined1 *)((int)puVar5 + 2) = 0;
  stack0xffffff80 = CONCAT11((undefined1)uStack_7f,((param_2 == '\0') - 1U & 7) + 0x66);
  switch(param_3) {
  case 0:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_00552c80;
    break;
  case 1:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_005535f0;
    break;
  case 2:
    puVar6 = (undefined2 *)auStack_81;
    do {
      pcVar3 = (char *)((int)puVar6 + 1);
      puVar6 = (undefined2 *)((int)puVar6 + 1);
    } while (*pcVar3 != '\0');
    *puVar6 = DAT_00552c7c;
    break;
  case 3:
    stack0xffffff80 = DAT_00552c78;
    SUBFIELD(uStack_7f,1,undefined1) = DAT_00552c7a;
  }
  puVar5 = (undefined4 *)auStack_81;
  do {
    puVar7 = puVar5;
    puVar5 = (undefined4 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined4 *)((int)puVar7 + 1) = DAT_00552c70;
  *(undefined1 *)((int)puVar7 + 5) = DAT_00552c74;
  iVar4 = OpenXFSEntryStream((int)param_1 + 0xf6e8, (char *)auStack_81, 1, 0);
  uVar2 = 0;
  if (iVar4 != 0) {
    ReadXFSEntryByte(iVar4,&local_108,4);
    if ((int)(uint)param_4 < local_108) {
      FUN_004f08a0(0,(int)(uint)param_4 * 0x84,iVar4);
      ReadXFSEntryByte(iVar4,&rec,0x84);
      CloseSpriteReadState();
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)outRecord,rec.id);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      pcVar3 = rec.name;
      iVar4 = (outRecord + 0x224) - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[iVar4] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (*(char *)(outRecord + 0x236) < '\0') {
        *(undefined1 *)(outRecord + 0x236) = 0;
      }
      *(undefined1 *)(outRecord + 0x237) = 0;
      *(undefined1 *)(outRecord + 0x23b) = rec.flag;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x23c),rec.attrs[0]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x460),rec.attrs[1]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x684),rec.attrs[2]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x8a8),rec.attrs[3]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0xacc),rec.attrs[4]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0xcf0),rec.attrs[5]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0xf14),rec.attrs[6]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x1138),rec.attrs[7]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x135c),rec.attrs[8]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(outRecord + 0x1580),rec.attrs[9]);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      pcVar3 = rec.desc;
      iVar4 = (outRecord + 0x17a4) - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[iVar4] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (*(char *)(outRecord + 0x17cb) < '\0') {
        *(undefined1 *)(outRecord + 0x17cb) = 0;
      }
      *(undefined1 *)(outRecord + 0x17cc) = 0;
      return CONCAT31((int3)((uint)iVar4 >> 8),1);
    }
    uVar2 = CloseSpriteReadState();
  }
  return uVar2 & 0xffffff00;
}

