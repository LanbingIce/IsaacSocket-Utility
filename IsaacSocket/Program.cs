using IsaacSocket.Forms;
using IsaacSocket.Utils;

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
            if (args.Contains("-console"))
            {
                WinAPIUtil.AllocConsole();
            }
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Form1(args));
        }
    }
}
