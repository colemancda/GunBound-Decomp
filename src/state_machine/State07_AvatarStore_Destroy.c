/* State07_AvatarStore_Destroy - 0x00443ed0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00443ed0).  The destructor body
 * behind State07_AvatarStore_Delete (vtable 0x5555f8 slot 0), its only
 * caller, which frees the object right after it returns.  Same shape
 * as the named sibling State09_ReadyRoom_Destroy (0x4d3810): it
 * re-stamps its own class vtable on entry (`mov [esi],0x5555f8` at
 * 0x443ef1, the State07 table), tears the members down in reverse
 * order under the SEH state counter, and finishes by installing the
 * shared null-object base vtable (`mov [esi],0x553fb0` at 0x4440a0),
 * the "poisoned after destroy" idiom ARCHITECTURE.md describes for
 * CGameState_BaseDestructor.  `this` arrives in ECX (`mov esi,ecx` at
 * 0x443eea).
 */
#include "ghidra_types.h"


void __fastcall State07_AvatarStore_Destroy(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053ad09;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &vtable_State07_AvatarStore;
  local_4 = 10;
  FUN_004254a0();
  local_4 = 9;
  if (param_1[0xc971] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xc971],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 8;
  _eh_vector_destructor_iterator_(param_1 + 0xc522,0x224,8,ScrubChecksumGuard);
  local_4 = 7;
  FUN_00443dc0(param_1 + 0xc2ef);
  local_4 = 6;
  if (param_1[0xc26a] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xc26a],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 5;
  if (param_1[0xc1e1] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xc1e1],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 4;
  if (param_1[0xc158] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xc158],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 3;
  _eh_vector_destructor_iterator_(param_1 + 0x36d7,0x17e4,0x15,FUN_004254a0);
  local_4 = 2;
  _eh_vector_destructor_iterator_(param_1 + 0x116,0x17e4,9,FUN_004254a0);
  local_4 = 1;
  if (param_1[0x8f] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x8f],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0;
  if (param_1[6] != 0) {
    ScrambleChecksumGuardBytes(param_1[6],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  *param_1 = &PTR_LAB_00553fb0;
  *unaff_FS_OFFSET = local_c;
  return;
}

