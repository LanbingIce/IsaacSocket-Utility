using System.Runtime.InteropServices;
using System.Text;
namespace IsaacSocket.Utils
{
    internal static partial class WinAPIUtil
    {
        [Flags]
        internal enum AllocationType : uint
        {
            COMMIT = 0x1000,
            RESERVE = 0x2000,
            RESET = 0x80000,
            LARGE_PAGES = 0x20000000,
            PHYSICAL = 0x400000,
            TOP_DOWN = 0x100000,
        }

        [Flags]
        internal enum MemoryProtection : uint
        {
            EXECUTE = 0x10,
            EXECUTE_READ = 0x20,
            EXECUTE_READWRITE = 0x40,
            EXECUTE_WRITECOPY = 0x80,
            NOACCESS = 0x01,
            READONLY = 0x02,
            READWRITE = 0x04,
            WRITECOPY = 0x08,
        }
        [Flags]
        public enum FreeType : uint
        {
            MEM_DECOMMIT = 0x4000,
            MEM_RELEASE = 0x8000
        }

        [DllImport("kernel32.dll")]
        internal static extern int GetProcessId(nint processHandle);

        [DllImport("kernel32.dll")]
        internal static extern bool AllocConsole();

        [Flags]
        internal enum ProcessAccessFlags : uint
        {
            All = 0x001F0FFF,
            Terminate = 0x00000001,
            CreateThread = 0x00000002,
            VMOperation = 0x00000008,
            VMRead = 0x00000010,
            VMWrite = 0x00000020,
            DupHandle = 0x00000040,
            SetInformation = 0x00000200,
            QueryInformation = 0x00000400,
            Synchronize = 0x00100000
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct MEMORY_BASIC_INFORMATION
        {
            internal nint BaseAddress;
            internal nint AllocationBase;
            internal uint AllocationProtect;
            internal nint RegionSize;
            internal uint State;
            internal uint Protect;
            internal uint Type;
        }

        [DllImport("kernel32.dll")]
        internal static extern bool WriteProcessMemory(nint hProcess, nint lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        internal static extern bool GetExitCodeProcess(nint hProcess, out uint lpExitCode);

        [DllImport("kernel32.dll")]
        internal static extern nint OpenProcess(ProcessAccessFlags access, bool inheritHandle, uint processId);

        [DllImport("kernel32.dll")]
        internal static extern bool ReadProcessMemory(nint hProcess, nint lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll")]
        internal static extern bool CloseHandle(nint hObject);

        [DllImport("kernel32.dll")]
        internal static extern uint VirtualQueryEx(nint hProcess, nint lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        [DllImport("kernel32.dll")]
        internal static extern nint VirtualAllocEx(nint hProcess, nint lpAddress, uint dwSize, AllocationType flAllocationType, MemoryProtection flProtect);

        [DllImport("user32.dll")]
        internal static extern uint GetWindowThreadProcessId(nint hWnd, out uint lpdwProcessId);

#pragma warning disable CA2101 // 指定对 P/Invoke 字符串参数进行封送处理
        [DllImport("kernel32.dll", CharSet = CharSet.Ansi)]
#pragma warning restore CA2101 // 指定对 P/Invoke 字符串参数进行封送处理
        internal static extern nint GetProcAddress(nint hModule, string procName);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        internal static extern nint CreateRemoteThread(nint hProcess, nint lpThreadAttributes, uint dwStackSize, nint lpStartAddress, nint lpParameter, uint dwCreationFlags, nint lpThreadId);

        [DllImport("kernel32.dll")]
        internal static extern uint WaitForSingleObject(nint hHandle, uint dwMilliseconds);

        [DllImport("kernel32.dll")]
        internal static extern bool GetExitCodeThread(nint hThread, out uint lpExitCode);

        [DllImport("kernel32.dll")]
        public static extern bool VirtualFreeEx(nint hProcess, nint lpAddress, int dwSize, FreeType dwFreeType);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        internal static extern nint GetModuleHandle(string moduleName);

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        internal static extern nint FindWindowEx(nint hwndParent, nint hwndChildAfter, string lpszClass, string? lpszWindow);

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        internal static extern int GetWindowText(nint hWnd, StringBuilder text, int count);

        [DllImport("user32.dll")]
        internal static extern int GetWindowTextLength(nint hWnd);

    }
}
