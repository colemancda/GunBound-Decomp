/* AudioStreamThreadProc - 0x004ef880 in the original binary.
 *
 * The DirectSound streaming worker-thread body: a double-buffered loop that WaitForMultipleObjects on the sound object's 2 position-notification events (100ms timeout), calling the object's refill method (vtable slot 0, given the event index) to decode+fill the just-played buffer half, plus a periodic tick (slot 1); loops while the running flag (obj+0x10) is set. See ARCHITECTURE.md audio section. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void AudioStreamThreadProc(void)

{
  DWORD DVar1;
  int *unaff_ESI;
  
  if ((char)unaff_ESI[4] != '\0') {
    do {
      DVar1 = WaitForMultipleObjects(2,(HANDLE *)(unaff_ESI + 2),0,100);
      if (DVar1 == 0xffffffff) break;
      if (DVar1 != 0) {
        if (DVar1 == 0x102) {
          if ((char)unaff_ESI[4] == '\0') break;
          (**(code **)(*unaff_ESI + 4))();
        }
        else {
          if ((char)unaff_ESI[4] == '\0') break;
          (**(code **)*unaff_ESI)(DVar1);
          (**(code **)(*unaff_ESI + 4))();
        }
      }
    } while ((char)unaff_ESI[4] != '\0');
  }
  __endthread();
  return;
}

