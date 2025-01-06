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

#include "..\Common\wclErrors.h"

#include "wclDriCommon.h"

namespace wclDri
{
	/// <summary> The ASD DRI message types. </summary>
	typedef enum
	{
		/// <summary> The Basic ID message. </summary>
		mtBasicId = 0,
		///<summary> The Location message. </summary>
		mtLocation = 1,
		/// <summary> The Authentication message. </summary>
		mtAuth = 2,
		/// <summary> The Self ID message. </summary>
		mtSelfId = 3,
		/// <summary> The System message. </summary>
		mtSystem = 4,
		/// <summary> The Operator ID message. </summary>
		mtOperatorId = 5
	} wclDriAsdMessageType;

	/// <summary> The ASD UAV ID type. </summary>
	typedef enum
	{
		/// <summary> Not assigned. </summary>
		itNone = 0,
		/// <summary> Serial number. </summary>
		itSerialNumber = 1,
		/// <summary> Civil Aviation Authority. </summary>
		itCaaRegistrationId = 2,
		/// <summary> UAS (Unmanned Aircraft System) Traffic Management. </summary>
		itUtmAssignedUuid = 3,
		/// <summary> ICAO managed ID. </summary>
		itSpecificSessionId = 4
	} wclDriAsdIdType;
	
	/// <summary> The ASD UAV type. </summary>
	typedef enum
	{
		/// <summary> Not specified. </summary>
		utNone = 0,
		/// <summary> Fixed wing. </summary>
		utAeroplane = 1,
		/// <summary> Helicopter or multirotor. </summary>
		utCopter = 2,
		/// <summary> Gyroplane. </summary>
		utGyroplane = 3,
		/// <summary> Fixed wing aircraft that can take off vertically. </summary>
		utHybridLift = 4,
		/// <summary> Ornithopter. </summary>
		utOrnithopter = 5,
		/// <summary> Glider. </summary>
		utGlider = 6,
		/// <summary> Kite. </summary>
		utKite = 7,
		/// <summary> Free balloon. </summary>
		utFreeBalloon = 8,
		/// <summary> Captive balloon. </summary>
		utCaptiveBalloon = 9,
		/// <summary> Such as a blimp. </summary>
		utAirship = 10,
		/// <summary> Unpowered parachute. </summary>
		utFreeFallParachute = 11,
		/// <summary> Rocket. </summary>
		utRocket = 12,
		/// <summary> Tethered powered aircraft. </summary>
		utTetheredPoweredAircraft = 13,
		/// <summary> Ground obstacle. </summary>
		utGroundObstacle = 14,
		/// <summary> Any other. </summary>
		utOther = 15
	} wclDriAsdUavType;

	/// <summary> The description type. </summary>
	typedef enum
	{
		/// <summary> General free-form information text. </summary>
		dtText = 0,
		/// <summary> Emergency status description. </summary>
		dtEmergency = 1,
		/// <summary> Extended status description. </summary>
		dtExtended = 2
	} wclDriAsdDescriptionType;

	/// <summary> UAV operator location type. </summary>
	typedef enum
	{
		/// <summary> Takeoff location and altitude. </summary>
		ltTakeOff = 0,
		/// <summary> Dynamic/Live location and altitude. </summary>
		ltLiveGnss = 1,
		/// <summary> Fixed location and altitude. </summary>
		ltFixed = 2
	} wclDriAsdOperatorLocationType;
	
	/// <summary> UAV operator classification. </summary>
	typedef enum
	{
		/// <summary> Classification not specififed. </summary>
		ocUndeclared = 0,
		/// <summary> European Union. </summary>
		ocEu = 1
	} wclDriAsdOperatorClassification;
	
	/// <summary> European UAV category. </summary>
	typedef enum
	{
		/// <summary> Unspecified. </summary>
		ucUndeclared = 0,
		/// <summary> Open category. </summary>
		ucOpen = 1,
		/// <summary> Specific category. </summary>
		ucSpecific = 2,
		/// <summary> Certified category. </summary>
		ucCertified = 3
	} wclDriAsdUavEuCategory;
	
	/// <summary> European UAV class. </summary>
	typedef enum
	{
		/// <summary> Unspecified. </summary>
		ucUnspecified = 0,
		/// <summary> Class 0. </summary>
		ucClass0 = 1,
		/// <summary> Class 0. </summary>
		ucClass1 = 2,
		/// <summary> Class 0. </summary>
		ucClass2 = 3,
		/// <summary> Class 0. </summary>
		ucClass3 = 4,
		/// <summary> Class 0. </summary>
		ucClass4 = 5,
		/// <summary> Class 0. </summary>
		ucClass5 = 6,
		/// <summary> Class 0. </summary>
		ucClass6 = 7
	} wclDriAsdUavEuClass;

	/// <summary> The ASD UAV status. </summary>
	typedef enum
	{
		/// <summary> Undeclared. </summary>
		usUndeclared = 0,
		/// <summary> Ground. </summary>
		usGround = 1,
		/// <summary> Airborne. </summary>
		usAirborne = 2,
		/// <summary> Emergency. </summary>
		usEmergency = 3,
		/// <summary> RID system failure. </summary>
		usFailure = 4
	} wclDriAsdUavStatus;

	/// <summary> The ASD UAV height reference. </summary>
	typedef enum
	{
		/// <summary> Takeoff reference. </summary>
		hrTakeOff = 0,
		/// <summary> Ground reference. </summary>
		hrGround = 1
	} wclDriAsdUavHeightReference;

	/// <summary> ASD UAV horizontal accuracy. </summary>
	typedef enum
	{
		/// <summary> Unknown. </summary>
		haUnknown = 0,
		/// <summary> 10 Nautical miles. 18.52 km </summary>
		ha10Nm = 1,
		/// <summary> 4 Nautical miles. 7.408 km </summary>
		ha4Nm = 2,
		/// <summary> 2 Nautical miles. 3.704 km </summary>
		ha2Nm = 3,
		/// <summary> 1 Nautical mile. 1.852 km </summary>
		ha1Nm = 4,
		/// <summary> 0.5 Nautical mile. 926 m </summary>
		ha05Nm = 5,
		/// <summary> 0.3 Nautical mile. 555.6 m </summary>
		ha03Nm = 6,
		/// <summary> 0.1 Nautical mile. 185.2 m </summary>
		ha01Nm = 7,
		/// <summary> 0.05 Nautical mile. 92.6 m </summary>
		ha005Nm = 8,
		/// <summary> 30 meters. </summary>
		ha30M = 9,
		/// <summary> 10 meters. </summary>
		ha10M = 10,
		/// <summary> 3 meters. </summary>
		ha3M = 11,
		/// <summary> 1 meter. </summary>
		ha1M = 12
	} wclDriAsdUavHorizontalAccuracy;

	/// <summary> ASD UAV vertical accuracy. </summary>
	typedef enum
	{
		/// <summary> Unknown. </summary>
		vaUnknown = 0,
		/// <summary> 150 meters. </summary>
		va150M = 1,
		/// <summary> 45 meters. </summary>
		va45M = 2,
		/// <summary> 25 meters. </summary>
		va25M = 3,
		/// <summary> 10 meters. </summary>
		va10M = 4,
		/// <summary> 3 meters. </summary>
		va3M = 5,
		/// <summary> 1 meter. </summary>
		va1M = 6
	} wclDriAsdUavVerticalAccuracy;

	/// <summary> ASD UAV speed accuracy. </summary>
	typedef enum
	{
		/// <summary> Unknown. </summary>
		saUnknown = 0,
		/// <summary> 10 m/s. </summary>
		sa10MS = 1,
		/// <summary> 3 m/s. </summary>
		sa3MS = 2,
		/// <summary> 1 m/s. </summary>
		sa1Ms = 3,
		/// <summary> 0.3 m/s. </summary>
		sa03Ms = 4
	} wclDriAsdUavSpeedAccuracy;

	/// <summary> ASD UAV timestamp accuracy. </summary>
	typedef enum
	{
		/// <summary> Unknown. </summary>
		taUnknown = 0,
		/// <summary> 0.1 second. </summary>
		ta01s = 1,
		/// <summary> 0.2 second. </summary>
		ta02s = 2,
		/// <summary> 0.3 second. </summary>
		ta03s = 3,
		/// <summary> 0.4 second. </summary>
		ta04s = 4,
		/// <summary> 0.5 second. </summary>
		ta05s = 5,
		/// <summary> 0.6 second. </summary>
		ta06s = 6,
		/// <summary> 0.7 second. </summary>
		ta07s = 7,
		/// <summary> 0.8 second. </summary>
		ta08s = 8,
		/// <summary> 0.9 second. </summary>
		ta09s = 9,
		/// <summary> 1 second. </summary>
		ta1s = 10,
		/// <summary> 1.1 second. </summary>
		ta11s = 11,
		/// <summary> 1.2 second. </summary>
		ta12s = 12,
		/// <summary> 1.3 second. </summary>
		ta13s = 13,
		/// <summary> 1.4 second. </summary>
		ta14s = 14,
		/// <summary> 1.5 second. </summary>
		ta15s = 15
	} wclDriAsdUavTimestampAccuracy;

	/// <summary> The ID value data type for DRI ASD IDs. </summary>
	typedef std::vector<unsigned char> wclDriAsdId;

	/// <summary> The base class for ASD DRI message. </summary>
	/// <seealso cref="CwclDriMessage" />
	class CwclDriAsdMessage : public CwclDriMessage
	{
		DISABLE_COPY(CwclDriAsdMessage);

	private:
		unsigned char			FCounter;
		wclDriAsdMessageType	FMessageType;
		unsigned char			FVersion;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the message counter. </summary>
		/// <returns> The message counter. </returns>
		unsigned char GetCounter() const;
		/// <summary> Gets the message counter. </summary>
		/// <value> The message counter. </value>
		__declspec(property(get = GetCounter)) unsigned char Counter;

		/// <summary> Gets the message type. </summary>
		/// <returns> The ASD DRI message type. </returns>
		/// <seealso cref="wclDriAsdMessageType" />
		wclDriAsdMessageType GetMessageType() const;
		/// <summary> Gets the message type. </summary>
		/// <value> The ASD DRI message type. </value>
		/// <seealso cref="wclDriAsdMessageType" />
		__declspec(property(get = GetMessageType)) wclDriAsdMessageType MessageType;
		
		/// <summary> Gets the protocol version. </summary>
		/// <returns> The protocol version number. </returns>
		unsigned char GetVersion() const;
		/// <summary> Gets the protocol version. </summary>
		/// <value> The protocol version number. </value>
		__declspec(property(get = GetVersion)) unsigned char Version;
	};

	/// <summary> The base class for ASD ID messages. </summary>
	/// <seealso cref="CwclDriAsdMessage" />
	class CwclDriAsdIdMessage : public CwclDriAsdMessage
	{
		DISABLE_COPY(CwclDriAsdIdMessage);
		
	private:
		wclDriAsdId	FId;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdIdMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the ID. </summary>
		/// <returns> The ID. </returns>
		/// <seealso cref="wclDriAsdId" />
		wclDriAsdId GetId() const;
		/// <summary> Gets the ID. </summary>
		/// <value> The ID. </value>
		/// <seealso cref="wclDriAsdId" />
		__declspec(property(get = GetId)) wclDriAsdId Id;
	};
	
	/// <summary> The ASD Basic ID message. </summary>
	/// <seealso cref="CwclDriAsdIdMessage" />
	class CwclDriAsdBasicIdMessage : public CwclDriAsdIdMessage
	{
		DISABLE_COPY(CwclDriAsdBasicIdMessage);
		
	private:
		wclDriAsdIdType		FIdType;
		wclDriAsdUavType	FUavType;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdBasicIdMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the UAV ID type. </summary>
		/// <returns> The ID type. </returns>
		/// <seealso cref="wclDriAsdIdType" />
		wclDriAsdIdType GetIdType() const;
		/// <summary> Gets the UAV ID type. </summary>
		/// <value> The ID type. </value>
		/// <seealso cref="wclDriAsdIdType" />
		__declspec(property(get = GetIdType)) wclDriAsdIdType IdType;
		
		/// <summary> Gets the UAV type. </summary>
		/// <returns> The UAV type. </returns>
		/// <seealso cref="wclDriAsdUavType" />
		wclDriAsdUavType GetUavType() const;
		/// <summary> Gets the UAV type. </summary>
		/// <value> The UAV type. </value>
		/// <seealso cref="TwclDriAsdUavType" />
		__declspec(property(get = GetUavType)) wclDriAsdUavType UavType;
	};

	/// <summary> The ASD Self ID message. </summary>
	/// <seealso cref="CwclDriAsdMessage" />
	class CwclDriAsdSelfIdMessage : public CwclDriAsdMessage
	{
		DISABLE_COPY(CwclDriAsdSelfIdMessage);
		
	private:
		std::string					FDescription;
		wclDriAsdDescriptionType	FDescriptionType;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdSelfIdMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the description. </summary>
		/// <returns> The description. </returns>
		std::string GetDescription() const;
		/// <summary> Gets the description. </summary>
		/// <value> The description. </value>
		__declspec(property(get = GetDescription)) std::string Description;
		
		/// <summary> Gets the description type. </summary>
		/// <returns> The description type. </returns>
		/// <seealso cref="wclDriAsdDescriptionType" />
		wclDriAsdDescriptionType GetDescriptionType() const;
		/// <summary> Gets the description type. </summary>
		/// <value> The description type. </value>
		/// <seealso cref="wclDriAsdDescriptionType" />
		__declspec(property(get = GetDescriptionType)) wclDriAsdDescriptionType DescriptionType;
	};

	/// <summary> The base class for ASD messages with coordinates. </summary>
	/// <seealso cref="CwclDriAsdMessage" />
	class CwclDriAsdCoordinateMessage : public CwclDriAsdMessage
	{
		DISABLE_COPY(CwclDriAsdCoordinateMessage);
		
	protected:
		/// <summary> Converts unsigned integer encoded value to a floating point
		///  altitude value. </summary>
		/// <param name="Value"> The encoded value. </param>
		/// <returns> The decoded altitude. </returns>
		float DecodeAltitude(const unsigned short Value) const;
		/// <summary> Converts unsigned integer encoded values to a floating point
		///   coordinate value. </summary>
		/// <param name="Value"> The encoded value. </param>
		/// <returns> The decoded coordinate. </returns>
		double DecodeCoordinate(const int Value) const;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdCoordinateMessage(const unsigned char Counter,
			const wclDriRawData& Data);
	};
	
	/// <summary> The ASD System message. </summary>
	/// <seealso cref="CwclDriAsdCoordinateMessage" />
	class CwclDriAsdSystemMessage : public CwclDriAsdCoordinateMessage
	{
		DISABLE_COPY(CwclDriAsdSystemMessage);
		
	private:
		float								FAreaCeiling;
		unsigned short						FAreaCount;
		float								FAreaFloor;
		unsigned short						FAreaRadius;
		float								FOperatorAltitude;
		wclDriAsdOperatorClassification		FOperatorClassification;
		double								FOperatorLatitude;
		wclDriAsdOperatorLocationType		FOperatorLocation;
		double								FOperatorLongitude;
		time_t								FTimestamp;
		wclDriAsdUavEuCategory				FUavEuCategory;
		wclDriAsdUavEuClass					FUavEuClass;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdSystemMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the area ceiling. </summary>
		/// <returns> The area ceiling in meters. If ceiling is unknown or invalid the
		///   value is -1000m. </returns>
		float GetAreaCeiling() const;
		/// <summary> Gets the area ceiling. </summary>
		/// <value> The area ceiling in meters. If ceiling is unknown or invalid the
		///   value is -1000m. </value>
		__declspec(property(get = GetAreaCeiling)) float AreaCeiling;
		
		/// <summary> Gets the area count. </summary>
		/// <returns> The area count. </returns>
		unsigned short GetAreaCount() const;
		/// <summary> Gets the area count. </summary>
		/// <value> The area count. </value>
		__declspec(property(get = GetAreaCount)) unsigned short AreaCount;
		
		/// <summary> Gets the area floor. </summary>
		/// <returns> The area floor in meters.  If floor is unknown or invalid the
		///   value is -1000m. </returns>
		float GetAreaFloor() const;
		/// <summary> Gets the area floor. </summary>
		/// <value> The area floor in meters.  If floor is unknown or invalid the
		///   value is -1000m. </value>
		__declspec(property(get = GetAreaFloor)) float AreaFloor;
		
		/// <summary> Gets the area radius. </summary>
		/// <returns> The area radius in meters. </returns>
		unsigned short GetAreaRadius() const;
		/// <summary> Gets the area radius. </summary>
		/// <value> The area radius in meters. </value>
		__declspec(property(get = GetAreaRadius)) unsigned short AreaRadius;
		
		/// <summary> Gets the operator altitude. </summary>
		/// <returns> The operator altitude. </returns>
		float GetOperatorAltitude() const;
		/// <summary> Gets the operator altitude. </summary>
		/// <value> The operator altitude. </value>
		__declspec(property(get = GetOperatorAltitude)) float OperatorAltitude;
		
		/// <summary> Gets the UAV operator classification. </summary>
		/// <returns> The operator classification. </returns>
		/// <seealso cref="wclDriAsdOperatorClassification" />
		wclDriAsdOperatorClassification GetOperatorClassification() const;
		/// <summary> Gets the UAV operator classification. </summary>
		/// <value> The operator classification. </value>
		/// <seealso cref="wclDriAsdOperatorClassification" />
		__declspec(property(get = GetOperatorClassification))
			wclDriAsdOperatorClassification OperatorClassification;
		
		/// <summary> Gets the UAV operator latitude. </summary>
		/// <returns> The latitude value. </returns>
		double GetOperatorLatitude() const;
		/// <summary> Gets the UAV operator latitude. </summary>
		/// <value> The latitude value. </value>
		__declspec(property(get = GetOperatorLatitude)) double OperatorLatitude;
		
		/// <summary> Gets the UAV operator location type. </summary>
		/// <returns> The location type. </returns>
		/// <seealso cref="wclDriAsdOperatorLocationType" />
		wclDriAsdOperatorLocationType GetOperatorLocation() const;
		/// <summary> Gets the UAV operator location type. </summary>
		/// <value> The location type. </value>
		/// <seealso cref="wclDriAsdOperatorLocationType" />
		__declspec(property(get = GetOperatorLocation))
			wclDriAsdOperatorLocationType OperatorLocation;
		
		/// <summary> Gets the UAV operator longitude. </summary>
		/// <returns> The longitude value. </returns>
		double GetOperatorLongitude() const;
		/// <summary> Gets the UAV operator longitude. </summary>
		/// <value> The longitude value. </value>
		__declspec(property(get = GetOperatorLongitude)) double OperatorLongitude;
		
		/// <summary> Gets the timestamp. </summary>
		/// <returns> The timestamp. </returns>
		time_t GetTimestamp() const;
		/// <summary> Gets the timestamp. </summary>
		/// <value> The timestamp. </value>
		__declspec(property(get = GetTimestamp)) time_t Timestamp;
		
		/// <summary> Gets the European UAV category. </summary>
		/// <returns> The UAV category. </returns>
		/// <seealso cref="wclDriAsdUavEuCategory" />
		wclDriAsdUavEuCategory GetUavEuCategory() const;
		/// <summary> Gets the European UAV category. </summary>
		/// <value> The UAV category. </value>
		/// <seealso cref="wclDriAsdUavEuCategory" />
		__declspec(property(get = GetUavEuCategory)) wclDriAsdUavEuCategory UavEuCategory;
		
		/// <summary> Gets the European UAV class. </summary>
		/// <returns> The UAV class. </returns>
		/// <seealso cref="wclDriAsdUavEuClass" />
		wclDriAsdUavEuClass GetUavEuClass() const;
		/// <summary> Gets the European UAV class. </summary>
		/// <value> The UAV class. </value>
		/// <seealso cref="wclDriAsdUavEuClass" />
		__declspec(property(get = GetUavEuClass)) wclDriAsdUavEuClass UavEuClass;
	};

	/// <summary> The ASD Operator ID message. </summary>
	/// <seealso cref="CwclDriAsdIdMessage" />
	class CwclDriAsdOperatorIdMessage : public CwclDriAsdIdMessage
	{
		DISABLE_COPY(CwclDriAsdOperatorIdMessage);
		
	private:
		unsigned char	FIdType;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdOperatorIdMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the UAV operator ID type. </summary>
		/// <returns> The operator ID type. </returns>
		unsigned char GetIdType() const;
		/// <summary> Gets the UAV operator ID type. </summary>
		/// <value> The operator ID type. </value>
		__declspec(property(get = GetIdType)) unsigned char IdType;
	};

	/// <summary> The ASD UAV Location message. </summary>
	/// <seealso cref="CwclDriAsdCoordinateMessage" />
	class CwclDriAsdLocationMessage : public CwclDriAsdCoordinateMessage
	{
		DISABLE_COPY(CwclDriAsdLocationMessage);

	private:
		float							FBaroAltitude;
		wclDriAsdUavVerticalAccuracy	FBaroAccuracy;
		unsigned short					FDirection;
		float							FGeoAltitude;
		float							FHeight;
		wclDriAsdUavHeightReference		FHeightReference;
		wclDriAsdUavHorizontalAccuracy	FHorizontalAccuracy;
		float							FHorizontalSpeed;
		double							FLatitude;
		double							FLongitude;
		wclDriAsdUavSpeedAccuracy		FSpeedAccuracy;
		wclDriAsdUavStatus				FStatus;
		float							FTimestamp;
		wclDriAsdUavTimestampAccuracy	FTimestampAccuracy;
		wclDriAsdUavVerticalAccuracy	FVerticalAccuracy;
		float							FVerticalSpeed;
		
		unsigned short DecodeDirection(const wclDriRawData& Data) const;
		float DecodeHorizontalSpeed(const wclDriRawData& Data) const;
		float DecodeVertocalSpeed(const wclDriRawData& Data) const;
		float DecodeTimestamp(const wclDriRawData& Data) const;
		
	public:
		/// <summary> Creates new DRI message object. </summary>
		/// <param name="Counter"> The message counter. </param>
		/// <param name="Data"> The raw DRI message data. </param>
		/// <seealso cref="wclDriRawData" />
		CwclDriAsdLocationMessage(const unsigned char Counter,
			const wclDriRawData& Data);
		
		/// <summary> Gets the baro altitude. </summary>
		/// <returns> The altitude in meters. If altitude is unknown or invalid the
		///   value is -1000m. </returns>
		float GetBaroAltitude() const;
		/// <summary> Gets the baro altitude. </summary>
		/// <value> The altitude in meters. If altitude is unknown or invalid the
		///   value is -1000m. </value>
		__declspec(property(get = GetBaroAltitude)) float BaroAltitude;
		
		/// <summary> Gets the baro altitude accuracy. </summary>
		/// <returns> The baro accuracy. </returns>
		/// <seealso cref="wclDriAsdUavVerticalAccuracy" />
		wclDriAsdUavVerticalAccuracy GetBaroAccuracy() const;
		/// <summary> Gets the baro altitude accuracy. </summary>
		/// <value> The baro accuracy. </value>
		/// <seealso cref="wclDriAsdUavVerticalAccuracy" />
		__declspec(property(get = GetBaroAccuracy))
			wclDriAsdUavVerticalAccuracy BaroAccuracy;
		
		/// <summary> Gets the UAV direction. </summary>
		/// <returns> The UAV direction in degrees. If the direction is unknown or
		///   invalid the value is 361. </returns>
		unsigned short GetDirection() const;
		/// <summary> Gets the UAV direction. </summary>
		/// <value> The UAV direction in degrees. If the direction is unknown or
		///   invalid the value is 361. </value>
		__declspec(property(get = GetDirection)) unsigned short Direction;
		
		/// <summary> Gets the geo altitude. </summary>
		/// <returns> The altitude in meters. If altitude is unknown or invalid the
		///   value is -1000m. </returns>
		float GetGeoAltitude() const;
		/// <summary> Gets the geo altitude. </summary>
		/// <value> The altitude in meters. If altitude is unknown or invalid the
		///   value is -1000m. </value>
		__declspec(property(get = GetGeoAltitude)) float GeoAltitude;
		
		/// <summary> Gets height. </summary>
		/// <returns> The height in meters. If height is unknown or invalid the
		///   value is -1000m. </returns>
		float GetHeight() const;
		/// <summary> Gets height. </summary>
		/// <value> The height in meters. If height is unknown or invalid the
		///   value is -1000m. </value>
		__declspec(property(get = GetHeight)) float Height;
		
		/// <summary> Gets the height reference. </summary>
		/// <returns> The height reference. </returns>
		/// <seealso cref="wclDriAsdUavHeightReference" />
		wclDriAsdUavHeightReference GetHeightReference() const;
		/// <summary> Gets the height reference. </summary>
		/// <value> The height reference. </value>
		/// <seealso cref="wclDriAsdUavHeightReference" />
		__declspec(property(get = GetHeightReference))
			wclDriAsdUavHeightReference HeightReference;
		
		/// <summary> Gets the horizontal accuracy. </summary>
		/// <returns> The horizontal accuracy. </returns>
		/// <seealso cref="wclDriAsdUavHorizontalAccuracy" />
		wclDriAsdUavHorizontalAccuracy GetHorizontalAccuracy() const;
		/// <summary> Gets the horizontal accuracy. </summary>
		/// <value> The horizontal accuracy. </value>
		/// <seealso cref="wclDriAsdUavHorizontalAccuracy" />
		__declspec(property(get = GetHorizontalAccuracy))
			wclDriAsdUavHorizontalAccuracy HorizontalAccuracy;
		
		/// <summary> Gets the horizontal speed. </summary>
		/// <returns> The horizontal speed in m/s. The maximum speed value is
		///   254.25 m/s. If the speed is unknown or invalid the value is
		///   255 m/s. </returns>
		float GetHorizontalSpeed() const;
		/// <summary> Gets the horizontal speed. </summary>
		/// <value> The horizontal speed in m/s. The maximum speed value is
		///   254.25 m/s. If the speed is unknown or invalid the value is
		///   255 m/s. </value>
		__declspec(property(get = GetHorizontalSpeed)) float HorizontalSpeed;
		
		/// <summary> Gets the latitude. </summary>
		/// <returns> The latitude. If the latitude is invalid or unknown the value
		///   is 0. </returns>
		double GetLatitude() const;
		/// <summary> Gets the latitude. </summary>
		/// <value> The latitude. If the latitude is invalid or unknown the value
		///   is 0. </value>
		__declspec(property(get = GetLatitude)) double Latitude;
		
		/// <summary> Gets the longitude. </summary>
		/// <returns> The longitude. If the longitude is invalid or unknown the value
		///   is 0. </returns>
		double GetLongitude() const;
		/// <summary> Gets the longitude. </summary>
		/// <value> The longitude. If the longitude is invalid or unknown the value
		///   is 0. </value>
		__declspec(property(get = GetLongitude)) double Longitude;
		
		/// <summary> Gets the speed accuracy. </summary>
		/// <returns> The speed accuracy. </returns>
		/// <seealso cref="wclDriAsdUavSpeedAccuracy" />
		wclDriAsdUavSpeedAccuracy GetSpeedAccuracy() const;
		/// <summary> Gets the speed accuracy. </summary>
		/// <value> The speed accuracy. </value>
		/// <seealso cref="wclDriAsdUavSpeedAccuracy" />
		__declspec(property(get = GetSpeedAccuracy))
			wclDriAsdUavSpeedAccuracy SpeedAccuracy;
		
		/// <summary> Gets the UAV status. </summary>
		/// <returns> The UAV status. </returns>
		/// <seealso cref="wclDriAsdUavStatus" />
		wclDriAsdUavStatus GetStatus() const;
		/// <summary> Gets the UAV status. </summary>
		/// <value> The UAV status. </value>
		/// <seealso cref="wclDriAsdUavStatus" />
		__declspec(property(get = GetStatus)) wclDriAsdUavStatus Status;
		
		/// <summary> Gets the timestamp. </summary>
		/// <returns> The timestamp. </returns>
		float GetTimestamp() const;
		/// <summary> Gets the timestamp. </summary>
		/// <value> The timestamp. </value>
		__declspec(property(get = GetTimestamp)) float Timestamp;
		
		/// <summary> Gets the timestamp accuracy. </summary>
		/// <returns> The timestamp accuracy. </returns>
		/// <seealso cref="wclDriAsdUavTimestampAccuracy" />
		wclDriAsdUavTimestampAccuracy GetTimestampAccuracy() const;
		/// <summary> Gets the timestamp accuracy. </summary>
		/// <value> The timestamp accuracy. </value>
		/// <seealso cref="wclDriAsdUavTimestampAccuracy" />
		__declspec(property(get = GetTimestampAccuracy))
			wclDriAsdUavTimestampAccuracy TimestampAccuracy;
		
		/// <summary> Gets the vertical accuracy. </summary>
		/// <returns> The vertical accuracy. </returns>
		/// <seealso cref="wclDriAsdUavVerticalAccuracy" />
		wclDriAsdUavVerticalAccuracy GetVerticalAccuracy() const;
		/// <summary> Gets the vertical accuracy. </summary>
		/// <value> The vertical accuracy. </value>
		/// <seealso cref="wclDriAsdUavVerticalAccuracy" />
		__declspec(property(get = GetVerticalAccuracy))
			wclDriAsdUavVerticalAccuracy VerticalAccuracy;
		
		/// <summary> Gets the vertical speed. </summary>
		/// <returns> The vertical speed in m/s. The maximum value is 62 m/s. If the
		///   speed is unknown or invalid the value is 63 m/s. </returns>
		float GetVerticalSpeed() const;
		/// <summary> Gets the vertical speed. </summary>
		/// <value> The vertical speed in m/s. The maximum value is 62 m/s. If the
		///   speed is unknown or invalid the value is 63 m/s. </value>
		__declspec(property(get = GetVerticalSpeed)) float VerticalSpeed;
	};

	/// <summary> The Drone Remote ID ASD messages parser. </summary>
	/// <remarks> The class is for internal use only. Use high-level DRI
	///   parsers or watchers instead. </remarks>
	class CwclDriAsdParser
	{
		DISABLE_COPY(CwclDriAsdParser);
		
	private:
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
		/// <summary> Creates new ASD message parser. </summary>
		CwclDriAsdParser();
		/// <summary> Free the parser. </summary>
		virtual ~CwclDriAsdParser();

		/// <summary> Parse ASD DRI messages. </summary>
		/// <param name="Raw"> The ASD DRI raw data. </param>
		/// <param name="Messages"> If the method completed with success on output
		///   contains the DRI messages list. An application is responsible to free
		///   the returned list. If no one DRI message found the returning value
		///   is the empty list. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Parse(const wclDriRawData& Raw, wclDriMessages& Messages);
	};
}