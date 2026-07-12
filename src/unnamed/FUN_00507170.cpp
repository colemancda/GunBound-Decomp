/* FUN_00507170 - 0x00507170 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Ported to C++ (2026-07-11) to call CWidget::DispatchKey/DispatchMouse
 * directly instead of through the now-removed Widget_DispatchKeyToChildren/
 * Widget_DispatchMouseToChildren shims - see src/cxx/PLAN.md's
 * "deduplicate C++-promoted functions" section.
 */
#include "../cxx/Widget.h"

extern "C" void FUN_00507170(CWidget *this_, int key)

{
  if (this_->m_focused != '\0') {
    this_->DispatchKey(key);
  }
  this_->DispatchMouse(key);
  return;
}
