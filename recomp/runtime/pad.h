/* Game controller and touch input, turned into the pointer and keyboard input
 * the game understands. The left stick moves the pointer, buttons are keys or
 * mouse buttons; a finger is the pointer with the left button held. */
#ifndef RECOMP_PAD_H
#define RECOMP_PAD_H

#include <stdio.h>

/* The first fifteen are in the order of SDL_GameControllerButton. */
enum {
    RT_PAD_A = 0, RT_PAD_B, RT_PAD_X, RT_PAD_Y, RT_PAD_BACK, RT_PAD_GUIDE, RT_PAD_START,
    RT_PAD_LS, RT_PAD_RS, RT_PAD_LB, RT_PAD_RB,
    RT_PAD_DPUP, RT_PAD_DPDOWN, RT_PAD_DPLEFT, RT_PAD_DPRIGHT,
    RT_PAD_LT, RT_PAD_RT, /* the triggers, as buttons */
    RT_PAD_NBUTTONS
};
enum { RT_TOUCH_DOWN = 0, RT_TOUCH_MOVE, RT_TOUCH_UP };

int rt_pad_button_by_name(const char *name); /* -1 if there is no such button */
int rt_pad_load_config(const char *path);    /* 0 if the file is missing or has errors */
void rt_pad_print_config(FILE *f);           /* the mapping in force, in the configuration's format */
void rt_pad_set_speed(double px_per_second);

/* Video thread only. */
void rt_pad_button(int button, int down);
void rt_pad_trigger(int which, double value);     /* 0 left, 1 right; 0..1 */
void rt_pad_stick(int which, double x, double y); /* 0 left, 1 right; -1..1, y down */
void rt_pad_release_all(void);                    /* the controller went away */
void rt_pad_tick(void);                           /* pointer motion, key repeat, delayed releases */
void rt_touch(int phase, int x, int y);           /* guest screen coordinates */
void rt_touch_right_click(void);                 /* a two-finger tap */

/* The input events video.c accepts from here. */
void rt_in_mouse_move_to(int x, int y);
void rt_in_mouse_move_by(int dx, int dy);
void rt_in_mouse_button(int button, int down, int clicks); /* 1 left, 2 middle, 3 right */
void rt_in_key(int vk, int dik, int down, int repeat);
void rt_in_char(int ch);
void rt_in_quit(void);

#endif
