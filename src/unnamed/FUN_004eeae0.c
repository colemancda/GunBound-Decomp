/* FUN_004eeae0 - 0x004eeae0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eeae0(void)

{
  int unaff_ESI;
  
  if (g_soundAvailable != '\0') {
    if (unaff_ESI != -1) {
      (**(code **)(**(int **)(g_soundChannels + unaff_ESI * 4) + 0xc))();
    }
    if (unaff_ESI == 0) {
      DAT_00793568 = 0;
    }
  }
  return;
}

