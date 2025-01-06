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

#include "wclHelpers.h"

namespace wclCommon
{
	#define WCL_WAIT_INFINITE	INFINITE
    #define WCL_WAIT_OBJECT_0	WAIT_OBJECT_0
    #define WCL_WAIT_TIMEOUT	WAIT_TIMEOUT
    #define WCL_WAIT_ERROR		WAIT_FAILED
	#define WCL_STILL_ACTIVE	STILL_ACTIVE

	/* Process and thread IDs */

	DWORD wclGetCurrentProcessId();
	DWORD wclGetCurrentThreadId();

	/* Mutex */

	HANDLE wclCreateMutex(const TCHAR* const, bool& Exist);
	HANDLE wclCreateMutex(const TCHAR* const);

	void wclAcquireMutex(HANDLE Mutex);
	void wclReleaseMutex(HANDLE Mutex);
	
	void wclCloseMutex(HANDLE& Mutex);
	void wclReleaseAndCloseMutex(HANDLE& Mutex);

	/* Event */

	HANDLE wclCreateAutoResetEvent();
	HANDLE wclCreateAutoResetEvent(const tstring& Name);

	HANDLE wclCreateManualResetEvent();
	HANDLE wclCreateManualResetEvent(const tstring& Name);
	
	HANDLE wclOpenEvent(const tstring& Name);
	
	void wclSetEvent(const HANDLE Event);
	void wclResetEvent(const HANDLE Event);
	
	int wclWaitEvent(const HANDLE Handle);
	int wclWaitEvent(const HANDLE Handle, const unsigned long Timeout);
	
	int wclWaitEvents(const unsigned char Count, HANDLE* const Handles);
	int wclWaitEvents(const unsigned char Count, HANDLE* const Handles,
		const unsigned long Timeout);
	
	void wclCloseEvent(HANDLE& Event);

	/* Thread */

	typedef UINT (__stdcall *PwclThreadProc)(void* Param);
	
	HANDLE wclCreateThread(PwclThreadProc Proc, void* const Param,
		unsigned int& ThreadId);

	HANDLE wclCreateThread(PwclThreadProc Proc, void* const Param,
		const bool Suspend);
	HANDLE wclCreateThread(PwclThreadProc Proc, void* const Param);
	
	void wclResumeThread(const HANDLE Thread);
	
	UINT wclGetThreadResult(const HANDLE Thread);
	
	void wclWaitThread(const HANDLE Thread);
	
	void wclCloseThread(HANDLE& Thread);
	void wclWaitAndCloseThread(HANDLE& Thread);
}