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

#include <tchar.h>

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "wclAudioErrors.h"

/// <summary> This macro helps to build correct documentation. </summary>
#define _WCL_AUDIO_API_INCLUDE_FILE_ "wclAudioApi.h"
#include _WCL_AUDIO_API_INCLUDE_FILE_

using namespace wclCommon;

namespace wclAudio
{
	/// <summary> The audio device data flow direction. </summary>
	/// <remarks> The Data Flow indicates the direction in which audio data flows
	///   between an audio endpoint device and an application. </remarks>
	typedef enum
	{
		/// <summary> Audio rendering stream. Audio data flows from the application
		///   to the audio endpoint device, which renders the stream. </summary>
		dfRender,
		/// <summary> Audio capture stream. Audio data flows from the audio endpoint
		///   device that captures the stream, to the application. </summary>
		dfCapture
	} wclAudioDeviceDataFlow;

	/// <summary> The audio device role. </summary>
	/// <remarks> indicate the role that the system has assigned to an audio
	///   endpoint device. </remarks>
	typedef enum
	{
		/// <summary> Games, system notification sounds, and voice
		///   commands. </summary>
		drConsole,
		/// <summary> Music, movies, narration, and live music
		///   recording. </summary>
		drMultimedia,
		/// <summary> Voice communications (talking to another person). </summary>
		drCommunications
	} wclAudioDeviceRole;
	/// <summary> The device roles set. </summary>
	/// <seealso cref="wclAudioDeviceRole" />
	typedef std::set<wclAudioDeviceRole> wclAudioDeviceRoles;

	/// <summary> Audio device state. </summary>
	typedef enum
	{
		/// <summary> Active device. </summary>
		asActive,
		/// <summary> Disabled device. </summary>
		asDisabled,
		/// <summary> Not present device. </summary>
		asNotPresent,
		/// <summary> Unplugged device. </summary>
		asUnplugged
	} wclAudioDeviceState;
	/// <summary> Set of audio device states. </summary>
	/// <seealso cref="wclAudioDeviceState" />
	typedef std::set<wclAudioDeviceState> wclAudioDeviceStates;

	/// <summary> The audio peak values array. </summary>
	typedef std::vector<float> wclAudioPeakValues;

	/// <summary> The hardware support features for an audio endpoint
	///   device. </summary>
	typedef enum
	{
		/// <summary> The audio endpoint device supports a hardware volume
		///   control. </summary>
		hfVolume,
		/// <summary> The audio endpoint device supports a hardware mute
		///   control. </summary>
		hfMute,
		/// <summary> The audio endpoint device supports a hardware peak
		///   meter. </summary>
		hfMeter
	} wclAudioHardwareFeature;
	/// <summary> The hardware support flags for an audio endpoint
	///   device. </summary>
	/// <seealso cref="wclAudioHardwareFeature" />
	typedef std::set<wclAudioHardwareFeature> wclAudioHardwareFeatures;

	/// <summary> Contains information about audio device. </summary>
	typedef struct
	{
		/// <summary> Device's ID. </summary>
		tstring Id;
		/// <summary> Device friendly name. </summary>
		tstring FriendlyName;
		/// <summary> Device description. </summary>
		tstring Description;
		/// <summary> The data flow. </summary>
		/// <seealso cref="wclAudioDeviceDataFlow" />
		wclAudioDeviceDataFlow Flow;
		/// <summary> The device default roles. </summary>
		/// <seealso cref="wclAudioDeviceRoles" />
		wclAudioDeviceRoles Roles;
		/// <summary> The device state. </summary>
		/// <seealso cref="wclAudioDeviceState" />
		wclAudioDeviceState State;
		/// <summary> <c>True</c> if the audio device is connected by
		///   Bluetooth. </summary>
		bool IsBluetooth;
		/// <summary> The device's MAC address if device is Bluetooth. Valid only if
		///   <c>IsBluetooth</c> is <c>True</c>.</summary>
		__int64 Mac;
		/// <summary> Bluetooth service UUID. Valid only if <c>IsBluetooth</c> is
		///   <c>True</c>. </summary>
		GUID Service;
	} wclAudioDevice;
	/// <summary> The array of audio devices. </summary>
	/// <seealso cref="wclAudioDevice" />
	typedef std::vector<wclAudioDevice> wclAudioDevices;

	/// <summary> A Bluetooth audio receiver state. </summary>
	typedef enum
	{
		/// <summary> A receiver is closed. </summary>
		arClosed,
		/// <summary> A receiver is opening. </summary>
		arOpening,
		/// <summary> A receiver is listening. </summary>
		arListen,
		/// <summary> A receiver is connecting to a remote audio device. </summary>
		arConnecting,
		/// <summary> A remote device is connected to a receiver. </summary>
		arConnected,
		/// <summary> A receiver is closing. </summary>
		arClosing
	} wclBluetoothAudioReceiverState;

	/// <summary> The Audio Switcher <c>OnDefaultDeviceChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> The device ID. </param>
	/// <param name="Flow"> The device data flow. </param>
	/// <param name="Role"> The device role. </param>
	/// <seealso cref="wclAudioDeviceDataFlow" />
	/// <seealso cref="wclAudioDeviceRole" />
	#define wclAudioDefaultDeviceChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const tstring& Id, const wclAudioDeviceDataFlow Flow, \
			const wclAudioDeviceRole Role)
	/// <summary> The Audio Switcher <c>OnDeviceAdded</c> and
	///   <c>OnDeviceRemoved</c> events handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> The device ID. </param>
	#define wclAudioDeviceEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const tstring& Id)
	/// <summary> The Audio Switcher <c>OnStateChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> The device ID. </param>
	/// <param name="State"> The new device state. </param>
	/// <seealso cref="wclAudioDeviceState" />
	#define wclAudioDeviceStateChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const tstring& Id, const wclAudioDeviceState State)
	/// <summary> The Audio Volume <c>OnChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Muted"> The mute state. </param>
	/// <param name="Volume"> The master volume. </param>
	/// <param name="Volumes"> The channel volumes. </param>
	#define wclAudioVolumeChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const bool Muted, const float Volume, \
			const wclAudioPeakValues& Volumes)

	/// <summary> The Bluetooth audio device watcher <c>OnDeviceAdded</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> An audio device ID. </param>
	/// <param name="Name"> An audio device name. </param>
	#define wclBluetoothAudioDeviceAddedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const tstring& Id, const tstring& Name)
	/// <summary> The Bluetooth audio device watcher <c>OnDeviceRemoved</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Id"> An audio device ID. </param>
	#define wclBluetoothAudioDeviceRemovedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const tstring& Id)

	/// <summary> The custom Audio component. </summary>
	/// <remarks> The class implements the basic Audio features for all Audio
	///   component. </remarks>
	class CwclCustomAudio
	{
		DISABLE_COPY(CwclCustomAudio);

	private:
		AudioApi::IMMDeviceEnumerator*		FEnumerator;
		AudioApi::IMMNotificationClient*	FEventHandler;
		wclMessageProcessingMethod			FMessageProcessing;
		CwclMessageReceiver*				FReceiver;

	protected:
		/// <summary> The method called during audio subsystem
		///   finalization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide extra
		///   finalization code. </remarks>
		virtual int InternalClose();
		/// <summary> The method called during audio subsystem
		///   initialization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide extra
		///   initialization code. </remarks>
		virtual int InternalOpen();

		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/// <summary> Calls the <c>OnClosed</c> event. </summary>
		virtual void DoClosed();
		/// <summary> Calls the <c>OnOpend</c> event. </summary>
		virtual void DoOpened();

		/// <summary> Opens the Audio component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int Open();
		
		/// <summary> Gets the Audio devices enumerator interface. </summary>
		/// <returns> The Audio device enumerator interface. </returns>
		AudioApi::IMMDeviceEnumerator* GetEnumerator() const;
		/// <summary> Gets the Audio devices enumerator interface. </summary>
		/// <value> The Audio device enumerator interface. </value>
		__declspec(property(get = GetEnumerator)) AudioApi::IMMDeviceEnumerator* Enumerator;
		
		/// <summary> Gets the message receiver. </summary>
		/// <returns> The message receiver object. </returns>
		/// <seealso cref="CwclMessageReceiver" />
		CwclMessageReceiver* GetReceiver() const;
		/// <summary> Gets the message receiver. </summary>
		/// <value> The message receiver object. </value>
		/// <seealso cref="CwclMessageReceiver" />
		__declspec(property(get = GetReceiver)) CwclMessageReceiver* Receiver;

	public:
		/// <summary> Creates new Audio component. </summary>
		CwclCustomAudio();
		/// <summary> Frees the component. </summary>
		virtual ~CwclCustomAudio();
		
		/// <summary> Closes the Audio component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int Close();
		
		/// <summary> Gets the Audio Switcher state. </summary>
		/// <returns> <c>True</c> if the Audio Switcher is active. <c>False</c>
		///   otherwsie. </returns>
		bool GetActive() const;
		/// <summary> Gets the Audio Switcher state. </summary>
		/// <value> <c>True</c> if the Audio Switcher is active. <c>False</c>
		///   otherwsie. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEAudio"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEAudio"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/// <summary> The event fires when the Audio Switcher was closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnClosed);
		/// <summary> The event fires when the Audio Switcher was opened. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnOpened);
	};

	/// <summary> The base component for Audio components that works with a single
	///  Audio endpoint. </summary>
	/// <seealso cref="CwclCustomAudio" />
	class CwclCustomAudioEndpoint : public CwclCustomAudio
	{
		DISABLE_COPY(CwclCustomAudioEndpoint);
		
	private:
		tstring	FId;
		
	protected:
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Fires the OnDisconnected event. </summary>
		virtual void DoDisconnected();
		
	public:
		/// <summary> Creates new custom audio endpoint component. </summary>
		CwclCustomAudioEndpoint();
		
		/// <summary> Closes the audio endpoint. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close() override;
		/// <summary> Opens the specified audio endpoint. </summary>
		/// <param name="Id"> The endpoint ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int Open(const tstring& Id);

		/// <summary> Gets the number of channels in the audio stream that are
		///   monitored by peak meters. </summary>
		/// <param name="Count"> The variable into which the method writes the
		///   number of channels. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   specific implementation. </remarks>
		virtual int GetChannels(unsigned long& Count) = 0;
		/// <summary> Queries the audio endpoint device for its hardware-supported
		///   functions. </summary>
		/// <param name="Features"> The variable into which the method writes a
		///   hardware support features that indicates the hardware capabilities of
		///   the audio endpoint device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   specific implementation. </remarks>
		/// <seealso cref="wclAudioHardwareFeatures" />
		virtual int GetHardwareFeatures(wclAudioHardwareFeatures& Features) = 0;

		/// <summary> Gets the endpoint ID. </summary>
		/// <returns> The endpoint ID string. </returns>
		tstring GetId() const;
		/// <summary> Gets the endpoint ID. </summary>
		/// <value> The endpoint ID string. </value>
		__declspec(property(get = GetId)) tstring Id;
		
		/// <summary> The even fires when the endpoint used by this class has been
		///   disconnected or removed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnDisconnected);
	};

	/// <summary> The class provides functional to select system default audio
	///   device. </summary>
	/// <seealso cref="CwclCustomAudio" />
	class CwclAudioSwitcher : public CwclCustomAudio
	{
		DISABLE_COPY(CwclAudioSwitcher);
		
	private:
		void GetBluetoothDetails(wclAudioDevice& Device);

		bool GetDeviceProps(AudioApi::IMMDevice* const MMDevice, wclAudioDevice& Device);
		wclAudioDeviceRoles GetRoles(const AudioApi::EDataFlow Flow, const tstring& Id);
		
		int EnumDevices(const wclAudioDeviceStates& States, wclAudioDevices& Devices);

		int CheckDeviceState(const tstring& Id, const bool Connect);
		int ChangeDeviceState(const tstring& Id, const bool Connect);

	protected:
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;

		/// <summary> Calls the <c>OnDefaultDeviceChanged</c> event. </summary>
		/// <param name="Id"> The device ID. </param>
		/// <param name="Flow"> The device data flow. </param>
		/// <param name="Role"> The device role. </param>
		/// <seealso cref="wclAudioDeviceDataFlow" />
		/// <seealso cref="wclAudioDeviceRole" />
		virtual void DoDefaultDeviceChanged(const tstring& Id, const wclAudioDeviceDataFlow Flow,
			const wclAudioDeviceRole Role);
		/// <summary> Calls the <c>OnDeviceAdded</c> event. </summary>
		/// <param name="Id"> The device ID. </param>
		virtual void DoDeviceAdded(const tstring& Id);
		/// <summary> Calls the <c>OnDeviceRemoved</c> event. </summary>
		/// <param name="Id"> The device ID. </param>
		virtual void DoDeviceRemoved(const tstring& Id);
		/// <summary> Calls the <c>OnStateChanged</c> event. </summary>
		/// <param name="Id"> The device ID. </param>
		/// <param name="State"> The new device state. </param>
		/// <seealso cref="wclAudioDeviceState" />
		virtual void DoStateChanged(const tstring& Id, const wclAudioDeviceState State);

	public:
		/// <summary> Creates new Audio Switcher component. </summary>
		CwclAudioSwitcher();

		/// <summary> Opens the Audio Switcher component. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int Open() override;
		
		/// <summary> Enumerates available audio devices. </summary>
		/// <param name="States"> The audio device states. </param>
		/// <param name="Devices"> If the method completed with success on output
		///   contains the list of found audio devices. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioDeviceStates" />
		/// <seealso cref="wclAudioDevices" />
		int Enum(const wclAudioDeviceStates& States, wclAudioDevices& Devices);

		/// <summary> Gets the specified Audio Device information. </summary>
		/// <param name="Id"> The Audio Device ID. </param>
		/// <param name="Device"> If the method completed with success on output
		///   contains information about specified Audio Device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioDevice" />
		int GetDeviceDetails(const tstring& Id, wclAudioDevice& Device);

		/// <summary> Gets the default Audio Device for the specified Role and
		///   Data Flow. </summary>
		/// <param name="Role"> The device role. </param>
		/// <param name="Flow"> The audio data flow. </param>
		/// <param name="Id"> If the method completed with success on output
		///   contains the default Audio Device ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioDeviceRole" />
		/// <seealso cref="wclAudioDeviceDataFlow" />
		int GetDefault(const wclAudioDeviceRole Role, const wclAudioDeviceDataFlow Flow,
			tstring& Id);
		/// <summary> Sets the specified Audio Device as default for the specified
		///   Role. </summary>
		/// <param name="Role"> The device role. </param>
		/// <param name="Id"> The device ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioDeviceRole" />
		int SetDefault(const wclAudioDeviceRole Role, const tstring& Id);
		
		/// <summary> Connects to the specified Audio Device. </summary>
		/// <param name="Id"> The device ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect(const tstring& Id);
		/// <summary> Connects to the specified Audio Device. </summary>
		/// <param name="Address"> The device Bluetooth MAC address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect(const __int64 Address);

		/// <summary> Disconnects from the specified Audio Device. </summary>
		/// <param name="Id"> The device ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect(const tstring& Id);
		/// <summary> Disconnects from the specified Audio Device. </summary>
		/// <param name="Address"> The device Bluetooth MAC address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect(const __int64 Address);

		/// <summary> The event fires when default audio device changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> The device ID. </param>
		/// <param name="Flow"> The device data flow. </param>
		/// <param name="Role"> The device role. </param>
		/// <seealso cref="wclAudioDeviceDataFlow" />
		/// <seealso cref="wclAudioDeviceRole" />
		wclAudioDefaultDeviceChangedEvent(OnDefaultDeviceChanged);
		/// <summary> The event fires when new audio device added. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> The device ID. </param>
		wclAudioDeviceEvent(OnDeviceAdded);
		/// <summary> The event fires when audio device removed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> The device ID. </param>
		wclAudioDeviceEvent(OnDeviceRemoved);
		/// <summary> The event fires when audio device state changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> The device ID. </param>
		/// <param name="State"> The new device state. </param>
		/// <seealso cref="wclAudioDeviceState" />
		wclAudioDeviceStateChangedEvent(OnStateChanged);
	};

	/// <summary> The Audio Meter component represents a peak meter on an audio
	///   stream to or from an audio endpoint device. </summary>
	/// <seealso cref="CwclCustomAudioEndpoint"/>
	class CwclAudioMeter : public CwclCustomAudioEndpoint
	{
		DISABLE_COPY(CwclAudioMeter);
		
	private:
		AudioApi::IAudioMeterInformation*	FMeter;
		
	protected:
		/// <summary> The method called during audio subsystem
		///   finalization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() override;
		/// <summary> The method called during audio subsystem
		///   initialization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() override;
		
	public:
		/// <summary> Creates new audio meter component. </summary>
		CwclAudioMeter();
		
		/// <summary> Gets the number of channels in the audio stream that are
		///   monitored by peak meters. </summary>
		/// <param name="Count"> The variable into which the method writes the
		///   number of channels. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int GetChannels(unsigned long& Count) override;
		/// <summary> Gets the peak sample value for the channels in the audio
		///   stream. </summary>
		/// <param name="Values"> The variable into which the method writes the peak
		///   sample value for the audio stream. The peak value is a number in the
		///   normalized range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioPeakValues" />
		int GetChannelsPeak(wclAudioPeakValues& Values);
		/// <summary> Queries the audio endpoint device for its hardware-supported
		///   functions. </summary>
		/// <param name="Features"> The variable into which the method writes a
		///   hardware support features that indicates the hardware capabilities of
		///   the audio endpoint device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioHardwareFeatures" />
		virtual int GetHardwareFeatures(wclAudioHardwareFeatures& Features) override;
		/// <summary> Gets the peak sample value in the audio stream. </summary>
		/// <param name="Value"> The variable into which the method writes the peak
		///   sample value for the audio stream. The peak value is a number in the
		///   normalized range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetPeak(float& Value);
	};

	/// <summary> The component provides methods to control volume control for
	///   an audio endpoints. </summary>
	/// <seealso cref="CwclCustomAudioEndpoint" />
	class CwclAudioVolume : public CwclCustomAudioEndpoint
	{
		DISABLE_COPY(CwclAudioVolume);
		
	private:
		GUID									FContext;
		AudioApi::IAudioEndpointVolume*			FVolume;
		AudioApi::IAudioEndpointVolumeCallback*	FVolumeCallback;
		
	protected:
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> The method called during audio subsystem
		///   finalization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalClose() override;
		/// <summary> The method called during audio subsystem
		///   initialization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int InternalOpen() override;
		
		/// <summary> The method fires the <c>OnChanged</c> event. </summary>
		/// <param name="Muted"> The mute state. </param>
		/// <param name="Volume"> The master volume. </param>
		/// <param name="Volumes"> The channel volumes. </param>
		virtual void DoChanged(const bool Muted, const float Volume,
			const wclAudioPeakValues& Volumes);
		
	public:
		/// <summary> Creates new audio volume component. </summary>
		CwclAudioVolume();
		
		/// <summary> Gets the number of channels in the audio stream that are
		///   controlled by the volume control. </summary>
		/// <param name="Count"> The variable into which the method writes the
		///   number of channels. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int GetChannels(unsigned long& Count) override;
		/// <summary> Queries the audio endpoint device for its hardware-supported
		///   functions. </summary>
		/// <param name="Features"> The variable into which the method writes a
		///   hardware support features that indicates the hardware capabilities of
		///   the audio endpoint device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclAudioHardwareFeatures" />
		virtual int GetHardwareFeatures(wclAudioHardwareFeatures& Features) override;
		
		/// <summary> Gets the channel volume level of the audio stream that enters
		///   or leaves the audio endpoint device. The volume level is expressed as
		///   a normalized, audio-tapered value in the range from 0.0
		///   to 1.0. </summary>
		/// <param name="Channel"> The audio endpoint channel number. The value
		///   must be in range between 0 and <c>Channels - 1</c>. </param>
		/// <param name="Volume"> The variable into which the method writes the
		///   volume level. The level is expressed as a normalized value in the
		///   range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetChannelVolume(const unsigned long Channel, float& Volume);
		/// <summary> Gets the audio endpoint mute. </summary>
		/// <param name="Mute"> If the method completed with success on output
		///   contains the mute state of the audio endpoint. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetMute(bool& Mute);
		/// <summary> Gets the master volume level of the audio stream that enters
		///   or leaves the audio endpoint device. The volume level is expressed as
		///   a normalized, audio-tapered value in the range from 0.0
		///   to 1.0. </summary>
		/// <param name="Volume"> The variable into which the method writes the
		///   volume level. The level is expressed as a normalized value in the
		///   range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetVolume(float& Volume);
		
		/// <summary> Sets the channel volume level of the audio stream that enters
		///   or leaves the audio endpoint device. The volume level is expressed as
		///   a normalized, audio-tapered value in the range from 0.0
		///   to 1.0. </summary>
		/// <param name="Channel"> The audio endpoint channel number. The value
		///   must be in range between 0 and <c>Channels - 1</c>. </param>
		/// <param name="Value"> The volume level. The level is expressed as a
		///   normalized value in the range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetChannelVolume(const unsigned long Channel, const float Value);
		/// <summary> Sets the audio endpoint mute. </summary>
		/// <param name="Mute"> The mute state of the audio endpoint. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetMute(const bool Mute);
		/// <summary> Sets the master volume level of the audio stream that enters
		///   or leaves the audio endpoint device. The volume level is expressed as
		///   a normalized, audio-tapered value in the range from 0.0
		///   to 1.0. </summary>
		/// <param name="Value"> The volume level. The level is expressed as a
		///   normalized value in the range from 0.0 to 1.0. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetVolume(const float Value);

		/// <summary> The event fires when the volumes of the specified audio
		///   endpoint changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Muted"> The mute state. </param>
		/// <param name="Volume"> The master volume. </param>
		/// <param name="Volumes"> The channel volumes. </param>
		wclAudioVolumeChangedEvent(OnChanged);
	};

	/// <summary> The Bluetooth Audio device watcher class. </summary>
	/// <remarks> <para> The class helps to find Audio devices that can accept
	///   incoming audio stream from extract Bluetooth devices. </para>
	///   <para> <c>The class is not thread-safe.</c> </para> </remarks>
	class CwclBluetoothAudioWatcher
	{
		DISABLE_COPY(CwclBluetoothAudioWatcher);

	private:
		wclMessageProcessingMethod	FMessageProcessing;
		CwclMessageReceiver*		FReceiver;
		
		HANDLE						FInitEvent;
		int							FInitResult;
		HANDLE						FTermEvent;
		HANDLE						FThread;
		
		static UINT __stdcall _ThreadProc(LPVOID Param);
		void ThreadProc();
		
	protected:
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="TwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/// <summary> Calls the <c>OnDeviceAdded</c> event. </summary>
		/// <param name="Id"> A device's ID. </param>
		/// <param name="Name"> A device's name. </param>
		virtual void DoDeviceAdded(const tstring& Id, const tstring& Name);
		/// <summary> Calls the <c>OnDeviceRemoved</c> event. </summary>
		/// <param name="Id"> A device's ID. </param>
		virtual void DoDeviceRemoved(const tstring& Id);
		/// <summary> Calls the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Calls the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		
	public:
		/// <summary> Creates new class. </summary>
		CwclBluetoothAudioWatcher();
		/// <summary> Frees the class. </summary>
		virtual ~CwclBluetoothAudioWatcher();
		
		/// <summary> Starts the Bluetooth audio watcher. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start();
		/// <summary> Stops the Bluetooth audio watcher. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Gets the Bluetooth audio watcher state. </summary>
		/// <value> <c>True</c> if the watcher is active. <c>False</c>
		///   otherwise. </value>
		bool GetActive() const;
		__declspec(property(get = GetActive)) bool Active;
		
		/// <summary> Gets and sets a message processing method that should be used
		///   by the audio component. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEAudio"></exception>
		wclMessageProcessingMethod GetMessageProcessing() const;
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;
		
		/// <summary> The event called when new Bluetooth audio device added
		///   (found). </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> An audio device ID. </param>
		/// <param name="Name"> An audio device name. </param>
		wclBluetoothAudioDeviceAddedEvent(OnDeviceAdded);
		/// <summary> The event called when new Bluetooth audio device
		///   removed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Id"> An audio device ID. </param>
		wclBluetoothAudioDeviceRemovedEvent(OnDeviceRemoved);
		/// <summary> The event called when the Bluetooth audio watcher was
		///   started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event called when the Bluetooth audio watcher was
		///   stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> A Bluetooth audio Receiver. </summary>
	/// <remarks> <para> This class switches your PC to a Bluetooth speaker
	///   that can receiver an audio stream from remote Bluetooth device and play
	///   it through PC speaker. </para>
	///   <para> <c>The class is not thread-safe.</c> </para> </remarks>
	class CwclBluetoothAudioReceiver
	{
		DISABLE_COPY(CwclBluetoothAudioReceiver);
		
	private:
		tstring								FId;
		wclMessageProcessingMethod			FMessageProcessing;
		CwclMessageReceiver*				FReceiver;
		wclBluetoothAudioReceiverState		FState;
		
		AudioApi::IAudioPlaybackConnection*	FConnection;
		WinApi::EventRegistrationToken		FToken;
		
		HANDLE								FInitEvent;
		int									FInitResult;
		HANDLE								FTermEvent;
		HANDLE								FThread;
		
		int CreateConnection();
		int AddEventHandler();
		
		void RemoveEventHandler();
		void DestroyConnection();
		
		static UINT __stdcall _ThreadProc(LPVOID Param);
		void ThreadProc();
		
	protected:
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/// <summary> Calls the <c>OnClosed</c> event. </summary>
		virtual void DoClosed();
		/// <summary> Calls the <c>OnConnected</c> event. </summary>
		virtual void DoConnected();
		/// <summary> Calls the <c>OnDisconnected</c> event. </summary>
		virtual void DoDisconnected();
		/// <summary> Calls the <c>OnListen</c> event. </summary>
		virtual void DoListen();
		
	public:
		/// <summary> Creates new component. </summary>
		CwclBluetoothAudioReceiver();
		/// <summary> Frees the component. </summary>
		virtual ~CwclBluetoothAudioReceiver();
		
		/// <summary> Closes the Bluetooth audio receiver and stops listening for
		///   audio connections. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Initializes the Bluetooth audio receiver and starts listening
		///   for audio connections. </summary>
		/// <param name="Id"> A Bluetooth audio device ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Listen(const tstring& Id);
		
		/// <summary> Initiates a connection to an associated Bluetooth audio
		///   device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Connect();
		
		/// <summary> Gets the Bluetooth audio device ID associated with the
		///   receiver. </summary>
		/// <value> A Bluetooth audio device ID. </value>
		tstring GetId() const;
		__declspec(property(get = GetId)) tstring Id;
		
		/// <summary> Gets the Bluetooth audio receiver state. </summary>
		/// <value> A Bluetooth audio receiver state. </value>
		/// <seealso cref="wclBluetoothAudioReceiverState" />
		wclBluetoothAudioReceiverState GetState() const;
		__declspec(property(get = GetState)) wclBluetoothAudioReceiverState State;
		
		/// <summary> Gets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEAudio"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method that should be used
		///   by the Audio component. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEAudio"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;
		
		/// <summary> The event called when a Bluetooth audio receiver is
		///   closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnClosed);
		/// <summary> The event called when a remote Bluetooth audio device is
		///   connected to the receiver. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnConnected);
		/// <summary> The event called when a remote Bluetooth audio device is
		///   disconnected from the receiver. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnDisconnected);
		/// <summary> The event called when the receiver is started listeting for
		///   audio connections. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnListen);
	};
}