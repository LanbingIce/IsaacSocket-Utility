namespace IsaacSocket.Forms
{
    partial class UpdateForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button1 = new Button();
            richTextBox1 = new RichTextBox();
            progressBar1 = new ProgressBar();
            button2 = new Button();
            label1 = new Label();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(12, 171);
            button1.Name = "button1";
            button1.Size = new Size(75, 23);
            button1.TabIndex = 0;
            button1.Text = "现在更新";
            button1.UseVisualStyleBackColor = true;
            button1.Click += Button1_Click;
            // 
            // richTextBox1
            // 
            richTextBox1.Location = new Point(12, 12);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(284, 124);
            richTextBox1.TabIndex = 1;
            richTextBox1.Text = "";
            richTextBox1.LinkClicked += RichTextBox1_LinkClicked;
            // 
            // progressBar1
            // 
            progressBar1.Location = new Point(12, 142);
            progressBar1.Name = "progressBar1";
            progressBar1.Size = new Size(284, 23);
            progressBar1.TabIndex = 2;
            // 
            // button2
            // 
            button2.Location = new Point(221, 171);
            button2.Name = "button2";
            button2.Size = new Size(75, 23);
            button2.TabIndex = 3;
            button2.Text = "下次再说";
            button2.UseVisualStyleBackColor = true;
            button2.Click += Button2_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(93, 174);
            label1.Name = "label1";
            label1.Size = new Size(0, 17);
            label1.TabIndex = 4;
            // 
            // UpdateForm
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(304, 201);
            ControlBox = false;
            Controls.Add(label1);
            Controls.Add(button2);
            Controls.Add(progressBar1);
            Controls.Add(richTextBox1);
            Controls.Add(button1);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "UpdateForm";
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "UpdateForm";
            TopMost = true;
            FormClosing += UpdateForm_FormClosing;
            Load += UpdateForm_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private RichTextBox richTextBox1;
        private ProgressBar progressBar1;
        private Button button2;
        private Label label1;
    }
}