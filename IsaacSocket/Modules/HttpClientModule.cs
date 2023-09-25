using IsaacSocket.Common;
using System.Text;
using System.Text.Json;

namespace IsaacSocket.Modules;
internal class HttpClientModule : Module
{
    private enum ActionType
    {
        RESPONSE = 0,
        FAULTED = 1,
        GET_REQUEST = 2,
        POST_REQUEST = 3
    }
    private CancellationTokenSource cancellationTokenSource;
    private readonly HttpClient client;
    private int taskCounter;
    public HttpClientModule(Channel channel, CallbackDelegate callback) : base(channel, callback)
    {
        cancellationTokenSource = new();
        client = new();
    }
    private static ActionType DeserializeResponse(byte[] message, out ushort id, out ushort statusCode, out string reasonPhrase, out Dictionary<string, string> headers, out byte[] body)
    {
        //0：action
        ActionType action = (ActionType)message[0];
        //1，2：id
        id = BitConverter.ToUInt16(message, 1);
        //3，4：statusCode
        statusCode = BitConverter.ToUInt16(message, 3);
        //5：reasonPhraseSize
        byte reasonPhraseSize = message[5];
        //6，7：headersSize
        ushort headersSize = BitConverter.ToUInt16(message, 6);
        int offset = 8;
        //reasonPhrase
        reasonPhrase = Encoding.UTF8.GetString(message[offset..(offset + reasonPhraseSize)]);
        offset += reasonPhraseSize;
        //headers
        headers = JsonSerializer.Deserialize<Dictionary<string, string>>(Encoding.UTF8.GetString(message[offset..(offset + headersSize)])) ?? new();
        offset += headersSize;
        // body
        body = message[offset..];
        return action;
    }
    private static ActionType DeserializeRequest(byte[] message, out ushort id, out string url, out Dictionary<string, string> headers, out byte[] body)
    {
        //0：action
        ActionType action = (ActionType)message[0];
        //1，2：id
        id = BitConverter.ToUInt16(message, 1);
        //3，4：urlSize
        ushort urlSize = BitConverter.ToUInt16(message, 3);
        //5，6：headersSize
        ushort headersSize = BitConverter.ToUInt16(message, 5);
        int offset = 7;
        //url
        url = Encoding.UTF8.GetString(message[offset..(offset + urlSize)]);
        offset += urlSize;
        //headers
        headers = JsonSerializer.Deserialize<Dictionary<string, string>>(Encoding.UTF8.GetString(message[offset..(offset + headersSize)])) ?? new();
        offset += headersSize;
        //body
        body = message[offset..];
        return action;
    }
    private static byte[] SerializeResponse(ushort id, HttpResponseMessage response)
    {
        string reasonPhrase = response.ReasonPhrase ?? "";
        Dictionary<string, string> headers = new();
        foreach (var header in response.Headers)
        {
            headers[header.Key] = string.Join(",", header.Value);
        }
        foreach (var header in response.Content.Headers)
        {
            headers[header.Key] = string.Join(",", header.Value);
        }
        string headersString = JsonSerializer.Serialize(headers);
        List<byte> bufferList = new()
            {
                // 0 ：action
                (byte)ActionType.RESPONSE
            };
        //1，2：id
        bufferList.AddRange(BitConverter.GetBytes(id));
        //3，4：statusCode
        bufferList.AddRange(BitConverter.GetBytes((ushort)response.StatusCode));
        //5：reasonPhraseSize
        bufferList.Add((byte)Encoding.UTF8.GetByteCount(reasonPhrase));
        //6，7：headersSize
        bufferList.AddRange(BitConverter.GetBytes((ushort)Encoding.UTF8.GetByteCount(headersString)));
        // reasonPhrase
        bufferList.AddRange(Encoding.UTF8.GetBytes(reasonPhrase));
        // headers
        bufferList.AddRange(Encoding.UTF8.GetBytes(headersString));
        // body
        bufferList.AddRange(response.Content.ReadAsByteArrayAsync().Result);
        return bufferList.ToArray();
    }
    private static ActionType DeserializeFaulted(byte[] message, out ushort id, out string reason)
    {
        //0：action
        ActionType action = (ActionType)message[0];
        //1，2：id
        id = BitConverter.ToUInt16(message, 1);
        // reason
        reason = Encoding.UTF8.GetString(message[3..]);
        return action;
    }
    private static byte[] SerializeFaulted(ushort id, string reason)
    {
        List<byte> bufferList = new()
            {
                // 0：action
                (byte)ActionType.FAULTED
            };
        // 1，2：id
        bufferList.AddRange(BitConverter.GetBytes(id));
        // reason
        bufferList.AddRange(Encoding.UTF8.GetBytes(reason));
        return bufferList.ToArray();
    }
    private static string SerializeHeaders(Dictionary<string, string> headers)
    {
        StringBuilder stringBuilder = new();
        foreach (var kvp in headers.OrderBy(x => x.Key).ToDictionary(x => x.Key, x => x.Value))
        {
            stringBuilder.AppendLine($"\t{kvp.Key} :\t\t{kvp.Value}");
        }
        return stringBuilder.ToString();
    }
    internal override void Connected()
    {
    }
    internal override void DisConnected()
    {
        cancellationTokenSource.Cancel();
        //要等待所有任务都结束之后才可以进行下一步
        while (taskCounter != 0)
        {
            Thread.Sleep(1);
        }
        cancellationTokenSource = new();
    }
    internal override void Exited()
    {
        client.Dispose();
    }
    internal override string MemoryMessageToString(byte[] message)
    {
        StringBuilder stringBuilder = new();
        ActionType action = (ActionType)message[0];
        ushort id = BitConverter.ToUInt16(message, 1);
        stringBuilder.AppendLine($"任务id :\t\t{id}");
        switch (action)
        {
            case ActionType.GET_REQUEST:
            case ActionType.POST_REQUEST:
                stringBuilder.AppendLine("消息类别 :\tHTTP 请求");
                DeserializeRequest(message, out _, out string url, out Dictionary<string, string> headers, out byte[] body);
                if (action == ActionType.GET_REQUEST)
                {
                    stringBuilder.AppendLine("请求方法 :\tGET");
                }
                else
                {
                    stringBuilder.AppendLine("请求方法 :\tPOST");
                }
                stringBuilder.AppendLine($"请求URL :\t{url}");
                stringBuilder.AppendLine("请求标头 :");
                stringBuilder.Append(SerializeHeaders(headers));
                if (body.Length != 0)
                {
                    stringBuilder.AppendLine("请求正文 :");
                    stringBuilder.AppendLine(Encoding.UTF8.GetString(body));
                }
                break;
            case ActionType.RESPONSE:
                stringBuilder.AppendLine("消息类别 :\tHTTP 响应");
                DeserializeResponse(message, out _, out ushort statusCode, out string reasonPhrase, out headers, out body);
                stringBuilder.AppendLine($"状态代码 :\t{statusCode} {reasonPhrase}");
                stringBuilder.AppendLine("响应标头 :");
                stringBuilder.Append(SerializeHeaders(headers));
                stringBuilder.AppendLine($"响应正文 :");
                stringBuilder.AppendLine(Encoding.UTF8.GetString(body));
                break;
            case ActionType.FAULTED:
                stringBuilder.AppendLine("消息类别 :\t任务失败");
                DeserializeFaulted(message, out _, out string reason);
                stringBuilder.AppendLine($"失败原因 :\t{reason}");
                break;
        }
        return stringBuilder.ToString();
    }
    internal override void ReceiveMemoryMessage(byte[] message)
    {
        HttpRequestMessage request;
        ActionType action = DeserializeRequest(message, out ushort id, out string url, out Dictionary<string, string> headers, out byte[] body);
        try
        {
            request = new()
            {
                RequestUri = new(url)
            };
            foreach (var kvp in headers)
            {
                request.Headers.Add(kvp.Key, kvp.Value);
            }
        }
        catch (Exception e)
        {
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, SerializeFaulted(id, e.Message));
            return;
        }
        switch (action)
        {
            case ActionType.GET_REQUEST:
                request.Method = HttpMethod.Get;
                Interlocked.Increment(ref taskCounter);
                client.SendAsync(request, cancellationTokenSource.Token).ContinueWith(task =>
                 {
                     if (task.IsCompletedSuccessfully)
                     {
                         Callback(CallbackType.MEMORY_MESSAGE_GENERATED, SerializeResponse(id, task.Result));
                     }
                     else
                     {
                         Callback(CallbackType.MEMORY_MESSAGE_GENERATED, SerializeFaulted(id, task.Exception?.Message ?? ""));
                     }
                     Interlocked.Decrement(ref taskCounter);
                 });
                break;
        }
    }
}