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

#include "..\\DRI\wclDroneRemoteId.h"
#include "wclWiFi.h"

using namespace wclDri;

namespace wclWiFi
{
	/// <summary> The class adds Drone Remote ID information element parsing
	///   methods. </summary>
	/// <seealso cref="CwclWiFiInformationElementParser" />
	class CwclWiFiDriParser : public CwclWiFiInformationElementParser
	{
		DISABLE_COPY(CwclWiFiDriParser);

	private:
		unsigned long GetOui(const wclWiFiInformationElement& Element) const;
		bool IsDriIe(const wclWiFiInformationElement& Element) const;
		
		wclDriRawData CopyData(const wclDriRawData& Data, const size_t Ndx,
			const size_t Len) const;
		wclDriRawData CopyData(const wclDriRawData& Data, const size_t Ndx) const;
		
		/* ASD message parsers */

		void ParseAsdMessage(const unsigned char Counter,
			const wclDriRawData& Data, wclDriMessages& Messages) const;
		void UnpackAsdMessages(const unsigned char Counter,
			const wclDriRawData& Data, wclDriMessages& Messages) const;
		void ParseAsdMessages(const wclDriRawData& Data,
			wclDriMessages& Messages) const;

	public:
		/// <summary> Creates new parser object. </summary>
		CwclWiFiDriParser();
		/// <summary> Frees the object. </summary>
		virtual ~CwclWiFiDriParser();

		/// <summary> Extracts Drone Remote ID information elements from WiFi BSS
		///   data. </summary>
		/// <param name="Bss"> The WiFi BSS data. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <remarks> As Windows may combine multiple Information Elements received
		///   in different Beacon advertisement in a single raw data stream there
		///   can be more than one IE with given ID. </remarks>
		/// <seealso cref="wclWiFiBss" />
		/// <seealso cref="wclWiFiInformationElements" />
		void ExtractDriElements(const wclWiFiBss& Bss,
			wclWiFiInformationElements& Elements) const;
		/// <summary> Extracts Drone Remote ID information elements from WiFi frame
		///   IE raw data. </summary>
		/// <param name="Raw"> The WiFi frame IE raw bytes array. </param>
		/// <param name="Elements"> If the method completed with success and at
		///   least one IE was found on output contains the array of IEs. </param>
		/// <remarks> As Windows may combine multiple Information Elements received
		///   in different Beacon advertisement in a single raw data stream there
		///   can be more than one IE with given ID. </remarks>
		/// <seealso cref="wclWiFiIeRawData" />
		/// <seealso cref="wclWiFiInformationElements" />
		void ExtractDriElements(const wclWiFiIeRawData& Raw,
			wclWiFiInformationElements& Elements) const;

		/// <summary> Extracts DRI messages from BSS information elements. </summary>
		/// <param name="Bss"> The WiFi BSS data. </param>
		/// <param name="Messages"> If the method completed with success on output
		///   contains the DRI messages list. An application is responsible to free
		///   the returned list. If no one DRI message found the returning value
		///   is the empty list. </param>
		/// <seealso cref="wclWiFiBss" />
		/// <seealso cref="wclWiFiDriMessages" />
		void ParseDriMessages(const wclWiFiBss& Bss, wclDriMessages& Messages) const;
		/// <summary> Extracts DRI messages from information elements raw
		///   data. </summary>
		/// <param name="Raw"> The IE raw data. </param>
		/// <param name="Messages"> If the method completed with success on output
		///   contains the DRI messages list. An application is responsible to free
		///   the returned list. If no one DRI message found the returning value
		///   is the empty list. </param>
		/// <seealso cref="wclWiFiIeRawData" />
		/// <seealso cref="wclWiFiDriMessages" />
		void ParseDriMessages(const wclWiFiIeRawData& Raw, wclDriMessages& Messages) const;
	};
}