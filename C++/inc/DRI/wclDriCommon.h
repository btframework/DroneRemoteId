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

#include "..\Common\wclHelpers.h"

namespace wclDri
{
	/// <summary> The enumeration defines supported Drone Remote ID
	///   vendors. </summary>
	typedef enum
	{
		/// <summary> ASD-STAN. </summary>
		driAsd
	} wclDriVendor;

	/// <summary> The Drone Remote ID message raw data. </summary>
	typedef std::vector<unsigned char> wclDriRawData;

	/// <summary> The base class for Drone Remote ID messages. </summary>
	class CwclDriMessage
	{
		DISABLE_COPY(CwclDriMessage);
		
	private:
		wclDriRawData	FData;
		wclDriVendor	FVendor;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <param name="Vendor"> The DRI system vendor ID. </param>
		/// <seealso cref="wclDriRawData" />
		/// <seealso cref="wclDriVendor" />
		CwclDriMessage(const wclDriRawData& Data, const wclDriVendor Vendor);
		/// <summary> Frees the object. </summary>
		virtual ~CwclDriMessage();
		
		/// <summary> Gets the message raw data. </summary>
		/// <returns> The raw bytes array. </returns>
		/// <seealso cref="wclDriRawData" />
		wclDriRawData GetData() const;
		/// <summary> Gets the message raw data. </summary>
		/// <value> The raw bytes array. </value>
		/// <seealso cref="wclDriRawData" />
		__declspec(property(get = GetData)) wclDriRawData Data;

		/// <summary> Gets the vendor ID. </summary>
		/// <returns> The vendor ID. </returns>
		/// <seealso cref="wclDriVendor" />
		wclDriVendor GetVendor() const;
		/// <summary> Gets the vendor ID. </summary>
		/// <value> The vendor ID. </value>
		/// <seealso cref="wclDriVendor" />
		__declspec(property(get = GetVendor)) wclDriVendor Vendor;
	};
	/// <summary> The <see cref="CwclDriMessage" /> messages array. </summary>
	/// <seealso cref="CwclDriMessage" />
	typedef std::vector<CwclDriMessage*> wclDriMessages;
}