using IsaacSocket.Common;
using IsaacSocket.Utils;
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
            RELOAD_LUA = 2
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

        private byte numPlayer;
        private int reloadAddress;
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
        private void ReloadLua()
        {
            MemoryUtil.WriteToMemory(isaacProcessHandle, reloadAddress, new byte[] { 1 });
        }
        private byte GetNumPlayers()
        {
            int address1 = MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET);
            int address2 = MemoryUtil.CalculateAddress(isaacProcessHandle, ImageBaseAdress + GAME_OFFSET, PLAYER_OFFSET + 4);
            int value1 = MemoryUtil.ReadInt32FromMemory(isaacProcessHandle, address1);
            int value2 = MemoryUtil.ReadInt32FromMemory(isaacProcessHandle, address2);
            return (byte)((value2 - value1) / 4);
        }
        private byte[] GetReloadAssembly(int pMem)
        {
            AssemblyCode assembly = new(pMem);
            //判断标志
            assembly.cmp_byte_ptr(pMem + 0xC5, 0);
            assembly.je("originalcode");
            assembly.mov_byte_ptr(pMem + 0xC5, 0);
            //传入this
            assembly.mov_ecx(ImageBaseAdress + 0x7FD680);
            assembly.lea_ecx_ecx(0x00029FD8);
            assembly.push_esi();
            assembly.move_esi(ImageBaseAdress + 0x7FD674);
            assembly.push_edi();
            assembly.push(ImageBaseAdress + 0x74F6F4);
            assembly.push((byte)0);
            assembly.mov_edi_ecx();
            assembly.call(ImageBaseAdress + 0x55E330);//输出
            assembly.add_esp(8);
            assembly.mov_ecx_esi();
            assembly.call(ImageBaseAdress + 0x40AE00);//卸载lua环境
            assembly.movzx_eax_byte_ptr_esi(0x1C);
            assembly.mov_ecx_esi();
            assembly.push_eax();
            assembly.call(ImageBaseAdress + 0x3FCB00);//加载lua配置
            assembly.mov_ecx_edi();
            assembly.call(ImageBaseAdress + 0x4702F0);//移除mod列表
            assembly.mov_ecx_edi();
            assembly.call(ImageBaseAdress + 0x470B40);//重建mod列表
            assembly.mov_ecx_edi();
            assembly.call(ImageBaseAdress + 0x46F2B0);//重载着色器
            assembly.call(ImageBaseAdress + 0x4AF200);//重新加载图形
            assembly.mov_ecx_edi();
            assembly.call(ImageBaseAdress + 0x46DAE0);//加载lua环境
            assembly.cmp_dword_ptr_byte(ImageBaseAdress + 0x7FD688, 0);
            assembly.je("pd");
            assembly.mov_ecx(ImageBaseAdress + GAME_OFFSET);
            assembly.test_ecx_ecx();
            assembly.je("pe");
            assembly.add_ecx(0x0010203C);
            assembly.call(ImageBaseAdress + 0x517F20);
            assembly.Flag("pe");
            assembly.call(ImageBaseAdress + 0x92A0);
            assembly.call(ImageBaseAdress + 0x4AFA70);
            assembly.move_esi(ImageBaseAdress + 0X7FD688);
            assembly.lea_ecx_esi(0x00101C00);
            assembly.call(ImageBaseAdress + 0x4A3F30);
            assembly.lea_ecx_esi(0x00102E80);
            assembly.call(ImageBaseAdress + 0x4AB4E0);
            assembly.Flag("pd");
            assembly.pop_edi();
            assembly.pop_esi();
            assembly.Flag("originalcode");
            assembly.call(ImageBaseAdress + 0x4B0010);
            assembly.jmp(ImageBaseAdress + 0x48BDFA);
            return assembly.GetBytes();
        }
        private void InjectCode()
        {
            int pMem;
            AssemblyCode assembly = new(ImageBaseAdress + INJECTION_POINT_OFFSET);
            assembly.call(ImageBaseAdress + 0x4B0010);
            byte[] byteArray = MemoryUtil.ReadFromMemory(isaacProcessHandle, ImageBaseAdress + INJECTION_POINT_OFFSET, 5);
            if (byteArray.SequenceEqual(assembly.GetBytes()))
            {
                pMem = (int)WinAPIUtil.VirtualAllocEx(isaacProcessHandle, 0, 256, WinAPIUtil.AllocationType.COMMIT | WinAPIUtil.AllocationType.RESERVE, WinAPIUtil.MemoryProtection.EXECUTE_READWRITE);
                if (pMem != 0)
                {
                    byteArray = GetReloadAssembly(pMem);
                    MemoryUtil.WriteToMemory(isaacProcessHandle, pMem, byteArray);

                    assembly = new(ImageBaseAdress + INJECTION_POINT_OFFSET);
                    assembly.jmp(pMem);
                    MemoryUtil.WriteToMemory(isaacProcessHandle, ImageBaseAdress + INJECTION_POINT_OFFSET, assembly.GetBytes());
                }
            }
            else
            {
                pMem = ImageBaseAdress + INJECTION_POINT_OFFSET + BitConverter.ToInt32(byteArray, 1) + 5;
                byteArray = GetReloadAssembly(pMem);
            }
            reloadAddress = pMem + byteArray.Length;
            string s = $"注入重载lua环境代码成功：{Environment.NewLine}\t内存地址：\t0x{pMem.ToString("X")}{Environment.NewLine}\t开关地址：\t0x{reloadAddress.ToString("X")} （1字节）{Environment.NewLine}\t注入点：\t0x{(ImageBaseAdress + INJECTION_POINT_OFFSET).ToString("X")}";
            Callback(CallbackType.MESSAGE, s);
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
                    DataType dataType = (DataType)message[1];
                    switch (dataType)
                    {
                        case DataType.DEBUG_FLAG:
                            int debugFlag = BitConverter.ToInt32(message, 2);
                            stringBuilder.Append($"debugFlag {debugFlag}");
                            break;
                        case DataType.PLAYER_DATA:
                            byte playerId = message[2];
                            stringBuilder.Append($"player {playerId} ");
                            PlayerDataType playerDataType = (PlayerDataType)message[3];
                            switch (playerDataType)
                            {
                                case PlayerDataType.CAN_SHOOT:
                                    byte canShoot = message[4];
                                    stringBuilder.Append($"canShoot {canShoot} ");
                                    break;
                                case PlayerDataType.ACTIVE_DATA:
                                    byte activeSlot = message[4];
                                    stringBuilder.Append($"active {activeSlot} ");
                                    ActiveDataType activeDataType = (ActiveDataType)message[5];
                                    switch (activeDataType)
                                    {
                                        case ActiveDataType.VAR_DATA:
                                            int varData = BitConverter.ToInt32(message, 6);
                                            stringBuilder.Append($"varData {varData} ");
                                            break;
                                        case ActiveDataType.PARTIAL_CHARGE:
                                            float partialCharge = BitConverter.ToSingle(message, 6);
                                            stringBuilder.Append($"partialCharge {partialCharge} ");
                                            break;
                                        case ActiveDataType.SUB_CHARGE:
                                            int subCharge = BitConverter.ToInt32(message, 6);
                                            stringBuilder.Append($"subCharge {subCharge} ");
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
