object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'ChitChat'
  ClientHeight = 372
  ClientWidth = 595
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 327
    Top = 250
    Width = 75
    Height = 25
    Caption = 'Send'
    TabOrder = 0
    OnClick = Button1Click
  end
  object MsgBox: TEdit
    Left = 24
    Top = 250
    Width = 290
    Height = 21
    TabOrder = 1
    TextHint = 'Type your message here...'
  end
  object ChatBox: TMemo
    Left = 24
    Top = 24
    Width = 378
    Height = 220
    Lines.Strings = (
      'ChatBox')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
end
