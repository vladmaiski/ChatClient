object Form3: TForm3
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Registration'
  ClientHeight = 285
  ClientWidth = 498
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 96
    Top = 72
    Width = 45
    Height = 13
    Caption = 'Nickname'
  end
  object Label2: TLabel
    Left = 96
    Top = 107
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object Button1: TButton
    Left = 192
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Registrate'
    TabOrder = 0
    OnClick = Button1Click
  end
  object NicknameField: TEdit
    Left = 168
    Top = 69
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object PasswordField: TEdit
    Left = 168
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 2
  end
end
