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

#include <vector>
#include <set>

#include <tchar.h>
#include <INITGUID.H>

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "..\DRI\wclDriAsd.h"

#include "wclWiFiErrors.h"

/// <summary> This macro helps to build correct documentation. </summary>
#define _WCL_WIFI_WLAN_INCLUDE_FILE_ "wclWlan.h"
#include _WCL_WIFI_WLAN_INCLUDE_FILE_ 

using namespace wclDri;

namespace wclWiFi
{
	/// <summary> The base component class for all WCL WiFi Framework
	///   components </summary>
	/// <remarks> The class implements the basic operations such us initializing
	///   and finalizing underlying WLAN subsystem, manages privileges and
	///   others common operations. </remarks>
	class CwclCustomWiFiComponent
	{
		DISABLE_COPY(CwclCustomWiFiComponent);
			
	private:
		HANDLE	FHandle;
		
	protected:
		/// <summary> The function must setup privileges for Native WiFi. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> By default this function does nothing and always returns
		///   <see cref="WCL_E_SUCCESS" />. The
		///   <c>CwclCustomWiFiSecurableComponent</c> class overrides this function
		///   to implement elevation code. </remarks>
		virtual int ElevatePrivileges() const;

		/// <summary> Executes additional finalization procedures. </summary>
		/// <remarks> <para> The derived class must override this method to execute
		///   extra finalization procedures. </para>
		///   <para> If the derived class does not need any extra finalization then
		///   the method must return <see cref="wclCommon::WCL_E_SUCCESS" /> result
		///   code. </para> </remarks>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() = 0;
		/// <summary> Executes additional initialization procedures. </summary>
		/// <remarks> <para> The derived class must override this method to execute
		///   extra initialization procedures. </para>
		///   <para> If the derived class does not need any extra initialization
		///   then the method must return <see cref="wclCommon::WCL_E_SUCCESS" /> result
		///   code. </para> </remarks>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() = 0;
		
		/// <summary> Fires the <c>AfterOpen</c> event. </summary>
		virtual void DoAfterOpen();
		/// <summary> Fires the <c>BeforeClose</c> event. </summary>
		virtual void DoBeforeClose();

		/// <summary> Provides access to the WLAN subsystem handle. </summary>
		/// <returns> The WLAN subsystem handle. </returns>
		HANDLE GetHandle() const;
		/// <summary> Provides access to the WLAN subsystem handle. </summary>
		/// <value> The WLAN subsystem handle. </value>
		__declspec(property(get = GetHandle)) HANDLE Handle;
		
	public:
		/// <summary> Creates a new component. </summary>
		CwclCustomWiFiComponent();
		/// <summary> Frees the component. </summary>
		virtual ~CwclCustomWiFiComponent();
		
		/// <summary> Closes the component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> Before using any of the methods of the component an
		///   application must call the <c>Open</c> method. </remarks>
		int Open();
		
		/// <summary> Gets the component state. </summary>
		/// <returns> <c>True</c> if the component is opened. </returns>
		bool GetActive() const;
		/// <summary> Gets the component state. </summary>
		/// <value> <c>True</c> if the component is opened. </value>
		__declspec(property(get = GetActive)) bool Active;
		
		/// <summary> The event fires after the component was successfully
		///   opened. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <remarks> The event fires only if the <c>Open</c> method returns
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the <c>Open</c> method failed then
		///   the even will not fire. </remarks>
		wclNotifyEvent(AfterOpen);
		
		/// <summary> The even fires before the component will be closed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(BeforeClose);
	};

	/// <summary> The class adds the WLAN security management to basic WiFi
	///   methods. </summary>
	/// <remarks> This is the base class for the WiFi Framework components
	///   which require security settings management. </remarks>
	/// <seealso cref="CwclCustomWiFiComponent" />
	class CwclCustomWiFiSecurableComponent : public CwclCustomWiFiComponent
	{
		DISABLE_COPY(CwclCustomWiFiSecurableComponent);

	protected:
		/// <summary> The function sets up privileges for Native WiFi. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int ElevatePrivileges() const override;

	public:
		/// <summary> Creates new object. </summary>
		CwclCustomWiFiSecurableComponent();
	};

	/// <summary> Adds the WLAN memory management methods to basic WiFi
	///   methods. </summary>
	/// <remarks> This is the base class for the WiFi Framework components
	///   which require memory disposing for some methods. </remarks>
	/// <seealso cref="CwclCustomWiFiSecurableComponent" />
	class CwclCustomWiFiMemoryComponent : public CwclCustomWiFiSecurableComponent
	{
		DISABLE_COPY(CwclCustomWiFiMemoryComponent);

	public:
		/// <summary> Creates new object. </summary>
		CwclCustomWiFiMemoryComponent();

		/// <summary> The method frees memory. </summary>
		/// <param name="Memory"> Pointer to the memory to be freed. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		int FreeMemory(const LPVOID Memory) const;
	};

	/// <summary> The connection state of an ad hoc network. </summary>
	typedef enum
	{
		/// <summary> The ad hoc network has been formed, but no client or
		///   host is connected to the network. </summary>
		asFormed,
		/// <summary> A client or host is connected to the ad hoc
		///   network. </summary>
		asConnected
	} wclWiFiAdHocNetworkState;

	/// <summary> Defines a basic service set (BSS) network type.. </summary>
	typedef enum
	{
		/// <summary> Specifies an infrastructure BSS network. </summary>
		bssInfrastructure,
		/// <summary> Specifies an independent BSS (IBSS) network. </summary>
		bssIndependent,
		/// <summary> Specifies either infrastructure or IBSS network. </summary>
		bssAny
	} wclWiFiBssType;

	/// <summary> Defines the mode of connection. </summary>
	typedef enum
	{
		/// <summary> A profile will be used to make the connection. </summary>
		cmProfile,
		/// <summary> A temporary profile will be used to make the
		///   connection. </summary>
		cmTemporaryProfile,
		/// <summary> Secure discovery will be used to make the
		///   connection. </summary>
		cmDiscoverySecure,
		/// <summary> Unsecure discovery will be used to make the
		///   connection. </summary>
		cmDiscoveryUnsecure,
		/// <summary> The connection is initiated by the wireless service
		///   automatically using a persistent profile. </summary>
		cmAuto,
		/// <summary> The connection mode is invalid or unsupported. </summary>
		cmInvalid
	} wclWiFiConnectionMode;

	/// <summary> The flags that provide additional information for the network
	///   connection. </summary>
	typedef enum
	{
		/// <summary> Indicates that an ad-hoc network is formed. </summary>
		cfAdHocNetworkFormed,
		/// <summary> Indicates that the connection uses a per-user profile owned
		///   by the console user. Non-console users will not be able to see the
		///   profile in their profile list. </summary>
		cfConsoleUserProfile
	} wclWiFiConnectionFlag;

	/// <summary> A set of flags that provide additional information for the
	///   network connection. </summary>
	/// <seealso cref="wclWiFiConnectionFlag" />
	typedef std::set<wclWiFiConnectionFlag> wclWiFiConnectionFlags;

	/// <summary> The record contains information about connection related
	///   events. </summary>
	typedef struct
	{
		/// <summary> The mode of the connection. </summary>
		/// <seealso cref="wclWiFiConnectionMode" />
		wclWiFiConnectionMode ConnectionMode;
		/// <summary> The name of the profile used for the connection.
		///   Profile names are case-sensitive. </summary>
		tstring ProfileName;
		/// <summary> The SSID of the association. </summary>
		tstring Ssid;
		/// <summary> The BSS network type. </summary>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiBssType BssType;
		/// <summary> Indicates whether security is enabled for this connection.
		///   If <c>True</c>, security is enabled. </summary>
		bool SecurityEnabled;
		/// <summary> The reason for an operation failure. This field has a value
		///   of <see cref="wclCommon::WCL_E_SUCCESS" /> for all connection-related
		///   events except <c>OnAcmConnectionComplete</c>. If the connection fails,
		///   this field indicates the reason for the failure. </summary>
		int Reason;
		/// <summary> A set of flags that provide additional information for the
		///   network connection. </summary>
		/// <seealso cref="wclWiFiConnectionFlags" />
		wclWiFiConnectionFlags Flags;
		/// <summary> The XML presentation of the profile used for discovery,
		///   if the connection succeeds. </summary>
		tstring ProfileXml;
	} wclWiFiAcmConnectionEventData;

	/// <summary> The WiFi power saving modes. </summary>
	typedef enum
	{
		/// <summary> Specifies no power-saving activity performed by the 802.11
		///   station. </summary>
		psNo,
		/// <summary> Specifies a power save polling (PSP) mode that uses the
		///   fastest power-saving mode. This power mode must provide the best
		///   combination of network performance and power usage. </summary>
		psLow,
		/// <summary> Specifies a PSP mode that uses the maximum (MAX) power saving
		///   capabilities. The MAX power save mode results in the greatest power
		///   savings for the radio on the 802.11 station. </summary>
		psMedium,
		/// <summary> Specifies a proprietary PSP mode implemented by the
		///   independent hardware vendor (IHV) that exceeds the "psMedium"
		///   power-saving level. </summary>
		psMaximum,
		/// <summary> The supplied power setting is invalid. </summary>
		psInvalid
	} wclWiFiPowerSetting;

	/// <summary> The possible values for the authentication state of a peer on
	///   the wireless Hosted Network. </summary>
	typedef enum
	{
		/// <summary> An invalid peer state. </summary>
		asInvalid,
		/// <summary> The peer is authenticated. </summary>
		asAuthenticated
	} wclWiFiHostedNetworkPeerAuthState;

	/// <summary> The record contains information about the peer state for a peer
	///   on the wireless Hosted Network. </summary>
	typedef struct
	{
		/// <summary> The MAC address of the peer being described. </summary>
		tstring Mac;
		/// <summary> The current authentication state of this peer. </summary>
		/// <seealso cref="wclWiFiHostedNetworkPeerAuthState" />
		wclWiFiHostedNetworkPeerAuthState AuthState;
	} wclWiFiHostedNetworkPeerState;
	/// <summary> The dynamic array of the
	///   <see cref="wclWiFi::wclWiFiHostedNetworkPeerState" /> records. </summary>
	typedef std::vector<wclWiFiHostedNetworkPeerState> wclWiFiHostedNetworkPeerStates;
	
	/// <summary> The Hosted Network connected peers MAC addresses array. </summary>
	typedef std::vector<tstring> wclWiFiHostedNetworkConnectedPeers;

	/// <summary> Specifies an 802.11 radio state. </summary>
	typedef enum
	{
		/// <summary> The radio state is unknown. </summary>
		rsUnknown,
		/// <summary> The radio is on. </summary>
		rsOn,
		/// <summary> The radio is off. </summary>
		rsOff
	} wclWiFiRadioState;

	/// <summary> The network state of the wireless Hosted Network. </summary>
	typedef enum
	{
		/// <summary> The wireless Hosted Network is unavailable. </summary>
		hnUnavailable,
		/// <summary> The wireless Hosted Network is idle. </summary>
		hnIdle,
		/// <summary> The wireless Hosted Network is active. </summary>
		hnActive
	} wclWiFiHostedNetworkState;

	/// <summary> The interface operation modes. </summary>
	typedef enum
	{
		/// <summary> The operation mode is unknown or unsupported. </summary>
		omUnknown,
		/// <summary> Specifies the Station (STA) operation mode. </summary>
		omStation,
		/// <summary> Specifies the Access Point (AP) operation mode. </summary>
		omAccessPoint,
		/// <summary> Specifies the Extensible Station (ExtSTA) operation
		///   mode. </summary>
		omExtensibleStation,
		/// <summary> Specifies the Extensible Access Point (ExtAP) operation
		///   mode. </summary>
		omExtensibleAccessPoint,
		/// <summary> Specifies the WiFi Direct Device operation mode. </summary>
		omWiFiDirectDevice,
		/// <summary> Specifies the WiFi Direct Group Owner operation
		///   mode. </summary>
		omWiFiDirectGroupOwner,
		/// <summary> Specifies the WiFi Direct Client operation mode. </summary>
		omWiFiDirectClient,
		/// <summary> Specifies the manufacturing operation mode. </summary>
		omManufacturing,
		/// <summary> Specifies the Network Monitor (NetMon) operation
		///   mode. </summary>
		omNetworkMonitor
	} wclWiFiOperationMode;

	/// <summary> Indicates the state of an interface. </summary>
	typedef enum
	{
		/// <summary> The interface is not ready to operate. </summary>
		isNotReady,
		/// <summary> The interface is connected to a network. </summary>
		isConnected,
		/// <summary> The interface is the first node in an ad hoc network. No peer
		///   has connected. </summary>
		isAdHocFormed,
		/// <summary> The interface is disconnecting from the current
		///   network. </summary>
		isDisconnecting,
		/// <summary> The interface is not connected to any network. </summary>
		isDisconnected,
		/// <summary> The interface is attempting to associate with a
		///   network. </summary>
		isAssociating,
		/// <summary> Auto configuration is discovering the settings for the
		///   network. </summary>
		isDiscovering,
		/// <summary> The interface is in the process of authenticating. </summary>
		isAuthenticating
	} wclWiFiInterfaceState;

	/// <summary> The record contains information about media specific module
	///   (MSM) connection related notifications. </summary>
	typedef struct
	{
		/// <summary> The mode of the connection. </summary>
		/// <seealso cref="wclWiFiConnectionMode" />
		wclWiFiConnectionMode ConnectionMode;
		/// <summary> The name of the profile used for the connection.
		///   Profile names are case-sensitive. </summary>
		tstring ProfileName;
		/// <summary> The SSID of the association. </summary>
		tstring Ssid;
		/// <summary> The BSS network type. </summary>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiBssType BssType;
		/// <summary> The MAC address of the peer or access point. </summary>
		tstring Mac;
		/// <summary> Indicates whether security is enabled for this connection.
		///   If <c>True</c>, security is enabled. </summary>
		bool SecurityEnabled;
		/// <summary> <para> Indicates whether the peer is the first to join the ad
		///   hoc network created by the machine. If <c>True</c>, the peer is the
		///   first to join. </para>
		///   <para> After the first peer joins the network, the interface state of
		///   the machine that created the ad hoc network changes from
		///   <c>isAdHocFormed</c> to <c>isConnected</c>. </para> </summary>
		/// <seealso cref="wclWiFiInterfaceState" />
		bool FirstPeer;
		/// <summary> Indicates whether the peer is the last to leave the ad hoc
		///   network created by the machine. If <c>True</c>, the peer is the last
		///   to leave. After the last peer leaves the network, the interface state
		///   of the machine that created the ad hoc network changes from
		///   <c>isConnected</c> to <c>isAdHocFormed</c>. </summary>
		/// <seealso cref="wclWiFiInterfaceState" />
		bool LastPeer;
		/// <summary> The reason for an operation failure. If the operation
		///   succeeds, this field has a value of <see cref="wclCommon::WCL_E_SUCCESS" />.
		///   Otherwise, this field indicates the reason for the failure. </summary>
		int Reason;
	} wclWiFiMsmConnectionEventData;

	/// <summary> Defines an 802.11 PHY and media type. </summary>
	typedef enum
	{
		/// <summary> Any PHY type. </summary>
		phyAny,
		/// <summary> A frequency-hopping spread-spectrum (FHSS) PHY.
		///   Bluetooth devices can use FHSS or an adaptation of FHSS. </summary>
		phyFhss,
		/// <summary> A direct sequence spread spectrum (DSSS) PHY type. </summary>
		phyDsss,
		/// <summary> An infrared (IR) baseband PHY type. </summary>
		phyIr,
		/// <summary> An orthogonal frequency division multiplexing (OFDM) PHY
		///   type. 802.11a devices can use OFDM. </summary>
		phyOfdm,
		/// <summary> A high-rate DSSS (HRDSSS) PHY type. </summary>
		phyHrDsss,
		/// <summary> An extended rate PHY type (ERP). 802.11g devices can use
		///   ERP. </summary>
		phyErp,
		/// <summary> The 802.11n PHY type. </summary>
		phyHt,
		/// <summary> The 802.11ac PHY type. This is the very high throughput PHY
		///   type specified in IEEE 802.11ac. </summary>
		phyVht,
		/// <summary> An unknown or uninitialized PHY type. </summary>
		phyUnknown
	} wclWiFiPhy;

	/// <summary> Set of the supported PHYs. </summary>
	/// <seealso cref="wclWiFiPhy" />
	typedef std::set<wclWiFiPhy> wclWiFiPhys;

	/// <summary> Specifies the radio state on a specific physical layer (PHY)
	///   type. </summary>
	typedef struct
	{
		/// <summary> The PHY type on which the radio state is being set or
		///   queried. </summary>
		/// <seealso cref="wclWiFiPhy" />
		wclWiFiPhy Phy;
		/// <summary> Indicates the software radio state. </summary>
		/// <seealso cref="wclWiFiRadioState" />
		wclWiFiRadioState SoftwareState;
		/// <summary> Indicates the hardware radio state. </summary>
		/// <seealso cref="wclWiFiRadioState" />
		wclWiFiRadioState HardwareState;
	} wclWiFiPhyRadioState;
	/// <summary> The array of the interface's radio states for supported
	///   PHYs. </summary>
	/// <seealso cref="wclWiFiPhyRadioState" />
	typedef std::vector<wclWiFiPhyRadioState> wclWiFiPhyRadioStates;

	/// <summary> The record represents IP settings. </summary>
	typedef struct
	{
		/// <summary> <c>True</c> if IP address is static. <c>False</c> if
		///   IP address is assigned by DHCP. </summary>
		bool Static;
		/// <summary> The IP address. </summary>
		tstring Address;
		/// <summary> The subnet mask. </summary>
		tstring Mask;
		/// <summary> The default gateway. </summary>
		tstring Gateway;
		/// <summary> The primary DNS address. </summary>
		tstring Dns1;
		/// <summary> The secondary DNS address. </summary>
		tstring Dns2;
	} wclWiFiIpSettings;

	/// <summary> The type specifies the possible values for the 802.1X
	///   authentication status. </summary>
	typedef enum
	{
		/// <summary> 802.1X authentication was not started. </summary>
		oxAuthNotStarted,
		/// <summary> 802.1X authentication is in progress. </summary>
		oxAuthInProgress,
		/// <summary> No 802.1X authenticator was found. The 802.1X authentication
		///   was attempted, but no 802.1X peer was found. In this case, either the
		///   network does not support or is not configured to support the 802.1X
		///   standard. </summary>
		oxAuthNoAuthenticatorFound,
		/// <summary> 802.1X authentication was successful. </summary>
		oxAuthSuccess,
		/// <summary> 802.1X authentication was a failure. </summary>
		oxAuthFailure,
		/// <summary> Unknown or invalid status. </summary>
		oxAuthInvalid
	} wclWiFiOneXAuthStatus;

	/// <summary> The structure contains the current 802.1X authentication
	///   status. </summary>
	typedef struct
	{
		/// <summary> The current status of the 802.1X authentication process. Any
		///   error that may have occurred during authentication is indicated below
		///   by the value of the <c>Reason</c> and <c>Error</c> members of the
		///   <c>wclWiFiOneXStatus</c> structure. </summary>
		/// <seealso cref="wclWiFiOneXAuthStatus" />
		wclWiFiOneXAuthStatus Status;
		/// <summary> If an error occurred during 802.1X authentication, this
		///   member contains the reason for the error  This member is normally
		///   <see cref="WCL_E_SUCCESS" /> when 802.1X authentication is successful
		///   and no error occurs. </summary>
		int Reason;
		/// <summary> If an error occurred during 802.1X authentication, this member
		///   contains the error. This member is normally
		///   <see cref="WCL_E_SUCCESS" />, except when an EAPHost error
		///   occurs. </summary>
		int Error;
	} wclWiFiOneXStatus;

	/// <summary> The type specifies the possible values for whether the EAP
	///   method configured on the supplicant for 802.1X authentication is
	///   supported on the authentication server. </summary>
	typedef enum
	{
		/// <summary> It is not known whether the EAP method configured on the
		///   supplicant for 802.1X authentication is supported on the
		///   authentication server. This value can be returned if the 802.1X
		///   authentication process is in the initial state. </summary>
		oxEapMethodBackendSupportUnknown,
		/// <summary> The EAP method configured on the supplicant for 802.1X
		///   authentication is supported on the authentication server. The 802.1X
		///   handshake is used to decide what is an acceptable EAP method to
		///   use. </summary>
		oxEapMethodBackendSupported,
		/// <summary> The EAP method configured on the supplicant for 802.1X
		///   authentication is not supported on the authentication
		///   server. </summary>
		oxEapMethodBackendUnsupported
	} wclWiFiOneXEapMethodBackendSupport;

	/// <summary> The type defines possible supplicant mode values. </summary>
	typedef enum
	{
		/// <summary> EAPOL-Start messages are not transmitted. Valid for wired LAN
		///   profiles only. </summary>
		oxSupplicantModeInhibitTransmission,
		/// <summary> The client determines when to send EAPOL-Start packets based
		///   on network capability. EAPOL-Start messages are only sent when
		///   required. Valid for wired LAN profiles only. </summary>
		oxSupplicantModeLearn,
		/// <summary> EAPOL-Start messages are transmitted as specified by 802.1X.
		///   Valid for both wired and wireless LAN profiles. </summary>
		oxSupplicantModeCompliant,
		/// <summary> Unknown or unsupported supplicant mode. </summary>
		oxSupplicantModeInvalid
	} wclWiFiOneXSupplicantMode;

	/// <summary> The type defines possible authentication mode values. </summary>
	typedef enum
	{
		/// <summary> Use machine or user credentials. When a user is logged on, the
		///   user's credentials are used for authentication. When no user is
		///   logged on, machine credentials are used. </summary>
		oxAuthModeMachineOrUser,
		/// <summary> Use machine credentials only. </summary>
		oxAuthModeMachineOnly,
		/// <summary> Use user credentials only. </summary>
		oxAuthModeUserOnly,
		/// <summary> Use guest (empty) credentials only. </summary>
		oxAuthModeGuest,
		/// <summary> Credentials to use are not specified. </summary>
		oxAuthModeUnspecified,
		/// <summary> Unknown or unsupported authentication mode. </summary>
		oxAuthModeInvalid
	} wclWiFiOnexXAuthMode;

	/// <summary> The structure contains information on the 802.1X connection
	///   profile currently used for 802.1X authentication. </summary>
	typedef struct
	{
		/// <summary> The supplicantMode element in the 802.1X schema that specifies
		///   the method of transmission used for EAPOL-Start messages. </summary>
		/// <seealso cref="wclWiFiOneXSupplicantMode" />
		wclWiFiOneXSupplicantMode SupplicantMode;
		/// <summary> The authMode element in the 802.1X schema that specifies the
		///   type of credentials used for 802.1X authentication. </summary>
		/// <seealso cref="wclWiFiOnexXAuthMode" />
		wclWiFiOnexXAuthMode AuthMode;
		/// <summary> The heldPeriod element in the 802.1X schema that specifies the
		///   length of time, in seconds, in which a client will not re-attempt
		///   authentication after a failed authentication attempt. </summary>
		unsigned long HeldPeriod;
		/// <summary> The authPeriod element in the 802.1X schema that specifies the
		///   maximum length of time, in seconds, in which a client waits for a
		///   response from the authenticator. If a response is not received within
		///   the specified period, the client assumes that there is no
		///   authenticator present on the network. </summary>
		unsigned long AuthPeriod;
		/// <summary> The startPeriod element in the 802.1X schema that specifies
		///   the length of time, in seconds, to wait before an EAPOL-Start is sent.
		///   An EAPOL-Start message is sent to start the 802.1X authentication
		///   process. </summary>
		unsigned long StartPeriod;
		/// <summary> The maxStart element in the 802.1X schema that specifies the
		///   maximum number of EAPOL-Start messages sent. After the maximum number
		///   of EAPOL-Start messages has been sent, the client assumes that there
		///   is no authenticator present on the network. </summary>
		unsigned long MaxStart;
		/// <summary> The maxAuthFailures element in the 802.1X schema that
		///   specifies the maximum number of authentication failures allowed for a
		///   set of credentials. </summary>
		unsigned long MaxAuthFailures;
		/// <summary> The time, in seconds, to wait for 802.1X authentication
		///   completion before normal logon proceeds. This value is used in single
		///   sign-on (SSO) scenarios. This value defaults to 10 seconds in an
		///   802.1X profile. </summary>
		unsigned long NetworkAuthTimeout;
		/// <summary> <para> The maximum duration time, in seconds, to wait for a
		///   connection in case a user interface dialog box that requires user
		///   input is displayed during the per-logon SSO. </para>
		///   <para> On Windows Vista with SP1 and later, this value is hard-coded
		///   to 10 minutes and is not configurable. On Windows Vista Release to
		///   Manufacturing, this value defaults to 60 seconds in an 802.1X profile
		///   and was controlled by the maxDelayWithAdditionalDialogs element in the
		///   schema. </para>
		///   <para> On Windows Vista with SP1 and later, the
		///   maxDelayWithAdditionalDialogs element in the 802.1X schema is ignored
		///   and deprecated. </para> </summary>
		unsigned long NetworkAuthWithUITimeout;
		/// <summary> A value that specifies whether to allow EAP dialogs to be
		///   displayed when using pre-logon SSO. </summary>
		bool AllowLogonDialogs;
		/// <summary> The userBasedVirtualLan element in the 802.1X schema that
		///   specifies if the virtual LAN (VLAN) used by the device changes based
		///   on the user's credentials. Some network access server (NAS) devices
		///   change the VLAN after a user authenticates. When userBasedVirtualLan
		///   is <c>TRUE</c>, the NAS may change a device's VLAN after a user
		///   authenticates. </summary>
		bool UserBasedVLan;
	} wclWiFiOneXConnectionProfile;

	/// <summary> The type specifies the possible values of the identity used for
	///   802.1X authentication status. </summary>
	typedef enum
	{
		/// <summary> No identity is specified in the profile used for 802.1X
		///   authentication. </summary>
		oxAuthIdentityNone,
		/// <summary> The identity of the local machine account is used for 802.1X
		///   authentication. </summary>
		oxAuthIdentityMachine,
		/// <summary> The identity of the logged-on user is used for 802.1X
		///   authentication. </summary>
		oxAuthIdentityUser,
		/// <summary> The identity of an explicit user as specified in the profile
		///   is used for 802.1X authentication. This value is used when performing
		///   single sign-on or when credentials are saved with the
		///   profile. </summary>
		oxAuthIdentityExplicitUser,
		/// <summary> The identity of the Guest account as specified in the profile
		///   is used for 802.1X authentication. </summary>
		oxAuthIdentityGuest,
		/// <summary> The identity is not valid as specified in the profile used for
		///   802.1X authentication. </summary>
		oxAuthIdentityInvalid,
		/// <summary> Unknown or unspecified identity. </summary>
		oxAuthIdentityUnknown
	} wclWiFiOneXAuthIdentity;

	/// <summary> Defines the set of possible isolation state values of a machine.
	///   The isolation state of a machine determines its network
	///   connectivity. </summary>
	typedef enum
	{
		/// <summary> The client's access to the network is unknown. </summary>
		isUnknonw,
		/// <summary> The client has unrestricted full access to the
		///   network. </summary>
		isNotRestricted,
		/// <summary> The client has probationary access to the network for a
		///   limited amount of time during which time they must fix their
		///   system. </summary>
		isInProbation,
		/// <summary> The client has restricted access to the network; the client is
		///   allowed access to some servers only from which they can obtain
		///   necessary information and patches to update themselves to become
		///   healthy. </summary>
		isRestrictedAccess,
		/// <summary> The isolation state is invalid or unspecified. </summary>
		isInvalid
	} wclWiFiIsolationState;

	/// <summary> The structure contains 802.1X authentication parameters used for
	///   802.1X authentication. </summary>
	typedef struct
	{
		/// <summary> Indicates if a status update is pending for 802.X
		///   authentication. </summary>
		bool UpdatePending;
		/// <summary> The 802.1X authentication connection profile. </summary>
		/// <seealso cref="wclWiFiOneXConnectionProfile" />
		wclWiFiOneXConnectionProfile Profile;
		/// <summary> The identity used for 802.1X authentication status. </summary>
		/// <seealso cref="wclWiFiOneXAuthIdentity" />
		wclWiFiOneXAuthIdentity AuthIdentity;
		/// <summary> The quarantine isolation state value of the local computer.
		///   The isolation state determines its network connectivity. </summary>
		/// <seealso cref="wclWiFiIsolationState" />
		wclWiFiIsolationState QuarantineState;
		/// <summary> The session ID of the user currently logged on to the
		///   console. </summary>
		unsigned long SessiondId;
		/// <summary> The 802.1X identity used for 802.1X authentication. </summary>
		tstring Identity;
		/// <summary> The user name used for 802.1X authentication. </summary>
		tstring UserName;
		/// <summary> The domain used for 802.1X authentication. </summary>
		tstring Domain;
	} wclWiFiOnexXAuthParams;

	/// <summary> The structure contains type and vendor identification
	///   information for an EAP method. </summary>
	typedef struct
	{
		/// <summary> The numeric type code for this EAP method. </summary>
		unsigned char EapType;
		/// <summary> The vendor ID for the EAP method. </summary>
		unsigned long VendorId;
		/// <summary> The numeric type code for the vendor of this EAP
		///   method. </summary>
		unsigned long VendorType;
	} wclWiFiEapType;

	/// <summary> The structure contains type, identification, and author
	///   information about an EAP method. </summary>
	typedef struct
	{
		/// <summary> Contains the ID for the EAP method as well as specific
		///   vendor information. </summary>
		/// <seealso cref="wclWiFiEapType" />
		wclWiFiEapType EapType;
		/// <summary> The numeric ID for the author of the EAP method. </summary>
		unsigned long AuthorId;
	} wclWiFiEapMethodType;

	/// <summary> structure contains 802.1X EAP error when an error occurs with
	///   802.1X authentication. </summary>
	typedef struct
	{
		/// <summary> The OS error code. </summary>
		int Error;
		/// <summary> The EAP method type that raised the error during 802.1X
		///   authentication. </summary>
		/// <seealso cref="wclWiFiEapMethodType" />
		wclWiFiEapMethodType MethodType;
		/// <summary> The reason the EAP method failed. </summary>
		int Reason;
		/// <summary> A unique ID that identifies cause of error in EAPHost. An EAP
		///   method can define a new GUID and associate the GUID with a specific
		///   root cause. </summary>
		GUID RootCauseGuid;
		/// <summary> A unique ID that maps to a localizable string that identifies
		///   the repair action that can be taken to fix the reported
		///   error. </summary>
		GUID RepairGuid;
		/// <summary> A unique ID that maps to a localizable string that specifies
		///   an URL for a page that contains additional information about an error
		///   or repair message. An EAP method can potentially define a new GUID and
		///   associate with one specific help link. </summary>
		GUID HelpLinkGuid;
		/// <summary> A localized and readable string that describes the root cause
		///   of the error. </summary>
		tstring RootCauseString;
		/// <summary> A localized and readable string that describes the possible
		///   repair action. </summary>
		tstring RepairString;
	} wclWiFiOneXEapError;

	/// <summary> The structure contains information on a status change to 802.1X
	///   authentication. </summary>
	typedef struct
	{
		/// <summary> Specifies the current 802.1X authentication status. </summary>
		/// <seealso cref="wclWiFiOneXStatus" />
		wclWiFiOneXStatus Status;
		/// <summary> <para> Indicates if the configured EAP method on the
		///   supplicant is supported on the 802.1X authentication server. </para>
		///   <para> EAP permits the use of a back-end authentication server, which
		///   may implement some or all authentication methods, with the
		///   authenticator acting as a pass-through for some or all methods and
		///   peers. </para> </summary>
		/// <seealso cref="wclWiFiOneXEapMethodBackendSupport" />
		wclWiFiOneXEapMethodBackendSupport BackendSupport;
		/// <summary> Indicates if a response was received from the 802.1X
		///   authentication server. </summary>
		bool BackendEngaged;
		/// <summary> The 802.1X authentication parameters. </summary>
		/// <seealso cref="wclWiFiOnexXAuthParams" />
		wclWiFiOnexXAuthParams AuthParams;
		/// <summary> An EAP error value. </summary>
		/// <seealso cref="wclWiFiOneXEapError" />
		wclWiFiOneXEapError EapError;
	} wclWiFiOneXStatusUpdate;

	/// <summary> The <c>OnAcmAdHocNetworkStateChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="State"> The new ad-hoc network state. </param>
	/// <seealso cref="wclWiFiAdHocNetworkState" />
	#define wclWiFiAcmAdHocNetworkStateChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiAdHocNetworkState State)
	/// <summary> The <c>OnAcmBssTypeChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="BssType"> The new basic service set (BSS) type. </param>
	/// <seealso cref="wclWiFiBssType" />
	#define wclWiFiAcmBssTypeChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId,  \
			const wclWiFiBssType BssType)
	/// <summary> The event handler prototype for ACM connection related
	///   events </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Data"> Contains information about connection related
	///   event. </param>
	/// <seealso cref="wclWiFiAcmConnectionEventData" />
	#define wclWiFiAcmConnectionEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiAcmConnectionEventData& Data)
	/// <summary> The <c>OnAcmPowerSettingChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Setting"> The new power setting of an interface. </param>
	/// <seealso cref="wclWiFiPowerSetting" />
	#define wclWiFiAcmPowerSettingChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiPowerSetting Setting)
	/// <summary> The <c>OnAcmProfileNameChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="OldName"> The old profile name. </param>
	/// <param name="NewName"> The new profile name. </param>
	#define wclWiFiAcmProfileNameChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const tstring& OldName, const tstring& NewName)
	/// <summary> The <c>OnAcmScanFail</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Reason"> The reason the WLAN operation failed. </param>
	#define wclWiFiAcmScanFailEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const int Reason)
	/// <summary> The <c>OnAcmScreenPowerChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="SwitchedOn"> The value of the screen power change. When this
	///   value is <c>True</c>, the screen changed to on. When this value is
	///   <c>False</c>, the screen changed to off. </param>
	#define wclWiFiAcmScreenPowerChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const bool SwitchedOn)

	/// <summary> The <c>OnHostednetworkPeerStateChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="OldState"> The previous network state for a data peer on
	///   the wireless Hosted Network. </param>
	/// <param name="NewState"> The current network state for a data peer on the
	///   wireless Hosted Network. </param>
	/// <param name="Reason"> The reason for the network state change for the data
	///   peer. </param>
	/// <seealso cref="wclWiFiHostedNetworkPeerState" />
	#define wclWiFiHostedNetworkPeerStateChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiHostedNetworkPeerState& OldState, \
		const wclWiFiHostedNetworkPeerState& NewState, const int Reason)
	/// <summary> The <c>OnHostedNetworkRadioStateChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="SoftwareState"> The software radio state of the wireless
	///   Hosted Network. </param>
	/// <param name="HardwareState"> The hardware radio state of the wireless
	///   Hosted Network. </param>
	/// <seealso cref="wclWiFiRadioState" />
	#define wclWiFiHostedNetworkRadioStateChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiRadioState SoftwareState, const wclWiFiRadioState HardwareState)
	/// <summary> The <c>OnHostedNetworkStateChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="OldState"> The previous network state on the wireless
	///   Hosted Network. </param>
	/// <param name="NewState"> The current network state on the wireless
	///   Hosted Network. </param>
	/// <param name="Reason"> The reason for the network state change. </param>
	/// <seealso cref="wclWiFiHostedNetworkState" />
	#define wclWiFiHostedNetworkStateChangeEvent(_event_name_) \
		__event void _event_name_(void *Sender, const GUID& IfaceId, \
		const wclWiFiHostedNetworkState OldState, \
		const wclWiFiHostedNetworkState NewState, const int Reason)

	/// <summary> The <c>OnMsmAdapterOperationModeChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Mode"> The new operation mode. </param>
	/// <seealso cref="wclWiFiOperationMode" />
	#define wclWiFiMsmAdapterOperationModeChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiOperationMode Mode)
	/// <summary> The event handler prototype for MSM connection related
	///   events </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Data"> Contains information about connection related
	///   event. </param>
	/// <seealso cref="wclWiFiMsmConnectionEventData" />
	#define wclWiFiMsmConnectionEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiMsmConnectionEventData& Data)
	/// <summary> The <c>OnMsmRadioStateChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="State"> The new radio state. </param>
	/// <seealso cref="wclWiFiPhyRadioState" />
	#define wclWiFiMsmRadioStateChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiPhyRadioState& State)
	/// <summary> The <c>OnMsmSignalQualityChange</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Quality"> The new signal quality. </param>
	#define wclWiFiMsmSignalQualityChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const unsigned long Quality)

	/// <summary> The <c>OnOneXAuthRestarted</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="Reason"> The reason that 802.1X authentication was
	///   restarted. </param>
	#define wclWiFiOneXAuthRestartedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const int Reason)
	/// <summary> The <c>OnOneXAuthUpdate</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	/// <param name="State"> Contains information on a status change to 802.1X
	///   authentication. </param>
	/// <seealso cref="wclWiFiOneXStatusUpdate" />
	#define wclWiFiOneXAuthUpdateEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiOneXStatusUpdate& State)

	/// <summary> The <c>OnIpChanged</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The WLAN interface ID. </param>
	/// <param name="Old"> The old IP settings. </param>
	/// <param name="New"> The new IP settings. </param>
	/// <seealso cref="wclWiFiIpSettings" />
	#define wclWiFiIpChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId, \
		const wclWiFiIpSettings& Old, const wclWiFiIpSettings& New)

	/// <summary> The very basic WiFi event handler prototype. This
	///   type used in lot of events of the WiFi components. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="IfaceId"> The interface's ID on which the event
	///   is for. </param>
	#define wclWiFiEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& IfaceId)

	/// <summary> The <c>CwclWiFiEvents</c> component provides access to the
	///   Wireless LAN notifications. </summary>
	/// <seealso cref="CwclCustomWiFiComponent" />
	class CwclWiFiEvents : public CwclCustomWiFiComponent
	{
		DISABLE_COPY(CwclWiFiEvents);

	private:
		typedef std::list<void*> IFACES;

		CwclMessageReceiver*		FReceiver;
		wclMessageProcessingMethod	FMessageProcessing;
		IFACES*						FIfaces;
		
		void MessageReceived(const CwclMessage* const Message);

	protected:
		/* Internal methods. */

		/// <summary> Executes additional finalization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() override;
		/// <summary> Executes additional initialization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() override;

		/* ACM events dispatchers. */
		
		/// <summary> Fires the <c>OnAcmAdHocNetworkStateChange</c>
		///   event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> The new ad-hoc network state. </param>
		/// <seealso cref="wclWiFiAdHocNetworkState" />
		virtual void DoAcmAdHocNetworkStateChange(const GUID& IfaceId, 
			const wclWiFiAdHocNetworkState State);
		/// <summary> Fires the <c>OnAcmAutoconfDisabled</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmAutoconfDisabled(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmAutoconfEnabled</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmAutoconfEnabled(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmBackgroundScanDisabled</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmBackgroundScanDisabled(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmBackgroundScanEnabled</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmBackgroundScanEnabled(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmBssTypeChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="BssType"> The new basic service set (BSS) type. </param>
		/// <seealso cref="wclWiFiBssType" />
		virtual void DoAcmBssTypeChange(const GUID& IfaceId, 
			const wclWiFiBssType BssType);
		/// <summary> Fires the <c>OnAcmConnectionAttemptFail</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <remarks> A connection consists of one or more connection attempts. An
		///   application may receive zero or more <c>OnAcmConnectionAttemptFail</c>
		///   events between receiving the <c>OnAcmConnectionStart</c> event and the
		///   <c>OnAcmConnectionComplete</c> event. </remarks>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		virtual void DoAcmConnectionAttemptFail(const GUID& IfaceId, 
			const wclWiFiAcmConnectionEventData& Data);
		/// <summary> Fires the <c>OnAcmConnectionComplete</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <remarks> The connection succeeded if the <c>Reason</c> field of the
		///   <c>Data</c> parameter is <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise,
		///   the connection has failed. </remarks>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		virtual void DoAcmConnectionComplete(const GUID& IfaceId, 
			const wclWiFiAcmConnectionEventData& Data);
		/// <summary> Fires the <c>OnAcmConnectionStart</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		virtual void DoAcmConnectionStart(const GUID& IfaceId, 
			const wclWiFiAcmConnectionEventData& Data);
		/// <summary> Fires the <c>OnAcmDisconnected</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		virtual void DoAcmDisconnected(const GUID& IfaceId, 
			const wclWiFiAcmConnectionEventData& Data);
		/// <summary> Fires the <c>OnAcmDisconnecting</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		virtual void DoAcmDisconnecting(const GUID& IfaceId, 
			const wclWiFiAcmConnectionEventData& Data);
		/// <summary> Fires the <c>OnAcmFilterListChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmFilterListChange(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmInterfaceArrival</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmInterfaceArrival(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmInterfaceRemoval</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmInterfaceRemoval(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmNetworkAvailable</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmNetworkAvailable(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmNetworkNotAvailable</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmNetworkNotAvailable(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmOperationalStateChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmOperationalStateChange(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmPowerSettingChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Setting"> The new power setting of an interface. </param>
		/// <seealso cref="wclWiFiPowerSetting" />
		virtual void DoAcmPowerSettingChange(const GUID& IfaceId, 
			const wclWiFiPowerSetting Setting);
		/// <summary> Fires the <c>OnAcmProfileBlocked</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmProfileBlocked(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmProfileChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmProfileChange(const GUID& IfaceId);
		/// <summary> Fires then <c>OnAcmProfileNameChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldName"> The old profile name. </param>
		/// <param name="NewName"> The new profile name. </param>
		virtual void DoAcmProfileNameChange(const GUID& IfaceId, 
			const tstring& OldName, const tstring& NewName);
		/// <summary> Fires the <c>OnAcmProfilesExhausted</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmProfilesExhausted(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmProfileUnblocked</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmProfileUnblocked(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmScanComplete</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmScanComplete(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmScanFail</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Reason"> The reason the WLAN operation failed. </param>
		virtual void DoAcmScanFail(const GUID& IfaceId, const int Reason);
		/// <summary> Fires the <c>OnAcmScanListRefresh</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoAcmScanListRefresh(const GUID& IfaceId);
		/// <summary> Fires the <c>OnAcmScreenPowerChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="SwitchedOn"> The value of the screen power change. When
		///   this value is <c>True</c>, the screen changed to on. When this value
		///   is <c>False</c>, the screen changed to off. </param>
		virtual void DoAcmScreenPowerChange(const GUID& IfaceId, 
			const bool SwitchedOn);

		/* Hosted Network events dispatchers. */

		/// <summary> Fires the <c>OnHostednetworkPeerStateChange</c>
		///   event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldState"> The previous network state for a data peer on
		///   the wireless Hosted Network. </param>
		/// <param name="NewState"> The current network state for a data peer on the
		///   wireless Hosted Network. </param>
		/// <param name="Reason"> The reason for the network state change for the
		///   data peer. </param>
		/// <seealso cref="wclWiFiHostedNetworkPeerState" />
		virtual void DoHostedNetworkPeerStateChange(const GUID& IfaceId,
			const wclWiFiHostedNetworkPeerState& OldState, 
			const wclWiFiHostedNetworkPeerState& NewState,
			const int Reason);
		/// <summary> Fires the <c>OnHostedNetworkRadioStateChange</c>
		///   event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="SoftwareState"> The software radio state of the wireless
		///   Hosted Network. </param>
		/// <param name="HardwareState"> The hardware radio state of the wireless
		///   Hosted Network. </param>
		/// <seealso cref="wclWiFiRadioState" />
		virtual void DoHostedNetworkRadioStateChange(const GUID& IfaceId, 
			const wclWiFiRadioState SoftwareState, const wclWiFiRadioState HardwareState);
		/// <summary> Fires the <c>OnHostedNetworkStateChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldState"> The previous network state on the wireless
		///   Hosted Network. </param>
		/// <param name="NewState"> The current network state on the wireless
		///   Hosted Network. </param>
		/// <param name="Reason"> The reason for the network state change. </param>
		/// <seealso cref="wclWiFiHostedNetworkState" />
		virtual void DoHostedNetworkStateChange(const GUID& IfaceId, 
			const wclWiFiHostedNetworkState OldState,
			const wclWiFiHostedNetworkState NewState, const int Reason);
		
		/* MSM events dispatcher. */

		/// <summary> Fires the <c>OnMsmAdapterOperationModeChange</c>
		///   event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Mode"> The new operation mode. </param>
		/// <seealso cref="wclWiFiOperationMode" />
		virtual void DoMsmAdapterOperationModeChange(const GUID& IfaceId, 
			const wclWiFiOperationMode Mode);
		
		/// <summary> Fires the <c>OnMsmAdapterRemoval</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmAdapterRemoval(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmAssociated</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmAssociated(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmAssociating</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmAssociating(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the "OnMsmAuthenticating" event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. Refer to
		///   <see cref="wclWiFiMsmConnectionEventData" />. </param>
		virtual void DoMsmAuthenticating(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmConnected</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmConnected(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmDisassociating</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmDisassociating(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmDisconnected</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmDisconnected(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmLinkDegraded</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoMsmLinkDegraded(const GUID& IfaceId);
		/// <summary> Fires the <c>OnMsmLinkImproved</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		virtual void DoMsmLinkImproved(const GUID& IfaceId);
		/// <summary> Fires the <c>OnMsmPeerJoin</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmPeerJoin(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmPeerLeave</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmPeerLeave(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmRadioStateChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> The new radio state. </param>
		/// <seealso cref="wclWiFiPhyRadioState" />
		virtual void DoMsmRadioStateChange(const GUID& IfaceId, 
			const wclWiFiPhyRadioState& State);
		/// <summary> Fires the <c>OnMsmRoamingEnd</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmRoamingEnd(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires the <c>OnMsmRoamingStart</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> The connection-related information. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		virtual void DoMsmRoamingStart(const GUID& IfaceId, 
			const wclWiFiMsmConnectionEventData& Data);
		/// <summary> Fires when <c>OnMsmSignalQualityChange</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Quality"> The new signal quality. </param>
		virtual void DoMsmSignalQualityChange(const GUID& IfaceId, 
			const unsigned long Quality);

		/* OneX events dispatchers. */

		/// <summary> Fires the <c>OnOneXAuthRestarted</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Reason"> The reason that 802.1X authentication was
		///   restarted. </param>
		virtual void DoOneXAuthRestarted(const GUID& IfaceId, const int Reason);
		/// <summary> Fires the <c>OnOneXAuthUpdate</c> event. </summary>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> Contains information on a status change to 802.1X
		///   authentication. </param>
		/// <seealso cref="wclWiFiOneXStatusUpdate" />
		virtual void DoOneXAuthUpdate(const GUID& IfaceId, 
			const wclWiFiOneXStatusUpdate& State);

		/* IP change events dispatchers. */
		
		/// <summary> Fires the <c>OnIpChanged</c> event. </summary>
		/// <param name="IfaceId"> The WLAN interface ID. </param>
		/// <param name="Old"> The old IP settings. </param>
		/// <param name="New"> The new IP settings. </param>
		/// <seealso cref="wclWiFiIpSettings" />
		virtual void DoIpChanged(const GUID& IfaceId, const wclWiFiIpSettings& Old,
			const wclWiFiIpSettings& New);

	public:
		/// <summary> Creates a new <c>CwclWiFiEvents</c> component. </summary>
		CwclWiFiEvents();

		/// <summary> Gets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiEvents"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiEvents"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/* ACM events. */

		/// <summary> The event fires when a state change has occurred for an
		///   ad-hoc network. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> The new ad-hoc network state. </param>
		/// <seealso cref="wclWiFiAdHocNetworkState" />
		wclWiFiAcmAdHocNetworkStateChangeEvent(OnAcmAdHocNetworkStateChange);
		/// <summary> The event fires when auto configuration is disabled on the
		///   auto configuration module (ACM). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmAutoconfDisabled);
		/// <summary> The event fires when auto configuration is enabled on the
		///   auto configuration module (ACM). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmAutoconfEnabled);
		/// <summary> The event fires when background scans are disabled on the
		///   auto configuration module (ACM). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmBackgroundScanDisabled);
		/// <summary> The event fires when background scans are enabled on the
		///   auto configuration module (ACM). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmBackgroundScanEnabled);
		/// <summary> The event fires when the BSS type for an interface
		///   has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="BssType"> The new basic service set (BSS) type. </param>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiAcmBssTypeChangeEvent(OnAcmBssTypeChange);
		/// <summary> The event fires when a connection attempt has
		///   failed. </summary>
		/// <remarks> A connection consists of one or more connection attempts. An
		///   application may receive zero or more <c>OnAcmConnectionAttemptFail</c>
		///   events between receiving the <c>OnAcmConnectionStart</c> event and the
		///   <c>OnAcmConnectionComplete</c> event. </remarks>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		wclWiFiAcmConnectionEvent(OnAcmConnectionAttemptFail);
		/// <summary> The event fires when a connection has completed. </summary>
		/// <remarks> The connection succeeded if the <c>Reason</c> field of the
		///   <c>Data</c> parameter is <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise,
		///   the connection has failed. </remarks>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		wclWiFiAcmConnectionEvent(OnAcmConnectionComplete);
		/// <summary> The event fires when a connection has started to a network
		///   in range. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		wclWiFiAcmConnectionEvent(OnAcmConnectionStart);
		/// <summary> The event fires when the wireless service has disconnected
		///   from a connectable network. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		wclWiFiAcmConnectionEvent(OnAcmDisconnected);
		/// <summary> The event fires when the wireless service is disconnecting
		///   from a connectable network. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiAcmConnectionEventData" />
		wclWiFiAcmConnectionEvent(OnAcmDisconnecting);
		/// <summary> The event fires when a change in the filter list has occurred,
		///   either through group policy or a call to the WiFI
		///   functions. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmFilterListChange);
		/// <summary> The event fires when a wireless LAN interface is been added
		///   to or enabled on the local computer. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmInterfaceArrival);
		/// <summary> The event fires when a wireless LAN interface has been
		///   removed or disabled on the local computer. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmInterfaceRemoval);
		/// <summary> The event fires when the wireless service found a connectable
		///   network after a scan, the interface was in the disconnected state,
		///   and there is no compatible auto-connect profile that the wireless
		///   service can use to connect. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmNetworkAvailable);
		/// <summary> The event fires when the wireless service cannot find any
		///   connectable network after a scan. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmNetworkNotAvailable);
		/// <summary> The event fires when the operational state has
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmOperationalStateChange);
		/// <summary> The event fires when the power setting for an interface
		///   has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Setting"> The new power setting of an interface. </param>
		/// <seealso cref="wclWiFiPowerSetting" />
		wclWiFiAcmPowerSettingChangeEvent(OnAcmPowerSettingChange);
		/// <summary> The event fires when a profile has been blocked. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmProfileBlocked);
		/// <summary> The event fires when a change in a profile or the profile
		///   list has occurred, either through group policy or by calls to Native
		///   Wi-Fi functions. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmProfileChange);
		/// <summary> The event fires when a profile name has changed, either
		///   through group policy or by calls to Native Wi-Fi
		///   functions. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldName"> The old profile name. </param>
		/// <param name="NewName"> The new profile name. </param>
		wclWiFiAcmProfileNameChangeEvent(OnAcmProfileNameChange);
		/// <summary> The event fires when all profiles were exhausted in an
		///   attempt to auto connect. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmProfilesExhausted);
		/// <summary> The event fires when a profile has been unblocked. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmProfileUnblocked);
		/// <summary> The event fires when a scan for networks has
		///   completed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmScanComplete);
		/// <summary> The event fires when a scan for connectable networks
		///   failed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Reason"> The reason the WLAN operation failed. </param>
		wclWiFiAcmScanFailEvent(OnAcmScanFail);
		/// <summary> The event fires when a scan list has been
		///   refreshed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnAcmScanListRefresh);
		/// <summary> The event fires when the screen power has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="SwitchedOn"> The value of the screen power change. When this
		///   value is <c>True</c>, the screen changed to on. When this value is
		///   <c>False</c>, the screen changed to off. </param>
		wclWiFiAcmScreenPowerChangeEvent(OnAcmScreenPowerChange);

		/* Hosted Network events. */

		/// <summary> The event fires when the wireless Hosted Network peer state
		///   has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldState"> The previous network state for a data peer on
		///   the wireless Hosted Network. </param>
		/// <param name="NewState"> The current network state for a data peer on the
		///   wireless Hosted Network. </param>
		/// <param name="Reason"> The reason for the network state change for the data
		///   peer. </param>
		/// <seealso cref="wclWiFiHostedNetworkPeerState" />
		wclWiFiHostedNetworkPeerStateChangeEvent(OnHostedNetworkPeerStateChange);
		/// <summary> The event fires when the wireless Hosted Network radio state
		///   has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="SoftwareState"> The software radio state of the wireless
		///   Hosted Network. </param>
		/// <param name="HardwareState"> The hardware radio state of the wireless
		///   Hosted Network. </param>
		/// <seealso cref="wclWiFiRadioState" />
		wclWiFiHostedNetworkRadioStateChangeEvent(OnHostedNetworkRadioStateChange);
		/// <summary> The event fires when the wireless Hosted Network state has
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="OldState"> The previous network state on the wireless
		///   Hosted Network. </param>
		/// <param name="NewState"> The current network state on the wireless
		///   Hosted Network. </param>
		/// <param name="Reason"> The reason for the network state change. </param>
		/// <seealso cref="wclWiFiHostedNetworkState" />
		wclWiFiHostedNetworkStateChangeEvent(OnHostedNetworkStateChange);
		
		/* MSM events. */

		/// <summary> The event fires when the operation mode of the wireless
		///   device has changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Mode"> The new operation mode. </param>
		/// <seealso cref="wclWiFiOperationMode" />
		wclWiFiMsmAdapterOperationModeChangeEvent(OnMsmAdapterOperationModeChange);
		/// <summary> The event fires when a wireless adapter has been removed from
		///   the local computer. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmAdapterRemoval);
		/// <summary> The event fires when the wireless device has associated
		///   with an access point or a peer station. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmAssociated);
		/// <summary> The event fires when a wireless device is in the process of
		///   associating with an access point or a peer station. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmAssociating);
		/// <summary> The event fires when the wireless device is in the process
		///   of authenticating. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmAuthenticating);
		/// <summary> The event fires when the wireless device is associated with
		///   an access point or a peer station, keys have been exchanged, and
		///   the wireless device is available to send data. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmConnected);
		/// <summary> The event fires when a wireless device is in the process of
		///   disassociating from an access point or a peer station. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmDisassociating);
		/// <summary> The event fires when the wireless device is not associated
		///   with an access point or a peer station. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmDisconnected);
		/// <summary> The event fires when the link was degraded. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnMsmLinkDegraded);
		/// <summary> The event fires when the link was improved. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		wclWiFiEvent(OnMsmLinkImproved);
		/// <summary> The event fires when a peer has joined an ad-hoc
		///   network. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmPeerJoin);
		/// <summary> The event fires when a peer has left an ad-hoc
		///   network. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmPeerLeave);
		/// <summary> The event fires when the radio state for an adapter has
		///   changed. Each physical layer (PHY) has its own radio state. The
		///   radio for an adapter is switched off when the radio state
		///   of every PHY is off. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> The new radio state. </param>
		/// <seealso cref="wclWiFiPhyRadioState" />
		wclWiFiMsmRadioStateChangeEvent(OnMsmRadioStateChange);
		/// <summary> The event fires when the wireless device was connected to
		///   an access point and has completed roaming to another access
		///   point. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmRoamingEnd);
		/// <summary> The event fires when the wireless device is connected to an
		///   access point and has initiated roaming to another access
		///   point. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Data"> Contains information about connection related
		///   event. </param>
		/// <seealso cref="wclWiFiMsmConnectionEventData" />
		wclWiFiMsmConnectionEvent(OnMsmRoamingStart);
		/// <summary> The event fires when a signal quality change for the
		///   currently associated access point or peer station. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Quality"> The new signal quality. </param>
		wclWiFiMsmSignalQualityChangeEvent(OnMsmSignalQualityChange);

		/* OneX events. */

		/// <summary> The event fires when the 802.1X authentication process
		///   was restarted. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="Reason"> The reason that 802.1X authentication was
		///   restarted. </param>
		wclWiFiOneXAuthRestartedEvent(OnOneXAuthRestarted);
		/// <summary> The event fires when the 802.1X authentication status has
		///   been updated. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The interface's ID on which the event
		///   is for. </param>
		/// <param name="State"> Contains information on a status change to 802.1X
		///   authentication. </param>
		/// <seealso cref="wclWiFiOneXStatusUpdate" />
		wclWiFiOneXAuthUpdateEvent(OnOneXAuthUpdate);

		/* IP change events. */

		/// <summary> The event fires when IP settings has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="IfaceId"> The WLAN interface ID. </param>
		/// <param name="Old"> The old IP settings. </param>
		/// <param name="New"> The new IP settings. </param>
		/// <seealso cref="wclWiFiIpSettings" />
		wclWiFiIpChangedEvent(OnIpChanged);
	};

	/// <summary> The record describes the WLAN interface. </summary>
	typedef struct
	{
		/// <summary> The WLAN interface GUID. </summary>
		GUID	Id;
		/// <summary> The WLAN interface description. </summary>
		tstring	Description;
		/// <summary> <c>true</c> if the interface is primary, <c>false</c> if the
		///   interface is secondary. </summary>
		bool	Primary;
	} wclWiFiInterfaceData;
	/// <summary> The WLAN interfaces dynamic array. </summary>
	/// <seealso cref="wclWiFiInterfaceData" />
	typedef std::vector<wclWiFiInterfaceData> wclWiFiInterfaces;

	class CwclWiFiClient;

	/// <summary> The flags that control the type of networks returned in
	///   the list by the <c>EnumAvailableNetworks</c> method of the
	///   <see cref="wclWiFi::CwclWiFiClient" /> component. </summary>
	typedef enum
	{
		/// <summary> Include all ad hoc network profiles in the available network
		///   list, including profiles that are not visible. </summary>
		ffIncludeAllAdhocProfiles,
		/// <summary> Include all hidden network profiles in the available network
		///   list, including profiles that are not visible. </summary>
		ffIncludeAllManualHiddenProfiles
	} wclWiFiAvailableNetworkFilter;

	/// <summary> A set of flags that control the type of networks returned in
	///   the list. </summary>
	/// <seealso cref="wclWiFiAvailableNetworkFilter" />
	typedef std::set<wclWiFiAvailableNetworkFilter> wclWiFiAvailableNetworkFilters;

	/// <summary> Defines a wireless LAN authentication algorithm. </summary>
	typedef enum
	{
		/// <summary> Specifies an IEEE 802.11 Open System authentication
		///   algorithm. </summary>
		auOpen,
		/// <summary> Specifies an 802.11 Shared Key authentication algorithm that
		///   requires the use of a pre-shared Wired Equivalent Privacy (WEP)
		///   key for the 802.11 authentication. </summary>
		auSharedKey,
		/// <summary> <para> Specifies a WiFi Protected Access (WPA) algorithm.
		///   IEEE 802.1X port authentication is performed by the supplicant,
		///   authenticator, and authentication server. Cipher keys are dynamically
		///   derived through the authentication process. </para>
		///   <para> This algorithm is valid only for BSS types of
		///   <c>bssInfrastructure</c>. </para>
		///   <para> When the WPA algorithm is enabled, the 802.11 station will
		///   associate only with an access point whose beacon or probe responses
		///   contain the authentication suite of type 1 (802.1X) within the WPA
		///   information element (IE). </para> </summary>
		/// <seealso cref="wclWiFiBssType" />
		auWpa,
		/// <summary> <para> Specifies a WPA algorithm that uses pre-shared keys
		///   (PSK). IEEE 802.1X port authentication is performed by the supplicant
		///   and authenticator. Cipher keys are dynamically derived through a
		///   pre-shared key that is used on both the supplicant and
		///   authenticator. </para>
		///   <para> This algorithm is valid only for BSS types of
		///   <c>bssInfrastructure</c>. </para>
		///   <para> When the WPA PSK algorithm is enabled, the 802.11 station will
		///   associate only with an access point whose beacon or probe responses
		///   contain the authentication suite of type 2 (pre-shared key) within
		///   the WPA IE. </para> </summary>
		/// <seealso cref="wclWiFiBssType" />
		auWpaPsk,
		/// <summary> This value is not supported. </summary>
		auWpaNone,
		/// <summary> <para> Specifies an 802.11i Robust Security Network
		///   Association (RSNA) algorithm. WPA2 is one such algorithm. IEEE 802.1X
		///   port authentication is performed by the supplicant, authenticator, and
		///   authentication server. Cipher keys are dynamically derived through
		///   the authentication process. </para>
		///   <para> This algorithm is valid only for BSS types of
		///   <c>bssInfrastructure</c>. </para>
		///   <para> When the RSNA algorithm is enabled, the 802.11 station will
		///   associate only with an access point whose beacon or probe responses
		///   contain the authentication suite of type 1 (802.1X) within the
		///   RSN IE. </para> </summary>
		/// <seealso cref="wclWiFiBssType" />
		auRsna,
		/// <summary> <para> Specifies an 802.11i RSNA algorithm that uses PSK.
		///   IEEE 802.1X port authentication is performed by the supplicant and
		///   authenticator. Cipher keys are dynamically derived through a
		///   pre-shared key that is used on both the supplicant and
		///   authenticator. </para>
		///   <para> This algorithm is valid only for BSS types of
		///   <c>bssInfrastructure</c>. </para>
		///   <para> When the RSNA PSK algorithm is enabled, the 802.11 station will
		///   associate only with an access point whose beacon or probe responses
		///   contain the authentication suite of type 2(pre-shared key) within
		///   the RSN IE. </para> </summary>
		/// <seealso cref="wclWiFiBssType" />
		auRsnaPsk,
		/// <summary> Specifies a WPA3-Enterprise 192-bit mode algorithm. </summary>
		auWpa3,
		/// <summary> Specifies a WPA3-Simultaneous Authentication of Equals
		///   (WPA3-SAE) algorithm. </summary>
		auWpa3Sae,
		/// <summary> Specifies an opportunistic wireless encryption (OWE)
		///   algorithm. </summary>
		auOwe,
		/// <summary> Specifies a WPA3-Enterprise algorithm. </summary>
		auWpa3Ent,
		/// <summary> The authentication algorithm is unknown or invalid. </summary>
		auUnknown
	} wclWiFiAuthAlgorithm;

	/// <summary> Defines a cipher algorithm for data encryption and
	///   decryption. </summary>
	typedef enum
	{
		/// <summary> Specifies that no cipher algorithm is enabled or
		///   supported. </summary>
		caNone,
		/// <summary> Specifies a Wired Equivalent Privacy (WEP) algorithm, which
		///   is the RC4-based algorithm that is specified in the 802.11-1999
		///   standard. This enumerator specifies the WEP cipher algorithm with a
		///   40-bit cipher key. </summary>
		caWep40,
		/// <summary> Specifies a Temporal Key Integrity Protocol (TKIP) algorithm,
		///   which is the RC4-based cipher suite that is based on the algorithms
		///   that are defined in the WPA specification and IEEE 802.11i-2004
		///   standard. This cipher also uses the Michael Message Integrity Code
		///   (MIC) algorithm for forgery protection. </summary>
		caTkip,
		/// <summary> Specifies an AES-CCMP algorithm, as specified in the
		///   IEEE 802.11i-2004 standard and RFC 3610. Advanced Encryption
		///   Standard (AES) is the encryption algorithm defined in
		///   FIPS PUB 197. </summary>
		caCcmp,
		/// <summary> Specifies a WEP cipher algorithm with a 104-bit cipher
		///   key. </summary>
		caWep104,
		/// <summary> Specifies a WiFi Protected Access (WPA) Use Group Key cipher
		///   suite. For more information about the Use Group Key cipher suite,
		///   refer to Clause 7.3.2.25.1 of the IEEE 802.11i-2004
		///   standard. </summary>
		caBip,
		/// <summary> Specifies a GCMP cipher algorithm with a 128-bit cipher
		///   key. </summary>
		caGcmp128,
		/// <summary> Specifies a GCMP cipher algorithm with a 256-bit cipher
		///   key. </summary>
		caGcmp256,
		/// <summary> Specifies an AES-CCMP algorithm with a 256-bit cipher
		///   key. </summary>
		caCcmp256,
		/// <summary> Specifies a Broadcast Integrity Protocol Galois Message
		///   Authentication Code (BIP-GMAC) cipher algorithm with a 128-bit cipher
		///   key. </summary>
		caBipGmac128,
		/// <summary> Specifies a Broadcast Integrity Protocol Galois Message
		///   Authentication Code (BIP-GMAC) cipher algorithm with a 256-bit cipher
		///   key. </summary>
		caBipGmac256,
		/// <summary> Specifies a Broadcast Integrity Protocol Cipher-based Message
		///   Authentication Code (BIP-CMAC) cipher algorithm with a 256-bit cipher
		///   key. </summary>
		caBipCmac256,
		/// <summary> Specifies a Robust Security Network (RSN) Use Group Key cipher
		///   suite. For more information about the Use Group Key cipher suite,
		///   refer to Clause 7.3.2.25.1 of the IEEE 802.11i-2004
		///   standard. </summary>
		caUseGroup,
		/// <summary> Specifies a WEP cipher algorithm with a cipher key of any
		///   length. </summary>
		caWep,
		/// <summary> The cipher algorithm is unknown or unsupported. </summary>
		caUnknown
	} wclWiFiCipherAlgorithm;

	/// <summary> Various flags for the available network. </summary>
	typedef enum
	{
		/// <summary> This network is currently connected. </summary>
		nfConnected,
		/// <summary> There is a profile for this network. </summary>
		nfHasProfile
	} wclWiFiAvailableNetworkFlag;

	/// <summary> The available network flags set. </summary>
	/// <seealso cref="wclWiFiAvailableNetworkFlag" />
	typedef std::set<wclWiFiAvailableNetworkFlag> wclWiFiAvailableNetworkFlags;

	/// <summary> The record contains information about an available wireless
	///   network. </summary>
	typedef struct
	{
		/// <summary> Contains the profile name associated with the network. If the
		///   network does not have a profile, this member will be empty. If
		///   multiple profiles are associated with the network, there will be
		///   multiple entries with the same SSID in the visible network list.
		///   Profile names are case-sensitive. </summary>
		tstring ProfileName;
		/// <summary> The SSID of the visible wireless network. </summary>
		tstring Ssid;
		/// <summary> Specifies whether the network is infrastructure or
		///   ad hoc. </summary>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiBssType BssType;
		/// <summary> Indicates the number of BSSIDs in the network. </summary>
		unsigned long NumberOfBssids;
		/// <summary> Indicates whether the network is connectable or not. If set
		///   to <c>True</c>, the network is connectable, otherwise the network
		///   cannot be connected to. </summary>
		bool NetworkConnectable;
		/// <summary> Indicates why a network cannot be connected to. This member
		///   is only valid when <c>NetworkConnectable</c> is
		///   <c>False</c>. </summary>
		int NotConnectableReason;
		/// <summary> Contains a set of <see cref="wclWiFiPhy" /> values that
		///   represent the PHY types supported by the available networks. If the
		///   network supports more than 8 PHYs, this set contains only
		///   the first 8 PHY types. </summary>
		/// <seealso cref="wclWiFiPhys" />
		wclWiFiPhys PhyTypes;
		/// <summary> <para> Specifies if there are more than 8 PHY types
		///   supported. </para>
		///   <para> When this member is set to <c>True</c>, an application must
		///   call <c>EnumBss</c> of the <see cref="CwclWiFiClient" /> component to
		///   get the complete list of PHY types. </para> </summary>
		bool MorePhyTypes;
		/// <summary> A percentage value that represents the signal quality of the
		///   network. This member contains a value between 0 and 100. A value of
		///   0 implies an actual RSSI signal strength of -100 dBm. A value of 100
		///   implies an actual RSSI signal strength of -50 dBm. You can calculate
		///   the RSSI signal strength value for <c>SignalQuality</c> values
		///   between 1 and 99 using linear interpolation. </summary>
		unsigned long SignalQuality;
		/// <summary> Indicates whether security is enabled on the network. A value
		///   of <c>True</c> indicates that security is enabled, otherwise it
		///   is not. </summary>
		bool SecurityEnabled;
		/// <summary> Indicates the default authentication algorithm used to join
		///   this network for the first time. </summary>
		/// <seealso cref="wclWiFiAuthAlgorithm" />
		wclWiFiAuthAlgorithm DefaultAuthAlgorithm;
		/// <summary> Indicates the default cipher algorithm to be used when
		///   joining this network. </summary>
		/// <seealso cref="wclWiFiCipherAlgorithm" />
		wclWiFiCipherAlgorithm DefaultCipherAlgorithm;
		/// <summary> Various flags for the network. </summary>
		/// <seealso cref="wclWiFiAvailableNetworkFlags" />
		wclWiFiAvailableNetworkFlags Flags;
	} wclWiFiAvailableNetwork;
	/// <summary> Contains an array of information about available
	///   networks. </summary>
	/// <seealso cref="wclWiFiAvailableNetwork" />
	typedef std::vector<wclWiFiAvailableNetwork> wclWiFiAvailableNetworks;

	/// <summary> Defines the BSS capability. </summary>
	typedef enum
	{
		/// <summary> <para> An extended service set. A set of one or more
		///   interconnected basic service sets (BSSs) and integrated local area
		///   networks (LANs) that appears as a single BSS to the logical link
		///   control layer at any station associated with one of those
		///   BSSs. </para>
		///   <para> An AP set the ESS subfield to 1 and the IBSS subfield to 0
		///   within transmitted Beacon or Probe Response frames. A peer station
		///   within an IBSS (ad hoc network) sets the ESS subfield to 0 and the
		///   IBSS subfield to 1 in transmitted Beacon or Probe Response
		///   frames. </para> </summary>
		bcEss,
		/// <summary> <para> An independent basic service set. A BSS that forms a
		///   self-contained network, and in which no access to a distribution
		///   system (DS) is available (an ad hoc network). </para>
		///   <para> An AP sets the ESS subfield to 1 and the IBSS subfield to 0
		///   within transmitted Beacon or Probe Response frames. A peer station
		///   within an IBSS (ad hoc network) sets the ESS subfield to 0 and the
		///   IBSS subfield to 1 in transmitted Beacon or Probe Response
		///   frames. </para> </summary>
		bcIbss,
		/// <summary> A value that indicates if the AP or peer station is
		///   pollable. </summary>
		bcCfPollable,
		/// <summary> A value that indicates how the AP or peer station handles
		///   poll requests. </summary>
		bcCfPollRequest,
		/// <summary> <para> A value that indicates if encryption is required for
		///   all data frames. </para>
		///   <para> An AP sets the Privacy subfield to 1 within transmitted Beacon
		///   and Probe Response frames if WEP, WPA, or WPA2 encryption is required
		///   for all data type frames exchanged within the BSS. If WEP, WPA, or
		///   WPA2 encryption is not required, the Privacy subfield
		///   is set to 0. </para>
		///   <para> A peer station within and IBSS sets the Privacy subfield to 1
		///   within transmitted Beacon and Probe Response frames if WEP, WPA, or
		///   WPA2 encryption is required for all data type frames exchanged within
		///   the IBSS. If WEP, WPA, or WPA2 encryption is not required, the
		///   Privacy subfield is set to 0. </para> </summary>
		bcPrivacy
	} wclWiFiBssCap;

	/// <summary> Defines the BSS capabilities. </summary>
	/// <seealso cref="wclWiFiBssCap" />
	typedef std::set<wclWiFiBssCap> wclWiFiBssCaps;

	/// <summary> The type represents a raw bytes array of an information
	///   element. </summary>
	typedef std::vector<unsigned char> wclWiFiIeRawData;

	/// <summary> The record contains information about a basic service
	///   set (BSS). </summary>
	typedef struct
	{
		/// <summary> The SSID of the access point (AP) or peer station associated
		///   with the BSS. </summary>
		tstring Ssid;
		/// <summary> The identifier (ID) of the PHY that the wireless LAN
		///   interface used to detect the BSS network. </summary>
		unsigned long PhyId;
		/// <summary> The media access control (MAC) address of the access point
		///   for infrastructure BSS networks or the peer station for independent
		///   BSS networks (ad hoc networks) that sent the 802.11 Beacon or
		///   Probe Response frame received by the wireless LAN interface while
		///   scanning. </summary>
		tstring Mac;
		/// <summary> The BSS network type. This member can be one of the
		///   following values: <c>bssInfrastructure</c> or
		///   <c>bssIndependent</c>. </summary>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiBssType BssType;
		/// <summary> The PHY type for this network. </summary>
		/// <seealso cref="wclWiFiPhy" />
		wclWiFiPhy PhyType;
		/// <summary> The received signal strength indicator (RSSI) value, in units
		///   of decibels referenced to 1.0 milliwatts (dBm), as detected by the
		///   wireless LAN interface driver for the AP or peer station. </summary>
		int Rssi;
		/// <summary> The link quality reported by the wireless LAN interface
		///   driver. The link quality value ranges from 0 through 100. A value
		///   of 100 specifies the highest link quality. </summary>
		unsigned long LinkQuality;
		/// <summary> <para> A value that specifies whether the AP or peer station
		///   is operating within the regulatory domain as identified by the
		///   country/region. </para>
		///   <para> If the wireless LAN interface driver does not support multiple
		///   regulatory domains, this member is set to <c>True</c>. </para>
		///   <para> If the 802.11 Beacon or Probe Response frame received from the
		///   AP or peer station does not include a Country information
		///   element (IE), this member is set to <c>True</c>. </para>
		///   <para> If the 802.11 Beacon or Probe Response frame received from the
		///   AP or peer station does include a Country IE, this member is set to
		///   <c>False</c> if the value of the Country String subfield does not
		///   equal the input country string. </para> </summary>
		bool InRegDomain;
		/// <summary> <para> The value of the Beacon Interval field from the 802.11
		///   Beacon or Probe Response frame received by the wireless LAN
		///   interface. </para>
		///   <para> The interval is in 1.024 microsecond time units between target
		///   beacon transmission times. This information is retrieved from the
		///   beacon packet sent by an access point in an infrastructure BSS network
		///   or a probe response from an access point or peer station in response
		///   to a wireless LAN client sending a Probe Request. </para>
		///   <para> The IEEE 802.11 standard defines a unit of time as equal
		///   to 1.024 microseconds. This unit was defined so that it could be
		///   easily implemented in hardware. </para> </summary>
		unsigned short BeaconPeriod;
		/// <summary> The value of the Timestamp field from the 802.11 Beacon or
		///   Probe Response frame received by the wireless LAN
		///   interface. </summary>
		unsigned long long Timestamp;
		/// <summary> The host timestamp value that records when wireless LAN
		///   interface received the Beacon or Probe Response frame. This member
		///   is a count of 100-nanosecond intervals since
		///   January 1, 1601. </summary>
		unsigned long long HostTimestamp;
		/// <summary> The value of the Capability Information field from the 802.11
		///   Beacon or Probe Response frame received by the wireless LAN
		///   interface. </summary>
		/// <seealso cref="wclWiFiBssCaps" />
		wclWiFiBssCaps Capability;
		/// <summary> <para> The channel center frequency of the band on which
		///   the 802.11 Beacon or Probe Response frame was received. The value of
		///   ChCenterFrequency is in units of kilohertz (kHz). </para>
		///   <para> This member is only valid for PHY types that are
		///   not frequency-hopping spread spectrum (FHSS). </para> </summary>
		unsigned long ChCenterFrequency;
		/// <summary> <para> An array of supported data transfer rates. </para>
		///   <para> Each supported data transfer rate is stored as a Word. The
		///   first bit of the Word specifies whether the rate is a basic rate. A
		///   basic rate is the data transfer rate that all stations in a basic
		///   service set (BSS) can use to receive frames from the wireless medium.
		///   If the rate is a basic rate, the first bit of the Word is
		///   set to 1. </para>
		///   <para> To calculate the data transfer rate in Mbps for an arbitrary
		///   array entry Rates[i], use the following equation: </para>
		///   <para> <c>rate_in_mbps =
		///   (Rates[i] and $7FFF) * 0.5</c> </para> </summary>
		/// <remarks> The caller is responsible to release the memory allocated for
		///   the dynamic array. </remarks>
		std::vector<unsigned short> Rates;
		/// <summary> <para> This member contains variable-length information
		///   elements (IEs) bytes array from the 802.11 Beacon or Probe Response
		///   frames. For each BSS, the IEs are from the last Beacon or Probe
		///   Response frame received from that BSS network. If an IE is available
		///   in only one frame, the wireless LAN interface driver merges the IE
		///   with the other IEs from the last received Beacon or Probe Response
		///   frame. </para>
		///   <para> Information elements are defined in the IEEE 802.11
		///   specifications to have a common general format consisting of a
		///   1-byte Element ID field, a 1-byte Length field, and a variable-length
		///   element-specific information field. Each information element is
		///   assigned a unique Element ID value as defined in this IEEE 802.11
		///   standards. The Length field specifies the number of bytes in the
		///   information field. </para> </summary>
		/// <remarks> The caller is responsible to release the memory allocated for
		///   the dynamic array. </remarks>
		/// <seealso cref="wclWiFiIeRawData" />
		wclWiFiIeRawData IeRaw;
	} wclWiFiBss;
	/// <summary> The BSS array. </summary>
	/// <seealso cref="wclWiFiBss" />
	typedef std::vector<wclWiFiBss> wclWiFiBssArray;

	/// <summary> Flags used to specify the connection parameters. </summary>
	typedef enum
	{
		/// <summary> <para> Connect to the destination network even if the
		///   destination is a hidden network. A hidden network does not broadcast
		///   its SSID. Do not use this flag if the destination network is an ad-hoc
		///   network. </para>
		///   <para> If the profile specified by <c>Profile</c> is not an empty
		///   string, then this flag is ignored and the <c>nonBroadcast</c> profile
		///   element determines whether to connect to a hidden
		///   network. </para> </summary>
		cfHiddentNetwork,
		/// <summary> Do not form an ad-hoc network. Only join an ad-hoc network if
		///   the network already exists. Do not use this flag if the destination
		///   network is an infrastructure network. </summary>
		cfAdHocJoinOnly,
		/// <summary> Ignore the privacy bit when connecting to the network.
		///   Ignoring the privacy bit has the effect of ignoring whether packets
		///   are encrypted and ignoring the method of encryption used. Only use
		///   this flag when connecting to an infrastructure network using a
		///   temporary profile. </summary>
		cfIgnorePrivacyBit,
		/// <summary> Exempt EAPOL traffic from encryption and decryption. This flag
		///   is used when an application must send EAPOL traffic over an
		///   infrastructure network that uses Open authentication and WEP
		///   encryption. This flag must not be used to connect to networks that
		///   require 802.1X authentication. This flag is only valid when
		///   <c>Mode</c> is set to <c>cmTemporaryProfile</c>. Avoid using this flag
		///   whenever possible. </summary>
		/// <seealso cref="wclWiFiConnectionMode" />
		cfEapolPassThrough,
		/// <summary> Automatically persist discovery profile on successful
		///   connection completion. This flag is only valid for
		///   <c>cmDiscoverySecure</c> or <c>cmDiscoveryUnsecure</c>. The profile
		///   will be saved as an all user profile, with the name generated from the
		///   SSID. If there is already a profile with the same name, a number will
		///   be appended to the end of the profile name. The profile will be saved
		///   with manual connection mode, unless
		///   <c>cfPersistDiscoveryProfileConnectionModeAuto</c> is also
		///   specified. </summary>
		/// <seealso cref="wclWiFiConnectionMode" />
		cfPersistDiscoveryProfile,
		/// <summary> To be used in conjunction with
		///   <c>cfPersistDiscoveryProfile</c>. The discovery profile will be
		///   persisted with automatic connection mode. </summary>
		cfPersistDiscoveryProfileConnectionModeAuto,
		/// <summary> To be used in conjunction with
		///   <c>cfPersistDiscoveryProfile</c>. The discovery profile will be
		///   persisted and attempt to overwrite an existing profile with the same
		///   name. </summary>
		cfPersistDiscoveryProfileOverwriteExisting
	} wclWiFiConnectFlag;
	/// <summary> Set of connection flags. </summary>
	/// <seealso cref="wclWiFiConnectFlag" />
	typedef std::set<wclWiFiConnectFlag> wclWiFiConnectFlags;

	/// <summary> The type represents a raw bytes array of an information element
	///   to include in Scan probe requests. </summary>
	typedef std::vector<unsigned char> wclWiFiScanIeData;

	/// <summary> The type represents the BSS IDs (MACs) list used in the
	///   Connect() operation. </summary>
	typedef std::vector<tstring> wclWiFiBssList;

	/// <summary> Information Element IDs as described in IEEE Std 802.11-2016,
	///   9.4.2.1, Table 9-77. </summary>
	typedef enum
	{
		/// <summary> SSID element. </summary>
		/// <remarks> The SSID element indicates the identity of an ESS or
		///   IBSS. </remarks>
		eidSsid = 0,
		/// <summary> Supported rates and BSS membership selectors
		///   element. </summary>
		/// <remarks> The supported rates and BSS membership selectors element
		///   specifies up to eight rates in the OperationalRateSet parameter, as
		///   described in the MLME-JOIN.request and MLME-START.request primitives,
		///   and zero or more BSS membership selectors. </remarks>
		eidSuppRates = 1,
		/// <summary> DSSS parameter set element. </summary>
		/// <remarks> The DSSS parameter set element contains information to allow
		///   channel number identification for STAs. </remarks>
		/// <summary> CF parameter set element. </summary>
		/// <remarks> <para>The CF Parameter Set element contains the set of
		///   parameters necessary to support the PCF.</para>
		///   <para><c>The PCF mechanism is obsolete. Consequently, this subclause
		///   might be removed in a later revision of the
		///   standard.</c></para> </remarks>
		eidCfParams = 4,
		/// <summary> TIM element. </summary>
		/// <remarks> The TIM element contains four fields: DTIM Count, DTIM Period,
		///   Bitmap Control, and Partial Virtual Bitmap. </remarks>
		eidTim = 5,
		/// <summary> IBSS parameter set element. </summary>
		/// <remarks> The IBSS parameter set element contains the set of parameters
		///   necessary to support an IBSS. </remarks>
		eidIbssParams = 6,
		/// <summary> Country element. </summary>
		/// <remarks> The country element contains the information required to allow
		///   a STA to identify the regulatory domain in which the STA is located
		///   and to configure its PHY for operation in that regulatory
		///   domain. </remarks>
		eidCountry = 7,
		/// <summary> Request element. </summary>
		/// <remarks> This element is placed in a Probe Request frame or Information
		///   Request frame to request that the responding STA include the requested
		///   information in the Probe Response frame or Information Response frame,
		///   respectively. </remarks>
		eidRequest = 10,
		/// <summary> BSS load element. </summary>
		/// <remarks> The BSS load element contains information on the current STA
		///   population and traffic levels in the BSS. </remarks>
		eidBssLoad = 11,
		/// <summary> EDCA parameter set elemen. </summary>
		/// <remarks> The EDCA Parameter Set element provides information needed by
		///   STAs for proper operation of the QoS facility during the
		///   CP. </remarks>
		eidEdcaParamSet = 12,
		/// <summary> TSPEC element. </summary>
		/// <remarks> The TSPEC element contains the set of parameters that define
		///   the characteristics and QoS expectations of a traffic flow, in the
		///   context of a particular STA, for use by the HC or PCP and STA(s) or a
		///   mesh STA and its peer mesh STAs in support of QoS traffic transfer
		///   using the procedures defined in 11.4 and 11.24.16.3. </remarks>
		eidTspec = 13,
		/// <summary> TCLAS element. </summary>
		/// <remarks> The TCLAS element contains a set of parameters necessary to
		///   identify various kinds of PDU or incoming MSDU (from a higher layer in
		///   all STAs or from the DS in an AP) that belong to a particular TS. The
		///   TCLAS element is also used when the traffic does not belong to a TS,
		///   for example, by the FMS, DMS, and TFS services. If required, the TCLAS
		///   element is provided in ADDTS Request and ADDTS Response frames only
		///   for the downlink or bidirectional links. The TCLAS element is always
		///   included when a PTP TSPEC is transmitted to a peer STA via an AP or
		///   PCP. </remarks>
		eidTclas = 14,
		/// <summary> Schedule element. </summary>
		/// <remarks> The Schedule element is transmitted by the HC to a STA to
		///   announce the schedule that the HC/AP follows for admitted streams
		///   originating from or destined to that STA, or GCR-SP streams destined
		///   to that STA, in the future. The information in this element might be
		///   used by the STA for power management, internal scheduling, or any
		///   other purpose. </remarks>
		eidSchedule = 15,
		/// <summary> Challenge text element. </summary>
		/// <remarks> The Challenge Text element contains the challenge text within
		///   Authentication exchanges. </remarks>
		eidChallenge = 16,
		/// <summary> Power constraint element. </summary>
		/// <remarks> The Power Constraint element contains the information
		///   necessary to allow a STA to determine the local maximum transmit power
		///   in the current channel. </remarks>
		eidPwrConstraint = 32,
		/// <summary> Power capability element. </summary>
		/// <remarks> The Power Capability element specifies the minimum and maximum
		///   transmit powers with which a STA is capable of transmitting in the
		///   current channel. </remarks>
		eidPwrCapability = 33,
		/// <summary> TPC request element. </summary>
		/// <remarks> The TPC Request element contains a request for a STA to report
		///   transmit power and link margin information using a TPC Report
		///   element. </remarks>
		eidTpcRequest = 34,
		/// <summary> TPC report element. </summary>
		/// <remarks> The TPC Report element contains transmit power and link margin
		///   information sent in response to a TPC Request element or a Link
		///   Measurement Request frame. A TPC Report element is included in a
		///   Beacon frame or Probe Response frame without a corresponding
		///   request. </remarks>
		eidTpcReport = 35,
		/// <summary> Supported channels element. </summary>
		/// <remarks> The Supported Channels element contains a list of channel
		///   subbands (from those channels defined in 17.3.8.4.3) in which a STA is
		///   capable of operating. </remarks>
		eidSupportedChannels = 36,
		/// <summary> Channel switch announcement element. </summary>
		/// <remarks> The Channel Switch Announcement element is used by an AP, IBSS
		///   STA, mesh STA, or PCP to advertise when it is changing to a new
		///   channel and the channel number of the new channel. </remarks>
		eidChannelSwitch = 37,
		/// <summary> Measurement request element. </summary>
		/// <remarks> The Measurement Request element contains a request that the
		///   receiving STA undertake the specified measurement action. </remarks>
		eidMeasureRequest = 38,
		/// <summary> Measurement report elemen. </summary>
		/// <remarks> The Measurement Report element contains a measurement
		///   report. </remarks>
		eidMeasureReport = 39,
		/// <summary> Quiet element. </summary>
		/// <remarks> The Quiet element defines an interval during which no
		///   transmission occurs in the current channel. This interval might be
		///   used to assist in making channel measurements without interference
		///   from other STAs in the BSS. </remarks>
		eidQuiet = 40,
		/// <summary> IBSS DFS element. </summary>
		/// <remarks> The IBSS DFS element contains information for DFS operation in
		///   an IBSS. </remarks>
		eidIbssDfs = 41,
		/// <summary> ERP element. </summary>
		/// <remarks> The ERP element contains information on the presence of
		///   Clause 15 or Clause 16 STAs in the BSS that are not capable of Clause
		///   18 (ERP-OFDM) data rates. It also contains the requirement of the ERP
		///   element sender (AP, IBSS STA, or mesh STA) as to the use of protection
		///   mechanisms to optimize BSS performance and as to the use of long or
		///   short Barker preambles. </remarks>
		eidErpInfo = 42,
		/// <summary> TS delay element. </summary>
		/// <remarks> The TS Delay element is used in an ADDTS Response frame
		///   transmitted by an HC and indicates the time after which the ADDTS can
		///   be retried. </remarks>
		eidTsDelay = 43,
		/// <summary> TCLAS processing element. </summary>
		/// <remarks> The TCLAS Processing element is present in ADDTS Request,
		///   ADDTS Response, FMS Request, FMS Response, DMS Request, DMS Response,
		///   TFS Request and SCS Descriptor frames if there are multiple TCLAS
		///   elements associated with the request, response or descriptor. It is
		///   optionally present in the ADDTS Request and ADDTS Response frames if
		///   there are no TCLAS elements. Together with the TCLAS element(s), if
		///   present, it indicates how a PDU or MSDU should be processed by the
		///   classifie. </remarks>
		eidTclasProcessing = 44,
		/// <summary> HT capabilities element. </summary>
		/// <remarks> The HT Capabilities element contains a number of fields that
		///   are used to advertise optional HT capabilities of an HT STA. The HT
		///   Capabilities element is present in Beacon, Association Request,
		///   Association Response, Reassociation Request, Reassociation Response,
		///   Probe Request, Probe Response, Mesh Peering Open, and Mesh Peering
		///   Close frames. </remarks>
		eidHtCap = 45,
		/// <summary> QoS capability element. </summary>
		/// <remarks> The QoS Capability element contains a number of subfields that
		///   are used to advertise optional QoS capabilities at a QoS STA. The QoS
		///   Capability element is present in Beacon frames that do not contain the
		///   EDCA Parameter Set element and in (Re)Association Request
		///   frame. </remarks>
		eidQos = 46,
		/// <summary> RSNE. </summary>
		/// <remarks> The RSNE contains the information required to establish an
		///   RSNA. </remarks>
		eidRns = 48,
		/// <summary> Extended supported rates and BSS membership selectors
		///   element. </summary>
		/// <remarks> The Extended Supported Rates and BSS Membership Selectors
		///   element specifies the rates in the OperationalRateSet parameter, as
		///   described in the MLME-JOIN.request and MLME-START.request primitives,
		///   and zero or more BSS membership selectors, where these are not carried
		///   in the Supported Rates and BSS Membership Selectors
		///   element. </remarks>
		eidExtSuppRates = 50,
		/// <summary> AP channel report element. </summary>
		/// <remarks> The AP Channel Report element contains a list of channels
		///   where a STA is likely to find an AP. </remarks>
		eidApChannelReport = 51,
		/// <summary> Neighbor report element. </summary>
		eidNeightborReport = 52,
		/// <summary> RCPI element. </summary>
		/// <remarks> The RCPI element indicates the received frame power level at
		///   the receiving STA. </remarks>
		eidRcpi = 53,
		/// <summary> Mobility domain element (MDE). </summary>
		/// <remarks> The MDE contains the MDID (Mobility Domain Identifier) field
		///   and the FT Capability and Policy field. The AP uses the MDE to
		///   advertise that it is included in the group of APs that constitute a
		///   mobility domain, to advertise its support for FT capability, and to
		///   advertise its FT policy information. </remarks>
		eidMobilityDomain = 54,
		/// <summary> Fast BSS transition element (FTE). </summary>
		/// <remarks> The FTE includes information needed to perform the FT
		///   authentication sequence during a fast BSS transition in an
		///   RSN. </remarks>
		eidFastBssTransition = 55,
		/// <summary> Timeout interval element (TIE). </summary>
		/// <remarks> The TIE specifies time intervals and timeouts. </remarks>
		eidTimeoutInterval = 56,
		/// <summary> RIC Data element (RDE). </summary>
		/// <remarks> <para>The RIC refers to a collection of elements that are used
		///   to express a resource request and to convey responses to the
		///   corresponding requests.</para>
		///   <para>A RIC is a sequence of one or more Resource Requests, or a
		///   sequence of one or more Resource Responses. Each Resource Request or
		///   Response consists of an RDE, followed by one or more elements that
		///   describe that resource.</para> </remarks>
		eidRicData = 57,
		/// <summary> DSE Registered Location element. </summary>
		/// <remarks> A DSE Registered Location element includes DSE location
		///   configuration information (LCI), which contains latitude, longitude,
		///   and altitude information. </remarks>
		eidDseRegisteredLocation = 58,
		/// <summary> Supported pperating classes element. </summary>
		/// <remarks> The Supported Operating Classes element is used by a STA to
		///   advertise the operating classes that it is capable of operating with
		///   in this country. </remarks>
		eidSupportedOperatingClasses = 59,
		/// <summary> Extended channel switch announcement element. </summary>
		/// <remarks> The Extended Channel Switch Announcement element is used by an
		///   AP, IBSS STA, or mesh STA to advertise when the BSS is changing to a
		///   new channel or a new channel in a new operating class. The
		///   announcement includes both the operating class and the channel number
		///   of the new channel. The element is present only when an extended
		///   channel switch is pending. </remarks>
		eidExtChanSwitchAnn = 60,
		/// <summary> HT Operation element. </summary>
		/// <remarks> The operation of HT STAs in the BSS is controlled by the HT
		///   Operation element. </remarks>
		eidHtOperation = 61,
		/// <summary> Secondary channel offset element. </summary>
		/// <remarks> The Secondary Channel Offset element is used by an AP, IBSS
		///   STA or mesh STA when changing to a new 40 MHz or wider
		///   channel. </remarks>
		eidSecondaryChannelOffset = 62,
		/// <summary> BSS average access delay element. </summary>
		/// <remarks> The BSS Average Access Delay element contains the AP Average
		///   Access Delay, which is a measure of load in the BSS and is available
		///   in both QoS APs and non-QoS APs. </remarks>
		eidBssAverageAccessDelay = 63,
		/// <summary>  Antenna element. </summary>
		/// <remarks> The Antenna element contains the Antenna ID field. </remarks>
		eidAntenna = 64,
		/// <summary> RSNI element. </summary>
		/// <remarks> The RSNI element contains an RSNI value. </remarks>
		eidRsni = 65,
		/// <summary> Measurement pilot transmission element. </summary>
		/// <remarks> The Measurement Pilot Transmission element contains a
		///   Measurement Pilot Transmission field. </remarks>
		eidMeasurementPilotTransmission = 66,
		/// <summary> BSS available admission capacity element. </summary>
		/// <remarks> The BSS Available Admission Capacity element contains a list
		///   of Available Admission Capacity fields at different User Priorities
		///   and Access Categories. </remarks>
		eidBssAvailableAdmCapa = 67,
		/// <summary> BSS AC Access Delay element. </summary>
		/// <remarks> The BSS AC access delay element contains an Access Category
		///   Access Delay field. </remarks>
		eidBssAcAccessDelay = 68,
		/// <summary> Time advertisement element. </summary>
		/// <remarks> The Time Advertisement element specifies fields describing the
		///   source of time corresponding to a time standard, an external clock
		///   (external time source), an estimate of the offset between that time
		///   standard and the TSF timer, and an estimate of the standard deviation
		///   of the error in the offset estimate. This information is used by a
		///   receiving STA to align its own estimate of the time standard based on
		///   that of another STA. </remarks>
		eidTimeAdvertisement = 69,
		/// <summary> RM enabled capabilities element. </summary>
		/// <remarks> The RM Enabled Capabilities element signals support for radio
		///   measurements in a STA. </remarks>
		eidRrmEnabledCapabilities = 70,
		/// <summary> Multiple BSSID element. </summary>
		eidMultipleBssid = 71,
		/// <summary> 20/40 BSS coexistence element. </summary>
		/// <remarks> The 20/40 BSS Coexistence element is used by STAs to exchange
		///   information that affects 20/40 BSS coexistence. </remarks>
		eid2040BssCoexistence = 72,
		/// <summary> 20/40 BSS intolerant channel report element. </summary>
		/// <remarks> The 20/40 BSS Intolerant Channel Report element contains a
		///   list of channels on which a STA has found conditions that disallow the
		///   use of a 20/40 MHz BSS. </remarks>
		eid2040BssIntolerant = 73,
		/// <summary> Overlapping BSS scan parameters element. </summary>
		/// <remarks> The Overlapping BSS Scan Parameters element is used by an AP
		///   to indicate the values to be used by BSS members when performing OBSS
		///   scan operations. </remarks>
		eidOverlappingBssScanParams = 74,
		/// <summary> RIC Descriptor element. </summary>
		/// <remarks> The RIC Descriptor element is used with an RDE during a fast
		///   BSS transition to negotiate resources that are not otherwise described
		///   by elements. </remarks>
		eidRicDescriptor = 75,
		/// <summary> Management MIC element. </summary>
		/// <remarks> The Management MIC element (MME) provides message integrity
		///   and protects group addressed robust Management frames from forgery and
		///   replay. </remarks>
		eidMmie = 76,
		/// <summary> Event request element. </summary>
		/// <remarks> The Event Request element contains a request to the receiving
		///   STA to perform the specified event action. </remarks>
		eidEventRequest = 78,
		/// <summary> Event report element. </summary>
		/// <remarks> The Event Report element is used by a STA to report an
		///   event. </remarks>
		eidEventReport = 79,
		/// <summary> Diagnostic request element. </summary>
		/// <remarks> The Diagnostic Request element contains a request that the
		///   receiving STA undertake the specified diagnostic action. </remarks>
		eidDiagnosticRequest = 80,
		/// <summary> Diagnostic report element. </summary>
		/// <remarks> The Diagnostic Report element contains a Diagnostic
		///   report. </remarks>
		eidDiagnosticReport = 81,
		/// <summary> Location parameters element. </summary>
		/// <remarks> The Location Parameters element is used for location
		///   service. </remarks>
		eidLocationParameters = 82,
		/// <summary> Nontransmitted BSSID capability element. </summary>
		/// <remarks> When transmitted by a DMG STA, the Nontransmitted BSSID
		///   Capability element includes the DMG BSS Control and the Nontransmitted
		///   BSSID DMG Capabilities Element fields. These fields are not present if
		///   this element is transmitted by non-DMG STAs. </remarks>
		eidNontransmittedBssidCapa = 83,
		/// <summary> SSID List element. </summary>
		/// <remarks> The SSID List field is a list of SSID elements for which the
		///   STA is requesting information. </remarks>
		eidSsidList = 84,
		/// <summary> Multiple BSSID-Index element. </summary>
		eidMultipleBssidIndex = 85,
		/// <summary> FMS descriptor element. </summary>
		/// <remarks> The FMS Descriptor element defines information about group
		///   addressed BUs buffered at the AP. It is present in the Beacon frames
		///   when dot11FMSActivated is true. </remarks>
		eidFmsDescriptor = 86,
		/// <summary> FMS request element. </summary>
		/// <remarks> The FMS Request element defines information about the group
		///   addressed frames being requested by the non-AP STA. </remarks>
		eidFmsRequest = 87,
		/// <summary> FMS response element. </summary>
		/// <remarks> The FMS Response element provides information about the
		///   delivery of group addressed frames. </remarks>
		eidFmsResponse = 88,
		/// <summary> QoS traffic capability element. </summary>
		/// <remarks> The QoS Traffic Capability element provides information about
		///   types of traffic generated by a non-AP QoS STA and is used by a QoS AP
		///   to indicate the access categories of associated non-AP QoS
		///   STAs. </remarks>
		eidQosTrafficCapability = 89,
		/// <summary> BSS max idle period element. </summary>
		/// <remarks> The BSS Max Idle Period element contains the time period a
		///   non-AP STA can refrain from transmitting frames to the AP before the
		///   AP disassociates the STA due to inactivity. </remarks>
		eidBssMaxIdlePeriod = 90,
		/// <summary> TFS request element. </summary>
		/// <remarks> The TFS Request element defines information about the traffic
		///   filters that are enabled at the AP for the requesting non-AP
		///   STA. </remarks>
		eidTfsReq = 91,
		/// <summary> TFS response element. </summary>
		/// <remarks> The TFS Response element defines information about the status
		///   of the requested filtering parameters. </remarks>
		eidTfsResp = 92,
		/// <summary> WNM sleep mode element. </summary>
		/// <remarks> The WNM Sleep Mode element is used to enter and exit the WNM
		///   sleep mode. </remarks>
		eidWnmSleep = 93,
		/// <summary> TIM broadcast request element. </summary>
		/// <remarks> The TIM Broadcast Request element contains information about
		///   the periodic TIM broadcast being requested by the non-AP
		///   STA. </remarks>
		eidTimBroadcastRequest = 94,
		/// <summary> TIM broadcast response element. </summary>
		/// <remarks> The TIM Broadcast Response element contains information about
		///   the periodic TIM broadcast by the AP. </remarks>
		eidTimBroadcastResponse = 95,
		/// <summary> Collocated interference report element. </summary>
		/// <remarks> The Collocated Interference Report element contains some
		///   characteristics of the reported collocated interference. </remarks>
		eidCollocatedInterferenceReport = 96,
		/// <summary> Channel usage element. </summary>
		/// <remarks> The Channel Usage element defines the channel usage
		///   information for BSSs that are not infrastructure BSSs or an off
		///   channel TDLS direct link. </remarks>
		eidChannelUsage = 97,
		/// <summary> Time zone element. </summary>
		/// <remarks> The Time Zone element contains the local time zone of the
		///   AP. </remarks>
		eidTimeZone = 98,
		/// <summary> DMS request element. </summary>
		/// <remarks> The DMS Request element defines information about the group
		///   addressed frames to be transmitted as individual addressed
		///   frames. </remarks>
		eidDmsRequest = 99,
		/// <summary> DMS response element. </summary>
		/// <remarks> The DMS Response element provides the status information about
		///   the requested group addressed frames. </remarks>
		eidDmsResponse = 100,
		/// <summary> Link identifier element. </summary>
		/// <remarks> The Link Identifier element contains information that
		///   identifies a TDLS direct link. </remarks>
		eidLinkId = 101,
		/// <summary> Wakeup schedule element. </summary>
		/// <remarks> The Wakeup Schedule element contains information regarding the
		///   periodic wakeup schedule for TDLS peer PSM. </remarks>
		eidWakeupSchedule = 102,
		/// <summary> Channel switch timing element. </summary>
		/// <remarks> The Channel Switch Timing element contains information
		///   regarding the channel switch timing. </remarks>
		eidChannelSwitchTiming = 104,
		/// <summary> PTI control element. </summary>
		/// <remarks> The PTI Control element contains information regarding the
		///   traffic buffered at the TPU buffer STA for the TPU sleep STA at the
		///   time a TDLS Peer Traffic Indication frame is transmitted by the TPU
		///   buffer STA. The element is optionally included in the TDLS Peer
		///   Traffic Indication frame. </remarks>
		eidPtiControl = 105,
		/// <summary> TPU buffer status element. </summary>
		/// <remarks> The TPU Buffer Status element contains information regarding
		///   the traffic buffered at the TPU buffer STA for the TPU sleep STA at
		///   the time a TDLS Peer Traffic Indication frame is transmitted by the
		///   TPU buffer STA. The element is included in the TDLS Peer Traffic
		///   Indication frame. </remarks>
		eidTpuBufferStatus = 106,
		/// <summary> Interworking element. </summary>
		/// <remarks> The Interworking element contains information about the
		///   interworking service capabilities of a STA. </remarks>
		eidInterworking = 107,
		/// <summary> Advertisement protocol element. </summary>
		/// <remarks> The Advertisement Protocol element contains information that
		///   identifies a particular advertisement protocol and its corresponding
		///   Advertisement Control. </remarks>
		eidAdvProto = 108,
		/// <summary> Expedited bandwidth request element. </summary>
		/// <remarks> The Expedited Bandwidth Request element is transmitted from a
		///   non-AP STA to an AP in an ADDTS Request frame containing a TSPEC
		///   element and provides usage information for the bandwidth
		///   request. </remarks>
		eidExpeditedBandwidthReq = 109,
		/// <summary> QoS map element. </summary>
		/// <remarks> The QoS Map element is transmitted from an AP to a non-AP STA
		///   in a (Re)Association Response frame or a QoS Map Configure frame and
		///   provides the mapping of higher layer quality-of-service constructs to
		///   User Priorities defined by transmission of Data frames in this
		///   standard. This element maps the higher layer priority from the DSCP
		///   field used with the Internet Protocol to User Priority as defined by
		///   this standard. </remarks>
		eidQosMapSet = 110,
		/// <summary> Roaming consortium element. </summary>
		/// <remarks> The Roaming Consortium element contains information
		///   identifying the roaming consortium and/or SSP whose security
		///   credentials can be used to authenticate with the AP transmitting this
		///   element. </remarks>
		eidRoamingConsortium = 111,
		/// <summary> Emergency alert identifier element. </summary>
		/// <remarks> The Emergency Alert Identifier element provides a hash to
		///   identify instances of the active EAS messages that are currently
		///   available from the network. The hash allows the non-AP STA to assess
		///   whether an EAS message advertised by an AP has been previously
		///   received and therefore whether it is necessary to download from the
		///   network. </remarks>
		eidEmergencyAlertId = 112,
		/// <summary> Mesh configuration element. </summary>
		/// <remarks> The Mesh Configuration element is used to advertise mesh
		///   services. It is contained in Beacon frames and Probe Response frames
		///   transmitted by mesh STAs and is also contained in Mesh Peering Open
		///   and Mesh Peering Confirm frames. </remarks>
		eidMeshConfig = 113,
		/// <summary> Mesh ID element. </summary>
		/// <remarks> The Mesh ID element is used to advertise the identification of
		///   an MBSS. The Mesh ID element is transmitted in Mesh Peering Open
		///   frames, Mesh Peering Confirm frames, Mesh Peering Close frames, Beacon
		///   frames, and Probe Request and Response frames. </remarks>
		eidMeshId = 114,
		/// <summary> Mesh link metric report element. </summary>
		/// <remarks> The Mesh Link Metric Report element is transmitted by a mesh
		///   STA to a neighbor peer mesh STA to indicate the quality of the link
		///   between the transmitting mesh STA and the neighbor peer mesh
		///   STA. </remarks>
		eidMeshLinkMetricReport = 115,
		/// <summary> Congestion notification element. </summary>
		/// <remarks> The Congestion Notification element is used to indicate the
		///   congestion status of the mesh STA per mesh destination and AC, and the
		///   duration for which the STA expects the congestion to last. The
		///   Congestion Notification element is included in Congestion Control
		///   Notification frames. </remarks>
		eidCongestionNotification = 116,
		/// <summary> Mesh peering management element. </summary>
		/// <remarks> The Mesh Peering Management element is used to manage a mesh
		///   peering with a neighbor mesh STA. </remarks>
		eidPeerMgmt = 117,
		/// <summary> Mesh channel switch parameters element. </summary>
		/// <remarks> The Mesh Channel Switch Parameters element is used together
		///   with Channel Switch Announcement element and Extended Channel Switch
		///   Announcement element by a mesh STA to advertise to other mesh STAs
		///   when it is changing to a new operating channel and/or operating
		///   class. </remarks>
		eidMeshChannelSwitchParameters = 118,
		/// <summary> Mesh awake window element. </summary>
		/// <remarks> The Mesh Awake Window element is present in DTIM Beacon frames
		///   and is optionally present in Beacon and Probe Response
		///   frame. </remarks>
		eidMeshAwakeWindow = 119,
		/// <summary> Beacon timing element. </summary>
		/// <remarks> The Beacon Timing element is used to advertise the beacon
		///   timing information of neighbor STAs (mesh STAs, IBSS APs, or IBSS
		///   STAs). </remarks>
		eidBeaconTiming = 120,
		/// <summary> MCCAOP setup request element. </summary>
		/// <remarks> The MCCAOP Setup Request element is used to make an MCCAOP
		///   reservation. This element is transmitted in individually addressed
		///   MCCA Setup Request frames or in group addressed MCCA Setup Request
		///   frames. The mesh STA transmitting the MCCA Setup Request element is
		///   the MCCAOP owner of the MCCAOPs that will be scheduled with this
		///   reservation setup request. The receivers of the MCCAOP Setup Request
		///   frame are the MCCAOP responders. </remarks>
		eidMccaopSetupRequest = 121,
		/// <summary> MCCAOP setup reply element. </summary>
		/// <remarks> The MCCAOP Setup Reply element is used to reply to an MCCAOP
		///   Setup Request. This element is transmitted in individually addressed
		///   MCCA Setup Reply frames. The mesh STA transmitting the MCCA Setup
		///   Reply element is the MCCAOP responder of the MCCAOPs scheduled in this
		///   reservation setup. The receiver of the MCCAOP Setup Reply is the
		///   MCCAOP owner. </remarks>
		eidMccaopSetupReplay = 122,
		/// <summary> MCCAOP advertisement element. </summary>
		/// <remarks> The MCCAOP Advertisement element is used by a mesh STA to
		///   advertise MCCAOP reservations to its neighbors. This element is
		///   transmitted in MCCA Advertisement frames and optionally present in
		///   Beacon frames. </remarks>
		eidMccaopAdvertisement = 123,
		/// <summary> MCCAOP teardown element. </summary>
		/// <remarks> The MCCAOP Teardown element is used to announce the teardown
		///   of an MCCAOP reservation. The MCCAOP Teardown element is transmitted
		///   in individually addressed MCCA Teardown frames or in group addressed
		///   MCCA Teardown frames. </remarks>
		eidMccaopTeardown = 124,
		/// <summary> GANN element. </summary>
		/// <remarks> The GANN (gate announcement) element is used for announcing
		///   the presence of a mesh gate in the MBSS. The GANN element is
		///   transmitted in a Gate Announcement frame. </remarks>
		eidGann = 125,
		/// <summary> RANN element. </summary>
		/// <remarks> The RANN (root announcement) element is used for announcing
		///   the presence of a mesh STA configured as root mesh STA with
		///   dot11MeshHWMProotMode set to rann (4). RANN elements are sent out
		///   periodically by such a root mesh STA. The RANN element is transmitted
		///   in an HWMP Mesh Path Selection frame. </remarks>
		eidRann = 126,
		/// <summary> Extended capabilities element. </summary>
		/// <remarks> The Extended Capabilities element carries information about
		///   the capabilities of a STA that augment the capabilities specified in
		///   the Capability Information field. </remarks>
		eidExtCapab = 127,
		/// <summary> PREQ element. </summary>
		/// <remarks> The PREQ (path request) element is used for discovering a path
		///   to one or more target mesh STAs, maintaining a path (optional),
		///   building a proactive (reverse) path selection tree to the root mesh
		///   STA, and confirming a path to a target mesh STA (optional). The PREQ
		///   element is transmitted in an HWMP Mesh Path Selection
		///   frame. </remarks>
		eidPreq = 130,
		/// <summary> PREP element. </summary>
		/// <remarks> The PREP (path reply) element is used to establish a forward
		///   path to a target and to confirm that a target is reachable. The PREP
		///   element is issued in response to a PREQ element. The PREP element is
		///   transmitted in an HWMP Mesh Path Selection frame. </remarks>
		eidPrep = 131,
		/// <summary> PERR element. </summary>
		/// <remarks> The PERR (path error) element is used for announcing an
		///   unreachable destination. The PERR element is transmitted in an HWMP
		///   Mesh Path Selection frame. </remarks>
		eidPerr = 132,
		/// <summary> PXU element. </summary>
		/// <remarks> The PXU (proxy update) element is used to inform the
		///   destination mesh STA of the proxy information at the originator mesh
		///   STA. The PXU element is transmitted in a Proxy Update
		///   frame. </remarks>
		eidPxu = 137,
		/// <summary> PXUC element. </summary>
		/// <remarks> The PXUC (proxy update confirmation) element is used to
		///   confirm the previously received PXU. The PXUC element is transmitted
		///   in a Proxy Update Confirmation frame. </remarks>
		eidPxuc = 138,
		/// <summary> Authenticated mesh peering exchange element. </summary>
		/// <remarks> The Authenticated Mesh Peering Exchange element includes
		///   information needed to perform the authentication sequence during an
		///   authenticated mesh peering exchang. </remarks>
		eidAmpe = 139,
		/// <summary> MIC element. </summary>
		/// <remarks> The MIC element provides message integrity to mesh peering
		///   Management frames. </remarks>
		eidMic = 140,
		/// <summary> Destination URI element. </summary>
		/// <remarks> The Destination URI element contains URI and ESS Detection
		///   Interval values from the requesting STA that the responding STA can be
		///   used to deliver Event or Diagnostic Report frames. </remarks>
		eidDestinationUri = 141,
		/// <summary> U-APSD coexistence element. </summary>
		/// <remarks> The U-APSD coexistence provides the duration of requested
		///   transmission during a U-APSD service period. </remarks>
		eidUApsdCoex = 142,
		/// <summary> DMG wakeup schedule element. </summary>
		/// <remarks> The DMG Wakeup Schedule element is used to communicate the
		///   wakeup schedule (WS) of DMG STAs. </remarks>
		eidDmgWakeupSchedule = 143,
		/// <summary> Extended Schedule element. </summary>
		eidExtendedSchedule = 144,
		/// <summary> STA availability element. </summary>
		/// <remarks> The STA Availability element is used by a non-AP and non-PCP
		///   STA to inform an AP or PCP about the STA availability during the
		///   subsequent CBAPs and to indicate participation in the dynamic
		///   allocation of service periods. The AP or PCP uses the STA Availability
		///   element to inform the non-AP and non-PCP STAs of other STAs
		///   availability during subsequent CBAPs and participation of other STAs
		///   in the Dynamic allocation of service periods. </remarks>
		eidStaAvailability = 145,
		/// <summary> DMG TSPEC element. </summary>
		/// <remarks> The DMG TSPEC element is present in the ADDTS Request frame
		///   sent by a non-AP and non-PCP DMG STA and contains the set of
		///   parameters needed to create or modify an airtime allocation. The DMG
		///   TSPEC element is also present in the ADDTS Response frame sent by a
		///   DMG AP or PCP and reflects the parameters, possibly modified, by which
		///   the allocation was create. </remarks>
		eidDmgTspec = 146,
		/// <summary> Next DMG ATI element. </summary>
		/// <remarks> The Next DMG ATI element indicates the earliest start time for
		///   the next ATI in a subsequent beacon interval. </remarks>
		eidNextDmgAti = 147,
		/// <summary> DMG capabilities element. </summary>
		/// <remarks> The DMG Capabilities element contains a STA identifier and
		///   several fields that are used to advertise the support of optional DMG
		///   capabilities of a DMG STA. The element is present in Association
		///   Request, Association Response, Reassociation Request, Reassociation
		///   Response, Probe Request and Probe Response frames and can be present
		///   in DMG Beacon, Information Request, and Information Response
		///   frames. </remarks>
		eidDmgCapabilities = 148,
		/// <summary> DMG operation element. </summary>
		/// <remarks> The operational parameters of a BSS provided by the AP or PCP
		///   are determined by the DMG Operation element. </remarks>
		eidDmgOperation = 151,
		/// <summary> DMG BSS parameter change element. </summary>
		eidDmgBssParameterChange = 152,
		/// <summary> DMG beam refinement element. </summary>
		eidDmgBeamRefinement = 153,
		/// <summary> Channel measurement feedback element. </summary>
		/// <remarks> The Channel Measurement Feedback element is used to carry the
		///   channel measurement feedback data that the STA has measured on the
		///   TRN-T fields of the BRP packet that contained the Channel Measurement
		///   request, to provide a list of sectors identified during a sector
		///   sweep, or during beam combination. The format and size of the Channel
		///   Measurement Feedback element are defined by the parameter values
		///   specified in the accompanying DMG Beam Refinement element. </remarks>
		eidChannelMeasurementFeedback = 154,
		/// <summary> Awake window element. </summary>
		eidAwakeWindow = 157,
		/// <summary> Multi-band element. </summary>
		/// <remarks> The Multi-band element indicates that the STA transmitting
		///   this element (the transmitting STA) is within a multi-band device
		///   capable of operating in a frequency band or operating class or channel
		///   other than the one in which this element is transmitted and that the
		///   transmitting STA is able to accomplish a session transfer from the
		///   current channel to a channel using another STA in the same device, in
		///   the other or same band. </remarks>
		eidMultiBand = 158,
		/// <summary> ADDBA Extension element. </summary>
		eidAddbaExtension = 159,
		/// <summary> Next PCP list element. </summary>
		/// <remarks> The Next PCP List element contains one or more AID of NextPCP
		///   <c>i</c> fields. </remarks>
		eidNextPcpList = 160,
		/// <summary> PCP handover element. </summary>
		/// <remarks> The PCP Handover element is used to indicate which STA becomes
		///   the new PCP following an explicit or implicit handover
		///   procedure. </remarks>
		eidPcpHandover = 161,
		/// <summary> DMG link margin element. </summary>
		/// <remarks> The DMG Link Margin element is included in a Link Measurement
		///   Report frame. </remarks>
		eidDmgLinkMargin = 162,
		/// <summary> Switching stream element. </summary>
		/// <remarks> The Switching Stream element indicates the streams that the
		///   transmitting STA requests to be switched to a new frequency band or
		///   operating class or channel. </remarks>
		eidSwitchingStream = 163,
		/// <summary> Session transition element. </summary>
		eidSessionTransition = 164,
		/// <summary> Dynamic tone pairing (DTP) report element. </summary>
		/// <remarks> The DTP Report element is included in the DTP Response
		///   frame. </remarks>
		eidDynamicTonePairingReport = 165,
		/// <summary> Cluster report element. </summary>
		/// <remarks> The Cluster Report element is included Action frames, such as
		///   Announce and Information Response frames, transmitted to the AP or PCP
		///   of the BSS. Because the Length field supports only 255 octets of
		///   information in an element, the STA can split the content of the
		///   Extended Schedule Element field in different Cluster Report
		///   elements. </remarks>
		eidClusterReport = 166,
		/// <summary> Relay capabilities element. </summary>
		/// <remarks> A STA that intends to participate in relay operation
		///   advertises its capabilities through the Relay Capabilities
		///   element. </remarks>
		eidRelayCapabilities = 167,
		/// <summary> Relay transfer parameter set element. </summary>
		/// <remarks> A source REDS that intends to transfer frames via an RDS
		///   advertises the parameters for the relay operation with the
		///   transmission of a Relay Transfer Parameter Set element. </remarks>
		eidRelayTransferParamSet = 168,
		/// <summary> BeamLink maintenance element. </summary>
		/// <remarks> The BeamLink Maintenance element is included in Action frames,
		///   such as Probe, Announce and the Information Request and Response
		///   frames, transmitted between a non-AP and non-PCP DMG STA and a DMG AP
		///   or PCP. The element is included in the Probe and Information Request
		///   and Response frames transmitted between non-AP and non-PCP DMG
		///   STAs. </remarks>
		eidBeamLinkMaintenance = 169,
		/// <summary> Multiple MAC sublayers (MMS) element. </summary>
		/// <remarks> The MMS element is included in Action frames, such as Probe
		///   Request, Association Request, Information Request, Announce, and
		///   Information Response frames, transmitted to the peer STA and the AP or
		///   PCP of the BSS. </remarks>
		eidMultipleMacSublayers = 170,
		/// <summary> U-PID element. </summary>
		/// <remarks> The Upper Layer Protocol Identification (U-PID)
		///   element. </remarks>
		eidUPid = 171,
		/// <summary> DMG link adaptation acknowledgment element. </summary>
		/// <remarks>  The DMG Link Adaptation Acknowledgment element is carried in
		///   the Optional Subelements field of the Link Measurement Report
		///   frame. </remarks>
		eidDmgLinkAdaptationAck = 172,
		/// <summary> MCCAOP advertisement overview element. </summary>
		/// <remarks> The MCCAOP Advertisement Overview element is used by a mesh
		///   STA to advertise its MCCA Information and information about its MCCAOP
		///   Advertisement elements, representing its MCCAOP advertisement set,
		///   to its neighbors. This element is transmitted in MCCA Advertisement
		///   frames and optionally present in Beacon frames. </remarks>
		eidMccaopAdvertisementOverview = 174,
		/// <summary> Quiet period request element. </summary>
		/// <remarks> The Quiet Period Request element defines a periodic sequence
		///   of quiet intervals that the requester AP requests the responder AP to
		///   schedule. </remarks>
		eidQuietPeriodRequest = 175,
		/// <summary> Quiet period response element. </summary>
		/// <remarks> The Quiet Period Response element defines the feedback
		///   information from the AP that received the Quiet Period Request
		///   element. </remarks>
		eidQuietPeriodResponse = 177,
		/// <summary>  Quality-of-Service management frame policy
		///   element. </summary>
		/// <remarks> The Quality-of-Service Management Frame (QMF) Policy element
		///   defines a QMF access category mapping QACM) of Management frames and
		///   is used to advertise and exchange QMF policy between STAs. </remarks>
		eidQmfPolicy = 181,
		/// <summary> ECAPC policy element. </summary>
		eidEcapcPolicy = 182,
		/// <summary> Cluster time offset element. </summary>
		eidClusterTimeOffset = 183,
		/// <summary> Intra-access category priority element. </summary>
		/// <remarks> The Intra-Access Category Priority element provides
		///   information from a non-AP STA to an AP on the relative priorities of
		///   streams within an AC. This element is optionally present in ADDTS
		///   Request, QoS Map Configure, or SCS Request frames. </remarks>
		eidIntraAccessCategoryPriority = 184,
		/// <summary> SCS descriptor element. </summary>
		/// <remarks> The SCS Descriptor element defines information about the
		///   stream. </remarks>
		eidScsDescriptor = 185,
		/// <summary> QLoad report element. </summary>
		/// <remarks> The QLoad Report element contains the set of parameters
		///   necessary to support OBSS management. </remarks>
		eidQLoadReport = 186,
		/// <summary> HCCA TXOP update count element. </summary>
		/// <remarks> The HCCA TXOP Update Count element is used by an AP to
		///   advertise its change in TXOP schedule. </remarks>
		eidHccaTxopUpdateCount = 187,
		/// <summary> Higher layer stream ID element. </summary>
		/// <remarks> The Higher Layer Stream ID element identifies a stream from a
		///   higher layer protocol. This element is used to bind messages that are
		///   exchanged in order to complete a procedure, e.g., messages exchanged
		///   in an AP-initiated TS setup procedure. </remarks>
		eidHigherLayerStreamId = 188,
		/// <summary> GCR group address element. </summary>
		/// <remarks> The GCR Group Address element defines information about group
		///   addressed frames to be transmitted using the GCR service. </remarks>
		eidGcrGroupAddress = 189,
		/// <summary> Antenna sector ID pattern element. </summary>
		eidAntennaSectorIdPattern = 190,
		/// <summary> VHT capabilities element. </summary>
		/// <remarks> The VHT Capabilities element contains a number of fields that
		///   are used to advertise the VHT capabilities of a VHT STA. </remarks>
		eidVhtCap = 191,
		/// <summary> VHT operation element. </summary>
		/// <remarks> The operation of VHT STAs in the BSS is controlled by the HT
		///   Operation element and the VHT Operation element. </remarks>
		eidVhtOperation = 192,
		/// <summary> Extended BSS load element. </summary>
		/// <remarks> The Extended BSS Load element reported by the AP contains
		///   information on MIMO spatial stream underutilization and bandwidth
		///   utilization. </remarks>
		eidExtendedBssLoad = 193,
		/// <summary> Wide bandwidth channel switch element. </summary>
		/// <remarks> The Wide Bandwidth Channel Switch element is included in
		///   Channel Switch Announcement frames Extended Channel Switch
		///   Announcement frames, and TDLS Channel Switch Request
		///   frames. </remarks>
		eidWideBwChSwitch = 194,
		/// <summary> Transmit power envelope element. </summary>
		/// <remarks> The Transmit Power Envelope element conveys the local maximum
		///   transmit power for various transmission bandwidths. </remarks>
		eidTransmitPowerEnvelop = 195,
		/// <summary> Channel switch wrapper element. </summary>
		/// <remarks> The Channel Switch Wrapper element contains subelements that
		///   indicate characteristics of the BSS after a channel switch. </remarks>
		eidChannelSwitchWrapper = 196,
		/// <summary> AID element. </summary>
		/// <remarks> The AID element includes the AID assigned by an AP during
		///   association that represents the 16-bit ID of a STA. </remarks>
		eidAid = 197,
		/// <summary> Quiet channel element. </summary>
		/// <remarks> The Quiet Channel element is used to indicate that the
		///   secondary 80 MHz channel of a VHT BSS is to be quieted during a quiet
		///   interval, and, in an infrastructure BSS, to indicate if the primary
		///   80 MHz channel of a VHT BSS can be used during the quiet interval. A
		///   quiet interval is established using either a Quiet element or, in an
		///   infrastructure BSS, the Quiet Channel element if its AP Quiet Mode
		///   field is equal to 1. </remarks>
		eidQuietChannel = 198,
		/// <summary> Operating mode notification element. </summary>
		/// <remarks> The Operating Mode Notification element is used to notify STAs
		///   that the transmitting STA is changing one or more of its operating
		///   channel width, the maximum number of spatial streams it can receive,
		///   and its LDPC receive preference. </remarks>
		eidOperatingModeNotification = 199,
		/// <summary> UPSIM element. </summary>
		eidUpsim = 200,
		/// <summary> Reduced neighbor report element. </summary>
		/// <remarks> The Reduced Neighbor Report element contains channel and other
		///   information related to neighbor APs. </remarks>
		eidReducedNeightborReport = 201,
		/// <summary> TVHT operation element. </summary>
		/// <remarks> The operation of TVHT STAs in the BSS is controlled by the
		///   TVHT Operation element. </remarks>
		eidTvhtOperation = 202,
		/// <summary> Device location element. </summary>
		/// <remarks> A Device Location element includes the location configuration
		///   information (LCI), which contains latitude, longitude, and altitude
		///   information. </remarks>
		eidDeviceLocation = 204,
		/// <summary> White space map element. </summary>
		/// <remarks> The White Space Map element includes available radio frequency
		///   information obtained from a GDB. The format of the WSM Information
		///   field is determined by the value of the WSM Type field. </remarks>
		eidWhiteSpaceMap = 205,
		/// <summary> Fine timing measurement parameters element. </summary>
		/// <remarks> The Fine Timing Measurement Parameters element contains a
		///   number of fields that are used to advertise the requested or allocated
		///   FTM configuration from one STA to another. The Fine Timing Measurement
		///   Parameters element is included in the initial Fine Timing Measurement
		///   Request frame and the initial Fine Timing Measurement
		///   frame. </remarks>
		eidFtmParameters = 206,
		/// <summary> Vendor specific element. </summary>
		/// <remarks> The Vendor Specific element is used to carry information not
		///   defined in this standard within a single defined format, so that
		///   reserved element IDs are not usurped for nonstandard purposes and so
		///   that interoperability is more easily achieved in the presence of
		///   nonstandard information. </remarks>
		eidVendorSpecific = 221,
		/// <summary> Extension element. </summary>
		/// <remarks> Use Element ID Extension field. </remarks>
		eidExtension = 255
	} wclWiFiInformationElementId;

	/// <summary> The record contains one information element. </summary>
	typedef struct
	{
		/// <summary> The information element ID. </summary>
		/// <seealso cref="wclWiFiInformationElementId" />
		wclWiFiInformationElementId Id;
		/// <summary> The information element raw data. </summary>
		/// <seealso cref="wclWiFiIeRawData" />
		wclWiFiIeRawData Data;
	} wclWiFiInformationElement;
	/// <summary> The information elements array. </summary>
	/// <seealso cref="wclWiFiInformationElement" />
	typedef std::vector<wclWiFiInformationElement> wclWiFiInformationElements;
	
	/// <summary> The helper class to parse raw Information Elements data
	///   stream. </summary>
	class CwclWiFiInformationElementParser
	{
		DISABLE_COPY(CwclWiFiInformationElementParser);

	public:
		/// <summary> Creates new Information Element parser object. </summary>
		CwclWiFiInformationElementParser();
		/// <summary> Frees the object. </summary>
		virtual ~CwclWiFiInformationElementParser();

		/// <summary> Extracts information elements from WiFi BSS data. </summary>
		/// <param name="Bss"> The WiFi BSS data. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiBss" />
		/// <seealso cref="wclWiFiInformationElements" />
		int ExtractInformationElements(const wclWiFiBss& Bss,
			wclWiFiInformationElements& Elements) const;
		/// <summary> Extracts information elements from WiFi frame IE raw
		///   data. </summary>
		/// <param name="Raw"> The WiFi frame IE raw bytes array. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiIeRawData" />
		/// <seealso cref="wclWiFiInformationElements" />
		int ExtractInformationElements(const wclWiFiIeRawData& Raw,
			wclWiFiInformationElements& Elements) const;

		/// <summary> Extracts information elements with specified ID from WiFi
		///   BSS data. </summary>
		/// <param name="Id"> The required Information Element ID. </param>
		/// <param name="Bss"> The WiFi BSS data. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> As Windows may combine multiple Information Elements received
		///   in different Beacon advertisement in a single raw data stream there
		///   can be more than one IE with given ID. </remarks>
		/// <seealso cref="wclWiFiInformationElementId" />
		/// <seealso cref="wclWiFiBss" />
		/// <seealso cref="wclWiFiInformationElements" />
		int ExtractInformationElements(const wclWiFiInformationElementId Id,
			const wclWiFiBss& Bss, wclWiFiInformationElements& Elements) const;
		/// <summary> Extracts information elements with specified ID from WiFi
		///   frame IE raw data. </summary>
		/// <param name="Id"> The required Information Element ID. </param>
		/// <param name="Raw"> The WiFi frame IE raw bytes array. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> As Windows may combine multiple Information Elements received
		///   in different Beacon advertisement in a single raw data stream there
		///   can be more than one IE with given ID. </remarks>
		/// <seealso cref="wclWiFiInformationElementId" />
		/// <seealso cref="wclWiFiIeRawData" />
		/// <seealso cref="wclWiFiInformationElements" />
		int ExtractInformationElements(const wclWiFiInformationElementId Id,
			const wclWiFiIeRawData& Raw, wclWiFiInformationElements& Elements) const;
	};

	/// <summary> The <c>CwclWiFiClient</c> component provides access to the
	///   Wireless LAN client functions. </summary>
	/// <remarks> <para> The component is not thread-safe and must be used in one
	///   thread in which it was created. </para>
	///   In order to be notified about the WLAN events an application must use
	///   the <see cref="CwclWiFiEvents" /> component. </remarks>
	/// <seealso cref="CwclCustomWiFiSecurableComponent" />
	class CwclWiFiClient : public CwclCustomWiFiSecurableComponent
	{
		DISABLE_COPY(CwclWiFiClient);
		
	private:
		// Reads the ACM settings.
		int AcmGetProperty(const WlanApi::WLAN_AUTOCONF_OPCODE PropId, void** Data) const;
		// Sets the ACM settings.
		int AcmSetProperty(const WlanApi::WLAN_AUTOCONF_OPCODE PropId, const DWORD DataSize,
			const void* const Data);

	protected:
		/// <summary> Executes additional finalization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() override;
		/// <summary> Executes additional initialization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() override;
		
	public:
		/// <summary> Creates new object. </summary>
		CwclWiFiClient();

		/// <summary> Enumerates all of the wireless LAN interfaces currently
		///   enabled on the local computer. </summary>
		/// <param name="Ifaces"> The dynamic array of the
		///   <see cref="wclWiFiInterfaceData" /> structures which receives the
		///   returned list of wireless LAN interfaces. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   error codes. </para> </returns>
		/// <remarks> An application is responsible for releasing a memory
		///   allocated for the <c>Ifaces</c> dynamic array. </remarks>
		/// <seealso cref="wclWiFiInterfaces" />
		int EnumInterfaces(wclWiFiInterfaces& Ifaces);
		
		/// <summary> Retrieves the list of available networks on a wireless
		///   LAN interface. </summary>
		/// <param name="IfaceId"> The Wireless LAN interface's ID to
		///   be queried. </param>
		/// <param name="Filters"> A set of flags that control the type of networks
		///   returned in the list. </param>
		/// <param name="Networks"> A dynamic array to receive the returned list
		///   of visible networks. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The caller is responsible to dispose the memory allocated for
		///   the dynamic array contains the available network list. </remarks>
		/// <seealso cref="wclWiFiAvailableNetworkFilters" />
		/// <seealso cref="wclWiFiAvailableNetworks" />
		int EnumAvailableNetworks(const GUID& IfaceId, const wclWiFiAvailableNetworkFilters& Filters,
			wclWiFiAvailableNetworks& Networks);
		/// <summary> The method retrieves a list of the basic service set (BSS)
		///   entries of the wireless network or networks on a given wireless
		///   LAN interface. </summary>
		/// <param name="IfaceId"> The Wireless LAN interface's ID to
		///   be queried. </param>
		/// <param name="Ssid"> <para> The SSID of the network from which the BSS
		///   list is requested. This parameter is optional. When set to the empty
		///   string, the returned list contains all of available BSS entries on a
		///   wireless LAN interface. </para>
		///   <para> In addition, the <c>BssType</c> parameter must be set to either
		///   <c>bssInfrastructure</c> or <c>bssindependent</c> and the
		///   <c>SecurityEnabled</c> parameter must be specified. </para> </param>
		/// <param name="BssType"> The BSS type of the network. This parameter is
		///   ignored if the SSID of the network for the BSS list is unspecified
		///   (the <c>Ssid</c> parameter is the empty string). </param>
		/// <param name="SecurityEnabled"> A value that indicates whether security
		///   is enabled on the network. This parameter is only valid when the SSID
		///   of the network for the BSS list is specified (the <c>Ssid</c>
		///   parameter is not an empty string). </param>
		/// <param name="BssList"> A storage to receive the returned list of BSS
		///   entries. The caller is responsible to dispose the allocated
		///   memory. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The caller is responsible to dispose the memory allocated for
		///   the dynamic array contains the BSS list. </remarks>
		/// <seealso cref="wclWiFiBssType" />
		/// <seealso cref="wclWiFiBssArray" />
		int EnumBss(const GUID& IfaceId, const tstring& Ssid, const wclWiFiBssType BssType, 
			const bool SecurityEnabled, wclWiFiBssArray& BssList);
		/// <summary> The Scan function requests a scan for available
		///   networks. </summary>
		/// <param name="IfaceId"> The WLAN interface's ID. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> The Scan function requests that the native 802.11 Wireless
		///   LAN driver scan for available wireless networks. </remarks>
		int Scan(const GUID& IfaceId);
		/// <summary> The Scan function requests a scan for available
		///   networks. </summary>
		/// <param name="IfaceId"> The WLAN interface's ID. </param>
		/// <param name="Ssid"> Specifies the SSID of the network to be scanned.
		///   This parameter is optional. When set to an empty string, the returned
		///   list contains all available networks. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> The Scan function requests that the native 802.11 Wireless
		///   LAN driver scan for available wireless networks. </remarks>
		int Scan(const GUID& IfaceId, const tstring& Ssid);
		/// <summary> The Scan function requests a scan for available
		///   networks. </summary>
		/// <param name="IfaceId"> The WLAN interface's ID. </param>
		/// <param name="Ie"> An information element to include in probe requests.
		///   This may include client provisioning availability information and
		///   802.1X authentication requirements. On Windows XP with SP3 and
		///   Wireless LAN API for Windows XP with SP2 this parameter must be
		///   empty. Maximum length of data is 240 bytes. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> The Scan function requests that the native 802.11 Wireless
		///   LAN driver scan for available wireless networks. </remarks>
		/// <seealso cref="wclWiFiScanIeData" />
		int Scan(const GUID& IfaceId, const wclWiFiScanIeData& Ie);
		/// <summary> The Scan function requests a scan for available
		///   networks. </summary>
		/// <param name="IfaceId"> The WLAN interface's ID. </param>
		/// <param name="Ssid"> Specifies the SSID of the network to be scanned.
		///   This parameter is optional. When set to an empty string, the returned
		///   list contains all available networks. </param>
		/// <param name="Ie"> An information element to include in probe requests.
		///   This may include client provisioning availability information and
		///   802.1X authentication requirements. On Windows XP with SP3 and
		///   Wireless LAN API for Windows XP with SP2 this parameter must be
		///   empty. Maximum length of data is 240 bytes. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> The Scan function requests that the native 802.11 Wireless
		///   LAN driver scan for available wireless networks. </remarks>
		/// <seealso cref="wclWiFiScanIeData" />
		int Scan(const GUID& IfaceId, const tstring& Ssid, const wclWiFiScanIeData& Ie);
		
		/// <summary> The method attempts to connect to a specific
		///   network. </summary>
		/// <param name="IfaceId"> The ID of the interface to use for the
		///   connection. </param>
		/// <param name="Mode"> A value that specifies the mode of
		///   connection. </param>
		/// <param name="Profile"> <para> Specifies the profile being used for the
		///   connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmProfile</c>, then <c>Profile</c>
		///   specifies the name of the profile used for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmTemporaryProfile</c>, then
		///   <c>Profile</c> specifies the XML representation of the profile used
		///   for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmDiscoverySecure</c>
		///   or <c>cmDiscoveryUnsecure</c>, then <c>Profile</c> should
		///   be set to an empty string. </para> </param>
		/// <param name="Ssid"> Specifies the SSID of the network to connect to.
		///   This parameter is optional. When set to and empty string, all SSIDs
		///   in the profile will be tried. This parameter must not be an empty
		///   string if <c>Mode</c> is set to <c>cmDiscoverySecure</c> or
		///   <c>cmDiscoveryUnsecure</c>. </param>
		/// <param name="BssType"> Indicates the BSS type of the network. If a
		///   profile is provided, this BSS type must be the same as the one in the
		///   profile. </param>
		/// <param name="Flags"> The flags used to specify the connection
		///   parameters. </param>
		/// <param name="BssList"> The basic service set (BSS) identifiers (MACs)
		///   desired for the connection. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> <para> The <c>Connect</c> method returns immediately. To be
		///   notified when a connection is established or when no further
		///   connections will be attempted, a client must use the
		///   <see cref="CwclWiFiEvents" /> component. </para> </remarks>
		/// <seealso cref="wclWiFiConnectionMode" />
		/// <seealso cref="wclWiFiBssType" />
		/// <seealso cref="wclWiFiConnectFlags" />
		/// <seealso cref="wclWiFiBssList" />
		int Connect(const GUID& IfaceId, const wclWiFiConnectionMode Mode, 
			const tstring& Profile, const tstring& Ssid, const wclWiFiBssType BssType, 
			const wclWiFiConnectFlags& Flags, const wclWiFiBssList& BssList);
		/// <summary> The method attempts to connect to a specific
		///   network. </summary>
		/// <param name="IfaceId"> The ID of the interface to use for the
		///   connection. </param>
		/// <param name="Mode"> A value that specifies the mode of
		///   connection. </param>
		/// <param name="Profile"> <para> Specifies the profile being used for the
		///   connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmProfile</c>, then <c>Profile</c>
		///   specifies the name of the profile used for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmTemporaryProfile</c>, then
		///   <c>Profile</c> specifies the XML representation of the profile used
		///   for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmDiscoverySecure</c>
		///   or <c>cmDiscoveryUnsecure</c>, then <c>Profile</c> should
		///   be set to an empty string. </para> </param>
		/// <param name="Ssid"> Specifies the SSID of the network to connect to.
		///   This parameter is optional. When set to and empty string, all SSIDs
		///   in the profile will be tried. This parameter must not be an empty
		///   string if <c>Mode</c> is set to <c>cmDiscoverySecure</c> or
		///   <c>cmDiscoveryUnsecure</c>. </param>
		/// <param name="BssType"> Indicates the BSS type of the network. If a
		///   profile is provided, this BSS type must be the same as the one in the
		///   profile. </param>
		/// <param name="Flags"> The flags used to specify the connection
		///   parameters. </param>
		/// <param name="Bss"> The basic service set (BSS) identifier (MAC) desired
		///   for the connection. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> <para> The <c>Connect</c> method returns immediately. To be
		///   notified when a connection is established or when no further
		///   connections will be attempted, a client must use the
		///   <see cref="CwclWiFiEvents" /> component. </para> </remarks>
		/// <seealso cref="wclWiFiConnectionMode" />
		/// <seealso cref="wclWiFiBssType" />
		/// <seealso cref="wclWiFiConnectFlags" />
		int Connect(const GUID& IfaceId, const wclWiFiConnectionMode Mode, 
			const tstring& Profile, const tstring& Ssid, const wclWiFiBssType BssType, 
			const wclWiFiConnectFlags& Flags, const tstring& Bss);
		/// <summary> The method attempts to connect to a specific
		///   network. </summary>
		/// <param name="IfaceId"> The ID of the interface to use for the
		///   connection. </param>
		/// <param name="Mode"> A value that specifies the mode of
		///   connection. </param>
		/// <param name="Profile"> <para> Specifies the profile being used for the
		///   connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmProfile</c>, then <c>Profile</c>
		///   specifies the name of the profile used for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmTemporaryProfile</c>, then
		///   <c>Profile</c> specifies the XML representation of the profile used
		///   for the connection. </para>
		///   <para> If <c>Mode</c> is set to <c>cmDiscoverySecure</c>
		///   or <c>cmDiscoveryUnsecure</c>, then <c>Profile</c> should
		///   be set to an empty string. </para> </param>
		/// <param name="Ssid"> Specifies the SSID of the network to connect to.
		///   This parameter is optional. When set to and empty string, all SSIDs
		///   in the profile will be tried. This parameter must not be an empty
		///   string if <c>Mode</c> is set to <c>cmDiscoverySecure</c> or
		///   <c>cmDiscoveryUnsecure</c>. </param>
		/// <param name="BssType"> Indicates the BSS type of the network. If a
		///   profile is provided, this BSS type must be the same as the one in the
		///   profile. </param>
		/// <param name="Flags"> The flags used to specify the connection
		///   parameters. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> <para> The <c>Connect</c> method returns immediately. To be
		///   notified when a connection is established or when no further
		///   connections will be attempted, a client must use the
		///   <see cref="CwclWiFiEvents" /> component. </para> </remarks>
		/// <seealso cref="wclWiFiConnectionMode" />
		/// <seealso cref="wclWiFiBssType" />
		/// <seealso cref="wclWiFiConnectFlags" />
		int Connect(const GUID& IfaceId, const wclWiFiConnectionMode Mode, 
			const tstring& Profile, const tstring& Ssid, const wclWiFiBssType BssType, 
			const wclWiFiConnectFlags& Flags);
		
		/// <summary> Disconnects an interface from its current network. </summary>
		/// <param name="IfaceId"> The WLAN interface's ID to be
		///   disconnected. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <remarks> Do not call the method before calling <c>Connect</c> unless
		///   you want to change a profile to an on-demand profile. When you call
		///   <c>Connect</c> to establish a network connection, any existing network
		///   connection is dropped automatically. </remarks>
		int Disconnect(const GUID& IfaceId);
		
		/// <summary> Reads the WLAN ACM value indicating whether user and group
		///   policy-denied networks will be included in the available networks
		///   list. </summary>
		/// <param name="Show"> If the method returns <see cref="wclCommon::WCL_E_SUCCESS" />
		///   <c>Show</c> parameter returned as <c>True</c>, then user and group
		///   policy-denied networks will be included in the available networks
		///   list; if the parameter is <c>False</c> on return, user and group
		///   policy-denied networks will not be included in the available
		///   networks list. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		int AcmGetShowDeniedNetworks(bool& Show) const;
		/// <summary> Reads the WLAN ACM Power Setting. </summary>
		/// <param name="Setting"> The ACM the power settings. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		/// <seealso cref="wclWiFiPowerSetting" />
		int AcmGetPowerSetting(wclWiFiPowerSetting& Setting) const;
		/// <summary> Reads the ACM value indicating whether profiles not created
		///   by group policy can be used to connect to an allowed network with a
		///   matching group policy profile. </summary>
		/// <param name="Enabled"> If <c>True</c> only profiles created by group
		///   policy can be used; if <c>False</c>, any profile can be
		///   used. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   return codes. </para> </returns>
		int AcmGetOnlyUseGpProfiles(bool& Enabled) const;
		/// <summary> Reads the ACM value indicating whether the current wireless
		///   interface has shared user credentials allowed. </summary>
		/// <param name="Allow"> If <c>True</c> then the current wireless interface
		///   has shared user credentials allowed; if <c>False</c>, the current
		///   wireless interface does not allow shared user credentials. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmGetAllowExplicitCreds(bool& Allow) const;
		/// <summary> Read the ACM value that indicates the blocked period setting
		///   for the current wireless interface. </summary>
		/// <param name="Period"> The blocked period setting for the current
		///   wireless interface. The blocked period is the amount of time, in
		///   seconds, for which automatic connection to a wireless network will
		///   not be attempted after a previous failure. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmGetBlockPeriod(unsigned long& Period) const;
		/// <summary> Reads the ACM value indicating whether extensibility on a
		///   virtual station is allowed. </summary>
		/// <param name="Allowed"> If <c>True</c> then extensibility on a virtual
		///   station is allowed; if <c>False</c>, extensibility on a virtual
		///   station is not allowed. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> By default, extensibility on a virtual station is allowed.
		///   This value is persisted across restarts. </remarks>
		int AcmGetVirtualStationExtensibility(bool& Allowed) const;
		
		/// <summary> Sets the WLAN ACM value indicating whether user and group
		///   policy-denied networks will be included in the available networks
		///   list. </summary>
		/// <param name="Show"> If <c>True</c>, then user and group policy-denied
		///   networks will be included in the available networks list; if the
		///   parameter is <c>False</c> on return, user and group policy-denied
		///   networks will not be included in the available networks list. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmSetShowDeniedNetworks(const bool Show);
		/// <summary> Sets the ACM value indicating whether the current wireless
		///   interface has shared user credentials allowed. </summary>
		/// <param name="Allow"> If <c>True</c> then the current wireless interface
		///   has shared user credentials allowed; if <c>False</c>, the current
		///   wireless interface does not allow shared user credentials. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmSetAllowExplicitCreds(const bool Allow);
		/// <summary> Sets the ACM value that indicates the blocked period setting
		///   for the current wireless interface. </summary>
		/// <param name="Period"> The blocked period setting for the current
		///   wireless interface. The blocked period is the amount of time, in
		///   seconds, for which automatic connection to a wireless network will
		///   not be attempted after a previous failure. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmSetBlockPeriod(const unsigned long Period);
		/// <summary> Sets the ACM value indicating whether extensibility on a
		///   virtual station is allowed. </summary>
		/// <param name="Allowed"> If <c>True</c> then extensibility on a virtual
		///   station is allowed; if <c>False</c>, extensibility on a virtual
		///   station is not allowed. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int AcmSetVirtualStationExtensibility(const bool Allowed);
	};

	/// <summary> Defines a pair of 802.11 authentication and cipher algorithms
	///   that can be enabled at the same time on the 802.11 station. </summary>
	typedef struct
	{
		/// <summary> An authentication algorithm as specified by a
		///   <see cref="wclWiFiAuthAlgorithm" /> value. </summary>
		wclWiFiAuthAlgorithm AuthAlgorithm;
		/// <summary> A cipher algorithm as specified by a
		///   <see cref="wclWiFiCipherAlgorithm" /> value. </summary>
		wclWiFiCipherAlgorithm	CipherAlgorithm;
	} wclWiFiAuthCipherPair;
	/// <summary> The dynamic array to store WiFi authentication and cipher
	///   algorithm pairs. </summary>
	/// <seealso cref="wclWiFiAuthCipherPair" />
	typedef std::vector<wclWiFiAuthCipherPair> wclWiFiAuthCipherPairs;

	/// <summary> Specifies the wireless interface type. </summary>
	typedef enum
	{
		/// <summary> An emulated 802.11 interface. </summary>
		itEmulated,
		/// <summary> A native 802.11 interface. </summary>
		itNative,
		/// <summary> The interface specified is invalid. </summary>
		itInvalid
	} wclWiFiInterfaceType;

	/// <summary> Contains information about the capabilities of the
	///   WLAN interface. </summary>
	typedef struct
	{
		/// <summary> Indicates the type of the interface. </summary>
		/// <seealso cref="wclWiFiInterfaceType" />
		wclWiFiInterfaceType IfaceType;
		/// <summary> Indicates whether 802.11d is supported by the interface.
		///   If <c>True</c>, 802.11d is supported. </summary>
		bool Dot11dSupport;
		///<summary> The maximum size of the SSID list supported by this
		///   interface. </summary>
		unsigned long MaxDesiredSsidListSize;
		/// <summary> The maximum size of the basic service set (BSS) identifier
		///   list supported by this interface. </summary>
		unsigned long MaxDesiredBssidListSize;
		/// <summary> A set of <see cref="wclWiFiPhy" /> values that specify the
		///   supported PHY types. </summary>
		/// <seealso cref="wclWiFiPhys" />
		wclWiFiPhys SupportedPhys;
	} wclWiFiInterfaceCapability;

	/// <summary> Contains association attributes for a connection. </summary>
	typedef struct
	{
		/// <summary> The SSID of the association. </summary>
		tstring Ssid;
		/// <summary> The value specifies whether the network is infrastructure or
		///   ad hoc. </summary>
		/// <seealso cref="wclWiFiBssType" />
		wclWiFiBssType BssType;
		/// <summary> The BSSID of the association. </summary>
		tstring BssId;
		/// <summary> The physical type of the association. </summary>
		/// <seealso cref="wclWiFiPhy" />
		wclWiFiPhy Phy;
		/// <summary> A percentage value that represents the signal quality of the
		///   network. Contains a value between 0 and 100. A value of 0 implies an
		///   actual RSSI signal strength of -100 dBm. A value of 100 implies an
		///   actual RSSI signal strength of -50 dBm. You can calculate the RSSI
		///   signal strength value for <c>SignalQuality</c> values between 1 and 99
		///   using linear interpolation. </summary>
		unsigned long SignalQuality;
		/// <summary> The receiving rate of the association. </summary>
		unsigned long RxRate;
		/// <summary> The transmission rate of the association. </summary>
		unsigned long TxRate;
	} wclWiFiAssociationAttributes;

	/// <summary> Defines the security attributes for a wireless
	///   connection. </summary>
	typedef struct
	{
		/// <summary> Indicates whether security is enabled for this
		///   connection. </summary>
		bool SecurityEnabled;
		/// <summary> Indicates whether 802.1X is enabled for this
		///   connection. </summary>
		bool OneXEnabled;
		/// <summary> Authentication and cipher algorithms used for this
		///   connection. </summary>
		/// <seealso cref="wclWiFiAuthCipherPair" />
		wclWiFiAuthCipherPair AuthCiperPair;
	} wclWiFiSecurityAttributes;

	/// <summary> Defines the attributes of a wireless connection. </summary>
	typedef struct
	{
		/// <summary> Indicates the state of the interface. </summary>
		/// <seealso cref="wclWiFiInterfaceState" />
		wclWiFiInterfaceState State;
		/// <summary> Indicates the mode of the connection. </summary>
		/// <seealso cref="wclWiFiConnectionMode" />
		wclWiFiConnectionMode Mode;
		/// <summary> The name of the profile used for the connection. Profile names
		///   are case-sensitive. </summary>
		tstring ProfileName;
		/// <summary> The attributes of the association. </summary>
		/// <seealso cref="wclWiFiAssociationAttributes" />
		wclWiFiAssociationAttributes Association;
		/// <summary> The security attributes of the connection. </summary>
		/// <seealso cref="wclWiFiSecurityAttributes" />
		wclWiFiSecurityAttributes Security;
	} wclWiFiConnectionAttributes;

	/// <summary> The dynamic array defines an 802.11 regulatory domain. For more
	///   information about country strings and regulatory domains, refer to the
	///   IEEE 802.11d-2001 standard. </summary>
	typedef std::vector<tstring> wclWiFiCountryOrRegions;

	/// <summary> The enumeration defines WiFi bands. </summary>
	typedef enum
	{
		/// <summary> The 2.4Ghz band. </summary>
		wb24GHz,
		/// <summary> The 3.65GHz band. </summary>
		wb365GHz,
		/// <summary> The 5GHz band. </summary>
		wb5GHz,
		/// <summary> The 6GHz band. </summary>
		wb6GHz,
		/// <summary> The 60GHz band. </summary>
		wb60GHz,
		/// <summary> The unknown band. </summary>
		wbUnknown
	} wclWiFiBand;

	/// <summary> The <c>CwclWiFiInterface</c> class represents the WLAN
	///   interface and allows an application to control the Wireless LAN
	///   interface. </summary>
	class CwclWiFiInterface
	{
		DISABLE_COPY(CwclWiFiInterface);
		
	private:
		HANDLE	FHandle;
		GUID	FId;
		
		int GetProperty(const WlanApi::WLAN_INTF_OPCODE PropId, void** Data) const;
		// Sets the interface's property.
		int SetProperty(const WlanApi::WLAN_INTF_OPCODE PropId, const DWORD DataSize,
			const void* const Data);

		int ElevatePrivileges() const;

		// Turns WiFi Adapter ON and OFF.
		int SwitchState(const bool TurnOn);
		
	public:
		/// <summary> Creates a new <c>CwclWiFiInterface</c> object. </summary>
		/// <param name="Id"> The interface's ID. </param>
		CwclWiFiInterface(const GUID& Id);
		/// <summary> Frees the <c>CwclWiFiInterface</c> object. </summary>
		virtual ~CwclWiFiInterface();
		
		/// <summary> Closes the WLAN interface and releases allocated WLAN
		///   resources. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int Close();
		/// <summary> Opens the WLAN interface and allocates the WLAN
		///   resources. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> Before an application can use any of the
		///   <c>CwclWiFiInterface</c> object's methods it must open the
		///   interface. </remarks>
		int Open();
		
		/// <summary> Reads the supported authentication and cipher
		///   pairs. </summary>
		/// <param name="AdHoc"> If this parameter set to <c>True</c> the method
		///   returns the pairs for the ad hoc mode. Otherwise the method returns
		///   pairs for the infrastructure mode. </param>
		/// <param name="Pairs"> The method fills this parameter with the array of
		///   the supported authentication and cipher pairs. If no pairs were found
		///   the <c>Pairs</c> parameter will set to <c>NULL</c>. </param>
		/// <returns> If the method succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The caller is responsible for clear memory allocated for the
		///   <c>Pairs</c> dynamic array. </remarks>
		/// <seealso cref="wclWiFiAuthCipherPairs" />
		int GetAuthCipherPairs(const bool AdHoc, wclWiFiAuthCipherPairs& Pairs) const;
		/// <summary> Reads the interface's auto configuration setting. </summary>
		/// <param name="Enabled"> The auto configuration state. If <c>True</c> then
		///   the auto configuration is enabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetAutoConfState(bool& Enabled) const;
		/// <summary> Reads the interface's background scan setting. </summary>
		/// <param name="Enabled"> The background scan state. If <c>True</c> then
		///   the background scan is enabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetBackgroundScanState(bool& Enabled) const;
		/// <summary> Reads the interface's BSS type. </summary>
		/// <param name="BssType"> The BSS type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiBssType" />
		int GetBssType(wclWiFiBssType& BssType) const;
		/// <summary> Reads the interface's capabilities. </summary>
		/// <param name="Capability"> A
		///   <see cref="wclWiFiInterfaceCapability" /> record
		///   which will be filled with the interface's capabilities. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetCapability(wclWiFiInterfaceCapability& Capability) const;
		/// <summary> Reads the interface's certified safe mode support. </summary>
		/// <param name="Supported"> The certified safe mode support. <c>True</c> if
		///   the certified safe mode is supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetCertifiedSafeMode(bool& Supported) const;
		/// <summary> Reads the interface's channel number. </summary>
		/// <param name="Channel"> The channel number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetChannel(unsigned long& Channel) const;
		/// <summary> Read the interface's connection attributes. </summary>
		/// <param name="Attributes"> The connection attributes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiConnectionAttributes" />
		int GetConnectionAttributes(wclWiFiConnectionAttributes& Attributes) const;
		/// <summary> Reads the WiFi interface supported Countries or Regions
		///   list. </summary>
		/// <param name="List"> The supported Countries and Regions List. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The caller is responsible for clear memory allocated for the
		///   <c>List</c> dynamic array. </remarks>
		/// <seealso cref="wclWiFiCountryOrRegions" />
		int GetCountryOrRegions(wclWiFiCountryOrRegions& List) const;
		/// <summary> Reads the WiFi Hosted Network capability of the
		///   interface. </summary>
		/// <param name="Supported"> The Hosted network support. <c>True</c> if the
		///   Hosted Network is supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetHostedNetworkCapable(bool& Supported) const;
		/// <summary> Reads the WiFi Management Frame Protection capability of the
		///   interface. </summary>
		/// <param name="Supported"> The Management Frame Protection support.
		///  <c>True</c> if the Management Frame Protection is supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetManagementFrameProtectionCapable(bool& Supported) const;
		/// <summary> Reads the interface's media streaming setting. </summary>
		/// <param name="Enabled"> The media streaming state. <c>True</c> if the
		///   media streaming is enabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetMediaStreaming(bool& Enabled) const;
		/// <summary> Reads the interface's current operation mode. </summary>
		/// <param name="Mode"> The WiFi interface's current operation
		///   mode. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiOperationMode" />
		int GetOperationMode(wclWiFiOperationMode& Mode) const;
		/// <summary> Reads the interface's radio states for each supported
		///   PHY. </summary>
		/// <param name="States"> The array of radios states. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The caller is responsible for clear memory allocated for the
		///   <c>States</c> dynamic array. </remarks>
		/// <seealso cref="wclWiFiPhyRadioStates" />
		int GetRadioState(wclWiFiPhyRadioStates& States) const;
		/// <summary> Reads the RSSI value. </summary>
		/// <param name="Rssi"> The RSSI value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetRssi(int& Rssi) const;
		/// <summary> Reads the interface's safe mode support. </summary>
		/// <param name="Supported"> The safe mode support. <c>True</c> if the safe
		///   mode is supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetSafeMode(bool& Supported) const;
		/// <summary> Querying dual-STA synchronized connections state. </summary>
		/// <param name="Enabled"> A <c>bool</c> value indicating whether the
		///   primary and secondary STA connections are synchronized. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> To determine whether an adapter will automatically connect
		///   over the secondary STA interface following a connection over the
		///   primary STA interface, your application can call this
		///   method. </remarks>
		int GetSecondarySta(bool& Enabled) const;
		/// <summary> Reads the interface's state. </summary>
		/// <param name="State"> The interface state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiInterfaceState" />
		int GetState(wclWiFiInterfaceState& State) const;
		
		/// <summary> Sets the interface's auto configuration setting. </summary>
		/// <param name="Enable"> If <c>True</c> then the auto configuration will be
		///   enabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetAutoConfState(const bool Enable);
		/// <summary> Sets the interface's background scan setting. </summary>
		/// <param name="Enable"> If <c>True</c> then the background scan will be
		///   enabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetBackgroundScanState(const bool Enable);
		/// <summary> Sets the interface's BSS type. </summary>
		/// <param name="BssType"> The BSS type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiBssType" />
		int SetBssType(const wclWiFiBssType BssType);
		/// <summary> Sets the interface's media streaming setting. </summary>
		/// <param name="Enable"> <c>True</c> to enable then media
		///   streaming. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetMediaStreaming(const bool Enable);
		/// <summary> Sets the interface's operation mode. </summary>
		/// <param name="Mode"> The WiFi interface's operation mode.  </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiOperationMode" />
		int SetOperationMode(const wclWiFiOperationMode Mode);
		/// <summary> Sets the software radio state of a specific physical layer
		///   (PHY) for the interface. </summary>
		/// <param name="State"> The radio state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiPhyRadioState" />
		int SetRadioState(const wclWiFiPhyRadioState& State);
		/// <summary> Enables or disables secondary STA on the given
		///   interface. </summary>
		/// <param name="Enable"> Set this parameter to <c>true</c> to enable
		///   a secondary STA on the given interface. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetSecondarySta(const bool Enable);

		/// <summary> Gets the current IP address of the interface. </summary>
		/// <param name="Static"> <c>True</c> if the interface uses static IP
		///   configuration. <c>False</c> if the interface uses DHCP. </param>
		/// <param name="Address"> The current IP address. </param>
		/// <param name="Mask"> The subnet mask. </param>
		/// <param name="Gateway"> The default gateway address. </param>
		/// <param name="Dns1"> The first DNS server address. </param>
		/// <param name="Dns2"> The second DNS server address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetCurrentIp(bool& Static, tstring& Address, tstring& Mask,
			tstring& Gateway, tstring& Dns1, tstring& Dns2) const;
		/// <summary> Gets current IP settings. </summary>
		/// <param name="Static"> <c>True</c> if the interface uses static IP
		///   configuration. <c>False</c> if the interface uses DHCP. </param>
		/// <param name="Address"> The current IP address. </param>
		/// <param name="Mask"> The subnet mask. </param>
		/// <param name="Gateway"> The default gateway address. </param>
		/// <param name="Dns1"> The first DNS server address. </param>
		/// <param name="Dns2"> The second DNS server address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetIpSettings(bool& Static, tstring& Address, tstring& Mask,
			tstring& Gateway, tstring& Dns1, tstring& Dns2) const;
		/// <summary> Sets current IP settings as static IP configuration. </summary>
		/// <param name="Address"> The current IP address. </param>
		/// <param name="Mask"> The subnet mask. </param>
		/// <param name="Gateway"> The default gateway address. </param>
		/// <param name="Dns1"> The first DNS server address. </param>
		/// <param name="Dns2"> The second DNS server address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetStaticIp(const tstring& Address, const tstring& Mask, 
			const tstring& Gateway, const tstring& Dns1, const tstring& Dns2);
		/// <summary> Enables DHCP configuration for the interface. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnableDhcp();
		
		/// <summary> Turns a WiFi Interface off. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int TurnOff();
		/// <summary> Turns a WiFi Interface on. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int TurnOn();

		/// <summary> Enumerate secondary interfaces of the current WLAN
		///   adapter. </summary>
		/// <param name="Ifaces"> The dynamic array of the
		///   <see cref="wclWiFiInterfaceData" /> structures which receives the
		///   returned list of wireless LAN interfaces. </param>
		/// <returns> <para> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. </para>
		///   <para> If the function fails, the return value may be one of the WCL
		///   error codes. </para> </returns>
		/// <remarks> An application is responsible for releasing a memory
		///   allocated for the <c>Ifaces</c> dynamic array. </remarks>
		/// <seealso cref="wclWiFiInterfaces" />
		int EnumInterfaces(wclWiFiInterfaces& Ifaces);
		
		/// <summary> The method converts the given frequency to the WLAN
		///   band. </summary>
		/// <param name="Frequency"> The central frequency. </param>
		/// <returns> The method returns the WLAN band. </returns>
		/// <seealso cref="wclWiFiBand" />
		static wclWiFiBand FrequencyToBand(const unsigned long Frequency);
		/// <summary> The method converts given central frequency to the WLAN
		///   channel number. </summary>
		/// <param name="Frequency"> The central frequency. </param>
		/// <returns> If the <c>Frequency</c> if a valid central frequency the method
		///   returns the channel number. If the central frequency is invalid or
		///   unknown the method returns 0. </returns>
		static unsigned char FrequencyToChannel(const unsigned long Frequency);
		
		/// <summary> Gets the interface active state. </summary>
		/// <returns> <c>True</c> if the interface is opened. </returns>
		bool GetActive() const;
		/// <summary> Gets the interface active state. </summary>
		/// <value> <c>True</c> if the interface is opened. </value>
		__declspec(property(get = GetActive)) bool Active;
		
		/// <summary> Gets the WLAN interface's ID. </summary>
		/// <returns> The WLAN interface's ID. </returns>
		GUID GetId() const;
		/// <summary> Gets the WLAN interface's ID. </summary>
		/// <value> The WLAN interface's ID. </value>
		__declspec(property(get = GetId)) GUID Id;
	};

	/// <summary> he structure contains information about the status of the
	///   wireless Hosted Network. </summary>
	typedef struct
	{
		/// <summary> <para> The current state of the wireless Hosted
		///   Network. </para>
		///   <para> If the value of this member is <c>hnUnavailable</c>, then the
		///   values of the other fields in this structure should not be
		///   used. </para> </summary>
		/// <seealso cref="wclWiFiHostedNetworkState" />
		wclWiFiHostedNetworkState State;
		/// <summary> <para> The actual network Device ID used for the wireless
		///   Hosted Network. </para>
		///   <para> This is member is the GUID of a virtual wireless device which
		///   would not be available through calls to the <c>EnumInterfaces</c>
		///   method of the <see cref="CwclWiFiClient" /> component. This GUID can
		///   be used for calling other higher layer networking functions that use
		///   the device GUID (IP Helper functions, for example). </para> </summary>
		GUID Id;
		/// <summary> The BSSID used by the wireless Hosted Network in packets,
		///   beacons, and probe responses. </summary>
		tstring BssId;
		/// <summary> <para> The physical type of the network interface used by
		///   wireless Hosted Network. </para>
		///   <para> This is one of the types reported by the related physical
		///   interface. This value is correct only if the <c>State</c> member is
		///   <c>hnActive</c>. </para> </summary>
		/// <seealso cref="wclWiFiPhy" />
		wclWiFiPhy Phy;
		/// <summary> <para> The channel frequency of the network interface used by
		///   wireless Hosted Network. </para>
		///   <para> This value is correct only if <c>State</c> is
		///   <c>hnActive</c>. </para> </summary>
		unsigned long ChannelFrequency;
		/// <summary> <para> A dynamic array of
		///   <see cref="wclWiFiHostedNetworkPeerState" /> structures
		///   describing each of the current peers on the wireless Hosted
		///   Network. </para>
		///   <para> This value is correct only if <c>State</c> is
		///   <c>hnActive</c>. </para> </summary>
		/// <remarks> The caller is responsible to release the memory allocated
		///   for the dynamic array. </remarks>
		/// <seealso cref="wclWiFiHostedNetworkPeerStates" />
		wclWiFiHostedNetworkPeerStates Peers;
	} wclWiFiHostedNetworkStatus;

	/// <summary> The structure contains information about the connection settings
	///   on the wireless Hosted Network. </summary>
	typedef struct
	{
		/// <summary> The SSID associated with the wireless Hosted
		///   Network. </summary>
		tstring Ssid;
		/// <summary> The maximum number of concurrent peers allowed by the wireless
		///   Hosted Network. </summary>
		unsigned long MaxNumberOfPeers;
	} wclWiFiHostedNetworkConnectionSettings;

	/// <summary> The <c>CwclWiFiHostedNetwork</c> component provides access to
	///   the WiFi Hosted Network features. </summary>
	/// <remarks> In order to receiver the Hosted Network notifications an
	///   application must use the <see cref="CwclWiFiEvents" />
	///   component. </remarks>
	class CwclWiFiHostedNetwork : public CwclCustomWiFiMemoryComponent
	{
		DISABLE_COPY(CwclWiFiHostedNetwork);
		
	private:
		wclWiFiScanIeData	FData;
		tstring				FFormat;

		int GetProperty(const WlanApi::WLAN_HOSTED_NETWORK_OPCODE OpCode, void** Data) const;
		int SetProperty(const WlanApi::WLAN_HOSTED_NETWORK_OPCODE OpCode, const DWORD Size,
			const void* const Data);

		int AddPsdIe();

		int GetStateOpened(bool& Enabled) const;
		int GetStateClosed(bool& Enabled) const;

		int SetStateOpened(const bool Enabled);
		int SetStateClosed(const bool Enabled);

	protected:
		/// <summary> Executes additional finalization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() override;
		/// <summary> Executes additional initialization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() override;
		
	public:
		/// <summary> Creates a new component. </summary>
		CwclWiFiHostedNetwork();

		/// <summary> Reads the information about the connection settings on the
		///   wireless Hosted Network. </summary>
		/// <param name="Settings"> The hosted network connection settings. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiHostedNetworkConnectionSettings" />
		int GetConnectionSettings(wclWiFiHostedNetworkConnectionSettings& Settings) const;
		/// <summary> Reads the secondary security key that is configured to be
		///   used by the wireless Hosted Network. </summary>
		/// <param name="KeyLength"> <para> A value that specifies number of valid
		///   data bytes in the key data array pointed to by the <c>KeyData</c>
		///   parameter, if the call to the method succeeds. </para>
		///   <para> This key length includes the terminating <c>0</c> if the key is
		///   a passphrase. </para> </param>
		/// <param name="KeyData"> A value that receives a pointer to the buffer
		///   returned with the secondary security key data, if the call to the
		///   method succeeds. </param>
		/// <param name="IsPassPhrase"> <para> A Boolean value that indicates if the
		///   key data array pointed to by the <c>KeyData</c> parameter is in
		///   passphrase format. </para>
		///   <para> If this parameter is <c>True</c>, the key data array is in
		///   passphrase format. If this parameter is <c>False</c>, the key data
		///   array is not in passphrase format. </para> </param>
		/// <param name="Persistent"> <para> A Boolean value that indicates if the
		///   key data array pointed to by the <c>KeyData</c> parameter is to be
		///   stored and reused later or is for one-time use only. </para>
		///   <para> If this parameter is <c>True</c>, the key data array is to be
		///   stored and reused later. If this parameter is <c>False</c>, the key
		///   data array is for one-time use only. </para> </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> A client application calls the <c>GetKey</c> method to
		///   query the secondary security key that will be used by the wireless
		///   Hosted Network. This function will return the key information
		///   including key data, key length, whether it is a passphrase, and
		///   whether it is persistent or for one-time use. This function does not
		///   change the state or properties of the wireless Hosted Network. </para>
		///   <para> The secondary security key is a passphrase if the value of the
		///   <c>IsPassPhrase</c> parameter is <c>True</c>. The secondary security
		///   key is a binary key if the value of the "IsPassPhrase" parameter is
		///   <c>False</c>. </para>
		///   <para> The secondary security key returned in the buffer pointed to
		//		by the <c>KeyData</c> parameter is used with WPA2-Personal
		///   authentication and is in one of the following formats: </para>
		///   <list type="bullet">
		///		 <item> A key passphrase that consists of an array of ASCII
		///						characters from 8 to 63 characters. The value of the
		///						<c>KeyLength</c> parameter includes the terminating <c>0</c>
		///						in the passphrase. The value of the <c>KeyLength</c>
		///						parameter should be in the range of 9 to 64. </item>
		///		 <item> A binary key that consist of 32 bytes of binary key data.
		///						The value of the <c>KeyLength</c> parameter should be 32
		///						for binary key. </item>
		///   </list>
		///   <para> The secondary security key is persistent if the value of the
		///   <c>Persistent</c> parameter is <c>True</c>. When persistent, the
		///   secondary security key would be used immediately if the Hosted
		///   Network is already started, and also reused whenever Hosted Network
		///   is started in the future. </para>
		///   <para> If secondary security key is not specified as persistent, it
		///   will be used immediately if the Hosted Network is already started, or
		///   only for the next time when the Hosted Network is started. After the
		///   Hosted Network is stopped, this secondary security key will never be
		///   used again and will be removed from the system. </para>
		///   <para> If there is no secondary security key currently configured, the
		///   returned value of the <c>KeyLength</c> parameter will be zero, and the
		///   value returned in the <c>KeyData</c> parameter will be <c>NULL</c>.
		///   In such case, the value returned in the <c>IsPassPhrase</c> and
		///   <c>Persistent</c> parameters will be meaningless. </para>
		///   <para> If the method succeeds, the memory used for the buffer in the
		///   <c>KeyData</c> parameter that is returned should be freed after use by
		///   calling the <c>FreeMemory</c> method. </para> </remarks>
		int GetKey(unsigned long& KeyLength, void*& KeyData,  bool& IsPassPhrase, 
			bool& Persistent) const;
		/// <summary> Gets the local IP address for the Hosted Network Virtual
		///   WiFi adapter. </summary>
		/// <param name="Address"> If the method completed with success on output
		///   contains the Hosted Network local IP address. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int GetLocalIp(tstring& Address) const;
		/// <summary> Gets the list of currently connected peers. </summary>
		/// <param name="Peers"> If the method completed with success on output
		///   contains the list of current connected peers. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiHostedNetworkConnectedPeers" />
		int GetConnectedPeers(wclWiFiHostedNetworkConnectedPeers& Peers);
		/// <summary> Reads the wireless Hosted Network station profile. </summary>
		/// <param name="ProfileXml"> Contains an XML WLAN profile for connecting
		///   to the wireless Hosted Network is returned. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int GetProfile(tstring& ProfileXml) const;
		/// <summary> Gets the remote IP address for the device connected to Hosted
		///   Network Virtual WiFi adapter. </summary>
		/// <param name="Mac"> The remote device's MAC address. </param>
		/// <param name="Address"> If the method completed with success on output
		///   contains the remote IP address. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int GetRemoteIp(const tstring& Mac, tstring& Address) const;
		/// <summary> Reads the information about the security settings on the
		///   wireless Hosted Network. </summary>
		/// <param name="Settings"> The security settings on the wireless Hosted
		///   Network. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiAuthCipherPair" />
		int GetSecuritySettings(wclWiFiAuthCipherPair& Settings) const;
		/// <summary> The function queries the current status of the
		///   wireless Hosted Network. </summary>
		/// <param name="Status"> Receives a current status of the wireless Hosted
		///   Network, if the call to the GetStatus method succeeds. The current
		///		status is returned in a <see cref="wclWiFiHostedNetworkStatus" />
		///   record. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int GetStatus(wclWiFiHostedNetworkStatus& Status) const;
		/// <summary> Reads the wireless Hosted Network enabled flag. </summary>
		/// <param name="Enabled"> <c>True</c> if the Wireless Hosted Network is
		///   enabled. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> The method can be called without opening the Hosted
		///   Network. </remarks>
		int GetState(bool& Enabled) const;
		
		/// <summary> Writes the information about the connection settings on the
		///   wireless Hosted Network. </summary>
		/// <param name="Settings"> The hosted network connection settings.</param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiHostedNetworkConnectionSettings" />
		int SetConnectionSettings(const wclWiFiHostedNetworkConnectionSettings& Settings);
		/// <summary> The method configures the secondary security key that will
		///   be used by the wireless Hosted Network. </summary>
		/// <param name="KeyLength"> The number of valid data bytes in the key data
		///   array pointed to by the <c>KeyData</c> parameter. This key length
		///   should include the terminating <c>0</c> if the key is a
		///   passphrase. </param>
		/// <param name="KeyData"> A pointer to a buffer that contains the key data.
		///   The number of valid data bytes in the buffer must be at least the
		///   value specified in <c>KeyLength</c> parameter. </param>
		/// <param name="IsPassPhrase"> <para> A Boolean value that indicates if the
		///   key data array pointed to by the <c>KeyData</c> parameter is in
		///   passphrase format. </para>
		///   <para> If this parameter is <c>True</c>, the key data array is in
		///   passphrase format. If this parameter is <c>False</c>, the key data
		///   array is not in passphrase format. </para> </param>
		/// <param name="Persistent"> <para> A Boolean value that indicates if the
		///   key data array pointed to by the <c>KeyData</c> parameter is to be
		///   stored and reused later or is for one-time use only. </para>
		///   <para> If this parameter is <c>True</c>, the key data array is to be
		///   stored and reused later. If this parameter is <c>False</c>, the key
		///   data array is to be used for one session (either the current session
		///   or the next session if the Hosted Network is not
		///   started). </para> </param>
		/// <remarks> <para> A client application calls the <c>SetKey</c> method to
		///   configure the secondary security key that will be used by the
		///   wireless Hosted Network. Any Hosted Network change caused by this
		///   function would not be automatically undone if the calling application
		///   closes or if the process ends. </para>
		///   <para> Once started, the wireless Hosted Network will allow wireless
		///   peers to associate with this secondary security key in addition to the
		///   primary security key. The secondary security key is always specified
		///   by the user as needed, while the primary security key is generated by
		///   the operating system with greater security strength. </para>
		///   <para> The secondary security key passed in the buffer pointed to by
		///   the <c>KeyData</c> parameter is used with WPA2-Personal authentication
		///   and should be in one of the following formats: </para>
		///   <list type="bullet">
		///		 <item> A key passphrase that consists of an array of ASCII
		///						characters from 8 to 63 characters. The <c>KeyLength</c>
		///						parameter should include the terminating <c>0</c> in the
		///						passphrase. The value of the <c>KeyLength</c> parameter
		///						should be in the range of 9 to 64. </item>
		///		 <item> A binary key that consists of 32 bytes of binary key data.
		///						The <c>KeyLength</c> parameter should be 32 for binary
		///						key. </item>
		///   </list>
		///   <para> To configure a valid secondary security key, the
		///   <c>KeyLength</c> parameter should be in the correct range and the
		///   <c>KeyData</c> parameter should point to a valid memory buffer
		///   containing the specified bytes of data. To remove the currently
		///   configured secondary security key from the system, the application
		///   should call the <c>SetKey</c> method with zero in <c>KeyLength</c>
		///   parameter and <c>NULL</c> in the <c>KeyData</c> parameter. </para>
		///   <para> The <c>SetKey</c> method will return
		///   <see cref="WCL_E_WIFI_INVALID_ARGUMENT" /> if the <c>KeyData</c>
		///   parameter is <c>NULL</c>, but the <c>KeyLength</c> parameter is not
		///   zero. The <c>SetKey</c> method will also return
		///   <see cref="WCL_E_WIFI_INVALID_ARGUMENT" /> if the <c>KeyLength</c>
		///   parameter is zero, but <c>KeyData</c> parameter is not
		///   <c>NULL</c>. </para>
		///   <para> The secondary security key can be specified as persistent if
		///   the <c>Persistent</c> parameter is set to <c>True</c>. When specified
		///   as persistent, the secondary security key would be used immediately
		///   and also reused whenever Hosted Network is started in the
		///   future. </para>
		///   <para> If secondary security key is not specified as persistent, it
		///   will be used immediately, or only for the next time when Hosted
		///   Network is started. After the Hosted Network is stopped, this
		///   secondary security key will never be used again and will be removed
		///   from the system. </para> </remarks>
		int SetKey(const unsigned long KeyLength, const void* const KeyData, 
			const bool IsPassPhrase, const bool Persistent);
		/// <summary> Writes the wireless Hosted Network enabled flag. </summary>
		/// <param name="Enabled"> <c>True</c> to enable the Wireless Hosted
		///   Network. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> The method can be called without opening the Hosted
		///   Network. The method requires administrative rights. </remarks>
		int SetState(const bool Enabled);

		/// <summary> The function refreshes the configurable and auto-generated
		///   parts of the wireless Hosted Network security settings. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> A client application calls the
		///   <c>RefreshSecuritySettings</c> method to force a refresh of the
		///   configurable and auto-generated parts of the security settings (the
		///   primary key) on the wireless Hosted Network. </para>
		///   <para> An application might call the <c>RefreshSecuritySettings</c>
		///   method after ensuring that the user accepts the impact of updating the
		///   security settings. In order to succeed, this function must persist the
		///   new settings which would require that Hosted Network state be
		///   transitioned to <c>hnIdle</c> if it was currently running
		///   (<c>hnActive</c>). </para>
		///   <para> Any network clients (PCs or devices) on the
		///   wireless Hosted Network would have to be re-configured after calling
		///   the <c>RefreshSecuritySettings</c> method if their continued usage is
		///   a goal. An application would typically call this function in
		///   situations where the user feels that the security of the previous
		///   primary key used for security by the wireless Hosted Network has been
		///   violated. </para>
		///   <para> Note that the <c>RefreshSecuritySettings</c> method does not
		///   change or reset the secondary key. </para> </remarks>
		int RefreshSecuritySettings();
		
		/// <summary> Restarts the Hosted Network service. </summary>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int Restart();

		/// <summary> Sets the proximity service discovery (PSD) information element
		///   (IE) data. </summary>
		/// <param name="Format"> The format of a PSD IE in the PSD IE data. This is
		///   a URI string that specifies the namespace of the protocol used for
		///   discovery. </param>
		/// <param name="Data"> The PSD IE data. The data must not exceed 240
		///   bytes. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> To reset PSD IE set the <c>Format</c> parameter to an
		///   empty string and the <c>Data</c> parameter to an empty array. </para>
		///   <para> The Proximity Service Discovery Protocol is a Microsoft
		///   proprietary protocol that allows a client to discover services in its
		///   physical proximity, which is defined by the radio range. The purpose
		///   of the Proximity Service Discovery Protocol is to convey service
		///   discovery information, such as service advertisements, as part of
		///   Beacon frames. Access points (APs) and stations (STAs) that operate in
		///   ad hoc mode periodically broadcast beacon frames. The beacon frame can
		///   contain single or multiple proprietary information elements that carry
		///   discovery information pertaining to the services that the device
		///   offers. </para>
		///   <para> A PSD IE is used to transmit compressed information provided by
		///   higher-level discovery protocols for the purpose of passive discovery.
		///   One such higher-level protocol used for discovery is the WS-Discovery
		///   protocol. Any protocol can be used for discovery. </para> </remarks>
		/// <seealso cref="wclWiFiScanIeData" />
		int SetPsdIe(const tstring& Format, const wclWiFiScanIeData& Data);

		/// <summary> Gets the PSD IE data. </summary>
		/// <returns> The bytes array represents a raw PSD IE data. </returns>
		/// <seealso cref="wclWiFiScanIeData" />
		wclWiFiScanIeData GetData() const;
		/// <summary> Gets the PSD IE data. </summary>
		/// <value> The bytes array represents a raw PSD IE data. </value>
		/// <seealso cref="wclWiFiScanIeData" />
		__declspec(property(get = GetData)) wclWiFiScanIeData Data;

		/// <summary> Gets the PSD IE format string. </summary>
		/// <returns> The string value represents PSD IE format. </returns>
		tstring GetFormat() const;
		/// <summary> Gets the PSD IE format string. </summary>
		/// <value> The string value represents PSD IE format. </value>
		__declspec(property(get = GetFormat)) tstring Format;
	};

	class CwclWiFiProfilesManager; // For XML Doc compilation.

	/// <summary> The flags specifying settings for wireless profile. </summary>
	typedef enum
	{
		/// <summary> This flag indicates that this profile was created by group
		///   policy. A group policy profile is read-only. Neither the content nor
		///   the preference order of the profile can be changed. </summary>
		pfGroupPolicy,
		/// <summary> This flag indicates that the profile is a per-user profile.
		///   If not set, this profile is an all-user profile. </summary>
		pfUser,
		/// <summary> This flag indicates that the caller wants to retrieve the
		///   plain text key from a wireless profile. If the calling thread has
		///   the required permissions, the <c>GetProfile</c> method of the
		///   <see cref="CwclWiFiProfilesManager" /> returns the plain text key in
		///   the <c>keyMaterial</c> element of the profile returned in the buffer
		///   pointed to by the <c>ProfileXml</c> parameter. </summary>
		pfGetPlaintextKey
	} wclWiFiProfileFlag;

	/// <summary> A set of the WiFi profile flags. </summary>
	/// <seealso cref="wclWiFiProfileFlag" />
	typedef std::set<wclWiFiProfileFlag> wclWiFiProfileFlags;

	/// <summary> The record contains basic information about a WLAN
	///   profile. </summary>
	typedef struct
	{
		/// <summary> The name of the profile. This value may be the name of a
		///   domain if the profile is for provisioning. Profile names are
		///   case-sensitive. </summary>
		tstring Name;
		/// <summary> A set of flags specifying settings for wireless
		///   profile. </summary>
		/// <seealso cref="wclWiFiProfileFlags" />
		wclWiFiProfileFlags Flags;
	} wclWiFiProfileData;
	/// <summary> A dynamic array for the Wireless profiles. </summary>
	/// <seealso cref="wclWiFiProfileData" />
	typedef std::vector<wclWiFiProfileData> wclWiFiProfiles;

	/// <summary> The flags to set on the profile. </summary>
	typedef enum
	{
		/// <summary> The profile is a per-user profile. </summary>
		tpfUser,
		/// <summary> The profile was created by the client. </summary>
		tpfConnectionModeSetByClient,
		/// <summary> The profile was created by the automatic configuration
		///   module. </summary>
		tpfConnectionModeAuto
	} wclWiFiTemporaryProfileFlag;

	/// <summary> The set of flags to set on the profile. </summary>
	/// <seealso cref="wclWiFiTemporaryProfileFlag" />
	typedef std::set<wclWiFiTemporaryProfileFlag> wclWiFiTemporaryProfileFlags;

	/// <summary> Specifies the active tab when the wireless profile user
	///   interface dialog box appears. </summary>
	typedef enum
	{
		/// <summary> Displays the Connection tab. </summary>
		epConnection,
		/// <summary> Displays the Security tab. </summary>
		epSecurity,
		/// <summary> Display the Advanced tab. </summary>
		epAdvanced
	} wclWiFiProfileEditPage;

	/// <summary> Provides access to the Wireless Network profiles. </summary>
	/// <remarks> <para> An application uses this component to manage the
	///   Wireless LAN profiles. </para>
	///   <para> In order to receiver the profile changes notifications an
	///   application must use the <see cref="CwclWiFiEvents" />
	///   component. </para> </remarks>
	class CwclWiFiProfilesManager : public CwclCustomWiFiMemoryComponent
	{
		DISABLE_COPY(CwclWiFiProfilesManager);
		
	protected:
		/// <summary> Executes additional finalization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int InternalClose();
		/// <summary> Executes additional initialization procedures. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int InternalOpen();
		
	public:
		/// <summary> Creates new object. </summary>
		CwclWiFiProfilesManager();

		/// <summary> The method retrieves all information about a specified
		///   wireless profile. </summary>
		/// <param name="IfaceId"> The ID of the wireless interface. </param>
		/// <param name="ProfileName"> The name of the profile. Profile names are
		///   case-sensitive. The maximum length of the profile name is 255
		///   characters. This means that the maximum length of this string
		///   is 255 characters. </param>
		/// <param name="Flags"> <para> On input is used to provide additional
		///   information about the request. If this parameter is an empty set on
		///   input, then no information on profile flags will be returned. </para>
		///   <para> On output is used to receive profile flags. </para> </param>
		/// <param name="ProfileXml"> A string that is the XML representation of
		///   the queried profile. There is no predefined maximum string
		///   length. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> If the <c>GetProfile</c> function succeeds, the
		///   wireless profile is returned in the <c>ProfileXml</c> parameter. This
		///   is a string that is the XML representation of the queried profile.
		///   For a description of the XML representation of the wireless profile,
		///   see <c>WLAN_profile</c> Schema. </para>
		///   <para> The <c>keyMaterial</c> element returned in the profile schema
		///   pointed to by the <c>ProfileXml</c> may be requested as plain text if
		///   the <c>GetProfile</c> function is called with the
		///   <c>pfGetPlaintextKey</c> flag set in the value of the <c>Flags</c>
		///   parameter on input. </para>
		///   <para> For a WEP key, both 5 ASCII characters or 10 hexadecimal
		///   characters can be used to set the plain text key when the profile is
		///   created or updated. However, a WEP profile will be saved with 10
		///   hexadecimal characters in the key no matter what the original input
		///   was used to create the profile. So in the profile returned by the
		///   <c>GetProfile</c> method, the plain text WEP key is always returned
		///   as 10 hexadecimal characters. </para>
		///   <para> By default, the <c>keyMaterial</c> element returned in the
		///   profile in the <c>ProfileXml</c> is encrypted. If your process runs in
		///   the context of the <c>LocalSystem</c> account on the same computer,
		///   then you can decrypt key material by calling the
		///   <c>CryptUnprotectData</c> function. </para> </remarks>
		/// <seealso cref="wclWiFiProfileFlags" />
		int GetProfile(const GUID& IfaceId, const tstring& ProfileName,
			wclWiFiProfileFlags& Flags, tstring& ProfileXml) const;
		/// <summary> The method retrieves the list of profiles in preference
		///   order. </summary>
		/// <param name="IfaceId"> The ID of the wireless interface. </param>
		/// <param name="Profiles"> A dynamic array that contains the list of
		///   profile information. The caller is responsible to free the memory
		///   allocated for the dynamic array. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> The <c>GetProfileList</c> method returns only the basic
		///   information on the wireless profiles on a wireless interface. The list
		///   of wireless profiles on a wireless interface are retrieved in the
		///   preference order. The <c>SetProfilePosition</c> method can be used to
		///   change the preference order for the wireless profiles on a wireless
		///   interface. </para>
		///   <para> More detailed information for a wireless profile on a wireless
		///   interface can be retrieved by using the <c>GetProfile</c> method. The
		///   <c>GetProfileUserData</c> method can be used to retrieve custom user
		///   data for a wireless profile on a wireless interface. A list of the
		///   wireless interfaces and associated IDs on the local computer can be
		///   retrieved using the <c>EnumInterfaces</c> method of the
		///   <see cref="CwclWiFiClient" /> component. </para> </remarks>
		/// <seealso cref="wclWiFiProfiles" />
		int GetProfileList(const GUID& IfaceId, wclWiFiProfiles& Profiles) const;
		/// <summary> The method deletes a wireless profile for a wireless interface
		///   on the local computer. </summary>
		/// <param name="IfaceId"> The ID of the interface from which to delete the
		///   profile. </param>
		/// <param name="ProfileName"> The name of the profile to be
		///   deleted. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int DeleteProfile(const GUID& IfaceId, const tstring& ProfileName);
		/// <summary> Renames the specified profile. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="OldName"> The profile name to be changed. </param>
		/// <param name="NewName"> The new name of the profile. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int RenameProfile(const GUID& IfaceId, const tstring& OldName,
			const tstring& NewName);
		
		/// <summary> Saves a temporary profile to the profile store. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> The name of the profile to be saved. Profile
		///   names are case-sensitive. </param>
		/// <param name="OverWrite"> Specifies whether this profile is overwriting
		///   an existing profile. If this parameter is <c>False</c> and the profile
		///   already exists, the existing profile will not be overwritten and an
		///   error will be returned. </param>
		/// <param name="Flags"> The flags to set on the profile. If the set is
		///   empty then the profile is an all-user profile. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> A temporary profile is the one passed to then
		///   <c>Connect</c> method of the <see cref="CwclWiFiClient" /> component
		///   or generated by the discovery engine. A network connection can be
		///   established using a temporary profile. Using this method saves the
		///   temporary profile and associated user data to the profile
		///   store. </para>
		///   <para> A new profile is added at the top of the list after the group
		///   policy profiles. A profile's position in the list is not changed if an
		///   existing profile is overwritten. </para> </remarks>
		/// <seealso cref="wclWiFiTemporaryProfileFlags" />
		int SaveTemporaryProfile(const GUID& IfaceId, const tstring& ProfileName, 
			const bool OverWrite, const wclWiFiTemporaryProfileFlags& Flags);
		
		/// <summary> The method sets the position of a single, specified profile
		///   in the preference list. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> The name of the profile. Profile names are
		///   case-sensitive. </param>
		/// <param name="Position"> Indicates the position in the preference list
		///   that the profile should be shifted to. 0 (zero) corresponds to the
		///   first profile in the list that is returned by the
		///   <c>GetProfileList</c> method. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int SetPosition(const GUID& IfaceId, const tstring& ProfileName, 
			const unsigned long Position);
		
		/// <summary> The method sets the content of a specific profile. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="Flags"> The flags to set on the profile. </param>
		/// <param name="ProfileXml"> Contains the XML representation of the
		///   profile. The <c>WLANProfile</c> element is the root profile
		///   element. </param>
		/// <param name="Overwrite"> Specifies whether this profile is overwriting
		///   an existing profile. If this parameter is <c>False</c> and the profile
		///   already exists, the existing profile will not be overwritten and
		///   an error will be returned. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> The SetProfile method can be used to add a new
		///   wireless LAN profile or replace an existing wireless LAN
		///   profile. </para>
		///   <para> A new profile is added at the top of the list after the group
		///   policy profiles. A profile's position in the list is not changed if an
		///   existing profile is overwritten. </para> </remarks>
		/// <seealso cref="wclWiFiProfileFlags" />
		int SetProfile(const GUID& IfaceId, const wclWiFiProfileFlags& Flags, 
			const tstring& ProfileXml, const bool Overwrite);
		
		/// <summary> The method sets the preference order of profiles for a
		///   given interface. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="Names"> The names of the profiles in the desired order.
		///   Profile names are case-sensitive. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> The method sets the preference order of wireless LAN
		///   profiles for a given wireless interface. </para>
		///   <para> The profiles in the list must be a one-to-one match with the
		///   current profiles returned by the <c>GetProfileList</c>
		///   method. </para> </remarks>
		int SetProfileList(const GUID& IfaceId, const std::vector<tstring>& Names);
		
		/// <summary> The method gets the custom user data associated with a
		///   wireless profile. </summary>
		/// <param name="IfaceId"> The ID of the wireless LAN interface. </param>
		/// <param name="ProfileName"> The name of the profile with which the custom
		///   user data is associated. Profile names are case-sensitive. </param>
		/// <param name="DataSize"> The size, in bytes, of the user data buffer
		///   pointed to by the <c>Data</c> parameter. </param>
		/// <param name="Data"> A pointer to the user data. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> For every wireless WLAN profile used by the Native Wi-Fi
		///   AutoConfig service, Windows maintains the concept of custom user data.
		///   This custom user data is initially non-existent, but can be set by
		///   calling the <c>SetProfileUserData</c> method. The custom user data
		///   gets reset to empty any time the profile is modified by calling the
		///   <c>SetProfile</c> method. </para>
		///   <para> Once custom user data has been set, this data can be accessed
		///   using the <c>GetProfileUserData</c> method. </para>
		///   <para> The caller is responsible for freeing the memory allocated for
		///   the buffer pointed to by the <c>Data</c> parameter using the
		///   <c>FreeMemory</c> method. </para> </remarks>
		int GetProfileUserData(const GUID& IfaceId,  const tstring& ProfileName, 
			unsigned long& DataSize, void*& Data) const;
		
		/// <summary> Sets the custom user data associated with a
		///   profile. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> The name of the profile associated with the
		///   custom user data. Profile names are case-sensitive. </param>
		/// <param name="DataSize"> The size of <c>Data</c>, in bytes. </param>
		/// <param name="Data"> A pointer to the user data to be set. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <remarks> <para> For every wireless WLAN profile used by the Native Wi-Fi
		///   AutoConfig service, Windows maintains the concept of custom user data.
		///   This custom user data is initially non-existent, but can be set by
		///   calling the <c>SetProfileUserData</c> method. The custom user data
		///   gets reset to empty any time the profile is modified by calling the
		///   <c>SetProfile</c> method. </para>
		///   <para> Once custom user data has been set, this data can be accessed
		///   using the <c>GetProfileUserData</c> method. </para> </remarks>
		int SetProfileUserData(const GUID& IfaceId, const tstring& ProfileName,
			const unsigned long DataSize, const void* const Data);

		/// <summary> The method sets the Extensible Authentication Protocol (EAP)
		///   user credentials as specified by an XML string. The user credentials
		///   apply to a profile on an adapter (interface). These credentials can
		///   only be used by the caller. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> <para> The name of the profile associated
		///   with the EAP user data. Profile names are case-sensitive. </para>
		///   <para> Windows XP with SP3 and Wireless LAN API for Windows XP with
		///   SP2:  The supplied name must match the profile name derived
		///   automatically from the SSID of the network. For an infrastructure
		///   network profile, the SSID must be supplied for the profile name.
		///   For an ad hoc network profile, the supplied name must be the SSID of
		///   the ad hoc network followed by -ad-hoc. </para> </param>
		/// <param name="AllUsers"> If this parameter is <c>True</c> on Windows 7,
		///   Windows Server 2008 R2, and later, the EAP host data will be set for
		///   all users of this profile. </param>
		/// <param name="UserData"> An XML string represents a data used to set the
		///   user credentials. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		int SetProfileEapXmlUserData(const GUID& IfaceId, const tstring& ProfileName, 
			const bool AllUsers, const tstring& UserData);
		/// <summary> The function sets the Extensible Authentication Protocol (EAP)
		///   user credentials as specified by raw EAP data. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> <para> The name of the profile associated
		///   with the EAP user data. Profile names are case-sensitive. </para>
		///   <para> Windows XP with SP3 and Wireless LAN API for Windows XP with
		///   SP2:  The supplied name must match the profile name derived
		///   automatically from the SSID of the network. For an infrastructure
		///   network profile, the SSID must be supplied for the profile name.
		///   For an ad hoc network profile, the supplied name must be the SSID of
		///   the ad hoc network followed by -ad-hoc. </para> </param>
		/// <param name="AllUsers"> If this parameter is <c>True</c> on Windows 7,
		///   Windows Server 2008 R2, and later, the EAP host data will be set for
		///   all users of this profile. </param>
		/// <param name="EapMethod"> An <see cref="wclWiFiEapMethodType" />
		///   structure that contains the method for which the caller is supplying
		///   EAP user credentials. </param>
		/// <param name="Data"> <para> A pointer to the raw EAP data used to set the
		///   user credentials. </para>
		///   <para> On Windows Vista and Windows Server 2008, this parameter must
		///   not be <c>nil</c>. </para>
		///   <para> On Windows 7, Windows Server 2008 R2, and later, this parameter
		///   can be set to <c>NULL</c> to delete the stored credentials for this
		///   profile if the <c>AllUsers</c> parameter contains set to <c>true</c>
		///   and the <c>Size</c> parameter is 0. </para> </param>
		/// <param name="Size"> The size, in bytes, of the data pointed to by
		///   <c>Data</c>. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiEapMethodType" />
		int SetProfileEapUserData(const GUID& IfaceId, const tstring& ProfileName, 
			const bool AllUsers, const wclWiFiEapMethodType& EapMethod, 
			const unsigned char* const Data, const unsigned long Size);

		/// <summary> Displays the wireless profile user interface (UI). This UI is
		///   used to view and edit advanced settings of a wireless network
		///   profile. </summary>
		/// <param name="IfaceId"> The ID of the interface. </param>
		/// <param name="ProfileName"> Contains the name of the profile to be viewed
		///   or edited. Profile names are case-sensitive. The supplied profile must
		///   be present on the interface. That means the profile must have been
		///   previously created and saved in the profile store and that the profile
		///   must be valid for the supplied interface. </param>
		/// <param name="Page"> A <see cref="wclWiFiProfileEditPage" /> value that
		///   specifies the active tab when the UI dialog box appears. </param>
		/// <returns> If the function succeeds, the return value is
		///   <see cref="WCL_E_SUCCESS" />. If the function fails, the return value
		///   may be one of the WCL return codes. </returns>
		/// <seealso cref="wclWiFiProfileEditPage" />
		int ShowUIEdit(const GUID& IfaceId, const tstring& ProfileName,
			const wclWiFiProfileEditPage Page = epConnection);

		/// <summary> The function creates a HEX representation for the provided
		///   SSID. </summary>
		/// <param name="Ssid"> The SSID. </param>
		/// <returns> The HEX that can be used in XML profile. </returns>
		tstring SsidToHex(const tstring& Ssid) const;
	};

	/// <summary> The PHY types used by the WiFi Sniffer. </summary>
	typedef enum
	{
		/// <summary> The 802.11a standard. </summary>
		ph802_11a,
		/// <summary> The 802.11b standard. </summary>
		ph802_11b,
		/// <summary> The 802.11g standard. </summary>
		ph802_11g,
		/// <summary> The 802.11n standard. </summary>
		ph802_11n,
		/// <summary> Undefined or unknown PHY. </summary>
		phUndefined
	} wclWiFiSnifferPhy;

	/// <summary> The structure contains meta data information about captured
	///   WiFi frame. </summary>
	typedef struct
	{
		/// <summary> The meta data version. </summary>
		unsigned char Version;
		/// <summary> The interface's operation mode. </summary>
		/// <seealso cref="wclWiFiOperationMode" />
		wclWiFiOperationMode Mode;
		/// <summary> The flags set. </summary>
		unsigned long Flags;
		/// <summary> The PHY. </summary>
		/// <seealso cref="wclWiFiSnifferPhy" />
		wclWiFiSnifferPhy Phy;
		/// <summary> The channel number. </summary>
		unsigned char Channel;
		/// <summary> The central frequency in MHz. </summary>
		unsigned long Freq;
		/// <summary> The RSSI value in dBm. </summary>
		int Rssi;
		/// <summary> The data rate in Mbps. </summary>
		float Rate;
		/// <summary> The frame's timestamp. </summary>
		SYSTEMTIME Timestamp;
	} wclWiFiSnifferFrameMetaData;

	/// <summary> The <c>OnFrameReceived</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Meta"> The frame's meta data. </param>
	/// <param name="Buffer"> The pointer to the received frame data buffer.
	///   The pointer is valid only inside the event handler. </param>
	/// <param name="Size"> The received frame size. </param>
	/// <remarks> Please note, that the buffer pointed by the <c>Buffer</c>
	///   parameter is valid only inside the event handler. If an application
	///   needs to use the data outside the event handler it must copy data from
	///   the buffer pointed by the <c>Buffer</c> parameter into the internal
	///   application's buffer. </remarks>
	/// <seealso cref="wclWiFiSnifferFrameMetaData" />
	#define wclWiFiSnifferFrameReceived(_event_name_) \
		__event void _event_name_(void* Sender, const wclWiFiSnifferFrameMetaData& Meta, \
		const void* const Buffer, const unsigned long Size)
	/// <summary> The <c>OnRawFrameReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Buffer"> The pointer to the received frame data buffer.
	///   The pointer is valid only inside the event handler. </param>
	/// <param name="Size"> The received frame size. </param>
	/// <remarks> Please note, that the buffer pointed by the <c>Buffer</c>
	///   parameter is valid only inside the event handler. If an application
	///   needs to use the data outside the event handler it must copy data from
	///   the buffer pointed by the <c>Buffer</c> parameter into the internal
	///   application's buffer. </remarks>
	#define wclWiFiSnifferRawFrameReceived(_event_name_) \
		__event void _event_name_(void* Sender, const void* const Buffer, \
		const unsigned long Size)

	#ifndef GUID_NULL
		DEFINE_GUID(GUID_NULL, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	#endif

	/// <summary> The component allows your application to capture raw packets
	///   from your WiFi adapter. </summary>
	/// <remarks> <para> Please note, that not all WiFi adapters can capture the
	///   raw packets. To be able to do that your adapter must support Monitor
	///   Mode. </para>
	///   <para> The component requires Microsoft Network Monitor 3.4 filter
	///   driver to be installed on your system. You can download and install
	///   the Microsoft Network Monitor 3.4 by the following link:
	///   https://www.microsoft.com/en-us/download/details.aspx?id=4865 </para>
	///   <para> NOTE: The component is not thread-safe. </para> </remarks>
	class CwclWiFiSniffer
	{
		DISABLE_COPY(CwclWiFiSniffer);

	private:
		tstring						FDeviceName;
		bool						FDoNotChangeMode;
		HANDLE						FEngine;
		CwclWiFiInterface*			FIface;
		ULONG						FIndex; // Adapters index.
		wclMessageProcessingMethod	FMessageProcessing;
		wclWiFiOperationMode		FMode; // Old operation mode.
		CwclMessageReceiver*		FReceiver;

		static void __stdcall wclNmFrameCallback(HANDLE hCaptureEngine,
			ULONG ulAdapterIndex, void* pCallerContext, HANDLE hFrame);
		
		int SetupInterface(const GUID& Id);
		void DestroyInterface();
		
		int StartCapture();
		void StopCapture();
		
		void MessageReceived(const CwclMessage* const Message);
		
		// Frame parsing helpers.
		unsigned short ConvertChannelToFreq(const UINT32 Phy, const UINT32 Channel);
		wclWiFiOperationMode ConvertOperationMode(const UINT32 Mode);
		wclWiFiSnifferPhy ConvertPhy(const UINT32 Phy);

		void ParseFrame(const void* const Buffer, const unsigned long Size);

	protected:
		/// <summary> Fires the <c>AfterOpen</c> event. </summary>
		virtual void DoAfterOpen();
		/// <summary> Fires the <c>BeforeClose</c> event. </summary>
		virtual void DoBeforeClose();
		/// <summary> Fires the <c>OnFrameReceived</c> event. </summary>
		/// <param name="Meta"> The frame's meta data. </param>
		/// <param name="Buffer"> The pointer to the buffer with received
		///   frame. </param>
		/// <param name="Size"> The size of the received frame in bytes. </param>
		/// <remarks> The data (frame) buffer pointed by the <c>Buffer</c>
		///   parameter is valid only inside the procedure. </remarks>
		/// <seealso cref="wclWiFiSnifferFrameMetaData" />
		virtual void DoFrameReceived(const wclWiFiSnifferFrameMetaData& Meta,
			const void* const Buffer, const unsigned long Size);
		/// <summary> Fires the <c>OnRawFrameReceived</c> event. </summary>
		/// <param name="Buffer"> The pointer to the buffer with received
		///   frame. </param>
		/// <param name="Size"> The size of the received frame in bytes. </param>
		/// <remarks> The data (frame) buffer pointed by the <c>Buffer</c>
		///   parameter is valid only inside the procedure. </remarks>
		virtual void DoRawFrameReceived(const void* const Buffer, 
			const unsigned long Size);

	public:
		/// <summary> Creates a new WiFi Sniffer. </summary>
		CwclWiFiSniffer();
		/// <summary> Frees the Sniffer. </summary>
		virtual ~CwclWiFiSniffer();

		/// <summary> Stops capturing WiFi frames and closes the sniffer. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the sniffer and starts capturing WiFI frames. </summary>
		/// <param name="Id"> The WiFi interface ID that should be used for
		///   capturing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Open(const GUID& Id);
		
		/// <summary> Get the current channel. </summary>
		/// <param name="Channel"> On output the currently used channel. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetChannel(unsigned long& Channel) const;
		/// <summary> Gets the WiFi adapter current MAC address. </summary>
		/// <param name="Address"> On output the current MAC address of the WiFi
		///   adapter used for frame capturing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetMacAddr(__int64& Address) const;
		/// <summary> Gets the current adapter's PHY. </summary>
		/// <param name="Phy"> On output the currently used PHY. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiSnifferPhy" />
		int GetPhy(wclWiFiSnifferPhy& Phy) const;
		
		/// <summary> Sets the current channel. </summary>
		/// <param name="Channel"> The new RF channel number. </param>
		/// <remarks> Not all adapters allow to change the channel
		///   number. </remarks>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetChannel(const unsigned long Channel);
		/// <summary> Sets the current PHY. </summary>
		/// <param name="Phy"> The new PHY. </param>
		/// <remarks> Not all adapters allow to change the PHY. </remarks>
		/// <returns> If the function succeed the return value is
		///   <see cref="wclCommon::WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiSnifferPhy" />
		int SetPhy(const wclWiFiSnifferPhy Phy);

		/// <summary> Gets the sniffer's state. </summary>
		/// <returns> <c>True</c> if the sniffer is active. <c>False</c>
		///   otherwise. </returns>
		bool GetActive() const;
		/// <summary> Gets the sniffer's state. </summary>
		/// <value> <c>True</c> if the sniffer is active. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets the WiFi Interface ID. </summary>
		/// <returns> The WiFi Interface ID. </returns>
		GUID GetIfaceId() const;
		/// <summary> Gets the WiFi Interface ID. </summary>
		/// <value> The WiFi Interface ID. </value>
		__declspec(property(get = GetIfaceId)) GUID IfaceId;

		/// <summary> Gets the current WiFi interface mode. </summary>
		/// <returns> The WiFi interface operation mode. </returns>
		/// <seealso cref="wclWiFiOperationMode" />
		wclWiFiOperationMode GetMode() const;
		/// <summary> Gets the current WiFi interface mode. </summary>
		/// <value> The WiFi interface operation mode. </value>
		/// <seealso cref="wclWiFiOperationMode" />
		__declspec(property(get = GetMode)) wclWiFiOperationMode Mode;

		/// <summary> Gets the value controlled how the Sniffer will work
		///   with the WiFi hardware interface. </summary>
		/// <returns> The boolean controls how to work with the WiFi hardware
		///   interface. </returns>
		/// <remarks> <c>True</c> indicates that the automatically switch the given
		///   WiFi hardware interface to the monitoring mode is disable. </remarks>
		bool GetDoNotChangeMode() const;
		/// <summary> Sets the value controlled how the Sniffer will work
		///   with the WiFi hardware interface. </summary>
		/// <param name="Value"> The boolean controls how to work with the WiFi hardware
		///   interface. </param>
		/// <remarks> Set this property to <c>True</c> to disable automatically
		///   switch the given WiFi hardware interface to the monitoring mode.
		///   If this property is <c>False</c> (the default value) the Sniffer will
		///   try to switch the given WiFi hardware interface to the
		///   monitoring mode. </remarks>
		/// <exception cref="wclEWiFiSniffer"></exception>
		void SetDoNotChangeMode(const bool Value);
		/// <summary> Gets and sets the value controlled how the Sniffer will work
		///   with the WiFi hardware interface. </summary>
		/// <value> The boolean controls how to work with the WiFi hardware
		///   interface. </value>
		/// <remarks> Set this property to <c>True</c> to disable automatically
		///   switch the given WiFi hardware interface to the monitoring mode.
		///   If this property is <c>False</c> (the default value) the Sniffer will
		///   try to switch the given WiFi hardware interface to the
		///   monitoring mode. </remarks>
		/// <exception cref="wclEWiFiSniffer"></exception>
		__declspec(property(get = GetDoNotChangeMode, put = SetDoNotChangeMode))
			bool DoNotChangeMode;

		/// <summary> Gets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiSniffer"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiSniffer"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/// <summary> The event fires after the Sniffer was opened with
		///   success. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(AfterOpen);
		/// <summary> The event fires before the Sniffer will be closed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(BeforeClose);
		/// <summary> The event fires when a new frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Meta"> The frame's meta data. </param>
		/// <param name="Buffer"> The pointer to the received frame data buffer.
		///   The pointer is valid only inside the event handler. </param>
		/// <param name="Size"> The received frame size. </param>
		/// <remarks> Please note, that the buffer pointed by the <c>Buffer</c>
		///   parameter is valid only inside the event handler. If an application
		///   needs to use the data outside the event handler it must copy data from
		///   the buffer pointed by the <c>Buffer</c> parameter into the internal
		///   application's buffer. </remarks>
		/// <seealso cref="wclWiFiSnifferFrameMetaData" />
		wclWiFiSnifferFrameReceived(OnFrameReceived);
		/// <summary> The event fires when a new frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Buffer"> The pointer to the received frame data buffer.
		///   The pointer is valid only inside the event handler. </param>
		/// <param name="Size"> The received frame size. </param>
		/// <remarks> Please note, that the buffer pointed by the <c>Buffer</c>
		///   parameter is valid only inside the event handler. If an application
		///   needs to use the data outside the event handler it must copy data from
		///   the buffer pointed by the <c>Buffer</c> parameter into the internal
		///   application's buffer. </remarks>
		wclWiFiSnifferRawFrameReceived(OnRawFrameReceived);
	};

	/// <summary> Specifies a WiFi Direct configuration method. Configuration is
	///   how a user tells one piece of WiFi Direct equipment to connect to
	///   another piece of WiFi Direct equipment. </summary>
	typedef enum
	{
		/// <summary> This device accepts connections from devices that provide the
		///   PIN this device currently displays. </summary>
		cmDisplayPin,
		/// <summary> This device accepts entry of the PIN being displayed on the
		///   accepting device. </summary>
		cmProvidePin,
		/// <summary> This device uses the pushbutton method for pairing. A user
		///   pushes a button on both the connecting device and the accepting device
		///   in order to establish a connection between them. </summary>
		cmPushButton
	} wclWiFiDirectConfigurationMethod;
	/// <summary> Set of supported configuration methods. </summary>
	/// <seealso cref="wclWiFiDirectConfigurationMethod" />
	typedef std::set<wclWiFiDirectConfigurationMethod> wclWiFiDirectConfigurationMethods;

	/// <summary> Specifies whether the WiFi Direct device is listening and
	///   discoverable. </summary>
	typedef enum
	{
		/// <summary> The device is discoverable when the app is in the foreground
		///   or in the background. </summary>
		adIntensive,
		/// <summary> The device is not discoverable. </summary>
		adNone,
		/// <summary> The device is highly discoverable so long as the app is in
		///   the foreground. </summary>
		adNormal
	} wclWiFiDirectAdvertisementDiscoverability;

	/// <summary> Specifies a direct pairing procedure. </summary>
	/// <remarks> WiFi Direct supports two different pairing procedures. In the
	///   Group Owner Negotiation procedure, the connecting device chooses the
	///   configuration method (PIN entry, PIN display, or pushbutton pairing.) In
	///   the P2P Invitation procedure, the accepting device chooses the
	///   configuration method. Use the values in this enumeration to identify a
	///   pairing procedure. </remarks>
	typedef enum
	{
		/// <summary> Group Owner Negotiation. The connecting device chooses the
		///   configuration method. </summary>
		ppGroupOwnerNegotiation,
		/// <summary> P2P Invitation. The accepting device chooses the configuration
		///   method. </summary>
		ppInvitation
	} wclWiFiDirectPairingProcedure;

	/// <summary> Possible WiFi Direct device states. </summary>
	typedef enum
	{
		/// <summary> WiFi Direct device is disconnected. </summary>
		dsDisconnected,
		/// <summary> WiFi Direct device is connecting to a remote
		///   WiFi Direct device. </summary>
		dsConnecting,
		/// <summary> WiFi Direct device is connected. </summary>
		dsConnected,
		/// <summary> WiFi Direct device is disconnecting. </summary>
		dsDisconnecting
	} wclWiFiDirectDeviceState;

	// Forward declaration
	class CwclWiFiDirectAdvertiser;
	class CwclWiFiDirectClient;
	class CwclWiFiDirectConnectionRequestedEventHandler;
	class CwclWiFiDirectPairParams;

	/// <summary> The class represents a WiFi Direct device. </summary>
	/// <remarks> An application must not create or destroy objects of this class
	///   directly. </remarks>
	class CwclWiFiDirectDevice
	{
		DISABLE_COPY(CwclWiFiDirectDevice);
		
	private:
		friend class CwclWiFiDirectAdvertiser;
		friend class CwclWiFiDirectConnectionRequestedEventHandler;
		friend class CwclWiFiDirectClient;

		/* Device's properties. */
		
		tstring						FId;
		bool						FLegacy;
		tstring						FLocalAddress;
		tstring						FName;
		tstring						FRemoteAddress;
		wclWiFiDirectDeviceState	FState;
		tstring						FSystemDeviceId;
		
		/* Internal fields. */
		
		long						FReceiverId;
		LONG						FRefCount;

		/* WinRT WiFi Direct interfaces. */
		
		WlanApi::IWiFiDirectDevice*					FDevice;
		wclCommon::WinApi::EventRegistrationToken	FDeviceEvent;
		
		/* WinRT thread. */
		
		// Used to synchronize access to IWiFiDirectDevice object.
		RTL_CRITICAL_SECTION FCS;
		HANDLE	FTerminationEvent;
		HANDLE	FThread;
		
		/* Device property getters. */
		
		tstring GetAddress(const bool Local);
		void GetDeviceName(wclCommon::WinApi::IDeviceInformation* const Info);
		
		/* Device pairing. */
		
		void AddOrderedMethods(WlanApi::IWiFiDirectConnectionParameters2* const Params,
			const CwclWiFiDirectPairParams* const UserParams);
		int CreatePairingInterfaces(wclCommon::WinApi::IDeviceInformation* const Info,
			wclCommon::WinApi::IDeviceInformationPairing*& Pairing,
			wclCommon::WinApi::IDeviceInformationPairing2*& Pairing2);
		wclCommon::WinApi::DevicePairingKinds EncodePairingMethods(
			const CwclWiFiDirectPairParams* const UserParams);
		void NotifyPairCompleted(const wclCommon::WinApi::DevicePairingResultStatus Status);
		int Pair(wclCommon::WinApi::IDeviceInformation* const Info, bool& JustPaired);
		int SetPairingProcedure(WlanApi::IWiFiDirectConnectionParameters2* const Params,
			const CwclWiFiDirectPairParams* const UserParams);
		int SetupPairingParams(wclCommon::WinApi::DevicePairingKinds& Kind,
			WlanApi::IWiFiDirectConnectionParameters*& Params);
		void Unpair(wclCommon::WinApi::IDeviceInformation* const Info);
		int WaitPairing(wclCommon::WinApi::IDevicePairingResultAsyncOperation* const AsyncOper,
			wclCommon::WinApi::DevicePairingResultStatus& Status, bool& JustPaired);
		
		/* Device creation. */
		
		int CreateDevice(wclCommon::WinApi::IDeviceInformation* const Info);
		void DestroyDevice();
		
		/* Connection management. */
		
		int InternalConnect(wclCommon::WinApi::IDeviceInformation* const Info);
		int InternalConnect();
		void InternalDisconnect();
		void SendConnectedMessage(const int Res);
		
		/* Connection thread and connection event management. */
		
		int CreateTerminationEvent();
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();
		
		/* "Public" methods. */
		
		// Accepts incoming connection request.
		bool Accept(wclCommon::WinApi::IDeviceInformation* const Info);
		// Connect to WiFi Direct device with its Device Information object.
		int Connect(wclCommon::WinApi::IDeviceInformation* const Info);
		// Connects to WiFi Direct device with given ID.
		int Connect(const tstring& Id);
		
		/* Reference counting. */
		
		void AddRef();
		void Release();
		
	public:
		/// <summary> Creates new WiFi Direct device object. </summary>
		/// <param name="ReceiverId"> The message receiver ID. </param>
		/// <param name="Legacy"> The device's legacy mode. </param>
		/// <remarks> An application must not create or destroy objects of this
		///   class directly. </remarks>
		CwclWiFiDirectDevice(const long ReceiverId, const bool Legacy);
		/// <summary> Frees the WiFi Direct device object. </summary>
		/// <remarks> An application must not create or destroy objects of this
		///   class directly. </remarks>
		virtual ~CwclWiFiDirectDevice();
		
		/// <summary> Disconnects a WiFi Direct device. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();
		
		/// <summary> Gets the device's ID. </summary>
		/// <returns> The WiFi Direct device's ID. </returns>
		tstring GetId() const;
		/// <summary> Gets the device's ID. </summary>
		/// <value> The WiFi Direct device's ID. </value>
		__declspec(property(get = GetId)) tstring Id;
		
		/// <summary> gets the legacy setting. </summary>
		/// <returns> <c>True</c> if the device is legacy WiFi device. <c>False</c>
		///   if the device is WiFi Direct device. </returns>
		bool GetLegacy() const;
		/// <summary> gets the legacy setting. </summary>
		/// <value> <c>True</c> if the device is legacy WiFi device. <c>False</c>
		///   if the device is WiFi Direct device. </value>
		__declspec(property(get = GetLegacy)) bool Legacy;
		
		/// <summary> Gets the local IP address. </summary>
		/// <returns> The connection's local IPD address. </returns>
		tstring GetLocalAddress() const;
		/// <summary> Gets the local IP address. </summary>
		/// <value> The connection's local IPD address. </value>
		__declspec(property(get = GetLocalAddress)) tstring LocalAddress;
		
		/// <summary> Gets the device's name. </summary>
		/// <returns> The WiFi Direct device's name. </returns>
		tstring GetName() const;
		/// <summary> Gets the device's name. </summary>
		/// <value> The WiFi Direct device's name. </value>
		__declspec(property(get = GetName)) tstring Name;
		
		/// <summary> Gets the remote IP address. </summary>
		/// <returns> The connection's remote IP address. </returns>
		tstring GetRemoteAddress() const;
		/// <summary> Gets the remote IP address. </summary>
		/// <value> The connection's remote IP address. </value>
		__declspec(property(get = GetRemoteAddress)) tstring RemoteAddress;
		
		/// <summary> Gets the current device's state. </summary>
		/// <returns> The WiFi Direct device's state. </returns>
		/// <seealso cref="wclWiFiDirectDeviceState" />
		wclWiFiDirectDeviceState GetState() const;
		/// <summary> Gets the current device's state. </summary>
		/// <value> The WiFi Direct device's state. </value>
		/// <seealso cref="wclWiFiDirectDeviceState" />
		__declspec(property(get = GetState)) wclWiFiDirectDeviceState State;
		
		/// <summary> Gets the system device ID. </summary>
		/// <returns> The WiFi Direct system device ID. </returns>
		/// <remarks> The system device ID is how system detected the
		///  device. </remarks>
		tstring GetSystemDeviceId() const;
		/// <summary> Gets the system device ID. </summary>
		/// <value> The WiFi Direct system device ID. </value>
		/// <remarks> The system device ID is how system detected the
		///  device. </remarks>
		__declspec(property(get = GetSystemDeviceId)) tstring SystemDeviceId;
	};

	/// <summary> The base class for all WiFi Direct components. </summary>
	class CwclCustomWiFiDirectComponent
	{
		DISABLE_COPY(CwclCustomWiFiDirectComponent);
		
	private:
		HANDLE						FHandle; // WLAN handle.
		bool						FHardwareAvailable;
		wclMessageProcessingMethod	FMessageProcessing;
		CwclMessageReceiver*		FReceiver;

	protected:
		/// <summary> The method called when WiFi hardware has been switched off
		///   or removed. </summary>
		/// <remarks> A derived class must override this method to handle WiFi
		///   hardware changes. </remarks>
		virtual void HardwareRemoved();
		
		/// <summary> Initializes native WLAN subsystem. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int InitWlan();
		/// <summary> Uninitializes native WLAN subsystem. </summary>
		void UninitWlan();
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/// <summary> Gets the Hardware Available flag. </summary>
		/// <returns> <c>True</c> if Hardware is available. <c>False</c>
		///   otherwise. </returns>
		/// <remarks> This property is for internal use only. </remarks>
		bool GetHardwareAvailable() const;
		/// <summary> Gets the Hardware Available flag. </summary>
		/// <returns> <c>True</c> if Hardware is available. <c>False</c>
		///   otherwise. </returns>
		/// <remarks> This property is for internal use only. </remarks>
		__declspec(property(get = GetHardwareAvailable)) bool HardwareAvailable;

		/// <summary> Gets the message receiver object. </summary>
		/// <returns> The <see cref="CwclMessageReceiver" /> object used by the
		///   component. </returns>
		/// <seealso cref="CwclMessageReceiver" />
		CwclMessageReceiver* GetReceiver() const;
		/// <summary> Gets the message receiver object. </summary>
		/// <value> The <see cref="CwclMessageReceiver" /> object used by the
		///   component. </value>
		/// <seealso cref="CwclMessageReceiver" />
		__declspec(property(get = GetReceiver)) CwclMessageReceiver* Receiver;
		
	public:
		/// <summary> Creates a new WiFi Direct Advertiser component. </summary>
		CwclCustomWiFiDirectComponent();
		/// <summary> Frees the WiFi Direct Advertiser component. </summary>
		virtual ~CwclCustomWiFiDirectComponent();

		/// <summary> Gets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiDirect"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiDirect"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;
	};

	/// <summary> The WiFi Direct Advertiser's <c>OnAcceptDevice</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object that fired the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Accept"> An application must set this parameter to
	///   <c>True</c> to accept a connection request. If an application sets
	///   the parameter to <c>False</c> a connection request will be
	///   rejected. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectAcceptDeviceEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		bool& Accept)
	/// <summary> The WiFi Direct <c>OnConnected</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Error"> The connection result code. If the <c>Error</c>
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection has
	///   been established. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectConnectedEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		const int Error)
	/// <summary> The WiFi Direct <c>OnConnected</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Reason"> The disconnection reason. If the <c>Reason</c>
	///   is <see cref="WCL_E_SUCCESS" /> then the client disconnected
	///   by call the <c>Disconnect</c> method. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectDisconnectedEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		const int Reason)
	/// <summary> The WiFi Direct <c>OnPairCompleted</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Result"> The pairing result code. If pairing completed
	///   with success the <c>Result</c> is <see cref="WCL_E_SUCCESS" />. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectPairCompletedEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		const int Result)
	/// <summary> The WiFi Direct <c>OnPairConfirm</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Confirm"> An application must set this parameter to
	///   <c>True</c> to confirm paring. To reject pairing an application
	///   must set this parameter to <c>False</c>. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectPairConfirmEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		bool& Confirm)
	/// <summary> The WiFi Direct <c>OnPairDisplayPin</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Pin"> The PIN code to display. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectPairDisplayPinEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		const tstring& Pin)
	/// <summary> The WiFi Direct <c>OnPairGetParams</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="GroupOwnerIntent"> The group owner intent value provided by
	///   the application and used for group owner negotiation in a WiFi Direct
	///   pairing operation. </param>
	/// <param name="ConfigurationMethods"> Supported pairing (configuration)
	///   methods provided by the application that should be used during
	///   pairing. </param>
	/// <param name="PairingProcedure"> The supported pairing procedure provided
	///   by the application to be used during pairing. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	/// <seealso cref="wclWiFiDirectConfigurationMethods" />
	/// <seealso cref="wclWiFiDirectPairingProcedure" />
	#define wclWiFiDirectPairGetParamsEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		short& GroupOwnerIntent, wclWiFiDirectConfigurationMethods& ConfigurationMethods, \
		wclWiFiDirectPairingProcedure& PairingProcedure)
	/// <summary> The WiFi Direct <c>OnPairProvidePin</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Pin"> An application must provide PIN for pairing. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectPairProvidePinEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		tstring& Pin)

	/// <summary> The base class for WiFi Direct connection components. </summary>
	/// <seealso cref="CwclCustomWiFiDirectComponent" />
	class CwclWiFiDirectConnectionComponent : public CwclCustomWiFiDirectComponent
	{
	protected:
		/// <summary> Gets device object by its ID. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <returns> If the device with given ID was found the function returns
		///   the <see cref="CwclWiFiDirectDevice" /> object. Otherwise the function
		///   returns <c>NULL</c>. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual CwclWiFiDirectDevice* FindDevice(const tstring& Id) const = 0;
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnDeviceConnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Error"> The connection result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection has
		///   been established. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceConnected(CwclWiFiDirectDevice* const Device, 
			const int Error);
		/// <summary> Fires the <c>OnDeviceDisconnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Reason"> The disconnection reason. If the <c>Reason</c>
		///   is <see cref="WCL_E_SUCCESS" /> then the client disconnected
		///   by call the <c>Disconnect</c> method. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceDisconnected(CwclWiFiDirectDevice* const Device, 
			const int Reason);
		/// <summary> Fires the <c>OnPairComplete</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Result"> The pairing result code. If pairing completed
		///   with success the <c>Result</c> is
		///   <see cref="WCL_E_SUCCESS" />. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoPairCompleted(CwclWiFiDirectDevice* const Device, 
			const int Result);
		/// <summary> Fires the <c>OnPairConfirm</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm paring. To reject pairing an application
		///   must set this parameter to <c>False</c>. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoPairConfirm(CwclWiFiDirectDevice* const Device, bool& Confirm);
		/// <summary> Fires the <c>OnPairDisplayPin</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Pin"> The PIN code to display. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoPairDisplayPin(CwclWiFiDirectDevice* const Device,
			const tstring& Pin);
		/// <summary> Fires the <c>OnPairGetParams</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="GroupOwnerIntent"> The group owner intent value provided by
		///   the application and used for group owner negotiation in a WiFi Direct
		///   pairing operation. </param>
		/// <param name="ConfigurationMethods"> Supported pairing (configuration)
		///   methods provided by the application that should be used during
		///   pairing. </param>
		/// <param name="PairingProcedure"> The supported pairing procedure provided
		///   by the application to be used during pairing. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		/// <seealso cref="wclWiFiDirectConfigurationMethods" />
		/// <seealso cref="wclWiFiDirectPairingProcedure" />
		virtual void DoPairGetParams(CwclWiFiDirectDevice* const Device, 
			short& GroupOwnerIntent, wclWiFiDirectConfigurationMethods& ConfigurationMethods, 
			wclWiFiDirectPairingProcedure& PairingProcedure);
		/// <summary> Fires the <c>OnPairProvidePin</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Pin"> An application must provide PIN for pairing. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoPairProvidePin(CwclWiFiDirectDevice* const Device, 
			tstring& Pin);
		
	public:
		/// <summary> Creates a new WiFi Direct Advertiser component. </summary>
		CwclWiFiDirectConnectionComponent();
		
		/// <summary> The event fires when a remote WiFi enabled device has been
		///   connected to the WiFi Direct Advertiser. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Error"> The connection result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection has
		///   been established. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectConnectedEvent(OnDeviceConnected);
		/// <summary> The event fires when the remote WiFi enabled device has been
		///   disconnected from the WiFi Direct Advertiser. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Reason"> The disconnection reason. If the <c>Reason</c>
		///   is <see cref="WCL_E_SUCCESS" /> then the client disconnected
		///   by call the <c>Disconnect</c> method. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectDisconnectedEvent(OnDeviceDisconnected);
		/// <summary> The event fires when pairing with a remote WiFi enabled device
		///   has been completed (with or without success). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Result"> The pairing result code. If pairing completed
		///   with success the <c>Result</c> is <see cref="WCL_E_SUCCESS" />. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectPairCompletedEvent(OnPairCompleted);
		/// <summary> The event fires when a remote WiFi enabled device requests
		///   simple pairing confirmation. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm paring. To reject pairing an application
		///   must set this parameter to <c>False</c>. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectPairConfirmEvent(OnPairConfirm);
		/// <summary> The event fires when a remote WiFi enabled device requests the
		///   Display Pin pairing procedure. An application must show the
		///   Pin received from the event. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Pin"> The PIN code to display. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectPairDisplayPinEvent(OnPairDisplayPin);
		/// <summary> The event fires when pairing parameters need to be
		///   set. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="GroupOwnerIntent"> The group owner intent value provided by
		///   the application and used for group owner negotiation in a WiFi Direct
		///   pairing operation. </param>
		/// <param name="ConfigurationMethods"> Supported pairing (configuration)
		///   methods provided by the application that should be used during
		///   pairing. </param>
		/// <param name="PairingProcedure"> The supported pairing procedure provided
		///   by the application to be used during pairing. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		/// <seealso cref="wclWiFiDirectConfigurationMethods" />
		/// <seealso cref="wclWiFiDirectPairingProcedure" />
		wclWiFiDirectPairGetParamsEvent(OnPairGetParams);
		/// <summary> The event fires when a remote WiFi enabled device requests Pin
		///   for pairing. An application must provide Pin. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Pin"> An application must provide PIN for pairing. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectPairProvidePinEvent(OnPairProvidePin);
	};

	/// <summary> The class allows to publish WiFi Direct advertisements. </summary>
	/// <remarks> <para> Windows 10, version 1607, supports Mobile HotSpot, an
	///   enhanced version of the mobile broadband tethering feature. If Mobile
	///   HotSpot is running, the functionality of this class is not supported.
	///   It is likely to stop working. </para>
	///   <para> The Mobile HotSpot and WiFi Direct technology cannot run at the
	///   same time. Mobile HotSpot takes precedence over all WiFi Direct
	///   scenarios. </para> </remarks>
	/// <seealso cref="CwclWiFiDirectConnectionComponent" />
	class CwclWiFiDirectAdvertiser : public CwclWiFiDirectConnectionComponent
	{
		DISABLE_COPY(CwclWiFiDirectAdvertiser);
		
	private:
		typedef std::list<CwclWiFiDirectDevice*> LIST;

		LIST*										FDevices; // Connected devices list.
		HANDLE										FMutex; // Indicates that WFD advertiser is running.
		HANDLE										FStatusEvent; // Used in Status Changed event handler.
		wclCommon::WinApi::EventRegistrationToken	FEventToken;

		/* WinRT thread fields. */
		
		HANDLE	FThread; // WinRT thread.
		HANDLE	FThreadInitEvent; // Thread initialization event.
		HANDLE	FThreadTermEvent;  // Thread termination event.
		int		FThreadResult; // Thread initialization result.
		
		/* WiFi Direct interfaces. */
		
		WlanApi::IWiFiDirectAdvertisement* FAdvertisement;
		WlanApi::IWiFiDirectConnectionListener*		FConnectionListener;
		WlanApi::IWiFiDirectLegacySettings*			FLegacySettings;
		WlanApi::IWiFiDirectAdvertisementPublisher*	FPublisher;
		wclCommon::WinApi::EventRegistrationToken	FConnectionRequestEventToken;
		
		/* Properties. */
		
		bool										FAutonomousGroupOwnerEnabled;
		wclWiFiDirectAdvertisementDiscoverability	FDiscoverability;
		bool										FLegacy;
		bool										FOpenAuth;
		tstring										FPassphrase;
		tstring										FSsid;
		
		/* Helper functions. */
		
		int SetupAdvertisement();
		int SetupLegacySettings();
		
		int StartPublisher();
		void StopPublisher();
		
		int StartListener();
		void StopListener();

		// Checks is Mobile HotSpot is running.
		int IsHotspotRunning() const;
		// Checks is x32 app runs on x64 platform.
		bool IsWow64() const;
		
		/* WinRT thread. */
		
		// Working thread procedure.
		// We need this separate working thread because WinRT is based on COM
		// so any previous WinRT or COM or even OLE initialization may cause
		// problems with WinRT initialization for multi threading.
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();
		// The thread checks if a Mobile HotSpot is running on this PC.
		// Param is a pointer to Boolean value that receives True if Mobile HotSpot
		// is running.
		static UINT __stdcall IsMobileHotspotRunningThread(LPVOID lpParam);
		
	protected:
		/// <summary> The method called when WiFi hardware has been switched off
		///   or removed. </summary>
		virtual void HardwareRemoved() override;
		
		/// <summary> Gets device object by its ID. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <returns> If the device with given ID was found the function returns
		///   the <see cref="CwclWiFiDirectDevice" /> object. Otherwise the function
		///   returns <c>NULL</c>. </returns>
		virtual CwclWiFiDirectDevice* FindDevice(const tstring& Id) const override;
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnAcceptDevice</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Accept"> An application must set this parameter to
		///   <c>True</c> to accept a connection request. If an application sets
		///   the parameter to <c>False</c> a connection request will be
		///   rejected. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoAcceptDevice(CwclWiFiDirectDevice* const Device, bool& Accept);
		/// <summary> Fires the <c>OnDeviceConnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Error"> The connection result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection has
		///   been established. </param>
		/// <remarks> A derived class must always call the inherited method
		///   if this one is override. </remarks>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceConnected(CwclWiFiDirectDevice* const Device, 
			const int Error) override;
		/// <summary> Fires the <c>OnDeviceDisconnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Reason"> The disconnection reason. If the <c>Reason</c>
		///   is <see cref="WCL_E_SUCCESS" /> then the client disconnected
		///   by call the <c>Disconnect</c> method. </param>
		/// <remarks> A derived class must always call the inherited method
		///   if this one is override. </remarks>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceDisconnected(CwclWiFiDirectDevice* const Device, 
			const int Reason) override;
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		
	public:
		/// <summary> Creates a new WiFi Direct Advertiser component. </summary>
		CwclWiFiDirectAdvertiser();
		/// <summary> Frees the WiFi Direct Advertiser component. </summary>
		virtual ~CwclWiFiDirectAdvertiser();
		
		/// <summary> Starts the WiFi Direct Advertisement. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start();
		/// <summary> Stops the WiFi Direct Advertisement. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Gets the WiFi Direct Advertiser state. </summary>
		/// <returns> <c>True</c> if advertising is running. <c>False</c> if
		///   advertising is not running. </returns>
		bool GetActive() const;
		/// <summary> Gets the WiFi Direct Advertiser state. </summary>
		/// <value> <c>True</c> if advertising is running. <c>False</c> if
		///   advertising is not running. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets connected devices number. </summary>
		/// <returns> Number of connected WiFi Direct enabled devices. </returns>
		size_t GetCount() const;
		/// <summary> Gets connected devices number. </summary>
		/// <value> Number of connected WiFi Direct enabled devices. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets connected device. </summary>
		/// <param name="Index"> A connected devices' index. </param>
		/// <returns> The WiFi Direct Device object. If device with given index was
		///   not found the value is <c>NULL</c>. </returns>
		/// <seealso cref="CwclWiFiDirectDevice" />
		CwclWiFiDirectDevice* GetDevices(const size_t Index) const;
		/// <summary> Gets connected device. </summary>
		/// <value> The WiFi Direct Device object. If device with given index was
		///   not found the value is <c>NULL</c>. </value>
		/// <seealso cref="CwclWiFiDirectDevice" />
		__declspec(property(get = GetDevices)) CwclWiFiDirectDevice* Devices[];
		
		/// <summary> Gets the autonomous group owner state. </summary>
		/// <returns> <c>True</c> if the autonomous group owner enabled.
		///   <c>False</c> otherwise. </returns>
		/// <remarks> <para> If the Advertiser is not running reading the property returns
		///   its default value. </para>
		///   <para> If the Advertiser is running reading the property returns
		///   current value used by the Advertiser. </para> </remarks>
		bool GetAutonomousGroupOwnerEnabled() const;
		/// <summary> Sets the autonomous group owner state. </summary>
		/// <param name="value"> <c>True</c> if the autonomous group owner enabled.
		///   <c>False</c> otherwise. </param>
		/// <remarks> <para> If the Advertiser is not running settings this property
		///   to <c>False</c> will also set the <c>Legacy</c> property to
		///   <c>False</c>. </para>
		///   <para> If the Advertiser is running setting this property does
		///   nothing and new value will be ignored. </para> </remarks>
		void SetAutonomousGroupOwnerEnabled(const bool value);
		/// <summary> Gets and sets the autonomous group owner state. </summary>
		/// <value> <c>True</c> if the autonomous group owner enabled.
		///   <c>False</c> otherwise. </value>
		/// <remarks> <para> If the Advertiser is not running settings this property
		///   to <c>False</c> will also set the <c>Legacy</c> property to
		///   <c>False</c>. Reading the property returns its default value. </para>
		///   <para> If the Advertiser is running setting this property does
		///   nothing and new value will be ignored. Reading the property returns
		///   current value used by the Advertiser. </para> </remarks>
		__declspec(property(get = GetAutonomousGroupOwnerEnabled,
			put = SetAutonomousGroupOwnerEnabled)) bool AutonomousGroupOwnerEnabled;
		
		/// <summary> Gets the listen state and whether the WiFi Direct
		///   device is discoverable. </summary>
		/// <returns> The listen state and whether the WiFi Direct device
		///   is discoverable. </returns>
		/// <remarks> <para> If the Advertiser is not running reading the property
		///   returns its current value. </para>
		///   <para> If the Advertiser is running reading the property returns current
		///   value used by the Advertiser. </para> </remarks>
		/// <seealso cref="wclWiFiDirectAdvertisementDiscoverability" />
		wclWiFiDirectAdvertisementDiscoverability GetDiscoverability() const;
		/// <summary> Sets the listen state and whether the WiFi Direct
		///   device is discoverable. </summary>
		/// <param name="value"> The listen state and whether the WiFi Direct device
		///   is discoverable. </param>
		/// <remarks> <para> If the Advertiser is not running setting the property
		///   changes its value. </para>
		///   <para> If the Advertiser is running setting the property does nothing
		///   and new value will be ignored. </para> </remarks>
		/// <seealso cref="wclWiFiDirectAdvertisementDiscoverability" />
		void SetDiscoverability(const wclWiFiDirectAdvertisementDiscoverability value);
		/// <summary> Gets and sets the listen state and whether the WiFi Direct
		///   device is discoverable. </summary>
		/// <value> The listen state and whether the WiFi Direct device
		///   is discoverable. </value>
		/// <remarks> <para> If the Advertiser is not running setting the property
		///   changes its value. Reading the property returns its current
		///   value. </para>
		///   <para> If the Advertiser is running setting the property does nothing
		///   and new value will be ignored. Reading the property returns current
		///   value used by the Advertiser. </para> </remarks>
		/// <seealso cref="wclWiFiDirectAdvertisementDiscoverability" />
		__declspec(property(get = GetDiscoverability, put = SetDiscoverability))
			wclWiFiDirectAdvertisementDiscoverability Discoverability;
		
		/// <summary> Gets the WiFi Direct Advertiser legacy node state. </summary>
		/// <returns> The current Legacy state of the WiFi Direct
		///   Advertiser. </returns>
		/// <remarks> <para> This property is used only if the
		///   <c>AutonomousGroupOwnerEnabled</c> is set to <c>True</c>. If the
		///   <c>AutonomousGroupOwnerEnabled</c> is <c>False</c> this property is
		///   always <c>False</c> and changing its value to <c>True</c> will not
		///   take effect. </para>
		///   <para> If the Advertiser is not running reading the property returns its current
		///   value. </para>
		///   <para> If the Advertiser is running reading the property returns its value
		///   used by the Advertiser. </para> </remarks>
		bool GetLegacy() const;
		/// <summary> Sets the WiFi Direct Advertiser legacy node
		///   state. </summary>
		/// <param name="value"> The current Legacy state of the WiFi Direct
		///   Advertiser. </param>
		/// <remarks> <para> This property is used only if the
		///   <c>AutonomousGroupOwnerEnabled</c> is set to <c>True</c>. If the
		///   <c>AutonomousGroupOwnerEnabled</c> is <c>False</c> this property is
		///   always <c>False</c> and changing its value to <c>True</c> will not
		///   take effect. </para>
		///   <para> If the Advertiser is not running setting this property changes
		///   its current value. </para>
		///   <para> If the Advertiser is running changing the property does nothing
		///   and new value will be ignored. </para> </remarks>
		void SetLegacy(const bool value);
		/// <summary> Gets and sets the WiFi Direct Advertiser legacy node
		///   state. </summary>
		/// <value> The current Legacy state of the WiFi Direct
		///   Advertiser. </value>
		/// <remarks> <para> This property is used only if the
		///   <c>AutonomousGroupOwnerEnabled</c> is set to <c>True</c>. If the
		///   <c>AutonomousGroupOwnerEnabled</c> is <c>False</c> this property is
		///   always <c>False</c> and changing its value to <c>True</c> will not
		///   take effect. </para>
		///   <para> If the Advertiser is not running setting this property changes
		///   its current value. Reading the property returns its current
		///   value. </para>
		///   <para> If the Advertiser is running changing the property does nothing
		///   and new value will be ignored. Reading the property returns its value
		///   used by the Advertiser. </para> </remarks>
		__declspec(property(get = GetLegacy, put = SetLegacy)) bool Legacy;
		
		/// <summary> Gets the Open Network flag. </summary>
		/// <returns> A flag that turns Open Network mode on or off. </returns>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> Windows 10 and Windows 10 Mobile can be configured to allow
		///   embedded mode, which allows a device to run a single app. If embedded
		///   mode is configured, the pass phrase can be empty to support Open/None
		///   Authentication. </para>
		///   <para> Instead of settings the <c>Passphrase</c> property to an
		///   empty string an application must set <c>OpenAuth</c> property to
		///   <c>True</c> to turn Open Authentication On. Or set the
		///   <c>OpenAuth</c> to <c>False</c> to switch to common authentication
		///   mode. </para>
		///   <para> If the Advertiser is running setting the property does nothing
		///   and new value will be ignored. Reading the property returns current
		///   value used by the Advertiser. </para>
		///   <para> Not all WiFi adapters may support this feature on
		///   Windows. </para> </remarks>
		bool GetOpenAuth() const;
		/// <summary> Sets the Open Network flag. </summary>
		/// <param name="value"> A flag that turns Open Network mode on or off. </param>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> Windows 10 and Windows 10 Mobile can be configured to allow
		///   embedded mode, which allows a device to run a single app. If embedded
		///   mode is configured, the pass phrase can be empty to support Open/None
		///   Authentication. </para>
		///   <para> Instead of settings the <c>Passphrase</c> property to an
		///   empty string an application must set <c>OpenAuth</c> property to
		///   <c>True</c> to turn Open Authentication On. Or set the
		///   <c>OpenAuth</c> to <c>False</c> to switch to common authentication
		///   mode. </para>
		///   <para> If the Advertiser is running setting the property does nothing
		///   and new value will be ignored. Reading the property returns current
		///   value used by the Advertiser. </para>
		///   <para> Not all WiFi adapters may support this feature on
		///   Windows. </para> </remarks>
		void SetOpenAuth(const bool value);
		/// <summary> Gets and sets the Open Network flag. </summary>
		/// <value> A flag that turns Open Network mode on or off. </value>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> Windows 10 and Windows 10 Mobile can be configured to allow
		///   embedded mode, which allows a device to run a single app. If embedded
		///   mode is configured, the pass phrase can be empty to support Open/None
		///   Authentication. </para>
		///   <para> Instead of settings the <c>Passphrase</c> property to an
		///   empty string an application must set <c>OpenAuth</c> property to
		///   <c>True</c> to turn Open Authentication On. Or set the
		///   <c>OpenAuth</c> to <c>False</c> to switch to common authentication
		///   mode. </para>
		///   <para> If the Advertiser is running setting the property does nothing
		///   and new value will be ignored. Reading the property returns current
		///   value used by the Advertiser. </para>
		///   <para> Not all WiFi adapters may support this feature on
		///   Windows. </para> </remarks>
		__declspec(property(get = GetOpenAuth, put = SetOpenAuth)) bool OpenAuth;

		/// <summary> Gets the pass phrase for Legacy mode. </summary>
		/// <returns> A pass phrase used by non-WiFi Direct clients
		///   to connect to this access point in "legacy mode". </returns>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> If the Advertiser is not running reading the property returns its current
		///   value. </para>
		///   <para> If the Advertiser is running and the <c>Legacy</c> is
		///   <c>True</c> reading the property returns its current value used
		///   by the Advertiser. If the value of the property was an empty string
		///   reading from the property returns auto generated random pass phrase
		///   used by the Advertiser. If the <c>Legacy</c> is <c>False</c> reading
		///   returns an empty string. </para> </remarks>
		tstring GetPassphrase() const;
		/// <summary> Sets the pass phrase for Legacy mode. </summary>
		/// <param name="value"> A pass phrase used by non-WiFi Direct clients
		///   to connect to this access point in "legacy mode". </param>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> If the Advertiser is not running setting the property
		///   changes it current value. </para>
		///   <para> If the Advertiser is running settings the property does
		///   nothing and new value will be ignored. </para> </remarks>
		void SetPassphrase(const tstring& value);
		/// <summary> Gets and sets the pass phrase for Legacy mode. </summary>
		/// <value> A pass phrase used by non-WiFi Direct clients
		///   to connect to this access point in "legacy mode". </value>
		/// <remarks> <para> This property is used only if <c>Legacy</c> mode
		///   set to <c>True</c>. If the <c>Legacy</c> is <c>False</c> the value
		///   of the property will not be used. </para>
		///   <para> If the Advertiser is not running setting the property
		///   changes it current value. Reading the property returns its current
		///   value. </para>
		///   <para> If the Advertiser is running settings the property does
		///   nothing and new value will be ignored. If the <c>Legacy</c> is
		///   <c>True</c> reading the property returns its current value used
		///   by the Advertiser. If the value of the property was an empty string
		///   reading from the property returns auto generated random pass phrase
		///   used by the Advertiser. If the <c>Legacy</c> is <c>False</c> reading
		///   returns an empty string. </para> </remarks>
		__declspec(property(get = GetPassphrase, put = SetPassphrase)) tstring Passphrase;
		
		/// <summary> Gets the Service Set Identifier (SSID). </summary>
		/// <returns> A WiFi Direct Advertiser SSID. </returns>
		/// <remarks> <para> This property used in both Legacy and non-Legacy
		///   modes. In Legacy mode it is the SoftAP SSID. In non-Legacy mode it
		///   is used as device name. </para>
		///   <para> If the Advertiser is running reading the property returns its
		///   current value used by the Advertiser. If the property was an empty
		///   string reading returns the auto generated SSID (device name) that
		///   begins with "DIRECT-". </para>
		///   <para> If the Advertiser is not running reading the property returns its current
		///   value. </para> </remarks>
		tstring GetSsid() const;
		/// <summary> Sets the Service Set Identifier (SSID). </summary>
		/// <param name="value"> A WiFi Direct Advertiser SSID. </param>
		/// <remarks> <para> This property used in both Legacy and non-Legacy
		///   modes. In Legacy mode it is the SoftAP SSID. In non-Legacy mode it
		///   is used as device name. </para>
		///   <para> If the Advertiser is running setting this property does nothing
		///   and new value will be ignored. </para>
		///   <para> If the Advertiser is not running setting the property changes
		///   its value. </para> </remarks>
		void SetSsid(const tstring& value);
		/// <summary> Gets and sets the Service Set Identifier (SSID). </summary>
		/// <value> A WiFi Direct Advertiser SSID. </value>
		/// <remarks> <para> This property used in both Legacy and non-Legacy
		///   modes. In Legacy mode it is the SoftAP SSID. In non-Legacy mode it
		///   is used as device name. </para>
		///   <para> If the Advertiser is running setting this property does nothing
		///   and new value will be ignored. Reading the property returns its
		///   current value used by the Advertiser. If the property was an empty
		///   string reading returns the auto generated SSID (device name) that
		///   begins with "DIRECT-". </para>
		///   <para> If the Advertiser is not running setting the property changes
		///   its value. Reading the property returns its current
		///   value. </para> </remarks>
		__declspec(property(get = GetSsid, put = SetSsid)) tstring Ssid;

		/// <summary> The event fires when a remote WiFi enable device connects to
		///   the WiFi Direct Advertiser and an application must accept or reject
		///   the connection request. </summary>
		/// <param name="Sender"> The object that fired the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Accept"> An application must set this parameter to
		///   <c>True</c> to accept a connection request. If an application sets
		///   the parameter to <c>False</c> a connection request will be
		///   rejected. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectAcceptDeviceEvent(OnAcceptDevice);
		/// <summary> The event fires when the WiFi Direct Advertiser has been
		///   started with success. </summary>
		/// <param name="Sender"> The object that fired the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the WiFi Direct Advertiser has been
		///   stopped. </summary>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The WiFi Direct SoftAP <c>OnDeviceAccept</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Accept"> An application must set this to <c>false</c> to
	///   reject connection request. Setting it to <c>true</c> (the default value)
	///   accepts connection. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectSoftAPAcceptEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		bool& Accept)
	/// <summary> The WiFi Direct SoftAP <c>OnDeviceConnected</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectSoftAPConnectedEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device)
	/// <summary> The WiFi Direct SoftAP <c>OnDeviceConnectError</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <param name="Error"> The connection error code. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectSoftAPConnectErrorEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device, \
		const int Error)
	/// <summary> The WiFi Direct SoftAP <c>OnDeviceDisconnected</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The WiFi Direct device object. </param>
	/// <seealso cref="CwclWiFiDirectDevice" />
	#define wclWiFiDirectSoftAPDisconnectedEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclWiFiDirectDevice* const Device)

	/// <summary> The component represents the WiFi Direct Legacy Soft AP. </summary>
	/// <remarks> <para> An application can use the <c>TwclWiFiSoftAP</c>
	///   component if needs to run Hosted Network (Legacy Soft AP) on a WiFi
	///   adapter that does not support Native WiFi Hosted network features and
	///   supports only WiFi Direct features. </para>
	///   <para> On other adapters that supports Native WiFi Hosted Network it is
	///   recommended to use the <see cref="CwclWiFiHostedNetwork" /> component
	///   instead. </para> </remarks>
	/// <seealso cref="CwclWiFiHostedNetwork" />
	class CwclWiFiSoftAP
	{
		DISABLE_COPY(CwclWiFiSoftAP);

	private:
		typedef std::list<tstring> LIST;

		CwclWiFiDirectAdvertiser*	FAdvertiser;
		LIST*						FAcceptedDevices;
		// WFD Virtual Adapter interface ID.
		GUID						FId;
		
		/* Events. */
		
		void DeviceAccept(void* Sender, CwclWiFiDirectDevice* const Device, 
			bool& Accept);
		void DeviceConnected(void* Sender, CwclWiFiDirectDevice* const Device, 
			const int Error);
		void DeviceDisconnected(void* Sender, CwclWiFiDirectDevice* const Device, 
			const int Reason);
		void Started(void* Sender);
		void Stopped(void* Sender);
		
	protected:
		/// <summary> Fires the <c>OnDeviceAccept</c> event. </summary>
		/// <param name="Device"> A <see cref="CwclWiFiDirectDevice" /> object
		///   represents remote WiFi Direct enabled device. </param>
		/// <param name="Accept"> An application must set this to <c>false</c> to
		///   reject connection request. Setting it to <c>true</c> (the default
		///   value) accepts connection. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceAccept(CwclWiFiDirectDevice* const Device, bool& Accept);
		/// <summary> Fires the <c>OnDeviceConnected</c> event. </summary>
		/// <param name="Device"> A <see cref="CwclWiFiDirectDevice" /> object
		///   represents remote WiFi Direct enabled device. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceConnected(CwclWiFiDirectDevice* const Device);
		/// <summary> Fires the <c>OnDeviceConnectError</c> event. </summary>
		/// <param name="Device"> A <see cref="CwclWiFiDirectDevice" /> object
		///   represents remote WiFi Direct enabled device. </param>
		/// <param name="Error"> A connection error code. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceConnectError(CwclWiFiDirectDevice* const Device, 
			const int Error);
		/// <summary> Fires the <c>OnDeviceDisconnected</c> event. </summary>
		/// <param name="Device"> A <see cref="CwclWiFiDirectDevice" /> object
		///   represents remote WiFi Direct enabled device. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceDisconnected(CwclWiFiDirectDevice* const Device);
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		
	public:
		/// <summary> Creates a new WiFi Soft AP component. </summary>
		CwclWiFiSoftAP();
		/// <summary> Frees the component. </summary>
		virtual ~CwclWiFiSoftAP();
		
		/// <summary> Starts the WiFi Direct Legacy Soft AP. </summary>
		/// <param name="Ssid"> The Soft AP SSID. If the parameter is an empty
		///   string the auto generated SSID will be used. An application can read
		///   the current SSID of the Soft AP by calling <c>GetSsid</c>
		///   method. </param>
		/// <param name="Passphrase"> The Soft AP passphrase. if the parameter is an
		///   empty string the auto generated random passphrase will be
		///   used. An application ca read the current Passphrase of the Soft AP by
		///   calling <c>GetPassphrase</c> method. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start(const tstring& Ssid, const tstring& Passphrase);
		/// <summary> Starts the WiFi Direct Legacy Soft AP in Open Authentication
		///   (Open Network) mode. </summary>
		/// <param name="Ssid"> The Soft AP SSID. If the parameter is an empty
		///   string the auto generated SSID will be used. An application can read
		///   the current SSID of the Soft AP by calling <c>GetSsid</c>
		///   method. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start(const tstring& Ssid);
		/// <summary> Stops the WiFi Direct Legacy Soft AP. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Reads the Soft AP passphrase. </summary>
		/// <param name="Passphrase"> If the function succeed on output contains
		///   the running Soft AP passphrase. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetPassphrase(tstring& Passphrase) const;
		/// <summary> Reads the Soft AP SSID. </summary>
		/// <param name="Ssid"> If the function succeed on output contains the
		///   running Soft AP SSID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetSsid(tstring& Ssid) const;
		
		/// <summary> Gets current IP settings. </summary>
		/// <param name="Address"> The current IP address. </param>
		/// <param name="Mask"> The subnet mask. </param>
		/// <param name="Gateway"> The default gateway address. </param>
		/// <param name="Dns1"> The first DNS server address. </param>
		/// <param name="Dns2"> The second DNS server address. </param>
		/// <remarks> If the method returns
		///   <c>WCL_E_WIFI_INTERFACE_IP_NOT_CONFIGURED</c> then the interface uses
		///   system default settings. </remarks>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetIpSettings(tstring& Address, tstring& Mask, tstring& Gateway,
			tstring& Dns1, tstring& Dns2) const;
		/// <summary> Sets current IP settings. </summary>
		/// <param name="Address"> The current IP address. </param>
		/// <param name="Mask"> The subnet mask. </param>
		/// <param name="Gateway"> The default gateway address. </param>
		/// <param name="Dns1"> The first DNS server address. </param>
		/// <param name="Dns2"> The second DNS server address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetIpSettings(const tstring& Address, const tstring& Mask, const tstring& Gateway, 
			const tstring& Dns1, const tstring& Dns2);
		/// <summary> Resets IP settings to its system default values. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int ResetIpSettings();
		
		/// <summary> Gets the Soft AP status. </summary>
		/// <returns> <c>True</c> if the Soft AP is running. <c>False</c>
		///   otherwise. </returns>
		bool GetActive() const;
		/// <summary> Gets the Soft AP status. </summary>
		/// <value> <c>True</c> if the Soft AP is running. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiDirect"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Events. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiDirect"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/// <summary> The event fires when new device is trying to connected to the
		///   WiFI Direct Soft AP. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Accept"> An application must set this to <c>false</c> to
		///   reject connection request. Setting it to <c>true</c> (the default value)
		///   accepts connection. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectSoftAPAcceptEvent(OnDeviceAccept);
		/// <summary> The event fires when new device is connected to the WiFI
		///   Direct Soft AP. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectSoftAPConnectedEvent(OnDeviceConnected);
		/// <summary> The event fires when new device is connected to the WiFI
		///   Direct Soft AP. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Error"> A connection error code. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectSoftAPConnectErrorEvent(OnDeviceConnectError);
		/// <summary> The event fires when the WiFi Direct device is disconnected
		///   from the WiFI Direct Soft AP. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		wclWiFiDirectSoftAPDisconnectedEvent(OnDeviceDisconnected);
		/// <summary> The event fires when the Soft AP has been started with
		///   success. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Soft AP has been stopped. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The <c>OnDeviceFound</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> The ID of the remote WiFi Direct device. </param>
	/// <param name="Name"> The name of the remote WiFi Direct device. </param>
	#define wclWiFiDirectDeviceFoundEvent(_event_name_) \
		__event void _event_name_(void* Sender, const tstring& Id, const tstring& Name)
	/// <summary> The <c>OnDiscovringCompleted</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Error"> The discovering result code. If the <c>Error</c>
	///   parameter is <see cref="WCL_E_SUCCESS" /> the discovering completed with
	///   success. </param>
	#define wclWiFiDirectDiscoveringCompletedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error)

	/// <summary> The type represents a paired WiFi Direct devices list. </summary>
	typedef std::list<tstring>	WCL_WFD_DEVICES;

	/// <summary> The component allows you application to enumerate (discover)
	///   nearby WiFi Direct Devices, </summary>
	/// <seealso cref="CwclCustomWiFiDirectComponent" />
	class CwclWiFiDirectDeviceWatcher : public CwclCustomWiFiDirectComponent
	{
		DISABLE_COPY(CwclWiFiDirectDeviceWatcher);

	private:
		HANDLE				FThread;
		HANDLE				FThreadEvent;
		HANDLE				FThreadInitEvent;
		int					FThreadResult;
		tstring				FDeviceId;
		bool				FPaired;
		WCL_WFD_DEVICES*	FPairedDevices;

		int CanExecuteOperation();

		int CreatePairingInterface(const tstring& Id, wclCommon::WinApi::IDeviceInformationPairing** Pairing);
		
		// Sets discovering thread initialization result and signals the initialization event.
		void SetThreadInitResult(int Res);
		// Discovering thread.
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();

		void Terminate(int Error);

		// These 2 threads used to check device's pairing state and to unpair paired
		// device.
		static UINT __stdcall _GetPairedThreadProc(LPVOID lpParam);
		static UINT __stdcall _UnpairThreadProc(LPVOID lpParam);
		void GetPairedThreadProc();
		void UnpairThreadProc();

		// Enumerates paired devices.
		static UINT __stdcall _EnumPairedDevicesThread(LPVOID lpParam);
		void EnumPairedDevicesThreadProc();
		
	protected:
		/// <summary> The method called when WiFi hardware has been switched off
		///   or removed. </summary>
		virtual void HardwareRemoved() override;
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnDeviceFound</c> event. </summary>
		/// <param name="Id"> The ID of the remote WiFi Direct device. </param>
		/// <param name="Name"> The name of the remote WiFi Direct device. </param>
		virtual void DoDeviceFound(const tstring& Id, const tstring& Name);
		/// <summary> Fires the <c>OnDiscoveringCompleted</c> event. </summary>
		/// <param name="Error"> The discovering result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the discovering completed
		///		with success. </param>
		virtual void DoDiscoveringCompleted(const int Error);
		/// <summary> Fires the <c>OnDiscoveringStarted</c> event. </summary>
		virtual void DoDiscoveringStarted();
		
	public:
		/// <summary> Creates a new WiFi Device Watcher component. </summary>
		CwclWiFiDirectDeviceWatcher();
		
		/// <summary> Starts discovering for nearby WiFi Direct devices. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Discover();
		/// <summary> Terminates discovering for nearby WiFi Direct
		///   devices. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Terminate();
		
		/// <summary> Gets The WiFi Direct device's pairing status. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <param name="Paired"> If the method completed with success on output
		///   contains information about WiFi Direct pairing status. <c>True</c> if
		///   the WiFi Direct device is paired. <c>False</c> otherwise. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int IsPaired(const tstring& Id, bool& Paired);
		/// <summary> Unpair a WiFi  Direct device. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Unpair(const tstring& Id);
		/// <summary> Enumerates paired WiFi Direct devices. </summary>
		/// <param name="Devices"> The StringList object that will be filled with
		///   found paired WiFi Direct devices IDs. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A called is responsible to create the <c>Devices</c>
		///   StringList object before calling the method and to destroy it after
		///   usage. The <c>Devices</c> list will be cleared before filled with
		///   found devices IDs. </remarks>
		/// <seealso cref="WCL_WFD_DEVICES" />
		int EnumPairedDevices(const WCL_WFD_DEVICES* const Devices);
		
		/// <summary> Gets discovering state of the component. </summary>
		/// <returns> The current discovering state. <c>True</c> if the discovering
		///   for nearby WiFi Direct devices is active. </returns>
		bool GetDiscovering() const;
		/// <summary> Gets discovering state of the component. </summary>
		/// <value> The current discovering state. <c>True</c> if the discovering
		///   for nearby WiFi Direct devices is active. </value>
		__declspec(property(get = GetDiscovering)) bool Discovering;

		/// <summary> The event fires when a nearby WiFi Direct device has
		///   been found. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> The ID of the remote WiFi Direct device. </param>
		/// <param name="Name"> The name of the remote WiFi Direct device. </param>
		wclWiFiDirectDeviceFoundEvent(OnDeviceFound);
		/// <summary> The event fires when discovering for nearby WiFi Direct
		///   devices has been completed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Error"> The discovering result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the discovering completed with
		///   success. </param>
		wclWiFiDirectDiscoveringCompletedEvent(OnDiscoveringCompleted);
		/// <summary> The event fires when discovering for nearby WiFi Direct
		///   devices has been started. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnDiscoveringStarted);
	};

	/// <summary> The WiFi Direct Client allows to connect to other WiFi Direct
	///   devices. </summary>
	/// <seealso cref="CwclWiFiDirectConnectionComponent" />
	class CwclWiFiDirectClient : public CwclWiFiDirectConnectionComponent
	{
		DISABLE_COPY(CwclWiFiDirectClient);
		
	private:
		CwclWiFiDirectDevice*	FDevice;
		
	protected:
		/// <summary> The method called when WiFi hardware has been switched off
		///   or removed. </summary>
		virtual void HardwareRemoved() override;
		
		/// <summary> Gets device object by its ID. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <returns> If the device with given ID was found the function returns
		///   the <see cref="CwclWiFiDirectDevice" /> object. Otherwise the function
		///   returns <c>NULL</c>. </returns>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual CwclWiFiDirectDevice* FindDevice(const tstring& Id) const override;
		
		/// <summary> Fires the <c>OnDeviceConnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Error"> The connection result code. If the <c>Error</c>
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection has
		///   been established. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceConnected(CwclWiFiDirectDevice* const Device, 
			const int Error) override;
		/// <summary> Fires the <c>OnDeviceDisconnected</c> event. </summary>
		/// <param name="Device"> The WiFi Direct device object. </param>
		/// <param name="Reason"> The disconnection reason. If the <c>Reason</c>
		///   is <see cref="WCL_E_SUCCESS" /> then the client disconnected
		///   by call the <c>Disconnect</c> method. </param>
		/// <seealso cref="CwclWiFiDirectDevice" />
		virtual void DoDeviceDisconnected(CwclWiFiDirectDevice* const Device, 
			const int Reason) override;
		
	public:
		/// <summary> Creates a new WiFi Direct Client component. </summary>
		CwclWiFiDirectClient();
		
		/// <summary> Connect to remote WiFi Direct device. </summary>
		/// <param name="Id"> The WiFi Direct device's ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect(const tstring& Id);
		/// <summary> Disconnect from the connected remote WiFi Direct
		///   device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();
		
		/// <summary> Gets local IP address for the connection. </summary>
		/// <returns> The connection's local IP address. </returns>
		tstring GetLocalAddress() const;
		/// <summary> Gets local IP address for the connection. </summary>
		/// <value> The connection's local IP address. </value>
		__declspec(property(get = GetLocalAddress)) tstring LocalAddress;

		/// <summary> Gets remote IP address for the connection. </summary>
		/// <returns> The connection's remote IP address. </returns>
		tstring GetRemoteAddress() const;
		/// <summary> Gets remote IP address for the connection. </summary>
		/// <value> The connection's remote IP address. </value>
		__declspec(property(get = GetRemoteAddress)) tstring RemoteAddress;

		/// <summary> Gets a client state. </summary>
		/// <returns> The current client's state. </returns>
		/// <seealso cref="wclWiFiDirectDeviceState" />
		wclWiFiDirectDeviceState GetState() const;
		/// <summary> Gets a client state. </summary>
		/// <value> The current client's state. </value>
		/// <seealso cref="wclWiFiDirectDeviceState" />
		__declspec(property(get = GetState)) wclWiFiDirectDeviceState State;
	};

	/// <summary> Enumeration represents a Mobile HotSpot states. </summary>
	typedef enum
	{
		/// <summary> Current state is unknown. </summary>
		mhsUnknown,
		/// <summary> Mobile HotSpot is up and running. </summary>
		mhsOn,
		/// <summary> Mobile HotSpot if turned off. </summary>
		mhsOff,
		/// <summary> The Mobile HotSpot is currently in transition between the
		///   <c>On</c> and <c>Off</c> states. </summary>
		mhsInTransition
	} wclMobileHotspotState;

	/// <summary> Defines constants that specify a wireless frequency band for a
	///   WiFi adapter used as Mobile HotSpot. </summary>
	typedef enum
	{
		/// <summary> Specifies that the WiFi adapter is free to choose any band per
		///   internal logic. </summary>
		mhbAuto,
		/// <summary> Specifies that the WiFi adapter uses only the 2.4 GHz
		///   band. </summary>
		mhbTwoPointFourGigahertz,
		/// <summary> Specifies that the WiFi adapter uses only the 5 GHz
		///   band. </summary>
		mhbFiveGigahertz
	} wclMobileHotspotBand;

	/// <summary> Represents a Mobile HotSpot connected client. </summary>
	typedef struct
	{
		/// <summary> The connected client's MAC address. </summary>
		tstring Mac;
		/// <summary> The host name. </summary>
		tstring Name;
	} wclMobileHotspotClient;
	/// <summary> Array of Mobile HotSpot connected clients. </summary>
	/// <seealso cref="wclMobileHotspotClient" />
	typedef std::list<wclMobileHotspotClient> wclMobileHotspotClients;

	/// <summary> The class allows to control Mobile HotSpot feature on Windows 10
	///   platform. </summary>
	class CwclMobileHotspot
	{
		DISABLE_COPY(CwclMobileHotspot);
		
	private:
		WlanApi::INetworkOperatorTetheringManager* FManager;
		
		HANDLE	FThread;
		HANDLE	FThreadInitEvent;
		int		FThreadInitResult;
		HANDLE	FThreadTermEvent;
		
		int StatusToError(const WlanApi::TetheringOperationStatus Status) const;
		
		int GetApConfig(WlanApi::INetworkOperatorTetheringAccessPointConfiguration** Config) const;
		int SetApConfig(WlanApi::INetworkOperatorTetheringAccessPointConfiguration* Config);
		
		int CreateStatics4(WlanApi::INetworkOperatorTetheringManagerStatics4** Statics);
		
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();
		
	protected:
		/// <summary> Fires the <c>OnClosed</c> event. </summary>
		virtual void DoClosed();
		/// <summary> Fires the <c>OnOpened</c> event. </summary>
		virtual void DoOpened();
		
	public:
		/// <summary> Creates a Mobile HotSpot component. </summary>
		CwclMobileHotspot();
		/// <summary> Frees the component. </summary>
		virtual ~CwclMobileHotspot();
		
		/// <summary> Closes the Mobile HotSpot API and uninitializes the
		///   component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method does not change current Mobile HotSpot state.
		///   The method simple releases the Mobile HotSpot API. </remarks>
		int Close();
		/// <summary> Opens the Mobile HotSpot API and initializes the
		///   component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method does not change current Mobile HotSpot state.
		///   The method simple initializes the Mobile HotSpot API. </remarks>
		int Open();
		
		/// <summary> Starts the Mobile HotSpot. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start();
		/// <summary> Stops the Mobile HotSpot. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Gets the current Mobile HotSpot state. </summary>
		/// <param name="State"> If the function completed with success on output
		///   the parameter contains the current Mobile HotSpot state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclMobileHotspotState" />
		int GetState(wclMobileHotspotState& State) const;
		
		/// <summary> Gets the AP SSID. </summary>
		/// <param name="Ssid"> If the method completed with success on output
		///   contains the current SSID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetSsid(tstring& Ssid) const;
		/// <summary> Sets the AP SSID. </summary>
		/// <param name="Ssid"> The new SSID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetSsid(const tstring& Ssid);
		
		/// <summary> Gets the AP passphrase. </summary>
		/// <param name="Passphrase"> If the method completed with success on output
		///   contains the current passphrase. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetPassphrase(tstring& Passphrase) const;
		/// <summary> Sets the AP passphrase. </summary>
		/// <param name="Passphrase"> The new passphrase. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetPassphrase(const tstring& Passphrase);
		
		/// <summary> Checks whether the WiFi Mobile HotSpot supports the specified
		///   wireless frequency band. </summary>
		/// <param name="Band"> A <see cref="wclMobileHotspotBand" /> constant,
		///   specifying the frequency band to query about. </param>
		/// <param name="Supported"> If the function completed with success
		///   on output contains a Boolean indicates if specified band is supported
		///   or not. <c>True</c> if the frequency band is supported, otherwise
		///   <c>False</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> For single band WiFi adapter this method may returns
		///   <c>False</c> for both bands. </para>
		///   <para> This feature is supported on Windows 10 2004 and
		///   above. </para> </remarks>
		/// <see cref="wclMobileHotspotBand" />
		int IsBandSupported(const wclMobileHotspotBand Band, bool& Supported) const;
		/// <summary> Gets the wireless frequency band of the WiFi Mobile
		///   HotSpot. </summary>
		/// <param name="Band"> If the function completed with success on output
		///   contain a <see cref="wclMobileHotspotBand" /> constant,
		///   specifying the current frequency band. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 2004 and
		///   above. </remarks>
		/// <see cref="wclMobileHotspotBand" />
		int GetBand(wclMobileHotspotBand& Band) const;
		/// <summary> Sets the wireless frequency band of the WiFi Mobile
		///   HotSpot. Use <c>IsBandSupported</c> to check whether the WiFi
		///   adapter allows configuring a specific frequency band. </summary>
		/// <param name="Band"> A <see cref="wclMobileHotspotBand" /> constant,
		///   specifying the frequency band. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 2004 and
		///   above. </remarks>
		/// <see cref="wclMobileHotspotBand" />
		int SetBand(const wclMobileHotspotBand Band);

		/// <summary> Gets the maximum number of client connections over a
		///   Mobile HotSpot. </summary>
		/// <param name="Count"> If the method completed with success on output
		///   contains the maximum number of client connections. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetMaxClientCount(unsigned long& Count) const;
		/// <summary> Gets the current number of connected clients on the Mobile
		///   HotSpot. </summary>
		/// <param name="Count"> If the method completed with success on output
		///   contains the current number of connected clients. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetClientCount(unsigned long& Count) const;
		/// <summary> Gets the list of connected clients. </summary>
		/// <param name="Clients"> If the function completed with success on output
		///   contains the array for currently connected clients. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclMobileHotspotClients" />
		int GetClients(wclMobileHotspotClients& Clients) const;
		
		/// <summary> Gets a value indicating whether the NoConnections timeout is
		///   enabled. If enabled, Mobile HotSpot turns off automatically in 5
		///   minutes after the last peer of the tethering connection goes
		///   away. </summary>
		/// <param name="Enabled"> If the method completed with success on output
		///   contains a Boolean indicates current NoConnectionTimeout state.
		///   <c>True</c> if the NoConnections timeout is enabled, otherwise
		///   <c>False</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 2004 and
		///   above. </remarks>
		int IsNoConnectionsTimeoutEnabled(bool& Enabled);
		/// <summary> Disables the NoConnections timeout. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 2004 and
		///   above. </remarks>
		int DisableNoConnectionsTimeout();
		/// <summary> Enables the NoConnections timeout. This means that Mobile
		///   HotSpot turns off automatically in 5 minutes after the last peer of
		///   the tethering connection goes away. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 2004 and
		///   above. </remarks>
		int EnableNoConnectionsTimeout();
		
		/// <summary> Gets the Mobile HotSpot component state. </summary>
		/// <returns> Returns <c>True</c> if the Mobile HotSpot component is
		///   opened. </returns>
		/// <remarks> This property does not indicate the real status of the
		///   Mobile HotSpot on this system. To get Mobile HotSpot state use
		///   <c>GetState</c> method. </remarks>
		bool GetActive() const;
		/// <summary> Gets the Mobile HotSpot component state. </summary>
		/// <value> Returns <c>True</c> if the Mobile HotSpot component is
		///   opened. </value>
		/// <remarks> This property does not indicate the real status of the
		///   Mobile HotSpot on this system. To get Mobile HotSpot state use
		///   <c>GetState</c> method. </remarks>
		__declspec(property(get = GetActive)) bool Active;
		
		/// <summary> The event fires when the Mobile HotSpot has been
		///   closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnClosed);
		/// <summary> The event fires when the Mobile HotSpot has been
		///   opened. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnOpened);
	};

	/// <summary> The class adds Drone Remote ID information element parsing
	///   methods. </summary>
	/// <seealso cref="CwclWiFiInformationElementParser" />
	class CwclWiFiDriParser : public CwclWiFiInformationElementParser
	{
		DISABLE_COPY(CwclWiFiDriParser);

	private:
		CwclDriAsdParser*	FAsdParser;

		unsigned long GetOui(const wclWiFiInformationElement& Element) const;
		bool IsDriIe(const wclWiFiInformationElement& Element) const;

		int ExtractDriElements(const wclWiFiIeRawData& Raw,
			wclWiFiInformationElements& Elements) const;
		
	public:
		/// <summary> Creates new parser object. </summary>
		CwclWiFiDriParser();
		/// <summary> Frees the object. </summary>
		virtual ~CwclWiFiDriParser();

		/// <summary> Extracts DRI messages from BSS information elements. </summary>
		/// <param name="Bss"> The WiFi BSS data. </param>
		/// <param name="Messages"> If the method completed with success on output
		///   contains the DRI messages list. An application is responsible to free
		///   the returned list. If no one DRI message found the returning value
		///   is the empty list. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiBss" />
		/// <seealso cref="wclWiFiDriMessages" />
		int ParseDriMessages(const wclWiFiBss& Bss, wclDriMessages& Messages) const;
		/// <summary> Extracts DRI messages from information elements raw
		///   data. </summary>
		/// <param name="Raw"> The IE raw data. </param>
		/// <param name="Messages"> If the method completed with success on output
		///   contains the DRI messages list. An application is responsible to free
		///   the returned list. If no one DRI message found the returning value
		///   is the empty list. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiFiIeRawData" />
		/// <seealso cref="wclWiFiDriMessages" />
		int ParseDriMessages(const wclWiFiIeRawData& Raw, wclDriMessages& Messages) const;
	};
}
