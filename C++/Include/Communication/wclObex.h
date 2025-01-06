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

#include <vector>
#include <set>

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "wclConnections.h"

using wclCommon::tstring;
using wclCommon::CwclStream;

namespace wclCommunication
{
	/// <summary> The common OBEX operation result event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The operation result code. If operation has been
	///   completed with success the <c>Error</c> is
	///   <seealso cref="WCL_E_SUCCESS" />. </param>
	/// <param name="Description"> Additional optional description of the
	///   operation result. </param>
	#define wclObexOperationResultEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error, const tstring& Description)
	/// <summary> The <c>OnProgress</c> event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Length"> The current object's length (size) in
	///   bytes. </param>
	/// <param name="Position"> The current transferring byte index. </param> 
	#define wclObexOperationProgressEvent(_event_name_) \
		__event void _event_name_(void* Sender, const unsigned long Length, \
		const unsigned long Position)

	/// <summary> The base class for OBEX client data processors. </summary>
	/// <seealso cref="CwclCustomClientDataProcessor" />
	class CwclCustomObexClient : public CwclCustomClientDataProcessor
	{
		DISABLE_COPY(CwclCustomObexClient);
		
	private:
		bool			FAbort; // Indicates that we want to abort operation.
		tstring			FAbortDescription; // Used in abort operation.
		unsigned char*	FBuffer; // Internal buffer.
		unsigned long	FBufferSize; // Internal buffer size.
		bool			FConnected; // OBEX session status.
		unsigned long	FConnectionId;
		tstring			FDescription; // Used in Get operation.
		unsigned short	FMaxSize; // Maximum server's OBEX packet size.
		unsigned char	FPrevRequest; // Used to store request ID that is aborting.
		unsigned char	FRequest; // Current operation.
		unsigned long	FSize; // Used in Get operation.
		CwclStream*		FStream; // Used in PUT and GET operations.
		
		void InitParameters();

		int ExecuteAbort();
		
		// Operation response handler. It is guaranteed that the Buffer contains
		// full OBEX packet.
		void ProcessAbort(const unsigned char* const Buffer);
		void ProcessConnect(const unsigned char* const Buffer);
		void ProcessDisconnect(const unsigned char* const Buffer);
		void ProcessGet(const unsigned char* const Buffer);
		void ProcessPut(const unsigned char* const Buffer);
		void ProcessSetPath(const unsigned char* const Buffer);

		void ProcessResponse(const unsigned char* const Buffer);
		
	protected:
		/// <summary> Connects to an OBEX server. </summary>
		/// <param name="Target">Specifies the UUID of the desired application.
		///   If the <c>Target</c> is not used it must be set to NULL GUID. </param>
		/// <param name="Who">Can also be used when it is necessary to identify the
		///   client initiating the exchange. If the <c>Who</c> is not used it must
		///   be set to NULL GUID. </param>
		/// <param name="Description">Provides an information about the device
		///   or service. If the <c>Description</c> is not used it must be set to
		///   an empty string.</param>
		/// <param name="PacketSize"> The maximum OBEX packet size. The minimum
		///   allowed value is 0x00FF. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks><para> <c>Target</c> and <c>Who</c> are used to hold a unique
		///   identifier, which allows applications to tell whether they are
		///   talking to a strict peer, or not. Typically, this is used to enable
		///   additional capabilities supplied only by an exact peer. </para>
		///   <para> On full-featured [PC] platforms, multiple OBEX applications may
		///   exist concurrently. This leads to the need for the client to be able
		///   to uniquely identify which server it wants to handle its request. The
		///   server is therefore identified with the OBEX <c>Target</c> header. If
		///   necessary, the client can also identify itself, using the OBEX
		///   <c>Who</c> header. The following text describes the exact uses of these
		///   headers. </para>
		///   <para> To target a specific application with OBEX commands the client
		///   must set-up a connection to the application by using the OBEX
		///   <c>Target</c> header in a CONNECT request. This type of connection is
		///   called a directed connection and provides a virtual binding between
		///   the client and server. The <c>Target</c> header should specify the
		///   UUID of the desired application. The <c>Who</c> header can also be
		///   used when it is necessary to identify the client initiating the
		///   exchange. The <c>Who</c> header should be used in cases where
		///   the target server application supports different client applications
		///   and may care which one it is connecting to. It is unnecessary to send
		///   a <c>Who</c> header in the request if its only logical value is the
		///   same as the <c>Target</c> header. </para> </remarks>
		int Connect(const GUID& Target, const GUID& Who, const tstring& Description,
			const unsigned short PacketSize);
		/// <summary> Requests an object from a server. </summary>
		/// <param name="Name"> The object's name. If the parameter is an empty
		///   string the Name is ignored.  </param>
		/// <param name="Mime"> The object's MIME type. If the parameter is an empty
		///   string the Mime is ignored. </param>
		/// <param name="Stream"> The object's data stream. This must be valid
		///   empty stream object. The stream must have write access
		///   permission. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts receiving an object from an OBEX
		///   server. When sending is completed the <c>OnGetComplete</c> event fires
		///   with the operation result. </para>
		///   <para> The Stream object passed to the method must be valid until
		///   <c>OnGetComplete</c> event fires. An application can destroy the
		///   stream object passed as the <c>Stream</c> parameter only after
		///   <c>OnGetComplete</c> event fired. </para>
		///   <para> During execution of the Get operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Get(const tstring& Name, const tstring& Mime, CwclStream* const Stream);
		/// <summary> Sends one object from the client to the server. </summary>
		/// <param name="Name"> The object's name. If the parameter is an empty
		///   string the Name is ignored.  </param>
		/// <param name="Mime"> The object's MIME type. If the parameter is an empty
		///   string the Mime is ignored. </param>
		/// <param name="Description"> The object's description. If the parameter is
		///   an empty string the Description is ignored. </param>
		/// <param name="Stream"> The object's data stream. If the parameter is
		///   <c>NULL</c> it forces to delete the object with the name specified
		///   by the <c>Name</c> parameter or with MIME type specified by the
		///   <c>Mime</c> parameter. If the <c>Stream</c> parameter is an empty
		///   stream (it is not <c>NULL</c> and the Stream size is <c>0</c>)
		///   it forces a server to create an empty object with the given Name or
		///   MIME. </param>
		/// <param name="AppParams"> The application parameters raw bytes. </param>
		/// <param name="AppParamsLength"> The length of the application parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts sending an object (or other operation
		///   described above) to a OBEX server. When sending is completed the
		///   <c>OnPutComplete</c> event fires with the operation result. </para>
		///   <para> If an application passes a valid Stream object to the method
		///   the object must be valid until <c>OnPutComplete</c> event fires.
		///   An application can destroy the stream object passed as the
		///   <c>Stream</c> parameter only after <c>OnPutComplete</c> event
		///   fired. </para>
		///   <para> During execution of the Put operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Put(const tstring& Name, const tstring& Mime, const tstring& Description,
			CwclStream* const Stream, const unsigned char* const AppParams,
			const unsigned short AppParamsLength);
		/// <summary> Changes the current directory on the server's side. </summary>
		/// <param name="Dir"> The directory name. If the <c>Dir</c> value is
		///   <c>".."</c> it tells to the server to backup a level (go one level
		///   up). If the <c>Dir</c> is an empty string it tells to the server to
		///   go to the default (root) directory). </param>
		/// <param name="Create"> If this parameter is set to <c>True</c> it tells
		///   server to create new directory with the given name. If this parameter
		///   is set to <c>False</c> and the directory specified in the <c>Dir</c>
		///   parameter does not exists the <c>WCL_E_OBEX_BAD_REQUEST</c> or
		///   the <c>WCL_E_OBEX_FORBIDDEN</c> error returned as the operation
		///   complete result. </param>
		/// <remarks> The method sets the current directory on the receiving side in
		///   order to enable transfers that need additional path information. For
		///   instance, when a nested set of directories is sent between two
		///   machines, <c>SetPath</c> is used to create the directory structure on
		///   the receiving side. </remarks>
		int SetPath(const tstring& Dir, const bool Create);
		
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		virtual void DoConnect(const int Error, const tstring& Description);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		virtual void DoDisconnect(const int Error, const tstring& Description);
		/// <summary> The method called when the OBEX GET operation has been
		///   completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoGetComplete(const int Error, const tstring& Description,
			CwclStream* const Stream);
		/// <summary> Fires the <c>OnProgress</c> event. </summary>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Position"> The current transferring byte index. </param>
		virtual void DoProgress(const unsigned long Length, const unsigned long Position);
		/// <summary> The method called when the OBEX PUT operation has been
		///   completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoPutComplete(const int Error, const tstring& Description,
			CwclStream* const Stream);
		/// <summary> The method called when the OBEX SET_PATH operation has
		///   been completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		virtual void DoSetPathComplete(const int Error, const tstring& Description);
		
	public:
		/// <summary> Creates new OBEX Client Data Processor. </summary>
		/// <param name="Connection"> A <see cref="CwclClientDataConnection" />
		///   object that is used to communicate with a remote device. </param>
		/// <seealso cref="CwclClientDataConnection" />
		CwclCustomObexClient(CwclClientDataConnection* const Connection);
		/// <summary> Frees the Data Processor. </summary>
		virtual ~CwclCustomObexClient();

		/// <summary> The method called by the Connection when data has been
		///   received from a remote device. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the method it must
		///   allocate own buffer and copy data. </param>
		/// <param name="Size"> The data buffer size. </param>
		virtual void ProcessData(const void* const Data, const unsigned long Size) override;
		
		/// <summary> Aborts current operation executing. </summary>
		/// <param name="Description"> An optional text value that describes
		///   the abort reason or provides any other information for
		///   a user on the server size. If this parameter is an empty string
		///   the description will not be sent to a server. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> Only <c>Pun</c> and <c>Get</c> operations can be
		///   aborted. </remarks>
		int Abort(const tstring& Description);
		/// <summary> Disconnects from an OBEX server. </summary>
		/// <param name="Description"> An optional text value that describes
		///   the disconnect reason or provides any other information for
		///   a user on the server size. If this parameter is an empty string
		///   the description will not be sent to a server. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect(const tstring& Description);
		
		/// <summary> Gets the connected state. </summary>
		/// <returns> <c>True</c> if the OBEX session was established. <c>False</c>
		///   otherwise. </returns>
		bool GetConnected() const;
		/// <summary> Gets the connected state. </summary>
		/// <value> <c>True</c> if the OBEX session was established. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetConnected)) bool Connected;
		
		/// <summary> The event fires when the Connect operation has been completed
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		wclObexOperationResultEvent(OnConnect);
		/// <summary> The event fires when the Disconnect operation
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		wclObexOperationResultEvent(OnDisconnect);
		/// <summary> The event fires during sending or receiving an object
		///   to indicate operation progress. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Position"> The current transferring byte index. </param> 
		wclObexOperationProgressEvent(OnProgress);
	};

	/// <summary> The Put and Get OBEX operations result event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The operation result code. If operation has been
	///   completed with success the <c>Error</c> is
	///   <seealso cref="WCL_E_SUCCESS" />. </param>
	/// <param name="Description"> Additional optional description of the
	///   operation result. </param>
	/// <param name="Stream"> The stream object used in operation. </param>
	/// <seealso cref="CwclStream" />
	#define wclObexObjectOperationResultEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error, const tstring& Description, \
		CwclStream* const Stream)

	/// <summary> The base class for OBEX file based clients: OPP, FTP,
	///   etc. </summary>
	/// <remarks> The class provides some basic events and methods that are common
	///   for all file based OBEX clients. </remarks>
	/// <seealso cref="CwclCustomObexClient" />
	class CwclObexFileClient : public CwclCustomObexClient
	{
		DISABLE_COPY(CwclObexFileClient);
		
	protected:
		/// <summary> Fires the <c>OnGetComplete</c> event. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoGetComplete(const int Error, const tstring& Description,
			CwclStream* const Stream) override;
		/// <summary> Fires the <c>OnPutComplete</c> event. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoPutComplete(const int Error, const tstring& Description,
			CwclStream* const Stream) override;
		
	public:
		/// <summary> Creates new OBEX File Client Data Processor. </summary>
		/// <param name="Connection"> A <see cref="CwclClientDataConnection" />
		///   object that is used to communicate with a remote device. </param>
		/// <seealso cref="CwclClientDataConnection" />
		CwclObexFileClient(CwclClientDataConnection* const Connection);
		/// <summary> Frees the object. </summary>
		virtual ~CwclObexFileClient();
		
		/// <summary> Sends one object from the client to the server. </summary>
		/// <param name="Name"> The object's name. If the parameter is an empty
		///   string the Name is ignored.  </param>
		/// <param name="Description"> The object's description. If the parameter is
		///   an empty string the Description is ignored. </param>
		/// <param name="Stream"> The object's data stream. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts sending an object to an OBEX server.
		///   When sending is completed the <c>OnPutComplete</c> event fires with
		///   the operation result. </para>
		///   <para> If an application passes a valid Stream object to the method
		///   the object must be valid until <c>OnPutComplete</c> event fires.
		///   An application can destroy the stream object passed as the
		///   <c>Stream</c> parameter only after <c>OnPutComplete</c> event
		///   fired. </para>
		///   <para> During execution of the Put operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Put(const tstring& Name, const tstring& Description, CwclStream* const Stream);
		
		/// <summary> The event fires when the Get operation has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <remarks> If the operation completed with success the Stream object
		///   contains the object's data. If the operation completed with error
		///   the Stream contains a partial data and is invalid. An application can
		///   not use the object from the Stream if the operation completed with
		///   error. </remarks>
		/// <seealso cref="CwclStream" />
		wclObexObjectOperationResultEvent(OnGetComplete);
		/// <summary> The event fires when the Put operation has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <remarks> An application can dispose the Stream object passed to the Put
		///   method. The state of the Stream object is changed. </remarks>
		/// <seealso cref="CwclStream" />
		wclObexObjectOperationResultEvent(OnPutComplete);
	};

	/// <summary> The data processor implements the OBEX Object Push Profile
	///   (OPP) client. </summary>
	/// <seealso cref="CwclObexFileClient" />
	class CwclObexOppClient : public CwclObexFileClient
	{
		DISABLE_COPY(CwclObexOppClient);
		
	public:
		/// <summary> Creates new ObjectPush Profile client. </summary>
		/// <param name="Connection"> A <see cref="CwclClientDataConnection" />
		///   object that is used to communicate with a remote device. </param>
		/// <seealso cref="CwclClientDataConnection" />
		CwclObexOppClient(CwclClientDataConnection* const Connection);
		/// <summary> Frees the object. </summary>
		virtual ~CwclObexOppClient();
		
		/// <summary> Connects to an OBEX server. </summary>
		/// <param name="PacketSize"> The maximum OBEX packet size. The minimum
		///   allowed value is 0x00FF. The default value is 0xFFFF. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect(const unsigned short PacketSize = 0xFFFF);
		
		/// <summary> The function reads the default object with given type from an
		///   OBEX Push server. </summary>
		/// <param name="aType"> The object's type. </param>
		/// <param name="Stream"> The object's data stream. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> This function can be used to pull (request) the default
		///   business card (vCard) from a target device. To do that the
		///   <c>aType</c> parameter must be "text/x-vCard" string. </para>
		///   <para> An application must pass a valid Stream object to the method
		///   and the stream object must be valid until <c>OnGetComplete</c> event
		///   fires. An application can destroy the stream object passed as the
		///   <c>Stream</c> parameter only after <c>OnGetComplete</c> event
		///   fired. </para>
		///   <para> During execution of the Get operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Get(const tstring& aType, CwclStream* const Stream);
	};

	/// <summary> The OBEX file object permission. </summary>
	typedef enum
	{
		/// <summary> Read permission. </summary>
		/// <remarks> The <c>READ</c> permission applies to all object types. It
		///   indicates that an attempt to <c>GET</c> the named object should
		///   successfully retrieve its contents. </remarks>
		opRead,
		/// <summary> Write permission. </summary>
		/// <remarks> The <c>WRITE</c> permission applies to all object types. It
		///   indicates that an attempt to modify the contents of the file by
		///   <c>PUT</c>’ing to the file should succeed. For folder objects it
		///   indicates that attempts to create a folder or other object within that
		///   folder should succeed. </remarks>
		opWrite,
		/// <summary> Delete permission. </summary>
		/// <remarks> The <c>DELETE</c> permission applies to file types. It
		///   indicates that the file may be removed by sending a <c>DELETE</c>
		///   command. </remarks>
		opDelete
	} wclObexFilePermission;

	/// <summary> The OBEX file object permissions. </summary>
	/// <seealso cref="wclObexFilePermission" />
	typedef std::set<wclObexFilePermission> wclObexFilePermissions;

	/// <summary> The record describes the OBEX file system object. </summary>
	typedef struct
	{
		/// <summary> If this member is <c>True</c> the file system object is
		///   directory. If this member is <c>False</c> the file system object
		///   if file. </summary>
		bool IsDirectory;
		/// <summary> The file system object name. </summary>
		tstring Name;
		/// <summary> The object's description. </summary>
		tstring Description;
		/// <summary> The file system object size in bytes. If the file system
		///   object is directory this member is always 0. </summary>
		unsigned long Size;
		/// <summary> The user level permissions. </summary>
		/// <remarks> A permission indicator does not imply that the appropriate
		///   command is guaranteed to work – just that it might. Other system
		///   specific limitations, such as limitations on available space for
		///   storing objects, may cause an operation to fail, where the permission
		///   flags may have indicated that it was likely to succeed. The
		///   permissions are a guide only. Some systems may have more specific
		///   permissions than those listed here, such systems should map those
		///   to the flags defined as best they are able. </remarks>
		/// <seealso cref="wclObexFilePermissions" />
		wclObexFilePermissions Permissions;
		/// <summary> The last modified time for the object. </summary>
		SYSTEMTIME Modified;
		/// <summary> The creation time for the object. </summary>
		SYSTEMTIME Created;
		/// <summary> The last accessed time for the object. </summary>
		SYSTEMTIME Accessed;
	} wclObexFileObject;

	/// <summary> Array of file system objects. </summary>
	/// <seealso cref="wclObexFileObject" />
	typedef std::list<wclObexFileObject> wclObexFileObjects;

	/// <summary> The <c>OnDirComplete</c> event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The operation result code. If operation has been
	///   completed with success the <c>Error</c> is
	///   <seealso cref="WCL_E_SUCCESS" />. </param>
	/// <param name="Description"> Additional optional description of the
	///   operation result. </param>
	/// <param name="Dirs"> The array of file system objects. This parameter can
	///   be <c>nil</c> if no file system objects found in current directory or
	///   if <c>Error</c> parameter is not <see cref="WCL_E_SUCCESS" />. </param>
	/// <seealso cref="wclObexFileObjects" />
	#define wclObexFtpDirCompleteEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error, const tstring& Description, \
		const wclObexFileObjects& Dirs)

	/// <summary> The data processor implements the OBEX File Transfer Profile
	///   (FTP) client. </summary>
	/// <seealso cref="CwclObexFileClient" />
	class CwclObexFtpClient : public CwclObexFileClient
	{
		DISABLE_COPY(CwclObexFtpClient);

	private:
		// The internal opcode. Helps to decode such operations as Dir, MkDir, etc.
		unsigned char FOpCode;
		
		void ConvertObexDateTime(const std::wstring& DateStr, SYSTEMTIME& DateTime);
		void ParseDirs(CwclStream* const Stream, const tstring& ResDesc);
		
	protected:
		/// <summary> The method called when the OBEX GET operation has been
		///   completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoGetComplete(const int Error, const tstring& Description,
			CwclStream* const Stream) override;
		/// <summary> The method called when the OBEX PUT operation has been
		///   completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Stream"> The stream object used in operation. </param>
		/// <seealso cref="CwclStream" />
		virtual void DoPutComplete(const int Error, const tstring& Description,
			CwclStream* const Stream) override;
		/// <summary> The method called when the OBEX SET_PATH operation has
		///   been completed. </summary>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		virtual void DoSetPathComplete(const int Error,
			const tstring& Description) override;
		
	public:
		/// <summary> Creates new OBEX File Transfer Profile Client Data
		///   Processor. </summary>
		/// <param name="Connection"> A <see cref="CwclClientDataConnection" />
		///   object that is used to communicate with a remote device. </param>
		/// <seealso cref="CwclClientDataConnection" />
		CwclObexFtpClient(CwclClientDataConnection* const Connection);
		/// <summary> Frees the data processor. </summary>
		virtual ~CwclObexFtpClient();
		
		/// <summary> Connects to an OBEX server. </summary>
		/// <param name="PacketSize"> The maximum OBEX packet size. The minimum
		///   allowed value is 0x00FF. The default value is 0xFFFF. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect(const unsigned short PacketSize = 0xFFFF);
		
		/// <summary> Changes current directory to the child directory. </summary>
		/// <param name="Name"> The child directory name. Use ".." to go one level
		///   up. Use empty name to go to the root directory. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> When operation completed the <c>OnChangeDirComplete</c>
		///   event fires. </remarks>
		int ChangeDir(const tstring& Name);
		/// <summary> Deletes the object with given name. </summary>
		/// <param name="Name"> The object's name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The object can be any object: file, directory, virtual
		///   object. </para>
		///   <para> When the operation completed the <c>OnDeleteComplete</c> event
		///   fires. </para> </remarks>
		int Delete(const tstring& Name);
		/// <summary> Requests the files listing for the current
		///   directory. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> When operation completed the <c>OnDirComplete</c> event
		///   fires. </remarks>
		int Dir();
		/// <summary> Requests an object from a server. </summary>
		/// <param name="Name"> The object's name. If the parameter is an empty
		///   string the Name is ignored.  </param>
		/// <param name="Stream"> The object's data stream. This must be valid
		///   empty stream object. The stream must have write access
		///   permission. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts receiving an object from an OBEX
		///   server. When sending is completed the <c>OnGetComplete</c> event fires
		///   with the operation result. </para>
		///   <para> The Stream object passed to the method must be valid until
		///   <c>OnGetComplete</c> event fires. An application can destroy the
		///   stream object passed as the <c>Stream</c> parameter only after
		///   <c>OnGetComplete</c> event fired. </para>
		///   <para> During execution of the Get operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Get(const tstring& Name, CwclStream* const Stream);
		/// <summary> Creates new directory. </summary>
		/// <param name="Name"> The directory name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> When operation completed the <c>OnMakeDirComplete</c>
		///   event fires. </para>
		///   <para> If the operation completed with success the current directory
		///   is changed to the just created directory. </para> </remarks>
		int MkDir(const tstring& Name);
		/// <summary> Sends one object from the client to the server. </summary>
		/// <param name="Name"> The object's name. </param>
		/// <param name="Description"> The object's description. If the parameter is
		///   an empty string the Description is ignored. </param>
		/// <param name="Stream"> The object's data stream. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts sending an object to an OBEX server.
		///   When sending is completed the <c>OnPutComplete</c> event fires with
		///   the operation result. </para>
		///   <para> If an application passes a valid Stream object to the method
		///   the object must be valid until <c>OnPutComplete</c> event fires.
		///   An application can destroy the stream object passed as the
		///   <c>Stream</c> parameter only after <c>OnPutComplete</c> event
		///   fired. </para>
		///   <para> During execution of the Put operation the <c>OnProgress</c>
		///   event may (or may not) fire indicating the operation
		///   progress. </para> </remarks>
		/// <seealso cref="CwclStream" />
		int Put(const tstring& Name, const tstring& Description,
			CwclStream* const Stream);
		
		/// <summary> The event fires when the change directory operation has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		wclObexOperationResultEvent(OnChangeDirComplete);
		/// <summary> The event fires when the delete operation has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		wclObexOperationResultEvent(OnDeleteComplete);
		/// <summary> The event fires when directory listing has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		/// <param name="Dirs"> The array of file system objects. This parameter can
		///   be <c>nil</c> if no file system objects found in current directory or
		///   if <c>Error</c> parameter is not <see cref="WCL_E_SUCCESS" />. </param>
		/// <seealso cref="wclObexFileObjects" />
		wclObexFtpDirCompleteEvent(OnDirComplete);
		/// <summary> The event fires when the creating directory operation has been
		///   completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation result code. If operation has been
		///   completed with success the <c>Error</c> is
		///   <seealso cref="WCL_E_SUCCESS" />. </param>
		/// <param name="Description"> Additional optional description of the
		///   operation result. </param>
		wclObexOperationResultEvent(OnMakeDirComplete);
	};

	/// <summary> The possible OBEX server operation results that can be returned
	///   to the client. </summary>
	typedef enum
	{
		/// <summary> The success result. Operation completed or started with
		///   success. </summary>
		orSuccess,
		/// <summary> The request was valid, but the server is refusing action. The
		///   user might not have the necessary permissions for an
		///   object. </summary>
		orForbidden,
		/// <summary> The requested object could not be found. </summary>
		orObjectNotFound,
		/// <summary> The request entity has a media type which the server or
		///   resource does not support. For example, the client uploads an image as
		///   image/svg+xml, but the server requires that images use a different
		///   format. </summary>
		orUnsupportedMedia,
		/// <summary> Similar to <c>orForbidden</c>, but specifically for use when
		///   authentication is required and has failed or has not yet been
		///   provided. </summary>
		orAccessDenied,
		/// <summary> Unexpected or unknown OBEX result code. </summary>
		orUnexpected
	} wclObexServerOperationResult;

	/// <summary> The OBEX server data processor <c>OnDisconnect</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Reason"> The disconnection reason code. </param>
	/// <param name="Description"> The disconnect reason description. </param>
	#define wclObexServerClientDisconnectedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Reason, \
		const tstring& Description)
	/// <summary> The OBEX server data processor <c>OnGetCompleted</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The operation completion reason code. If operation
	///   completed with success the <c>Error</c> is WCL_E_SUCCESS. </param>
	/// <param name="Stream"> The requested OBEX object's data stream. This is the
	///   same stream object that was passed to the <c>OnGetRequest</c> event
	///   handler. An application can dispose the stream in this event
	///   handler.</param>
	/// <seealso cref="CwclStream" />
	#define wclObexServerClientGetCompletedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error, \
		CwclStream* const Stream)
	/// <summary> The OBEX server data processor <c>OnPutProgress</c> and
	///   <c>OnGetProgress</c> operations event handler. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Position"> The current position in object's data in
	///   bytes </param>
	/// <param name="Length"> The current object's length (size) in
	///   bytes. </param>
	/// <param name="Continue"> An application must set this flag to <c>True</c>
	///   if still want continue process the object. If application wants to
	///   terminate the operation set this flags to <c>False</c>. </param>
	#define wclObexServerClientOperationProgressEvent(_event_name_) \
		__event void _event_name_(void* Sender, const unsigned long Position, \
		const unsigned long Length, bool& Continue)
	/// <summary> The OBEX server data processor <c>OnPutBegin</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Name"> The object's name. Can be empty. </param>
	/// <param name="Description"> The object's description. Can be
	///   empty. </param>
	/// <param name="Mime"> The object's MIME type. Can be empty. </param>
	/// <param name="Length"> The object's data size (length) in bytes.
	///   Can be 0. </param>
	/// <param name="Accept"> Must be set to <c>True</c> to accept object.
	///   If set to <c>False</c> the object will be rejected. </param>
	#define wclObexServerClientPutBeginEvent(_event_name_) \
		__event void _event_name_(void* Sender, const tstring& Name, \
		const tstring& Description, const tstring& Mime, \
		const unsigned long Length, bool& Accept)
	/// <summary> The OBEX server data processor <c>OnPutCompleted</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The operation completion reason code. If operation
	///   completed with success the <c>Reason</c> is WCL_E_SUCCESS. An
	///   application may accept or reject all the object by setting the
	///   <c>Accept</c> parameter. </param>
	/// <param name="Stream"> The received object's data stream. </param>
	/// <param name="Accept"> Set this parameter to <c>True</c> to accept the
	///   object. Set this parameter to <c>False</c> to reject the object. In case
	///   if object rejected the OBEX Forbidden error will be send. </param>
	/// <remarks> The <c>Stream</c> parameter contains the received object's data.
	///   This parameter is valid only inside the event handler and must be saved
	///   or copied by an application if an application needs to use it later.
	///   The <c>Stream</c> parameter can be <c>NULL</c> or empty if received
	///   object does not have body (data). </remarks>
	/// <seealso cref="CwclStream" />
	#define wclObexServerClientPutCompletedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const int Error, CwclStream* const Stream, \
		bool& Accept)

	/// <summary> The base class for OBEX server data processors. </summary>
	/// <seealso cref="CwclCustomServerClientDataProcessor" />
	class CwclCustomObexServer : public CwclCustomServerClientDataProcessor
	{
		DISABLE_COPY(CwclCustomObexServer);
		
	private:
		/* Internal fields */
		
		unsigned char*	FBuffer; // Internal buffer.
		unsigned long	FBufferSize; // Internal buffer size.
		bool			FConnecting; // Indicates connection request processing.
		unsigned short	FMaxSize; // Maximum client's OBEX packet size.
		unsigned char	FOperation; // Current OBEX operation.
		CwclStream*		FStream; // Object's stream. Used in PUT and GET operations.

		/* GET request fields. */
		
		bool			FFinalBitSet;
		tstring			FMime;
		tstring			FName;
		
		/* Property fields */
		
		unsigned long	FConnectionId; // Current connection ID.
		tstring			FDescription; // Server's description.
		GUID			FTarget; // The current connected client's ID.
		GUID			FWho; // The server's service ID.
		
		/* Helper methods */
		
		// Generates unique Connection ID.
		int GenerateConnectionId();
		void ReleaseStream();

		/* GET helpers. */
		
		void ResetGetFields();
		void ResetGetOperation();
		
		/* Request processing methods */
		
		// Handles OBEX ABORT request.
		void ProcessAbort(const unsigned char* const Buffer);
		// Handles OBEX CONNECT request.
		void ProcessConnect(const unsigned char* const Buffer);
		// Handles OBEX DISCONNECT request.
		void ProcessDisconnect(const unsigned char* const Buffer);
		// Handles OBEX GET request.
		void ProcessGet(const unsigned char* const Buffer);
		// Handles OBEX PUT request.
		void ProcessPut(const unsigned char* const Buffer);
		
		// Decodes request and calls specific handler.
		void ProcessRequest(const unsigned char* const Buffer);
		
		/* Response methods */
		
		// Sends object's size to the GET request.
		void SendObjectSize();
		// Sends object's body to the GET request.
		void SendObjectBody();
		// Sends response for other than connect requests.
		void SendResponse(const unsigned char Id, const unsigned long ConId,
			const tstring& Description);
		// Sends reject response on connect request.
		void SendRejectResponse(const tstring& Description);

		/* Completion method callers. */
		
		// Helper procedure that calls DoGetCompleted event. It fires the event and
		// then resets the stream pointer.
		void CallDoGetCompleted(const int Error);
		// Helper procedure that calls DoGetRequest event.
		void CallDoGetRequest(wclObexServerOperationResult& Result,
			CwclStream*& Stream);
		// Helper procedure that calls DoPutCompleted event. It resets the stream
		// position and then fires the event.
		void CallDoPutCompleted(const int Error, bool& Accept);
		
	protected:
		/// <summary> The method called when a remote client opens OBEX session
		///   (connects). </summary>
		/// <param name="Target"> The requested target service/server ID. </param>
		/// <param name="Who"> The client's ID. </param>
		/// <param name="Description"> The connect operation's or client's
		///   description. </param>
		/// <remarks> <para> A derived class must override this method to
		///   accept or reject connection. The default implementation rejects
		///   any connection requests. </para>
		///   <para> To accept connection an implementation must call the
		///   <c>Accept</c> method. To reject the connection request an
		///   implementation must call the <c>Reject</c> method. </para>
		///   <para> In case the <c>Target</c> and/or <c>Who</c> values were not
		///   provided by a client the values of these parameters are
		///   <c>GUID_NULL</c>. If the <c>Description</c> was not provided by a
		///   client the value of this parameter is an empty
		///   string. </para> </remarks>
		virtual void DoConnect(const GUID& Target, const GUID& Who,
			const tstring& Description);
		/// <summary> Fires the <c>OnDisconnected</c> event. </summary>
		/// <param name="Reason"> The disconnection reason code. </param>
		/// <param name="Description"> The disconnect reason description. </param>
		virtual void DoDisconnected(const int Reason, const tstring& Description);
		/// <summary> Fires the <c>OnGetCompleted</c> event. </summary>
		/// <param name="Error"> The operation completion reason code. If operation
		///   completed with success the <c>Error</c> is WCL_E_SUCCESS. </param>
		/// <param name="Stream"> The requested OBEX object's data stream. This is
		///   the same stream object that was passed to the <c>OnGetRequest</c>
		///   event handler. An application can dispose the stream in this event
		///   handler.</param>
		virtual void DoGetCompleted(const int Error, CwclStream* const Stream);
		/// <summary> The method called when the GET request received from a
		///   OBEX OPP Client. </summary>
		/// <param name="Name"> The requested OBEX object's name. </param>
		/// <param name="Mime"> The requested OBEX object's MIME type. </param>
		/// <param name="Result"> An application must set this parameter to the
		///   operation result code. If an application can send the requested object
		///   the <c>Result</c> must be set to <c>orSuccess</c>. </param>
		/// <param name="Stream"> The requested OBEX object's data stream. An
		///   application must provide the object's stream only in case if the
		///   <c>Result</c> set to <c>orSuccess</c>. In any other case the
		///   <c>Stream</c> must be set to <c>NULL</c>. The stream object passed to
		///   the event must be valid during all Get operation and can be released
		///   when the <c>OnGetCompleted</c> event received. </param>
		/// <seealso cref="wclObexServerOperationResult" />
		/// <seealso cref="CwclStream" />
		virtual void DoGetRequest(const tstring& Name, const tstring& Mime,
			wclObexServerOperationResult& Result, CwclStream*& Stream);
		/// <summary> Fires the <c>OnProgress</c> event. </summary>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Position"> The current transferring byte index. </param>
		virtual void DoProgress(const unsigned long Length,
			const unsigned long Position);
		/// <summary> Fires the <c>OnPutBegin</c> event. </summary>
		/// <param name="Name"> The object's name. Can be empty. </param>
		/// <param name="Description"> The object's description. Can be
		///   empty. </param>
		/// <param name="Mime"> The object's MIME type. Can be empty. </param>
		/// <param name="Length"> The object's data size (length) in bytes.
		///   Can be 0. </param>
		/// <param name="Accept"> Must be set to <c>True</c> to accept object.
		///   If set to <c>False</c> the object will be rejected. </param>
		/// <remarks> The method called when first PUT packet received. </remarks>
		virtual void DoPutBegin(const tstring& Name, const tstring& Description,
			const tstring& Mime, const unsigned long Length, bool& Accept);
		/// <summary> Fires the <c>OnPutCompleted</c> event. </summary>
		/// <param name="Error"> The operation completion reason code. If operation
		///   completed with success the <c>Reason</c> is WCL_E_SUCCESS. An
		///   application may accept or reject all the object by setting the
		///   <c>Accept</c> parameter. </param>
		/// <param name="Stream"> The received object's data stream. </param>
		/// <param name="Accept"> Set this parameter to <c>True</c> to accept the
		///   object. Set this parameter to <c>False</c> to reject the object. In
		///   case if object rejected the OBEX Forbidden error will be
		///   send. </param>
		/// <remarks> The <c>Stream</c> parameter contains the received object's
		///   data. This parameter is valid only inside the event handler and must
		///   be saved or copied by an application if an application needs to use it
		///   later. The <c>Stream</c> parameter can be <c>NULL</c> or empty if
		///   received object does not have body (data). </remarks>
		/// <seealso cref="CwclStream" />
		virtual void DoPutCompleted(const int Error, CwclStream* const Stream,
			bool& Accept);
		/// <summary> Fires the <c>OnPutProgress</c> event. </summary>
		/// <param name="Position"> The current position in object's data in
		///   bytes </param>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Continue"> An application must set this flag to
		///   <c>True</c> if still want continue process the object. If application
		///   wants to terminate the operation set this flags to
		///   <c>False</c>. </param>
		virtual void DoPutProgress(const unsigned long Position, const unsigned long Length,
			bool& Continue);

		/// <summary> The service ID that is implemented by the server. </summary>
		/// <returns> The UUID of the service. </returns>
		virtual GUID GetWho() const;
		__declspec(property(get = GetWho)) GUID Who;

	public:
		/// <summary> Creates new OBEX Server Client Data Processor. </summary>
		/// <param name="Connection"> A
		///   <see cref="CwclServerClientDataConnection" /> object that is used to
		///   communicate with a remote device. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		CwclCustomObexServer(CwclServerClientDataConnection* const Connection);
		/// <summary> Frees the Data Processor. </summary>
		virtual ~CwclCustomObexServer();

		/// <summary> The method called by the Connection when data has been
		///   received from a remote device. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the method it must
		///   allocate own buffer and copy data. </param>
		/// <param name="Size"> The data buffer size. </param>
		virtual void ProcessData(const void* const Data, const unsigned long Size) override;
		
		/// <summary> Accepts the client's connection request. </summary>
		/// <param name="Description"> The service's description. </param>
		/// <param name="PacketSize"> The maximum OBEX packet size. The minimum
		///   allowed value is 0x00FF. The default value is 0xFFFF. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application calls this method from <c>DoConnect</c>
		///   method or from <c>OnConnect</c> event handler to accept the connection
		///   request. </para>
		///   <para> If the method completed with success the <c>ConnectionId</c>
		///   property has valid connection ID that can be used to unique identify
		///   the connected client. </para>
		///   <para> If method failed the connection request has been rejected by
		///   the implementation. </para> </remarks>
		int Accept(const tstring& Description, const unsigned short PacketSize = 0xFFFF);
		/// <summary> Rejects the connection request. </summary>
		/// <param name="Description"> The string description of the rejection
		///   reason. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application calls this method from <c>DoConnect</c>
		///   method or from <c>OnConnect</c> event handler to reject the connection
		///   request. </para> </remarks>
		int Reject(const tstring& Description);
		
		/// <summary> Gets the connected state. </summary>
		/// <returns> <c>True</c> if the OBEX session was established (client is
		///   connected). <c>False</c> otherwise. </returns>
		bool GetConnected() const;
		/// <summary> Gets the connected state. </summary>
		/// <value> <c>True</c> if the OBEX session was established (client is
		///   connected). <c>False</c> otherwise. </value>
		__declspec(property(get = GetConnected)) bool Connected;

		/// <summary> Connection ID. </summary>
		/// <returns> The unique connection ID of the current OBEX session. Zero if
		///   client is not connected yet. </returns>
		/// <remarks> <para> The Connection ID is assigned internally when a remote
		///   client opens OBEX session. An application may use this value to unique
		///   identify the connected client and/or session. </para>
		///   <para> The Connect ID value is unique per application. If the
		///   Connection ID is zero the OBEX session has not been established
		///   yet. </para> </remarks>
		unsigned long GetConnectionId() const;
		/// <summary> Connection ID. </summary>
		/// <value> The unique connection ID of the current OBEX session. Zero if
		///   client is not connected yet. </value>
		/// <remarks> <para> The Connection ID is assigned internally when a remote
		///   client opens OBEX session. An application may use this value to unique
		///   identify the connected client and/or session. </para>
		///   <para> The Connect ID value is unique per application. If the
		///   Connection ID is zero the OBEX session has not been established
		///   yet. </para> </remarks>
		__declspec(property(get = GetConnectionId)) unsigned long ConnectionId;

		/// <summary> The current server's description. </summary>
		/// <returns> The string value that describes the server. </returns>
		tstring GetDescription() const;
		/// <summary> The current server's description. </summary>
		/// <value> The string value that describes the server. </value>
		__declspec(property(get = GetDescription)) tstring Description;

		/// <summary> The current connected client's ID. </summary>
		/// <returns> The UUID of the current connected client. </returns>
		/// <remarks> If the connected client did not provide its ID the value
		///  of this property is <c>GUID_NULL</c>. </remarks>
		GUID GetTarget() const;
		/// <summary> The current connected client's ID. </summary>
		/// <value> The UUID of the current connected client. </value>
		/// <remarks> If the connected client did not provide its ID the value
		///  of this property is <c>GUID_NULL</c>. </remarks>
		__declspec(property(get = GetTarget)) GUID Target;
		
		/// <summary> The event fires when a remote client closes the OBEX session
		///   (disconnects). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection reason code. </param>
		/// <param name="Description"> The disconnect reason description. </param>
		wclObexServerClientDisconnectedEvent(OnDisconnected);
		/// <summary> The event fires when the get request completed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation completion reason code. If operation
		///   completed with success the <c>Error</c> is WCL_E_SUCCESS. </param>
		/// <param name="Stream"> The requested OBEX object's data stream. This is the
		///   same stream object that was passed to the <c>OnGetRequest</c> event
		///   handler. An application can dispose the stream in this event
		///   handler.</param>
		/// <seealso cref="CwclStream" />
		wclObexServerClientGetCompletedEvent(OnGetCompleted);
		/// <summary> The event fires during sending the object. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Position"> The current transferring byte index. </param> 
		wclObexOperationProgressEvent(OnProgress);
		/// <summary> The event fires when client started object sending (OBEX PUT)
		///   operation. An application must accept or reject the object. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Name"> The object's name. Can be empty. </param>
		/// <param name="Description"> The object's description. Can be
		///   empty. </param>
		/// <param name="Mime"> The object's MIME type. Can be empty. </param>
		/// <param name="Length"> The object's data size (length) in bytes.
		///   Can be 0. </param>
		/// <param name="Accept"> Must be set to <c>True</c> to accept object.
		///   If set to <c>False</c> the object will be rejected. </param>
		wclObexServerClientPutBeginEvent(OnPutBegin);
		/// <summary> The event fires when all object has been received. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The operation completion reason code. If operation
		///   completed with success the <c>Reason</c> is WCL_E_SUCCESS. An
		///   application may accept or reject all the object by setting the
		///   <c>Accept</c> parameter. </param>
		/// <param name="Stream"> The received object's data stream. </param>
		/// <param name="Accept"> Set this parameter to <c>True</c> to accept the
		///   object. Set this parameter to <c>False</c> to reject the object. In case
		///   if object rejected the OBEX Forbidden error will be send. </param>
		/// <remarks> The <c>Stream</c> parameter contains the received object's data.
		///   This parameter is valid only inside the event handler and must be saved
		///   or copied by an application if an application needs to use it later.
		///   The <c>Stream</c> parameter can be <c>NULL</c> or empty if received
		///   object does not have body (data). </remarks>
		wclObexServerClientPutCompletedEvent(OnPutCompleted);
		/// <summary> The event fires during receiving the object. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Position"> The current position in object's data in
		///   bytes </param>
		/// <param name="Length"> The current object's length (size) in
		///   bytes. </param>
		/// <param name="Continue"> An application must set this flag to <c>True</c>
		///   if still want continue process the object. If application wants to
		///   terminate the operation set this flags to <c>False</c>. </param>
		/// <remarks> The event may fire one or more times per object. </remarks>
		wclObexServerClientOperationProgressEvent(OnPutProgress);
	};

	/// <summary> The <c>OnConnect</c> even handler prototype for the
	///   OBEX Object Push Profile Server data processor. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Description"> The client's description. </param>
	#define wclObexOppServerConnectEvent(_event_name_) \
		__event void _event_name_(void* Sender, const tstring& Description)
	/// <summary> The OBEX server data processor <c>OnGetRequest</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="aType"> The requested OBEX object type. </param>
	/// <param name="Result"> An application must set this parameter to the
	///   operation result code. If an application can send the requested object
	///   the <c>Result</c> must be set to <c>orSuccess</c>. </param>
	/// <param name="Stream"> The requested OBEX object's data stream. An
	///   application must provide the object's stream only in case if the
	///   <c>Result</c> set to <c>orSuccess</c>. In any other case the
	///   <c>Stream</c> must be set to <c>NULL</c>. The stream object passed to
	///   the event must be valid during all Get operation and can be released
	///   when the <c>OnGetCompleted</c> event received. </param>
	/// <seealso cref="wclObexServerOperationResult" />
	/// <seealso cref="CwclStream" />
	#define wclObexOppServerGetRequestEvent(_event_name_) \
		__event void _event_name_(void* Sender, const tstring& aType, \
		wclObexServerOperationResult& Result, CwclStream*& Stream)

	/// <summary> The data processor implements the OBEX Object Push Profile
	///   (OPP) server. </summary>
	/// <seealso cref="CwclCustomObexServer" />
	class CwclObexOppServer : public CwclCustomObexServer
	{
		DISABLE_COPY(CwclObexOppServer);

	protected:
		/// <summary> The method called when a remote client opens OBEX session
		///   (connects). </summary>
		/// <param name="Target"> The requested target service/server ID. </param>
		/// <param name="Who"> The client's ID. </param>
		/// <param name="Description"> The connect operation's or client's
		///   description. </param>
		virtual void DoConnect(const GUID& Target, const GUID& Who,
			const tstring& Description) override;
		/// <summary> Fires the <c>OnGetRequest</c> event. </summary>
		/// <param name="Name"> The requested OBEX object's name. </param>
		/// <param name="Mime"> The requested OBEX object's MIME type. </param>
		/// <param name="Result"> An application must set this parameter to the
		///   operation result code. If an application can send the requested object
		///   the <c>Result</c> must be set to <c>orSuccess</c>. </param>
		/// <param name="Stream"> The requested OBEX object's data stream. An
		///   application must provide the object's stream only in case if the
		///   <c>Result</c> set to <c>orSuccess</c>. In any other case the
		///   <c>Stream</c> must be set to <c>NULL</c>. The stream object passed to
		///   the event must be valid during all Get operation and can be released
		///   when the <c>OnGetCompleted</c> event received. </param>
		/// <seealso cref="wclObexServerOperationResult" />
		virtual void DoGetRequest(const tstring& Name, const tstring& Mime,
			wclObexServerOperationResult& Result, CwclStream*& Stream) override;
		
	public:
		/// <summary> Creates new OBEX Server Client Data Processor. </summary>
		/// <param name="Connection"> A
		///   <see cref="CwclServerClientDataConnection" /> object that is used to
		///   communicate with a remote device. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		CwclObexOppServer(CwclServerClientDataConnection* const Connection);
		virtual ~CwclObexOppServer();
		
		/// <summary> The event fires when a client connects to the
		///   server. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Description"> The client's description. </param>
		/// <remarks> The server should accept connection by calling <c>Accept</c>
		///   method or reject connection by calling <c>Reject</c>
		///   method. </remarks>
		wclObexOppServerConnectEvent(OnConnect);
		/// <summary> The event fires when a remote connected client requests the
		///   OBEX object (sends the get request). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="aType"> The requested OBEX object's MIME type. </param>
		/// <param name="Result"> An application must set this parameter to the
		///   operation result code. If an application can send the requested object
		///   the <c>Result</c> must be set to <c>orSuccess</c>. </param>
		/// <param name="Stream"> The requested OBEX object's data stream. An
		///   application must provide the object's stream only in case if the
		///   <c>Result</c> set to <c>orSuccess</c>. In any other case the
		///   <c>Stream</c> must be set to <c>NULL</c>. The stream object passed to
		///   the event must be valid during all Get operation and can be released
		///   when the <c>OnGetCompleted</c> event received. </param>
		/// <seealso cref="wclObexServerOperationResult" />
		/// <seealso cref="CwclStream" />
		wclObexOppServerGetRequestEvent(OnGetRequest);
	};
}