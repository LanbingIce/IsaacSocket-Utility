using System.Collections.Concurrent;
using System.Reflection;
using System.Text.Json;

namespace IsaacSocket.Forms;

public partial class Form1 : Form
{
    private readonly UpdateForm updateForm;
    private readonly ConcurrentQueue<string> logQueue1, logQueue2, logQueue3, logQueue4;
    private int size;
    private readonly Main main;
    public Form1()
    {
        InitializeComponent();
        Version? version = Assembly.GetEntryAssembly()?.GetName().Version;
        string versionString = $"{version?.Major}.{version?.Minor}";
        Text = $"IsaacSocket ���ӳ��� v{versionString}";
        logQueue1 = new();
        logQueue2 = new();
        logQueue3 = new();
        logQueue4 = new();
        size = 1024;
        updateForm = new();
        main = new(size, Callback);
    }
    private void UpdateLog(ConcurrentQueue<string> logQueue, RichTextBox logTextBox, string logText)
    {
        if (logText != "")
        {
            logQueue.Enqueue($"- {DateTime.Now:HH:mm:ss} {logText}");
            if (logQueue.Count > 100)
            {
                logQueue.TryDequeue(out _);
            }
        }
        if (Visible)
        {
            BeginInvoke(() =>
            {
                logTextBox.Text = string.Join(Environment.NewLine, logQueue);
                if (logTextBox.Text.Length > 0)
                {
                    logTextBox.SelectionStart = logTextBox.Text.Length - 1;
                    logTextBox.ScrollToCaret();
                }
            });
        }
    }

    private void Callback(params object[] args)
    {
        if (IsDisposed)
        {
            return;
        }
        switch (args[0])
        {
            case Main.CallbackType.RECEIVE:
                UpdateLog(logQueue1, richTextBox1, args[1] + Environment.NewLine);
                break;
            case Main.CallbackType.SEND:
                UpdateLog(logQueue2, richTextBox2, args[1] + Environment.NewLine);
                break;
            case Main.CallbackType.MESSAGE:
                UpdateLog(logQueue3, richTextBox3, args[1] + Environment.NewLine);
                break;
            case Main.CallbackType.HEART_BEAT:
                UpdateLog(logQueue4, richTextBox4, (string)args[1]);
                break;
        }
    }
    private void SetDataSpaceSizeToolStripMenuItem_Click(object sender, EventArgs e)
    {
        string userInput = Microsoft.VisualBasic.Interaction.InputBox("�������µĽ�������С����Χ�� 64 ~ 4194304��", "������", size.ToString());

        if (!string.IsNullOrEmpty(userInput))
        {
            if (int.TryParse(userInput, out size))
            {
                main.SetDataSpaceSize(size);
            }
            else
            {
                MessageBox.Show("��Ч�����룬������һ����Ч�����֡�");
            }
        }
    }
    private void Form1_Load(object sender, EventArgs e)
    {
        _ = CheckUpdate();
        main.Start();
    }
    private void ShowMainWindowToolStripMenuItem_Click(object sender, EventArgs e)
    {
        TopMost = true;
        Visible = true;
        WindowState = FormWindowState.Normal;
        TopMost = false;

        UpdateLog(logQueue1, richTextBox1, "");
        UpdateLog(logQueue2, richTextBox2, "");
        UpdateLog(logQueue3, richTextBox3, "");
        UpdateLog(logQueue4, richTextBox4, "");
    }
    private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
    {
        Close();
    }
    private void HideMainWindowToolStripMenuItem_Click(object sender, EventArgs e)
    {
        WindowState = FormWindowState.Minimized;
    }
    private void Form1_SizeChanged(object sender, EventArgs e)
    {
        if (WindowState == FormWindowState.Minimized)
        {
            // ����֪ͨ��Ϣ�ı�
            notifyIcon1.BalloonTipText = "Ҫ�ٴδ򿪴��ڣ�����������˫������ͼ��";
            Visible = false;
            // ��ʾ֪ͨ��Ϣ
            notifyIcon1.ShowBalloonTip(3000); // 3000��ʾ֪ͨ��Ϣ��ʾ��ʱ�䣨�Ժ���Ϊ��λ��
        }
    }
    private void Form1_FormClosing(object sender, FormClosingEventArgs e)
    {
        if (e.CloseReason == CloseReason.UserClosing)
        {
            updateForm.TopMost = false;
            if (MessageBox.Show("ȷ��Ҫ�˳�������", "�˳�����", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
            {
                e.Cancel = true;
                updateForm.TopMost = true;
            }
        }
    }
    private void NotifyIcon1_DoubleClick(object sender, EventArgs e)
    {
        showMainWindowToolStripMenuItem.PerformClick();
    }
    private async Task CheckUpdate()
    {
        File.Delete("update.bat");
        using HttpClient client = new();
        client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.31");
        try
        {
            string json = await client.GetStringAsync("https://api.github.com/repos/LanbingIce/IsaacSocket-Utility/releases/latest");
            using JsonDocument doc = JsonDocument.Parse(json);
            JsonElement root = doc.RootElement;
            string tagName = root.GetProperty("tag_name").GetString() ?? "v1.0";
            // tagName = "v9.9";
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
                updateForm.body = root.GetProperty("body").GetString() ?? "";
                updateForm.tagName = tagName;
                updateForm.downloadLink = root.GetProperty("assets")[0].GetProperty("browser_download_url").GetString() ?? "";
                updateForm.Show();
            }
        }
        catch (Exception e)
        {
            await Console.Out.WriteLineAsync(e.Message);
        }
    }
}
