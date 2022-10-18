using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using RFID;
using System.Runtime.InteropServices;
using System.Net;

namespace WindowsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            button2.Enabled = false;
            textBoxSN.Text = "00000000000000";
            if (RFID.NetUdpApi.NetUdp_OpenDevice() == false)
            {
                SetText("Open Error\r\n");
            }
        }

        delegate void SetTextCallback(string text);
        private void SetText(string text)
        {
            if (this.textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox1.Text = this.textBox1.Text + text;
                this.textBox1.SelectionStart = this.textBox1.Text.Length;
                this.textBox1.ScrollToCaret(); 
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            RFID.NetUdpApi.NetUdp_ScanDevice();
        }

        public void ShowInfo(byte[] pSN, byte[] pBuffer)
        {
            int i = 0;
            string str1 = "", str2 = "";
            for (i = 0; i < 7; i++)
            {
                str1 = pSN[i].ToString("X2");
                str2 = str2 + str1;
            }
            textBoxSN.Text = str2;  //SN

            //pBuffer[0] : SoftVersion
            //pBuffer[1] : HardVersion
            str2 = "";
            for (i = 0; i < 6; i++)
            {
                str1 = pBuffer[2+i].ToString("X2");
                str2 = str2 + str1;
            }
            textBoxMac.Text = str2;  //Mac

            str2 = "";
            for (i = 0; i < 4; i++)
            {
                str1 = pBuffer[8 + i].ToString();
                str2 = str2 + str1 + ".";
            }
            str2 = str2.Substring(0, str2.Length - 1);
            textBoxIP.Text = str2;  //IP

            str2 = "";
            for (i = 0; i < 4; i++)
            {
                str1 = pBuffer[12 + i].ToString();
                str2 = str2 + str1 + ".";
            }
            str2 = str2.Substring(0, str2.Length - 1);
            textBoxMask.Text = str2;  //Mask

            str2 = "";
            for (i = 0; i < 4; i++)
            {
                str1 = pBuffer[16 + i].ToString();
                str2 = str2 + str1 + ".";
            }
            str2 = str2.Substring(0, str2.Length - 1);
            textBoxGate.Text = str2;  //Gate

            int iPort = 0;
            iPort = pBuffer[20] * 256 + pBuffer[21];
            textBoxLocalPort.Text = iPort.ToString();
        }

        public void ProcessDelegate(int msg, int param1, byte[] pSN, byte[] pBuffer, UInt16 param4)
        { 
            if (msg == 2)
            {   //pSN : DeviceSN  pBuffer: other info
                this.ShowInfo(pSN, pBuffer);
                this.timer1.Enabled = false;
                this.button1.Enabled = true;
                this.button2.Enabled = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            button2.Enabled = true;
            timer1.Interval = 800;
            timer1.Enabled = true;
            RFID.NetUdpApi.NetUdp_SetCallbackAddr(ProcessDelegate);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            button1.Enabled = true;
            button2.Enabled = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBoxIP.Text = "";
            textBoxLocalPort.Text = "";
            textBoxMac.Text = "";
            textBoxMask.Text = "";
            textBoxDNS.Text = "";
            textBoxRSSI.Text = "";
            textBoxPass.Text = "";


            byte[] arrSN = new byte[8];
            int i = 0;
            for (i = 2; i < textBoxSN.Text.Length; i += 2)
            {
                arrSN[i / 2 - 1] = (byte)Convert.ToByte(textBoxSN.Text.Substring(i, 2), 16);
            }
            byte[] pBuffer = new byte[512];
            ushort ucParamLength = 0;
            string str1, str2;
            if (RFID.NetUdpApi.NetUdp_ReadDeviceNetParam(arrSN, pBuffer, out ucParamLength))
            {
                str2 = "";
                for (i = 0; i < 6; i++)
                {
                    str1 = pBuffer[2 + i].ToString("X2");
                    str2 = str2 + str1;
                }
                textBoxMac.Text = str2;  //Mac

                str2 = "";
                for (i = 0; i < 4; i++)
                {
                    str1 = pBuffer[8 + i].ToString();
                    str2 = str2 + str1 + ".";
                }
                str2 = str2.Substring(0, str2.Length - 1);
                textBoxIP.Text = str2;  //IP

                str2 = "";
                for (i = 0; i < 4; i++)
                {
                    str1 = pBuffer[12 + i].ToString();
                    str2 = str2 + str1 + ".";
                }
                str2 = str2.Substring(0, str2.Length - 1);
                textBoxMask.Text = str2;  //Mask

                str2 = "";
                for (i = 0; i < 4; i++)
                {
                    str1 = pBuffer[16 + i].ToString();
                    str2 = str2 + str1 + ".";
                }
                str2 = str2.Substring(0, str2.Length - 1);
                textBoxGate.Text = str2;  //Gate

                str2 = "";
                for (i = 0; i < 4; i++)
                {
                    str1 = pBuffer[20 + i].ToString();
                    str2 = str2 + str1 + ".";
                }
                str2 = str2.Substring(0, str2.Length - 1);
                textBoxDistinIP.Text = str2;  //Gate

                int iPort = 0;
                iPort = pBuffer[25] * 256 + pBuffer[24];
                textBoxLocalPort.Text = iPort.ToString();

                iPort = pBuffer[27] * 256 + pBuffer[26];
                textBoxDistinPort.Text = iPort.ToString();

                if (pBuffer[28] == 1) checkBoxDHCP.Checked = true;
                else checkBoxDHCP.Checked = false;

                if (pBuffer[29] == 1) checkBoxDNS.Checked = true;
                else checkBoxDNS.Checked = false;

                textBoxHeartTime.Text = pBuffer[30].ToString();

                byte[] arrDns = new byte[48];
                for (i = 0; i < 32; i++ )
                {
                    arrDns[i] = pBuffer[31 + i];
                }
                str1 = System.Text.Encoding.ASCII.GetString(arrDns);
                textBoxDNS.Text = str1;

                for (i = 0; i < 32; i++)
                {
                    arrDns[i] = pBuffer[31 + 32 + i];
                }
                str1 = System.Text.Encoding.ASCII.GetString(arrDns);
                textBoxRSSI.Text = str1;

                for (i = 0; i < 32; i++)
                {
                    arrDns[i] = pBuffer[31 + 64 + i];
                }
                str1 = System.Text.Encoding.ASCII.GetString(arrDns);
                textBoxPass.Text = str1;

                SetText("Success\r\n");

            }
            else { SetText("failed\r\n"); }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] arrSN = new byte[16];
            byte[] arrTemp = new byte[512];
            byte[] ucBuffer = new byte[512];
            int i = 0;
            for (i = 2; i < textBoxSN.Text.Length; i += 2)
            {
                arrSN[i / 2 - 1] = (byte)Convert.ToByte(textBoxSN.Text.Substring(i, 2), 16);
            }

            for (i = 0; i < 12; i += 2)
            {
                ucBuffer[i / 2] = (byte)Convert.ToByte(textBoxMac.Text.Substring(i, 2), 16);
            }

            byte[] byts = IPAddress.Parse(textBoxIP.Text).GetAddressBytes();

            ucBuffer[6] = byts[0]; ucBuffer[7] = byts[1]; ucBuffer[8] = byts[2]; ucBuffer[9] = byts[3]; //IP

            byts = IPAddress.Parse(textBoxMask.Text).GetAddressBytes();
            ucBuffer[10] = byts[0]; ucBuffer[11] = byts[1]; ucBuffer[12] = byts[2]; ucBuffer[13] = byts[3]; //Mask

            byts = IPAddress.Parse(textBoxGate.Text).GetAddressBytes();
            ucBuffer[14] = byts[0]; ucBuffer[15] = byts[1]; ucBuffer[16] = byts[2]; ucBuffer[17] = byts[3]; //Gate

            byts = IPAddress.Parse(textBoxDistinIP.Text).GetAddressBytes();
            ucBuffer[18] = byts[0]; ucBuffer[19] = byts[1]; ucBuffer[20] = byts[2]; ucBuffer[21] = byts[3]; //DistinIP

            UInt16 iPort = Convert.ToUInt16(textBoxLocalPort.Text);
            ucBuffer[22] = (Byte)(iPort % 256);
            ucBuffer[23] = (Byte)(iPort / 256);  //LocalPort

            iPort = Convert.ToUInt16(textBoxDistinPort.Text);
            ucBuffer[24] = (Byte)(iPort % 256);
            ucBuffer[25] = (Byte)(iPort / 256);  //DistinPort

            if (checkBoxDHCP.Checked) ucBuffer[26] = 1;
            else ucBuffer[26] = 0;

            if (checkBoxDNS.Checked) ucBuffer[27] = 1;
            else ucBuffer[27] = 0;

            ucBuffer[28] = Convert.ToByte(textBoxHeartTime.Text);

            arrTemp = System.Text.Encoding.Default.GetBytes(textBoxDNS.Text);
            for (i = 0; i < textBoxDNS.Text.Length; i++) ucBuffer[29 + i] = arrTemp[i];   //DNS name

            arrTemp = System.Text.Encoding.Default.GetBytes(textBoxRSSI.Text);
            for (i = 0; i < textBoxRSSI.Text.Length; i++) ucBuffer[29 + 32 + i] = arrTemp[i];   //DNS name

            arrTemp = System.Text.Encoding.Default.GetBytes(textBoxPass.Text);
            for (i = 0; i < textBoxPass.Text.Length; i++) ucBuffer[29 + 64 + i] = arrTemp[i];   //DNS name

            if (RFID.NetUdpApi.NetUdp_SetDeviceNetParam(arrSN, ucBuffer, 29 + 64+32))
            {
                SetText("Success\r\n");
            }
            else SetText("failed\r\n");
        }
    }
}