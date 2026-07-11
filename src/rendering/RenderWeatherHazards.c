/* RenderWeatherHazards - 0x004508a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RenderWeatherHazards(int param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  int local_4;
  
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  local_4 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  DAT_00793611 = 1;
  if (local_4 != *(int *)(param_1 + 4)) {
    do {
      uVar2 = *(uint *)(local_4 + 4);
      if (1000 < uVar2) {
        return;
      }
      if (uVar2 < 0x1f6) {
        if (uVar2 == 0x1f5) {
          if (g_currentBlendMode != 1) {
            g_currentBlendMode = 1;
            _DAT_00792194 = 1;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
          }
          pcVar5 = s_FirewallTexture_00555bb0;
          goto LAB_00450ac5;
        }
        if (uVar2 == 100) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_004f01d0();
          iVar4 = FindTextureCacheEntryByName
                            ((uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a1ec8 +
                             g_clientContext);
          if (iVar4 == 0) {
            (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
          }
          else {
            (**(code **)(*g_pD3DDevice7 + 0x8c))
                      (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
          }
        }
        else if (uVar2 == 500) {
          if (g_currentBlendMode != 1) {
            g_currentBlendMode = 1;
            _DAT_00792194 = 1;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
          }
          pcVar5 = s_TornadoTexture_00555bc0;
          goto LAB_00450ac5;
        }
      }
      else {
        if (uVar2 == 0x1f6) {
          if (g_currentBlendMode != 2) {
            g_currentBlendMode = 2;
            _DAT_00792194 = 2;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
          }
          pcVar5 = s_LightningTexture_00555b9c;
        }
        else {
          if (uVar2 != 0x1f7) goto LAB_00450b04;
          if (g_currentBlendMode != 2) {
            g_currentBlendMode = 2;
            _DAT_00792194 = 2;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
          }
          pcVar5 = s_Lightning_00555b90;
        }
LAB_00450ac5:
        iVar4 = FindTextureCacheEntryByName(pcVar5);
        if (iVar4 == 0) {
          (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
        }
        else {
          (**(code **)(*g_pD3DDevice7 + 0x8c))
                    (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
        }
      }
LAB_00450b04:
      piVar3 = *(int **)(local_4 + 0x10);
      cVar1 = *(char *)((int)piVar3 + 0x15);
      while (cVar1 == '\0') {
        (**(code **)(*piVar3 + 0xc))();
        piVar3 = (int *)piVar3[4];
        cVar1 = *(char *)((int)piVar3 + 0x15);
      }
      local_4 = *(int *)(local_4 + 0x1c);
      if (g_spriteVertexCount != 0) {
        g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
        (**(code **)(*g_pD3DDevice7 + 100))
                  (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
        g_spriteVertexCount = 0;
      }
    } while (local_4 != *(int *)(param_1 + 4));
  }
  return;
}

