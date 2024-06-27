//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "wclWiFi.hpp"
#include <Vcl.ComCtrls.hpp>
#include "wclBluetooth.hpp"
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
	TwclBluetoothManager *BluetoothManager;
	TwclBluetoothLeBeaconWatcher *BeaconWatcher;
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
	void __fastcall BeaconWatcherDriAsdMessage(TObject *Sender, const __int64 Address,
          const __int64 Timestamp, const SByte Rssi, const TwclDriRawData Raw);
	void __fastcall BluetoothManagerAfterOpen(TObject *Sender);
	void __fastcall BluetoothManagerClosed(TObject *Sender);
	void __fastcall BeaconWatcherStarted(TObject *Sender);
	void __fastcall BeaconWatcherStopped(TObject *Sender);


private:	// User declarations
	TGUID FId;
	TwclDriAsdParser* FBtParser;
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
	String __fastcall MessageTypeToText(TwclDriAsdMessage* Message);

	String __fastcall AsdVerticalAccuracyToText(
		TwclDriAsdUavVerticalAccuracy Accuracy);
	String __fastcall AsdHeightReferenceToText(
		TwclDriAsdUavHeightReference Reference);
	String __fastcall AsdHorizontalAccuracyToText(
		TwclDriAsdUavHorizontalAccuracy Accuracy);
	String __fastcall AsdSpeedAccuracyToText(
		TwclDriAsdUavSpeedAccuracy Accuracy);
	String __fastcall AsdStatusToText(TwclDriAsdUavStatus Status);
	String __fastcall AsdTimestampAccuracyToText(
		TwclDriAsdUavTimestampAccuracy Accuracy);
	String __fastcall AsdAltitudeToText(float Altitude);
	String __fastcall AsdDescriptionTypeToText(
		TwclDriAsdDescriptionType DescriptionType);
	String __fastcall AsdDirectionToText(unsigned short Direction);
	String __fastcall AsdHorizontalSpeedToText(float Speed);
	String __fastcall AsdLatLonToText(double LatLon);
	String __fastcall AsdOperatorClassificationToText(
		TwclDriAsdOperatorClassification Classification);
	String __fastcall AsdLocationTypeToText(
		TwclDriAsdOperatorLocationType Location);
	String __fastcall AsdEuUavCategoryToText(
		TwclDriAsdUavEuCategory Category);
	String __fastcall AsdEuUavClassToText(TwclDriAsdUavEuClass UavClass);
	String __fastcall AsdIdTypeToText(TwclDriAsdIdType IdType);
	String __fastcall AsdUavTypeToText(TwclDriAsdUavType UavType);
	String __fastcall VendorToText(TwclDriMessage* Message);

	void __fastcall ShowAsdLocationMessage(
		TwclDriAsdLocationMessage* Message);
	void __fastcall ShowAsdSelfIdMessage(TwclDriAsdSelfIdMessage* Message);
	void __fastcall ShowAsdOperatorIdMessage(
		TwclDriAsdOperatorIdMessage* Message);
	void __fastcall ShowAsdSystemMessage(TwclDriAsdSystemMessage* Message);
	void __fastcall ShowAsdBassicIdMessage(
		TwclDriAsdBasicIdMessage* Message);
	void __fastcall ShowUnknownAsdMessage(TwclDriAsdMessage* Message);

	void __fastcall ClearMessageDetails();
	void __fastcall GetDriInfo();
	void __fastcall UpdateAsdMessageDetails(String Ssid,
		TwclDriAsdMessage* Message);
	void __fastcall UpdateDroneMessages(TTreeNode* Node, TList* Messages);
	void __fastcall UpdateMessageDetails(String Ssid,
		TwclDriMessage* Message);
	void __fastcall UpdateMessages(String Ssid, TList* Messages);

public:		// User declarations
	__fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
