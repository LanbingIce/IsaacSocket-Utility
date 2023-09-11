using System.Diagnostics;

namespace IsaacSocket.Utils
{
    internal static class MiscUtil
    {

        internal static int FindPatternIndex(byte[] byteArray, byte[] patternData, int startIndex)
        {

            int end = byteArray.Length - patternData.Length;
            for (int i = startIndex; i <= end; i += 4)
            {
                bool isPatternFound = true;
                for (int j = 0; j < 16; j++)
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
        internal static long GetCurrentTime()
        {
            return new DateTimeOffset(DateTime.UtcNow).ToUnixTimeMilliseconds();
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
    }
}
