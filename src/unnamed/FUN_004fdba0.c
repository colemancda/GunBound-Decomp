/* FUN_004fdba0 - 0x004fdba0 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x557608 = SLOT 16 (the last) of the CommP2P owner vtable
 * 0x5575c8 (read from the original .data). Extent 0x4fdba0-0x4fdc27 (136
 * bytes; both exits `ret 8`, then int3 padding to 0x4fdc30).
 *
 * __thiscall, two stack words: `mov edi,ecx` (0x4fdbae) = this; `mov
 * al,[esp+8]` (0x4fdba0, before any push) is the SECOND argument, a flag
 * byte; `mov esi,[esp+0x20]` (0x4fdba9, depth 0x1c) is the FIRST, a name
 * pointer. Body: copy up to 16 non-NUL bytes of the name into a key
 * buffer, NUL-terminate it and record its length in the byte after the 17
 * key bytes ([esp+0x1f] = buffer + 0x11, the layout FUN_004fdb40 and
 * StringMap_Find_1c already use), then operate on the string map at
 * this+0x1af0 (`lea eax,[edi+0x1af0]` 0x4fdbd7 / `lea esi,[edi+0x1af0]`
 * 0x4fdc08): flag != 0 -> StringMap_RemoveKey_1c (call 0x4fe500, EDX =
 * key, EAX = map); flag == 0 -> StringMap_SetAt_1c (call 0x4fe490, push 1,
 * EDI = key, ESI = map; the SetAt header already records this as its one
 * binary call site). I.e. a set/clear of a per-name flag. Left unnamed.
 * Erased __thiscall: `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void FUN_004fdba0(int param_1,char *param_2,char param_3)

{
  /* key[0..16] then the length byte at key[17]: one contiguous frame. */
  char key[18];
  uchar i;
  char c;

  i = 0;
  do {
    c = param_2[i];
    if (c == '\0') break;
    key[i] = c;
    i = i + 1;
  } while (i < 0x10);
  key[17] = (char)i;
  key[i] = '\0';
  if (param_3 != '\0') {
    StringMap_RemoveKey_1c(key,(int *)(param_1 + 0x1af0));
    return;
  }
  StringMap_SetAt_1c(1,(undefined4)key,(int *)(param_1 + 0x1af0));
  return;
}
