namespace IsaacSocket;

public partial class Form1 : Form
{
    internal Main main;
    public Form1()
    {
        InitializeComponent();
        main = new(1024, Callback);

    }
    private void UpdateTextBox(RichTextBox richTextBox, string text)
    {
        DateTime currentTime = DateTime.Now;

        // ��ȡʱ���벿��
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
    private void ���ý�������СToolStripMenuItem_Click(object sender, EventArgs e)
    {
        string userInput = Microsoft.VisualBasic.Interaction.InputBox("�������µĽ�������С����Χ�� 64 ~ 4194304��", "������", "1024");

        if (!string.IsNullOrEmpty(userInput))
        {
            int number;
            if (int.TryParse(userInput, out number))
            {
                main.SetDataSpaceSize(number);
            }
            else
            {
                MessageBox.Show("��Ч�����룬������һ����Ч�����֡�");
            }
        }
    }

    private void Form1_Load(object sender, EventArgs e)
    {
        main.Start();
    }

    private void ��ʾ������ToolStripMenuItem_Click(object sender, EventArgs e)
    {
        Show();
        WindowState = FormWindowState.Normal;

        TopMost = true;
        TopMost=false;
    }

    private void �˳�����ToolStripMenuItem_Click(object sender, EventArgs e)
    {
        Close();
    }

    private void ����������ToolStripMenuItem_Click(object sender, EventArgs e)
    {
        WindowState = FormWindowState.Minimized;
    }

    private void Form1_SizeChanged(object sender, EventArgs e)
    {
        switch (WindowState)
        {
            case FormWindowState.Minimized:
                // ����֪ͨ��Ϣ�ı�
                notifyIcon1.BalloonTipText = "Ҫ�ٴδ򿪴��ڣ�����������˫������ͼ��";
                Hide();
                // ��ʾ֪ͨ��Ϣ
                notifyIcon1.ShowBalloonTip(3000); // 2000��ʾ֪ͨ��Ϣ��ʾ��ʱ�䣨�Ժ���Ϊ��λ��
                ShowInTaskbar = false;
                break;
            case FormWindowState.Normal:
                ShowInTaskbar = true;
                break;
        }
    }

    private void Form1_FormClosing(object sender, FormClosingEventArgs e)
    {
        DialogResult result = MessageBox.Show("ȷ��Ҫ�˳�������", "�˳�����", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
        if (result == DialogResult.No)
        {
            e.Cancel = true;

        }
    }

    private void notifyIcon1_DoubleClick(object sender, EventArgs e)
    {
        Show();
        WindowState = FormWindowState.Normal;

        TopMost = true;
        TopMost = false;
    }
}
