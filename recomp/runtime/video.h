/* Host video and input: an SDL2 window showing the guest's 800x600 screen, or
 * nothing at all in headless mode. Frames can be dumped as PNG files either way. */
#ifndef RECOMP_VIDEO_H
#define RECOMP_VIDEO_H

#include <stdint.h>

enum {
    RT_EV_NONE = 0,
    RT_EV_MOUSE_MOVE,  /* x, y */
    RT_EV_MOUSE_BUTTON, /* x, y, code = 1 left / 2 middle / 3 right, down, repeat = click count */
    RT_EV_KEY,         /* code = Windows virtual key, scan = set-1 scan code, down, repeat */
    RT_EV_CHAR,        /* code = character (Latin-1) */
    RT_EV_FOCUS,       /* down = gained */
    RT_EV_QUIT
};

typedef struct RtInputEvent {
    int type;
    int x, y;
    int code, scan;
    int down, repeat;
} RtInputEvent;

/* Opens the window on first use (unless headless). The calling thread becomes the
 * video thread: the only one that talks to SDL. */
void rt_video_open(const char *title, int width, int height);
int rt_video_is_open(void);
int rt_video_on_video_thread(void);
/* Next translated input event; 0 when there is none. Video thread only; also
 * shows a frame presented by another thread since the last call. */
int rt_video_poll(RtInputEvent *ev);
/* Show a frame of 16-bit pixels: RGB565, or XRGB1555 when is555 is set. */
void rt_video_present(const void *pixels, int width, int height, int pitch, int is555);
void rt_video_warp_mouse(int x, int y);
void rt_video_show_cursor(int show);
void rt_video_set_title(const char *title);
void rt_video_message_box(const char *caption, const char *text);
unsigned rt_video_frames(void);

/* Input state shared with DirectInput (written by the video thread). */
extern uint8_t rt_vk_state[256];   /* bit 7: down, bit 0: toggled */
extern uint8_t rt_dik_state[256];  /* 0x80: down, indexed by DirectInput key code */
extern uint8_t rt_mouse_buttons;   /* bit 0 left, bit 1 right, bit 2 middle */
extern int rt_mouse_x, rt_mouse_y; /* last position in guest screen coordinates */
void rt_mouse_take_motion(int *dx, int *dy, int *dz); /* relative motion since the last call */

/* Raw input log for DirectInput's buffered data: every reader keeps its own cursor. */
enum { RT_RAW_KEY = 1, RT_RAW_AXIS, RT_RAW_BUTTON };
typedef struct RtRawInput {
    int kind;
    int code;  /* key: DirectInput key code; axis: 0 x, 1 y, 2 wheel; button: 0 left, 1 right, 2 middle */
    int value; /* key/button: 0x80 down, 0 up; axis: relative motion */
    uint32_t time_ms, seq;
} RtRawInput;
unsigned rt_input_position(void);
/* Next event at *cursor; 0 when the reader has caught up. *overflow is set if events were lost. */
int rt_input_read(unsigned *cursor, RtRawInput *out, int *overflow);

int rt_write_png(const char *path, const uint8_t *rgb, int width, int height);

#endif
