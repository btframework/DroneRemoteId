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

#include "..\Common\wclErrors.h"

using namespace wclCommon;

namespace wclWiFi
{
	/* WLAN subsystem error codes. */

	/// <summary> The base error code for the WLAN subsystem. </summary>
	const int WCL_E_WLAN_BASE = 0x00020000;
	/// <summary> Unable to load the WiFi subsystem. </summary>
	const int WCL_E_WLAN_UNABLE_LOAD = WCL_E_WLAN_BASE + 0x0000;
	/// <summary> The WiFi subsystem was not loaded. </summary>
	const int WCL_E_WLAN_NOT_LOADED = WCL_E_WLAN_BASE + 0x0001;
	/// <summary> The WiFi subsystem can not create synchronization mutex
	///   object. </summary>
	const int WCL_E_WLAN_UNABLE_CREATE_MUTEX = WCL_E_WLAN_BASE + 0x0002;

	/* Common WiFi Framework error codes. */

	/// <summary> The base error code for the WiFi framework. </summary>
	const int WCL_E_WIFI_BASE = WCL_E_WLAN_BASE + 0x1000;
	/// <summary> A WiFi is already opened. </summary>
	const int WCL_E_WIFI_OPENED = WCL_E_WIFI_BASE + 0x0000;
	/// <summary> A WiFi is already closed. </summary>
	const int WCL_E_WIFI_CLOSED = WCL_E_WIFI_BASE + 0x0001;
	/// <summary> A WiFi was not opened (is not active;. </summary>
	const int WCL_E_WIFI_NOT_ACTIVE = WCL_E_WIFI_BASE + 0x0002;
	/// <summary> A calling function was not found in WLAN API. </summary>
	const int WCL_E_WIFI_FUNCTION_NOT_FOUND = WCL_E_WIFI_BASE + 0x0003;
	/// <summary> The caller does not have sufficient permissions. </summary>
	const int WCL_E_WIFI_ACCESS_DENIED = WCL_E_WIFI_BASE + 0x0004;
	/// <summary> An invalid WLAN client handle used. </summary>
	const int WCL_E_WIFI_INVALID_CLIENT_HANDLE = WCL_E_WIFI_BASE + 0x0005;
	/// <summary> WLAN API can not allocate memory to execute an
	///   requested operation. </summary>
	const int WCL_E_WIFI_NOT_ENOUGH_MEMORY = WCL_E_WIFI_BASE + 0x0006;
	/// <summary> The required operation is not supported by the WiFi
	///   subsystem. </summary>
	const int WCL_E_WIFI_NOT_SUPPORTED = WCL_E_WIFI_BASE + 0x0007;
	/// <summary> An unexpected exception was raised during WLAN API
	///   call. </summary>
	const int WCL_E_WIFI_UNEXPECTED = WCL_E_WIFI_BASE + 0x0008;
	/// <summary> One or more arguments passed into the WLAN API are
	///   invalid. </summary>
	const int WCL_E_WIFI_INVALID_ARGUMENT = WCL_E_WIFI_BASE + 0x0009;
	/// <summary> The WiFi hardware or driver was not found. </summary>
	const int WCL_E_WIFI_NOT_AVAILABLE = WCL_E_WIFI_BASE + 0x000A;
	/// <summary> Too many sessions to WLAN subsystem are opened. </summary>
	const int WCL_E_WIFI_TOO_MANY_SESSIONS = WCL_E_WIFI_BASE + 0x000B;
	/// <summary> The resource is not in the correct state to perform the
	///   requested operation. This error is returned if the wireless Hosted
	///   Network is disabled by group policy on a domain. </summary>
	const int WCL_E_WIFI_INVALID_STATE = WCL_E_WIFI_BASE + 0x000C;
	/// <summary> The radio associated with the interface is turned off.
	///   There are no available networks when the radio is off. </summary>
	const int WCL_E_WIFI_RADIO_OFF = WCL_E_WIFI_BASE + 0x000D;
	/// <summary> Internal WLAN driver error. </summary>
	const int WCL_E_WIFI_RPC_SUBSYSTEM = WCL_E_WIFI_BASE + 0x000E;
	/// <summary> The PHY with given index was not found. </summary>
	const int WCL_E_WIFI_PHY_NOT_FOUND = WCL_E_WIFI_BASE + 0x000F;
	/// <summary> The configuration data for the wireless Hosted Network is
	///   not configured. This error is returned if the application queries
	///   the Hosted Network Profile or Hosted Network Connection Settings
	///   before a SSID is configured in the wireless Hosted Network. </summary>
	const int WCL_E_WIFI_BAD_CONFIGURATION = WCL_E_WIFI_BASE + 0x0010;
	/// <summary> The wireless profile specified by was not found in the profile
	///   store. </summary>
	const int WCL_E_WIFI_NOT_FOUND = WCL_E_WIFI_BASE + 0x0011;
	/// <summary> The WLAN profile already exists. Typically, this return value
	///   is used when <c>Overwrite</c> is <c>False</c>, however, if
	///   <c>Overwrite</c> is <c>True</c> and <c>Flags</c> specifies a different
	///   profile type than the one used by the existing profile, then the
	///   existing profile will not be overwritten and
	///   <c>WCL_E_WIFI_ALREADY_EXISTS</c> will be returned. </summary>
	const int WCL_E_WIFI_ALREADY_EXISTS = WCL_E_WIFI_BASE + 0x0012;
	/// <summary> The profile is not valid. </summary>
	const int WCL_E_WIFI_BAD_PROFILE = WCL_E_WIFI_BASE + 0x0013;
	/// <summary> The interface does not support one or more of the capabilities
	///   specified in the profile. For example, if a profile specifies the use
	///   of WPA2 when the NIC only supports WPA, then this error code is
	///   returned. Also, if a profile specifies the use of FIPS mode when the
	///   NIC does not support FIPS mode, then this error code is
	///   returned. </summary>
	const int WCL_E_WIFI_NO_MATCH = WCL_E_WIFI_BASE + 0x0014;
	/// <summary> This error is returned if no user custom data exists for the
	///   profile specified. </summary>
	const int WCL_E_WIFI_DATA_NOT_FOUND = WCL_E_WIFI_BASE + 0x0015;
	/// <summary> Unable to create thread. </summary>
	const int WCL_E_WIFI_CREATE_THREAD_FAILED = WCL_E_WIFI_BASE + 0x0016;
	/// <summary> Unable to get operation thread result code. </summary> 
	const int WCL_E_WIFI_GET_THREAD_RESULT_FAILED = WCL_E_WIFI_BASE + 0x0017;
	/// <summary> Unable to start asynchronous operation. </summary>
	const int WCL_E_WIFI_START_ASYNC_OPERATION_FAILED = WCL_E_WIFI_BASE + 0x0018;
	/// <summary> Unable to get asynchronous operation information
	///   interface. </summary>
	const int WCL_E_WIFI_WAIT_ASYNC_OPERATION_FAILED = WCL_E_WIFI_BASE + 0x0019;
	/// <summary> Unable to get asynchronous operation result. </summary> 
	const int WCL_E_WIFI_GET_ASYNC_RESULT_FAILED = WCL_E_WIFI_BASE + 0x001A;
	/// <summary> Unable to get found adapters count. </summary>
	const int WCL_E_WIFI_GET_SIZE_FAILED = WCL_E_WIFI_BASE + 0x001B;
	/// <summary> Unable to change the WiFi Adapter state. </summary>
	const int WCL_E_WIFI_CHANGE_STATE_FAILED = WCL_E_WIFI_BASE + 0x001C;
	/// <summary> The feature is not supported on this platform. </summary>
	const int WCL_E_WIFI_FEATURE_NOT_SUPPORTED = WCL_E_WIFI_BASE + 0x001D;
	/// <summary> One or more BSS ID in the BSS list used in Connect operation
	///   is invalid. </summary>
	const int WCL_E_WIFI_ONE_OF_MORE_BSS_IS_INVALID = WCL_E_WIFI_BASE + 0x001E;
	/// <summary> The system cannot find the path specified. </summary>
	const int WCL_E_WIFI_PATH_NOT_FOUND = WCL_E_WIFI_BASE + 0x001F;
	/// <summary> The data is not valid. </summary>
	const int WCL_E_WIFI_INVALID_DATA = WCL_E_WIFI_BASE + 0x0020;
	/// <summary> One or more arguments are not correct. </summary>
	const int WCL_E_WIFI_BAD_ARGUMENTS = WCL_E_WIFI_BASE + 0x0021;
	/// <summary> The configuration registry key could not be opened. </summary>
	const int WCL_E_WIFI_CANTOPEN = WCL_E_WIFI_BASE + 0x0022;
	/// <summary> The data supplied is of the wrong type. </summary>
	const int WCL_E_WIFI_DATATYPE_MISMATCH = WCL_E_WIFI_BASE + 0x0023;
	/// <summary> The error indicates that the WiFi access disabled in the system
	///   settings. </summary>
	const int WCL_E_WIFI_ACCESS_DENIED_BY_SYSTEM = WCL_E_WIFI_BASE + 0x0024;
	/// <summary> The error indicates that the WiFi access disabled for the classic
	///   applications in system settings and used did not grant access during
	///   access request. </summary>
	const int WCL_E_WIFI_ACCESS_DENIED_BY_USER = WCL_E_WIFI_BASE + 0x0025;
	
	/* AEP authentication error codes. */

	/// <summary> The base error code for WiFi EAP errors. </summary>
	const int WCL_E_WIFI_EAP_BASE = WCL_E_WIFI_BASE + 0x0100;
	/// <summary> The EAPHost received EAP failure after the identity exchange.
	///   There is likely a problem with the authenticating user
	///   account. </summary>
	const int WCL_E_WIFI_EAP_USER_ACCOUNT_OTHER_ERROR = WCL_E_WIFI_EAP_BASE + 0x0000;
	/// <summary> The certificate store can not be accessed on either the
	///   authenticator or the peer. </summary>
	const int WCL_E_WIFI_EAP_CERT_STORE_INACCESSIBLE = WCL_E_WIFI_EAP_BASE + 0x0001;
	/// <summary> The requested EAP method is not installed. </summary>
	const int WCL_E_WIFI_EAP_HOST_METHOD_NOT_INSTALLED = WCL_E_WIFI_EAP_BASE + 0x0002;
	/// <summary> The EAPHost is not able to communicate with the EAP quarantine
	///   enforcement client (QEC) on a client with Network Access Protection
	///   (NAP) enabled. </summary>
	const int WCL_E_WIFI_EAP_HOST_QEC_INACCESSIBLE = WCL_E_WIFI_EAP_BASE + 0x0003;
	/// <summary> The EAPHost returns this error if the authenticator fails the
	///   authentication after the peer sent its identity. </summary>
	const int WCL_E_WIFI_EAP_HOST_IDENTITY_UNKNOWN = WCL_E_WIFI_EAP_BASE + 0x0004;
	/// <summary> The EAPHost returns this error on authentication
	///   failure. </summary>
	const int WCL_E_WIFI_EAP_AUTHENTICATION_FAILED = WCL_E_WIFI_EAP_BASE + 0x0005;
	/// <summary> The EAPHost returns this error when the client and the server
	///   are not configured with compatible EAP types. </summary>
	const int WCL_E_WIFI_EAP_HOST_NEGOTIATION_FAILED = WCL_E_WIFI_EAP_BASE + 0x0006;
	/// <summary> The EAPMethod received an EAP packet that cannot be
	///   processed. </summary>
	const int WCL_E_WIFI_EAP_HOST_METHOD_INVALID_PACKET = WCL_E_WIFI_EAP_BASE + 0x0007;
	/// <summary> The EAPHost received a packet that cannot be
	///   processed. </summary>
	const int WCL_E_WIFI_EAP_HOST_REMOTE_INVALID_PACKET = WCL_E_WIFI_EAP_BASE + 0x0008;
	/// <summary> The EAPHost configuration schema validation failed. </summary>
	const int WCL_E_WIFI_EAP_HOST_XML_MALFORMED = WCL_E_WIFI_EAP_BASE + 0x0009;
	/// <summary> The EAP method does not support single sign-on for the provided
	///   configuration. </summary>
	const int WCL_E_WIFI_EAP_METHOD_CONFIG_DOES_NOT_SUPPORT_SSO = WCL_E_WIFI_EAP_BASE + 0x000A;
	/// <summary> The EAPHost returns this error when a configured EAP method does
	///   not support a requested operation (procedure call). </summary>
	const int WCL_E_WIFI_EAP_HOST_METHOD_OPERATION_NOT_SUPPORTED = WCL_E_WIFI_EAP_BASE + 0x000B;
	/// <summary> The EAPHost could not find the user certificate for
	///   authentication. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_NOT_FOUND = WCL_E_WIFI_EAP_BASE + 0x000C;
	/// <summary> The user certificate being used for authentication does not have
	///   a proper extended key usage (EKU) set. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_INVALID = WCL_E_WIFI_EAP_BASE + 0x000D;
	/// <summary> The EAPhost found a user certificate which has
	///   expired. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_EXPIRED = WCL_E_WIFI_EAP_BASE + 0x000E;
	/// <summary> The user certificate being used for authentication has been
	///   revoked. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_REVOKED = WCL_E_WIFI_EAP_BASE + 0x000F;
	/// <summary> An unknown error occurred with the user certificate being used
	///   for authentication. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_OTHER_ERROR = WCL_E_WIFI_EAP_BASE + 0x0010;
	/// <summary> The authenticator rejected the user certificate being used for
	///   authentication. </summary>
	const int WCL_E_WIFI_EAP_USER_CERT_REJECTED = WCL_E_WIFI_EAP_BASE + 0x0011;
	/// <summary> The authenticator rejected the user credentials for
	///   authentication. </summary>
	const int WCL_E_WIFI_EAP_USER_CREDENTIALS_REJECTED = WCL_E_WIFI_EAP_BASE + 0x0012;
	/// <summary> The authenticator rejected the user credentials for
	///   authentication. </summary>
	const int WCL_E_WIFI_EAP_USER_NAME_PASSWORD_REJECTED = WCL_E_WIFI_EAP_BASE + 0x0013;
	/// <summary> No smart card reader was present. </summary>
	const int WCL_E_WIFI_EAP_NO_SMART_CARD_READER = WCL_E_WIFI_EAP_BASE + 0x0014;
	/// <summary> The server certificate being user for authentication does not
	///   have a proper EKU set. </summary>
	const int WCL_E_WIFI_EAP_SERVER_CERT_INVALID = WCL_E_WIFI_EAP_BASE + 0x0015;
	/// <summary> The EAPhost found a server certificate which has
	///   expired. </summary>
	const int WCL_E_WIFI_EAP_SERVER_CERT_EXPIRED = WCL_E_WIFI_EAP_BASE + 0x0016;
	/// <summary> The server certificate being used for authentication has been
	///   revoked. </summary>
	const int WCL_E_WIFI_EAP_SERVER_CERT_REVOKED = WCL_E_WIFI_EAP_BASE + 0x0017;
	/// <summary> An unknown error occurred with the server certificate being used
	///   for authentication. </summary>
	const int WCL_E_WIFI_EAP_SERVER_CERT_OTHER_ERROR = WCL_E_WIFI_EAP_BASE + 0x0018;
	/// <summary> The EAPHost could not find a certificate in trusted root
	///   certificate store for user certificate validation. </summary>
	const int WCL_E_WIFI_EAP_USER_ROOT_CERT_NOT_FOUND = WCL_E_WIFI_EAP_BASE + 0x0019;
	/// <summary> The authentication failed because the root certificate used for
	///   this network is not valid. </summary>
	const int WCL_E_WIFI_EAP_USER_ROOT_CERT_INVALID = WCL_E_WIFI_EAP_BASE + 0x001A;
	/// <summary> The trusted root certificate needed for user certificate
	///   validation has expired. </summary>
	const int WCL_E_WIFI_EAP_USER_ROOT_CERT_EXPIRED = WCL_E_WIFI_EAP_BASE + 0x001B;
	/// <summary> The EAPHost could not find a root certificate in the trusted
	///   root certificate store for server certificate validation. </summary>
	const int WCL_E_WIFI_EAP_SERVER_ROOT_CERT_NOT_FOUND = WCL_E_WIFI_EAP_BASE + 0x001C;

	/* WLAN reason codes. */

	/// <summary> The base code for the WiFi subsystem reasons. </summary>
	const int WCL_E_WIFI_RES_BASE = WCL_E_WLAN_BASE + 0x2000;
	/// <summary> The reason for failure is unknown. </summary>
	const int WCL_E_WIFI_RES_UNKNOWN = WCL_E_WIFI_RES_BASE + 0x0000;
	/// <summary> The wireless network is not compatible. </summary>
	const int WCL_E_WIFI_RES_NETWORK_NOT_COMPATIBLE = WCL_E_WIFI_RES_BASE + 0x0001;
	/// <summary> The wireless network profile is not compatible. </summary>
	const int WCL_E_WIFI_RES_PROFILE_NOT_COMPATIBLE = WCL_E_WIFI_RES_BASE + 0x0002;
	/// <summary> The profile specifies no auto connection. </summary>
	const int WCL_E_WIFI_RES_NO_AUTO_CONNECTION = WCL_E_WIFI_RES_BASE + 0x0003;
	/// <summary> The wireless network is not visible. </summary>
	const int WCL_E_WIFI_RES_NOT_VISIBLE = WCL_E_WIFI_RES_BASE + 0x0004;
	/// <summary> The wireless network is blocked by group policy. </summary>
	const int WCL_E_WIFI_RES_GP_DENIED = WCL_E_WIFI_RES_BASE + 0x0005;
	/// <summary> The wireless network is blocked by the user. </summary>
	const int WCL_E_WIFI_RES_USER_DENIED = WCL_E_WIFI_RES_BASE + 0x0006;
	/// <summary> The basic service set (BSS; type is not allowed on this wireless
	///   adapter. </summary>
	const int WCL_E_WIFI_RES_BSS_TYPE_NOT_ALLOWED = WCL_E_WIFI_RES_BASE + 0x0007;
	/// <summary> The wireless network is in the failed list. </summary>
	const int WCL_E_WIFI_RES_IN_FAILED_LIST = WCL_E_WIFI_RES_BASE + 0x0008;
	/// <summary> The wireless network is in the blocked list. </summary>
	const int WCL_E_WIFI_RES_IN_BLOCKED_LIST = WCL_E_WIFI_RES_BASE + 0x0009;
	/// <summary> The size of the service set identifiers (SSID; list exceeds the
	///   maximum size supported by the adapter. </summary>
	const int WCL_E_WIFI_RES_SSID_LIST_TOO_LONG = WCL_E_WIFI_RES_BASE + 0x000A;
	/// <summary> The Media Specific Module (MSM; connect call fails. </summary>
	const int WCL_E_WIFI_RES_CONNECT_CALL_FAIL = WCL_E_WIFI_RES_BASE + 0x000B;
	/// <summary> The MSM scan call fails. </summary>
	const int WCL_E_WIFI_RES_SCAN_CALL_FAIL = WCL_E_WIFI_RES_BASE + 0x000C;
	/// <summary> <para> The specified network is not available. </para>
	///   <para> This reason code is also used when there is a mismatch between
	///   capabilities specified in an XML profile and interface and/or network
	///   capabilities. For example, if a profile specifies the use of WPA2 when
	///   the NIC only supports WPA, then this error code is returned. Also, if
	///   a profile specifies the use of FIPS mode when the NIC does not
	///   support FIPS mode, then this error code is returned. </para> </summary>
	const int WCL_E_WIFI_RES_NETWORK_NOT_AVAILABLE = WCL_E_WIFI_RES_BASE + 0x000D;
	/// <summary> The profile was changed or deleted before the connection was
	///   established. </summary>
	const int WCL_E_WIFI_RES_PROFILE_CHANGED_OR_DELETED = WCL_E_WIFI_RES_BASE + 0x000E;
	/// <summary> The profile key does not match the network key. </summary>
	const int WCL_E_WIFI_RES_KEY_MISMATCH = WCL_E_WIFI_RES_BASE + 0x000F;
	/// <summary> The user is not responding. </summary>
	const int WCL_E_WIFI_RES_USER_NOT_RESPOND = WCL_E_WIFI_RES_BASE + 0x0010;
	/// <summary> An application tried to apply a wireless Hosted Network profile
	///   to a physical wireless network adapter using the WlanSetProfile
	///   function, rather than to a virtual device. </summary>
	const int WCL_E_WIFI_RES_AP_PROFILE_NOT_ALLOWED_FOR_CLIENT = WCL_E_WIFI_RES_BASE + 0x0011;
	/// <summary> An application tried to apply a wireless Hosted Network profile
	///   to a physical wireless network adapter using the <c>SetProfile</c>
	///   method, rather than to a virtual device. </summary>
	const int WCL_E_WIFI_RES_AP_PROFILE_NOT_ALLOWED = WCL_E_WIFI_RES_BASE + 0x0012;
	/// <summary> The profile invalid according to the schema. </summary>
	const int WCL_E_WIFI_RES_INVALID_PROFILE_SCHEMA = WCL_E_WIFI_RES_BASE + 0x0013;
	/// <summary> The <c>WLANProfile</c> element is missing. </summary>
	const int WCL_E_WIFI_RES_PROFILE_MISSING = WCL_E_WIFI_RES_BASE + 0x0014;
	/// <summary> The name of the profile is invalid. </summary>
	const int WCL_E_WIFI_RES_INVALID_PROFILE_NAME = WCL_E_WIFI_RES_BASE + 0x0015;
	/// <summary> The type of the profile is invalid. </summary>
	const int WCL_E_WIFI_RES_INVALID_PROFILE_TYPE = WCL_E_WIFI_RES_BASE + 0x0016;
	/// <summary> The PHY type is invalid. </summary>
	const int WCL_E_WIFI_RES_INVALID_PHY_TYPE = WCL_E_WIFI_RES_BASE + 0x0017;
	/// <summary> The MSM security settings are missing. </summary>
	const int WCL_E_WIFI_RES_MSM_SECURITY_MISSING = WCL_E_WIFI_RES_BASE + 0x0018;
	/// <summary> The independent hardware vendor (IHV; security settings are
	///   missing. </summary>
	const int WCL_E_WIFI_RES_IHV_SECURITY_NOT_SUPPORTED = WCL_E_WIFI_RES_BASE + 0x0019;
	/// <summary> The IHV profile OUI did not match with the adapter
	///   OUI. </summary>
	const int WCL_E_WIFI_RES_IHV_OUI_MISMATCH = WCL_E_WIFI_RES_BASE + 0x001A;
	/// <summary> The IHV OUI settings are missing. </summary>
	const int WCL_E_WIFI_RES_IHV_OUI_MISSING = WCL_E_WIFI_RES_BASE + 0x001B;
	/// <summary> The IHV security settings are missing. </summary>
	const int WCL_E_WIFI_RES_IHV_SETTINGS_MISSING = WCL_E_WIFI_RES_BASE + 0x001C;
	/// <summary> An application tried to apply an IHV profile on an adapter that
	///   does not support IHV connectivity settings. </summary>
	const int WCL_E_WIFI_RES_IHV_CONNECTIVITY_NOT_SUPPORTED = WCL_E_WIFI_RES_BASE + 0x001D;
	/// <summary> The security settings conflict. </summary>
	const int WCL_E_WIFI_RES_CONFLICT_SECURITY = WCL_E_WIFI_RES_BASE + 0x001E;
	/// <summary> The security settings are missing. </summary>
	const int WCL_E_WIFI_RES_SECURITY_MISSING = WCL_E_WIFI_RES_BASE + 0x001F;
	/// <summary> The BSS type is not valid. </summary>
	const int WCL_E_WIFI_RES_INVALID_BSS_TYPE = WCL_E_WIFI_RES_BASE + 0x0020;
	/// <summary> Automatic connection cannot be set for an ad hoc
	///   network. </summary>
	const int WCL_E_WIFI_RES_INVALID_ADHOC_CONNECTION_MODE = WCL_E_WIFI_RES_BASE + 0x0021;
	/// <summary> Non-broadcast cannot be set for an ad hoc network. </summary>
	const int WCL_E_WIFI_RES_NON_BROADCAST_SET_FOR_ADHOC = WCL_E_WIFI_RES_BASE + 0x0022;
	/// <summary> Auto-switch cannot be set for an ad hoc network. </summary>
	const int WCL_E_WIFI_RES_AUTO_SWITCH_SET_FOR_ADHOC = WCL_E_WIFI_RES_BASE + 0x0023;
	/// <summary> Auto-switch cannot be set for a manual connection
	///   profile. </summary>
	const int WCL_E_WIFI_RES_AUTO_SWITCH_SET_FOR_MANUAL_CONNECTION = WCL_E_WIFI_RES_BASE + 0x0024;
	/// <summary> The IHV 802.1X security settings are missing. </summary>
	const int WCL_E_WIFI_RES_IHV_SECURITY_ONEX_MISSING = WCL_E_WIFI_RES_BASE + 0x0025;
	/// <summary> The SSID in the profile is invalid or missing. </summary>
	const int WCL_E_WIFI_RES_PROFILE_SSID_INVALID = WCL_E_WIFI_RES_BASE + 0x0026;
	/// <summary> Too many SSIDs were specified in the profile. </summary>
	const int WCL_E_WIFI_RES_TOO_MANY_SSID = WCL_E_WIFI_RES_BASE + 0x0027;
	/// <summary> An application tried to apply a wireless Hosted Network profile
	///   to a physical network adapter NIC using the <c>SetProfile</c> method,
	///   and specified an unacceptable value for the maximum number of clients
	///   allowed. </summary>
	const int WCL_E_WIFI_RES_BAD_MAX_NUMBER_OF_CLIENTS_FOR_AP = WCL_E_WIFI_RES_BASE + 0x0028;
	/// <summary> The channel specified is invalid. </summary>
	const int WCL_E_WIFI_RES_INVALID_CHANNEL = WCL_E_WIFI_RES_BASE + 0x0029;
	/// <summary> The operation mode is not supported. </summary>
	const int WCL_E_WIFI_RES_OPERATION_MODE_NOT_SUPPORTED = WCL_E_WIFI_RES_BASE + 0x002A;
	/// <summary> An internal operating system error occurred with the wireless
	///   Hosted Network. </summary>
	const int WCL_E_WIFI_RES_AUTO_AP_PROFILE_NOT_ALLOWED = WCL_E_WIFI_RES_BASE + 0x002B;
	/// <summary> An internal operating system error occurred with the wireless
	///   Hosted Network. </summary>
	const int WCL_E_WIFI_RES_AUTO_CONNECTION_NOT_ALLOWED = WCL_E_WIFI_RES_BASE + 0x002C;
	/// <summary> The security settings are not supported by the operating
	///   system. </summary>
	const int WCL_E_WIFI_RES_UNSUPPORTED_SECURITY_SET_BY_OS = WCL_E_WIFI_RES_BASE + 0x002D;
	/// <summary> The security settings are not supported. </summary>
	const int WCL_E_WIFI_RES_UNSUPPORTED_SECURITY_SET = WCL_E_WIFI_RES_BASE + 0x002E;
	/// <summary> The BSS type does not match. </summary>
	const int WCL_E_WIFI_RES_BSS_TYPE_UNMATCH = WCL_E_WIFI_RES_BASE + 0x002F;
	/// <summary> The PHY type does not match. </summary>
	const int WCL_E_WIFI_RES_PHY_TYPE_UNMATCH = WCL_E_WIFI_RES_BASE + 0x0030;
	/// <summary> The data rate does not match. </summary>
	const int WCL_E_WIFI_RES_DATARATE_UNMATCH = WCL_E_WIFI_RES_BASE + 0x0031;
	/// <summary> User has canceled the operation. </summary>
	const int WCL_E_WIFI_RES_USER_CANCELLED = WCL_E_WIFI_RES_BASE + 0x0032;
	/// <summary> Driver disconnected while associating. </summary>
	const int WCL_E_WIFI_RES_ASSOCIATION_FAILURE = WCL_E_WIFI_RES_BASE + 0x0033;
	/// <summary> Association timed out. </summary>
	const int WCL_E_WIFI_RES_ASSOCIATION_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x0034;
	/// <summary> Pre-association security failure. </summary>
	const int WCL_E_WIFI_RES_PRE_SECURITY_FAILURE = WCL_E_WIFI_RES_BASE + 0x0035;
	/// <summary> Failed to start security after association. </summary>
	const int WCL_E_WIFI_RES_START_SECURITY_FAILURE = WCL_E_WIFI_RES_BASE + 0x0036;
	/// <summary> Security ends up with failure. </summary>
	const int WCL_E_WIFI_RES_SECURITY_FAILURE = WCL_E_WIFI_RES_BASE + 0x0037;
	/// <summary> Security operation times out. </summary>
	const int WCL_E_WIFI_RES_SECURITY_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x0038;
	/// <summary> Driver disconnected while roaming. </summary>
	const int WCL_E_WIFI_RES_ROAMING_FAILURE = WCL_E_WIFI_RES_BASE + 0x0039;
	/// <summary> Failed to start security for roaming. </summary>
	const int WCL_E_WIFI_RES_ROAMING_SECURITY_FAILURE = WCL_E_WIFI_RES_BASE + 0x003A;
	/// <summary> Failed to start security for ad hoc peer. </summary>
	const int WCL_E_WIFI_RES_ADHOC_SECURITY_FAILURE = WCL_E_WIFI_RES_BASE + 0x003B;
	/// <summary> Driver disconnected. </summary>
	const int WCL_E_WIFI_RES_DRIVER_DISCONNECTED = WCL_E_WIFI_RES_BASE + 0x003C;
	/// <summary> Driver failed to perform some operations. </summary>
	const int WCL_E_WIFI_RES_DRIVER_OPERATION_FAILURE = WCL_E_WIFI_RES_BASE + 0x003D;
	/// <summary> The IHV service is not available. </summary>
	const int WCL_E_WIFI_RES_IHV_NOT_AVAILABLE = WCL_E_WIFI_RES_BASE + 0x003E;
	/// <summary> The response from the IHV service timed out. </summary>
	const int WCL_E_WIFI_RES_IHV_NOT_RESPONDING = WCL_E_WIFI_RES_BASE + 0x003F;
	/// <summary> Timed out waiting for the driver to disconnect. </summary>
	const int WCL_E_WIFI_RES_DISCONNECT_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x0040;
	/// <summary> An internal error prevented the operation from being
	///   completed. </summary>
	const int WCL_E_WIFI_RES_INTERNAL_FAILURE = WCL_E_WIFI_RES_BASE + 0x0041;
	/// <summary> A user interaction request timed out. </summary>
	const int WCL_E_WIFI_RES_UI_REQUEST_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x0042;
	/// <summary> Roaming too often. Post security was not completed after 5
	///   attempts. </summary>
	const int WCL_E_WIFI_RES_TOO_MANY_SECURITY_ATTEMPTS = WCL_E_WIFI_RES_BASE + 0x0043;
	/// <summary> An internal operating system error occurred that resulted in a
	///   failure to start the wireless Hosted Network. </summary>
	const int WCL_E_WIFI_RES_AP_STARTING_FAILURE = WCL_E_WIFI_RES_BASE + 0x0044;
	/// <summary> Failed to connect because no connectable Access Point was
	///   visible. </summary>
	const int WCL_E_WIFI_RES_NO_VISIBLE_AP = WCL_E_WIFI_RES_BASE + 0x0045;

	/// <summary> Key index specified is not valid. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_KEY_INDEX = WCL_E_WIFI_RES_BASE + 0x0046;
	/// <summary> Key required, PSK present. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_PSK_PRESENT = WCL_E_WIFI_RES_BASE + 0x0047;
	/// <summary> Invalid key length. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_KEY_LENGTH = WCL_E_WIFI_RES_BASE + 0x0048;
	/// <summary> Invalid PSK length. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_PSK_LENGTH = WCL_E_WIFI_RES_BASE + 0x0049;
	/// <summary> No auth/cipher pairs specified. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_NO_AUTH_CIPHER_SPECIFIED = WCL_E_WIFI_RES_BASE + 0x004A;
	/// <summary> Too many auth/cipher pairs specified. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_TOO_MANY_AUTH_CIPHER_SPECIFIED = WCL_E_WIFI_RES_BASE + 0x004B;
	/// <summary> Profile contains duplicate auth/cipher pair. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_DUPLICATE_AUTH_CIPHER = WCL_E_WIFI_RES_BASE + 0x004C;
	/// <summary> Profile raw data is invalid. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_RAWDATA_INVALID = WCL_E_WIFI_RES_BASE + 0x004D;
	/// <summary> Invalid auth/cipher combination. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_AUTH_CIPHER = WCL_E_WIFI_RES_BASE + 0x004E;
	/// <summary> 802.1X disabled when it is required to be enabled. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_ONEX_DISABLED = WCL_E_WIFI_RES_BASE + 0x004F;
	/// <summary> 802.1X enabled when it is required to be disabled. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_ONEX_ENABLED = WCL_E_WIFI_RES_BASE + 0x0050;
	/// <summary> Invalid PMK cache mode. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_PMKCACHE_MODE = WCL_E_WIFI_RES_BASE + 0x0051;
	/// <summary> Invalid PMK cache size. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_PMKCACHE_SIZE = WCL_E_WIFI_RES_BASE + 0x0052;
	/// <summary> Invalid PMK cache TTL. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_PMKCACHE_TTL = WCL_E_WIFI_RES_BASE + 0x0053;
	/// <summary> Invalid pre-auth mode. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_PREAUTH_MODE = WCL_E_WIFI_RES_BASE + 0x0054;
	/// <summary> Invalid pre-auth throttle. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_PREAUTH_THROTTLE = WCL_E_WIFI_RES_BASE + 0x0055;
	/// <summary> Pre-auth enabled when PMK cache is disabled. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_PREAUTH_ONLY_ENABLED = WCL_E_WIFI_RES_BASE + 0x0056;
	/// <summary> Capability matching failed at network. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_NETWORK = WCL_E_WIFI_RES_BASE + 0x0057;
	/// <summary> Capability matching failed at NIC. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_NIC = WCL_E_WIFI_RES_BASE + 0x0058;
	/// <summary> Capability matching failed at profile. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_PROFILE = WCL_E_WIFI_RES_BASE + 0x0059;
	/// <summary> Network does not support specified capability type. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_DISCOVERY = WCL_E_WIFI_RES_BASE + 0x005A;
	/// <summary> Passphrase contains invalid character. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_PASSPHRASE_CHAR = WCL_E_WIFI_RES_BASE + 0x005B;
	/// <summary> Key material contains invalid character. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_KEYMATERIAL_CHAR = WCL_E_WIFI_RES_BASE + 0x005C;
	/// <summary> The key type specified does not match the key
	///   material. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_WRONG_KEYTYPE = WCL_E_WIFI_RES_BASE + 0x005D;
	/// <summary> A mixed cell is suspected. The AP is not signaling that it is
	///   compatible with a privacy-enabled profile. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_MIXED_CELL = WCL_E_WIFI_RES_BASE + 0x005E;
	/// <summary> The number of authentication timers or the number of timeouts
	///   specified in the profile is invalid. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_AUTH_TIMERS_INVALID = WCL_E_WIFI_RES_BASE + 0x005F;
	/// <summary> The group key update interval specified in the profile is
	///   invalid. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_INVALID_GKEY_INTV = WCL_E_WIFI_RES_BASE + 0x0060;
	/// <summary> A "transition network" is suspected. Legacy 802.11 security is
	///   used for the next authentication attempt. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_TRANSITION_NETWORK = WCL_E_WIFI_RES_BASE + 0x0061;
	/// <summary> The key contains characters that are not in the ASCII character
	///   set. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_KEY_UNMAPPED_CHAR = WCL_E_WIFI_RES_BASE + 0x0062;
	/// <summary> Capability matching failed because the network does not support
	///   the authentication method in the profile. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_PROFILE_AUTH = WCL_E_WIFI_RES_BASE + 0x0063;
	/// <summary> Capability matching failed because the network does not support
	///   the cipher algorithm in the profile. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_PROFILE_CIPHER = WCL_E_WIFI_RES_BASE + 0x0064;
	/// <summary> FIPS 140-2 mode value in the profile is invalid. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_SAFE_MODE = WCL_E_WIFI_RES_BASE + 0x0065;
	/// <summary> Profile requires FIPS 140-2 mode, which is not supported by
	///   network interface card (NIC;. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_PROFILE_SAFE_MODE_NIC = WCL_E_WIFI_RES_BASE + 0x0066;
	/// <summary> Profile requires FIPS 140-2 mode, which is not supported by
	///    network. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_PROFILE_SAFE_MODE_NW = WCL_E_WIFI_RES_BASE + 0x0067;
	/// <summary> Profile specifies an unsupported authentication,
	///   mechanism. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_UNSUPPORTED_AUTH = WCL_E_WIFI_RES_BASE + 0x0068;
	/// <summary> Profile specifies an unsupported cipher. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PROFILE_UNSUPPORTED_CIPHER = WCL_E_WIFI_RES_BASE + 0x0069;
	/// <summary> Failed to queue the user interface request. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_UI_REQUEST_FAILURE = WCL_E_WIFI_RES_BASE + 0x006A;
	/// <summary> The wireless LAN requires Management Frame Protection (MFP; and
	///   the network interface does not support MFP. For more information, see
	///   the IEEE 802.11w amendment to the 802.11 standard. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CAPABILITY_MFP_NW_NIC = WCL_E_WIFI_RES_BASE + 0x006B;
	/// <summary> 802.1X authentication did not start within configured
	///   time. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_AUTH_START_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x006C;
	/// <summary> 802.1X authentication did not complete within configured
	///   time. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_AUTH_SUCCESS_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x006D;
	/// <summary> Dynamic key exchange did not start within configured
	///   time. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_KEY_START_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x006E;
	/// <summary> Dynamic key exchange did not complete within configured
	///   time. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_KEY_SUCCESS_TIMEOUT = WCL_E_WIFI_RES_BASE + 0x006F;
	/// <summary> Message 3 of 4-way handshake has no key data. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M3_MISSING_KEY_DATA = WCL_E_WIFI_RES_BASE + 0x0070;
	/// <summary> Message 3 of 4-way handshake has no IE. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M3_MISSING_IE = WCL_E_WIFI_RES_BASE + 0x0071;
	/// <summary> Message 3 of 4-way handshake has no GRP key. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M3_MISSING_GRP_KEY = WCL_E_WIFI_RES_BASE + 0x0072;
	/// <summary> Matching security capabilities of IE in M3 failed. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PR_IE_MATCHING = WCL_E_WIFI_RES_BASE + 0x0073;
	/// <summary> Matching security capabilities of secondary IE in M3
	///   failed. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_SEC_IE_MATCHING = WCL_E_WIFI_RES_BASE + 0x0074;
	/// <summary> Required a pairwise key but access point (AP; configured only
	///   group keys. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_NO_PAIRWISE_KEY = WCL_E_WIFI_RES_BASE + 0x0075;
	/// <summary> Message 1 of group key handshake has no key data. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_G1_MISSING_KEY_DATA = WCL_E_WIFI_RES_BASE + 0x0076;
	/// <summary> Message 1 of group key handshake has no group key. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_G1_MISSING_GRP_KEY = WCL_E_WIFI_RES_BASE + 0x0077;
	/// <summary> AP reset secure bit after connection was secured. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PEER_INDICATED_INSECURE = WCL_E_WIFI_RES_BASE + 0x0078;
	/// <summary> 802.1X indicated that there is no authenticator, but the profile
	///   requires one. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_NO_AUTHENTICATOR = WCL_E_WIFI_RES_BASE + 0x0079;
	/// <summary> Plumbing settings to NIC failed. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_NIC_FAILURE = WCL_E_WIFI_RES_BASE + 0x007A;
	/// <summary> Operation was canceled by a caller. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_CANCELLED = WCL_E_WIFI_RES_BASE + 0x007B;
	/// <summary> Entered key format is not in a valid format. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_KEY_FORMAT = WCL_E_WIFI_RES_BASE + 0x007C;
	/// <summary> A security downgrade was detected. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_DOWNGRADE_DETECTED = WCL_E_WIFI_RES_BASE + 0x007D;
	/// <summary> A PSK mismatch is suspected. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_PSK_MISMATCH_SUSPECTED = WCL_E_WIFI_RES_BASE + 0x007E;
	/// <summary> There was a forced failure because the connection method was not
	///   secure. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_FORCED_FAILURE = WCL_E_WIFI_RES_BASE + 0x007F;
	/// <summary> Message 3 of 4 way handshake contains too many RSN IE
	///   (RSN;. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M3_TOO_MANY_RSNIE = WCL_E_WIFI_RES_BASE + 0x0080;
	/// <summary> Message 2 of 4 way handshake has no key data (RSN
	///   Ad-hoc;. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M2_MISSING_KEY_DATA = WCL_E_WIFI_RES_BASE + 0x0081;
	/// <summary> Message 2 of 4 way handshake has no IE (RSN Ad-hoc;. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M2_MISSING_IE = WCL_E_WIFI_RES_BASE + 0x0082;
	/// <summary> A MSM authentication WCN completed. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_AUTH_WCN_COMPLETED = WCL_E_WIFI_RES_BASE + 0x0083;
	/// <summary> Message 3 of 4 way handshake has no Mgmt Group Key
	///   (RSN;. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_M3_MISSING_MGMT_GRP_KEY = WCL_E_WIFI_RES_BASE + 0x0084;
	/// <summary> Message 1 of group key handshake has no group management
	///   key. </summary>
	const int WCL_E_WIFI_RES_MSMSEC_G1_MISSING_MGMT_GRP_KEY = WCL_E_WIFI_RES_BASE + 0x0085;

	/// <summary> No user is available for 802.1X authentication. This error can
	///   occur when machine authentication is disabled and no user is logged on
	///   to the machine. </summary>
	const int WCL_E_WIFI_RES_ONEX_UNABLE_TO_IDENTIFY_USER = WCL_E_WIFI_RES_BASE + 0x0086;
	/// <summary> The 802.1X identity could not be found. </summary>
	const int WCL_E_WIFI_RES_ONEX_IDENTITY_NOT_FOUND = WCL_E_WIFI_RES_BASE + 0x0087;
	/// <summary> Authentication could only be completed through the user
	///   interface and this interface could not be displayed. </summary>
	const int WCL_E_WIFI_RES_ONEX_UI_DISABLED = WCL_E_WIFI_RES_BASE + 0x0088;
	/// <summary> The EAP authentication failed. </summary>
	const int WCL_E_WIFI_RES_ONEX_EAP_FAILURE_RECEIVED = WCL_E_WIFI_RES_BASE + 0x0089;
	/// <summary> The 802.1X authenticator went away from the network. </summary>
	const int WCL_E_WIFI_RES_ONEX_AUTHENTICATOR_NO_LONGER_PRESENT = WCL_E_WIFI_RES_BASE + 0x008A;
	/// <summary> The version of the OneX profile supplied is not
	///   supported. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_VERSION_NOT_SUPPORTED = WCL_E_WIFI_RES_BASE + 0x008B;
	/// <summary> The OneX profile has an invalid length. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_LENGTH = WCL_E_WIFI_RES_BASE + 0x008C;
	/// <summary> The EAP type specified in the OneX profile(possibly supplied by
	///   the EAPType element; is not allowed. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_DISALLOWED_EAP_TYPE = WCL_E_WIFI_RES_BASE + 0x008D;
	/// <summary> The EAP Type specified in the OneX profile (possibly supplied
	///   by the EAPType element; is invalid, or one of the EAP flags (possibly
	///   supplied in the EAPConfig element; is invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_EAP_TYPE_OR_FLAG = WCL_E_WIFI_RES_BASE + 0x008E;
	/// <summary> The supplicant flags (possibly supplied in the EAPConfig
	///   element; in the OneX profile are invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_ONEX_FLAGS = WCL_E_WIFI_RES_BASE + 0x008F;
	/// <summary> A timer specified in the OneX profile (possibly supplied by the
	///   heldPeriod, authPeriod, or startPeriod element; is invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_TIMER_VALUE = WCL_E_WIFI_RES_BASE + 0x0090;
	/// <summary> The supplicant mode specified in the OneX profile (possibly
	///   supplied by the supplicantMode element; is invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_SUPPLICANT_MODE = WCL_E_WIFI_RES_BASE + 0x0091;
	/// <summary> The authentication mode specified in the OneX profile (possibly
	///   supplied by the authMode element; is invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_AUTH_MODE = WCL_E_WIFI_RES_BASE + 0x0092;
	/// <summary> The connection properties specified in the OneX profile
	///   (possibly supplied by the EAPConfig element; are invalid. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_EAP_CONNECTION_PROPERTIES = WCL_E_WIFI_RES_BASE + 0x0093;
	/// <summary> User input was canceled. This value can be returned if an EAP
	///   method requested user input, but the user hit the Cancel button or
	///   dismissed the user input dialog. </summary>
	const int WCL_E_WIFI_RES_ONEX_UI_CANCELLED = WCL_E_WIFI_RES_BASE + 0x0094;
	/// <summary> The saved user credentials are not valid. This value can be
	///   returned if a profile was saved with bad credentials (an incorrect
	///   password, for example), since the credentials are not tested until the
	///   profile is actually used to establish a connection. </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_INVALID_EXPLICIT_CREDENTIALS = WCL_E_WIFI_RES_BASE + 0x0095;
	/// <summary> The saved user credentials have expired. This value can be
	///   returned if a profile was saved with credentials and the credentials
	///   subsequently expired (password expiration after some period of time,
	///   for example). </summary>
	const int WCL_E_WIFI_RES_ONEX_PROFILE_EXPIRED_EXPLICIT_CREDENTIALS = WCL_E_WIFI_RES_BASE + 0x0096;
	/// <summary> User interface is not permitted. On Windows 7 and on Windows
	///   Server 2008 R2 with the Wireless LAN Service installed, this value can
	///   be returned if an EAP method requested user input and the profile is
	///   configured with user credentials saved by another user and not the
	///   currently logged in user. </summary>
	const int WCL_E_WIFI_RES_ONEX_UI_NOT_PERMITTED = WCL_E_WIFI_RES_BASE + 0x0097;
	/// <summary> The undefined reason code. </summary>
	const int WCL_E_WIFI_RES_UNDEFINED = WCL_E_WIFI_RES_BASE + 0x0098;

	/* 802.1x reason codes. */

	/// <summary> The base code for the 802.1x authentication reasons. </summary>
	const int WCL_E_WIFI_ONEX_RES_BASE = WCL_E_WLAN_BASE + 0x3000;
	/// <summary> The EAPHost component (the peer; requested the 802.1x module
	///   to restart 802.1X authentication. This results from a
	///   EapHostPeerProcessReceivedPacket function call that returns an
	///   EapHostPeerResponseAction enumeration value of
	///   EapHostPeerResponseStartAuthentication in the pEapOutput
	///   parameter. </summary>
	const int WCL_E_WIFI_ONEX_RES_PEER_INITIATED = WCL_E_WIFI_ONEX_RES_BASE + 0x0000;
	/// <summary> The Media Specific Module (MSM; initiated the 802.1X
	///   authentication restart. </summary>
	const int WCL_E_WIFI_ONEX_RES_MSM_INITIATED = WCL_E_WIFI_ONEX_RES_BASE + 0x0001;
	/// <summary> The 802.1X authentication restart was the result of a state
	///   timeout. The timer expiring is the heldWhile timer of the 802.1X
	///   supplicant state machine defined in IEEE 802.1X - 2004 standard for
	///   Port-Based Network Access Control. The heldWhile timer is used by the
	///   supplicant state machine to define periods of time during which
	///   it will not attempt to acquire an authenticator. </summary>
	const int WCL_E_WIFI_ONEX_RES_HELD_STATE_TIMEOUT = WCL_E_WIFI_ONEX_RES_BASE + 0x0002;
	/// <summary> The 802.1X authentication restart was the result of an state
	///   timeout. The timer expiring is the authWhile timer of the 802.1X
	///   supplicant port access entity defined in IEEE 802.1X - 2004 standard
	///   for Port-Based Network Access Control. The authWhile timer is
	///   used by the supplicant port access entity to determine how long to
	///   wait for a request from the authenticator before timing it
	///   out. </summary>
	const int WCL_E_WIFI_ONEX_RES_AUTH_TIMEOUT = WCL_E_WIFI_ONEX_RES_BASE + 0x0003;
	/// <summary> The 802.1X authentication restart was the result of a
	///   configuration change to the current profile. </summary>
	const int WCL_E_WIFI_ONEX_RES_CONFIGURATION_CHANGED = WCL_E_WIFI_ONEX_RES_BASE + 0x0004;
	/// <summary> The 802.1X authentication restart was the result of a change
	///   of user. This could occur if the current user logs off and new user
	///   logs on to the local computer. </summary>
	const int WCL_E_WIFI_ONEX_RES_USER_CHANGED = WCL_E_WIFI_ONEX_RES_BASE + 0x0005;
	/// <summary> The 802.1X authentication restart was the result of receiving
	///   a notification from the EAP quarantine enforcement client (QEC; due
	///   to a network health change. If an EAPHost supplicant is participating
	///   in network access protection (NAP;, the supplicant will respond to
	///   changes in the state of its network health. If that state changes,
	///   the supplicant must then initiate a re-authentication
	///   session. </summary>
	const int WCL_E_WIFI_ONEX_RES_QUARANTINE_STATE_CHANGED = WCL_E_WIFI_ONEX_RES_BASE + 0x0006;
	/// <summary> The 802.1X authentication restart was caused by a new
	///   authentication attempt with alternate user credentials. EAP methods
	///   like MSCHAPv2 prefer to use logged-on user credentials for 802.1X
	///   authentication. If these user credentials do not work, then a dialog
	///   will be displayed to the user that asks permission to use alternate
	///   credentials for 802.1X authentication. </summary>
	const int WCL_E_WIFI_ONEX_RES_ALT_CREDS_TRIAL = WCL_E_WIFI_ONEX_RES_BASE + 0x0007;
	/// <summary> Unknown reason. </summary>
	const int WCL_E_WIFI_ONEX_RES_INVALID = WCL_E_WIFI_ONEX_RES_BASE + 0x0008;

	/* Hosted Network error codes. */

	/// <summary> The base code for the hosted network reasons. </summary>
	const int WCL_E_WIFI_HN_RES_BASE = WCL_E_WLAN_BASE + 0x4000;
	/// <summary> Unknown error. </summary>
	const int WCL_E_WIFI_HN_RES_UNSPECIFIED = WCL_E_WIFI_HN_RES_BASE + 0x0000;
	/// <summary> Bad parameters. </summary>
	const int WCL_E_WIFI_HN_RES_BAD_PARAMETER = WCL_E_WIFI_HN_RES_BASE + 0x0001;
	/// <summary> Service is shutting down. </summary>
	const int WCL_E_WIFI_HN_RES_SERVICE_SHUTTING_DOWN = WCL_E_WIFI_HN_RES_BASE + 0x0002;
	/// <summary> Service is out of resources. </summary>
	const int WCL_E_WIFI_HN_RES_INSUFFICIENT_RESOURCES = WCL_E_WIFI_HN_RES_BASE + 0x0003;
	/// <summary> This operation requires elevation. </summary>
	const int WCL_E_WIFI_HN_RES_ELEVATION_REQUIRED = WCL_E_WIFI_HN_RES_BASE + 0x0004;
	/// <summary> An attempt was made to write read-only data. </summary>
	const int WCL_E_WIFI_HN_RES_READ_ONLY = WCL_E_WIFI_HN_RES_BASE + 0x0005;
	/// <summary> Data persistence failed. </summary>
	const int WCL_E_WIFI_HN_RES_PERSISTENCE_FAILED = WCL_E_WIFI_HN_RES_BASE + 0x0006;
	/// <summary> A cryptographic error occurred. </summary>
	const int WCL_E_WIFI_HN_RES_CRYPT_ERROR = WCL_E_WIFI_HN_RES_BASE + 0x0007;
	/// <summary> User impersonation failed. </summary>
	const int WCL_E_WIFI_HN_RES_IMPERSONATION = WCL_E_WIFI_HN_RES_BASE + 0x0008;
	/// <summary> An incorrect function call sequence was made. </summary>
	const int WCL_E_WIFI_HN_RES_STOP_BEFORE_START = WCL_E_WIFI_HN_RES_BASE + 0x0009;
	/// <summary> A wireless interface has become available. </summary>
	const int WCL_E_WIFI_HN_RES_INTERFACE_AVAILABLE = WCL_E_WIFI_HN_RES_BASE + 0x000A;
	/// <summary> <para> A wireless interface has become unavailable. </para>
	///   <para> This reason code is returned by the wireless Hosted Network
	///   functions any time the network state of the wireless Hosted Network is
	///   <c>hnUnavailable</c>. For example if the wireless Hosted Network is
	///   disabled by group policy on a domain, then the network state of the
	///   wireless Hosted Network is <c>hnUnavailable</c>. </para> </summary>
	const int WCL_E_WIFI_HN_RES_INTERFACE_UNAVAILABLE = WCL_E_WIFI_HN_RES_BASE + 0x000B;
	/// <summary> The wireless mini-port driver stopped the Hosted
	///   Network. </summary>
	const int WCL_E_WIFI_HN_RES_MINIPORT_STOPPED = WCL_E_WIFI_HN_RES_BASE + 0x000C;
	/// <summary> The wireless mini-port driver status changed. </summary>
	const int WCL_E_WIFI_HN_RES_MINIPORT_STARTED = WCL_E_WIFI_HN_RES_BASE + 0x000D;
	/// <summary> <para> An incompatible connection started. </para>
	///   <para> An incompatible connection refers to one of the following
	///   cases: </para>
	///   <list type="bullet">
	///     <item> An ad hoc wireless connection is started on the primary station
	///            adapter. </item>
	///     <item> Network monitoring is started on the primary station adapter by
	///            an application (Network Monitor, for example;. </item>
	///     <item> A wireless connection is started in FIPS safe mode on the
	///            primary station adapter. FIPS safe mode is specified in the
	///            profile of the wireless connection. </item>
	///   </list>
	///   <para> Windows will stop the wireless Hosted Network on the
	///   software-based wireless access point (AP; adapter when an incompatible
	///   connection starts on the primary station adapter. The network state of
	///   the wireless Hosted Network state would become
	///   <c>hnUnavailable</c>. </para> </summary>
	const int WCL_E_WIFI_HN_RES_INCOMPATIBLE_CONNECTION_STARTED = WCL_E_WIFI_HN_RES_BASE + 0x000E;
	/// <summary> <para> An incompatible connection stopped. </para>
	///   <para> An incompatible connection previously started on the primary
	///   station adapter
	///   (<see cref="wclWiFi::WCL_E_WIFI_HN_RES_INCOMPATIBLE_CONNECTION_STARTED" />;,
	///   but the incompatible connection has stopped. If the wireless Hosted
	///   Network was previously stopped as a result of an incompatible connection
	///   being started, Windows will not automatically restart the wireless
	///   Hosted Network. </para> </summary>
	const int WCL_E_WIFI_HN_RES_INCOMPATIBLE_CONNECTION_STOPPED = WCL_E_WIFI_HN_RES_BASE + 0x000F;
	/// <summary> A state change occurred that was caused by explicit user
	///   action. </summary>
	const int WCL_E_WIFI_HN_RES_USER_ACTION = WCL_E_WIFI_HN_RES_BASE + 0x0010;
	/// <summary> A state change occurred that was caused by client
	///   abort. </summary>
	const int WCL_E_WIFI_HN_RES_CLIENT_ABORT = WCL_E_WIFI_HN_RES_BASE + 0x0011;
	/// <summary> The driver for the wireless Hosted Network failed to
	///   start. </summary>
	const int WCL_E_WIFI_HN_RES_AP_START_FAILED = WCL_E_WIFI_HN_RES_BASE + 0x0012;
	/// <summary> A peer connected to the wireless Hosted Network. </summary>
	const int WCL_E_WIFI_HN_RES_PEER_ARRIVED = WCL_E_WIFI_HN_RES_BASE + 0x0013;
	/// <summary> A peer disconnected from the wireless Hosted Network. </summary>
	const int WCL_E_WIFI_HN_RES_PEER_DEPARTED = WCL_E_WIFI_HN_RES_BASE + 0x0014;
	/// <summary> A peer timed out. </summary>
	const int WCL_E_WIFI_HN_RES_PEER_TIMEOUT = WCL_E_WIFI_HN_RES_BASE + 0x0015;
	/// <summary> The operation was denied by group policy. </summary>
	const int WCL_E_WIFI_HN_RES_GP_DENIED = WCL_E_WIFI_HN_RES_BASE + 0x0016;
	/// <summary> The Wireless LAN service is not running. </summary>
	const int WCL_E_WIFI_HN_RES_SERVICE_UNAVAILABLE = WCL_E_WIFI_HN_RES_BASE + 0x0017;
	/// <summary> The wireless adapter used by the wireless Hosted Network
	///   changed. </summary>
	const int WCL_E_WIFI_HN_RES_DEVICE_CHANGE = WCL_E_WIFI_HN_RES_BASE + 0x0018;
	/// <summary> The properties of the wireless Hosted Network
	///   changed. </summary>
	const int WCL_E_WIFI_HN_RES_PROPERTIES_CHANGE = WCL_E_WIFI_HN_RES_BASE + 0x0019;
	/// <summary> A virtual station is active and blocking operation. </summary>
	const int WCL_E_WIFI_HN_RES_VIRTUAL_STATION_BLOCKING_USE = WCL_E_WIFI_HN_RES_BASE + 0x001A;
	/// <summary> An identical service is available on a virtual
	///   station. </summary>
	const int WCL_E_WIFI_HN_RES_SERVICE_AVAILABLE_ON_VIRTUAL_STATION = WCL_E_WIFI_HN_RES_BASE + 0x001B;

	/* Common Hosted Network error codes. */

	/// <summary> The base error code for common Hosted Network errors. </summary>
	const int WCL_E_WIFI_HN_BASE = WCL_E_WIFI_HN_RES_BASE + 0x0100;
	/// <summary> Unable to access the IP settings of a Hosted Network. </summary>
	const int WCL_E_WIFI_HN_OPEN_IP_SETTINGS_FAILED = WCL_E_WIFI_HN_BASE + 0x0000;
	/// <summary> Unable to read TCP/IP settings of a Hosted Network. </summary>
	const int WCL_E_WIFI_HN_READ_IP_FAILED = WCL_E_WIFI_HN_BASE + 0x0001;
	/// <summary> The requested feature is not supported on current platform. </summary>
	const int WCL_E_WIFI_HN_FEATURE_NOT_SUPPORTED = WCL_E_WIFI_HN_BASE + 0x0002;
	/// <summary> Get IP table failed. </summary>
	const int WCL_E_WIFI_HN_GET_IP_TABLE_FAILED = WCL_E_WIFI_HN_BASE + 0x0003;
	/// <summary> The peer with specified MAC was not found. </summary>
	const int WCL_E_WIFI_HN_PEER_NOT_FOUND = WCL_E_WIFI_HN_BASE + 0x0004;
	/// <summary> The Hosted Network has already been started. </summary>
	const int WCL_E_WIFI_HN_STARTED = WCL_E_WIFI_HN_BASE + 0x0005;
	/// <summary> The Hosted Network does not support PSD IE on this
	///   platform. </summary>
	const int WCL_E_WIFI_HN_PSD_IE_NOT_SUPPORTED = WCL_E_WIFI_HN_BASE + 0x0006;
	/// <summary> The error indicates that the WiFi access disabled in the system
	///   settings. </summary>
	const int WCL_E_WIFI_HN_ACCESS_DENIED_BY_SYSTEM = WCL_E_WIFI_HN_BASE + 0x0007;
	/// <summary> The error indicates that the WiFi access disabled for the classic
	///   applications in system settings and used did not grant access during
	///   access request. </summary>
	const int WCL_E_WIFI_HN_ACCESS_DENIED_BY_USER = WCL_E_WIFI_HN_BASE + 0x0008;

	/* Network List Manager error codes. */

	/// <summary> The base Network List Manager error code. </summary>
	const int WCL_E_NLM_BASE = WCL_E_WLAN_BASE + 0x5000;
	/// <summary> The Network List Manager is closed. </summary>
	const int WCL_E_NLM_CLOSED = WCL_E_NLM_BASE + 0x0000;
	/// <summary> The Network List Manager is opened. </summary>
	const int WCL_E_NLM_OPENED = WCL_E_NLM_BASE + 0x0001;
	/// <summary> Unable to initialize COM subsystem. </summary>
	const int WCL_E_NLM_COINITIALIZE_FAILED = WCL_E_NLM_BASE + 0x0002;
	/// <summary> The Network List Manager is not supported on this
	///   platform. </summary>
	const int WCL_E_NLM_UNSUPPORTED = WCL_E_NLM_BASE + 0x0003;
	/// <summary> The Network List Manager events handler is already
	///   set. </summary>
	const int WCL_E_NLM_EVENTS_HANDLER_SET = WCL_E_NLM_BASE + 0x0004;
	/// <summary> The Network List Manager events handler was not set. </summary>
	const int WCL_E_NLM_EVENTS_HANDLER_NOT_SET = WCL_E_NLM_BASE + 0x0005;
	/// <summary> Unable to find the Network List Manager events handler
	///   connection points container. </summary>
	const int WCL_E_NLM_UNABLE_FIND_CONNECTION_POINTS_CONTAINER = WCL_E_NLM_BASE + 0x0006;
	/// <summary> Unable to find the Network List Manager events handler
	///   connection point. </summary>
	const int WCL_E_NLM_UNABLE_FIND_CONNECTION_POINT = WCL_E_NLM_BASE + 0x0007;
	/// <summary> Unable to find the Network events handler connection points
	///   container. </summary>
	const int WCL_E_NLM_NE_UNABLE_FIND_CONNECTION_POINTS_CONTAINER = WCL_E_NLM_BASE + 0x0008;
	/// <summary> Unable to find the Network events handler connection
	///   point. </summary>
	const int WCL_E_NLM_NE_UNABLE_FIND_CONNECTION_POINT = WCL_E_NLM_BASE + 0x0009;
	/// <summary> The network with given ID was not found. </summary>
	const int WCL_E_NLM_NETWORK_NOT_FOUND = WCL_E_NLM_BASE + 0x000A;
	/// <summary> Unable to get a network's or machine's connectivity. </summary>
	const int WCL_E_NLM_UNABLE_GET_CONNECTIVITY = WCL_E_NLM_BASE + 0x000B;
	/// <summary> Unable to read <c>Connected</c> property of the Network List
	///   Manager or Network. </summary>
	const int WCL_E_NLM_UNABLE_GET_CONNECTED_PROPERTY = WCL_E_NLM_BASE + 0x000C;
	/// <summary> Unable to get a network's domain type. </summary>
	const int WCL_E_NLM_UNABLE_GET_DOMAIN_TYPE = WCL_E_NLM_BASE + 0x000D;
	/// <summary> Unable to get a network's category. </summary>
	const int WCL_E_NLM_UNABLE_GET_NETWORK_CATEGORY = WCL_E_NLM_BASE + 0x000E;
	/// <summary> Unable to get a network's description. </summary>
	const int WCL_E_NLM_UNABLE_GET_NETWORK_DESCRIPTION = WCL_E_NLM_BASE + 0x000F;
	/// <summary> Unable to get a network's name. </summary>
	const int WCL_E_NLM_UNABLE_GET_NETWORK_NAME = WCL_E_NLM_BASE + 0x0010;
	/// <summary> Unable to get a network's ID. </summary>
	const int WCL_E_NLM_UNABLE_GET_NETWORK_ID = WCL_E_NLM_BASE + 0x0011;
	/// <summary> Unable to get a network's creation and connection date and
	///   time. </summary>
	const int WCL_E_NLM_UNABLE_GET_NETWORK_CREATED_AND_CONNECTED_DATE_TIME = WCL_E_NLM_BASE + 0x0012;
	/// <summary> Unable to get a connection's adapter ID. </summary>
	const int WCL_E_NLM_UNABLE_GET_CONNECTION_ADAPTER_ID = WCL_E_NLM_BASE + 0x0013;
	/// <summary> Unable to read a connection's ID. </summary>
	const int WCL_E_NLM_UNABLE_GET_CONNECTION_ID = WCL_E_NLM_BASE + 0x0014;
	/// <summary> Unable to set a network's category. </summary>
	const int WCL_E_NLM_UNABLE_SET_NETWORK_CATEGORY = WCL_E_NLM_BASE + 0x0015;
	/// <summary> Unable to set a network's description. </summary>
	const int WCL_E_NLM_UNABLE_SET_NETWORK_DESCRIPTION = WCL_E_NLM_BASE + 0x0016;
	/// <summary> Unable to set a network's name. </summary>
	const int WCL_E_NLM_UNABLE_SET_NETWORK_NAME = WCL_E_NLM_BASE + 0x0017;
	/// <summary> Unable to enumerate available networks. </summary>
	const int WCL_E_NLM_UNABLE_ENUMERATE_NETWORKS = WCL_E_NLM_BASE + 0x0018;
	/// <summary> Networks with required type were not found. </summary>
	const int WCL_E_NLM_NETWORKS_NOT_FOUND = WCL_E_NLM_BASE + 0x0019;
	/// <summary> Connections were not found. </summary>
	const int WCL_E_NLM_CONNECTIONS_NOT_FOUND = WCL_E_NLM_BASE + 0x001A;
	/// <summary> Unable to enumerate connections. </summary>
	const int WCL_E_NLM_UNABLE_ENUMERATE_CONNECTIONS = WCL_E_NLM_BASE + 0x001B;
	/// <summary> Network profiles list was not found. </summary>
	const int WCL_E_NLM_NETWORK_PROFILES_NOT_FOUND = WCL_E_NLM_BASE + 0x001C;
	/// <summary> Administrative rights required for this operation. </summary>
	const int WCL_E_NLM_ACCESS_DENIED = WCL_E_NLM_BASE + 0x001D;
	/// <summary> Unexpected or unknown error. </summary>
	const int WCL_E_NLM_UNEXPECTED = WCL_E_NLM_BASE + 0x001E;

	/* WiFi sniffer error codes. */

	/// <summary> The base error code for the WiFi Sniffer. </summary>
	const int WCL_E_WIFI_SNIFF_BASE = WCL_E_WLAN_BASE + 0x6000;
	/// <summary> Unable to create API synchronization mutex. </summary>
	const int WCL_E_WIFI_SNIFF_UNABLE_CREATE_MUTEX = WCL_E_WIFI_SNIFF_BASE + 0x0000;
	/// <summary> Unable to load NetMon API DLL. </summary>
	const int WCL_E_WIFI_SNIFF_UNABLE_LOAD_DLL = WCL_E_WIFI_SNIFF_BASE + 0x0001;
	/// <summary> The API references counter is in wrong state. </summary>
	const int WCL_E_WIFI_SNIFF_WRONG_REF_COUNTER = WCL_E_WIFI_SNIFF_BASE + 0x0002;
	/// <summary> The WiFi Sniffer has already been opened. </summary>
	const int WCL_E_WIFI_SNIFF_OPENED = WCL_E_WIFI_SNIFF_BASE + 0x0003;
	/// <summary> The WiFi Sniffer is closed. </summary>
	const int WCL_E_WIFI_SNIFF_CLOSED = WCL_E_WIFI_SNIFF_BASE + 0x0004;
	/// <summary> Unable to create interface protection mutex. </summary>
	const int WCL_E_WIFI_SNIFF_UNABLE_CREATE_IFACE_MUTEX = WCL_E_WIFI_SNIFF_BASE + 0x0005;
	/// <summary> The other instance of the WiFi Sniffer is already using the same
	///   interface for capturing. </summary>
	const int WCL_E_WIFI_SNIFF_IFACE_IN_USE = WCL_E_WIFI_SNIFF_BASE + 0x0006;
	/// <summary> Indicates an issue between the Network Monitor API and the
	///   ndisnapp object. See Working with Multi-Threaded Code. </summary>
	const int WCL_E_WIFI_SNIFF_NOINTERFACE = WCL_E_WIFI_SNIFF_BASE + 0x0007;
	/// <summary> The object that you are trying to create already exists. </summary>
	const int WCL_E_WIFI_SNIFF_ALREADY_EXIST = WCL_E_WIFI_SNIFF_BASE + 0x0008;
	/// <summary> Frame comment information was not found. </summary>
	const int WCL_E_WIFI_SNIFF_EMPTY = WCL_E_WIFI_SNIFF_BASE + 0x0009;
	/// <summary> The specified file was not found. </summary>
	const int WCL_E_WIFI_SNIFF_FILE_NOT_FOUND = WCL_E_WIFI_SNIFF_BASE + 0x000A;
	/// <summary> The API or driver is in the wrong state for the requested operation. </summary>
	const int WCL_E_WIFI_SNIFF_INVALID_STATE = WCL_E_WIFI_SNIFF_BASE + 0x000B;
	/// <summary> Reference to a file, file path, handle, or data field is incorrect. </summary>
	const int WCL_E_WIFI_SNIFF_NOT_FOUND = WCL_E_WIFI_SNIFF_BASE + 0x000C;
	/// <summary> This function is not currently supported. </summary>
	const int WCL_E_WIFI_SNIFF_NOT_SUPPORTED = WCL_E_WIFI_SNIFF_BASE + 0x000D;
	/// <summary> The upper limit of a resource has been reached. This may
	///   indicate that a handle limit has been reached. Sometimes this is an
	///   indication that handles are being leaked. These resources can be read
	///   with the NmGetApiConfiguration function and set with the NmApiInitialize
	///   function. </summary>
	const int WCL_E_WIFI_SNIFF_PARAMETER_QUOTA_EXCEEDED = WCL_E_WIFI_SNIFF_BASE + 0x000E;
	/// <summary> The field is a container, so the content is not available. </summary>
	const int WCL_E_WIFI_SNIFF_RESOURCE_NOT_AVAILABLE = WCL_E_WIFI_SNIFF_BASE + 0x000F;
	/// <summary> The version of the DLL does not match the version with which
	///   this executable was compiled. </summary>
	const int WCL_E_WIFI_SNIFF_API_VERSION_MISMATCHED = WCL_E_WIFI_SNIFF_BASE + 0x0010;
	/// <summary> The file size of the capture specified by the capture function
	///   exceeds the current limit, 500 MB. </summary>
	const int WCL_E_WIFI_SNIFF_FILE_TOO_LARGE = WCL_E_WIFI_SNIFF_BASE + 0x0011;
	/// <summary> The file size of the capture specified by the capture function
	///   is too small to contain any useful frame information. </summary>
	const int WCL_E_WIFI_SNIFF_FILE_TOO_SMALL = WCL_E_WIFI_SNIFF_BASE + 0x0012;
	/// <summary> The frame size overlaps with the next frame. </summary>
	const int WCL_E_WIFI_SNIFF_FRAME_CONTINUES_INTO_NEXT_FRAME = WCL_E_WIFI_SNIFF_BASE + 0x0013;
	/// <summary> The offset in the frame table points past the bounds of the file. </summary>
	const int WCL_E_WIFI_SNIFF_FRAME_RANGE_OUT_OF_BOUNDS = WCL_E_WIFI_SNIFF_BASE + 0x0014;
	/// <summary> The file that you are saving to does not have enough space to
	///   hold the frame. This can occur when there is not enough disk space or
	///   if the file is over the 500 MB size limit. </summary>
	const int WCL_E_WIFI_SNIFF_FRAME_TOO_BIG_FOR_FILE = WCL_E_WIFI_SNIFF_BASE + 0x0015;
	/// <summary> The file type is not a valid Network Monitor 3 capture file. </summary>
	const int WCL_E_WIFI_SNIFF_INVALID_NETMON_CAP_FILE = WCL_E_WIFI_SNIFF_BASE + 0x0016;
	/// <summary> The file type is not supported. </summary>
	const int WCL_E_WIFI_SNIFF_UNSUPPORTED_FILE_TYPE = WCL_E_WIFI_SNIFF_BASE + 0x0017;
	/// <summary> The PCAP data link type is not supported. </summary>
	const int WCL_E_WIFI_SNIFF_UNSUPPORTED_PCAP_DLT = WCL_E_WIFI_SNIFF_BASE + 0x0018;
	/// <summary> The data is big-endian, but only little-endian data is supported. </summary>
	const int WCL_E_WIFI_SNIFF_WRONG_ENDIAN = WCL_E_WIFI_SNIFF_BASE + 0x0019;
	/// <summary> The file is not a supported PCAP version. </summary>
	const int WCL_E_WIFI_SNIFF_WRONG_PCAP_VERSION = WCL_E_WIFI_SNIFF_BASE + 0x001A;
	/// <summary> Indicates an issue between the application and the API. </summary>
	const int WCL_E_WIFI_SNIFF_CHANGED_MODE = WCL_E_WIFI_SNIFF_BASE + 0x001B;
	/// <summary> Unexpected WiFI Sniffer error. </summary>
	const int WCL_E_WIFI_SNIFF_UNEXPECTED = WCL_E_WIFI_SNIFF_BASE + 0x001C;
	/// <summary> No one supported adapter was found. </summary>
	const int WCL_E_WIFI_SNIFF_ADAPTER_NOT_FOUND = WCL_E_WIFI_SNIFF_BASE + 0x001D;

	/* Base WiFi direct error codes. */

	/// <summary> The base WiFi Direct error code. </summary>
	const int WCL_E_WIFI_DIRECT_BASE = WCL_E_WLAN_BASE + 0x7000;
	/// <summary> The WiFi Direct radio was not available. This error occurs when
	///   the WiFi Direct radio has been turned off. </summary>
	const int WCL_E_WIFI_DIRECT_RADIO_NOT_AVAILABLE = WCL_E_WIFI_DIRECT_BASE + 0x0000;
	/// <summary> The operation cannot be serviced because the necessary resources
	///   are currently in use. </summary>
	const int WCL_E_WIFI_DIRECT_RESOURCE_IN_USE = WCL_E_WIFI_DIRECT_BASE + 0x0001;
	/// <summary> Unknown or unexpected WiFi Direct error. </summary>
	const int WCL_E_WIFI_DIRECT_UNKNOWN = WCL_E_WIFI_DIRECT_BASE + 0x0002;
	/// <summary> WiFi Direct features are not supported. For WiFi Direct features
	///   Windows 10 is required. </summary>
	const int WCL_E_WIFI_DIRECT_NOT_SUPPORTED = WCL_E_WIFI_DIRECT_BASE + 0x0003;

	/* WiFi direct pairing error codes. */

	/// <summary> The base error code for all WiFi Direct pairing errors. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_BASE = WCL_E_WLAN_BASE + 0x8000;
	/// <summary> The device is not in a state where it can be paired. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_NOT_READY = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0000;
	/// <summary> The device is not currently paired. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_NOT_PAIRED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0001;
	/// <summary> The device has already been paired. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_ALREADY_PAIRED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0002;
	/// <summary> The device rejected the connection. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_REJECTED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0003;
	/// <summary> The device indicated it cannot accept any more incoming connections. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_TOO_MANY_CONNECTTIONS = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0004;
	/// <summary> The device indicated there was a hardware failure. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_HARDWARE_FAILURE = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0005;
	/// <summary> The authentication process timed out before it could complete. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_TIMEOUT = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0006;
	/// <summary> The authentication protocol is not supported, so the device is not paired. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_NOT_ALLOWED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0007;
	/// <summary> Authentication failed, so the device is not paired. Either the
	///   device or the application rejected the authentication. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_AUTHENTICATION_FAILURE = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0008;
	/// <summary> There are no network profiles for this device to use. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_NO_PROFILES = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0009;
	/// <summary> The minimum level of protection is not supported by the device
	///   or the application. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_PROTECTION_LEVEL = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000A;
	/// <summary> Your application does not have the appropriate permissions level
	///   to pair the device. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_ACCESS_DENIED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000B;
	/// <summary> The ceremony data was incorrect. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_INVALID_CEREMONY = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000C;
	/// <summary> The pairing action was canceled before completion. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_CANCELLED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000D;
	/// <summary> The device is already attempting to pair or unpair. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_IN_PROGRESS = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000E;
	/// <summary> Either the event handler wasn't registered or a required
	///   <c>wclWiFiDirectPairingKinds</c> was not supported. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_HANDLER_NOT_REGISTERED = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x000F;
	/// <summary> The application handler rejected the pairing. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_REJECTED_BY_HANDLER = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0010;
	/// <summary> The remove device already has an association. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_HAS_ASSOCCIATION = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0011;
	/// <summary> An unexpected failure occurred. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_UNKNOWN = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0012;
	/// <summary> An unknown failure occurred. </summary>
	const int WCL_E_WIFI_DIRECT_PAIR_FAILURE = WCL_E_WIFI_DIRECT_PAIR_BASE + 0x0013;

	/* WiFi direct device error codes. */

	/// <summary> The base error code for WiFi Direct device errors. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_BASE = WCL_E_WLAN_BASE + 0x9000;
	/// <summary> The WiFi Direct device is connected or connecting. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CONNECTED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0000;
	/// <summary> The WiFi Direct device is disconnected or
	///   disconnecting. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_DISCONNECTED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0001;
	/// <summary> Unable to create WiFi Direct device's thread termination event. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_TERMINATION_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0002;
	/// <summary> Unable to start WiFi Direct device connection thread. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_START_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0003;
	/// <summary> Unable to create device information object. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_INFORMATION_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0004;
	/// <summary> IAsyncInfor interface not supported. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_QUERY_ASYNC_INFO_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0005;
	/// <summary> Unable to get device information object. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_INFORMATION_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0006;
	/// <summary> Extended device information not supported. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_EXTENDED_INFO_NOT_SUPPORTED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0007;
	/// <summary> WiFi Direct device does not support pairing. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_PAIRING_NOT_SUPPORTED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0008;
	/// <summary> WiFi Direct device does not support custom pairing. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CUSTOM_PAIRING_NOT_SUPPORTED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0009;
	/// <summary> Unable to create WiFi Direct device pairing notification
	///   synchronization event. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_PAIRING_SYNC_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000A;
	/// <summary> Connection has been terminated by user. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CONNECTION_TERMINATED_BT_USER = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000B;
	/// <summary> Wait for notification message processing failed. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WAIT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000C;
	/// <summary> Unable to create pairing synchronization mutex. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_PAIRING_MUTEX_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000D;
	/// <summary> Unable to set Group Owner Intent. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_SET_GO_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000E;
	/// <summary> Unable to get connection parameters. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_CONNECTION_PARAMETERS_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x000F;
	/// <summary> Unable to set preferred pairing procedure. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_SET_PAIRING_PROCEDURE_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0010;
	/// <summary> Unable to get custom pairing interface. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_CUSTOM_PAIRING_FILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0011;
	/// <summary> Unable to set pairing event handler. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_SET_PAIRING_EVENT_HANDLER_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0012;
	/// <summary> Unable to get pairing settings. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_PAIRING_SETTINGS_FILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0013;
	/// <summary> Unable to start pairing with remote WiFi Direct device. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_START_PAIRING_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0014;
	/// <summary> Unable to get pairing result. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_PAIRING_RESULT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0015;
	/// <summary> Unable to pair with remote device. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_PAIRING_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0016;
	/// <summary> Unable to create WiFi Direct device object. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0017;
	/// <summary> Unable to get WiFi Direct device creation operation result. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_GET_RESULT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0018;
	/// <summary> WiFi Direct device object was not created. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_OBJECT_NOT_CREATED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0019;
	/// <summary> Unable to set disconnection event handler. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_SET_DISCONNECT_EVENT_HANDLER_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001A;
	/// <summary> Unable to get WiFi Direct device's pairing status. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_PAIRED_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001B;
	/// <summary> Unable to start unpairing operation. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_START_UNPAIR_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001C;
	/// <summary> Timeout during creating WiFi Direct device object. Usually it
	///   appears when device has wrong DHCP configuration or uses static IP. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_CREATE_TIMEOUT = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001D;
	/// <summary> Unable to start WiFi Direct device object creating procedure. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_START_CREATE_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001E;
	/// <summary> Unable to get device ID. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_GET_ID_FAILED = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x001F;
	/// <summary> The WiFi Direct device or driver is busy. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_BUSY = WCL_E_WIFI_DIRECT_DEVICE_BASE + 0x0020;

	/* WiFi direct advertiser error codes. */

	/// <summary> The base error code for WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_BASE = WCL_E_WLAN_BASE + 0xA000;
	/// <summary> The publisher is aborted due to error. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_START_ABORTED = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0000;
	/// <summary> Unable to get the WiFi Direct Advertisement object. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_GET_ADVERTISEMENT = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0001;
	/// <summary> Unable to set an Autonomous  Group Owner state. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_GO = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0002;
	/// <summary> Unable to set Listen State Discoverability. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_SET_DISCOVERABILITY_FAILED = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0003;
	/// <summary> Unable to access the WiFi Direct Advertiser Legacy mode settings. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_GET_LEGACY_SETTINGS = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0004;
	/// <summary> Unable to change the Legacy mode setting of the WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_CHANGE_LEGACY_MODE = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0005;
	/// <summary> Unable to set SSID for the WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_SSID = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0006;
	/// <summary> Unable to access Legacy mode security settings of the WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_GET_CREDENTIAL = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0007;
	/// <summary> Unable to set the WiFi Direct Advertiser's Legacy mode pass phrase. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_PASSPHRASE = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0008;
	/// <summary> Unable to create start synchronization event for the WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_CREATE_ASYNC_EVENT = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0009;
	/// <summary> Unable to set event handler for WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_PUBLISHER_EVENT = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000A;
	/// <summary> Filed to start WiFi Direct Advertiser. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_START_PUBLISHER = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000B;
	/// <summary> Unable to set event handler for WiFi Direct Advertiser connection listening. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_LISTENER_HANDLER = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000C;
	/// <summary> A WiFi Direct Advertiser is already running. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_ACTIVE = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000D;
	/// <summary> Unable to create WiFi Direct Advertiser working thread initialization event. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_CREATE_THREAD_EVENT = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000E;
	/// <summary> Unable to start WiFi Direct Advertiser working thread. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_CREATE_WORKING_THREAD = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x000F;
	/// <summary> WiFi Direct Advertiser is not running. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_NOT_ACTIVE = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0010;
	/// <summary> Unable to create legacy Soft AP with Open Authentication (Open Network). </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_UNABLE_SET_OPEN_AUTH_MODE = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0011;
	/// <summary> WiFi Direct Advertiser is already running by other WiFi Framework based application. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_ALREADY_RUNNING = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0012;
	/// <summary> Unable to create global mutex object. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_CREATE_MUTEX_FAILED = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0013;
	/// <summary> Mobile HotSpot is already running on PC. </summary>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_HOTSPOT_RUNNING = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0014;
	/// <summary> This error returned when your run x32 application on x64
	///   platform and Autonomous Group Owner enabled in WiFiDirectAdvertiser and
	///   the Advertiser runs not in Legacy mode. </summary>
	/// <remarks> Windows API has some bug when pairing always failed if you
	///   run WiFi Direct Advertiser in Autonomous Group Owner mode in x32
	///   application on x64 platform. </remarks>
	const int WCL_E_WIFI_DIRECT_ADVERTISER_INVALID_OS_BITS = WCL_E_WIFI_DIRECT_ADVERTISER_BASE + 0x0015;

	/* WiFi direct device watcher error codes. */

	/// <summary> The base error code for WiFi Direct Device Watcher. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE = WCL_E_WLAN_BASE + 0xB000;
	/// <summary> The WiFi Direct Device Watcher is already running. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_ACTIVE = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0000;
	/// <summary> Unable to create WiFi Direct Device Watcher thread
	///   synchronization event. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0001;
	/// <summary> Unable to start WiFi Direct Device Watcher worker thread. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0002;
	/// <summary> The WiFi Direct Device Watcher is not running. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_NOT_ACTIVE = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0003;
	/// <summary> Unable to create WiFi Direct Device activation factory. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_DEVICE_STATICS_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0004;
	/// <summary> IWiFiDirectDeviceStatics2 interface is not supported. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_DEVICE_STATICS2_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0005;
	/// <summary> Unable to get Device Selector. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_GET_DEVICE_SELECTOR_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0006;
	/// <summary> Unable to create Device Information Activation Factory. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_DEVICE_INFORMATION_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0007;
	/// <summary> Unable to create Device Watcher object. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0008;
	/// <summary> Unable to set device added event handler. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_SET_ADDED_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0009;
	/// <summary> Unable to set discovering completed event handler. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_SET_COMPLETED_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000A;
	/// <summary> Unable to start WiFi Direct Device Watcher. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_START_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000B;
	/// <summary> Unable to create discovering completed notification event. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_NOTIFICATION_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000C;
	/// <summary> Discovering terminated by user. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_DISCOVERING_TERMINATED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000D;
	/// <summary> Unexpected or unknown error. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_UNEXPECTED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000E;
	/// <summary> Unable to create WiFi Direct Device Watcher thread initialization event. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_CREATE_INIT_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x000F;
	/// <summary> Unable to set device watcher stopped event handler. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_SET_STOPPED_EVENT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0010;
	/// <summary> Unable to start working thread to read remote WiFi Direct device's paired status. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_START_GET_PAIRED_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0011;
	/// <summary> Unable to start WiFi Direct device unpairing thread. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_START_UNPAIR_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0012;
	/// <summary> Unable to start WiFi Direct device name resolving thread. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_START_NAME_RESOLVING_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0013;
	/// <summary> Unable to start paired WiFi Direct devices enumeration thread. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_START_ENUM_PAIRED_DEVICES_THREAD_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0014;
	/// <summary> Unable to enumerate available devices. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_ENUMERATE_DEVICES_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0015;
	/// <summary> IAsyncInfor interface not supported. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_QUERY_ASYNC_INFO_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0016;
	/// <summary> Get devices enumeration result failed. </summary>
	const int WCL_E_WIFI_DIRECT_DEVICE_WATCHER_GET_ENUM_RESULT_FAILED = WCL_E_WIFI_DIRECT_DEVICE_WATCHER_BASE + 0x0017;

	/* WiFi interface error codes. */

	/// <summary> The base error code for WiFi interface operations. </summary>
	const int WCL_E_WIFI_INTERFACE_BASE = WCL_E_WLAN_BASE + 0xC000;
	/// <summary> A WiFi interface is not connected. </summary>
	const int WCL_E_WIFI_INTERFACE_NOT_CONNECTED = WCL_E_WIFI_INTERFACE_BASE + 0x0000;
	/// <summary> Unable to access the IP settings of an WiFi interface. </summary>
	const int WCL_E_WIFI_INTERFACE_OPEN_IP_SETTINGS_FAILED = WCL_E_WIFI_INTERFACE_BASE + 0x0001;
	/// <summary> Unable to read TCP/IP settings of an WiFi interface. </summary>
	const int WCL_E_WIFI_INTERFACE_READ_IP_FAILED = WCL_E_WIFI_INTERFACE_BASE + 0x0002;
	/// <summary> Unable to change IP settings for a WiFi interface. </summary>
	const int WCL_E_WIFI_INTERFACE_SET_IP_FAILED = WCL_E_WIFI_INTERFACE_BASE + 0x0003;
	/// <summary> IP address is not valid. </summary>
	const int WCL_E_WIFI_INTERFACE_INVALID_IP = WCL_E_WIFI_INTERFACE_BASE + 0x0004;
	/// <summary> Administrative rights required for this operation. </summary>
	const int WCL_E_WIFI_INTERFACE_ADMIN_RIGHTS_REQUIRED = WCL_E_WIFI_INTERFACE_BASE + 0x0005;
	/// <summary> The TCP/IP settings for the given WLAN interface was not
	///   configured. </summary>
	const int WCL_E_WIFI_INTERFACE_IP_NOT_CONFIGURED = WCL_E_WIFI_INTERFACE_BASE + 0x0006;
	/// <summary> The network interface for the given virtual adapter was not
	///   found. </summary>
	const int WCL_E_WIFI_INTERFACE_VIRTUAL_ADAPTER_NOT_FOUND = WCL_E_WIFI_INTERFACE_BASE + 0x0007;

	/* NetCfg subsystem error codes. */

	/// <summary> The base error code for Network Configuration operations. </summary>
	const int WCL_E_WIFI_NETCFG_BASE = WCL_E_WLAN_BASE + 0xD000;
	/// <summary> Unable to prepare Network Configuration API. </summary>
	const int WCL_E_WIFI_NETCFG_PREPARE_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0000;
	/// <summary> Network Configuration API create failed. </summary>
	const int WCL_E_WIFI_NETCFG_CREATE_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0001;
	/// <summary> Network Configuration API lock create failed. </summary>
	const int WCL_E_WIFI_NETCFG_LOCK_CREATE_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0002;
	/// <summary> Network Configuration API lock failed. </summary>
	const int WCL_E_WIFI_NETCFG_LOCK_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0003;
	/// <summary> Network Configuration API initialization failed. </summary>
	const int WCL_E_WIFI_NETCFG_INIT_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0004;
	/// <summary> Unable to enumerate network interfaces. </summary>
	const int WCL_E_WIFI_NETCFG_ENUM_INTERFACES_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0005;
	/// <summary> Interface was not found. </summary>
	const int WCL_E_WIFI_NETCFG_INTERFACE_NOT_FOUND = WCL_E_WIFI_NETCFG_BASE + 0x0006;
	/// <summary> TCP/IP protocol was not found for the given WiFi interface. </summary>
	const int WCL_E_WIFI_NETCFG_PROTOCOL_NOT_FOUND = WCL_E_WIFI_NETCFG_BASE + 0x0007;
	/// <summary> Unable to switch protocol state. </summary>
	const int WCL_E_WIFI_NETCFG_SWITCH_PROTOCOL_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0008;
	/// <summary> Unable to apply changes in network configuration. </summary>
	const int WCL_E_WIFI_NETCFG_APPLY_CHANGES_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x0009;
	/// <summary> Start protocol changes thread. </summary>
	const int WCL_E_WIFI_NETCFG_START_THREAD_FAILED = WCL_E_WIFI_NETCFG_BASE + 0x000A;

	/* Mobile HotSpot error codes. */

	/// <summary> The base error code for Mobile HotSpot operations. </summary>
	const int WCL_E_WIFI_HOTSPOT_BASE = WCL_E_WLAN_BASE + 0xE000;
	/// <summary> A Mobile HotSpot has already been opened. </summary>
	const int WCL_E_WIFI_HOTSPOT_ACTIVE = WCL_E_WIFI_HOTSPOT_BASE + 0x0000;
	/// <summary> A Mobile HotSpot is closed. </summary>
	const int WCL_E_WIFI_HOTSPOT_NOT_ACTIVE = WCL_E_WIFI_HOTSPOT_BASE + 0x0001;
	/// <summary> A Mobile HotSpot has already been closed. </summary>
	const int WCL_E_WIFI_HOTSPOT_CLOSED = WCL_E_WIFI_HOTSPOT_BASE + 0x0002;
	/// <summary> Unable to create initialization event. </summary>
	const int WCL_E_WIFI_HOTSPOT_CREATE_INIT_EVENT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0003;
	/// <summary> Unable to create termination event. </summary>
	const int WCL_E_WIFI_HOTSPOT_CREATE_TERM_EVENT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0004;
	/// <summary> Unable to create and start working thread. </summary>
	const int WCL_E_WIFI_HOTSPOT_START_THREAD_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0005;
	/// <summary> Unable to create Network Information object. </summary>
	const int WCL_E_WIFI_HOTSPOT_CREATE_NET_INFO_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0006;
	/// <summary> Unable to get Internet connection profile. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_PROFILE_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0007;
	/// <summary> Internet connection profile was not found. </summary>
	const int WCL_E_WIFI_HOTSPOT_PROFILE_NOT_FOUND = WCL_E_WIFI_HOTSPOT_BASE + 0x0008;
	/// <summary> Unable to create Mobile HotSpot Manager activation factory object. </summary>
	const int WCL_E_WIFI_HOTSPOT_CREATE_MANAGER_FACTORY_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0009;
	/// <summary> Unable to create Mobile HotSpot Manager. </summary>
	const int WCL_E_WIFI_HOTSPOT_CREATE_MANAGER_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x000A;
	/// <summary> Unable to get Mobile HotSpot state. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_STATE_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x000B;
	/// <summary> Mobile hotSpot is already started. </summary>
	const int WCL_E_WIFI_HOTSPOT_STARTED = WCL_E_WIFI_HOTSPOT_BASE + 0x000C;
	/// <summary> Unable to start Mobile HotSpot. </summary>
	const int WCL_E_WIFI_HOTSPOT_START_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x000D;
	/// <summary> IAsyncInfor interface not supported. </summary>
	const int WCL_E_WIFI_HOTSPOT_QUERY_ASYNC_INFO_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x000E;
	/// <summary> Unable to get operation result. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_OPERATION_RESULT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x000F;
	/// <summary> Get operation status failed. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_OPERATION_STATUS_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0010;
	/// <summary> The operation could not begin because the mobile broadband
	///   device is turned off. </summary>
	const int WCL_E_WIFI_HOTSPOT_MOBILE_DEVICE_OFF = WCL_E_WIFI_HOTSPOT_BASE + 0x0011;
	/// <summary> The operation could not begin because the Wi-Fi device is turned off. </summary>
	const int WCL_E_WIFI_HOTSPOT_WIFI_DEVICE_OFF = WCL_E_WIFI_HOTSPOT_BASE + 0x0012;
	/// <summary> The operation did not complete because the mobile operator could
	///   not be contacted to confirm tethering capabilities are provided for
	///   this account. </summary>
	const int WCL_E_WIFI_HOTSPOT_CHECK_TIMEOUT = WCL_E_WIFI_HOTSPOT_BASE + 0x0013;
	/// <summary> The operation did not complete because the account does not
	///   currently support tethering operations. </summary>
	const int WCL_E_WIFI_HOTSPOT_CHECK_FAILURE = WCL_E_WIFI_HOTSPOT_BASE + 0x0014;
	/// <summary> The operation is still in progress. </summary>
	const int WCL_E_WIFI_HOTSPOT_OPERATION_IN_PROGRESS = WCL_E_WIFI_HOTSPOT_BASE + 0x0015;
	/// <summary> The operation could not begin because Bluetooth or a required
	///   Bluetooth device is turned off. </summary>
	const int WCL_E_WIFI_HOTSPOT_BLUETOOTH_DEVICE_OFF = WCL_E_WIFI_HOTSPOT_BASE + 0x0016;
	/// <summary> The operation did not complete because of limited network
	///   connectivity. </summary>
	const int WCL_E_WIFI_HOTSPOT_NETWORK_LIMITATION = WCL_E_WIFI_HOTSPOT_BASE + 0x0017;
	/// <summary> Unknown or undefined operation result. </summary>
	const int WCL_E_WIFI_HOTSPOT_UNKNOWN = WCL_E_WIFI_HOTSPOT_BASE + 0x0018;
	/// <summary> The Mobile HotSpot is topped. </summary>
	const int WCL_E_WIFI_HOTSPOT_STOPPED = WCL_E_WIFI_HOTSPOT_BASE + 0x0019;
	/// <summary> WiFi hardware is turned off or not available. </summary>
	const int WCL_E_WIFI_HOTSPOT_WIFI_HARDWARE_NOT_FOUND = WCL_E_WIFI_HOTSPOT_BASE + 0x001A;
	/// <summary> Get access point configuration failed. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_CONFIG_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x001B;
	/// <summary> Unable to get current SSID. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_SSID_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x001C;
	/// <summary> Unable to set new SSID. </summary>
	const int WCL_E_WIFI_HOTSPOT_SET_SSID_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x001D;
	/// <summary> Unable to save new AP config. </summary>
	const int WCL_E_WIFI_HOTSPOT_SET_CONFIG_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x001E;
	/// <summary> Unable to get current passphrase. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_PASSPHRASE_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x001F;
	/// <summary> Unable to set new passphrase. </summary>
	const int WCL_E_WIFI_HOTSPOT_SET_PASSPHRASE_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0020;
	/// <summary> Unable to get maximum client connections count. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_MAX_CLIENTS_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0021;
	/// <summary> Unable to get connected clients count. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_CLIENTS_COUNT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0022;
	/// <summary> Unable to get connected clients list. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_CLIENTS_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0023;
	/// <summary> Unable to get connected clients list size. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_CLIENTS_LIST_SIZE_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0024;
	/// <summary> Specified band is not supported. </summary>
	const int WCL_E_WIFI_HOTSPOT_BAND_NOT_SUPPORTED = WCL_E_WIFI_HOTSPOT_BASE + 0x0025;
	/// <summary> Unable to change band. </summary>
	const int WCL_E_WIFI_HOTSPOT_SET_BAND_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0026;
	/// <summary> Unable to change No Connection Timeout state. </summary>
	const int WCL_E_WIFI_HOTSPOT_CHANGE_NO_CONNECTION_TIMEOUT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0027;
	/// <summary> Get Not Connection Timeout state failed. </summary>
	const int WCL_E_WIFI_HOTSPOT_GET_NO_CONNECTION_TIMEOUT_FAILED = WCL_E_WIFI_HOTSPOT_BASE + 0x0028;

	/// <summary> The base exception class for all WiFi exceptions. </summary>
	/// <seealso cref="wclCommon::wclException" />
	class wclEWiFi : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEWiFi(const char* msg) : wclException(msg) { };
	};

	/// <summary> The wclWiFiEvents exceptions. </summary>
	/// <seealso cref="wclEWiFi" />
	class wclEWiFiEvents : public wclEWiFi
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEWiFiEvents(const char* msg) : wclEWiFi(msg) { };
	};

	/// <summary> The WiFi Sniffer exceptions. </summary>
	  /// <seealso cref="wclEWiFi" />
	class wclEWiFiSniffer : public wclEWiFi
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEWiFiSniffer(const char* msg) : wclEWiFi(msg) { };
	};

	/// <summary> The WiFi direct exceptions. </summary>
	/// <seealso cref="wclEWiFi" />
	class wclEWiFiDirect : public wclEWiFi
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEWiFiDirect(const char* msg) : wclEWiFi(msg) { };
	};
	
	/// <summary> The Network List Manager exceptions. </summary>
	/// <seealso cref="wclEWiFi" />
	class wclEWiFiNlm : public wclEWiFi
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEWiFiNlm(const char* msg) : wclEWiFi(msg) { };
	};

	/// <summary> The function allocates error space for the WiFi subsystem. </summary>
	/// <returns> Returns <c>0</c> if operation completed with success. </returns>
	/// <remarks> The function is for internal use only. An application
	///   must never use this function. </remarks>
	int wclWiFiErrorHelperAllocator();
}