/* WorldListPanel_Draw - 0x0050dc40 in the original binary.
 *
 * The WORLD LIST panel's own draw method: was previously untracked in
 * PROGRESS.csv (a real, already-analyzed Ghidra function that the CSV
 * export/sync process had missed - added back this pass). Checks the
 * hidden flag (this+0x1e), draws its own background/children via
 * Widget_DrawSelf (0x5054b0), then loops the server count
 * (g_clientContext+0x3f808) calling RenderWorldListRow (0x50dc80) once per
 * server.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall WorldListPanel_Draw(void *this)

{
  int count;
  int i;

  if (*(char *)((int)this + 0x1e) == '\0') {
    Widget_DrawSelf();
    count = *(unsigned char *)(g_clientContext + 0x3f808);
    for (i = 0; i < count; i++) {
      RenderWorldListRow(i);
    }
  }
  return;
}
