/* Panel_BaseConstructor - 0x00505760 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13): stripped Windows SEH frame plumbing (direct `FS`
 * segment-register manipulation via `unaff_FS_OFFSET`/`local_c`/
 * `puStack_8`/`local_4`) - same pattern and same fix already applied to
 * `entry/InitGame.c` (see src/README.md's "Raw/verbatim ports" section).
 * The handler this installs (`LAB_005378c8`) is referenced here only as
 * a raw data value, never as real code included in this function's own
 * decompile, so there is no exact handler behavior to preserve; the
 * frame push/pop/restore triple and its scope-tracking local were
 * simply removed, leaving the real constructor logic (the field inits
 * and the `_eh_vector_constructor_iterator_` array-construction call)
 * intact. Confirmed via objdump at 0x505760-0x5057d7: `mov eax,fs:[0]`
 * / `push -1` / `push 0x5378c8` / `push eax` / `mov fs:[0],esp` at
 * entry, mirrored by `mov ecx,[esp+4]` / `mov fs:[0],ecx` at exit -
 * pure frame plumbing, no other use of those stack slots.
 */
#include "ghidra_types.h"


undefined4 * Panel_BaseConstructor(undefined4 *param_1)

{
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  *(undefined1 *)(param_1 + 7) = 1;
  *(undefined1 *)((int)param_1 + 0x1d) = 0;
  *(undefined1 *)((int)param_1 + 0x1e) = 0;
  param_1[8] = 0;
  *(undefined1 *)((int)param_1 + 0x39) = 0;
  *(undefined1 *)(param_1 + 0xe) = 0;
  *(undefined1 *)((int)param_1 + 5) = 1;
  *param_1 = &PTR_LAB_00557bbc;
  _eh_vector_constructor_iterator_(param_1 + 0x14,4,0x10,FUN_00426410,FUN_00405320);
  return param_1;
}

