using IsaacSocket.Common;
using IsaacSocket.Utils;
using System.Diagnostics;
using System.IO.MemoryMappedFiles;
using System.Reflection;
using System.Text;

namespace IsaacSocket.Modules
{
    internal class IsaacAPIModule : Module, IProcessOperation
    {
        //常量：一级偏移（Game）
        const int GAME_OFFSET = 0x7FD65C;
        //常量：二级偏移（Player）
        const int PLAYER_OFFSET = 0x1BA50;
        //常量：一级偏移（注入点）
        const int INJECTION_POINT_OFFSET = 0x48BDF5;
        //常量：debug标志偏移
        const int DEBUG_FLAG_OFFSET = 0x001C3164;
        private enum ActionType
        {
            //数据已更新
            DATA_UPDATED = 0,
            //设置数据
            SET_DATA = 1,
            //重载lua环境
            RELOAD_LUA = 2,
            FORCE_PAUSE = 3
        }
        private enum DataType
        {
            //debug标志
            DEBUG_FLAG = 0,
            //角色信息
            PLAYER_DATA = 1
        }
        private enum PlayerDataType
        {
            //主动
            ACTIVE_DATA = 0,
            //是否能射击
            CAN_SHOOT = 1,
        }

        private enum ActiveDataType
        {
            //主动附加变量
            VAR_DATA = 0,
            //4.5伏特进度（浮点）
            PARTIAL_CHARGE = 1,
            //9伏特进度
            SUB_CHARGE = 2
        }
        private string tempDLLPath;
        private byte numPlayer;
        private nint isaacProcessHandle;
        private int ImageBaseAdress;
        private readonly Dictionary<DataType, object> dataDictionary;

        public nint IsaacProcessHandle
        {
            get => isaacProcessHandle;
            set => isaacProcessHandle = value;
        }

        internal IsaacAPIModule(Channel channel, CallbackDelegate callback) : base(channel, callback)
        {
            if (Debugger.IsAttached)
            {
                tempDLLPath = "C:\\Users\\lanbing\\OneDrive\\Desktop\\IsaacSocket\\Release\\IsaacSocket.dll";
            }
            else
            {
                tempDLLPath = Path.Combine(MiscUtil.GetTemporaryDirectory("IsaacSocket_"), "IsaacSocket.dll");
            }
            MiscUtil.ExtractFile("IsaacSocket.dll", tempDLLPath);
            Dictionary<PlayerDataType, object>[] players = new Dictionary<PlayerDataType, object>[64];
            for (byte i = 0; i < 64; i++)
            {
                Dictionary<ActiveDataType, object>[] actives = new Dictionary<ActiveDataType, object>[4];
                for (byte j = 0; j < 4; j++)
                {
                    actives[j] = new()
                    {
                        { ActiveDataType.VAR_DATA, 0 },
                        { ActiveDataType.PARTIAL_CHARGE, (float)0 },
                        { ActiveDataType.SUB_CHARGE, 0 }
                    };
                }
                players[i] = new()
                {
                    { PlayerDataType.ACTIVE_DATA, actives },
                    { PlayerDataType.CAN_SHOOT, (byte)0 },
                };
            }
            dataDictionary = new()
            {
                { DataType.DEBUG_FLAG, 0 },
                { DataType.PLAYER_DATA, players }
            };
        }


        private int GetDataAddress(params object[] args)
        {
            switch ((DataType)args[0])
            {
                case DataType.DEBUG_FLAG:
                    return MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, DEBUG_FLAG_OFFSET);
                case DataType.PLAYER_DATA:
                    byte playerId = (byte)args[1];
                    switch ((PlayerDataType)args[2])
                    {
                        case PlayerDataType.CAN_SHOOT:
                            return MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET, playerId * 4, 0x1745);
                        case PlayerDataType.ACTIVE_DATA:
                            byte activeSlot = (byte)args[3];
                            switch ((ActiveDataType)args[4])
                            {
                                case ActiveDataType.VAR_DATA:
                                    return MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET, playerId * 4, 0x14dc + activeSlot * 28);
                                case ActiveDataType.PARTIAL_CHARGE:
                                    return MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET, playerId * 4, 0x14d8 + activeSlot * 28);
                                case ActiveDataType.SUB_CHARGE:
                                    return MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET, playerId * 4, 0x14d0 + activeSlot * 28);
                            }
                            break;
                    }
                    break;
            }
            return 0;
        }
        private bool SetData(object data, params object[] args)
        {
            return MemoryUtil.WriteToMemory(isaacProcessHandle, GetDataAddress(args), MiscUtil.ConvertToByteArray(data));
        }
        private object GetData(params object[] args)
        {
            int address = GetDataAddress(args);
            if ((DataType)args[0] == DataType.PLAYER_DATA)
            {
                if ((PlayerDataType)args[2] == PlayerDataType.CAN_SHOOT)
                {
                    return MemoryUtil.ReadByteFromMemory(isaacProcessHandle, address);
                }
                if ((ActiveDataType)args[4] == ActiveDataType.PARTIAL_CHARGE)
                {
                    return MemoryUtil.ReadFloatFromMemory(isaacProcessHandle, address);
                }
            }
            return MemoryUtil.ReadInt32FromMemory(isaacProcessHandle, address);
        }
        private void DataUpdated(object data, params object[] args)
        {
            DataType dataType = (DataType)args[0];
            List<byte> buffer = new()
            {
                (byte)ActionType.DATA_UPDATED,
                (byte)dataType
            };
            if (dataType == DataType.PLAYER_DATA)
            {
                byte playerId = (byte)args[1];
                buffer.Add(playerId);
                PlayerDataType playDataType = (PlayerDataType)args[2];
                buffer.Add((byte)playDataType);
                if (playDataType == PlayerDataType.ACTIVE_DATA)
                {
                    byte activeSlot = (byte)args[3];
                    buffer.Add(activeSlot);
                    ActiveDataType activeDataType = (ActiveDataType)args[4];
                    buffer.Add((byte)activeDataType);
                }
            }
            buffer.AddRange(MiscUtil.ConvertToByteArray(data));
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, buffer.ToArray());
        }

        private void ForcePause(bool pause)
        {
            using MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("IsaacSocketSharedMemory");
            using MemoryMappedViewAccessor accessor = mmf.CreateViewAccessor();
            accessor.Write(4, pause);
        }
        private void ReloadLua()
        {
            using MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("IsaacSocketSharedMemory");
            using MemoryMappedViewAccessor accessor = mmf.CreateViewAccessor();
            accessor.Write(0, true);
        }
        private byte GetNumPlayers()
        {
            int address1 = MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET);
            int address2 = MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET + 4);
            int value1 = MemoryUtil.ReadInt32FromMemory(isaacProcessHandle, address1);
            int value2 = MemoryUtil.ReadInt32FromMemory(isaacProcessHandle, address2);
            return (byte)((value2 - value1) / 4);
        }

        private void InjectCode()
        {
            if (File.Exists(tempDLLPath))
            {
                _ = WinAPIUtil.GetWindowThreadProcessId(WinAPIUtil.FindWindow("GLFW30", "Binding of Isaac: Repentance"), out uint processID);
                using Process isaacProcess = Process.GetProcessById((int)processID);
                nint handle = WinAPIUtil.GetModuleHandleA("Kernel32.dll");
                nint address = WinAPIUtil.GetProcAddress(handle, "LoadLibraryW");
                int size = Encoding.Unicode.GetByteCount(tempDLLPath); ;
                int pMem = (int)WinAPIUtil.VirtualAllocEx(isaacProcess.Handle, 0, (uint)size, WinAPIUtil.AllocationType.COMMIT | WinAPIUtil.AllocationType.RESERVE, WinAPIUtil.MemoryProtection.EXECUTE_READWRITE);
                bool success = WinAPIUtil.WriteProcessMemory(isaacProcess.Handle, pMem, Encoding.Unicode.GetBytes(tempDLLPath), (uint)size, out _);
                nint hThread = WinAPIUtil.CreateRemoteThread(isaacProcess.Handle, 0, 0, address, pMem, 0, 0);

                _ = WinAPIUtil.WaitForSingleObject(hThread, uint.MaxValue);
                WinAPIUtil.GetExitCodeThread(hThread, out uint hDllModule);
                WinAPIUtil.CloseHandle(hThread);
                WinAPIUtil.VirtualFreeEx(isaacProcess.Handle, pMem, size, 32768);

                using MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("IsaacSocketSharedMemory");
                string s = "注入dll成功";
                Callback(CallbackType.MESSAGE, s);
            }
            else
            {
                string s = "注入dll失败";
                Callback(CallbackType.MESSAGE, s);
            }

        }
        internal override void Connected()
        {
            ImageBaseAdress = MemoryUtil.GetImageBaseAdress(isaacProcessHandle);
            //代码注入
            InjectCode();

            //debug标志
            int debugFlag = (int)GetData(DataType.DEBUG_FLAG);
            dataDictionary[DataType.DEBUG_FLAG] = debugFlag;
            DataUpdated(debugFlag, DataType.DEBUG_FLAG);

            //players
            Dictionary<PlayerDataType, object>[] players = (Dictionary<PlayerDataType, object>[])dataDictionary[DataType.PLAYER_DATA];
            numPlayer = GetNumPlayers();
            for (byte i = 0; i < numPlayer; i++)
            {
                Dictionary<PlayerDataType, object> player = players[i];
                //能否射击
                byte canShoot = (byte)GetData(DataType.PLAYER_DATA, i, PlayerDataType.CAN_SHOOT);
                player[PlayerDataType.CAN_SHOOT] = canShoot;
                DataUpdated(canShoot, DataType.PLAYER_DATA, i, PlayerDataType.CAN_SHOOT);
                //actives
                Dictionary<ActiveDataType, object>[] actives = (Dictionary<ActiveDataType, object>[])player[PlayerDataType.ACTIVE_DATA];
                for (byte j = 0; j < 4; j++)
                {
                    Dictionary<ActiveDataType, object> active = actives[j];
                    //vardata
                    int varData = (int)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.VAR_DATA);
                    active[ActiveDataType.VAR_DATA] = varData;
                    DataUpdated(varData, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.VAR_DATA);
                    //4.5伏特
                    float partialCharge = (float)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.PARTIAL_CHARGE);
                    active[ActiveDataType.PARTIAL_CHARGE] = partialCharge;
                    DataUpdated(partialCharge, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.PARTIAL_CHARGE);
                    //9伏特
                    int subCharge = (int)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.SUB_CHARGE);
                    active[ActiveDataType.SUB_CHARGE] = subCharge;
                    DataUpdated(subCharge, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.SUB_CHARGE);
                }
            }
        }

        internal override void Disconnected()
        {

        }

        internal override void Exited()
        {

        }

        internal override string MemoryMessageToString(byte[] message)
        {
            StringBuilder stringBuilder = new();
            ActionType action = (ActionType)message[0];
            //0:action 1:数据类型 2:playerid 3:player数据类型 4:主动id
            switch (action)
            {
                case ActionType.DATA_UPDATED:
                case ActionType.SET_DATA:
                    string actionText = action == ActionType.DATA_UPDATED ? "当前值" : "设置为";
                    DataType dataType = (DataType)message[1];
                    switch (dataType)
                    {
                        case DataType.DEBUG_FLAG:
                            int debugFlag = BitConverter.ToInt32(message, 2);
                            stringBuilder.Append($"Debug标志 {actionText}: {debugFlag}");
                            break;
                        case DataType.PLAYER_DATA:
                            byte playerId = message[2];
                            stringBuilder.Append($"角色 {playerId} ");
                            PlayerDataType playerDataType = (PlayerDataType)message[3];
                            switch (playerDataType)
                            {
                                case PlayerDataType.CAN_SHOOT:
                                    byte canShoot = message[4];
                                    stringBuilder.Append($"能否射击: {canShoot == 1}");
                                    break;
                                case PlayerDataType.ACTIVE_DATA:
                                    byte activeSlot = message[4];
                                    stringBuilder.Append($"主动 {activeSlot} 的 ");
                                    ActiveDataType activeDataType = (ActiveDataType)message[5];
                                    switch (activeDataType)
                                    {
                                        case ActiveDataType.VAR_DATA:
                                            int varData = BitConverter.ToInt32(message, 6);
                                            stringBuilder.Append($"VarData: {varData}");
                                            break;
                                        case ActiveDataType.PARTIAL_CHARGE:
                                            float partialCharge = BitConverter.ToSingle(message, 6);
                                            stringBuilder.Append($"4.5伏特充能: {partialCharge}");
                                            break;
                                        case ActiveDataType.SUB_CHARGE:
                                            int subCharge = BitConverter.ToInt32(message, 6);
                                            stringBuilder.Append($"9伏特充能: {subCharge}");
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case ActionType.RELOAD_LUA:
                    stringBuilder.Append(" 重新加载lua环境");
                    break;
                case ActionType.FORCE_PAUSE:
                    bool pause = message[1] == 1;
                    if (pause)
                    {
                        stringBuilder.Append("强制暂停游戏");
                    }
                    else
                    {
                        stringBuilder.Append("取消强制暂停");
                    }
                    break;
            }
            return stringBuilder.ToString();
        }

        internal override void ReceiveMemoryMessage(byte[] message)
        {
            ActionType action = (ActionType)message[0];
            switch (action)
            {
                case ActionType.SET_DATA:
                    DataType dataType = (DataType)message[1];
                    switch (dataType)
                    {
                        case DataType.DEBUG_FLAG:
                            int debugFlag = BitConverter.ToInt32(message, 2);
                            SetData(debugFlag, DataType.DEBUG_FLAG);
                            break;
                        case DataType.PLAYER_DATA:
                            byte playerId = message[2];
                            PlayerDataType playerDataType = (PlayerDataType)message[3];
                            switch (playerDataType)
                            {
                                case PlayerDataType.CAN_SHOOT:
                                    byte canShoot = message[4];
                                    SetData(canShoot, DataType.PLAYER_DATA, playerId, PlayerDataType.CAN_SHOOT);
                                    break;
                                case PlayerDataType.ACTIVE_DATA:
                                    byte activeSlot = message[4];
                                    ActiveDataType activeDataType = (ActiveDataType)message[5];
                                    switch (activeDataType)
                                    {
                                        case ActiveDataType.VAR_DATA:
                                            int varData = BitConverter.ToInt32(message, 6);
                                            SetData(varData, DataType.PLAYER_DATA, playerId, PlayerDataType.ACTIVE_DATA, activeSlot, ActiveDataType.VAR_DATA);
                                            break;
                                        case ActiveDataType.PARTIAL_CHARGE:
                                            float partialCharge = BitConverter.ToSingle(message, 6);
                                            SetData(partialCharge, DataType.PLAYER_DATA, playerId, PlayerDataType.ACTIVE_DATA, activeSlot, ActiveDataType.PARTIAL_CHARGE);
                                            break;
                                        case ActiveDataType.SUB_CHARGE:
                                            int subCharge = BitConverter.ToInt32(message, 6);
                                            SetData(subCharge, DataType.PLAYER_DATA, playerId, PlayerDataType.ACTIVE_DATA, activeSlot, ActiveDataType.SUB_CHARGE);
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case ActionType.RELOAD_LUA:
                    ReloadLua();
                    break;
                case ActionType.FORCE_PAUSE:
                    bool pause = message[1] == 1;
                    ForcePause(pause);
                    break;
            }
        }

        internal override void Update()
        {
            //debug标志
            int debugFlag = (int)GetData(DataType.DEBUG_FLAG);
            if (debugFlag != (int)dataDictionary[DataType.DEBUG_FLAG])
            {
                dataDictionary[DataType.DEBUG_FLAG] = debugFlag;
                DataUpdated(debugFlag, DataType.DEBUG_FLAG);
            }
            //players
            Dictionary<PlayerDataType, object>[] players = (Dictionary<PlayerDataType, object>[])dataDictionary[DataType.PLAYER_DATA];
            byte lastNumPlayer = numPlayer;
            numPlayer = GetNumPlayers();

            for (byte i = 0; i < numPlayer; i++)
            {
                Dictionary<PlayerDataType, object> player = players[i];
                bool isNewPlayer = i >= lastNumPlayer;
                //能否射击
                byte canShoot = (byte)GetData(DataType.PLAYER_DATA, i, PlayerDataType.CAN_SHOOT);
                if (isNewPlayer || canShoot != (byte)player[PlayerDataType.CAN_SHOOT])
                {
                    player[PlayerDataType.CAN_SHOOT] = canShoot;
                    DataUpdated(canShoot, DataType.PLAYER_DATA, i, PlayerDataType.CAN_SHOOT);
                }
                //actives
                Dictionary<ActiveDataType, object>[] actives = (Dictionary<ActiveDataType, object>[])player[PlayerDataType.ACTIVE_DATA];
                for (byte j = 0; j < 4; j++)
                {
                    Dictionary<ActiveDataType, object> active = actives[j];
                    //vardata
                    int varData = (int)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.VAR_DATA);
                    if (isNewPlayer || varData != (int)active[ActiveDataType.VAR_DATA])
                    {
                        active[ActiveDataType.VAR_DATA] = varData;
                        DataUpdated(varData, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.VAR_DATA);
                    }
                    //4.5伏特
                    float partialCharge = (float)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.PARTIAL_CHARGE);
                    if (isNewPlayer || partialCharge != (float)active[ActiveDataType.PARTIAL_CHARGE])
                    {
                        active[ActiveDataType.PARTIAL_CHARGE] = partialCharge;
                        DataUpdated(partialCharge, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.PARTIAL_CHARGE);
                    }
                    //9伏特
                    int subCharge = (int)GetData(DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.SUB_CHARGE);
                    if (isNewPlayer || subCharge != (int)active[ActiveDataType.SUB_CHARGE])
                    {
                        active[ActiveDataType.SUB_CHARGE] = subCharge;
                        DataUpdated(subCharge, DataType.PLAYER_DATA, i, PlayerDataType.ACTIVE_DATA, j, ActiveDataType.SUB_CHARGE);
                    }
                }
            }
        }
    }
}
