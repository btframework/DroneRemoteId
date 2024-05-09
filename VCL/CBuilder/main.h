//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "wclWiFi.hpp"
#include "wclWiFiDri.hpp"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-managed Components
	TButton *btStart;
	TButton *btStop;
	TListBox *lbLog;
	TButton *btClear;
	TTreeView *tvDrones;
	TListView *lvDetails;
	TwclWiFiClient *WiFiClient;
	TwclWiFiEvents *WiFiEvents;
	void __fastcall tvDronesClick(TObject *Sender);
	void __fastcall WiFiClientAfterOpen(TObject *Sender);
	void __fastcall WiFiClientBeforeClose(TObject *Sender);
	void __fastcall WiFiEventsAcmInterfaceArrival(TObject *Sender,
		const TGUID &IfaceId);
	void __fastcall WiFiEventsAcmInterfaceRemoval(TObject *Sender,
		const TGUID &IfaceId);
	void __fastcall WiFiEventsAcmScanComplete(TObject *Sender,
		const TGUID &IfaceId);
	void __fastcall WiFiEventsAcmScanFail(TObject *Sender, const TGUID &IfaceId,
		const int Reason);
	void __fastcall WiFiEventsAfterOpen(TObject *Sender);
	void __fastcall WiFiEventsBeforeClose(TObject *Sender);
	void __fastcall WiFiEventsMsmRadioStateChange(TObject *Sender,
		const TGUID &IfaceId, const TwclWiFiPhyRadioState &State);
	void __fastcall btClearClick(TObject *Sender);
	void __fastcall btStartClick(TObject *Sender);
	void __fastcall btStopClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
	TGUID FId;
	TwclWiFiDriParser* FParser;
	TTreeNode* FRootNode;
	bool FScanActive;

	void __fastcall EnumInterfaces();

	void __fastcall Trace(String Msg);
	void __fastcall Trace(String Msg, int Res);

	void __fastcall AdapterDisabled();
	void __fastcall RestartScan();
	void __fastcall StartScan();
	void __fastcall StopScan();

	TTreeNode* __fastcall FindDrone(String Ssid);
	String __fastcall MessageTypeToText(TwclWiFiDriAsdMessage* Message);

	String __fastcall AsdVerticalAccuracyToText(
		TwclWiFiDriAsdUavVerticalAccuracy Accuracy);
	String __fastcall AsdHeightReferenceToText(
		TwclWiFiDriAsdUavHeightReference Reference);
	String __fastcall AsdHorizontalAccuracyToText(
		TwclWiFiDriAsdUavHorizontalAccuracy Accuracy);
	String __fastcall AsdSpeedAccuracyToText(
		TwclWiFiDriAsdUavSpeedAccuracy Accuracy);
	String __fastcall AsdStatusToText(TwclWiFiDriAsdUavStatus Status);
	String __fastcall AsdTimestampAccuracyToText(
		TwclWiFiDriAsdUavTimestampAccuracy Accuracy);
	String __fastcall AsdAltitudeToText(float Altitude);
	String __fastcall AsdDescriptionTypeToText(
		TwclWiFiDriAsdDescriptionType DescriptionType);
	String __fastcall AsdDirectionToText(unsigned short Direction);
	String __fastcall AsdHorizontalSpeedToText(float Speed);
	String __fastcall AsdLatLonToText(double LatLon);
	String __fastcall AsdOperatorClassificationToText(
		TwclWiDiDriAsdOperatorClassification Classification);
	String __fastcall AsdLocationTypeToText(
		TwclWiDiDriAsdOperatorLocationType Location);
	String __fastcall AsdEuUavCategoryToText(
		TwclWiDiDriAsdUavEuCategory Category);
	String __fastcall AsdEuUavClassToText(TwclWiDiDriAsdUavEuClass UavClass);
	String __fastcall AsdIdTypeToText(TwclWiFiDriAsdIdType IdType);
	String __fastcall AsdUavTypeToText(TwclWiFiDriAsdUavType UavType);

	void __fastcall ShowAsdLocationMessage(
		TwclWiFiDriAsdLocationMessage* Message);
	void __fastcall ShowAsdSelfIdMessage(TwclWiFiDriAsdSelfIdMessage* Message);
	void __fastcall ShowAsdOperatorIdMessage(
		TwclWiFiDriAsdOperatorIdMessage* Message);
	void __fastcall ShowAsdSystemMessage(TwclWiFiDriAsdSystemMessage* Message);
	void __fastcall ShowAsdBassicIdMessage(
		TwclWiFiDriAsdBasicIdMessage* Message);
	void __fastcall ShowUnknownAsdMessage(TwclWiFiDriAsdMessage* Message);

	void __fastcall ClearMessageDetails();
	void __fastcall GetDriInfo();
	void __fastcall UpdateAsdMessageDetails(String Ssid,
		TwclWiFiDriAsdMessage* Message);
	void __fastcall UpdateDroneMessages(TTreeNode* Node, TList* Messages);
	void __fastcall UpdateMessageDetails(String Ssid,
		TwclWiFiDriMessage* Message);
	void __fastcall UpdateMessages(String Ssid, TList* Messages);

public:		// User declarations
	__fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
