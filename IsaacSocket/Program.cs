using IsaacSocket.Forms;
using IsaacSocket.Utils;
using System.Diagnostics;

namespace IsaacSocket;

static class Program
{
    /// <summary>
    ///  The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main(string[] args)
    {
        using Mutex mutex = new(true, "Isaac Socket", out bool createdNew);
        if (createdNew)
        {
            // �ж��Ƿ��ڵ���ģʽ���ǵĻ����������д���
            if (Debugger.IsAttached)
            {
                WinAPIUtil.AllocConsole();
            }
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            bool silentStart = args.Contains("-silent");
            Application.Run(new Form1(silentStart));
        }
    }
}
