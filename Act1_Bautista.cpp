#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char cmd[] = "cmd.exe /c dir"; // Command to execute

    if (!CreateProcess(
        NULL,   // Application name (use command line)
        cmd,    // Command line
        NULL,   // Process security attributes
        NULL,   // Thread security attributes
        FALSE,  // Inherit handles? (No)
        0,      // Creation flags
        NULL,   // Environment block (parent's)
        NULL,   // Working directory (parent's)
        &si,    // STARTUPINFO
        &pi     // PROCESS_INFORMATION
    )) {
        cerr << "CreateProcess failed: " << GetLastError() << endl;
        return 1;
    }

    // Wait for child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exit_code;
	GetExitCodeProcess(pi.hProcess, &exit_code);
	std::cout << "Child process exited with code: " << exit_code << std::endl;

	// Execution time measurement
	DWORD start_time = GetTickCount();
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD duration = GetTickCount() - start_time;
	std::cout << "Execution time: " << duration << "ms" << std::endl;


    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "Child process completed." << endl;
    return 0;
}

