/* UpdateDeviceAcquisition - 0x004edce0 in the original binary.
 *
 * PROMOTED (2026-07-14): called twice from WndProc's WM_ACTIVATEAPP handler
 * (orig 0x4100ab/0x4100b5), once per DirectInput device (keyboard 0xe52810,
 * then mouse 0xe53698) - (re)acquires or releases the device's DirectInput
 * object on app activate/deactivate: if the app was PREVIOUSLY active
 * (wasActive != 0, the pre-exchange value of DAT_00e9c348), call the
 * device's vtable slot 0x1c (Unacquire-shaped, no args beyond `this`);
 * otherwise call vtable slot 0x20 (Acquire-shaped) on the device's +4
 * sub-object. Either way the activation byte is stored at the device
 * object's +0x54.
 *
 * DROPPED-ARGUMENT FIX: Ghidra typed this function void() and read both the
 * device object and the flag as unaff_ESI/unaff_BL. Recovered from the two
 * call sites (orig 0x4100a8 `setne bl` off InterlockedExchange's return
 * value; 0x4100ab/0x4100b5 `mov esi,<device addr>`).
 *
 * BRING-UP: both device addresses are literals for the DirectInput device
 * singletons that FUN_004edd70/FUN_004ee270 (their real constructors) skip
 * for bring-up (see those files) - never constructed, so their +4
 * sub-object pointer is unbacked. WndProc.c now passes the same zeroed
 * g_keyboardDeviceTimerBlock/g_mouseDeviceTimerBlock backing GameTick.c
 * already uses for these two devices, so +4 reads a clean NULL and this
 * safely no-ops (skips both vtable calls) instead of dereferencing garbage.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void UpdateDeviceAcquisition(int deviceObj, char wasActive)

{
  int *piVar1;

  piVar1 = *(int **)(deviceObj + 4);
  if (piVar1 != (int *)0x0) {
    if (wasActive != '\0') {
      (**(code **)(*piVar1 + 0x1c))();
      *(char *)(deviceObj + 0x54) = wasActive;
      return;
    }
    (**(code **)(*piVar1 + 0x20))(piVar1);
  }
  *(char *)(deviceObj + 0x54) = wasActive;
  return;
}
