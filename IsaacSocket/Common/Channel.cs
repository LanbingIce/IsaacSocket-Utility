namespace IsaacSocket.Common
{
    internal enum Channel
    {
        //心跳包
        HEARTBEAT = 0,
        // WebSocket
        WEB_SOCKET_CLIENT = 1,
        //HTTP
        HTTP_CLIENT = 3
    }
}
