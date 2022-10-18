unit Unit1;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, SWNetServerApi;

type
  TForm1 = class(TForm)
    btnOpen: TButton;
    btnClose: TButton;
    EditShow: TRichEdit;
    Button1: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    ComboBox2: TComboBox;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    Edit1: TEdit;
    Edit2: TEdit;
    Button2: TButton;
    Button3: TButton;
    procedure btnOpenClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
   g_iSock:Word;
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

procedure ServerCallback(msg:Integer;pIP:PByte;iSock:Integer;tagLength:Integer;tagdata:PByte;tagNumber:Integer;devsn:PByte);cdecl;
var
 strIP:String;
 strSock:String;
 strSN:String;
 i:Word;
 str1:String;
 iIP:byte;
begin
     strIP := '';
     while pIP[i] > 0 do    //Get IP
        begin
           iIP := Ord(pIP[i]);
           SetLength(str1, 1);
           Move(iIP, str1[1], 1);
           strIP := strIP + str1;
           i := i +1;
        end;
     strSock := IntToStr(iSock);
     if msg = 2 then
       begin
          for i := 0 to 6 do
              begin
                 str1 := IntToHex(Ord(devsn[i]),2);
                 strSN := strSN + str1;
              end;
          ShowList(strIP+':'+strSock+' ' +strSN +' ');
          if tagNumber <> 0 then
            begin
               ShowTag(0, tagNumber, @(tagdata[0]));
            end;
       end
     else  if msg = 1 then
       begin
         ShowList(strIP+':'+strSock+' Disconnnect');
       end
     else  if msg = 0 then
       begin
         Form1.Edit1.Text := strSock;
         ShowList(strIP+':'+strSock+' Connect');
       end;
       //Warning:The ShowTag and  ShowList have bug with multi-connect, it can not show at the same time.
       //you can solve with fifo technology.
end;

procedure TForm1.btnCloseClick(Sender: TObject);
begin
      SWNet_CloseAllSocket();   //close all running socket, if not close first, will memory crash
      Sleep(1000);         //the delay time need bigger if many clients connect
      SWNet_SetCallback(nil);
      SWNet_CloseDevice();
      ShowList('Close');
      btnOpen.Enabled := true;
      btnClose.Enabled :=false;
end;

procedure TForm1.btnOpenClick(Sender: TObject);   //Open
var pucSystemInfo: array[0..255] of Byte;
 strShow:String;
 str:String ;
 iSock:Integer;
begin
      iSock :=  strtoint(Edit2.Text);
      if SWNet_Listening(iSock) then
      begin
          EditShow.Lines.Add('Open Success');
          btnOpen.Enabled := false;
          btnClose.Enabled :=true;
          SWNet_SetCallback(ServerCallback);
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
var
   iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
    //WriteTag
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
    if SWNet_WriteCardG2(iSock,@(Password[0]),Mem,WordPtr,Writelen,@(Writedata[0])) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
	  if SWNet_StopRead(iSock) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
   iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
	  if SWNet_StartRead(iSock) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button5Click(Sender: TObject);
var Value: array[0..2] of Byte;
    DevParamAddr:Byte;
    str1:String;
    iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
	  //01: Transport
		//02: WorkMode
		//03: DeviceAddr
		//04: FilterTime
		//05: RFPower
		//06: BeepEnable
		//07: UartBaudRate
    DevParamAddr := 5;

	  if SWNet_ReadDeviceOneParam(iSock,DevParamAddr,@(Value[0])) then
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
    iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
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
	  if SWNet_SetDeviceOneParam(iSock,DevParamAddr,Value) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button7Click(Sender: TObject);
var
   iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
	  if SWNet_RelayOn(iSock) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

procedure TForm1.Button8Click(Sender: TObject);
var
   iSock:Integer;
begin
    iSock :=  strtoint(Edit1.Text);
	  if SWNet_RelayOff(iSock) then
        begin
            ShowList('Success');
        end
    else
        begin
            ShowList('Failed');
        end;
end;

end.
