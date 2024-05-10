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

#include <exception>

namespace wclCommon
{
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

	/* Configuration Manager API error codes */

	/// <summary> The base error code for Configuration Manager error codes. </summary>
	const int WCL_E_CFGMGR_BASE = WCL_E_BASE + 0x7000;
	/// <summary> Unable to load Configuration Manager API. </summary>
	const int WCL_E_CFGMGR_LOAD_FAILED = WCL_E_CFGMGR_BASE + 0x0000;

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

	/// <summary> Critical exception. </summary>
	/// <seealso cref="wclException" />
	class wclECritical : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclECritical(const char* msg) : wclException(msg) { };
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