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

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "wclConnectionErrors.h"

using wclCommon::wclMessageProcessingMethod;
using wclCommon::CwclMessage;
using wclCommon::CwclMessageReceiver;

namespace wclCommunication
{
	/// <summary> The base class for all WCL connections. </summary>
	/// <remarks> A connection implements a hardware-dependent methods
	///  to communicate with a remote devices: IrDA, Classic Bluetooth, BLE,
	///  Serial etc. </remarks>
	class CwclCustomConnection
	{
		DISABLE_COPY(CwclCustomConnection);

	private:
		RTL_CRITICAL_SECTION	FCS;
		CwclMessageReceiver*	FReceiver;
		DWORD					FThreadId;
		
	protected:
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);

		/* Thread synchronization. */

		/// <summary> Enters the connection's critical section. </summary>
		/// <remarks> The method should be used to protect connection in
		///   multi-threaded applications. </remarks>
		void Enter();
		/// <summary> Exists *leaves) the connection's critical section. </summary>
		/// <remarks> The method should be used to protect connection in
		///   multi-threaded applications. </remarks>
		void Leave();
		
	public:
		/// <summary> Creates a new connection. </summary>
		CwclCustomConnection();
		/// <summary> Frees the connection. </summary>
		virtual ~CwclCustomConnection();

		/// <summary> Gets the message processing method used by the
		///   connection. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Gets the message processing method used by the
		///   connection. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		__declspec(property(get = GetMessageProcessing)) wclMessageProcessingMethod MessageProcessing;

		/// <summary> Gets the connection message receiver object. </summary>
		/// <returns> The internal message receiver object. </returns>
		/// <seealso cref="CwclMessageReceiver" />
		CwclMessageReceiver* GetReceiver() const;
		/// <summary> Gets the connection message receiver object. </summary>
		/// <value> The internal message receiver object. </value>
		/// <seealso cref="CwclMessageReceiver" />
		__declspec(property(get = GetReceiver)) CwclMessageReceiver* Receiver;

		/// <summary> Gets the connection's thread ID. </summary>
		/// <returns> The thread ID. </returns>
		/// <remarks> The connection's thread ID is the ID of the thread that
		///   created and used to handle the connection. </remarks>
		DWORD GetThreadId() const;
		/// <summary> Gets the connection's thread ID. </summary>
		/// <value> The thread ID. </value>
		/// <remarks> The connection's thread ID is the ID of the thread that
		///   created and used to handle the connection. </remarks>
		__declspec(property(get = GetThreadId)) DWORD ThreadId;
	};

	/// <summary> The client connection states. </summary>
	typedef enum
	{
		/// <summary> A client is disconnected. </summary>
		csDisconnected,
		/// <summary> A client is preparing for connection. </summary>
		csPreparing,
		/// <summary> A client is connecting to a remote device. </summary>
		csConnecting,
		/// <summary> A client is connected to a remote device. </summary>
		csConnected,
		/// <summary> A client is disconnecting from a remote device. </summary>
		csDisconnecting
	} wclClientState;

	/// <summary> The <c>OnConnect</c> event handler prototype.  </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The connection operation result code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
	///   device was established and the remote device is connected. Otherwise
	///   the connection was not established and the remote device is
	///   not connected. </param>
	/// <remarks> If the <c>Error</c> parameter of the event is not
	///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
	///   method again from inside the event handler. </remarks>
	#define wclClientConnectionConnectEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error)
	/// <summary> The <c>OnDisconnect</c> and <c>OnClose</c> events handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Reason"> The disconnection code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
	///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
	///   reason. </param>
	#define wclClientConnectionDisconnectEvent(_event_name_) \
		__event void _event_name_(void*Sender, const int Reason)

	/// <summary> The base class for all client oriented connections. </summary>
	/// <remarks> The class provides the basic methods for client
	///   connections. </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclClientConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclClientConnection);
		
	private:
		wclClientState	FState;
		unsigned long	FTimeout;
		
		// Used to notify communication thread that the connection is ready for
		// communicate and is in valid connected state.
		HANDLE	FConnectedEvent;
		// Communication thread termination event.
		HANDLE	FDisconnectEvent;
		// Communication thread handle.
		HANDLE	FThread;
		
		// Internal communication thread routine. Calls HalConnect and if succeeded
		// calls HalCommunicate.
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void CommunicationThread();

	protected:
		/// <summary> The internal disconnect method. Disconnects from a
		///   connected remote device. </summary>
		/// <param name="Reason"> The disconnection reason code. If the
		///   method has been called by the <c>Disconnect</c> method the
		///   reason is <see cref="WCL_E_SUCCESS" /> </param>
		void InternalDisconnect(const int Reason);

		/// <summary> Send a Disconnect notification message. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		void NotifyClosed(const int Reason);
		
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		virtual void DoDisconnect(const int Reason);
		
		/// <summary> Implements a hardware-dependent code that communicate with the
		///   connected remote device. </summary>
		/// <param name="Event"> The system even object handle (disconnect
		///   event). </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Derived classes must override this method to implement
		///   a hardware-dependent code that exchanges data with a remote
		///   device. </para>
		///   <para> The method executes in a separate thread. </para>
		///   <para> The method implementation must monitor the <c>Event</c>
		///   parameter. The <c>Event</c> parameter is set if the
		///   <c>Disconnect</c> method was called and the method must terminate
		///   communication and exit. </para>
		///   <para> The default implementation simple waits for the <c>Event</c>
		///   and exists when the events signaled. </para> </remarks>
		virtual int HalCommunicate(const HANDLE Event);
		/// <summary> Implements a hardware-dependent code that connects to a
		///   remote device. </summary>
		/// <param name="Event"> The system even object handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Derived classes must override this method to implement
		///   a hardware-dependent code that connects to a remote device. </para>
		///   <para> The method executes in a separate thread. </para>
		///   <para> The method implementation must monitor the <c>Event</c>
		///   parameter. The <c>Event</c> parameter is set if the
		///   <c>Disconnect</c> method was called. If the termination event was set
		///   the method must terminate connection operation. </para>
		///   <para> If connection to a remote device was terminated the method
		///   must release all allocated resources because the <c>HalDisconnect</c>
		///   will not be called. </para> </remarks>
		virtual int HalConnect(const HANDLE Event) = 0;
		/// <summary> Implements a hardware-dependent code that disconnects from the
		///   connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method is called only if a connection to a remote
		///   device was established with success (the <c>Connect</c> method was
		///   success). </para>
		///   <para> The method will not be called if the connection to the  remote
		///   device was terminated in the middle of the <c>HalConnect</c>
		///   method. </para> </remarks>
		virtual int HalDisconnect() = 0;
		
	public:
		/// <summary> Creates a new client connection. </summary>
		CwclClientConnection();
		/// <summary> Frees the connection. </summary>
		virtual~CwclClientConnection();

		/// <summary> Connects to a remote device. </summary>
		/// <param name="MessageProcessing"> Specifies a message processing method
		///   that should be used by the connection. </param>
		/// <param name="Timeout"> The connect timeout in milliseconds. The
		///   default value is 10000 milliseconds. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method starts a connection operation to a remote device.
		///   If the method success that does not mean that the connection was
		///   established. That just means that the connection operation was
		///   started. The real connection result will be passed to the
		///   <c>OnConnect</c> event handler. </remarks>
		/// <seealso cref="wclMessageProcessingMethod" />
		int Connect(const wclMessageProcessingMethod MessageProcessing,
			const unsigned long Timeout = 10000);
		/// <summary> Disconnects from the connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method disconnects from the connected remote device or
		///   terminates the pending connection. </remarks>
		int Disconnect();

		/// <summary> Gets the connection state. </summary>
		/// <returns> The <see cref="wclClientState" /> indicates the current
		///   connection state. </returns>
		/// <seealso cref="wclClientState" />
		wclClientState GetState() const;
		/// <summary> Gets the connection state. </summary>
		/// <value> The <see cref="wclClientState" /> indicates the current
		///   connection state. </value>
		/// <seealso cref="wclClientState" />
		__declspec(property(get = GetState)) wclClientState State;

		/// <summary> Gets the connect timeout value. </summary>
		/// <returns> The connect timeout value in milliseconds. </returns>
		unsigned long GetTimeout() const;
		/// <summary> Gets the connect timeout value. </summary>
		/// <value> The connect timeout value in milliseconds. </value>
		__declspec(property(get = GetTimeout)) unsigned long Timeout;

		/// <summary> The event fires when a connection to a remote device
		///   has been completed (with or without success). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <remarks> If the <c>Error</c> parameter of the event is not
		///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
		///   method again from inside the event handler. </remarks>
		wclClientConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when the remote connected device has been
		///   disconnected. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnDisconnect);
	};

	/// <summary> The <c>OnData</c> event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Data"> The pointer to the received data buffer.
	///   It is guaranteed that the parameter points to a valid data buffer.
	///   The data buffer is valid only inside the event handler. If an
	///   application needs to use the data outside the event handle it must
	///   allocate own buffer and copy data into it. </param>
	/// <param name="Size"> The data buffer size. It is guaranteed that the size
	///   is greater than 0. </param>
	#define wclConnectionDataEvent(_event_name_) \
		__event void _event_name_(void* Sender, const void* const Data, \
		const unsigned long Size)

	// Forward declaration.
	class CwclCustomClientDataProcessor;

	/// <summary> The base class for the client connection that requires data
	///   exchange with a remote device. </summary>
	/// <seealso cref="CwclClientConnection" />
	class CwclClientDataConnection : public CwclClientConnection
	{
		DISABLE_COPY(CwclClientDataConnection);

	private:
		friend class CwclCustomClientDataProcessor;

		CwclCustomClientDataProcessor*	FProcessor;

	protected:
		/// <summary> Allocates memory for incoming data buffer. </summary>
		/// <param name="Buffer"> The read buffer. </param>
		/// <param name="Size"> The read buffer size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int AllocateReadBuffer(void*& Buffer, unsigned long& Size);

		/// <summary> Send a data notification message. </summary>
		/// <param name="Data"> The data buffer contains received data. </param>
		/// <param name="Size"> The length of the received data. </param>
		void NotifyDataReceived(const void* const Data, const unsigned long Size);
		
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnData</c> event. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		virtual void DoData(const void* const Data, const unsigned long Size);
		
		/// <summary> Reads the read buffer size. </summary>
		/// <param name="Size"> On output he read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size reading code. </remarks>
		virtual int HalGetReadBufferSize(unsigned long& Size) = 0;
		/// <summary> Reads the write buffer size. </summary>
		/// <param name="Size"> On output the write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size reading code. </remarks>
		virtual int HalGetWriteBufferSize(unsigned long& Size) = 0;
		
		/// <summary> Sets the read buffer size. </summary>
		/// <param name="Size"> The new read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size setting code. </remarks>
		virtual int HalSetReadBufferSize(const unsigned long Size) = 0;
		/// <summary> Sets the write buffer size. </summary>
		/// <param name="Size"> The new write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size setting code. </remarks>
		virtual int HalSetWriteBufferSize(const unsigned long Size) = 0;
		
		/// <summary> Implements a hardware-dependent code that sends data to the
		///   connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   hardware-dependent code that sends data to the connected device.
		///   The method executes in the main thread and must be
		///   synchronous. </remarks>
		virtual int HalWrite(const void* const Data, const unsigned long Size,
			unsigned long& Written) = 0;
		
	public:
		/// <summary> Creates a new client data connection. </summary>
		CwclClientDataConnection();
		
		/// <summary> Reads the read buffer size. </summary>
		/// <param name="Size"> On output he read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetReadBufferSize(unsigned long& Size);
		/// <summary> Reads the write buffer size. </summary>
		/// <param name="Size"> On output the write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetWriteBufferSize(unsigned long& Size);
		
		/// <summary> Sets the read buffer size. </summary>
		/// <param name="Size"> The new read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetReadBufferSize(const unsigned long Size);
		/// <summary> Sets the write buffer size. </summary>
		/// <param name="Size"> The new write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetWriteBufferSize(const unsigned long Size);
		
		/// <summary> Sends data to the connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The write is synchronous operation. </remarks>
		int Write(const void* const Data, const unsigned long Size, unsigned long& Written);

		/// <summary> Gets the current Data Processor object assigned to the
		///   Connection. </summary>
		/// <returns> The <see cref="CwclCustomClientDataProcessor" /> object
		///   used by the Connection to process data. </returns>
		/// <seealso cref="CwclCustomClientDataProcessor" />
		CwclCustomClientDataProcessor* GetProcessor() const;
		__declspec(property(get = GetProcessor)) CwclCustomClientDataProcessor* Processor;

		/// <summary> The event fires when new data is received from the
		///   connected remote device. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		wclConnectionDataEvent(OnData);
	};

	// Forward declaration.
	class CwclServerConnection;

	/// <summary> The base class for all server client connection. </summary>
	/// <remarks> The class provides the basic methods for server
	///   connections. </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclServerClientConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclServerClientConnection);
		
	private:
		friend class CwclServerConnection;

		bool					FDisconnected; // Internal flag used to indicate disconnection.
		CwclServerConnection*	FServer; // Owner.
		
		void*					FParams; // Custom connection parameters.
		
		HANDLE					FDisconnectEvent;
		HANDLE					FThread;
		HANDLE					FThreadInitDoneEvent;
		int						FThreadInitResult;
		
		// Internal communication thread routine. Calls HalConnect and if succeeded
		// calls HalCommunicate.
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void CommunicationThread();
		// Executes disconnection from remote device.
		void InternalDisconnect(const int Reason);
		
	protected:
		/// <summary> Send a Disconnect notification message. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		void NotifyClosed(const int Reason);
		
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		virtual void DoDisconnect(const int Reason);
		
		/// <summary> The method accepts the client connection request. </summary>
		/// <param name="Server"> A <see cref="CwclServerConnection" />
		///   object owns the client connection. </param>
		/// <param name="Params"> An optional pointer to the hardware-dependent
		///   data contains information about client connection request. </param>
		/// <param name="ParamsSize"> An optional parameters size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method called by the server when connection from a
		///   remote client device has already been accepted. </para>
		///   <para> The method is always called from the main (or from the same)
		///   thread that runs the server. </para>
		///   <para> The method prepares the class for communication with a remote
		///   client. </para>
		///   <para> If the method fails it disconnects already accepted client
		///   connection. </para> </remarks>
		/// <seealso cref="CwclServerConnection" />
		virtual int Accept(CwclServerConnection* const Server, const void* const Params,
			const unsigned long ParamsSize);
		
		/// <summary> Hardware-dependent method that prepares to communicate
		///   with a connected remote client device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide a
		///   hardware-dependent code that prepares the class to communicate
		///   with a remote connected device. </remarks>
		virtual int HalAccept() = 0;
		/// <summary> Implements a hardware-dependent code that communicate with the
		///   connected remote device. </summary>
		/// <param name="Event"> The system even object handle (disconnect
		///   event). </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Derived classes must override this method to implement
		///   a hardware-dependent code that exchanges data with a remote
		///   device. </para>
		///   <para> The method executes in a separate thread. </para>
		///   <para> The method implementation must monitor the <c>Event</c>
		///   parameter. The <c>Event</c> parameter is set if the
		///   <c>Disconnect</c> method was called and the method must terminate
		///   communication and exit. </para>
		///   <para> The default implementation simple waits for the <c>Event</c>
		///   and exists when the events signaled. </para> </remarks>
		virtual int HalCommunicate(const HANDLE Event);
		/// <summary> Implements a hardware-dependent code that disconnects from the
		///   connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide a
		///   hardware-dependent code that disconnects from a remote connected
		///   device. </remarks>
		virtual int HalDisconnect() = 0;

		/// <summary> Gets the connection state. </summary>
		/// <returns> <c>True</c> if the connection is disconnected. </returns>
		bool GetDisconnected() const;
		/// <summary> Gets the connection state. </summary>
		/// <value> <c>True</c> if the connection is disconnected. </value>
		__declspec(property(get = GetDisconnected)) bool Disconnected;

		/// <summary> Custom connection parameters. </summary>
		/// <returns> The pointer to the custom connection parameters. </returns>
		/// <remarks> The parameters passed from the
		///   <see cref="CwclServerConnection" /> object and contains
		///   hardware-dependent data about accepted client connections. </remarks>
		void* GetParams() const;
		__declspec(property(get = GetParams)) void* Params;

	public:
		/// <summary> Creates a new server client connection. </summary>
		CwclServerClientConnection();
		/// <summary> Frees the connection. </summary>
		virtual ~CwclServerClientConnection();

		/// <summary> Disconnects from the connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method disconnects from the connected remote
		///   device. </para>
		///   <para> The method also frees the object. After calling this method an
		///   application must not use the object. </para> </remarks>
		int Disconnect();

		/// <summary> Gets the client owner. </summary>
		/// <returns> The <see cref="CwclServerConnection" /> object
		///   that owns the connection. </returns>
		/// <seealso cref="CwclServerConnection" />
		CwclServerConnection* GetServer() const;
		__declspec(property(get = GetServer)) CwclServerConnection* Server;

		/// <summary> The event fires when a connection to a remote device
		///   has been completed (with or without success). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <remarks> If the <c>Error</c> parameter of the event is not
		///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
		///   method again from inside the event handler. </remarks>
		wclClientConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when the remote connected device has been
		///   disconnected. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnDisconnect);
	};

	/// <summary> The server connections states. </summary>
	typedef enum
	{
		/// <summary> A server is closed. </summary>
		ssClosed,
		/// <summary> A server is preparing for connection. </summary>
		ssPreparing,
		/// <summary> A server is listening. </summary>
		ssListening,
		/// <summary> A server is closing. </summary>
		ssClosing
	} wclServerState;

	/// <summary> The server's <c>OnConnect</c> event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> The
	///   <see cref="CwclServerClientConnection" /> represents a remote
	///   connected client. </param>
	/// <param name="Error"> The connection operation result code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
	///   device was established and the remote device is connected. Otherwise
	///   the connection was not established and the remote device is
	///   not connected. </param>
	/// <seealso cref="CwclServerClientConnection" />
	#define wclServerConnectionConnectEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclServerClientConnection* const Client, \
		const int Error)
	/// <summary> The server's <c>OnDisconnect</c> event handler prototype. </summary>
	/// <summary> The prototype of the <c>OnDisconnect</c> event handler for
	///   server connections. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> The
	///   <see cref="CwclServerClientConnection" /> represents a remote
	///   connected client. </param>
	/// <param name="Reason"> The disconnection code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
	///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
	///   reason. </param>
	/// <seealso cref="CwclServerClientConnection" />
	#define wclServerConnectionDisconnectEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclServerClientConnection* const Client, \
		const int Reason)

	/// <summary> The base class for all server connections. </summary>
	/// <remarks> An application must never create this class directly.
	///   Instead of that an application must use high-level
	///   components. </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclServerConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclServerConnection);

	private:
		friend class CwclServerClientConnection;
		typedef std::list<CwclServerClientConnection*> CLIENTS;

		// Clients list.
		CLIENTS*		FClients;
		wclServerState	FState;

		// Client that should be deleted.
		CwclServerClientConnection* FClientToDelete;
		
		// Communication thread termination event.
		HANDLE			FCloseEvent;
		// Communication thread handle.
		HANDLE			FThread;
		// Indicates the communication thread has been initialized.
		HANDLE			FThreadInitDoneEvent;
		// Indicates the thread initialization result.
		int				FThreadInitResult;
		
		void ClientConnect(void* Sender, const int Error);
		void ClientDisconnect(void* Sender, const int Reason);
		
		// Internal communication thread routine. Calls HalConnect and if succeeded
		// calls HalCommunicate.
		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void CommunicationThread();

		void DeleteClient(CwclServerClientConnection* const Client);
		
	protected:
		/// <summary> Unhooks events from the client that should be deleted. </summary>
		virtual void UnhookDeletedClientEvents(CwclServerClientConnection* const Client);

		/// <summary> Closes the server. </summary>
		/// <param name="Reason"> The close reason code. If the server closed by
		///   the <c>Close</c> method call the <c>Reason</c> is
		///   <see cref="WCL_E_SUCCESS" /> </param>
		void InternalClose(const int Reason);

		/// <summary> Sends a notification to the main thread to create and init
		///   new client connection. </summary>
		/// <param name="Params"> An optional pointer to the hardware-dependent
		///   data contains information about client connection request. </param>
		/// <param name="ParamsSize"> An optional parameters size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The <c>HalListen</c> method should call this method to
		///   create and initialize new client connection. </remarks>
		int CreateNewClientConnection(const void* const Params, const unsigned long ParamsSize);
		
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the <c>OnClosed</c> event. </summary>
		/// <param name="Reason"> The close reason code. If the server closed by
		///   the <c>Close</c> method call the <c>Reason</c> is
		///   <see cref="WCL_E_SUCCESS" /> </param>
		virtual void DoClosed(const int Reason);
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <seealso cref="CwclServerClientConnection" />
		virtual void DoConnect(CwclServerClientConnection* const Client, const int Error);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		/// <seealso cref="CwclServerClientConnection" />
		virtual void DoDisconnect(CwclServerClientConnection* const Client, const int Reason);
		/// <summary> Fires the <c>OnListen</c> event. </summary>
		virtual void DoListen();
		
		/// <summary> The method sets the client's event handlers. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a client
		///   connection. </param>
		/// <seealso cref="CwclServerClientConnection" />
		virtual void SetClientEvents(CwclServerClientConnection* const Client);
		
		/// <summary> Implements a hardware-dependent method for listening the client
		///   connections. </summary>
		/// <param name="Event"> The termination event handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement
		///   a hardware-dependent code for listening for incoming
		///   connections. </remarks>
		virtual int HalListen(const HANDLE Event) = 0;
		/// <summary> Implements a hardware-dependent method to stop
		///   listening. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method is called only if the <c>HalListen</c> was
		///   success. </remarks>
		virtual int HalClose() = 0;
		/// <summary> The method creates a hardware and transport-dependent
		///   client connection. </summary>
		/// <returns> If the method success the return value is the object
		///   represents the client connection. Otherwise the method returns
		///   <c>NULL</c>. </returns>
		/// <remarks> A derived class must override this method to create a
		///   custom HAL server client connection. </remarks>
		/// <seealso cref="CwclServerClientConnection" />
		virtual CwclServerClientConnection* HalCreateClient() = 0;
		/// <summary> Implements a hardware-dependent code that prepares for
		///   listening. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   hardware-dependent code that prepares the server connection. </remarks>
		virtual int HalPrepare() = 0;

	public:
		/// <summary> Creates a new server connection. </summary>
		CwclServerConnection();
		/// <summary> Frees the server connection. </summary>
		virtual ~CwclServerConnection();
		
		/// <summary> The method disconnects all connected clients and closes the
		///   server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method must be called from the same thread that called
		///   the <c>Listen</c> method. The method is not thread-safe. </remarks>
		int Close();
		/// <summary> The method starts listening for client connections. </summary>
		/// <param name="MessageProcessing"> A message processing method that should
		///   be used by the server. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		int Listen(const wclMessageProcessingMethod MessageProcessing);
		
		/// <summary> Gets a connected client by its index. </summary>
		/// <param name="Index"> Client's index. </param>
		/// <returns> The connected client. </returns>
		/// <seealso cref="CwclServerClientConnection" />
		CwclServerClientConnection* GetClients(const size_t Index) const;
		/// <summary> Gets a connected client by its index. </summary>
		/// <value> The connected client. </value>
		/// <seealso cref="CwclServerClientConnection" />
		__declspec(property(get = GetClients)) CwclServerClientConnection* Clients[];

		/// <summary> Gets the number of connected clients. </summary>
		/// <returns> The number of the connected clients. </returns>
		size_t GetClientsCount() const;
		/// <summary> Gets the number of connected clients. </summary>
		/// <value> The number of the connected clients. </value>
		__declspec(property(get = GetClientsCount)) size_t ClientsCount;
		
		/// <summary> Gets the connection state. </summary>
		/// <returns> The <see cref="wclServerState" /> indicates the current
		///   connection state. </returns>
		/// <seealso cref="wclServerState" />
		wclServerState GetState() const;
		/// <summary> Gets the connection state. </summary>
		/// <value> The <see cref="wclServerState" /> indicates the current
		///   connection state. </value>
		/// <seealso cref="wclServerState" />
		__declspec(property(get = GetState)) wclServerState State;
		
		/// <summary> The event fires when the server is closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnClosed);
		/// <summary> The event fires when a remote client is connected to
		///   the server. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <seealso cref="CwclServerClientConnection" />
		wclServerConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when a remote client has disconnected from the
		///   server. </summary>
		/// <summary> The prototype of the <c>OnDisconnect</c> event handler for
		///   server connections. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		/// <seealso cref="CwclServerClientConnection" />
		wclServerConnectionDisconnectEvent(OnDisconnect);
		/// <summary> The event fires when the server is ready to accept incoming
		///   connections (is in listening state). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnListen);
	};

	// Forward declaration.
	class CwclServerDataConnection;
	class CwclCustomServerClientDataProcessor;

	/// <summary> The base class for the server client connection that
	///   requires data exchange with a remote device. </summary>
	/// <seealso cref="CwclServerClientConnection" />
	class CwclServerClientDataConnection : public CwclServerClientConnection
	{
		DISABLE_COPY(CwclServerClientDataConnection);

	private:
		friend class CwclCustomServerClientDataProcessor;

		CwclCustomServerClientDataProcessor*	FProcessor;

	protected:
		/// <summary> Allocates memory for incoming data buffer. </summary>
		/// <param name="Buffer"> The read buffer. </param>
		/// <param name="Size"> The read buffer size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int AllocateReadBuffer(void*& Buffer, unsigned long& Size);

		/// <summary> Send a data notification message. </summary>
		/// <param name="Data"> The data buffer contains received data. </param>
		/// <param name="Size"> The length of the received data. </param>
		void NotifyDataReceived(const void* const Data, const unsigned long Size);
		
		/// <summary> The message receiver calls this method when a new notification
		///   message has been received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents the notification message. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> The method accepts the client connection request. </summary>
		/// <param name="Server"> A <see cref="CwclServerConnection" />
		///   object owns the client connection. </param>
		/// <param name="Params"> An optional pointer to the hardware-dependent
		///   data contains information about client connection request. </param>
		/// <param name="ParamsSize"> An optional parameters size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method called by the server when connection from a
		///   remote client device has already been accepted. </para>
		///   <para> The method is always called from the main (or from the same)
		///   thread that runs the server. </para>
		///   <para> The method prepares the class for communication with a remote
		///   client. </para>
		///   <para> If the method fails it disconnects already accepted client
		///   connection. </para>
		///   <para> The <c>Server</c> parameter must be a
		///   <see cref="CwclServerDataConnection" />
		///    object. </para> </remarks>
		/// <seealso cref="CwclServerConnection" />
		/// <seealso cref="CwclServerDataConnection" />
		virtual int Accept(CwclServerConnection* const Server, const void* const Params,
			const unsigned long ParamsSize) override;
		
		/// <summary> Fires the <c>OnData</c> event. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		virtual void DoData(const void* const Data, const unsigned long Size);

		/// <summary> Reads the read buffer size. </summary>
		/// <param name="Size"> On output he read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size reading code. </remarks>
		virtual int HalGetReadBufferSize(unsigned long& Size) = 0;
		/// <summary> Reads the write buffer size. </summary>
		/// <param name="Size"> On output the write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size reading code. </remarks>
		virtual int HalGetWriteBufferSize(unsigned long& Size) = 0;

		/// <summary> Sets the read buffer size. </summary>
		/// <param name="Size"> The new read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size setting code. </remarks>
		virtual int HalSetReadBufferSize(const unsigned long Size) = 0;
		/// <summary> Sets the write buffer size. </summary>
		/// <param name="Size"> The new write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement the
		///  buffer size setting code. </remarks>
		virtual int HalSetWriteBufferSize(const unsigned long Size) = 0;

		/// <summary> Implements a hardware-dependent code that sends data to the
		///   connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   hardware-dependent code that sends data to the connected device.
		///   The method executes in the main thread and must be
		///   synchronous. </remarks>
		virtual int HalWrite(const void* const Data, const unsigned long Size,
			unsigned long& Written) = 0;

	public:
		/// <summary> Creates a new server client data connection. </summary>
		CwclServerClientDataConnection();

		/// <summary> Reads the read buffer size. </summary>
		/// <param name="Size"> On output he read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetReadBufferSize(unsigned long& Size);
		/// <summary> Reads the write buffer size. </summary>
		/// <param name="Size"> On output the write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetWriteBufferSize(unsigned long& Size);

		/// <summary> Sets the read buffer size. </summary>
		/// <param name="Size"> The new read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetReadBufferSize(const unsigned long Size);
		/// <summary> Sets the write buffer size. </summary>
		/// <param name="Size"> The new write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetWriteBufferSize(const unsigned long Size);

		/// <summary> Sends data to the connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The write is synchronous operation. </remarks>
		int Write(const void* const Data, const unsigned long Size,
			unsigned long& Written);

		/// <summary> Gets the current Data Processor object assigned to the
		///   Connection. </summary>
		/// <returns> The <see cref="CwclCustomServerClientDataProcessor" /> object
		///   used by the Connection to process data. </returns>
		/// <seealso cref="CwclCustomServerClientDataProcessor" />
		CwclCustomServerClientDataProcessor* GetProcessor() const;
		/// <summary> Gets the current Data Processor object assigned to the
		///   Connection. </summary>
		/// <value> The <see cref="CwclCustomServerClientDataProcessor" /> object
		///   used by the Connection to process data. </value>
		/// <seealso cref="CwclCustomServerClientDataProcessor" />
		__declspec(property(get = GetProcessor)) CwclCustomServerClientDataProcessor* Processor;

		/// <summary> The event fires when new data is received from the
		///   connected remote device. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		wclConnectionDataEvent(OnData);
	};

	/// <summary> The server's <c>OnData</c> event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> A
	///   <see cref="CwclServerClientDataConnection" /> object
	///   represents a remote client connection. </param>
	/// <param name="Data"> The pointer to the received data buffer.
	///   It is guaranteed that the parameter points to a valid data buffer.
	///   The data buffer is valid only inside the event handler. If an
	///   application needs to use the data outside the event handle it must
	///   allocate own buffer and copy data into it. </param>
	/// <param name="Size"> The data buffer size. It is guaranteed that the size
	///   is greater than 0. </param>
	/// <seealso cref="CwclServerClientDataConnection" />
	#define wclServerConnectionDataEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclServerClientDataConnection* const Client, \
		const void* const Data, const unsigned long Size)

	/// <summary> The base class for the server connection that
	///   requires data exchange with a remote device. </summary>
	/// <seealso cref="CwclServerConnection" />
	class CwclServerDataConnection : public CwclServerConnection
	{
		DISABLE_COPY(CwclServerDataConnection);

	private:
		void ClientData(void* Sender, const void* const Data, const unsigned long Size);
		
	protected:
		/// <summary> Unhooks events from the client that should be deleted. </summary>
		virtual void UnhookDeletedClientEvents(CwclServerClientConnection* const Client) override;

		/// <summary> The method sets the client's event handlers. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a client
		///   connection. </param>
		/// <seealso cref="CwclServerClientConnection" />
		virtual void SetClientEvents(CwclServerClientConnection* const Client) override;
		
		/// <summary> Fires the <c>OnData</c> event. </summary>
		/// <param name="Client"> A
		///   <see cref="CwclServerClientDataConnection" /> object
		///   represents a remote client connection. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		virtual void DoData(CwclServerClientDataConnection* const Client, const void* const Data,
			const unsigned long Size);
		
	public:
		/// <summary> Creates a new client data connection. </summary>
		CwclServerDataConnection();
		
		/// <summary> The event fires when new data is received from the
		///   connected remote device. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> A
		///   <see cref="CwclServerClientDataConnection" /> object
		///   represents a remote client connection. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		wclServerConnectionDataEvent(OnData);
	};

	class CwclCustomDataProcessor;

	/// <summary> The <see cref="CwclCustomDataProcessor" /> <c>OnWrite</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Data"> The pointer to the data buffer that a Data Processor
	///   needs to send to a connection. </param>
	/// <param name="Size"> The data buffer size. </param>
	/// <param name="Written"> The amount of bytes actually written to the
	///   device. </param>
	/// <param name="WriteResult"> The write operation result. </param>
	/// <seealso cref="CwclCustomDataProcessor" />
	#define wclDataProcessorWriteEvent(_event_name_) \
		__event void _event_name_(void* Sender, const void* const Data, \
		const unsigned long Size, unsigned long& Written, int& WriteResult)

	/// <summary> The base class for all WCL Data Processors. </summary>
	/// <remarks> The Data Processor is a class the allows to add additional
	///   data processing for Connections. </remarks>
	class CwclCustomDataProcessor
	{
		DISABLE_COPY(CwclCustomDataProcessor);

	protected:
		/// <summary> Fires the <c>OnWrite</c> event. </summary>
		/// <param name="Data"> The pointer to the data buffer that a Data Processor
		///   needs to send to a connection. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <param name="WriteResult"> The write operation result. </param>
		virtual void DoWrite(const void* const Data, const unsigned long Size,
			unsigned long& Written, int& WriteResult);

		/// <summary> Implements a connection-dependent code that sends data to the
		///   connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   connection-dependent code that sends data to the connected
		///   device. </remarks>
		virtual int WriteData(const void* const Data, const unsigned long Size,
			unsigned long& Written) = 0;
		
		/// <summary> Sends data to the connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Write(const void* const Data, const unsigned long Size);

	public:
		/// <summary> Creates new Data Processor object. </summary>
		CwclCustomDataProcessor();
		/// <summary> Frees the Data Processor object. </summary>
		virtual ~CwclCustomDataProcessor();

		/// <summary> The method called by the Connection when data has been
		///   received from a remote device. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the method it must
		///   allocate own buffer and copy data. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <remarks> <para> A derived classes must override this method to process
		///   the received data. </para>
		///   <para> The <c>Data</c> parameter is valid only inside the
		///   procedure. If a derived class needs to use data outside the method it
		///   must copy the data into internal buffer. </para> </remarks>
		virtual void ProcessData(const void* const Data, const unsigned long Size) = 0;

		/// <summary> The event fires when the Data Processor needs to write data
		///   to a connection but a connection is not assigned. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Data"> The pointer to the data buffer that a Data Processor
		///   needs to send to a connection. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <param name="WriteResult"> The write operation result. </param>
		wclDataProcessorWriteEvent(OnWrite);
	};

	/// <summary> The base class for all WCL Client Data Processors. </summary>
	/// <remarks> The Client Data Processor allows to add additional data
	///   processing for the Client Data Connections. </remarks>
	/// <seealso cref="CwclCustomDataProcessor" />
	/// <seealso cref="CwclClientDataConnection" />
	class CwclCustomClientDataProcessor : public CwclCustomDataProcessor
	{
		DISABLE_COPY(CwclCustomClientDataProcessor);

	private:
		friend class CwclClientDataConnection;

		CwclClientDataConnection*	FConnection;
		bool						FConnectionSet;
		
	protected:
		/// <summary> Writes data to the Client Connection. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int WriteData(const void* const Data, const unsigned long Size,
			unsigned long& Written) override;
		
	public:
		/// <summary> Creates new Client Data Processor. </summary>
		/// <param name="Connection"> A <see cref="CwclClientDataConnection" />
		///   object that is used to communicate with a remote device. </param>
		/// <seealso cref="CwclClientDataConnection" />
		CwclCustomClientDataProcessor(CwclClientDataConnection* const Connection);
		/// <summary> Frees the Data Processor. </summary>
		virtual ~CwclCustomClientDataProcessor();
		
		/// <summary> Gets the connection object used to communicate with a remote
		///   device. </summary>
		/// <returns> The <see cref="CwclClientDataConnection" /> object. </returns>
		/// <seealso cref="CwclClientDataConnection" />
		CwclClientDataConnection* GetConnection() const;
		__declspec(property(get = GetConnection)) CwclClientDataConnection* Connection;
	};

	/// <summary> The Data Client Component's event handler prototype for
	///   <c>OnCreateProcessor</c> and <c>OnDestroyProcessor</c>
	///   events. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
	///   object that requires a Data Processor. </param>
	/// <seealso cref="CwclClientDataConnection" />
	/// <seealso cref="CwclCustomClientDataProcessor" />
	#define wclClientConnectionProcessorEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclClientDataConnection* const Connection)

	/// <summary> The base class for all WCL Server Client Data
	///   Processors. </summary>
	/// <remarks> The Server Client Data Processor allows to add additional data
	///   processing for the Server Client Data Connections. </remarks>
	/// <seealso cref="CwclCustomDataProcessor" />
	/// <seealso cref="CwclServerClientDataConnection" />
	class CwclCustomServerClientDataProcessor : public CwclCustomDataProcessor
	{
		DISABLE_COPY(CwclCustomServerClientDataProcessor);

	private:
		friend class CwclServerClientDataConnection;

		CwclServerClientDataConnection*	FConnection;
		bool							FConnectionSet;
		
	protected:
		/// <summary> Writes data to the Connection. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int WriteData(const void* const Data, const unsigned long Size,
			unsigned long& Written) override;
		
	public:
		/// <summary> Creates new Client Data Processor. </summary>
		/// <param name="Connection"> A
		///   <see cref="CwclServerClientDataConnection" /> object that is used to
		///   communicate with a remote device. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		CwclCustomServerClientDataProcessor(CwclServerClientDataConnection* const Connection);
		/// <summary> Frees the Data Processor. </summary>
		virtual ~CwclCustomServerClientDataProcessor();
		
		/// <summary> Gets the connection object used to communicate with a remote
		///   device. </summary>
		/// <returns> The <see cref="CwclServerClientDataConnection" />
		///   object. </returns>
		/// <seealso cref="CwclServerClientDataConnection" />
		CwclServerClientDataConnection* GetConnection() const;
		__declspec(property(get = GetConnection)) CwclServerClientDataConnection* Connection;
	};

	/// <summary> The Data Server Component's event handler prototype for
	///   <c>OnCreateProcessor</c> and <c>OnDestroyProcessor</c>
	///   events. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Connection"> The
	///   <see cref="CwclServerClientDataConnection" /> object that requires a
	///   Data Processor. </param>
	/// <seealso cref="CwclServerDataConnection" />
	/// <seealso cref="CwclServerClientDataConnection" />
	#define wclServerConnectionProcessorEvent(_event_name_) \
		__event void _event_name_(void* Sender, CwclServerClientDataConnection* const Connection)
}