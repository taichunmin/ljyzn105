namespace WindowsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// 
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="disposing"></param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows

        /// <summary>
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxSN = new System.Windows.Forms.TextBox();
            this.textBoxMac = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxLocalPort = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxMask = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxGate = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxDistinIP = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBoxDistinPort = new System.Windows.Forms.TextBox();
            this.checkBoxDHCP = new System.Windows.Forms.CheckBox();
            this.checkBoxDNS = new System.Windows.Forms.CheckBox();
            this.textBoxDNS = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxHeartTime = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxRSSI = new System.Windows.Forms.TextBox();
            this.textBoxPass = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 315);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(439, 76);
            this.textBox1.TabIndex = 5;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(42, 13);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 6;
            this.button1.Text = "Scan";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(163, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 7;
            this.button2.Text = "Stop";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(40, 54);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "CurrentSN";
            // 
            // textBoxSN
            // 
            this.textBoxSN.Location = new System.Drawing.Point(104, 51);
            this.textBoxSN.Name = "textBoxSN";
            this.textBoxSN.Size = new System.Drawing.Size(100, 21);
            this.textBoxSN.TabIndex = 9;
            // 
            // textBoxMac
            // 
            this.textBoxMac.Location = new System.Drawing.Point(104, 86);
            this.textBoxMac.Name = "textBoxMac";
            this.textBoxMac.Size = new System.Drawing.Size(100, 21);
            this.textBoxMac.TabIndex = 10;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 95);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 12);
            this.label2.TabIndex = 11;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(46, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 12);
            this.label3.TabIndex = 12;
            this.label3.Text = "Mac";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(44, 125);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(17, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "IP";
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(104, 120);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(100, 21);
            this.textBoxIP.TabIndex = 14;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(234, 123);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 15;
            this.label5.Text = "LocalPort";
            // 
            // textBoxLocalPort
            // 
            this.textBoxLocalPort.Location = new System.Drawing.Point(303, 118);
            this.textBoxLocalPort.Name = "textBoxLocalPort";
            this.textBoxLocalPort.Size = new System.Drawing.Size(100, 21);
            this.textBoxLocalPort.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(44, 159);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 17;
            this.label6.Text = "Mask";
            // 
            // textBoxMask
            // 
            this.textBoxMask.Location = new System.Drawing.Point(104, 156);
            this.textBoxMask.Name = "textBoxMask";
            this.textBoxMask.Size = new System.Drawing.Size(100, 21);
            this.textBoxMask.TabIndex = 18;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(234, 159);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(29, 12);
            this.label7.TabIndex = 19;
            this.label7.Text = "Gate";
            // 
            // textBoxGate
            // 
            this.textBoxGate.Location = new System.Drawing.Point(303, 156);
            this.textBoxGate.Name = "textBoxGate";
            this.textBoxGate.Size = new System.Drawing.Size(100, 21);
            this.textBoxGate.TabIndex = 20;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(40, 193);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 21;
            this.label8.Text = "DistinIP";
            // 
            // textBoxDistinIP
            // 
            this.textBoxDistinIP.Location = new System.Drawing.Point(104, 190);
            this.textBoxDistinIP.Name = "textBoxDistinIP";
            this.textBoxDistinIP.Size = new System.Drawing.Size(100, 21);
            this.textBoxDistinIP.TabIndex = 22;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(233, 193);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 23;
            this.label9.Text = "DistinPort";
            // 
            // textBoxDistinPort
            // 
            this.textBoxDistinPort.Location = new System.Drawing.Point(303, 190);
            this.textBoxDistinPort.Name = "textBoxDistinPort";
            this.textBoxDistinPort.Size = new System.Drawing.Size(100, 21);
            this.textBoxDistinPort.TabIndex = 24;
            // 
            // checkBoxDHCP
            // 
            this.checkBoxDHCP.AutoSize = true;
            this.checkBoxDHCP.Location = new System.Drawing.Point(42, 227);
            this.checkBoxDHCP.Name = "checkBoxDHCP";
            this.checkBoxDHCP.Size = new System.Drawing.Size(48, 16);
            this.checkBoxDHCP.TabIndex = 25;
            this.checkBoxDHCP.Text = "DHCP";
            this.checkBoxDHCP.UseVisualStyleBackColor = true;
            // 
            // checkBoxDNS
            // 
            this.checkBoxDNS.AutoSize = true;
            this.checkBoxDNS.Location = new System.Drawing.Point(122, 226);
            this.checkBoxDNS.Name = "checkBoxDNS";
            this.checkBoxDNS.Size = new System.Drawing.Size(42, 16);
            this.checkBoxDNS.TabIndex = 26;
            this.checkBoxDNS.Text = "DNS";
            this.checkBoxDNS.UseVisualStyleBackColor = true;
            // 
            // textBoxDNS
            // 
            this.textBoxDNS.Location = new System.Drawing.Point(182, 224);
            this.textBoxDNS.Name = "textBoxDNS";
            this.textBoxDNS.Size = new System.Drawing.Size(221, 21);
            this.textBoxDNS.TabIndex = 27;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(40, 258);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 28;
            this.label10.Text = "HeartTime";
            // 
            // textBoxHeartTime
            // 
            this.textBoxHeartTime.Location = new System.Drawing.Point(105, 253);
            this.textBoxHeartTime.Name = "textBoxHeartTime";
            this.textBoxHeartTime.Size = new System.Drawing.Size(100, 21);
            this.textBoxHeartTime.TabIndex = 29;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(257, 51);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 30;
            this.button3.Text = "Read";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(367, 51);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 31;
            this.button4.Text = "Set";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(40, 289);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(53, 12);
            this.label11.TabIndex = 32;
            this.label11.Text = "WifiRSSI";
            // 
            // textBoxRSSI
            // 
            this.textBoxRSSI.Location = new System.Drawing.Point(105, 286);
            this.textBoxRSSI.Name = "textBoxRSSI";
            this.textBoxRSSI.Size = new System.Drawing.Size(100, 21);
            this.textBoxRSSI.TabIndex = 33;
            // 
            // textBoxPass
            // 
            this.textBoxPass.Location = new System.Drawing.Point(303, 286);
            this.textBoxPass.Name = "textBoxPass";
            this.textBoxPass.Size = new System.Drawing.Size(100, 21);
            this.textBoxPass.TabIndex = 35;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(238, 289);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 34;
            this.label12.Text = "WifiPass";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 389);
            this.Controls.Add(this.textBoxPass);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.textBoxRSSI);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.textBoxHeartTime);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.textBoxDNS);
            this.Controls.Add(this.checkBoxDNS);
            this.Controls.Add(this.checkBoxDHCP);
            this.Controls.Add(this.textBoxDistinPort);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.textBoxDistinIP);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.textBoxGate);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBoxMask);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBoxLocalPort);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxMac);
            this.Controls.Add(this.textBoxSN);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox1);
            this.Name = "Form1";
            this.Text = "ScanDevice";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxSN;
        private System.Windows.Forms.TextBox textBoxMac;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxLocalPort;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxMask;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxGate;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxDistinIP;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBoxDistinPort;
        private System.Windows.Forms.CheckBox checkBoxDHCP;
        private System.Windows.Forms.CheckBox checkBoxDNS;
        private System.Windows.Forms.TextBox textBoxDNS;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxHeartTime;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxRSSI;
        private System.Windows.Forms.TextBox textBoxPass;
        private System.Windows.Forms.Label label12;
    }
}

