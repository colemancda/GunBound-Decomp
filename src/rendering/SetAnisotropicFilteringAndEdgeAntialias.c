/* SetAnisotropicFilteringAndEdgeAntialias - 0x004f0100 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY on the exact noun): the only call is InitGame at
 * 0x40ed0a, made right after the keyboard table setup with `mov al,1`
 * at 0x40ecc5 and nothing writing AL in between, so the flag is 1 at
 * startup. The D3D7 calls decode against IDirect3DDevice7's vtable:
 * +0x50 is SetRenderState (slot 20) and +0x94 is SetTextureStageState
 * (slot 37). Render state 0x28 is D3DRENDERSTATE_EDGEANTIALIAS; texture
 * stage state 0x10 is D3DTSS_MAGFILTER and 0x11 is D3DTSS_MINFILTER. With
 * the flag set it writes EDGEANTIALIAS = 1, MAGFILTER = 5
 * (D3DTFG_ANISOTROPIC) and MINFILTER = 3 (D3DTFN_ANISOTROPIC) on stages 0
 * and 1; cleared, it writes EDGEANTIALIAS = 0 and MAG/MINFILTER = 1
 * (point) on the same stages. The last state is cached in the byte at
 * 0x588f64 and the calls are skipped when the flag is unchanged. So the
 * one flag controls both anisotropic filtering and edge antialiasing,
 * and the name says both.
 *
 * The flag arrives in AL (the original compares it straight against the
 * cache byte); it is a trailing parameter here and InitGame passes 1.
 */
#include "ghidra_types.h"


void SetAnisotropicFilteringAndEdgeAntialias(char in_AL)

{
  if (DAT_00588f64 != in_AL) {
    DAT_00588f64 = in_AL;
    if (in_AL != '\0') {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x28,1);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x10,5);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x11,3);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x10,5);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x11,3);
      return;
    }
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x28,0);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x10,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x11,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x10,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x11,1);
  }
  return;
}

