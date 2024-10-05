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

#include <INITGUID.H>

#include <rpc.h>
#include <rpcndr.h>
#include <windows.h>
#include <ole2.h>
#include <unknwn.h>
#include <objidl.h>
#include <oaidl.h>
#include <ocidl.h>

namespace wclWiFi
{
	namespace NlmApi
	{
		DEFINE_GUID(LIBID_NETWORKLIST, 0xDCB00D01, 0x570F, 0x4A9B, 0x8D, 0x69, 0x19, 0x9F, 0xDB, 0xA5, 0x72, 0x3B);

		DEFINE_GUID(CLSID_NetworkListManager, 0xDCB00C01, 0x570F, 0x4A9B, 0x8D, 0x69, 0x19, 0x9F, 0xDB, 0xA5, 0x72, 0x3B);

		typedef interface INetworkListManager INetworkListManager;
		typedef interface INetworkListManagerEvents INetworkListManagerEvents;
		typedef interface INetwork INetwork;
		typedef interface IEnumNetworks IEnumNetworks;
		typedef interface INetworkEvents INetworkEvents;
		typedef interface INetworkConnection INetworkConnection;
		typedef interface IEnumNetworkConnections IEnumNetworkConnections;
		typedef interface INetworkConnectionEvents INetworkConnectionEvents;
		typedef interface INetworkCostManager INetworkCostManager;
		typedef interface INetworkCostManagerEvents INetworkCostManagerEvents;
		typedef interface INetworkConnectionCost INetworkConnectionCost;
		typedef interface INetworkConnectionCostEvents INetworkConnectionCostEvents;
		typedef interface INetworkConnectionCost INetworkConnectionCost;

		typedef class NetworkListManager NetworkListManager;

		#define NA_DomainAuthenticationFailed	L"NA_DomainAuthenticationFailed"
		#define NA_NetworkClass					L"NA_NetworkClass"
		#define NA_NameSetByPolicy				L"NA_NameSetByPolicy"
		#define NA_IconSetByPolicy				L"NA_IconSetByPolicy"
		#define NA_DescriptionSetByPolicy		L"NA_DescriptionSetByPolicy"
		#define NA_CategorySetByPolicy			L"NA_CategorySetByPolicy"
		#define NA_NameReadOnly					L"NA_NameReadOnly"
		#define NA_IconReadOnly					L"NA_IconReadOnly"
		#define NA_DescriptionReadOnly			L"NA_DescriptionReadOnly"
		#define NA_CategoryReadOnly				L"NA_CategoryReadOnly"
		#define NA_AllowMerge					L"NA_AllowMerge"
		#define NA_InternetConnectivityV4		L"NA_InternetConnectivityV4"
		#define NA_InternetConnectivityV6		L"NA_InternetConnectivityV6"

		#define	NLM_MAX_ADDRESS_LIST_SIZE	10

		#define	NLM_UNKNOWN_DATAPLAN_STATUS	0xffffffff

		typedef enum
		{
			NLM_CONNECTION_COST_UNKNOWN	= 0,
			NLM_CONNECTION_COST_UNRESTRICTED = 0x1,
			NLM_CONNECTION_COST_FIXED = 0x2,
			NLM_CONNECTION_COST_VARIABLE = 0x4,
			NLM_CONNECTION_COST_OVERDATALIMIT = 0x10000,
			NLM_CONNECTION_COST_CONGESTED = 0x20000,
			NLM_CONNECTION_COST_ROAMING	= 0x40000,
			NLM_CONNECTION_COST_APPROACHINGDATALIMIT = 0x80000
		} NLM_CONNECTION_COST;

		typedef struct
		{
			DWORD		UsageInMegabytes;
			FILETIME	LastSyncTime;
		} NLM_USAGE_DATA;

		typedef struct
		{
			GUID			InterfaceGuid;
			NLM_USAGE_DATA	UsageData;
			DWORD			DataLimitInMegabytes;
			DWORD			InboundBandwidthInKbps;
			DWORD			OutboundBandwidthInKbps;
			FILETIME		NextBillingCycle;
			DWORD			MaxTransferSizeInMegabytes;
			DWORD			Reserved;
		} NLM_DATAPLAN_STATUS;

		typedef struct
		{
			BYTE	data[128];
		} NLM_SOCKADDR;

		typedef enum
		{
			NLM_NETWORK_IDENTIFYING = 0x1,
			NLM_NETWORK_IDENTIFIED = 0x2,
			NLM_NETWORK_UNIDENTIFIED = 0x3
		} NLM_NETWORK_CLASS;

		typedef struct
		{
			WCHAR				ProfileName[256];
			NLM_CONNECTION_COST	cost;
			DWORD				UsageInMegabytes;
			DWORD				DataLimitInMegabytes;
		} NLM_SIMULATED_PROFILE_INFO;

		typedef enum
		{
			NLM_INTERNET_CONNECTIVITY_WEBHIJACK = 0x1,
			NLM_INTERNET_CONNECTIVITY_PROXIED = 0x2,
			NLM_INTERNET_CONNECTIVITY_CORPORATE = 0x4
		} NLM_INTERNET_CONNECTIVITY;

		typedef enum
		{
			NLM_CONNECTIVITY_DISCONNECTED = 0,
			NLM_CONNECTIVITY_IPV4_NOTRAFFIC = 0x1,
			NLM_CONNECTIVITY_IPV6_NOTRAFFIC = 0x2,
			NLM_CONNECTIVITY_IPV4_SUBNET = 0x10,
			NLM_CONNECTIVITY_IPV4_LOCALNETWORK = 0x20,
			NLM_CONNECTIVITY_IPV4_INTERNET = 0x40,
			NLM_CONNECTIVITY_IPV6_SUBNET = 0x100,
			NLM_CONNECTIVITY_IPV6_LOCALNETWORK = 0x200,
			NLM_CONNECTIVITY_IPV6_INTERNET = 0x400
		} NLM_CONNECTIVITY;

		typedef enum
		{
			NLM_DOMAIN_TYPE_NON_DOMAIN_NETWORK = 0,
			NLM_DOMAIN_TYPE_DOMAIN_NETWORK = 0x1,
			NLM_DOMAIN_TYPE_DOMAIN_AUTHENTICATED = 0x2
		} NLM_DOMAIN_TYPE;

		typedef enum NLM_ENUM_NETWORK
		{
			NLM_ENUM_NETWORK_CONNECTED = 0x1,
			NLM_ENUM_NETWORK_DISCONNECTED = 0x2,
			NLM_ENUM_NETWORK_ALL = 0x3
		} NLM_ENUM_NETWORK;

		MIDL_INTERFACE("DCB00000-570F-4A9B-8D69-199FDBA5723B")
		INetworkListManager : public IDispatch
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetNetworks(NLM_ENUM_NETWORK Flags,
				IEnumNetworks **ppEnumNetwork) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetwork(GUID gdNetworkId,
				INetwork **ppNetwork) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkConnections(IEnumNetworkConnections **ppEnum) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkConnection(GUID gdNetworkConnectionId,
				INetworkConnection **ppNetworkConnection) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnectedToInternet(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnected(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectivity(NLM_CONNECTIVITY *pConnectivity) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetSimulatedProfileInfo(NLM_SIMULATED_PROFILE_INFO *pSimulatedInfo) = 0;
			virtual HRESULT STDMETHODCALLTYPE ClearSimulatedProfileInfo() = 0;
		};

		MIDL_INTERFACE("DCB00001-570F-4A9B-8D69-199FDBA5723B")
		INetworkListManagerEvents : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ConnectivityChanged(NLM_CONNECTIVITY newConnectivity) = 0;
		};

		typedef enum
		{
			NLM_NETWORK_CATEGORY_PUBLIC = 0,
			NLM_NETWORK_CATEGORY_PRIVATE = 0x1,
			NLM_NETWORK_CATEGORY_DOMAIN_AUTHENTICATED = 0x2
		} NLM_NETWORK_CATEGORY;

		MIDL_INTERFACE("DCB00002-570F-4A9B-8D69-199FDBA5723B")
		INetwork : public IDispatch
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetName(BSTR *pszNetworkName) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetName(BSTR szNetworkNewName) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDescription(BSTR *pszDescription) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDescription(BSTR szDescription) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkId(GUID *pgdGuidNetworkId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDomainType(NLM_DOMAIN_TYPE *pNetworkType) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetNetworkConnections(
				IEnumNetworkConnections **ppEnumNetworkConnection) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetTimeCreatedAndConnected(DWORD *pdwLowDateTimeCreated,
				DWORD *pdwHighDateTimeCreated, DWORD *pdwLowDateTimeConnected, DWORD *pdwHighDateTimeConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnectedToInternet(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnected(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectivity(NLM_CONNECTIVITY *pConnectivity) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetCategory(NLM_NETWORK_CATEGORY *pCategory) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetCategory(NLM_NETWORK_CATEGORY NewCategory) = 0;
		};


		MIDL_INTERFACE("DCB00003-570F-4A9B-8D69-199FDBA5723B")
		IEnumNetworks : public IDispatch
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get__NewEnum(IEnumVARIANT **ppEnumVar) = 0;
			virtual HRESULT STDMETHODCALLTYPE Next(ULONG celt, INetwork **rgelt, ULONG *pceltFetched) = 0;
			virtual HRESULT STDMETHODCALLTYPE Skip(ULONG celt) = 0;
			virtual HRESULT STDMETHODCALLTYPE Reset() = 0;
			virtual HRESULT STDMETHODCALLTYPE Clone(IEnumNetworks **ppEnumNetwork) = 0;
		};

		typedef enum
		{
			NLM_NETWORK_PROPERTY_CHANGE_CONNECTION = 0x1,
			NLM_NETWORK_PROPERTY_CHANGE_DESCRIPTION = 0x2,
			NLM_NETWORK_PROPERTY_CHANGE_NAME = 0x4,
			NLM_NETWORK_PROPERTY_CHANGE_ICON = 0x8,
			NLM_NETWORK_PROPERTY_CHANGE_CATEGORY_VALUE = 0x10
		} NLM_NETWORK_PROPERTY_CHANGE;

		MIDL_INTERFACE("DCB00004-570F-4A9B-8D69-199FDBA5723B")
		INetworkEvents : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE NetworkAdded(GUID networkId) = 0;
			virtual HRESULT STDMETHODCALLTYPE NetworkDeleted(GUID networkId) = 0;
			virtual HRESULT STDMETHODCALLTYPE NetworkConnectivityChanged(GUID networkId,
				NLM_CONNECTIVITY newConnectivity) = 0;
			virtual HRESULT STDMETHODCALLTYPE NetworkPropertyChanged(GUID networkId,
				NLM_NETWORK_PROPERTY_CHANGE flags) = 0;
		};

		MIDL_INTERFACE("DCB00005-570F-4A9B-8D69-199FDBA5723B")
		INetworkConnection : public IDispatch
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetNetwork(INetwork **ppNetwork) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnectedToInternet(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_IsConnected(VARIANT_BOOL *pbIsConnected) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectivity(NLM_CONNECTIVITY *pConnectivity) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetConnectionId(GUID *pgdConnectionId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetAdapterId(GUID *pgdAdapterId) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDomainType(NLM_DOMAIN_TYPE *pDomainType) = 0;
		};

		MIDL_INTERFACE("DCB00006-570F-4A9B-8D69-199FDBA5723B")
		IEnumNetworkConnections : public IDispatch
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE get__NewEnum(IEnumVARIANT **ppEnumVar) = 0;
			virtual HRESULT STDMETHODCALLTYPE Next(ULONG celt, INetworkConnection **rgelt,
				ULONG *pceltFetched) = 0;
			virtual HRESULT STDMETHODCALLTYPE Skip(ULONG celt) = 0;
			virtual HRESULT STDMETHODCALLTYPE Reset() = 0;
			virtual HRESULT STDMETHODCALLTYPE Clone(IEnumNetworkConnections **ppEnumNetwork) = 0;
		};

		typedef enum
		{
			NLM_CONNECTION_PROPERTY_CHANGE_AUTHENTICATION = 0x1
		} NLM_CONNECTION_PROPERTY_CHANGE;

		MIDL_INTERFACE("DCB00007-570F-4A9B-8D69-199FDBA5723B")
		INetworkConnectionEvents : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE NetworkConnectionConnectivityChanged(GUID connectionId,
				NLM_CONNECTIVITY newConnectivity) = 0;
			virtual HRESULT STDMETHODCALLTYPE NetworkConnectionPropertyChanged(GUID connectionId,
				NLM_CONNECTION_PROPERTY_CHANGE flags) = 0;
		};

		MIDL_INTERFACE("DCB00008-570F-4A9B-8D69-199FDBA5723B")
		INetworkCostManager : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetCost(DWORD *pCost, NLM_SOCKADDR *pDestIPAddr) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDataPlanStatus(NLM_DATAPLAN_STATUS *pDataPlanStatus,
				NLM_SOCKADDR *pDestIPAddr) = 0;
			virtual HRESULT STDMETHODCALLTYPE SetDestinationAddresses(UINT32 length,
				NLM_SOCKADDR *pDestIPAddrList, VARIANT_BOOL bAppend) = 0;
		};

		MIDL_INTERFACE("DCB00009-570F-4A9B-8D69-199FDBA5723B")
		INetworkCostManagerEvents : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE CostChanged(DWORD newCost, NLM_SOCKADDR *pDestAddr) = 0;
			virtual HRESULT STDMETHODCALLTYPE DataPlanStatusChanged(NLM_SOCKADDR *pDestAddr) = 0;
		};

		MIDL_INTERFACE("DCB0000a-570F-4A9B-8D69-199FDBA5723B")
		INetworkConnectionCost : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE GetCost(DWORD *pCost) = 0;
			virtual HRESULT STDMETHODCALLTYPE GetDataPlanStatus(NLM_DATAPLAN_STATUS *pDataPlanStatus) = 0;
		};

		MIDL_INTERFACE("DCB0000b-570F-4A9B-8D69-199FDBA5723B")
		INetworkConnectionCostEvents : public IUnknown
		{
		public:
			virtual HRESULT STDMETHODCALLTYPE ConnectionCostChanged(GUID connectionId, DWORD newCost) = 0;
			virtual HRESULT STDMETHODCALLTYPE ConnectionDataPlanStatusChanged(GUID connectionId) = 0;
		};

		class DECLSPEC_UUID("DCB00C01-570F-4A9B-8D69-199FDBA5723B")
		NetworkListManager;
	}
}