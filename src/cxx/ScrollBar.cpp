/* CScrollBar methods - promoted from the raw C ports
 * src/ui_widget/ScrollListWidget_OnMouseDown.c (0x50f500) and
 * ScrollListWidget_OnMouseUp.c (0x50f5f0), plus the thumb-height helper
 * FUN_0050e050. See src/cxx/README.md. */
#include "Widget.h"

/* 0x50e050. Thumb height in pixels: the page's share of the track
 * (pageSize/total), floored at 10 and rounded down to a multiple of 5;
 * a scrollbar with no items fills the whole track. */
int CScrollBar::ThumbHeight()
{
    if (0 < m_total) {
        int h = (m_pageSize * m_height) / m_total;
        int clamped = 10;
        if (9 < h) {
            clamped = h;
        }
        return (clamped / 5) * 5;
    }
    return m_height;
}

/* 0x50f770. Is the point over the thumb: x within the track (inclusive),
 * y within [thumbTop, thumbTop + ThumbHeight()]. */
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
 * OnCommand spine (0x2000). Then the usual child draw broadcast. */
void CScrollBar::Draw()
{
    if (m_pressed != '\0' && 0 < m_total) {
        int heldY = m_lastY;
        if (!IsOverThumb(m_lastX, heldY)) {
            /* held above the thumb: page up (clamped at 0) */
            unsigned int pos = (unsigned int)m_scrollPos;
            if (heldY < m_y + (int)((unsigned int)m_height * pos) / m_total) {
                unsigned int newPos = pos - (unsigned int)m_pageSize;
                if ((int)newPos < 0) {
                    newPos = 0;
                }
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
    if (m_childCount != 0) {
        unsigned int i = 0;
        do {
            ChildAt(this, i)->Draw();
            ++i;
        } while (i < (unsigned int)m_childCount);
    }
}

/* 0x50f500, vtable slot 2. Record the click, then decide between the
 * two press modes: a hit on the thumb itself arms dragging (+grab
 * offset so the thumb doesn't jump under the cursor); any other press
 * inside the widget arms m_pressed (the arrows'/track's auto-repeat
 * path, driven per-tick elsewhere). Finally the usual child broadcast
 * (the up/down arrow CLabels) decides consumption together with the
 * rect test. */
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
    m_unk04 = 0;
    return MouseUpChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}
