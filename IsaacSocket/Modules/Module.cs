

using IsaacSocket.Common;

namespace IsaacSocket.Modules
{
    internal abstract class Module
    {
        private readonly Channel channel;
        private readonly CallbackDelegate callback;


        internal enum CallbackType
        {

            MEMORY_MESSAGE_GENERATED = 0,
            MESSAGE = 1

        }
        internal abstract string MemoryMessageToString(byte[] message);
        internal abstract void ReceiveMemoryMessage(byte[] message);
        protected void Callback(CallbackType callbackType, params object[] args)
        {
            callback?.Invoke(callbackType, channel, args[0]);
        }
        internal abstract void Connected();
        internal abstract void Disconnected();
        internal abstract void Update();
        internal abstract void Exited();

        internal Module(Channel channel, CallbackDelegate callback)
        {
            this.channel = channel;
            this.callback = callback;
        }

    }
}
