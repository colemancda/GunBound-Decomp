/* LoadButtonDefinitionFromXFS - 0x00401440 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void LoadButtonDefinitionFromXFS(void)

{
  /* BRING-UP WORKAROUND: skip button-definition loading entirely.
   *
   * Two dropped-register issues, neither with a quick fix: OpenXFSEntryStream(0)
   * needs an XFSArchive* and a name string via implicit EDI/EAX registers
   * inherited from the caller's own context (see FUN_004eae60.c for the
   * same situation), and this function's OWN output buffer (unaff_EBX) is
   * ALSO a dropped register never assigned anywhere in the decompiled body -
   * it's used as a 6-int header (count + 5 allocated array pointers) that
   * some caller-side local must have supplied. Recovering either means
   * tracing register provenance through multiple call levels.
   *
   * This loads clickable-button hit-test/icon definitions - not required to
   * reach the logo/menu render loop (which is what bring-up targets); revisit
   * once the archive/name/output-buffer provenance is understood. */
  return;
}

