/* TickButtonAnimation - 0x00405e90 in the original binary.
 *
 * ButtonWidget vtable slot 2 (animation tick). Thin wrapper forwarding to
 * AdvanceSpriteAnimation, the generic per-object sprite-animation ticker
 * shared across the engine. Was previously untracked in PROGRESS.csv (a
 * real, already-analyzed Ghidra function the CSV export/sync process had
 * missed - added back this pass, same as WorldListPanel_Draw earlier).
 *
 * Ghidra shows this itself taking no arguments, but orig 0x405e90 is
 * `mov eax,ecx` / `jmp 0x450730` - a fastcall `this` (in ECX) tail-forwarded
 * into AdvanceSpriteAnimation's dropped EAX argument. Promoted to an
 * explicit parameter forwarded through.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"

void __fastcall TickButtonAnimation(int thisPtr)

{
  AdvanceSpriteAnimation(thisPtr);
  return;
}
