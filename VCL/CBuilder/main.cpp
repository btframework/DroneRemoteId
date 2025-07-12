//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "wclWiFi"
#pragma link "wclBluetooth"
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::Trace(const String Msg)
{
	lbLog->Items->Add(Msg);
	lbLog->TopIndex = lbLog->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::Trace(const String Msg, const int Res)
{
	Trace(Msg + ": 0x" + IntToHex(Res, 8));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::tvDronesClick(TObject *Sender)
{
	ClearMessageDetails();

	if (tvDrones->Selected != NULL)
	{
		if (tvDrones->Selected->Data != NULL)
		{
			UpdateMessageDetails(tvDrones->Selected->Parent->Text,
				(TwclDriMessage*)tvDrones->Selected->Data);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiClientAfterOpen(TObject *Sender)
{
	Trace("WiFi Client opened");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiClientBeforeClose(TObject *Sender)
{
	Trace("WiFi Client closed");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsAcmInterfaceArrival(TObject *Sender,
	const TGUID &IfaceId)
{
	if (CompareMem((void*)&FId, (void*)&GUID_NULL, sizeof(TGUID)))
		EnumInterfaces();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsAcmInterfaceRemoval(TObject *Sender,
	const TGUID &IfaceId)
{
	if (CompareMem((void*)&FId, (void*)&IfaceId, sizeof(TGUID)))
	{
		Trace("Adapter removed");

		AdapterDisabled();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsAcmScanComplete(TObject *Sender,
	const TGUID &IfaceId)
{
	if (FScanActive && CompareMem((void*)&FId, (void*)&IfaceId, sizeof(TGUID)))
	{
		GetDriInfo();

		RestartScan();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsAcmScanFail(TObject *Sender,
	const TGUID &IfaceId, const int Reason)
{
	if (FScanActive && CompareMem((void*)&FId, (void*)&IfaceId, sizeof(TGUID)))
	{
		Trace("Scan failed", Reason);

		RestartScan();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsAfterOpen(TObject *Sender)
{
	Trace("WiFi Events opened");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsBeforeClose(TObject *Sender)
{
	Trace("WiFi Events closed");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::WiFiEventsMsmRadioStateChange(TObject *Sender,
	const TGUID &IfaceId, const TwclWiFiPhyRadioState &State)
{
	if (CompareMem((void*)&FId, (void*)&GUID_NULL, sizeof(TGUID)))
		EnumInterfaces();
	else
	{
		if (CompareMem((void*)&FId, (void*)&IfaceId, sizeof(TGUID)))
		{
			if (State.SoftwareState == rsOff || State.HardwareState == rsOff)
			{
				Trace("Adapter disabled");

				AdapterDisabled();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::AdapterDisabled()
{
	StopScan();
	FId = GUID_NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btClearClick(TObject *Sender)
{
	lbLog->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btStartClick(TObject *Sender)
{
	StartScan();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btStopClick(TObject *Sender)
{
	StopScan();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ClearMessageDetails()
{
	lvDetails->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::EnumInterfaces()
{
	TwclWiFiInterfaces Ifaces;
	int Res = WiFiClient->EnumInterfaces(Ifaces);
	if (Res != WCL_E_SUCCESS)
		Trace("Enum interfaces failed", Res);
	else
	{
		if (Ifaces.Length == 0)
			Trace("No one WiFi interface found");
		else
		{
			bool Found = false;
			for (int i = 0; i < Ifaces.Length; i++)
			{
				TwclWiFiInterface* Iface = new TwclWiFiInterface(Ifaces[i].Id);
				if (Iface->Open() == WCL_E_SUCCESS)
				{
					TwclWiFiPhyRadioStates States;
					Res = Iface->GetRadioState(States);
					if (Res == WCL_E_SUCCESS)
					{
						if (States.Length > 0)
						{
							bool Enabled = false;
							for (int j = 0; j < States.Length; j++)
							{
								Enabled = (States[i].SoftwareState == rsOn &&
									States[i].HardwareState == rsOn);
								if (!Enabled)
									break;
							}

							Found = Enabled;
						}
					}

					if (Found)
						FId = Iface->Id;
					Iface->Close();
				}
				Iface->Free();

				if (Found)
					break;
			}

			if (Found)
				Trace("Use WiFi interface " + GUIDToString(FId));
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormCreate(TObject *Sender)
{
	FBtParser = new TwclDriAsdParser();
	FParser = new TwclWiFiDriParser();
	FScanActive = false;
	FRootNode = NULL;

	btStart->Enabled = true;
	btStop->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormDestroy(TObject *Sender)
{
	StopScan();

	FBtParser->Free();
	FParser->Free();
}
//---------------------------------------------------------------------------
TTreeNode* __fastcall TfmMain::FindDrone(const String Ssid)
{
	TTreeNode* Result = NULL;

	TTreeNode* DroneNode = FRootNode->getFirstChild();
	while (DroneNode != NULL)
	{
		if (DroneNode->Text == Ssid)
		{
			Result = DroneNode;
			break;
		}

		DroneNode = FRootNode->GetNextChild(DroneNode);
	}

	if (Result == NULL)
	{
		Result = tvDrones->Items->AddChild(FRootNode, Ssid);
		FRootNode->Expand(true);
	}

	return Result;
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::MessageTypeToText(TwclDriAsdMessage* Message)
{
	switch (Message->MessageType)
	{
		case mtBasicId:
			return "BASIC ID";
		case mtLocation:
			return "LOCATION";
		case mtAuth:
			return "AUTH";
		case mtSelfId:
			return "SELF ID";
		case mtSystem:
			return "SYSTEM";
		case mtOperatorId:
			return "OPERATOR ID";
		default:
			return "UNKNOWN";
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdVerticalAccuracyToText(
	TwclDriAsdUavVerticalAccuracy Accuracy)
{
	switch (Accuracy)
	{
		case vaUnknown:
			return "Unknow";
		case va150M:
			return "150 m";
		case va45M:
			return "45 m";
		case va25M:
			return "25 m";
		case va10M:
			return "10 m";
		case va3M:
			return "3 m";
		case va1M:
			return "1 m";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Accuracy), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdHeightReferenceToText(
	TwclDriAsdUavHeightReference Reference)
{
	switch (Reference)
	{
		case hrTakeOff:
			return "Take off";
		case hrGround:
			return "Ground";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Reference), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdHorizontalAccuracyToText(
	TwclDriAsdUavHorizontalAccuracy Accuracy)
{
	switch (Accuracy)
	{
		case haUnknown:
			return "Unknown";
		case ha10Nm:
			return "10 miles";
		case ha4Nm:
			return "4 miles";
		case ha2Nm:
			return "2 miles";
		case ha1Nm:
			return "1 mile";
		case ha05Nm:
			return "0.5 mile";
		case ha03Nm:
			return "0.3 mile";
		case ha01Nm:
			return "0.1 mile";
		case ha005Nm:
			return "0.05 mile";
		case ha30M:
			return "30 meters";
		case ha10M:
			return "10 meters";
		case ha3M:
			return "3 meters";
		case ha1M:
			return "1 meter";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Accuracy), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdSpeedAccuracyToText(
	TwclDriAsdUavSpeedAccuracy Accuracy)
{
	switch (Accuracy)
	{
		case saUnknown:
			return "Unknown";
		case sa10MS:
			return "10 m/s";
		case sa3MS:
			return "3 m/s";
		case sa1Ms:
			return "1 m/s";
		case sa03Ms:
			return "0.3 m/s";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Accuracy), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdStatusToText(TwclDriAsdUavStatus Status)
{
	switch (Status)
	{
		case usUndeclared:
			return "Undeclared";
		case usGround:
			return "Ground";
		case usAirborne:
			return "Airborne";
		case usEmergency:
			return "Emergency";
		case usFailure:
			return "Failure";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Status), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdTimestampAccuracyToText(
	TwclDriAsdUavTimestampAccuracy Accuracy)
{
	switch (Accuracy)
	{
		case taUnknown:
			return "Unknown";
		case ta01s:
			return "0.1 second";
		case ta02s:
			return "0.2 second";
		case ta03s:
			return "0.3 second";
		case ta04s:
			return "0.4 second";
		case ta05s:
			return "0.5 second";
		case ta06s:
			return "0.6 second";
		case ta07s:
			return "0.7 second";
		case ta08s:
			return "0.8 second";
		case ta09s:
			return "0.9 second";
		case ta1s:
			return "1 second";
		case ta11s:
			return "1.1 second";
		case ta12s:
			return "1.2 second";
		case ta13s:
			return "1.3 second";
		case ta14s:
			return "1.4 second";
		case ta15s:
			return "1.5 second";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Accuracy), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdAltitudeToText(float Altitude)
{
	if (Altitude == -1000)
		return "Invalid";
	return FloatToStr(Altitude);
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdDescriptionTypeToText(
	TwclDriAsdDescriptionType DescriptionType)
{
	switch (DescriptionType)
	{
		case dtText:
			return "Text";
		case dtEmergency:
			return "Emergency";
		case dtExtended:
			return "Extended";
		default:
			return "Raw value: 0x" + IntToHex(Byte(DescriptionType), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdDirectionToText(unsigned short Direction)
{
	if (Direction > 360)
		return "Invalid";
	return IntToStr(Direction);
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdHorizontalSpeedToText(float Speed)
{
	if (Speed == 255)
		return "Invalid";
	return FloatToStr(Speed);
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdLatLonToText(double LatLon)
{
	if (LatLon == 0)
		return "Invalid";
	return FloatToStr(LatLon);
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdOperatorClassificationToText(
	TwclDriAsdOperatorClassification Classification)
{
	switch (Classification)
	{
		case ocUndeclared:
			return "Undeclared";
		case ocEu:
			return "EU";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Classification), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdLocationTypeToText(
	TwclDriAsdOperatorLocationType Location)
{
	switch (Location)
	{
		case ltTakeOff:
			return "Take off";
		case ltLiveGnss:
			return "Live GNSS";
		case ltFixed:
			return "Fixed";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Location), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdEuUavCategoryToText(
	TwclDriAsdUavEuCategory Category)
{
	switch (Category)
	{
		case ucUndeclared:
			return "Undeclared";
		case ucOpen:
			return "Open";
		case ucSpecific:
			return "Specific";
		case ucCertified:
			return "Certified";
		default:
			return "Raw value: 0x" + IntToHex(Byte(Category), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdEuUavClassToText(
	TwclDriAsdUavEuClass UavClass)
{
	switch (UavClass)
	{
		case ucUnspecified:
			return "Unspecified";
		case ucClass0:
			return "Class 0";
		case ucClass1:
			return "Class 1";
		case ucClass2:
			return "Class 2";
		case ucClass3:
			return "Class 3";
		case ucClass4:
			return "Class 4";
		case ucClass5:
			return "Class 5";
		case ucClass6:
			return "Class 6";
		default:
			return "Raw value: 0x" + IntToHex(Byte(UavClass), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdIdTypeToText(TwclDriAsdIdType IdType)
{
	switch (IdType)
	{
		case itNone:
			return "None";
		case itSerialNumber:
			return "Serial number";
		case itCaaRegistrationId:
			return "CAA registration ID";
		case itUtmAssignedUuid:
			return "UTM assigned UUID";
		case itSpecificSessionId:
			return "Specific session ID";
		default:
			return "Raw value: 0x" + IntToHex(Byte(IdType), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::AsdUavTypeToText(TwclDriAsdUavType UavType)
{
	switch (UavType)
	{
		case utNone:
			return "None";
		case utAeroplane:
			return "Aeroplane";
		case utCopter:
			return "Copter";
		case utGyroplane:
			return "Gyroplane";
		case utHybridLift:
			return "Hybrid";
		case utOrnithopter:
			return "Ornithopter";
		case utGlider:
			return "Glider";
		case utKite:
			return "Kite";
		case utFreeBalloon:
			return "Free balloon";
		case utCaptiveBalloon:
			return "Captive balloon";
		case utAirship:
			return "Airship";
		case utFreeFallParachute:
			return "Free fall parachute";
		case utRocket:
			return "Rocket";
		case utTetheredPoweredAircraft:
			return "Tethered powered aircraft";
		case utGroundObstacle:
			return "Ground obstacle";
		default:
			return "Raw value: 0x" + IntToHex(Byte(UavType), 2);
	}
}
//---------------------------------------------------------------------------
String __fastcall TfmMain::VendorToText(TwclDriMessage* Message)
{
	switch (Message->Vendor)
	{
		case driAsd:
			return "ASD";
		default:
			return "UKNOWN";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowAsdLocationMessage(
	TwclDriAsdLocationMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "Baro Altitude";
	Item->SubItems->Add(AsdAltitudeToText(Message->BaroAltitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Baro Accuracy";
	Item->SubItems->Add(AsdVerticalAccuracyToText(Message->BaroAccuracy));

	Item = lvDetails->Items->Add();
	Item->Caption = "Direction";
	Item->SubItems->Add(AsdDirectionToText(Message->Direction));

	Item = lvDetails->Items->Add();
	Item->Caption = "Geo Altitude";
	Item->SubItems->Add(AsdAltitudeToText(Message->GeoAltitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Height";
	Item->SubItems->Add(AsdAltitudeToText(Message->Height));

	Item = lvDetails->Items->Add();
	Item->Caption = "Height Reference";
	Item->SubItems->Add(AsdHeightReferenceToText(Message->HeightReference));

	Item = lvDetails->Items->Add();
	Item->Caption = "Horizontal Accuracy";
	Item->SubItems->Add(AsdHorizontalAccuracyToText(
		Message->HorizontalAccuracy));

	Item = lvDetails->Items->Add();
	Item->Caption = "Horizontal Speed";
	Item->SubItems->Add(AsdHorizontalSpeedToText(Message->HorizontalSpeed));

	Item = lvDetails->Items->Add();
	Item->Caption = "Latitude";
	Item->SubItems->Add(AsdLatLonToText(Message->Latitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Longitude";
	Item->SubItems->Add(AsdLatLonToText(Message->Longitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Speed Accuracy";
	Item->SubItems->Add(AsdSpeedAccuracyToText(Message->SpeedAccuracy));

	Item = lvDetails->Items->Add();
	Item->Caption = "Status";
	Item->SubItems->Add(AsdStatusToText(Message->Status));

	Item = lvDetails->Items->Add();
	Item->Caption = "Timestamp";
	Item->SubItems->Add(FloatToStr(Message->Timestamp));

	Item = lvDetails->Items->Add();
	Item->Caption = "Timestamp Accuracy";
	Item->SubItems->Add(AsdTimestampAccuracyToText(Message->TimestampAccuracy));

	Item = lvDetails->Items->Add();
	Item->Caption = "Vertical Accuracy";
	Item->SubItems->Add(AsdVerticalAccuracyToText(Message->VerticalAccuracy));

	Item = lvDetails->Items->Add();
	Item->Caption = "Vertical Speed";
	Item->SubItems->Add(FloatToStr(Message->VerticalSpeed));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowAsdSelfIdMessage(
	TwclDriAsdSelfIdMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "Description";
	Item->SubItems->Add(String(Message->Description));

	Item = lvDetails->Items->Add();
	Item->Caption = "Description Type";
	Item->SubItems->Add(AsdDescriptionTypeToText(Message->DescriptionType));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowAsdOperatorIdMessage(
	TwclDriAsdOperatorIdMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "ID";
	Item->SubItems->Add(String(AnsiString(PAnsiChar(&Message->Id[0]))));

	Item = lvDetails->Items->Add();
	Item->Caption = "ID Type";
	Item->SubItems->Add("0x" + IntToHex(Message->IdType, 2));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowAsdSystemMessage(
	TwclDriAsdSystemMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "Area ceiling";
	Item->SubItems->Add(AsdAltitudeToText(Message->AreaCeiling));

	Item = lvDetails->Items->Add();
	Item->Caption = "Area count";
	Item->SubItems->Add(IntToStr(Message->AreaCount));

	Item = lvDetails->Items->Add();
	Item->Caption = "Area floor";
	Item->SubItems->Add(AsdAltitudeToText(Message->AreaFloor));

	Item = lvDetails->Items->Add();
	Item->Caption = "Area radius";
	Item->SubItems->Add(IntToStr(Message->AreaRadius));

	Item = lvDetails->Items->Add();
	Item->Caption = "Operator altitude";
	Item->SubItems->Add(FloatToStr(Message->OperatorAltitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Operator classification";
	Item->SubItems->Add(AsdOperatorClassificationToText(
		Message->OperatorClassification));

	Item = lvDetails->Items->Add();
	Item->Caption = "Operator latitude";
	Item->SubItems->Add(AsdLatLonToText(Message->OperatorLatitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Operator longitude";
	Item->SubItems->Add(AsdLatLonToText(Message->OperatorLongitude));

	Item = lvDetails->Items->Add();
	Item->Caption = "Location type";
	Item->SubItems->Add(AsdLocationTypeToText(Message->OperatorLocation));

	Item = lvDetails->Items->Add();
	Item->Caption = "Timestamp";
	Item->SubItems->Add(DateTimeToStr(Message->Timestamp));

	Item = lvDetails->Items->Add();
	Item->Caption = "UAV EU category";
	Item->SubItems->Add(AsdEuUavCategoryToText(Message->UavEuCategory));

	Item = lvDetails->Items->Add();
	Item->Caption = "UAV EU class";
	Item->SubItems->Add(AsdEuUavClassToText(Message->UavEuClass));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowAsdBassicIdMessage(
	TwclDriAsdBasicIdMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "ID";
	Item->SubItems->Add(String(AnsiString(PAnsiChar(&Message->Id[0]))));

	Item = lvDetails->Items->Add();
	Item->Caption = "ID type";
	Item->SubItems->Add(AsdIdTypeToText(Message->IdType));

	Item = lvDetails->Items->Add();
	Item->Caption = "ID type";
	Item->SubItems->Add(AsdUavTypeToText(Message->UavType));
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::ShowUnknownAsdMessage(TwclDriAsdMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "Message type";
	Item->SubItems->Add(IntToHex(Byte(Message->MessageType), 2));

	String Str = "";
	if (Message->Data.Length > 0)
	{
		for (int i = 0; i < Message->Data.Length; i++)
			Str += IntToHex(Message->Data[i], 2);
	}
	Item = lvDetails->Items->Add();
	Item->Caption = "Raw date";
	Item->SubItems->Add(Str);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::UpdateAsdMessageDetails(String Ssid,
	TwclDriAsdMessage* Message)
{
	TListItem* Item = lvDetails->Items->Add();
	Item->Caption = "SSID";
	Item->SubItems->Add(Ssid);

	Item = lvDetails->Items->Add();
	Item->Caption = "Vendor";
	Item->SubItems->Add(VendorToText(Message));

	Item = lvDetails->Items->Add();
	Item->Caption = "";
	Item->SubItems->Add("");

	switch (Message->MessageType)
	{
		case mtBasicId:
			ShowAsdBassicIdMessage((TwclDriAsdBasicIdMessage*)Message);
			break;
		case mtLocation:
			ShowAsdLocationMessage((TwclDriAsdLocationMessage*)Message);
			break;
		case mtAuth:
			ShowUnknownAsdMessage(Message);
			break;
		case mtSelfId:
			ShowAsdSelfIdMessage((TwclDriAsdSelfIdMessage*)Message);
			break;
		case mtSystem:
			ShowAsdSystemMessage((TwclDriAsdSystemMessage*)Message);
			break;
		case mtOperatorId:
			ShowAsdOperatorIdMessage((TwclDriAsdOperatorIdMessage*)Message);
			break;
		default:
			ShowUnknownAsdMessage(Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::UpdateDroneMessages(TTreeNode* Node, TList* Messages)
{
	for (int i = 0; i < Messages->Count; i++)
	{
		TwclDriMessage* Message = (TwclDriMessage*)(Messages->Items[i]);
		if (Message->Vendor != driAsd)
			Message->Free();
		else
		{
			TwclDriAsdMessage* AsdMessage = (TwclDriAsdMessage*)Message;
			String MessageType = MessageTypeToText(AsdMessage);

			TTreeNode* MessageNode = Node->getFirstChild();
			while (MessageNode != NULL)
			{
				if (MessageNode->Text == MessageType)
				{
					((TwclDriMessage*)MessageNode->Data)->Free();
					MessageNode->Data = NULL;
					break;
				}

				MessageNode = Node->GetNextChild(MessageNode);
			}

			if (MessageNode == NULL)
				MessageNode = tvDrones->Items->AddChild(Node, MessageType);
			MessageNode->Data = AsdMessage;
			if (MessageNode->Selected)
				UpdateMessageDetails(MessageNode->Parent->Text, AsdMessage);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::UpdateMessageDetails(String Ssid,
	TwclDriMessage* Message)
{
	ClearMessageDetails();

	if (Message->Vendor == driAsd)
		UpdateAsdMessageDetails(Ssid, (TwclDriAsdMessage*)Message);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::UpdateMessages(String Ssid, TList* Messages)
{
	TTreeNode* DroneNode = FindDrone(Ssid);
	if (DroneNode != NULL)
	{
		UpdateDroneMessages(DroneNode, Messages);
		DroneNode->Expand(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::GetDriInfo()
{
	TwclWiFiBssArray BssList;
	int Res = WiFiClient->EnumBss(FId, "", bssAny, True, BssList);
	if (Res != WCL_E_SUCCESS)
		Trace("Enum BSS failed", Res);
	else
	{
		if (BssList.Length > 0)
		{
			TList* Messages = new TList();
			for (int i = 0; i < BssList.Length; i++)
			{
				if (BssList[i].IeRaw.Length > 0)
				{
					FParser->ParseDriMessages(BssList[i], Messages);
					if (Messages->Count > 0)
						UpdateMessages(BssList[i].Ssid, Messages);
				}
			}
			Messages->Free();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::RestartScan()
{
	if (FScanActive)
	{
		int Res = WiFiClient->Scan(FId);
		if (Res != WCL_E_SUCCESS)
		{
			Trace("Restart scan failed", Res);

			StopScan();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::StartScan()
{
	if (!FScanActive)
	{
		FId = GUID_NULL;

		int Res = WiFiClient->Open();
		if (Res != WCL_E_SUCCESS)
			Trace("WiFiClient open failed", Res);
		else
		{
			Res = WiFiEvents->Open();
			if (Res != WCL_E_SUCCESS)
				Trace("WiFiEvents open failed", Res);
			else
				EnumInterfaces();

			if (Res != WCL_E_SUCCESS)
				WiFiClient->Close();
		}

		if (!CompareMem((void*)&FId, (void*)&GUID_NULL, sizeof(TGUID)))
		{
			int Res = WiFiClient->Scan(FId);
			if (Res != WCL_E_SUCCESS)
				Trace("Start WiFi scan failed", Res);
			else
				Trace("WiFi Scan started");
		}

		Res = BluetoothManager->Open();
		if (Res != WCL_E_SUCCESS)
			Trace("Bluetooth manager open failed", Res);
		else
		{
			TwclBluetoothRadio* Radio;
			Res = BluetoothManager->GetLeRadio(Radio);
			if (Res != WCL_E_SUCCESS)
				Trace("Get LE radio failed", Res);
			else
			{
				BeaconWatcher->AllowExtendedAdvertisements = true;
				Res = BeaconWatcher->Start(Radio);
				if (Res != WCL_E_SUCCESS)
				{
					BeaconWatcher->AllowExtendedAdvertisements = false;
					Res = BeaconWatcher->Start(Radio);
				}

				if (Res != WCL_E_SUCCESS)
					Trace("Start Bluetooth scan failed", Res);
			}

			if (Res != WCL_E_SUCCESS)
				BluetoothManager->Close();
		}

		FScanActive = (BeaconWatcher->Monitoring || WiFiClient->Active);
		if (FScanActive)
		{
			FRootNode = tvDrones->Items->Add(NULL, "Drones");

			btStart->Enabled = false;
			btStop->Enabled = true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::StopScan()
{
	if (FScanActive)
	{
		WiFiEvents->Close();
		WiFiClient->Close();

		BeaconWatcher->Stop();
		BluetoothManager->Close();

		btStart->Enabled = true;
		btStop->Enabled = false;

		FScanActive = false;

		TTreeNode* DroneNode = FRootNode->getFirstChild();
		while (DroneNode != NULL)
		{
			TTreeNode* MessageNode = DroneNode->getFirstChild();
			while (MessageNode != NULL)
			{
				((TwclDriMessage*)MessageNode->Data)->Free();
				MessageNode = DroneNode->GetNextChild(MessageNode);
			}
			DroneNode = FRootNode->GetNextChild(DroneNode);
		}

		tvDrones->Items->Clear();
		FRootNode = NULL;

		ClearMessageDetails();

		Trace("Scan sopped");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BeaconWatcherDriAsdMessage(TObject *Sender,
	const __int64 Address, const __int64 Timestamp, const SByte Rssi,
	const TwclDriRawData Raw)

{
	TList* Messages = new TList();
	if (FBtParser->Parse(Raw, Messages) == WCL_E_SUCCESS)
	{
		if (Messages->Count > 0)
			UpdateMessages(IntToHex(Address, 12), Messages);
	}
	Messages->Free();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BluetoothManagerAfterOpen(TObject *Sender)
{
	Trace("Bluetooth manager opened");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BluetoothManagerClosed(TObject *Sender)
{
	Trace("Bluetooth manager closed");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BeaconWatcherStarted(TObject *Sender)
{
	Trace("Bluetooth scan started");
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::BeaconWatcherStopped(TObject *Sender)
{
	Trace("Bluetooth scan stopped");
}
//---------------------------------------------------------------------------

