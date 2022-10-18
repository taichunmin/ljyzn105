package com;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.*;
import com.sun.jna.ptr.*;

public class Function {
	public interface RFID extends Library{		
		RFID instance = (RFID)Native.loadLibrary("SWHidApi", RFID.class);
		//******** Func: Get Usb Device Number**********/
		//  Param: None
		//  Return: Success return number, failed return 0
		//*********************************************************/
		public int SWHid_GetUsbCount();
		//******** Func: Get USB HID value**********/
        //  Param: iIndex: HID Index 0,1,2....
        //         pucDeviceInfo: HID value
        //  Return: Success return number, failed return 0
        //*********************************************************/
		public boolean SWHid_GetUsbInfo(int iIndex, char[] pucDeviceInfo);
        //******** Func: Open Device  *******************************/
        //  Param: iIndex: HID Index 0,1,2....
        //  Return: Success return 1, failed return 0
        //*********************************************************/
		public boolean SWHid_OpenDevice(int b);
        //******** Func: Close Device *******************************/
        //  Param: None
        //  Return: Success return 1, failed return 0
        //*********************************************************/
		public boolean SWHid_CloseDevice();
        //******** Func: GetDeviceInfo. 9Bytes**********/
        //  Param: bDevAdr: 0xFF
        //         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_GetDeviceSystemInfo(byte bDevAdr, byte[] pucSystemInfo);
        //******** Func: Get Device One Param**********/
        //  Param: bDevAdr: 0xFF
        //         pucDevParamAddr: Param Addr			
        //         pValue: Return Param Value 
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_ReadDeviceOneParam(byte bDevAdr, byte pucDevParamAddr, byte[] pValue);
        //******** Func: Set Device One Param**********/
        //  Param: bDevAdr: 0xFF
        //         pucDevParamAddr: Param Addr		
        //         bValue: Param	
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_SetDeviceOneParam(byte bDevAdr, byte pucDevParamAddr, byte bValue);
        //******** Func: Stop all RF reading**********/
        //  Param: bDevAdr: 0xFF
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_StopRead(byte bDevAdr);
        //******** Func: Start all RF reading**********/
        //  Param: bDevAdr:0xFF
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_StartRead(byte bDevAdr);
        //******** Func: Inventory EPC**********/
        //  Param: bDevAdr: 0xFF
        //         pBuffer: Get Buffer
        //         Totallen: Get Buffer Length
        //         CardNum: Tag Number
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_InventoryG2(byte bDevAdr, byte[] pBuffer, short[] Totallen, short[] CardNum);
        //******** Func: Write EPC**********/
        //  Param: bDevAdr: 0xFF
        //         Password: Password (4 bytes)
        //         WriteEPC: Write Data
        //         WriteEPClen: Write Length
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_WriteEPCG2(byte bDevAdr, byte[] Password, byte[] WriteEPC, byte WriteEPClen);
        //******** Func: Read Card**********/
        //  Param: bDevAdr: 0xFF
        //         Password: Password (4 bytes)
        //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
        //         WordPtr:  Start Address 
        //         ReadEPClen: Read Length
        //         Data: Read Data
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_ReadCardG2(byte bDevAdr, byte[] Password, byte Mem, byte WordPtr, byte ReadEPClen, byte[] Data);
        //******** Func: Write Card**********/
        //  Param: bDevAdr: 0xFF
        //         Password: Password (4 bytes)
        //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
        //         WordPtr:  Start Address 
        //         WriteEPC: Write Data
        //         WriteEPClen: Write Length
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_WriteCardG2(byte bDevAdr, byte[] Password, byte Mem, byte WordPtr, byte Writelen, byte[] Writedata);
        //******** Func: RelayOn**********/
        //  Param: bDevAdr:  0xFF
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_RelayOn(byte bDevAdr);
        //******** Func: RelayOff**********/
        //  Param: bDevAdr: 0xFF
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_RelayOff(byte bDevAdr);
        //******** Func: ClearTagBuf(ActiveMode)**********/
        //  Param: None
        //  Return: Success return 1, failed return 0
        //*********************************************************/
	    public boolean SWHid_ClearTagBuf();
        //******** Func: GetTagBuf(ActiveMode)**********/
        //  Param: 
        //         pBuf: Get Buffer
        //         pLength: Get Buffer Length
        //         pTagNumber: Tag Number
        //  Return:Success return 1, failed return 0
        //*********************************************************/
	    public byte SWHid_GetTagBuf(byte[] pBuf, int[] pLength, int[] pTagNumber);
        //******** Func: SetFreq**********/
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
        //*********************************************************/
	    public boolean SWHid_SetFreq(byte bDevAdr, byte[] pFreq);
        //******** Func: ReadFreq**********/
        //  Param: bDevAdr:  0xFF
        //         pFreq:return 2bytes Freq Value
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
        //*********************************************************/
	    public boolean SWHid_ReadFreq(byte bDevAdr, byte[] pFreq);
	}
}

