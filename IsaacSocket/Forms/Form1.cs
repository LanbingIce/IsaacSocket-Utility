namespace IsaacSocket;

public partial class Form1 : Form
{
    private int size;
    internal Main main;
    public Form1()
    {
        InitializeComponent();
        size = 1024;
        main = new(size, Callback);
    }
    private void UpdateTextBox(RichTextBox richTextBox, string text)
    {
        DateTime currentTime = DateTime.Now;

        // 提取时分秒部分
        int hours = currentTime.Hour;
        int minutes = currentTime.Minute;
        int seconds = currentTime.Second;

        richTextBox.AppendText($"\n- {hours:D2}:{minutes:D2}:{seconds:D2} {text}");
        richTextBox.ScrollToCaret();
    }
    private void Callback(params object[] args)
    {

        switch (args[0])
        {
            case Main.CallbackType.RECEIVE:

                if (!richTextBox1.IsDisposed)
                {
                    richTextBox1.BeginInvoke(UpdateTextBox, richTextBox1, args[1] + "\n");
                }
                break;
            case Main.CallbackType.SEND:
                if (!richTextBox2.IsDisposed)
                {
                    richTextBox2.BeginInvoke(UpdateTextBox, richTextBox2, args[1] + "\n");
                }
                break;
            case Main.CallbackType.MESSAGE:
                if (!richTextBox3.IsDisposed)
                {
                    richTextBox3.BeginInvoke(UpdateTextBox, richTextBox3, args[1] + "\n");
                }
                break;
            case Main.CallbackType.HEART_BEAT:
                if (!richTextBox4.IsDisposed)
                {
                    richTextBox4.BeginInvoke(UpdateTextBox, richTextBox4, args[1]);
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
        switch (WindowState)
        {
            case FormWindowState.Minimized:
                // 设置通知消息文本
                notifyIcon1.BalloonTipText = "要再次打开窗口，请在托盘区双击托盘图标";
                Visible = false;
                // 显示通知消息
                notifyIcon1.ShowBalloonTip(3000); // 2000表示通知消息显示的时间（以毫秒为单位）
                break;
            case FormWindowState.Normal:
                break;
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

    private void notifyIcon1_DoubleClick(object sender, EventArgs e)
    {
        TopMost = true;
        Visible = true;
        WindowState = FormWindowState.Normal;
        TopMost = false;
    }
}
