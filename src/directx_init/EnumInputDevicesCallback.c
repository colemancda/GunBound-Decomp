/* EnumInputDevicesCallback - 0x004edc10 in the original binary.
 *
 * IDirectInput8::EnumDevices callback (LPDIENUMDEVICESCALLBACKA), passed by
 * InitDirectInput (0x4edc9a: push 0x4edc10) as the vtbl+0x10 argument.
 * Disassembly of 0x4edc10..0x4edc49:
 *   eax = [0x793540]; if (eax >= 16) { eax = 0; ret 8 }   (DIENUM_STOP)
 *   esi = [esp+8] (lpddi, the first arg after the return address);
 *   edi = 0x674f70 + eax * 0x244; rep movsd x 0x91 (0x244 bytes = one
 *   DIDEVICEINSTANCEA); [0x793540] = eax + 1; eax = 1; ret 8  (DIENUM_CONTINUE).
 * `ret 8` means __stdcall with two args (lpddi, pvRef; pvRef unused).
 * Records up to 16 enumerated devices into a table at 0x674f70. */
#include "ghidra_types.h"
#include <windows.h>


int __stdcall EnumInputDevicesCallback(const void *lpddi,void *pvRef)

{
  int count;
  unsigned int *dst;
  const unsigned int *src;
  int i;

  count = g_dinputDeviceCount;
  if (count >= 16) {
    return 0;
  }
  dst = (unsigned int *)(g_dinputDeviceInstances + count * 0x244);
  src = (const unsigned int *)lpddi;
  for (i = 0x91; i != 0; i = i - 1) {
    *dst = *src;
    dst = dst + 1;
    src = src + 1;
  }
  g_dinputDeviceCount = count + 1;
  return 1;
}
