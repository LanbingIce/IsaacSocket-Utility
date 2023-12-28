#include <format>
#include <iostream>
#include <windows.h>

std::wstring getExecutableDirW() {
    WCHAR buffer[MAX_PATH + 1];
    DWORD len = GetModuleFileNameW(NULL, buffer, MAX_PATH);
    if (len == 0) return L".";
    buffer[len] = '\0';
    std::wstring executableDir = buffer;
    size_t lastSlashIndex = executableDir.find_last_of(L"\\/");
    executableDir = executableDir.substr(0, lastSlashIndex);
    return executableDir;
}

HANDLE executeCommandA(std::string cmdLine)
{
    BOOL bSuccess = FALSE;

    PROCESS_INFORMATION piProcInfo; 
    STARTUPINFOA siStartInfo;    
    ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
    siStartInfo.cb = sizeof(STARTUPINFO); 
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    cmdLine = "\"" + cmdLine + "\"";
    // Execute a synchronous child process & get exit code
    bSuccess = CreateProcessA( NULL,
      cmdLine.data(),       // command line
      NULL,                 // process security attributes
      NULL,                 // primary thread security attributes
      TRUE,                 // handles are inherited
      0,                    // creation flags
      NULL,                 // use parent's environment
      NULL,                 // use parent's current directory
      &siStartInfo,         // STARTUPINFO pointer
      &piProcInfo );        // receives PROCESS_INFORMATION
    if( !bSuccess ) return NULL;
    CloseHandle(piProcInfo.hThread);
    return piProcInfo.hProcess;
}

void dllInjection(HANDLE hProcess, std::wstring const &dllName) {
    std::wstring dllPath = getExecutableDirW() + L"\\" + dllName;
    /* std::wstring dllPath = L"C:\\users\\steamuser\\Temp\\IsaacSocket.dll"; */

    std::wcout << std::format(L"Injecting DLL path: {}", dllPath) << std::endl;
    SIZE_T evilLen = dllPath.size() * sizeof(WCHAR);
    LPCVOID evilDLL = dllPath.data();
    auto pMem = VirtualAllocEx(hProcess, NULL, (DWORD)evilLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, pMem, evilDLL, evilLen, NULL);

    std::cout << std::format("Starting injection thread") << std::endl;
    HMODULE hKernel32 = GetModuleHandleW(L"Kernel32");
    FARPROC loadLibraryW = GetProcAddress(hKernel32, "LoadLibraryW");
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryW, pMem, 0, NULL);

    std::cout << std::format("Waiting for injection thread to exit") << std::endl;
    WaitForSingleObject(hThread, INFINITE);
    DWORD exitCode = STATUS_PENDING;
    GetExitCodeThread(hThread, &exitCode);
    std::cout << std::format("Injection thread exited with {}", exitCode) << std::endl;

    /* if (exitCode == 0) { */
    /*     std::cout << std::format("Starting error detection thread") << std::endl; */
    /*     FARPROC getLastError = GetProcAddress(hKernel32, "GetLastError"); */
    /*     HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)getLastError, pMem, 0, NULL); */
    /*     std::cout << std::format("Waiting for error detection thread to exit") << std::endl; */
    /*     WaitForSingleObject(hThread, INFINITE); */
    /*     DWORD exitCode = STATUS_PENDING; */
    /*     GetExitCodeThread(hThread, &exitCode); */
    /*     std::cout << std::format("Error detection thread exited with {}", exitCode) << std::endl; */
    /* } */

    CloseHandle(hThread);
    VirtualFreeEx(hProcess, pMem, evilLen, MEM_RELEASE);
}

int main(int argc, char **argv) {
    LPCSTR game = argv[1];
    if (!game) return -1;

    std::cout << std::format("Launching {}", game) << std::endl;
    HANDLE hProcess = executeCommandA(game);
    if (hProcess == NULL) {
        std::cout << std::format("Failed to start game process") << std::endl;
        return -1;
    }

    /* if (dwProcessId == 0) { */
    /*     std::cout << std::format("Failed to launch {}", game) << std::endl; */
    /*     return -1; */
    /* } */
    /* std::cout << std::format("Game started, PID {}", dwProcessId) << std::endl; */
    /* HANDLE hProcess = OpenProcess(0xffff, FALSE, dwProcessId); */
    /* if (hProcess == NULL || hProcess == INVALID_HANDLE_VALUE) { */
    /*     std::cout << std::format("Failed to open process {}", dwProcessId) << std::endl; */
    /*     return -1; */
    /* } */

    std::cout << std::format("Waiting for 5 seconds before injection") << std::endl;
    Sleep(5000);
    dllInjection(hProcess, L"libwinpthread-1.dll");
    dllInjection(hProcess, L"libgcc_s_dw2-1.dll");
    dllInjection(hProcess, L"libstdc++-6.dll");
    dllInjection(hProcess, L"IsaacSocket.dll");

    std::cout << std::format("Waiting for game to exit") << std::endl;
    WaitForSingleObject(hProcess, INFINITE);
    DWORD exitCode = STATUS_PENDING;
    GetExitCodeProcess(hProcess, &exitCode);
    CloseHandle(hProcess);

    std::cout << std::format("Game exited with {}", exitCode) << std::endl;
    return 0;
}
