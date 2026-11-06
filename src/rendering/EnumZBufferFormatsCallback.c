/* EnumZBufferFormatsCallback - 0x004ef970 in the original binary.
 *
 * The IDirect3D7::EnumZBufferFormats callback passed by SetupZBuffer: it
 * copies the enumerated DDPIXELFORMAT (32 bytes) into the caller's context
 * when the Z-buffer bit depths (offset +0xc) match, then returns
 * D3DENUMRET_CANCEL (0) to stop the enum; otherwise D3DENUMRET_OK (1) to
 * continue. DirectDraw enum callbacks are __stdcall (the original ends in
 * `ret 8`); WITHOUT it the port defaults to __cdecl and wine's ddraw - which
 * invokes the callback as __stdcall - leaks 8 bytes of args on every call,
 * drifting ESP until the stack corrupts and control returns into garbage
 * (observed as a page fault at EIP=0x000000dd during SetupZBuffer). The
 * __stdcall decorates it _EnumZBufferFormatsCallback@8, matching functions.h.
 *
 * NAMED (batch 36).
 *
 * Evidence is the sole caller. SetupZBuffer passes this as the callback of
 * the vtable slot 6 (+0x18) call on g_pDirect3D7 - EnumZBufferFormats -
 * with a zeroed DDPIXELFORMAT whose +0xc it pre-sets to the wanted depth,
 * then tests the context's dwSize to see whether a format was copied in.
 * The name matches the sibling EnumTextureFormatsCallback.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 __stdcall EnumZBufferFormatsCallback(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (param_2[3] == param_1[3]) {
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    return 0;
  }
  return 1;
}

