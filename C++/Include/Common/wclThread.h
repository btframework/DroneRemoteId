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

#include "wclErrors.h"
#include "wclHelpers.h"
#include "wclMessaging.h"

namespace wclCommon
{
	/// <summary> The class allows to use WCL components in threads, console and
	///   service applications. </summary>
	class CwclThread
	{
		DISABLE_COPY(CwclThread);

	private:
		typedef unsigned (__stdcall *THREAD_PROC)(void*);

		RTL_CRITICAL_SECTION	FCS;
		HANDLE					FInitEvent;
		int						FInitResult;
		UINT					FMsg;
		CwclMessageReceiver*	FReceiver;
		HANDLE					FSyncEvent;
		CwclMessageReceiver*	FSyncReceiver;
		HANDLE					FTermEvent;
		HANDLE					FThread;
		HWND					FWnd;

		int StartThread(THREAD_PROC Proc);
		void StopThread();

		void SyncMessageReceived(const CwclMessage* const Message);
		
		/* Messages synchronization. */

		static UINT __stdcall _WndThreadProc(LPVOID lpParam);
		void WndThreadProc();
		static LRESULT __stdcall _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
		int RunWndThread();

		/* APC and Separate thread synchronization. */

		static UINT __stdcall _ApcOrSeparateThreadProc(LPVOID lpParam);
		void ApcOrSeparateThread();
		int RunApcOrSeparateThread();

	protected:
		/// <summary> Executes a method call within the main thread. </summary>
		/// <param name="Param"> A pointer to any user-defined data. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> The method causes the <c>OnSynchronize</c> method to be
		///   executed using the main thread (the thread, that was used to call
		///   the <c>Run</c>). The thread execution is blocked until
		///   the <c>OnSynchronize</c> method completes. </remarks>
		int Synchronize(const void* const Param);

		/// <summary> The method called when new message received. </summary>
		/// <param name="Message"> The message object. </param>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);

		/// <summary> The method called by the thread when it just started.
		///   An application must override this method to execute initialization
		///   code. </summary>
		/// <returns> If initialization completed successfully the function must
		///   return <c>true</c>. Otherwise the function must return <c>false</c>. </returns>
		/// <remarks> The default implementation always returns <c>true</c>. </remarks>
		virtual bool OnInitialize();
		/// <summary> This procedure is called when a signal received from the
		///   other thread. </summary>
		/// <param name="Id"> The user defined signal ID. </param>
		virtual void OnSignal(const unsigned char Id);
		/// <summary> This procedure called by the <c>Syncrhonize</c>
		///   method. </summary>
		/// <param name="Param"> A pointer to an user-defined data. </param>
		/// <remarks> This method is always called in the main thread (the thread
		///   that called the <c>Run</c> method) context in response to the
		///   <c>Synchronize</c> method call. </remarks>
		virtual void OnSynchronize(const void* const Param);
		/// <summary> The procedure is called when the thread is about termination.
		///   An application must execute all finalization code here. </summary>
		virtual void OnTerminate();
		
	public:
		/// <summary> Creates new Thread object. </summary>
		/// <remarks> The constructor does not start the thread. </remarks>
		CwclThread();
		/// <summary> Terminates (if running) and frees the Thread
		///   object. </summary>
		virtual ~CwclThread();
		
		/// <summary> Starts the Thread execution. </summary>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> The method waits for thread initialization (refer to the
		///   <c>OnInitialize</c> method description). </remarks>
		int Run();
		/// <summary> Posts signal to the Thread. </summary>
		/// <param name="Id"> The user defined Signal ID. </param>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		/// <remarks> The signal is posted to the thread. That means that
		///   the method does not wait when the Thread receives and processes the
		///   signal. Also the method can not know if thread processed the
		///   signal. </remarks>
		int Signal(const unsigned char Id);
		/// <summary> Terminates the thread. </summary>
		/// <returns> If the function succeed the returns value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the function returns one
		///   of the WCL error codes. </returns>
		int Terminate();
		
		/// <summary> Gets the thread state. </summary>
		/// <returns> <c>true</c> if the Thread is running. <c>false</c>
		///   otherwise. </returns>
		bool GetRunning();
		/// <summary> Gets the thread state. </summary>
		/// <value> <c>true</c> if the Thread is running. <c>false</c>
		///   otherwise. </value>
		__declspec(property(get = GetRunning)) bool Running;
	};
}