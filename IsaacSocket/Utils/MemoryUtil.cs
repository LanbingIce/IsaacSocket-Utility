using System.Diagnostics;
using System.Runtime.InteropServices;

namespace IsaacSocket.Utils
{
    internal static class MemoryUtil
    {



        // 定义写入内存的方法
        internal static bool WriteToMemory(IntPtr processHandle, IntPtr address, byte[] data)
        {

            bool success = WinAPIUtil.WriteProcessMemory(processHandle, address, data, (uint)data.Length, out _);
            return success;
        }

        internal static byte[] ReadFromMemory(IntPtr processHandle, IntPtr address, uint size)
        {

            byte[] dataBuffer = new byte[size];

            bool readResult = WinAPIUtil.ReadProcessMemory(processHandle, address, dataBuffer, size, out _);

            if (readResult)
            {
                return dataBuffer;
            }
            else
            {
                return Array.Empty<byte>();
            }
        }

        internal static byte ReadByteFromMemory(IntPtr processHandle, IntPtr address)
        {

            byte[] dataBuffer = new byte[1];
            bool readResult = WinAPIUtil.ReadProcessMemory(processHandle, address, dataBuffer, 1, out _);
            return readResult ? dataBuffer[0] : (byte)0;
        }


        internal static int ReadInt32FromMemory(IntPtr processHandle, IntPtr address)
        {
            byte[] dataBuffer = new byte[4];
            bool readResult = WinAPIUtil.ReadProcessMemory(processHandle, address, dataBuffer, 8, out _);
            return readResult ? BitConverter.ToInt32(dataBuffer, 0) : 0;
        }
        internal static uint ReadUInt32FromMemory(IntPtr processHandle, IntPtr address)
        {
            byte[] dataBuffer = new byte[4];
            bool readResult = WinAPIUtil.ReadProcessMemory(processHandle, address, dataBuffer, 8, out _);
            return readResult ? BitConverter.ToUInt32(dataBuffer, 0) : 0;
        }



        // 定义函数来搜索值
        internal static IntPtr SearchAddresses(IntPtr processHandle, long data)
        {

            List<byte> buffer = new();
            buffer.AddRange(BitConverter.GetBytes(1));
            buffer.AddRange(BitConverter.GetBytes(data));
            buffer.AddRange(BitConverter.GetBytes(0x13));
            byte[] patternData = buffer.ToArray();

            IntPtr address = 0;
            byte[] dataBuffer;
            IntPtr memoryAddress = 0;
            bool readResult;
            int foundOffset = 0;

            int count = 0;
            while (WinAPIUtil.VirtualQueryEx(processHandle, memoryAddress, out WinAPIUtil.MEMORY_BASIC_INFORMATION memoryBlockInfo, (uint)Marshal.SizeOf(typeof(WinAPIUtil.MEMORY_BASIC_INFORMATION)))!=0)
            {

                if (memoryBlockInfo.Protect == 4 && memoryBlockInfo.Type == 0x00020000)
                {
                    count++;
                    dataBuffer = new byte[memoryBlockInfo.RegionSize];
                    readResult = WinAPIUtil.ReadProcessMemory(processHandle, memoryAddress, dataBuffer, (uint)memoryBlockInfo.RegionSize, out _);

                    while (readResult)
                    {
                        foundOffset = MiscUtil.FindPatternIndex(dataBuffer, patternData, foundOffset);
                        if (foundOffset == -1)
                        {
                            foundOffset = 0;
                            break;
                        }
                        else if (address ==0)
                        {
                            address = memoryAddress + foundOffset + 4;
                        }
                        else
                        {
                            return 0;
                        }
                        foundOffset += 16;
                    }


                }


                memoryAddress += memoryBlockInfo.RegionSize;



            }



            return address;
        }

    }
}
