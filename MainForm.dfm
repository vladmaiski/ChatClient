object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'ChitChat'
  ClientHeight = 330
  ClientWidth = 570
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWhite
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 272
    Top = 277
    Width = 34
    Height = 13
    Caption = '0/1000'
    Color = clBackground
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNone
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
    StyleElements = []
  end
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
    OnChange = MsgBoxChange
    OnKeyPress = MsgBoxKeyPress
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
  object ListBox1: TListBox
    Left = 424
    Top = 24
    Width = 130
    Height = 220
    ItemHeight = 13
    TabOrder = 3
  end
end
