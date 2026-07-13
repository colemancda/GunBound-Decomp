/* AdvanceSpriteAnimation - 0x00450730 in the original binary.
 *
 * Generic per-tick keyframe-animation advance for a sprite-animation-player
 * object. Ghidra shows the object pointer as a read of unaff/in_EAX with no
 * parameter - a dropped register argument. Every call site loads the object
 * pointer into EAX immediately before `call 0x450730` with no intervening
 * push (e.g. SimulateMobileFrame.c's `mov eax,ebp` / `call 0x450730` at
 * orig 0x461cf0-0x461cf2 and 0x461e47-0x461e49; GameTick.c's
 * `mov eax,0x7a7644` / `call 0x450730` at orig 0x413354-0x413359 for the
 * cursor singleton; TickButtonAnimation.c's `mov eax,ecx` / `jmp 0x450730`
 * at orig 0x405e90). Promoted to an explicit parameter; all ~19 call sites
 * across src/ updated to pass their own object pointer explicitly.
 *
 * Fields: +0x1c = anim descriptor (tables at +8 loop-flag, +0xc step-count,
 * +0x10 step->frame, +0x14 step-duration), +0x20 enabled, +0x24 current
 * animation/state, +0x28 sub-timer, +0x2c current step, +0x30 the resolved
 * sprite frame to draw. Each tick it ticks the sub-timer, advances the step
 * when the step's duration elapses, loops at the end, and writes
 * step->frame into +0x30. **This is the routine that animates the
 * software cursor** (the cursor object is the singleton at 0x7a7644, whose
 * +0x30 is g_cursorFrame) - see ARCHITECTURE.md "custom cursor".
 * Confirmed against a live-client debugger probe (g_cursorFrame cycles
 * 0..16 in lockstep with the per-frame call). Raw/near-verbatim Ghidra port.
 */
#include "ghidra_types.h"


void AdvanceSpriteAnimation(int animObj)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int in_EAX = animObj;
  int iVar4;

  if (((*(char *)(in_EAX + 0x20) != '\0') &&
      (piVar2 = *(int **)(in_EAX + 0x1c), piVar2 != (int *)0x0)) &&
     (iVar3 = *(int *)(in_EAX + 0x24), -1 < iVar3)) {
    if (*piVar2 == 0) {
      *(undefined4 *)(in_EAX + 0x2c) = 0;
      *(undefined4 *)(in_EAX + 0x28) = 0;
      *(undefined4 *)(in_EAX + 0x30) = 0;
      *(undefined1 *)(in_EAX + 0x34) = 1;
      return;
    }
    iVar4 = *(int *)(in_EAX + 0x28) + 1;
    *(int *)(in_EAX + 0x28) = iVar4;
    if (*(int *)(*(int *)(piVar2[5] + iVar3 * 4) + *(int *)(in_EAX + 0x2c) * 4) <= iVar4) {
      *(undefined4 *)(in_EAX + 0x28) = 0;
      *(int *)(in_EAX + 0x2c) = *(int *)(in_EAX + 0x2c) + 1;
    }
    iVar4 = *(int *)(piVar2[3] + iVar3 * 4);
    if (iVar4 <= *(int *)(in_EAX + 0x2c)) {
      cVar1 = *(char *)(iVar3 + piVar2[2]);
      *(undefined4 *)(in_EAX + 0x28) = 0;
      if (cVar1 != '\0') {
        *(undefined4 *)(in_EAX + 0x2c) = 0;
        *(undefined4 *)(in_EAX + 0x30) = **(undefined4 **)(piVar2[4] + iVar3 * 4);
        return;
      }
      *(int *)(in_EAX + 0x2c) = iVar4 + -1;
      *(undefined1 *)(in_EAX + 0x34) = 1;
    }
    *(undefined4 *)(in_EAX + 0x30) =
         *(undefined4 *)(*(int *)(piVar2[4] + iVar3 * 4) + *(int *)(in_EAX + 0x2c) * 4);
  }
  return;
}

