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
	/// <summary> The enumeration defines the system power states. </summary>
	typedef enum
	{
		/// <summary>  Indicates that the system is resuming from sleep or
		///   hibernation. This state is delivered every time the system resumes and
		///   does not indicate whether a user is present. </summary>
		psResumeAutomatic,
		/// <summary> Indicates that the system is resuming from a low-power state.
		///   This state appears after <c>psResumeAutomatic</c> if the resume is
		///   triggered by user input, such as pressing a key. </summary>
		psResume,
		/// <summary> Indicates that the computer is about to enter a suspended
		///   state. </summary>
		psSuspend,
		/// <summary> Unknown power state. </summary>
		psUnknown
	} wclPowerState;

	/// <summary> The <c>OnPowerStateChanged</c> event handler
	///   prototype </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="State"> The new power state. </param>
	/// <seealso cref="wclPowerState" />
	#define wclPowerStateChangedEvent(_event_name_) \
		__event void _event_name_(void* Sender, const wclPowerState State)

	/// <summary> The class allows an application to receive power state changes
	///   notifications. </summary>
	class CwclPowerEventsMonitor
	{
		DISABLE_COPY(CwclPowerEventsMonitor);
		
	private:
		CwclMessageReceiver* FReceiver;
		
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
		
		/// <summary> Fires the <c>OnChanged</c> event. </summary>
		/// <param name="State"> The new power state. </param>
		/// <seealso cref="wclPowerState" />
		virtual void DoPowerStateChanged(const wclPowerState State);
		
	public:
		/// <summary> Creates new object of the <c>TwclPowerEventsMonitor</c>
		///   class. </summary>
		CwclPowerEventsMonitor();
		/// <summary> Free the object. </summary>
		virtual ~CwclPowerEventsMonitor();
		
		/// <summary> Stops listening for the power events and releases all
		///   resources. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the power state changes monitor and starts listening for
		///   events. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Open();
		
		/// <summary> Gets the monitor's state. </summary>
		/// <returns> <c>true</c> if the power state monitor is listening for power
		///   state changes. <c>false</c> otherwise. </returns>
		bool GetActive() const;
		/// <summary> Gets the monitor's state. </summary>
		/// <value> <c>true</c> if the power state monitor is listening for power
		///   state changes. <c>false</c> otherwise. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> The event fires when the system's power state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="State"> The new power state. </param>
		/// <seealso cref="wclPowerState" />
		wclPowerStateChangedEvent(OnPowerStateChanged);
	};
}