/* FUN_00443c20 - 0x00443c20 in the original binary. CState07AvatarStore's
 * constructor - called from InitGame right after the object is allocated,
 * stores its pointer into g_gameStateVTableArray[7].
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-07-29): same bug class already fixed in
 * WidgetChildArray_Destroy.c - Ghidra's `unaff_FS_OFFSET` was an
 * UNINITIALISED pointer that the body wrote through (`*unaff_FS_OFFSET =
 * &local_c;`), faulting on the very first write - immediately after
 * setting the real vtable pointer, so InitGame's caller saw a NULL/never-
 * assigned `g_gameStateVTableArray[7]` and this state's every later vtable
 * dispatch (including OnEnter, the AVATAR button's actual crash) called
 * through whatever garbage was left, not State07_AvatarStore_OnEnter -
 * reproduced live: ChangeGameState's own OnEnter call returned normally
 * (landed on inert garbage) while State07_AvatarStore_OnEnter's own entry
 * probe never fired. The original's `push -1 / push <handler> / mov
 * fs:[0],esp` is a standard MSVC exception frame; per the
 * entry/InitGame.c idiom (and WidgetChildArray_Destroy's), we don't
 * reproduce __try/__except frames for a bring-up port - stripped along
 * with the (write-only, SEH-unwind-only) `local_4` state marker. *
 * FIXED (2026-09-01): recovered the dropped guard-cell arg at the 3
 * argless InitGuardedBool sites (ECX arg; `lea ecx,[esi+OFF]`,
 * esi = param_1, calls 0x443d5e/0x443d69/0x443d74). Byte offsets
 * 0x32c54, 0x32ce0, 0x32e63. The trailing FUN_00425350() also takes
 * ECX (esi+0x32fa0 at 0x443d7f) but is out of this sweep's scope.
 */
#include "ghidra_types.h"


undefined4 * FUN_00443c20(undefined4 *param_1)

{
  *param_1 = &vtable_State07_AvatarStore;
  *(undefined1 *)(param_1 + 0x89) = 0;
  param_1[6] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x443c55
   * (`lea edi,[esi+4]` at 0x443c42, esi = this file's own param_1) the
   * cell is (int)param_1+4; tableHandle(+0x14)=param_1+0x18=param_1[6],
   * activeFlag(+0x220)=param_1 byte 0x224=*(undefined1*)(param_1+0x89) -
   * both match the zero-writes immediately above. `param_1` is
   * `undefined4 *` (scales by 4), so the byte offset is taken via `(int)
   * param_1 + N`. Same evidence pattern for all 6 cells below. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 4, 0);
  *(undefined1 *)(param_1 + 0x112) = 0;
  param_1[0x8f] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443c6f
   * (`lea edi,[esi+0x228]`); tableHandle=param_1[0x8f],
   * activeFlag=*(undefined1*)(param_1+0x112), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x228, 0);
  _eh_vector_constructor_iterator_(param_1 + 0x116,0x17e4,9,FUN_00425350,FUN_004254a0);
  _eh_vector_constructor_iterator_(param_1 + 0x36d7,0x17e4,0x15,FUN_00425350,FUN_004254a0);
  *(undefined1 *)(param_1 + 0xc1db) = 0;
  param_1[0xc158] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443ccd
   * (`lea edi,[esi+0x3054c]`); tableHandle=param_1[0xc158],
   * activeFlag=*(undefined1*)(param_1+0xc1db), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x3054c, 0);
  *(undefined1 *)(param_1 + 0xc264) = 0;
  param_1[0xc1e1] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443ce7
   * (`lea edi,[esi+0x30770]`); tableHandle=param_1[0xc1e1],
   * activeFlag=*(undefined1*)(param_1+0xc264), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x30770, 0);
  *(undefined1 *)(param_1 + 0xc2ed) = 0;
  param_1[0xc26a] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443d01
   * (`lea edi,[esi+0x30994]`); tableHandle=param_1[0xc26a],
   * activeFlag=*(undefined1*)(param_1+0xc2ed), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x30994, 0);
  FUN_0044fb40(param_1 + 0xc2ef);
  _eh_vector_constructor_iterator_(param_1 + 0xc522,0x224,8,InitGuardSlot,ScrubChecksumGuard);
  *(undefined1 *)(param_1 + 0xc9f4) = 0;
  param_1[0xc971] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443d4e
   * (`lea edi,[esi+0x325b0]`); tableHandle=param_1[0xc971],
   * activeFlag=*(undefined1*)(param_1+0xc9f4), matching above. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x325b0, 0);
  InitGuardedBool((byte *)param_1 + 0x32c54);
  InitGuardedBool((byte *)param_1 + 0x32ce0);
  InitGuardedBool((byte *)param_1 + 0x32e63);
  FUN_00425350();
  return param_1;
}

