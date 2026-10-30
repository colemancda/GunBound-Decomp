/* FUN_004ee850 - 0x004ee850 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CloseXFSArchive ARCHIVE RECOVERED (2026-10-30): the FUN_004f0d70 call
 * at 0x4ee98e is preceded by `mov esi,0xea0f50` (0x4ee989) - the sound
 * archive singleton InitDirectSound opens (`esi=0xea0f50` at its
 * OpenXFSArchive call, 0x4ee5ff).  The port called it with no archive.
 * This tree has no object for 0xea0f50: InitDirectSound's port opens
 * the shared bring-up archive g_xfsScratch in its place (see its
 * comment at that call), so this close now passes &g_xfsScratch, the
 * archive the matching open used.
 */
#include "ghidra_types.h"
#include "xfs.h"


void FUN_004ee850(void)

{
  int iVar1;
  void *_Memory;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (g_soundChannelCount != 0) {
    do {
      if (g_soundAvailable != '\0') {
        if (uVar3 != 0xffffffff) {
          (**(code **)(**(int **)((int)g_soundChannels + uVar3 * 4) + 0xc))();
        }
        if (uVar3 == 0) {
          DAT_00793568 = 0;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < g_soundChannelCount);
  }
  if (g_directSound != (int *)0x0) {
    uVar3 = 0;
    if (g_soundChannelCount != 0) {
      do {
        if (g_soundChannels != (void *)0x0) {
          (**(code **)(**(int **)((int)g_soundChannels + uVar3 * 4) + 0xc))();
          iVar1 = *(int *)((int)g_soundChannels + uVar3 * 4);
          *(undefined1 *)(iVar1 + 0x10) = 0;
          SetEvent(*(HANDLE *)(iVar1 + 8));
          if (*(HANDLE *)(iVar1 + 4) != (HANDLE)0x0) {
            WaitForSingleObject(*(HANDLE *)(iVar1 + 4),1000);
          }
          _Memory = *(void **)((int)g_soundChannels + uVar3 * 4);
          if (_Memory != (void *)0x0) {
            FUN_004ef3f0(_Memory);
            _free(_Memory);
          }
        }
        if (g_secondarySoundBuffers != (void *)0x0) {
          piVar2 = *(int **)((int)g_secondarySoundBuffers + uVar3 * 4);
          (**(code **)(*piVar2 + 8))(piVar2);
          *(undefined4 *)((int)g_secondarySoundBuffers + uVar3 * 4) = 0;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < g_soundChannelCount);
    }
    if (g_soundChannels != (void *)0x0) {
      _free(g_soundChannels);
      g_soundChannels = (void *)0x0;
    }
    if (g_secondarySoundBuffers != (void *)0x0) {
      _free(g_secondarySoundBuffers);
      g_secondarySoundBuffers = (void *)0x0;
    }
    if (g_primarySoundBuffer != (int *)0x0) {
      (**(code **)(*g_primarySoundBuffer + 0x48))(g_primarySoundBuffer);
      (**(code **)(*g_primarySoundBuffer + 8))(g_primarySoundBuffer);
      g_primarySoundBuffer = (int *)0x0;
    }
    (**(code **)(*g_directSound + 8))(g_directSound);
    g_directSound = (int *)0x0;
  }
  /* 0x4ee989: ESI = 0xea0f50, the sound archive (g_xfsScratch here) */
  FUN_004f0d70(&g_xfsScratch);
  FreeLibrary(DAT_007935e8);
  return;
}

