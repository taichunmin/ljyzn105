object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'USB'
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
    Left = 13
    Top = 39
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 0
    OnClick = btnOpenClick
  end
  object btnClose: TButton
    Left = 8
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 1
    OnClick = btnCloseClick
  end
  object EditShow: TRichEdit
    Left = 8
    Top = 169
    Width = 399
    Height = 169
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
    Left = 314
    Top = 70
    Width = 75
    Height = 25
    Caption = 'WriteTag'
    TabOrder = 3
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 101
    Width = 208
    Height = 62
    Caption = 'ActiveMode CallBack'
    TabOrder = 4
    object Button2: TButton
      Left = 24
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Reading'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button4: TButton
      Left = 120
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Stop'
      TabOrder = 1
      OnClick = Button4Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 222
    Top = 101
    Width = 185
    Height = 62
    Caption = 'AnswerMode'
    TabOrder = 5
    object Button3: TButton
      Left = 56
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Read'
      TabOrder = 0
      OnClick = Button3Click
    end
  end
  object ComboBox1: TComboBox
    Left = 24
    Top = 8
    Width = 145
    Height = 21
    TabOrder = 6
  end
  object Button5: TButton
    Left = 314
    Top = 8
    Width = 75
    Height = 25
    Caption = 'ReadRFPower'
    TabOrder = 7
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 314
    Top = 39
    Width = 75
    Height = 25
    Caption = 'SetRFPower'
    TabOrder = 8
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 128
    Top = 70
    Width = 75
    Height = 25
    Caption = 'RelayOn'
    TabOrder = 9
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 222
    Top = 70
    Width = 75
    Height = 25
    Caption = 'RelayOff'
    TabOrder = 10
    OnClick = Button8Click
  end
  object Button30: TButton
    Left = 94
    Top = 39
    Width = 75
    Height = 25
    Caption = 'Scan'
    TabOrder = 12
    OnClick = Button30Click
  end
  object ComboBox2: TComboBox
    Left = 209
    Top = 8
    Width = 99
    Height = 21
    TabOrder = 11
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
end
