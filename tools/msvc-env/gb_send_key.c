/* gb_send_key - inject a keystroke into the running GunBound client's
 * message queue via PostMessage, standing in for xdotool (not installed
 * on this box, and no sudo to add it).
 *
 * The client's window is class "Softnyx", title "GunBound" (see
 * src/entry/WinMain.c: RegisterClassA/CreateWindowExA). Its WndProc
 * dispatches WM_KEYDOWN to the current game state's slot-6 handler -
 * for ServerSelect that is State02_ServerSelect_HandleKeyInput, which
 * on VK_RETURN auto-selects the first online server and calls
 * ConnectToSelectedServer. So `gb_send_key` (default VK_RETURN) drives
 * the server-join from the ServerSelect screen without a real key press.
 *
 * Usage:  wine gb_send_key.exe [vk]     (vk hex/dec, default 0x0d = Enter)
 *
 * Build (in the gb-check container):
 *   cl /nologo /Fe:gb_send_key.exe gb_send_key.c user32.lib
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int vk = (argc > 1) ? (int)strtol(argv[1], NULL, 0) : VK_RETURN;
    HWND h = FindWindowA("Softnyx", "GunBound");
    if (h == NULL) {
        h = FindWindowA(NULL, "GunBound");   /* fall back to title-only */
    }
    if (h == NULL) {
        fprintf(stderr, "GunBound window not found\n");
        return 1;
    }
    {
        UINT   sc   = MapVirtualKeyA((UINT)vk, 0);
        LPARAM down = (LPARAM)(1u | (sc << 16));
        LPARAM up   = (LPARAM)(1u | (sc << 16) | (1u << 30) | (1u << 31));
        PostMessageA(h, WM_KEYDOWN, (WPARAM)vk, down);
        Sleep(40);
        PostMessageA(h, WM_KEYUP,   (WPARAM)vk, up);
    }
    printf("sent vk=0x%02x to hwnd=%p\n", vk, (void *)h);
    return 0;
}
