
namespace IsaacSocket.Utils
{
    internal static class ProcessUtil
    {
        internal static bool IsProcessRunning(IntPtr processHandle)
        {
            WinAPIUtil.GetExitCodeProcess(processHandle, out uint exitCode);

            return exitCode == 259;
        }

        internal static IntPtr OpenProcess(uint processId)
        {


            IntPtr processHandle = WinAPIUtil.OpenProcess(WinAPIUtil.ProcessAccessFlags.VMRead | WinAPIUtil.ProcessAccessFlags.VMWrite | WinAPIUtil.ProcessAccessFlags.QueryInformation, false, processId);
            return processHandle;
        }
        internal static void CloseProcessHandle(IntPtr processHandle)
        {

            WinAPIUtil.CloseHandle(processHandle);
        }



        internal static uint GetProcessId(string lpClassName, string lpWindowName)
        {
            _ = WinAPIUtil.GetWindowThreadProcessId(WinAPIUtil.FindWindow(lpClassName, lpWindowName), out uint processID);

            return processID;
        }

    }
}
