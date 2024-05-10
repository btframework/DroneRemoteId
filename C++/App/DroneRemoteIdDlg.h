
// DroneRemoteIdDlg.h : header file
//

#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "wclWiFiDri.h"

using namespace wclWiFi;
using namespace wclWiFi::Dri;


// CDroneRemoteIdDlg dialog
class CDroneRemoteIdDlg : public CDialogEx
{
// Construction
public:
	CDroneRemoteIdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRONEREMOTEID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTvnSelchangedTreeDrones(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl tvDrones;
	CListCtrl lvDetails;
	CButton btStart;
	CButton btStop;
	CListBox lbLog;

private:
	CwclWiFiClient WiFiClient;
	CwclWiFiEvents WiFiEvents;
	
	GUID FId;
	CwclWiFiDriParser FParser;
	HTREEITEM FRootNode;
	bool FScanActive;

	CString IntToHex(const int Val) const;
	CString IntToHex(const unsigned char Val) const;
	CString FloatToStr(const float Val) const;
	CString FloatToStr(const double Val) const;
	CString IntToStr(const unsigned short Val) const;
	CString GuidToString(const GUID& Guid) const;
	CString DateTimeToStr(const time_t Time) const;

	void Trace(const CString& Msg);
	void Trace(const CString& Msg, int Res);
	void AdapterDisabled();
	void ClearMessageDetails();
	void EnumInterfaces();
	HTREEITEM FindDrone(const CString& Ssid);

	CString MessageTypeToText(const CwclWiFiDriAsdMessage* const Message) const;
	CString AsdVerticalAccuracyToText(const wclWiFiDriAsdUavVerticalAccuracy Accuracy) const;
	CString AsdHeightReferenceToText(const wclWiFiDriAsdUavHeightReference Reference) const;
	CString AsdHorizontalAccuracyToText(const wclWiFiDriAsdUavHorizontalAccuracy Accuracy) const;
	CString AsdSpeedAccuracyToText(const wclWiFiDriAsdUavSpeedAccuracy Accuracy) const;
	CString AsdStatusToText(const wclWiFiDriAsdUavStatus Status) const;
	CString AsdTimestampAccuracyToText(const wclWiFiDriAsdUavTimestampAccuracy Accuracy) const;
	CString AsdAltitudeToText(const float Altitude) const;
	CString AsdDescriptionTypeToText(const wclWiFiDriAsdDescriptionType DescriptionType) const;
	CString AsdDirectionToText(const unsigned short Direction) const;
	CString AsdHorizontalSpeedToText(const float Speed) const;
	CString AsdLatLonToText(const double LatLon) const;
	CString AsdOperatorClassificationToText(const wclWiDiDriAsdOperatorClassification Classification) const;
	CString AsdLocationTypeToText(const wclWiDiDriAsdOperatorLocationType Location) const;
	CString AsdEuUavCategoryToText(const wclWiDiDriAsdUavEuCategory Category) const;
	CString AsdEuUavClassToText(const wclWiDiDriAsdUavEuClass UavClass) const;
	CString AsdIdTypeToText(const wclWiFiDriAsdIdType IdType) const;
	CString AsdUavTypeToText(const wclWiFiDriAsdUavType UavType) const;
	CString VendorToText(const CwclWiFiDriMessage* const Message) const;

	void ShowAsdLocationMessage(const CwclWiFiDriAsdLocationMessage* const Message);
	void ShowAsdSelfIdMessage(const CwclWiFiDriAsdSelfIdMessage* const Message);
	void ShowAsdOperatorIdMessage(const CwclWiFiDriAsdOperatorIdMessage* const Message);
	void ShowAsdSystemMessage(const CwclWiFiDriAsdSystemMessage* const Message);
	void ShowAsdBassicIdMessage(const CwclWiFiDriAsdBasicIdMessage* const Message);
	void ShowUnknownAsdMessage(const CwclWiFiDriAsdMessage* const Message);

	void UpdateAsdMessageDetails(const CString& Ssid, const CwclWiFiDriAsdMessage* const Message);
	void UpdateDroneMessages(const HTREEITEM Node, wclWiFiDriMessages& Messages);
	void UpdateMessageDetails(const CString& Ssid, const CwclWiFiDriMessage* const Message);
	void UpdateMessages(const CString& Ssid, wclWiFiDriMessages& Messages);

	void GetDriInfo();

	void RestartScan();
	void StartScan();
	void StopScan();

	void WiFiEventsMsmRadioStateChange(void* sender, const GUID& IfaceId,
		const wclWiFiPhyRadioState& State);
	void WiFiEventsBeforeClose(void* sender);
	void WiFiEventsAfterOpen(void* sender);
	void WiFiEventsAcmScanFail(void* sender, const GUID& IfaceId, const int Reason);
	void WiFiEventsAcmScanComplete(void* sender, const GUID& IfaceId);
	void WiFiEventsAcmInterfaceRemoval(void* sender, const GUID& IfaceId);
	void WiFiEventsAcmInterfaceArrival(void* sender, const GUID& IfaceId);

	void WiFiClientBeforeClose(void* sender);
	void WiFiClientAfterOpen(void* sender);
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnDestroy();
};
