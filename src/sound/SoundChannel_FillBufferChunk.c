/* SoundChannel_FillBufferChunk - 0x004ef610 in the original binary.
 *
 * NAMED (batch 41), LIKELY. Slot 4 (+0x10) of vtable 0x5574e8, the
 * secondary sound channel's (find_vtable_refs: 0x4ef610 at .data
 * 0x5574f8), refilling one half of the channel's streaming DirectSound
 * buffer from its open XFS entry stream.
 *
 * Evidence outside the body: PollSoundBufferPosition (0x4ef450, slot 1)
 * reads the play cursor with IDirectSoundBuffer::GetCurrentPosition and,
 * when it crosses into the other half (compares against m_half * chunk
 * size, DAT_00588f44), calls `call [vtbl+0x10]` with m_half (+0x40) and
 * then flips m_half; slot 2 (the start, 0x4ef4c0) calls it with 1 for the
 * first fill and stores its byte third argument at +0x3c. So the stack
 * argument is the half selector (0 refills the second half, nonzero the
 * first, Lock offset = (arg != 0) - 1 & chunkSize), NOT a looping flag;
 * the looping flag is +0x3c.
 *
 * What it does: under the lock at +0x20 it Locks that half (IDirectSoundBuffer
 * vtable +0x2c, DAT_00588f44 bytes), pulls PCM into it with
 * ReadXFSEntryByte, and Unlocks (+0x4c). If the stream ran short it
 * either rewinds with RewindXFSEntryStream and keeps reading (+0x3c set)
 * or pads the rest with silence (0x80 bytes for 8-bit, else 0) and, once
 * the padding has been written, calls StopSoundChannel on the channel.
 * Whether "FillBufferChunk" is the original's own word is unknown.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __thiscall SoundChannel_FillBufferChunk(int param_1,int param_2)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  char acHeaderSkip [16];   /* orig 0x4ef6ef: lea eax,[esp+0x28] with EAX=0x10 bytes - the stream-header re-read target */
  LPCRITICAL_SECTION lpCriticalSection;
  LONG *pLVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  LONG LVar6;
  uint uVar7;
  undefined4 unaff_EDI;
  uint uVar8;
  undefined4 *puVar9;
  LONG *pLVar10;
  char cStack_45;
  undefined1 local_24 [4];
  LPCRITICAL_SECTION local_20;
  undefined1 local_1c [4];
  _RTL_CRITICAL_SECTION local_18;
  
  if ((*(int *)(param_1 + 0x14) != 0) && (*(char *)(param_1 + 0x4c) != '\0')) {
    lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x20);
    EnterCriticalSection(lpCriticalSection);
    if (g_soundChannelCount < *(uint *)(param_1 + 0x38)) {
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    piVar2 = *(int **)(g_secondarySoundBuffers + *(uint *)(param_1 + 0x38) * 4);
    pLVar1 = &local_18.LockCount;
    cStack_45 = (char)((uint)local_24 >> 0x18);
    local_20 = lpCriticalSection;
    iVar3 = (**(code **)(*piVar2 + 0x2c))(piVar2,(param_2 != 0) - 1 & DAT_00588f44,DAT_00588f44);
    if (iVar3 == 0) {
      if (*(int *)(param_1 + 0x14) != 0) {
        uVar4 = ReadXFSEntryByte(*(int *)(param_1 + 0x14),pLVar1,DAT_00588f44);
        uVar8 = DAT_00588f44;
        iVar3 = 0;
        if (uVar4 != DAT_00588f44) {
          if (*(int *)(param_1 + 0x3c) == 0) {
            if (*(int *)(param_1 + 0x48) == 0) {
              uVar7 = DAT_00588f44 - uVar4;
              puVar9 = (undefined4 *)((int)pLVar1 + uVar4);
              uVar8 = uVar7 >> 2;
              if (DAT_00588f38 == 8) {
                uVar5 = 0x80808080;
              }
              else {
                uVar5 = 0;
              }
              for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                *puVar9 = uVar5;
                puVar9 = puVar9 + 1;
              }
              for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(char *)puVar9 = (char)uVar5;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 1;
            }
            else if (*(int *)(param_1 + 0x48) == 1) {
              uVar4 = DAT_00588f44 >> 2;
              pLVar10 = pLVar1;
              if (DAT_00588f38 == 8) {
                LVar6 = -0x7f7f7f80;
              }
              else {
                LVar6 = 0;
              }
              for (; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pLVar10 = LVar6;
                pLVar10 = pLVar10 + 1;
              }
              for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
                *(char *)pLVar10 = (char)LVar6;
                pLVar10 = (LONG *)((int)pLVar10 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 2;
            }
            else {
              cStack_45 = '\x01';
            }
          }
          else {
            do {
              iVar3 = iVar3 + uVar4;
              uVar8 = uVar8 - uVar4;
              RewindXFSEntryStream();
              ReadXFSEntryByte(*(undefined4 *)(param_1 + 0x14),acHeaderSkip,0x10);
              uVar4 = ReadXFSEntryByte(*(undefined4 *)(param_1 + 0x14),(int)pLVar1 + iVar3,uVar8);
            } while (uVar4 != uVar8);
          }
        }
      }
      piVar2 = *(int **)(g_secondarySoundBuffers + *(int *)(param_1 + 0x38) * 4);
      (**(code **)(*piVar2 + 0x4c))(piVar2,pLVar1,unaff_EDI,0,local_1c);
      if (cStack_45 == '\0') {
        LeaveCriticalSection(&local_18);
        return;
      }
    }
    LeaveCriticalSection(&local_18);
    StopSoundChannel(*(int *)(param_1 + 0x38));
  }
  return;
}

