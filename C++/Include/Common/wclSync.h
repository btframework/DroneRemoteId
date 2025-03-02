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

using namespace wclCommon;

namespace wclSync
{
	/// <summary> Specifies the infinite wait interval. If this value is specified
	///   as a <c>Timeout</c> parameter value the Wait method will not returns
	///   until object signals. </summary>
	#define WCL_WAIT_INFINITE		0xFFFFFFFF
	
	/// <summary> Indicates the success wait result. </summary>
	#define WCL_WAIT_OBJECT_0		0x00000000
	
	/// <summary> Indicates the success wait result but one of the specified
	///   objects is a mutex object that was not released by the thread that owned
	///   the mutex object before the owning thread terminated. The returning
	///   value is the abandoned object index. </summary>
	#define WCL_WAIT_ABANDONED_0	0x00000080
	/// <summary> Indicates the success wait result but the wait objects is a
	///   mutex object that was not released by the thread that owned the mutex
	///   object before the owning thread terminated. </summary>
	/// <seealso cref="WAIT_ABANDONED_0" />
	#define WCL_WAIT_ABANDONED		WCL_WAIT_ABANDONED_0
	
	/// <summary> The time-out interval elapsed, and no one of the object is
	///   signaled. </summary>
	#define WCL_WAIT_TIMEOUT		0x00000102
	/// <summary> The wait method has failed. </summary>
	#define WCL_WAIT_FAILED			0xFFFFFFFF

	/// <summary> The base class for Wireless Communication Library
	///   synchronization objects. </summary>
	class CwclSyncObject
	{
		DISABLE_COPY(CwclSyncObject);

	protected:
		/// <summary> Creates new synchronization object. </summary>
		CwclSyncObject();

	public:
		/// <summary> Frees the synchronization object. </summary>
		virtual ~CwclSyncObject();
	};

	/// <summary> The base class for waitable synchronization objects. </summary>
	/// <seealso cref="CwclSyncObject" />
	class CwclWaitableSyncObject : public CwclSyncObject
	{
		DISABLE_COPY(CwclWaitableSyncObject);

	private:
		HANDLE	FHandle;

	protected:
		/// <summary> Creates new synchronization object. </summary>
		/// <param name="Handle"> A system dependent synchronization object
		///   handle. </param>
		CwclWaitableSyncObject(const HANDLE Handle);

		/// <summary> Waits until the object is in the signaled state. </summary>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the wait operation completed
		///   with success the waitable object is a mutex and the thread that owned
		///   that mutex has exited without releasing the mutex the returning value
		///   is <see cref="WCL_WAIT_ABANDONED" />. If the wait failed the returning
		///   value is <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		virtual unsigned long WaitOne();
		/// <summary> Waits until the object is in the signaled state or the
		///   time-out interval elapses. </summary>
		/// <param name="Timeout"> The wait timeout value. </param>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the wait operation completed
		///   with success the waitable object is a mutex and the thread that owned
		///   that mutex has exited without releasing the mutex the returning value
		///   is <see cref="WCL_WAIT_ABANDONED" />. If the time-out elapsed the
		///   returning value is <see cref="WCL_WAIT_TIMEOUT" />. If the wait failed
		///   the returning value is  <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_TIMEOUT" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		virtual unsigned long WaitOne(const unsigned long Timeout);

	public:
		/// <summary> Frees the waitable synchronization object. </summary>
		virtual ~CwclWaitableSyncObject();
		
		/// <summary> Waits until all of the specified objects are in the signaled
		///   state. </summary>
		/// <param name="Count"> A number of the waitable objects in the objects
		///   array. </param>
		/// <param name="Objects"> An array of waitable objects. </param>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the wait operation completed
		///   with success but one of the waitable object is a mutex and the thread
		///   that owned that mutex has exited without releasing the mutex the
		///   returning value is <see cref="WCL_WAIT_ABANDONED" />. If the wait
		///   failed the returning value is
		///   <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		/// <seealso cref="CwclWaitableSyncObject" />
		static unsigned long WaitAll(const unsigned long Count,
			CwclWaitableSyncObject** const Objects);
		/// <summary> Waits until all of the specified objects are in the signaled
		///   state or the time-out interval elapses. </summary>
		/// <param name="Count"> A number of the waitable objects in the objects
		///   array. </param>
		/// <param name="Objects"> An array of waitable objects. </param>
		/// <param name="Timeout"> The wait timeout value. </param>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the wait operation completed
		///   with success but one of the waitable object is a mutex and the thread
		///   that owned that mutex has exited without releasing the mutex the
		///   returning value is <see cref="WCL_WAIT_ABANDONED" />. If the time-out
		///   elapsed the returning value is <see cref="WCL_WAIT_TIMEOUT" />. If the
		///   wait failed the returning value is
		///   <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_TIMEOUT" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		/// <seealso cref="CwclWaitableSyncObject" />
		static unsigned long WaitAll(const unsigned long Count,
			CwclWaitableSyncObject** const Objects, const unsigned long Timeout);

		/// <summary> Waits until one or all of the specified objects are in the
		///   signaled state. </summary>
		/// <param name="Count"> A number of the waitable objects in the objects
		///   array. </param>
		/// <param name="Objects"> An array of waitable objects. </param>
		/// <returns> If the wait completed with success the returning value is a
		///   signaled object index starting from <see cref="WCL_WAIT_OBJECT_0" />.
		///   If the wait operation completed with success but one of the waitable
		///   object is a mutex and the thread that owned that mutex has exited
		///   without releasing the mutex the returning value is a mutex index
		///   starting from <see cref="WCL_WAIT_ABANDONED_0" />. If the wait
		///   failed the returning value is
		///   <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED_0" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		/// <seealso cref="CwclWaitableSyncObject" />
		static unsigned long WaitAny(const unsigned long Count,
			CwclWaitableSyncObject** const Objects);
		/// <summary> Waits until one of the specified objects are in the signaled
		///   state or the time-out interval elapses. </summary>
		/// <param name="Count"> A number of the waitable objects in the objects
		///   array. </param>
		/// <param name="Objects"> An array of waitable objects. </param>
		/// <param name="Timeout"> The wait timeout value. </param>
		/// <returns> If the wait completed with success the returning value is a
		///   signaled object index starting from <see cref="WCL_WAIT_OBJECT_0" />.
		///   If the wait operation completed with success but one of the waitable
		///   object is a mutex and the thread that owned that mutex has exited
		///   without releasing the mutex the returning value is a mutex index
		///   starting from <see cref="WCL_WAIT_ABANDONED_0" />. If the time-out
		///   elapsed the returning value is <see cref="WCL_WAIT_TIMEOUT" />. If the
		///   wait failed the returning value is
		///   <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED_0" />
		/// <seealso cref="WCL_WAIT_TIMEOUT" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		/// <seealso cref="CwclWaitableSyncObject" />
		static unsigned long WaitAny(const unsigned long Count,
			CwclWaitableSyncObject** const Objects, const unsigned long Timeout);

		/// <summary> Gets the system dependent synchronization object
		///   handle. </summary>
		/// <returns> The object handle. </returns>
		HANDLE GetHandle() const;
		/// <summary> Gets the system dependent synchronization object
		///   handle. </summary>
		/// <value> The object handle. </value>
		__declspec(property(get = GetHandle)) HANDLE Handle;
	};

	/// <summary> The base class for the Wireless Communication Library
	///   named synchronization objects. </summary>
	/// <seealso cref="CwclWaitableSyncObject" />
	class CwclNamedSyncObject : public CwclWaitableSyncObject
	{
		DISABLE_COPY(CwclNamedSyncObject);
	
	protected:
		/// <summary> Creates new synchronization object. </summary>
		/// <param name="Handle"> A system dependent synchronization object
		///   handle. </param>
		CwclNamedSyncObject(const HANDLE Handle);

		/// <summary> Makes unique synchronization object name. </summary>
		/// <param name="Name"> The synchronization object name. </param>
		/// <returns> The method returns the unique synchronization object name:
		///   the original object name expanded with the process ID. </returns>
		static tstring MakeUniqueName(const tstring& Name);

	public:
		/// <summary> Frees the named synchronization object. </summary>
		virtual ~CwclNamedSyncObject();
	};

	/// <summary> The class represents a creitical section synchronization
	///   primitive. </summary>
	/// <remarks> A critical section object provides synchronization similar to
	///   that provided by a mutex object, except that a critical section can be
	///   used only by the threads of a single process. Critical section objects
	///   cannot be shared across processes. </remarks>
	/// <seealso cref="CwclSyncObject" />
	class CwclCriticalSection : public CwclSyncObject
	{
		DISABLE_COPY(CwclCriticalSection);
		
	private:
		RTL_CRITICAL_SECTION	FCS;
		
	public:
		/// <summary> Creates and initializes a critical section object. </summary>
		CwclCriticalSection();
		/// <summary> Destroys the critical section object and releases all
		///   allocated resources. </summary>
		virtual ~CwclCriticalSection();
		
		/// <summary> Waits for ownership of the critical section object. </summary>
		/// <remarks> The function returns when the calling thread is granted
		///   ownership. </remarks>
		void Enter();
		/// <summary> Releases ownership of the critical section object. </summary>
		void Leave();
	};

	/// <summary> The class represents a mutex synchronization object. </summary>
	/// <remarks> A mutex object is a synchronization object whose state is set to
	///   signaled when it is not owned by any thread, and nonsignaled when it is
	///   owned. Only one thread at a time can own a mutex object, whose name
	///   comes from the fact that it is useful in coordinating mutually exclusive
	///   access to a shared resource. </remarks>
	/// <seealso cref="CwclNamedSyncObject" />
	class CwclMutex : public CwclNamedSyncObject
	{
		DISABLE_COPY(CwclMutex);

	private:
		CwclMutex(const HANDLE Handle);
		
	public:
		/// <summary> Creates an unnamed mutex object. </summary>
		/// <returns> If the method completed with success the returning value is
		///   a new <c>CwclMutex</c> class object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <seealso cref="CwclMutex" />
		static CwclMutex* Create();
		/// <summary> Creates or opens a named mutex object. </summary>
		/// <param name="Name"> The mutex name. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <c>CwclMutex</c> class object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <seealso cref="CwclMutex" />
		static CwclMutex* Create(const tstring& Name);
		/// <summary> Creates or opens a named mutex object. </summary>
		/// <param name="Name"> The mutex name. </param>
		/// <param name="Exist"> If the method completed with success the parameter
		///   indicates whether a named mutex object was just created or existing
		///   was opened. <c>True</c> indicates that a mutex object was opened.
		///   <c>False</c> indicates that a new mutex object was created. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <c>CwclMutex</c> class object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <seealso cref="CwclMutex" />
		static CwclMutex* Create(const tstring& Name, bool& Exist);

		/// <summary> Opens an existing mutex with the specified name. </summary>
		/// <param name="Name"> The mutex name. </param>
		/// <returns> If the method completed with success the returning value is
		///   a <c>CwclMutex</c> class object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <seealso cref="CwclMutex" />
		static CwclMutex* Open(const tstring& Name);
		
		/// <summary> Acquires the mutex object. </summary>
		/// <returns> If the mutex acquired with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the thread that owned that mutex
		///   has exited without releasing the mutex the returning value
		///   is <see cref="WCL_WAIT_ABANDONED" />. If the wait failed the returning
		///   value is <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		unsigned long Acquire();
		/// <summary> Tries to acquire the mutex object during the given time-out
		///   interval. </summary>
		/// <param name="Timeout"> The wait timeout value. </param>
		/// <returns> If the mutex acquired with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the thread that owned that mutex
		///   has exited without releasing the mutex the returning value
		///   is <see cref="WCL_WAIT_ABANDONED" />. If the time-out elapsed the
		///   returning value is <see cref="WCL_WAIT_TIMEOUT" />. If the wait failed
		///   the returning value is  <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_ABANDONED" />
		/// <seealso cref="WCL_WAIT_TIMEOUT" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		unsigned long Acquire(const unsigned long Timeout);

		/// <summary> Releases the mutex object. </summary>
		/// <returns> If the method completed with success the returning value is
		///   <c>True</c>. </returns>
		bool Release();
	};

	/// <summary> The class represents an event synchronization object. </summary>
	/// <remarks> An event object is a synchronization object whose state can be
	///   explicitly set to signaled by use of the SetEvent function. </remarks>
	/// <seealso cref="CwclNamedSyncObject" />
	class CwclEvent : public CwclNamedSyncObject
	{
		DISABLE_COPY(CwclEvent);

	protected:
		/// <summary> Creates new event object. </summary>
		CwclEvent(const HANDLE Handle);

	public:
		/// <summary> Waits until the object is in the signaled state. </summary>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the wait failed the returning
		///   value is <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		virtual unsigned long WaitOne() override;
		/// <summary> Waits until the object is in the signaled state or the
		///   time-out interval elapses. </summary>
		/// <param name="Timeout"> The wait timeout value. </param>
		/// <returns> If the wait completed with success the returning value is
		///   <see cref="WCL_WAIT_OBJECT_0" />. If the time-out elapsed the
		///   returning value is <see cref="WCL_WAIT_TIMEOUT" />. If the wait failed
		///   the returning value is  <see cref="WCL_WAIT_FAILED" />. </returns>
		/// <seealso cref="WCL_WAIT_OBJECT_0" />
		/// <seealso cref="WCL_WAIT_TIMEOUT" />
		/// <seealso cref="WCL_WAIT_FAILED" />
		virtual unsigned long WaitOne(const unsigned long Timeout) override;
		
		/// <summary> Creates an unnamed event object. </summary>
		/// <param name="ManualReset"> If this parameter is <c>true</c>, the
		///   method creates a manual-reset event object, which requires the use of
		///   the <c>ResetEvent</c> method to set the event state to nonsignaled.
		///   If this parameter is <c>false</c>, the method creates an auto-reset
		///   event object, and the system automatically resets the event state to
		///   nonsignaled after a single waiting thread has been released. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclEvent" />
		static CwclEvent* Create(const bool ManualReset);
		/// <summary> Creates or opens a named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <param name="ManualReset"> If this parameter is <c>true</c>, the
		///   method creates a manual-reset event object, which requires the use of
		///   the <c>ResetEvent</c> method to set the event state to nonsignaled.
		///   If this parameter is <c>false</c>, the method creates an auto-reset
		///   event object, and the system automatically resets the event state to
		///   nonsignaled after a single waiting thread has been released. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclEvent" />
		static CwclEvent* Create(const tstring& Name, const bool ManualReset);
		/// <summary> Creates or opens a named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <param name="ManualReset"> If this parameter is <c>true</c>, the
		///   method creates a manual-reset event object, which requires the use of
		///   the <c>ResetEvent</c> method to set the event state to nonsignaled.
		///   If this parameter is <c>false</c>, the method creates an auto-reset
		///   event object, and the system automatically resets the event state to
		///   nonsignaled after a single waiting thread has been released. </param>
		/// <param name="Exist"> If the method completed with success the parameter
		///   indicates whether a named event object was just created or existing
		///   was opened. <c>true</c> indicates that an event object was opened.
		///   <c>false</c> indicates that a new event object was created. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclEvent" />
		static CwclEvent* Create(const tstring& Name, const bool ManualReset,
			bool& Exist);
		
		/// <summary> Opens an existing named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <returns> If the method completed with success the returning value is
		///   an opened <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclEvent" />
		static CwclEvent* Open(const tstring& Name);
		
		/// <summary> Sets the event object to the nonsignaled state. </summary>
		/// <returns> If the method succeeds, the return value is <c>true</c>.
		///   If the method fails, the return value is <c>false</c>. </returns>
		bool ResetEvent();
		/// <summary> Sets the event object to the signaled state. </summary>
		/// <returns> If the method succeeds, the return value is <c>true</c>.
		///   If the method fails, the return value is <c>false</c>. </returns>
		bool SetEvent();
	};
	
	/// <summary> The class represents an auto-reset event synchronization
	///    object. </summary>
	/// <remarks> An event object is a synchronization object whose state can be
	///   explicitly set to signaled by use of the SetEvent function. </remarks>
	/// <seealso cref="CwclEvent" />
	class CwclAutoResetEvent : public CwclEvent
	{
		DISABLE_COPY(CwclAutoResetEvent);

	private:
		friend class CwclEvent;

		CwclAutoResetEvent(const HANDLE Handle);
		
	public:
		/// <summary> Creates an unnamed auto-reset event object. </summary>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclAutoResetEvent" />
		static CwclAutoResetEvent* Create();
		/// <summary> Creates or opens an auto-reset named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclAutoResetEvent" />
		static CwclAutoResetEvent* Create(const tstring& Name);
		/// <summary> Creates or opens an auto-reset named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <param name="Exist"> If the method completed with success the parameter
		///   indicates whether a named event object was just created or existing
		///   was opened. <c>true</c> indicates that an event object was opened.
		///   <c>false</c> indicates that a new event object was created. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclAutoResetEvent" />
		static CwclAutoResetEvent* Create(const tstring& Name, bool& Exist);
	};

	/// <summary> The class represents a manual-reset event synchronization
	///    object. </summary>
	/// <remarks> An event object is a synchronization object whose state can be
	///   explicitly set to signaled by use of the SetEvent function. </remarks>
	/// <seealso cref="CwclEvent" />
	class CwclManualResetEvent : public CwclEvent
	{
		DISABLE_COPY(CwclManualResetEvent);

	private:
		friend class CwclEvent;

		CwclManualResetEvent(const HANDLE Handle);
		
	public:
		/// <summary> Creates an unnamed manual-reset event object. </summary>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclManualResetEvent" />
		static CwclManualResetEvent* Create();
		/// <summary> Creates or opens a manual-reset named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclManualResetEvent" />
		static CwclManualResetEvent* Create(const tstring& Name);
		/// <summary> Creates or opens a manual-reset named event object. </summary>
		/// <param name="Name"> The event name. </param>
		/// <param name="Exist"> If the method completed with success the parameter
		///   indicates whether a named event object was just created or existing
		///   was opened. <c>true</c> indicates that an event object was opened.
		///   <c>false</c> indicates that a new event object was created. </param>
		/// <returns> If the method completed with success the returning value is
		///   a new <see cref="CwclEvent" /> object. If the method failed the
		///   returning value is <c>NULL</c>. </returns>
		/// <see cref="CwclManualResetEvent" />
		static CwclManualResetEvent* Create(const tstring& Name, bool& Exist);
	};
}

namespace wclCommon
{
	#define WCL_WAIT_ERROR		WAIT_FAILED
	#define WCL_STILL_ACTIVE	STILL_ACTIVE

	/* Process and thread IDs */

	DWORD wclGetCurrentProcessId();
	DWORD wclGetCurrentThreadId();

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