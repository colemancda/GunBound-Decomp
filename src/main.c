/* Entry point and top-level flow - WinMain (0x40d8e0) in the original
 * binary.
 *
 * Requires Winelib (winegcc) to build, not the native `make` target -
 * this file is real Win32 API surface (registry, window creation,
 * WSAStartup, the message loop), unlike the pure-algorithm modules
 * under src/lzhuf/. See src/README.md for build instructions once
 * Winelib is available.
 *
 * STATUS: skeleton only. The real WinMain does, per ARCHITECTURE.md's
 * "Entry point and top-level flow" section:
 *   1. Registry checks + a single-instance mutex.
 *   2. Window class registration/creation (WndProc, 0x410040).
 *   3. WSAStartup.
 *   4. InitGame(hWnd, hInstance) (0x40eaa0) - sets up DirectDraw/
 *      DirectSound/DirectInput and constructs the 16-slot game-state
 *      object array (g_gameStateVTableArray, base 0x5b33f8).
 *   5. Standard Win32 message loop: PeekMessage when idle calls
 *      GameTick (0x413130) every idle cycle; GetMessage/
 *      DispatchMessage otherwise.
 *   6. Shutdown() (0x40f400) tears down sockets/DirectX on exit.
 *
 * None of WndProc/InitGame/GameTick/Shutdown have been ported yet -
 * each is a substantial function in its own right (GameTick alone
 * dispatches to the whole per-state vtable system documented in
 * ARCHITECTURE.md) and belongs in its own file once tackled, matching
 * the one-file-per-function convention used elsewhere in src/. This
 * file just wires up the real control flow shape with stubs so the
 * skeleton is honest about what's implemented vs. not, rather than
 * omitting the top-level structure entirely.
 */
#include <windows.h>

/* WndProc - 0x410040. Not yet ported. */
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

/* InitGame - 0x40eaa0. Not yet ported: DirectDraw/DirectSound/
 * DirectInput setup and the 16-slot game-state object array
 * construction (see ARCHITECTURE.md's game-state-machine section)
 * all belong here once attempted. */
static BOOL InitGame(HWND hwnd, HINSTANCE hInstance) {
    (void)hwnd;
    (void)hInstance;
    return TRUE;
}

/* GameTick - 0x413130. Not yet ported: the per-frame update/render
 * tick, dispatching through g_gameStateVTableArray[g_currentGameState]
 * (vtable slots 14/15 for D3D/software render, per ARCHITECTURE.md's
 * "GameTick's exact per-frame render dispatch" section) plus the
 * generic active-object sweep. */
static void GameTick(void) {
}

/* Shutdown - 0x40f400. Not yet ported: tears down sockets/DirectX. */
static void Shutdown(void) {
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "GunBoundWindowClass";
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA(wc.lpszClassName, "GunBound", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                               NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        return 1;
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);

    if (!InitGame(hwnd, hInstance)) {
        return 1;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    for (;;) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            GameTick();
        }
    }

    Shutdown();
    WSACleanup();
    return (int)msg.wParam;
}
