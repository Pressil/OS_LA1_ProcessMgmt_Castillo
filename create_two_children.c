#include <stdio.h>
#include <windows.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi[2];
    DWORD parentPid = GetCurrentProcessId();

    printf("Parent PID: %lu\n", parentPid);
    fflush(stdout);

    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        char cmdLine[256];
        sprintf(cmdLine, "child_echo.exe %lu", parentPid);

        if (!CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi[i])) {
            printf("CreateProcess failed for child %d (%lu).\n", i + 1, GetLastError());
            return 1;
        }

        // ✅ Wait immediately for this child before moving on
        WaitForSingleObject(pi[i].hProcess, INFINITE);

        DWORD exitCode;
        if (GetExitCodeProcess(pi[i].hProcess, &exitCode)) {
            printf("Child %d exited with code %lu\n", i + 1, exitCode);
        }

        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}
