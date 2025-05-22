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

#include <exception>

#include "wclSync.h"

using namespace wclSync;

namespace wclCommon
{
	/// <summary> The structure contains detailed information about Wireless
	///   Communication Library error code. </summary>
	typedef struct
	{
		/// <summary> The error code. </summary>
		int Error;
		/// <summary> The framework name that the error relates to. </summary>
		tstring Framework;
		/// <summary> The error category. </summary>
		tstring Category;
		/// <summary> The error constant name. </summary>
		tstring Constant;
		/// <summary> The human readable error description. </summary>
		tstring Description;
	} wclErrorDetails;

	/// <summary> The class provides methods to get human readable information
	///   about Wireless Communication Library errors. </summary>
	class CwclErrorInformation
	{
		DISABLE_COPY(CwclErrorInformation);

	private:
		bool					FComInitialized;
		CwclCriticalSection*	FCS;
		
		IXMLDOMDocument*		FDocument;
		IXMLDOMElement*			FRootElement;
		IXMLDOMNodeList*		FFrameworks;
		
		void InitializeXmlDocument();

		bool GetFrameworksNodes();
		bool GetRootElement();
		bool InitializeCom();
		bool LoadDocument(const tstring& FileName);

		void ReleaseInterfaces();
		void UninitializeCom();

		bool GetAttributeText(IXMLDOMNode* const Node,
			const tstring& AttributeName, tstring& Text);
		void GetErrorDescription(IXMLDOMNode* const Node, tstring& Description);

		bool ErrorFound(IXMLDOMNode* const Node, const int Error);
		
	public:
		/// <summary> Creates new object. </summary>
		CwclErrorInformation();
		/// <summary> Free the object. </summary>
		virtual ~CwclErrorInformation();
		
		/// <summary> Closes the errors description file. </summary>
		/// <returns> <c>True</c> if the method completed with success. <c>False</c>
		///   otherwise. </returns>
		bool Close();
		/// <summary> Opens the errors description file. </summary>
		/// <param name="FileName"> Full path (including file name) to the
		///   errors.xml file. </param>
		/// <returns> <c>True</c> if errors file was opened. <c>False</c>
		///   otherwise. </returns>
		bool Open(const tstring& FileName);
		
		/// <summary> Gets the Wireless Communication Library error
		///   details. </summary>
		/// <param name="Error"> An error code. </param>
		/// <param name="Details"> If the method completed with success the
		///   Details structure will be fulfilled with the specified error
		///   details. </param>
		/// <returns> If the method completed with success the returning value is
		///   <c>True</c>. If the method failed the returning value is
		///   <c>False</c>. </returns>
		/// <seealso cref="wclErrorDetails" />
		bool GetDetails(const int Error, wclErrorDetails& Details);
		
		/// <summary> Gets the file state. </summary>
		/// <returns> <c>True</c> if the errors description file is opened.
		///   <c>False</c> otherwise. </returns>
		bool GetOpened() const;
		/// <summary> Gets the file state. </summary>
		/// <value> <c>True</c> if the errors description file is opened.
		///   <c>False</c> otherwise. </value>
		__declspec(property(get = GetOpened)) bool Opened;
	};

	/* Common error codes. */
	
	/// <summary> Operation completed with success. </summary>
	const int WCL_E_SUCCESS = 0x00000000;
	
	/// <summary> The base error code for the WCL system/common errors. </summary>
	const int WCL_E_BASE = 0x00010000;
	/// <summary> One or more arguments passed into the method or function are
	///   invalid. </summary>
	const int WCL_E_INVALID_ARGUMENT = WCL_E_BASE + 0x0000;
	/// <summary> Out of system memory. </summary>
	const int WCL_E_OUT_OF_MEMORY = WCL_E_BASE + 0x0001;
	
	/* Message receiver error codes. */
	
	/// <summary> The base error code for the message receiver. </summary>
	const int WCL_E_MR_BASE = WCL_E_BASE + 0x1000;
	/// <summary> A message receiver has already been closed or not opened. </summary>
	const int WCL_E_MR_CLOSED = WCL_E_MR_BASE + 0x0000;
	/// <summary> A message receiver has already been opened. </summary>
	const int WCL_E_MR_OPENED = WCL_E_MR_BASE + 0x0001;
	/// <summary> A message receiver was not opened yet. </summary>
	const int WCL_E_MR_NOT_OPENED = WCL_E_MR_BASE + 0x0002;
	/// <summary> A message receiver can not synchronize threads and notify
	///   a "main" thread about new received message. </summary>
	const int WCL_E_MR_UNABLE_SYNCHRONIZE = WCL_E_MR_BASE + 0x0003;
	/// <summary> A message receiver can not register for threads
	///   synchronization. </summary>
	const int WCL_E_MR_UNABLE_REGISTER_SYNC_OBJ = WCL_E_MR_BASE + 0x0004;
	/// <summary> A message receiver can not create a thread synchronization
	///   object. </summary>
	const int WCL_E_MR_UNABLE_CREATE_SYNC_OBJ = WCL_E_MR_BASE + 0x0005;
	/// <summary> A thread synchronization object has not been created. </summary>
	const int WCL_E_MR_SYNC_OBJ_NOT_CREATED = WCL_E_MR_BASE + 0x0006;
	/// <summary> An invalid thread used to call the method. </summary>
	const int WCL_E_MR_INVALID_THREAD = WCL_E_MR_BASE + 0x0007;
	/// <summary> Unable to create asynchronous message processing thread
	///   termination event. </summary>
	const int WCL_E_MR_UNABLE_CREATE_TERM_EVENT = WCL_E_MR_BASE + 0x0008;
	/// <summary> Invalid or unsupported message processing method. </summary>
	const int WCL_E_MR_INVALID_MESSAGE_PROCESSING_METHOD = WCL_E_MR_BASE + 0x0009;

	/* Message broadcaster error codes. */

	/// <summary> The base error code for the message broadcaster. </summary>
	const int WCL_E_MB_BASE = WCL_E_BASE + 0x2000;
	/// <summary> A message receiver has already been subscribed. </summary>
	const int WCL_E_MB_RECEIVER_ALREADY_SUBSCRIBED = WCL_E_MB_BASE + 0x0000;
	/// <summary> A message receiver has not been subscribed. </summary>
	const int WCL_E_MB_RECEIVER_NOT_SUBSCRIBED = WCL_E_MB_BASE + 0x0001;
	/// <summary> The message broadcaster can not initialize the hardware
	///   monitoring thread. </summary>
	const int WCL_E_MB_CAN_NOT_INIT_HW_THREAD = WCL_E_MB_BASE + 0x0002;
	/// <summary> The message broadcaster can not start the hardware monitoring
	///   thread. </summary>
	const int WCL_E_MB_CAN_NOT_START_HW_THREAD = WCL_E_MB_BASE + 0x0003;
	/// <summary> The message broadcaster can not create the hardware monitoring
	///   object. </summary>
	const int WCL_E_MB_UNABLE_CREATE_HW_OBJ = WCL_E_MB_BASE + 0x0004;
	/// <summary> The message broadcaster can not register for hardware changes
	///   notifications. </summary>
	const int WCL_E_MB_UNABLE_REGISTER_HW_NOTIFY = WCL_E_MB_BASE + 0x0005;
	/// <summary> The message broadcaster can not create a mutex synchronization
	///   object. </summary>
	const int WCL_E_MB_UNABLE_CREATE_MUTEX = WCL_E_MB_BASE + 0x0006;
	/// <summary> The message broadcaster was not created. </summary>
	const int WCL_E_MB_NOT_CREATED = WCL_E_MB_BASE + 0x0007;
	/// <summary> There is the error with the references counter. </summary>
	const int WCL_E_MB_REF_COUNT_ERROR = WCL_E_MB_BASE + 0x0008;
	/// <summary> The messaging subsystem is already running. </summary>
	const int WCL_E_MB_RUNNING = WCL_E_MB_BASE + 0x0009;
	/// <summary> Invalid or unknown synchronization method. </summary>
	const int WCL_E_MB_INVALID_SYNC_METHOD = WCL_E_MB_BASE + 0x000A;
	/// <summary> A timeout appeared during wait operation. </summary>
	const int WCL_E_MB_WAIT_TIMEOUT = WCL_E_MB_BASE + 0x000B;
	/// <summary> Wait operation failed. </summary>
	const int WCL_E_MB_WAIT_FAILED = WCL_E_MB_BASE + 0x000C;
	/// <summary> A message receiver with given ID was not found. </summary>
	const int WCL_E_MB_RECEIVER_NOT_FOUND = WCL_E_MB_BASE + 0x000D;

	/* WinRT subsystem error codes. */
	  
	/// <summary> The base WinRT subsystem error code. </summary>
	const int WCL_E_WINRT_BASE = WCL_E_BASE + 0x3000;
	/// <summary> Unable to create synchronization mutex for WinRT
	///   control. </summary>
	const int WCL_E_WINRT_UNABLE_CREATE_MUTEX = WCL_E_WINRT_BASE + 0x0000;
	/// <summary> unable to load WinRT core DLL. </summary>
	const int WCL_E_WINRT_UNABLE_LOAD_CORE_DLL = WCL_E_WINRT_BASE + 0x0001;
	/// <summary> unable to load WinRT string DLL. </summary>
	const int WCL_E_WINRT_UNABLE_LOAD_STRING_DLL = WCL_E_WINRT_BASE + 0x0002;
	/// <summary> WinRT initialization failed. </summary>
	const int WCL_E_WINRT_INIT_FAILED = WCL_E_WINRT_BASE + 0x0003;
	/// <summary> Unable to create string. </summary>
	const int WCL_E_WINRT_UNABLE_CREATE_STRING = WCL_E_WINRT_BASE + 0x0004;
	/// <summary> Unable to active instance of the required class. </summary>
	const int WCL_E_WINRT_UNABLE_ACTIVATE_INSTANCE = WCL_E_WINRT_BASE + 0x0005;
	/// <summary> Unable to create interface of the required class. </summary>
	const int WCL_E_WINRT_UNABLE_CREATE_INTERFACE = WCL_E_WINRT_BASE + 0x0006;
	/// <summary> Failed to read asynchronous operation status. </summary>
	const int WCL_E_WINRT_ASYNC_OPERATION_FAILED = WCL_E_WINRT_BASE + 0x0007;
	/// <summary> An asynchronous operation canceled. </summary>
	const int WCL_E_WINRT_ASYNC_OPERATION_CANCELLED = WCL_E_WINRT_BASE + 0x0008;
	/// <summary> An asynchronous operation completed with error. </summary>
	const int WCL_E_WINRT_ASYNC_OPERATION_ERROR = WCL_E_WINRT_BASE + 0x0009;
	/// <summary> Unable to detach raw buffer. </summary>
	const int WCL_E_WINRT_DETACH_BUFFER_FAILED = WCL_E_WINRT_BASE + 0x000A;
	/// <summary> An asynchronous operation timed out. </summary>
	const int WCL_E_WINRT_ASYNC_OPERATION_TIMEOUT = WCL_E_WINRT_BASE + 0x000B;

	/* WinUSB subsystem error codes. */

	/// <summary> The base error code for all WinUSB subsystem errors. </summary>
	const int WCL_E_WINUSB_BASE = WCL_E_BASE + 0x4000;
	/// <summary> Unable create WinSUB subsystem synchronization mutex. </summary>
	const int WCL_E_WINUSB_UNABLE_CREATE_MUTEX = WCL_E_WINUSB_BASE + 0x0000;
	/// <summary> WinUSB subsystem is not available on your system. </summary>
	const int WCL_E_WINUSB_UNABLE_LOAD = WCL_E_WINUSB_BASE + 0x0001;
	/// <summary> WinUSB subsystem was not loaded. </summary>
	const int WCL_E_WINUSB_NOT_LOADED = WCL_E_WINUSB_BASE + 0x0002;
	/// <summary> Unknown or unexpected WinUSB error. </summary>
	const int WCL_E_WINUSB_UNEXPECTED = WCL_E_WINUSB_BASE + 0x0003;
	/// <summary> A WinUSB device is already opened. </summary>
	const int WCL_E_WINUSB_DEVICE_OPENED = WCL_E_WINUSB_BASE + 0x0004;
	/// <summary> A WinUSB device is closed. </summary>
	const int WCL_E_WINUSB_DEVICE_CLOSED = WCL_E_WINUSB_BASE + 0x0005;
	/// <summary> A WinUSB device is not opened. </summary>
	const int WCL_E_WINUSB_DEVICE_NOT_OPENED = WCL_E_WINUSB_BASE + 0x0006;
	/// <summary> Unable to open specified WinUSB device. </summary>
	const int WCL_E_WINUSB_OPEN_DEVICE_FAILED = WCL_E_WINUSB_BASE + 0x0007;
	/// <summary> Initialize WinUSB device failed. </summary>
	const int WCL_E_WINUSB_INIT_DEVICE_FAILED = WCL_E_WINUSB_BASE + 0x0008;
	/// <summary> Control transfer failed. </summary>
	const int WCL_E_WINUSB_CONTROL_TRANSFER_FAILED = WCL_E_WINUSB_BASE + 0x0009;
	/// <summary> Read data from pipe (endpoint) failed. </summary>
	const int WCL_E_WINUSB_READ_PIPE_FAILED = WCL_E_WINUSB_BASE + 0x000A;

	/* WCL thread error codes. */

	/// <summary> The base error code for all WCL thread errors. </summary>
	const int WCL_E_THREAD_BASE = WCL_E_BASE + 0x5000;
	/// <summary> The thread is already running. </summary>
	const int WCL_E_THREAD_RUNNING = WCL_E_THREAD_BASE + 0x0000;
	/// <summary> Unable to create thread initialization event. </summary>
	const int WCL_E_THREAD_UNABLE_CREATE_THREAD_INIT_EVENT = WCL_E_THREAD_BASE + 0x0001;
	/// <summary> Unable to create thread. </summary>
	const int WCL_E_THREAD_UNABLE_CREATE_THREAD = WCL_E_THREAD_BASE + 0x0002;
	/// <summary> The thread is not running. </summary>
	const int WCL_E_THREAD_NOT_RUNNING = WCL_E_THREAD_BASE + 0x0003;
	/// <summary> The synchronization method is not supported by the wclThread
	///   class. </summary>
	const int WCL_E_THREAD_INVALID_SYNCHRONIZATION = WCL_E_THREAD_BASE + 0x0004;
	/// <summary> Unable to register thread message. </summary>
	const int WCL_E_THREAD_MESSAGE_REGISTRATION_FAILED = WCL_E_THREAD_BASE + 0x0005;
	/// <summary> Unable to create thread window. </summary>
	const int WCL_E_THREAD_WINDOW_CREATION_FAILED = WCL_E_THREAD_BASE + 0x0006;
	/// <summary> Thread user initialization failed. </summary>
	const int WCL_E_THREAD_INITIALIZATION_FAILED = WCL_E_THREAD_BASE + 0x0007;
	/// <summary> Unable to create thread termination event. </summary>
	const int WCL_E_THREAD_UNABLE_CREATE_THREAD_TERM_EVENT = WCL_E_THREAD_BASE + 0x0008;
	/// <summary> Unable to create thread synchronization event. </summary>
	const int WCL_E_THREAD_UNABLE_CREATE_THREAD_SYNC_EVENT = WCL_E_THREAD_BASE + 0x0009;

	/* Power monitoring error codes. */

	/// <summary> The base error code for Power Events monitor error codes. </summary>
	const int WCL_E_PEM_BASE = WCL_E_BASE + 0x6000;
	/// <summary> The power events monitor is already opened. </summary>
	const int WCL_E_PEM_OPENED = WCL_E_PEM_BASE + 0x0000;
	/// <summary> The power events monitor is already closed. </summary>
	const int WCL_E_PEM_CLOSED = WCL_E_PEM_BASE + 0x0001;
	/// <summary> The power state monitoring feature is supported on Windows 8 and
	///   above. </summary>
	const int WCL_E_PEM_FEATURE_NOT_SUPPORTED = WCL_E_PEM_BASE + 0x0002;
	/// <summary> Unable to get system power status. </summary>
	const int WCL_E_PEM_GET_POWER_STATUS_FAILED = WCL_E_PEM_BASE + 0x0003;
	/// <summary> Unable to create Power Events Window initialization
	///   event. </summary>
	const int WCL_E_PEM_CREATE_INIT_EVENT_FAILED = WCL_E_PEM_BASE + 0x0004;
	/// <summary> Unable to create and start Power Event Window thread. </summary>
	const int WCL_E_PEM_CREATE_WND_THREAD_FAILED = WCL_E_PEM_BASE + 0x0005;
	/// <summary> Unable to create Power Events Window. </summary>
	const int WCL_E_PEM_CREATE_WND_FAILED = WCL_E_PEM_BASE + 0x0006;

	/* Configuration Manager API error codes */

	/// <summary> The base error code for Configuration Manager error codes. </summary>
	const int WCL_E_CFGMGR_BASE = WCL_E_BASE + 0x7000;
	/// <summary> Unable to load Configuration Manager API. </summary>
	const int WCL_E_CFGMGR_LOAD_FAILED = WCL_E_CFGMGR_BASE + 0x0000;

	/* LAF error codes. */
	
	/// <summary> The base error code for Limited Access Feature
	///   errors. </summary>
	const int WCL_E_LAF_BASE = WCL_E_BASE + 0x8000;
	/// <summary> The LAF ID was not found. </summary>
	const int WCL_E_LAF_NOT_FOUND = WCL_E_LAF_BASE + 0x0000;
	/// <summary> Unable to access the LAF key information. </summary>
	const int WCL_E_LAF_OPEN_KEY_FAILED = WCL_E_LAF_BASE + 0x0001;
	/// <summary> The LAF key was not found. </summary>
	const int WCL_E_LAF_KEY_NOT_FOUND = WCL_E_LAF_BASE + 0x0002;
	/// <summary> Unable to load encryption DLL. </summary>
	const int WCL_E_LAF_DLL_LOAD_FAILED = WCL_E_LAF_BASE + 0x0003;
	/// <summary> Encryption functions not found. </summary>
	const int WCL_E_LAF_FUNC_NOT_FOUND = WCL_E_LAF_BASE + 0x0004;
	/// <summary> Unable to acquire encryption context. </summary>
	const int WCL_E_LAF_ACQUIRE_CONTEXT_FAILED = WCL_E_LAF_BASE + 0x0005;
	/// <summary> Unable to build hash. </summary>
	const int WCL_E_LAF_CREATE_HASH_FAILED = WCL_E_LAF_BASE + 0x0006;
	/// <summary> Unable to crypt the hash. </summary>
	const int WCL_E_LAF_CRYPT_HASH_FAILED = WCL_E_LAF_BASE + 0x0007;
	/// <summary> Unable to get crypted hash. </summary>
	const int WCL_E_LAF_GET_CRYPTED_HASH_FAILED = WCL_E_LAF_BASE + 0x0008;
	/// <summary> An application file does not contain the identity
	///   resource. </summary> 
	const int WCL_E_LAF_IDENTITY_NOT_FOUND = WCL_E_LAF_BASE + 0x0009;
	/// <summary> Unable to read the identity. </summary>
	const int WCL_E_LAF_IDENTITY_READ_FAILED = WCL_E_LAF_BASE + 0x000A;
	/// <summary> The identity has invalid format. </summary>
	const int WCL_E_LAF_IDENTITY_INVALID = WCL_E_LAF_BASE + 0x000B;
	/// <summary> The identity is empty. </summary>
	const int WCL_E_LAF_IDENTITY_EMPTY = WCL_E_LAF_BASE + 0x000C;
	/// <summary> The identity has invalid format. </summary>
	const int WCL_E_LAF_IDENTITY_INVALID_FORMAT = WCL_E_LAF_BASE + 0x000D;
	/// <summary> Request to unlock limited feature failed. </summary>
	const int WCL_E_LAF_UNLOCK_REQUEST_FAILED = WCL_E_LAF_BASE + 0x000E;
	/// <summary> Unable to get unlock request status. </summary>
	const int WCL_E_LAF_GET_REQUEST_STATUS_FAILED = WCL_E_LAF_BASE + 0x000F;
	/// <summary> The LAF is locked. </summary>
	const int WCL_E_LAF_LOCKED = WCL_E_LAF_BASE + 0x0010;
	/// <summary> The LAF unavailable because was not found. </summary>
	const int WCL_E_LAF_UNAVAILABLE = WCL_E_LAF_BASE + 0x0011;
	/// <summary> Unknown or undefined LAF status. </summary>
	const int WCL_E_LAF_STATUS_UNKNOWN = WCL_E_LAF_BASE + 0x0012;
	/// <summary> The LAF manager has already been opened. </summary>
	const int WCL_E_LAF_MANAGER_OPENED = WCL_E_LAF_BASE + 0x0013;
	/// <summary> The LAF manager was not opened. </summary>
	const int WCL_E_LAF_MANAGER_NOT_OPENED = WCL_E_LAF_BASE + 0x0014;
	/// <summary> The LAF manager is closed. </summary>
	const int WCL_E_LAF_MANAGER_CLOSED = WCL_E_LAF_BASE + 0x0015;
	/// <summary> Create LAF manager initialization event failed. </summary>
	const int WCL_E_LAF_MANAGER_CREATE_INIT_EVENT_FAILED = WCL_E_LAF_BASE + 0x0016;
	/// <summary> Create LAF manager termination event failed. </summary>
	const int WCL_E_LAF_MANAGER_CREATE_TERM_EVENT_FAILED = WCL_E_LAF_BASE + 0x0017;
	/// <summary> Unable to start the LAF manager working thread. </summary>
	const int WCL_E_LAF_MANAGER_START_THREAD_FAILED = WCL_E_LAF_BASE + 0x0018;
	/// <summary> The LAF feature is not supported on this platform. </summary>
	const int WCL_E_LAF_MANAGER_FEATURE_NOT_SUPPORTED = WCL_E_LAF_BASE + 0x0019;
	/// <summary> Unable to access the LAF list. </summary>
	const int WCL_E_LAF_MANAGER_GET_LAF_LIST_FAILED = WCL_E_LAF_BASE + 0x001A;

	/* Common WCL exceptions. */

	/// <summary> The base WCL exceptions class. </summary>
	class wclException : public std::exception
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclException(const char* msg) : std::exception(msg) { };
	};

	/// <summary> One or more arguments passed into constructor are
	///   invalid. </summary>
	/// <seealso cref="wclException" />
	class wclEInvalidArgument : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEInvalidArgument(const char* msg) : wclException(msg) { };
	};

	/// <summary> Not enough system memory. </summary>
	/// <seealso cref="wclException" />
	class wclEOutOfMemory : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEOutOfMemory(const char* msg) : wclException(msg) { };
	};

	/// <summary> The Power Events Monitor exceptions class. </summary>
	/// <seealso cref="wclException" />
	class wclEPowerEvents : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEPowerEvents(const char* msg) : wclException(msg) { };
	};

	/// <summary> Failed to open file. </summary>
	/// <seealso cref="wclException" />
	class wclEFileOpenFailed : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEFileOpenFailed(const char* msg) : wclException(msg) { };
	};
}