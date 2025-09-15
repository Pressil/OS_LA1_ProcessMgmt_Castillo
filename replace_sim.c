#include <stdio.h>
#include <windows.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command to simulate exec: run cmd /c dir
    char cmdLine[] = "cmd /c dir";

    // Create the new process
    if (!CreateProcess(
            NULL,        // Application name (NULL = use cmdLine)
            cmdLine,     // Command line
            NULL, NULL,  // Process/thread security
            FALSE,       // Inherit handles
            0,           // Creation flags
            NULL,        // Environment
            NULL,        // Current directory
            &si,
            &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for it to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get exit code
    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        printf("Failed to get exit code (%lu).\n", GetLastError());
        exitCode = 1; 
    }

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    Sleep(5000);
    return exitCode;
}
