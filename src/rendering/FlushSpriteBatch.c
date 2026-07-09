/* FlushSpriteBatch - 0x004f4110 in the original binary.
 *
 * Flushes the accumulated sprite-quad batch: if g_spriteVertexCount != 0, issues one IDirect3DDevice7::DrawPrimitive(D3DPT_TRIANGLELIST, FVF 0x244, g_spriteVertexBuffer, count*3, 1) for every quad queued that frame, then resets the cursor to 0. See ARCHITECTURE.md rendering section. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FlushSpriteBatch(void)

{
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  return;
}

