namespace IsaacSocket.Forms;

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
        showMainWindowToolStripMenuItem = new ToolStripMenuItem();
        hideMainWindowToolStripMenuItem = new ToolStripMenuItem();
        toolStripSeparator1 = new ToolStripSeparator();
        setDataSpaceSizeToolStripMenuItem = new ToolStripMenuItem();
        toolStripSeparator2 = new ToolStripSeparator();
        exitToolStripMenuItem = new ToolStripMenuItem();
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
        notifyIcon1.Text = "IsaacSocket";
        notifyIcon1.Visible = true;
        notifyIcon1.DoubleClick += NotifyIcon1_DoubleClick;
        // 
        // contextMenuStrip1
        // 
        contextMenuStrip1.Items.AddRange(new ToolStripItem[] { showMainWindowToolStripMenuItem, hideMainWindowToolStripMenuItem, toolStripSeparator1, setDataSpaceSizeToolStripMenuItem, toolStripSeparator2, exitToolStripMenuItem });
        contextMenuStrip1.Name = "contextMenuStrip1";
        contextMenuStrip1.Size = new Size(161, 104);
        // 
        // showMainWindowToolStripMenuItem
        // 
        showMainWindowToolStripMenuItem.Name = "showMainWindowToolStripMenuItem";
        showMainWindowToolStripMenuItem.Size = new Size(160, 22);
        showMainWindowToolStripMenuItem.Text = "显示主窗口";
        showMainWindowToolStripMenuItem.Click += ShowMainWindowToolStripMenuItem_Click;
        // 
        // hideMainWindowToolStripMenuItem
        // 
        hideMainWindowToolStripMenuItem.Name = "hideMainWindowToolStripMenuItem";
        hideMainWindowToolStripMenuItem.Size = new Size(160, 22);
        hideMainWindowToolStripMenuItem.Text = "隐藏主窗口";
        hideMainWindowToolStripMenuItem.Click += HideMainWindowToolStripMenuItem_Click;
        // 
        // toolStripSeparator1
        // 
        toolStripSeparator1.Name = "toolStripSeparator1";
        toolStripSeparator1.Size = new Size(157, 6);
        // 
        // setDataSpaceSizeToolStripMenuItem
        // 
        setDataSpaceSizeToolStripMenuItem.Name = "setDataSpaceSizeToolStripMenuItem";
        setDataSpaceSizeToolStripMenuItem.Size = new Size(160, 22);
        setDataSpaceSizeToolStripMenuItem.Text = "设置交换区大小";
        setDataSpaceSizeToolStripMenuItem.Click += SetDataSpaceSizeToolStripMenuItem_Click;
        // 
        // toolStripSeparator2
        // 
        toolStripSeparator2.Name = "toolStripSeparator2";
        toolStripSeparator2.Size = new Size(157, 6);
        // 
        // exitToolStripMenuItem
        // 
        exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        exitToolStripMenuItem.Size = new Size(160, 22);
        exitToolStripMenuItem.Text = "退出程序";
        exitToolStripMenuItem.Click += ExitToolStripMenuItem_Click;
        // 
        // groupBox1
        // 
        groupBox1.Controls.Add(richTextBox1);
        groupBox1.Location = new Point(12, 12);
        groupBox1.Name = "groupBox1";
        groupBox1.Size = new Size(320, 480);
        groupBox1.TabIndex = 1;
        groupBox1.TabStop = false;
        groupBox1.Text = "消息：从 Mod 到 连接程序";
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
        groupBox2.Text = "消息：从 连接程序 到 Mod";
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
        groupBox3.Text = "心跳包和系统消息";
        // 
        // richTextBox4
        // 
        richTextBox4.Location = new Point(6, 22);
        richTextBox4.Name = "richTextBox4";
        richTextBox4.Size = new Size(308, 80);
        richTextBox4.TabIndex = 1;
        richTextBox4.Text = "";
        // 
        // richTextBox3
        // 
        richTextBox3.Location = new Point(6, 108);
        richTextBox3.Name = "richTextBox3";
        richTextBox3.Size = new Size(308, 366);
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
        Icon = (Icon)resources.GetObject("$this.Icon");
        MaximizeBox = false;
        Name = "Form1";
        StartPosition = FormStartPosition.CenterScreen;
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
    private ToolStripMenuItem showMainWindowToolStripMenuItem;
    private ToolStripMenuItem hideMainWindowToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem exitToolStripMenuItem;
    private ToolStripMenuItem setDataSpaceSizeToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator2;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private GroupBox groupBox3;
    private RichTextBox richTextBox1;
    private RichTextBox richTextBox2;
    private RichTextBox richTextBox4;
    private RichTextBox richTextBox3;
}
