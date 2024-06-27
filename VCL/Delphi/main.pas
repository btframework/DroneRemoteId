unit main;

interface

uses
  Vcl.Forms, Vcl.Controls, Vcl.StdCtrls, wclWiFi, System.Classes, Vcl.ComCtrls,
  wclDriCommon, wclDriAsd, wclBluetooth;

type
  TfmMain = class(TForm)
    WiFiClient: TwclWiFiClient;
    WiFiEvents: TwclWiFiEvents;
    btStart: TButton;
    btStop: TButton;
    lbLog: TListBox;
    btClear: TButton;
    tvDrones: TTreeView;
    lvDetails: TListView;
    BluetoothManager: TwclBluetoothManager;
    BeaconWatcher: TwclBluetoothLeBeaconWatcher;
    procedure btClearClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure WiFiEventsMsmRadioStateChange(Sender: TObject;
      const IfaceId: TGUID; const State: TwclWiFiPhyRadioState);
    procedure WiFiEventsAcmInterfaceArrival(Sender: TObject;
      const IfaceId: TGUID);
    procedure WiFiEventsAcmInterfaceRemoval(Sender: TObject;
      const IfaceId: TGUID);
    procedure FormDestroy(Sender: TObject);
    procedure WiFiClientAfterOpen(Sender: TObject);
    procedure WiFiClientBeforeClose(Sender: TObject);
    procedure WiFiEventsAfterOpen(Sender: TObject);
    procedure WiFiEventsBeforeClose(Sender: TObject);
    procedure btStopClick(Sender: TObject);
    procedure btStartClick(Sender: TObject);
    procedure WiFiEventsAcmScanFail(Sender: TObject; const IfaceId: TGUID;
      const Reason: Integer);
    procedure WiFiEventsAcmScanComplete(Sender: TObject; const IfaceId: TGUID);
    procedure tvDronesClick(Sender: TObject);
    procedure BeaconWatcherDriAsdMessage(Sender: TObject; const Address: Int64;
      const Timestamp: Int64; const Rssi: SByte; const Raw: TwclDriRawData);
    procedure BluetoothManagerAfterOpen(Sender: TObject);
    procedure BluetoothManagerClosed(Sender: TObject);
    procedure BeaconWatcherStarted(Sender: TObject);
    procedure BeaconWatcherStopped(Sender: TObject);

  private
    FId: TGUID;
    FBtParser: TwclDriAsdParser;
    FParser: TwclWiFiDriParser;
    FRootNode: TTreeNode;
    FScanActive: Boolean;

    procedure EnumInterfaces;

    procedure Trace(const Msg: string); overload;
    procedure Trace(const Msg: string; const Res: Integer); overload;

    procedure AdapterDisabled;
    procedure RestartScan;
    procedure StartScan;
    procedure StopScan;

    function FindDrone(const Ssid: string): TTreeNode;
    function MessageTypeToText(const Message: TwclDriAsdMessage): string;

    function AsdVerticalAccuracyToText(
      const Accuracy: TwclDriAsdUavVerticalAccuracy): string;
    function AsdHeightReferenceToText(
      const Reference: TwclDriAsdUavHeightReference): string;
    function AsdHorizontalAccuracyToText(
      const Accuracy: TwclDriAsdUavHorizontalAccuracy): string;
    function AsdSpeedAccuracyToText(
      const Accuracy: TwclDriAsdUavSpeedAccuracy): string;
    function AsdStatusToText(const Status: TwclDriAsdUavStatus): string;
    function AsdTimestampAccuracyToText(
      const Accuracy: TwclDriAsdUavTimestampAccuracy): string;
    function AsdAltitudeToText(const Altitude: Single): string;
    function AsdDescriptionTypeToText(
      const DescriptionType: TwclDriAsdDescriptionType): string;
    function AsdDirectionToText(const Direction: Word): string;
    function AsdHorizontalSpeedToText(const Speed: Single): string;
    function AsdLatLonToText(const LatLon: Double): string;
    function AsdOperatorClassificationToText(
      const Classification: TwclDriAsdOperatorClassification): string;
    function AsdLocationTypeToText(
      const Location: TwclDriAsdOperatorLocationType): string;
    function AsdEuUavCategoryToText(
      const Category: TwclDriAsdUavEuCategory): string;
    function AsdEuUavClassToText(
      const UavClass: TwclDriAsdUavEuClass): string;
    function AsdIdTypeToText(const IdType: TwclDriAsdIdType): string;
    function AsdUavTypeToText(const UavType: TwclDriAsdUavType): string;
    function VendorToText(const Message: TwclDriMessage): string;

    procedure ShowAsdLocationMessage(
      const Message: TwclDriAsdLocationMessage);
    procedure ShowAsdSelfIdMessage(const Message: TwclDriAsdSelfIdMessage);
    procedure ShowAsdOperatorIdMessage(
      const Message: TwclDriAsdOperatorIdMessage);
    procedure ShowAsdSystemMessage(const Message: TwclDriAsdSystemMessage);
    procedure ShowAsdBassicIdMessage(
      const Message: TwclDriAsdBasicIdMessage);
    procedure ShowUnknownAsdMessage(const Message: TwclDriAsdMessage);

    procedure ClearMessageDetails;
    procedure GetDriInfo;
    procedure UpdateAsdMessageDetails(const Ssid: string;
      const Message: TwclDriAsdMessage);
    procedure UpdateDroneMessages(const Node: TTreeNode; const Messages: TList);
    procedure UpdateMessageDetails(const Ssid: string;
      const Message: TwclDriMessage);
    procedure UpdateMessages(const Ssid: string; const Messages: TList);
  end;

var
  fmMain: TfmMain;

implementation

{$R *.dfm}

uses
  wclHelpers, wclErrors, SysUtils, ActiveX, Contnrs;

procedure TfmMain.Trace(const Msg: string);
begin
  lbLog.Items.Add(Msg);
  lbLog.TopIndex := lbLog.Items.Count - 1;
end;

procedure TfmMain.Trace(const Msg: string; const Res: Integer);
begin
  Trace(Msg + ': 0x' + IntToHex(Res, 8));
end;

procedure TfmMain.tvDronesClick(Sender: TObject);
begin
  ClearMessageDetails;

  if tvDrones.Selected <> nil then begin
    if tvDrones.Selected.Data <> nil then begin
      UpdateMessageDetails(tvDrones.Selected.Parent.Text,
        TwclDriMessage(tvDrones.Selected.Data));
    end;
  end;
end;

procedure TfmMain.WiFiClientAfterOpen(Sender: TObject);
begin
  Trace('WiFi Client opened');
end;

procedure TfmMain.WiFiClientBeforeClose(Sender: TObject);
begin
  Trace('WiFi Client closed');
end;

procedure TfmMain.WiFiEventsAcmInterfaceArrival(Sender: TObject;
  const IfaceId: TGUID);
begin
  if CompareMem(@FId, @GUID_NULL, SizeOf(TGUID)) then
    EnumInterfaces;
end;

procedure TfmMain.WiFiEventsAcmInterfaceRemoval(Sender: TObject;
  const IfaceId: TGUID);
begin
  if CompareMem(@FId, @IfaceId, SizeOf(TGUID)) then begin
    Trace('Adapter removed');

    AdapterDisabled;
  end;
end;

procedure TfmMain.WiFiEventsAcmScanComplete(Sender: TObject;
  const IfaceId: TGUID);
begin
  if FScanActive and CompareMem(@FId, @IfaceId, SizeOf(TGUID)) then begin
    GetDriInfo;

    RestartScan;
  end;
end;

procedure TfmMain.WiFiEventsAcmScanFail(Sender: TObject; const IfaceId: TGUID;
  const Reason: Integer);
begin
  if FScanActive and CompareMem(@FId, @IfaceId, SizeOf(TGUID)) then begin
    Trace('Scan failed', Reason);

    RestartScan;
  end;
end;

procedure TfmMain.WiFiEventsAfterOpen(Sender: TObject);
begin
  Trace('WiFi Events opened');
end;

procedure TfmMain.WiFiEventsBeforeClose(Sender: TObject);
begin
  Trace('WiFi Events closed');
end;

procedure TfmMain.WiFiEventsMsmRadioStateChange(Sender: TObject;
  const IfaceId: TGUID; const State: TwclWiFiPhyRadioState);
begin
  if CompareMem(@FId, @GUID_NULL, SizeOf(TGUID)) then
    EnumInterfaces

  else begin
    if CompareMem(@FId, @IfaceId, SizeOf(TGUID)) then begin
      if (State.SoftwareState = rsOff) or (State.HardwareState = rsOff) then
      begin
        Trace('Adapter disabled');

        AdapterDisabled;
      end;
    end;
  end;
end;

procedure TfmMain.AdapterDisabled;
begin
  StopScan;
  FId := GUID_NULL;
end;

procedure TfmMain.btClearClick(Sender: TObject);
begin
  lbLog.Items.Clear;
end;

procedure TfmMain.btStartClick(Sender: TObject);
begin
  StartScan;
end;

procedure TfmMain.btStopClick(Sender: TObject);
begin
  StopScan;
end;

procedure TfmMain.ClearMessageDetails;
begin
  lvDetails.Items.Clear;
end;

procedure TfmMain.EnumInterfaces;
var
  Res: Integer;
  Ifaces: TwclWiFiInterfaces;
  i: Integer;
  Iface: TwclWiFiInterface;
  States: TwclWiFiPhyRadioStates;
  Found: Boolean;
  j: Integer;
  Enabled: Boolean;
begin
  Res := WiFiClient.EnumInterfaces(Ifaces);
  if Res <> WCL_E_SUCCESS then
    Trace('Enum interfaces failed', Res)

  else begin
    if Length(Ifaces) = 0 then
      Trace('No one WiFi interface found')

    else begin
      Found := False;
      for i := 0 to Length(Ifaces) - 1 do begin
        Iface := TwclWiFiInterface.Create(Ifaces[i].Id);
        if Iface.Open = WCL_E_SUCCESS then begin
          Res := Iface.GetRadioState(States);
          if Res = WCL_E_SUCCESS then begin
            if Length(States) > 0 then begin
              Enabled := False;
              for j := 0 to Length(States) - 1 do begin
                Enabled := (States[i].SoftwareState = rsOn) and
                   (States[i].HardwareState = rsOn);
                if not Enabled then
                  Break;
              end;

              Found := Enabled;
            end;
          end;

          if Found then
            FId := Iface.Id;
          Iface.Close;
        end;
        Iface.Free;

        if Found then
          Break;
      end;

      if Found then
        Trace('Use WiFi interface ' + GUIDToString(FId));
    end;
  end;
end;

procedure TfmMain.FormCreate(Sender: TObject);
begin
  FBtParser := TwclDriAsdParser.Create;
  FParser := TwclWiFiDriParser.Create;
  FScanActive := False;
  FRootNode := nil;

  btStart.Enabled := True;
  btStop.Enabled := False;
end;

procedure TfmMain.FormDestroy(Sender: TObject);
begin
  StopScan;

  FBtParser.Free;
  FParser.Free;
end;

function TfmMain.FindDrone(const Ssid: string): TTreeNode;
var
  DroneNode: TTreeNode;
begin
  Result := nil;

  DroneNode := FRootNode.getFirstChild;
  while DroneNode <> nil do begin
    if DroneNode.Text = Ssid then begin
      Result := DroneNode;
      Break;
    end;

    DroneNode := FRootNode.GetNextChild(DroneNode);
  end;

  if Result = nil then begin
    Result := tvDrones.Items.AddChild(FRootNode, Ssid);
    FRootNode.Expand(True);
  end;
end;

function TfmMain.MessageTypeToText(
  const Message: TwclDriAsdMessage): string;
begin
  case Message.MessageType of
    mtBasicId:
      Result := 'BASIC ID';
    mtLocation:
      Result := 'LOCATION';
    mtAuth:
      Result := 'AUTH';
    mtSelfId:
      Result := 'SELF ID';
    mtSystem:
      Result := 'SYSTEM';
    mtOperatorId:
      Result := 'OPERATOR ID';
    else
      Result := 'UNKNOWN';
  end;
end;

function TfmMain.AsdVerticalAccuracyToText(
  const Accuracy: TwclDriAsdUavVerticalAccuracy): string;
begin
  case Accuracy of
    vaUnknown:
      Result := 'Unknow';
    va150M:
      Result := '150 m';
    va45M:
      Result := '45 m';
    va25M:
      Result := '25 m';
    va10M:
      Result := '10 m';
    va3M:
      Result := '3 m';
    va1M:
      Result := '1 m';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Accuracy), 2);
  end;
end;

procedure TfmMain.BeaconWatcherDriAsdMessage(Sender: TObject;
  const Address: Int64; const Timestamp: Int64; const Rssi: SByte;
  const Raw: TwclDriRawData);
var
  Messages: TList;
begin
  Messages := TList.Create;
  if FBtParser.Parse(Raw, Messages) = WCL_E_SUCCESS then begin
    if Messages.Count > 0 then
      UpdateMessages(IntToHex(Address, 12), Messages);
  end;
  Messages.Free;
end;

procedure TfmMain.BeaconWatcherStarted(Sender: TObject);
begin
  Trace('Bluetooth scan started');
end;

procedure TfmMain.BeaconWatcherStopped(Sender: TObject);
begin
  Trace('Bluetooth scan stopped');
end;

procedure TfmMain.BluetoothManagerAfterOpen(Sender: TObject);
begin
  Trace('Bluetooth manager opened');
end;

procedure TfmMain.BluetoothManagerClosed(Sender: TObject);
begin
  Trace('Bluetooth manager closed');
end;

function TfmMain.AsdHeightReferenceToText(
  const Reference: TwclDriAsdUavHeightReference): string;
begin
  case Reference of
    hrTakeOff:
      Result := 'Take off';
    hrGround:
      Result := 'Ground';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Reference), 2);
  end;
end;

function TfmMain.AsdHorizontalAccuracyToText(
  const Accuracy: TwclDriAsdUavHorizontalAccuracy): string;
begin
  case Accuracy of
    haUnknown:
      Result := 'Unknown';
    ha10Nm:
      Result := '10 miles';
    ha4Nm:
      Result := '4 miles';
    ha2Nm:
      Result := '2 miles';
    ha1Nm:
      Result := '1 mile';
    ha05Nm:
      Result := '0.5 mile';
    ha03Nm:
      Result := '0.3 mile';
    ha01Nm:
      Result := '0.1 mile';
    ha005Nm:
      Result := '0.05 mile';
    ha30M:
      Result := '30 meters';
    ha10M:
      Result := '10 meters';
    ha3M:
      Result := '3 meters';
    ha1M:
      Result := '1 meter';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Accuracy), 2);
  end;
end;

function TfmMain.AsdSpeedAccuracyToText(
  const Accuracy: TwclDriAsdUavSpeedAccuracy): string;
begin
  case Accuracy of
    saUnknown:
      Result := 'Unknown';
    sa10MS:
      Result := '10 m/s';
    sa3MS:
      Result := '3 m/s';
    sa1Ms:
      Result := '1 m/s';
    sa03Ms:
      Result := '0.3 m/s';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Accuracy), 2);
  end;
end;

function TfmMain.AsdStatusToText(const Status: TwclDriAsdUavStatus): string;
begin
  case Status of
    usUndeclared:
      Result := 'Undeclared';
    usGround:
      Result := 'Ground';
    usAirborne:
      Result := 'Airborne';
    usEmergency:
      Result := 'Emergency';
    usFailure:
      Result := 'Failure';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Status), 2);
  end;
end;

function TfmMain.AsdTimestampAccuracyToText(
  const Accuracy: TwclDriAsdUavTimestampAccuracy): string;
begin
  case Accuracy of
    taUnknown:
      Result := 'Unknown';
    ta01s:
      Result := '0.1 second';
    ta02s:
      Result := '0.2 second';
    ta03s:
      Result := '0.3 second';
    ta04s:
      Result := '0.4 second';
    ta05s:
      Result := '0.5 second';
    ta06s:
      Result := '0.6 second';
    ta07s:
      Result := '0.7 second';
    ta08s:
      Result := '0.8 second';
    ta09s:
      Result := '0.9 second';
    ta1s:
      Result := '1 second';
    ta11s:
      Result := '1.1 second';
    ta12s:
      Result := '1.2 second';
    ta13s:
      Result := '1.3 second';
    ta14s:
      Result := '1.4 second';
    ta15s:
      Result := '1.5 second';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Accuracy), 2);
  end;
end;

function TfmMain.AsdAltitudeToText(const Altitude: Single): string;
begin
  if Altitude = -1000 then
    Result := 'Invalid'
  else
    Result := FloatToStr(Altitude);
end;

function TfmMain.AsdDescriptionTypeToText(
  const DescriptionType: TwclDriAsdDescriptionType): string;
begin
  case DescriptionType of
    dtText:
      Result := 'Text';
    dtEmergency:
      Result := 'Emergency';
    dtExtended:
      Result := 'Extended';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(DescriptionType), 2);
  end;
end;

function TfmMain.AsdDirectionToText(const Direction: Word): string;
begin
  if Direction > 360 then
    Result := 'Invalid'
  else
    Result := IntToStr(Direction);
end;

function TfmMain.AsdHorizontalSpeedToText(const Speed: Single): string;
begin
  if Speed = 255 then
    Result := 'Invalid'
  else
    Result := FloatToStr(Speed);
end;

function TfmMain.AsdLatLonToText(const LatLon: Double): string;
begin
  if LatLon = 0 then
    Result := 'Invalid'
  else
    Result := FloatToStr(LatLon);
end;

function TfmMain.AsdOperatorClassificationToText(
  const Classification: TwclDriAsdOperatorClassification): string;
begin
  case Classification of
    ocUndeclared:
      Result := 'Undeclared';
    ocEu:
      Result := 'EU';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Classification), 2);
  end;
end;

function TfmMain.AsdLocationTypeToText(
  const Location: TwclDriAsdOperatorLocationType): string;
begin
  case Location of
    ltTakeOff:
      Result := 'Take off';
    ltLiveGnss:
      Result := 'Live GNSS';
    ltFixed:
      Result := 'Fixed';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Location), 2);
  end;
end;

function TfmMain.AsdEuUavCategoryToText(
  const Category: TwclDriAsdUavEuCategory): string;
begin
  case Category of
    ucUndeclared:
      Result := 'Undeclared';
    ucOpen:
      Result := 'Open';
    ucSpecific:
      Result := 'Specific';
    ucCertified:
      Result := 'Certified';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(Category), 2);
  end;
end;

function TfmMain.AsdEuUavClassToText(
  const UavClass: TwclDriAsdUavEuClass): string;
begin
  case UavClass of
    ucUnspecified:
      Result := 'Unspecified';
    ucClass0:
      Result := 'Class 0';
    ucClass1:
      Result := 'Class 1';
    ucClass2:
      Result := 'Class 2';
    ucClass3:
      Result := 'Class 3';
    ucClass4:
      Result := 'Class 4';
    ucClass5:
      Result := 'Class 5';
    ucClass6:
      Result := 'Class 6';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(UavClass), 2);
  end;
end;

function TfmMain.AsdIdTypeToText(const IdType: TwclDriAsdIdType): string;
begin
  case IdType of
    itNone:
      Result := 'None';
    itSerialNumber:
      Result := 'Serial number';
    itCaaRegistrationId:
      Result := 'CAA registration ID';
    itUtmAssignedUuid:
      Result := 'UTM assigned UUID';
    itSpecificSessionId:
      Result := 'Specific session ID';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(IdType), 2);
  end;
end;

function TfmMain.AsdUavTypeToText(const UavType: TwclDriAsdUavType): string;
begin
  case UavType of
    utNone:
      Result := 'None';
    utAeroplane:
      Result := 'Aeroplane';
    utCopter:
      Result := 'Copter';
    utGyroplane:
      Result := 'Gyroplane';
    utHybridLift:
      Result := 'Hybrid';
    utOrnithopter:
      Result := 'Ornithopter';
    utGlider:
      Result := 'Glider';
    utKite:
      Result := 'Kite';
    utFreeBalloon:
      Result := 'Free balloon';
    utCaptiveBalloon:
      Result := 'Captive balloon';
    utAirship:
      Result := 'Airship';
    utFreeFallParachute:
      Result := 'Free fall parachute';
    utRocket:
      Result := 'Rocket';
    utTetheredPoweredAircraft:
      Result := 'Tethered powered aircraft';
    utGroundObstacle:
      Result := 'Ground obstacle';
    else
      Result := 'Raw value: 0x' + IntToHex(Byte(UavType), 2);
  end;
end;

procedure TfmMain.ShowAsdLocationMessage(
  const Message: TwclDriAsdLocationMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'Baro Altitude';
  Item.SubItems.Add(AsdAltitudeToText(Message.BaroAltitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Baro Accuracy';
  Item.SubItems.Add(AsdVerticalAccuracyToText(Message.BaroAccuracy));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Direction';
  Item.SubItems.Add(AsdDirectionToText(Message.Direction));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Geo Altitude';
  Item.SubItems.Add(AsdAltitudeToText(Message.GeoAltitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Height';
  Item.SubItems.Add(AsdAltitudeToText(Message.Height));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Height Reference';
  Item.SubItems.Add(AsdHeightReferenceToText(Message.HeightReference));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Horizontal Accuracy';
  Item.SubItems.Add(AsdHorizontalAccuracyToText(Message.HorizontalAccuracy));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Horizontal Speed';
  Item.SubItems.Add(AsdHorizontalSpeedToText(Message.HorizontalSpeed));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Latitude';
  Item.SubItems.Add(AsdLatLonToText(Message.Latitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Longitude';
  Item.SubItems.Add(AsdLatLonToText(Message.Longitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Speed Accuracy';
  Item.SubItems.Add(AsdSpeedAccuracyToText(Message.SpeedAccuracy));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Status';
  Item.SubItems.Add(AsdStatusToText(Message.Status));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Timestamp';
  Item.SubItems.Add(FloatToStr(Message.Timestamp));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Timestamp Accuracy';
  Item.SubItems.Add(AsdTimestampAccuracyToText(Message.TimestampAccuracy));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Vertical Accuracy';
  Item.SubItems.Add(AsdVerticalAccuracyToText(Message.VerticalAccuracy));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Vertical Speed';
  Item.SubItems.Add(FloatToStr(Message.VerticalSpeed));
end;

procedure TfmMain.ShowAsdSelfIdMessage(
  const Message: TwclDriAsdSelfIdMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'Description';
  Item.SubItems.Add(String(Message.Description));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Description Type';
  Item.SubItems.Add(AsdDescriptionTypeToText(Message.DescriptionType));
end;

procedure TfmMain.ShowAsdOperatorIdMessage(
  const Message: TwclDriAsdOperatorIdMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'ID';
  Item.SubItems.Add(String(AnsiString(PAnsiChar(Message.Id))));

  Item := lvDetails.Items.Add;
  Item.Caption := 'ID Type';
  Item.SubItems.Add('0x' + IntToHex(Message.IdType, 2));
end;

procedure TfmMain.ShowAsdSystemMessage(
  const Message: TwclDriAsdSystemMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'Area ceiling';
  Item.SubItems.Add(AsdAltitudeToText(Message.AreaCeiling));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Area count';
  Item.SubItems.Add(IntToStr(Message.AreaCount));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Area floor';
  Item.SubItems.Add(AsdAltitudeToText(Message.AreaFloor));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Area radius';
  Item.SubItems.Add(IntToStr(Message.AreaRadius));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Operator altitude';
  Item.SubItems.Add(FloatToStr(Message.OperatorAltitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Operator classification';
  Item.SubItems.Add(AsdOperatorClassificationToText(
    Message.OperatorClassification));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Operator latitude';
  Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Operator latitude';
  Item.SubItems.Add(AsdLatLonToText(Message.OperatorLatitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Operator longitude';
  Item.SubItems.Add(AsdLatLonToText(Message.OperatorLongitude));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Location type';
  Item.SubItems.Add(AsdLocationTypeToText(Message.OperatorLocation));

  Item := lvDetails.Items.Add;
  Item.Caption := 'Timestamp';
  Item.SubItems.Add(DateTimeToStr(Message.Timestamp));

  Item := lvDetails.Items.Add;
  Item.Caption := 'UAV EU category';
  Item.SubItems.Add(AsdEuUavCategoryToText(Message.UavEuCategory));

  Item := lvDetails.Items.Add;
  Item.Caption := 'UAV EU class';
  Item.SubItems.Add(AsdEuUavClassToText(Message.UavEuClass));
end;

procedure TfmMain.ShowAsdBassicIdMessage(
  const Message: TwclDriAsdBasicIdMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'ID';
  Item.SubItems.Add(String(AnsiString(PAnsiChar(Message.Id))));

  Item := lvDetails.Items.Add;
  Item.Caption := 'ID type';
  Item.SubItems.Add(AsdIdTypeToText(Message.IdType));

  Item := lvDetails.Items.Add;
  Item.Caption := 'ID type';
  Item.SubItems.Add(AsdUavTypeToText(Message.UavType));
end;

procedure TfmMain.ShowUnknownAsdMessage(const Message: TwclDriAsdMessage);
var
  Item: TListItem;
  Str: string;
  i: Integer;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'Message type';
  Item.SubItems.Add(IntToHex(Byte(Message.MessageType), 2));

  Str := '';
  if Length(Message.Data) > 0 then begin
    for i := 0 to Length(Message.Data) - 1 do
      Str := Str + IntToHex(Message.Data[i], 2);
  end;
  Item := lvDetails.Items.Add;
  Item.Caption := 'Raw date';
  Item.SubItems.Add(Str);
end;

procedure TfmMain.UpdateAsdMessageDetails(const Ssid: string;
  const Message: TwclDriAsdMessage);
var
  Item: TListItem;
begin
  Item := lvDetails.Items.Add;
  Item.Caption := 'SSID';
  Item.SubItems.Add(Ssid);

  Item := lvDetails.Items.Add;
  Item.Caption := 'Vendor';
  Item.SubItems.Add(VendorToText(Message));

  Item := lvDetails.Items.Add;
  Item.Caption := '';
  Item.SubItems.Add('');

  case Message.MessageType of
    mtBasicId:
      ShowAsdBassicIdMessage(TwclDriAsdBasicIdMessage(Message));
    mtLocation:
      ShowAsdLocationMessage(TwclDriAsdLocationMessage(Message));
    mtAuth:
      ShowUnknownAsdMessage(Message);
    mtSelfId:
      ShowAsdSelfIdMessage(TwclDriAsdSelfIdMessage(Message));
    mtSystem:
      ShowAsdSystemMessage(TwclDriAsdSystemMessage(Message));
    mtOperatorId:
      ShowAsdOperatorIdMessage(TwclDriAsdOperatorIdMessage(Message));
    else
      ShowUnknownAsdMessage(Message);
  end;
end;

procedure TfmMain.UpdateDroneMessages(const Node: TTreeNode;
  const Messages: TList);
var
  i: Integer;
  Message: TwclDriMessage;
  AsdMessage: TwclDriAsdMessage;
  MessageType: string;
  MessageNode: TTreeNode;
begin
  for i := 0 to Messages.Count - 1 do begin
    Message := TwclDriMessage(Messages[i]);
    if Message.Vendor <> driAsd then
      Message.Free

    else begin
      AsdMessage := TwclDriAsdMessage(Message);
      MessageType := MessageTypeToText(AsdMessage);

      MessageNode := Node.getFirstChild;
      while MessageNode <> nil do begin
        if MessageNode.Text = MessageType then begin
          TwclDriMessage(MessageNode.Data).Free;
          MessageNode.Data := nil;
          Break;
        end;

        MessageNode := Node.GetNextChild(MessageNode);
      end;

      if MessageNode = nil then
        MessageNode := tvDrones.Items.AddChild(Node, MessageType);
      MessageNode.Data := AsdMessage;
      if MessageNode.Selected then
        UpdateMessageDetails(MessageNode.Parent.Text, AsdMessage);
    end;
  end;
end;

procedure TfmMain.UpdateMessageDetails(const Ssid: string;
  const Message: TwclDriMessage);
begin
  ClearMessageDetails;

  if Message.Vendor = driAsd then
    UpdateAsdMessageDetails(Ssid, TwclDriAsdMessage(Message));
end;

procedure TfmMain.UpdateMessages(const Ssid: string; const Messages: TList);
var
  DroneNode: TTreeNode;
begin
  DroneNode := FindDrone(Ssid);
  if DroneNode <> nil then begin
    UpdateDroneMessages(DroneNode, Messages);
    DroneNode.Expand(True);
  end;
end;

function TfmMain.VendorToText(const Message: TwclDriMessage): string;
begin
  case Message.Vendor of
    driAsd:
      Result := 'ASD';
    else
      Result := 'UKNOWN';
  end;
end;

procedure TfmMain.GetDriInfo;
var
  Res: Integer;
  BssList: TwclWiFiBssArray;
  i: Integer;
  Messages: TList;
begin
  Res := WiFiClient.EnumBss(FId, '', bssAny, True, BssList);
  if Res <> WCL_E_SUCCESS then
    Trace('Enum BSS failed', Res)

  else begin
    if Length(BssList) > 0 then begin
      Messages := TList.Create;
      for i := 0 to Length(BssList) - 1 do begin
        if Length(BssList[i].IeRaw) > 0 then begin
          FParser.ParseDriMessages(BssList[i], Messages);
          if Messages.Count > 0 then
            UpdateMessages(BssList[i].Ssid, Messages);
        end;
      end;
      Messages.Free;
    end;
  end;
end;

procedure TfmMain.RestartScan;
var
  Res: Integer;
begin
  if FScanActive then begin
    Res := WiFiClient.Scan(FId);
    if Res <> WCL_E_SUCCESS then begin
      Trace('Restart scan failed', Res);

      StopScan;
    end;
  end;
end;

procedure TfmMain.StartScan;
var
  Res: Integer;
  Radio: TwclBluetoothRadio;
begin
  if not FScanActive then begin
    FId := GUID_NULL;

    Res := WiFiClient.Open;
    if Res <> WCL_E_SUCCESS then
      Trace('WiFiClient open failed', Res)

    else begin
      Res := WiFiEvents.Open;
      if Res <> WCL_E_SUCCESS then
        Trace('WiFiEvents open failed', Res)
      else
        EnumInterfaces;

      if Res <> WCL_E_SUCCESS then
        WiFiClient.Close;
    end;

    if not CompareMem(@FId, @GUID_NULL, SizeOf(TGUID)) then begin
      Res := WiFiClient.Scan(FId);
      if Res <> WCL_E_SUCCESS then
        Trace('Start WiFi scan failed', Res)
      else
        Trace('WiFi scan started');
    end;

    Res := BluetoothManager.Open;
    if Res <> WCL_E_SUCCESS then
      Trace('Bluetooth manager open failed', Res)

    else begin
      Res := BluetoothManager.GetLeRadio(Radio);
      if Res <> WCL_E_SUCCESS then
        Trace('Get LE radio failed', Res)

      else begin
        BeaconWatcher.AllowExtendedAdvertisements := True;
        Res := BeaconWatcher.Start(Radio);
        if Res <> WCL_E_SUCCESS then begin
          BeaconWatcher.AllowExtendedAdvertisements := False;
          Res := BeaconWatcher.Start(Radio);
        end;

        if Res <> WCL_E_SUCCESS then
          Trace('Start Bluetooth scan failed', Res);
      end;

      if Res <> WCL_E_SUCCESS then
        BluetoothManager.Close;
    end;

    FScanActive := BeaconWatcher.Monitoring or WiFiClient.Active;
    if FScanActive then begin
      FRootNode := tvDrones.Items.Add(nil, 'Drones');

      btStart.Enabled := False;
      btStop.Enabled := True;
    end;
  end;
end;

procedure TfmMain.StopScan;
var
  DroneNode: TTreeNode;
  MessageNode: TTreeNode;
begin
  if FScanActive then begin
    WiFiEvents.Close;
    WiFiClient.Close;

    BeaconWatcher.Stop;
    BluetoothManager.Close;

    btStart.Enabled := True;
    btStop.Enabled := False;

    FScanActive := False;

    DroneNode := FRootNode.getFirstChild;
    while DroneNode <> nil do begin
      MessageNode := DroneNode.getFirstChild;
      while MessageNode <> nil do begin
        TwclDriMessage(MessageNode.Data).Free;
        MessageNode := DroneNode.GetNextChild(MessageNode);
      end;
      DroneNode := FRootNode.GetNextChild(DroneNode);
    end;

    tvDrones.Items.Clear;
    FRootNode := nil;

    ClearMessageDetails;

    Trace('Scan sopped');
  end;
end;

end.
