object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Sign up'
  ClientHeight = 265
  ClientWidth = 483
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 112
    Top = 64
    Width = 25
    Height = 13
    Caption = 'Login'
  end
  object Label2: TLabel
    Left = 112
    Top = 112
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object Label3: TLabel
    Left = 328
    Top = 112
    Width = 34
    Height = 13
    Caption = 'Show'
    OnMouseMove = Label3MouseMove
    OnMouseLeave = Label3MouseLeave
  end
  object Edit1: TEdit
    Left = 192
    Top = 61
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 192
    Top = 109
    Width = 121
    Height = 21
    TabOrder = 1
    TextHint = 'Enter your login'
  end
  object Button1: TButton
    Left = 168
    Top = 160
    Width = 89
    Height = 33
    Caption = 'Log In'
    TabOrder = 2
    OnClick = Button1Click
  end
end