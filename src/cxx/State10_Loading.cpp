/* CState10Loading - the loading interstitial. Only OnExit is promoted
 * so far (0x43eff0); OnEnter (0x43e840, checksum-state seeding) and
 * PreloadAssets are Phase 3 work - they live deep in g_clientContext.
 * See src/cxx/README.md. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "GameState.h"
#include "ActiveObjects.h"

extern "C" {
extern int g_clientContext;
extern unsigned char DAT_007933b8;      /* "chat entry armed" flag */
extern unsigned int DAT_007934e4;       /* shared overlay EDIT control (+4 = HWND) */
extern unsigned char DAT_00551cb1;      /* the empty string the EDIT is reset to */
extern unsigned char g_localizedStringTable;      /* localized-string table base */
char PeekPacketChecksumBool(void);                /* replay-playback mode check */
void FUN_0040c880(char *out);           /* read the EDIT control's text into out[128] */
char ParseChatSlashCommand(int ctx, char *text); /* slash-command handler (true = consumed) */
char CheckChatWordFilter(char *text);          /* "message too long" check */
char FUN_00415230(void);                /* "not allowed right now" check */
void QueueBroadcastEvent(int type);
void AppendBroadcastString(const char *s);
void BroadcastQueuedEvent(void);
void FUN_00426230(void);                /* playback-mode chat path */
void *GetLocalizedString(void *table, int id);
}

/* 0x43eff0 - destroy the loading screen's three container buckets:
 * 10000 (the screen sprite set every state uses) plus 10001/10002
 * (the preloaded battle asset buckets PreloadAssets fills). */
void CState10Loading::OnExit()
{
    ActiveObjects_DestroyBucket(10000);
    ActiveObjects_DestroyBucket(0x2711);
    ActiveObjects_DestroyBucket(0x2712);
}

/* 0x43e720 (State10_Loading_HandleChatInput), vtable slot 5. On the
 * Enter key (WM_KEYDOWN 0x100, VK_RETURN 0xd), while chat entry is
 * armed and not replaying: read the overlay EDIT's text; if non-empty
 * and not a slash command, either reject it (too long -> localized
 * 0x202, not-allowed -> 0x205, shown via the widget's slot-10 dialog)
 * or record it into the replay stream. Always clears the EDIT box
 * afterward (except the not-armed early-out, a bare return). In
 * replay-playback mode the FUN_00426230 path runs instead. The
 * `this->vtable[0x28]` call is a widget dialog method on the screen's
 * overlaid input object - kept as the raw code* dispatch. */
void CState10Loading::OnKeyInput(int msg, int a, int /*b*/)
{
    char text[128];
    if (msg != 0x100 || a != 0xd) {
        return;
    }
    if (DAT_007933b8 != 1) {
        return;
    }
    if (PeekPacketChecksumBool() == 0) {
        FUN_0040c880(text);
        if (text[0] != '\0' && ParseChatSlashCommand(g_clientContext, text) == 0) {
            int msgId;
            if (CheckChatWordFilter(text) == 1) {
                msgId = 0x202;
            } else if (FUN_00415230() == 0) {
                QueueBroadcastEvent(1);
                AppendBroadcastString(text);
                BroadcastQueuedEvent();
                goto reset;
            } else {
                msgId = 0x205;
            }
            int *self = (int *)this;
            void *localized = GetLocalizedString(&g_localizedStringTable, msgId);
            ((void (__cdecl *)(void *, int, int))*(void **)(*self + 0x28))(localized, 2, 6);
        }
    } else {
        FUN_00426230();
    }
reset:
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4), (LPCSTR)&DAT_00551cb1);
}
