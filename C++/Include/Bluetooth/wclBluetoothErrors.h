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

#include "..\Communication\wclConnectionErrors.h"

namespace wclBluetooth
{
	/* Classic Bluetooth error codes. */

	/// <summary> The base code for the Bluetooth errors. </summary>
	const int WCL_E_BLUETOOTH_BASE = 0x00050000;
	/// <summary> A Bluetooth Manager is closed. </summary>
	const int WCL_E_BLUETOOTH_MANAGER_CLOSED = WCL_E_BLUETOOTH_BASE + 0x0000;
	/// <summary> A Bluetooth Manager is opened. </summary>
	const int WCL_E_BLUETOOTH_MANAGER_OPENED = WCL_E_BLUETOOTH_BASE + 0x0001;
	/// <summary> Unable to open the Bluetooth Manager. </summary>
	const int WCL_E_BLUETOOTH_MANAGER_OPEN_FAILED = WCL_E_BLUETOOTH_BASE + 0x0002;
	/// <summary> An other instance of the Bluetooth Manager is already opened. </summary>
	const int WCL_E_BLUETOOTH_MANAGER_EXISTS = WCL_E_BLUETOOTH_BASE + 0x0003;
	/// <summary> A Bluetooth driver is not available or not loaded. </summary>
	const int WCL_E_BLUETOOTH_DRIVER_NOT_AVAILABLE = WCL_E_BLUETOOTH_BASE + 0x0004;
	/// <summary> A Bluetooth hardware is not available. </summary>
	const int WCL_E_BLUETOOTH_HARDWARE_NOT_AVAILABLE = WCL_E_BLUETOOTH_BASE + 0x0005;
	/// <summary> A Bluetooth API (driver) was not loaded. </summary>
	const int WCL_E_BLUETOOTH_API_NOT_LOADED = WCL_E_BLUETOOTH_BASE + 0x0006;
	/// <summary> Unable to initialize a Bluetooth API (driver) subsystem. </summary>
	const int WCL_E_BLUETOOTH_API_INITIALIZATION_FAILED = WCL_E_BLUETOOTH_BASE + 0x0007;
	/// <summary> A Bluetooth API (driver) was not found in this system. </summary>
	const int WCL_E_BLUETOOTH_API_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x0008;
	/// <summary> A Bluetooth driver was not initialized. </summary>
	const int WCL_E_BLUETOOTH_API_NOT_INITIALIZED = WCL_E_BLUETOOTH_BASE + 0x0009;
	/// <summary> A Bluetooth driver has been found but it does not support
	///   all the features that WCL requires for correct work. You should
	///   update your Bluetooth driver for the latest available version. </summary>
	const int WCL_E_BLUETOOTH_WRONG_DRIVER_VERSION = WCL_E_BLUETOOTH_BASE + 0x000A;
	/// <summary> A Bluetooth Radio object is opened. </summary>
	const int WCL_E_BLUETOOTH_RADIO_OPENED = WCL_E_BLUETOOTH_BASE + 0x000B;
	/// <summary> A Bluetooth Radio object is closed. </summary>
	const int WCL_E_BLUETOOTH_RADIO_CLOSED = WCL_E_BLUETOOTH_BASE + 0x000C;
	/// <summary> The Bluetooth Radio object has been removed (destroyed). </summary>
	const int WCL_E_BLUETOOTH_RADIO_REMOVED = WCL_E_BLUETOOTH_BASE + 0x000D;
	/// <summary> Unable to initialize a Bluetooth Radio instance mutex. </summary>
	const int WCL_E_BLUETOOTH_RADIO_INSTANCE_INIT_FAILED = WCL_E_BLUETOOTH_BASE + 0x000E;
	/// <summary> The same Bluetooth Radio instance has already been initialized. </summary>
	const int WCL_E_BLUETOOTH_RADIO_INSTANCE_EXISTS = WCL_E_BLUETOOTH_BASE + 0x000F;
	/// <summary> The Bluetooth Radio object become unavailable. </summary>
	const int WCL_E_BLUETOOTH_RADIO_UNAVAILABLE = WCL_E_BLUETOOTH_BASE + 0x0010;
	/// <summary> Unable to change Radio connectable state. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CHANGE_CONNECTABLE_STATE = WCL_E_BLUETOOTH_BASE + 0x0011;
	/// <summary> Unable to change Radio discoverable state. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CHANGE_DISCOVERABLE_STATE = WCL_E_BLUETOOTH_BASE + 0x0012;
	/// <summary> Unable to change Radio name. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CHANGE_NAME = WCL_E_BLUETOOTH_BASE + 0x0013;
	/// <summary> The requested feature is not supported by a Bluetooth driver. </summary>
	const int WCL_E_BLUETOOTH_FEATURE_NOT_SUPPORTED = WCL_E_BLUETOOTH_BASE + 0x0014;
	/// <summary> Unexpected or unknown Bluetooth error. </summary>
	const int WCL_E_BLUETOOTH_UNEXPECTED = WCL_E_BLUETOOTH_BASE + 0x0015;
	/// <summary> <para> Error other than time-out at L2CAP or Bluetooth radio level. </para>
	///   <para> Usually this error appears if you try to connect to device that is paired on PC side
	///   but PC is not paired or has been unpaired on the device side. Unpairing device on PC side
	///   usually solves the error. </para> </summary>
	const int WCL_E_BLUETOOTH_LINK_UNEXPECTED = WCL_E_BLUETOOTH_BASE + 0x0016;
	/// <summary> The operation fails for an undefined reason. </summary>
	const int WCL_E_BLUETOOTH_OPERATION_FAILED = WCL_E_BLUETOOTH_BASE + 0x0017;
	/// <summary> The request can not be processed since a same request is being processed. </summary>
	const int WCL_E_BLUETOOTH_OPERATION_CONFLICT = WCL_E_BLUETOOTH_BASE + 0x0018;
	/// <summary> The limit of connection number is reached. </summary>
	const int WCL_E_BLUETOOTH_NO_MORE_CONNECTION_ALLOWED = WCL_E_BLUETOOTH_BASE + 0x0019;
	/// <summary> An object with the specified attribute exists. </summary>
	const int WCL_E_BLUETOOTH_OBJECT_EXISTS = WCL_E_BLUETOOTH_BASE + 0x001A;
	/// <summary> The specified object is accessed by other process. It can not
	///   be removed or modified. </summary>
	const int WCL_E_BLUETOOTH_OBJECT_IN_USE = WCL_E_BLUETOOTH_BASE + 0x001B;
	/// <summary> Discovering is already running. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_RUNNING = WCL_E_BLUETOOTH_BASE + 0x001C;
	/// <summary> Discovering is not running. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_NOT_RUNNING = WCL_E_BLUETOOTH_BASE + 0x001D;
	/// <summary> Discovering has been terminated. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_TERMINATED = WCL_E_BLUETOOTH_BASE + 0x001E;
	/// <summary> Operation has been canceled by user. </summary>
	const int WCL_E_BLUETOOTH_CANCELLED_BY_USER = WCL_E_BLUETOOTH_BASE + 0x001F;
	/// <summary> Operation time out. </summary>
	const int WCL_E_BLUETOOTH_TIMEOUT = WCL_E_BLUETOOTH_BASE + 0x0020;
	/// <summary> Connection has been terminated by a user. </summary>
	const int WCL_E_BLUETOOTH_CONNECTION_TERMINATED_BY_USER = WCL_E_BLUETOOTH_BASE + 0x0021;
	/// <summary> Asynchronous processing is pending. </summary>
	const int WCL_E_BLUETOOTH_PENDING = WCL_E_BLUETOOTH_BASE + 0x0022;
	/// <summary> Connection failure. </summary>
	const int WCL_E_BLUETOOTH_CONNECTION_FAILED = WCL_E_BLUETOOTH_BASE + 0x0023;
	/// <summary> A specified remote Bluetooth device was not found. </summary>
	const int WCL_E_BLUETOOTH_DEVICE_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x0024;
	/// <summary> Pairing operation is executing. </summary>
	const int WCL_E_BLUETOOTH_PAIRING = WCL_E_BLUETOOTH_BASE + 0x0025;
	/// <summary> Unable to start pairing with a remote Bluetooth device. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_PAIRING = WCL_E_BLUETOOTH_BASE + 0x0026;
	/// <summary> A device has already been paired. </summary>
	const int WCL_E_BLUETOOTH_ALREADY_PAIRED = WCL_E_BLUETOOTH_BASE + 0x0027;
	/// <summary> The specified remote device is not paired. </summary>
	const int WCL_E_BLUETOOTH_DEVICE_NOT_PAIRED = WCL_E_BLUETOOTH_BASE + 0x0028;
	/// <summary> Access denied. </summary>
	const int WCL_E_BLUETOOTH_ACCESS_DENIED = WCL_E_BLUETOOTH_BASE + 0x0029;
	/// <summary> Authentication (paring) with a remote Bluetooth device is failed. </summary>
	const int WCL_E_BLUETOOTH_AUTHENTICATION_FAILED = WCL_E_BLUETOOTH_BASE + 0x002A;
	/// <summary> Operation has been rejected. </summary>
	const int WCL_E_BLUETOOTH_REJECTED = WCL_E_BLUETOOTH_BASE + 0x002B;
	/// <summary> Unable to get a read buffer size. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_GET_READ_BUFFER = WCL_E_BLUETOOTH_BASE + 0x002C;
	/// <summary> Unable to get a write buffer size. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_GET_WRITE_BUFFER = WCL_E_BLUETOOTH_BASE + 0x002D;
	/// <summary> Unable to set a read buffer size. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_READ_BUFFER = WCL_E_BLUETOOTH_BASE + 0x002E;
	/// <summary> Unable to set a write buffer size. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_WRITE_BUFFER = WCL_E_BLUETOOTH_BASE + 0x002F;
	/// <summary> A client is already connected to a Bluetooth device. </summary>
	const int WCL_E_BLUETOOTH_CLIENT_CONNECTED = WCL_E_BLUETOOTH_BASE + 0x0030;
	/// <summary> A client is not connected to a Bluetooth device. </summary>
	const int WCL_E_BLUETOOTH_CLIENT_NOT_CONNECTED = WCL_E_BLUETOOTH_BASE + 0x0031;
	/// <summary> The L2CAP channel disconnected by remote peer. </summary>
	const int WCL_E_BLUETOOTH_L2CAP_DISCONNECTED = WCL_E_BLUETOOTH_BASE + 0x0032;
	/// <summary> Wrong device type used in connection. </summary>
	const int WCL_E_BLUETOOTH_INVALID_DEVICE_TYPE = WCL_E_BLUETOOTH_BASE + 0x0033;
	/// <summary> The port/channel number requested is in use. </summary>
	const int WCL_E_BLUETOOTH_CHANNEL_IN_USE = WCL_E_BLUETOOTH_BASE + 0x0034;
	/// <summary> The Bluetooth port/channel or device address not valid. </summary>
	const int WCL_E_BLUETOOTH_SERVICE_NOT_VALID = WCL_E_BLUETOOTH_BASE + 0x0035;
	/// <summary> No service record with the specified search pattern is found
	///   on the remote device. </summary>
	const int WCL_E_BLUETOOTH_SERVICE_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x0036;
	/// <summary> Unable to create a Bluetooth socket. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_SOCKET = WCL_E_BLUETOOTH_BASE + 0x0037;
	/// <summary> Unable to set client authentication and/or encryption states. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_CLIENT_SECURITY = WCL_E_BLUETOOTH_BASE + 0x0038;
	/// <summary> Unable to create socket event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_EVENT = WCL_E_BLUETOOTH_BASE + 0x0039;
	/// <summary> Unable to select socket events. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_EVENT = WCL_E_BLUETOOTH_BASE + 0x003A;
	/// <summary> Unable to acquire the connections mutex object. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_LOCK_CONNECT_MUTEX = WCL_E_BLUETOOTH_BASE + 0x003B;
	/// <summary> Unable to create system event object for
	///   overlapped IO. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_INIT_OVERLAPPED_OPERATION = WCL_E_BLUETOOTH_BASE + 0x003C;
	/// <summary> Unable to create disconnect notification event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_DISCONNECT_EVENT = WCL_E_BLUETOOTH_BASE + 0x003D;
	/// <summary> Unable to create connect notification connection
	///   event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_CONNECT_EVENT = WCL_E_BLUETOOTH_BASE + 0x003E;
	/// <summary> Unable to acquire the SDP mutex object. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_LOCK_SDP_MUTEX = WCL_E_BLUETOOTH_BASE + 0x003F;
	/// <summary> The RFCOMM multiplexor (session) disconnected by remote
	///   peer. </summary>
	const int WCL_E_BLUETOOTH_RFCOMM_SESSION_DISCONNECTED = WCL_E_BLUETOOTH_BASE + 0x0040;
	/// <summary> The RFCOMM received DM response. </summary>
	const int WCL_E_BLUETOOTH_RFCOMM_DOWN = WCL_E_BLUETOOTH_BASE + 0x0041;
	/// <summary> The RFCOMM channel disconnected by remote peer. </summary>
	const int WCL_E_BLUETOOTH_RFCOMM_DISCONNECTED = WCL_E_BLUETOOTH_BASE + 0x0042;
	/// <summary> Unable to resolve connected remote device address. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_RESOLVE_ADDRESS = WCL_E_BLUETOOTH_BASE + 0x0043;
	/// <summary> Unable to add new SDP record. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_ADD_SDP_RECORD = WCL_E_BLUETOOTH_BASE + 0x0044;
	/// <summary> Unable to set server authentication and/or encryption
	///   states. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_SERVER_SECURITY = WCL_E_BLUETOOTH_BASE + 0x0045;
	/// <summary> Local service is still active. </summary>
	const int WCL_E_BLUETOOTH_LOCAL_SERVICE_ACTIVE = WCL_E_BLUETOOTH_BASE + 0x0046;
	/// <summary> Unable to create Bluetooth server. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_SERVER = WCL_E_BLUETOOTH_BASE + 0x0047;
	/// <summary> Unable to enumerate local running services. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_ENUMERATE_LOCAL_SERVICES = WCL_E_BLUETOOTH_BASE + 0x0048;
	/// <summary> Unable to stop local predefined server. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_STOP_LOCAL_SERVER = WCL_E_BLUETOOTH_BASE + 0x0049;
	/// <summary> Unable to update local server database. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_UPDATE_LOCAL_SERVER = WCL_E_BLUETOOTH_BASE + 0x004A;
	/// <summary> Unable to setup the communication port. </summary>
	const int WCL_E_BLUETOOTH_SETUP_COM_FAILED = WCL_E_BLUETOOTH_BASE + 0x004B;
	/// <summary> Unable to open the client COM port for the Bluetooth
	///   connection. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_OPEN_CLIENT_COM = WCL_E_BLUETOOTH_BASE + 0x004C;
	/// <summary> Unable to open the server COM port for the Bluetooth
	///   connection. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_OPEN_SERVER_COM = WCL_E_BLUETOOTH_BASE + 0x004D;
	/// <summary> Sending data to a remote device was failed. </summary>
	const int WCL_E_BLUETOOTH_WRITE_FAILED = WCL_E_BLUETOOTH_BASE + 0x004E;
	/// <summary> Abnormal data received. </summary>
	const int WCL_E_BLUETOOTH_READ_FAILED = WCL_E_BLUETOOTH_BASE + 0x004F;
	/// <summary> Unable to create Toshiba notifications window. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_WND = WCL_E_BLUETOOTH_BASE + 0x0050;
	/// <summary> Unable to register Toshiba notification message. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_REGISTER_MESSAGE = WCL_E_BLUETOOTH_BASE + 0x0051;
	/// <summary> Unable to create synchronization event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_SYNC_EVENT = WCL_E_BLUETOOTH_BASE + 0x0052;
	/// <summary> SDP transaction processing failure. </summary>
	const int WCL_E_BLUETOOTH_SDP_TRANSACTION = WCL_E_BLUETOOTH_BASE + 0x0053;
	/// <summary> Unable start SDP connection thread. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_SDP_THREAD = WCL_E_BLUETOOTH_BASE + 0x0054;
	/// <summary> Unable to start connection thread. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_CONNECT_THREAD = WCL_E_BLUETOOTH_BASE + 0x0055;
	/// <summary> Unable to start listening thread. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_LISTEN_THREAD = WCL_E_BLUETOOTH_BASE + 0x0056;
	/// <summary> Inquiry processing failure. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_FAILED = WCL_E_BLUETOOTH_BASE + 0x0057;
	/// <summary> Remote name acquisition processing failure. </summary>
	const int WCL_E_BLUETOOTH_READ_REMOTE_NAME_FAILED = WCL_E_BLUETOOTH_BASE + 0x0058;
	/// <summary> Unable to destroy COM port. </summary>
	const int WCL_E_BLUETOOTH_DESTROY_COM_FAILED = WCL_E_BLUETOOTH_BASE + 0x0059;
	/// <summary> Unable to connect COM port. </summary>
	const int WCL_E_BLUETOOTH_CONNECT_COM_FAILED = WCL_E_BLUETOOTH_BASE + 0x005A;
	/// <summary> Unable to disconnect COM port. </summary>
	const int WCL_E_BLUETOOTH_DISCONNECT_COM_FAILED = WCL_E_BLUETOOTH_BASE + 0x005B;
	/// <summary> Unable to turn Bluetooth ON or OFF. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_SWITCH_ON_OR_OFF = WCL_E_BLUETOOTH_BASE + 0x005C;
	/// <summary> Can not assign PSM. </summary>
	const int WCL_E_BLUETOOTH_CANNOT_ASSIGN_PSM = WCL_E_BLUETOOTH_BASE + 0x005D;
	/// <summary> Unable to read local Radio information. </summary>
	const int WCL_E_BLUETOOTH_GETLOCALINFO_FAILED = WCL_E_BLUETOOTH_BASE + 0x005E;
	/// <summary> Unable to disconnect from SDP server. </summary>
	const int WCL_E_BLUETOOTH_DISCONNECT_SDP_FAILED = WCL_E_BLUETOOTH_BASE + 0x005F;
	/// <summary> Unable to register COM port notifications. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_REGISTER_COM_NOTIFICATION = WCL_E_BLUETOOTH_BASE + 0x0060;
	/// <summary> Unable to change local radio information. </summary>
	const int WCL_E_BLUETOOTH_SETLOCALINFO_FAILED = WCL_E_BLUETOOTH_BASE + 0x0061;
	/// <summary> Unable o get connected state of the device. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_GET_CONNECTED_DEVICES = WCL_E_BLUETOOTH_BASE + 0x0062;
	/// <summary> Unable to connect to a remote device. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CONNECT = WCL_E_BLUETOOTH_BASE + 0x0063;
	/// <summary> Unable to start connection to a remote device. PSM
	///   error. </summary>
	const int WCL_E_BLUETOOTH_CONNECT_PSM = WCL_E_BLUETOOTH_BASE + 0x0064;
	/// <summary> SDP record parsing error. </summary>
	const int WCL_E_BLUETOOTH_SDP_PARSE_ERROR = WCL_E_BLUETOOTH_BASE + 0x0065;
	/// <summary> Unable to read RSSI value. </summary> 
	const int WCL_E_BLUETOOTH_UNABLE_READ_RSSI = WCL_E_BLUETOOTH_BASE + 0x0066;
	/// <summary> Unable to change pairing mode. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CHANGE_PAIRING_MODE = WCL_E_BLUETOOTH_BASE + 0x0067;
	/// <summary> Error working with SDP records. </summary>
	const int WCL_E_BLUETOOTH_SDP_ERROR = WCL_E_BLUETOOTH_BASE + 0x0068;
	/// <summary> Unable to start Toshiba main thread. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_THREAD = WCL_E_BLUETOOTH_BASE + 0x0069;
	/// <summary> Unable to create BlueSoleil initialization event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_INIT_EVENT = WCL_E_BLUETOOTH_BASE + 0x006A;
	/// <summary> Unable to start BlueSoleil initialization thread. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_START_INIT_THREAD = WCL_E_BLUETOOTH_BASE + 0x006B;
	/// <summary> The virtual COM port was not found. Probably it was not
	///   created by this Bluetooth radio object. </summary>
	const int WCL_E_BLUETOOTH_VCOM_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x006C;
	/// <summary> A virtual COM port was already created for this Bluetooth device
	///   and service. </summary>
	const int WCL_E_BLUETOOTH_VCOM_EXISTS = WCL_E_BLUETOOTH_BASE + 0x006D;
	/// <summary> Unable create Bluetooth Device Statics interface. </summary>
	const int WCL_E_BLUETOOTH_CREATE_DEVICE_STATICS_FAILED = WCL_E_BLUETOOTH_BASE + 0x006E;
	/// <summary> Unable start Win RT asynchronous operation. </summary>
	const int WCL_E_BLUETOOTH_START_ASYNC_OPERATION_FAILED = WCL_E_BLUETOOTH_BASE + 0x006F;
	/// <summary> Unable set Win RT asynchronous operation event handler. </summary>
	const int WCL_E_BLUETOOTH_SET_ASYNC_OPERATION_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x0070;
	/// <summary> Unable create Bluetooth Device interface. </summary>
	const int WCL_E_BLUETOOTH_CREATE_DEVICE_FAILED = WCL_E_BLUETOOTH_BASE + 0x0071;
	/// <summary> Unable get Win RT async operation result. </summary>
	const int WCL_E_BLUETOOTH_GET_ASYNC_OPERATION_RESULT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0072;
	/// <summary> Failed to get Bluetooth Device ID. </summary>
	const int WCL_E_BLUETOOTH_GET_DEVICE_ID_FAILED = WCL_E_BLUETOOTH_BASE + 0x0073;
	/// <summary> Failed to read Bluetooth Device properties. </summary>
	const int WCL_E_BLUETOOTH_GET_DEVICE_PROPERTIES_FAILED = WCL_E_BLUETOOTH_BASE + 0x0074;
	/// <summary> Unable to start RSSI measurement thread. </summary>
	const int WCL_E_BLUETOOTH_START_RSSI_THREAD_FAILED = WCL_E_BLUETOOTH_BASE + 0x0075;
	/// <summary> This is Microsoft specific error indicates that the pairing with
	///   remote classic Bluetooth enabled device was not started and need to be
	///   re-initiated. </summary>
	const int WCL_E_BLUETOOTH_AUTHENTICATION_DEVICE_IGNORED = WCL_E_BLUETOOTH_BASE + 0x0076;
	/// <summary> Incompatible OS. This feature required to run x64 application
	///   on x64 platform and/or x86 application on x86 platform. </summary>
	const int WCL_E_BLUETOOTH_INCOMPATIBLE_OS_BITS = WCL_E_BLUETOOTH_BASE + 0x0077;
	/// <summary> Unable to get Bluetooth radios list. </summary>
	const int WCL_E_BLUETOOTH_GET_RADIOS_LIST_FAILED = WCL_E_BLUETOOTH_BASE + 0x0078;
	/// <summary> Unable to get number of available Bluetooth radios. </summary>
	const int WCL_E_BLUETOOTH_GET_RADIOS_COUNT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0079;
	/// <summary> Access to Bluetooth Radio driver instance has been failed. </summary>
	const int WCL_E_BLUETOOTH_GET_BLUETOOTH_RADIO_FAILED = WCL_E_BLUETOOTH_BASE + 0x007A;
	/// <summary> Unable to change Bluetooth Radio state. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CHANGE_RADIO_STATE = WCL_E_BLUETOOTH_BASE + 0x007B;
	/// <summary> Bluetooth features are unsupported by the hardware. </summary>
	const int WCL_E_BLUETOOTH_UNSUPPORTED_BY_HARDWARE = WCL_E_BLUETOOTH_BASE + 0x007C;
	/// <summary> A Bluetooth Radio object is closing. The operation can not be
	///   executed. </summary>
	const int WCL_E_BLUETOOTH_RADIO_CLOSING = WCL_E_BLUETOOTH_BASE + 0x007D;
	/// <summary> Unable to start asynchronous name reading of a remote Bluetooth
	///   LE device. </summary>
	const int WCL_E_BLUETOOTH_START_GET_DEV_NAME_THREAD_FAILED = WCL_E_BLUETOOTH_BASE + 0x007E;
	/// <summary> Invalid pairing method specified. </summary>
	const int WCL_E_BLUETOOTH_INVALID_PAIRING_METHOD = WCL_E_BLUETOOTH_BASE + 0x007F;
	/// <summary> No system resources. </summary>
	const int WCL_E_BLUETOOTH_NO_SYSTEM_RESOURCES = WCL_E_BLUETOOTH_BASE + 0x0080;
	/// <summary> Unable to create registry changes monitoring thread termination
	///   event. </summary>
	const int WCL_E_BLUETOOTH_CREATE_REG_CHANGE_TERMINATION_EVENT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0081;
	/// <summary> Unable to create registry changes monitoring thread
	///   initialization event. </summary>
	const int WCL_E_BLUETOOTH_CREATE_REG_CHANGE_RESULT_EVENT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0082;
	/// <summary> Failed to start registry changes monitoring thread. </summary>
	const int WCL_E_BLUETOOTH_START_REG_CHANGE_THREAD_FAILED = WCL_E_BLUETOOTH_BASE + 0x0083;
	/// <summary> Unable to registry authentication callback. </summary>
	const int WCL_E_BLUETOOTH_REGISTER_AUTHENTICATION_CALLBACK_FAILED = WCL_E_BLUETOOTH_BASE + 0x0084;
	/// <summary> Unable to open or create authentication agent registry key. </summary>
	const int WCL_E_BLUETOOTH_FAILED_TO_OPEN_AUTH_AGENT_REG_KEY = WCL_E_BLUETOOTH_BASE + 0x0085;
	/// <summary> Create registry changes notification event failed. </summary>
	const int WCL_E_BLUETOOTH_CREATE_REG_CHANGES_NOTIFICATION_EVENT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0086;
	/// <summary> Unable to set registry changes notification indication. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_SET_REGISTRY_CHANGES_NOTIFICATIONS = WCL_E_BLUETOOTH_BASE + 0x0087;
	/// <summary> Unable to disable Bluetooth Authentication Agent. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_DISABLE_AUTHENTICATION_AGENT = WCL_E_BLUETOOTH_BASE + 0x0088;
	/// <summary> Device has been paired by other application. </summary>
	const int WCL_E_BLUETOOTH_PAIRED_BY_OTHER = WCL_E_BLUETOOTH_BASE + 0x0089;
	/// <summary> Drivers for the Bluetooth device has already been installed. </summary>
	const int WCL_E_BLUETOOTH_DEVICE_ALREADY_INSTALLED = WCL_E_BLUETOOTH_BASE + 0x008A;
	/// <summary> Disconnect operation failed because device is not connected. </summary>
	const int WCL_E_BLUETOOTH_DEVICE_NOT_CONNECTED = WCL_E_BLUETOOTH_BASE + 0x008B;
	/// <summary> Device has not been installed. </summary>
	const int WCL_E_BLUETOOTH_DEVICE_NOT_INSTALLED = WCL_E_BLUETOOTH_BASE + 0x008C;
	/// <summary> Unable to enumerate connections. </summary>
	const int WCL_E_BLUETOOTH_ENUM_CONNECTION_FAILED = WCL_E_BLUETOOTH_BASE + 0x008D;
	/// <summary> Wait for Bluetooth communication events failed. </summary>
	const int WCL_E_BLUETOOTH_WAIT_FAILED = WCL_E_BLUETOOTH_BASE + 0x008E;
	/// <summary> The operation requires administrative rights. </summary>
	const int WCL_E_BLUETOOTH_ADMIN_RIGHTS_REQUIRED = WCL_E_BLUETOOTH_BASE + 0x008F;
	/// <summary> The discovering Timeout value is too high. You can not use
	///   Timeout greater than 61 seconds. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_TIMEOUT_TOO_HIGH = WCL_E_BLUETOOTH_BASE + 0x0090;
	/// <summary> The discovering Timeout is too low. You can not use Timeout
	///   less than 2 seconds. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_TIMEOUT_TOO_LOW = WCL_E_BLUETOOTH_BASE + 0x0091;
	/// <summary> Unable to read remote device's address type. </summary>
	const int WCL_E_BLUETOOTH_GET_REMOTE_ADDRESS_TYPE_FAILED = WCL_E_BLUETOOTH_BASE + 0x0092;
	/// <summary> Unable read device's address type because device's type is unknown. </summary>
	const int WCL_E_BLUETOOTH_UNKNOWN_DEVICE_TYPE = WCL_E_BLUETOOTH_BASE + 0x0093;
	/// <summary> Unable to start Win RT classic working thread. </summary>
	const int WCL_E_BLUETOOTH_START_WINRT_THREAD_FAILED = WCL_E_BLUETOOTH_BASE + 0x0094;
	/// <summary> Create Device Watcher Factory failed. </summary>
	const int WCL_E_BLUETOOTH_CREATE_WATCHER_FACTORY_FAILED = WCL_E_BLUETOOTH_BASE + 0x0095;
	/// <summary> Create device's filter for Device Watcher failed. </summary>
	const int WCL_E_BLUETOOTH_CREATE_FILTER_FAILED = WCL_E_BLUETOOTH_BASE + 0x0096;
	/// <summary> Create Bluetooth devices watcher failed. </summary>
	const int WCL_E_BLUETOOTH_CREATE_WATCHER_FAILED = WCL_E_BLUETOOTH_BASE + 0x0097;
	/// <summary> Create discovering completion event failed. </summary>
	const int WCL_E_BLUETOOTH_CREATE_COMPLETION_EVENT_FAILED = WCL_E_BLUETOOTH_BASE + 0x0098;
	/// <summary> Set Bluetooth device watcher Added event handler failed. </summary>
	const int WCL_E_BLUETOOTH_SET_ADDED_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x0099;
	/// <summary> Set Bluetooth device watcher Updated event handler failed. </summary>
	const int WCL_E_BLUETOOTH_SET_UPDATED_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x009A;
	/// <summary> Set Bluetooth device watcher Removed event handler failed. </summary>
	const int WCL_E_BLUETOOTH_SET_REMOVED_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x009B;
	/// <summary> Set Bluetooth device watcher Discovering Completed event handler failed. </summary>
	const int WCL_E_BLUETOOTH_SET_COMPLETED_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x009C;
	/// <summary> Start discovering failed. </summary>
	const int WCL_E_BLUETOOTH_WATCHER_START_FAILED = WCL_E_BLUETOOTH_BASE + 0x009D;
	/// <summary> Unable to create write completion event object. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_TO_CREATE_WRITE_EVENT = WCL_E_BLUETOOTH_BASE + 0x009E;
	/// <summary> Discovering has been canceled (aborted) by the system. </summary>
	const int WCL_E_BLUETOOTH_DISCOVERING_CANCELED = WCL_E_BLUETOOTH_BASE + 0x009F;
	/// <summary> Unable to create asynchronous operation termination indication
	///   event. </summary>
	const int WCL_E_BLUETOOTH_CREATE_STOPPED_EVENT_FAILED = WCL_E_BLUETOOTH_BASE + 0x00A0;
	/// <summary> Unable to set Win RT object's event handler. </summary>
	const int WCL_E_BLUETOOTH_SET_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_BASE + 0x00A1;
	/// <summary> Unable to register Wii Remote client connect notification
	///   message. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_REGISTER_CONNECT_MESSAGE = WCL_E_BLUETOOTH_BASE + 0x00A2;
	/// <summary> Unable to register Wii Remote client disconnect notification
	///   message. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_REGISTER_DISCONNECT_MESSAGE = WCL_E_BLUETOOTH_BASE + 0x00A3;
	/// <summary> Unable to register Wii Remote client data notification
	///   message. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_REGISTER_DATA_MESSAGE = WCL_E_BLUETOOTH_BASE + 0x00A4;
	/// <summary> Unable to create data received notification event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_DATA_EVENT = WCL_E_BLUETOOTH_BASE + 0x00A5;
	/// <summary> Unable to create pairing timeout event. </summary>
	const int WCL_E_BLUETOOTH_UNABLE_CREATE_PAIRING_TIMEOUT_EVENT = WCL_E_BLUETOOTH_BASE + 0x00A6;
	/// <summary> Bluetooth hardware failed. </summary>
	const int WCL_E_BLUETOOTH_HARDWARE_FAILED = WCL_E_BLUETOOTH_BASE + 0x00A7;
	/// <summary> A Classic Bluetooth Radio is not available. </summary>
	const int WCL_E_BLUETOOTH_CLASSIC_RADIO_UNAVAILABLE = WCL_E_BLUETOOTH_BASE + 0x00A8;
	/// <summary> The pairing is handled by the OS. </summary>
	const int WCL_E_BLUETOOTH_PAIRING_HANDLED_BY_SYSTEM = WCL_E_BLUETOOTH_BASE + 0x00A9;
	/// <summary> The Bluetooth radio instance was not found. </summary>
	const int WCL_E_BLUETOOTH_RADIO_INSTANCE_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x00AA;
	/// <summary> Unable to open a Bluetooth Radio driver. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_FAILED = WCL_E_BLUETOOTH_BASE + 0x00AB;
	/// <summary> Invalid Bluetooth Radio driver instance name. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_INVALID_DRIVER = WCL_E_BLUETOOTH_BASE + 0x00AC;
	/// <summary> Invalid Bluetooth Radio driver instance path. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_INVALID_PATH = WCL_E_BLUETOOTH_BASE + 0x00AD;
	/// <summary> An application does not have enough rights to open Bluetooth
	///   Radio driver. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_ACCESS_DENIED = WCL_E_BLUETOOTH_BASE + 0x00AE;
	/// <summary> Bluetooth Radio driver not found or not working. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_DEVICE_NOT_FOUND = WCL_E_BLUETOOTH_BASE + 0x00AF;
	/// <summary> The Bluetooth Radio driver is already in use by other
	///   application. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_IN_USE = WCL_E_BLUETOOTH_BASE + 0x00B0;
	/// <summary> Invalid parameters specified in Bluetooth Radio driver open
	///   request. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_INVALID_PARAM = WCL_E_BLUETOOTH_BASE + 0x00B1;
	/// <summary> Invalid Bluetooth Radio driver name. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_INVALID_NAME = WCL_E_BLUETOOTH_BASE + 0x00B2;
	/// <summary> Too many opened Bluetooth Radio driver instances. </summary>
	const int WCL_E_BLUETOOTH_OPEN_RADIO_COUNT_LIMIT = WCL_E_BLUETOOTH_BASE + 0x00B3;
	/// <summary> <para> A Bluetooth driver is busy. </para>
	///   <para> This error usually returned when your application tries to change
	///   Radio state (ON/OFF) right inside OnStatusChanged event handler when
	///   Radio was turned ON/OFF from system control panel. </para>
	///   <para> If you receive this error simple add small delay (about 200 ms)
	///   and try to switch radio state again. </para>. </summary>
	const int WCL_E_BLUETOOTH_DRIVER_BUSY = WCL_E_BLUETOOTH_BASE + 0x00B4;

	/* Bluetooth LE error codes. */

	/// <summary> The base error code for Bluetooth Low Energy. </summary>
	const int WCL_E_BLUETOOTH_LE_BASE = WCL_E_BLUETOOTH_BASE + 0x1000;
	/// <summary> The attribute handle given was not valid on this
	///   server. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_HANDLE = WCL_E_BLUETOOTH_LE_BASE + 0x0000;
	/// <summary> Attribute reading is not permitted. </summary>
	const int WCL_E_BLUETOOTH_LE_READ_NOT_PERMITTED = WCL_E_BLUETOOTH_LE_BASE + 0x0001;
	/// <summary> Attribute writing is not permitted. </summary>
	const int WCL_E_BLUETOOTH_LE_WRITE_NOT_PERMITTED = WCL_E_BLUETOOTH_LE_BASE + 0x0002;
	/// <summary> Invalid request format. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_PDU = WCL_E_BLUETOOTH_LE_BASE + 0x0003;
	/// <summary> The attribute requires authentication before it can be read or
	///   written. </summary>
	const int WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHENTICATION = WCL_E_BLUETOOTH_LE_BASE + 0x0004;
	/// <summary> Attribute server does not support the request received from the
	///   client. </summary>
	const int WCL_E_BLUETOOTH_LE_REQUEST_NOT_SUPPORTED = WCL_E_BLUETOOTH_LE_BASE + 0x0005;
	/// <summary> Offset specified was past the end of the attribute. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_OFFSET = WCL_E_BLUETOOTH_LE_BASE + 0x0006;
	/// <summary> The attribute requires authorization before it can be read or written. </summary>
	const int WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHORIZATION = WCL_E_BLUETOOTH_LE_BASE + 0x0007;
	/// <summary> Prepare queue is full. Too many prepare writes have been queued. </summary>
	const int WCL_E_BLUETOOTH_LE_PREPARE_QUEUE_FULL = WCL_E_BLUETOOTH_LE_BASE + 0x0008;
	/// <summary> No attribute found within the given attribute handle range. </summary>
	const int WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_FOUND = WCL_E_BLUETOOTH_LE_BASE + 0x0009;
	/// <summary> The attribute cannot be read or written using the Read Blob Request. </summary>
	const int WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_LONG = WCL_E_BLUETOOTH_LE_BASE + 0x000A;
	/// <summary> The Encryption Key Size used for encrypting this link is insufficient. </summary>
	const int WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION_KEYSIZE = WCL_E_BLUETOOTH_LE_BASE + 0x000B;
	/// <summary> The attribute value length is invalid for the operation. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_ATTRIBUTE_VALUE_LENGTH = WCL_E_BLUETOOTH_LE_BASE + 0x000C;
	/// <summary> The attribute requires encryption before it can be read or written. </summary>
	const int WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION = WCL_E_BLUETOOTH_LE_BASE + 0x000D;
	/// <summary> The attribute type is not a supported grouping attribute as
	///   defined by a higher layer specification. </summary>
	const int WCL_E_BLUETOOTH_LE_UNSUPPORTED_GROUP_TYPE = WCL_E_BLUETOOTH_LE_BASE + 0x000E;
	/// <summary> Insufficient Resources to complete the request. </summary>
	const int WCL_E_BLUETOOTH_LE_INSUFFICIENT_RESOURCES = WCL_E_BLUETOOTH_LE_BASE + 0x000F;
	/// <summary> SMP failed. </summary>
	const int WCL_E_BLUETOOTH_LE_SMP_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0010;
	/// <summary> Task cancel. </summary>
	const int WCL_E_BLUETOOTH_LE_TASK_CANCEL = WCL_E_BLUETOOTH_LE_BASE + 0x0011;
	/// <summary> Connect failed. </summary>
	const int WCL_E_BLUETOOTH_LE_CONNECT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0012;
	/// <summary> Response timed out. </summary>
	const int WCL_E_BLUETOOTH_LE_TIMEOUT = WCL_E_BLUETOOTH_LE_BASE + 0x0013;
	/// <summary> CCC improperly configured. </summary>
	const int WCL_E_BLUETOOTH_LE_WRONG_CONFIGURATION = WCL_E_BLUETOOTH_LE_BASE + 0x0014;
	/// <summary> Requested procedure is already in progress. </summary>
	const int WCL_E_BLUETOOTH_LE_PROCEDURE_IN_PROGRESS = WCL_E_BLUETOOTH_LE_BASE + 0x0015;
	/// <summary> Out of range. </summary>
	const int WCL_E_BLUETOOTH_LE_OUT_OF_RANGE = WCL_E_BLUETOOTH_LE_BASE + 0x0016;
	/// <summary> The access to the Bluetooth LE attribute failed. This is
	///   Microsoft specific error code and usually indicates that the driver or
	///   low-level API can not access to the internal GATT attribute
	///   object. </summary>
	const int WCL_E_BLUETOOTH_LE_ACCESS_DENIED = WCL_E_BLUETOOTH_LE_BASE + 0x0017;
	/// <summary> At least one subscription active. The error appears if you try
	///   to read services, characteristics or descriptors with
	///   <c>goReadFromDevice</c> flag and there is at least one subscription
	///   active. </summary>
	const int WCL_E_BLUETOOTH_LE_SUBSCRIPTION_ACTIVE = WCL_E_BLUETOOTH_LE_BASE + 0x0018;
	/// <summary> The GATT connection is already subscribed for this attribute
	///   changes notifications. </summary>
	const int WCL_E_BLUETOOTH_LE_ALREADY_SUBSCRIBED = WCL_E_BLUETOOTH_LE_BASE + 0x0019;
	/// <summary> The GATT connection has not been subscribed for this attribute
	///   changes notifications. </summary>
	const int WCL_E_BLUETOOTH_LE_NOT_SUBSCRIBED = WCL_E_BLUETOOTH_LE_BASE + 0x001A;
	/// <summary> The attribute request that was requested has encountered an
	///   error that was unlikely, and therefore could not be completed as
	///   requested. </summary>
	const int WCL_E_BLUETOOTH_LE_UNLIKELY = WCL_E_BLUETOOTH_LE_BASE + 0x001B;
	/// <summary> A remote device closes the connection. </summary>
	const int WCL_E_BLUETOOTH_LE_REMOTE_DEVICE_DISCONNECTS = WCL_E_BLUETOOTH_LE_BASE + 0x001C;
	/// <summary> A buffer is specified, but the buffer count size is smaller than
	///   what is required, in bytes. </summary>
	const int WCL_E_BLUETOOTH_LE_INAVLID_USER_BUFFER = WCL_E_BLUETOOTH_LE_BASE + 0x001D;
	/// <summary> The current data in the cache appears to be inconsistent, and
	///   is leading to internal errors. </summary>
	const int WCL_E_BLUETOOTH_LE_INCONSISTENT_DATA = WCL_E_BLUETOOTH_LE_BASE + 0x001E;
	/// <summary> The target server did not provide an appropriate network
	///   response. </summary>
	const int WCL_E_BLUETOOTH_LE_COMMUNICATION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x001F;
	/// <summary> The characteristic value is not readable as dictated by the
	///   characteristic properties. </summary>
	const int WCL_E_BLUETOOTH_LE_CHARACTERISTIC_NOT_READABLE = WCL_E_BLUETOOTH_LE_BASE + 0x0020;
	/// <summary> Unable to create Bluetooth LE Advertisement Watcher. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_WATCHER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0021;
	/// <summary> Unable to change Bluetooth LE Advertisement Watcher
	///   scanning mode. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_SCANNING_MODE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0022;
	/// <summary> Unable start Bluetooth LE Advertisement Watcher. </summary>
	const int WCL_E_BLUETOOTH_LE_START_WATCHER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0023;
	/// <summary> Unable to start Win RT LE working thread. </summary>
	const int WCL_E_BLUETOOTH_LE_START_WINRT_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0024;
	/// <summary> Unable to set Win RT object's event handler. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0025;
	/// <summary> Unable create Bluetooth LE Device Statics interface. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_DEVICE_STATICS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0026;
	/// <summary> Unable create Bluetooth LE Device interface. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_DEVICE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0027;
	/// <summary> Unable start Win RT asynchronous operation. </summary>
	const int WCL_E_BLUETOOTH_LE_START_ASYNC_OPERATION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0028;
	/// <summary> Unable set Win RT asynchronous operation event
	///   handler. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_ASYNC_OPERATION_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0029;
	/// <summary> Unable get Win RT async operation result. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_ASYNC_OPERATION_RESULT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002A;
	/// <summary> Unable create IBluetoothLEDevice2 interface. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_DEVICE2_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002B;
	/// <summary> Unable to get IDeviceInformation interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_INFORMATION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002C;
	/// <summary> Unable to get IDeviceInformation2 interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_INFORMATION2_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002D;
	/// <summary> Unable to get IDeviceInformationPairing interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_INFORMATION_PAIRING_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002E;
	/// <summary> Unable to get IDeviceInformationPairing2 interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_INFORMATION_PAIRING2_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x002F;
	/// <summary> Unable to get IDeviceInformationCustomPairing interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_INFORMATION_CUSTOM_PAIRING_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0030;
	/// <summary> Bluetooth Beacons monitoring is running. </summary>
	const int WCL_E_BLUETOOTH_LE_BEACON_MONITORING_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x0031;
	/// <summary> Bluetooth Beacons monitoring is not running. </summary>
	const int WCL_E_BLUETOOTH_LE_BEACON_MONITORING_NOT_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x0032;
	/// <summary> The Bluetooth LE advertising is already running. </summary>
	const int WCL_E_BLUETOOTH_LE_ADVERTISING_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x0033;
	/// <summary> The Bluetooth LE advertising is not running. </summary>
	const int WCL_E_BLUETOOTH_LE_ADVERTISING_NOT_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x0034;
	/// <summary> Unable create initialization event for the Bluetooth LE
	///   advertising thread. </summary>
	const int WCL_E_BLUETOOTH_LE_ADVERTISING_UNBALE_CREATE_INIT_EVENT = WCL_E_BLUETOOTH_LE_BASE + 0x0035;
	/// <summary> Unable create termination event for the Bluetooth LE
	///   advertising thread. </summary>
	const int WCL_E_BLUETOOTH_LE_ADVERTISING_UNBALE_CREATE_TERMINATE_EVENT = WCL_E_BLUETOOTH_LE_BASE + 0x0036;
	/// <summary> Unable start Bluetooth LE Advertising thread. </summary>
	const int WCL_E_BLUETOOTH_LE_ADVERTISING_UNBALE_START_THREAD = WCL_E_BLUETOOTH_LE_BASE + 0x0037;
	/// <summary> An application executes Write Without Response with value size
	///   longer than maximum PDU size (MTU). An application must use Write With
	///   Response instead. To do that an application must set
	///   <c>IsWritableWithoutResponse</c> characteristic's property to
	///   <c>false</c> and then call the <c>WriteCharacteristicValue</c>
	///   method to force Write With Response. </summary>
	const int WCL_E_BLUETOOTH_LE_WRITE_VALUE_TOO_LONG = WCL_E_BLUETOOTH_LE_BASE + 0x0038;
	/// <summary> Unable to get Bluetooth LE Advertiser object. </summary>
	const int WCL_E_BLUETOOTH_LE_UNABLE_GET_ADVERTISER = WCL_E_BLUETOOTH_LE_BASE + 0x0039;
	/// <summary> Unable to start subscribing thread. </summary>
	const int WCL_E_BLUETOOTH_LE_SUBSCRIBE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x003A;
	/// <summary> No subscribed clients found. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_NO_SUBSCRIBED_CLIENTS = WCL_E_BLUETOOTH_LE_BASE + 0x003B;
	/// <summary> Unable to create connection completion event. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_CONNECTION_COMPLETION_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x003C;
	/// <summary> Unable to start LE devices discovering thread. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_DISCOVERING_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x003D;
	/// <summary> The URL passed to the Eddystone URL Beacon is empty or too
	///   short. The length of the URL must be at least 8 characters. </summary>
	const int WCL_E_BLUETOOTH_LE_EDDYSTONE_URL_TOO_SHORT = WCL_E_BLUETOOTH_LE_BASE + 0x003E;
	/// <summary> Invalid Eddystone URL Beacon URL scheme. An URL must start with
	///   "http://" or "https://".  </summary>
	const int WCL_E_BLUETOOTH_LE_EDDYSTONE_URL_SCHEME_INVALID = WCL_E_BLUETOOTH_LE_BASE + 0x003F;
	/// <summary> The Eddystone URL Beacon URL is too long. </summary>
	const int WCL_E_BLUETOOTH_LE_EDDYSTONE_URL_TOO_LONG = WCL_E_BLUETOOTH_LE_BASE + 0x0040;
	/// <summary> Failed to start asynchronous pairing with Bluetooth LE device. </summary>
	const int WCL_E_BLUETOOTH_LE_ASYNC_PAIR_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0041;
	/// <summary> Error during executing asynchronous pairing with Bluetooth LE device. </summary>
	const int WCL_E_BLUETOOTH_LE_ASYNC_PAIR_ERROR = WCL_E_BLUETOOTH_LE_BASE + 0x0042;
	/// <summary> The OS does not support automatic connection to BLE device
	///   and manual pairing is required. </summary>
	const int WCL_E_BLUETOOTH_LE_MANUAL_PAIRING_REQUIRED = WCL_E_BLUETOOTH_LE_BASE + 0x0043;
	/// <summary> The device object is not in a state where it can be paired. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_NOT_READY_TO_PAIR = WCL_E_BLUETOOTH_LE_BASE + 0x0044;
	/// <summary> The device object is not currently paired. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_NOT_PAIRED = WCL_E_BLUETOOTH_LE_BASE + 0x0045;
	/// <summary> The device object rejected the connection. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_CONNECTION_REJECTED = WCL_E_BLUETOOTH_LE_BASE + 0x0046;
	/// <summary> The device object indicated it cannot accept any more incoming connections. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_TOO_MANY_CONNECTIONS = WCL_E_BLUETOOTH_LE_BASE + 0x0047;
	/// <summary> The device object indicated there was a hardware failure. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_HARDWARE_FAILURE = WCL_E_BLUETOOTH_LE_BASE + 0x0048;
	/// <summary> The authentication process timed out before it could complete. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_TIMEOUT = WCL_E_BLUETOOTH_LE_BASE + 0x0049;
	/// <summary> The authentication protocol is not supported, so the device is not paired. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_NOT_ALLOWED = WCL_E_BLUETOOTH_LE_BASE + 0x004A;
	/// <summary> Authentication failed, so the device is not paired. Either the
	///   device object or the application rejected the authentication. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_FAILURE = WCL_E_BLUETOOTH_LE_BASE + 0x004B;
	/// <summary> There are no network profiles for this device object to use. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_NO_SUPPORTED_PROFILE = WCL_E_BLUETOOTH_LE_BASE + 0x004C;
	/// <summary> The minimum level of protection is not supported by the device
	///   object or the application. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_PROTECTION_LEVEL_COULD_NOT_BE_MET = WCL_E_BLUETOOTH_LE_BASE + 0x004D;
	/// <summary> Your application does not have the appropriate permissions level
	///   to pair the device object. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_ACCESS_DENIED = WCL_E_BLUETOOTH_LE_BASE + 0x004E;
	/// <summary> The ceremony data was incorrect. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_INVALID_CEREMONY_DATA = WCL_E_BLUETOOTH_LE_BASE + 0x004F;
	/// <summary> The pairing action was canceled before completion. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_PAIRING_CANCELED = WCL_E_BLUETOOTH_LE_BASE + 0x0050;
	/// <summary> The device object is already attempting to pair or unpair. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_OPERATION_ALREADY_IN_POROGRESS = WCL_E_BLUETOOTH_LE_BASE + 0x0051;
	/// <summary> Either the event handler was not registered or a required
	///   pairing method was not supported. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_REQUIRED_HANDLER_NOT_REGISTERED = WCL_E_BLUETOOTH_LE_BASE + 0x0052;
	/// <summary> The application handler rejected the pairing. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_REJECTED_BY_HANDLER = WCL_E_BLUETOOTH_LE_BASE + 0x0053;
	/// <summary> The remove device already has an association. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_REMOTE_DEVICE_HAS_ASSOCIATION = WCL_E_BLUETOOTH_LE_BASE + 0x0054;
	/// <summary> An unknown failure occurred. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0055;
	/// <summary> Failed to change protection level. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_PROTECTION_LEVEL_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0056;
	/// <summary> The characteristic value is not writable as dictated by the
	///   characteristic properties. </summary>
	const int WCL_E_BLUETOOTH_LE_CHARACTERISTIC_NOT_WRITABLE = WCL_E_BLUETOOTH_LE_BASE + 0x0057;
	/// <summary> Attempt to connect to not previously discovered Bluetooth LE
	///   GATT device. Device object was not found by the system. </summary>
	const int WCL_E_BLUETOOTH_LE_DEVICE_NOT_DISCOVERED = WCL_E_BLUETOOTH_LE_BASE + 0x0058;
	/// <summary> A device has already been paired. </summary>
	const int WCL_E_BLUETOOTH_LE_ALREADY_PAIRED = WCL_E_BLUETOOTH_LE_BASE + 0x0059;
	/// <summary> Bluetooth LE features are unsupported by the hardware. Bluetooth
	///   LE features requires Bluetooth 4.0 or newest Bluetooth hardware with
	///   HCI version 6 and above. </summary>
	const int WCL_E_BLUETOOTH_LE_UNSUPPORTED_BY_HARDWARE = WCL_E_BLUETOOTH_LE_BASE + 0x005A;
	/// <summary> Unable to create LE devices discovering thread termination
	///   event. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_DISCOVERING_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x005B;
	/// <summary> A specified remote Bluetooth LE device was not found. </summary>
	const int WCL_E_BLUETOOTH_LE_DEVICE_NOT_FOUND = WCL_E_BLUETOOTH_LE_BASE + 0x005C;
	/// <summary> Failed to get Bluetooth LE Device ID. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_ID_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x005D;
	/// <summary> Failed to read Bluetooth LE Device properties. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_PROPERTIES_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x005E;
	/// <summary> The requested feature is not supported bu a Bluetooth LE
	///   driver. </summary>
	const int WCL_E_BLUETOOTH_LE_FEATURE_NOT_SUPPORTED = WCL_E_BLUETOOTH_LE_BASE + 0x005F;
	/// <summary> Unable to read RSSI value. </summary>
	const int WCL_E_BLUETOOTH_LE_UNABLE_READ_RSSI = WCL_E_BLUETOOTH_LE_BASE + 0x0060;
	/// <summary> Unable to start BLE RSSI measurement thread. </summary>
	const int WCL_E_BLUETOOTH_LE_START_RSSI_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0061;
	/// <summary> Application error code defined by a higher layer specification. </summary>
	const int WCL_E_BLUETOOTH_LE_APPLICATION = WCL_E_BLUETOOTH_LE_BASE + 0x0062;
	/// <summary> Pairing or authentication procedure is disallowed because too
	///   little time has elapsed since last pairing request or security
	///   request. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_REPEATED_ATTEMPTS = WCL_E_BLUETOOTH_LE_BASE + 0x0063;
	/// <summary> Out of Band data is not available for authentication. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_OOB_NOT_AVAILABLE = WCL_E_BLUETOOTH_LE_BASE + 0x0064;
	/// <summary> Unable to get information about Bluetooth LE service that
	///   owns an attribute. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_ROOT_SERVICE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0065;
	/// <summary> Unable to read Bluetooth LE GATT service handle. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_SERVICE_HANDLE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0066;
	/// <summary> Unable to read Bluetooth LE GATT characteristic
	///   handle. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISTIC_HANDLE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0067;
	/// <summary> Unable to read Bluetooth LE GATT descriptor handle. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_HANDLE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0068;
	/// <summary> Unable to read Bluetooth LE GATT descriptor UUID. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_UUID_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0069;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   formats list. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMATS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006A;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   formats list size (length). </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMATS_LIST_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006B;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006C;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format type. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_TYPE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006D;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format exponent. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_EXPONENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006E;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format unit. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_UNIT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x006F;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format namespace. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_NAMESPACE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0070;
	/// <summary> Unable to read Bluetooth LE GATT characteristics presentation
	///   format description. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_PRESENTATION_FORMAT_DESCRIPTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0071;
	/// <summary> Unable to get Bluetooth LE GATT descriptor value
	///   size. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_VALUE_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0072;
	/// <summary> Unable to get access to Bluetooth LE GATT descriptor value raw
	///   data. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_VALUE_RAW_DATA_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0073;
	/// <summary> Unable to get access to Bluetooth LE GATT descriptor value
	///   data. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_VALUE_DATA_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0074;
	/// <summary> Unable to read Bluetooth LE GATT characteristic UUID. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISTIC_UUID_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0075;
	/// <summary> Unable to read Bluetooth LE GATT characteristic
	///   properties. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISTIC_PROPETIES_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0076;
	/// <summary> Unable to get Bluetooth LE GATT descriptor value data
	///   buffer. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTOR_VALUE_DATA_BUFFER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0077;
	/// <summary> Unable to get Bluetooth LE GATT characteristic value data
	///   buffer. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISTIC_VALUE_DATA_BUFFER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0078;
	/// <summary> Unable to get Bluetooth LE GATT characteristic value
	///   size. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISTIC_VALUE_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0079;
	/// <summary> Unable to get access to Bluetooth LE GATT characteristic value
	///   raw data. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISITC_VALUE_RAW_DATA_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007A;
	/// <summary> Unable to get access to Bluetooth LE GATT characteristic value
	///   data. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISITC_VALUE_DATA_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007B;
	/// <summary> Unable to read Bluetooth LE GATT descriptors list size
	///   (length). </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DESCRIPTORS_LIST_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007C;
	/// <summary> Unable to read Bluetooth LE GATT service UUID. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_SERVICE_UUID_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007D;
	/// <summary> Unable to read Bluetooth LE GATT characteristics list size
	///   (length). </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CHARACTERISITCS_LIST_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007E;
	/// <summary> Unable to read Bluetooth LE GATT services list size
	///   (length). </summary>
	const int WCL_E_BLUETOOTH_LE_GET_SERVICES_LIST_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x007F;
	/// <summary> Unable to start reading device's connected status thread. </summary>
	const int WCL_E_BLUETOOTH_LE_START_GET_DEV_CONNECTED_STATUS_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0080;
	/// <summary> LL initiated a connection but the connection has failed to be
	///   established. Controller did not receive any packets from remote
	///   end. </summary>
	const int WCL_E_BLUETOOTH_LE_CONNECTION_ESTABLISHING_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0081;
	/// <summary> Unable to get Bluetooth LE device connected status. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTED_STATUS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0082;
	/// <summary> Unable to start Bluetooth LE device paired status reading thread. </summary>
	const int WCL_E_BLUETOOTH_LE_START_GET_DEV_PAIRED_STATUS_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0083;
	/// <summary> Connection was terminated because the Message Integrity Check
	///   (MIC) failed on a received packet. </summary>
	const int WCL_E_BLUETOOTH_LE_MIC_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0084;
	/// <summary> Unable to get Bluetooth LE device's paired status. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_DEVICE_PAIRED_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0085;
	/// <summary> GATT protocol error. Usually this error indicates that a client
	///   sent wrong data to a server. Or sometime it may indicates that server
	///   requires subscribing to a characteristic before it can accept any
	///   write requests. </summary>
	const int WCL_E_BLUETOOTH_LE_PROTOCOL_ERROR = WCL_E_BLUETOOTH_LE_BASE + 0x0086;
	/// <summary> The characteristic has already been added to the local GATT
	///   service. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CHARACTERISTIC_ADDED = WCL_E_BLUETOOTH_LE_BASE + 0x0087;
	/// <summary> The characteristic has already been removed from the local GATT
	///   service. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CHARACTERISTIC_REMOVED = WCL_E_BLUETOOTH_LE_BASE + 0x0088;
	/// <summary> The service has already been added to the GATT server. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SERVICE_ADDED = WCL_E_BLUETOOTH_LE_BASE + 0x0089;
	/// <summary> The service has already been removed from the GATT server. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SERVICE_REMOVED = WCL_E_BLUETOOTH_LE_BASE + 0x008A;
	/// <summary> The GATT server is running (advertising). </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x008B;
	/// <summary> The GATT server is not running. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_NOT_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x008C;
	/// <summary> Failed to create GATT server thread initialization event. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_INIT_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x008D;
	/// <summary> Failed to create GATT server thread termination event. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_TERM_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x008E;
	/// <summary> Failed to create GATT server communication thread. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_THREAD_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x008F;
	/// <summary> Failed to get GATT local service interface. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_GET_SERVICE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0090;
	/// <summary> Unable to create local GATT characteristic parameters object. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0091;
	/// <summary> Failed to set local GATT characteristic read protection level. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_READ_PROTECTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0092;
	/// <summary> Failed to set local GATT characteristic write protection level. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_WRITE_PROTECTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0093;
	/// <summary> Unable to set properties of a local GATT characteristic. </summary> 
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_PROPERTIES_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0094;
	/// <summary> Unable to create local GATT characteristic. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_CHARACTERISTIC_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0095;
	/// <summary> Local GATT characteristic was not created by unknown reason. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_INVALID_CHARACTERISTIC = WCL_E_BLUETOOTH_LE_BASE + 0x0096;
	/// <summary> Failed to set local GATT service advertisement parameters. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_ADV_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0097;
	/// <summary> Bluetooth hardware does not support peripheral mode. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_PERIPHERAL_MODE_NOT_SUPPORTED = WCL_E_BLUETOOTH_LE_BASE + 0x0098;
	/// <summary> Unable to publish local GATT service. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_START_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x0099;
	/// <summary> Unable to create local GATT service. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_SERVICE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x009A;
	/// <summary> Local GATT service was not created by unknown reason. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_INVALID_SERVICE = WCL_E_BLUETOOTH_LE_BASE + 0x009B;
	/// <summary> The GATT server is not initialized. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_NOT_INITIALIZED = WCL_E_BLUETOOTH_LE_BASE + 0x009C;
	/// <summary> The GATT server has already been initialized. </summary> 
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_INITIALIZED = WCL_E_BLUETOOTH_LE_BASE + 0x009D;
	/// <summary> Unable to set GATT local characteristic write request event
	///   handler. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_WRITE_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x009E;
	/// <summary> Unable to set GATT local characteristic read request event
	///   handler. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_READ_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x009F;
	/// <summary> Unable to set GATT local characteristic subscribed clients changed event handler. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_CLIENTS_CHANGED_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00A0;
	/// <summary> Unable to start unsubscribing thread. </summary>
	const int WCL_E_BLUETOOTH_LE_UNSUBSCRIBE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00A1;
	/// <summary> One or more connection parameter values are not valid. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_CONNECTION_PARAMETERS_VALUE = WCL_E_BLUETOOTH_LE_BASE + 0x00A2;
	/// <summary> Characteristic is not notifiable or indicatable. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CHARACTERISTIC_NOT_NOTIFIABLE = WCL_E_BLUETOOTH_LE_BASE + 0x00A3;
	/// <summary> Directed advertising completed without a connection being
	///   created. </summary>
	const int WCL_E_BLUETOOTH_LE_DIRECT_ADVERTISING_TIMEOUT = WCL_E_BLUETOOTH_LE_BASE + 0x00A4;
	/// <summary> Unable to create GATT Server protection mutex. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_MUTEX_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00A5;
	/// <summary> Other instance of the GATT server is already running. Only
	///   one instance of the GATT server is allowed. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_OTHER_INSTANCE_RUNNING = WCL_E_BLUETOOTH_LE_BASE + 0x00A6;
	/// <summary> A client is not connected to a Bluetooth device. </summary>
	const int WCL_E_BLUETOOTH_LE_CLIENT_NOT_CONNECTED = WCL_E_BLUETOOTH_LE_BASE + 0x00A7;
	/// <summary> Unexpected or unknown error. </summary>
	const int WCL_E_BLUETOOTH_LE_UNEXPECTED = WCL_E_BLUETOOTH_LE_BASE + 0x00A8;
	/// <summary> Unable to set Bluetooth LE scan parameters. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_SCAN_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00A9;
	/// <summary> A characteristic does not support the Write Without Response operation. </summary>
	const int WCL_E_BLUETOOTH_LE_WRITE_WITHOUT_RESPONSE_NOT_SUPPORTED = WCL_E_BLUETOOTH_LE_BASE + 0x00AA;
	/// <summary> Unable to create scan parameters changing event. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_SCAN_PARAMS_SET_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00AB;
	/// <summary> Unable to set Bluetooth LE advertising parameters. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_ADV_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00AC;
	/// <summary> The error code indicates that the remote device terminated the
	///   connection because of an unacceptable connection interval. </summary>
	const int WCL_E_BLUETOOTH_LE_WRONG_CONNECTION_INTERVAL = WCL_E_BLUETOOTH_LE_BASE + 0x00AD;
	/// <summary> Get connection PHY value failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTION_PHY_VALUE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00AE;
	/// <summary> Unable to open process token. </summary>
	const int WCL_E_BLUETOOTH_LE_OPEN_PROCESS_TOKEN_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00AF;
	/// <summary> Unable to find one or more required privilege. </summary> 
	const int WCL_E_BLUETOOTH_LE_LOOKUP_PRIVILEGE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B0;
	/// <summary> Unable to change one or more privilege. </summary>
	const int WCL_E_BLUETOOTH_LE_ADJUST_PRIVILEGE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B1;
	/// <summary> Unable to allocate and initialize SID. </summary>
	const int WCL_E_BLUETOOTH_LE_ALLOCATE_SID_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B2;
	/// <summary> Unable to take registry key ownership. </summary>
	const int WCL_E_BLUETOOTH_LE_TAKE_OWNERSHIP_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B3;
	/// <summary> Unable to set ACL. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_ACL_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B4;
	/// <summary> Unable to change registry access rights. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_REGISTRY_RIGHTS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B5;
	/// <summary> The characteristic has invalid configuration. This error means
	///   that the characteristic has both <c>IsNotifiable</c> and
	///   <c>IsIndicatable</c> properties are set to <c>True</c>. Set one of
	///   the property to <c>False</c>. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_CHARACTERISTIC_CONFIGURATION = WCL_E_BLUETOOTH_LE_BASE + 0x00B6;
	/// <summary> Unable to create asynchronous operation termination indication
	///   event. </summary>
	const int WCL_E_BLUETOOTH_LE_CREATE_STOPPED_EVENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00B7;
	/// <summary> Discovering has been terminated. </summary>
	const int WCL_E_BLUETOOTH_LE_DISCOVERING_TERMINATED = WCL_E_BLUETOOTH_LE_BASE + 0x00B8;
	/// <summary> Discovering has been canceled (aborted) by the system. </summary>
	const int WCL_E_BLUETOOTH_LE_DISCOVERING_CANCELED = WCL_E_BLUETOOTH_LE_BASE + 0x00B9;
	/// <summary> Local device terminated the connection. </summary>
	const int WCL_E_BLUETOOTH_LE_CONNECTION_TERMINATED = WCL_E_BLUETOOTH_LE_BASE + 0x00BA;
	/// <summary> Bluetooth LE advertisement initialization failed. </summary>
	const int WCL_E_BLUETOOTH_LE_INIT_ADVERTISEMENT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00BB;
	/// <summary> Bluetooth LE advertisement type is not supported. </summary>
	const int WCL_E_BLUETOOTH_LE_UNSUPPORTED_ADVERTISEMENT_TYPE = WCL_E_BLUETOOTH_LE_BASE + 0x00BC;
	/// <summary> Bluetooth LE advertisement has invalid format. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_ADVERTISEMENT_FORMAT = WCL_E_BLUETOOTH_LE_BASE + 0x00BD;
	/// <summary> A Bluetooth LE Radio is not available. </summary>
	const int WCL_E_BLUETOOTH_LE_RADIO_UNAVAILABLE = WCL_E_BLUETOOTH_LE_BASE + 0x00BE;
	/// <summary> Unable to get the current connection parameters. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTION_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00BF;
	/// <summary> Invalid or unknown preferred connection parameters type. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_CONNECTION_PARAMS = WCL_E_BLUETOOTH_LE_BASE + 0x00C0;
	/// <summary> Unable to set the current connection parameters. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_CONNECTION_PARAMS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C1;
	/// <summary> The extended advertisement properties are not supported.
	///   Set the <c>UseExtendedAdvertisement</c> property of the
	///   <c>wclBluetoothLeAdvertiser</c> component to <c>False</c> and
	///   try to restart the advertisement. </summary>
	const int WCL_E_BLUETOOTH_LE_EXT_ADV_NOT_SUPPORTED = WCL_E_BLUETOOTH_LE_BASE + 0x00C2;
	/// <summary> Set extended advertisement properties failed. </summary>
	const int WCL_E_BLUETOOTH_LE_SET_EXT_ADV_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C3;
	/// <summary> Unable to set client disconnect event handler for the GATT
	///   server. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_DISCONNECT_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C4;
	/// <summary> The client is not subscribed to any GATT server characteristic. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CLIENT_NOT_SUBSCRIBED = WCL_E_BLUETOOTH_LE_BASE + 0x00C5;
	/// <summary> Unable to read maximum notification size. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CLIENT_GET_MAX_NOTIFICATION_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C6;
	/// <summary> Unable to get maximum PDU size. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_MAX_PDU_SIZE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C7;
	/// <summary> Unknown or unexpected error appeared during pairing procedure. </summary>
	const int WCL_E_BLUETOOTH_LE_AUTH_UNKNOWN = WCL_E_BLUETOOTH_LE_BASE + 0x00C8;
	/// <summary> Unable to set disconnect event handler for the GATT client. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_CLIENT_SET_DISCONNECT_EVENT_HANDLER_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00C9;
	/// <summary> Unable to set local GATT characteristic user-friendly description. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_DESCRIPTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CA;
	/// <summary> Unable to get GATT local characteristic presentation formats list. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_GET_FORMATS_LIST_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CB;
	/// <summary> Unable to create GATT local characteristic presentation format statics. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_FORMAT_STATICS_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CC;
	/// <summary> Unable to create GATT local characteristic presentation format. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_FORMAT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CD;
	/// <summary> Unable to add GATT local characteristic presentation format. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_ADD_FORMAT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CE;
	/// <summary> Read characteristic's user description descriptor failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_USER_DESCRIPTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00CF;
	/// <summary> The descriptor with given UUID can not be used as custom
	///   descriptor in GATT server. </summary>
	const int WCL_E_BLUETOOTH_LE_INVALID_DESCRIPTOR_UUID = WCL_E_BLUETOOTH_LE_BASE + 0x00D0;
	/// <summary> Create custom descriptor failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_CREATE_DESCRIPTOR_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D1;
	/// <summary> Unable to add custom descriptor. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_ADD_DESCRIPTOR_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D2;
	/// <summary> Set descriptor's value failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_DESCRIPTOR_VALUE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D3;
	/// <summary> Failed to set local GATT descriptor read protection level. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_DESCRIPTOR_READ_PROTECTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D4;
	/// <summary> Failed to set local GATT descriptor write protection level. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SET_DESCRIPTOR_WRITE_PROTECTION_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D5;
	/// <summary> Unable to get result of descriptor creation operation. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_GET_CREATE_DESCRIPTOR_RESULT_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D6;
	/// <summary> Unable to get result code of description creation operation. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_GET_CREATE_DESCRIPTOR_ERROR_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D7;
	/// <summary> Unable to get Bluetooth LE connection PHY data. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTION_PHY_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D8;
	/// <summary> Get transmit PHY information failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTION_TX_PHY_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00D9;
	/// <summary> Get receive PHY information failed. </summary>
	const int WCL_E_BLUETOOTH_LE_GET_CONNECTION_RX_PHY_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00DA;
	/// <summary> There is no advertisements that can be advertised. </summary>
	const int WCL_E_BLUETOOTH_LE_NOTHING_ADVERTISE = WCL_E_BLUETOOTH_LE_BASE + 0x00DB;
	/// <summary> Too many advertisements. </summary>
	const int WCL_E_BLUETOOTH_LE_TOO_MANY_ADVERTISEMENTS = WCL_E_BLUETOOTH_LE_BASE + 0x00DC;
	/// <summary> Unable to send response to a connected GATT client. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_SEND_RESPONSE_FAILED = WCL_E_BLUETOOTH_LE_BASE + 0x00DD;
	/// <summary> The write operation was requested as Write Without Response. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_WRITE_WITHOUT_RESPONSE = WCL_E_BLUETOOTH_LE_BASE + 0x00DE;
	/// <summary> The response was already sent. </summary>
	const int WCL_E_BLUETOOTH_LE_GATT_SERVER_RESPONSE_ALREADY_SENT = WCL_E_BLUETOOTH_LE_BASE + 0x00DF;
	
	/* Wii Remote error codes. */

	/// <summary> The base error code for Wii Remote errors. </summary>
	const int WCL_E_WII_REMOTE_BASE = WCL_E_BLUETOOTH_BASE + 0x2000;
	/// <summary> Can not create HID devices list. </summary>
	const int WCL_E_WII_REMOTE_ENUM_HID_FAILED = WCL_E_WII_REMOTE_BASE + 0x0000;
	/// <summary> A Wii Remote controller has not been installed.</summary>
	const int WCL_E_WII_REMOTE_NOT_INSTALLED = WCL_E_WII_REMOTE_BASE + 0x0001;
	/// <summary> Unable to create overlapped read event. </summary>
	const int WCL_E_WII_REMOTE_CREATE_READ_EVENT_FAILED = WCL_E_WII_REMOTE_BASE + 0x0002;
	/// <summary> Unable to create overlapped write event. </summary>
	const int WCL_E_WII_REMOTE_CREATE_WRITE_EVENT_FAILED = WCL_E_WII_REMOTE_BASE + 0x0003;
	/// <summary> Unable to connect to the Wii Remote controller. </summary>
	const int WCL_E_WII_REMOTE_CONNECT_FAILED = WCL_E_WII_REMOTE_BASE + 0x0004;
	/// <summary> Unable to create HID API access mutex. </summary>
	const int WCL_E_WII_REMOTE_HID_UNABLE_CREATE_MUTEX = WCL_E_WII_REMOTE_BASE + 0x0005;
	/// <summary> HID subsystem is not available on this platform. </summary>
	const int WCL_E_WII_REMOTE_HID_SUBSYSTEM_NOT_AVAILABLE = WCL_E_WII_REMOTE_BASE + 0x0006;
	/// <summary> Not all required HID features are supported by the
	///   system. </summary>
	const int WCL_E_WII_REMOTE_HID_NOT_SUPPORTED = WCL_E_WII_REMOTE_BASE + 0x0007;
	/// <summary> Read data from the Wii Remote failed. </summary>
	const int WCL_E_WII_REMOTE_READ_REPORT_FAILED = WCL_E_WII_REMOTE_BASE + 0x0008;
	/// <summary> Write data to the Wii Remote failed. </summary>
	const int WCL_E_WII_REMOTE_WRITE_REPORT_FAILED = WCL_E_WII_REMOTE_BASE + 0x0009;
	/// <summary> Write data to the Wii Remote has timed out. </summary>
	const int WCL_E_WII_REMOTE_WRITE_REPORT_TIMEOUT = WCL_E_WII_REMOTE_BASE + 0x000A;
	/// <summary> Unable to create read memory event object. </summary>
	const int WCL_E_WII_REMOTE_CREATE_READ_MEMORY_EVENT_FAILED = WCL_E_WII_REMOTE_BASE + 0x000B;
	/// <summary> Unable to create write memory event object. </summary>
	const int WCL_E_WII_REMOTE_CREATE_WRITE_MEMORY_EVENT_FAILED = WCL_E_WII_REMOTE_BASE + 0x000C;
	/// <summary> The Wii Remote controller has not been initialized
	///   yet. </summary>
	const int WCL_E_WII_REMOTE_NOT_INITIALIZED = WCL_E_WII_REMOTE_BASE + 0x000D;
	/// <summary> Wrong IR sensor level has been specified. </summary>
	const int WCL_E_WII_REMOTE_IR_LEVEL_WRONG = WCL_E_WII_REMOTE_BASE + 0x000E;
	/// <summary> Unknown IR sensor level has been specified. </summary>
	const int WCL_E_WII_REMOTE_IR_LEVEL_UNKNOWN = WCL_E_WII_REMOTE_BASE + 0x000F;
	/// <summary> Wrong IR sensor mode has been specified. </summary>
	const int WCL_E_WII_REMOTE_IR_MODE_WRONG = WCL_E_WII_REMOTE_BASE + 0x0010;
	/// <summary> Unknown IR sensor mode has been specified. </summary>
	const int WCL_E_WII_REMOTE_IR_MODE_UNKNOWN = WCL_E_WII_REMOTE_BASE + 0x0011;
	/// <summary> The extension has not been detected (or partially inserted)
	///   during initialization. </summary>
	const int WCL_E_WII_REMOTE_EXTENSION_NOT_FOUND = WCL_E_WII_REMOTE_BASE + 0x0012;
	/// <summary> Unknown or unsupported extension has been attached. </summary>
	const int WCL_E_WII_REMOTE_EXTENSION_UNKNOWN = WCL_E_WII_REMOTE_BASE + 0x0013;
	/// <summary> The requested feature is not supported. Probably because
	///   Balance Board is connected. </summary>
	const int WCL_E_WII_REMOTE_FEATURE_NOT_SUPPORTED = WCL_E_WII_REMOTE_BASE + 0x0014;
	/// <summary> Accelerometer is already enabled. </summary>
	const int WCL_E_WII_REMOTE_ACCELEROMETER_ENABLED = WCL_E_WII_REMOTE_BASE + 0x0015;
	/// <summary> Accelerometer is disabled. </summary>
	const int WCL_E_WII_REMOTE_ACCELEROMETER_DISABLED = WCL_E_WII_REMOTE_BASE + 0x0016;
	/// <summary> Invalid Wii Remote configuration. </summary>
	const int WCL_E_WII_REMOTE_INVALID_CONFIGURATION = WCL_E_WII_REMOTE_BASE + 0x0017;

	/* BLED112 error codes. */

	/// <summary> The base error code for BLED112 errors. </summary>
	const int WCL_E_BLED112_BASE = WCL_E_BLUETOOTH_BASE + 0x3000;
	/// <summary> Command contained invalid parameter. </summary>
	const int WCL_E_BLED112_INVALID_PARAM = WCL_E_BLED112_BASE + 0x0000;
	/// <summary> Device is in wrong state to receive command. </summary>
	const int WCL_E_BLED112_WRONG_STATE = WCL_E_BLED112_BASE + 0x0001;
	/// <summary> Device has run out of memory. </summary>
	const int WCL_E_BLED112_OUT_OF_MEMORY = WCL_E_BLED112_BASE + 0x0002;
	/// <summary> Feature is not implemented. </summary>
	const int WCL_E_BLED112_NOT_IMPLEMENTED = WCL_E_BLED112_BASE + 0x0003;
	/// <summary> Command was not recognized. </summary>
	const int WCL_E_BLED112_INVALID_COMMAND = WCL_E_BLED112_BASE + 0x0004;
	/// <summary> Command or Procedure failed due to timeout. </summary>
	const int WCL_E_BLED112_TIMEOUT = WCL_E_BLED112_BASE + 0x0005;
	/// <summary> Connection handle passed is to command is not a valid
	///   handle. </summary>
	const int WCL_E_BLED112_NOT_CONNECTED = WCL_E_BLED112_BASE + 0x0006;
	/// <summary> Command would cause either underflow or overflow 
	///   error. </summary>
	const int WCL_E_BLED112_FLOW = WCL_E_BLED112_BASE + 0x0007;
	/// <summary> User attribute was accessed through API which is not
	///   supported. </summary>
	const int WCL_E_BLED112_USER_ATTRIBUTE = WCL_E_BLED112_BASE + 0x0008;
	/// <summary> No valid license key found. </summary>
	const int WCL_E_BLED112_INVALID_LICENSE_KEY = WCL_E_BLED112_BASE + 0x0009;
	/// <summary> Command maximum length exceeded. </summary>
	const int WCL_E_BLED112_COMMAND_TOO_LONG = WCL_E_BLED112_BASE + 0x000A;
	/// <summary> Bonding procedure can not be started because device has no space
	///   left for bond. </summary>
	const int WCL_E_BLED112_OUT_OF_BONDS = WCL_E_BLED112_BASE + 0x000B;
	/// <summary> Module was reset due to script stack overflow. </summary>
	const int WCL_E_BLED112_SCRIPT_OVERFLOW = WCL_E_BLED112_BASE + 0x000C;
	/// <summary> Controller is at limit of connections it can support. </summary>
	const int WCL_E_BLED112_TOO_MANY_CONNECTIONS = WCL_E_BLED112_BASE + 0x000D;
	/// <summary> Operation was rejected because the controller is busy and unable
	///   to process the request. </summary>
	const int WCL_E_BLED112_BUSY = WCL_E_BLED112_BASE + 0x000E;
	/// <summary> A command can not be executed because other command is still
	///   running. </summary>
	const int WCL_E_BLED112_COMMAND_IN_POROGRESS = WCL_E_BLED112_BASE + 0x000F;
	/// <summary> Set handflow failed. </summary>
	const int WCL_E_BLED112_SET_HANDFLOW_FAILED = WCL_E_BLED112_BASE + 0x0010;
	/// <summary> Invalid response data size. </summary>
	const int WCL_E_BLED112_INVALID_RESPONSE_SIZE = WCL_E_BLED112_BASE + 0x0011;
	/// <summary> Unable to set input and output queue size. </summary>
	const int WCL_E_BLED112_SET_QUEUE_SIZE_FAILED = WCL_E_BLED112_BASE + 0x0012;
	/// <summary> Unable to set communication timeouts. </summary>
	const int WCL_E_BLED112_SET_TIMEOUTS_FAILED = WCL_E_BLED112_BASE + 0x0013;
	/// <summary> Unable to set required baud rate. </summary>
	const int WCL_E_BLED112_SET_BAUD_RATE_FAILED = WCL_E_BLED112_BASE + 0x0014;
	/// <summary> Set DTR control failed. </summary>
	const int WCL_E_BLED112_SET_DTR_FAILED = WCL_E_BLED112_BASE + 0x0015;
	/// <summary> Set line control failed. </summary>
	const int WCL_E_BLED112_SET_LINE_CONTROL_FAILED = WCL_E_BLED112_BASE + 0x0016;
	/// <summary> Set the special characters failed. </summary>
	const int WCL_E_BLED112_SET_CHARS_FAILED = WCL_E_BLED112_BASE + 0x0017;
	/// <summary> BLED112 does not support pairing. The pairing done during
	///   connection procedure. </summary>
	const int WCL_E_BLED112_PAIR_DURING_CONNECT = WCL_E_BLED112_BASE + 0x0018;

	/* Bluetooth LE sniffer error codes. */

	/// <summary> The base error code for BLE sniffer errors. </summary>
	const int WCL_E_BLE_SNIFFER_BASE = WCL_E_BLUETOOTH_BASE + 0x4000;
	/// <summary> The BLE sniffer is already active. </summary>
	const int WCL_E_BLE_SNIFFER_ACTIVE = WCL_E_BLE_SNIFFER_BASE + 0x0000;
	/// <summary> The BLE sniffer is not active. </summary>
	const int WCL_E_BLE_SNIFFER_NOT_ACTIVE = WCL_E_BLE_SNIFFER_BASE + 0x0001;
	/// <summary> Unable to create the thread initialization event. </summary>
	const int WCL_E_BLE_SNIFFER_CREATE_INIT_EVENT_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0002;
	/// <summary> Unable to create the thread termination event. </summary>
	const int WCL_E_BLE_SNIFFER_CREATE_TERM_EVENT_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0003;
	/// <summary> Unable to start BLE sniffer working thread. </summary>
	const int WCL_E_BLE_SNIFFER_START_THREAD_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0004;
	/// <summary> The CC2540 device was not found. </summary>
	const int WCL_E_BLE_SNIFFER_CC2540_DEVICE_NOT_FOUND = WCL_E_BLE_SNIFFER_BASE + 0x0005;
	/// <summary> Unable to read BLE sniffer device ident. </summary>
	const int WCL_E_BLE_SNIFFER_GET_IDENT_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0006;
	/// <summary> Set BLE sniffer device power failed. </summary>
	const int WCL_E_BLE_SNIFFER_SET_POWER_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0007;
	/// <summary> Get BLE sniffer device power failed. </summary>
	const int WCL_E_BLE_SNIFFER_GET_POWER_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0008;
	/// <summary> Set capturing channel failed. </summary>
	const int WCL_E_BLE_SNIFFER_SET_CHANNEL_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x0009;
	/// <summary> Unable to start packet capturing. </summary>
	const int WCL_E_BLE_SNIFFER_START_CAPTURE_FAILED = WCL_E_BLE_SNIFFER_BASE + 0x000A;

	/* Bluetooth exceptions. */

	/// <summary> The base exception class for all Bluetooth exceptions. </summary>
	/// <seealso cref="wclCommon::wclException" />
	class wclEBluetooth : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetooth(const char* msg) : wclException(msg) { };
	};

	/// <summary> The Bluetooth Manager exceptions. </summary>
	/// <seealso cref="wclEBluetooth" />
	class wclEBluetoothManager : public wclEBluetooth
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetoothManager(const char* msg) : wclEBluetooth(msg) { };
	};

	/// <summary> The Bluetooth clients exceptions. </summary>
	/// <seealso cref="wclEBluetooth" />
	class wclEBluetoothClient : public wclEBluetooth
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetoothClient(const char* msg) : wclEBluetooth(msg) { };
	};

	/// <summary> The Bluetooth server exceptions. </summary>
	/// <seealso cref="wclEBluetooth" />
	class wclEBluetoothServer : public wclEBluetooth
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetoothServer(const char* msg) : wclEBluetooth(msg) { };
	};

	/// <summary> The Bluetooth GATT client exceptions. </summary>
	/// <seealso cref="wclEBluetoothClient" />
	class wclEGattClient : public wclEBluetoothClient
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEGattClient(const char* msg) : wclEBluetoothClient(msg) { };
	};

	/// <summary> The Bluetooth GATT server exceptions. </summary>
	/// <seealso cref="wclEBluetoothServer" />
	class wclEGattServer : public wclEBluetoothServer
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEGattServer(const char* msg) : wclEBluetoothServer(msg) { };
	};

	/// <summary> The Bluetooth LE beacon exceptions. </summary>
	/// <seealso cref="wclEBluetooth" />
	class wclEBluetoothLeBeacon : public wclEBluetooth
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetoothLeBeacon(const char* msg) : wclEBluetooth(msg) { };
	};

	/// <summary> The Bluetooth LE Sniffer exceptions. </summary>
	/// <seealso cref="wclEBluetooth" />
	class wclEBluetoothLeSniffer : public wclEBluetooth
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEBluetoothLeSniffer(const char* msg) : wclEBluetooth(msg) { };
	};
}