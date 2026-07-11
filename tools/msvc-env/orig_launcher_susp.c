/* Suspended launcher for the ORIGINAL GunBound.gme - identical to
 * bringup_launcher_susp.c but targets the real binary, for side-by-side
 * comparison against the bring-up port under a live debugger.
 *
 * Usage (from gamedir):
 *   wine orig_launcher_susp.exe [96-hex-token]
 * Prints CHILD_PID, then waits for gamedir/dbg_go.txt before ResumeThread.
 */
#include <windows.h>
#include <string.h>
#include <stdio.h>

static const char DEFAULT_TOKEN[] =
    "000000000000000000000000000000000000000000000000"
    "000000000000000000000000000000000000000000000000";

int main(int argc, char **argv)
{
    const char *token = (argc > 1) ? argv[1] : DEFAULT_TOKEN;
    char cmdline[128];
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    int i;

    if (strlen(token) != 0x60) {
        fprintf(stderr, "token must be exactly 96 chars (got %u)\n",
                (unsigned)strlen(token));
        return 2;
    }
    strcpy(cmdline, token);

    ZeroMemory(&si, sizeof si); si.cb = sizeof si;
    ZeroMemory(&pi, sizeof pi);

    if (!CreateProcessA("GunBound.gme", cmdline, NULL, NULL, FALSE,
                        CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
        return 1;
    }
    printf("CHILD_PID=%lu (0x%lx)  waiting for dbg_go.txt ...\n",
           pi.dwProcessId, pi.dwProcessId);
    fflush(stdout);

    for (i = 0; i < 3000; i++) {
        DWORD a = GetFileAttributesA("dbg_go.txt");
        if (a != INVALID_FILE_ATTRIBUTES) break;
        Sleep(100);
    }
    DeleteFileA("dbg_go.txt");
    printf("resuming child\n"); fflush(stdout);
    ResumeThread(pi.hThread);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
