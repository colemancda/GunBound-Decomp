/* LoadButtonDefinitionFromXFS - 0x00401440 in the original binary.
 *
 * RECONSTRUCTED (2026-07-18): was a bring-up stub (`return;`). It loads a
 * button/sprite animation-state definition from the graphics.xfs archive
 * and fills the caller-supplied 6-int descriptor entry that
 * FindPreloadedTextureByName later hands back and that
 * CButtonWidget::SetState (via FindStringNoCase) and AdvanceSpriteAnimation
 * consume. Without it every button's descriptor stayed all-zero
 * (count=0/names=NULL), so SetState("ready"/"active"/"disable") always
 * failed -> the button stayed disabled -> its sprite frame was never set
 * -> nothing drew.
 *
 * TWO DROPPED REGISTER ARGS recovered from the sole caller
 * (AppendPersistentButtonName, orig 0x40179e/0x4017a5, just before
 * `call 0x401440`):
 *   - EBX = the output descriptor entry, `param_1 + *param_1*6 + 0x8001`
 *     (== FindPreloadedTextureByName's return for this index; the
 *     `lea ebx,[ebp+ecx*8+0x20004]` form) -> `entry` here.
 *   - EAX = the assembled "<name>.<ext>" string buffer -> `name` here.
 * The archive is the fixed global &g_graphicsArchive (orig `mov edi,0xf11dd0`;
 * DAT_00f11dd0 was promoted to g_graphicsArchive).
 *
 * DESCRIPTOR LAYOUT (6 ints, per the original's allocations at
 * 0x401468-0x4014a8 and AdvanceSpriteAnimation's reads):
 *   entry[0] = state count
 *   entry[1] = char*[count]  state names (each malloc'd, NUL-terminated)
 *   entry[2] = char [count]  per-state loop flag
 *   entry[3] = int  [count]  per-state step (frame) count
 *   entry[4] = int*[count]   per-state frame table (step_count ints each)
 *   entry[5] = int*[count]   per-state duration table (step_count ints each)
 *
 * The XFS read order per state (0x4014c0-0x4015b4): name length (4B) ->
 * name bytes -> loop flag (1B) -> step count (4B) -> frame table
 * (step_count*4 B) -> duration table (step_count*4 B). ReadXFSEntryByte
 * takes its byte count in the (originally EAX) 3rd argument. Cleanup +
 * archive-cursor fold-back + free is CloseSpriteReadState (which is exactly
 * the original's inline 0x4015ba-0x401603 tail).
 *
 * operator_new here is 0x520228 (the original's raw allocator, no throw).
 */
#include "ghidra_types.h"
#include "xfs.h"


void LoadButtonDefinitionFromXFS(int *entry, char *name)
{
  int stream;
  int stateCount;
  int i;
  int nameLen;
  int stepCount;
  int *names;
  char *loopFlags;
  int *stepCounts;
  int *frameTables;
  int *durTables;

  stream = (int)OpenXFSEntryStream((int)&g_graphicsArchive, name, 1, 0);
  if (stream == 0) {
    return;
  }
  ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)entry, 4);
  stateCount = entry[0];
  names       = (int *)operator_new(stateCount * 4);
  loopFlags   = (char *)operator_new(stateCount);
  stepCounts  = (int *)operator_new(stateCount * 4);
  frameTables = (int *)operator_new(stateCount * 4);
  durTables   = (int *)operator_new(stateCount * 4);
  entry[1] = (int)names;
  entry[2] = (int)loopFlags;
  entry[3] = (int)stepCounts;
  entry[4] = (int)frameTables;
  entry[5] = (int)durTables;
  for (i = 0; i < stateCount; i = i + 1) {
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)&nameLen, 4) == 0xffffffff) break;
    names[i] = (int)operator_new(nameLen + 1);
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)names[i], nameLen) == 0xffffffff) break;
    *(char *)(names[i] + nameLen) = '\0';
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)(loopFlags + i), 1) == 0xffffffff) break;
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)(stepCounts + i), 4) == 0xffffffff) break;
    stepCount = stepCounts[i];
    frameTables[i] = (int)operator_new(stepCount * 4);
    durTables[i]   = (int)operator_new(stepCount * 4);
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)frameTables[i], stepCount * 4) == 0xffffffff) break;
    if (ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)durTables[i], stepCount * 4) == 0xffffffff) break;
  }
  CloseSpriteReadState((void *)stream, (int)&g_graphicsArchive);
}
