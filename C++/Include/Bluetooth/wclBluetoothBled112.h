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

#include <list>

namespace wclBluetooth
{
	/* BLED112 control functions declarations. */
		
	/// <summary> Enumerates BLEd112 devices. </summary>
	/// <returns> The list of BLEd112 COM ports. </returns>
	/// <remarks> An application must never call this function. Instead it must use
	///   high-level Bluetooth functions and classes. This function is for
	///   internal use only. </remarks>
	std::list<tstring>* wclBled112EnumDevices();

	/// <summary> Gets the BLED112 device COM port name. </summary>
	/// <param name="Instance"> The device instance string. </param>
	/// <param name="Port"> If the function completed with success on output
	///    contains the BLED112 device COM port name. </param>
	/// <returns> Returns <c>True</c> if the device represented with the
	///   <c>Instance</c> parameter is a BLED112 device. </returns>
	bool wclBled112GetPort(const tstring& Instance, tstring& Port);

	/// <summary> Creates a BLED112 Bluetooth Radio object. </summary>
	/// <param name="Manager"> The <see cref="CwclBluetoothManager" /> object that
	///   owns the Radio. </param>
	/// <param name="Port"> The BLED112 COM port name. </param>
	/// <returns> The function returns a Radio object that represents the BLED112
	///   Bluetooth driver. </returns>
	/// <remarks> An application must never call this function. Instead it must use
	///   high-level Bluetooth functions and classes. This function is for
	///   internal use only. </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclBluetoothManager" />
	CwclBluetoothRadio* wclLoadBled112(CwclBluetoothManager* const Manager, const tstring& Port);
}