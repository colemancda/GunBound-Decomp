/* FUN_004f2a10 - 0x004f2a10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f2a10(void)

{
  int iVar1;
  int unaff_ESI;
  
  if (*(void **)(unaff_ESI + 0x1c8) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1c8));
  }
  *(undefined4 *)(unaff_ESI + 0x1c8) = 0;
  if (*(void **)(unaff_ESI + 0x1cc) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1cc));
  }
  *(undefined4 *)(unaff_ESI + 0x1cc) = 0;
  if (*(void **)(unaff_ESI + 0x1d0) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1d0));
  }
  *(undefined4 *)(unaff_ESI + 0x1d0) = 0;
  if (*(void **)(unaff_ESI + 0x1d4) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1d4));
  }
  *(undefined4 *)(unaff_ESI + 0x1d4) = 0;
  if (*(void **)(unaff_ESI + 0x1d8) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1d8));
  }
  *(undefined4 *)(unaff_ESI + 0x1d8) = 0;
  if (*(void **)(unaff_ESI + 0x1dc) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1dc));
  }
  *(undefined4 *)(unaff_ESI + 0x1dc) = 0;
  if (*(void **)(unaff_ESI + 0x1e0) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1e0));
  }
  *(undefined4 *)(unaff_ESI + 0x1e0) = 0;
  if (*(void **)(unaff_ESI + 0x1e4) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1e4));
  }
  *(undefined4 *)(unaff_ESI + 0x1e4) = 0;
  if (*(void **)(unaff_ESI + 0x1e8) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1e8));
  }
  *(undefined4 *)(unaff_ESI + 0x1e8) = 0;
  if (*(void **)(unaff_ESI + 0x1ec) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1ec));
  }
  *(undefined4 *)(unaff_ESI + 0x1ec) = 0;
  if (*(void **)(unaff_ESI + 0x1f0) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1f0));
  }
  *(undefined4 *)(unaff_ESI + 0x1f0) = 0;
  if (*(void **)(unaff_ESI + 500) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 500));
  }
  *(undefined4 *)(unaff_ESI + 500) = 0;
  if (*(void **)(unaff_ESI + 0x1fc) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1fc));
  }
  *(undefined4 *)(unaff_ESI + 0x1fc) = 0;
  if (*(void **)(unaff_ESI + 0x200) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x200));
  }
  *(undefined4 *)(unaff_ESI + 0x200) = 0;
  if (*(void **)(unaff_ESI + 0x204) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x204));
  }
  *(undefined4 *)(unaff_ESI + 0x204) = 0;
  if (*(void **)(unaff_ESI + 0x208) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x208));
  }
  *(undefined4 *)(unaff_ESI + 0x208) = 0;
  if (*(void **)(unaff_ESI + 0x20c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x20c));
  }
  *(undefined4 *)(unaff_ESI + 0x20c) = 0;
  if (*(void **)(unaff_ESI + 0x218) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x218));
  }
  *(undefined4 *)(unaff_ESI + 0x218) = 0;
  if (*(int *)(unaff_ESI + 0x21c) != 0) {
    if (0 < *(int *)(unaff_ESI + 0x214)) {
      iVar1 = 0;
      do {
        _free(*(void **)(*(int *)(unaff_ESI + 0x21c) + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)(unaff_ESI + 0x214));
    }
    _free(*(void **)(unaff_ESI + 0x21c));
  }
  *(undefined4 *)(unaff_ESI + 0x21c) = 0;
  if (*(void **)(unaff_ESI + 0x254) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x254));
  }
  if (*(void **)(unaff_ESI + 0x224) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x224));
  }
  *(undefined4 *)(unaff_ESI + 0x224) = 0;
  if (*(void **)(unaff_ESI + 0x228) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x228));
  }
  *(undefined4 *)(unaff_ESI + 0x228) = 0;
  if (*(void **)(unaff_ESI + 0x22c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x22c));
  }
  *(undefined4 *)(unaff_ESI + 0x22c) = 0;
  if (*(void **)(unaff_ESI + 0x230) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x230));
  }
  *(undefined4 *)(unaff_ESI + 0x230) = 0;
  if (*(void **)(unaff_ESI + 0x234) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x234));
  }
  *(undefined4 *)(unaff_ESI + 0x234) = 0;
  if (*(void **)(unaff_ESI + 0x238) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x238));
  }
  *(undefined4 *)(unaff_ESI + 0x238) = 0;
  if (*(void **)(unaff_ESI + 0x23c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x23c));
  }
  *(undefined4 *)(unaff_ESI + 0x23c) = 0;
  if (*(void **)(unaff_ESI + 0x240) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x240));
  }
  *(undefined4 *)(unaff_ESI + 0x240) = 0;
  if (*(void **)(unaff_ESI + 0x244) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x244));
  }
  *(undefined4 *)(unaff_ESI + 0x244) = 0;
  return;
}

