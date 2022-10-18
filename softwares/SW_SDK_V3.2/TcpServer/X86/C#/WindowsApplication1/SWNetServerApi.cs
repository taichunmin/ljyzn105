using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace RFID
{
    public class SWNetServerApi
    {
        /******** Func: Listening *******************************/
        //  Param: 
        //         iSocket: Listening Socket example: 65000
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_Listening(UInt16 iSocket);

        /******** Func: Close Device *******************************/
        //  Param: None
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_CloseDevice();

        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_GetTotalClientIPAndSocket(out int iCnt, byte[] IPInfo);

        /******** Func: GetDeviceInfo. 9Bytes**********/
        //  Param:  iSocket: Socket
        //          pucSystemInfo:SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_GetDeviceSystemInfo(int iSocket, byte[] pucSystemInfo);

        /******** Func: Get Device One Param**********/
        //  Param: iSocket: Socket
        //         pucDevParamAddr: Param Addr			
        //         pValue: Return Param Value
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_ReadDeviceOneParam(int iSocket, byte pucDevParamAddr, byte[] pValue);

        /******** Func: Set Device One Param**********/
        //  Param: iSocket: Socket
        //         pucDevParamAddr: Param Addr		
        //         bValue: Param	
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_SetDeviceOneParam(int iSocket, byte pucDevParamAddr, byte bValue);
        
        /******** Func: Stop all RF reading**********/
        //  Param: iSocket: Socket
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_StopRead(int iSocket);
        
        /******** Func: Start all RF reading**********/
        //  Param:  iSocket: Socket
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_StartRead(int iSocket);

        /******** Func: Inventory EPC**********/
        //  Param: iSocket: Socket
        //         pBuffer: Get Buffer
        //         Totallen: Get Buffer Length
        //         CardNum: Tag Number
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_InventoryG2(int iSocket, byte[] pBuffer, out ushort Totallen, out ushort CardNum);

        /******** Func: Write EPC**********/
        //  Param: iSocket: Socket
        //         Password: Password (4 bytes)
        //         WriteEPC: Write Data
        //         WriteEPClen: Write Length
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_WriteEPCG2(int iSocket, byte[] Password, byte[] WriteEPC, byte WriteEPClen);

        /******** Func: Read Card**********/
        //  Param: iSocket: Socket
        //         Password: Password (4 bytes)
        //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
        //         WordPtr:  Start Address 
        //         ReadEPClen: Read Length
        //         Data: Read Data
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_ReadCardG2(int iSocket, byte[] Password, byte Mem, byte WordPtr, byte ReadEPClen, byte[] Data);

        /******** Func: Write Card**********/
        //  Param: iSocket: Socket
        //         Password: Password (4 bytes)
        //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
        //         WordPtr:  Start Address 
        //         WriteEPC: Write Data
        //         WriteEPClen: Write Length
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_WriteCardG2(int iSocket, byte[] Password, byte Mem, byte WordPtr, byte Writelen, byte[] Writedata);
    
        /******** Func: RelayOn**********/
        //  Param: iSocket: Socket
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_RelayOn(int iSocket);

        /******** Func: RelayOff**********/
        //  Param: iSocket: Socket
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_RelayOff(int iSocket);

        /******** Func: ClearTagBuf(ActiveMode)**********/
        //  Param: None
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_ClearTagBuf();

        /******** Func: GetTagBuf(ActiveMode)**********/
        //  Param: 
        //         pBuf: Get Buffer
        //         pTotalCnt: Get Buffer Length
        //         pLineCnt: Line Number
        //  Return: Success return 1, failed return 0
        /*********************************************************/
        [DllImport("SWNetServerApi.dll")]
        public static extern byte SWNet_GetTagBuf(byte[] pBuf, out int pTotalCnt, out int pLineCnt);

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
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_SetFreq(int iSocket, byte[] pFreq);

        /******** Func: ReadFreq**********/
        //  Param: iSocket: Socket
        //         pFreq: return 2bytes Freq Value
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
        [DllImport("SWNetServerApi.dll")]
        public static extern bool SWNet_ReadFreq(int iSocket, byte[] pFreq);
    }
}
