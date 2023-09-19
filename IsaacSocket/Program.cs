using IsaacSocket.Utils;
using System.Diagnostics;
using System.Reflection;
using System.Text.Json;

namespace IsaacSocket;

static class Program
{
    /// <summary>
    ///  The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main()
    {
        using Mutex mutex = new(true, "Isaac Socket", out bool createdNew);
        if (createdNew)
        {
            // 判断是否处于调试模式，是的话启用命令行窗口
            if (Debugger.IsAttached)
            {
                WinAPIUtil.AllocConsole();
            }
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            _ = CheckUpdate();
            ApplicationConfiguration.Initialize();
            Application.Run(new Form1());
        }
    }

    static async Task CheckUpdate()
    {
        using HttpClient client = new();
        client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.31");
        try
        {
            string json = await client.GetStringAsync("https://api.github.com/repos/LanbingIce/IsaacSocket-Utility/releases/latest");
            using JsonDocument doc = JsonDocument.Parse(json);
            JsonElement root = doc.RootElement;

            string tagName = root.GetProperty("tag_name").GetString() ?? "v1.0";
            string versionString = tagName[1..];
            string[] parts = versionString.Split('.');
            for (int i = 0; i < 4 - parts.Length; i++)
            {
                versionString += ".0";
            }

            Version? clientVersion = Assembly.GetEntryAssembly()?.GetName().Version;
            Version serverVersion = new(versionString);

            if (serverVersion.CompareTo(clientVersion) > 0)
            {
                DialogResult result = MessageBox.Show($"{tagName} 更新说明：{Environment.NewLine}{Environment.NewLine}{root.GetProperty("body").GetString() ?? ""}{Environment.NewLine}{Environment.NewLine}是否要现在下载？", $"软件有更新版本：{ tagName}", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    Process.Start("explorer.exe", root.GetProperty("assets")[0].GetProperty("browser_download_url").GetString() ?? "https://github.com/LanbingIce/IsaacSocket-Utility/releases/latest");
                }
            }
        }
        catch (Exception e)
        {
            await Console.Out.WriteLineAsync(e.Message);
        }
    }
}
