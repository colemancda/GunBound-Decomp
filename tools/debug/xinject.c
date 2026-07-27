/* Minimal XTest input injector (stands in for xdotool, which isn't installed).
 * Usage: xinject click <x> <y>      - move pointer to absolute (x,y) and click
 *        xinject key <keysym-hex>   - press+release a key (e.g. ff0d = Return)
 * XTest prototypes are declared here because XTest.h isn't installed. */
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern int XTestFakeMotionEvent(Display*, int, int, int, unsigned long);
extern int XTestFakeButtonEvent(Display*, unsigned int, int, unsigned long);
extern int XTestFakeKeyEvent(Display*, unsigned int, int, unsigned long);
int main(int argc, char **argv)
{
    Display *d = XOpenDisplay(NULL);
    if (!d) { fprintf(stderr, "cannot open display\n"); return 1; }
    if (argc >= 4 && !strcmp(argv[1], "click")) {
        int x = atoi(argv[2]), y = atoi(argv[3]);
        XTestFakeMotionEvent(d, -1, x, y, 0); XFlush(d); usleep(120000);
        XTestFakeButtonEvent(d, 1, 1, 0); XFlush(d); usleep(80000);
        XTestFakeButtonEvent(d, 1, 0, 0); XFlush(d);
        printf("clicked (%d,%d)\n", x, y);
    } else if (argc >= 3 && !strcmp(argv[1], "key")) {
        KeySym ks = (KeySym)strtoul(argv[2], NULL, 16);
        KeyCode kc = XKeysymToKeycode(d, ks);
        if (!kc) { fprintf(stderr, "no keycode for %lx\n", (unsigned long)ks); return 2; }
        XTestFakeKeyEvent(d, kc, 1, 0); XFlush(d); usleep(60000);
        XTestFakeKeyEvent(d, kc, 0, 0); XFlush(d);
        printf("key %lx sent\n", (unsigned long)ks);
    } else { fprintf(stderr, "usage: xinject click X Y | key KEYSYMHEX\n"); return 1; }
    XCloseDisplay(d);
    return 0;
}

/* Build:  gcc -O1 -o xinject xinject.c -lX11 -l:libXtst.so.6
 * Needed because xdotool is not installed on this box and the in-wine
 * injectors (gb_send_mouse/gb_send_key) raise SIGFPE when a second wine
 * process attaches to the Lutris win32 prefix while the game is running.
 * Coordinates are ABSOLUTE screen coords: the 800x600 client area starts at
 * the wine-desktop window origin + (62,97). */
