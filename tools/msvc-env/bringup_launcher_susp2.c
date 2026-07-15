/* Two-stage suspended bring-up launcher - like bringup_launcher_susp.c,
 * but the child is briefly RESUMED and then RE-SUSPENDED before the
 * debugger-attach wait, instead of staying frozen from the very first
 * instruction.
 *
 * This works around a winedbg limitation observed on this box: `winedbg
 * --gdb --no-start --port N <pid>` returns "Can't attach process ...:
 * error 87" for a process that is CREATE_SUSPENDED and has never
 * executed any code (no loader/DLL init has happened yet) - but attaches
 * fine once the process has run for even a short time. Letting the child
 * run for KICK_MS milliseconds (past DLL/CRT init) then suspending it
 * again gives winedbg a valid attach point while still stopping well
 * before any real crash further into the program.
 *
 * Usage (from gamedir):
 *   wine bringup_launcher_susp2.exe [96-hex-token]
 * It prints the child's win32 PID, then polls for gamedir/dbg_go.txt.
 * Attach the debugger to that PID, then:
 *   echo go > dbg_go.txt   (from the host) -> final ResumeThread + wait.
 */
#include <windows.h>
#include <string.h>
#include <stdio.h>

#define KICK_MS 300

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

    if (!CreateProcessA("gunbound_bringup.exe", cmdline, NULL, NULL, FALSE,
                        CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
        return 1;
    }

    ResumeThread(pi.hThread);
    Sleep(KICK_MS);
    SuspendThread(pi.hThread);

    printf("CHILD_PID=%lu (0x%lx)  kicked+resuspended, waiting for dbg_go.txt ...\n",
           pi.dwProcessId, pi.dwProcessId);
    fflush(stdout);

    /* wait up to 300s for the go signal */
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
