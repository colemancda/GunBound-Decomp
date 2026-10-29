/* StringMap_SetAt_CString - 0x00426620 in the original binary.
 *
 * ATL7 CAtlMap::SetAt for the CStringA->CStringA instantiation whose
 * find/insert halves are StringMap_Find_10 (0x426780) and
 * StringMap_Insert_CString (0x426960): look the key up and, on a miss,
 * (init the hash table through HashMap_InitHashTable if still empty,
 * then) insert a fresh node; either way assign the value string into
 * node+4 through AssignStringBuffer.  ECX is the key, the stack carries
 * the map and the value.  Member-for-member the shape of the named
 * StringMap_SetAt_1c (0x4fe490) and StringMap_SetAt_28 (0x503e30), and
 * it carries atlcoll.h's own exception guard around the value store:
 * the unwind path at 0x4266ae runs 0x426730 on the new node and
 * rethrows through 0x528798 - SetAt's
 * `_ATLTRY { m_value = value } _ATLCATCHALL() { RemoveAtPos; RETHROW }`.
 *
 * _CString for the value type, on the StringMap_Insert_CString argument
 * (that file's header): the stride alone cannot separate this
 * instantiation from the CStringA->POD ChooseEvent table's, whose
 * SetAt-shaped store is ParseChooseEventLine (0x409cb0).
 *
 * Its maps are exactly the CString-valued ones: the nickname<->user-id
 * caches at ctx+0x6aa41c/+0x6aa44c (ProcessUserLookupResponse,
 * CacheNicknameUserIdPair, DispatchDirectLinkMessengerPacket,
 * ApplyBattleActionToContext) and the Sound.txt table DAT_00794e14
 * (LoadSoundConfig).  13 binary call sites.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (In the note below, FUN_00426780 is now StringMap_Find_10 and
 * FUN_00426960 is StringMap_Insert_CString.)
 *
 * FIXED (2026-09-01): interior call sites recovered their register args -
 * FUN_00426780 gains the promoted table/key trailing args (0x426652 mov
 * eax,esi=param_2; 0x426648 mov ebx,ecx=param_1), and FUN_00426960 was one
 * slot left of its 4-param list (0x42667e ECX=[ebp-0x18]=local_1c bucket
 * index that FUN_00426780 wrote).
 */
#include "ghidra_types.h"


int __thiscall StringMap_SetAt_CString(undefined4 param_1,int *param_2,char *param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffffd4;
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_20 [4];
  int local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537a80;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = &stack0xffffffd4;
  iVar2 = StringMap_Find_10(&local_1c,&local_18,local_20,param_2,(uchar *)param_1);
  if (iVar2 == 0) {
    if ((*param_2 == 0) && (cVar1 = HashMap_InitHashTable(param_2,param_2[2],1), cVar1 == '\0')) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    iVar2 = StringMap_Insert_CString(local_1c,param_2,param_1,local_18);
    local_8 = 0;
    iVar4 = iVar2 + 4;
    pcVar3 = param_3;
    local_1c = iVar2;
    if (param_3 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
  }
  else {
    iVar4 = iVar2 + 4;
    pcVar3 = param_3;
    if (param_3 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
  }
  AssignStringBuffer(iVar4,param_3);
  *unaff_FS_OFFSET = local_10;
  return iVar2;
}

