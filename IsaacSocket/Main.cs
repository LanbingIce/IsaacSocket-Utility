﻿using IsaacSocket.Common;
using IsaacSocket.Modules;
using IsaacSocket.Properties;
using IsaacSocket.Utils;
using System.Collections.Concurrent;
using System.IO.MemoryMappedFiles;
using System.Text;


namespace IsaacSocket
{
    internal class Main
    {
        private class ReceiveTable
        {
            private byte page, replyPage;
            private int size, replySize;
            private readonly LinkedList<byte[]> messages = new();
            private readonly List<byte> buffer = new();
            internal byte GetPage()
            {
                return page;
            }
            internal int GetSize()
            {
                return size;
            }
            internal byte GetReplyPage()
            {
                return replyPage;
            }
            internal int GetReplySize()
            {
                return replySize;
            }

            internal byte[]? GetMessage()
            {
                if (messages.First != null)
                {
                    byte[] result = messages.First.Value;
                    messages.RemoveFirst();
                    return result;
                }
                return null;
            }
            internal void Initialize()
            {

                page = 0;
                size = 0;
                replyPage = 0;
                replySize = 0;
                messages.Clear();
                buffer.Clear();
            }

            internal bool Update(byte[] receiveData)
            {

                if (receiveData.Length < DATA_HEAD_SIZE)
                {
                    return false;
                }
                byte oldPage = page;
                byte oldReplyPage = replyPage;
                int oldReplySize = replySize;
                int oldSize = size;

                page = receiveData[0];
                replyPage = receiveData[1];
                replySize = BitConverter.ToInt32(receiveData, 2);

                int offset = DATA_HEAD_SIZE;

                // 如果上次收到的和这次收到的是同一页数据，更新 offset，忽略已接收的数据
                if (oldPage == page)
                {
                    offset += oldSize;
                }

                // 检查剩余空间，如果足够，可能存在新消息，执行循环

                while (receiveData.Length - offset >= 5)
                {

                    // 取出下一条消息的尺寸
                    int messageSize = BitConverter.ToInt32(receiveData, offset);
                    // 如果尺寸为 0，表示没有新消息，跳出循环
                    if (messageSize == 0)
                    {
                        break;
                    }
                    offset += 4;
                    // 根据消息尺寸，取出数据放入缓冲区，并判断是否完整接收到一条消息
                    byte[] data;
                    if (offset + messageSize > receiveData.Length)
                    {
                        data = receiveData[offset..];
                        buffer.AddRange(data);
                    }
                    else
                    {
                        data = receiveData[offset..(offset + messageSize)];
                        buffer.AddRange(data);
                        messages.AddLast(buffer.ToArray());
                        buffer.Clear();
                    }

                    offset += data.Length;

                }

                size = offset - DATA_HEAD_SIZE;

                // 比较更新前后的数据，若有不同则更新并返回 true，否则返回 false

                return replyPage != oldReplyPage || replySize != oldReplySize || page != oldPage || size != oldSize;
            }
        }

        private class SendTable
        {
            private int dataSpaceSize, dataBodySize, replySize;
            private byte page, replyPage;
            private readonly List<byte> buffer = new();
            private readonly LinkedList<byte[]> messages = new();

            internal SendTable(int dataSpaceSize)
            {
                Initialize(dataSpaceSize);
            }
            internal void Initialize(int dataSpaceSize)
            {
                this.dataSpaceSize = dataSpaceSize;
                dataBodySize = dataSpaceSize - DATA_HEAD_SIZE;
                page = 0;
                buffer.Clear();
                replyPage = 0;
                replySize = 0;
                messages.Clear();
            }

            internal void AddNewMessage(byte[] newMessage)
            {
                messages.AddLast(newMessage);
            }

            internal bool Update(ReceiveTable receiveTable)
            {

                //备份更新前的数据
                byte oldPage = page;
                int oldSize = buffer.Count;
                byte oldReplyPage = replyPage;
                int oldReplySize = replySize;


                replyPage = receiveTable.GetPage();
                replySize = receiveTable.GetSize();
                //如果上次发送的数据不为空并且确认对方全部收到，那么翻页，否则维持现状

                if (oldSize > 0 && receiveTable.GetReplyPage() == oldPage && receiveTable.GetReplySize() == oldSize)
                {
                    page = (byte)(page % 255 + 1);
                    buffer.Clear();
                }
                // 如果剩余空间足够（一条消息至少需要5字节的空间），且还存在要发送的消息，执行此循环
                while (dataBodySize - buffer.Count >= 5 && messages.First != null)
                {
                    // 先取出第一条消息，并把第一条消息的长度加入buffer
                    byte[] firstMessage = messages.First.Value;
                    messages.RemoveFirst();
                    buffer.AddRange(BitConverter.GetBytes(firstMessage.Length));
                    // 将尽可能多的部分放入buffer，如果空间不够，将剩余部分放回消息列表的顶部
                    int spaceLeft = dataBodySize - buffer.Count;
                    if (spaceLeft < firstMessage.Length)
                    {
                        messages.AddFirst(firstMessage[spaceLeft..]);
                        firstMessage = firstMessage[..spaceLeft];
                    }
                    buffer.AddRange(firstMessage);
                }
                // 比较更新前和更新后的回复时间戳/回复有效长度/时间戳/数据，若有不同，则说明本次更新有效并返回真，否则返回假

                return page != oldPage || buffer.Count != oldSize || replyPage != oldReplyPage || replySize != oldReplySize;

            }
            internal byte[] Serialize()
            {
                List<byte> buffer = new() { page, replyPage };
                buffer.AddRange(BitConverter.GetBytes(replySize));
                buffer.AddRange(this.buffer);
                int spaceLeft = dataSpaceSize - buffer.Count;
                if (spaceLeft >= 5)
                {
                    buffer.AddRange(new byte[4]);
                }
                return buffer.ToArray();

            }
        }

        private enum ConnectionState
        {
            DISCONNECTED = 0,
            FOUND_PROCESS = 1,
            CONNECTING = 2,
            CONNECTED = 3,
        }
        internal enum CallbackType
        {
            RECEIVE = 0,
            SEND = 1,
            MESSAGE = 2,
            HEART_BEAT = 3
        }
        private const int MAX_DATA_SPACE_SIZE = 4 * 1024 * 1024;
        //头部长度：6字节
        // 1字节page,1字节replyPage，4字节replySize
        private const int DATA_HEAD_SIZE = 1 + 1 + 4;
        private const uint SEND_ADDRESS_FEATURE_VALUE = 1842063751;
        private const uint RECEIVE_ADDRESS_FEATURE_VALUE = 2128394904;


        private readonly CallbackDelegate callback;
        private readonly Dictionary<Channel, Module> modules;
        private readonly ConcurrentQueue<byte[]> sendMessagesBuffer;
        private int newSize;
        private readonly CancellationTokenSource cancellationTokenSource;
        private readonly string dllPath;
        private readonly string version;

        private async Task UpdateTask(CancellationToken cancellationToken)
        {
            int dataSpaceSize = 1024;
            ConnectionState connectionState = ConnectionState.DISCONNECTED;
            IntPtr isaacProcessHandle = 0;
            IntPtr sendAddress = 0;
            IntPtr receiveAddress = 0;
            ReceiveTable receiveTable = new();
            SendTable sendTable = new(dataSpaceSize);
            try
            {
                while (!cancellationToken.IsCancellationRequested)
                {

                    ConnectionState oldState = connectionState;
                    if (newSize >= 64 && newSize <= MAX_DATA_SPACE_SIZE)
                    {
                        dataSpaceSize = newSize;
                        newSize = 0;
                        if (connectionState == ConnectionState.CONNECTED || connectionState == ConnectionState.CONNECTING)
                        {
                            connectionState = ConnectionState.FOUND_PROCESS;
                        }
                    }
                    byte sendAddressType = 0;
                    uint sendTextAddress = 0;
                    byte receiveAddressType = 0;
                    uint receiveTextAddress = 0;

                    if (connectionState == ConnectionState.CONNECTED || connectionState == ConnectionState.CONNECTING)
                    {
                        sendAddressType = MemoryUtil.ReadByteFromMemory(isaacProcessHandle, sendAddress + 0x8);
                        sendTextAddress = MemoryUtil.ReadUInt32FromMemory(isaacProcessHandle, sendAddress);
                        receiveAddressType = MemoryUtil.ReadByteFromMemory(isaacProcessHandle, receiveAddress + 0x8);
                        receiveTextAddress = MemoryUtil.ReadUInt32FromMemory(isaacProcessHandle, receiveAddress);
                        if (sendAddressType == 0x54 && (receiveAddressType == 0x44 || receiveAddressType == 0x54))//两个变量都为文本
                        {
                            connectionState = ConnectionState.CONNECTED;
                        }
                        else if ((sendAddressType == 0x13 || sendAddressType == 0x3) && sendTextAddress == dataSpaceSize && (receiveAddressType == 0x13 || receiveAddressType == 0x3) && receiveTextAddress == 1)//两个变量都是数值型且mod向程序发送数据的变量地址为1
                        {
                            connectionState = ConnectionState.CONNECTING;
                        }
                        else
                        {
                            connectionState = ConnectionState.FOUND_PROCESS;
                        }
                    }
                    switch (connectionState)
                    {
                        case ConnectionState.CONNECTED:
                            if (oldState == ConnectionState.CONNECTING)
                            {
                                receiveTable.Initialize();
                                sendTable.Initialize(dataSpaceSize);
                                Connected(dataSpaceSize);
                            }
                            uint size;
                            if (receiveAddressType == 0x44)
                            {
                                size = MemoryUtil.ReadByteFromMemory(isaacProcessHandle, (IntPtr)(receiveTextAddress + 0x7));
                            }
                            else
                            {
                                size = MemoryUtil.ReadUInt32FromMemory(isaacProcessHandle, (IntPtr)receiveTextAddress + 0xD);
                            }

                            receiveTable.Update(MemoryUtil.ReadFromMemory(isaacProcessHandle, (IntPtr)(receiveTextAddress + 0x10), size));
                            byte[]? newMessage = receiveTable.GetMessage();
                            while (newMessage != null)
                            {
                                NewMessageReceived(newMessage);
                                newMessage = receiveTable.GetMessage();
                            }
                            UpdateModules();
                            while (sendMessagesBuffer.TryDequeue(out newMessage))
                            {
                                sendTable.AddNewMessage(newMessage);
                                NewMessageSent(newMessage);
                            }

                            if (sendTable.Update(receiveTable))
                            {

                                MemoryUtil.WriteToMemory(isaacProcessHandle, (IntPtr)(sendTextAddress + 0x10), sendTable.Serialize());


                            }
                            await Task.Delay(1, cancellationToken);
                            break;
                        case ConnectionState.CONNECTING:
                            await Task.Delay(1000, cancellationToken);
                            break;
                        case ConnectionState.FOUND_PROCESS:
                            if (oldState == ConnectionState.CONNECTING || oldState == ConnectionState.CONNECTED)
                            {
                                Disconnected();
                            }
                            if (ProcessUtil.IsProcessRunning(isaacProcessHandle))
                            {
                                sendAddress = MemoryUtil.SearchAddresses(isaacProcessHandle, SEND_ADDRESS_FEATURE_VALUE);
                                receiveAddress = MemoryUtil.SearchAddresses(isaacProcessHandle, RECEIVE_ADDRESS_FEATURE_VALUE);

                                if (sendAddress == -1 || receiveAddress == -1)
                                {
                                    sendAddress = 0;
                                    receiveAddress = 0;
                                    callback.Invoke(CallbackType.MESSAGE, "请在游戏中关闭多余的 IsaacSocket ");
                                }

                                if (sendAddress != 0 && receiveAddress != 0)
                                {
                                    try
                                    {
                                        ExtractFile();
                                        using (MemoryMappedFile.OpenExisting("IsaacSocketSharedMemory")) { }
                                    }
                                    catch (FileNotFoundException)
                                    {
                                        callback.Invoke(CallbackType.MESSAGE, $"注入dll{(InjectCode(isaacProcessHandle) ? "成功" : "失败")} ");
                                    }

                                    try
                                    {
                                        using MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("IsaacSocketSharedMemory");
                                        using MemoryMappedViewAccessor accessor = mmf.CreateViewAccessor();

                                        byte[] bytes = new byte[8];
                                        accessor.ReadArray(0, bytes, 0, 8);
                                        int nullIndex = Array.IndexOf(bytes, (byte)0);
                                        string oldVersion = Encoding.ASCII.GetString(bytes, 0, nullIndex);

                                        if (oldVersion != "" && oldVersion != version)
                                        {
                                            callback.Invoke(CallbackType.MESSAGE, "dll版本校验失败，请重启游戏 ");
                                            await Task.Delay(3000, cancellationToken);
                                        }
                                        else
                                        {
                                            bytes = Encoding.ASCII.GetBytes(version + '\0');
                                            accessor.WriteArray(0, bytes, 0, bytes.Length);

                                            MemoryUtil.WriteToMemory(isaacProcessHandle, sendAddress, BitConverter.GetBytes(dataSpaceSize));
                                            MemoryUtil.WriteToMemory(isaacProcessHandle, receiveAddress, BitConverter.GetBytes(1));
                                            connectionState = ConnectionState.CONNECTING;
                                            Connecting();
                                        }
                                    }
                                    catch (FileNotFoundException)
                                    {
                                        callback.Invoke(CallbackType.MESSAGE, "打开共享内存失败 ");
                                    }
                                }
                                else
                                {
                                    await Task.Delay(2000, cancellationToken);
                                }
                            }
                            else
                            {
                                ProcessUtil.CloseProcessHandle(isaacProcessHandle);
                                connectionState = ConnectionState.DISCONNECTED;
                                LostProcess();
                            }

                            break;
                        case ConnectionState.DISCONNECTED:
                            isaacProcessHandle = ProcessUtil.OpenProcess(ProcessUtil.GetProcessId("GLFW30", "Binding of Isaac: Repentance"));

                            if (isaacProcessHandle != 0)
                            {
                                connectionState = ConnectionState.FOUND_PROCESS;
                                FoundProcess();
                            }
                            else
                            {
                                await Task.Delay(3000, cancellationToken);
                            }
                            break;
                    }
                }
            }
            catch (TaskCanceledException)
            {
                await Console.Out.WriteLineAsync("正常退出");
            }
            catch (Exception e)
            {
                await Console.Out.WriteLineAsync(e.ToString());
            }
            finally
            {
                ProcessUtil.CloseProcessHandle(isaacProcessHandle);
            }
        }

        private bool InjectCode(nint isaacProcessHandle)
        {
            MiscUtil.LoadLibrary(isaacProcessHandle, MiscUtil.GetDataFilePath("ImSDK.dll"));
            return MiscUtil.LoadLibrary(isaacProcessHandle, dllPath);
        }

        internal void Send(Channel channel, byte[] data)
        {
            List<byte> list = new() { (byte)channel };
            list.AddRange(data);
            sendMessagesBuffer.Enqueue(list.ToArray());

        }
        internal void SetDataSpaceSize(int newSize)
        {
            if (newSize >= 64 && newSize <= MAX_DATA_SPACE_SIZE)
            {
                callback.Invoke(CallbackType.MESSAGE, "交换区大小已设置为" + newSize + "字节");
                this.newSize = newSize;
            }
            else
            {
                callback.Invoke(CallbackType.MESSAGE, "设置失败，尺寸范围： 64 ~ " + MAX_DATA_SPACE_SIZE);
            }


        }
        private void ModuleCallback(params object[] args)
        {

            switch (args[0])
            {
                case Module.CallbackType.MEMORY_MESSAGE_GENERATED:
                    Send((Channel)args[1], (byte[])args[2]);
                    break;
                case Module.CallbackType.MESSAGE:
                    callback(CallbackType.MESSAGE, args[2]);
                    break;
            }
        }

        private void ExtractFile()
        {
            string configFilePath = MiscUtil.GetDataFilePath("config.json");
            if (!File.Exists(configFilePath))
            {
                File.WriteAllText(configFilePath, "{}");
            }
            string dllPath = MiscUtil.GetDataFilePath("IsaacSocket.dll");
            if (this.dllPath == dllPath)
            {
                MiscUtil.ExtractFile(Resources.IsaacSocket, dllPath);
            }
            MiscUtil.ExtractFile(Resources.VonwaonBitmap_16px, MiscUtil.GetDataFilePath("VonwaonBitmap-16px.ttf"));
            MiscUtil.ExtractFile(Resources.ImSDK, MiscUtil.GetDataFilePath("ImSDK.dll"));
        }

        internal Main(int dataSpaceSize, CallbackDelegate callback, string dllPath, string version)
        {
            this.version = version;
            if (dllPath == "")
            {
                dllPath = MiscUtil.GetDataFilePath("IsaacSocket.dll");
            }

            this.dllPath = dllPath;

            Application.ApplicationExit += OnExit;
            sendMessagesBuffer = new();
            this.callback = callback;
            newSize = dataSpaceSize;
            modules = new()
            {
                [Channel.WEB_SOCKET_CLIENT] = new WebsocketClientModule(Channel.WEB_SOCKET_CLIENT, ModuleCallback),
                [Channel.HTTP_CLIENT] = new HttpClientModule(Channel.HTTP_CLIENT, ModuleCallback)
            };
            cancellationTokenSource = new();
        }

        internal void Start(string dllPath)
        {
            if (dllPath != "")
            {
                callback.Invoke(CallbackType.MESSAGE, "已指定dll路径：" + dllPath);
                if (!File.Exists(dllPath))
                {
                    callback.Invoke(CallbackType.MESSAGE, "指定的dll不存在");
                    return;
                }
            }
            Task.Run(() => UpdateTask(cancellationTokenSource.Token));
        }


        private void OnExit(object? sender, EventArgs e)
        {
            cancellationTokenSource.Cancel();
            foreach (KeyValuePair<Channel, Module> kvp in modules)
            {
                kvp.Value.Exited();
            }
            Console.ReadKey();

        }

        private void NewMessageSent(byte[] newMessage)
        {
            Channel channel = (Channel)newMessage[0];
            byte[] message = newMessage[1..];
            callback.Invoke(CallbackType.SEND, $"【{channel}】：{Environment.NewLine}{modules[channel].MemoryMessageToString(message)}");

        }
        private void NewMessageReceived(byte[] newMessage)
        {
            Channel channel = (Channel)newMessage[0];
            byte[] message = newMessage[1..];
            if (channel == Channel.HEARTBEAT)
            {
                callback.Invoke(CallbackType.HEART_BEAT, "心跳包");
            }
            else if (Enum.IsDefined(typeof(Channel), channel))
            {
                callback.Invoke(CallbackType.RECEIVE, $"【{channel}】：{Environment.NewLine}{modules[channel].MemoryMessageToString(message)}");
                modules[channel].ReceiveMemoryMessage(message);
            }
        }

        private void FoundProcess()
        {

            callback.Invoke(CallbackType.MESSAGE, "以撒进程已找到！");
        }

        private void LostProcess()
        {
            callback.Invoke(CallbackType.MESSAGE, "以撒进程已关闭！");
        }

        private void UpdateModules()
        {
            foreach (KeyValuePair<Channel, Module> keyValuePair in modules)
            {
                keyValuePair.Value.Update();
            }
        }



        private void Connecting()
        {
            callback.Invoke(CallbackType.MESSAGE, "正在等待Mod回应...");
        }

        private void Disconnected()
        {
            foreach (KeyValuePair<Channel, Module> keyValuePair in modules)
            {
                keyValuePair.Value.Disconnected();
            }
            callback.Invoke(CallbackType.MESSAGE, "连接已断开！");
        }

        private void Connected(int dataSpaceSize)
        {
            sendMessagesBuffer.Clear();
            foreach (KeyValuePair<Channel, Module> keyValuePair in modules)
            {
                keyValuePair.Value.Connected();
            }
            callback.Invoke(CallbackType.MESSAGE, "已连接！交换区大小：" + dataSpaceSize + "字节");
        }
    }
}