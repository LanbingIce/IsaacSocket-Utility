using System.Diagnostics;
using System.IO.Compression;
using System.Text;

namespace IsaacSocket.Utils
{
    internal static class MiscUtil
    {
        internal static byte[] ConvertToByteArray(object value)
        {
            return value switch
            {
                int intValue => BitConverter.GetBytes(intValue),
                byte byteValue => new byte[] { byteValue },
                float floatValue => BitConverter.GetBytes(floatValue),
                _ => Array.Empty<byte>()
            };
        }

        internal static int FindPatternIndex(byte[] byteArray, byte[] patternData, int startIndex)
        {

            int end = byteArray.Length - patternData.Length;
            for (int i = startIndex; i <= end; i += 4)
            {
                bool isPatternFound = true;
                for (int j = 0; j < patternData.Length; j++)
                {

                    if (byteArray[i + j] != patternData[j])
                    {
                        isPatternFound = false;
                        break;
                    }
                }


                if (isPatternFound)
                {

                    return i;
                }
            }

            return -1;
        }

        internal static string GetDataFilePath(string fileName)
        {
            string dirPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "IsaacSocket");
            string filePath = Path.Combine(dirPath, fileName);

            if (!File.Exists(dirPath))
            {
                Directory.CreateDirectory(dirPath);
            }

            return filePath;
        }

        internal static long GetCurrentTime()
        {
            return new DateTimeOffset(DateTime.UtcNow).ToUnixTimeMilliseconds();
        }
        internal static bool IsValidUTF8ByteArray(byte[] bytes)
        {
            byte UTF8CharacterMask1Byte = 0b1000_0000;
            byte Valid1Byte = 0b0000_0000;//0b0xxx_xxxx

            byte UTF8CharacterMask2Byte = 0b1110_0000;
            byte Valid2Byte = 0b1100_0000;//0b110x_xxxx

            byte UTF8CharacterMask3Byte = 0b1111_0000;
            byte Valid3Byte = 0b1110_0000;//0b1110_xxxx

            byte UTF8CharacterMask4Byte = 0b1111_1000;
            byte Valid4Byte = 0b1111_0000;//0b1111_0xxx

            byte UTF8CharacterMaskForExtraByte = 0b1100_0000;
            byte ValidExtraByte = 0b1000_0000;//0b10xx_xxxx
            short extraByteCount = 0;

            foreach (byte bt in bytes)
            {

                if (extraByteCount > 0)
                {
                    extraByteCount--;

                    // Extra Byte Pattern.
                    if ((bt & UTF8CharacterMaskForExtraByte) != ValidExtraByte)
                        return false;
                    continue;
                }
                else
                {
                    // 1 Byte Pattern.
                    if ((bt & UTF8CharacterMask1Byte) == Valid1Byte)
                    {
                        continue;
                    }

                    // 2 Bytes Pattern.
                    if ((bt & UTF8CharacterMask2Byte) == Valid2Byte)
                    {
                        extraByteCount = 1;
                        continue;
                    }

                    // 3 Bytes Pattern.
                    if ((bt & UTF8CharacterMask3Byte) == Valid3Byte)
                    {
                        extraByteCount = 2;
                        continue;
                    }

                    // 4 Bytes Pattern.
                    if ((bt & UTF8CharacterMask4Byte) == Valid4Byte)
                    {
                        extraByteCount = 3;
                        continue;
                    }

                    // invalid UTF8-Bytes.
                    return false;
                }
            }

            return extraByteCount == 0;
        }
        internal static bool ExtractFile(byte[] resource, string path)
        {
            try
            {
                File.WriteAllBytes(path, Decompress(resource));
            }
            catch
            {
                return false;
            }
            return true;
        }
        internal static string GetCurrentExecutableFileName()
        {
            using Process process = Process.GetCurrentProcess();
            return Path.GetFileName(process.MainModule?.FileName ?? "IsaacSocket.exe");
        }
        internal static long GetSystemStartTime()
        {
            // 获取系统启动时间
            DateTime bootTime = DateTime.MinValue;
            try
            {
                // PerformanceCounter用于获取系统信息
                using PerformanceCounter pc = new("System", "System Up Time");
                pc.NextValue(); // 第一次调用时返回0，所以需要忽略

                // 获取系统启动时间（从1970年1月1日开始的秒数）
                bootTime = DateTime.Now - TimeSpan.FromSeconds(pc.NextValue());
            }
            catch (Exception)
            {
                return GetCurrentTime();
            }
            long uptimeTimestamp = new DateTimeOffset(bootTime).ToUnixTimeMilliseconds();
            return uptimeTimestamp;
        }

        internal static IntPtr FindWindow(string lpClassName, string lpWindowName)
        {
            nint h = nint.Zero;
            while (true)
            {
                h = WinAPIUtil.FindWindowEx(0, h, lpClassName, null);
                if (h != 0)
                {
                    string TitleName = GetWindowText(h);
                    if (TitleName.Contains(lpWindowName))
                    {
                        return h;
                    }
                }

            }
        }

        public static string GetWindowText(nint hWnd)
        {
            int length = WinAPIUtil.GetWindowTextLength(hWnd);
            if (length > 0)
            {
                StringBuilder sb = new(length + 1);
                _ = WinAPIUtil.GetWindowText(hWnd, sb, sb.Capacity);
                return sb.ToString();
            }
            return "";
        }

        internal static bool LoadLibrary(nint isaacProcessHandle, string dllPath)
        {
            nint pMem = 0;
            nint hThread = 0;
            uint exitCode = 0;
            try
            {
                byte[] pathData = Encoding.Unicode.GetBytes(dllPath + "\0");
                uint pathSize = (uint)pathData.Length;
                pMem = WinAPIUtil.VirtualAllocEx(isaacProcessHandle, 0, pathSize, WinAPIUtil.AllocationType.COMMIT | WinAPIUtil.AllocationType.RESERVE, WinAPIUtil.MemoryProtection.READWRITE);
                WinAPIUtil.WriteProcessMemory(isaacProcessHandle, pMem, pathData, pathSize, out _);
                nint hModule = WinAPIUtil.GetModuleHandle("Kernel32.dll");
                nint funcAddress = WinAPIUtil.GetProcAddress(hModule, "LoadLibraryW");
                hThread = WinAPIUtil.CreateRemoteThread(isaacProcessHandle, 0, 0, funcAddress, pMem, 0, 0);
                _ = WinAPIUtil.WaitForSingleObject(hThread, uint.MaxValue);
                WinAPIUtil.GetExitCodeThread(hThread, out exitCode);
            }
            catch { }
            finally
            {
                WinAPIUtil.CloseHandle(hThread);
                WinAPIUtil.VirtualFreeEx(isaacProcessHandle, pMem, 0, WinAPIUtil.FreeType.MEM_RELEASE);
            }
            return exitCode != 0;
        }

        internal static byte[] Decompress(byte[] data)
        {
            using MemoryStream input = new(data);
            using MemoryStream output = new();
            using DeflateStream dstream = new(input, CompressionMode.Decompress);
            dstream.CopyTo(output);
            return output.ToArray();
        }
    }
}
