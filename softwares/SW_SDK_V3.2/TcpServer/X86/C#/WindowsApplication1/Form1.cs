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
        private int g_iSockTotal = 0;
        public Form1()
        {
            InitializeComponent();
            textBoxPort.Text = "60000";
            textBox2.Text = "0";
            textBox3.Text = "0";
            button2.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {  
            byte[] arrBuffer = new byte[64];
            UInt16 iSock = Convert.ToUInt16(textBoxPort.Text);
            if (RFID.SWNetServerApi.SWNet_Listening(iSock))
            {
				this.SetText("ListeningSuccess\r\n");
            }
            else
            {
                this.SetText("Failed\r\n");
                return;
            }
            button1.Enabled = false;
            button2.Enabled = true;
            RFID.SWNetServerApi.SWNet_ClearTagBuf();  //Open cache mode, the data will saved in dll. 
            timer1.Interval = 100;
            timer1.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            RFID.SWNetServerApi.SWNet_CloseDevice();
            button1.Enabled = true;
            button2.Enabled = false;
            this.SetText("Close\r\n");

            timer1.Enabled = false;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_StartRead(iSock))
            {
                this.SetText("Success\r\n");
            }
            else
            {
                this.SetText("Failed\r\n");
                return;
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
                if (this.textBox1.TextLength > 1000) this.textBox1.Text = "";
                this.textBox1.Text = this.textBox1.Text + text;
                this.textBox1.SelectionStart = this.textBox1.Text.Length;
                this.textBox1.ScrollToCaret(); 
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_StopRead(iSock))
            {
                this.SetText("Success\r\n");
            }
            else
            {
                this.SetText("Failed\r\n");
                return;
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
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_WriteCardG2(iSock, Password, 1, 2, 6, arrBuffer) == false)
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
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_ReadDeviceOneParam(iSock, bParamAddr, bValue) == false)
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
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_SetDeviceOneParam(iSock, bParamAddr, bValue) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_RelayOn(iSock) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            UInt16 iSock = Convert.ToUInt16(textBox2.Text);
            if (RFID.SWNetServerApi.SWNet_RelayOff(iSock) == false)
            {
                this.SetText("Faild");
                return;
            }
            this.SetText("Success");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            byte[] IPInfo = new byte[4096];
            int IPCnt = 0;
            RFID.SWNetServerApi.SWNet_GetTotalClientIPAndSocket(out IPCnt,IPInfo);

            if (g_iSockTotal != IPCnt)  //Connect Change
            {
                if (g_iSockTotal < IPCnt)  //Connect
                {
                    string strSock;
                    int iConnectSock = 0;
                    //IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
                                                       // then 2 bytes is socket, high byte is first
                    //last ip is new coming connect
                    iConnectSock = IPInfo[g_iSockTotal * 17 + 15] * 256 + IPInfo[g_iSockTotal * 17 + 16];
                    strSock = iConnectSock.ToString();
                    
                    string strIP = "";
                    byte[] ucIP = new byte[16];
                    for (int ii = 0; ii < 15; ii++) ucIP[ii] = IPInfo[g_iSockTotal * 17 + ii];
                    ucIP[15] = 0;
                    strIP = System.Text.Encoding.ASCII.GetString(ucIP);
                    strIP = strIP.Substring(0, strIP.Length - 1);
                    this.SetText(strIP + ":" + strSock + " connect\r\n");
                }
                else  //Disconnect
                { //Need to compare old IPinfo, you can solve by yourself, this is not to show

                }
                g_iSockTotal = IPCnt;
                textBox3.Text = g_iSockTotal.ToString();
            }
            if (IPCnt == 0) return;
            //IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
                                                       // then 2 bytes is socket, high byte is first
            int iSock = 0;
            iSock = IPInfo[15]*256 + IPInfo[16];
            textBox2.Text = iSock.ToString();


            byte[] arrBuffer = new byte[1024*64];
            int iLineCnt = 0;
            int iTotalLen = 0;
            byte bRet = 0;

            bRet = RFID.SWNetServerApi.SWNet_GetTagBuf(arrBuffer, out iTotalLen, out iLineCnt);
            if (bRet == 0)
            {
                return; 
            }
            if (iTotalLen == 0)
            {
                return;
            }

            int i = 0, j = 0, k = 0;
            int iTagLength = 0;
            int iTagNumber = 0;
            string strTagIP = "";
            string str1;
            string strSocket;
            string strSN;
            int iTotalCnt = 0;
            int iIDLen = 0;
            for (k = 0; k < iLineCnt; k++) //iLineCnt mean pakage number
            {
                //every pakage group is 2 bytes length + 15 bytes ip+ 2bytes socket+ 7bytes SN + 1 bytes tagcnt + tagcontent
                iTagLength = arrBuffer[0 + iTotalCnt] * 256 + arrBuffer[1 + iTotalCnt];  //GetPakageLength
                //get IP
                byte[] IP = new byte[16];
                for (i = 0; i < 15; i++) IP[i] = arrBuffer[2 + i];
                IP[15] = 0;
                strTagIP = System.Text.Encoding.ASCII.GetString(IP);
                strTagIP = strTagIP.Substring(0, strTagIP.Length - 1);
                //Get Socket
                int iSocket = 0;
                iSocket = arrBuffer[2 + 15 + iTotalCnt] * 256 + arrBuffer[2 + 16 + iTotalCnt];
                strSocket = iSocket.ToString();
                //Get SN
                strSN = "";
                for (i = 0; i < 7; i++)
                {
                    str1 = arrBuffer[2 + 17 + i + iTotalCnt].ToString("X2");
                    strSN = strSN + str1;
                }
                this.SetText(strTagIP + ":" + strSocket + " " + strSN+"\r\n");
                //Get TagCnt
                iTagNumber = arrBuffer[2 + 17 + 7 + iTotalCnt];
                //Get TagContent
                byte bPackLength = 0;
                int iLength = 0;
                for (i = 0; i < iTagNumber; i++)
                {
                    bPackLength = arrBuffer[2 + 17 + 8 + iLength + iTotalCnt];
                    string str2 = "";
                    str1 = "";
                    str1 = arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt].ToString("X2");
                    str2 = str2 + "Type:" + str1 + " ";  //Tag Type
                    if ((arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt] & 0x80) == 0x80)
                    {   // with TimeStamp , last 6 bytes is time
                        iIDLen = bPackLength - 7;
                    }
                    else iIDLen = bPackLength - 1;

                    str1 = arrBuffer[2 + 17 + 8 + 2 + iLength + iTotalCnt].ToString("X2");
                    str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

                    string str3 = "";
                    for (j = 2; j < iIDLen; j++)
                    {
                        str1 = arrBuffer[2 + 17 + 8 + 1 + iLength + j + iTotalCnt].ToString("X2");
                        str3 = str3 + str1 + " ";
                    }
                    str2 = str2 + str3;
                    str1 = arrBuffer[2 + 17 + 8 + 1 + iLength + j + iTotalCnt].ToString("X2");
                    str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
                    iLength = iLength + bPackLength + 1;
                    this.SetText(str2);
                }
                iTotalCnt = iTotalCnt + iTagLength + 2;
                if (iTotalCnt > iTotalLen) break;

            }
        }
    }
}