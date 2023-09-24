using System.Diagnostics;

namespace IsaacSocket.Forms
{
    public partial class UpdateForm : Form
    {
        internal string? downloadLink;
        internal string? tagName;
        internal string? body;
        public UpdateForm()
        {
            InitializeComponent();
        }

        private void UpdateForm_Load(object sender, EventArgs e)
        {
            richTextBox1.Text = $"{tagName} 更新说明：{Environment.NewLine}{Environment.NewLine}{body}";
            Text = $"软件有更新版本：{tagName}";
        }
        private async void UpdateAsync()
        {
            label1.Text = "正在下载";
            button1.Enabled = false;
            button2.Enabled = false;
            try
            {
                using HttpClient client = new();
                Uri downloadUri = new(downloadLink ?? "");
                using (var response = await client.GetAsync(downloadUri, HttpCompletionOption.ResponseHeadersRead))
                using (var stream = await response.Content.ReadAsStreamAsync())
                using (var fileStream = new FileStream("update.exe", FileMode.Create, FileAccess.Write))
                {
                    var buffer = new byte[8192];
                    int bytesRead;
                    long totalBytesRead = 0;
                    long totalBytes = response.Content.Headers.ContentLength.GetValueOrDefault();

                    while ((bytesRead = await stream.ReadAsync(buffer)) > 0)
                    {
                        await fileStream.WriteAsync(buffer.AsMemory(0, bytesRead));
                        totalBytesRead += bytesRead;
                        int progressPercentage = (int)((double)totalBytesRead / totalBytes * 100);
                        progressBar1.Value = progressPercentage;
                    }
                }

                string batchScript = @"
@echo off
:a
if exist %1 (
    timeout /t 1 /nobreak > nul
    del /f /q %1
    goto a
) else (
    ren %2 %1
    start .\%1
)
";
                string batchFilePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "update.bat");
                File.WriteAllText("update.bat", batchScript);
                string argument1 = AppDomain.CurrentDomain.FriendlyName + ".exe";
                string argument2 = "update.exe";

                // 运行批处理文件
                Process.Start(new ProcessStartInfo
                {
                    FileName = batchFilePath,
                    Arguments = $"\"{argument1}\" \"{argument2}\"",
                    UseShellExecute = true
                });
                Application.Exit();
            }
            catch (Exception)
            {
                label1.Text = "下载出错,请稍后再试";
                button1.Enabled = true;
                button2.Enabled = true;
            }
        }
        private void Button1_Click(object sender, EventArgs e)
        {
            UpdateAsync();
        }
        private void UpdateForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Visible = false;
        }

        private void RichTextBox1_LinkClicked(object sender, LinkClickedEventArgs e)
        {
            Process.Start("explorer.exe", e.LinkText ?? "");
        }
    }
}
