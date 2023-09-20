using System.Reflection;

namespace IsaacSocket;

public partial class Form1 : Form
{
    private readonly Queue<string> logQueue1, logQueue2, logQueue3, logQueue4;
    private int size;
    private readonly Main main;
    public Form1()
    {
        InitializeComponent();
        Version? version = Assembly.GetEntryAssembly()?.GetName().Version;
        string versionString = $"{version?.Major}.{version?.Minor}";
        Text = $"IsaacSocket 连接程序 v{versionString}";
        logQueue1 = new();
        logQueue2 = new();
        logQueue3 = new();
        logQueue4 = new();
        size = 1024;
        main = new(size, Callback);
    }
    private void UpdateLog(Queue<string> logQueue, RichTextBox logTextBox, string logText)
    {
        if (logText != "")
        {
            logQueue.Enqueue($"- {DateTime.Now:HH:mm:ss} {logText}");
            if (logQueue.Count > 100)
            {
                logQueue.Dequeue();
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
        string userInput = Microsoft.VisualBasic.Interaction.InputBox("请输入新的交换区大小，范围： 64 ~ 4194304：", "请输入", size.ToString());

        if (!string.IsNullOrEmpty(userInput))
        {
            if (int.TryParse(userInput, out size))
            {
                main.SetDataSpaceSize(size);
            }
            else
            {
                MessageBox.Show("无效的输入，请输入一个有效的数字。");
            }
        }
    }
    private void Form1_Load(object sender, EventArgs e)
    {
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
            // 设置通知消息文本
            notifyIcon1.BalloonTipText = "要再次打开窗口，请在托盘区双击托盘图标";
            Visible = false;
            // 显示通知消息
            notifyIcon1.ShowBalloonTip(3000); // 3000表示通知消息显示的时间（以毫秒为单位）
        }
    }
    private void Form1_FormClosing(object sender, FormClosingEventArgs e)
    {
        DialogResult result = MessageBox.Show("确定要退出程序吗？", "退出程序", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
        if (result == DialogResult.No)
        {
            e.Cancel = true;
        }
    }
    private void NotifyIcon1_DoubleClick(object sender, EventArgs e)
    {
        showMainWindowToolStripMenuItem.PerformClick();
    }
}
