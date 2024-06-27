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

#include "..\Common\wclErrors.h"

using wclCommon::wclException;

namespace wclCommunication
{
	/* Connection error codes. */

	/// <summary> The base error code for all connection errors. </summary>
	const int WCL_E_CONNECTION_BASE = 0x00030000;
	/// <summary> A connection is active. </summary>
	const int WCL_E_CONNECTION_ACTIVE = WCL_E_CONNECTION_BASE + 0x0000;
	/// <summary> A connection is not active. </summary>
	const int WCL_E_CONNECTION_NOT_ACTIVE = WCL_E_CONNECTION_BASE + 0x0001;
	/// <summary> Unable to create communication termination event object. </summary>
	const int WCL_E_CONNECTION_UNABLE_CREATE_TERMINATE_EVENT = WCL_E_CONNECTION_BASE + 0x0002;
	/// <summary> Unable to create connection complete event object. </summary>
	const int WCL_E_CONNECTION_UNABLE_CREATE_CONNECTION_COMPLETE_EVENT = WCL_E_CONNECTION_BASE + 0x0003;
	/// <summary> Unable to create communication thread. </summary>
	const int WCL_E_CONNECTION_UNABLE_START_COMMUNICATION = WCL_E_CONNECTION_BASE + 0x0004;
	/// <summary> The connection has been terminated by unknown reason. </summary>
	const int WCL_E_CONNECTION_TERMINATED = WCL_E_CONNECTION_BASE + 0x0005;
	/// <summary> The connection has been terminated by user. </summary>
	const int WCL_E_CONNECTION_TERMINATED_BY_USER = WCL_E_CONNECTION_BASE + 0x0006;
	/// <summary> Unable to create a communication thread initialization event. </summary>
	const int WCL_E_CONNECTION_UNABLE_CREATE_INIT_EVENT = WCL_E_CONNECTION_BASE + 0x0007;
	/// <summary> The connection has been closed. </summary>
	const int WCL_E_CONNECTION_CLOSED = WCL_E_CONNECTION_BASE + 0x0008;
	/// <summary> Unexpected error. </summary>
	const int WCL_E_CONNECTION_UNEXPECTED = WCL_E_CONNECTION_BASE + 0x0009;
	/// <summary> A server was not able to create or init client connection instance. </summary>
	const int WCL_E_CONNECTION_UNABLE_CREATE_OR_INIT_CLIENT = WCL_E_CONNECTION_BASE + 0x000A;
	/// <summary> A server was not able to find a specific client connection class. </summary>
	const int WCL_E_CONNECTION_UNABLE_FIND_CLIENT_CLASS = WCL_E_CONNECTION_BASE + 0x000B;

	/* OBEX error codes. */

	/// <summary> The base error code for OBEX errors. </summary>
	const int WCL_E_OBEX_BASE = WCL_E_CONNECTION_BASE + 0x1000;
	/// <summary> An OBEX client is not connected to an OBEX server. </summary>
	const int WCL_E_OBEX_NOT_CONNECTED = WCL_E_OBEX_BASE + 0x0000;
	/// <summary> An OBEX client is already connected to an OBEX
	///   server. </summary>
	const int WCL_E_OBEX_CONNECTED = WCL_E_OBEX_BASE + 0x0001;
	/// <summary> An OBEX operation is in progress. </summary>
	const int WCL_E_OBEX_OPERATION_IN_PROGRESS = WCL_E_OBEX_BASE + 0x0002;
	/// <summary> The server has received the request headers and the client
	///   should proceed to send the request body (in the case of a request for
	///   which a body needs to be sent). </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_CONTINUE = WCL_E_OBEX_BASE + 0x0003;
	/// <summary> The request has been fulfilled, resulting in the creation of a
	///   new resource. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_CREATED = WCL_E_OBEX_BASE + 0x0004;
	/// <summary> The request has been accepted for processing, but the
	///   processing has not been completed. The request might or might not be
	///   eventually acted upon, and may be disallowed when processing
	///   occurs. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_ACCEPTED = WCL_E_OBEX_BASE + 0x0005;
	/// <summary> The server is a transforming proxy that received a
	///   <c>WCL_E_SUCCESS</c> from its origin, but is returning a modified
	///   version of the origin's response. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_NON_AUTHORITATIVE = WCL_E_OBEX_BASE + 0x0006;
	/// <summary> The server successfully processed the request and is not
	///   returning any content. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_NO_CONTENT = WCL_E_OBEX_BASE + 0x0007;
	/// <summary> The server successfully processed the request, but is not
	///   returning any content. Unlike a <c>WCL_E_OBEX_NO_CONTENT</c> error,
	///   this error requires that the requester reset the object. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_RESET_CONTENT = WCL_E_OBEX_BASE + 0x0008;
	/// <summary> The server is delivering only part of the resource due to a
	///   range header sent by the client. The range header is used by OBEX
	///   clients to enable resuming of interrupted downloads, or split a
	///   download into multiple simultaneous streams. </summary>
	/// <remarks> This result code is not an error and indicates the action
	///   requested by the client was received, understood and
	///   accepted. </remarks>
	const int WCL_E_OBEX_PARTIAL_CONTENT = WCL_E_OBEX_BASE + 0x0009;
	/// <summary> Indicates multiple options for the resource from which the
	///   client may choose. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_MULTIPLE_CHOICES = WCL_E_OBEX_BASE + 0x000A;
	/// <summary> This and all future requests should be directed to the given
	///   URI. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_MOVED_PERMANENTLY = WCL_E_OBEX_BASE + 0x000B;
	/// <summary> The response to the request can be found under another URI
	///   using the GET method. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_MOVED_TEMPORARY = WCL_E_OBEX_BASE + 0x000C;
	/// <summary> The response to the request can be found under another URI
	///   using the GET method. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_SEE_OTHER = WCL_E_OBEX_BASE + 0x000D;
	/// <summary> Indicates that the resource has not been modified since the
	///   version specified by the request headers If-Modified-Since or
	///   If-None-Match. In such case, there is no need to retransmit the resource
	///   since the client still has a previously-downloaded copy. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_NOT_MODIFIED = WCL_E_OBEX_BASE + 0x000E;
	/// <summary> The requested resource is available only through a proxy, the
	///   address for which is provided in the response. </summary>
	/// <remarks> This status code is not an error but indicates the client must
	///   take additional action to complete the request. </remarks>
	const int WCL_E_OBEX_USE_PROXY = WCL_E_OBEX_BASE + 0x000F;
	/// <summary> The server cannot or will not process the request due to an
	///   apparent client error (e.g., malformed request syntax, size too large,
	///   invalid request message framing, or deceptive request
	///   routing). </summary>
	const int WCL_E_OBEX_BAD_REQUEST = WCL_E_OBEX_BASE + 0x0010;
	/// <summary> Similar to <c>WCL_E_OBEX_FORBIDDEN</c>, but specifically for
	///   use when authentication is required and has failed or has not yet been
	///   provided. The response must include a WWW-Authenticate header field
	///   containing a challenge applicable to the requested resource. </summary>
	const int WCL_E_OBEX_UNAUTHORIZED = WCL_E_OBEX_BASE + 0x0011;
	/// <summary> Reserved for future use. </summary>
	const int WCL_E_OBEX_PAYMENT_REQUIRED = WCL_E_OBEX_BASE + 0x0012;
	/// <summary> The request was valid, but the server is refusing action. The
	///   user might not have the necessary permissions for a resource, or may
	///   need an account of some sort. </summary>
	const int WCL_E_OBEX_FORBIDDEN = WCL_E_OBEX_BASE + 0x0013;
	/// <summary> The requested resource could not be found but may be available
	///   in the future. Subsequent requests by the client are
	///   permissible. </summary>
	const int WCL_E_OBEX_NOT_FOUND = WCL_E_OBEX_BASE + 0x0014;
	/// <summary> A request method is not supported for the requested
	///   resource. </summary>
	const int WCL_E_OBEX_METHOD_NOT_ALLOWED = WCL_E_OBEX_BASE + 0x0015;
	/// <summary> The requested resource is capable of generating only content not
	///   acceptable according to the Accept headers sent in the
	///   request. </summary>
	const int WCL_E_OBEX_NOT_ACCEPTABLE = WCL_E_OBEX_BASE + 0x0016;
	/// <summary> The client must first authenticate itself with the
	///   proxy. </summary>
	const int WCL_E_OBEX_PROXY_AUTH_REQUIRED = WCL_E_OBEX_BASE + 0x0017;
	/// <summary> The server timed out waiting for the request. </summary>
	const int WCL_E_OBEX_REQUEST_TIMEOUT = WCL_E_OBEX_BASE + 0x0018;
	/// <summary> Indicates that the request could not be processed because of
	///   conflict in the request, such as an edit conflict between multiple
	///   simultaneous updates. </summary>
	const int WCL_E_OBEX_CONFLICT = WCL_E_OBEX_BASE + 0x0019;
	/// <summary> Indicates that the resource requested is no longer available and
	///   will not be available again. </summary>
	const int WCL_E_OBEX_GONE = WCL_E_OBEX_BASE + 0x001A;
	/// <summary> The request did not specify the length of its content, which is
	///   required by the requested resource. </summary>
	const int WCL_E_OBEX_LENGTH_REQUIRED = WCL_E_OBEX_BASE + 0x001B;
	/// <summary> The server does not meet one of the preconditions that the
	///   requester put on the request. </summary>
	const int WCL_E_OBEX_PRECONDITION_FAILED = WCL_E_OBEX_BASE + 0x001C;
	/// <summary> The request is larger than the server is willing or able to
	///   process. </summary>
	const int WCL_E_OBEX_REQUEST_TOO_LARGE = WCL_E_OBEX_BASE + 0x001D;
	/// <summary> The URI provided was too long for the server to
	///   process. </summary>
	const int WCL_E_OBEX_URL_TOO_LARGE = WCL_E_OBEX_BASE + 0x001E;
	/// <summary> The request entity has a media type which the server or resource
	///   does not support. For example, the client uploads an image as
	///   image/svg+xml, but the server requires that images use a different
	///   format. </summary>
	const int WCL_E_OBEX_UNSUPPORTED_MEDIA_TYPE = WCL_E_OBEX_BASE + 0x001F;
	/// <summary> A generic error, given when an unexpected condition was
	///   encountered and no more specific message is suitable. </summary>
	const int WCL_E_OBEX_INTERNAL = WCL_E_OBEX_BASE + 0x0020;
	/// <summary> The server either does not recognize the request method, or it
	///   lacks the ability to fulfill the request. </summary>
	const int WCL_E_OBEX_NOT_IMPLEMENTED = WCL_E_OBEX_BASE + 0x0021;
	/// <summary> The server was acting as a gateway or proxy and received an
	///   invalid response from the upstream server. </summary>
	const int WCL_E_OBEX_BAD_GATEWAY = WCL_E_OBEX_BASE + 0x0022;
	/// <summary> The server is currently unavailable (because it is overloaded or
	///   down for maintenance). Generally, this is a temporary state.
	///  Also this error indicates that wrong Connect ID or Target
	///   used. </summary>
	const int WCL_E_OBEX_SERVICE_UNAVAILABLE = WCL_E_OBEX_BASE + 0x0023;
	/// <summary> The server was acting as a gateway or proxy and did not receive
	///   a timely response from the upstream server. </summary>
	const int WCL_E_OBEX_GATEWAY_TIMEOUT = WCL_E_OBEX_BASE + 0x0024;
	/// <summary> The server does not support the HTTP protocol version used in
	///   the request.[ </summary>
	const int WCL_E_OBEX_HTTP_VERSION_NOT_SUPPORTED = WCL_E_OBEX_BASE + 0x0025;
	/// <summary> Indicates that the client requests that something be placed into
	///   a database but the database is full (cannot take more data). </summary>
	const int WCL_E_OBEX_DATABASE_FULL = WCL_E_OBEX_BASE + 0x0026;
	/// <summary> Returned when the client wishes to access a database, database
	///   table, or database record that has been locked. </summary>
	const int WCL_E_OBEX_DATABASE_LOCKED = WCL_E_OBEX_BASE + 0x0027;
	/// <summary> The current operation has been terminated because a remote
	///   device is disconnected. </summary>
	const int WCL_E_OBEX_OPERATION_TERMINATED_BY_DISCONNECT = WCL_E_OBEX_BASE + 0x0028;
	/// <summary> The current operation has been terminated by a user. </summary>
	const int WCL_E_OBEX_OPERATION_TERMINATED_BY_USER = WCL_E_OBEX_BASE + 0x0029;
	/// <summary> The operation can not be executed at this time. This error
	///   appears if for example an application calls Terminate for Connect,
	///   Disconnect or SetPath operations. </summary>
	const int WCL_E_OBEX_INVALID_OPERATION_SEQUENCE = WCL_E_OBEX_BASE + 0x002A;
	/// <summary> The error code indicates that the OBEX session has been
	///   disconnected by a remote side. </summary>
	const int WCL_E_OBEX_DISCONNECTED = WCL_E_OBEX_BASE + 0x002B;
	/// <summary> Unexpected or unknown OBEX result code. </summary>
	const int WCL_E_OBEX_UNEXPECTED = WCL_E_OBEX_BASE + 0x002C;
	/// <summary> Unable to create synchronization Mutex used to generate
	///   connection ID. </summary>
	const int WCL_E_OBEX_CREATE_CONNECTION_ID_MUTEX_FAILED = WCL_E_OBEX_BASE + 0x002D;
	/// <summary> The maximum connection ID has been reached. </summary>
	const int WCL_E_OBEX_MAX_CONNECTION_ID = WCL_E_OBEX_BASE + 0x002E;
	/// <summary> Invalid data processor state. </summary>
	const int WCL_E_OBEX_INVALID_STATE = WCL_E_OBEX_BASE + 0x002F;
	/// <summary> Unable to parse directory listing. </summary>
	const int WCL_E_OBEX_INVALID_DIR_LIST = WCL_E_OBEX_BASE + 0x0030;
	/// <summary> Wrong directory listing format. </summary>
	const int WCL_E_OBEX_INVALID_DIR_FORMAT = WCL_E_OBEX_BASE + 0x0031;
	/// <summary> COM initialization failed. </summary>
	const int WCL_E_OBEX_COM_INIT_FAILED = WCL_E_OBEX_BASE + 0x0032;
	/// <summary> XML parser is not available. </summary>
	const int WCL_E_OBEX_XML_NOT_AVAILABLE = WCL_E_OBEX_BASE + 0x0033;

	/* Connections exceptions. */

	/// <summary> The base class for connections exceptions. </summary>
	/// <seealso cref="wclException" />
	class wclEConnection : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEConnection(const char* msg) : wclException(msg) { };
	};

	/// <summary> Exception class used for client connections. </summary>
	/// <seealso cref="wclEConnection" />
	class wclEClientConnection : public wclEConnection
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEClientConnection(const char* msg) : wclEConnection(msg) { };
	};

	/// <summary> The exception raises when an application tries to change
	///   any property of already active (connecting or connected) client
	///   component. </summary>
	/// <seealso cref="wclEClientConnection" />
	class wclEClientActive : public wclEClientConnection
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEClientActive(const char* msg) : wclEClientConnection(msg) { };
	};

	/// <summary> Exception class used for server connections. </summary>
	/// <seealso cref="wclEConnection" />
	class wclEServerConnection : public wclEConnection
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEServerConnection(const char* msg) : wclEConnection(msg) { };
	};

	/// <summary> The exception raises when an application tries to change
	///   any property of already active (listening) server component. </summary>
	/// <seealso cref="wclEServerConnection" />
	class wclEServerActive : public wclEServerConnection
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEServerActive(const char* msg) : wclEServerConnection(msg) { };
	};

	/// <summary> Exception class used for server client connections. </summary>
	/// <seealso cref="wclEServerConnection" />
	class wclEServerClientConnection : public wclEServerConnection
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEServerClientConnection(const char* msg) : wclEServerConnection(msg) { };
	};
}