object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'NetServer'
  ClientHeight = 346
  ClientWidth = 415
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object btnOpen: TButton
    Left = 24
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Listening'
    TabOrder = 0
    OnClick = btnOpenClick
  end
  object btnClose: TButton
    Left = 120
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 1
    OnClick = btnCloseClick
  end
  object EditShow: TRichEdit
    Left = 8
    Top = 152
    Width = 399
    Height = 186
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      '')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Button1: TButton
    Left = 332
    Top = 70
    Width = 75
    Height = 25
    Caption = 'WriteTag'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 106
    Top = 8
    Width = 48
    Height = 21
    TabOrder = 4
    Text = '60000'
  end
  object Button5: TButton
    Left = 332
    Top = 8
    Width = 75
    Height = 25
    Caption = 'ReadRFPower'
    TabOrder = 5
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 332
    Top = 39
    Width = 75
    Height = 25
    Caption = 'SetRFPower'
    TabOrder = 6
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 222
    Top = 110
    Width = 75
    Height = 25
    Caption = 'RelayOn'
    TabOrder = 7
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 222
    Top = 70
    Width = 75
    Height = 25
    Caption = 'RelayOff'
    TabOrder = 9
    OnClick = Button8Click
  end
  object ComboBox2: TComboBox
    Left = 227
    Top = 12
    Width = 99
    Height = 21
    TabOrder = 8
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16'
      '17'
      '18'
      '19'
      '20'
      '21'
      '22'
      '23'
      '24'
      '25'
      '26'
      '27'
      '28'
      '29'
      '30')
  end
  object StaticText1: TStaticText
    Left = 24
    Top = 8
    Width = 66
    Height = 17
    Caption = 'ListeningPort'
    TabOrder = 10
  end
  object StaticText2: TStaticText
    Left = 24
    Top = 35
    Width = 76
    Height = 17
    Caption = 'Current Socket'
    TabOrder = 11
  end
  object Edit1: TEdit
    Left = 106
    Top = 35
    Width = 48
    Height = 21
    TabOrder = 12
    Text = '0'
  end
  object Button2: TButton
    Left = 24
    Top = 110
    Width = 75
    Height = 25
    Caption = 'StopRead'
    TabOrder = 13
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 120
    Top = 110
    Width = 75
    Height = 25
    Caption = 'StartRead'
    TabOrder = 14
    OnClick = Button3Click
  end
end
