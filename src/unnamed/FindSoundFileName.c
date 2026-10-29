/* FindSoundFileName - 0x004e3740 in the original binary.
 *
 * Looks a key up in the Sound.txt table and returns the sound file name
 * stored under it, or NULL when absent.  StringMap_Find_10 over the
 * map; on a hit the node+4 CStringA is assigned into a local CStringA
 * (FUN_0043ddb0), the local's reference is dropped, and its buffer
 * pointer - still owned by the map's value - is returned.
 *
 * What the table and the result are is settled outside the body:
 * - The table: all three binary call sites (0x4233af in
 *   ApplyBattleActionToContext, 0x4b564a/0x4b5846 in
 *   State11_InBattle_ProcessBattleAction) push 0x794e14 - DAT_00794e14,
 *   the map InitGame hands to LoadSoundConfig, which fills it from the
 *   graphics.xfs entry "Sound.txt" through StringMap_SetAt_CString.
 * - The result: at every site the next instructions are
 *   `mov edi,eax; call 0x4ee9b0` - the return goes straight into
 *   AcquireSoundChannel's EDI, its .xes sound-name argument - with the
 *   `push 0` made before this call left on the stack as
 *   AcquireSoundChannel's flag (this function is ret 4, so it pops only
 *   the map).
 *
 * RETURN FIXED (2026-10-29), with the rename: on a hit the port released
 * and returned the NIL buffer it had constructed the local from, so every
 * lookup came back as the empty string.  The original reloads the local
 * after the assignment - `mov esi,[esp+8]` at 0x4e37a6, release
 * `[esi-0x10]`, `mov eax,esi` at 0x4e37c5 - i.e. it releases and returns
 * the ASSIGNED buffer.  The three call sites, which discarded the result
 * and passed AcquireSoundChannel a stray 0 as its name, are fixed with it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_00426780 below is now StringMap_Find_10.)
 *
 * PROMOTED (2026-09-01): was `(void)` but the original is `ret 4` with one
 * stack param (the hash table - EAX=[esp+0x2c]=entry+4 at 0x4e3784 feeds
 * FUN_00426780's table register) plus EBX live-in (the key string, likewise
 * fed straight through). The interior FUN_00426780 call gains both as its
 * promoted trailing args.
 */
#include "ghidra_types.h"


undefined4 * FindSoundFileName(int *param_1,uchar *regEbx)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000004;
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_14 [4];
  undefined1 auStack_10 [4];
  undefined4 uStack_c;
  int local_18;                      /* a CString: the operator= destination, see below */
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00537b38;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  puVar2 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
  /* orig 0x4e3769 `mov [esp+4],esi`, esi = GetNilString() + 0x10: the local
   * CString constructed to the nil buffer before FUN_0043ddb0 assigns into
   * it.  The store was folded away by Ghidra - same as GetLocalizedString. */
  local_18 = (int)(puVar2 + 4);
  uStack_4 = 0;
  iVar3 = StringMap_Find_10(auStack_10,auStack_14,&stack0x00000004,param_1,regEbx);
  if (iVar3 != 0) {
    FUN_0043ddb0((int *)(iVar3 + 4),&local_18);
    /* 0x4e37a6 `mov esi,[esp+8]`: from here on the local is the ASSIGNED
     * value, not the nil it was built from - release and return that. */
    puVar2 = (undefined4 *)(local_18 - 0x10);
    uStack_4 = 0xffffffff;
    piVar1 = puVar2 + 3;
    LOCK();
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 == 1 || iVar3 + -1 < 0) {
      (**(code **)(*(int *)*puVar2 + 4))(puVar2);
    }
    *unaff_FS_OFFSET = uStack_c;
    return puVar2 + 4;
  }
  uStack_4 = 0xffffffff;
  piVar1 = puVar2 + 3;
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 == 1 || iVar3 + -1 < 0) {
    (**(code **)(*(int *)*puVar2 + 4))(puVar2);
  }
  *unaff_FS_OFFSET = uStack_c;
  return (undefined4 *)0x0;
}

