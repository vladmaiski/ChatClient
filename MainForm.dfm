object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'ChitChat'
  ClientHeight = 326
  ClientWidth = 564
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWhite
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 272
    Top = 277
    Width = 34
    Height = 13
    Caption = '0/1000'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
    StyleElements = []
  end
  object MsgToLabel: TLabel
    Left = 24
    Top = 277
    Width = 28
    Height = 13
    Caption = 'to: All'
  end
  object DevInf: TLabel
    Left = 429
    Top = 316
    Width = 133
    Height = 10
    Caption = 'Developed by Vlad Maiski BSUIR 2020'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGrayText
    Font.Height = -8
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
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
  object ListBox1: TListBox
    Left = 424
    Top = 24
    Width = 130
    Height = 220
    ItemHeight = 13
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object MsgBox: TEdit
    Left = 24
    Top = 250
    Width = 290
    Height = 21
    TabOrder = 2
    TextHint = 'Type your message here...'
    OnChange = MsgBoxChange
    OnKeyPress = MsgBoxKeyPress
  end
  object ChatBox: TRichEdit
    Left = 24
    Top = 24
    Width = 378
    Height = 220
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    HideScrollBars = False
    Lines.Strings = (
      'ChatBox')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
    Zoom = 100
  end
end
