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

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "wclWiFiErrors.h"

/// <summary> This macro helps to build correct documentation. </summary>
#define _WCL_WIFI_NLMAPI_INCLUDE_FILE_ "wclNlmAPI.h"
#include _WCL_WIFI_NLMAPI_INCLUDE_FILE_

namespace wclWiFi
{
	/// <summary> The <c>wclNlmConnectivity</c> enumeration describes the network
	///   connectivity of this machine. </summary>
	typedef enum
	{
		/// <summary> The underlying network interfaces have no connectivity to any
		///   network. </summary>
		nlmDisconnected,
		/// <summary> There is connectivity to a network, but the service cannot
		///   detect any IPv4 Network Traffic. </summary>
		nlmIPv4NoTraffic,
		/// <summary> There is connectivity to a network, but the service cannot
		///   detect any IPv6 Network Traffic. </summary>
		nlmIPv6NoTraffic,
		/// <summary> There is connectivity to the local subnet using the IPv4
		///   protocol. </summary>
		nlmIPv4Subnet,
		/// <summary> There is connectivity to a routed network using the IPv4
		///   protocol. </summary>
		nlmIPv4LocalNetwork,
		/// <summary> There is connectivity to the Internet using the IPv4
		///   protocol. </summary>
		nlmIPv4Internet,
		/// <summary> There is connectivity to the local subnet using the IPv6
		///   protocol. </summary>
		nlmIPv6Subnet,
		/// <summary> There is connectivity to a local network using the IPv6
		///   protocol. </summary>
		nlmIPv6LocalNetwork,
		/// <summary> There is connectivity to the Internet using the IPv6
		///   protocol. </summary>
		nlmIPv6Internet
	} wclNlmConnectivity;
	/// <summary> The <c>wclNlmConnectivityFlags</c> is the set of flags
	///   that contains information about the machine connectivity. </summary>
	/// <seealso cref="wclNlmConnectivity" />
	typedef std::set<wclNlmConnectivity> wclNlmConnectivityFlags;

	/// <summary> The enumeration defines changes made to the properties of a
	///   network. </summary>
	typedef enum
	{
		/// <summary> A connection to this network has been added or
		///   removed. </summary>
		nlmNetworkChangeConnection,
		/// <summary> The description of the network has changed. </summary>
		nlmNetworkChangeDescription,
		/// <summary> The name of the network has changed. </summary>
		nlmNetworkChangeName,
		/// <summary> The icon of the network has changed. </summary>
		nlmNetworkChangeIcon,
		/// <summary> The category of the network has changed. </summary>
		nlmNetworkChangeCategoryValue
	} wclNlmNetworkPropertyChange;
	/// <summary> The <c>wclNlmNetworkPropertyChangeFlags</c> is the set of flags
	///   that define changes made to the properties of a network. </summary>
	/// <seealso cref="wclNlmNetworkPropertyChange" />
	typedef std::set<wclNlmNetworkPropertyChange> wclNlmNetworkPropertyChangeFlags;

	/// <summary> The enumeration is a set of flags that specify the category
	///   type of a network. </summary>
	/// <remarks> The private or public network categories must never be used to
	///   assume which Windows Firewall ports are open, as the user can change the
	///   default settings of these categories. Instead, Firewall APIs should be
	///   called to ensure the ports that the required ports are open. </remarks>
	typedef enum
	{
		/// <summary> The network is a public (untrusted) network.  </summary>
		nlmCategoryPublic,
		/// <summary> The network is a private (trusted) network.  </summary>
		nlmCategoryPrivate,
		/// <summary> The network is authenticated against an Active Directory
		///   domain. </summary>
		nlmCategoryDomainAuthenticated
	} wclNlmNetworkCategory;

	/// <summary> The enumeration is a set of flags that specify the domain type
	///   of a network. </summary>
	typedef enum
	{
		/// <summary> The Network is not an Active Directory Network. </summary>
		nlmNonDomainNetwork,
		/// <summary> The Network is an Active Directory Network, but this machine
		///   is not authenticated against it. </summary>
		nlmDomainNetwork,
		/// <summary> The Network is an Active Directory Network, and this machine
		///   is authenticated against it. </summary>
		nlmDomainAuthenticated
	} wclNlmDomainType;

	/// <summary> The enumeration is a set of flags that define changes made to
	///   the properties of a network connection. </summary>
	typedef enum
	{
		/// <summary> The Authentication (Domain Type) of this Network Connection
		///   has changed. </summary>
		nlmAuthentication
	} wclNlmConnectionProperty;

	// Forward declaration makes help generator happy.
	class CwclNetworkListManager;
	class CwclNlmNetwork;

	/// <summary> The class represents a single network connection. </summary>
	/// <remarks> An application must never create objects of this class
	///   directly Instead an application must use the <c>GetConnections</c>
	///   method of the <see cref="CwclNetworkListManager" /> component or
	///   <see cref="CwclNlmNetwork" /> class. </remarks>
	class CwclNlmConnection
	{
		DISABLE_COPY(CwclNlmConnection);

	private:
		NlmApi::INetworkConnection*	FConnection;

	public:
		/// <summary> Creates a new Connection object. </summary>
		/// <param name="Connection"> The INetworkConnection interface
		///   pointer. </param>
		/// <remarks> An application must never create objects of this class
		///   directly Instead an application must use the <c>GetConnections</c>
		///   method of the <see cref="CwclNetworkListManager" /> component or
		///   <see cref="CwclNlmNetwork" /> class. </remarks>
		CwclNlmConnection(NlmApi::INetworkConnection* const Connection);
		/// <summary> Frees the network class. </summary>
		virtual ~CwclNlmConnection();
		
		/// <summary> Reads the ID of the network adapter used by this
		///   connection. </summary>
		/// <param name="Id"> On output contains a GUID that specifies the adapter
		///   ID of the TCP/IP interface used by this network connection. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetAdapterId(GUID& Id) const;
		/// <summary> Checks if the associated network connection has network
		///   connectivity. </summary>
		/// <param name="Connected"> On output if <c>True</c>, this network
		///   connection has connectivity; if <c>False</c>, it does not. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnected(bool& Connected) const;
		/// <summary> Checks if the associated network connection has Internet
		///   connectivity. </summary>
		/// <param name="Connected"> On output if <c>True</c>, this network
		///   connection has connectivity to the Internet; if <c>False</c>,
		///   it does not. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnectedToInternet(bool& Connected) const;
		/// <summary> Reads the connectivity state of the network
		///   connection. </summary>
		/// <param name="Connectivity"> On output contains the connectivity of this
		///   network connection. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmConnectivityFlags" />
		int GetConnectivity(wclNlmConnectivityFlags& Connectivity) const;
		/// <summary> Reads the domain type of the network connection. </summary>
		/// <param name="DomainType"> On output contains the domain type of the
		///   network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmDomainType" />
		int GetDomainType(wclNlmDomainType& DomainType) const;
		/// <summary> Reads the Connection ID associated with this network
		///   connection. </summary>
		/// <param name="Id"> On output contains a GUID that specifies the
		///   Connection ID associated with this network connection. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetId(GUID& Id) const;
		/// <summary> Gets the network associated with the connection. </summary>
		/// <param name="Network"> If the method succeeded on output contains the
		///   <see cref="CwclNlmNetwork" /> object that represents the network
		///   associated with the connection. An application is responsible to
		///   dispose the returned object. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclNlmNetwork" />
		int GetNetwork(CwclNlmNetwork*& Network) const;
	};

	/// <summary> The connections array. </summary>
	/// <remarks> An application is responsible to free the objects of the
	///   <see cref="CwclNlmConnection" /> class from the array. </remarks>
	/// <seealso cref="CwclNlmConnection" />
	typedef std::vector<CwclNlmConnection*> wclNlmConnections;

	/// <summary> The class represents a network on the local machine. It can
	///   also represent a collection of network connections with a similar
	///   network signature. </summary>
	/// <remarks> An application must never create this class directly.
	///   Instead of that an application must use <c>GetNetwork</c> or
	///   <c>GetNetworks</c> methods of the <see cref="CwclNetworkListManager" />
	///   component. </remarks>
	class CwclNlmNetwork
	{
		DISABLE_COPY(CwclNlmNetwork);

	private:
		NlmApi::INetwork*	FNetwork;
		
	public:
		/// <summary> Creates a new Network object. </summary>
		/// <param name="Network"> The INetwork interface pointer. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use <c>GetNetwork</c> or
		///   <c>GetNetworks</c> methods of the
		///   <see cref="CwclNetworkListManager" /> component. </remarks>
		CwclNlmNetwork(NlmApi::INetwork* const Network);
		/// <summary> Frees the network class. </summary>
		virtual ~CwclNlmNetwork();
		
		/// <summary> Reads the category of the network. </summary>
		/// <param name="Category"> On output specifies the category information
		///   for the network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The private or public network categories must never be used to
		///   assume which Windows Firewall ports are open, as the user can change
		///   the default settings of these categories. Instead, Windows Firewall
		///   APIs should be called to ensure the ports that the required ports
		///   are open. </remarks>
		/// <seealso cref="wclNlmNetworkCategory" />
		int GetCategory(wclNlmNetworkCategory& Category) const;
		/// <summary> Checks  if the network has any network
		///   connectivity. </summary>
		/// <param name="Connected"> <para> If the method succeeded on output
		///   returns the network connectivity state. </para>
		///   <para> If the <c>Connected</c> is <c>True</c>, the network has at
		///   least local connectivity via ipv4 or ipv6 or both. The network may
		///   also have Internet connectivity. Thus, the network is
		///   connected. </para>
		///   <para> If the <c>Connected</c> is <c>False</c>, the network does not
		///   have local or Internet connectivity. The network is not
		///   connected. </para> </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnected(bool& Connected) const;
		/// <summary> Checks if the network has Internet connectivity. </summary>
		/// <param name="Connected"> <para> If the method succeeded on output
		///   returns the Internet connectivity state. </para>
		///   <para> If the <c>Connected</c> is <c>True</c>, the network is
		///   connected to the Internet; if the <c>Connected</c> is <c>False</c>, it
		///   is not. </para> </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnectedToInternet(bool& Connected) const;
		/// <summary> The method returns an enumeration of all network connections
		///   for a network. A network can have multiple connections to it from
		///   different interfaces or different links from the same
		///   interface. </summary>
		/// <param name="Connections"> On output contains all network connections
		///   on the machine. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmConnections" />
		int GetConnections(wclNlmConnections& Connections) const;
		/// <summary> Reads the connectivity state of the network. </summary>
		/// <param name="Connectivity"> On output contains a set that specifies the
		///   connectivity state of this network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmConnectivityFlags" />
		int GetConnectivity(wclNlmConnectivityFlags& Connectivity) const;
		/// <summary> Reads the description string for the network. </summary>
		/// <param name="Description"> On output contains a string that specifies
		///   the text description of the network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetDescription(tstring& Description) const;
		/// <summary> Reads the domain type of a network. </summary>
		/// <param name="DomainType"> On output contains the value that specifies
		///   the domain type of the network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmDomainType" />
		int GetDomainType(wclNlmDomainType& DomainType) const;
		/// <summary> Reads the name of a network. </summary>
		/// <param name="Name"> On output contains the name of the network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetName(tstring& Name) const;
		/// <summary> Reads the unique identifier of a network. </summary>
		/// <param name="Id"> On output contains the network ID. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetNetworkId(GUID& Id) const;
		/// <summary> Reads the local date and time when the network was created
		///   and connected. </summary>
		/// <param name="Created"> On output contains a date and time when the network
		///   was created. </param>
		/// <param name="Connected"> On output contains a date and time when the network
		///   was last connected to. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetTimeCreatedAndConnected(SYSTEMTIME& Created, SYSTEMTIME& Connected) const;
		
		/// <summary> Sets the category of a network. Changes made take effect
		///   immediately. Administrative privileges are needed for this
		///   method. </summary>
		/// <param name="Category"> Specifies the new category of the
		///   network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmNetworkCategory" />
		int SetCategory(const wclNlmNetworkCategory Category);
		/// <summary> Sets or replaces the description for a network. </summary>
		/// <param name="Description"> Contains a string that contains the
		///   description of the network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetDescription(const tstring& Description);
		/// <summary> Sets or renames a network. </summary>
		/// <param name="Name"> A string that contains the new name of the
		///   network. </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetName(const tstring& Name);
	};

	/// <summary> The dynamic array contains the list of networks. </summary>
	/// <remarks> An application is responsible to free the objects of the
	///   <see cref="CwclNlmNetwork" /> class from the array. </remarks>
	/// <seealso cref="CwclNlmNetwork" />
	typedef std::vector<CwclNlmNetwork*> wclNlmNetworks;


	/// <summary> The enumeration contains a set of flags that specify what
	///   types of networks are enumerated. </summary>
	typedef enum
	{
		/// <summary> Returns connected networks. </summary>
		nlmEnumConnected,
		/// <summary> Returns disconnected networks. </summary>
		nlmEnumDisconnected,
		/// <summary> Returns connected and disconnected networks. </summary>
		nlmEnumAll
	} wclNlmEnumNetwork;

	/// <summary> The <c>OnConnectivityChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Connectivity"> The new connectivity settings of the
	///   machine. </param>
	/// <seealso cref="wclNlmConnectivityFlags" />
	#define wclNlmConnectivityChangeEvent(_event_name_) \
		__event void _event_name_(void* Sender, \
		const wclNlmConnectivityFlags& Connectivity)

	/// <summary> The <c>OnNetworkConnectivityChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="NetworkId"> A GUID that specifies the network. </param>
	/// <param name="Connectivity"> The new connectivity settings of the
	///   machine. </param>
	/// <seealso cref="wclNlmConnectivityFlags" />
	#define wclNlmNetworkConnectivityChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& NetworkId, \
		const wclNlmConnectivityFlags& Connectivity)
	/// <summary> The network event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="NetworkId"> A GUID that specifies the network. </param>
	#define wclNlmNetworkEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& NetworkId)
	/// <summary> The <c>OnNetworkPropertyChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="NetworkId"> A GUID that specifies the network. </param>
	/// <param name="Change"> The value that specifies the network property
	///   that changed. </param>
	/// <seealso cref="wclNlmNetworkPropertyChangeFlags" />
	#define wclNlmNetworkPropertyChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& NetworkId, \
		const wclNlmNetworkPropertyChangeFlags& Change)

	/// <summary> The <c>OnConnectionConnectivityChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="ConnectionId"> A GUID that identifies the network connection
	///   on which the event occurred. </param>
	/// <param name="Connectivity"> The new connectivity settings of the
	///   connection. </param>
	/// <seealso cref="wclNlmConnectivityFlags" />
	#define wclNlmConnectionConnectivityChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& ConnectionId, \
		const wclNlmConnectivityFlags& Connectivity)
	/// <summary> The <c>OnConnectionPropertyChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="ConnectionId"> A GUID that identifies the network connection
	///   on which the event occurred. </param>
	/// <param name="Prop"> Indicates the changed properties. </param>
	/// <seealso cref="wclNlmConnectionProperty" />
	#define wclNlmConnectionPropertyChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const GUID& ConnectionId, \
		const wclNlmConnectionProperty Prop)

	/// <summary> The <c>CwclNetworkListManager</c> class provides a set of methods
	///   to perform network list management functions and receives events related
	///   to the Network List Manager. </summary>
	/// <remarks> The component is not thread safe. </remarks>
	class CwclNetworkListManager
	{
		DISABLE_COPY(CwclNetworkListManager);

	private:
		NlmApi::INetworkListManager*	FManager;
		wclMessageProcessingMethod		FMessageProcessing;
		CwclMessageReceiver*			FReceiver;

		// Connection points.
		IConnectionPoint*		FListConnectionPoint;
		DWORD					FListCookie;
		IConnectionPoint*		FNetworkConnectionPoint;
		DWORD					FNetworkCookie;
		IConnectionPoint*		FConnectionConnectionPoint;
		DWORD					FConnectionCookie;

		void MessageReceived(const CwclMessage* const Message);
		
		int DecodeRegError(const LONG Res) const;
		
	protected:
		/// <summary> Fires the <c>AfterOpen</c> event. </summary>
		virtual void DoAfterOpen();
		/// <summary> Fires the <c>BeforeClose</c> event. </summary>
		virtual void DoBeforeClose();
		
		/// <summary> Fires the <c>OnConnectivityChanged</c> event. </summary>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   machine. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		virtual void DoConnectivityChanged(const wclNlmConnectivityFlags& Connectivity);
		/// <summary> Fires the <c>OnNetworkAdded</c> event. </summary>
		/// <param name="NetworkId"> A GUID that specifies the network that was
		///   added. </param>
		virtual void DoNetworkAdded(const GUID& NetworkId);
		
		/// <summary> Fires then <c>OnNetworkConnectivityChanged</c>
		///   event. </summary>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   machine. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		virtual void DoNetworkConnectivityChanged(const GUID& NetworkId,
			const wclNlmConnectivityFlags& Connectivity);
		/// <summary> Fires the <c>OnNetworkDeleted</c> event. </summary>
		/// <param name="NetworkId"> A GUID that specifies the network that was
		///   deleted. </param>
		virtual void DoNetworkDeleted(const GUID& NetworkId);
		/// <summary> Fires the <c>OnNetworkPropertyChanged</c> event. </summary>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		/// <param name="Change"> The value that specifies the network property
		///   that changed. </param>
		/// <seealso cref="wclNlmNetworkPropertyChangeFlags" />
		virtual void DoNetworkPropertyChanged(const GUID& NetworkId,
			const wclNlmNetworkPropertyChangeFlags& Change);

		/// <summary> Fires the <c>OnConnectionConnectivityChanged</c>
		///   event. </summary>
		/// <param name="ConnectionId"> A GUID that identifies the network
		///   connection on which the event occurred. </param>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   connection. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		virtual void DoConnectionConnectivityChanged(const GUID& ConnectionId,
			const wclNlmConnectivityFlags& Connectivity);
		/// <summary> Fires the <c>OnConnectionPropertyChanged</c> event. </summary>
		/// <param name="ConnectionId"> A GUID that identifies the network
		///   connection on which the event occurred. </param>
		/// <param name="Prop"> Indicates the changed properties. </param>
		/// <seealso cref="wclNlmConnectionProperty" />
		virtual void DoConnectionPropertyChanged(const GUID& ConnectionId,
			const wclNlmConnectionProperty Prop);
		
	public:
		/// <summary> Creates a new component. </summary>
		CwclNetworkListManager();
		/// <summary> Frees the component. </summary>
		virtual ~CwclNetworkListManager();
		
		/// <summary> Closes the Network List Manager and releases all allocated
		///   resources. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the Network List Manager and prepares for events
		///   receiving. </summary>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Open();
		
		/// <summary> Checks if the machine has network connectivity. </summary>
		/// <param name="Connected"> <para> If the method succeeded on output
		///   returns the network connectivity state. </para>
		///   <para> If the <c>Connected</c> is <c>True</c>, the network has at
		///   least local connectivity via ipv4 or ipv6 or both. The network may
		///   also have Internet connectivity. Thus, the network is
		///   connected. </para>
		///   <para> If the <c>Connected</c> is <c>False</c>, the network does not
		///   have local or Internet connectivity. The network is not
		///   connected. </para> </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnected(bool& Connected) const;
		/// <summary> Checks if the local machine has Internet
		///   connectivity. </summary>
		/// <param name="Connected"> <para> If the method succeeded on output
		///   returns the Internet connectivity state. </para>
		///   <para> If the <c>Connected</c> is <c>True</c>, the local machine is
		///   connected to the Internet; if the <c>Connected</c> is <c>False</c>, it
		///   is not. </para> </param>
		/// <returns> If the function succeeded the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetConnectedToInternet(bool& Connected) const;
		/// <summary> The <c>GetConnectivity</c> method reads the overall
		///   connectivity state of the machine. </summary>
		/// <param name="Connectivity"> If the method succeeded on output contains
		///   the information about the machine connectivity. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmConnectivityFlags" />
		int GetConnectivity(wclNlmConnectivityFlags& Connectivity) const;
		
		/// <summary> The method enumerates a complete list of the network
		///   connections that have been made. </summary>
		/// <param name="Connections"> On output contains all network connections
		///   on the machine. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmConnections" />
		int GetConnections(wclNlmConnections& Connections) const;
		
		/// <summary> The method retrieves a network based on a supplied
		///   network ID. </summary>
		/// <param name="NetworkId"> GUID that specifies the network ID. </param>
		/// <param name="Network"> If the method succeeded on output contains the
		///   <see cref="CwclNlmNetwork" /> object that represents the network.
		///   An application is responsible to dispose the returned
		///   object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclNlmNetwork" />
		int GetNetwork(const GUID& NetworkId, CwclNlmNetwork*& Network) const;
		/// <summary> Retrieves the list of networks available on the local
		///   machine. </summary>
		/// <param name="Flags"> The value specifies the flags for the network
		///   (specifically, connected or not connected). </param>
		/// <param name="Networks"> A dynamic array that receives the
		///   <see cref="CwclNlmNetwork" /> class objects for available
		///   networks. An application is responsible to free all the <c>Network</c>
		///   objects in the array as well as release the memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclNlmEnumNetwork" />
		/// <seealso cref="wclNlmNetworks" />
		int GetNetworks(const wclNlmEnumNetwork Flags, wclNlmNetworks& Networks) const;

		/// <summary> Deletes network profile with given ID. </summary>
		/// <param name="NetworkId"> GUID that specifies the network ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DeleteNetwork(const GUID& NetworkId);

		/// <summary> Gets the Network List Manager status. </summary>
		/// <returns> <c>True</c> if the NLM was opened. <c>False</c>
		///   otherwise. </returns>
		bool GetActive() const;
		/// <summary> Gets the Network List Manager status. </summary>
		/// <value> <c>True</c> if the NLM was opened. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiNlm"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be
		///   used by the WiFi Sniffer. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEWiFiNlm"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			 wclMessageProcessingMethod MessageProcessing;
		
		/// <summary> The event fires after Network List Manager opened. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(AfterOpen);
		/// <summary> The event fires before the Network List Manager
		///   closed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(BeforeClose);
		
		/// <summary> The event fires  when network connectivity related changes
		///   occur. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   machine. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		wclNlmConnectivityChangeEvent(OnConnectivityChanged);

		/// <summary> The event fires when a new network is added. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		wclNlmNetworkEvent(OnNetworkAdded);
		/// <summary> The event fires when network connectivity related changes
		///   occur. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   machine. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		wclNlmNetworkConnectivityChangedEvent(OnNetworkConnectivityChanged);
		/// <summary> The event fires when a network is deleted. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		wclNlmNetworkEvent(OnNetworkDeleted);
		/// <summary> The event fires when a network property change is
		///   detected. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="NetworkId"> A GUID that specifies the network. </param>
		/// <param name="Change"> The value that specifies the network property
		///   that changed. </param>
		/// <seealso cref="wclNlmNetworkPropertyChangeFlags" />
		wclNlmNetworkPropertyChangedEvent(OnNetworkPropertyChanged);

		/// <summary> The <c>OnConnectionConnectivityChanged</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="ConnectionId"> A GUID that identifies the network connection
		///   on which the event occurred. </param>
		/// <param name="Connectivity"> The new connectivity settings of the
		///   connection. </param>
		/// <seealso cref="wclNlmConnectivityFlags" />
		wclNlmConnectionConnectivityChangedEvent(OnConnectionConnectivityChanged);
		/// <summary> The <c>OnConnectionPropertyChanged</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="ConnectionId"> A GUID that identifies the network connection
		///   on which the event occurred. </param>
		/// <param name="Prop"> Indicates the changed properties. </param>
		/// <seealso cref="wclNlmConnectionProperty" />
		wclNlmConnectionPropertyChangedEvent(OnConnectionPropertyChanged);
	};
}