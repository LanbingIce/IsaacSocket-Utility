using IsaacSocket.Common;
using IsaacSocket.Utils;
using System.Text;

namespace IsaacSocket.Modules
{
    internal class ClipboardModule : Module
    {
        private class VirtualForm : Form
        {
            private static readonly int WM_CLIPBOARDUPDATE = 0x031D;
            private readonly CallbackDelegate callback;
            private string clipboardText;
            internal VirtualForm(CallbackDelegate callback)
            {
                clipboardText = Clipboard.GetText();
                this.callback = callback;
                WindowState=FormWindowState.Minimized;
                Show();
                Visible = false;
            }

            internal void SendClipboardText()
            {
                callback(clipboardText);
            }
            protected override void DefWndProc(ref Message m)
            {
                base.DefWndProc(ref m);
                if (m.Msg == WM_CLIPBOARDUPDATE)
                {
                    string newText = Clipboard.GetText();
                    if (newText != clipboardText)
                    {
                        clipboardText = newText;
                        SendClipboardText();
                    }
                }
            }
        }

        private readonly VirtualForm virtualForm;

        internal ClipboardModule(Channel channel, CallbackDelegate callback) : base(channel, callback)
        {
            virtualForm = new VirtualForm(VirtualFormCallBack);
            WinAPIUtil.AddClipboardFormatListener(virtualForm.Handle);
        }

        private enum ActionType
        {
            CLIPBOARD_UPDATED = 0,
            SET_CLIPBOARD = 1
        }

        internal void VirtualFormCallBack(params object[] args)
        {
            List<byte> buffer = new() { (byte)ActionType.CLIPBOARD_UPDATED };
            buffer.AddRange(Encoding.UTF8.GetBytes((string)args[0]));
            Callback(CallbackType.MEMORY_MESSAGE_GENERATED, buffer.ToArray());
        }

        internal override void ReceiveMemoryMessage(byte[] message)
        {
            ActionType messageType = (ActionType)message[0];
            switch (messageType)
            {
                case ActionType.SET_CLIPBOARD:
                    string text = Encoding.UTF8.GetString(message[1..]);
                    virtualForm.Invoke(() =>
                    {
                        if (text == "")
                        {
                            Clipboard.Clear();
                        }
                        else
                        {
                            Clipboard.SetText(text);
                        }
                    });
                    break;
            }

        }

        internal override void Connected()
        {
            virtualForm.SendClipboardText();

        }

        internal override void DisConnected()
        {

        }


        internal override string MemoryMessageToString(byte[] message)
        {
            StringBuilder stringBuilder = new();
            string text = Encoding.UTF8.GetString(message[1..]);
            ActionType messageType = (ActionType)message[0];
            switch (messageType)
            {
                case ActionType.CLIPBOARD_UPDATED:
                    if (text == "")
                    {
                        stringBuilder.Append($"剪贴板内容变为空");
                    }
                    else
                    {
                        stringBuilder.Append($"剪贴板内容变为：{text}");
                    }
                    break;

                case ActionType.SET_CLIPBOARD:
                    if (text == "")
                    {
                        stringBuilder.Append($"清空剪贴板");
                    }
                    else
                    {
                        stringBuilder.Append($"置剪贴板文本：{text}");
                    }
                    break;
            }
            return stringBuilder.ToString();
        }

        internal override void Exited()
        {
            WinAPIUtil.RemoveClipboardFormatListener(virtualForm.Handle);

        }
    }
}