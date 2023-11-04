using System.Runtime.InteropServices;
namespace IsaacSocket.Utils
{
    internal static partial class WinAPIUtil
    {
        [DllImport("kernel32.dll")]
        internal static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, AllocationType flAllocationType, MemoryProtection flProtect);

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
        [DllImport("kernel32.dll")]
        internal static extern int GetProcessId(IntPtr processHandle);

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern bool AddClipboardFormatListener(IntPtr hwnd);

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern bool RemoveClipboardFormatListener(IntPtr hwnd);

        [DllImport("kernel32.dll", SetLastError = true)]
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
            internal IntPtr BaseAddress;
            internal IntPtr AllocationBase;
            internal uint AllocationProtect;
            internal IntPtr RegionSize;
            internal uint State;
            internal uint Protect;
            internal uint Type;
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool GetExitCodeProcess(IntPtr hProcess, out uint lpExitCode);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern IntPtr OpenProcess(ProcessAccessFlags access, bool inheritHandle, uint processId);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern uint VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        internal static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint lpdwProcessId);

    }
}
