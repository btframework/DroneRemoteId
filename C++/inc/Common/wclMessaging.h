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

#include <list>

#include "wclErrors.h"
#include "wclHelpers.h"

/// <summary> This macro helps to build correct documentation. </summary>
#define _WCL_COMMON_WINAPI_INCLUDE_FILE_ "wclWinAPI.h"
#include _WCL_COMMON_WINAPI_INCLUDE_FILE_

namespace wclCommon
{
	/* Message categories. */
	
	/// <summary> The message categories. </summary>
	typedef enum
	{
		/// <summary> The Audio Framework messages category. </summary>
		mcAudio,
		/// <summary> The Bluetooth Framework messages category. </summary>
		mcBluetooth,
		/// <summary> The Connections and Connection providers messages
		///   category. </summary>
		mcConnection,
		/// <summary> The Power Monitoring subsystem messages category. </summary>
		mcPower,
		/// <summary> The Serial Framework messages category. </summary>
		mcSerial,
		/// <summary> The System messages category. </summary>
		mcSystem,
		/// <summary> The USB Framework messages category. </summary>
		mcUsb,
		/// <summary> The User Defined messages category. </summary>
		mcUser,
		/// <summary> The WiFi Framework messages category. </summary>
		mcWiFi,
		/// <summary> The WiiRemote Framework messages category. </summary>
		mcWiiRemote
	} wclMessageCategory;

	/* Base message classes. */

	// Forward declaration.
	class CwclMessageReceiver;

	/// <summary> The message object. </summary>
	class CwclMessage
	{
		DISABLE_COPY(CwclMessage);

	private:
		friend class CwclMessageReceiver;

		unsigned char		FId;
		wclMessageCategory	FCategory;
		LONG				FRefCounter;
		
		unsigned long		FCreated;
		unsigned long		FQueued;
		unsigned long		FProcessed;
		
	public:
		/// <summary> Creates new message object. </summary>
		/// <param name="Id"> The message ID. </param>
		/// <param name="Category"> The message category ID. </param>
		/// <seealso cref="wclMessageCategory" />
		CwclMessage(const unsigned char Id,
			const wclMessageCategory Category);
		/// <summary> Frees the message object. </summary>
		virtual ~CwclMessage();
		
		/// <summary> Increments the reference count of the object. This method
		///   should be called for every new reference to the object. </summary>
		void AddRef();
		/// <summary> Decrements the reference count for the object. </summary>
		/// <remarks> When the reference count on the object reaches zero,
		///   <c>Release</c> causes the object to free itself. When the released
		///   pointer is the only existing reference to an object, the
		///   implementation frees the object. </remarks>
		void Release();
		
		/// <summary> Gets the message category ID. </summary>
		/// <returns> The message category ID. </returns>
		/// <seealso cref="wclMessageCategory" />
		wclMessageCategory GetCategory() const;
		/// <summary> Gets the message category ID. </summary>
		/// <value> The message category ID. </value>
		/// <seealso cref="wclMessageCategory" />
		__declspec(property(get = GetCategory)) wclMessageCategory Category;

		/// <summary> Gets the message ID. </summary>
		/// <returns> The message ID. </returns>
		unsigned char GetId() const;
		/// <summary> Gets the message ID. </summary>
		/// <value> The message ID. </value>
		__declspec(property(get = GetId)) unsigned char Id;

		/// <summary> Gets message created timestamp. </summary>
		/// <returns> The timestamp in ticks when the message was created. </returns>
		unsigned long GetCreated() const;
		/// <summary> Gets message created timestamp. </summary>
		/// <value> The timestamp in ticks when the message was created. </value>
		__declspec(property(get = GetCreated)) unsigned long Created;
		
		/// <summary> Gets the message queued timestamp. </summary>
		/// <returns> The timestamp in ticks when the message was placed to the
		///   messages queue. If the value is 0 then the message was not
		///   queued. </returns>
		unsigned long GetQueued() const;
		/// <summary> Gets the message queued timestamp. </summary>
		/// <value> The timestamp in ticks when the message was placed to the
		///   messages queue. If the value is 0 then the message was not
		///   queued. </value>
		__declspec(property(get = GetQueued)) unsigned long Queued;
		
		/// <summary> Gets the message processed timestamp. </summary>
		/// <returns> The timestamp on ticks when the message was processed. If the
		///   message was not processed the value is 0. </returns>
		unsigned long GetProcessed() const;
		/// <summary> Gets the message processed timestamp. </summary>
		/// <value> The timestamp on ticks when the message was processed. If the
		///   message was not processed the value is 0. </value>
		__declspec(property(get = GetProcessed)) unsigned long Processed;
	};

	/// <summary> The Audio category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclAudioCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclAudioCategoryMessage);

	public:
		/// <summary> Creates new Audio message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclAudioCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Bluetooth category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclBluetoothCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclBluetoothCategoryMessage);

	public:
		/// <summary> Creates new Bluetooth message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclBluetoothCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Connection category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclConnectionCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclConnectionCategoryMessage);

	public:
		/// <summary> Creates new Connection message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclConnectionCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Power Monitoring category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclPowerCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclPowerCategoryMessage);
		
	public:
		/// <summary> Creates new Power message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclPowerCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Serial category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclSerialCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclSerialCategoryMessage);

	public:
		/// <summary> Creates new Serial message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclSerialCategoryMessage(const unsigned char Id);
	};

	/// <summary> The System category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclSystemCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclSystemCategoryMessage);
		
	public:
		/// <summary> Create a new System message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclSystemCategoryMessage(const unsigned char Id);
	};

	/// <summary> The USB category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclUsbCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclUsbCategoryMessage);

	public:
		/// <summary> Creates new USB message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclUsbCategoryMessage(const unsigned char Id);
	};

	/// <summary> The User Defined messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclUserDefinedCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclUserDefinedCategoryMessage);

	public:
		/// <summary> Creates new User Defined message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclUserDefinedCategoryMessage(const unsigned char Id);
	};

	/// <summary> The WiFi category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclWiFiCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclWiFiCategoryMessage);
		
	public:
		/// <summary> Creates new WiFi message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclWiFiCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Wii Remote category messages base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclWiiRemoteCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclWiiRemoteCategoryMessage);

	public:
		/// <summary> Creates new Wii Remote message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclWiiRemoteCategoryMessage(const unsigned char Id);
	};

	/* System messages. */

	/// <summary> The Hardware Changed message is broadcast to all subscribers
	///   when changes in the hardware configuration have been detected. The
	///   message ID is 
	///   <see cref="wclCommon::WCL_MSG_ID_SYS_HARDWARE_CHANGED" />. </summary>
	/// <seealso cref="CwclSystemCategoryMessage" />
	class CwclHardwareChangeMessage : public CwclSystemCategoryMessage
	{
		DISABLE_COPY(CwclHardwareChangeMessage);

	private:
		GUID		FInterfaceClass;
		GUID		FDeviceClass;
		tstring		FInstance;
		bool		FInserted;
		
	public:
		/// <summary> Creates new Hardware Changed message object. </summary>
		/// <param name="InterfaceClass"> The device interface class GUID. </param>
		/// <param name="DeviceClass"> The device class GUID. </param>
		/// <param name="Instance"> The device instance string. </param>
		/// <param name="Inserted"> <c>true</c> if the device has been
		///   inserted. </param>
		CwclHardwareChangeMessage(const GUID& InterfaceClass, const GUID& DeviceClass,
			const tstring& Instance, const bool Inserted);
		
		/// <summary> Gets the device interface class GUID. </summary>
		/// <returns> The device interface class GUID. </returns>
		GUID GetInterfaceClass() const;
		/// <summary> Gets the device interface class GUID. </summary>
		/// <value> The device interface class GUID. </value>
		__declspec(property(get = GetInterfaceClass)) GUID InterfaceClass;

		/// <summary> Gets the device class GUID. </summary>
		/// <returns> The device class GUID. </returns>
		GUID GetDeviceClass() const;
		/// <summary> Gets the device class GUID. </summary>
		/// <value> The device class GUID. </value>
		__declspec(property(get = GetDeviceClass)) GUID DeviceClass;

		/// <summary> Gets the device instance string. </summary>
		/// <returns> The device instance string. </returns>
		tstring GetInstance() const;
		/// <summary> Gets the device instance string. </summary>
		/// <value> The device instance string. </value>
		__declspec(property(get = GetInstance)) tstring Instance;

		/// <summary> Gets the device state. </summary>
		/// <returns> <c>true</c> if the device has been inserted. </returns>
		bool GetInserted() const;
		/// <summary> Gets the device state. </summary>
		/// <value> <c>true</c> if the device has been inserted. </value>
		__declspec(property(get = GetInserted)) bool Inserted;
	};

	/* Message processing methods. */

	/// <summary> Message processing methods used in inter-threading
	///   notifications. </summary>
	typedef enum
	{
		/// <summary> Asynchronous message processing. All events are called in a
		///   separate thread. An application is responsible for the synchronization
		///   with UI thread. Must be used carefully. </summary>
		mpAsync,
		/// <summary> Synchronous message processing method based on Windows
		///   Messages. </summary>
		/// <remarks> This method is recommended for single threading UI
		///   applications. </remarks>
		mpSync
	} wclMessageProcessingMethod;

	/* Message Receiver. */

	/// <summary> The <c>OnMessage</c> event handler prototype. </summary>
	/// <param name="Message"> The <see cref="CwclMessage" /> object represented
	///   a message. </param>
	/// <remarks> <para> The event always fires in the same thread which was used
	///   to create the receiver. </para>
	///   <para> The <c>Message</c> object is valid only inside an event
	///   handler. </para> </remarks>
	/// <seealso cref="CwclMessage" />
	#define wclMessageEvent(_event_name_) \
		__event void _event_name_(const CwclMessage* const Message)

	/// <summary> The Wireless Communication Library message receiver. </summary>
	class CwclMessageReceiver
	{
		DISABLE_COPY(CwclMessageReceiver);

	private:
		/* Some type definitions */

		friend class CwclMessageBroadcaster;

		typedef std::list<CwclMessage*> MESSAGES;

		/* Common fields */

		// Messages queue critical section.
		CwclCriticalSection*		FCS;
		// Recevier's ID.
		long						FId;
		// A message receiver status.
		bool						FListening;
		// Message processing methods.
		wclMessageProcessingMethod	FMethod;
		// Id of the thread that used to call the Open method.
		ULONG						FOpenThreadId;
		// Messages queue.
		MESSAGES*					FQueue;

		/* Asynchronous message processing fields */

		// New message/thread termination auto reset event.
		CwclAutoResetEvent*			FEvent;
		// Termination event.
		CwclManualResetEvent*		FTermEvent;
		// Termination flag.
		bool						FTerminated;
		// Message processing thread.
		HANDLE						FThread;
		// We also need thread ID.
		unsigned int				FThreadId;

		/* Synchronous message processing fields */

		// Message ID used for synchronization.
		UINT						FMsg;
		// Receiver's Window handle.
		HWND						FWnd;

		/* Common message processing methods */

		int Initialize();
		int Uninitialize();

		int ProcessMessages();
		void DispatchMessages();

		int Synchronize();

		/* Asynchronous message processing methods */

		static UINT __stdcall _AsyncThreadProc(LPVOID lpParam);
		void AsyncThreadProc();
		
		int AsyncInitialize();
		int AsyncUninitialize();
		int AsyncSynchronize();
		int AsyncProcessMessages();

		/* Synchronous message processing methods */

		static LRESULT __stdcall _SyncWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
			LPARAM lParam);
		bool SyncWndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam,
			const LPARAM lParam);

		int SyncInitialize();
		int SyncUninitialize();
		int SyncSynchronize();
		int SyncProcessMessages();
		
	protected:

		/// <summary> Calls the <c>OnMessage</c> event </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object. </param>
		/// <remarks> The <c>Message</c> parameter is valid only inside the
		///   method. </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void DoMessage(const CwclMessage* const Message);
		
	public:
		/// <summary> Creates new message receiver object. </summary>
		CwclMessageReceiver();
		/// <summary> Frees the message receiver. </summary>
		virtual ~CwclMessageReceiver();
		
		/// <summary> Closes the message receiver. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the message receiver. </summary>
		/// <param name="Method"> The message processing method that should be used
		///   by the Message Receiver. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="TwclMessageProcessingMethod" />
		int Open(const wclMessageProcessingMethod Method);
		
		/// <summary> Places a message to the messages queue and starts processing
		///   the messages. </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object. A caller
		///   is responsible to dispose the message object passed into the
		///   method. </param>
		/// <param name="Sync"> <para> If the <c>Sync</c> parameter is <c>True</c>
		///   and the thread that called the method is the same that used to call
		///   the <c>Open</c> method the message will be delivered without placing
		///   it to the messages queue. </para>
		///   <para> If the thread that posting the message is different from one
		///   that was used to call the <c>Open</c> method or the <c>Sync</c>
		///   parameter is <c>False</c> (the default value) the message will be
		///   placed to the messages queue. </para> </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> If sync messages is posted it can be processed before any
		///   other messages in the queue. </remarks>
		/// <seealso cref="CwclMessage" />
		int Post(CwclMessage* const Message, const bool Sync = false);
		
		/// <summary> Processes all messages in the messages queue. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int ProcessAllMessages();

		/// <summary> Gets the receiver's ID. </summary>
		/// <returns> Unique message receiver ID. </returns>
		long GetId() const;
		/// <summary> Gets the receiver's ID. </summary>
		/// <value> Unique message receiver ID. </value>
		__declspec(property(get = GetId)) long Id;
		
		/// <summary> Gets the receiver status. </summary>
		/// <returns> <c>True</c> if the receiver is listening for the
		///   messages. </returns>
		bool GetListening() const;
		/// <summary> Gets the receiver status. </summary>
		/// <value> <c>True</c> if the receiver is listening for the
		///   messages. </value>
		__declspec(property(get = GetListening)) bool Listening;
		
		/// <summary> Get a message processing method supported by the message
		///   receiver. </summary>
		/// <returns> A message processing method. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported message processing method. </remarks>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMethod() const;
		/// <summary> Gets a message processing method supported by the message
		///   receiver. </summary>
		/// <value> A message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		__declspec(property(get = GetMethod)) wclMessageProcessingMethod Method;
		
		/// <summary> Gets an ID of a thread that was used to call the <c>Open</c>
		///   method. </summary>
		/// <returns> Thread ID. </returns>
		ULONG GetOpenThreadId() const;
		/// <summary> Gets an ID of a thread that was used to call the <c>Open</c>
		///   method. </summary>
		/// <value> Thread ID. </value>
		__declspec(property(get = GetOpenThreadId)) ULONG OpenThreadId;
		
		/// <summary> The event called when new message was received. </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object represented
		///   a message. </param>
		/// <remarks> <para> The event always fires in the same thread which was used
		///   to create the receiver. </para>
		///   <para> The <c>Message</c> object is valid only inside an event
		///   handler. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		wclMessageEvent(OnMessage);
	};

	/* Message Broadcaster. */

	/// <summary> The message broadcaster manages broadcast messages between
	///   subscribers (message receivers subscribed for broadcast messages).
	///   Also the message broadcaster monitors changes in the hardware
	///   configuration and notifies subscribers about the changes. </summary>
	class CwclMessageBroadcaster
	{
		DISABLE_COPY(CwclMessageBroadcaster);
		
	private:
		friend class CwclMessageReceiver;

		typedef std::list<CwclMessageReceiver*> RECEIVERS;
		
		RECEIVERS*				FReceivers; // Subscribed receivers.
		CwclCriticalSection*	FReceiversCS; // Subscribers list synchronization.
		
		// Hardware monitoring.
		bool					FCfgMgrLoaded;
		HDEVNOTIFY				FDevNotify;
		HANDLE					FThread;
		CwclManualResetEvent*	FThreadEvent; // Thread ready event.
		HWND					FWnd;
		
		// Creation error.
		int	FError;
		
		bool GetDevClassSetupApi(const GUID& IntfClass, const tstring& DevName, GUID& DevClass);
		bool GetDevClassCfgMgrApi(const tstring& DevName, GUID& DevClass);
		
		static DWORD __stdcall _DeviceChangeNotification(WinApi::HCMNOTIFICATION hNotify, PVOID Context,
			WinApi::CM_NOTIFY_ACTION Action, WinApi::PCM_NOTIFY_EVENT_DATA EventData, DWORD EventDataSize);

		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();

		static LRESULT __stdcall _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void ProcessWmDestroy();
		void ProcessWmDeviceChange(const WPARAM wParam, const LPARAM lParam);
		bool WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		
		static int CreateBroadcaster();
		static void DeleteBroadcaster();

		/* Subscription management. */

		int InternalSubscribe(CwclMessageReceiver* const Receiver);
		int InternalUnsubscribe(CwclMessageReceiver* const Receiver);

		static int Subscribe(CwclMessageReceiver* const Receiver);
		static int Unsubscribe(CwclMessageReceiver* const Receiver);

		/* Message processing. */
		
		void InternalBroadcast(CwclMessage* const Message);
		int InternalPost(const long Id, CwclMessage* const Message);
		void InternalProcessMessages();
		
	public:
		/// <summary> Creates message broadcaster. </summary>
		/// <remarks> An application must never create the broadcaster
		///   directly. It is created when needed by the message
		///   receivers. </remarks>
		CwclMessageBroadcaster();
		/// <summary> Frees the message broadcaster. </summary>
		/// <remarks> An application must never destroy the broadcaster
		///   directly. It is destroyed when not needed any more by the message
		///   receivers. </remarks>
		virtual ~CwclMessageBroadcaster();

		/// <summary> Broadcasts a Message to all message receivers. </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object represented
		///   the message. A caller is responsible to free the <c>Message</c> object
		///   after procedure call. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <seealso cref="CwclMessage" />
		static int Broadcast(CwclMessage* const Message);
		/// <summary> Posts a Message to a message receiver with specified
		///   ID. </summary>
		/// <param name="Id"> A message receiver ID. </param>
		/// <param name="Message"> The <see cref="CwclMessage" /> object represents
		///   the message. A caller is responsible to free the <c>Message</c> object
		///   after procedure the call. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <seealso cref="CwclMessage" />
		static int Post(const long Id, CwclMessage* const Message);

		/// <summary> Force WCL message processing for current thread. </summary>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> This function can be used to force WCL message processing in
		///   case if your execution thread is blocked. </remarks>
		static int ProcessMessages();
	};

	/* Predefined WCL message IDs. */

	/// <summary> The Hardware Change message ID. </summary>
	const unsigned char WCL_MSG_ID_SYS_HARDWARE_CHANGED = 1;
}
