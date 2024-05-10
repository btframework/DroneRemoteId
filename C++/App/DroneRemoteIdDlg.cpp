
// DroneRemoteIdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DroneRemoteId.h"
#include "DroneRemoteIdDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDroneRemoteIdDlg dialog



CDroneRemoteIdDlg::CDroneRemoteIdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRONEREMOTEID_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDroneRemoteIdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DRONES, tvDrones);
	DDX_Control(pDX, IDC_LIST_DETAILS, lvDetails);
	DDX_Control(pDX, IDC_BUTTON_START, btStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, btStop);
	DDX_Control(pDX, IDC_LIST_LOG, lbLog);
}

BEGIN_MESSAGE_MAP(CDroneRemoteIdDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DRONES, &CDroneRemoteIdDlg::OnTvnSelchangedTreeDrones)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDroneRemoteIdDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDroneRemoteIdDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDroneRemoteIdDlg::OnBnClickedButtonStop)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDroneRemoteIdDlg message handlers

BOOL CDroneRemoteIdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	lvDetails.InsertColumn(0, _T("Parameters"), 0, 100);
	lvDetails.InsertColumn(1, _T("Value"), 0, 540);

	__hook(&CwclWiFiClient::AfterOpen, &WiFiClient, &CDroneRemoteIdDlg::WiFiClientAfterOpen);
	__hook(&CwclWiFiClient::BeforeClose, &WiFiClient, &CDroneRemoteIdDlg::WiFiClientBeforeClose);

	__hook(&CwclWiFiEvents::OnAcmInterfaceArrival, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsAcmInterfaceArrival);
	__hook(&CwclWiFiEvents::OnAcmInterfaceRemoval, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsAcmInterfaceRemoval);
	__hook(&CwclWiFiEvents::OnAcmScanComplete, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsAcmScanComplete);
	__hook(&CwclWiFiEvents::OnAcmScanFail, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsAcmScanFail);
	__hook(&CwclWiFiEvents::AfterOpen, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsAfterOpen);
	__hook(&CwclWiFiEvents::BeforeClose, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsBeforeClose);
	__hook(&CwclWiFiEvents::OnMsmRadioStateChange, &WiFiEvents, &CDroneRemoteIdDlg::WiFiEventsMsmRadioStateChange);

	FScanActive = false;
	FRootNode = NULL;

	int Res = WiFiClient.Open();
	if (Res != WCL_E_SUCCESS)
		Trace(_T("WiFiClient open failed"), Res);
	else
	{
		Res = WiFiEvents.Open();
		if (Res != WCL_E_SUCCESS)
			Trace(_T("WiFiEvents open failed"), Res);
		else
			EnumInterfaces();

		if (Res != WCL_E_SUCCESS)
			WiFiClient.Close();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDroneRemoteIdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDroneRemoteIdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDroneRemoteIdDlg::OnTvnSelchangedTreeDrones(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	ClearMessageDetails();

	if (tvDrones.GetSelectedCount() != 0)
	{
		if (tvDrones.GetItemData(tvDrones.GetSelectedItem()) != NULL)
		{
			UpdateMessageDetails(tvDrones.GetItemText(tvDrones.GetParentItem(tvDrones.GetSelectedItem())),
				(CwclWiFiDriMessage*)tvDrones.GetItemData(tvDrones.GetSelectedItem()));
		}
	}

	*pResult = 0;
}

CString CDroneRemoteIdDlg::IntToHex(const int Val) const
{
	CString s;
	s.Format(_T(".8X"), Val);
	return s;
}

CString CDroneRemoteIdDlg::IntToHex(const unsigned char Val) const
{
	CString s;
	s.Format(_T(".2X"), Val);
	return s;
}

CString CDroneRemoteIdDlg::FloatToStr(const float Val) const
{
	CString s;
	s.Format(_T("%f"), Val);
	return s;
}

CString CDroneRemoteIdDlg::FloatToStr(const double Val) const
{
	CString s;
	s.Format(_T("%f"), Val);
	return s;
}

CString CDroneRemoteIdDlg::IntToStr(const unsigned short Val) const
{
	CString s;
	s.Format(_T("%d"), Val);
	return s;
}

CString CDroneRemoteIdDlg::GuidToString(const GUID& Guid) const
{
	LPOLESTR GuidStr;
	StringFromCLSID(Guid, &GuidStr);
	CString ResStr(GuidStr);
	CoTaskMemFree(GuidStr);
	return ResStr;
}

CString CDroneRemoteIdDlg::DateTimeToStr(const time_t Time) const
{
	tm* ptm = localtime(&Time);
	TCHAR Buffer[32];
	// Format: Mo, 15.06.2009 20:20:00
	_tcsftime(Buffer, 32, _T("%a, %d.%m.%Y %H:%M:%S"), ptm);
	return CString(Buffer);
}

void CDroneRemoteIdDlg::Trace(const CString& Msg)
{
	lbLog.AddString(Msg);
	lbLog.SetTopIndex(lbLog.GetCount() - 1);
}

void CDroneRemoteIdDlg::Trace(const CString& Msg, int Res)
{
	Trace(Msg + _T(": 0x") + IntToHex(Res));
}

void CDroneRemoteIdDlg::AdapterDisabled()
{
	StopScan();
	FId = wclWiFi::GUID_NULL;

	btStart.EnableWindow(FALSE);
	btStop.EnableWindow(FALSE);
}

void CDroneRemoteIdDlg::ClearMessageDetails()
{
	lvDetails.DeleteAllItems();
}

void CDroneRemoteIdDlg::EnumInterfaces()
{
	btStart.EnableWindow(FALSE);
	btStop.EnableWindow(FALSE);

	wclWiFiInterfaces Ifaces;
	int Res = WiFiClient.EnumInterfaces(Ifaces);
	if (Res != WCL_E_SUCCESS)
		Trace(_T("Enum interfaces failed"), Res);
	else
	{
		if (Ifaces.size() == 0)
			Trace(_T("No one WiFi interface found"));
		else
		{
			bool Found = false;
			for (wclWiFiInterfaces::iterator Data = Ifaces.begin(); Data != Ifaces.end(); Data++)
			{
				CwclWiFiInterface* Iface = new CwclWiFiInterface(Data->Id);
				if (Iface->Open() == WCL_E_SUCCESS)
				{
					wclWiFiPhyRadioStates States;
					Res = Iface->GetRadioState(States);
					if (Res == WCL_E_SUCCESS)
					{
						if (States.size() > 0)
						{
							bool Enabled = false;
							for (wclWiFiPhyRadioStates::iterator State = States.begin(); State != States.end(); State++)
							{
								Enabled = (State->SoftwareState == rsOn && State->HardwareState == rsOn);
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
				delete Iface;

				if (Found)
					break;
			}

			if (Found)
			{
				Trace(_T("Use WiFi interface ") + GuidToString(FId));

				btStart.EnableWindow(TRUE);
				btStop.EnableWindow(FALSE);
			}
		}
	}
}

HTREEITEM CDroneRemoteIdDlg::FindDrone(const CString& Ssid)
{
	HTREEITEM Result = NULL;

	HTREEITEM DroneNode = tvDrones.GetChildItem(FRootNode);
	while (DroneNode != NULL)
	{
		if (tvDrones.GetItemText(DroneNode) == Ssid)
		{
			Result = DroneNode;
			break;
		}
		DroneNode = tvDrones.GetNextSiblingItem(DroneNode);
	}

	if (Result == NULL)
	{
		tvDrones.InsertItem(Ssid, FRootNode);
		tvDrones.Expand(FRootNode, TVE_EXPAND);
	}
	return Result;
}

CString CDroneRemoteIdDlg::MessageTypeToText(const CwclWiFiDriAsdMessage* const Message) const
{
	switch (Message->MessageType)
	{
		case mtBasicId:
			return _T("BASIC ID");
		case mtLocation:
			return _T("LOCATION");
		case mtAuth:
			return _T("AUTH");
		case mtSelfId:
			return _T("SELF ID");
		case mtSystem:
			return _T("SYSTEM");
		case mtOperatorId:
			return _T("OPERATOR ID");
		default:
			return _T("UNKNOWN");
	}
}

CString CDroneRemoteIdDlg::AsdVerticalAccuracyToText(
	const wclWiFiDriAsdUavVerticalAccuracy Accuracy) const
{
	switch (Accuracy)
	{
		case vaUnknown:
			return _T("Unknow");
		case va150M:
			return _T("150 m");
		case va45M:
			return _T("45 m");
		case va25M:
			return _T("25 m");
		case va10M:
			return _T("10 m");
		case va3M:
			return _T("3 m");
		case va1M:
			return _T("1 m");
		default:
			return _T("Raw value: 0x") + IntToHex(((unsigned char)Accuracy));
	}
}

CString CDroneRemoteIdDlg::AsdHeightReferenceToText(
	const wclWiFiDriAsdUavHeightReference Reference) const
{
	switch (Reference)
	{
		case hrTakeOff:
			return _T("Take off");
		case hrGround:
			return _T("Ground");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Reference);
	}
}

CString CDroneRemoteIdDlg::AsdHorizontalAccuracyToText(
	const wclWiFiDriAsdUavHorizontalAccuracy Accuracy) const
{
	switch (Accuracy)
	{
		case haUnknown:
			return _T("Unknown");
		case ha10Nm:
			return _T("10 miles");
		case ha4Nm:
			return _T("4 miles");
		case ha2Nm:
			return _T("2 miles");
		case ha1Nm:
			return _T("1 mile");
		case ha05Nm:
			return _T("0.5 mile");
		case ha03Nm:
			return _T("0.3 mile");
		case ha01Nm:
			return _T("0.1 mile");
		case ha005Nm:
			return _T("0.05 mile");
		case ha30M:
			return _T("30 meters");
		case ha10M:
			return _T("10 meters");
		case ha3M:
			return _T("3 meters");
		case ha1M:
			return _T("1 meter");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Accuracy);
	}
}

CString CDroneRemoteIdDlg::AsdSpeedAccuracyToText(
	const wclWiFiDriAsdUavSpeedAccuracy Accuracy) const
{
	switch (Accuracy)
	{
		case saUnknown:
			return _T("Unknown");
		case sa10MS:
			return _T("10 m/s");
		case sa3MS:
			return _T("3 m/s");
		case sa1Ms:
			return _T("1 m/s");
		case sa03Ms:
			return _T("0.3 m/s");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Accuracy);
	}
}

CString CDroneRemoteIdDlg::AsdStatusToText(const wclWiFiDriAsdUavStatus Status) const
{
	switch (Status)
	{
		case usUndeclared:
			return _T("Undeclared");
		case usGround:
			return _T("Ground");
		case usAirborne:
			return _T("Airborne");
		case usEmergency:
			return _T("Emergency");
		case usFailure:
			return _T("Failure");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Status);
	}
}

CString CDroneRemoteIdDlg::AsdTimestampAccuracyToText(
	const wclWiFiDriAsdUavTimestampAccuracy Accuracy) const
{
	switch (Accuracy)
	{
		case taUnknown:
			return _T("Unknown");
		case ta01s:
			return _T("0.1 second");
		case ta02s:
			return _T("0.2 second");
		case ta03s:
			return _T("0.3 second");
		case ta04s:
			return _T("0.4 second");
		case ta05s:
			return _T("0.5 second");
		case ta06s:
			return _T("0.6 second");
		case ta07s:
			return _T("0.7 second");
		case ta08s:
			return _T("0.8 second");
		case ta09s:
			return _T("0.9 second");
		case ta1s:
			return _T("1 second");
		case ta11s:
			return _T("1.1 second");
		case ta12s:
			return _T("1.2 second");
		case ta13s:
			return _T("1.3 second");
		case ta14s:
			return _T("1.4 second");
		case ta15s:
			return _T("1.5 second");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Accuracy);
	}
}

CString CDroneRemoteIdDlg::AsdAltitudeToText(const float Altitude) const
{
	if (Altitude == -1000)
		return _T("Invalid");
	return FloatToStr(Altitude);
}

CString CDroneRemoteIdDlg::AsdDescriptionTypeToText(
	const wclWiFiDriAsdDescriptionType DescriptionType) const
{
	switch (DescriptionType)
	{
		case dtText:
			return _T("Text");
		case dtEmergency:
			return _T("Emergency");
		case dtExtended:
			return _T("Extended");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)DescriptionType);
	}
}

CString CDroneRemoteIdDlg::AsdDirectionToText(const unsigned short Direction) const
{
	if (Direction > 360)
		return _T("Invalid");
	return IntToStr(Direction);
}

CString CDroneRemoteIdDlg::AsdHorizontalSpeedToText(const float Speed) const
{
	if (Speed == 255)
		return _T("Invalid");
	return FloatToStr(Speed);
}

CString CDroneRemoteIdDlg::AsdLatLonToText(const double LatLon) const
{
	if (LatLon == 0)
		return _T("Invalid");
	return FloatToStr(LatLon);
}

CString CDroneRemoteIdDlg::AsdOperatorClassificationToText(
	const wclWiDiDriAsdOperatorClassification Classification) const
{
	switch (Classification)
	{
		case ocUndeclared:
			return _T("Undeclared");
		case ocEu:
			return _T("EU");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Classification);
	}
}

CString CDroneRemoteIdDlg::AsdLocationTypeToText(
	const wclWiDiDriAsdOperatorLocationType Location) const
{
	switch (Location)
	{
		case ltTakeOff:
			return _T("Take off");
		case ltLiveGnss:
			return _T("Live GNSS");
		case ltFixed:
			return _T("Fixed");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Location);
	}
}

CString CDroneRemoteIdDlg::AsdEuUavCategoryToText(
	const wclWiDiDriAsdUavEuCategory Category) const
{
	switch (Category)
	{
		case ucUndeclared:
			return _T("Undeclared");
		case ucOpen:
			return _T("Open");
		case ucSpecific:
			return _T("Specific");
		case ucCertified:
			return _T("Certified");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)Category);
	}
}

CString CDroneRemoteIdDlg::AsdEuUavClassToText(const wclWiDiDriAsdUavEuClass UavClass) const
{
	switch (UavClass)
	{
		case ucUnspecified:
			return _T("Unspecified");
		case ucClass0:
			return _T("Class 0");
		case ucClass1:
			return _T("Class 1");
		case ucClass2:
			return _T("Class 2");
		case ucClass3:
			return _T("Class 3");
		case ucClass4:
			return _T("Class 4");
		case ucClass5:
			return _T("Class 5");
		case ucClass6:
			return _T("Class 6");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)UavClass);
	}
}

CString CDroneRemoteIdDlg::AsdIdTypeToText(const wclWiFiDriAsdIdType IdType) const
{
	switch (IdType)
	{
		case itNone:
			return _T("None");
		case itSerialNumber:
			return _T("Serial number");
		case itCaaRegistrationId:
			return _T("CAA registration ID");
		case itUtmAssignedUuid:
			return _T("UTM assigned UUID");
		case itSpecificSessionId:
			return _T("Specific session ID");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)IdType);
	}
}

CString CDroneRemoteIdDlg::AsdUavTypeToText(const wclWiFiDriAsdUavType UavType) const
{
	switch (UavType)
	{
		case utNone:
			return _T("None");
		case utAeroplane:
			return _T("Aeroplane");
		case utCopter:
			return _T("Copter");
		case utGyroplane:
			return _T("Gyroplane");
		case utHybridLift:
			return _T("Hybrid");
		case utOrnithopter:
			return _T("Ornithopter");
		case utGlider:
			return _T("Glider");
		case utKite:
			return _T("Kite");
		case utFreeBalloon:
			return _T("Free balloon");
		case utCaptiveBalloon:
			return _T("Captive balloon");
		case utAirship:
			return _T("Airship");
		case utFreeFallParachute:
			return _T("Free fall parachute");
		case utRocket:
			return _T("Rocket");
		case utTetheredPoweredAircraft:
			return _T("Tethered powered aircraft");
		case utGroundObstacle:
			return _T("Ground obstacle");
		default:
			return _T("Raw value: 0x") + IntToHex((unsigned char)UavType);
	}
}

void CDroneRemoteIdDlg::ShowAsdLocationMessage(
	const CwclWiFiDriAsdLocationMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("Baro Altitude"));
	lvDetails.SetItemText(Item, 1, AsdAltitudeToText(Message->BaroAltitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Baro Accuracy"));
	lvDetails.SetItemText(Item, 1, AsdVerticalAccuracyToText(Message->BaroAccuracy));
	Item++;

	lvDetails.InsertItem(Item, _T("Direction"));
	lvDetails.SetItemText(Item, 1, AsdDirectionToText(Message->Direction));
	Item++;

	lvDetails.InsertItem(Item, _T("Geo Altitude"));
	lvDetails.SetItemText(Item, 1, AsdAltitudeToText(Message->GeoAltitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Height"));
	lvDetails.SetItemText(Item, 1, AsdAltitudeToText(Message->Height));
	Item++;

	lvDetails.InsertItem(Item, _T("Height Reference"));
	lvDetails.SetItemText(Item, 1, AsdHeightReferenceToText(Message->HeightReference));
	Item++;

	lvDetails.InsertItem(Item, _T("Horizontal Accuracy"));
	lvDetails.SetItemText(Item, 1, AsdHorizontalAccuracyToText(Message->HorizontalAccuracy));
	Item++;

	lvDetails.InsertItem(Item, _T("Horizontal Speed"));
	lvDetails.SetItemText(Item, 1, AsdHorizontalSpeedToText(Message->HorizontalSpeed));
	Item++;

	lvDetails.InsertItem(Item, _T("Latitude"));
	lvDetails.SetItemText(Item, 1, AsdLatLonToText(Message->Latitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Longitude"));
	lvDetails.SetItemText(Item, 1, AsdLatLonToText(Message->Longitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Speed Accuracy"));
	lvDetails.SetItemText(Item, 1, AsdSpeedAccuracyToText(Message->SpeedAccuracy));
	Item++;

	lvDetails.InsertItem(Item, _T("Status"));
	lvDetails.SetItemText(Item, 1, AsdStatusToText(Message->Status));
	Item++;

	lvDetails.InsertItem(Item, _T("Timestamp"));
	lvDetails.SetItemText(Item, 1, FloatToStr(Message->Timestamp));
	Item++;

	lvDetails.InsertItem(Item, _T("Timestamp Accuracy"));
	lvDetails.SetItemText(Item, 1, AsdTimestampAccuracyToText(Message->TimestampAccuracy));
	Item++;

	lvDetails.InsertItem(Item, _T("Vertical Accuracy"));
	lvDetails.SetItemText(Item, 1, AsdVerticalAccuracyToText(Message->VerticalAccuracy));
	Item++;

	lvDetails.InsertItem(Item, _T("Vertical Speed"));
	lvDetails.SetItemText(Item, 1, FloatToStr(Message->VerticalSpeed));
}

void CDroneRemoteIdDlg::ShowAsdSelfIdMessage(const CwclWiFiDriAsdSelfIdMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("Description"));
	lvDetails.SetItemText(Item, 1, CString(Message->Description.c_str()));
	Item++;

	lvDetails.InsertItem(Item, _T("Description Type"));
	lvDetails.SetItemText(Item, 1, AsdDescriptionTypeToText(Message->DescriptionType));
	Item++;
}

void CDroneRemoteIdDlg::ShowAsdOperatorIdMessage(
	const CwclWiFiDriAsdOperatorIdMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("ID"));
	lvDetails.SetItemText(Item, 1, CString((char*)&Message->Id[0]));
	Item++;

	lvDetails.InsertItem(Item, _T("ID Type"));
	lvDetails.SetItemText(Item, 1, _T("0x") + IntToHex(Message->IdType));
}

void CDroneRemoteIdDlg::ShowAsdSystemMessage(const CwclWiFiDriAsdSystemMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("Area ceiling"));
	lvDetails.SetItemText(Item, 1, AsdAltitudeToText(Message->AreaCeiling));
	Item++;

	lvDetails.InsertItem(Item, _T("Area count"));
	lvDetails.SetItemText(Item, 1, IntToStr(Message->AreaCount));
	Item++;

	lvDetails.InsertItem(Item, _T("Area floor"));
	lvDetails.SetItemText(Item, 1, AsdAltitudeToText(Message->AreaFloor));
	Item++;

	lvDetails.InsertItem(Item, _T("Area radius"));
	lvDetails.SetItemText(Item, 1, IntToStr(Message->AreaRadius));
	Item++;

	lvDetails.InsertItem(Item, _T("Operator altitude"));
	lvDetails.SetItemText(Item, 1, FloatToStr(Message->OperatorAltitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Operator classification"));
	lvDetails.SetItemText(Item, 1, AsdOperatorClassificationToText(Message->OperatorClassification));
	Item++;

	lvDetails.InsertItem(Item, _T("Operator latitude"));
	lvDetails.SetItemText(Item, 1, AsdLatLonToText(Message->OperatorLatitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Operator latitude"));
	lvDetails.SetItemText(Item, 1, AsdLatLonToText(Message->OperatorLatitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Operator longitude"));
	lvDetails.SetItemText(Item, 1, AsdLatLonToText(Message->OperatorLongitude));
	Item++;

	lvDetails.InsertItem(Item, _T("Location type"));
	lvDetails.SetItemText(Item, 1, AsdLocationTypeToText(Message->OperatorLocation));
	Item++;

	lvDetails.InsertItem(Item, _T("Timestamp"));
	lvDetails.SetItemText(Item, 1, DateTimeToStr(Message->Timestamp));
	Item++;

	lvDetails.InsertItem(Item, _T("UAV EU category"));
	lvDetails.SetItemText(Item, 1, AsdEuUavCategoryToText(Message->UavEuCategory));
	Item++;

	lvDetails.InsertItem(Item, _T("UAV EU class"));
	lvDetails.SetItemText(Item, 1, AsdEuUavClassToText(Message->UavEuClass));
}

void CDroneRemoteIdDlg::ShowAsdBassicIdMessage(const CwclWiFiDriAsdBasicIdMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("ID"));
	lvDetails.SetItemText(Item, 1, CString((char*)&Message->Id[0]));
	Item++;

	lvDetails.InsertItem(Item, _T("ID type"));
	lvDetails.SetItemText(Item, 1, AsdIdTypeToText(Message->IdType));
	Item++;

	lvDetails.InsertItem(Item, _T("ID type"));
	lvDetails.SetItemText(Item, 1, AsdUavTypeToText(Message->UavType));
}

void CDroneRemoteIdDlg::ShowUnknownAsdMessage(const CwclWiFiDriAsdMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("Message type"));
	lvDetails.SetItemText(Item, 1, IntToHex((unsigned char)Message->MessageType));
	Item++;

	CString Str = _T("");
	if (Message->Data.size() > 0)
	{
		for (wclWiFiIeRawData::iterator b = Message->Data.begin(); b != Message->Data.end(); b++)
			Str += IntToHex(*b);
	}
	lvDetails.InsertItem(Item, _T("Raw date"));
	lvDetails.SetItemText(Item, 1, Str);
}

void CDroneRemoteIdDlg::UpdateAsdMessageDetails(const CString& Ssid,
	const CwclWiFiDriAsdMessage* const Message)
{
	int Item = lvDetails.GetItemCount();
	lvDetails.InsertItem(Item, _T("SSID"));
	lvDetails.SetItemText(Item, 1, Ssid);
	Item++;

	lvDetails.InsertItem(Item, _T(""));
	lvDetails.SetItemText(Item, 1, _T(""));

	switch (Message->MessageType)
	{
		case mtBasicId:
			ShowAsdBassicIdMessage((CwclWiFiDriAsdBasicIdMessage*)Message);
			break;
		case mtLocation:
			ShowAsdLocationMessage((CwclWiFiDriAsdLocationMessage*)Message);
			break;
		case mtAuth:
			ShowUnknownAsdMessage(Message);
			break;
		case mtSelfId:
			ShowAsdSelfIdMessage((CwclWiFiDriAsdSelfIdMessage*)Message);
			break;
		case mtSystem:
			ShowAsdSystemMessage((CwclWiFiDriAsdSystemMessage*)Message);
			break;
		case mtOperatorId:
			ShowAsdOperatorIdMessage((CwclWiFiDriAsdOperatorIdMessage*)Message);
			break;
		default:
			ShowUnknownAsdMessage(Message);
			break;
	}
}

void CDroneRemoteIdDlg::UpdateDroneMessages(const HTREEITEM Node,
	wclWiFiDriMessages& Messages)
{
	for (wclWiFiDriMessages::iterator Message = Messages.begin(); Message != Messages.end(); Message++)
	{
		if ((*Message)->Vendor != driAsd)
			delete (*Message);
		else
		{
			CwclWiFiDriAsdMessage* AsdMessage = (CwclWiFiDriAsdMessage*)(*Message);
			CString MessageType = MessageTypeToText(AsdMessage);

			HTREEITEM MessageNode = tvDrones.GetChildItem(Node);
			while (MessageNode != NULL)
			{
				if (tvDrones.GetItemText(MessageNode) == MessageType)
				{
					delete (CwclWiFiDriMessage*)tvDrones.GetItemData(MessageNode);
					tvDrones.SetItemData(MessageNode, NULL);
					break;
				}

				MessageNode = tvDrones.GetNextSiblingItem(MessageNode);
			}
			
			if (MessageNode == NULL)
				MessageNode  = tvDrones.InsertItem(MessageType, Node);
			tvDrones.SetItemData(MessageNode, (DWORD_PTR)AsdMessage);
			if (tvDrones.GetSelectedItem() == MessageNode)
				UpdateMessageDetails(tvDrones.GetItemText(tvDrones.GetParentItem(MessageNode)), AsdMessage);
		}
	}
}

void CDroneRemoteIdDlg::UpdateMessageDetails(const CString& Ssid, const CwclWiFiDriMessage* const Message)
{
	ClearMessageDetails();

	if (Message->Vendor == driAsd)
		UpdateAsdMessageDetails(Ssid, (CwclWiFiDriAsdMessage*)Message);
}

void CDroneRemoteIdDlg::UpdateMessages(const CString& Ssid, wclWiFiDriMessages& Messages)
{
	HTREEITEM DroneNode = FindDrone(Ssid);
	if (DroneNode != NULL)
	{
		UpdateDroneMessages(DroneNode, Messages);
		tvDrones.Expand(DroneNode, TVE_EXPAND);
	}
}

void CDroneRemoteIdDlg::GetDriInfo()
{
	wclWiFiBssArray BssList;
	int Res  = WiFiClient.EnumBss(FId, _T(""), bssAny, true, BssList);
	if (Res != WCL_E_SUCCESS)
		Trace(_T("Enum BSS failed"), Res);
	else
	{
		if (BssList.size() > 0)
		{
			wclWiFiDriMessages Messages;
			for (wclWiFiBssArray::iterator Bss = BssList.begin(); Bss != BssList.end(); Bss++)
			{
				if (Bss->IeRaw.size() > 0)
				{
					FParser.ParseDriMessages(*Bss, Messages);
					if (Messages.size() > 0)
						UpdateMessages(CString(Bss->Ssid.c_str()), Messages);
				}
			}
		}
	}
}

void CDroneRemoteIdDlg::RestartScan()
{
	if (FScanActive)
	{
		int Res = WiFiClient.Scan(FId);
		if (Res != WCL_E_SUCCESS)
		{
			Trace(_T("Restart scan failed"), Res);

			StopScan();
		}
	}
}

void CDroneRemoteIdDlg::StartScan()
{
	if (!FScanActive)
	{
		if (FId != wclWiFi::GUID_NULL)
		{
			int Res = WiFiClient.Scan(FId);
			if (Res != WCL_E_SUCCESS)
				Trace(_T("Start scan failed"), Res);
			else
			{
				btStart.EnableWindow(FALSE);
				btStop.EnableWindow(TRUE);

				FScanActive = true;
				FRootNode = tvDrones.InsertItem(_T("Drones"));

				Trace(_T("Scan started"));
			}
		}
	}
}

void CDroneRemoteIdDlg::StopScan()
{
	if (FScanActive)
	{
		btStart.EnableWindow(TRUE);
		btStop.EnableWindow(FALSE);

		FScanActive = false;

		tvDrones.DeleteAllItems();
		FRootNode = NULL;

		ClearMessageDetails();

		Trace(_T("Scan sopped"));
	}
}

void CDroneRemoteIdDlg::WiFiEventsMsmRadioStateChange(void* sender, const GUID& IfaceId,
	const wclWiFiPhyRadioState& State)
{
	UNREFERENCED_PARAMETER(sender);

	if (FId == wclWiFi::GUID_NULL)
		EnumInterfaces();
	else
	{
		if (FId == IfaceId)
		{
			if (State.SoftwareState == rsOff || State.HardwareState == rsOff)
			{
				Trace(_T("Adapter disabled"));

				AdapterDisabled();
			}
		}
	}
}

void CDroneRemoteIdDlg::WiFiEventsBeforeClose(void* sender)
{
	UNREFERENCED_PARAMETER(sender);

	Trace(_T("WiFi Events closed"));
}

void CDroneRemoteIdDlg::WiFiEventsAfterOpen(void* sender)
{
	UNREFERENCED_PARAMETER(sender);

	Trace(_T("WiFi Events opened"));
}

void CDroneRemoteIdDlg::WiFiEventsAcmScanFail(void* sender, const GUID& IfaceId, const int Reason)
{
	UNREFERENCED_PARAMETER(sender);

	if (FScanActive && FId == IfaceId)
	{
		Trace(_T("Scan failed"), Reason);

		RestartScan();
	}
}

void CDroneRemoteIdDlg::WiFiEventsAcmScanComplete(void* sender, const GUID& IfaceId)
{
	UNREFERENCED_PARAMETER(sender);

	if (FScanActive && FId == IfaceId)
	{
		GetDriInfo();

		RestartScan();
	}
}

void CDroneRemoteIdDlg::WiFiEventsAcmInterfaceRemoval(void* sender, const GUID& IfaceId)
{
	UNREFERENCED_PARAMETER(sender);

	if (FId == IfaceId)
	{
		Trace(_T("Adapter removed"));

		AdapterDisabled();
	}
}

void CDroneRemoteIdDlg::WiFiEventsAcmInterfaceArrival(void* sender, const GUID& IfaceId)
{
	UNREFERENCED_PARAMETER(sender);

	if (FId == wclWiFi::GUID_NULL)
		EnumInterfaces();
}

void CDroneRemoteIdDlg::WiFiClientBeforeClose(void* sender)
{
	UNREFERENCED_PARAMETER(sender);

	Trace(_T("WiFi Client closed"));
}

void CDroneRemoteIdDlg::WiFiClientAfterOpen(void* sender)
{
	UNREFERENCED_PARAMETER(sender);

	Trace(_T("WiFi Client opened"));
}

void CDroneRemoteIdDlg::OnBnClickedButtonClear()
{
	lbLog.ResetContent();
}

void CDroneRemoteIdDlg::OnBnClickedButtonStart()
{
	StartScan();
}

void CDroneRemoteIdDlg::OnBnClickedButtonStop()
{
	StopScan();
}

void CDroneRemoteIdDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	StopScan();

	WiFiEvents.Close();
	WiFiClient.Close();

	__unhook(&WiFiEvents);
	__unhook(&WiFiClient);
}
