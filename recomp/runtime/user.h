/* user32 services used by other parts of the runtime. */
#ifndef RECOMP_USER_H
#define RECOMP_USER_H

#include <stdint.h>

/* Post a message to a window's queue from any host thread. Returns 0 if the window is gone. */
int rt_post_message(uint32_t hwnd, uint32_t msg, uint32_t wparam, uint32_t lparam);
/* The game's main window (0 before it is shown). */
uint32_t rt_main_window(void);

#endif
