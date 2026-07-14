/* FUN_004eae60 - 0x004eae60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eae60(void)

{
  /* BRING-UP WORKAROUND: skip this startup data load entirely.
   *
   * OpenXFSEntryStream (called with param_1=0 here) opens an XFS entry via two
   * further-implicit register args (an XFSArchive* in EDI and a name string
   * in EAX) that are themselves inherited from the CALLER's context rather
   * than passed explicitly - Ghidra didn't recover either, and neither is
   * set anywhere in this function or its own callers' C source (InitGame
   * just calls FUN_004eae60() with nothing else established). Recovering
   * the real archive/name would mean tracing register provenance back
   * through multiple call levels without a quick original-binary anchor.
   *
   * This reads DAT_00673628/DAT_005b3628 (purpose unconfirmed - likely
   * non-essential startup config/version data) via OpenXFSEntryStream/
   * ReadXFSEntryByte/FUN_004f1460. Skipping it entirely is safe for
   * bring-up (reaching the logo/menu states); revisit once the archive/name
   * provenance is understood. */
  return;
}

