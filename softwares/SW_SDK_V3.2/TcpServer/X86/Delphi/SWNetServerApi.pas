unit SWNetServerApi;

interface

//******** Func: Listening  *******************************/
//  iPort: IP Port example: 60000
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_Listening(iPort:Word):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Close Device *******************************/
//  Param: None
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_CloseDevice():Boolean;cdecl;external 'SWNetServerApi.dll';
function SWNet_CloseAllSocket():Boolean;cdecl;external 'SWNetServerApi.dll';
//******** Func: GetDeviceInfo. 9Bytes**********/
//  Param: iSock: Socket
//         pucSystemInfo: SysInfo  9Bytes 1:SoftVer 2:HardVer 3 - 9:DeviceSN
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_GetDeviceSystemInfo(iSock:Integer; pucSystemInfo:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Get Device One Param**********/
//  Param: iSock: Socket
//         pucDevParamAddr: Param Addr
//         pValue: Return Param Value
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_ReadDeviceOneParam(iSock:Integer; DevParamAddr:Byte;pValue:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Set Device One Param**********/
//  Param: iSock: Socket
//         pucDevParamAddr: Param Addr
//         bValue: Param
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_SetDeviceOneParam(iSock:Integer; DevParamAddr:Byte;bValue:Byte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Stop all RF reading**********/
//  Param: iSock: Socket
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_StopRead(iSock:Integer):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Start all RF reading**********/
//  Param: iSock: Socket
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_StartRead(iSock:Integer):Boolean;cdecl;external 'SWNetServerApi.dll';

type  FUNPTR_SERVER_CALLBACK=procedure(msg:Integer;pIP:PByte;iSock:Integer;tagLength:Integer;tagdata:PByte;tagNumber:Integer;devsn:PByte);cdecl;
function  SWNet_SetCallback(pActiveCallback:FUNPTR_SERVER_CALLBACK):Integer;cdecl;external 'SWNetServerApi.dll';

//******** Func: Inventory EPC**********/
//  Param: iSock: Socket
//         pBuffer: Get Buffer
//         Totallen: Get Buffer Length
//         CardNum: Tag Number
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_InventoryG2(iSock:Integer;pBuffer:PByte;Totallen:PByte;CardNum:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Write EPC**********/
//  Param: iSock: Socket
//         Password: Password (4 bytes)
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_WriteEPCG2(iSock:Integer;Password:PByte;WriteEPC:PByte;WriteEPClen:Byte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Read Card**********/
//  Param: iSock: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address
//         ReadEPClen: Read Length
//         Data: Read Data
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_ReadCardG2(iSock:Integer;Password:PByte;Mem:Byte;WordPtr:Byte;ReadEPClen:Byte;ReadData:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: Write Card**********/
//  Param: iSock: Socket
//         Password: Password (4 bytes)
//         Mem:      0:Reserved 1:EPC 2:TID 3:USER
//         WordPtr:  Start Address
//         WriteEPC: Write Data
//         WriteEPClen: Write Length
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_WriteCardG2(iSock:Integer;Password:PByte;Mem:Byte;WordPtr:Byte;Writelen:Byte;Writedata:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: RelayOn**********/
//  Param: iSock: Socket
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_RelayOn(iSock:Integer):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: RelayOff**********/
//  Param: iSock: Socket
//  Return: Success return 1, failed return 0
//*********************************************************/
function SWNet_RelayOff(iSock:Integer):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: SetFreq**********/
//  Param: iSock: Socket
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
//*********************************************************/
function SWNet_SetFreq(iSock:Integer;pFreq:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

//******** Func: ReadFreq**********/
//  Param: iSock: Socket
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
//*********************************************************/
function SWNet_ReadFreq(iSock:Integer;pFreq:PByte):Boolean;cdecl;external 'SWNetServerApi.dll';

implementation

end.