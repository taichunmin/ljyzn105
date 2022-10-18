#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>

#include "SWNetServerApi.h"

#define FALSE 0
#define TRUE  1

using namespace std;


void CallBackFunc(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6)
{
	string IP;
	char buf[512]={0};
	IP = (char *)param1;
	string strSock;
	sprintf(buf,"%d", param2);
	strSock= buf;
	string strSN="";
	if(msg == 2)
	{
		sprintf(buf,"SN:%.2X%.2X%.2X%.2X%.2X%.2X%.2X",param6[0],param6[1],param6[2],param6[3],param6[4],param6[5],param6[6]);
		strSN = buf;
    }
	string strInfo;
	strInfo = IP + ":"+strSock+" "+strSN+" ";
	if (msg == 2)  //Data
	{
		unsigned short iTagLength = 0;
		unsigned short iTagNumber = 0;
		iTagLength = param3;  //
		iTagNumber = param5;  //
		unsigned char *pBuffer = NULL;
		pBuffer = (unsigned char *)param4;
		//param4

		if(iTagNumber== 0) return;
		int iIndex = 0;
		int iLength = 0;
		unsigned char *pID;
		unsigned char bPackLength = 0;
		int iIDLen = 0;

		for(iIndex = 0; iIndex < iTagNumber; iIndex++)
		{
			bPackLength = pBuffer[iLength];
			pID = (unsigned char *)&pBuffer[1 + iLength];

			string str1="", str2="", strTemp="";

			sprintf(buf,"Type:%.2X ", pID[0]);
			strTemp = buf;
			if((pID[0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
			{
				iIDLen = bPackLength - 7;
			}
			else iIDLen = bPackLength - 1;
			str2 = str2 + strTemp;  //Tag Type
			sprintf(buf,"Ant:%.2X Tag:", pID[1]);
			strTemp = buf;
			str2 = str2 + strTemp;  //Ant
			for (int i = 2; i < iIDLen; i++)
			{
				sprintf(buf,"%.2X ",pID[i]);
				str1 = buf;
				str2 = str2 + str1;
			}
			sprintf(buf,"RSSI:%.2X", pID[iIDLen]);
			strTemp =buf;
			str2 = str2 + strTemp;  //RSSI

			cout<<strInfo + str2<<endl;
			iLength = iLength + bPackLength + 1;
		}
	}
	else if(msg == 1) //Device Out
	{
		cout<<"Disconnect"<<endl;
	}
	else if(msg == 0) //Device Insert
	{
		cout<<strInfo + "Connect"<<endl;
	}
}

int main()
{
    cout << "DemoSystem" << endl;
    cout << "TcpServer: 60000 port , listening..." << endl;
    //cin>>strDev>>iPort;
    //if(SWNet_OpenDevice((char *)"192.168.1.250",60000) == FALSE)
    if(SWNet_Listening(60000) == FALSE)
    {
        cout << "Listening error" << endl;
        return 0;
    }
    cout << "Listening success" << endl;
    SWNet_SetCallback(CallBackFunc);
    while(1)
    {
    }
    SWNet_SetCallback(NULL);
    SWNet_CloseDevice();
    return 0;
}
