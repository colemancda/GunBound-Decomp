/* Darwin only: keep the system from throttling the game.
 *
 * Once the process has a window, macOS treats it as an application and puts it
 * in App Nap while the window is hidden or covered: timers are coalesced and
 * sleeps stretched, and the game, which paces itself with Sleep, falls from 20
 * frames per second to about 2 (its network peers then time out). An activity
 * from NSProcessInfo marked user-initiated and latency-critical prevents that,
 * as a game or a media player does. Called from plain C through the
 * Objective-C runtime, so that the runtime stays C. */
#if defined(__APPLE__)
#include <objc/message.h>
#include <objc/runtime.h>
#include <stdint.h>

#include "rt.h"

/* NSActivityOptions */
#define NS_ACTIVITY_USER_INITIATED 0x00FFFFFFull
#define NS_ACTIVITY_LATENCY_CRITICAL 0xFF00000000ull

void rt_darwin_no_app_nap(void) {
    static id activity;
    if (activity) return;
    Class pi_class = objc_getClass("NSProcessInfo");
    Class str_class = objc_getClass("NSString");
    if (!pi_class || !str_class) return;
    id pi = ((id(*)(Class, SEL))objc_msgSend)(pi_class, sel_registerName("processInfo"));
    id reason = ((id(*)(Class, SEL, const char *))objc_msgSend)(str_class, sel_registerName("stringWithUTF8String:"),
                                                                 "a game paced by its own timers");
    activity = ((id(*)(id, SEL, uint64_t, id))objc_msgSend)(
        pi, sel_registerName("beginActivityWithOptions:reason:"),
        NS_ACTIVITY_USER_INITIATED | NS_ACTIVITY_LATENCY_CRITICAL, reason);
    /* the activity object is kept for the life of the process: ending it would end the exemption */
    if (activity) ((id(*)(id, SEL))objc_msgSend)(activity, sel_registerName("retain"));
}
#endif
