/* TickButtonAnimation - 0x00405e90 in the original binary.
 *
 * ButtonWidget vtable slot 2 (animation tick). Thin wrapper forwarding to
 * AdvanceSpriteAnimation, the generic per-object sprite-animation ticker
 * shared across the engine. Was previously untracked in PROGRESS.csv (a
 * real, already-analyzed Ghidra function the CSV export/sync process had
 * missed - added back this pass, same as WorldListPanel_Draw earlier).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"

void TickButtonAnimation(void)

{
  AdvanceSpriteAnimation();
  return;
}
