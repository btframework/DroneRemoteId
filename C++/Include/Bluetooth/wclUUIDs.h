////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Wireless Communication Library 7                                         //
//                                                                            //
//   Copyright (C) 2006-2024 Mike Petrichenko                                 //
//                           Soft Service Company                             //
//                           All Rights Reserved                              //
//                                                                            //
//   http://www.btframework.com                                               //
//                                                                            //
//   support@btframework.com                                                  //
//   shop@btframework.com                                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace wclBluetooth
{
	/// <summary> Bluetooth base UUID. </summary>
	const GUID Bluetooth_Base_UUID = { 0x00000000, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

	/* Protocol UUIDs. */

	/// <summary> SDP UUID. </summary>
	const GUID SDP_PROTOCOL_UUID = { 0x00000001, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UDP UUID. </summary>
	const GUID UDP_PROTOCOL_UUID = { 0x00000002, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> RFCOMM protocol UUID. </summary>
	const GUID RFCOMM_PROTOCOL_UUID = { 0x00000003, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> TCP UUID. </summary>
	const GUID TCP_PROTOCOL_UUID = { 0x00000004, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> TCS-BIN protocol UUID. </summary>
	const GUID TCSBIN_PROTOCOL_UUID = { 0x00000005, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> TCS–AT protocol UUID. </summary>
	const GUID TCSAT_PROTOCOL_UUID = { 0x00000006, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> ATT protocol UUID. </summary>
	const GUID ATT_PROTOCOL_UUID = { 0x00000007, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> OBEX protocol UUID. </summary>
	const GUID OBEX_PROTOCOL_UUID = { 0x00000008, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> IP UUID. </summary>
	const GUID IP_PROTOCOL_UUID = { 0x00000009, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> FTP UUID. </summary>
	const GUID FTP_PROTOCOL_UUID = { 0x0000000A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HTTP UUID. </summary>
	const GUID HTTP_PROTOCOL_UUID = { 0x0000000C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> WSP UUID. </summary>
	const GUID WSP_PROTOCOL_UUID = { 0x0000000E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> BNEP UUID. </summary>
	const GUID BNEP_PROTOCOL_UUID = { 0x0000000F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UPnP protocol UUID. </summary>
	const GUID UPNP_PROTOCOL_UUID = { 0x00000010, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HID protocol UUID. </summary>
	const GUID HID_PROTOCOL_UUID = { 0x00000011, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HCCC protocol UUID. </summary>
	const GUID HCCC_PROTOCOL_UUID = { 0x00000012, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HCDC protocol UUID. </summary>
	const GUID HCDC_PROTOCOL_UUID = { 0x00000014, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Home network protocol UUID. </summary>
	const GUID HN_PROTOCOL_UUID = { 0x00000016, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> AVCTP UUID. </summary>
	const GUID AVCTP_PROTOCOL_UUID = { 0x00000017, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> AVDTP UUID. </summary>
	const GUID AVDTP_PROTOCOL_UUID = { 0x00000019, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> CMPT protocol UUID. </summary>
	const GUID CMPT_PROTOCOL_UUID = { 0x0000001B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UDI C Plane protocol UUID. </summary>
	const GUID UDI_C_PLANE_PROTOCOL_UUID = { 0x0000001D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> MCAP control channel protocol UUID. </summary>
	const GUID MCAP_CONTROL_PROTOCOL_UUID = { 0x0000001E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> MCAP data channel protocol UUID. </summary>
	const GUID MCAP_DATA_PROTOCOL_UUID = { 0x0000001F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> L2CAP UUID. </summary>
	const GUID L2CAP_PROTOCOL_UUID = { 0x00000100, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

	/// <summary> SDP short UUID. </summary>
	#define SDP_PROTOCOL_UUID16				0x0001
	/// <summary> UDP short UUID. </summary>
	#define UDP_PROTOCOL_UUID16				0x0002
	/// <summary> RFCOMM protocol short UUID. </summary>
	#define RFCOMM_PROTOCOL_UUID16			0x0003
	/// <summary> TCP short UUID. </summary>
	#define TCP_PROTOCOL_UUID16				0x0004
	/// <summary> TCS-BIN protocol short UUID. </summary>
	#define TCSBIN_PROTOCOL_UUID16			0x0005
	/// <summary> TCS–AT protocol short UUID. </summary>
	#define TCSAT_PROTOCOL_UUID16			0x0006
	/// <summary> ATT protocol UUID. </summary>
	#define ATT_PROTOCOL_UUID16				0x0007
	/// <summary> OBEX protocol short UUID. </summary>
	#define OBEX_PROTOCOL_UUID16			0x0008
	/// <summary> IP short UUID. </summary>
	#define IP_PROTOCOL_UUID16				0x0009
	/// <summary> FTP short UUID. </summary>
	#define FTP_PROTOCOL_UUID16				0x000A
	/// <summary> HTTP short UUID. </summary>
	#define HTTP_PROTOCOL_UUID16			0x000C
	/// <summary> WSP short UUID. </summary>
	#define WSP_PROTOCOL_UUID16				0x000E
	/// <summary> BNEP short UUID. </summary>
	#define BNEP_PROTOCOL_UUID16			0x000F
	/// <summary> UPnP protocol short UUID. </summary>
	#define UPNP_PROTOCOL_UUID16			0x0010
	/// <summary> HID protocol short UUID. </summary>
	#define HID_PROTOCOL_UUID16				0x0011
	/// <summary> HCCC protocol short UUID. </summary>
	#define HCCC_PROTOCOL_UUID16			0x0012
	/// <summary> HCDC protocol short UUID. </summary>
	#define HCDC_PROTOCOL_UUID16			0x0014
	/// <summary> Home network protocol short UUID. </summary>
	#define HN_PROTOCOL_UUID16				0x0016
	/// <summary> AVCTP short UUID. </summary>
	#define AVCTP_PROTOCOL_UUID16			0x0017
	/// <summary> AVDTP short UUID. </summary>
	#define AVDTP_PROTOCOL_UUID16			0x0019
	/// <summary> CMPT protocol short UUID. </summary>
	#define CMPT_PROTOCOL_UUID16			0x001B
	/// <summary> UDI C Plane protocol short UUID. </summary>
	#define UDI_C_PLANE_PROTOCOL_UUID16		0x001D;
	/// <summary> MCAP control channel protocol UUID. </summary>
	#define MCAP_CONTROL_PROTOCOL_UUID16	0x001E
	/// <summary> MCAP data channel protocol UUID. </summary>
	#define MCAP_DATA_PROTOCOL_UUID16		0x001F
	/// <summary> L2CAP short UUID. </summary>
	#define L2CAP_PROTOCOL_UUID16			0x0100

	/* Service Class UUIDs. */

	/// <summary> Service discovery server service class ID. </summary>
	const GUID ServiceDiscoveryServerServiceClassID_UUID = { 0x00001000, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Browse group descriptor service class ID. </summary>
	const GUID BrowseGroupDescriptorServiceClassID_UUID = { 0x00001001, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Public browse group service class ID. </summary>
	const GUID PublicBrowseGroupServiceClass_UUID = { 0x00001002, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Serial Port service class ID. </summary>
	const GUID SerialPortServiceClass_UUID = { 0x00001101, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> LAN access using PPP service class ID. </summary>
	const GUID LANAccessUsingPPPServiceClass_UUID = { 0x00001102, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Dialup networking service class ID. </summary>
	const GUID DialupNetworkingServiceClass_UUID = { 0x00001103, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> IrMC sync service class ID. </summary>
	const GUID IrMCSyncServiceClass_UUID = { 0x00001104, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> OBEX object push service class ID. </summary>
	const GUID OBEXObjectPushServiceClass_UUID = { 0x00001105, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> OBEX file transfer service class ID. </summary>
	const GUID OBEXFileTransferServiceClass_UUID = { 0x00001106, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> IrMC sync command service class ID. </summary>
	const GUID IrMCSyncCommandServiceClass_UUID = { 0x00001107, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Headset service class ID. </summary>
	const GUID HeadsetServiceClass_UUID = { 0x00001108, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Cordless telephony service class ID. </summary>
	const GUID CordlessTelephonyServiceClass_UUID = { 0x00001109, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Audio source service class ID. </summary>
	const GUID AudioSourceServiceClass_UUID = { 0x0000110A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Audio sink service class ID. </summary>
	const GUID AudioSinkServiceClass_UUID = { 0x0000110B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> A/V remote control target service class ID. </summary>
	const GUID AVRemoteControlTargetServiceClass_UUID = { 0x0000110C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Advanced audio distribution service class ID. </summary>
	const GUID AdvancedAudioDistributionServiceClass_UUID = { 0x0000110D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> A/V remote control service class ID. </summary>
	const GUID AVRemoteControlServiceClass_UUID = { 0x0000110E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Video conferencing service class ID. </summary>
	const GUID VideoConferencingServiceClass_UUID = { 0x0000110F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Intercom service class ID. </summary>
	const GUID IntercomServiceClass_UUID = { 0x00001110, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Fax service class ID. </summary>
	const GUID FaxServiceClass_UUID = { 0x00001111, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Headset audio gateway service class ID. </summary>
	const GUID HeadsetAudioGatewayServiceClass_UUID = { 0x00001112, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> WAP service class ID. </summary>
	const GUID WAPServiceClass_UUID = { 0x00001113, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> WAP client service class ID. </summary>
	const GUID WAPClientServiceClass_UUID = { 0x00001114, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> PANU service class ID. </summary>
	const GUID PANUServiceClass_UUID = { 0x00001115, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> NAP service class ID. </summary>
	const GUID NAPServiceClass_UUID = { 0x00001116, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> GN service class ID. </summary>
	const GUID GNServiceClass_UUID = { 0x00001117, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Direct printing service class ID. </summary>
	const GUID DirectPrintingServiceClass_UUID = { 0x00001118, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Reference printing service class ID. </summary>
	const GUID ReferencePrintingServiceClass_UUID = { 0x00001119, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Basic imaging service class ID. </summary>
	const GUID ImagingServiceClass_UUID = { 0x0000111A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Imaging responder service class ID. </summary>
	const GUID ImagingResponderServiceClass_UUID = { 0x0000111B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Imaging automatic archive service class ID. </summary>
	const GUID ImagingAutomaticArchiveServiceClass_UUID = { 0x0000111C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Imaging referenced objects service class ID. </summary>
	const GUID ImagingReferenceObjectsServiceClass_UUID = { 0x0000111D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Handsfree service class ID. </summary>
	const GUID HandsfreeServiceClass_UUID = { 0x0000111E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Handsfree audio gateway service class ID. </summary>
	const GUID HandsfreeAudioGatewayServiceClass_UUID = { 0x0000111F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Direct printing reference objects service class ID. </summary>
	const GUID DirectPrintingReferenceObjectsServiceClass_UUID = { 0x00001120, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Reflected UI service class ID. </summary>
	const GUID ReflectedUIServiceClass_UUID = { 0x00001121, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Basic printing service class ID. </summary>
	const GUID BasicPrintingServiceClass_UUID = { 0x00001122, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Printing status service class ID. </summary>
	const GUID PrintingStatusServiceClass_UUID = { 0x00001123, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Human interface device service class ID. </summary>
	const GUID HumanInterfaceDeviceServiceClass_UUID = { 0x00001124, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Hardcopy cable replacement service class ID. </summary>
	const GUID HardcopyCableReplacementServiceClass_UUID = { 0x00001125, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HCR print service class ID. </summary>
	const GUID HCRPrintServiceClass_UUID = { 0x00001126, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HCR scan service class ID. </summary>
	const GUID HCRScanServiceClass_UUID = { 0x00001127, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Common ISDN access service class ID. </summary>
	const GUID CommonISDNAccessServiceClass_UUID = { 0x00001128, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Video conferencing GW service class ID. </summary>
	const GUID VideoConferencingGWServiceClass_UUID = { 0x00001129, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UDIMT service class ID. </summary>
	const GUID UDIMTServiceClass_UUID = { 0x0000112A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UDITA service class ID. </summary>
	const GUID UDITAServiceClass_UUID = { 0x0000112B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Audio/video service class ID. </summary>
	const GUID AudioVideoServiceClass_UUID = { 0x0000112C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> SIM access service class ID. </summary>
	const GUID SimAccessServiceClass_UUID = { 0x0000112D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Phonebook access client equipment (PCE) service class ID. </summary>
	const GUID PhonebookClientEquipmentServiceClass_UUID = { 0x0000112E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Phonebook server equipment (PSE) service class ID. </summary>
	const GUID PhonebookServerEquipmentServiceClass_UUID = { 0x0000112F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Phonebook access service class ID. </summary>
	const GUID PhonebookServiceClass_UUID = { 0x00001130, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Headset HS service class ID. </summary>
	const GUID HeadsetHSServiceClass_UUID = { 0x00001131, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Message access server service class ID. </summary>
	const GUID MessageAccessServerServiceClass_UUID = { 0x00001132, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Message notification server service class ID. </summary>
	const GUID MessageNotificationServerServiceClass_UUID = { 0x00001133, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Message access profile service class ID. </summary>
	const GUID MessageAccessProfileServiceClass_UUID = { 0x00001134, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> GNSS profile service class ID. </summary>
	const GUID GNSSProfileServiceClass_UUID = { 0x00001135, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> GNSS server service class ID. </summary>
	const GUID GNSSServerServiceClass_UUID = { 0x00001136, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> 3D display service class ID. </summary>
	const GUID ThreeDDisplayServiceClass_UUID = { 0x00001137, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> 3D glasses service class ID. </summary>
	const GUID ThreeDGlassesServiceClass_UUID = { 0x00001138, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> 3D synchronization profile service class ID. </summary>
	const GUID ThreeDSynchronizationProfileServiceClass_UUID = { 0x00001139, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> MPS profile service class ID. </summary>
	const GUID MPSProfileServiceClass_UUID = { 0x0000113A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> MPSS service class ID. </summary>
	const GUID MPSSCServiceClass_UUID = { 0x0000113B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> CTN access service class ID. </summary>
	const GUID CTNAccessServiceClass_UUID = { 0x0000113C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> CTN notification service class ID. </summary>
	const GUID CTNNotificationServiceClass_UUID = { 0x0000113D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> CTN profile service class ID. </summary>
	const GUID CTNProfileServiceClass_UUID = { 0x0000113E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> PnP information service class ID. </summary>
	const GUID PnPInformationServiceClass_UUID = { 0x00001200, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Generic networking service class ID. </summary>
	const GUID GenericNetworkingServiceClass_UUID = { 0x00001201, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Generic file transfer service class ID. </summary>
	const GUID GenericFileTransferServiceClass_UUID = { 0x00001202, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Generic audio service class ID. </summary>
	const GUID GenericAudioServiceClass_UUID = { 0x00001203, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Generic telephony service class ID. </summary>
	const GUID GenericTelephonyServiceClass_UUID = { 0x00001204, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UPnP service class ID. </summary>
	const GUID UPnpServiceClass_UUID = { 0x00001205, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> UPnP IP service class ID. </summary>
	const GUID UPnpIpServiceClass_UUID = { 0x00001206, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> ESDP UPnP IP PAN service class ID. </summary>
	const GUID ESdpUpnpIpPanServiceClass_UUID = { 0x00001300, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> ESDP UPnP IP LAP service class ID. </summary>
	const GUID ESdpUpnpIpLapServiceClass_UUID = { 0x00001301, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> ESDP UPnP L2CAP service class ID. </summary>
	const GUID ESdpUpnpL2capServiceClass_UUID = { 0x00001302, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Video source service class ID. </summary>
	const GUID VideoSourceServiceClass_UUID = { 0x00001303, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Video sink service class ID. </summary>
	const GUID VideoSinkServiceClass_UUID = { 0x00001304, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> Video distribution service class ID. </summary>
	const GUID VideoDistributionServiceClass_UUID = { 0x00001305, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HDP service class ID. </summary>
	const GUID HDPServiceClass_UUID = { 0x00001400, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HDP source service class ID. </summary>
	const GUID HDPSourceServiceClass_UUID = { 0x00001401, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };
	/// <summary> HDP sink service class ID. </summary>
	const GUID HDPSinkServiceClass_UUID = { 0x00001402, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

	/// <summary> SyncML server service class ID. </summary>
	const GUID SyncMLServerServiceClass_UUID = { 0x00000001, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x02, 0xEE, 0x00, 0x00, 0x02 };
	/// <summary> SyncML client service class ID. </summary>
	const GUID SyncMLClientServiceClass_UUID = { 0x00000002, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x02, 0xEE, 0x00, 0x00, 0x02 };
	/// <summary> Nokia OBEX PCSuite service class ID. </summary>
	const GUID NokiaOBEXPCSuiteServiceClass_UUID = { 0x00005005, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x02, 0xEE, 0x00, 0x00, 0x01 };

	/// <summary> Service discovery server service class short ID. </summary>
	#define ServiceDiscoveryServerServiceClassID_UUID16				0x1000
	/// <summary> Browse group descriptor service class short ID. </summary>
	#define BrowseGroupDescriptorServiceClassID_UUID16				0x1001
	/// <summary> Public browse group service class short ID. </summary>
	#define PublicBrowseGroupServiceClass_UUID16					0x1002
	/// <summary> Serial Port service class short ID. </summary>
	#define SerialPortServiceClass_UUID16							0x1101
	/// <summary> LAN access using PPP service class short ID. </summary>
	#define LANAccessUsingPPPServiceClass_UUID16					0x1102
	/// <summary> Dialup networking service class short ID. </summary>
	#define DialupNetworkingServiceClass_UUID16						0x1103
	/// <summary> IrMC sync service class short ID. </summary>
	#define IrMCSyncServiceClass_UUID16								0x1104
	/// <summary> OBEX object push service class short ID. </summary>
	#define OBEXObjectPushServiceClass_UUID16						0x1105
	/// <summary> OBEX file transfer service class short ID. </summary>
	#define OBEXFileTransferServiceClass_UUID16						0x1106
	/// <summary> IrMC sync command service class short ID. </summary>
	#define IrMCSyncCommandServiceClass_UUID16						0x1107
	/// <summary> Headset service class short ID. </summary>
	#define HeadsetServiceClass_UUID16								0x1108
	/// <summary> Cordless telephony service class short ID. </summary>
	#define CordlessTelephonyServiceClass_UUID16					0x1109
	/// <summary> Audio source service class short ID. </summary>
	#define AudioSourceServiceClass_UUID16							0x110A
	/// <summary> Audio sink service class short ID. </summary>
	#define AudioSinkServiceClass_UUID16							0x110B
	/// <summary> A/V remote control target service class short ID. </summary>
	#define AVRemoteControlTargetServiceClass_UUID16				0x110C
	/// <summary> Advanced audio distribution service class short ID. </summary>
	#define AdvancedAudioDistributionServiceClass_UUID16			0x110D
	/// <summary> A/V remote control service class short ID. </summary>
	#define AVRemoteControlServiceClass_UUID16						0x110E
	/// <summary> Video conferencing service class short ID. </summary>
	#define VideoConferencingServiceClass_UUID16					0x110F
	/// <summary> Intercom service class short ID. </summary>
	#define IntercomServiceClass_UUID16								0x1110
	/// <summary> Fax service class short ID. </summary>
	#define FaxServiceClass_UUID16									0x1111
	/// <summary> Headset audio gateway service class short ID. </summary>
	#define HeadsetAudioGatewayServiceClass_UUID16					0x1112
	/// <summary> WAP service class short ID. </summary>
	#define WAPServiceClass_UUID16									0x1113
	/// <summary> WAP client service class short ID. </summary>
	#define WAPClientServiceClass_UUID16							0x1114
	/// <summary> PANU service class short ID. </summary>
	#define PANUServiceClass_UUID16									0x1115
	/// <summary> NAP service class short ID. </summary>
	#define NAPServiceClass_UUID16									0x1116
	/// <summary> GN service class short ID. </summary>
	#define GNServiceClass_UUID16									0x1117
	/// <summary> Direct printing service class short ID. </summary>
	#define DirectPrintingServiceClass_UUID16						0x1118
	/// <summary> Reference printing service class short ID. </summary>
	#define ReferencePrintingServiceClass_UUID16					0x1119
	/// <summary> Basic imaging service class short ID. </summary>
	#define ImagingServiceClass_UUID16								0x111A
	/// <summary> Imaging responder service class short ID. </summary>
	#define ImagingResponderServiceClass_UUID16						0x111B
	/// <summary> Imaging automatic archive service class short ID. </summary>
	#define ImagingAutomaticArchiveServiceClass_UUID16				0x111C
	/// <summary> Imaging referenced objects service class short ID. </summary>
	#define ImagingReferenceObjectsServiceClass_UUID16				0x111D
	/// <summary> Handsfree service class short ID. </summary>
	#define HandsfreeServiceClass_UUID16							0x111E
	/// <summary> Handsfree audio gateway service class short ID. </summary>
	#define HandsfreeAudioGatewayServiceClass_UUID16				0x111F
	/// <summary> Direct printing reference objects service class short ID. </summary>
	#define DirectPrintingReferenceObjectsServiceClass_UUID16		0x1120
	/// <summary> Reflected UI service class short ID. </summary>
	#define ReflectedUIServiceClass_UUID16							0x1121
	/// <summary> Basic printing service class short ID. </summary>
	#define BasicPrintingServiceClass_UUID16						0x1122
	/// <summary> Printing status service class short ID. </summary>
	#define PrintingStatusServiceClass_UUID16						0x1123
	/// <summary> Human interface device service class short ID. </summary>
	#define HumanInterfaceDeviceServiceClass_UUID16					0x1124
	/// <summary> Hardcopy cable replacement service class short ID. </summary>
	#define HardcopyCableReplacementServiceClass_UUID16				0x1125
	/// <summary> HCR print service class short ID. </summary>
	#define HCRPrintServiceClass_UUID16								0x1126
	/// <summary> HCR scan service class short ID. </summary>
	#define HCRScanServiceClass_UUID16								0x1127
	/// <summary> Common ISDN access service class short ID. </summary>
	#define CommonISDNAccessServiceClass_UUID16						0x1128
	/// <summary> Video conferencing GW service class short ID. </summary>
	#define VideoConferencingGWServiceClass_UUID16					0x1129
	/// <summary> UDIMT service class short ID. </summary>
	#define UDIMTServiceClass_UUID16								0x112A
	/// <summary> UDITA service class short ID. </summary>
	#define UDITAServiceClass_UUID16								0x112B
	/// <summary> Audio/video service class short ID. </summary>
	#define AudioVideoServiceClass_UUID16							0x112C
	/// <summary> SIM access service class short ID. </summary>
	#define SimAccessServiceClass_UUID16							0x112D
	/// <summary> Phonebook access client equipment (PCE) service class short
	///   ID. </summary>
	#define PhonebookClientEquipmentServiceClass_UUID16				0x112E
	/// <summary> Phonebook server equipment (PSE) service class short ID. </summary>
	#define PhonebookServerEquipmentServiceClass_UUID16				0x112F
	/// <summary> Phonebook access service class short ID. </summary>
	#define PhonebookServiceClass_UUID16							0x1130
	/// <summary> Headset HS service class short ID. </summary>
	#define HeadsetHSServiceClass_UUID16							0x1131
	/// <summary> Message access server service class short ID. </summary>
	#define MessageAccessServerServiceClass_UUID16					0x1132
	/// <summary> Message notification server service class short ID. </summary>
	#define MessageNotificationServerServiceClass_UUID16			0x1133
	/// <summary> Message access profile service class short ID. </summary>
	#define MessageAccessProfileServiceClass_UUID16					0x1134
	/// <summary> GNSS profile service class short ID. </summary>
	#define GNSSProfileServiceClass_UUID16							0x1135
	/// <summary> GNSS server service class short ID. </summary>
	#define GNSSServerServiceClass_UUID16							0x1136
	/// <summary> 3D display service class short ID. </summary>
	#define ThreeDDisplayServiceClass_UUID16						0x1137
	/// <summary> 3D glasses service class short ID. </summary>
	#define ThreeDGlassesServiceClass_UUID16						0x1138
	/// <summary> 3D synchronization profile service class short ID. </summary>
	#define ThreeDSynchronizationProfileServiceClass_UUID16			0x1139
	/// <summary> MPS profile service class short ID. </summary>
	#define MPSProfileServiceClass_UUID16							0x113A
	/// <summary> MPSS service class short ID. </summary>
	#define MPSSCServiceClass_UUID16								0x113B
	/// <summary> CTN access service class short ID. </summary>
	#define CTNAccessServiceClass_UUID16							0x113C
	/// <summary> CTN notification service class short ID. </summary>
	#define CTNNotificationServiceClass_UUID16						0x113D
	/// <summary> CTN profile service class short ID. </summary>
	#define CTNProfileServiceClass_UUID16							0x113E
	/// <summary> PnP information service class short ID. </summary>
	#define PnPInformationServiceClass_UUID16						0x1200
	/// <summary> Generic networking service class short ID. </summary>
	#define GenericNetworkingServiceClass_UUID16					0x1201
	/// <summary> Generic file transfer service class short ID. </summary>
	#define GenericFileTransferServiceClass_UUID16					0x1202
	/// <summary> Generic audio service class short ID. </summary>
	#define GenericAudioServiceClass_UUID16							0x1203
	/// <summary> Generic telephony service class short ID. </summary>
	#define GenericTelephonyServiceClass_UUID16						0x1204
	/// <summary> UPnP service class short ID. </summary>
	#define UPnpServiceClass_UUID16									0x1205
	/// <summary> UPnP IP service class short ID. </summary>
	#define UPnpIpServiceClass_UUID16								0x1206
	/// <summary> ESDP UPnP IP PAN service class short ID. </summary>
	#define ESdpUpnpIpPanServiceClass_UUID16						0x1300
	/// <summary> ESDP UPnP IP LAP service class short ID. </summary>
	#define ESdpUpnpIpLapServiceClass_UUID16						0x1301
	/// <summary> ESDP UPnP L2CAP service class short ID. </summary>
	#define ESdpUpnpL2capServiceClass_UUID16						0x1302
	/// <summary> Video source service class short ID. </summary>
	#define VideoSourceServiceClass_UUID16							0x1303
	/// <summary> Video sink service class short ID. </summary>
	#define VideoSinkServiceClass_UUID16							0x1304
	/// <summary> Video distribution service class short ID. </summary>
	#define VideoDistributionServiceClass_UUID16					0x1305
	/// <summary> HDP service class short ID. </summary>
	#define HDPServiceClass_UUID16									0x1400
	/// <summary> HDP source service class short ID. </summary>
	#define HDPSourceServiceClass_UUID16							0x1401
	/// <summary> HDP sink service class short ID. </summary>
	#define HDPSinkServiceClass_UUID16								0x1402

	/* PSM IDs. */

	/// <summary> SDP PSM ID. </summary>
	#define PSM_SDP					0x0001
	/// <summary> RFCOMM PSM ID. </summary>
	#define PSM_RFCOMM				0x0003
	/// <summary> Telephony control protocol PSM ID. </summary>
	#define PSM_TCS_BIN				0x0005
	/// <summary> TCS cordless PSM ID. </summary>
	#define PSM_TCS_BIN_CORDLESS	0x0007
	/// <summary> BNEP PSM ID. </summary>
	#define PSM_BNEP				0x000F
	/// <summary> HID control channel PSM ID. </summary>
	#define PSM_HID_CONTROL			0x0011
	/// <summary> HID interrupt channel PSM ID. </summary>
	#define PSM_HID_INTERRUPT		0x0013
	/// <summary> UPNP PSM ID. </summary>
	#define PSM_UPNP				0x0015
	/// <summary> AVCTP PSM ID. </summary>
	#define PSM_AVCTP				0x0017
	/// <summary> AVDTP PSM ID. </summary>
	#define PSM_AVDTP				0x0019
	/// <summary> AVCTP browse PSM ID. </summary>
	#define PSM_AVCTP_BROWSE		0x001B
	/// <summary> UDI C plane PSM ID. </summary>
	#define PSM_UDI_C_PLANE			0x001D
	/// <summary> ATT PSM ID. </summary>
	#define PSM_ATT					0x001F
	/// <summary> 3DSP PSM ID. </summary>
	#define PSM_3DSP				0x0021
	/// <summary> LE IPSP PSM ID. </summary>
	#define PSM_LE_IPSP				0x0023
	/// <summary> Object Transfer Service PSM ID. </summary>
	#define PSM_OTS					0x0025
	/// <summary> EATT PSM ID. </summary>
	#define PSM_EATT				0x0027

	/* GATT Services UUIDs. */

	/// <summary> Base Bluetooth LE UUID. </summary>
	const GUID LE_ATT_BLUETOOTH_BASE_GUID = { 0x00000000, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

	/// <summary> Generic Access service ID. </summary>
	#define GATT_SERVICE_GAP								0x1800
	/// <summary> Generic Attribute service ID. </summary>
	#define GATT_SERVICE_GATT								0x1801
	/// <summary> Immediate Alert service ID. </summary>
	#define GATT_SERVICE_IMMEDIATE_ALERT					0x1802
	/// <summary> Link Loss service ID. </summary>
	#define GATT_SERVICE_LINK_LOSS							0x1803
	/// <summary> Tx Power service ID. </summary>
	#define GATT_SERVICE_TX_POWER							0x1804
	/// <summary> Current Time service ID. </summary>
	#define GATT_SERVICE_CURRENT_TIME						0x1805
	/// <summary> Reference Time Update service ID. </summary>
	#define GATT_SERVICE_REFERENCE_TIME_UPDATE				0x1806
	/// <summary> Next DST Change service ID. </summary>
	#define GATT_SERVICE_NEXT_SDT_CHANGE					0x1807
	/// <summary> Glucose service ID. </summary>
	#define GATT_SERVICE_GLUCOSE							0x1808
	/// <summary> Health Thermometer service ID. </summary>
	#define GATT_SERVICE_HEALTH_THERMOMETER					0x1809
	/// <summary> Device Information service ID. </summary>
	#define GATT_SERVICE_DEVICE_INFORMATION					0x180A
	/// <summary> Heart Rate service ID. </summary>
	#define GATT_SERVICE_HEART_RATE							0x180D
	/// <summary> Phone Alert Status service ID. </summary>
	#define GATT_SERVICE_PHONE_ALERT_STATUS					0x180E
	/// <summary> Battery service ID. </summary>
	#define GATT_SERVICE_BATTERY							0x180F
	/// <summary> Blood Pressure service ID. </summary>
	#define GATT_SERVICE_BLOOD_PRESSURE						0x1810
	/// <summary> Alert Notification service ID. </summary>
	#define GATT_SERVICE_ALERT_NOTIFICATION					0x1811
	/// <summary> Human Interface Device service ID. </summary>
	#define GATT_SERVICE_HID								0x1812
	/// <summary> Scan Parameters service ID. </summary>
	#define GATT_SERVICE_SCAN_PARAMETERS					0x1813
	/// <summary> Running Speed and Cadence service ID. </summary>
	#define GATT_SERVICE_RUNNING_SPEED_AND_CADENCE			0x1814
	/// <summary> Automation IO service ID. </summary>
	#define GATT_SERVICE_AUTOMATION_IO						0x1815
	/// <summary> Cycling Speed and Cadence service ID. </summary>
	#define GATT_SERVICE_CYCLING_SPEED_AND_CADENCE			0x1816
	/// <summary> Cycling Power service ID. </summary>
	#define GATT_SERVICE_CYCLING_POWER						0x1818
	/// <summary> Location and Navigation service ID. </summary>
	#define GATT_SERVICE_LOCATION_AND_NAVIGATION			0x1819
	/// <summary> Environmental Sensing service ID. </summary>
	#define GATT_SERVICE_ENVIRONMENTAL_SENSING				0x181A
	/// <summary> Body Composition service ID. </summary>
	#define GATT_SERVICE_BODY_COMPOSITION					0x181B
	/// <summary> User Data service ID. </summary>
	#define GATT_SERVICE_USER_DATA							0x181C
	/// <summary> Weight Scale service ID. </summary>
	#define GATT_SERVICE_WEIGHT_SCALE						0x181D
	/// <summary> Bond Management service ID. </summary>
	#define GATT_SERVICE_BOND_MANAGEMENT					0x181E
	/// <summary> Continuous Glucose Monitoring service ID. </summary>
	#define GATT_SERVICE_CONTINUOUS_GLUCOSE_MONITORING		0x181F
	/// <summary> Internet Protocol Support service ID. </summary>
	#define GATT_SERVICE_INTERNET_PROTOCOL_SUPPORT			0x1820
	/// <summary> Indoor Positioning service ID. </summary>
	#define GATT_SERVICE_INDOOR_POSITIONING					0x1821
	/// <summary> Pulse Oximeter service ID. </summary>
	#define GATT_SERVICE_PULSE_OXIMETER						0x1822
	/// <summary> HTTP Proxy service ID. </summary>
	#define GATT_SERVICE_HTTP_PROXY							0x1823
	/// <summary> Transport Discovery service ID. </summary>
	#define GATT_SERVICE_TRANSPORT_DISCOVERY				0x1824
	/// <summary> Object Transfer service ID. </summary>
	#define GATT_SERVICE_OBJECT_TRANSFER					0x1825
	/// <summary> Fitness Machine service ID. </summary>
	#define GATT_SERVICE_FITNESS_MACHINE					0x1826
	/// <summary> Mesh Provisioning service ID. </summary>
	#define GATT_SERVICE_MESH_PROVISIONING					0x1827
	/// <summary> Mesh Proxy service ID. </summary>
	#define GATT_SERVICE_MESH_PROXY							0x1828
	/// <summary> Reconnection Configuration service ID. </summary>
	#define GATT_SERVICE_RECONNECTION_CONFIGURATION			0x1829
	/// <summary> Insulin Delivery service ID. </summary>
	#define GATT_SERVICE_INSULIN_DELIVERY					0x183A
	/// <summary> Binary Sensor service ID. </summary>
	#define GATT_SERVICE_BINARY_SENSOR						0x183B
	/// <summary> Emergency Configuration service ID. </summary>
	#define GATT_SERVICE_EMERGENCY_CONFIGURATION			0x183C
	/// <summary> Authorization Control service ID. </summary>
	#define GATT_SERVICE_AUTHORIZATION_CONTROL				0x183D
	/// <summary> Physical Activity Monitor service ID. </summary>
	#define GATT_SERVICE_PHYSICAL_ACTIVITY_MONITOR			0x183E
	/// <summary> Elapsed Time service ID. </summary>
	#define GATT_SERVICE_ELAPSED_TIME						0x183F
	/// <summary> Generic Health Sensor service ID. </summary>
	#define GATT_SERVICE_GENERIC_HEALTH_SENSOR				0x1840
	/// <summary> Audio Input Control service ID. </summary>
	#define GATT_SERVICE_AUDIO_INPUT_CONTROL				0x1843
	/// <summary> Volume Control service ID. </summary>
	#define GATT_SERVICE_VOLUME_CONTROL						0x1844
	/// <summary> Volume Offset Control service ID. </summary>
	#define GATT_SERVICE_VOLUME_OFFSET_CONTROL				0x1845
	/// <summary> Coordinated Set Identification service ID. </summary>
	#define GATT_SERVICE_COORDINATED_SET_IDENTIFICATION		0x1846
	/// <summary> Device Time service ID. </summary>
	#define GATT_SERVICE_DEVICE_TIME						0x1847
	/// <summary> Media Control service ID. </summary>
	#define GATT_SERVICE_MEDIA_CONTROL						0x1848
	/// <summary> Generic Media Control service ID. </summary>
	#define GATT_SERVICE_GENERIC_MEDIA_CONTROL				0x1849
	/// <summary> Constant Tone Extension service ID. </summary>
	#define GATT_SERVICE_CONSTANT_TONE_EXTENSION			0x184A
	/// <summary> Telephone Bearer service ID. </summary>
	#define GATT_SERVICE_TELEPHONE_BEARER					0x184B
	/// <summary> Generic Telephone Bearer service ID. </summary>
	#define GATT_SERVICE_GENERIC_TELEPHONE_BEARER			0x184C
	/// <summary> Microphone Control service ID. </summary>
	#define GATT_SERVICE_MICROPHONE_CONTROL					0x184D
	/// <summary> Audio Stream Control service ID. </summary>
	#define GATT_SERVICE_AUDIO_STREAM_CONTROL				0x184E
	/// <summary> Broadcast Audio Scan service ID. </summary>
	#define GATT_SERVICE_BROADCAST_AUDIO_SCAN				0x184F
	/// <summary> Published Audio Capabilities service ID. </summary>
	#define GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES		0x1850
	/// <summary> Basic Audio Announcement service ID. </summary>
	#define GATT_SERVICE_BASIC_AUDIO_ANNOUNCEMENT			0x1851
	/// <summary> Broadcast Audio Announcement service ID. </summary>
	#define GATT_SERVICE_BROADCAST_AUDIO_ANNOUNCEMENT		0x1852
	/// <summary> Common Audio service ID. </summary>
	#define GATT_SERVICE_COMMON_AUDIO						0x1853
	/// <summary> Hearing Access service ID. </summary>
	#define GATT_SERVICE_HEARING_ACCESS						0x1854
	/// <summary> Telephony and Media Audio service ID. </summary>
	#define GATT_SERVICE_TELEPHONY_AND_MEDIA_AUDIO			0x1855
	/// <summary> Public Broadcast Announcement service ID. </summary>
	#define GATT_SERVICE_PUBLIC_BROADCAST_ANNOUNCEMENT		0x1856
	/// <summary> Electronic Shelf Label service ID. </summary>
	#define GATT_SERVICE_ELECTRONIC_SHELF_LABEL				0x1857
	/// <summary> Gaming Audio service ID. </summary>
	#define GATT_SERVICE_GAMING_AUDIO						0x1858
	/// <summary> Mesh Proxy Solicitation service ID. </summary>
	#define GATT_SERVICE_MESH_PROXY_SOLICITATION			0x1859

	/* GATT attribute types. */

	/// <summary> Primary service attribute type ID. </summary>
	#define GATT_ATTRIBUTE_TYPE_PRIMARY_SERVICE		0x2800
	/// <summary> Secondary service attribute type ID. </summary>
	#define GATT_ATTRIBUTE_TYPE_SECONDARY_SERVICE	0x2801
	/// <summary> Included service attribute type ID. </summary>
	#define GATT_ATTRIBUTE_TYPE_INCLUDE				0x2802
	/// <summary> Characteristic attribute type ID. </summary>
	#define GATT_ATTRIBUTE_TYPE_CHARACTERISTIC		0x2803

	/* GATT Descriptors. */

	/// <summary> Characteristic extended properties descriptor ID. </summary>
	#define GATT_DESCRIPTOR_CHARACTERISTIC_EXTENDED_PROPERTIES		0x2900
	/// <summary> Characteristic user description descriptor ID. </summary>
	#define GATT_DESCRIPTOR_CHARACTERISTIC_USER_DESCRIPTION			0x2901
	/// <summary> Client characteristic configuration descriptor ID. </summary>
	#define GATT_DESCRIPTOR_CLIENT_CHARACTERISTIC_CONFIGURATION		0x2902
	/// <summary> Server characteristic configuration descriptor ID. </summary>
	#define GATT_DESCRIPTOR_SERVER_CHARACTERISTIC_CONFIGURATION		0x2903
	/// <summary> Characteristic presentation format descriptor ID. </summary>
	#define GATT_DESCRIPTOR_CHARACTERISTIC_PRESENTATION_FORMAT		0x2904
	/// <summary> Characteristic aggregate format descriptor ID. </summary>
	#define GATT_DESCRIPTOR_CHARACTERISTIC_AGGREGATE_FORMAT			0x2905
	/// <summary> Valid range descriptor ID. </summary>
	#define GATT_DESCRIPTOR_VALID_RANGE								0x2906
	/// <summary> External report reference descriptor ID. </summary>
	#define GATT_DESCRIPTOR_EXTERNAL_REPORT_REFERENCE				0x2907
	/// <summary> Report reference descriptor ID. </summary>
	#define GATT_DESCRIPTOR_REPORT_REFERENCE						0x2908
	/// <summary> Number of digitals descriptor ID. </summary>
	#define GATT_DESCRIPTOR_NUMBER_OF_DIGITALS						0x2909
	/// <summary> Value trigger setting descriptor ID. </summary>
	#define GATT_DESCRIPTOR_VALUE_TRIGGER_SETTING					0x290A
	/// <summary> Environmental sensing configuration descriptor ID. </summary>
	#define GATT_DESCRIPTOR_ENVIRONMENTAL_SENSING_CONFIGURATION		0x290B
	/// <summary> Environmental sensing measurement descriptor ID. </summary>
	#define GATT_DESCRIPTOR_ENVIRONMENTAL_SENSING_MEASUREMENT		0x290C
	/// <summary> Environmental sensing trigger setting descriptor ID. </summary>
	#define GATT_DESCRIPTOR_ENVIRONMENTAL_SENSING_TRIGGER_SETTING	0x290D
	/// <summary> Time trigger setting descriptor ID. </summary>
	#define GATT_DESCRIPTOR_TIME_TRIGGER_SETTING					0x290E
	/// <summary> Complete BR-EDR transport block data descriptor ID. </summary>
	#define GATT_DESCRIPTOR_COLPLETE_BR_EDR_TRANSPORT_BLOCK_DATA	0x290F
	/// <summary> Observation schedule descriptor ID. </summary>
	#define GATT_DESCRIPTOR_OBSERVATION_SCHEDULE					0x2910
	/// <summary> Valid range and accuracy descriptor ID. </summary>
	#define GATT_DESCRIPTOR_VALID_RANGE_AND_ACCURACY				0x2911

	/* GATT Characteristics. */

	/// <summary> Device name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_NAME													0x2A00
	/// <summary> Appearance characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_APPEARANCE													0x2A01
	/// <summary> Peripheral privacy flag characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PERIPHERAL_PRIVACY_FLAG										0x2A02
	/// <summary> Reconnection address characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RECONNECTION_ADDRESS										0x2A03
	/// <summary> Peripheral preferred connection parameters characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS					0x2A04
	/// <summary> Service changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SERVICE_CHANGED												0x2A05
	/// <summary> Alert level characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALERT_LEVEL													0x2A06
	/// <summary> TX power level characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TX_POWER_LEVEL												0x2A07
	/// <summary> Date/time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATE_TIME													0x2A08
	/// <summary> Day of week characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DAY_OF_WEEK													0x2A09
	/// <summary> Day date/time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DAY_DATE_TIME												0x2A0A
	/// <summary> Exact time 256 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_EXACT_TIME_256												0x2A0C
	/// <summary> DST offset characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DST_OFFSET													0x2A0D
	/// <summary> Time zone characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_ZONE													0x2A0E
	/// <summary> Local time information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LOCAL_TIME_INFORMATION										0x2A0F
	/// <summary> Time with DST characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_WITH_DST												0x2A11
	/// <summary> Time accuracy characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_ACCURACY												0x2A12
	/// <summary> Time source characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_SOURCE													0x2A13
	/// <summary> Reference time information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_REFERENCE_TIME_INFORMATION									0x2A14
	/// <summary> Time update control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_UPDATE_CONTROL_POINT									0x2A16
	/// <summary> Time update state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_UPDATE_STATE											0x2A17
	/// <summary> Glucose measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GLUCOSE_MEASUREMENT											0x2A18
	/// <summary> Battery level characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_LEVEL												0x2A19
	/// <summary> Temperature measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_MEASUREMENT										0x2A1C
	/// <summary> Temperature type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_TYPE											0x2A1D
	/// <summary> Intermediate temperature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INTERMEDIATE_TEMPERATURE									0x2A1E
	/// <summary> Measurement interval characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEASUREMENT_INTERVAL										0x2A21
	/// <summary> Boot keyboard input report characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT									0x2A22
	/// <summary> System ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SYSTEM_ID													0x2A23
	/// <summary> Model number string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MODEL_NUMBER_STRING											0x2A24
	/// <summary> Serial number string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SERIAL_NUMBER_STRING										0x2A25
	/// <summary> Firmware revision string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIRMWARE_REVISION_STRING									0x2A26
	/// <summary> Hardware revision string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HARDWARE_REVISION_STRING									0x2A27
	/// <summary> Software revision string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SOFTWARE_REVISION_STRING									0x2A28
	/// <summary> Manufacturer name string characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MANUFACTURER_NAME_STRING									0x2A29
	/// <summary> IEEE 11073-20601 regulatory certification data list characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IEEE_CERTIFICATION_DATA_LIST								0x2A2A
	/// <summary> Current time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CURRENT_TIME												0x2A2B
	/// <summary> Magnetic declination characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MAGNETIC_DECLINATION										0x2A2C
	/// <summary> Scan refresh characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SCAN_REFRESH												0x2A31
	/// <summary> Boot keyboard output report characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT									0x2A32
	/// <summary> Boot mouse input report characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT										0x2A33
	/// <summary> Glucose measurement context characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GLUCOSE_MEASUREMENT_CONTEXT									0x2A34
	/// <summary> Blood pressure measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BLOOD_PRESSURE_MEASUREMENT									0x2A35
	/// <summary> Intermediate cuff pressure characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INTERMEDIATE_CUFF_PRESSURE									0x2A36
	/// <summary> Heart rate measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEART_RATE_MEASUREMENT										0x2A37
	/// <summary> Body sensor location characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BODY_SENSOR_LOCATION										0x2A38
	/// <summary> Heart rate control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEART_RATE_CONTROL_POINT									0x2A39
	/// <summary> Alert status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALERT_STATUS												0x2A3F
	/// <summary> Ringer control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RINGER_CONTROL_POINT										0x2A40
	/// <summary> Ringer setting characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RINGER_SETTING												0x2A41
	/// <summary> Alert category ID bit mask characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALERT_CATEGORY_ID_BIT_MASK									0x2A42
	/// <summary> Alert category ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALERT_CATEGORY_ID											0x2A43
	/// <summary> Alert notification control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT							0x2A44
	/// <summary> Unread alert status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UNREAD_ALERT_STATUS											0x2A45
	/// <summary> New alert characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NEW_ALERT													0x2A46
	/// <summary> Supported new alert category characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY								0x2A47
	/// <summary> Supported unread alert category characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY								0x2A48
	/// <summary> Blood pressure feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BLOOD_PRESSURE_FEATURE										0x2A49
	/// <summary> HID information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HID_INFORMATION												0x2A4A
	/// <summary> Report map characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_REPORT_MAP													0x2A4B
	/// <summary> HID control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HID_CONTROL_POINT											0x2A4C
	/// <summary> Report characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_REPORT														0x2A4D
	/// <summary> Protocol mode characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PROTOCOL_MODE												0x2A4E
	/// <summary> Scan interval window characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SCAN_INTERVAL_WINDOW										0x2A4F
	/// <summary> PnP ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PNP_ID														0x2A50
	/// <summary> Glucose feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GLUCOSE_FEATURE												0x2A51
	/// <summary> Record access control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT									0x2A52
	/// <summary> RSC measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RSC_MEASUREMENT												0x2A53
	/// <summary> RSC feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RSC_FEATURE													0x2A54
	/// <summary> SC control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SC_CONTROL_POINT											0x2A55
	/// <summary> Aggregate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AGGREGATE													0x2A5A
	/// <summary> CSC measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CSC_MEASUREMENT												0x2A5B
	/// <summary> CSC feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CSC_FEATURE													0x2A5C
	/// <summary> Sensor location characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SENSOR_LOCATION												0x2A5D
	/// <summary> PLX spot-check measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLX_SPOT_CHECK_MEASUREMENT									0x2A5E
	/// <summary> PLX continuous measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLX_CONTINUOUS_MEASUREMENT									0x2A5F
	/// <summary> PLX features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLX_FEATURES												0x2A60
	/// <summary> Cycling power measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CYCLING_POWER_MEASUREMENT									0x2A63
	/// <summary> Cycling power vector characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CYCLING_POWER_VECTOR										0x2A64
	/// <summary> Cycling power feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CYCLING_POWER_FEATURE										0x2A65
	/// <summary> Cycling power control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CYCLING_POWER_CONTROL_POINT									0x2A66
	/// <summary> Location and speed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LOCATION_AND_SPEED											0x2A67
	/// <summary> Navigation characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NAVIGATION													0x2A68
	/// <summary> Position quality characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_POSITION_QUALITY											0x2A69
	/// <summary> LN feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LN_FEATURE													0x2A6A
	/// <summary> LN control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LN_CONTROL_POINT											0x2A6B
	/// <summary> Elevation characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ELEVATION													0x2A6C
	/// <summary> Pressure characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PRESSURE													0x2A6D
	/// <summary> Temperature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE													0x2A6E
	/// <summary> Humidity characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HUMIDITY													0x2A6F
	/// <summary> True wind speed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRUE_WIND_SPEED												0x2A70
	/// <summary> True wind direction characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRUE_WIND_DIRECTION											0x2A71
	/// <summary> Apparent wind speed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_APPARENT_WIND_SPEED											0x2A72
	/// <summary> Apparent wind direction characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_APPARENT_WIND_DIRECTION										0x2A73
	/// <summary> Gust factor characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GUST_FACTOR													0x2A74
	/// <summary> Pollen concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_POLLEN_CONCENTRATION										0x2A75
	/// <summary> UV index characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UV_INDEX													0x2A76
	/// <summary> Irradiance characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IRRADIANCE													0x2A77
	/// <summary> Rainfall characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RAINFALL													0x2A78
	/// <summary> Wind chill characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_WIND_CHILL													0x2A79
	/// <summary> Heat index characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEAT_INDEX													0x2A7A
	/// <summary> Dew point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEW_POINT													0x2A7B
	/// <summary> Descriptor value changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DESCRIPTOR_VALUE_CHANGED									0x2A7D
	/// <summary> Aerobic heart rate lower limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AEROBIC_HEART_RATE_LOWER_LIMIT								0x2A7E
	/// <summary> Aerobic threshold characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AEROBIC_TRESHOLD											0x2A7F
	/// <summary> Age characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AGE															0x2A80
	/// <summary> Anaerobic heart rate lower limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ANAEROBIC_HEART_RATE_LOWER_LIMIT							0x2A81
	/// <summary> Anaerobic heart rate upper limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ANAEROBIC_HEART_RATE_UPPER_LIMIT							0x2A82
	/// <summary> Anaerobic threshold characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ANAEROBIC_TRESHOLD											0x2A83
	/// <summary> Aerobic heart rate upper limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AEROBIC_HEART_RATE_UPPER_LIMIT								0x2A84
	/// <summary> Date of birth characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATE_OF_BIRTH												0x2A85
	/// <summary> Date of threshold assessment characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATE_OF_TRESHOLD_ASSESSMENT									0x2A86
	/// <summary> Email address characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_EMAIL_ADDRESS												0x2A87
	/// <summary> Fat burn heart rate lower limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FAT_BURN_HEART_RATE_LOWER_LIMIT								0x2A88
	/// <summary> Fat burn heart rate upper limit characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FAT_BURN_HEART_RATE_UPPER_LIMIT								0x2A89
	/// <summary> First name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIRST_NAME													0x2A8A
	/// <summary> Five zone heart rate limits characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIVE_ZONE_HEART_RATE_LIMITS									0x2A8B
	/// <summary> Gender characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GENDER														0x2A8C
	/// <summary> Heart rate max characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEART_RATE_MAX												0x2A8D
	/// <summary> Height characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEIGHT														0x2A8E
	/// <summary> Hip circumference characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HIP_CIRCUMFERENCE											0x2A8F
	/// <summary> Last name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LAST_NAME													0x2A90
	/// <summary> Maximum recommended heart rate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MAXIMUM_RECOMMENDED_HEART_RATE								0x2A91
	/// <summary> Resting heart rate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RESTING_HEART_RATE											0x2A92
	/// <summary> Sport type for aerobic and anaerobic thresholds characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SPORT_TYPE_FOR_AEROBIC_AND_ANAEROBIC_THRESHOLDS				0x2A93
	/// <summary> Three zone heart rate limits characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_THREE_ZONE_HEART_RATE_LIMITS								0x2A94
	/// <summary> Two zone heart rate limits characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TWO_ZONE_HEART_RATE_LIMITS									0x2A95
	/// <summary> VO2 max characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VO2_MAX														0x2A96
	/// <summary> Waist circumference characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_WAIST_CIRCUMFERENCE											0x2A97
	/// <summary> Weight characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_WEIGHT														0x2A98
	/// <summary> Database change increment characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATABASE_CHANGE_INCREMENT									0x2A99
	/// <summary> User index characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_USER_INDEX													0x2A9A
	/// <summary> Body composition feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BODY_COMPOSITION_FEATURE									0x2A9B
	/// <summary> Body composition measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BODY_COMPOSITION_MEASUREMENT								0x2A9C
	/// <summary> Weight measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_WEIGHT_MEASUREMENT											0x2A9D
	/// <summary> Weight scale feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_WEIGHT_SCALE_FEATURE										0x2A9E
	/// <summary> User control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_USER_CONTROL_POINT											0x2A9F
	/// <summary> Magnetic flux density - 2D characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MAGINETIC_FLUX_DENSITY_2D									0x2AA0
	/// <summary> Magnetic flux density - 3D characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MAGINETIC_FLUX_DENSITY_3D									0x2AA1
	/// <summary> Language characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LANGUAGE													0x2AA2
	/// <summary> Barometric pressure trend characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BAROMETRIC_PRESSURE_TREND									0x2AA3
	/// <summary> Bond management control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOND_MANAGEMENT_CONTROL_POINT								0x2AA4
	/// <summary> Bond management feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOND_MANAGEMENT_FEATURE										0x2AA5
	/// <summary> Central address resolution characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION									0x2AA6
	/// <summary> CGM measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_MEASUREMENT												0x2AA7
	/// <summary> CGM feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_FEATURE													0x2AA8
	/// <summary> CGM status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_STATUS													0x2AA9
	/// <summary> CGM session start time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_SESSION_START_TIME										0x2AAA
	/// <summary> CGM session run time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_SESSION_RUN_TIME										0x2AAB
	/// <summary> CGM specific ops control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CGM_SPECIFIC_OPS_CONTROL_POINT								0x2AAC
	/// <summary> Indoor positioning configuration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INDOOR_POSITIONING_CONFIGURATION							0x2AAD
	/// <summary> Latitude characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LATITUDE													0x2AAE
	/// <summary> Longitude characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LONGITUDE													0x2AAF
	/// <summary> Local north coordinate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LOCAL_NORTH_COORDINATE										0x2AB0
	/// <summary> Local east coordinate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LOCAL_EAST_COORDINATE										0x2AB1
	/// <summary> Floor number characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FLOOR_NUMBER												0x2AB2
	/// <summary> Altitude characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ALTITUDE													0x2AB3
	/// <summary> Uncertainty characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UNCERTAINTY													0x2AB4
	/// <summary> Location name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LOCATION_NAME												0x2AB5
	/// <summary> URI characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_URI															0x2AB6
	/// <summary> HTTP headers characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HTTP_HEADERS												0x2AB7
	/// <summary> HTTP status code characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HTTP_STATUS_CODE											0x2AB8
	/// <summary> HTTP entity body characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HTTP_ENTITY_BODY											0x2AB9
	/// <summary> HTTP control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HTTP_CONTROL_POINT											0x2ABA
	/// <summary> HTTPS security characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HTTPS_SECURITY												0x2ABB
	/// <summary> TDS control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TDS_CONTROL_POINT											0x2ABC
	/// <summary> OTS feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OTS_FEATURE													0x2ABD
	/// <summary> Object name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_NAME													0x2ABE
	/// <summary> Object type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_TYPE													0x2ABF
	/// <summary> Object size characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_SIZE													0x2AC0
	/// <summary> Object first-created characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_FIRST_CREATED										0x2AC1
	/// <summary> Object last-modified characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_LEAST_MODIFIED										0x2AC2
	/// <summary> Object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_ID													0x2AC3
	/// <summary> Object properties characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_PROPERTIES											0x2AC4
	/// <summary> Object action control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_ACTION_CONTROL_POINT									0x2AC5
	/// <summary> Object list control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_LIST_CONTROL_POINT									0x2AC6
	/// <summary> Object list filter characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_LIST_FILTER											0x2AC7
	/// <summary> Object changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBJECT_CHANGED												0x2AC8
	/// <summary> Resolvable private address only characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY								0x2AC9
	/// <summary> Fitness machine feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FITNESS_MACHINE_FEATURE										0x2ACC
	/// <summary> Treadmill data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TREADMILL_DATA												0x2ACD
	/// <summary> Cross trainer data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CROSS_TRAINER_DATA											0x2ACE
	/// <summary> Step climber data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STEP_CLIMBER_DATA											0x2ACF
	/// <summary> Stair climber data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STAIR_CLIMBER_DATA											0x2AD0
	/// <summary> Rower data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ROWER_DATA													0x2AD1
	/// <summary> Indoor bike data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INDOOR_BIKE_DATA											0x2AD2
	/// <summary> Training status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRAINING_STATUS												0x2AD3
	/// <summary> Supported speed range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_SPEED_RANGE										0x2AD4
	/// <summary> Supported inclination range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_INCLINATION_RANGE									0x2AD5
	/// <summary> Supported resistance level range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_RESISTANCE_LEVEL_RANGE							0x2AD6
	/// <summary> Supported heart rate range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_HEART_RATE_RANGE									0x2AD7
	/// <summary> Supported power range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_POWER_RANGE										0x2AD8
	/// <summary> Fitness machine control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FITNESS_MACHINE_CONTROL_POINT								0x2AD9
	/// <summary> Fitness machine status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FITNESS_MACHINE_STATUS										0x2ADA
	/// <summary> Mesh provisioning data in characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN									0x2ADB
	/// <summary> Mesh provisioning data out characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT									0x2ADC
	/// <summary> Mesh proxy data in characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MESH_PROXY_DATA_IN											0x2ADD
	/// <summary> Mesh proxy data out characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MESH_PROXY_DATA_OUT											0x2ADE
	/// <summary> Average current characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AVERAGE_CURRENT												0x2AE0
	/// <summary> Average voltage characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AVERAGE_VOLTAGE												0x2AE1
	/// <summary> Boolean characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BOOLEAN														0x2AE2
	/// <summary> Chromatic distance from planckian characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CHROMATIC_DISTANCE_FROM_PLANCKIAN							0x2AE3
	/// <summary> Chromaticity coordinates characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CHROMATICITY_COORDINATES									0x2AE4
	/// <summary> Chromaticity in CCT and duv values characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CHROMATICITY_IN_CCT_AND_DUV_VALUES							0x2AE5
	/// <summary> Chromaticity tolerance characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CHROMATICITY_TOLERANCE										0x2AE6
	/// <summary> CIE 13.3-1995 color rendering index characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CIE_COLOR_RENDERING_INDEX									0x2AE7
	/// <summary> Coefficient characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COEFFICIENT													0x2AE8
	/// <summary> Correlated color temperature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CORRELATED_COLOR_TEMPERATURE								0x2AE9
	/// <summary> Count 16 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COUNT_16													0x2AEA
	/// <summary> Count 24 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COUNT_24													0x2AEB
	/// <summary> Country code characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COUNTRY_CODE												0x2AEC
	/// <summary> Date UTC characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATE_UTC													0x2AED
	/// <summary> Electric current characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ELECTRIC_CURRENT											0x2AEE
	/// <summary> Electric current range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ELECTRIC_CURRENT_RANGE										0x2AEF
	/// <summary> Electric current specification characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ELECTRIC_CURRENT_SPECIFICATION								0x2AF0
	/// <summary> Electric current statistics characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ELECTRIC_CURRENT_STATISTICS									0x2AF1
	/// <summary> Energy characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENERGY														0x2AF2
	/// <summary> Energy in a period of day characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENERGY_IN_PERIOD_OF_DAY										0x2AF3
	/// <summary> Event statistics characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_EVENT_STATISTICS											0x2AF4
	/// <summary> Fixed string 16 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIXED_STRING_16												0x2AF5
	/// <summary> Fixed string 24 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIXED_STRING_24												0x2AF6
	/// <summary> Fixed string 36 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIXED_STRING_36												0x2AF7
	/// <summary> Fixed string 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIXED_STRING_8												0x2AF8
	/// <summary> Generic level characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GENERIC_LEVEL												0x2AF9
	/// <summary> Global trade item number characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GLOBAL_TRADE_ITEM_NUMBER									0x2AFA
	/// <summary> Illuminance characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ILLUMINANCE													0x2AFB
	/// <summary> Luminous efficacy characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_EFFICACY											0x2AFC
	/// <summary> Luminous energy characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_ENERGY												0x2AFD
	/// <summary> Luminous exposure characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_EXPOSURE											0x2AFE
	/// <summary> Luminous flux characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_FLUX												0x2AFF
	/// <summary> Luminous flux range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_FLUX_RANGE											0x2B00
	/// <summary> Luminous intensity characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LUMINOUS_INTENSITY											0x2B01
	/// <summary> Mass flow characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MASS_FLOW													0x2B02
	/// <summary> Perceived lightness characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PERCEIVED_LIGHTNESS											0x2B03
	/// <summary> Percentage 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PERCENTAGE_8												0x2B04
	/// <summary> Power characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_POWER														0x2B05
	/// <summary> Power specification characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_POWER_SPECIFICATION											0x2B06
	/// <summary> Relative runtime in a current range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_RUNTIME_IN_CURRENT_RANGE							0x2B07
	/// <summary> Relative runtime in a generic level range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_RUNTIME_IN_GENERIC_LEVEL_RANGE						0x2B08
	/// <summary> Relative value in a voltage range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_VALUE_IN_VOLTAGE_RANGE								0x2B09
	/// <summary> Relative value in an illuminance range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_VALUE_IN_ILLUMINANCE_RANGE							0x2B0A
	/// <summary> Relative value in a period of day characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_VALUE_IN_PERIOD_OF_DAY								0x2B0B
	/// <summary> Relative value in a temperature range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_VALUE_IN_TEMPERATURE_RANGE							0x2B0C
	/// <summary> Temperature 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_8												0x2B0D
	/// <summary> Temperature 8 in a period of day characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_8_IN_PERIOD_OF_DAY								0x2B0E
	/// <summary> Temperature 8 statistics characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_8_STATISTICS									0x2B0F
	/// <summary> Temperature range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_RANGE											0x2B10
	/// <summary> Temperature statistics characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TEMPERATURE_STATISTICS										0x2B11
	/// <summary> Time decihour 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_DECIHOUR_8												0x2B12
	/// <summary> Time exponential 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_EXPONENTIAL_8											0x2B13
	/// <summary> Time hour 24 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_HOUR_24												0x2B14
	/// <summary> Time millisecond 24 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_MILLISECOND_24											0x2B15
	/// <summary> Time second 16 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_SECOND_16												0x2B16
	/// <summary> Time second 8 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_SECOND_8												0x2B17
	/// <summary> Voltage characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLTAGE														0x2B18
	/// <summary> Voltage specification characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLTAGE_SPECIFICATION										0x2B19
	/// <summary> Voltage statistics characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLTAGE_STATISTICS											0x2B1A
	/// <summary> Volume flow characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_FLOW													0x2B1B
	/// <summary> Chromaticity coordinate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CHROMATICITY_COORDINATE										0x2B1C
	/// <summary> RC feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RC_FEATURE													0x2B1D
	/// <summary> RC settings characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RC_SETTINGS													0x2B1E
	/// <summary> Reconnection configuration control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RECONNECTION_CONFIGURATION_CONTROL_POINT					0x2B1F
	/// <summary> IDD status changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_STATUS_CHANGED											0x2B20
	/// <summary> IDD status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_STATUS													0x2B21
	/// <summary> IDD annunciation status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_ANNUNCIATION_STATUS										0x2B22
	/// <summary> IDD features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_FEATURES												0x2B23
	/// <summary> IDD status reader control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_STATUS_READER_CONTROL_POINT								0x2B24
	/// <summary> IDD command control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_COMMAND_CONTROL_POINT									0x2B25
	/// <summary> IDD command data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_COMMAND_DATA											0x2B26
	/// <summary> IDD record access control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_RECORD_ACCESS_CONTROL_POINT								0x2B27
	/// <summary> IDD history data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_IID_HISTORY_DATA											0x2B28
	/// <summary> Client supported features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURES									0x2B29
	/// <summary> Database hash characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DATABASE_HASH												0x2B2A
	/// <summary> BSS control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BSS_CONTROL_POINT											0x2B2B
	/// <summary> BSS response characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BSS_RESPONSE												0x2B2C
	/// <summary> Emergency ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_EMERGENCY_ID												0x2B2D
	/// <summary> Emergency text characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_EMERGENCY_TEXT												0x2B2E
	/// <summary> ACS status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACS_STATUS													0x2B2F
	/// <summary> ACS data in characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACS_DATA_IN													0x2B30
	/// <summary> ACS data out notify characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACS_DATA_OUT_NOTIFY											0x2B31
	/// <summary> ACS data out indicate characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACS_DATA_OUT_INDICATE										0x2B32
	/// <summary> ACS control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACS_CONTROL_POINT											0x2B33
	/// <summary> Enhanced blood pressure measurement characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENHANCED_BLOOD_PRESSURE_MEASUREMENT							0x2B34
	/// <summary> Enhanced intermediate cuff pressure characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENHANCED_INTERMEDIATE_CUFF_PRESSURE							0x2B35
	/// <summary> Blood pressure record characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BLOOD_PRESSURE_RECORD										0x2B36
	/// <summary> Registered user characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_REGISTERED_USER_DATA										0x2B37
	/// <summary> BR-EDR handover data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BR_EDR_HANDOVER_DATA										0x2B38
	/// <summary> Bluetooth SIG data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BLUETOOTH_SIG_DATA											0x2B39
	/// <summary> Server supported features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE									0x2B3A
	/// <summary> Physical activity monitor features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PHYSICAL_ACTIVITY_MONITOR_FEATURES							0x2B3B
	/// <summary> General activity instantaneous data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GENERAL_ACTIVITY_INSTANTANEOUS_DATA							0x2B3C
	/// <summary> General activity summary data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA								0x2B3D
	/// <summary> CardioRespiratory activity instantaneous data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CARDIO_RESPIRATORY_ACTIVITY_INSTANTANEOUS_DATA				0x2B3E
	/// <summary> CardioRespiratory activity summary data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CARDIO_RESPIRATORY_ACTIVITY_SUMMARY_DATA					0x2B3F
	/// <summary> Step counter activity summary data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STEP_COUNTER_ACTIVITY_SUMMARY_DATA							0x2B40
	/// <summary> Sleep activity instantaneous data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SLEEP_ACTIVITY_INSTANTANEOUS_DATA							0x2B41
	/// <summary> Sleep activity summary data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SLEEP_ACTIVITY_SUMMARY_DATA									0x2B42
	/// <summary> Physical activity monitor control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PHYSICAL_ACTIVITY_MONITOR_CONTROL_POINT						0x2B43
	/// <summary> Physical activity current session characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PHYSICAL_ACTIVITY_CURRENT_SESSION							0x2B44
	/// <summary> Physical activity session descriptor characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PHYSICAL_ACTIVITY_SESSION_DESCRIPTOR						0x2B45
	/// <summary> Preferred units characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PREFERRED_UNITS												0x2B46
	/// <summary> High resolution height characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HIGH_RESOLUTION_HEIGHT										0x2B47
	/// <summary> Middle name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MIDDLE_NAME													0x2B48
	/// <summary> Stride length characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STRIDE_LENGTH												0x2B49
	/// <summary> Handedness characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HANDEDNESS													0x2B4A
	/// <summary> Device wearing position characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_WEARING_POSITION										0x2B4B
	/// <summary> Four zone heart rate limits characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FOUR_ZONE_HEART_RATE_LIMITS									0x2B4C
	/// <summary> High intensity exercise threshold characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HIGH_INTENSITY_EXERCISE_THRESHOLD							0x2B4D
	/// <summary> Activity goal characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACTIVITY_GOAL												0x2B4E
	/// <summary> Sedentary interval notification characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SEDENTARY_INTERVAL_NOTIFICATION								0x2B4F
	/// <summary> Caloric intake characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CALORIC_INTAKE												0x2B50
	/// <summary> TMAP role characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TMAP_ROLE													0x2B51
	/// <summary> Audio input state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_INPUT_STATE											0x2B77
	/// <summary> Gain settings attribute characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GAIN_SETTINGS_ATTRIBUTE										0x2B78
	/// <summary> Audio input type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_INPUT_TYPE											0x2B79
	/// <summary> Audio input status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_INPUT_STATUS											0x2B7A
	/// <summary> Audio input control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT									0x2B7B
	/// <summary> Audio input description characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION										0x2B7C
	/// <summary> Volume state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_STATE												0x2B7D
	/// <summary> Volume control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_CONTROL_POINT										0x2B7E
	/// <summary> Volume flags characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_FLAGS												0x2B7F
	/// <summary> Volume offset state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_OFFSET_STATE											0x2B80
	/// <summary> Audio location characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_LOCATION												0x2B81
	/// <summary> Volume offset control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT									0x2B82
	/// <summary> Audio output description characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION									0x2B83
	/// <summary> Set identity resolving key characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY									0x2B84
	/// <summary> Coordinated set size characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COORDINATED_SET_SIZE										0x2B85
	/// <summary> Set member lock characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SET_MEMBER_LOCK												0x2B86
	/// <summary> Set member rank characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SET_MEMBER_RANK												0x2B87
	/// <summary> Encrypted data key material characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL									0x2B88
	/// <summary> Apparent energy 32 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_APPARENT_ENERGY_32											0x2B89
	/// <summary> Apparent power characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_APPARENT_POWER												0x2B8A
	/// <summary> Live health observations characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LIVE_HEALTH_OBSERVATIONS									0x2B8B
	/// <summary> CO concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CO_CONCENTRATION											0x2B8C
	/// <summary> Cosine of the angle characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_COSINE_OF_ANGLE												0x2B8D
	/// <summary> Device time feature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_TIME_FEATURE											0x2B8E
	/// <summary> Device time parameters characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_TIME_PARAMETERS										0x2B8F
	/// <summary> Device time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_TIME													0x2B90
	/// <summary> Device time control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_DEVICE_TIME_CONTROL_POINT									0x2B91
	/// <summary> Time change log data characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_CHANGE_LOG_DATA										0x2B92
	/// <summary> Media player name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_PLAYER_NAME											0x2B93
	/// <summary> Media player icon object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_PLAYER_ICON_OBJECT_ID									0x2B94
	/// <summary> Media player icon URL characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_PLAYER_ICON_URL										0x2B95
	/// <summary> Track changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_CHANGED												0x2B96
	/// <summary> Track title characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_TITLE													0x2B97
	/// <summary> Track duration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_DURATION												0x2B98
	/// <summary> Track position characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_POSITION												0x2B99
	/// <summary> Playback speed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLAYBACK_SPEED												0x2B9A
	/// <summary> Seeking speed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SEEKING_SPEED												0x2B9B
	/// <summary> Current track segments object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CURRENT_TRACK_SEGMENTS_OBJECT_ID							0x2B9C
	/// <summary> Current track object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CURRENT_TRACK_OBJECT_ID										0x2B9D
	/// <summary> Next track object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NEXT_TRACK_OBJECT_ID										0x2B9E
	/// <summary> Parent group object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PARENT_GROUP_OBJECT_ID										0x2B9F
	/// <summary> Current group object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CURRENT_GROUP_OBJECT_ID										0x2BA0
	/// <summary> Playing order characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLAYING_ORDER												0x2BA1
	/// <summary> Playing orders supported characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PLAYING_ORDERS_SUPPORTED									0x2BA2
	/// <summary> Media state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_STATE													0x2BA3
	/// <summary> Media control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_CONTROL_POINT											0x2BA4
	/// <summary> Media control point opcodes supported characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_CONTROL_POINT_OPCODES_SUPPORTED						0x2BA5
	/// <summary> Search results object ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SEARCH_RESULTS_OBJECT_ID									0x2BA6
	/// <summary> Search control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SEARCH_CONTROL_POINT										0x2BA7
	/// <summary> Energy 32 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ENERGY_32													0x2BA8
	/// <summary> Media player icon object type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MEDIA_PLAYER_ICON_OBJECT_TYPE								0x2BA9
	/// <summary> Track segments object type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_SEGMENTS_OBJECT_TYPE									0x2BAA
	/// <summary> Track object type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TRACK_OBJECT_TYPE											0x2BAB
	/// <summary> Group object type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GROUP_OBJECT_TYPE											0x2BAC
	/// <summary> Constant tone extension enable characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CONSTANT_TONE_EXTENSION_ENABLE								0x2BAD
	/// <summary> Advertising constant tone extension minimum length characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ADVERTISING_CONSTANT_TONE_EXTENSION_MINIMUM_LENGTH			0x2BAE
	/// <summary> Advertising constant tone extension minimum transmit count characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ADVERTISING_CONSTANT_TONE_EXTENSION_MINIMUM_TRANSMIT_COUNT	0x2BAF
	/// <summary> Advertising constant tone extension transmit duration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ADVERTISING_CONSTANT_TONE_EXTENSION_TRANSMIT_DURATION		0x2BB0
	/// <summary> Advertising constant tone extension interval characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ADVERTISING_CONSTANT_TONE_EXTENSION_INTERVAL				0x2BB1
	/// <summary> Advertising constant tone extension PHY characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ADVERTISING_CONSTANT_TONE_EXTENSION_PHY						0x2BB2
	/// <summary> Bearer provider name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_PROVIDER_NAME										0x2BB3
	/// <summary> Bearer UCI characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_UCI													0x2BB4
	/// <summary> Bearer technology characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_TECHNOLOGY											0x2BB5
	/// <summary> Bearer URI schemes supported list characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST							0x2BB6
	/// <summary> Bearer signal strength characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_SIGNAL_STRENGTH										0x2BB7
	/// <summary> Bearer signal strength reporting interval characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_SIGNAL_STRENGTH_REPORTING_INTERVAL					0x2BB8
	/// <summary> Bearer list current calls characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS									0x2BB9
	/// <summary> Content control ID characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CONTENT_CONTROL_ID											0x2BBA
	/// <summary> Status flags characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STATUS_FLAGS												0x2BBB
	/// <summary> Incoming call target bearer URI characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INCOMING_CALL_TARGET_BEARER_URI								0x2BBC
	/// <summary> Call state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CALL_STATE													0x2BBD
	/// <summary> Call control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CALL_CONTROL_POINT											0x2BBE
	/// <summary> Call control point optional opcodes characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODES							0x2BBF
	/// <summary> Termination reason characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TERMINATION_REASON											0x2BC0
	/// <summary> Incoming call characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_INCOMING_CALL												0x2BC1
	/// <summary> Call friendly name characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CALL_FRIENDLY_NAME											0x2BC2
	/// <summary> Mute characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_MUTE														0x2BC3
	/// <summary> Sink ASE characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SINK_ASE													0x2BC4
	/// <summary> Source ASE characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SOURCE_ASE													0x2BC5
	/// <summary> ASE control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ASE_CONTROL_POINT											0x2BC6
	/// <summary> Broadcast audio scan control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT							0x2BC7
	/// <summary> Broadcast receive state characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BROADCAST_RECEIVE_STATE										0x2BC8
	/// <summary> Sink PAC characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SINK_PAC													0x2BC9
	/// <summary> Sink audio locations characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SINK_AUDIO_LOCATIONS										0x2BCA
	/// <summary> Source PAC characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SOURCE_PAC													0x2BCB
	/// <summary> Source audio locations characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SOURCE_AUDIO_LOCATIONS										0x2BCC
	/// <summary> Available audio contexts characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS									0x2BCD
	/// <summary> Supported audio contexts characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS									0x2BCE
	/// <summary> Ammonia concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AMMONIA_CONCENTRATION										0x2BCF
	/// <summary> Carbon monoxide concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CARBON_MONOXIDE_CONCENTRATION								0x2BD0
	/// <summary> Methane concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_METHANE_CONCENTRATION										0x2BD1
	/// <summary> Nitrogen dioxide concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NITROGEN_DIOXIDE_CONCENTRATION								0x2BD2
	/// <summary> Non-Methane volatile organic compounds concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NON_METHANE_VOLATILE_ORGANIC_COMPOUNDS_CONCENTRATION		0x2BD3
	/// <summary> Ozone concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OZONE_CONCENTRATION											0x2BD4
	/// <summary> Particulate matter - PM1 concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PARTICULATE_MATTER_PM1_CONCENTRATION						0x2BD5
	/// <summary> Particulate matter - PM2.5 concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PARTICULATE_MATTER_PM25_CONCENTRATION						0x2BD6
	/// <summary> Particulate mMatter - PM10 concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_PARTICULATE_MATTER_PM10_CONCENTRATION						0x2BD7
	/// <summary> Sulfur dioxide concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SULFUR_DIOXIDE_CONCENTRATION								0x2BD8
	/// <summary> Sulfur hexafluoride concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_SULFUR_HEXAFLUORIDE_CONCENTRATION							0x2BD9
	/// <summary> Hearing aid features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEARING_AID_FEATURES										0x2BDA
	/// <summary> Hearing aid preset control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEARING_AID_PRESENT_CONTROL_POINT							0x2BDB
	/// <summary> Active preset index characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ACTIVE_PRESENT_INDEX										0x2BDC
	/// <summary> Stored health observations characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_STORED_HEALTH_OBSERVATIONS									0x2BDD
	/// <summary> Fixed string 64 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_FIXED_STRING_64												0x2BDE
	/// <summary> High temperature characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HIGH_TEMPERATURE											0x2BDF
	/// <summary> High voltage characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HIGH_VOLTAGE												0x2BE0
	/// <summary> Light distribution characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LIGHT_DISTRIBUTION											0x2BE1
	/// <summary> Light output characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LIGHT_OUTPUT												0x2BE2
	/// <summary> Light source type characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LIGHT_SOURCE_TYPE											0x2BE3
	/// <summary> Noise characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_NOISE														0x2BE4
	/// <summary> Relative runtime in a correlated color temperature range characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_RELATIVE_RUNTIME_CORRELATED_COLOR_TEMPERATURE_RANGE			0x2BE5
	/// <summary> Time second 32 characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_TIME_SECOND_32												0x2BE6
	/// <summary> VOC concentration characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOC_CONCENTRATION											0x2BE7
	/// <summary> Voltage frequency characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_VOLTAGE_FREQUENCY											0x2BE8
	/// <summary> Battery critical status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_CRITICAL_STATUS										0x2BE9
	/// <summary> Battery health status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_HEALTH_STATUS										0x2BEA
	/// <summary> Battery health information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_HEALTH_INFORMATION									0x2BEB
	/// <summary> Battery information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_INFORMATION											0x2BEC
	/// <summary> Battery level status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_LEVEL_STATUS										0x2BED
	/// <summary> Battery time status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_TIME_STATUS											0x2BEE
	/// <summary> Estimated service date characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESTIMATED_SERVICE_DATE										0x2BEF
	/// <summary> Battery energy status characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BATTERY_ENERGY_STATUS										0x2BF0
	/// <summary> Observation schedule changed characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_OBSERVATION_SCHEDULE_CHANGED								0x2BF1
	/// <summary> Current elapsed time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_CURRENT_ELAPSED_TIME										0x2BF2
	/// <summary> Health sensor features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_HEALTH_SENSOR_FEATURES										0x2BF3
	/// <summary> GHS control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GHS_CONTROL_POINT											0x2BF4
	/// <summary> LE GATT security levels characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS										0x2BF5
	/// <summary> ESL Address characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_ADDRESS													0x2BF6
	/// <summary> AP sync key material characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_AP_SYNC_KEY_MATERIAL										0x2BF7
	/// <summary> ESL response key material characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_RESPONSE_KEY_MATERIAL									0x2BF8
	/// <summary> ESL current absolute time characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_CURRENT_ABSOLUTE_TIME									0x2BF9
	/// <summary> ESL display information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_DISPLAY_INFORMATION										0x2BFA
	/// <summary> ESL image information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_IMAGE_INFORMATION										0x2BFB
	/// <summary> ESL sensor information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_SENSOR_INFORMATION										0x2BFC
	/// <summary> ESL LED information characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_LED_INFORMATION											0x2BFD
	/// <summary> ESL control point characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_ESL_CONTROL_POINT											0x2BFE
	/// <summary> UDI for medical devices characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UDI_MEDICAL_DEVICES											0x2BFF
	/// <summary> GMAP role characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_GMAP_ROLE													0x2C00
	/// <summary> UGG features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UGG_FEATURES												0x2C01
	/// <summary> UGT features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_UGT_FEATURES												0x2C02
	/// <summary> BGS features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BGS_FEATURES												0x2C03
	/// <summary> BGR features characteristic ID. </summary>
	#define GATT_CHARACTERISTIC_BGR_FEATURES												0x2C04

	/* Object Types. */

	/// <summary> Unspecified object type ID. </summary>
	#define GATT_OBJECT_TYPE_UNSPECIFIED		0x2ACA
	/// <summary> Directory listing object type ID. </summary>
	#define GATT_OBJECT_TYPE_DIRECTORY_LISTING	0x2ACB

	/* GAP Appearance. */

	/// <summary> GAP appearance category bits offset. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_OFFSET		0x6
	/// <summary> GAP appearance category bits mask. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_MASK			0x3ff
	/// <summary> GAP appearance subcategory bits mask. </summary>
	#define LE_GAP_APPEARANCE_SUB_CATEGORY_MASK		0x3f

	/// <summary> Unknown GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_UNKNOWN						0x0000
	/// <summary> Phone GAT appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_PHONE						0x0001
	/// <summary> Computer GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_COMPUTER						0x0002
	/// <summary> Watch GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_WATCH						0x0003
	/// <summary> Clock GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_CLOCK						0x0004
	/// <summary> Display GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_DISPLAY						0x0005
	/// <summary> Remote control GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_REMOTE_CONTROL				0x0006
	/// <summary> Eye-glasses GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_EYE_GLASSES					0x0007
	/// <summary> Tag GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_TAG							0x0008
	/// <summary> Keyring GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_KEYRING						0x0009
	/// <summary> Media player GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_MEDIA_PLAYER					0x000A
	/// <summary> Barcode scanner GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_BARCODE_SCANNER				0x000B
	/// <summary> Thermometer GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_THERMOMETER					0x000C
	/// <summary> Heart rate sensor GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HEART_RATE_SENSOR			0x000D
	/// <summary> Blood pressure GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_BLOOD_PRESSURE				0x000E
	/// <summary> Human interface device (HID) GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HUMAN_INTERFACE_DEVICE		0x000F
	/// <summary> Glucose meter GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_GLUCOSE_METER				0x0010
	/// <summary> Running walking sensor GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_RUNNING_WALKING_SENSOR		0x0011
	/// <summary> Cycling GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_CYCLING						0x0012
	/// <summary> Control device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_CONTROL_DEVICE				0x0013
	/// <summary> Network device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_NETWORK_DEVICE				0x0014
	/// <summary> Sensor GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_SENSOR						0x0015
	/// <summary> Light fixtures GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_LIGHT_FIXTURES				0x0016
	/// <summary> Fan GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_FAN							0x0017
	/// <summary> HVAC GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HVAC							0x0018
	/// <summary> Air conditioning GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_AIR_CONDITIONING				0x0019
	/// <summary> Humidifier GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HUMIDIFIER					0x001A
	/// <summary> Heating GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HEATING						0x001B
	/// <summary> Access control GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_ACCESS_CONTROL				0x001C
	/// <summary> Motorized device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_MOTORIZED_DEVICE				0x001D
	/// <summary> Power device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_POWER_DEVICE					0x001E
	/// <summary> Light source GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_LIGHT_SOURCE					0x001F
	/// <summary> Window covering GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_WINDOW_COVERING				0x0020
	/// <summary> Audio sink GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_AUDIO_SINK					0x0021
	/// <summary> Audio source GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_AUDIO_SOURCE					0x0022
	/// <summary> Motorized vehicle GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_MOTORIZED_VEHICLE			0x0023
	/// <summary> Domestic appliance GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_DOMESTIC_APPLIANCE			0x0024
	/// <summary> Wearable audio device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_WEARABLE_AUDIO_DEVICE		0x0025
	/// <summary> Aircraft GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_AIRCRAFT						0x0026
	/// <summary> AV equipment GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_AV_EQUIPMENT					0x0027
	/// <summary> Display equipment GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_DISPLAY_EQUIPMENT			0x0028
	/// <summary> Hearing aid GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_HEARING_AID					0x0029
	/// <summary> Gaming GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_GAMING						0x002A
	/// <summary> Signage GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_SIGNAGE						0x002B
	/// <summary> Pulse oximeter GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_PULSE_OXIMETER				0x0031
	/// <summary> Weight scale GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_WEIGHT_SCALE					0x0032
	/// <summary> Personal mobility device GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_PERSONAL_MOBILITY_DEVICE		0x0033
	/// <summary> Continuous glucose monitor GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_CONTINUOUS_GLUCOSE_MONITOR	0x0034
	/// <summary> Insulin pump GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_INSULIN_PUMP					0x0035
	/// <summary> Medication delivery GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_MEDICATION_DELIVERY			0x0036
	/// <summary> Spirometer GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_SPIROMETER					0x0037
	/// <summary> Outdoor sports activity GAP appearance category. </summary>
	#define LE_GAP_APPEARANCE_CATEGORY_OUTDOOR_SPORTS_ACTIVITY		0x0051

	/// <summary> Generic unknown GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_UNKNOWN						0x0000
	/// <summary> Generic phone GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_PHONE							0x0040
	/// <summary> Generic computer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_COMPUTER						0x0080
	/// <summary> Desktop workstation GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DESKTOP_WORKSTATION					0x0081
	/// <summary> Server-class computer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SERVER_CLASS_COMPUTER					0x0082
	/// <summary> Laptop GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LAPTOP								0x0083
	/// <summary> Handheld PC/PDA (clamshell) GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HANDHELD_COMPUTER						0x0084
	/// <summary> Palm-size PC/PDA GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PALM_SIZE_COMPUTER					0x0085
	/// <summary> Wearable computer (watch size) GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WEARABLE_COMPUTER						0x0086
	/// <summary> Tablet GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TABLET_COMPUTER						0x0087
	/// <summary> Docking station GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DOCKING_STATION						0x0088
	/// <summary> All in one GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ALL_IN_ONE							0x0089
	/// <summary> Blade server GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BLADE_SERVER							0x008A
	/// <summary> Convertible GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CONVERTIBLE							0x008B
	/// <summary> Detachable GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DETACHABLE							0x008C
	/// <summary> IoT gateway GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_IOT_GATEWAY							0x008D
	/// <summary> Mini PC GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MINI_PC								0x008E
	/// <summary> Stick PC GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_STICK_PC								0x008F
	/// <summary> Generic watch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_WATCH							0x00C0
	/// <summary> Sports watch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SPORTS_WATCH							0x00C1
	/// <summary> Smartwatch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SMARTWATCH							0x00C2
	/// <summary> Generic clock GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_CLOCK							0x0100
	/// <summary> Generic display GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_DISPLAY						0x0140
	/// <summary> Generic remote control GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_REMOTE_CONTROL				0x0180
	/// <summary> Generic eye-glasses GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_EYE_GLASSES					0x01C0
	/// <summary> Generic tag GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_TAG							0x0200
	/// <summary> Generic keyring GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_KEYRING						0x0240
	/// <summary> Generic media player GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_MEDIA_PLAYER					0x0280
	/// <summary> Generic barcode scanner GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_BARCODE_SCANNER				0x02C0
	/// <summary> Generic thermometer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_THERMOMETER					0x0300
	/// <summary> Ear thermometer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EAR_THERMOMETER						0x0301
	/// <summary> Generic heart rate sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HEART_RATE_SENSOR				0x0340
	/// <summary> Heart rate belt GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HEART_RATE_BELT						0x0341
	/// <summary> Generic blood pressure GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_BLOOD_PRESSURE				0x0380
	/// <summary> Arm blood pressure GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ARM_BLOOD_PRESSURE					0x0381
	/// <summary> Wrist blood pressure GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WRIST_BLOOD_PRESSURE					0x0382
	/// <summary> Generic human interface device (HID) GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HUMAN_INTERFACE_DEVICE		0x03C0
	/// <summary> Keyboard GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_KEYBOARD								0x03C1
	/// <summary> Mouse GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOUSE									0x03C2
	/// <summary> Joystick GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_JOYSTICK								0x03C3
	/// <summary> Gamepad GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GAMEPAD								0x03C4
	/// <summary> Digitizer tablet GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DIGITIZER_TABLET						0x03C5
	/// <summary> Card reader GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CARD_READER							0x03C6
	/// <summary> Digital pen GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DIGITAL_PEN							0x03C7
	/// <summary> Barcode scanner GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BARCODE_SCANNER						0x03C8
	/// <summary> Touchpad GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TOUCHPAD								0x03C9
	/// <summary> Presentation remote GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PRESENTATION_REMOTE					0x03CA
	/// <summary> Generic glucose meter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_GLUCOSE_METER					0x0400
	/// <summary> Generic running walking sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR		0x0440
	/// <summary> In-shoe running walking sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_IN_SHOE_RUNNING_WALKING_SENSOR		0x0441
	/// <summary> On-shoe running walking sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ON_SHOE_RUNNING_WALKING_SENSOR		0x0442
	/// <summary> On-hip running walking sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ON_HIP_RUNNING_WALKING_SENSOR			0x0443
	/// <summary> Generic cycling GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_CYCLING						0x0480
	/// <summary> Cycling computer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CYCLING_COMPUTER						0x0481
	/// <summary> Speed sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SPEED_SENSOR							0x0482
	/// <summary> Cadence sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CADENCE_SENSOR						0x0483
	/// <summary> Power sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWER_SENSOR							0x0484
	/// <summary> Speed and cadence sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SPEED_AND_CADENCE_SENSOR				0x0485
	/// <summary> Generic control device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_CONTROL_DEVICE				0x04C0
	/// <summary> Switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SWITCH								0x04C1
	/// <summary> Multi-switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MULTI_SWITCH							0x04C2
	/// <summary> Button GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BUTTON								0x04C3
	/// <summary> Slider GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SLIDER								0x04C4
	/// <summary> Rotary switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ROTARY_SWITCH							0x04C5
	/// <summary> Touch panel GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TOUCH_PANEL							0x04C6
	/// <summary> Single switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SINGLE_SWITCH							0x04C7
	/// <summary> Double switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DOUBLE_SWITCH							0x04C8
	/// <summary> Triple switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TRIPLE_SWITCH							0x04C9
	/// <summary> Battery switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BATTERY_SWITCH						0x04CA
	/// <summary> Energy harvesting switch GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ENERGY_HARVESTING_SWITCH				0x04CB
	/// <summary> Push button GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PUSH_BUTTON							0x04CC
	/// <summary> Dial GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DIAL									0x04CD
	/// <summary> Generic network device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_NETWORK_DEVICE				0x0500
	/// <summary> Access point GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ACCESS_POINT							0x0501
	/// <summary> Mesh device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MESH_DEVICE							0x0502
	/// <summary> Mesh network proxy GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MESH_NETWORK_PROXY					0x0503
	/// <summary> Generic sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_SENSOR						0x0540
	/// <summary> Motion sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOTION_SENSOR							0x0541
	/// <summary> Air quality sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AIR_QUALITY_SENSOR					0x0542
	/// <summary> Temperature sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TEMPERATURE_SENSOR					0x0543
	/// <summary> Humidity sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HUMIDITY_SENSOR						0x0544
	/// <summary> Leak sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LEAK_SENSOR							0x0545
	/// <summary> Smoke sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SMOKE_SENSOR							0x0546
	/// <summary> Occupancy sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_OCCUPANCY_SENSOR						0x0547
	/// <summary> Contact sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CONTACT_SENSOR						0x0548
	/// <summary> Carbon monoxide sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CARBON_MONOXIDE_SENSOR				0x0549
	/// <summary> Carbon dioxide sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CARBON_DIOXIDE_SENSOR					0x054A
	/// <summary> Ambient light sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AMBIENT_LIGHT_SENSOR					0x054B
	/// <summary> Energy sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ENERGY_SENSOR							0x054C
	/// <summary> Color light sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_COLOR_LIGHT_SENSOR					0x054D
	/// <summary> Rain sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RAIN_SENSOR							0x054E
	/// <summary> Fire sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FIRE_SENSOR							0x054F
	/// <summary> Wind sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WIND_SENSOR							0x0550
	/// <summary> Proximity sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PROXIMITY_SENSOR						0x0551
	/// <summary> Multi-sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MULTI_SENSOR							0x0552
	/// <summary> Flush mounted sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLUSH_MOUNTED_SENSOR					0x0553
	/// <summary> Ceiling mounted sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CEILING_MOUNTED_SENSOR				0x0554
	/// <summary> Wall mounted sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WALL_MOUNTED_SENSOR					0x0555
	/// <summary> Multisensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MULTISENSOR							0x0556
	/// <summary> Energy meter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ENERGY_METER							0x0557
	/// <summary> Flame detector GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLAME_DETECTOR						0x0558
	/// <summary> Vehicle tire pressure sensor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_VEHICLE_TIRE_PRESSURE_SENSOR			0x0559
	/// <summary> Generic light fixtures GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_LIGHT_FIXTURES				0x0580
	/// <summary> Wall light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WALL_LIGHT							0x0581
	/// <summary> Ceiling light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CEILING_LIGHT							0x0582
	/// <summary> Floor light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLOOR_LIGHT							0x0583
	/// <summary> Cabinet light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CABINET_LIGHT							0x0584
	/// <summary> Desk light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DESK_LIGHT							0x0585
	/// <summary> Troffer light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TROFFER_LIGHT							0x0586
	/// <summary> Pendant light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PENDANT_LIGHT							0x0587
	/// <summary> In-ground light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_IN_GROUND_LIGHT						0x0588
	/// <summary> Flood light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLOOD_LIGHT							0x0589
	/// <summary> Underwater light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_UNDERWATER_LIGHT						0x058A
	/// <summary> Bollard with light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BOLLARD_WITH_LIGHT					0x058B
	/// <summary> Pathway light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PATHWAY_LIGHT							0x058C
	/// <summary> Garden light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GARDEN_LIGHT							0x058D
	/// <summary> Pole-top light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POLE_TOP_LIGHT						0x058E
	/// <summary> Spotlight GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SPOTLIGHT								0x058F
	/// <summary> Linear light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LINEAR_LIGHT							0x0590
	/// <summary> Street light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_STREET_LIGHT							0x0591
	/// <summary> Shelves light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SHELVES_LIGHT							0x0592
	/// <summary> Bay light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BAY_LIGHT								0x0593
	/// <summary> Emergency exit light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EMERGENCY_EXIT_LIGHT					0x0594
	/// <summary> Light controller GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LIGHT_CONTROLLER						0x0595
	/// <summary> Light driver GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LIGHT_DRIVER							0x0596
	/// <summary> Bulb GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BULD									0x0597
	/// <summary> Low-bay light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOW_BAY_LIGHT							0x0598
	/// <summary> High-bay light GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HIGH_BAY_LIGHT						0x0599
	/// <summary> Generic fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_FAN							0x05C0
	/// <summary> Ceiling fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CEILING_FAN							0x05C1
	/// <summary> Axial fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AXIAL_FAN								0x05C2
	/// <summary> Exhaust fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EXHAUST_FAN							0x05C3
	/// <summary> Pedestal fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PEDESTAL_FAN							0x05C4
	/// <summary> Desk fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DESK_FAN								0x05C5
	/// <summary> Wall fan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WALL_FAN								0x05C6
	/// <summary> Generic HVAC GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HVAC							0x0600
	/// <summary> Thermostat GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_THERMOSTAT							0x0601
	/// <summary> Humidifier GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HUMIDIFIER							0x0602
	/// <summary> De-humidifier GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DE_HUMIDIFIER							0x0603
	/// <summary> Heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HEATER								0x0604
	/// <summary> HVAC radiator GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_RADIATOR							0x0605
	/// <summary> HVAC boiler GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_BOILER							0x0606
	/// <summary> HVAC heat pump GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_HEAT_PUMP						0x0607
	/// <summary> HVAC infrared heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_INFRARED_HEATER					0x0608
	/// <summary> HVAC radiant panel heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_RADIANT_PANEL_HEATER				0x0609
	/// <summary> HVAC fan heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_FAN_HEATER						0x060A
	/// <summary> HVAC air curtain GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HVAC_AIR_CURTAIN						0x060B
	/// <summary> Generic air conditioning GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_AIR_CONDITIONING				0x0640
	/// <summary> Generic humidifier GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HUMIDIFIER					0x0680
	/// <summary> Generic heating GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HEATING						0x06C0
	/// <summary> Radiator GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RADIATOR								0x06C1
	/// <summary> Boiler GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BOILER								0x06C2
	/// <summary> Heat pump GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HEAT_PUMP								0x06C3
	/// <summary> Infrared heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_INFRARED_HEATER						0x06C4
	/// <summary> Radiant panel heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RADIANT_PANEL_HEATER					0x06C5
	/// <summary> Fan heater GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FAN_HEATER							0x06C6
	/// <summary> Air curtain GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AIR_CURTAIN							0x06C7
	/// <summary> Generic access control GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_ACCESS_CONTROL				0x0700
	/// <summary> Access door GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ACCESS_DOOR							0x0701
	/// <summary> Garage door GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GARAGE_DOOR							0x0702
	/// <summary> Emergency exit door GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EMERGENCY_EXIT_DOOR					0x0703
	/// <summary> Access lock GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ACCESS_LOCK							0x0704
	/// <summary> Elevator GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ELEVATOR								0x0705
	/// <summary> Window GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WINDOW								0x0706
	/// <summary> Entrance gate GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ENTRANCE_GATE							0x0707
	/// <summary> Door lock GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DOOR_LOCK								0x0708
	/// <summary> Locker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOCKER								0x0709
	/// <summary> Generic motorized device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_MOTORIZED_DEVICE				0x0740
	/// <summary> Motorized gate GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOTORIZED_GATE						0x0741
	/// <summary> Awning GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AWNING								0x0742
	/// <summary> Blinds or shades GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BLINDS_SHADES							0x0743
	/// <summary> Curtains GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CURTAINS								0x0744
	/// <summary> Screen GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SCREEN								0x0745
	/// <summary> Generic power device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_POWER_DEVICE					0x0780
	/// <summary> Power outlet GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWER_OUTLET							0x0781
	/// <summary> Power strip GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWER_STRIP							0x0782
	/// <summary> Plug GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PLUG									0x0783
	/// <summary> Power supply GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWER_SUPPLY							0x0784
	/// <summary> LED driver GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LED_DRIVER							0x0785
	/// <summary> Fluorescent lamp gear GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLUORESCENT_LAMP_GEAR					0x0786
	/// <summary> HID lamp gear GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HID_LAMP_GEAR							0x0787
	/// <summary> Charge case GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CHARGE_CASE							0x0788
	/// <summary> Power bank GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWER_BANK							0x0789
	/// <summary> Generic light source GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_LIGHT_SOURCE					0x07C0
	/// <summary> Incandescent light bulb GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_INCANDESCENT_LIGHT_BULB				0x07C1
	/// <summary> LED lamp GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LED_LAMP								0x07C2
	/// <summary> HID lamp GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HID_LAMP								0x07C3
	/// <summary> Fluorescent lamp GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FLUORESCENT_LAMP						0x07C4
	/// <summary> LED array GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LED_ARRAY								0x07C5
	/// <summary> Multi-color LED array GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MULTI_COLOR_LED_ARRAY					0x07C6
	/// <summary> Low voltage halogen GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOW_VOLTAGE_HALOGEN					0x07C7
	/// <summary> Organic light emitting diode (OLED) GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_OLED									0x07C8
	/// <summary> Generic window covering GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GEENRIC_WINDOW_COVERING				0x0800
	/// <summary> Window shades GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WINDOW_SHADES							0x0801
	/// <summary> Window blinds GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WINDOW_BLINDS							0x0802
	/// <summary> Window awning GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WINDOW_AWNING							0x0803
	/// <summary> Window curtain GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WINDOW_CURTAIN						0x0804
	/// <summary> Exterior shutter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EXTERIOR_SHUTTER						0x0805
	/// <summary> Exterior screen GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EXTERIOR_SCREEN						0x0806
	/// <summary> Generic audio sink GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_AUDIO_SINK					0x0840
	/// <summary> Standalone speaker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_STANDALONE_SPEAKER					0x0841
	/// <summary> Soundbar GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SOUNDBAR								0x0842
	/// <summary> Bookshelf speaker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BOOKSHELF_SPEAKER						0x0843
	/// <summary> Standmounted speaker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_STANDMOUNTED_SPEAKER					0x0844
	/// <summary> Speakerphone GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SPEAKERPHONE							0x0845
	/// <summary> Generic audio source GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_AUDIO_SOURCE					0x0880
	/// <summary> Microphone GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MICROPHONE							0x0881
	/// <summary> Alarm GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ALARM									0x0882
	/// <summary> Bell GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BELL									0x0883
	/// <summary> Horn GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HORN									0x0884
	/// <summary> Broadcasting device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BROADCASTING_DEVICE					0x0885
	/// <summary> Service desk GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SERVICE_DESK							0x0886
	/// <summary> Kiosk GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_KIOSK									0x0887
	/// <summary> Broadcasting room GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BROADCASTING_ROOM						0x0888
	/// <summary> Auditorium GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AUDITORIUM							0x0889
	/// <summary> Generic motorized vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_MOTORIZED_VEHICLE				0x08C0
	/// <summary> Car GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CAR									0x08C1
	/// <summary> Large goods vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LARGE_GOODS_VEHICLE					0x08C2
	/// <summary> 2-Wheeled vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_2_WHEELED_VEHICLE						0x08C3
	/// <summary> Motorbike GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOTORBIKE								0x08C4
	/// <summary> Scooter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SCOOTER								0x08C5
	/// <summary> Moped GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOPED									0x08C6
	/// <summary> 3-Wheeled vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_3_WHEELED_VEHICLE						0x08C7
	/// <summary> Light vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LIGHT_VEHICLE							0x08C8
	/// <summary> Quad bike GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_QUAD_BIKE								0x08C9
	/// <summary> Minibus GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MINIBUS								0x08CA
	/// <summary> Bus GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BUS									0x08CB
	/// <summary> Trolley GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TROLLEY								0x08CC
	/// <summary> Agricultural vehicle GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AGRICULTURAL_VEHICLE					0x08CD
	/// <summary> Camper/Caravan GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CAMPER								0x08CE
	/// <summary> Recreational vehicle/Motor home GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RECREATIONAL_VEHICLE					0x08CF
	/// <summary> Generic domestic appliance GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_DOMESTIC_APPLIANCE			0x0900
	/// <summary> Refrigerator GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_REFRIGERATOR							0x0901
	/// <summary> Freezer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FREEZER								0x0902
	/// <summary> Oven GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_OVEN									0x0903
	/// <summary> Microwave GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MICROWAVE								0x0904
	/// <summary> Toaster GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TOASTER								0x0905
	/// <summary> Washing machine GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WASHING_MACHINE						0x0906
	/// <summary> Dryer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DRYER									0x0907
	/// <summary> Coffee maker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_COFFEE_MAKER							0x0908
	/// <summary> Clothes iron GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CLOTHES_IRON							0x0909
	/// <summary> Curling iron GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CURLING_IRON							0x090A
	/// <summary> Hair dryer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HAIR_DRYER							0x090B
	/// <summary> Vacuum cleaner GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_VACUUM_CLEANER						0x090C
	/// <summary> Robotic vacuum cleaner GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ROBOTIC_VACUUM_CLEANER				0x090D
	/// <summary> Rice cooker GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RICE_COOKER							0x090E
	/// <summary> Clothes steamer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CLOTHES_STEAMER						0x090F
	/// <summary> Generic wearable audio device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_WARABLE_AUDIO_DEVICE			0x0940
	/// <summary> Earbud GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_EARBUD								0x0941
	/// <summary> Headset GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HEADSET								0x0942
	/// <summary> Headphones GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HEADPHONES							0x0943
	/// <summary> Neck band GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_NECK_BAND								0x0944
	/// <summary> Generic aircraft GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_AIRCRAFT						0x0980
	/// <summary> Light aircraft GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LIGHT_AIRCRAFT						0x0981
	/// <summary> Microlight GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MICROLIGHT							0x0982
	/// <summary> Paraglider GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PARAGLIDER							0x0983
	/// <summary> Large passenger aircraft GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LARGE_PASSENGER_AIRCRAFT				0x0984
	/// <summary> Generic AV equipment GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_AV_EQUIPMENT					0x09C0
	/// <summary> Amplifier GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_AMPLIFIER								0x09C1
	/// <summary> Receiver GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RECEIVER								0x09C2
	/// <summary> Radio GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_RADIO									0x09C3
	/// <summary> Tuner GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TUNER									0x09C4
	/// <summary> Turntable GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TURNTABLE								0x09C5
	/// <summary> CD player GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_CD_PLAYER								0x09C6
	/// <summary> DVD player GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DVD_PLAYER							0x09C7
	/// <summary> Bluray player GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BLURAY_PLAYER							0x09C8
	/// <summary> Optical disc player GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_OPTICAL_DISC_PLAYER					0x09C9
	/// <summary> Set-top box GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_SET_TOP_BOX							0x09CA
	/// <summary> Generic display equipment GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_DISPLAY_EQUIPMENT				0x0A00
	/// <summary> Television GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_TELEVISION							0x0A01
	/// <summary> Monitor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MONITOR								0x0A02
	/// <summary> Projector GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PROJECTOR								0x0A03
	/// <summary> Generic hearing aid GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_HEARING_AID					0x0A40
	/// <summary> In-ear hearing aid GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_IN_EAR_HEARING_AID					0x0A41
	/// <summary> Behind-ear hearing aid GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_BEHIND_EAR_HEARING_AID				0x0A42
	/// <summary> Cochlear implant GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_COCHLEAR_IMPLANT						0x0A43
	/// <summary> Generic gaming GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_GAMING						0x0A80
	/// <summary> Home video game console GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HOME_VIDEO_GAME_CONSOLE				0x0A81
	/// <summary> Portable handheld console GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_PORTABLE_HANDHELD_CONSOLE				0x0A82
	/// <summary> Generic signage GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_SIGNAGE						0x0AC0
	/// <summary> Digital signage GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_DIGITAL_SIGNAGE						0x0AC1
	/// <summary> Electronic label GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_ELECTRONIC_LABEL						0x0AC2
	/// <summary> Generic pulse oximeter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_PULSE_OXIMETER				0x0C40
	/// <summary> Fingertip pulse oximeter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_FINGERTIP_PULSE_OXIMETER				0x0C41
	/// <summary> Wrist worn pulse oximeter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_WRIST_WORN_PULSE_OXIMETER				0x0C42
	/// <summary> Generic weight scale GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_WEIGHT_SCALE					0x0C80
	/// <summary> Generic personal mobility device GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_PERSONAL_MOBILITY_DEVICE		0x0CC0
	/// <summary> Powered wheelchair GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_POWERED_WHEELCHAIR					0x0CC1
	/// <summary> Mobility scooter GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_MOBILITY_SCOOTER						0x0CC2
	/// <summary> Generic continuous glucose monitor GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR	0x0D00
	/// <summary> Generic insulin pump GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_INSULIN_PUMP					0x0D40
	/// <summary> Insulin pump, durable pump GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_INSULIN_PUMP_DURABLE					0x0D41
	/// <summary> Insulin pump, patch pump GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_INSULIN_PUMP_PATCH					0x0D44
	/// <summary> Insulin pen GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_INSULIN_PEN							0x0D48
	/// <summary> Generic medication delivery GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_MEDICATION_DELIVERY			0x0D80
	/// <summary> Generic spirometer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_SPIROMETER					0x0DC0
	/// <summary> Handheld spirometer GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_HANDHELD_SPIROMETER					0x0DC1
	/// <summary> Generic outdoor sports activity GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_GENERIC_OUTDOOR_SPORTS_ACTIVITY		0x1440
	/// <summary> Location display GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOCATION_DISPLAY						0x1441
	/// <summary> Location and navigation display GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOCATION_NAVIGATION_DISPLAY			0x1442
	/// <summary> Location pod GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOCATION_POD							0x1443
	/// <summary> Location and navigation pod GAP appearance. </summary>
	#define LE_GAP_APPEARANCE_LOCATION_NAVIGATION_POD				0x1444

	/* GAP Advertisement Types. */

	/// <summary> None or invalid. </summary>
	#define LE_GAP_AD_TYPE_NONE						0x00
	/// <summary> Flags. </summary>
	#define LE_GAP_AD_TYPE_FLAGS					0x01
	/// <summary> Incomplete List of 16-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_16_MORE			0x02
	/// <summary> Complete List of 16-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_16_ALL			0x03
	/// <summary> Incomplete List of 32-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_32_MORE			0x04
	/// <summary> Complete List of 32-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_32_ALL			0x05
	/// <summary> Incomplete List of 128-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_128_MORE		0x06
	/// <summary> Complete List of 128-bit Service Class UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICES_128_ALL			0x07
	/// <summary> Shortened Local Name. </summary>
	#define LE_GAP_AD_TYPE_LOCAL_NAME_SHORT			0x08
	/// <summary> Complete Local Name. </summary>
	#define LE_GAP_AD_TYPE_LOCAL_NAME_COMPLETE		0x09
	/// <summary> TX Power Level. </summary>
	#define LE_GAP_AD_TYPE_TXPOWER					0x0A
	/// <summary> Class of Device. </summary>
	#define LE_GAP_AD_TYPE_COD						0x0D
	/// <summary> Simple Pairing Hash C. </summary>
	#define LE_GAP_AD_TYPE_PAIRING_HASH_C			0x0E
	/// <summary> Simple Pairing Randomizer R. </summary>
	#define LE_GAP_AD_TYPE_PAIRING_RAND_R			0x0F
	/// <summary> Device ID. </summary>
	#define LE_GAP_AD_TYPE_DEVICE_ID				0x10
	/// <summary> Security Manager Out of Band Flags. </summary>
	#define LE_GAP_AD_TYPE_SM_OOB_FLAGS				0x11
	/// <summary> Slave Connection Interval Range. </summary>
	#define LE_GAP_AD_TYPE_CON_INTERVALS			0x12
	/// <summary> List of 16-bit Service Solicitation UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_SOL_UUIDS_16		0x14
	/// <summary> List of 128-bit Service Solicitation UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_SOL_UUIDS_128	0x15
	/// <summary> Service Data 16-bit UUID. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_DATA_16			0x16
	/// <summary> Public Target Address. </summary>
	#define LE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS	0x17
	/// <summary> Random Target Address. </summary>
	#define LE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS	0x18
	/// <summary> Appearance. </summary>
	#define LE_GAP_AD_TYPE_APPEARANCE				0x19
	/// <summary> Advertising Interval. </summary>
	#define LE_GAP_AD_TYPE_ADV_INTERVAL				0x1A
	/// <summary> LE Bluetooth Device Address. </summary>
	#define LE_GAP_AD_TYPE_ADDRESS					0x1B
	/// <summary> LE Role. </summary>
	#define LE_GAP_AD_TYPE_ROLE						0x1C
	/// <summary> Simple Pairing Hash C-256. </summary>
	#define LE_GAP_AD_TYPE_PAIRING_HASH_C_256		0x1D
	/// <summary> Simple Pairing Randomizer R-256. </summary>
	#define LE_GAP_AD_TYPE_PAIRING_RAND_R_256		0x1E
	/// <summary> List of 32-bit Service Solicitation UUIDs. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_SOL_UUIDS_32		0x1F
	/// <summary> Service Data - 32-bit UUID. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_DATA_32			0x20
	/// <summary> Service Data - 128-bit UUID. </summary>
	#define LE_GAP_AD_TYPE_SERVICE_DATA_128			0x21
	/// <summary> LE Secure Connections Confirmation Value. </summary>
	#define LE_GAP_AD_TYPE_SECURE_CONFIRM			0x22
	/// <summary> LE Secure Connections Random Value. </summary>
	#define LE_GAP_AD_TYPE_SECURE_RAND				0x23
	/// <summary> URI. </summary>
	#define LE_GAP_AD_TYPE_URI						0x24
	/// <summary> Indoor Positioning. </summary>
	#define LE_GAP_AD_TYPE_INDOOR_POS				0x25
	/// <summary> Transport Discovery Data. </summary>
	#define LE_GAP_AD_TYPE_TRANS_DISC_DATA			0x26
	/// <summary> LE Supported Features. </summary>
	#define LE_GAP_AD_TYPE_FEATURES					0x27
	/// <summary> Channel Map Update Indication. </summary>
	#define LE_GAP_AD_TYPE_CH_MAP					0x28
	/// <summary> PB-ADV. </summary>
	#define LE_GAP_AD_TYPE_PB_ADV					0x29
	/// <summary> Mesh Message. </summary>
	#define LE_GAP_AD_TYPE_MESH_MSG					0x2A
	/// <summary> Mesh Beacon. </summary>
	#define LE_GAP_AD_TYPE_MESH_BEACON				0x2B
	/// <summary> BIGInfo. </summary>
	#define LE_GAP_AD_TYPE_BIG_INGO					0x2C
	/// <summary> Broadcast Code. </summary>
	#define LE_GAP_AD_TYPE_BROADCAST_CODE			0x2D
	/// <summary> 3D Information Data. </summary>
	#define LE_GAP_AD_TYPE_3D_INFO					0x3D
	/// <summary> Manufacturer Specific Data. </summary>
	#define LE_GAP_AD_TYPE_MANUFACTURER				0xFF

	/* LE Beacons UUIDs. */

	/// <summary> Eddystone Beacon service UUID. </summary>
	#define EDDYSTONE_BEACON_UUID_16	0xFEAA

	/// <summary> Eddystone UID beacon frame ID. </summary>
	/// <remarks> This constant is defined for internal use only. </remarks>
	#define EDDYSTONE_UID_FRAME_ID	0x00
	/// <summary> Eddystone URL beacon frame ID. </summary>
	/// <remarks> This constant is defined for internal use only. </remarks>
	#define EDDYSTONE_URL_FRAME_ID	0x10
	/// <summary> Eddystone TLM beacon frame ID. </summary>
	/// <remarks> This constant is defined for internal use only. </remarks>
	#define EDDYSTONE_TLM_FRAME_ID	0x20

	/* DRI UUIDs. */

	/// <summary> The Drone Remote ID ASD service UUID. </summary>
	#define DRI_ASD_UUID_16		0xFFFA
}