/* SetEffectsEnabled - 0x004eeb70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence. The flag byte it writes, 0x0079354b, is the sound-effects
 * enable flag: AcquireSoundChannel refuses to hand out a channel when it is
 * clear, InitDirectSound sets it, and the battle mouse handler writes it
 * next to each effects-volume slider click. The music counterpart is
 * 0x0079354a, which the same key handler toggles inline and pairs with a
 * Stop call (vtable slot 3, +0xc) on channel 0; this function is the effects
 * equivalent, stopping channels 1.. through that same slot when the flag is
 * turned off. Both call sites in State11_InBattle_HandleKeyInput (0x4b882b
 * and 0x4b9258) are preceded by the music volume update and followed by
 * SetEffectsVolume, and at both the value in AL comes from the instruction
 * pair cmp [ebp+0x11bc], ebx / setne al with EBX zeroed at function entry
 * (0x4b82bc xor ebx, ebx and never rewritten before the sites). So AL is
 * whether the saved effects option at +0x11bc is non-zero, the same field
 * that then gates SetEffectsVolume.
 *
 * Recovered argument. AL was the unassigned local in_AL; it is promoted to
 * the trailing parameter regAl. The stored flag is regAl AND the sound-
 * available flag.
 */
#include "ghidra_types.h"


void SetEffectsEnabled(char regAl)

{
  uint uVar1;
  
  if ((((g_soundAvailable == '\0') || (DAT_0079354b = 1, regAl == '\0')) &&
      (DAT_0079354b = 0, regAl == '\0')) && (uVar1 = 1, 1 < g_soundChannelCount)) {
    do {
      if (g_soundAvailable != '\0') {
        if (uVar1 != 0xffffffff) {
          (**(code **)(**(int **)(g_soundChannels + uVar1 * 4) + 0xc))();
        }
        if (uVar1 == 0) {
          DAT_00793568 = 0;
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < g_soundChannelCount);
  }
  return;
}

