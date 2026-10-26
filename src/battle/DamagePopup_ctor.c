/* DamagePopup_ctor - 0x00468620 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26). SpawnDamagePopup's own header already identifies
 * this address as "the class-id-0x30d54 constructor": `in_EAX[1] =
 * 0x30d54` below stamps that exact class id into the new object, and
 * `*in_EAX = &PTR_FUN_00555d98` installs the class's vtable - the same
 * 0x555d98 vtable docs/vtable_census.txt lists with slot 0
 * DeletePoisonedBaseObject, slot 1 ResolveNamedState, slot 4 NoOpMethod,
 * and slots 2/3 UNCARVED, matching SpawnDamagePopup's header description
 * of this class's Tick (0x468660) and Draw (0x4686b0) virtuals. Zeroing
 * the rest of the object's fields (hit total, age counters, screen
 * position, etc.) is the standard constructor idiom for this family of
 * new(0x50)-allocated effect classes.
 *
 * Not independently verified beyond this cross-reference and the vtable
 * match (e.g. no separate confirmation that `in_EAX` is really ECX here
 * rather than a genuinely dropped register - SpawnDamagePopup's own call
 * site passes 0 arguments, so that question is unresolved and left to a
 * future dropped-register pass).
 */
#include "ghidra_types.h"


void __fastcall DamagePopup_ctor(undefined4 param_1)

{
  undefined4 *in_EAX;

  in_EAX[2] = param_1;
  in_EAX[1] = 0x30d54;
  in_EAX[3] = 0;
  in_EAX[4] = 0;
  *(undefined1 *)(in_EAX + 5) = 0;
  *(undefined1 *)((int)in_EAX + 0x15) = 0;
  in_EAX[6] = 0xffffffff;
  in_EAX[7] = 0;
  *(undefined1 *)(in_EAX + 8) = 0;
  in_EAX[10] = 0;
  in_EAX[0xb] = 0;
  in_EAX[9] = 0xffffffff;
  *in_EAX = &PTR_FUN_00555d98;
  in_EAX[0x10] = 0;
  in_EAX[0x13] = 0;
  in_EAX[0x11] = 0;
  return;
}
