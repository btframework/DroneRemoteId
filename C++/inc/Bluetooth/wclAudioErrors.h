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

#include "wclBluetoothErrors.h"

namespace wclAudio
{
	/* Common audio error codes. */

	/// <summary> The base error code for audio errors. </summary>
	const int WCL_E_AUDIO_BASE = 0x00080000;

	/// <summary> COM initialization failed. </summary>
	const int WCL_E_AUDIO_COM_INIT_FAILED = WCL_E_AUDIO_BASE + 0x0000;
	/// <summary> Create device enumerator failed. </summary>
	const int WCL_E_AUDIO_CREATE_ENUMERATOR_FAILED = WCL_E_AUDIO_BASE + 0x0001;
	/// <summary> Audio features is not supported on this platform. </summary>
	const int WCL_E_AUDIO_FEATURE_NOT_SUPPORTED = WCL_E_AUDIO_BASE + 0x0002;
	/// <summary> The Audio component is already closed. </summary>
	const int WCL_E_AUDIO_CLOSED = WCL_E_AUDIO_BASE + 0x0003;
	/// <summary> The Audio component is already opened. </summary>
	const int WCL_E_AUDIO_OPENED = WCL_E_AUDIO_BASE + 0x0004;
	/// <summary> Unable to register audio device changes event handler. </summary>
	const int WCL_E_AUDIO_REGISTER_EVENT_FAILED = WCL_E_AUDIO_BASE + 0x0005;
	/// <summary> The specified audio endpoint not found. </summary>
	const int WCL_E_AUDIO_ENDPOINT_NOT_FOUND = WCL_E_AUDIO_BASE + 0x0006;
	/// <summary> Unable to get audio endpoint channels number. </summary>
	const int WCL_E_AUDIO_GET_CHANNELS_COUNT_FAILED = WCL_E_AUDIO_BASE + 0x0007;
	/// <summary> Unable to get hardware supported features of the specified
	///   audio endpoint. </summary>
	const int WCL_E_AUDIO_GET_HARDWARE_FEATURES_FAILED = WCL_E_AUDIO_BASE + 0x0008;

	/* Audio switcher error codes. */

	/// <summary> The base error code for audio switcher errors. </summary>
	const int WCL_E_AUDIO_SWITCHER_BASE = WCL_E_AUDIO_BASE + 0x1000;
	/// <summary> The Audio Switcher is not opened. </summary>
	const int WCL_E_AUDIO_SWITCHER_NOT_OPENED = WCL_E_AUDIO_SWITCHER_BASE + 0x0000;
	/// <summary> Unable to enumerate audio endpoints. </summary>
	const int WCL_E_AUDIO_SWITCHER_ENUM_ENDPOINTS_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x0001;
	/// <summary> Get audio endpoints count failed. </summary>
	const int WCL_E_AUDIO_SWITCHER_GET_ENDPOIN_COUNT_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x0002;
	/// <summary> Create Audio configurator failed. </summary>
	const int WCL_E_AUDIO_SWITCHER_CREATE_CONFIGURATOR_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x0003;
	/// <summary> Unable to change default Audio Device. </summary>
	const int WCL_E_AUDIO_SWITCHER_SET_DEFAULT_DEVICE_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x0004;
	/// <summary> The specified device not found. </summary>
	const int WCL_E_AUDIO_SWITCHER_DEVICE_NOT_FOUND = WCL_E_AUDIO_SWITCHER_BASE + 0x0005;
	/// <summary> Invalid device selected. Connect and Disconnect features are
	///   supported for Bluetooth Audio Devices only. </summary>
	const int WCL_E_AUDIO_SWITCHER_INVALID_DEVICE = WCL_E_AUDIO_SWITCHER_BASE + 0x0006;
	/// <summary> The device is already connected. </summary>
	const int WCL_E_AUDIO_SWITCHER_DEVICE_CONNECTED = WCL_E_AUDIO_SWITCHER_BASE + 0x0007;
	/// <summary> The device is disconnected. </summary>
	const int WCL_E_AUDIO_SWITCHER_DEVICE_DISCONNECTED = WCL_E_AUDIO_SWITCHER_BASE + 0x0008;
	/// <summary> Unable to create device topology object. </summary>
	const int WCL_E_AUDIO_SWITCHER_CREATE_TOPOLOGY_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x0009;
	/// <summary> Unable to get device topology connectors number. </summary>
	const int WCL_E_AUDIO_SWITCHER_GET_CONNECTORS_COUNT_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x000A;
	/// <summary> Unable to connect to device. </summary>
	const int WCL_E_AUDIO_SWITCHER_CONNECT_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x000B;
	/// <summary> Unable to disconnect from device. </summary>
	const int WCL_E_AUDIO_SWITCHER_DISCONNECT_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x000C;
	/// <summary> No device connectors found. </summary>
	const int WCL_E_AUDIO_SWITCHER_NO_CONNECTORS_FOUND = WCL_E_AUDIO_SWITCHER_BASE + 0x000D;
	/// <summary> Unable to get default Audio Device. </summary>
	const int WCL_E_AUDIO_SWITCHER_GET_DEFAULT_DEVICE_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x000E;
	/// <summary> Get Audio Device ID failed. </summary>
	const int WCL_E_AUDIO_SWITCHER_GET_DEVICE_ID_FAILED = WCL_E_AUDIO_SWITCHER_BASE + 0x000F;
	/// <summary> Default audio device not found. </summary>
	const int WCL_E_AUDIO_SWITCHER_DEFAULT_DEVICE_NOT_FOUND = WCL_E_AUDIO_SWITCHER_BASE + 0x0010;

	/* Audio meter error codes. */

	/// <summary> The base error code for audio meter errors. </summary>
	const int WCL_E_AUDIO_METER_BASE = WCL_E_AUDIO_BASE + 0x2000;
	/// <summary> Unable to get audio stream peak value. </summary>
	const int WCL_E_AUDIO_METER_GET_PEAK_VALUE_FAILED = WCL_E_AUDIO_METER_BASE + 0x0000;
	/// <summary> Unable to create Audio meter instance. </summary>
	const int WCL_E_AUDIO_METER_CREATE_FAILED = WCL_E_AUDIO_METER_BASE + 0x0001;

	/* Audio volume error codes. */

	/// <summary> The base error code for audio volume errors. </summary>
	const int WCL_E_AUDIO_VOLUME_BASE = WCL_E_AUDIO_BASE + 0x3000;
	/// <summary> Unable to create Audio volume instance. </summary>
	const int WCL_E_AUDIO_VOLUME_CREATE_FAILED = WCL_E_AUDIO_VOLUME_BASE + 0x0000;
	/// <summary> Unable to get audio volume level. </summary>
	const int WCL_E_AUDIO_VOLUME_GET_VOLUME_FAILED = WCL_E_AUDIO_VOLUME_BASE + 0x0001;
	/// <summary> Unable to set audio volume level. </summary>
	const int WCL_E_AUDIO_VOLUME_SET_VOLUME_FAILED = WCL_E_AUDIO_VOLUME_BASE + 0x0002;
	/// <summary> Unable to get audio endpoint mute status. </summary>
	const int WCL_E_AUDIO_VOLUME_GET_MUTE_FAILED = WCL_E_AUDIO_VOLUME_BASE + 0x0003;
	/// <summary> Unable to set audio endpoint mute status. </summary>
	const int WCL_E_AUDIO_VOLUME_SET_MUTE_FAILED = WCL_E_AUDIO_VOLUME_BASE + 0x0004;

	/* Bluetooth Audio error codes. */
	
	/// <summary> The base error code for Bluetooth Audio errors. </summary>
	const int WCL_E_BT_AUDIO_BASE = WCL_E_AUDIO_BASE + 0x4000;
	/// <summary> This Bluetooth audio feature is not supported on this
	///   platform. </summary>
	const int WCL_E_BT_AUDIO_FEATURE_NOT_SUPPORTED = WCL_E_BT_AUDIO_BASE + 0x0000;
	
	/* Bluetooth Audio Device Watcher error codes. */

	/// <summary> The base error code for Bluetooth Audio Watcher
	///   errors. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_BASE = WCL_E_BT_AUDIO_BASE + 0x0100;
	/// <summary> Bluetooth Audio Watcher already started. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_STARTED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0000;
	/// <summary> Bluetooth Audio Watcher already stopped. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_STOPPED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0001;
	/// <summary> Unable to create Bluetooth Audio Watcher initialization
	///   event. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_CREATE_INIT_EVENT_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0002;
	/// <summary> Create Bluetooth Audio Watcher termination event
	///   failed. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_CREATE_TERM_EVENT_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0003;
	/// <summary> Unable to start Bluetooth Audio Watcher working
	///   thread. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_START_THREAD_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0004;
	/// <summary> Unable to get Bluetooth Audio Device selector. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_GET_SELECTOR_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0005;
	/// <summary> Create device watcher failed. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_CREATE_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0006;
	/// <summary> Set Device Added event handler failed. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_SET_ADDED_EVENT_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0007;
	/// <summary> Set Device Removed event handler failed. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_SET_REMOVED_EVENT_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0008;
	/// <summary> Unable to start Bluetooth Audio device watcher. </summary>
	const int WCL_E_BT_AUDIO_WATCHER_START_FAILED = WCL_E_BT_AUDIO_WATCHER_BASE + 0x0009;
	
	/* Bluetooth Audio Receiver error codes. */

	/// <summary> The base error code for Bluetooth Audio Receiver
	///   errors. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_BASE = WCL_E_BT_AUDIO_BASE + 0x0200;
	/// <summary> The audio receiver is closed. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_CLOSED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0000;
	/// <summary> The audio receiver is opened closed. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_OPENED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0001;
	/// <summary> Unable to create Bluetooth Audio Receiver initialization
	///   event. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_CREATE_INIT_EVENT_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0002;
	/// <summary> Create Bluetooth Audio Receiver termination event
	///   failed. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_CREATE_TERM_EVENT_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0003;
	/// <summary> Unable to start Bluetooth Audio Receiver working
	///   thread. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_START_THREAD_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0004;
	/// <summary> Unable to create Audio Connection Listener for the specified
	///   Bluetooth Audio device. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_CREATE_CONNECTION_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0005;
	/// <summary> Unable to add Audio Connect Listener event handler. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_SET_EVENT_HANDLER_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0006;
	/// <summary> Enable incoming Bluetooth Audio connection failed. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_ENABLE_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0007;
	/// <summary> A Bluetooth audio device is already connected. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_DEVICE_CONNECTED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0008;
	/// <summary> Start Bluetooth Audio connection failed. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_START_CONNECT_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x0009;
	/// <summary> Start Bluetooth Audio connection timedout. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_START_TIMEOUT = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x000A;
	/// <summary> Start Bluetooth Audio connection denied by system. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_START_DENIED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x000B;
	/// <summary> Unknow error occured during starting Bluetooth Audio
	///   connection. </summary>
	const int WCL_E_BT_AUDIO_RECEIVER_START_UNKNOWN_FAILED = WCL_E_BT_AUDIO_RECEIVER_BASE + 0x000C;

	/// <summary> The base exception class for all Audio exceptions. </summary>
	/// <seealso cref="wclCommon::wclException" />
	class wclEAudio : public wclException
	{
	public:
		/// <summary> Creates new exception object. </summary>
		/// <param name="msg"> The exception message. </param>
		wclEAudio(const char* msg) : wclException(msg) { };
	};
}