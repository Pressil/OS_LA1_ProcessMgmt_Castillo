// create_basic.c
#include <stdio.h>
#include <windows.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD parentPid = GetCurrentProcessId();
    printf("Parent PID: %lu\n", parentPid);

    // Build command line: child_echo.exe <parentPid>
    char cmdLine[256];
    sprintf(cmdLine, "child_echo.exe %lu", parentPid);

    if (!CreateProcess(
            NULL,           // Application name
            cmdLine,        // Command line
            NULL, NULL,     // Process/thread security
            FALSE,          // Inherit handles
            0,              // Creation flags
            NULL,           // Environment
            NULL,           // Current directory
            &si,            // Startup info
            &pi)) {         // Process info
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get child exit code
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode))
        printf("Child exited with code %lu\n", exitCode);
    else
        printf("Failed to get child exit code.\n");

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
