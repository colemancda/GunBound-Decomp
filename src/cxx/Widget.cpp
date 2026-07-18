/* CWidget base methods - promoted from the raw C ports under
 * src/ui_widget/ (Widget_HitTest 0x50e9c0, Widget_DispatchKeyToChildren
 * 0x50ea50, Widget_DispatchMouseToChildren 0x50eab0, Widget_DrawChildren
 * 0x50e520). See src/cxx/README.md.
 *
 * The child list is an embedded ATL7 CAtlArray<CWidget *> (see
 * AtlArray.h for the identification evidence); the bounds guard in
 * every loop below comes from its checked operator[], exactly as the
 * original object code inlines it.
 *
 * EVERY child-broadcast loop below shares one fix that mattered for
 * byte-matching (see Draw's score.sh comment for the full writeup):
 * `unsigned int count = m_children.GetCount(); unsigned int i = 0; if
 * (i < count) { do {...} while (...); }` instead of the more natural
 * `if (m_children.GetCount() != 0) { unsigned int i = 0; do {...} }`.
 * Both are behaviorally identical, but the second form makes MSVC 7.1
 * emit a different early-exit branch (je vs. the original's jbe) and
 * skip the register push for the loop index on the early-exit path -
 * changes that show up as real diff score even though nothing is
 * actually wrong. Applied throughout this file; each method's score.sh
 * result is noted individually below - "105" (or "210" for methods with
 * a second unresolved call target, e.g. a recursive self-call) is the
 * effective ceiling for a fully-matched loop body, since the AtlThrow
 * bounds-guard call target can't resolve against an unlinked .obj (no
 * relinked image exists - see tools/README.md). Confirmed instruction-
 * for-instruction identical past that ceiling for every method below
 * that reports it.
 */
#include "Widget.h"

/* 0x50e9c0, vtable slot 4. Rect test against (+0x28..+0x34), then
 * broadcast to every child's HitTest - a child hit counts even when the
 * point misses this widget's own rect. Hidden (+0x1e) short-circuits.
 * score.sh: 645/5700 (/O2) - the child-walk loop and every branch/vtable-
 * call sequence is byte-identical (confirmed via tools/promote.sh);
 * remaining delta is purely where `hit` lives during the rect-test chain
 * - the original keeps it in CL and only spills to a stack slot once,
 * right before the loop (since CL survives the loop's recursive calls),
 * whereas this compile keeps it on the stack from the start. Tried
 * rewriting the `a && b && c && d` chain as an explicit if/else - MSVC
 * 7.1 produces byte-identical output either way, so this is a genuine
 * register-allocation heuristic difference, not a source-shape issue
 * like the loop-hoist fix elsewhere in this file. Not chased further -
 * everything that matters (every branch, every call, the full loop) is
 * confirmed correct. */
bool CWidget::HitTest(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool hit = m_x < x && x < m_x + m_width &&
               m_y < y && y < m_y + m_height;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->HitTest(x, y)) {
                hit = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return hit;
}

/* 0x50ea50, vtable slot 5. First child that consumes the key wins;
 * the original accumulates into a register and breaks rather than
 * returning from inside the loop.
 * score.sh: 105/4500 - effectively perfect. */
bool CWidget::DispatchKey(int key)
{
    if (m_hidden) {
        return false;
    }
    bool consumed = false;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->DispatchKey(key)) {
                consumed = true;
                break;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return consumed;
}

/* 0x50eab0, vtable slot 6. Same broadcast as DispatchKey over the
 * mouse-message slot; this one does return from inside the loop.
 * score.sh: 105/4000 - effectively perfect. */
bool CWidget::DispatchMouse(int msg)
{
    if (m_hidden) {
        return false;
    }
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->DispatchMouse(msg)) {
                return true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return false;
}

/* 0x50e2f0 - the shared tail of the leaf press handlers (CLabel's
 * OnMouseDown calls it): clear the +0x38 gate and +0x04 active flags,
 * broadcast mouse-UP to the children, and report consumed-or-inside.
 * +0x38 is in the subclass region (CWidget proper ends at +0x38), so
 * the store is by explicit offset until the field's true home class
 * is pinned. */
bool CWidget::ResetPressState(int x, int y)
{
    ((u8 *)this)[0x38] = 0;
    m_focused = 0;
    return MouseUpChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}

/* 0x50e3a0, vtable slot 11 (base drag). While the drag flag is armed,
 * shift by the delta from the last drag point and update it; then the
 * mouse-move child broadcast and the usual consumed-or-inside report.
 * The drag fields (+0x39 flag, +0x3c/+0x40 last point) live in the
 * subclass region - explicit offsets, same caveat as ResetPressState
 * (labels reuse +0x3c as m_spriteId and simply never arm the flag). */
bool CWidget::OnDragMove(int x, int y)
{
    if (((u8 *)this)[0x39] != 0) {
        MoveBy(x - *(int *)((u8 *)this + 0x3c), y - *(int *)((u8 *)this + 0x40));
        *(int *)((u8 *)this + 0x3c) = x;
        *(int *)((u8 *)this + 0x40) = y;
    }
    return MouseMoveChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}

/* 0x50e860 (exported via ghidra_scripts/DecompileAt.java - no raw port
 * existed; the function is only reachable through vtables). The
 * trivial focus setter shared - via identical-code folding - with
 * slot 10.
 * score.sh: 0/300 (/O2) - perfect byte match, the first confirmed in
 * this tree. tools/promote.sh src/cxx/Widget.cpp
 * '?SetFocus@CWidget@@UAEX_N@Z' 50e860 50e868 */
void CWidget::SetFocus(bool active)
{
    m_focused = (u8)active;
}

/* 0x50e730. Shift this widget and, recursively, its whole subtree by a
 * delta - the drag-move workhorse. The recursion is a direct (non-
 * virtual) member call in the original.
 * score.sh: 210/3500 - effectively perfect (two unresolved call targets:
 * the recursive self-call and the AtlThrow guard, both expected). */
void CWidget::MoveBy(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->MoveBy(dx, dy);
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x50e870 / 0x50e8e0 / 0x50e950 - the slot-1/2/3 child broadcasts.
 * All three share the shape: hidden gate, visit EVERY child (no early
 * exit, unlike DispatchKey/DispatchMouse), accumulate any-consumed.
 * score.sh: 105/4400 each (MouseMoveChildren/MouseDownChildren/
 * MouseUpChildren) - effectively perfect. */
bool CWidget::MouseMoveChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->OnMouseMove(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

bool CWidget::MouseDownChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->OnMouseDown(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

bool CWidget::MouseUpChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            if (m_children[i]->OnMouseUp(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

/* 0x50e670. Append a child: grow-or-throw via the CAtlArray (the
 * original open-codes Add's body; E_OUTOFMEMORY on growth failure),
 * shift the child from parent-relative to absolute coordinates, and
 * take ownership of its callback parent pointer. Ghidra shows `this`
 * arriving in EBX.
 * score.sh: 2380/3200 (/O2), the worst match ratio in this file (25.6%)
 * - confirmed NOT chaseable from portable C++: the original really does
 * take `this` in EBX rather than ECX (a non-standard calling convention
 * a normal __thiscall member function can't reproduce without inline
 * asm/`__declspec(naked)`), so the prologue alone guarantees a
 * mismatch. Everything past the prologue (grow-or-throw, MoveBy call,
 * parent pointer store) is logically identical; not worth further
 * byte-chasing given the convention mismatch is structural. */
void CWidget::AddChild(CWidget *child)
{
    m_children.Add(child);
    child->MoveBy(m_x, m_y);
    child->m_parent = this;
}

/* 0x50e7d0. Recursively enable/disable this subtree (+0x1c); disabling
 * also drops the +0x04 active flag.
 * score.sh: 210/3000 - effectively perfect (recursive self-call +
 * AtlThrow guard, both unresolved as expected). */
void CWidget::SetEnabled(bool enabled)
{
    m_enabled = (u8)enabled;
    if (m_focused != 0) {
        m_focused = 0;
    }
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->SetEnabled(enabled);
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x50e620. Index of the child matching (typeId, id); child count when
 * absent. The focus mover calls it with typeId 2 (text-entry) and the
 * id of the child that sent the focus event. */
int CWidget::FindChildIndex(int typeId, int id)
{
    unsigned int count = (unsigned int)m_children.GetCount();
    for (unsigned int i = 0; i < count; ++i) {
        if (m_children[i]->m_typeId == typeId && m_children[i]->m_id == id) {
            return (int)i;
        }
    }
    return (int)count;
}

/* 0x50eb10, vtable slot 7 - the leaf/base OnCommand default: the focus
 * mover plus the upward-forwarding tail of the event spine.
 *   0x1100 focus-next: from the sender (the focused type-2 child), scan
 *          forward; SetFocus(0) the loser, SetFocus(1) the winner; if
 *          focus runs off the end, report 0x1000 through our own
 *          (virtual) OnCommand so panel overrides see it.
 *   0x1101 focus-prev / 0x1102 focus-set: same, scanning backward /
 *          from the current position with wraparound. The target-index
 *          arithmetic mirrors the decompile literally.
 *   anything else: forward to m_parent.
 * score.sh: 13120 -> 8175/17900 (/O2) after switching the dispatch from
 * an if/else-if chain to a real `switch` - the original compiles the
 * evt==0x1100/0x1101/0x1102 check as a dense subl-then-decrement-chain
 * jump sequence, which MSVC 7.1 only emits for an actual switch
 * statement, not sequential if/else-if compares (confirmed: the
 * dispatch prologue is now instruction-for-instruction identical).
 * Remaining delta is register allocation (ebx/ebp for this/count in the
 * original vs. esi/edi here) - a much deeper rabbit hole, not chased
 * further this pass. See tools/promote.sh src/cxx/Widget.cpp
 * '?OnCommand@CWidget@@UAEXHHH@Z' 50eb10 50ece1 */
void CWidget::OnCommand(int evt, int id, int arg)
{
    int count = m_children.GetCount();
    switch (evt) {
    case 0x1100: {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        unsigned int i = cur + 1;
        for (; (int)i < count; ++i) {
            if (m_children[i]->m_typeId == 2 && i != cur) {
                m_children[cur]->SetFocus(false);
                m_children[i]->SetFocus(true);
                return;
            }
        }
        if (i == (unsigned int)count) {
            OnCommand(0x1000, id, 0);
        }
        break;
    }
    case 0x1101: {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        int steps = 0;
        int walk = (int)cur + count;
        if (0 < count) {
            do {
                unsigned int probe = (unsigned int)(walk % count);
                if (m_children[probe]->m_typeId == 2 && probe != cur) {
                    m_children[cur]->SetFocus(false);
                    m_children[(unsigned int)(((int)cur - steps + count) % count)]->SetFocus(true);
                    return;
                }
                ++steps;
                --walk;
            } while (steps < count);
        }
        break;
    }
    case 0x1102: {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        int steps = 0;
        int walk = (int)cur;
        if (0 < count) {
            do {
                unsigned int probe = (unsigned int)(walk % count);
                if (m_children[probe]->m_typeId == 2 && probe != cur) {
                    m_children[cur]->SetFocus(false);
                    m_children[(unsigned int)((steps + (int)probe) % count)]->SetFocus(true);
                    return;
                }
                ++steps;
                ++walk;
            } while (steps < count);
        }
        break;
    }
    default:
        if (m_parent != 0) {
            m_parent->OnCommand(evt, id, arg);
        }
        break;
    }
}

/* 0x50e520, vtable slot 8 (container base). Ghidra typed it __fastcall
 * (this in ECX, no other args) - as a member function the convention is
 * exact. No hidden check in the original: hiding is enforced on the
 * hit-test/input path, not the draw broadcast.
 * score.sh: 105/2200 (/O2), effectively a perfect match - every
 * instruction is byte-identical except the unresolvable AtlThrow call
 * target (expected without a full relinked image, tools/README.md).
 * Getting here required caching GetCount() into a local `count` and
 * initializing the loop index `i` OUTSIDE the `if`, both ahead of the
 * branch - inlining GetCount() into the condition or scoping `i` inside
 * the `if` (the more "natural" C++ phrasing) changes the compiler's
 * early-exit codegen and costs several hundred points. See
 * tools/promote.sh for the verify command. */
void CWidget::Draw()
{
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* Base entries for the per-class slots. Slots 1/2/3 point at the
 * child-broadcast bodies above (0x50e870/0x50e8e0/0x50e950) - concrete
 * classes that take input themselves override the slot and call the
 * broadcast as their shared tail (see ResetPressState). */
bool CWidget::OnMouseMove(int x, int y)
{
    return MouseMoveChildren(x, y);
}

bool CWidget::OnMouseDown(int x, int y)
{
    return MouseDownChildren(x, y);
}

bool CWidget::OnMouseUp(int x, int y)
{
    return MouseUpChildren(x, y);
}

/* Slot 9, the per-class secondary render/refresh hook (panel row-loop
 * 0x50dc40, text-entry TextEntry_SyncFromControl).
 *
 * CORRECTED (2026-07-18): the base entry is NOT a no-op - it is the child
 * Update broadcast at 0x50ecf0 (`if (!hidden) for each child: call
 * child->vtable[+0x24]`), the same shared tail every Update override
 * (CLabel 0x505380, CScrollBar 0x50e090, CWorldListPanel 0x50dc40)
 * jmp's to on exit. With the base modeled as a no-op the Update chain
 * was severed at any widget that didn't override it - concretely the
 * scrollbar (before its own 0x50e090 was recovered) never forwarded
 * Update to its arrow CLabel children, so the arrows never drew. */
void CWidget::Update()
{
    if (m_hidden) {
        return;
    }
    unsigned int count = m_children.GetCount();
    for (unsigned int i = 0; i < count; ++i) {
        m_children[i]->Update();
    }
}

/* Slot 10 - 0x50e860, byte-identical to SetFocus (identical-code
 * folding; see the Widget.h slot-10 note). Kept as a separate method so
 * the vtable keeps its 12 distinct slots. */
void CWidget::v10(bool b)
{
    m_focused = (u8)b;
}

/* ===========================================================================
 * TEMPORARY extern "C" compatibility shims.
 *
 * These exist ONLY so the ~100 raw-C files under src/ that still call these
 * functions by their old FUN_-derived names (Widget_AddChild, etc.) keep
 * linking now that the raw C ports (src/ui_widget/Widget_*.c) have been
 * deleted in favor of the real implementations above. Each shim is NOT
 * expected to byte-match anything in the original binary - it has no
 * counterpart there at all (the original never had "two versions" of a
 * function). The scores that matter are on the CWidget:: methods above.
 *
 * REMOVE these once every caller has been migrated to call the C++ methods
 * directly (or been promoted to C++ itself) - tracked as follow-up work,
 * not done in this pass. See src/cxx/PLAN.md.
 *
 * A few of these (AddChild, FindChildIndex) forward arguments that the
 * ORIGINAL binary passes in registers the raw C decompile never resolved
 * (Ghidra's own `unaff_EBX`/`unaff_EDI`/`unaff_ESI` artifacts - see the
 * deleted raw files' own comments, preserved in git history). Rather than
 * change every existing caller, each shim below captures that same
 * register at function entry via inline asm, exactly replicating what the
 * callers already implicitly relied on - not a new assumption, just made
 * explicit. Verified via disassembly that the capture is the very first
 * instruction, before anything else can clobber the register.
 */
extern "C" {

void Widget_MoveBy(CWidget *this_, int dx, int dy)
{
    this_->MoveBy(dx, dy);
}

void Widget_SetEnabled(CWidget *this_, bool enabled)
{
    this_->SetEnabled(enabled);
}




void Widget_OnCommandDefault(CWidget *this_, int evt, int id, int arg)
{
    this_->OnCommand(evt, id, arg);
}

/* `this` arrives in EBX in the original (Widget_AddChild.c's own
 * `unaff_EBX` - the raw port never had `this` as a real parameter at
 * all). Captured here rather than changed at each of Widget_AddChild's
 * ~19 call sites. */
void Widget_AddChild(CWidget *child)
{
    CWidget *self;
    __asm {
        mov self, ebx
    }
    self->AddChild(child);
}

/* `typeId`/`id` arrive in EDI/ESI in the original (Widget_FindChildIndex.c's
 * own `unaff_EDI`/`unaff_ESI`). Captured here rather than changed at each
 * of its ~13 call sites. */
unsigned int Widget_FindChildIndex(CWidget *this_)
{
    int typeId, id;
    __asm {
        mov typeId, edi
        mov id, esi
    }
    return (unsigned int)this_->FindChildIndex(typeId, id);
}

} // extern "C"
