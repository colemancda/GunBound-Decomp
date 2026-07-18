/* gb_send_mouse - inject a WM_MOUSEMOVE into the running GunBound client
 * to test the software cursor's tracking (xdotool/xlib unavailable).
 * Usage: wine gb_send_mouse.exe X Y   (client-relative pixels) */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int x = (argc > 1) ? (int)strtol(argv[1], NULL, 0) : 200;
    int y = (argc > 2) ? (int)strtol(argv[2], NULL, 0) : 200;
    HWND h = FindWindowA("Softnyx", "GunBound");
    if (!h) h = FindWindowA(NULL, "GunBound");
    if (!h) { fprintf(stderr, "GunBound window not found\n"); return 1; }
    {
        LPARAM lp = (LPARAM)((y << 16) | (x & 0xffff));
        PostMessageA(h, WM_MOUSEMOVE, 0, lp);
    }
    printf("sent WM_MOUSEMOVE (%d,%d) to hwnd=%p\n", x, y, (void*)h);
    return 0;
}
