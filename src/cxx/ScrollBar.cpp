/* CScrollBar methods - promoted from the raw C ports
 * src/ui_widget/ScrollListWidget_OnMouseDown.c (0x50f500) and
 * ScrollListWidget_OnMouseUp.c (0x50f5f0), plus the thumb-height helper
 * ScrollListWidget_ThumbHeight. See src/cxx/README.md. */
#include "Widget.h"

/* 0x50e050. Thumb height in pixels: the page's share of the track
 * (pageSize/total), floored at 10 and rounded down to a multiple of 5;
 * a scrollbar with no items fills the whole track.
 * score.sh: 645 -> 535/2200. Caching m_height into a local (matching
 * the original's early register load, reused by both branches) and
 * writing the floor check as `h >= 10` instead of `9 < h` (matching the
 * original's `cmpl $0xa` boundary) each helped. The remaining delta is
 * the "this in EAX, not ECX" custom convention noted in Widget.h's
 * class comment above - confirmed via the diff (my version needs an
 * extra register + push/pop to preserve `this` across idivl, which the
 * original doesn't need since it never had to move `this` out of a
 * scratch register in the first place). Same unfixable-from-portable-
 * C++ category as CWidget::AddChild. */
int CScrollBar::ThumbHeight()
{
    int height = m_height;
    if (0 < m_total) {
        int h = (m_pageSize * height) / m_total;
        int clamped = 10;
        if (h >= 10) {
            clamped = h;
        }
        return (clamped / 5) * 5;
    }
    return height;
}

extern CLabel * __stdcall CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h);

/* 0x5080a0 - the scrollbar factory (docs' CreateScrollListWidget).
 * Same guarded-default-ctor + unguarded-pokes split as the other
 * factories, plus construction of the two 18x18 arrow children (id 0
 * up, placed above the track at y -28; id 1 down, below it at h+10;
 * sprites spriteBase*10 + 0x259/0x25a) and a final SetEnabled(total
 * >= 1) so an empty list starts disabled.
 * score.sh: 3900/8400 - the zero-init and vtable install match; the
 * guarded-ctor block has the same field-write-scheduling delta already
 * documented for CreateLabelWidget/CreateTextEntryWidget/
 * CreateButtonWidget (now confirmed across 4 constructors - a compiler-
 * internal heuristic, not chased further here either).
 *
 * NOTE: the original takes spriteBase in EAX and total in EDI (the
 * docs' "item count arrives in a register") - a custom convention not
 * expressible from C++, so they're normal parameters here; exact
 * byte-match is blocked on that, same family as LoadSpriteSet. The
 * first stack argument of the original is never read (id is hardcoded
 * 0); dropped here. */
CScrollBar * __stdcall CreateScrollListWidget(int spriteBase, int total,
                                              int x, int y, int w, int h, int pageSize)
{
    CScrollBar *p = new CScrollBar();
    p->m_y = y;
    p->m_x = x;
    p->m_width = w;
    p->m_id = 0;
    p->m_height = h;
    p->m_unk54 = (spriteBase * 5 + 300) * 2;
    p->AddChild(CreateLabelWidget(0, spriteBase * 10 + 0x259, 0, -0x1c, 0x12, 0x12));
    p->AddChild(CreateLabelWidget(1, spriteBase * 10 + 0x25a, 0, h + 10, 0x12, 0x12));
    p->m_pageSize = pageSize;
    p->m_total = total;
    p->SetEnabled(0 < total);
    return p;
}

/* 0x50f770. Is the point over the thumb: x within the track (inclusive),
 * y within [thumbTop, thumbTop + ThumbHeight()].
 * score.sh: 1350/3200 - confirmed structural, not chased further: the
 * `retl` (no stack cleanup) at every original return proves `y` really
 * does arrive in EBX rather than as a normal stack argument, matching
 * the "custom register use" note on this method's declaration in
 * Widget.h. Same unfixable-from-portable-C++ category as
 * CWidget::AddChild/ThumbHeight above. */
bool CScrollBar::IsOverThumb(int x, int y)
{
    if (m_x <= x && x <= m_x + m_width) {
        int thumbTop = m_y;
        if (0 < m_total) {
            thumbTop = m_y + (m_scrollPos * m_height) / m_total;
        }
        if (thumbTop <= y && y <= thumbTop + ThumbHeight()) {
            return true;
        }
    }
    return false;
}

/* 0x50f660, the draw-path hook (see the slot-binding note in Widget.h).
 * While the track (not the thumb) is held pressed, page-scroll one
 * pageSize per frame toward the held point - the "auto-scroll while
 * held past the ends" behavior - reporting each change up the
 * OnCommand spine (0x2000). Then the usual child draw broadcast.
 * score.sh: 2344 -> 1744/10800 (loop-hoist fix + rewriting the page-up
 * clamp as the branchless `x & ((x < 0) - 1)` bit-trick, matching
 * Ghidra's literal decompile of the same idiom elsewhere in this file -
 * see OnCommand's comment). The page-down clamp has the same shape but
 * wasn't converted - its surrounding branch polarity also differs from
 * the original (jle vs. jge), a deeper mismatch not chased further. */
void CScrollBar::Draw()
{
    if (m_pressed != '\0' && 0 < m_total) {
        int heldY = m_lastY;
        if (!IsOverThumb(m_lastX, heldY)) {
            /* held above the thumb: page up (clamped at 0) */
            unsigned int pos = (unsigned int)m_scrollPos;
            if (heldY < m_y + (int)((unsigned int)m_height * pos) / m_total) {
                unsigned int newPos = pos - (unsigned int)m_pageSize;
                newPos = newPos & (((int)newPos < 0) - 1);
                if (newPos != pos) {
                    m_scrollPos = (int)newPos;
                    if (m_parent != 0) {
                        m_parent->OnCommand(0x2000, m_id, (int)newPos);
                    }
                }
            }
            /* held below the thumb: page down (clamped to total - pageSize) */
            int thumbTop = m_y;
            if (0 < m_total) {
                thumbTop = m_y + (m_height * m_scrollPos) / m_total;
            }
            if (thumbTop + ThumbHeight() < m_lastY) {
                int want = m_pageSize + m_scrollPos;
                int maxPos = m_total - m_pageSize;
                int newPos = want < maxPos ? want : maxPos;
                if (newPos < 0) {
                    newPos = 0;
                }
                if (newPos != m_scrollPos) {
                    m_scrollPos = newPos;
                    if (m_parent != 0) {
                        m_parent->OnCommand(0x2000, m_id, newPos);
                    }
                }
            }
        }
    }
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x50f7c0, vtable slot 7 (exported via DecompileAt - no raw port
 * existed). The arrow stepper: a HELD arrow label re-fires evt 1 every
 * frame from its Draw (gated on the +0x38 armed flag), so this steps
 * the scroll position once per frame while held - the docs' "+/-1
 * arrow steps" auto-repeat. id 0 = up (clamp at 0), id 1 = down
 * (clamp at total - pageSize, floored at 0), any other id resets the
 * position to 1 (CONFIRMED via a fresh Ghidra decompile of 0x50f7c0 -
 * `else { uVar1 = 1; }` literally, not id itself; an earlier reading of
 * the raw asm-differ output looked like it read `id` back off the
 * stack here, but that was a stack-offset misread after the compiler's
 * own reordering - checked against Ghidra before "fixing" it). Changes
 * are reported to the parent as 0x2000.
 * score.sh: 2380 -> 2235/5100 - rewriting the id==0/1 clamps to match
 * Ghidra's literal branchless bit-trick form (`x & ((x < 0) - 1)`
 * instead of an if-branch) helped a little; the bulk of the remaining
 * delta is the id==0 body being laid out as a "cold" tail block after
 * id==1's body (a pure code-layout/branch-ordering choice) plus a few
 * reversed-polarity comparisons (sets vs. setl, jg vs. jl) - not chased
 * further, diminishing returns relative to the other fixes in this
 * file. */
void CScrollBar::OnCommand(int evt, int id, int arg)
{
    if (evt == 1 && 0 < m_total) {
        unsigned int newPos;
        if (id == 0) {
            newPos = (unsigned int)m_scrollPos - 1;
            newPos = newPos & (((int)newPos < 0) - 1);
        } else if (id == 1) {
            unsigned int want = (unsigned int)(m_total - m_pageSize);
            unsigned int cur = (unsigned int)(m_scrollPos + 1);
            newPos = cur;
            if ((int)want <= (int)cur) {
                newPos = want;
            }
            if ((int)newPos < 0) {
                newPos = 0;
            } else if ((int)want <= (int)cur) {
                newPos = want;
            }
        } else {
            newPos = 1;
        }
        if (newPos != (unsigned int)m_scrollPos) {
            m_scrollPos = (int)newPos;
            if (m_parent != 0) {
                m_parent->OnCommand(0x2000, m_id, (int)newPos);
            }
        }
    }
}

/* 0x50f500, vtable slot 2. Record the click, then decide between the
 * two press modes: a hit on the thumb itself arms dragging (+grab
 * offset so the thumb doesn't jump under the cursor); any other press
 * inside the widget arms m_pressed (the arrows'/track's auto-repeat
 * path, driven per-tick elsewhere). Finally the usual child broadcast
 * (the up/down arrow CLabels) decides consumption together with the
 * rect test.
 * score.sh: 1671/9300 - the rect-test chain has the same "hit lives in
 * a register vs. a stack slot" delta already found and left unfixed on
 * CWidget::HitTest, plus some reversed-polarity comparisons in the
 * thumb-hit path. Not chased further - same low-ROI category. */
bool CScrollBar::OnMouseDown(int x, int y)
{
    m_lastX = x;
    m_lastY = y;
    bool inside = !m_hidden &&
                  m_x < x && x < m_x + m_width &&
                  m_y < y && y < m_y + m_height;
    bool grabbedThumb = false;
    if (m_x <= x && x <= m_x + m_width) {
        int thumbTop = m_y;
        if (0 < m_total) {
            thumbTop = m_y + (m_scrollPos * m_height) / m_total;
        }
        if (thumbTop <= y && y <= thumbTop + ThumbHeight()) {
            /* the original recomputes the thumb top here rather than
             * reusing it - kept for byte-match shape */
            int grabBase = m_y;
            if (0 < m_total) {
                grabBase = m_y + (m_scrollPos * m_height) / m_total;
            }
            m_grabOffset = grabBase - y;
            m_dragging = 1;
            m_pressed = 0;
            grabbedThumb = true;
        }
    }
    if (!grabbedThumb) {
        m_pressed = inside;
    }
    return MouseDownChildren(x, y) || inside;
}

/* 0x50f5f0, vtable slot 3. Record the release, disarm both press modes
 * and the base +0x04 active flag, broadcast to the arrow children, and
 * report consumption like the other handlers. */
bool CScrollBar::OnMouseUp(int x, int y)
{
    m_lastX = x;
    m_lastY = y;
    m_pressed = 0;
    m_dragging = 0;
    m_focused = 0;
    return MouseUpChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}

/* TEMPORARY extern "C" compatibility shim - see the note at the bottom of
 * Widget.cpp. `this` arrives in EAX in the original (Widget.h's own note
 * on this method: "Ghidra shows the original receiving this in EAX (in_EAX),
 * not ECX"), captured here rather than changed at
 * ScrollListWidget_DrawThumb.c's call site. REMOVE once that caller is
 * ported to call ThumbHeight() directly. */
extern "C" int ScrollListWidget_ThumbHeight()
{
    CScrollBar *self;
    __asm {
        mov self, eax
    }
    return self->ThumbHeight();
}
