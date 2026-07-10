/* Bring-up launcher - stands in for the real Softnyx Launcher.exe.
 *
 * GunBound's WinMain is NOT a standalone entry point: it calls
 * GetCommandLineA() and bails immediately (return 0, no window) unless
 * the command line is exactly 0x60 = 96 characters, which it then
 * parses as 48 hex byte-pairs ("%02x" x48) into the session blob at
 * DAT_005b3440 (server address/port/user id/session key). The real
 * Launcher obtains that blob from the login server, then starts the
 * game via CreateProcess with lpApplicationName set separately and
 * lpCommandLine = the 96-char token ALONE - so the game sees only the
 * token, not its own exe path.
 *
 * This shim reproduces that launch exactly with a synthetic token (96
 * chars, all hex). For reaching the logo screens (states 5/6, which run
 * before any connect) the byte values don't matter - only that the
 * length gate passes and the hex parse succeeds. Override the token
 * with argv[1] (must be 96 hex chars) to drive later states.
 *
 * Build (in the gb-msvc container):
 *   cl /nologo /Fe:bringup_launcher.exe bringup_launcher.c user32.lib
 * Run from the game dir:
 *   wine bringup_launcher.exe [96-hex-token]
 */
#include <windows.h>
#include <string.h>
#include <stdio.h>

/* 96 hex chars. All-zero blob: server 0.0.0.0, ids/keys 0. Enough to
 * pass the gate and reach the logo. */
static const char DEFAULT_TOKEN[] =
    "000000000000000000000000000000000000000000000000"
    "000000000000000000000000000000000000000000000000";

int main(int argc, char **argv)
{
    const char *token = (argc > 1) ? argv[1] : DEFAULT_TOKEN;
    char cmdline[128];
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    if (strlen(token) != 0x60) {
        fprintf(stderr, "token must be exactly 96 chars (got %u)\n",
                (unsigned)strlen(token));
        return 2;
    }
    /* lpCommandLine is mutable and must be the token alone */
    strcpy(cmdline, token);

    ZeroMemory(&si, sizeof si);
    si.cb = sizeof si;
    ZeroMemory(&pi, sizeof pi);

    if (!CreateProcessA("gunbound_bringup.exe", cmdline, NULL, NULL, FALSE,
                        0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
