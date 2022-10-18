#ifndef _SWTcpServerAPI_H_
#define _SWTcpServerAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/******** Func: GetTotalClientSocketCnt*******************************/
//  Param: None
//  Return: GetTotalClientSocketCnt
/*********************************************************/
int  SWNet_GetTotalClientSocketCnt(void);

/******** Func: TCP Listening *******************************/
//  Param: iSocket: ListeningSocket
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_Listening(unsigned short iSocket);

/******** Func: Close Device *******************************/
//  Param: None
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_CloseDevice(void);
char SWNet_CloseAllSocket(void);

/******** Func: GetDeviceInfo. 9Bytes**********/
//  Param: iSocket: Socket
//         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_GetDeviceSystemInfo(int iSocket,unsigned char *pucSystemInfo);

/******** Func: Get Device One Param**********/
//  Param: iSocket: Socket
//         pucDevParamAddr: Param Addr
//         pValue: Return Param Value
//         ucParamLength: Return Param Length
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_ReadDeviceOneParam(int iSocket,unsigned char pucDevParamAddr,unsigned char *pValue);

/******** Func: Set Device One Param**********/
//  Param: iSocket: Socket
//         pucDevParamAddr: Param Addr
//         bValue: Param
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_SetDeviceOneParam(int iSocket,unsigned char pucDevParamAddr,unsigned char bValue);

/******** Func: Stop all RF reading**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_StopRead(int iSocket);

/******** Func: Start all RF reading**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_StartRead(int iSocket);

/******** Func: Inventory EPC**********/
//  Param: iSocket: Socket
//         pBuffer: Get Buffer
//         Totallen: Get Buffer Length
//         CardNum: Tag Number
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_InventoryG2(int iSocket, unsigned char *pBuffer, unsigned short * Totallen, unsigned short *CardNum);

/******** Func: Write EPC**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_WriteEPCG2(int iSocket, unsigned char * Password, unsigned char * WriteEPC, unsigned char WriteEPClen);

/******** Func: Read Card**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address
//         ReadEPClen: Read Length
//         Data: Read Data
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_ReadCardG2 (int iSocket, unsigned char * Password ,unsigned char Mem, unsigned char WordPtr, unsigned char ReadEPClen, unsigned char * Data);

/******** Func: Write Card**********/
//  Param: iSocket: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_WriteCardG2(int iSocket, unsigned char * Password, unsigned char Mem, unsigned char WordPtr,unsigned char Writelen, unsigned char * Writedata);

/******** Func: RelayOn**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_RelayOn(int iSocket);

/******** Func: RelayOff**********/
//  Param: iSocket: Socket
//  Return: Success return 1, failed return 0
/*********************************************************/
char SWNet_RelayOff(int iSocket);

/*
* Callback function prototype
* msg == 0: Device Insert
* msg == 1: Device Out
* msg == 2: Active data comming. param1 means IP, param2 means Socket, param3 means tagdata length,param4 means Data, param5 means tagCnt,param6 means DevSN
*/
typedef void (*callback)(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6);
int SWNet_SetCallback(callback pfAddr);

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
char SWNet_SetFreq(int iSock, unsigned char *pFreq);

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
char SWNet_ReadFreq(int iSock, unsigned char *pFreq);

#ifdef __cplusplus
}
#endif

#endif

