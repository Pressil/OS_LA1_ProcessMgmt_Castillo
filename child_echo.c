// child_echo.c
#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc < 2) {
        printf("Usage: child_echo <parent_pid>\n");
        fflush(stdout);
        return 1;
    }

    printf("Child PID: %lu, Parent PID (passed): %s\n", pid, argv[1]);
    fflush(stdout);

    // Sleep for 15 seconds so you can see the child in PowerShell
    Sleep(30000);

    printf("Child PID %lu exiting normally.\n", pid);
    fflush(stdout);

    return 0; // success
}
