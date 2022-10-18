#ifndef _SWHidAPI_H_
#define _SWHidAPI_H_

#define SWSDK_API __declspec(dllimport)

/******** Func: Get Usb Device Number**********/
//  Param: None
//  Return: Success return number, failed return 0
/*********************************************************/
extern "C" int SWSDK_API SWHid_GetUsbCount(void);

/******** Func: Get USB HID value**********/
//  Param: iIndex: HID Index 0,1,2....
//         pucDeviceInfo: HID value
//  Return: Success return number, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_GetUsbInfo(unsigned short iIndex, char *pucDeviceInfo);

/******** Func: Open Device  *******************************/
//  Param: iIndex: HID Index 0,1,2....
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_OpenDevice(unsigned short iIndex);

/******** Func: Close Device *******************************/
//  Param: None
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_CloseDevice(void);

/******** Func: GetDeviceInfo. 9Bytes**********/
//  Param: bDevAdr: 0xFF 
//         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_GetDeviceSystemInfo(unsigned char bDevAdr,unsigned char *pucSystemInfo);

/******** Func: Get Device One Param**********/
//  Param: bDevAdr: 0xFF
//         pucDevParamAddr: Param Addr			
//         pValue: Return Param Value
//         ucParamLength: Return Param Length 
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_ReadDeviceOneParam(unsigned char bDevAdr,unsigned char pucDevParamAddr,unsigned char *pValue);

/******** Func: Set Device One Param**********/
//  Param: bDevAdr: 0xFF
//         pucDevParamAddr: Param Addr		
//         bValue: Param	
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_SetDeviceOneParam(unsigned char bDevAdr,unsigned char pucDevParamAddr,unsigned char bValue);

/******** Func: Stop all RF reading**********/
//  Param: bDevAdr: 0xFF
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_StopRead(unsigned char bDevAdr);

/******** Func: Start all RF reading**********/
//  Param: bDevAdr: 0xFF
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_StartRead(unsigned char bDevAdr);

/*
* Callback function prototype
* msg == 0: Device Insert
* msg == 1: Device Out
* msg == 2: param1 means tag number, param2 means tagdata, param3 means tagdata length,param4 means DevSN
*/
typedef void ( * FUNPTR_ACTIVE_CALLBACK)(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4);
extern "C" int SWSDK_API SWHid_SetCallback(FUNPTR_ACTIVE_CALLBACK pfAddr);

/******** Func: Inventory EPC**********/
//  Param: bDevAdr: 0xFF
//         pBuffer: Get Buffer
//         Totallen: Get Buffer Length
//         CardNum: Tag Number
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_InventoryG2(unsigned char bDevAdr, unsigned char *pBuffer, unsigned short * Totallen, unsigned short *CardNum);

/******** Func: Write EPC**********/
//  Param: bDevAdr: 0xFF
//         Password: Password (4 bytes)
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_WriteEPCG2(unsigned char bDevAdr, unsigned char * Password, unsigned char * WriteEPC, unsigned char WriteEPClen);

/******** Func: Read Card**********/
//  Param: bDevAdr: 0xFF
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address 
//         ReadEPClen: Read Length
//         Data: Read Data
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_ReadCardG2 (unsigned char bDevAdr, unsigned char * Password ,unsigned char Mem, unsigned char WordPtr, unsigned char ReadEPClen, unsigned char * Data);

/******** Func: Write Card**********/
//  Param: bDevAdr:  0xFF
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address 
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_WriteCardG2(unsigned char bDevAdr, unsigned char * Password, unsigned char Mem, unsigned char WordPtr,unsigned char Writelen, unsigned char * Writedata);

/******** Func: RelayOn**********/
//  Param: bDevAdr: 0xFF
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_RelayOn(unsigned char bDevAdr);

/******** Func: RelayOff**********/
//  Param: bDevAdr: 0xFF
//  Return: Success return 1, failed return 0
/*********************************************************/
extern "C" BOOL SWSDK_API SWHid_RelayOff(unsigned char bDevAdr);

/******** Func: SetFreq**********/
//  Param: bDevAdr: 0xFF
//         pFreq:Set 2bytes Freq Value
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
extern "C" BOOL SWSDK_API SWHid_SetFreq(unsigned char bDevAdr, unsigned char *pFreq);

/******** Func: ReadFreq**********/
//  Param: bDevAdr: 0xFF
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
extern "C" BOOL SWSDK_API SWHid_ReadFreq(unsigned char bDevAdr, unsigned char *pFreq);

#endif

