unit Unit1;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, SWHidApi;

type
  TForm1 = class(TForm)
    btnOpen: TButton;
    btnClose: TButton;
    EditShow: TRichEdit;
    Button1: TButton;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    ComboBox1: TComboBox;
    Button30: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    ComboBox2: TComboBox;
    procedure btnOpenClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button30Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
var
  Form1: TForm1;

implementation

{$R *.dfm}

function ShowList(str: String):Boolean;
  begin
    if Form1.EditShow.Lines.count > 30 then
         begin
            Form1.EditShow.Clear();
         end;

    Form1.EditShow.Lines.Add(str);
    SendMessage(Form1.EditShow.Handle,WM_VScroll,sb_Bottom,0);
  end;


function ShowTag(Totallen:Word;CardNum:Word;pBuffer:PByte):Boolean;
var
  iIndex:Word;
  i:Word;
  iLength:Word;
  bPackLength:Byte;
  bIDLen:Byte;
  str1:String;
  str2:String;
  str3:String;
begin
     iLength := 0;
     str1 := '';
     str2 := '';
     for iIndex := 0 to CardNum-1 do
         begin
             str1 := '';
             str2 := '';
             bPackLength := Ord(pBuffer[iLength]);
             str1 := IntToHex(Ord(pBuffer[1 + iLength + 0]),2);
             if (pBuffer[1 + iLength + 0] and $80) =  $80 then
               begin
                bIDLen := bPackLength - 7;  // with TimeStamp , last 6 bytes is time
               end
             else
               begin
                bIDLen := bPackLength - 1;
               end;

             str2 := str2 + 'Type:'+str1+' ';       //Tag Type
             str1 := IntToHex(Ord(pBuffer[1 + iLength + 1]),2);
             str2 := str2 + 'Ant:' + str1+' Tag:';  //Ant
             str3 := '';
             for i := 2 to ord(bIDLen) - 1 do
                 begin
                     str1 := IntToHex(Ord(pBuffer[1 + iLength + i]),2);
                     str3 := str3 + str1+' ';
                 end;
             str2 := str2 + str3;
             str1 := IntToHex(Ord(pBuffer[1 + iLength + i]),2);
             str2 := str2 + 'RSSI:' + str1;  //RSSI
             iLength := iLength + Ord(bPackLength) + 1;
             ShowList(str2);
         end;
end;

procedure ActiveCallback(msg:Integer;tagnum:Integer;tagdata:PByte;devsn:PByte);cdecl;
begin
     if msg = 2 then
       begin
          if tagnum <> 0 then
            begin
               ShowTag(0, tagnum, @(tagdata[0]));
            end;
       end
     else  if msg = 1 then
       begin
         ShowList('No Device');
       end
     else  if msg = 0 then
       begin
         ShowList('Device Insert');
       end;
end;

procedure TForm1.btnCloseClick(Sender: TObject);
begin
      SWHid_SetCallback(nil);
      SWHid_CloseDevice();
      ShowList('Close');
      btnOpen.Enabled := true;
      btnClose.Enabled :=false;

      Button2.Enabled := true;
      Button3.Enabled :=true;
      Button4.Enabled :=false;
end;

procedure TForm1.btnOpenClick(Sender: TObject);   //Open
var pucSystemInfo: array[0..255] of Byte;
 strShow:String;
 str:String ;
 I: Integer;
begin
    if ComboBox1.ItemIndex >= 0 then
      if SWHid_OpenDevice(ComboBox1.ItemIndex) then
      begin
          EditShow.Lines.Add('Open Success');
          if SWHid_GetDeviceSystemInfo($FF, @(pucSystemInfo[0])) then
            begin
                strShow :=  'SoftVer:' + IntToHex((pucSystemInfo[0]) shr 4,2) + '.' +IntToHex((pucSystemInfo[0]) and 15,2);
                ShowList(strShow);
                strShow :=  'HardVer:' + IntToHex((pucSystemInfo[1]) shr 4,2) + '.' +IntToHex((pucSystemInfo[1]) and 15,2);
                ShowList(strShow);
                str := 'SN:';
                for I := 0 to 7 do
                begin
                    str:= str+IntToHex(ord(pucSystemInfo[2+i]),2);
                end;
                EditShow.Lines.Add(str);
            end;
          //else
          //  begin
          //      SWHid_CloseDevice();
          //      ShowList('Device is out');
          //  end;
          btnOpen.Enabled := false;
          btnClose.Enabled :=true;
      end
      else
          begin
              ShowList('Failed');
          end;
end;

procedure TForm1.Button1Click(Sender: TObject);
var Password: array[0..4] of Byte;
    Mem:Byte;
    WordPtr:Byte ;
    Writelen: Integer;
    Writedata: array[0..16] of Byte;
begin    //WriteTag
    Password[0] := 0;
    Password[1] := 0;
    Password[2] := 0;
    Password[3] := 0;
    Mem := 1;
    WordPtr := 2;
    Writelen := 6;
    Writedata[0] := $00;Writedata[1] := $11;Writedata[2] := $22;Writedata[3] := $33;
    Writedata[4] := $44;Writedata[5] := $55;Writedata[6] := $66;Writedata[7] := $77;
    Writedata[8] := $88;Writedata[9] := $99;Writedata[10] := $AA;Writedata[11] := $BB;
    if SWHid_WriteCardG2($FF,@(Password[0]),Mem,WordPtr,Writelen,@(Writedata[0])) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;



procedure TForm1.Button2Click(Sender: TObject);
begin
    ShowList('ActiveMode');
	SWHid_SetCallback(ActiveCallback);
    Button4.Enabled := true;
    Button2.Enabled :=false;
    Button3.Enabled :=false;
end;

procedure TForm1.Button3Click(Sender: TObject);
var pBuffer:array[0..2048] of Byte;
    Totallen:array[0..2] of Byte;
    CardNum:array[0..2] of Byte;
    iTotallen:Word;
    iCardNum:Word;
begin
    CardNum[0] := 0; CardNum[1] := 0;
    Totallen[0] := 0; Totallen[1] := 0;
    if SWHid_InventoryG2($FF,@(pBuffer[0]),@(Totallen[0]),@(CardNum[0])) then
        begin
            iTotallen := Totallen[0] + Totallen[1] * 256;
            iCardNum :=  CardNum[0] + CardNum[1] * 256;
            if iCardNum = 0 then
                begin
                    ShowList('NoData');
                end
            else
                begin  //ShowData
                    ShowTag(iTotallen, iCardNum, @(pBuffer[0]));
                end;
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin    //stop
    ShowList('Stop');
    SWHid_SetCallback(nil);
    Button2.Enabled := true;
    Button3.Enabled :=true;
    Button4.Enabled :=false;
end;

procedure TForm1.Button30Click(Sender: TObject);
var
  arrHidName:array[0..512] of Byte;
  iHidNum: Integer;
  i: Integer;
  j: Integer;
  str:String;
begin
  ComboBox1.Items.Clear;
	iHidNum := SWHid_GetUsbCount();
  for i := 0 to iHidNum-1 do
         begin
           SWHid_GetUsbInfo(i, @(arrHidName[0]));
           str:= '';
           For j:=low(arrHidName) to high(arrHidName) do
              begin
                str:=str+char(arrHidName[j]);
              end;
           ComboBox1.Items.Add(str);
         end;
	ComboBox1.ItemIndex :=0;
end;


procedure TForm1.Button5Click(Sender: TObject);
var Value: array[0..2] of Byte;
    DevParamAddr:Byte;
    str1:String;
begin
	  //01: Transport
		//02: WorkMode
		//03: DeviceAddr
		//04: FilterTime
		//05: RFPower
		//06: BeepEnable
		//07: UartBaudRate
    DevParamAddr := 5;

	  if SWHid_ReadDeviceOneParam($FF,DevParamAddr,@(Value[0])) then
        begin
             str1 := IntToHex(Ord(Value[0]),2);
             ShowList(str1);
             ComboBox2.ItemIndex := Ord(Value[0]);
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button6Click(Sender: TObject);
var Value:Byte;
    DevParamAddr:Byte;
    str1:String;
begin
	  //01: Transport
		//02: WorkMode
		//03: DeviceAddr
		//04: FilterTime
		//05: RFPower
		//06: BeepEnable
		//07: UartBaudRate
    DevParamAddr := 5;
    //Value := 26;  //RFPower = 26
    Value := Ord(ComboBox2.ItemIndex);
	  if SWHid_SetDeviceOneParam($FF,DevParamAddr,Value) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
	  if SWHid_RelayOn($FF) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
	  if SWHid_RelayOff($FF) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

end.

