namespace IsaacSocket;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        components = new System.ComponentModel.Container();
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
        notifyIcon1 = new NotifyIcon(components);
        contextMenuStrip1 = new ContextMenuStrip(components);
        显示主窗口ToolStripMenuItem = new ToolStripMenuItem();
        隐藏主窗口ToolStripMenuItem = new ToolStripMenuItem();
        toolStripSeparator1 = new ToolStripSeparator();
        设置交换区大小ToolStripMenuItem = new ToolStripMenuItem();
        toolStripSeparator2 = new ToolStripSeparator();
        退出程序ToolStripMenuItem = new ToolStripMenuItem();
        groupBox1 = new GroupBox();
        richTextBox1 = new RichTextBox();
        groupBox2 = new GroupBox();
        richTextBox2 = new RichTextBox();
        groupBox3 = new GroupBox();
        richTextBox4 = new RichTextBox();
        richTextBox3 = new RichTextBox();
        contextMenuStrip1.SuspendLayout();
        groupBox1.SuspendLayout();
        groupBox2.SuspendLayout();
        groupBox3.SuspendLayout();
        SuspendLayout();
        // 
        // notifyIcon1
        // 
        notifyIcon1.ContextMenuStrip = contextMenuStrip1;
        notifyIcon1.Icon = (Icon)resources.GetObject("notifyIcon1.Icon");
        notifyIcon1.Text = "notifyIcon1";
        notifyIcon1.Visible = true;
        notifyIcon1.DoubleClick += notifyIcon1_DoubleClick;
        // 
        // contextMenuStrip1
        // 
        contextMenuStrip1.Items.AddRange(new ToolStripItem[] { 显示主窗口ToolStripMenuItem, 隐藏主窗口ToolStripMenuItem, toolStripSeparator1, 设置交换区大小ToolStripMenuItem, toolStripSeparator2, 退出程序ToolStripMenuItem });
        contextMenuStrip1.Name = "contextMenuStrip1";
        contextMenuStrip1.Size = new Size(161, 104);
        // 
        // 显示主窗口ToolStripMenuItem
        // 
        显示主窗口ToolStripMenuItem.Name = "显示主窗口ToolStripMenuItem";
        显示主窗口ToolStripMenuItem.Size = new Size(160, 22);
        显示主窗口ToolStripMenuItem.Text = "显示主窗口";
        显示主窗口ToolStripMenuItem.Click += 显示主窗口ToolStripMenuItem_Click;
        // 
        // 隐藏主窗口ToolStripMenuItem
        // 
        隐藏主窗口ToolStripMenuItem.Name = "隐藏主窗口ToolStripMenuItem";
        隐藏主窗口ToolStripMenuItem.Size = new Size(160, 22);
        隐藏主窗口ToolStripMenuItem.Text = "隐藏主窗口";
        隐藏主窗口ToolStripMenuItem.Click += 隐藏主窗口ToolStripMenuItem_Click;
        // 
        // toolStripSeparator1
        // 
        toolStripSeparator1.Name = "toolStripSeparator1";
        toolStripSeparator1.Size = new Size(157, 6);
        // 
        // 设置交换区大小ToolStripMenuItem
        // 
        设置交换区大小ToolStripMenuItem.Name = "设置交换区大小ToolStripMenuItem";
        设置交换区大小ToolStripMenuItem.Size = new Size(160, 22);
        设置交换区大小ToolStripMenuItem.Text = "设置交换区大小";
        设置交换区大小ToolStripMenuItem.Click += 设置交换区大小ToolStripMenuItem_Click;
        // 
        // toolStripSeparator2
        // 
        toolStripSeparator2.Name = "toolStripSeparator2";
        toolStripSeparator2.Size = new Size(157, 6);
        // 
        // 退出程序ToolStripMenuItem
        // 
        退出程序ToolStripMenuItem.Name = "退出程序ToolStripMenuItem";
        退出程序ToolStripMenuItem.Size = new Size(160, 22);
        退出程序ToolStripMenuItem.Text = "退出程序";
        退出程序ToolStripMenuItem.Click += 退出程序ToolStripMenuItem_Click;
        // 
        // groupBox1
        // 
        groupBox1.Controls.Add(richTextBox1);
        groupBox1.Location = new Point(12, 12);
        groupBox1.Name = "groupBox1";
        groupBox1.Size = new Size(320, 480);
        groupBox1.TabIndex = 1;
        groupBox1.TabStop = false;
        groupBox1.Text = "收到的消息";
        // 
        // richTextBox1
        // 
        richTextBox1.Location = new Point(6, 22);
        richTextBox1.Name = "richTextBox1";
        richTextBox1.Size = new Size(308, 452);
        richTextBox1.TabIndex = 0;
        richTextBox1.Text = "";
        // 
        // groupBox2
        // 
        groupBox2.Controls.Add(richTextBox2);
        groupBox2.Location = new Point(338, 12);
        groupBox2.Name = "groupBox2";
        groupBox2.Size = new Size(320, 480);
        groupBox2.TabIndex = 2;
        groupBox2.TabStop = false;
        groupBox2.Text = "发出的消息";
        // 
        // richTextBox2
        // 
        richTextBox2.Location = new Point(6, 22);
        richTextBox2.Name = "richTextBox2";
        richTextBox2.Size = new Size(308, 452);
        richTextBox2.TabIndex = 0;
        richTextBox2.Text = "";
        // 
        // groupBox3
        // 
        groupBox3.Controls.Add(richTextBox4);
        groupBox3.Controls.Add(richTextBox3);
        groupBox3.Location = new Point(664, 12);
        groupBox3.Name = "groupBox3";
        groupBox3.Size = new Size(320, 480);
        groupBox3.TabIndex = 3;
        groupBox3.TabStop = false;
        groupBox3.Text = "心跳包和其他消息";
        // 
        // richTextBox4
        // 
        richTextBox4.Location = new Point(6, 22);
        richTextBox4.Name = "richTextBox4";
        richTextBox4.Size = new Size(308, 64);
        richTextBox4.TabIndex = 1;
        richTextBox4.Text = "";
        // 
        // richTextBox3
        // 
        richTextBox3.Location = new Point(6, 92);
        richTextBox3.Name = "richTextBox3";
        richTextBox3.Size = new Size(308, 382);
        richTextBox3.TabIndex = 0;
        richTextBox3.Text = "";
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(7F, 17F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(992, 501);
        Controls.Add(groupBox3);
        Controls.Add(groupBox2);
        Controls.Add(groupBox1);
        FormBorderStyle = FormBorderStyle.FixedSingle;
        MaximizeBox = false;
        Name = "Form1";
        Text = "IsaacSocket 连接程序";
        FormClosing += Form1_FormClosing;
        Load += Form1_Load;
        SizeChanged += Form1_SizeChanged;
        contextMenuStrip1.ResumeLayout(false);
        groupBox1.ResumeLayout(false);
        groupBox2.ResumeLayout(false);
        groupBox3.ResumeLayout(false);
        ResumeLayout(false);
    }

    #endregion

    private NotifyIcon notifyIcon1;
    private ContextMenuStrip contextMenuStrip1;
    private ToolStripMenuItem 显示主窗口ToolStripMenuItem;
    private ToolStripMenuItem 隐藏主窗口ToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem 退出程序ToolStripMenuItem;
    private ToolStripMenuItem 设置交换区大小ToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator2;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private GroupBox groupBox3;
    private RichTextBox richTextBox1;
    private RichTextBox richTextBox2;
    private RichTextBox richTextBox4;
    private RichTextBox richTextBox3;
}
