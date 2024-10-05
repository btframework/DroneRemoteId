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

#include <set>

#include "wclErrors.h"
#include "wclHelpers.h"
#include "wclMessaging.h"

namespace wclCommon
{
	/// <summary> The enumeration defines the system power states. </summary>
	typedef enum
	{
		/// <summary> The power status of the computer has been changed. </summary>
		psPowerStatusChanged,
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

	/// <summary> The AC power status. </summary>
	typedef enum
	{
		/// <summary> Offline. </summary>
		lsOffline,
		/// <summary> Online. </summary>
		lsOnline,
		/// <summary> Backupo power. </summary>
		lsBackup,
		/// <summary> Unknown status. </summary>
		lsUnknown
	} wclACLineStatus;

	/// <summary> The battery charge statuses. </summary>
	typedef enum
	{
		/// <summary> High—the battery capacity is at more than 66
		///   percent. </summary>
		csCapacityHigh,
		/// <summary> Low—the battery capacity is at less than 33
		///   percent. </summary>
		csCapacityLow,
		/// <summary> Critical—the battery capacity is at less than five
		///   percent. </summary>
		csCapacityCritical,
		/// <summary> Charging. </summary>
		csCharging,
		/// <summary> No system battery. </summary>
		csNoSystemBattery,
		/// <summary> Unknown status—unable to read the battery flag
		///   information. </summary>
		csUnknown
	} wclBatteryChargeStatus;
	/// <summary> The battery charge status. </summary>
	/// <seealso cref="wclBatteryChargeStatus" />
	typedef std::set<wclBatteryChargeStatus> wclBatteryChargeStatusFlags;

	/// <summary> Contains information about the power status of the
	///   system. </summary>
	typedef struct
	{
		/// <summary> The AC power status. </summary>
		/// <seealso cref="wclACLineStatus" />
		wclACLineStatus ACLineStatus;
		/// <summary> The battery charge status. The set is empty if the battery is
		///   not being charged and the battery capacity is between low and
		///   high. </summary>
		/// <seealso cref="wclBatteryChargeStatusFlags" />
		wclBatteryChargeStatusFlags BatteryChargeStatus;
		/// <summary> The percentage of full battery charge remaining. This member
		///   can be a value in the range 0 to 100, or 255 if status is
		///   unknown. </summary>
		unsigned char BatteryLifePercent;
		/// <summary> The status of battery saver. <c>False</c> if the battery saver
		///   is off. <c>True</c> if the battery saver on. Save energy where
		///   possible. </summary>
		bool BatterySavingState;
		/// <summary> The number of seconds of battery life remaining, or
		///   <c>0xFFFFFFFF</c> if remaining seconds are unknown or if the device is
		///   connected to AC power. </summary>
		unsigned long BatteryLifeTime;
		/// <summary> The number of seconds of battery life when at full charge, or
		///   <c>0xFFFFFFFF</c> if full battery lifetime is unknown or if the device
		///   is connected to AC power. </summary>
		unsigned long BatteryFullLifeTime;
	} wclPowerStatus;

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
		CwclMessageReceiver*	FReceiver;

		/* APM DLL. */
		
		HMODULE					FPowerDll;
		HANDLE					FPowerReg;

		/* Power events window. */
		
		HWND					FWnd;
		HANDLE					FWndThread;
		HANDLE					FWndThreadInitEvent;
		int						FWndThreadInitResult;

		/* APM support. */
		
		bool RegisterPowerChanges();
		void UnregisterPowerChanges();

		/* Power events window support. */
		
		int CreatePowerEventWindow();
		void DestroyPowerEventWindow();
		
		static LRESULT __stdcall _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool WndProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam);
		static UINT __stdcall _WndThread(LPVOID lpParam);
		void WndThread();
		
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

		/// <summary> Retrieves the power status of the system. The status indicates
		///   whether the system is running on AC or DC power, whether the battery
		///   is currently charging, how much battery life remains, and if battery
		///   saver is on or off. </summary>
		/// <param name="Status"> A <see cref="wclPowerStatus" /> structure that
		///   receives status information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclPowerStatus" />
		int GetPowerStatus(wclPowerStatus& Status);
		
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