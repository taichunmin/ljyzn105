#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>

#include "SWComApi.h"

#define FALSE 0
#define TRUE  1

using namespace std;


void ReadAnswerMode(void)
{
	unsigned char arrBuffer[2048] = {0};
	unsigned short iTagLength = 0;
	unsigned short iTagNumber = 0;
	//cout<<"AnswerMode"<<endl;
	if (SWCom_InventoryG2(0xFF,arrBuffer,&iTagLength,&iTagNumber) == FALSE)
	{
		//cout<<"Failed"<<endl;
		return;
	}
	if (iTagNumber == 0)
	{
		cout<<"NoData"<<endl;
		return;
	}
	int iIndex = 0;
	int iLength = 0;
	unsigned char *pID;
	unsigned char bPackLength = 0;
	unsigned char bIDLength = 0;
	unsigned char iIDLen = 0;
	char buf[512]={0};

	for(iIndex = 0; iIndex < iTagNumber; iIndex++)
	{
		bPackLength = arrBuffer[iLength];
		pID = (unsigned char *)&arrBuffer[1 + iLength];
		string str1="", str2="", strTemp="";

		sprintf(buf,"Type:%.2X ", pID[0]);
		if((pID[0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
		{
		    iIDLen = bPackLength - 7;
		}
		else iIDLen = bPackLength - 1;
		strTemp = buf;

        str2 = str2 + strTemp;  //Tag Type

		sprintf(buf,"Ant:%.2X Tag:", pID[1]);
		strTemp = buf;

		str2 = str2 + strTemp;  //Ant
		for (int i = 2; i < iIDLen; i++)
		{
			sprintf(buf,"%.2X ", pID[i]);
			str1 = buf;
			str2 = str2 + str1;
		}
		sprintf(buf,"RSSI:%.2X", pID[iIDLen]);
		strTemp = buf;

		str2 = str2 + strTemp;  //RSSI
		cout<<str2<<endl;
		iLength = iLength + bPackLength + 1;
	}
}

void CallBackFunc(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4)
{
	if (msg == 2)  //Data
	{
		//unsigned short iTagLength = 0;
		unsigned short iTagNumber = 0;
		//iTagLength = param3;  //
		iTagNumber = param1;  //
		unsigned char *pBuffer = NULL;
		pBuffer = (unsigned char *)param2;
		//param4

		if(iTagNumber== 0) return;
		int iIndex = 0;
		int iLength = 0;
		unsigned char *pID;
		unsigned char bPackLength = 0;
		unsigned char bIDLen = 0;

        char buf[512]={0};

		for(iIndex = 0; iIndex < iTagNumber; iIndex++)
		{
            bPackLength = pBuffer[iLength];
            pID = (unsigned char *)&pBuffer[1 + iLength];
            string str1="", str2="", strTemp="";

            sprintf(buf,"Type:%.2X ", pID[0]);
            if((pID[0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
            {
                  iIDLen = bPackLength - 7;
            }
            else iIDLen = bPackLength - 1;
            strTemp = buf;

            str2 = str2 + strTemp;  //Tag Type

            sprintf(buf,"Ant:%.2X Tag:", pID[1]);
            strTemp = buf;

            str2 = str2 + strTemp;  //Ant
            for (int i = 2; i < iIDLen; i++)
            {
                sprintf(buf,"%.2X ", pID[i]);
                str1 = buf;
                str2 = str2 + str1;
            }
            sprintf(buf,"RSSI:%.2X", pID[iIDLen]);
            strTemp = buf;

            str2 = str2 + strTemp;  //RSSI
            cout<<str2<<endl;
            iLength = iLength + bPackLength + 1;
		}
	}
	else if(msg == 1) //Device Out
	{
		cout<<"No Device"<<endl;
	}
	else if(msg == 0) //Device Insert
	{
		cout<<"Device Insert"<<endl;
	}
}

int main()
{
    cout << "DemoSystem" << endl;
    cout << "OpenDevice:Please input device description like /dev/ttyAMA0 or /dev/ttyUSB0" << endl;
    char strDev[256]={0};

    //cin>>strDev;
    if(SWCom_OpenDevice((char *)"/dev/ttyUSB0",115200) == FALSE)
    //if(SWCom_OpenDevice(strDev,115200) == FALSE)
    {
        cout << "open error" << endl;
        return 0;
    }
    cout << "open success" << endl;

    cout << "[0]:ReadRFPower" << endl;
    cout << "[1]:SetRFpower" << endl;
    cout << "[2]:WriteTag" << endl;
    cout << "[3]:RelayOn" << endl;
    cout << "[4]:RelayOff" << endl;
    cout << "[5]:ReadTag in answermode" << endl;
    cout << "[6]:ReadTag in activemode(callback function)" << endl;
    cout << "[7]:stop reading" << endl;
    cout << "[8]:start reading" << endl;

    cout << "Please input key" << endl;

    int key=0;
    cin>>key;

    //SWCom_StopRead(0xFF);
    unsigned char bValue = 0;
    unsigned char bParamAddr = 0;
    string str;
    char buf[16]={0};

    unsigned char Password[4] = {0x00,0x00,0x00,0x00};
    unsigned char Mem = 1;  //EPC   3:USER
    unsigned char WordPtr = 2;  //EPC First Address
    unsigned char WriteLen = 6; //6 Words, 12 bytes data
    unsigned char Writedata[12]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB};

    int i=0;
    switch(key)
    {
        case 0://readRFPower
                /*01: Transport
                02: WorkMode
                03: DeviceAddr
                04: FilterTime
                05: RFPower
                06: BeepEnable
                07: UartBaudRate*/
            bParamAddr = 0x05;
            if (SWCom_ReadDeviceOneParam(0xFF,bParamAddr, &bValue) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            sprintf(buf,"%d",bValue);
            str=buf;
            cout<<str<<endl;
            break;
        case 1: //SetRF
                /*01: Transport
                02: WorkMode
                03: DeviceAddr
                04: FilterTime
                05: RFPower
                06: BeepEnable
                07: UartBaudRate*/
            bParamAddr = 0x05;  //05: RFPower
            //bValue = 26;  //RF 26dBm
            cout<<"Please input RFValue"<<endl;
            cin >>bValue;
            if (SWCom_SetDeviceOneParam(0xFF,bParamAddr, bValue) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;
        case 2://WriteTag
            if (SWCom_WriteCardG2(0xFF,Password,Mem,WordPtr,WriteLen,Writedata) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;
        case 3://RelayOn
            if (SWCom_RelayOn(0xFF) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;
        case 4://RelayOff
            if (SWCom_RelayOff(0xFF) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;
        case 5: //AnswerMode
            for(i=0; i <100;i++)
            {
                ReadAnswerMode();
                usleep(10000);  //delay 10ms
            }
            break;
        case 6://callback mode
            //SWCom_StartRead(0xFF);
            cout<<"Q: exit"<<endl;
            SWCom_SetCallback(CallBackFunc);
            break;
        case 7://stop
            if (SWCom_StopRead(0xFF) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;
        case 8://start
            if (SWCom_StartRead(0xFF) == FALSE)
            {
                cout<<"Failed"<<endl;
                return 0;
            }
            cout<<"Success"<<endl;
            break;

    }
    if(key != 6) cout<<"demo exit"<<endl;
    while(1)
    {
        cin>>key;
        if(key == 'Q')
        {
            SWCom_SetCallback(NULL);
        }
    }
    SWCom_CloseDevice();
    return 0;
}
