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

namespace WindowsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBoxIP.Text = "192.168.1.250";
            textBoxPort.Text = "60000";
            button2.Enabled = false;
            button11.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {  
            byte[] arrBuffer = new byte[64];

            string stringIP = textBoxIP.Text;
            UInt16 iPort = Convert.ToUInt16(textBoxPort.Text);
            if (RFID.SWNetApi.SWNet_OpenDevice(stringIP, iPort))
            {
				this.SetText("OpenSuccess\r\n");
                if (RFID.SWNetApi.SWNet_GetDeviceSystemInfo(0xFF,arrBuffer) == false) 
                {
					this.SetText("Device is Out\r\n");
                    //RFID.SWNetApi.SWNet_CloseDevice();
                    //return;
                }
            }
            else
            {
                this.SetText("Failed\r\n");
                return;
            }

            string str = "",str1="";
            str = String.Format("SoftVer:{0:D}.{0:D}\r\n", arrBuffer[0] >> 4, arrBuffer[0] & 0x0F);
            this.SetText(str);
            str = String.Format("HardVer:{0:D}.{0:D}\r\n", arrBuffer[1] >> 4, arrBuffer[1] & 0x0F);
            this.SetText(str);
            str = "SN:";
            for (int i = 0; i < 7; i++)
            {
                str1 = String.Format("{0:X2}", arrBuffer[2 + i]);
                str = str + str1;
            }
            str = str + "\r\n";
            this.SetText(str);
            button1.Enabled = false;
            button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            RFID.SWNetApi.SWNet_CloseDevice();
            button1.Enabled = true;
            button2.Enabled = false;
            button6.Enabled = true;
            button11.Enabled = false;
            this.SetText("Close\r\n");
        }

        private void button11_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            button6.Enabled = true;
            button11.Enabled = false;
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
                if (this.textBox1.TextLength > 1000) this.textBox1.Text = "";
                this.textBox1.Text = this.textBox1.Text + text;
                this.textBox1.SelectionStart = this.textBox1.Text.Length;
                this.textBox1.ScrollToCaret(); 
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            this.SetText("ActiveMode\r\n");
            RFID.SWNetApi.SWNet_ClearTagBuf();
            timer1.Interval = 100;
            timer1.Enabled = true;
            button6.Enabled = false;
            button11.Enabled = true;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            byte[] arrBuffer = new byte[64000];
            ushort iNum = 0;
            ushort iTotalLen = 0; 
            this.SetText("AnswerMode\r\n");
            if (RFID.SWNetApi.SWNet_InventoryG2(0xFF, arrBuffer, out iTotalLen, out iNum) == false)
            {
                this.SetText("Failed\r\n");
                return;
            }
            int iTagLength = 0;
            int iTagNumber = 0;
            iTagLength = iTotalLen;
            iTagNumber = iNum;
            if (iTagNumber == 0) return;
            int iIndex = 0;
            int iLength = 0;
            byte bPackLength = 0;
            int iIDLen = 0;
            int i = 0;

            for (iIndex = 0; iIndex < iTagNumber; iIndex++)
            {
                bPackLength = arrBuffer[iLength];
                string str2 = "";
                string str1 = "";
                str1 = arrBuffer[1 + iLength + 0].ToString("X2");
                if ((arrBuffer[1 + iLength + 0] & 0x80) == 0x80)
                {   // with TimeStamp , last 6 bytes is time
                    iIDLen = bPackLength - 7;
                }
                else iIDLen = bPackLength - 1;

                str2 = str2 + "Type:" + str1 + " ";  //Tag Type

                str1 = arrBuffer[1 + iLength + 1].ToString("X2");
                str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

                string str3 = "";
                for (i = 2; i < iIDLen; i++)
                {
                    str1 = arrBuffer[1 + iLength + i].ToString("X2");
                    str3 = str3 + str1 + " ";
                }
                str2 = str2 + str3;
                str1 = arrBuffer[1 + iLength + i].ToString("X2");
                str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
                iLength = iLength + bPackLength + 1;
                this.SetText(str2);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] Password = new byte[4];
            Password[0] = 0; 
            Password[1] = 0;
            Password[2] = 0;
            Password[3] = 0;
            byte[] arrBuffer = new byte[12];
            arrBuffer[0] = 0x00;
            arrBuffer[1] = 0x11;
            arrBuffer[2] = 0x22;
            arrBuffer[3] = 0x33;
            arrBuffer[4] = 0x44;
            arrBuffer[5] = 0x55;
            arrBuffer[6] = 0x66;
            arrBuffer[7] = 0x77;
            arrBuffer[8] = 0x88;
            arrBuffer[9] = 0x99;
            arrBuffer[10] = 0xAA;
            arrBuffer[11] = 0xBB;
            if (RFID.SWNetApi.SWNet_WriteCardG2(0xFF, Password, 1, 2, 6, arrBuffer) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void button4_Click(object sender, EventArgs e)
        {  //ReadRFPower
            byte bParamAddr = 0;
            byte[] bValue = new byte[2];

            /*  01: Transport
                02: WorkMode
                03: DeviceAddr
                04: FilterTime
                05: RFPower
                06: BeepEnable
                07: UartBaudRate*/
            bParamAddr = 0x05;

            if (RFID.SWNetApi.SWNet_ReadDeviceOneParam(0xFF, bParamAddr, bValue) == false)
            {
                this.SetText("Faild");
                return;
            }
            string str1 = "";
            str1 = bValue[0].ToString("d2");
            str1 = "RF:"+str1 + "\r\n";

            comboBox2.SelectedIndex = bValue[0];
            this.SetText(str1);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte bParamAddr = 0;
            byte bValue = 0;

            /*  01: Transport
                02: WorkMode
                03: DeviceAddr
                04: FilterTime
                05: RFPower
                06: BeepEnable
                07: UartBaudRate*/
            bParamAddr = 0x05;
            //bValue = 26;   //RF = 26

            bValue = (byte)Convert.ToInt16(comboBox2.SelectedItem);

            if (RFID.SWNetApi.SWNet_SetDeviceOneParam(0xFF, bParamAddr, bValue) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (RFID.SWNetApi.SWNet_RelayOn(0xFF) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (RFID.SWNetApi.SWNet_RelayOff(0xFF) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            byte[] arrBuffer = new byte[64000];
            int iNum = 0;
            int iTotalLen = 0;
            byte bRet = 0;

            bRet = RFID.SWNetApi.SWNet_GetTagBuf(arrBuffer, out iTotalLen, out iNum);
            if (bRet == 1)
            {
                this.SetText("DevOut");
                return; //DevOut
            }
            else if (bRet == 0) return; //No Connect
            int iTagLength = 0;
            int iTagNumber = 0;
            iTagLength = iTotalLen;
            iTagNumber = iNum;
            if (iTagNumber == 0) return;
            int iIndex = 0;
            int iLength = 0;
            byte bPackLength = 0;
            int i = 0;
            int iIDLen = 0;
            for (iIndex = 0; iIndex < iTagNumber; iIndex++)
            {
                bPackLength = arrBuffer[iLength];
                string str2 = "";
                string str1 = "";
                str1 = arrBuffer[1 + iLength + 0].ToString("X2");
                str2 = str2 + "Type:" + str1 + " ";  //Tag Type
                if ((arrBuffer[1 + iLength + 0] & 0x80) == 0x80)
                {   // with TimeStamp , last 6 bytes is time
                    iIDLen = bPackLength - 7;
                }
                else iIDLen = bPackLength - 1;

                str1 = arrBuffer[1 + iLength + 1].ToString("X2");
                str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

                string str3 = "";
                for (i = 2; i < iIDLen; i++)
                {
                    str1 = arrBuffer[1 + iLength + i].ToString("X2");
                    str3 = str3 + str1 + " ";
                }
                str2 = str2 + str3;
                str1 = arrBuffer[1 + iLength + i].ToString("X2");
                str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
                iLength = iLength + bPackLength + 1;
                this.SetText(str2);
            }
        }
    }
}