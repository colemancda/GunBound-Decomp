/* FindFreeAtlasTileSlot - 0x004f4750 in the original binary.
 *
 * Walks the texture cache's page list (+0x114) matching page tag and
 * format id, scans each page's used-tile flags up to the tile count
 * (+0x10c), returns the first free tile index (or -1) and the owning
 * page via the out-param. NAMED (2026-07-18); called by PreloadTexture.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER FIX (2026-08-06): all THREE of this function's inputs
 * other than the out-param were dropped - it read an uninitialised
 * `in_EAX` (the texture cache), `unaff_ESI` (the page tag) and
 * `unaff_BL` (the format id). With `in_EAX` garbage, the very first
 * statement walked a wild page list and faulted at `[page+4]` - live
 * crash reached the moment State07_AvatarStore_OnEnter's texture
 * preload became reachable (the fault is swallowed by SEH, so it does
 * not kill the process; it aborts the state transition instead, which
 * is why AVATAR silently bounced back to the lobby).
 *
 * All three recovered from the sole call site, PreloadTexture at orig
 * 0x4f4466-0x4f4475:
 *   mov bl, byte ptr [esp+0x13]   ; formatId  = PreloadTexture's local_91
 *   mov esi, dword ptr [esp+0x18] ; pageTag   = PreloadTexture's local_8c
 *   lea eax, [esp+0x14]           ; outPage   = &local_90 (already passed)
 *   mov eax, ebp                  ; cache     = PreloadTexture's param_1
 *   call 0x4f4750
 * `ebp` is param_1 by the prologue (`sub esp,0x94; push ebp;
 * mov ebp,[esp+0x9c]` - i.e. the first stack argument). The [esp]
 * offsets pin the other two exactly: with the out-param at [esp+0x14]
 * == &local_90, the Ghidra local names (which ARE the frame offsets)
 * give local_8c at [esp+0x18] and local_91 at [esp+0x13] - and those
 * are two of the four values ReadXFSEntryByte fills in immediately
 * before the call, which is what a page tag / format id read out of a
 * texture header should be.
 */
#include "ghidra_types.h"


int FindFreeAtlasTileSlot(undefined4 *param_1,int cache,int pageTag,char formatId)

{
  char *pcVar1;
  int in_EAX = cache;
  int iVar2;
  char unaff_BL = formatId;
  int unaff_ESI = pageTag;

  pcVar1 = *(char **)(in_EAX + 0x114);
  do {
    if (pcVar1 == (char *)0x0) {
      return -1;
    }
    if ((unaff_ESI == *(int *)(pcVar1 + 4)) && (unaff_BL == *pcVar1)) {
      iVar2 = 0;
      if (0 < *(int *)(pcVar1 + 0x10c)) {
        do {
          if (pcVar1[iVar2 + 0xc] == '\0') {
            if (iVar2 != -1) {
              *param_1 = pcVar1;
              return iVar2;
            }
            break;
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(pcVar1 + 0x10c));
      }
    }
    pcVar1 = *(char **)(pcVar1 + 0x114);
  } while( true );
}

