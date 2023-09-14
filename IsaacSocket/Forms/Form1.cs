using System.Reflection;
using System.Text;
namespace IsaacSocket;

public partial class Form1 : Form
{
    private readonly StringBuilder stringBuilder1, stringBuilder2, stringBuilder3, stringBuilder4;
    private int size;
    private readonly Main main;
    public Form1()
    {
        InitializeComponent();
        Version? version = Assembly.GetEntryAssembly()?.GetName().Version;
        string versionString = $"{version?.Major}.{version?.Minor}";
        Text = $"IsaacSocket 连接程序 v{versionString}";
        stringBuilder1 = new();
        stringBuilder2 = new();
        stringBuilder3 = new();
        stringBuilder4 = new();
        size = 1024;
        main = new(size, Callback);
    }
    private void UpdateStringBuilder(StringBuilder stringBuilder, string text)
    {
        stringBuilder.Append($"\n- {DateTime.Now:HH:mm:ss} {text}");
    }
    private void UpdateTextBox(RichTextBox richTextBox, string text)
    {
        richTextBox.AppendText($"\n- {DateTime.Now:HH:mm:ss} {text}");
        richTextBox.ScrollToCaret();
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
                if (Visible)
                {
                    richTextBox1.BeginInvoke(UpdateTextBox, richTextBox1, args[1] + "\n");
                }
                else
                {
                    UpdateStringBuilder(stringBuilder1, args[1] + "\n");

                }
                break;
            case Main.CallbackType.SEND:
                if (Visible)
                {
                    richTextBox2.BeginInvoke(UpdateTextBox, richTextBox2, args[1] + "\n");
                }
                else
                {
                    UpdateStringBuilder(stringBuilder2, args[1] + "\n");

                }
                break;
            case Main.CallbackType.MESSAGE:
                if (Visible)
                {
                    richTextBox3.BeginInvoke(UpdateTextBox, richTextBox3, args[1] + "\n");
                }
                else
                {
                    UpdateStringBuilder(stringBuilder3, args[1] + "\n");
                }
                break;
            case Main.CallbackType.HEART_BEAT:

                if (Visible)
                {
                    richTextBox4.BeginInvoke(UpdateTextBox, richTextBox4, args[1]);
                }
                else
                {
                    UpdateStringBuilder(stringBuilder4, (string)args[1]);
                }
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

        richTextBox1.AppendText(stringBuilder1.ToString());
        richTextBox2.AppendText(stringBuilder2.ToString());
        richTextBox3.AppendText(stringBuilder3.ToString());
        richTextBox4.AppendText(stringBuilder4.ToString());
        richTextBox1.ScrollToCaret();
        richTextBox2.ScrollToCaret();
        richTextBox3.ScrollToCaret();
        richTextBox4.ScrollToCaret();
        stringBuilder1.Clear();
        stringBuilder2.Clear();
        stringBuilder3.Clear();
        stringBuilder4.Clear();
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
            stringBuilder1.Append(richTextBox1.Text);
            stringBuilder2.Append(richTextBox2.Text);
            stringBuilder3.Append(richTextBox3.Text);
            stringBuilder4.Append(richTextBox4.Text);
            richTextBox1.Clear();
            richTextBox2.Clear();
            richTextBox3.Clear();
            richTextBox4.Clear();
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
