package com.readerapi;

public class netserverapi {
    static {
        System.loadLibrary("NetServerApi");
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    /******** Func: Open Device  *******************************/
    //  Param:
    //         iPort: IP Port example: 60000
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiListening(int iPort);
    /******** Func: Close Device *******************************/
    //  Param: None
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native void NetApiCloseDevice();

    static public native boolean NetApiGetTotalClientIPAndSocket(int[] iCnt, byte[] IPInfo);
    /******** Func: GetDeviceInfo. 9Bytes**********/
    //  Param: iSock: Connect sock
    //         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiGetDeviceSystemInfo(int iSock, byte pucSystemInfo[]);
    /******** Func: Get Device One Param**********/
    //  Param: iSock: Connect sock
    //         pucDevParamAddr: Param Addr
    //         pValue: Return Param Value
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiReadDeviceOneParam(int iSock,byte pucDevParamAddr,byte pValue[]);
    /******** Func: Set Device One Param**********/
    //  Param: iSock: Connect sock
    //         pucDevParamAddr: Param Addr
    //         bValue: Param
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiSetDeviceOneParam(int iSock,byte pucDevParamAddr,byte pValue);
    /******** Func: Stop all RF reading**********/
    //  Param: iSock: Connect sock
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiStopRead(int iSock);
    /******** Func: Start all RF reading**********/
    //  Param: iSock: Connect sock
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiStartRead(int iSock);
    /******** Func: Inventory EPC**********/
    //  Param: iSock: Connect sock
    //         pBuffer: Get Buffer
    //         Totallen: Get Buffer Length
    //         CardNum: Tag Number
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiInventoryG2(int iSock, byte[] pBuffer, int[] Totallen, int[] CardNum);
    /******** Func: Write EPC**********/
    //  Param: iSock: Connect sock
    //         Password: Password (4 bytes)
    //         WriteEPC: Write Data
    //         WriteEPClen: Write Length
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiWriteEPCG2(int iSock, byte[] Password, byte[] WriteEPC, byte WriteEPClen);
    /******** Func: Read Card**********/
    //  Param: iSock: Connect sock
    //         Password: Password (4 bytes)
    //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    //         WordPtr:  Start Address
    //         ReadEPClen: Read Length
    //         Data: Read Data
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiReadCardG2(int iSock, byte[] Password, byte Mem, byte WordPtr, byte ReadEPClen, byte[] Data);
    /******** Func: Write Card**********/
    //  Param: iSock: Connect sock
    //         Password: Password (4 bytes)
    //         Mem:      0:Reserved 1:EPC 2:TID 3:USER
    //         WordPtr:  Start Address
    //         WriteEPC: Write Data
    //         WriteEPClen: Write Length
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiWriteCardG2(int iSock, byte[] Password, byte Mem, byte WordPtr, byte Writelen, byte[] Writedata);
    /******** Func: RelayOn**********/
    //  Param: iSock: Connect sock
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiRelayOn(int iSock);
    /******** Func: RelayOff**********/
    //  Param: iSock: Connect sock
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiRelayOff(int iSock);
    /******** Func: ClearTagBuf(ActiveMode)**********/
    //  Param: None
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native boolean NetApiClearTagBuf();
    /******** Func: GetTagBuf(ActiveMode)**********/
    //  Param:
    //         pBuf: Get Buffer
    //         pLength: Get Buffer Length
    //         pTagNumber: Tag Number
    //  Return: Success return 1, failed return 0
    /*********************************************************/
    static public native byte NetApiGetTagBuf(byte[] pBuf, int[] pLength, int[] pTagNumber);
    /******** Func: SetFreq**********/
    //  Param: iSock: Connect sock
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
    static public native boolean NetApiSetFreq(int iSock, byte[] pFreq);
    /******** Func: ReadFreq**********/
    //  Param: iSock: Connect sock
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
    static public native boolean NetApiReadFreq(int iSock, byte[] pFreq);
}
