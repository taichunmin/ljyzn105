#ifndef _SWNetAPI_H_
#define _SWNetAPI_H_

#define SWSDK_API __declspec(dllimport)

/******** Func: GetHostName *******************************/
//  Param: sLocalName: return HostName
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_GetLocalHostIPName(unsigned char *sLocalName);

/******** Func: EnableNetAnswer*******************************/
//  Param: None
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" void  SWSDK_API SWNet_EnableNetAnswer(void);

/******** Func: DisableNetAnswer*******************************/
//  Param: None
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" void  SWSDK_API SWNet_DisableNetAnswer(void);

/******** Func: GetTotalClientSocketCnt*******************************/
//  Param: None
//  Return: GetTotalClientSocketCnt
/*********************************************************/
extern "C" int   SWSDK_API SWNet_GetTotalClientSocketCnt(void); 

/******** Func: TCP Listening *******************************/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_Listening(unsigned short iSocket);

/******** Func: Close Device *******************************/
//  Param: None
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_CloseDevice(void);
extern "C" BOOL SWSDK_API SWNet_CloseAllSocket(void);

/******** Func: GetDeviceInfo. 9Bytes**********/
//  Param: iSocket: Socket
//         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_GetDeviceSystemInfo(int iSocket,unsigned char *pucSystemInfo);

/******** Func: Get Device One Param**********/
//  Param: iSocket: Socket
//         pucDevParamAddr: Param Addr			
//         pValue: Return Param Value
//         ucParamLength: Return Param Length 
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_ReadDeviceOneParam(int iSocket,unsigned char pucDevParamAddr,unsigned char *pValue);

/******** Func: Set Device One Param**********/
//  Param: iSocket: Socket
//         pucDevParamAddr: Param Addr		
//         bValue: Param	
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_SetDeviceOneParam(int iSocket,unsigned char pucDevParamAddr,unsigned char bValue);

/******** Func: Stop all RF reading**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_StopRead(int iSocket);

/******** Func: Start all RF reading**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_StartRead(int iSocket);

/******** Func: Inventory EPC**********/
//  Param: iSocket: Socket
//         pBuffer: Get Buffer
//         Totallen: Get Buffer Length
//         CardNum: Tag Number
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_InventoryG2(int iSocket, unsigned char *pBuffer, unsigned short * Totallen, unsigned short *CardNum);

/******** Func: Write EPC**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_WriteEPCG2(int iSocket, unsigned char * Password, unsigned char * WriteEPC, unsigned char WriteEPClen);

/******** Func: Read Card**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address 
//         ReadEPClen: Read Length
//         Data: Read Data
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_ReadCardG2 (int iSocket, unsigned char * Password ,unsigned char Mem, unsigned char WordPtr, unsigned char ReadEPClen, unsigned char * Data);

/******** Func: Write Card**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address 
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_WriteCardG2(int iSocket, unsigned char * Password, unsigned char Mem, unsigned char WordPtr,unsigned char Writelen, unsigned char * Writedata);

/******** Func: RelayOn**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_RelayOn(int iSocket);

/******** Func: RelayOff**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_RelayOff(int iSocket);

/*
* Callback function prototype
* msg == 0: Device Insert
* msg == 1: Device Out
* msg == 2: Active data comming. param1 means IP, param2 means Socket, param3 means tagdata length,param4 means Data, param5 means tagCnt,param6 means DevSN 
*/
typedef void ( * FUNPTR_SERVER_CALLBACK)(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6);
extern "C" int SWSDK_API SWNet_SetCallback(FUNPTR_SERVER_CALLBACK pfAddr);

/******** Func: SetFreq**********/
//  Param: iSocket: Socket
//         pFreq: Set 2bytes Freq Value
	//pFreq[0]   pFreq[1]
	//0x31        0x80     //US Freq
	//0x4E        0x00     //Europe
	//0x2C        0xA3     //China
	//0x29        0x9D     //Korea
	//0x2E        0x9F     //Australia
	//0x4E        0x00     //New Zealand
	//0x4E        0x00     //India
	//0x2C        0x81     //Singapore
	//0x2C        0xA3     //Hongkong
	//0x31        0xA7     //Taiwan
	//0x31        0x80     //Canada
	//0x31        0x80     //Mexico
	//0x31        0x99     //Brazil
	//0x1C        0x99     //Israel
	//0x24        0x9D     //South Africa
	//0x2C        0xA3     //Thailand
	//0x28        0xA1     //Malaysia
	//0x29        0x9D     //Japan
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_SetFreq(int iSock, unsigned char *pFreq);

/******** Func: ReadFreq**********/
//  Param: iSocket: Socket
//         pFreq: Return 2bytes Freq Value
	//pFreq[0]   pFreq[1]
	//0x31        0x80     //US Freq
	//0x4E        0x00     //Europe
	//0x2C        0xA3     //China
	//0x29        0x9D     //Korea
	//0x2E        0x9F     //Australia
	//0x4E        0x00     //New Zealand
	//0x4E        0x00     //India
	//0x2C        0x81     //Singapore
	//0x2C        0xA3     //Hongkong
	//0x31        0xA7     //Taiwan
	//0x31        0x80     //Canada
	//0x31        0x80     //Mexico
	//0x31        0x99     //Brazil
	//0x1C        0x99     //Israel
	//0x24        0x9D     //South Africa
	//0x2C        0xA3     //Thailand
	//0x28        0xA1     //Malaysia
	//0x29        0x9D     //Japan
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWNet_ReadFreq(int iSock, unsigned char *pFreq);

#endif

