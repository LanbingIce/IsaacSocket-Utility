using WebSocketSharp;
using System.Text;
using IsaacSocket.Common;



namespace IsaacSocket.Modules
{
    internal class WebsocketClientModule : Module
    {
        private WebSocket[] clientWebSockets;
        internal WebsocketClientModule(Channel channel, CallbackDelegate callback) : base(channel, callback)
        {
            clientWebSockets = new WebSocket[256];
        }



        // 枚举类型定义
        //
        // WebSocket消息类型

        private enum ActionType
        {
            //连接
            CONNECT = 0,
            //关闭
            CLOSE = 1,
            //连接成功
            ON_OPEN = 2,
            //消息
            ON_MESSAGE = 3,
            //已关闭
            ON_CLOSED = 4,
            //出现错误
            ON_ERROR = 5
        }
        private enum MessageType
        {
            TEXT = 0,
            BINARY = 1
        }





        internal override void ReceiveMemoryMessage(byte[] message)
        {
            //0:ActionType 1:id 
            ActionType actionType = (ActionType)message[0];
            byte id = message[1];
            try
            {
                if (id == 0)
                {
                    throw new Exception("Too many connections");
                }
                WebSocket ws = clientWebSockets[id];
                switch (actionType)
                {
                    case ActionType.CONNECT:
                        string url = Encoding.UTF8.GetString(message[2..]);

                        ws = new(url);
                        clientWebSockets[id] = ws;
                        ws.OnOpen += (sender, e) => OnOpen(id);
                        ws.OnMessage += (sender, e) => OnMessage(id, e);
                        ws.OnClose += (sender, e) => OnClose(id, e);
                        ws.OnError += (sender, e) => OnError(id, e.Message);
                        Task.Run(ws.Connect);
                        break;
                    case ActionType.CLOSE:
                        Task.Run(() => clientWebSockets[id].Close(BitConverter.ToUInt16(message, 2), Encoding.UTF8.GetString(message[4..])));
                        break;
                    case ActionType.ON_MESSAGE:
                        MessageType messageType = (MessageType)message[2];
                        if (messageType == MessageType.BINARY)
                        {
                            Task.Run(() => clientWebSockets[id].Send(message[3..]));
                        }
                        else
                        {
                            Task.Run(() => clientWebSockets[id].Send(Encoding.UTF8.GetString(message[3..])));
                        }
                        break;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                OnError(id, e.Message);
            }
        }

        private void OnMessage(byte id, MessageEventArgs e)
        {
            List<byte> bufferList = new() { (byte)ActionType.ON_MESSAGE, id };
            if (e.IsText)
            {
                bufferList.Add((byte)MessageType.TEXT);
            }
            else if (e.IsBinary)
            {
                bufferList.Add((byte)MessageType.BINARY);
            }
            else
            {
                return;
            }
            bufferList.AddRange(e.RawData);
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, bufferList.ToArray());
        }
        private void OnError(byte id, string errorMessage)
        {
            List<byte> bufferList = new() { (byte)ActionType.ON_ERROR, id };
            bufferList.AddRange(Encoding.UTF8.GetBytes(errorMessage));
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, bufferList.ToArray());
        }
        private void OnClose(byte id, CloseEventArgs e)
        {
            List<byte> bufferList = new() { (byte)ActionType.ON_CLOSED, id };
            bufferList.AddRange(BitConverter.GetBytes(e.Code));
            bufferList.AddRange(Encoding.UTF8.GetBytes(e.Reason));
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, bufferList.ToArray());
        }
        private void OnOpen(byte id)
        {
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, new byte[] { (byte)ActionType.ON_OPEN, id });
        }


        internal override void Connected()
        {
        }
        internal override void DisConnected()
        {
            WebSocket[] temp = clientWebSockets;
            clientWebSockets = new WebSocket[256];
            Task.Run(() =>
            {
                for (byte i = 255; i > 0; i--)
                {
                    temp[i]?.Close();
                }
            });
        }


        internal override string MemoryMessageToString(byte[] message)
        {

            //0:ActionType 1:id 

            StringBuilder stringBuilder = new();
            ActionType actionType = (ActionType)message[0];

            switch (actionType)
            {
                case ActionType.ON_OPEN:
                    stringBuilder.Append($"连接 {message[1]} 已成功连接");
                    break;
                case ActionType.CONNECT:
                    stringBuilder.Append($"连接 {message[1]} 请求连接，地址： {Encoding.UTF8.GetString(message[2..])}");
                    break;
                case ActionType.CLOSE:
                    stringBuilder.Append($"连接 {message[1]} 请求关闭 状态码：{BitConverter.ToUInt16(message, 2)} 关闭描述：{Encoding.UTF8.GetString(message[4..])}");
                    break;
                case ActionType.ON_MESSAGE:
                    if ((MessageType)message[2] == MessageType.TEXT)
                    {
                        stringBuilder.Append($"连接 {message[1]} 文本消息：{Encoding.UTF8.GetString(message[3..])}");
                    }
                    else
                    {
                        stringBuilder.Append($"连接 {message[1]} 二进制消息[{message[3..].Length}]：{BitConverter.ToString(message[3..])}");

                    }
                    break;
                case ActionType.ON_CLOSED:
                    stringBuilder.Append($"连接 {message[1]} 已关闭，状态码：{BitConverter.ToInt16(message, 2)} 关闭描述：{Encoding.UTF8.GetString(message[4..])}");
                    break;
                case ActionType.ON_ERROR:
                    stringBuilder.Append($"连接 {message[1]} 出现错误并关闭，错误文本：{Encoding.UTF8.GetString(message[2..])}");
                    break;


            }
            return stringBuilder.ToString();
        }

        internal override void Exited()
        {
        }
    }

}



