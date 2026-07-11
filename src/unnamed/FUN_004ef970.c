/* FUN_004ef970 - 0x004ef970 in the original binary.
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
 * __stdcall decorates it _FUN_004ef970@8, matching functions.h.
 */
#include "ghidra_types.h"


undefined4 __stdcall FUN_004ef970(undefined4 *param_1,undefined4 *param_2)

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

