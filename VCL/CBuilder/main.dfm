object fmMain: TfmMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Drone Remote ID Receiver'
  ClientHeight = 678
  ClientWidth = 957
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object btStart: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 0
    OnClick = btStartClick
  end
  object btStop: TButton
    Left = 89
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Stop'
    TabOrder = 1
    OnClick = btStopClick
  end
  object lbLog: TListBox
    Left = 8
    Top = 544
    Width = 941
    Height = 126
    ItemHeight = 13
    TabOrder = 2
  end
  object btClear: TButton
    Left = 874
    Top = 513
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 3
    OnClick = btClearClick
  end
  object tvDrones: TTreeView
    Left = 8
    Top = 47
    Width = 201
    Height = 460
    HideSelection = False
    Indent = 19
    ReadOnly = True
    RowSelect = True
    TabOrder = 4
    OnClick = tvDronesClick
  end
  object lvDetails: TListView
    Left = 215
    Top = 47
    Width = 734
    Height = 460
    Columns = <
      item
        Caption = 'Parameter'
        Width = 150
      end
      item
        Caption = 'Value'
        Width = 540
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 5
    ViewStyle = vsReport
  end
  object WiFiClient: TwclWiFiClient
    AfterOpen = WiFiClientAfterOpen
    BeforeClose = WiFiClientBeforeClose
    Left = 72
    Top = 184
  end
  object WiFiEvents: TwclWiFiEvents
    AfterOpen = WiFiEventsAfterOpen
    BeforeClose = WiFiEventsBeforeClose
    OnAcmInterfaceArrival = WiFiEventsAcmInterfaceArrival
    OnAcmInterfaceRemoval = WiFiEventsAcmInterfaceRemoval
    OnAcmScanComplete = WiFiEventsAcmScanComplete
    OnAcmScanFail = WiFiEventsAcmScanFail
    OnMsmRadioStateChange = WiFiEventsMsmRadioStateChange
    Left = 72
    Top = 240
  end
  object BluetoothManager: TwclBluetoothManager
    AfterOpen = BluetoothManagerAfterOpen
    OnClosed = BluetoothManagerClosed
    Left = 72
    Top = 296
  end
  object BeaconWatcher: TwclBluetoothLeBeaconWatcher
    OnDriAsdMessage = BeaconWatcherDriAsdMessage
    OnStarted = BeaconWatcherStarted
    OnStopped = BeaconWatcherStopped
    Left = 72
    Top = 360
  end
end
