////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Wireless Communication Library 7                                         //
//                                                                            //
//   Copyright (C) 2006-2025 Mike Petrichenko                                 //
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

#include <initguid.h>
#include <list>

#include "wclHelpers.h"

using namespace wclSync;

namespace wclCommon
{
	namespace WinApi
	{
		#ifndef ERROR_DEVICE_FEATURE_NOT_SUPPORTED
			#define ERROR_DEVICE_FEATURE_NOT_SUPPORTED	316
		#endif

		DEFINE_GUID(GUID_SERIAL_PORT, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
		DEFINE_GUID(GUID_MODEM, 0x4D36E96D, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
		DEFINE_GUID(GUID_COM0COM, 0xdf799e12, 0x3c56, 0x421b, 0xb2, 0x98, 0xb6, 0xd3, 0x64, 0x2b, 0xc8, 0x78);
		DEFINE_GUID(GUID_USB, 0xA5DCBF10, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);

		// Configuration Manager API used on Windows 10 IoT.
		// We can not use regular import because it doe snot available on all platforms
		// So we will use LoadLibrary and GetProcAddress when needed. Declare only
		// pointers here.

		#ifndef MAX_DEVICE_ID_LEN
			#define MAX_DEVICE_ID_LEN	200
		#endif

		#ifndef CM_NOTIFY_FILTER_FLAG_ALL_INTERFACE_CLASSES
			#define CM_NOTIFY_FILTER_FLAG_ALL_INTERFACE_CLASSES	0x00000001
		#endif
		#ifndef CM_NOTIFY_FILTER_FLAG_ALL_DEVICE_INSTANCES
			#define CM_NOTIFY_FILTER_FLAG_ALL_DEVICE_INSTANCES	0x00000002
		#endif

		#ifndef CR_SUCCESS
			#define CR_SUCCESS						0x00000000
		#endif
		#ifndef CR_DEFAULT
			#define CR_DEFAULT						0x00000001
		#endif
		#ifndef CR_OUT_OF_MEMORY
			#define CR_OUT_OF_MEMORY				0x00000002
		#endif
		#ifndef CR_INVALID_POINTER
			#define CR_INVALID_POINTER				0x00000003
		#endif
		#ifndef CR_INVALID_FLAG
			#define CR_INVALID_FLAG					0x00000004
		#endif
		#ifndef CR_INVALID_DEVNODE
			#define CR_INVALID_DEVNODE				0x00000005
		#endif
		#ifndef CR_INVALID_DEVINST
			#define CR_INVALID_DEVINST				CR_INVALID_DEVNODE
		#endif
		#ifndef CR_INVALID_RES_DES
			#define CR_INVALID_RES_DES				0x00000006
		#endif
		#ifndef CR_INVALID_LOG_CONF
			#define CR_INVALID_LOG_CONF				0x00000007
		#endif
		#ifndef CR_INVALID_ARBITRATOR
			#define CR_INVALID_ARBITRATOR			0x00000008
		#endif
		#ifndef CR_INVALID_NODELIST
			#define CR_INVALID_NODELIST				0x00000009
		#endif
		#ifndef CR_DEVNODE_HAS_REQS
			#define CR_DEVNODE_HAS_REQS				0x0000000A
		#endif
		#ifndef CR_DEVINST_HAS_REQS
			#define CR_DEVINST_HAS_REQS				CR_DEVNODE_HAS_REQS
		#endif
		#ifndef CR_INVALID_RESOURCEID
			#define CR_INVALID_RESOURCEID			0x0000000B
		#endif
		#ifndef CR_DLVXD_NOT_FOUND
			#define CR_DLVXD_NOT_FOUND				0x0000000C
		#endif
		#ifndef CR_NO_SUCH_DEVNODE
			#define CR_NO_SUCH_DEVNODE				0x0000000D
		#endif
		#ifndef CR_NO_SUCH_DEVINST
			#define CR_NO_SUCH_DEVINST				CR_NO_SUCH_DEVNODE
		#endif
		#ifndef CR_NO_MORE_LOG_CONF
			#define CR_NO_MORE_LOG_CONF				0x0000000E
		#endif
		#ifndef CR_NO_MORE_RES_DES
			#define CR_NO_MORE_RES_DES				0x0000000F
		#endif
		#ifndef CR_ALREADY_SUCH_DEVNODE
			#define CR_ALREADY_SUCH_DEVNODE			0x00000010
		#endif
		#ifndef CR_ALREADY_SUCH_DEVINST
			#define CR_ALREADY_SUCH_DEVINST			CR_ALREADY_SUCH_DEVNODE
		#endif
		#ifndef CR_INVALID_RANGE_LIST
			#define CR_INVALID_RANGE_LIST			0x00000011
		#endif
		#ifndef CR_INVALID_RANGE
			#define CR_INVALID_RANGE				0x00000012
		#endif
		#ifndef CR_FAILURE
			#define CR_FAILURE						0x00000013
		#endif
		#ifndef CR_NO_SUCH_LOGICAL_DEV
			#define CR_NO_SUCH_LOGICAL_DEV			0x00000014
		#endif
		#ifndef CR_CREATE_BLOCKED
			#define CR_CREATE_BLOCKED				0x00000015
		#endif
		#ifndef CR_NOT_SYSTEM_VM
			#define CR_NOT_SYSTEM_VM				0x00000016
		#endif
		#ifndef CR_REMOVE_VETOED
			#define CR_REMOVE_VETOED				0x00000017
		#endif
		#ifndef CR_APM_VETOED
			#define CR_APM_VETOED					0x00000018
		#endif
		#ifndef CR_INVALID_LOAD_TYPE
			#define CR_INVALID_LOAD_TYPE			0x00000019
		#endif
		#ifndef CR_BUFFER_SMALL
			#define CR_BUFFER_SMALL					0x0000001A
		#endif
		#ifndef CR_NO_ARBITRATOR
			#define CR_NO_ARBITRATOR				0x0000001B
		#endif
		#ifndef CR_NO_REGISTRY_HANDLE
			#define CR_NO_REGISTRY_HANDLE			0x0000001C
		#endif
		#ifndef CR_REGISTRY_ERROR
			#define CR_REGISTRY_ERROR				0x0000001D
		#endif
		#ifndef CR_INVALID_DEVICE_ID
			#define CR_INVALID_DEVICE_ID			0x0000001E
		#endif
		#ifndef CR_INVALID_DATA
			#define CR_INVALID_DATA					0x0000001F
		#endif
		#ifndef CR_INVALID_API
			#define CR_INVALID_API					0x00000020
		#endif
		#ifndef CR_DEVLOADER_NOT_READY
			#define CR_DEVLOADER_NOT_READY			0x00000021
		#endif
		#ifndef CR_NEED_RESTART
			#define CR_NEED_RESTART					0x00000022
		#endif
		#ifndef CR_NO_MORE_HW_PROFILES
			#define CR_NO_MORE_HW_PROFILES			0x00000023
		#endif
		#ifndef CR_DEVICE_NOT_THERE
			#define CR_DEVICE_NOT_THERE				0x00000024
		#endif
		#ifndef CR_NO_SUCH_VALUE
			#define CR_NO_SUCH_VALUE				0x00000025
		#endif
		#ifndef CR_WRONG_TYPE
			#define CR_WRONG_TYPE					0x00000026
		#endif
		#ifndef CR_INVALID_PRIORITY
			#define CR_INVALID_PRIORITY				0x00000027
		#endif
		#ifndef CR_NOT_DISABLEABLE
			#define CR_NOT_DISABLEABLE				0x00000028
		#endif
		#ifndef CR_FREE_RESOURCES
			#define CR_FREE_RESOURCES				0x00000029
		#endif
		#ifndef CR_QUERY_VETOED
			#define CR_QUERY_VETOED					0x0000002A
		#endif
		#ifndef CR_CANT_SHARE_IRQ
			#define CR_CANT_SHARE_IRQ				0x0000002B
		#endif
		#ifndef CR_NO_DEPENDENT
			#define CR_NO_DEPENDENT					0x0000002C
		#endif
		#ifndef CR_SAME_RESOURCES
			#define CR_SAME_RESOURCES				0x0000002D
		#endif
		#ifndef CR_NO_SUCH_REGISTRY_KEY
			#define CR_NO_SUCH_REGISTRY_KEY			0x0000002E
		#endif
		#ifndef CR_INVALID_MACHINENAME
			#define CR_INVALID_MACHINENAME			0x0000002F
		#endif
		#ifndef CR_REMOTE_COMM_FAILURE
			#define CR_REMOTE_COMM_FAILURE			0x00000030
		#endif
		#ifndef CR_MACHINE_UNAVAILABLE
			#define CR_MACHINE_UNAVAILABLE			0x00000031
		#endif
		#ifndef CR_NO_CM_SERVICES
			#define CR_NO_CM_SERVICES				0x00000032
		#endif
		#ifndef CR_ACCESS_DENIED
			#define CR_ACCESS_DENIED				0x00000033
		#endif
		#ifndef CR_CALL_NOT_IMPLEMENTED
			#define CR_CALL_NOT_IMPLEMENTED			0x00000034
		#endif
		#ifndef CR_INVALID_PROPERTY
			#define CR_INVALID_PROPERTY				0x00000035
		#endif
		#ifndef CR_DEVICE_INTERFACE_ACTIVE
			#define CR_DEVICE_INTERFACE_ACTIVE		0x00000036
		#endif
		#ifndef CR_NO_SUCH_DEVICE_INTERFACE
			#define CR_NO_SUCH_DEVICE_INTERFACE		0x00000037
		#endif
		#ifndef CR_INVALID_REFERENCE_STRING
			#define CR_INVALID_REFERENCE_STRING		0x00000038
		#endif
		#ifndef CR_INVALID_CONFLICT_LIST
			#define CR_INVALID_CONFLICT_LIST		0x00000039
		#endif
		#ifndef CR_INVALID_INDEX
			#define CR_INVALID_INDEX				0x0000003A
		#endif
		#ifndef CR_INVALID_STRUCTURE_SIZE
			#define CR_INVALID_STRUCTURE_SIZE		0x0000003B
		#endif
		#ifndef NUM_CR_RESULTS
			#define NUM_CR_RESULTS					0x0000003C
		#endif

		#ifndef CM_LOCATE_DEVNODE_NORMAL
			#define CM_LOCATE_DEVNODE_NORMAL		0x00000000
		#endif
		#ifndef CM_LOCATE_DEVNODE_PHANTOM
			#define CM_LOCATE_DEVNODE_PHANTOM		0x00000001
		#endif
		#ifndef CM_LOCATE_DEVNODE_CANCELREMOVE
			#define CM_LOCATE_DEVNODE_CANCELREMOVE	0x00000002
		#endif
		#ifndef CM_LOCATE_DEVNODE_NOVALIDATION
			#define CM_LOCATE_DEVNODE_NOVALIDATION	0x00000004
		#endif
		#ifndef CM_LOCATE_DEVNODE_BITS
			#define CM_LOCATE_DEVNODE_BITS			0x00000007
		#endif

		#ifndef CM_GET_DEVICE_INTERFACE_LIST_PRESENT
			#define CM_GET_DEVICE_INTERFACE_LIST_PRESENT		0x00000000
		#endif
		#ifndef CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES
			#define CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES	0x00000001
		#endif
		#ifndef CM_GET_DEVICE_INTERFACE_LIST_BITS
			#define CM_GET_DEVICE_INTERFACE_LIST_BITS			0x00000001
		#endif

		#ifndef CM_PROB_DISABLED
			#define CM_PROB_DISABLED	0x00000016
		#endif

		#ifndef CM_DISABLE_UI_NOT_OK
			#define CM_DISABLE_UI_NOT_OK	0x00000004
		#endif
		#ifndef CM_DISABLE_PERSIST
			#define CM_DISABLE_PERSIST		0x00000008
		#endif

		#ifndef DN_HAS_PROBLEM
			#define DN_HAS_PROBLEM		0x00000400
		#endif
		#ifndef DN_PRIVATE_PROBLEM
			#define DN_PRIVATE_PROBLEM	0x00008000
		#endif
		#ifndef DN_STARTED
			#define DN_STARTED			0x00000008
		#endif

		typedef DWORD	CONFIGRET;
		typedef PWCHAR	DEVINSTID;
		typedef DWORD	DEVINST, *PDEVINST;
		typedef DWORD	DEVNODE, *PDEVNODE;

		typedef enum
		{
			CM_NOTIFY_FILTER_TYPE_DEVICEINTERFACE = 0,
			CM_NOTIFY_FILTER_TYPE_DEVICEHANDLE,
			CM_NOTIFY_FILTER_TYPE_DEVICEINSTANCE,
			CM_NOTIFY_FILTER_TYPE_MAX
		} CM_NOTIFY_FILTER_TYPE, *PCM_NOTIFY_FILTER_TYPE;

		typedef struct
		{
				DWORD cbSize;
				DWORD Flags;
				CM_NOTIFY_FILTER_TYPE FilterType;
				DWORD Reserved;
				union
				{
					struct
					{
						GUID ClassGuid;
					} DeviceInterface;
					struct
					{
						HANDLE hTarget;
					} DeviceHandle;
					struct
					{
						WCHAR InstanceId[MAX_DEVICE_ID_LEN];
					} DeviceInstance;
				} u;
		} CM_NOTIFY_FILTER, *PCM_NOTIFY_FILTER;

		typedef HANDLE HCMNOTIFICATION, *PHCMNOTIFICATION;

		typedef enum
		{
			CM_NOTIFY_ACTION_DEVICEINTERFACEARRIVAL = 0,
			CM_NOTIFY_ACTION_DEVICEINTERFACEREMOVAL,

			CM_NOTIFY_ACTION_DEVICEQUERYREMOVE,
			CM_NOTIFY_ACTION_DEVICEQUERYREMOVEFAILED,
			CM_NOTIFY_ACTION_DEVICEREMOVEPENDING,
			CM_NOTIFY_ACTION_DEVICEREMOVECOMPLETE,
			CM_NOTIFY_ACTION_DEVICECUSTOMEVENT,

			CM_NOTIFY_ACTION_DEVICEINSTANCEENUMERATED,
			CM_NOTIFY_ACTION_DEVICEINSTANCESTARTED,
			CM_NOTIFY_ACTION_DEVICEINSTANCEREMOVED,

			CM_NOTIFY_ACTION_MAX
		} CM_NOTIFY_ACTION, *PCM_NOTIFY_ACTION;

		typedef struct
		{
				CM_NOTIFY_FILTER_TYPE FilterType;
				DWORD Reserved;
				union
				{
					struct
					{
						GUID ClassGuid;
						WCHAR SymbolicLink[1];
					} DeviceInterface;
					struct
					{
						GUID EventGuid;
						LONG NameOffset;
						DWORD DataSize;
						BYTE Data[1];
					} DeviceHandle;
					struct
					{
						WCHAR InstanceId[1];
					} DeviceInstance;
				} u;
		} CM_NOTIFY_EVENT_DATA, *PCM_NOTIFY_EVENT_DATA;

		typedef GUID DEVPROPGUID, *PDEVPROPGUID;
		typedef ULONG DEVPROPID, *PDEVPROPID;

		typedef struct
		{
				DEVPROPGUID fmtid;
				DEVPROPID pid;
		} DEVPROPKEY, *PDEVPROPKEY;

		typedef ULONG DEVPROPTYPE, *PDEVPROPTYPE;

		typedef DWORD (__stdcall *PCM_NOTIFY_CALLBACK)(HCMNOTIFICATION hNotify,
			PVOID Context, CM_NOTIFY_ACTION Action, PCM_NOTIFY_EVENT_DATA EventData,
			DWORD EventDataSize);

		// Note that for all functions we will use only Unicode!
		CONFIGRET CM_Register_Notification(PCM_NOTIFY_FILTER pFilter, void* pContext,
			PCM_NOTIFY_CALLBACK pCallback, PHCMNOTIFICATION pNotifyContext);
		CONFIGRET CM_Unregister_Notification(HCMNOTIFICATION NotifyContex);
		CONFIGRET CM_Locate_DevNode(PDEVINST pdnDevInst, DEVINSTID pDeviceID, ULONG ulFlags);
		CONFIGRET CM_Get_DevNode_Property(DEVINST dnDevInst, PDEVPROPKEY PropertyKey,
			PDEVPROPTYPE PropertyType, PBYTE PropertyBuffer, PULONG PropertyBufferSize,
			ULONG ulFlags);
		CONFIGRET CM_Get_Device_Interface_List_Size(PULONG pulLen, LPGUID InterfaceClassGuid,
			DEVINSTID pDeviceID, ULONG ulFlags);
		CONFIGRET CM_Get_Device_Interface_List(LPGUID InterfaceClassGuid,
			DEVINSTID pDeviceID, PWCHAR Buffer, ULONG BufferLen, ULONG ulFlags);
		CONFIGRET CM_Get_Device_Interface_Property(LPCWSTR pszDeviceInterface,
			PDEVPROPKEY PropertyKey, PDEVPROPTYPE PropertyType, PBYTE PropertyBuffer,
			PULONG PropertyBufferSize, ULONG ulFlags);
		CONFIGRET CM_Get_DevNode_Status(PULONG pulStatus, PULONG pulProblemNumber,
			DEVINST dnDevInst, ULONG ulFlags);
		CONFIGRET CM_Disable_DevNode(DEVINST dnDevInst, ULONG ulFlags);
		CONFIGRET CM_Enable_DevNode(DEVINST dnDevInst, ULONG ulFlags);
		CONFIGRET CM_Get_Parent(PDEVINST pdnDevInst, DEVINST dnDevInst, ULONG ulFlags);

		// Configuration manager initialization.
		bool wclLoadCfgMgr();
		bool wclUnloadCfgMgr();

		const DEVPROPKEY DEVPKEY_Device_ClassGuid = { { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } }, 10 };
		const DEVPROPKEY DEVPKEY_Device_FriendlyName = { { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } }, 14 };
		const DEVPROPKEY DEVPKEY_Device_InstanceId = { { 0x78c34fc8, 0x104a, 0x4aca, { 0x9e, 0xa4, 0x52, 0x4d, 0x52, 0x99, 0x6e, 0x57 } }, 256 };
		const DEVPROPKEY DEVPKEY_Device_DeviceDesc = { { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } }, 2 };
		const DEVPROPKEY DEVPKEY_Device_HardwareIds = { { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } }, 3 };
		const DEVPROPKEY DEVPKEY_Device_Manufacturer = { { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } }, 13 };

		const DEVPROPKEY PKEY_DeviceInterface_Serial_PortName = { { 0x4C6BF15C, 0x4C03, 0x4AAC, { 0x91, 0xF5, 0x64, 0xC0, 0xF8, 0x52, 0xBC, 0xF4 } }, 4 };
		const DEVPROPKEY PKEY_DeviceInterface_Bluetooth_DeviceAddress = { { 0x2BD67D8B, 0x8BEB, 0x48D5, { 0x87, 0xE0, 0x6C, 0xDA, 0x34, 0x28, 0x04, 0x0A } }, 1 };
		const DEVPROPKEY PKEY_DeviceInterface_Bluetooth_ServiceGuid = { { 0x2BD67D8B, 0x8BEB, 0x48D5, { 0x87, 0xE0, 0x6C, 0xDA, 0x34, 0x28, 0x04, 0x0A } }, 2 };

		// Serial port IO CTRLS

		#ifndef IOCTL_SERIAL_SET_BAUD_RATE
			#define IOCTL_SERIAL_SET_BAUD_RATE		0x1B0004
		#endif
		#ifndef IOCTL_SERIAL_SET_DTR
			#define IOCTL_SERIAL_SET_DTR			0x1B0024
		#endif
		#ifndef IOCTL_SERIAL_SET_LINE_CONTROL
			#define IOCTL_SERIAL_SET_LINE_CONTROL	0x1B000C
		#endif
		#ifndef IOCTL_SERIAL_SET_CHARS
			#define IOCTL_SERIAL_SET_CHARS			0x1B005C
		#endif
		#ifndef IOCTL_SERIAL_SET_HANDFLOW
			#define IOCTL_SERIAL_SET_HANDFLOW		0x1B0064
		#endif

		#define STOP_BIT_1	0
		#define NO_PARITY	0

		#pragma pack(push, 1)
		typedef struct
		{
			UCHAR	StopBits;
			UCHAR	Parity;
			UCHAR	WordLength;
		} SERIAL_LINE_CONTROL, *PSERIAL_LINE_CONTROL;

		typedef struct
		{
			UCHAR	EofChar;
			UCHAR	ErrorChar;
			UCHAR	BreakChar;
			UCHAR	EventChar;
			UCHAR	XonChar;
			UCHAR	XoffChar;
		} SERIAL_CHARS, *PSERIAL_CHARS;

		typedef struct
		{
			ULONG	ControlHandShake;
			ULONG	FlowReplace;
			LONG	XonLimit;
			LONG	XoffLimit;
		} SERIAL_HANDFLOW, *PSERIAL_HANDFLOW;
		#pragma pack(pop)

		// WinRT data types.

		typedef LPCWSTR	PCNZWCH;

		typedef HANDLE HSTRING, *PHSTRING, **PPHSTRING;

		typedef struct
		{
			__int64 UniversalTime;
		} DateTime, *PDateTime;

		typedef struct
		{
			__int64 Duration;
		} TimeSpan;

		typedef struct
		{
			__int64 value;
		} EventRegistrationToken;

		typedef struct
		{
			UINT32	Variance;
			UINT32	Max;
			UINT32	Min;
			UINT32	Sum;
		} RoundTripTimeStatistics;

		typedef struct
		{
			UINT64	OutboundBitsPerSecond;
			UINT64	InboundBitsPerSecond;
			UINT64	OutboundBitsPerSecondInstability;
			UINT64	InboundBitsPerSecondInstability;
			BOOLEAN	OutboundBandwidthPeaked;
			BOOLEAN	InboundBandwidthPeaked;
		} BandwidthStatistics;

		typedef struct
		{
			BYTE	A;
			BYTE	R;
			BYTE	G;
			BYTE	B;
		} Color;

		typedef struct
		{
			FLOAT	X;
			FLOAT	Y;
		} Point;

		typedef struct
		{
			FLOAT	X;
			FLOAT	Y;
			FLOAT	Width;
			FLOAT	Height;
		} Rect;

		typedef struct
		{
			FLOAT	Width;
			FLOAT	Height;
		} Size;

		typedef enum
		{
			RO_INIT_SINGLETHREADED,
			RO_INIT_MULTITHREADED
		} RO_INIT_TYPE;

		typedef enum
		{
			BaseTrust,
			PartialTrust = BaseTrust + 1,
			FullTrust = PartialTrust + 1
		} TrustLevel;

		typedef enum
		{
			Started = 0,
			Completed = 1,
			Canceled = 2,
			Error = 3
		} AsyncStatus, *PAsyncStatus;

		typedef enum
		{
			NetworkConnectivityLevel_None = 0,
			NetworkConnectivityLevel_LocalAccess = 1,
			NetworkConnectivityLevel_ConstrainedInternetAccess = 2,
			NetworkConnectivityLevel_InternetAccess = 3
		} NetworkConnectivityLevel;

		typedef enum
		{
			NetworkCostType_Unknown = 0,
			NetworkCostType_Unrestricted = 1,
			NetworkCostType_Fixed = 2,
			NetworkCostType_Variable = 3
		} NetworkCostType;

		typedef enum
		{
			RoamingStates_None = 0,
			RoamingStates_NotRoaming = 0x1,
			RoamingStates_Roaming = 0x2
		} RoamingStates;

		typedef enum
		{
			NetworkAuthenticationType_None = 0,
			NetworkAuthenticationType_Unknown = 1,
			NetworkAuthenticationType_Open80211 = 2,
			NetworkAuthenticationType_SharedKey80211 = 3,
			NetworkAuthenticationType_Wpa = 4,
			NetworkAuthenticationType_WpaPsk = 5,
			NetworkAuthenticationType_WpaNone = 6,
			NetworkAuthenticationType_Rsna = 7,
			NetworkAuthenticationType_RsnaPsk = 8,
			NetworkAuthenticationType_Ihv = 9
		} NetworkAuthenticationType;

		typedef enum
		{
			NetworkEncryptionType_None = 0,
			NetworkEncryptionType_Unknown = 1,
			NetworkEncryptionType_Wep = 2,
			NetworkEncryptionType_Wep40 = 3,
			NetworkEncryptionType_Wep104 = 4,
			NetworkEncryptionType_Tkip = 5,
			NetworkEncryptionType_Ccmp = 6,
			NetworkEncryptionType_WpaUseGroup = 7,
			NetworkEncryptionType_RsnUseGroup = 8,
			NetworkEncryptionType_Ihv = 9
		} NetworkEncryptionType;

		typedef enum
		{
			NetworkTypes_None = 0,
			NetworkTypes_Internet = 0x1,
			NetworkTypes_PrivateNetwork = 0x2
		} NetworkTypes;

		typedef enum
		{
			HostNameType_DomainName = 0,
			HostNameType_Ipv4 = 1,
			HostNameType_Ipv6 = 2,
			HostNameType_Bluetooth = 3
		} HostNameType;

		typedef enum
		{
			Panel_Unknown = 0,
			Panel_Front = 1,
			Panel_Back = 2,
			Panel_Top = 3,
			Panel_Bottom = 4,
			Panel_Left = 5,
			Panel_Right = 6
		} Panel;

		typedef enum
		{
			DevicePairingKinds_None = 0,
			DevicePairingKinds_ConfirmOnly = 0x1,
			DevicePairingKinds_DisplayPin = 0x2,
			DevicePairingKinds_ProvidePin = 0x4,
			DevicePairingKinds_ConfirmPinMatch = 0x8
		} DevicePairingKinds;

		typedef enum
		{
			SocketProtectionLevel_PlainSocket = 0,
			SocketProtectionLevel_Ssl = 1,
			SocketProtectionLevel_SslAllowNullEncryption = 2,
			SocketProtectionLevel_BluetoothEncryptionAllowNullAuthentication = 3,
			SocketProtectionLevel_BluetoothEncryptionWithAuthentication = 4,
			SocketProtectionLevel_Ssl3AllowWeakEncryption = 5,
			SocketProtectionLevel_Tls10 = 6,
			SocketProtectionLevel_Tls11 = 7,
			SocketProtectionLevel_Tls12 = 8
		} SocketProtectionLevel;

		typedef enum
		{
			DeviceClass_All = 0,
			DeviceClass_AudioCapture = 1,
			DeviceClass_AudioRender = 2,
			DeviceClass_PortableStorageDevice = 3,
			DeviceClass_VideoCapture = 4,
			DeviceClass_ImageScanner = 5,
			DeviceClass_Location = 6
		} DeviceClass;

		typedef enum
		{
			DeviceWatcherStatus_Created = 0,
			DeviceWatcherStatus_Started = 1,
			DeviceWatcherStatus_EnumerationCompleted = 2,
			DeviceWatcherStatus_Stopping = 3,
			DeviceWatcherStatus_Stopped = 4,
			DeviceWatcherStatus_Aborted = 5
		} DeviceWatcherStatus;

		typedef enum
		{
			RadioState_Unknown = 0,
			RadioState_On = 1,
			RadioState_Off = 2,
			RadioState_Disabled = 3
		} RadioState;

		typedef enum
		{
			RadioAccessStatus_Unspecified = 0,
			RadioAccessStatus_Allowed = 1,
			RadioAccessStatus_DeniedByUser = 2,
			RadioAccessStatus_DeniedBySystem = 3
		} RadioAccessStatus;

		typedef enum
		{
			RadioKind_Other = 0,
			RadioKind_WiFi = 1,
			RadioKind_MobileBroadband = 2,
			RadioKind_Bluetooth = 3,
			RadioKind_FM = 4
		} RadioKind;

		typedef enum
		{
			DeviceAccessStatus_Unspecified = 0,
			DeviceAccessStatus_Allowed = 1,
			DeviceAccessStatus_DeniedByUser = 2,
			DeviceAccessStatus_DeniedBySystem = 3
		} DeviceAccessStatus;

		typedef enum
		{
			UnicodeEncoding_Utf8 = 0,
			UnicodeEncoding_Utf16LE = 1,
			UnicodeEncoding_Utf16BE = 2
		} UnicodeEncoding;

		typedef enum
		{
			ByteOrder_LittleEndian = 0,
			ByteOrder_BigEndian = 1
		} ByteOrder;

		typedef enum
		{
			SocketQualityOfService_Normal = 0,
			SocketQualityOfService_LowLatency = 1
		} SocketQualityOfService;

		typedef enum
		{
			InputStreamOptions_None = 0,
			InputStreamOptions_Partial = 0x1,
			InputStreamOptions_ReadAhead = 0x2
		} InputStreamOptions;

		typedef enum
		{
			SocketActivityConnectedStandbyAction_DoNotWake = 0,
			SocketActivityConnectedStandbyAction_Wake = 1
		} SocketActivityConnectedStandbyAction;

		typedef enum
		{
			DeviceInformationKind_Unknown = 0,
			DeviceInformationKind_DeviceInterface = 1,
			DeviceInformationKind_DeviceContainer = 2,
			DeviceInformationKind_Device = 3,
			DeviceInformationKind_DeviceInterfaceClass = 4,
			DeviceInformationKind_AssociationEndpoint = 5,
			DeviceInformationKind_AssociationEndpointContainer = 6,
			DeviceInformationKind_AssociationEndpointService = 7
		} DeviceInformationKind;

		typedef enum
		{
			DevicePairingResultStatus_Paired = 0,
			DevicePairingResultStatus_NotReadyToPair = 1,
			DevicePairingResultStatus_NotPaired = 2,
			DevicePairingResultStatus_AlreadyPaired = 3,
			DevicePairingResultStatus_ConnectionRejected = 4,
			DevicePairingResultStatus_TooManyConnections = 5,
			DevicePairingResultStatus_HardwareFailure = 6,
			DevicePairingResultStatus_AuthenticationTimeout = 7,
			DevicePairingResultStatus_AuthenticationNotAllowed = 8,
			DevicePairingResultStatus_AuthenticationFailure = 9,
			DevicePairingResultStatus_NoSupportedProfiles = 10,
			DevicePairingResultStatus_ProtectionLevelCouldNotBeMet = 11,
			DevicePairingResultStatus_AccessDenied = 12,
			DevicePairingResultStatus_InvalidCeremonyData = 13,
			DevicePairingResultStatus_PairingCanceled = 14,
			DevicePairingResultStatus_OperationAlreadyInProgress = 15,
			DevicePairingResultStatus_RequiredHandlerNotRegistered = 16,
			DevicePairingResultStatus_RejectedByHandler = 17,
			DevicePairingResultStatus_RemoteDeviceHasAssociation = 18,
			DevicePairingResultStatus_Failed = 19
		} DevicePairingResultStatus;

		typedef enum
		{
			DevicePairingProtectionLevel_Default = 0,
			DevicePairingProtectionLevel_None = 1,
			DevicePairingProtectionLevel_Encryption = 2,
			DevicePairingProtectionLevel_EncryptionAndAuthentication = 3
		} DevicePairingProtectionLevel;

		typedef enum
		{
			DeviceUnpairingResultStatus_Unpaired = 0,
			DeviceUnpairingResultStatus_AlreadyUnpaired = 1,
			DeviceUnpairingResultStatus_OperationAlreadyInProgress = 2,
			DeviceUnpairingResultStatus_AccessDenied = 3,
			DeviceUnpairingResultStatus_Failed = 4
		} DeviceUnpairingResultStatus;

		typedef enum
		{
			WebAccountState_None = 0,
			WebAccountState_Connected = 1,
			WebAccountState_Error = 2
		} WebAccountState;

		typedef enum
		{
			PropertyType_Empty = 0,
			PropertyType_UInt8 = 1,
			PropertyType_Int16 = 2,
			PropertyType_UInt16 = 3,
			PropertyType_Int32 = 4,
			PropertyType_UInt32 = 5,
			PropertyType_Int64 = 6,
			PropertyType_UInt64 = 7,
			PropertyType_Single = 8,
			PropertyType_Double = 9,
			PropertyType_Char16 = 10,
			PropertyType_Boolean = 11,
			PropertyType_String = 12,
			PropertyType_Inspectable = 13,
			PropertyType_DateTime = 14,
			PropertyType_TimeSpan = 15,
			PropertyType_Guid = 16,
			PropertyType_Point = 17,
			PropertyType_Size = 18,
			PropertyType_Rect = 19,
			PropertyType_OtherType = 20,
			PropertyType_UInt8Array = 1025,
			PropertyType_Int16Array = 1026,
			PropertyType_UInt16Array = 1027,
			PropertyType_Int32Array = 1028,
			PropertyType_UInt32Array = 1029,
			PropertyType_Int64Array = 1030,
			PropertyType_UInt64Array = 1031,
			PropertyType_SingleArray = 1032,
			PropertyType_DoubleArray = 1033,
			PropertyType_Char16Array = 1034,
			PropertyType_BooleanArray = 1035,
			PropertyType_StringArray = 1036,
			PropertyType_InspectableArray = 1037,
			PropertyType_DateTimeArray = 1038,
			PropertyType_TimeSpanArray = 1039,
			PropertyType_GuidArray = 1040,
			PropertyType_PointArray = 1041,
			PropertyType_SizeArray = 1042,
			PropertyType_RectArray = 1043,
			PropertyType_OtherTypeArray = 1044
		} PropertyType;

		typedef enum
		{
			UserAuthenticationStatus_Unauthenticated = 0,
			UserAuthenticationStatus_LocallyAuthenticated = 1,
			UserAuthenticationStatus_RemotelyAuthenticated = 2
		} UserAuthenticationStatus;

		typedef enum
		{
			UserType_LocalUser = 0,
			UserType_RemoteUser = 1,
			UserType_LocalGuest = 2,
			UserType_RemoteGuest = 3
		} UserType;

		typedef enum
		{
			UserPictureSize_Size64x64 = 0,
			UserPictureSize_Size208x208 = 1,
			UserPictureSize_Size424x424 = 2,
			UserPictureSize_Size1080x1080 = 3
		} UserPictureSize;

		// WinRT interfaces.

		#define DeviceInformationName (_T("Windows.Devices.Enumeration.DeviceInformation"))
		#define RadioName (_T("Windows.Devices.Radios.Radio"))
		#define DataWriterName (_T("Windows.Storage.Streams.DataWriter"))
		#define StreamSocketListenerName (_T("Windows.Networking.Sockets.StreamSocketListener"))
		#define UriRuntimeClassName (_T("Windows.Foundation.Uri"))
		#define PasswordCredentialFactoryName (_T("Windows.Security.Credentials.CredentialFactory"))
		#define PasswordCredentialName (_T("Windows.Security.Credentials.PasswordCredential"))
		#define PropertyValueName	(_T("Windows.Foundation.PropertyValue"))

		// Forward declarations.
		typedef interface IInspectable IInspectable;
		typedef interface IActivationFactory IActivationFactory;
		typedef interface IHSTRINGVectorView IHSTRINGVectorView;
		typedef interface IUInt32Reference IUInt32Reference;
		typedef interface IIntReference IIntReference;
		typedef interface IUInt64Reference IUInt64Reference;
		typedef interface IDateTimeReference IDateTimeReference;
		typedef interface ITimeSpanReference ITimeSpanReference;
		typedef interface IByteReference IByteReference;
		typedef interface IShortReference IShortReference;
		typedef interface IHSTRINGIterator IHSTRINGIterator;
		typedef interface IHSTRINGIterable IHSTRINGIterable;
		typedef interface IBuffer IBuffer;
		typedef interface IHSTRINGMapView IHSTRINGMapView;
		typedef interface IRandomAccessStreamWithContentType IRandomAccessStreamWithContentType;
		typedef interface IRandomAccessStreamWithContentTypeAsyncOperationCompletedHandler IRandomAccessStreamWithContentTypeAsyncOperationCompletedHandler;
		typedef interface IRandomAccessStreamWithContentTypeAsyncOperation IRandomAccessStreamWithContentTypeAsyncOperation;
		typedef interface IRandomAccessStreamReference IRandomAccessStreamReference;
		typedef interface IPropertySet IPropertySet;
		typedef interface IPropertyValue IPropertyValue;
		typedef interface IPropertyValueStatics IPropertyValueStatics;
		typedef interface IConnectionCost IConnectionCost;
		typedef interface IDataPlanUsage IDataPlanUsage;
		typedef interface IDataPlanStatus IDataPlanStatus;
		typedef interface IDataUsage IDataUsage;
		typedef interface INetworkSecuritySettings INetworkSecuritySettings;
		typedef interface IConnectionProfile IConnectionProfile;
		typedef interface IConnectionProfileAsyncOperation IConnectionProfileAsyncOperation;
		typedef interface IConnectionProfileAsyncOperationCompletedHandler IConnectionProfileAsyncOperationCompletedHandler;
		typedef interface INetworkItem INetworkItem;
		typedef interface INetworkAdapter INetworkAdapter;
		typedef interface IIPInformation IIPInformation;
		typedef interface IHostName IHostName;
		typedef interface IEndpointPair IEndpointPair;
		typedef interface IEndpointPairIterator IEndpointPairIterator;
		typedef interface IEndpointPairVectorView IEndpointPairVectorView;
		typedef interface IEnclosureLocation IEnclosureLocation;
		typedef interface IDeviceInformationUpdate IDeviceInformationUpdate;
		typedef interface IDeviceThumbnailAsyncOperationCompletedHandler IDeviceThumbnailAsyncOperationCompletedHandler;
		typedef interface IDeviceThumbnailAsyncOperation IDeviceThumbnailAsyncOperation;
		typedef interface IDeviceInformation IDeviceInformation;
		typedef interface IDeviceInformationAsyncOperationCompletedHandler IDeviceInformationAsyncOperationCompletedHandler;
		typedef interface IDeviceInformationAsyncOperation IDeviceInformationAsyncOperation;
		typedef interface IDeviceInformationCollectionAsyncOperationCompletedHandler IDeviceInformationCollectionAsyncOperationCompletedHandler;
		typedef interface IDeviceInformationVectorView IDeviceInformationVectorView;
		typedef interface IDeviceInformationCollectionAsyncOperation IDeviceInformationCollectionAsyncOperation;
		typedef interface IDeviceInformationEventHandler IDeviceInformationEventHandler;
		typedef interface IDeviceInformationUpdateEventHandler IDeviceInformationUpdateEventHandler;
		typedef interface IDeviceWatcherEventHandler IDeviceWatcherEventHandler;
		typedef interface IDeviceWatcher IDeviceWatcher;
		typedef interface IDeviceInformationStatics IDeviceInformationStatics;
		typedef interface IDeviceInformationStatics2 IDeviceInformationStatics2;
		typedef interface ICredentialFactory ICredentialFactory;
		typedef interface IPasswordCredential IPasswordCredential;
		typedef interface IDeferral IDeferral;
		typedef interface IHSTRINGVector IHSTRINGVector;
		typedef interface IAsyncAction IAsyncAction;
		typedef interface IAsyncActionCompletedHandler IAsyncActionCompletedHandler;
		typedef interface IBufferByteAccess IBufferByteAccess;
		typedef interface IAsyncInfo IAsyncInfo;
		typedef interface IBufferVectorView IBufferVectorView;
		typedef interface IUInt32BufferMapView IUInt32BufferMapView;
		typedef interface IRadioVectorView IRadioVectorView;
		typedef interface IRadioAsyncOperationCompletedHandler IRadioAsyncOperationCompletedHandler;
		typedef interface IRadioAccessStatusAsyncOperationCompletedHandler IRadioAccessStatusAsyncOperationCompletedHandler;
		typedef interface IRadioEventHandler IRadioEventHandler;
		typedef interface IRadioStaticsAsyncOperationCompletedHandler IRadioStaticsAsyncOperationCompletedHandler;
		typedef interface IRadioAsyncOperation IRadioAsyncOperation;
		typedef interface IRadioAccessStatusAsyncOperation IRadioAccessStatusAsyncOperation;
		typedef interface IRadioStaticsAsyncOperation IRadioStaticsAsyncOperation;
		typedef interface IRadio IRadio;
		typedef interface IRadioStatics IRadioStatics;
		typedef interface IDeviceAccessChangedEventArgs IDeviceAccessChangedEventArgs;
		typedef interface IDeviceAccessInformationEventHandler IDeviceAccessInformationEventHandler;
		typedef interface IDeviceAccessInformation IDeviceAccessInformation;
		typedef interface IDeviceAccessStatusAsyncOperationCompletedHandler IDeviceAccessStatusAsyncOperationCompletedHandler;
		typedef interface IDeviceAccessStatusAsyncOperation IDeviceAccessStatusAsyncOperation;
		typedef interface IDataWriter IDataWriter;
		typedef interface IBufferAsyncOperationProgressHandler IBufferAsyncOperationProgressHandler;
		typedef interface IBufferAsyncOperationWithProgressCompletedHandler IBufferAsyncOperationWithProgressCompletedHandler;
		typedef interface IStreamAsyncOperationWithProgress IStreamAsyncOperationWithProgress;
		typedef interface IInputStream IInputStream;
		typedef interface IUint32AsyncOperationProgressHandler IUint32AsyncOperationProgressHandler;
		typedef interface IUInt32AsyncOperationWithProgressCompletedHandler IUInt32AsyncOperationWithProgressCompletedHandler;
		typedef interface IUint32AsyncOperationWithProgress IUint32AsyncOperationWithProgress;
		typedef interface IInspectableEventHandler IInspectableEventHandler;
		typedef interface IGuidAsyncOperationCompletedHandler IGuidAsyncOperationCompletedHandler;
		typedef interface IGuidAsyncOperation IGuidAsyncOperation;
		typedef interface IBooleanAsyncOperationCompletedHandler IBooleanAsyncOperationCompletedHandler;
		typedef interface IBooleanAsyncOperation IBooleanAsyncOperation;
		typedef interface IOutputStream IOutputStream;
		typedef interface IStreamSocketListenerControl IStreamSocketListenerControl;
		typedef interface IStreamSocketListenerControl2 IStreamSocketListenerControl2;
		typedef interface IStreamSocketListenerInformation IStreamSocketListenerInformation;
		typedef interface IStreamSocketControl IStreamSocketControl;
		typedef interface IStreamSocketInformation IStreamSocketInformation;
		typedef interface IStreamSocket IStreamSocket;
		typedef interface IStreamSocket2 IStreamSocket2;
		typedef interface ISocketActivityContext ISocketActivityContext;
		typedef interface IStreamSocket3 IStreamSocket3;
		typedef interface IStreamSocketListenerConnectionReceivedEventArgs IStreamSocketListenerConnectionReceivedEventArgs;
		typedef interface IStreamSocketListenerConnectionReceivedEventHandler IStreamSocketListenerConnectionReceivedEventHandler;
		typedef interface IStreamSocketListener IStreamSocketListener;
		typedef interface IStreamSocketListener2 IStreamSocketListener2;
		typedef interface IStreamSocketListener3 IStreamSocketListener3;
		typedef interface IDeviceInformationPairing IDeviceInformationPairing;
		typedef interface IDeviceInformation2 IDeviceInformation2;
		typedef interface IDevicePairingSettings IDevicePairingSettings;
		typedef interface IDeviceInformationCustomPairing IDeviceInformationCustomPairing;
		typedef interface IDeviceInformationPairing2 IDeviceInformationPairing2;
		typedef interface IGUIDVectorView IGUIDVectorView;
		typedef interface IGUIDVector IGUIDVector;
		typedef interface IDevicePairingResultAsyncOperationCompletedHandler IDevicePairingResultAsyncOperationCompletedHandler;
		typedef interface IDevicePairingRequestedEventHandler IDevicePairingRequestedEventHandler;
		typedef interface IDeviceUnpairingResultAsyncOperationCompletedHandler IDeviceUnpairingResultAsyncOperationCompletedHandler;
		typedef interface IDevicePairingResultAsyncOperation IDevicePairingResultAsyncOperation;
		typedef interface IDeviceUnpairingResultAsyncOperation IDeviceUnpairingResultAsyncOperation;
		typedef interface IDevicePairingResult IDevicePairingResult;
		typedef interface IDeviceUnpairingResult IDeviceUnpairingResult;
		typedef interface IDevicePairingRequestedEventArgs IDevicePairingRequestedEventArgs;
		typedef interface IClosable IClosable;
		typedef interface IUriRuntimeClass IUriRuntimeClass;
		typedef interface IWwwFormUrlDecoderRuntimeClass IWwwFormUrlDecoderRuntimeClass;
		typedef interface IAdaptiveCard IAdaptiveCard;
		typedef interface IWebAccount IWebAccount;
		typedef interface IWebAccountProvider IWebAccountProvider;
		typedef interface IUriRuntimeClassFactory IUriRuntimeClassFactory;
		typedef interface IHostNameVectorView IHostNameVectorView;
		typedef interface IHSTRINGInspectableKeyValuePairIterator IHSTRINGInspectableKeyValuePairIterator;
		typedef interface IHSTRINGInspectableKeyValuePairIterable IHSTRINGInspectableKeyValuePairIterable;
		typedef interface IHSTRINGInspectableKeyValuePair IHSTRINGInspectableKeyValuePair;
		typedef interface IUint32AsyncOperationCompletedHandler IUint32AsyncOperationCompletedHandler;
		typedef interface IUint32AsyncOperation IUint32AsyncOperation;
		typedef interface IInspectableAsyncOperationCompletedHandler IInspectableAsyncOperationCompletedHandler;
		typedef interface IInspectableAsyncOperation IInspectableAsyncOperation;
		typedef interface IPropertySetAsyncOperationCompletedHandler IPropertySetAsyncOperationCompletedHandler;
		typedef interface IPropertySetAsyncOperation IPropertySetAsyncOperation;
		typedef interface IRandomAccessStreamReferenceAsyncOperationCompletedHandler IRandomAccessStreamReferenceAsyncOperationCompletedHandler;
		typedef interface IRandomAccessStreamReferenceAsyncOperation IRandomAccessStreamReferenceAsyncOperation;
		typedef interface IUser IUser;

		MIDL_INTERFACE("AF86E2E0-B12D-4c6a-9C5A-D7AA65101E90")
		IInspectable : public  IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetIids(DWORD* iidCount, GUID** iids) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(HSTRING* className) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel* trust) = 0;
		};

		MIDL_INTERFACE("00000035-0000-0000-C000-000000000046")
		IActivationFactory : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ActivateInstance(IInspectable** instance) = 0;
		};

		MIDL_INTERFACE("2f13c006-a03a-5f69-b090-75a43e33423e")
		IHSTRINGVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, HSTRING* item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(HSTRING item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity, HSTRING* items,
				DWORD* actual) = 0;
		};

		MIDL_INTERFACE("513ef3af-e784-5325-a91e-97c2b8111cf3")
		IUInt32Reference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(DWORD* value) = 0;
		};

		MIDL_INTERFACE("548cefbd-bc8a-5fa0-8df2-957440fc8bf4")
		IIntReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(int* value) = 0;
		};

		MIDL_INTERFACE("6755e376-53bb-568b-a11d-17239868309e")
		IUInt64Reference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(__int64* value) = 0;
		};

		MIDL_INTERFACE("5541d8a7-497c-5aa4-86fc-7713adbf2a2c")
		IDateTimeReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(DateTime* value) = 0;
		};

		MIDL_INTERFACE("604d0c4c-91de-5c2a-935f-362f13eaf800")
		ITimeSpanReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(TimeSpan* value) = 0;
		};

		MIDL_INTERFACE("e5198cc8-2873-55f5-b0a1-84ff9e4aad62")
		IByteReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(BYTE* value) = 0;
		};

		MIDL_INTERFACE("6ec9e41b-6709-5647-9918-a1270110fc4e")
		IShortReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Value(short* value) = 0;
		};

		MIDL_INTERFACE("33ee3134-1dd6-4e3a-8067-d1c162e8642b")
		IRandomAccessStreamReference : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE OpenReadAsync(
				IRandomAccessStreamWithContentTypeAsyncOperation** operation) = 0;
		};

		MIDL_INTERFACE("8c304ebb-6615-50a4-8829-879ecd443236")
		IHSTRINGIterator : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Current(HSTRING* current) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_HasCurrent(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveNext(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD capacity, HSTRING* items,
				DWORD* actual) = 0;
		};

		MIDL_INTERFACE("5db5fa32-707c-5849-a06b-91c8eb9d10e8")
		IHSTRINGInspectableKeyValuePairIterator : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Current(IHSTRINGInspectableKeyValuePair** current) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_HasCurrent(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveNext(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD capacity,
				IHSTRINGInspectableKeyValuePair** items, DWORD* actual) = 0;
		};

		MIDL_INTERFACE("e2fcc7c1-3bfc-5a0b-b2b0-72e769d1cb7e")
		IHSTRINGIterable : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE First(IHSTRINGIterator** first) = 0;
		};

		MIDL_INTERFACE("fe2f3d47-5d47-5499-8374-430c7cda0204")
		IHSTRINGInspectableKeyValuePairIterable : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE First(IHSTRINGInspectableKeyValuePairIterator** first) = 0;
		};

		MIDL_INTERFACE("905A0FE0-BC53-11DF-8C49-001E4FC686DA")
		IBuffer : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Capacity(DWORD* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Length(DWORD* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_Length(DWORD value) = 0;
		};

		MIDL_INTERFACE("bb78502a-f79d-54fa-92c9-90c5039fdf7e")
		IHSTRINGMapView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Lookup(HSTRING key, IInspectable** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE HasKey(HSTRING key, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE Split(IHSTRINGMapView** firstPartition, IHSTRINGMapView** secondPartition) = 0;
		};

		MIDL_INTERFACE("CC254827-4B3D-438F-9232-10C76BC7E038")
		IRandomAccessStreamWithContentType : public IInspectable
		{
		public:
		};

		MIDL_INTERFACE("3dddecf4-1d39-58e8-83b1-dbed541c7f35")
		IRandomAccessStreamWithContentTypeAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRandomAccessStreamWithContentTypeAsyncOperation* asyncInfo,
				AsyncStatus asyncStatus) = 0;
		};

		MIDL_INTERFACE("c4a57c5e-32b0-55b3-ad13-ce1c23041ed6")
		IRandomAccessStreamWithContentTypeAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IRandomAccessStreamWithContentTypeAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IRandomAccessStreamWithContentTypeAsyncOperationCompletedHandler** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(
				IRandomAccessStreamWithContentType** result) = 0;
		};

		MIDL_INTERFACE("8A43ED9F-F4E6-4421-ACF9-1DAB2986820C")
		IPropertySet : public IInspectable
		{
		public:
		};

		MIDL_INTERFACE("09335560-6c6b-5a26-9348-97b781132b20")
		IHSTRINGInspectableKeyValuePair : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Key(HSTRING* key) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Value(IInspectable** value) = 0;
		};

		MIDL_INTERFACE("9343b6e7-e3d2-5e4a-ab2d-2bce4919a6a4")
		IUint32AsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IUint32AsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("ef60385f-be78-584b-aaef-7829ada2b0de")
		IUint32AsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IUint32AsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IUint32AsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(UINT32* results) = 0;
		};

		MIDL_INTERFACE("3f08262e-a2e1-5134-9297-e9211f481a2d")
		IInspectableAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IInspectableAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("abf53c57-ee50-5342-b52a-26e3b8cc024f")
		IInspectableAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IInspectableAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IInspectableAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IInspectable** results) = 0;
		};

		MIDL_INTERFACE("5075a55f-68ba-56f2-97e6-9b1cbfa2c5f2")
		IPropertySetAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IPropertySetAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("490b0686-afd7-5037-9647-d8fe248f182c")
		IPropertySetAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IPropertySetAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IPropertySetAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IPropertySet** results) = 0;
		};

		MIDL_INTERFACE("60847289-ea0b-5df6-89df-f2c62cba9693")
		IRandomAccessStreamReferenceAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRandomAccessStreamReferenceAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("65178d50-e6a2-5d16-b244-65e9725e5a0c")
		IRandomAccessStreamReferenceAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IRandomAccessStreamReferenceAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IRandomAccessStreamReferenceAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IRandomAccessStreamReference** results) = 0;
		};

		MIDL_INTERFACE("DF9A26C6-E746-4BCD-B5D4-120103C4209B")
		IUser : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NonRoamableId(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_AuthenticationStatus(
				UserAuthenticationStatus* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Type(UserType* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPropertyAsync(HSTRING value,
				IInspectableAsyncOperation** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPropertiesAsync(IHSTRINGVectorView* values,
				IPropertySetAsyncOperation** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPictureAsync(UserPictureSize* desiredSize,
				IRandomAccessStreamReferenceAsyncOperation** operation) = 0;
		};

		MIDL_INTERFACE("4BD682DD-7554-40E9-9A9B-82654EDE7E62")
		IPropertyValue : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Type(PropertyType* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsNumericScalar(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt8(BYTE* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt16(INT16* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt16(UINT16* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt32(INT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt32(UINT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt64(INT64* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt64(UINT64* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSingle(FLOAT* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDouble(DOUBLE* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChar16(WCHAR* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetBoolean(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetString(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetGuid(GUID* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDateTime(DateTime* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetTimeSpan(TimeSpan* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPoint(Point* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSize(Size* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetRect(Rect* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt8Array(UINT32* __valueSize, BYTE** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt16Array(UINT32* __valueSize, INT16** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt16Array(UINT32* __valueSize, UINT16** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt32Array(UINT32* __valueSize, INT32** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt32Array(UINT32* __valueSize, UINT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInt64Array(UINT32* __valueSize, INT64** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetUInt64Array(UINT32* __valueSize, UINT64** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSingleArray(UINT32* __valueSize, FLOAT** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDoubleArray(UINT32* __valueSize, DOUBLE** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChar16Array(UINT32* __valueSize, WCHAR** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetBooleanArray(UINT32* __valueSize, BOOLEAN** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetStringArray(UINT32* __valueSize, HSTRING** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetInspectableArray(UINT32* __valueSize, IInspectable** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetGuidArray(UINT32* __valueSize, GUID** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDateTimeArray(UINT32* __valueSize, DateTime** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetTimeSpanArray(UINT32* __valueSize, TimeSpan** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPointArray(UINT32* __valueSize, Point** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSizeArray(UINT32* __valueSize, Size** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetRectArray(UINT32* __valueSize, Rect** value) = 0;
		};

		MIDL_INTERFACE("629BDBC8-D932-4FF4-96B9-8D96C5C1E858")
		IPropertyValueStatics : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CreateEmpty(IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt8(BYTE value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt16(INT16 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt16(UINT16 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt32(INT32 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt32(UINT32 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt64(INT64 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt64(UINT64 value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateSingle(FLOAT value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateDouble(DOUBLE value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateChar16(WCHAR value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateBoolean(BOOLEAN value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateString(HSTRING value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInspectable(IInspectable* value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateGuid(GUID value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateDateTime(DateTime value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateTimeSpan(TimeSpan value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreatePoint(Point value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateSize(Size value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateRect(Rect value,
				IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt8Array(UINT32 __valueSize,
				BYTE* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt16Array(UINT32 __valueSize,
				INT16* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt16Array(UINT32 __valueSize,
				UINT16* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt32Array(UINT32 __valueSize,
				INT32* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt32Array(UINT32 __valueSize,
				UINT32* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInt64Array(UINT32 __valueSize,
				INT64* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateUInt64Array(UINT32 __valueSize,
				UINT64* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateSingleArray(UINT32 __valueSize,
				FLOAT* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateDoubleArray(UINT32 __valueSize,
				DOUBLE* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateChar16Array(UINT32 __valueSize,
				WCHAR* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateBooleanArray(UINT32 __valueSize,
				BOOLEAN* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateStringArray(UINT32 __valueSize,
				HSTRING* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateInspectableArray(UINT32 __valueSize,
				IInspectable** value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateGuidArray(UINT32 __valueSize,
				GUID* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateDateTimeArray(UINT32 __valueSize,
				DateTime* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateTimeSpanArray(UINT32 __valueSize,
				TimeSpan* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreatePointArray(UINT32 __valueSize,
				Point* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateSizeArray(UINT32 __valueSize,
				Size* value, IInspectable** propertyValue) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateRectArray(UINT32 __valueSize,
				Rect* value, IInspectable** propertyValue) = 0;
		};

		MIDL_INTERFACE("BAD7D829-3416-4B10-A202-BAC0B075BDAE")
		IConnectionCost : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NetworkCostType(NetworkCostType* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Roaming(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OverDataLimit(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ApproachingDataLimit(BOOLEAN* value) = 0;
		};

		MIDL_INTERFACE("B921492D-3B44-47FF-B361-BE59E69ED1B0")
		IDataPlanUsage : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_MegabytesUsed(DWORD* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_LastSyncTime(DateTime* value) = 0;
		};

		MIDL_INTERFACE("977A8B8C-3885-40F3-8851-42CD2BD568BB")
		IDataPlanStatus : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_DataPlanUsage(IDataPlanUsage** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DataLimitInMegabytes(IUInt32Reference** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_InboundBitsPerSecond(IUInt64Reference** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutboundBitsPerSecond(IUInt64Reference** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NextBillingCycle(IDateTimeReference** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_MaxTransferSizeInMegabytes(IUInt32Reference** value) = 0;
		};

		MIDL_INTERFACE("C1431DD3-B146-4D39-B959-0C69B096C512")
		IDataUsage : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_BytesSent(__int64* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_BytesReceived(__int64* value) = 0;
		};

		MIDL_INTERFACE("7CA07E8D-917B-4B5F-B84D-28F7A5AC5402")
		INetworkSecuritySettings : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NetworkAuthenticationType(NetworkAuthenticationType* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NetworkEncryptionType(NetworkEncryptionType* value) = 0;
		};

		MIDL_INTERFACE("71BA143C-598E-49D0-84EB-8FEBAEDCC195")
		IConnectionProfile : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_ProfileName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkConnectivityLevel(NetworkConnectivityLevel* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkNames(IHSTRINGVectorView** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectionCost(IConnectionCost** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDataPlanStatus(IDataPlanStatus** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NetworkAdapter(INetworkAdapter** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetLocalUsage(DateTime StartTime, DateTime EndTime, IDataUsage** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetLocalUsagePerRoamingStates(DateTime StartTime, DateTime EndTime,
				RoamingStates States, IDataUsage** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NetworkSecuritySettings(INetworkSecuritySettings** value) = 0;
		};

		MIDL_INTERFACE("5bf519ca-8adb-5ab5-abb8-ff1bbe5d2de8")
		IConnectionProfileAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IConnectionProfileAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IConnectionProfileAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IConnectionProfile** results) = 0;
		};

		MIDL_INTERFACE("e4f0c96a-0571-59f4-a9a9-afac3e61caa0")
		IConnectionProfileAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IConnectionProfileAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("01BC4D39-F5E0-4567-A28C-42080C831B2B")
		INetworkItem : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NetworkId(GUID* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkTypes(NetworkTypes* value) = 0;
		};

		MIDL_INTERFACE("3B542E03-5388-496C-A8A3-AFFD39AEC2E6")
		INetworkAdapter : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_OutboundMaxBitsPerSecond(__int64* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_InboundMaxBitsPerSecond(__int64* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IanaInterfaceType(DWORD* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NetworkItem(INetworkItem** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_NetworkAdapterId(GUID* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectedProfileAsync(IConnectionProfileAsyncOperation** value) = 0;
		};

		MIDL_INTERFACE("D85145E0-138F-47D7-9B3A-36BB488CEF33")
		IIPInformation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NetworkAdapter(INetworkAdapter** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_PrefixLength(IByteReference** value) = 0;
		};

		MIDL_INTERFACE("BF8ECAAD-ED96-49A7-9084-D416CAE88DCB")
		IHostName : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_IPInformation(IIPInformation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RawName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DisplayName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_CanonicalName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Type(HostNameType* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsEqual(IHostName* hostName, BOOLEAN* isEqual) = 0;
		};

		MIDL_INTERFACE("33A0AA36-F8FA-4B30-B856-76517C3BD06D")
		IEndpointPair : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_LocalHostName(IHostName** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_LocalHostName(IHostName* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_LocalServiceName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_LocalServiceName(HSTRING value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemoteHostName(IHostName** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_RemoteHostName(IHostName* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemoteServiceName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_RemoteServiceName(HSTRING value) = 0;
		};

		MIDL_INTERFACE("c899ff9f-e6f5-5673-810c-04e2ff98704f")
		IEndpointPairIterator : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Current(IEndpointPair** current) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_HasCurrent(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE MoveNext(BOOLEAN* hasCurrent) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD capacity, IEndpointPair** items, DWORD* actual) = 0;
		};

		MIDL_INTERFACE("8780a851-6d48-5006-9288-81f3d7045a96")
		IEndpointPairVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, IEndpointPair** item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(IEndpointPair* item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity, IEndpointPair** items,
				DWORD* actual) = 0;
		};

		MIDL_INTERFACE("42340A27-5810-459C-AABB-C65E1F813ECF")
		IEnclosureLocation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_InDock(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_InLid(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Panel(Panel* value) = 0;
		};

		MIDL_INTERFACE("8F315305-D972-44B7-A37E-9E822C78213B")
		IDeviceInformationUpdate : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Id(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Properties(IHSTRINGMapView** value) = 0;
		};

		MIDL_INTERFACE("86d455b2-d795-554c-9c31-bf6539349c19")
		IDeviceThumbnailAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceThumbnailAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("bac083a3-3a19-5072-9d90-133323a049ba")
		IDeviceThumbnailAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(IDeviceThumbnailAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(IDeviceThumbnailAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IRandomAccessStreamWithContentType** results) = 0;
		};

		MIDL_INTERFACE("ABA0FB95-4398-489D-8E44-E6130927011F")
		IDeviceInformation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Id(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Name(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsEnabled(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsDefault(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_EnclosureLocation(IEnclosureLocation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Properties(IHSTRINGMapView** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE Update(IDeviceInformationUpdate* updateInfo) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetThumbnailAsync(IDeviceThumbnailAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetGlyphThumbnailAsync(IDeviceThumbnailAsyncOperation** asyncOp) = 0;
		};

		MIDL_INTERFACE("bb483df2-7bb6-5923-a28d-8342ec30046b")
		IDeviceInformationAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceInformationAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("07faa053-eb2f-5cba-b25b-d9d57be6715f")
		IDeviceInformationAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IDeviceInformationAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IDeviceInformationAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IDeviceInformation** results) = 0;
		};

		MIDL_INTERFACE("4a458732-527e-5c73-9a68-a73da370f782")
		IDeviceInformationCollectionAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceInformationCollectionAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("e170688f-3495-5bf6-aab5-9cac17e0f10f")
		IDeviceInformationVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, IDeviceInformation** item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(IDeviceInformation* item, DWORD* index,
				BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				IDeviceInformation** items, DWORD* actual) = 0;
		};

		MIDL_INTERFACE("45180254-082e-5274-b2e7-ac0517f44d07")
		IDeviceInformationCollectionAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IDeviceInformationCollectionAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IDeviceInformationCollectionAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IDeviceInformationVectorView** results) = 0;
		};

		MIDL_INTERFACE("03c5a07b-990c-5d09-b0b8-5734eaa38222")
		IDeviceInformationEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceWatcher* sender, IDeviceInformation* e) = 0;
		};

		MIDL_INTERFACE("906f1254-79ad-54fc-93c4-cdb99b437899")
		IDeviceInformationUpdateEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceWatcher* sender, IDeviceInformationUpdate* e) = 0;
		};

		MIDL_INTERFACE("9234630f-1ff4-54f6-9e3f-ac20369b7725")
		IDeviceWatcherEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceWatcher* sender, IInspectable* e) = 0;
		};

		MIDL_INTERFACE("C9EAB97D-8F6B-4F96-A9F4-ABC814E22271")
		IDeviceWatcher : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE add_Added(IDeviceInformationEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_Added(EventRegistrationToken token) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_Updated(IDeviceInformationUpdateEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_Updated(EventRegistrationToken token) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_Removed(IDeviceInformationUpdateEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_Removed(EventRegistrationToken token) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_EnumerationCompleted(IDeviceWatcherEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_EnumerationCompleted(EventRegistrationToken token) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_Stopped(IDeviceWatcherEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_Stopped(EventRegistrationToken token) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Status(DeviceWatcherStatus* status) = 0;
			virtual HRESULT STDMETHODCALLTYPE Start() = 0;
			virtual HRESULT STDMETHODCALLTYPE Stop() = 0;
		};

		MIDL_INTERFACE("C17F100E-3A46-4A78-8013-769DC9B97390")
		IDeviceInformationStatics : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CreateFromIdAsync(HSTRING deviceId,
				IDeviceInformationAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateFromIdAsyncAdditionalProperties(HSTRING deviceId,
				IHSTRINGIterable* additionalProperties, IDeviceInformationAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindAllAsync(
				IDeviceInformationCollectionAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindAllAsyncDeviceClass(DeviceClass deviceClass,
				IDeviceInformationCollectionAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindAllAsyncAqsFilter(HSTRING aqsFilter,
				IDeviceInformationCollectionAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindAllAsyncAqsFilterAndAdditionalProperties(HSTRING aqsFilter,
				IHSTRINGIterable* additionalProperties, IDeviceInformationCollectionAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWatcher(IDeviceWatcher** watcher) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWatcherDeviceClass(DeviceClass deviceClass,
				IDeviceWatcher** watcher) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWatcherAqsFilter(HSTRING aqsFilter,
				IDeviceWatcher** watcher) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWatcherAqsFilterAndAdditionalProperties(HSTRING aqsFilter,
				IHSTRINGIterable* additionalProperties, IDeviceWatcher** watcher) = 0;
		};

		MIDL_INTERFACE("493B4F34-A84F-45FD-9167-15D1CB1BD1F9")
		IDeviceInformationStatics2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAqsFilterFromDeviceClass(DeviceClass deviceClass,
				HSTRING* aqsFilter) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateFromIdAsyncWithKindAndAdditionalProperties(
				HSTRING deviceId, IHSTRINGIterable* additionalProperties, DeviceInformationKind kind,
				IDeviceInformationAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE FindAllAsyncWithKindAqsFilterAndAdditionalProperties(
				HSTRING aqsFilter, IHSTRINGIterable* additionalProperties, DeviceInformationKind kind,
				IDeviceInformationCollectionAsyncOperation** asyncOp) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWatcherWithKindAqsFilterAndAdditionalProperties(
				HSTRING aqsFilter, IHSTRINGIterable* additionalProperties, DeviceInformationKind kind,
				IDeviceWatcher** watcher) = 0;
		};

		MIDL_INTERFACE("54EF13A1-BF26-47B5-97DD-DE779B7CAD58")
		ICredentialFactory : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CreatePasswordCredential(HSTRING resource, HSTRING userName,
				HSTRING password, IPasswordCredential** credential) = 0;
		};

		MIDL_INTERFACE("6AB18989-C720-41A7-A6C1-FEADB36329A0")
		IPasswordCredential : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Resource(HSTRING* resource) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_Resource(HSTRING resource) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_UserName(HSTRING* userName) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_UserName(HSTRING userName) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Password(HSTRING* password) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_Password(HSTRING password) = 0;
			virtual HRESULT STDMETHODCALLTYPE RetrievePassword() = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Properties(IPropertySet** props) = 0;
		};

		MIDL_INTERFACE("D6269732-3B7F-46A7-B40B-4FDCA2A2C693")
		IDeferral : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Complete() = 0;
		};

		MIDL_INTERFACE("98b9acc1-4b56-532e-ac73-03d5291cca90")
		IHSTRINGVector : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, HSTRING* item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetView(IHSTRINGVectorView** view) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(HSTRING item, DWORD* index,
				BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAt(DWORD index, HSTRING item) = 0;
			virtual HRESULT STDMETHODCALLTYPE InsertAt(DWORD index, HSTRING item) = 0;
			virtual HRESULT STDMETHODCALLTYPE RemoveAt(DWORD index) = 0;
			virtual HRESULT STDMETHODCALLTYPE Append(HSTRING item) = 0;
			virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd() = 0;
			virtual HRESULT STDMETHODCALLTYPE Clear() = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				HSTRING* items, DWORD* actual) = 0;
			virtual HRESULT STDMETHODCALLTYPE ReplaceAll(DWORD count, HSTRING* value) = 0;
		};

		MIDL_INTERFACE("5A648006-843A-4DA9-865B-9D26E5DFAD7B")
		IAsyncAction : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IAsyncActionCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IAsyncActionCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults() = 0;
		};

		MIDL_INTERFACE("A4ED5C81-76C9-40BD-8BE6-B1D90FB20AE7")
		IAsyncActionCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IAsyncAction* asyncInfo,
				AsyncStatus asyncStatus) = 0;
		};

		MIDL_INTERFACE("905a0fef-bc53-11df-8c49-001e4fc686da")
		IBufferByteAccess : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Buffer(BYTE** value) = 0;
		};

		MIDL_INTERFACE("00000036-0000-0000-C000-000000000046")
		IAsyncInfo : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Id(DWORD* id) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Status(AsyncStatus* status) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ErrorCode(HRESULT* errorCode) = 0;
			virtual HRESULT STDMETHODCALLTYPE Cancel() = 0;
			virtual HRESULT STDMETHODCALLTYPE Close() = 0;
		};

		MIDL_INTERFACE("fd944562-11d6-5eab-bd72-701993b68fac")
		IBufferVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, IBuffer** item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(IBuffer* item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				IBuffer** items, DWORD* actual)= 0;
		};

		MIDL_INTERFACE("57dc41e6-8b4d-5910-9703-d7c668436852")
		IUInt32BufferMapView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Lookup(UINT32 key, IBuffer** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE HasKey(UINT32 key, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE Split(IUInt32BufferMapView** firstPartition,
				IUInt32BufferMapView** secondPartition) = 0;
		};

		MIDL_INTERFACE("65066c36-090b-5466-b8e5-e7565dc34175")
		IRadioVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, IRadio** item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(IRadio* item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				IRadio** items, DWORD* actual) = 0;
		};

		MIDL_INTERFACE("8a5c7e3a-80e2-585b-8630-7a8e777f0354")
		IRadioAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRadioAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("bd248e73-f05f-574c-ae3d-9b95c4bf282a")
		IRadioAccessStatusAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRadioAccessStatusAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("fc6aa329-b586-5ebb-9e85-3f6b84ebdf18")
		IRadioEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRadio* sender, IInspectable* e) = 0;
		};

		MIDL_INTERFACE("d30691e6-60a0-59c9-8965-5bbe282e8208")
		IRadioStaticsAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IRadioStaticsAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("eac62c40-8dbc-5854-8ba0-b7b9940e7389")
		IRadioAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(IRadioAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(IRadioAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IRadio** results) = 0;
		};

		MIDL_INTERFACE("21fb30ef-072f-502c-9898-d0c3b2cd9ac5")
		IRadioAccessStatusAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IRadioAccessStatusAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IRadioAccessStatusAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(RadioAccessStatus* results) = 0;
		};

		MIDL_INTERFACE("040b54a1-203e-58f5-943f-c1cca86bd532")
		IRadioStaticsAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IRadioStaticsAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IRadioStaticsAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IRadioVectorView** results) = 0;
		};

		MIDL_INTERFACE("252118DF-B33E-416A-875F-1CF38AE2D83E")
		IRadio : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetStateAsync(RadioState value,
				IRadioAccessStatusAsyncOperation** retval) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_StateChanged(IRadioEventHandler* handler,
				EventRegistrationToken* eventCookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_StateChanged(EventRegistrationToken eventCookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_State(RadioState* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Name(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Kind(RadioKind* value) = 0;
		};

		MIDL_INTERFACE("5FB6A12E-67CB-46AE-AAE9-65919F86EFF4")
		IRadioStatics : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetRadiosAsync(
				IRadioStaticsAsyncOperation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeviceSelector(HSTRING* deviceSelector) = 0;
			virtual HRESULT STDMETHODCALLTYPE FromIdAsync(HSTRING deviceId,
				IRadioAsyncOperation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE RequestAccessAsync(
				IRadioAccessStatusAsyncOperation** value) = 0;
		};

		MIDL_INTERFACE("DEDA0BCC-4F9D-4F58-9DBA-A9BC800408D5")
		IDeviceAccessChangedEventArgs : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Status(DeviceAccessStatus* value) = 0;
		};

		MIDL_INTERFACE("4c71d028-b793-5bce-ae59-fa77f45a40d8")
		IDeviceAccessInformationEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceAccessInformation* sender,
				IDeviceAccessChangedEventArgs* e) = 0;
		};

		MIDL_INTERFACE("0BAA9A73-6DE5-4915-8DDD-9A0554A6F545")
		IDeviceAccessInformation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE add_AccessChanged(
				IDeviceAccessInformationEventHandler* handler,
				EventRegistrationToken* cookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_AccessChanged(
				EventRegistrationToken cookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_CurrentStatus(DeviceAccessStatus* status) = 0;
		};

		MIDL_INTERFACE("ee154d83-805b-53e8-8469-90715036d013")
		IDeviceAccessStatusAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceAccessStatusAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("c00bc2f2-a7f8-5f3f-80d1-2808ef6bca10")
		IDeviceAccessStatusAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IDeviceAccessStatusAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IDeviceAccessStatusAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(DeviceAccessStatus* results) = 0;
		};

		MIDL_INTERFACE("64B89265-D341-4922-B38A-DD4AF8808C4E")
		IDataWriter : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_UnstoredBufferLength(UINT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_UnicodeEncoding(UnicodeEncoding* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_UnicodeEncoding(UnicodeEncoding value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ByteOrder(ByteOrder* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_ByteOrder(ByteOrder value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteByte(BYTE value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteBytes(UINT32 __valueSize, BYTE* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteBuffer(IBuffer* buffer) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteBufferRange(IBuffer* buffer, UINT32 start,
				UINT32 count) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteBoolean(BOOLEAN value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteGuid(GUID value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteInt16(INT16 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteInt32(INT32 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteInt64(INT64 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteUInt16(UINT16 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteUInt32(UINT32 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteUInt64(UINT64 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteSingle(FLOAT value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteDouble(DOUBLE value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteDateTime(DateTime value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteTimeSpan(TimeSpan value) = 0;
			virtual HRESULT STDMETHODCALLTYPE WriteString(HSTRING value, UINT32* codeUnitCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE MeasureString(HSTRING value, UINT32* codeUnitCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE StoreAsync(void** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE FlushAsync(void** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE DetachBuffer(IBuffer** buffer) = 0;
			virtual HRESULT STDMETHODCALLTYPE DetachStream(void** outputStream) = 0;
		};

		MIDL_INTERFACE("bf666554-7605-5d9a-b14e-18d8c8472afe")
		IBufferAsyncOperationProgressHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IStreamAsyncOperationWithProgress* asyncInfo,
				UINT32 progressInfo) = 0;
		};

		MIDL_INTERFACE("06386a7a-e009-5b0b-ab68-a8e48b516647")
		IBufferAsyncOperationWithProgressCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IStreamAsyncOperationWithProgress* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("d26b2819-897f-5c7d-84d6-56d796561431")
		IStreamAsyncOperationWithProgress : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Progress(
				IBufferAsyncOperationProgressHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Progress(
				IBufferAsyncOperationProgressHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IBufferAsyncOperationWithProgressCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IBufferAsyncOperationWithProgressCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IBuffer** results) = 0;
		};

		MIDL_INTERFACE("905A0FE2-BC53-11DF-8C49-001E4FC686DA")
		IInputStream : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ReadAsync(IBuffer* buffer, UINT32 count,
				InputStreamOptions options, IStreamAsyncOperationWithProgress** operation) = 0;
		};

		MIDL_INTERFACE("ea0fe405-d432-5ac7-9ef8-5a65e1f97d7e")
		IUint32AsyncOperationProgressHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IUint32AsyncOperationWithProgress* asyncInfo,
				UINT32 progressInfo) = 0;
		};

		MIDL_INTERFACE("1e466dc5-840f-54f9-b877-5e3a9f4b6c74")
		IUInt32AsyncOperationWithProgressCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IUint32AsyncOperationWithProgress* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("eccb574a-c684-5572-a679-6b0842cfb57f")
		IUint32AsyncOperationWithProgress : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Progress(IUint32AsyncOperationProgressHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Progress(IUint32AsyncOperationProgressHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IUInt32AsyncOperationWithProgressCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IUInt32AsyncOperationWithProgressCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(UINT32* results) = 0;
		};

		MIDL_INTERFACE("c50898f6-c536-5f47-8583-8b2c2438a13b")
		IInspectableEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IInspectable* sender,
				IInspectable* args) = 0;
		};

		MIDL_INTERFACE("5233899b-ba7e-504f-bb83-ceebac62decf")
		IGuidAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IGuidAsyncOperationCompletedHandler* asyncInfo,
				AsyncStatus asyncStatus) = 0;
		};

		MIDL_INTERFACE("6607bc41-294b-5975-9c3f-4b49836d0916")
		IGuidAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IGuidAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IGuidAsyncOperationCompletedHandler** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(GUID* result) = 0;
		};

		MIDL_INTERFACE("c1d3d1a2-ae17-5a5f-b5a2-bdcc8844889a")
		IBooleanAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IBooleanAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("cdb5efb3-5788-509d-9be1-71ccb8a3362a")
		IBooleanAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(IBooleanAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(IBooleanAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(BOOLEAN* results) = 0;
		};

		MIDL_INTERFACE("905A0FE6-BC53-11DF-8C49-001E4FC686DA")
		IOutputStream : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE WriteAsync(IBuffer* buffer,
				IUint32AsyncOperationWithProgress** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE FlushAsync(IBooleanAsyncOperation** operation) = 0;
		};

		MIDL_INTERFACE("20D8C576-8D8A-4DBA-9722-A16C4D984980")
		IStreamSocketListenerControl : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_QualityOfService(SocketQualityOfService* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_QualityOfService(SocketQualityOfService value) = 0;
		};

		MIDL_INTERFACE("948BB665-2C3E-404B-B8B0-8EB249A2B0A1")
		IStreamSocketListenerControl2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NoDelay(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_NoDelay(BOOLEAN value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_KeepAlive(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_KeepAlive(BOOLEAN value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutboundBufferSizeInBytes(UINT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_OutboundBufferSizeInBytes(UINT32 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutboundUnicastHopLimit(BYTE* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_OutboundUnicastHopLimit(BYTE value) = 0;
		};

		MIDL_INTERFACE("E62BA82F-A63A-430B-BF62-29E93E5633B4")
		IStreamSocketListenerInformation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_LocalPort(HSTRING* value) = 0;
		};

		MIDL_INTERFACE("FE25ADF1-92AB-4AF3-9992-0F4C85E36CC4")
		IStreamSocketControl : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_NoDelay(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_NoDelay(BOOLEAN value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_KeepAlive(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_KeepAlive(BOOLEAN value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutboundBufferSizeInBytes(UINT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_OutboundBufferSizeInBytes(UINT32 value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_QualityOfService(SocketQualityOfService* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_QualityOfService(SocketQualityOfService value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutboundUnicastHopLimit(BYTE* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE put_OutboundUnicastHopLimit(BYTE value) = 0;
		};

		MIDL_INTERFACE("3B80AE30-5E68-4205-88F0-DC85D2E25DED")
		IStreamSocketInformation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_LocalAddress(IHostName** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_LocalPort(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemoteHostName(IHostName** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemoteAddress(IHostName** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemoteServiceName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RemotePort(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RoundTripTimeStatistics(RoundTripTimeStatistics* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_BandwidthStatistics(BandwidthStatistics* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ProtectionLevel(SocketProtectionLevel* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_SessionKey(IBuffer** value) = 0;
		};

		MIDL_INTERFACE("69A22CF3-FC7B-4857-AF38-F6E7DE6A5B49")
		IStreamSocket : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Control(IStreamSocketControl** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Information(IStreamSocketInformation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_InputStream(IInputStream** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_OutputStream(IOutputStream** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectWithEndpointPairAsync(IEndpointPair* endpointPair,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectAsync(IHostName* remoteHostName, HSTRING remoteServiceName,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectWithEndpointPairAndProtectionLevelAsync(
				IEndpointPair* endpointPair, SocketProtectionLevel protectionLevel,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectWithProtectionLevelAsync(IHostName* remoteHostName,
				HSTRING remoteServiceName, SocketProtectionLevel protectionLevel,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE UpgradeToSslAsync(SocketProtectionLevel protectionLevel,
				IHostName* validationHostName, IAsyncAction** operation) = 0;
		};

		MIDL_INTERFACE("29D0E575-F314-4D09-ADF0-0FBD967FBD9F")
		IStreamSocket2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ConnectWithProtectionLevelAndAdapterAsync(
				IHostName* remoteHostName, HSTRING remoteServiceName,
				SocketProtectionLevel protectionLevel, INetworkAdapter* adapter,
				IAsyncAction** operation) = 0;
		};

		MIDL_INTERFACE("43B04D64-4C85-4396-A637-1D973F6EBD49")
		ISocketActivityContext : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Data(IBuffer** value) = 0;
		};

		MIDL_INTERFACE("3F430B00-9D28-4854-BAC3-2301941EC223")
		IStreamSocket3 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CancelIOAsync(IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnableTransferOwnership(GUID taskId) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnableTransferOwnershipWithConnectedStandbyAction(
				GUID taskId, SocketActivityConnectedStandbyAction connectedStandbyAction) = 0;
			virtual HRESULT STDMETHODCALLTYPE TransferOwnership(HSTRING socketId) = 0;
			virtual HRESULT STDMETHODCALLTYPE TransferOwnershipWithContext(HSTRING socketId,
				ISocketActivityContext* data) = 0;
			virtual HRESULT STDMETHODCALLTYPE TransferOwnershipWithContextAndKeepAliveTime(
				HSTRING socketId, ISocketActivityContext* data, TimeSpan keepAliveTime) = 0;
		};

		MIDL_INTERFACE("0C472EA9-373F-447B-85B1-DDD4548803BA")
		IStreamSocketListenerConnectionReceivedEventArgs : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Socket(IStreamSocket** value) = 0;
		};

		MIDL_INTERFACE("33d00d41-c94f-5a61-9ab7-280dcefa0b08")
		IStreamSocketListenerConnectionReceivedEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IStreamSocketListener* sender,
				IStreamSocketListenerConnectionReceivedEventArgs* e) = 0;
		};

		MIDL_INTERFACE("FF513437-DF9F-4DF0-BF82-0EC5D7B35AAE")
		IStreamSocketListener : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Control(IStreamSocketListenerControl** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Information(IStreamSocketListenerInformation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE BindServiceNameAsync(HSTRING localServiceName,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE BindEndpointAsync(IHostName* localHostName,
				HSTRING localServiceName, IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_ConnectionReceived(
				IStreamSocketListenerConnectionReceivedEventHandler* eventHandler,
				EventRegistrationToken* eventCookie) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_ConnectionReceived(
				EventRegistrationToken eventCookie) = 0;
		};

		MIDL_INTERFACE("658DC13E-BB3E-4458-B232-ED1088694B98")
		IStreamSocketListener2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE BindServiceNameWithProtectionLevelAsync(
				HSTRING localServiceName, SocketProtectionLevel protectionLevel,
				IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE BindServiceNameWithProtectionLevelAndAdapterAsync(
				HSTRING localServiceName, SocketProtectionLevel protectionLevel,
				INetworkAdapter* adapter, IAsyncAction** operation) = 0;
		};

		MIDL_INTERFACE("4798201C-BDF8-4919-8542-28D450E74507")
		IStreamSocketListener3 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CancelIOAsync(IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnableTransferOwnership(GUID taskId) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnableTransferOwnershipWithConnectedStandbyAction(
				GUID taskId, SocketActivityConnectedStandbyAction connectedStandbyAction) = 0;
			virtual HRESULT STDMETHODCALLTYPE TransferOwnership(HSTRING socketId) = 0;
			virtual HRESULT STDMETHODCALLTYPE TransferOwnershipWithContext(HSTRING socketId,
				ISocketActivityContext* data) = 0;
		};

		MIDL_INTERFACE("2C4769F5-F684-40D5-8469-E8DBAAB70485")
		IDeviceInformationPairing : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_IsPaired(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_CanPair(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE PairAsync(IDevicePairingResultAsyncOperation** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE PairWithProtectionLevelAsync(DevicePairingProtectionLevel minProtectionLevel,
				IDevicePairingResultAsyncOperation** result) = 0;
		};

		MIDL_INTERFACE("F156A638-7997-48D9-A10C-269D46533F48")
		IDeviceInformation2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Kind(DeviceInformationKind* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Pairing(IDeviceInformationPairing** value) = 0;
		};

		MIDL_INTERFACE("482CB27C-83BB-420E-BE51-6602B222DE54")
		IDevicePairingSettings : public IInspectable
		{
		public:
		};

		MIDL_INTERFACE("85138C02-4EE6-4914-8370-107A39144C0E")
		IDeviceInformationCustomPairing : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE PairAsync(DevicePairingKinds pairingKindsSupported,
				IDevicePairingResultAsyncOperation** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE PairWithProtectionLevelAsync(
				DevicePairingKinds pairingKindsSupported, DevicePairingProtectionLevel minProtectionLevel,
				IDevicePairingResultAsyncOperation** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE PairWithProtectionLevelAndSettingsAsync(
				DevicePairingKinds pairingKindsSupported, DevicePairingProtectionLevel minProtectionLevel,
				IDevicePairingSettings* devicePairingSettings, IDevicePairingResultAsyncOperation** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_PairingRequested(IDevicePairingRequestedEventHandler* handler,
				EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_PairingRequested(EventRegistrationToken token) = 0;
		};

		MIDL_INTERFACE("F68612FD-0AEE-4328-85CC-1C742BB1790D")
		IDeviceInformationPairing2 : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_ProtectionLevel(DevicePairingProtectionLevel* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Custom(IDeviceInformationCustomPairing** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE PairWithProtectionLevelAndSettingsAsync(
				DevicePairingProtectionLevel minProtectionLevel, IDevicePairingSettings* devicePairingSettings,
				IDevicePairingResultAsyncOperation** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnpairAsync(IDeviceUnpairingResultAsyncOperation** result) = 0;
		};

		MIDL_INTERFACE("9520e64b-15b2-52a6-98ed-3191fa6cf68a")
		IGUIDVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, GUID* item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(GUID item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				GUID* items, DWORD* actual) = 0;
		};

		MIDL_INTERFACE("482e676d-b913-5ec1-afa8-5f96922e94ae")
		IGUIDVector : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, GUID* item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetView(IGUIDVectorView** view) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(GUID item, DWORD* index, BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAt(DWORD index, GUID item) = 0;
			virtual HRESULT STDMETHODCALLTYPE InsertAt(DWORD index, GUID item) = 0;
			virtual HRESULT STDMETHODCALLTYPE RemoveAt(DWORD index) = 0;
			virtual HRESULT STDMETHODCALLTYPE Append(GUID item) = 0;
			virtual HRESULT STDMETHODCALLTYPE RemoveAtEnd() = 0;
			virtual HRESULT STDMETHODCALLTYPE Clear() = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity, GUID* items, DWORD* actual) = 0;
			virtual HRESULT STDMETHODCALLTYPE ReplaceAll(DWORD count, GUID* value) = 0;
		};

		MIDL_INTERFACE("7ee0247f-5f57-5cb2-b40e-18b5a211d6c3")
		IDevicePairingResultAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDevicePairingResultAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("fa65231f-4178-5de1-b2cc-03e22d7702b4")
		IDevicePairingRequestedEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceInformationCustomPairing* sender,
				IDevicePairingRequestedEventArgs* e) = 0;
		};

		MIDL_INTERFACE("9bbe6eb9-db2d-5160-a20c-f0c265f20d8e")
		IDeviceUnpairingResultAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceUnpairingResultAsyncOperation* asyncInfo,
				AsyncStatus status) = 0;
		};

		MIDL_INTERFACE("1002db74-8948-591e-815d-e40b667599a3")
		IDevicePairingResultAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IDevicePairingResultAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IDevicePairingResultAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IDevicePairingResult** results) = 0;
		};

		MIDL_INTERFACE("2bb4df3d-bd7e-5fe0-9020-56dc0d30b935")
		IDeviceUnpairingResultAsyncOperation : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IDeviceUnpairingResultAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IDeviceUnpairingResultAsyncOperationCompletedHandler** handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(IDeviceUnpairingResult** results) = 0;
		};

		MIDL_INTERFACE("072B02BF-DD95-4025-9B37-DE51ADBA37B7")
		IDevicePairingResult : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Status(DevicePairingResultStatus* status) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ProtectionLevelUsed(
				DevicePairingProtectionLevel* value) = 0;
		};

		MIDL_INTERFACE("66F44AD3-79D9-444B-92CF-A92EF72571C7")
		IDeviceUnpairingResult : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Status(DeviceUnpairingResultStatus* status) = 0;
		};

		MIDL_INTERFACE("F717FC56-DE6B-487F-8376-0180ACA69963")
		IDevicePairingRequestedEventArgs : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_DeviceInformation(IDeviceInformation** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_PairingKind(DevicePairingKinds* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Pin(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE Accept() = 0;
			virtual HRESULT STDMETHODCALLTYPE AcceptWithPin(HSTRING pin) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeferral(IDeferral** result) = 0;
		};

		MIDL_INTERFACE("30D5A829-7FA4-4026-83BB-D75BAE4EA99E")
		IClosable : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Close() = 0;
		};

		MIDL_INTERFACE("9E365E57-48B2-4160-956F-C7385120BBFC")
		IUriRuntimeClass : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_AbsoluteUri(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DisplayUri(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Domain(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Extension(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Fragment(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Host(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Password(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Path(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Query(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_QueryParsed(
				IWwwFormUrlDecoderRuntimeClass** ppWwwFormUrlDecoder) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_RawUri(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_SchemeName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_UserName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Port(INT32* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Suspicious(BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE Equals(IUriRuntimeClass* pUri, BOOLEAN* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE CombineUri(HSTRING relativeUri,
				IUriRuntimeClass** instance) = 0;
		};

		MIDL_INTERFACE("D45A0451-F225-4542-9296-0E1DF5D254DF")
		IWwwFormUrlDecoderRuntimeClass : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetFirstValueByName(HSTRING name,
				HSTRING* phstrValue) = 0;
		};

		MIDL_INTERFACE("72D0568C-A274-41CD-82A8-989D40B9B05E")
		IAdaptiveCard : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ToJson(HSTRING* result) = 0;
		};

		MIDL_INTERFACE("69473EB2-8031-49BE-80BB-96CB46D99ABA")
		IWebAccount : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_WebAccountProvider(IWebAccountProvider** value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_UserName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_State(WebAccountState* value) = 0;
		};

		MIDL_INTERFACE("29DCC8C3-7AB9-4A7C-A336-B942F9DBF7C7")
		IWebAccountProvider : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Id(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DisplayName(HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IconUri(IUriRuntimeClass** value) = 0;
		};

		MIDL_INTERFACE("44A9796F-723E-4FDF-A218-033E75B0C084")
		IUriRuntimeClassFactory : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CreateUri(HSTRING uri, IUriRuntimeClass** instance) = 0;
			virtual HRESULT STDMETHODCALLTYPE CreateWithRelativeUri(HSTRING baseUri, HSTRING relativeUri,
				IUriRuntimeClass** instance) = 0;
		};

		MIDL_INTERFACE("f4706ab1-55a3-5270-afb2-732988fe8227")
		IHostNameVectorView : public IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD index, IHostName** item) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Size(DWORD* size) = 0;
			virtual HRESULT STDMETHODCALLTYPE IndexOf(IHostName* item, DWORD* index,
				BOOLEAN* found) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD startIndex, DWORD capacity,
				IHostName** items, DWORD* actual) = 0;
		};

		// WinRT control functions.

		int wclLoadWinRt();
		int wclUnloadWinRt();

		// WinRT string helper functions.

		int wclWinRtStringToHString(const TCHAR* Str, HSTRING* hStr);
		tstring wclWinRtHStringToString(HSTRING hStr);
		void wclWinRtDeleteHString(HSTRING hStr);

		// WinRT helper functions.

		int wclWinRtCreateInstance(const TCHAR* const ClassName, const GUID& ClsId, IInspectable** const Intf);
		int wclWinRtActivateFactory(const TCHAR* const ClassName, const GUID& ClsId, IInspectable** const Intf);

		int wclWinRtWaitAsync(IAsyncInfo* const Async, CwclEvent* const Event, const DWORD Timeout);
		int wclWinRtWaitAsync(IAsyncInfo* const Async, CwclEvent* const Event);
		int wclWinRtWaitAsync(IAsyncInfo* const Async);

		// ======================================================================
		//  IUnknown helpers
		//

		#define _WCL_UNKNOWN_REF_CNT_	LONG	FRefCount;

		// ----------------------------------------------------------------------

		#define _WCL_UNKNOWN_ADD_RELEASE_							\
			virtual ULONG STDMETHODCALLTYPE AddRef() override		\
			{														\
				return InterlockedIncrement(&FRefCount);			\
			}														\
																	\
			virtual ULONG STDMETHODCALLTYPE Release() override		\
			{														\
				ULONG Result = InterlockedDecrement(&FRefCount);	\
				if (!Result)										\
					delete this;									\
				return Result;										\
			}

		// ----------------------------------------------------------------------

		#define _WCL_UKNOWN_CTR_DTR_(_class_)						\
			_class_()												\
			{														\
				FRefCount = 0;										\
			}														\
																	\
			virtual ~_class_()										\
			{														\
			}

		// ----------------------------------------------------------------------

		#define _WCL_INSPECTABLE_									\
			virtual HRESULT STDMETHODCALLTYPE GetIids(				\
				DWORD* iidCount, GUID** iids) override				\
			{														\
				*iidCount = 0;										\
				*iids = NULL;										\
				return E_NOTIMPL;									\
			}														\
																	\
			virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(	\
				HSTRING* className) override						\
			{														\
				*className = NULL;									\
				return E_NOTIMPL;									\
			}														\
																	\
			virtual HRESULT STDMETHODCALLTYPE GetTrustLevel(		\
				TrustLevel* trust) override							\
			{														\
				*trust = FullTrust;									\
				return E_NOTIMPL;									\
			}

		// ----------------------------------------------------------------------

		template <class I>
		class CwclUnknown : public I
		{
		private:
			_WCL_UNKNOWN_REF_CNT_

		public:
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
				void** ppvObject) override
			{
				if (!ppvObject)
					return E_POINTER;
				
				if (riid == __uuidof(IUnknown))
					*ppvObject = static_cast<IUnknown*>(this);
				else if (riid == __uuidof(I))
					*ppvObject = static_cast<I*>(this);
				else
				{
					*ppvObject = NULL;
					return E_NOINTERFACE;
				}
				
				static_cast<IUnknown*>(*ppvObject)->AddRef(); 
				return S_OK;
			}

			_WCL_UNKNOWN_ADD_RELEASE_

		public:
			_WCL_UKNOWN_CTR_DTR_(CwclUnknown)
		};

		// ----------------------------------------------------------------------

		template <class I1, class I2>
		class CwclUnknown2 : public I1, public I2
		{
		private:
			_WCL_UNKNOWN_REF_CNT_

		public:
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
				void** ppvObject) override
			{
				if (!ppvObject)
					return E_POINTER;
				
				if (riid == __uuidof(IUnknown))
					*ppvObject = static_cast<I1*>(this);
				else if (riid == __uuidof(I1))
					*ppvObject = static_cast<I1*>(this);
				else if (riid == __uuidof(I2))
					*ppvObject = static_cast<I2*>(this);
				else
				{
					*ppvObject = NULL;
					return E_NOINTERFACE;
				}
				
				static_cast<IUnknown*>(*ppvObject)->AddRef(); 
				return S_OK;
			}

			_WCL_UNKNOWN_ADD_RELEASE_

		public:
			_WCL_UKNOWN_CTR_DTR_(CwclUnknown2)
		};

		// ----------------------------------------------------------------------

		template <class I1, class I2, class I3>
		class CwclUnknown3 : public I1, public I2, public I3
		{
		private:
			_WCL_UNKNOWN_REF_CNT_

		public:
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
				void** ppvObject) override
			{
				if (!ppvObject)
					return E_POINTER;
				
				if (riid == __uuidof(IUnknown))
					*ppvObject = static_cast<I1*>(this);
				else if (riid == __uuidof(I1))
					*ppvObject = static_cast<I1*>(this);
				else if (riid == __uuidof(I2))
					*ppvObject = static_cast<I2*>(this);
				else if (riid == __uuidof(I3))
					*ppvObject = static_cast<I3*>(this);
				else
				{
					*ppvObject = NULL;
					return E_NOINTERFACE;
				}
				
				static_cast<IUnknown*>(*ppvObject)->AddRef(); 
				return S_OK;
			}

			_WCL_UNKNOWN_ADD_RELEASE_

		public:
			_WCL_UKNOWN_CTR_DTR_(CwclUnknown3)
		};

		// ----------------------------------------------------------------------

		template <class I>
		class CwclInspectable : public I
		{
		private:
			_WCL_UNKNOWN_REF_CNT_

		public:
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
				void** ppvObject) override
			{
				if (!ppvObject)
					return E_POINTER;
				
				if (riid == __uuidof(IUnknown))
					*ppvObject = static_cast<IUnknown*>(this);
				else if (riid == __uuidof(IInspectable))
					*ppvObject = static_cast<IInspectable*>(this);
				else if (riid == __uuidof(I))
					*ppvObject = static_cast<I*>(this);
				else
				{
					*ppvObject = NULL;
					return E_NOINTERFACE;
				}
				
				static_cast<IUnknown*>(*ppvObject)->AddRef(); 
				return S_OK;
			}

			_WCL_UNKNOWN_ADD_RELEASE_
			_WCL_INSPECTABLE_

		public:
			_WCL_UKNOWN_CTR_DTR_(CwclInspectable)
		};

		//
		//  IUnknown helpers
		// ======================================================================

		// Helper class implements IDeviceWatcherEventHandler for DeviceWatcher
		// Stopped event. When event fires the class signals the Event.
		class CwclWinRtDeviceWatcherStoppedEventHandler : public CwclUnknown<IDeviceWatcherEventHandler>
		{
			DISABLE_COPY(CwclWinRtDeviceWatcherStoppedEventHandler);

		private:
			CwclEvent*	FEvent;

		public:
			/* IDeviceWatcherEventHandler */
			
			virtual HRESULT STDMETHODCALLTYPE Invoke(IDeviceWatcher* sender, IInspectable* e) override;

		public:
			CwclWinRtDeviceWatcherStoppedEventHandler(CwclEvent* const Event);
		};

		// Helper class implements WinRT iterator for strings array.
		class CwclWinRtHStringIterator : public CwclInspectable<IHSTRINGIterator>
		{
			DISABLE_COPY(CwclWinRtHStringIterator);
			
		private:
			tstring			FString;
			unsigned char	FNdx;

		public:
			/* IHSTRINGIterator */

			virtual HRESULT STDMETHODCALLTYPE get_Current(HSTRING* current) override;
			virtual HRESULT STDMETHODCALLTYPE get_HasCurrent(BOOLEAN* hasCurrent) override;
			virtual HRESULT STDMETHODCALLTYPE MoveNext(BOOLEAN* hasCurrent) override;
			virtual HRESULT STDMETHODCALLTYPE GetMany(DWORD capacity, HSTRING* items, DWORD* actual) override;

		public:
			CwclWinRtHStringIterator(const tstring& Str);
		};

		// Helper class represents IHSTRINGIterable interface.
		class CwclWinRtHStringIterable : public CwclInspectable<IHSTRINGIterable>
		{
			DISABLE_COPY(CwclWinRtHStringIterable);

		private:
			tstring	FString;

		public:
			/* IHSTRINGIterable */

			virtual HRESULT STDMETHODCALLTYPE First(IHSTRINGIterator** first) override;

		public:
			CwclWinRtHStringIterable(const tstring& Str);
		};

		// Helper class implements IShortReference interface.
		class CwclWinRtShortReference : public CwclInspectable<IShortReference>
		{
			DISABLE_COPY(CwclWinRtShortReference);
			
		private:
			short	FValue;

		public:
			/* IShortReference */
			
			virtual HRESULT STDMETHODCALLTYPE get_Value(short* value) override;
			
		public:
			CwclWinRtShortReference(const short Value);
		};

		// Helper class implements IUInt32Reference interface.
		class CwclWinRtUInt32Reference : public CwclInspectable<IUInt32Reference>
		{
			DISABLE_COPY(CwclWinRtUInt32Reference);
			
		private:
			DWORD	FValue;
			
		public:
			/* IUInt32Reference */

			virtual HRESULT STDMETHODCALLTYPE get_Value(DWORD* value) override;
			
		public:
			CwclWinRtUInt32Reference(const DWORD Value);
		};

		// Windows management

		HWND wclCreateWindow(const TCHAR* Name);
		void wclDestroyWindow(HWND hWnd);

		// Some required functions.

		bool wclIsUserAnAdmin();

		// MSXML helper functions.

		HRESULT wclCreateMsXmlInstance(IXMLDOMDocument** Doc);
	}
}
