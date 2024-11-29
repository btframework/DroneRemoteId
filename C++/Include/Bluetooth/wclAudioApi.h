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

#include <initguid.h>
#include <mmreg.h>

#include "..\Common\wclWinAPI.h"

namespace wclAudio
{
	namespace AudioApi
	{
		DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E);

		DEFINE_GUID(CLSID_PolicyConfigClient, 0x870af99c, 0x171d, 0x4f9e, 0xaf, 0x0d, 0xe6, 0x3d, 0xf4, 0x0c, 0x2b, 0xc9);
		DEFINE_GUID(CLSID_PolicyConfigVistaClient, 0x294935CE, 0xF637, 0x4E7C, 0xA4, 0x1B, 0xAB, 0x25, 0x54, 0x60, 0xB8, 0x62);

		DEFINE_GUID(KSPROPSETID_BtAudio, 0x7FA06C40, 0xB8F6, 0x4C7E, 0x85, 0x56, 0xE8, 0xC3, 0x3A, 0x12, 0xE5, 0x4D);

		#define DEVICE_STATE_ACTIVE		0x00000001
		#define DEVICE_STATE_DISABLED	0x00000002
		#define DEVICE_STATE_NOTPRESENT	0x00000004
		#define DEVICE_STATE_UNPLUGGED	0x00000008
		#define DEVICE_STATEMASK_ALL	0x0000000F

		#define KSMETHOD_TYPE_NONE		0x00000000
		#define KSMETHOD_TYPE_READ		0x00000001
		#define KSMETHOD_TYPE_WRITE		0x00000002
		#define KSMETHOD_TYPE_MODIFY	0x00000003
		#define KSMETHOD_TYPE_SOURCE	0x00000004

		#define KSMETHOD_TYPE_SEND			0x00000001
		#define KSMETHOD_TYPE_SETSUPPORT	0x00000100
		#define KSMETHOD_TYPE_BASICSUPPORT	0x00000200

		#define KSMETHOD_TYPE_TOPOLOGY	0x10000000

		#define KSPROPERTY_TYPE_GET				0x00000001
		#define KSPROPERTY_TYPE_SET				0x00000002
		#define KSPROPERTY_TYPE_GETPAYLOADSIZE	0x00000004
		#define KSPROPERTY_TYPE_SETSUPPORT		0x00000100
		#define KSPROPERTY_TYPE_BASICSUPPORT	0x00000200
		#define KSPROPERTY_TYPE_RELATIONS		0x00000400
		#define KSPROPERTY_TYPE_SERIALIZESET	0x00000800
		#define KSPROPERTY_TYPE_UNSERIALIZESET	0x00001000
		#define KSPROPERTY_TYPE_SERIALIZERAW	0x00002000
		#define KSPROPERTY_TYPE_UNSERIALIZERAW	0x00004000
		#define KSPROPERTY_TYPE_SERIALIZESIZE	0x00008000
		#define KSPROPERTY_TYPE_DEFAULTVALUES	0x00010000

		#define KSPROPERTY_TYPE_TOPOLOGY		0x10000000
		#define KSPROPERTY_TYPE_HIGHPRIORITY	0x08000000
		#define KSPROPERTY_TYPE_FSFILTERSCOPE	0x40000000
		#define KSPROPERTY_TYPE_COPYPAYLOAD		0x80000000

		#define ENDPOINT_HARDWARE_SUPPORT_VOLUME	0x00000001
		#define ENDPOINT_HARDWARE_SUPPORT_MUTE		0x00000002
		#define ENDPOINT_HARDWARE_SUPPORT_METER		0x00000004

		#define AUDCLNT_STREAMFLAGS_CROSSPROCESS				0x00010000
		#define AUDCLNT_STREAMFLAGS_LOOPBACK					0x00020000
		#define AUDCLNT_STREAMFLAGS_EVENTCALLBACK				0x00040000
		#define AUDCLNT_STREAMFLAGS_NOPERSIST					0x00080000
		#define AUDCLNT_STREAMFLAGS_RATEADJUST					0x00100000
		#define AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY			0x08000000
		#define AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM				0x80000000
		#define AUDCLNT_SESSIONFLAGS_EXPIREWHENUNOWNED			0x10000000
		#define AUDCLNT_SESSIONFLAGS_DISPLAY_HIDE				0x20000000
		#define AUDCLNT_SESSIONFLAGS_DISPLAY_HIDEWHENEXPIRED	0x40000000

		#define AMBISONICS_PARAM_VERSION_1	1

		#ifndef FACILITY_AUDCLNT
			#define FACILITY_AUDCLNT						0x889
		#endif

		#define AUDCLNT_S_BUFFER_EMPTY					((SEVERITY_SUCCESS << 31) | (FACILITY_AUDCLNT << 16) | 0x001)
		#define AUDCLNT_S_THREAD_ALREADY_REGISTERED		((SEVERITY_SUCCESS << 31) | (FACILITY_AUDCLNT << 16) | 0x002)
		#define AUDCLNT_S_POSITION_STALLED				((SEVERITY_SUCCESS << 31) | (FACILITY_AUDCLNT << 16) | 0x003)

		#define AUDCLNT_E_NOT_INITIALIZED				((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x001)
		#define AUDCLNT_E_ALREADY_INITIALIZED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x002)
		#define AUDCLNT_E_WRONG_ENDPOINT_TYPE			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x003)
		#define AUDCLNT_E_DEVICE_INVALIDATED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x004)
		#define AUDCLNT_E_NOT_STOPPED					((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x005)
		#define AUDCLNT_E_BUFFER_TOO_LARGE				((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x006)
		#define AUDCLNT_E_OUT_OF_ORDER					((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x007)
		#define AUDCLNT_E_UNSUPPORTED_FORMAT			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x008)
		#define AUDCLNT_E_INVALID_SIZE					((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x009)
		#define AUDCLNT_E_DEVICE_IN_USE					((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x00a)
		#define AUDCLNT_E_BUFFER_OPERATION_PENDING		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x00b)
		#define AUDCLNT_E_THREAD_NOT_REGISTERED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x00c)
		#define AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED	((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x00e)
		#define AUDCLNT_E_ENDPOINT_CREATE_FAILED		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x00f)
		#define AUDCLNT_E_SERVICE_NOT_RUNNING			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x010)
		#define AUDCLNT_E_EVENTHANDLE_NOT_EXPECTED		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x011)
		#define AUDCLNT_E_EXCLUSIVE_MODE_ONLY			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x012)
		#define AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL	((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x013)
		#define AUDCLNT_E_EVENTHANDLE_NOT_SET			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x014)
		#define AUDCLNT_E_INCORRECT_BUFFER_SIZE			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x015)
		#define AUDCLNT_E_BUFFER_SIZE_ERROR				((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x016)
		#define AUDCLNT_E_CPUUSAGE_EXCEEDED				((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x017)
		#define AUDCLNT_E_BUFFER_ERROR					((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x018)
		#define AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x019)
		#define AUDCLNT_E_INVALID_DEVICE_PERIOD			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x020)
		#define AUDCLNT_E_INVALID_STREAM_FLAG			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x021)
		#define AUDCLNT_E_ENDPOINT_OFFLOAD_NOT_CAPABLE	((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x022)
		#define AUDCLNT_E_OUT_OF_OFFLOAD_RESOURCES		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x023)
		#define AUDCLNT_E_OFFLOAD_MODE_ONLY				((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x024)
		#define AUDCLNT_E_NONOFFLOAD_MODE_ONLY			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x025)
		#define AUDCLNT_E_RESOURCES_INVALIDATED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x026)
		#define AUDCLNT_E_RAW_MODE_UNSUPPORTED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x027)
		#define AUDCLNT_E_ENGINE_PERIODICITY_LOCKED		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x028)
		#define AUDCLNT_E_ENGINE_FORMAT_LOCKED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x029)
		#define AUDCLNT_E_HEADTRACKING_ENABLED			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x030)
		#define AUDCLNT_E_HEADTRACKING_UNSUPPORTED		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x040)
		#define AUDCLNT_E_EFFECT_NOT_AVAILABLE			((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x041)
		#define AUDCLNT_E_EFFECT_STATE_READ_ONLY		((SEVERITY_ERROR << 31) | (FACILITY_AUDCLNT << 16) | 0x042)

		#ifndef PROPERTYKEY
			typedef wclCommon::WinApi::DEVPROPKEY PROPERTYKEY;
		#endif
		#ifndef REFPROPERTYKEY
			typedef PROPERTYKEY *REFPROPERTYKEY;
		#endif
		#ifndef REFPROPVARIANT
			typedef PROPVARIANT *REFPROPVARIANT;
		#endif

		typedef enum
		{
			eRender = 0,
			eCapture = eRender + 1,
			eAll = eCapture + 1
		} EDataFlow;

		typedef enum
		{
			eConsole = 0,
			eMultimedia = eConsole + 1,
			eCommunications = eMultimedia + 1
		} ERole;

		typedef enum
		{
			Unknown_Connector = 0,
			Physical_Internal = Unknown_Connector + 1,
			Physical_External = Physical_Internal + 1,
			Software_IO	= Physical_External + 1,
			Software_Fixed = Software_IO + 1,
			Network = Software_Fixed + 1
		} ConnectorType;

		typedef enum
		{
			_In = 0,
			_Out = _In + 1
		} DataFlow;

		typedef enum
		{
			Connector = 0,
			Subunit = Connector + 1
		} PartType;

		typedef enum
		{
			KSPROPERTY_ONESHOT_RECONNECT,
			KSPROPERTY_ONESHOT_DISCONNECT
		} KSPROPERTY_BTAUDIO;

		typedef enum
		{
			AUDCLNT_SHAREMODE_SHARED,
			AUDCLNT_SHAREMODE_EXCLUSIVE
		} AUDCLNT_SHAREMODE;

		typedef enum
		{
			AudioCategory_Other = 0,
			AudioCategory_ForegroundOnlyMedia = 1,
			AudioCategory_BackgroundCapableMedia = 2,
			AudioCategory_Communications = 3,
			AudioCategory_Alerts = 4,
			AudioCategory_SoundEffects = 5,
			AudioCategory_GameEffects = 6,
			AudioCategory_GameMedia = 7,
			AudioCategory_GameChat = 8,
			AudioCategory_Speech = 9,
			AudioCategory_Movie = 10,
			AudioCategory_Media = 11,
			AudioCategory_FarFieldSpeech = 12,
			AudioCategory_UniformSpeech = 13,
			AudioCategory_VoiceTyping = 14
		} AUDIO_STREAM_CATEGORY;

		typedef enum
		{
			AudioSessionStateInactive = 0,
			AudioSessionStateActive = 1,
			AudioSessionStateExpired = 2
		} AudioSessionState;

		typedef enum
		{
			AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY = 0x01,
			AUDCLNT_BUFFERFLAGS_SILENT = 0x02,
			AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR = 0x04
		} AUDCLNT_BUFFERFLAGS;

		typedef enum
		{
			AUDCLNT_STREAMOPTIONS_NONE = 0x00,
			AUDCLNT_STREAMOPTIONS_RAW = 0x01,
			AUDCLNT_STREAMOPTIONS_MATCH_FORMAT = 0x02,
			AUDCLNT_STREAMOPTIONS_AMBISONICS = 0x04
		} AUDCLNT_STREAMOPTIONS;

		typedef enum
		{
			AUDIO_DUCKING_OPTIONS_DEFAULT = 0x00,
			AUDIO_DUCKING_OPTIONS_DO_NOT_DUCK_OTHER_STREAMS = 0x01
		} AUDIO_DUCKING_OPTIONS;

		typedef enum
		{
			AUDIO_EFFECT_STATE_OFF = 0,
			AUDIO_EFFECT_STATE_ON = AUDIO_EFFECT_STATE_OFF + 1
		} AUDIO_EFFECT_STATE;

		typedef enum
		{
			AMBISONICS_TYPE_FULL3D = 0
		} AMBISONICS_TYPE;

		typedef enum
		{
			AMBISONICS_CHANNEL_ORDERING_ACN = 0
		} AMBISONICS_CHANNEL_ORDERING;

		typedef enum
		{
			AMBISONICS_NORMALIZATION_SN3D = 0,
			AMBISONICS_NORMALIZATION_N3D = AMBISONICS_NORMALIZATION_SN3D + 1
		} AMBISONICS_NORMALIZATION;

		#pragma pack(push, 1)
		typedef struct
		{
			GUID		_Set;
			ULONG		Id;
			ULONG		Flags;
			LONGLONG	Alignment;
		} KSIDENTIFIER, *PKSIDENTIFIER;
		#pragma pack(pop)

		typedef KSIDENTIFIER KSPROPERTY, *PKSPROPERTY;
		typedef KSIDENTIFIER KSMETHOD, *PKSMETHOD;
		typedef KSIDENTIFIER KSEVENT, *PKSEVENT;

		typedef struct
		{
			GUID	guidEventContext;
			BOOL	bMuted;
			FLOAT	fMasterVolume;
			UINT	nChannels;
			FLOAT	afChannelVolumes[1];
		} AUDIO_VOLUME_NOTIFICATION_DATA, *PAUDIO_VOLUME_NOTIFICATION_DATA;

		// If Win Ver < 8.1
		typedef struct
		{
			UINT32					cbSize;
			BOOL					bIsOffload;
			AUDIO_STREAM_CATEGORY	eCategory;
		} AudioClientProperties_Win8;

		// Wn Ver >= 8.1 We use this one because Audio features are supported on
		// Win 10 and above. However, we can always control the structure by cbSize!
		typedef struct
		{
			UINT32					cbSize;
			BOOL					bIsOffload;
			AUDIO_STREAM_CATEGORY	eCategory;
			AUDCLNT_STREAMOPTIONS	Options;
		} AudioClientProperties, *PAudioClientProperties;

		typedef LONGLONG REFERENCE_TIME, *PREFERENCE_TIME;

		typedef struct
		{
			GUID	tracingContextId;
		} AudioClient3ActivationParams;

		typedef struct
		{
			GUID				id;
			BOOL				canSetState;
			AUDIO_EFFECT_STATE	state;
		} AUDIO_EFFECT, *PAUDIO_EFFECT;

		typedef struct
		{
			UINT32						u32Size;
			UINT32						u32Version;
			AMBISONICS_TYPE				u32Type;
			AMBISONICS_CHANNEL_ORDERING	u32ChannelOrdering;
			AMBISONICS_NORMALIZATION	u32Normalization;
			UINT32						u32Order;
			UINT32						u32NumChannels;
			PDWORD						pu32ChannelMap;
		} AMBISONICS_PARAMS, *PAMBISONICS_PARAMS;

		interface IPart;
		interface IPartsList;

		MIDL_INTERFACE("886d8eeb-8cf2-4446-8d02-cdba1dbdcf99")
		IPropertyStore : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetCount(DWORD* cProps) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAt(DWORD iProp,
				PROPERTYKEY* pkey) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetValue(REFPROPERTYKEY key,
				PROPVARIANT* pv) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetValue(REFPROPERTYKEY key,
				REFPROPVARIANT propvar) = 0;
			virtual HRESULT STDMETHODCALLTYPE Commit() = 0;
		};

		MIDL_INTERFACE("D666063F-1587-4E43-81F1-B948E807363F")
		IMMDevice : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Activate(REFIID iid, DWORD dwClsCtx,
				PROPVARIANT* pActivationParams, void** ppInterface) = 0;
			virtual HRESULT STDMETHODCALLTYPE OpenPropertyStore(DWORD stgmAccess,
				IPropertyStore** ppProperties) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetId(LPWSTR* ppstrId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetState(DWORD* pdwState) = 0;
		};

		MIDL_INTERFACE("0BD7A1BE-7A1A-44DB-8397-CC5392387B5E")
		IMMDeviceCollection : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetCount(UINT* pcDevices) = 0;
			virtual HRESULT STDMETHODCALLTYPE Item(UINT nDevice,
				IMMDevice** ppDevice) = 0;
		};

		MIDL_INTERFACE("7991EEC9-7E89-4D85-8390-6C703CEC60C0")
		IMMNotificationClient : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId,
				DWORD dwNewState) = 0;
			virtual HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId) = 0;
			virtual HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId) = 0;
			virtual HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role,
				LPCWSTR pwstrDefaultDeviceId) = 0;
			virtual HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId,
				PROPERTYKEY key) = 0;
		};

		MIDL_INTERFACE("A95664D2-9614-4F35-A746-DE8DB63617E6")
		IMMDeviceEnumerator : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE EnumAudioEndpoints(EDataFlow dataFlow,
				DWORD dwStateMask, IMMDeviceCollection** ppDevices) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDefaultAudioEndpoint(EDataFlow dataFlow,
				ERole role, IMMDevice** ppEndpoint) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDevice(LPCWSTR pwstrId,
				IMMDevice** ppDevice) = 0;
			virtual HRESULT STDMETHODCALLTYPE RegisterEndpointNotificationCallback(
				IMMNotificationClient* pClient) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnregisterEndpointNotificationCallback(
				IMMNotificationClient* pClient) = 0;
		};

		MIDL_INTERFACE("1BE09788-6894-4089-8586-9A2A6C265AC5")
		IMMEndpoint : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetDataFlow(
				EDataFlow* pDataFlow) = 0;
		};

		MIDL_INTERFACE("3B0D0EA4-D0A9-4B0E-935B-09516746FAC0")
		IMMDeviceActivator : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Activate(REFIID iid, IMMDevice* pDevice,
				PROPVARIANT* pActivationParams, void** ppInterface) = 0;
		};

		MIDL_INTERFACE("72A22D78-CDE4-431D-B8CC-843A71199B6D")
		IActivateAudioInterfaceAsyncOperation : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetActivateResult(HRESULT* activateResult,
				IUnknown** activatedInterface) = 0;
		};

		MIDL_INTERFACE("41D949AB-9862-444A-80F6-C261334DA5EB")
		IActivateAudioInterfaceCompletionHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ActivateCompleted(
				IActivateAudioInterfaceAsyncOperation* activateOperation) = 0;
		};

		MIDL_INTERFACE("f8679f50-850a-41cf-9c72-430f290290c8")
		IPolicyConfig : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetMixFormat(PCWSTR arg1,
				void** /* PWAVEFORMATEX */ arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeviceFormat(PCWSTR arg1,
				INT arg2, void** /* PWAVEFORMATEX */ arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE ResetDeviceFormat(
				PCWSTR arg1) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDeviceFormat(PCWSTR arg1,
				void* /* PWAVEFORMATEX */ arg2,
				void* /* PWAVEFORMATEX */ arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetProcessingPeriod(PCWSTR arg1,
				INT arg2, PINT64 arg3, PINT64 agr4) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetProcessingPeriod(PCWSTR arg1,
				PINT64 arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetShareMode(PCWSTR arg1,
				void* /* PDeviceShareMode */ agr2) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetShareMode(PCWSTR arg1,
				void* /* PDeviceShareMode */ arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPropertyValue(PCWSTR arg1,
				REFPROPERTYKEY arg2, PROPVARIANT* arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetPropertyValue(PCWSTR arg1,
				REFPROPERTYKEY arg2, PROPVARIANT* arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDefaultEndpoint(PCWSTR wszDeviceId,
				ERole eRole) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetEndpointVisibility(PCWSTR arg1,
				INT arg2) = 0;
		};

		MIDL_INTERFACE("568b9108-44bf-40b4-9006-86afe5b5a620")
		IPolicyConfigVista : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetMixFormat(PCWSTR arg1,
				void** /* PWAVEFORMATEX* */ arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeviceFormat(PCWSTR arg1,
				INT arg2, void** /* PWAVEFORMATEX* */ arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDeviceFormat(PCWSTR arg1,
				void* /* PWAVEFORMATEX */ arg2,
				void* /* PWAVEFORMATEX */ arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetProcessingPeriod(PCWSTR arg1,
				INT arg2, PINT64 arg3, PINT64 agr4) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetProcessingPeriod(PCWSTR arg1,
				PINT64 arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetShareMode(PCWSTR arg1,
				void* /* PDeviceShareMode */ agr2) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetShareMode(PCWSTR arg1,
				void* /* PDeviceShareMode */ arg2) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPropertyValue(PCWSTR arg1,
				REFPROPERTYKEY arg2, PROPVARIANT* arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetPropertyValue(PCWSTR arg1,
				REFPROPERTYKEY arg2, PROPVARIANT* arg3) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDefaultEndpoint(PCWSTR wszDeviceId,
				ERole eRole) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetEndpointVisibility(PCWSTR arg1,
				INT arg2) = 0;
		};

		MIDL_INTERFACE("9c2c4058-23f5-41de-877a-df3af236a09e")
		IConnector : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetType(ConnectorType* pType) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDataFlow(DataFlow* pFlow) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectTo(IConnector* pConnectTo) = 0;
			virtual HRESULT STDMETHODCALLTYPE Disconnect() = 0;
			virtual HRESULT STDMETHODCALLTYPE IsConnected(BOOL* pbConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectedTo(IConnector** ppConTo) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectorIdConnectedTo(
				LPWSTR* ppwstrConnectorId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeviceIdConnectedTo(
				LPWSTR* ppwstrDeviceId) = 0;
		};

		MIDL_INTERFACE("82149A85-DBA6-4487-86BB-EA8F7FEFCC71")
		ISubunit : public IUnknown
		{
		public:
		};

		MIDL_INTERFACE("45d37c3f-5140-444a-ae24-400789f3cbf3")
		IControlInterface : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetName(LPWSTR* ppwstrName) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetIID(GUID* pIID) = 0;
		};

		MIDL_INTERFACE("2A07407E-6497-4A18-9787-32F79BD0D98F")
		IDeviceTopology : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetConnectorCount(
				UINT* pCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnector(UINT nIndex,
				IConnector** ppConnector) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSubunitCount(
				UINT* pCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSubunit(UINT* nIndex,
				ISubunit** ppSubunit) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPartById(UINT nId,
				IPart** ppPart) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDeviceId(LPWSTR* ppwstrDeviceId);
			virtual HRESULT STDMETHODCALLTYPE GetSignalPath(IPart* pIPartFrom,
				IPart* pIPartTo, BOOL bRejectMixedPaths, IPartsList** ppParts) = 0;
		};

		MIDL_INTERFACE("A09513ED-C709-4d21-BD7B-5F34C47F3947")
		IControlChangeNotify : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE OnNotify(DWORD dwSenderProcessId,
				GUID* pguidEventContext) = 0;
		};

		MIDL_INTERFACE("AE2DE0E4-5BCA-4F2D-AA46-5D13F8FDB3A9")
		IPart : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetName(LPWSTR* ppwstrName) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetLocalId(UINT* pnId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetGlobalId(
				LPWSTR* ppwstrGlobalId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPartType(PartType* pPartType) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetSubType(GUID* pSubType) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetControlInterfaceCount(
				UINT* pCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetControlInterface(UINT nIndex,
				IControlInterface** ppInterfaceDesc) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnumPartsIncoming(
				IPartsList** ppParts) = 0;
			virtual HRESULT STDMETHODCALLTYPE EnumPartsOutgoing(
				IPartsList** ppParts) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetTopologyObject(
				IDeviceTopology** ppTopology) = 0;
			virtual HRESULT STDMETHODCALLTYPE Activate(DWORD dwClsContext, REFIID refiid,
				void** ppvObject) = 0;
			virtual HRESULT STDMETHODCALLTYPE RegisterControlChangeCallback(REFGUID riid,
				IControlChangeNotify* pNotify) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnregisterControlChangeCallback(
				IControlChangeNotify* pNotify) = 0;
		};

		MIDL_INTERFACE("6DAA848C-5EB0-45CC-AEA5-998A2CDA1FFB")
		IPartsList : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetCount(UINT* pCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPart(UINT nIndex,
				IPart** ppPart) = 0;
		};

		MIDL_INTERFACE("28F54685-06FD-11D2-B27A-00A0C9223196")
		IKsControl : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE KsProperty(PKSPROPERTY Property,
				ULONG PropertyLength, void* PropertyData, ULONG DataLength,
				ULONG* BytesReturned) = 0;
			virtual HRESULT STDMETHODCALLTYPE KsMethod(PKSMETHOD Method,
				ULONG MethodLength, void* MethodData, ULONG DataLength,
				ULONG* BytesReturned) = 0;
			virtual HRESULT STDMETHODCALLTYPE KsEvent(PKSEVENT Event,
				ULONG EventLength, void* EventData, ULONG DataLength,
				ULONG* BytesReturned) = 0;
		};

		MIDL_INTERFACE("657804FA-D6AD-4496-8A60-352752AF4F89")
		IAudioEndpointVolumeCallback : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE OnNotify(
				PAUDIO_VOLUME_NOTIFICATION_DATA pNotify) = 0;
		};

		MIDL_INTERFACE("5CDF2C82-841E-4546-9722-0CF74078229A")
		IAudioEndpointVolume : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE RegisterControlChangeNotify(
				IAudioEndpointVolumeCallback* pNotify) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnregisterControlChangeNotify(
				IAudioEndpointVolumeCallback* pNotify) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelCount(
				UINT* pnChannelCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetMasterVolumeLevel(FLOAT fLevelDB,
				LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetMasterVolumeLevelScalar(FLOAT fLevel,
				LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMasterVolumeLevel(
				FLOAT* pfLevelDB) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMasterVolumeLevelScalar(
				FLOAT* pfLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetChannelVolumeLevel(UINT nChannel,
				FLOAT fLevelDB, LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetChannelVolumeLevelScalar(
				UINT nChannel, FLOAT fLevel, LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelVolumeLevel(UINT nChannel,
				FLOAT* pfLevelDB) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelVolumeLevelScalar(UINT nChannel,
				FLOAT* pfLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetMute(BOOL bMute,
				LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMute(BOOL* pbMute) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetVolumeStepInfo(UINT* pnStep,
				UINT* pnStepCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE VolumeStepUp(LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE VolumeStepDown(
				LPGUID pguidEventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE QueryHardwareSupport(
				DWORD* pdwHardwareSupportMask) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetVolumeRange(FLOAT* pflVolumeMindB,
				FLOAT* pflVolumeMaxdB, FLOAT* pflVolumeIncrementdB) = 0;
		};

		MIDL_INTERFACE("66E11784-F695-4F28-A505-A7080081A78F")
		IAudioEndpointVolumeEx : public IAudioEndpointVolume
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetVolumeRangeChannel(UINT iChannel,
				FLOAT* pflVolumeMindB, FLOAT* pflVolumeMaxdB,
				FLOAT* pflVolumeIncrementdB) = 0;
		};

		MIDL_INTERFACE("C02216F6-8C67-4B5B-9D00-D008E73E0064")
		IAudioMeterInformation : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetPeakValue(FLOAT* pfPeak) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMeteringChannelCount(
				UINT* pnChannelCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelsPeakValues(
				UINT32 u32ChannelCount, FLOAT* afPeakValues) = 0;
			virtual HRESULT STDMETHODCALLTYPE QueryHardwareSupport(
				DWORD* pdwHardwareSupportMask) = 0;
		};

		MIDL_INTERFACE("1CB9AD4C-DBFA-4c32-B178-C2F568A703B2")
		IAudioClient : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Initialize(AUDCLNT_SHAREMODE ShareMode,
				DWORD StreamFlags, REFERENCE_TIME hnsBufferDuration, REFERENCE_TIME hnsPeriodicity,
				PWAVEFORMATEX pFormat, LPGUID AudioSessionGuid) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetBufferSize(UINT32* pNumBufferFrames) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetStreamLatency(REFERENCE_TIME* phnsLatency) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCurrentPadding(UINT32* pNumPaddingFrames) = 0;
			virtual HRESULT STDMETHODCALLTYPE IsFormatSupported(AUDCLNT_SHAREMODE ShareMode,
				PWAVEFORMATEX pFormat, PWAVEFORMATEX* ppClosestMatch) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMixFormat(PWAVEFORMATEX* ppDeviceFormat) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDevicePeriod(REFERENCE_TIME* phnsDefaultDevicePeriod,
				REFERENCE_TIME* phnsMinimumDevicePeriod) = 0;
			virtual HRESULT STDMETHODCALLTYPE Start() = 0;
			virtual HRESULT STDMETHODCALLTYPE Stop() = 0;
			virtual HRESULT STDMETHODCALLTYPE Reset() = 0;
			virtual HRESULT STDMETHODCALLTYPE SetEventHandle(HANDLE eventHandle) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetService(LPGUID riid, void** ppInterface) = 0;
		};

		MIDL_INTERFACE("726778CD-F60A-4eda-82DE-E47610CD78AA")
		IAudioClient2 : public IAudioClient
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE IsOffloadCapable(AUDIO_STREAM_CATEGORY Category,
				BOOL* pbOffloadCapable) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetClientProperties(
				AudioClientProperties* pProperties) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetBufferSizeLimits(PWAVEFORMATEX pFormat,
				BOOL bEventDriven, REFERENCE_TIME* phnsMinBufferDuration,
				REFERENCE_TIME* phnsMaxBufferDuration) = 0;
		};

		MIDL_INTERFACE("7ED4EE07-8E67-4CD4-8C1A-2B7A5987AD42")
		IAudioClient3 : public IAudioClient2
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetSharedModeEnginePeriod(
				PWAVEFORMATEX pFormat, UINT32* pDefaultPeriodInFrames,
				UINT32* pFundamentalPeriodInFrames, UINT32* pMinPeriodInFrames,
				UINT32* pMaxPeriodInFrames) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCurrentSharedModeEnginePeriod(
				PWAVEFORMATEX* ppFormat, UINT32* pCurrentPeriodInFrames) = 0;
			virtual HRESULT STDMETHODCALLTYPE InitializeSharedAudioStream(DWORD StreamFlags,
				UINT32 PeriodInFrames, PWAVEFORMATEX pFormat, LPGUID AudioSessionGuid) = 0;
		};

		MIDL_INTERFACE("F294ACFC-3146-4483-A7BF-ADDCA7C260E2")
		IAudioRenderClient : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetBuffer(UINT32 NumFramesRequested,
				PBYTE* ppData) = 0;
			virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer(UINT32 NumFramesWritten,
				DWORD dwFlags) = 0;
		};

		MIDL_INTERFACE("C8ADBD64-E71E-48a0-A4DE-185C395CD317")
		IAudioCaptureClient : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetBuffer(PBYTE* ppData,
				UINT32* pNumFramesToRead, DWORD* pdwFlags, UINT64* pu64DevicePosition,
				UINT64* pu64QPCPosition) = 0;
			virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer(UINT32 NumFramesRead) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNextPacketSize(
				UINT32* pNumFramesInNextPacket) = 0;
		};

		MIDL_INTERFACE("CD63314F-3FBA-4a1b-812C-EF96358728E7")
		IAudioClock : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetFrequency(UINT64* pu64Frequency) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetPosition(UINT64* pu64Position,
				UINT64* pu64QPCPosition) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCharacteristics(DWORD
				* pdwCharacteristics) = 0;
		};

		MIDL_INTERFACE("6f49ff73-6727-49ac-a008-d98cf5e70048")
		IAudioClock2 : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetDevicePosition(UINT64* DevicePosition,
				UINT64* QPCPosition) = 0;
		};

		MIDL_INTERFACE("f6e4c0a0-46d9-4fb8-be21-57a3ef2b626c")
		IAudioClockAdjustment : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetSampleRate(FLOAT flSampleRate) = 0;
		};

		MIDL_INTERFACE("87CE5498-68D6-44E5-9215-6DA47EF883D8")
		ISimpleAudioVolume : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetMasterVolume(FLOAT fLevel,
				LPGUID EventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMasterVolume(FLOAT* pfLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetMute(BOOL bMute, LPGUID EventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetMute(BOOL* pbMute) = 0;
		};

		MIDL_INTERFACE("C789D381-A28C-4168-B28F-D3A837924DC3")
		IAudioClientDuckingControl : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetDuckingOptionsForCurrentStream(
				AUDIO_DUCKING_OPTIONS options) = 0;
		};

		MIDL_INTERFACE("A7A7EF10-1F49-45E0-AD35-612057CC8F74")
		IAudioViewManagerService : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetAudioStreamWindow(HWND hwnd) = 0;
		};

		MIDL_INTERFACE("A5DED44F-3C5D-4B2B-BD1E-5DC1EE20BBF6")
		IAudioEffectsChangedNotificationClient : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE OnAudioEffectsChanged() = 0;
		};

		MIDL_INTERFACE("4460B3AE-4B44-4527-8676-7548A8ACD260")
		IAudioEffectsManager : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE RegisterAudioEffectsChangedNotificationCallback(
				IAudioEffectsChangedNotificationClient* client) = 0;
			virtual HRESULT STDMETHODCALLTYPE UnregisterAudioEffectsChangedNotificationCallback(
				IAudioEffectsChangedNotificationClient* client) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAudioEffects(PAUDIO_EFFECT* effects,
				UINT32* numEffects) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAudioEffectState(GUID effectId,
				AUDIO_EFFECT_STATE state) = 0;
		};

		MIDL_INTERFACE("93014887-242D-4068-8A15-CF5E93B90FE3")
		IAudioStreamVolume : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetChannelCount(UINT32* pdwCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetChannelVolume(UINT32 dwIndex,
				FLOAT fLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelVolume(UINT32 dwIndex,
				FLOAT* pfLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAllVolumes(UINT32 dwCount,
				PFLOAT pfVolumes) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAllVolumes(UINT32 dwCount,
				PFLOAT pfVolumes) = 0;
		};

		MIDL_INTERFACE("28724C91-DF35-4856-9F76-D6A26413F3DF")
		IAudioAmbisonicsControl : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetData(PAMBISONICS_PARAMS pAmbisonicsParams,
				UINT32 cbAmbisonicsParams) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetHeadTracking(BOOL bEnableHeadTracking) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetHeadTracking(BOOL* pbEnableHeadTracking) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetRotation(FLOAT X, FLOAT Y,
				FLOAT Z, FLOAT W) = 0;
		};

		MIDL_INTERFACE("1C158861-B533-4B30-B1CF-E853E51C59B8")
		IChannelAudioVolume : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetChannelCount(UINT32* pdwCount) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetChannelVolume(UINT32 dwIndex,
				FLOAT fLevel, LPGUID EventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetChannelVolume(UINT32 dwIndex,
				FLOAT* pfLevel) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetAllVolumes(UINT32 dwCount,
				FLOAT* pfVolumes, LPGUID EventContext) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAllVolumes(UINT32 dwCount,
				FLOAT* pfVolumes) = 0;
		};

		MIDL_INTERFACE("f4ae25b5-aaa3-437d-b6b3-dbbe2d0e9549")
		IAcousticEchoCancellationControl : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE SetEchoCancellationRenderEndpoint(
				LPCWSTR endpointId) = 0;
		};

		/* WinRT Audio API */

		#define AudioPlaybackConnectionName	_T("Windows.Media.Audio.AudioPlaybackConnection")
		
		typedef enum
		{
			AudioPlaybackConnectionState_Closed = 0,
			AudioPlaybackConnectionState_Opened = 1
		} AudioPlaybackConnectionState;
		
		typedef enum
		{
			AudioPlaybackConnectionOpenResultStatus_Success = 0,
			AudioPlaybackConnectionOpenResultStatus_RequestTimedOut = 1,
			AudioPlaybackConnectionOpenResultStatus_DeniedBySystem = 2,
			AudioPlaybackConnectionOpenResultStatus_UnknownFailure = 3
		} AudioPlaybackConnectionOpenResultStatus;

		// Forward declarations
		interface IAudioPlaybackConnection;
		interface IAudioPlaybackConnectionOpenAsyncOperation;

		MIDL_INTERFACE("4e656aef-39f9-5fc9-a519-a5bbfd9fe921")
		IAudioPlaybackConnectionOpenResult : public wclCommon::WinApi::IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get_Status(
				AudioPlaybackConnectionOpenResultStatus* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(HRESULT* value) = 0;
		};

		MIDL_INTERFACE("56ddb54d-eb8d-5ffb-a54b-8faf918c8031")
		IAudioPlaybackConnectionOpenAsyncOperationCompletedHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(
				IAudioPlaybackConnectionOpenAsyncOperation* asyncInfo,
				wclCommon::WinApi::AsyncStatus asyncStatus) = 0;
		};

		MIDL_INTERFACE("f5245f8a-3dd1-56b2-829b-9888251d689c")
		IAudioPlaybackConnectionOpenAsyncOperation : public wclCommon::WinApi::IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE put_Completed(
				IAudioPlaybackConnectionOpenAsyncOperationCompletedHandler* handler) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_Completed(
				IAudioPlaybackConnectionOpenAsyncOperationCompletedHandler** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetResults(
				IAudioPlaybackConnectionOpenResult** result) = 0;
		};

		MIDL_INTERFACE("0e389b05-31a6-58f1-9ea4-0c1e4d70a7b8")
		IAudioPlaybackConnectionEventHandler : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Invoke(IAudioPlaybackConnection* sender,
				wclCommon::WinApi::IInspectable* args) = 0;
		};

		MIDL_INTERFACE("1a4c1dea-cafc-50e7-8718-ea3f81cbfa51")
		IAudioPlaybackConnection : public wclCommon::WinApi::IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE Start() = 0;
			virtual HRESULT STDMETHODCALLTYPE StartAsync(
				wclCommon::WinApi::IAsyncAction** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DeviceId(
				wclCommon::WinApi::HSTRING* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_State(AudioPlaybackConnectionState* value) = 0;
			virtual HRESULT STDMETHODCALLTYPE Open(IAudioPlaybackConnectionOpenResult** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE OpenAsync(
				IAudioPlaybackConnectionOpenAsyncOperation** operation) = 0;
			virtual HRESULT STDMETHODCALLTYPE add_StateChanged(
				IAudioPlaybackConnectionEventHandler* handler,
				wclCommon::WinApi::EventRegistrationToken* token) = 0;
			virtual HRESULT STDMETHODCALLTYPE remove_StateChanged(
				wclCommon::WinApi::EventRegistrationToken token) = 0;
		};

		MIDL_INTERFACE("e60963a2-69e6-5ffc-9e13-824a85213daf")
		IAudioPlaybackConnectionStatics : public wclCommon::WinApi::IInspectable
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetDeviceSelector(
				wclCommon::WinApi::HSTRING* result) = 0;
			virtual HRESULT STDMETHODCALLTYPE TryCreateFromId(
				wclCommon::WinApi::HSTRING id,
				IAudioPlaybackConnection** result) = 0;
		};
	}
}