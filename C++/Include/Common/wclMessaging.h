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

#include <list>

#include "wclHelpers.h"
#include "wclErrors.h"

/// <summary> This macro helps to build correct documentation. </summary>
#define _WCL_COMMON_WINAPI_INCLUDE_FILE_ "wclWinAPI.h"
#include _WCL_COMMON_WINAPI_INCLUDE_FILE_

namespace wclCommon
{
	/// <summary> Message synchronization methods used to inter-threading
	///   synchronization and notification. </summary>
	typedef enum
	{
		/// <summary> Default synchronization method based on Windows
		///   Messages. </summary>
		/// <remarks> This synchronization is recommended for single threading UI
		///   applications. </remarks>
		skMessages,
		/// <summary> Asynchronous notifications. All events fire in a separate
		///   thread. An application is responsible for the synchronization with
		///   UI thread. Must be used carefully. </summary>
		/// <remarks> Your application should not use this synchronization method
		///   except just a few cases. Use <c>skApc</c> instead. </remarks>
		skThread,
		/// <summary> Asynchronous Procedure Call (APC) synchronization. </summary>
		/// <remarks> This synchronization method is good for non-UI or
		///   multi-threading applications. It can be used in UI applications but your
		///   application must process APC manually. </remarks>
		skApc
	} wclMessageSynchronizationKind;

	/// <summary> The message object. </summary>
	class CwclMessage
	{
		DISABLE_COPY(CwclMessage);

	private:
		unsigned char	FId;
		unsigned char	FCategory;
		LONG			FRefCounter;
		
	public:
		/// <summary> Creates new message object. </summary>
		/// <param name="Id"> The message ID. </param>
		/// <param name="Category"> The message category ID. </param>
		CwclMessage(const unsigned char Id, const unsigned char Category);
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
		unsigned char GetCategory() const;
		/// <summary> Gets the message category ID. </summary>
		/// <value> The message category ID. </value>
		__declspec(property(get = GetCategory)) unsigned char Category;

		/// <summary> Gets the message ID. </summary>
		/// <returns> The message ID. </returns>
		unsigned char GetId() const;
		/// <summary> Gets the message ID. </summary>
		/// <value> The message ID. </value>
		__declspec(property(get = GetId)) unsigned char Id;
	};

	/* Messages categories. */

	/// <summary> System messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_SYSTEM = 1;
	/// <summary> WiFi Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_WIFI = 2;
	/// <summary> Bluetooth Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_BLUETOOTH = 3;
	/// <summary> IrDA Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_IRDA = 4;
	/// <summary> Serial Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_SERIAL = 5;
	/// <summary> USB Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_USB = 6;
	/// <summary> Wii remote Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_WII = 7;
	/// <summary> Kinect Framework messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_KINECT = 8;
	/// <summary> The connections and connection providers messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_CONNECTION = 9;
	/// <summary> The audio switcher messages category. </summary>
	const unsigned char WCL_MSG_CATEGORY_AUDIO = 10;
		
	/// <summary> User defined message categories should start from this
	///   Category ID. </summary>
	const unsigned char WCL_MSG_CATEGORY_USER = 200;

	/* Predefined WCL message IDs. */

	/// <summary> The Hardware Change message ID. </summary>
	const unsigned char WCL_MSG_ID_SYS_HARDWARE_CHANGED = 1;
	/// <summary> The Power State Changed message ID. </summary>
	const unsigned char WCL_MSG_ID_SYS_POWER_STATE_CHANGED = 2;
	/// <summary> The WCL Thread Signal message ID. </summary>
	const unsigned char WCL_MSG_ID_SYS_THREAD_SIGNAL = 3;
	/// <summary> The WCL Thread Synchronize message ID. </summary>
	const unsigned char WCL_MSG_ID_SYS_THREAD_SYNCHRONIZE = 4;

	/// <summary> The system category message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclSystemCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclSystemCategoryMessage);
		
	public:
		/// <summary> Creates new system message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclSystemCategoryMessage(const unsigned char Id);
	};

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

	/// <summary> The Power State Changed message is broadcast to all
	///   subscribers when changes in the power state have been detected. The
	///   message ID is
	///   <see cref="WCL_MSG_ID_SYS_POWER_STATE_CHANGED" />. </summary>
	/// <remarks> This message is supported on Windows 8 and above. </remarks>
	/// <seealso cref="CwclSystemCategoryMessage" />
	class CwclPowerStateChangeMessage : public CwclSystemCategoryMessage
	{
		DISABLE_COPY(CwclPowerStateChangeMessage);
		
	private:
		ULONG FState;
		
	public:
		/// <summary> Creates new Power State Changed message object. </summary>
		/// <param name="State"> The current power state. </param>
		CwclPowerStateChangeMessage(const ULONG State);
		
		/// <summary> Gets the current power state. </summary>
		/// <returns> The current power state. </returns>
		ULONG GetState() const;
		/// <summary> Gets the current power state. </summary>
		/// <value> The current power state. </value>
		__declspec(property(get = GetState)) ULONG State;
	};

	/// <summary> The WCL Thread Signal message. </summary>
	/// <seealso cref="CwclSystemCategoryMessage" />
	class CwclThreadSignalMessage : public CwclSystemCategoryMessage
	{
		DISABLE_COPY(CwclThreadSignalMessage);
		
	private:
		unsigned char	FSignal;
		
	public:
		/// <summary> Creates new message object. </summary>
		/// <param name="Signal"> The thread signal ID. </param>
		CwclThreadSignalMessage(const unsigned char Signal);
		
		/// <summary> Gets the thread signal ID. </summary>
		/// <returns> The signal ID. </returns>
		unsigned char GetSignal() const;
		/// <summary> Gets the thread signal ID. </summary>
		/// <value> The signal ID. </value>
		__declspec(property(get = GetSignal)) unsigned char Signal;
	};

	/// <summary> The WCL Thread Synchronize message. </summary>
	/// <seealso cref="CwclSystemCategoryMessage" />
	class CwclThreadSynchronizeMessage : public CwclSystemCategoryMessage
	{
		DISABLE_COPY(CwclThreadSynchronizeMessage);
		
	private:
		HANDLE	FEvent;
		void*	FParam;
		
	public:
		/// <summary> Creates new message object. </summary>
		/// <param name="Event"> The synchronization event. </param>
		/// <param name="Param"> The pointer to the user-defined data. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclThreadSynchronizeMessage(const HANDLE Event, const void* const Param);
		/// <summary> Frees the object. </summary>
		~CwclThreadSynchronizeMessage();

		/// <summary> gets the pointer to the user-defined data. </summary>
		/// <returns> The pointer to the user-defined data. </returns>
		void* const GetParam() const;
		/// <summary> gets the pointer to the user-defined data. </summary>
		/// <value> The pointer to the user-defined data. </value>
		__declspec(property(get = GetParam)) void* const Param;
	};

	/// <summary> The WiFi Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclWiFiCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclWiFiCategoryMessage);
		
	public:
		/// <summary> Creates new WiFi message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclWiFiCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Bluetooth Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclBluetoothCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclBluetoothCategoryMessage);

	public:
		/// <summary> Creates new Bluetooth message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclBluetoothCategoryMessage(const unsigned char Id);
	};

	/// <summary> The IrDA Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclIrDACategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclIrDACategoryMessage);

	public:
		/// <summary> Creates new IrDA message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclIrDACategoryMessage(const unsigned char Id);
	};

	/// <summary> The Serial Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclSerialCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclSerialCategoryMessage);

	public:
		/// <summary> Creates new Serial message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclSerialCategoryMessage(const unsigned char Id);
	};

	/// <summary> The USB Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclUsbCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclUsbCategoryMessage);

	public:
		/// <summary> Creates new USB message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclUsbCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Wii Remote Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclWiiCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclWiiCategoryMessage);

	public:
		/// <summary> Creates new Wiimote message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclWiiCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Kinect Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclKinectCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclKinectCategoryMessage);

	public:
		/// <summary> Creates new Kinect message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclKinectCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Connection Category Message base class. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclConnectionCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclConnectionCategoryMessage);

	public:
		/// <summary> Creates new Connection message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclConnectionCategoryMessage(const unsigned char Id);
	};

	/// <summary> The Audio Switcher Category message object. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclAudioCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclAudioCategoryMessage);

	public:
		/// <summary> Creates new Audio Switcher message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclAudioCategoryMessage(const unsigned char Id);
	};

	/// <summary> The base class for user-defined messages. </summary>
	/// <seealso cref="CwclMessage" />
	class CwclUserDefinedCategoryMessage : public CwclMessage
	{
		DISABLE_COPY(CwclUserDefinedCategoryMessage);

	public:
		/// <summary> Creates new user-defined message object. </summary>
		/// <param name="Id"> The message ID. </param>
		CwclUserDefinedCategoryMessage(const unsigned char Id);
	};

	/// <summary> The <c>OnMessage</c> event handler prototype. </summary>
	/// <param name="Message"> The <see cref="CwclMessage" /> object represented
	///   a message. </param>
	/// <remarks> <para> The event always fires in the same thread which was used
	///   to create the receiver. </para>
	///   <para> The <c>Message</c> object is valid only inside an event
	///   handler. </para> </remarks>
	#define wclMessageEvent(_event_name_) \
		__event void _event_name_(const CwclMessage* const Message)

	/// <summary> The message receiver object. </summary>
	class CwclMessageReceiver
	{
		DISABLE_COPY(CwclMessageReceiver);
		
	private:
		friend class CwclMessageBroadcaster;

		typedef std::list<CwclMessage*> MESSAGES;

		wclMessageSynchronizationKind	FKind;
		MESSAGES*						FMessages; // Messages queue.
		RTL_CRITICAL_SECTION			FMessagesCS; // Messages queue synchronization.
		HANDLE							FThreadHandle; // Used for APC synchronization.
		DWORD							FThreadId; // ID of the thread that running the message loop.
		DWORD							FWndThreadId; // Used only in asynchronous mode.
		
		HANDLE	FWndThread;
		int		FWndThreadResult;
		HANDLE	FWndThreadEvent;
		
		bool	FListening;
		
		// Thread synchronization.
		UINT	FMsg;
		HWND	FWnd;

		// Always synchronized with "main" thread. Returns "true" if the message
		// was processed.
		static LRESULT __stdcall _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		static UINT __stdcall _WndThread(LPVOID lpParam);
		void WndThread();

		static void __stdcall MsgApcFunc(ULONG_PTR lpParam);
		
		// Always synchronized with "main" thread.
		int CreateSyncObj();
		int CreateSyncWnd();

		// Always synchronized with "main" thread.
		int DestroySyncObj();
		int DestroySyncWnd();
		
		// Can be called from any thread. The method MUST never raise any exception.
		int Synchronize();
		
		// Always synchronized with "main" thread.
		void ProcessMessages();
		
	protected:
		/// <summary> Fires the <c>OnMessage</c> event </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object
		///   represented the message. </param>
		/// <remarks> The <c>Message</c> parameter is valid only inside the
		///   method. The method is always called in the same thread which was used
		///   to create the receiver. </remarks>
		virtual void DoMessage(const CwclMessage* const Message);
		
	public:
		/// <summary> Creates new message receiver object. </summary>
		CwclMessageReceiver();
		/// <summary> Frees the message receiver. </summary>
		/// <remarks> The destructor must be called from the same thread which
		///   was used to create the receiver. </remarks>
		virtual ~CwclMessageReceiver();
		
		/// <summary> Closes the receiver and stops listening for the
		///   messages. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method must be called from the same thread which was
		///   used to create the receiver. </remarks>
		int Close();
		
		/// <summary> Opens the receiver and starts listening for the
		///   messages. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method must be called from the same thread which was
		///   used to create the receiver. </remarks>
		int Open();
		
		/// <summary> Posts the message into the messages queue. </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object represents
		///   a message. A caller is responsible to dispose the message object
		///   passed into the method. </param>
		/// <param name="Sync"> <para>I f the <c>Sync</c> parameter set to
		///   <c>true</c> and the thread that called the method is the same that
		///   opened the receiver the message will be delivered without putting it
		///   into the message queue. </para>
		///   <para> If the thread that posting the message is different than one
		///   that opened the receiver or the <c>Sync</c> parameter is <c>false</c>
		///   (the default value) the message will be posted into the message
		///   queue. </para> </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method can be called from any thread. </para>
		///   <para> Note that if sync messages is posted it can be processed
		///   before any other message in the queue. </para> </remarks>
		int Post(CwclMessage* const Message, const bool Sync = false);
		
		/// <summary> Gets the receiver state. </summary>
		/// <returns> <c>true</c> if the receiver is listening for the
		///   messages. </returns>
		bool _GetListening() const;
		/// <summary> Gets the receiver state. </summary>
		/// <value> <c>true</c> if the receiver is listening for the
		///   messages. </value>
		__declspec(property(get = _GetListening)) bool Listening;
		
		/// <summary> The event fires when a new message has been received. </summary>
		/// <param name="Message"> The <see cref="CwclMessage" /> object represented
		///   the message. </param>
		/// <remarks> <para> The event always fires in the same thread which was used
		///   to create the receiver. </para>
		///   <para> The <c>Message</c> object is valid only inside an event
		///   handler. </para> </remarks>
		wclMessageEvent(OnMessage);
	};

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
		RTL_CRITICAL_SECTION	FReceiversCS; // Subscribers list synchronization.

		// Power changes notification registration.
		HMODULE	FPowerDll;
		HANDLE	FPowerReg;
		
		// Hardware monitoring.
		bool		FCfgMgrLoaded;
		HDEVNOTIFY	FDevNotify;
		HANDLE		FThread;
		HANDLE		FThreadEvent; // Thread ready event.
		HWND		FWnd;
		
		// Creation error.
		int	FError;
		
		// Power changes notifications.
		void RegisterPowerChanges();
		void UnregisterPowerChanges();

		bool GetDevClassSetupApi(const GUID& IntfClass, const tstring& DevName, GUID& DevClass);
		bool GetDevClassCfgMgrApi(const tstring& DevName, GUID& DevClass);
		
		static DWORD __stdcall _DeviceChangeNotification(WinApi::HCMNOTIFICATION hNotify, PVOID Context,
			WinApi::CM_NOTIFY_ACTION Action, WinApi::PCM_NOTIFY_EVENT_DATA EventData, DWORD EventDataSize);

		static UINT __stdcall _ThreadProc(LPVOID lpParam);
		void ThreadProc();

		static LRESULT __stdcall _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void ProcessWmDestroy();
		void ProcessWmDeviceChange(const WPARAM wParam, const LPARAM lParam);
		void ProcessWmPowerBroadcast(const WPARAM wParam);
		bool WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		
		// Subscription management.
		int InternalSubscribe(CwclMessageReceiver* const Receiver);
		int InternalUnsubscribe(CwclMessageReceiver* const Receiver);
		
		static int CreateBroadcaster();
		static void DeleteBroadcaster();

		static int Subscribe(CwclMessageReceiver* const Receiver);
		static int Unsubscribe(CwclMessageReceiver* const Receiver);
		
		void InternalBroadcast(CwclMessage* const Message);

		/* Message processing. */
		
		void InternalProcessApcMessages();
		void InternalProcessThreadMessages();
		void InternalProcessWindowsMessages();
		void InternalProcessMessages();

		/* Wait functions. */
		
		int InternalWaitWindowsMessages(const unsigned long Count,
			const HANDLE* Events, const unsigned long Timeout,
			unsigned long& Index);
		int InternalWaitThread(const unsigned long Count,
			const HANDLE* Events, const unsigned long Timeout,
			unsigned long& Index);
		int InternalWaitApcMessages(const unsigned long Count,
			const HANDLE* Events, const unsigned long Timeout,
			unsigned long& Index);
		int InternalWait(const unsigned long Count, const HANDLE* Events,
			const unsigned long Timeout, unsigned long& Index);
		
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
		static int Broadcast(CwclMessage* const Message);

		/// <summary> Force WCL message processing for current thread. </summary>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> This function can be used to force WCL message processing in
		///   case if your execution thread is blocked. </remarks>
		static int ProcessMessages();
		
		/// <summary> Waits until one or all of the specified objects are in the
		///   signaled state or the time-out interval elapses. </summary>
		/// <param name="Count"> The number of object handles in the array pointed
		///   to by Events. The maximum number of object handles is 64. </param>
		/// <param name="Events"> An array of object handles. </param>
		/// <param name="Timeout"> The time-out interval, in milliseconds. If a
		///   nonzero value is specified, the function waits until the event is
		///   signaled or the interval elapses. If <c>Timeout</c> is zero, the
		///   function does not enter a wait state if the event is not signaled;
		///   it always returns immediately. If <c>Timeout</c> is <c>INFINITE</c>,
		///   the function will return only when the event is signaled. </param>
		/// <param name="Index"> If the function completed with success on output
		///   contains the index of the signaled object. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		static int Wait(const unsigned long Count, const HANDLE* Events,
			const unsigned long Timeout, unsigned long& Index);
		/// <summary> Waits until one or all of the specified objects are in the
		///   signaled state or the time-out interval elapses. </summary>
		/// <param name="Count"> The number of object handles in the array pointed
		///   to by Events. The maximum number of object handles is 64. </param>
		/// <param name="Events"> An array of object handles. </param>
		/// <param name="Index"> If the function completed with success on output
		///   contains the index of the signaled object. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		static int Wait(const unsigned long Count, const HANDLE* Events,
			unsigned long& Index);
		/// <summary> Waits until the specified event is in the signaled state or
		///   the time-out interval elapses. </summary>
		/// <param name="Event"> A handle to the event. </param>
		/// <param name="Timeout"> The time-out interval, in milliseconds. If a
		///   nonzero value is specified, the function waits until the event is
		///   signaled or the interval elapses. If <c>Timeout</c> is zero, the
		///   function does not enter a wait state if the event is not signaled;
		///   it always returns immediately. If <c>Timeout</c> is <c>INFINITE</c>,
		///   the function will return only when the event is signaled. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		static int Wait(HANDLE Event, unsigned long Timeout);
		/// <summary> Waits until the specified event is in the signaled
		///   state. </summary>
		/// <param name="Event"> A handle to the event. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		static int Wait(const HANDLE Event);
		
		/// <summary> Gets the current inter-threading synchronization method. </summary>
		/// <returns> The current inter-threading synchronization method. </returns>
		/// <seealso cref="wclMessageSynchronizationKind" />
		static wclMessageSynchronizationKind GetSyncMethod();
		/// <summary> Changes the current inter-threading synchronization
		///   method. </summary>
		/// <param name="Kind"> The new synchronization method. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> An application must call this method to change the current
		///   inter-threading synchronization method before any other call to
		///   WCL. </remarks>
		/// <seealso cref="wclMessageSynchronizationKind" />
		static int SetSyncMethod(const wclMessageSynchronizationKind Kind);
	};
}
