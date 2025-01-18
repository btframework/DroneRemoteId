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
#include "..\Communication\wclConnections.h"

#include "..\DRI\wclDriAsd.h"

#include "wclBluetoothErrors.h"

using namespace wclCommon;
using namespace wclCommunication;
using namespace wclDri;

namespace wclBluetooth
{
	/* Forward declaration */

	class CwclBluetoothRadio;
	class CwclBluetoothManager;
	class CwclRfCommServerClientConnection;
	class CwclGattLocalCharacteristic;
	class CwclGattLocalCharacteristicReadRequest;
	class CwclGattLocalCharacteristicWriteRequest;
	class CwclGattLocalService;
	class CwclGattServerConnection;
	class CwclGattServerClient;

	/* Data types */

	/// <summary> Supported Bluetooth APIs (drivers). </summary>
	typedef enum
	{
		/// <summary> BlueSoleil Bluetooth driver. </summary>
		baBlueSoleil,
		/// <summary> Microsoft Bluetooth driver. </summary>
		baMicrosoft,
		/// <summary> Toshiba Bluetooth driver. </summary>
		baToshiba,
		/// <summary> Silicon Labs BLED112 module. </summary>
		baBled112
	} wclBluetoothApi;
	/// <summary> The set of APIs that should be used by Bluetooth
	///   Framework. </summary>
	/// <seealso cref="wclBluetoothApi" />
	typedef std::set<wclBluetoothApi> wclBluetoothApis;

	/// <summary> Bluetooth versions. </summary>
	typedef enum
	{
		/// <summary> Bluetooth 1.0b. </summary>
		bt10,
		/// <summary> Bluetooth 1.1. </summary>
		bt11,
		/// <summary> Bluetooth 1.2. </summary>
		bt12,
		/// <summary> Bluetooth 2.0 + EDR. </summary>
		bt20,
		/// <summary> Bluetooth 2.1 + EDR. </summary>
		bt21,
		/// <summary> Bluetooth 3.0 + HS. </summary>
		bt30,
		/// <summary> Bluetooth 4.0. </summary>
		bt40,
		/// <summary> Bluetooth 4.1. </summary>
		bt41,
		/// <summary> Bluetooth 4.2. </summary>
		bt42,
		/// <summary> Bluetooth 5.0. </summary>
		bt50,
		/// <summary> Bluetooth 5.1. </summary>
		bt51,
		/// <summary> Bluetooth 5.2. </summary>
		bt52,
		/// <summary> Bluetooth 5.3. </summary>
		bt53,
		/// <summary> Bluetooth 5.4. </summary>
		bt54,
		/// <summary> Other Bluetooth version. </summary>
		btOther
	} wclBluetoothVersion;

	/// <summary> A remote device types. </summary>
	typedef enum
	{
		/// <summary> Classic Bluetooth device. </summary>
		dtClassic,
		/// <summary> BLE (Bluetooth Low Energy) device. </summary>
		dtBle,
		/// <summary> Mixed device (supports both classic and LE
		///   functions). </summary>
		dtMixed,
		/// <summary> Unknown device type. </summary>
		dtUnknown
	} wclBluetoothDeviceType;

	/// <summary> The structure represents a Bluetooth Service record. </summary>
	typedef struct
	{
		/// <summary> The service' handle. </summary>
		unsigned long Handle;
		/// <summary> The service's UUID. </summary>
		GUID Uuid;
		/// <summary> The service's RFCOMM channel number. For non-RFCOMM
		///   services this value is <c>0</c>. </summary>
		unsigned char Channel;
		/// <summary> The service's name. </summary>
		tstring Name;
		/// <summary> The service's comment. </summary>
		tstring Comment;
	} wclBluetoothService;
	/// <summary> The dynamic array for the service's list. </summary>
	/// <seealso cref="wclBluetoothService" />
	typedef std::vector<wclBluetoothService> wclBluetoothServices;

	/// <summary> Bluetooth MAC address array. </summary>
	typedef std::vector<__int64> wclBluetoothAddresses;
	/// <summary> The Bluetooth installed services GUIDs array. </summary>
	typedef std::vector<GUID> wclBluetoothInstalledServices;

	/// <summary> The record describes created virtual COM port. </summary>
	typedef struct
	{
		/// <summary> Remote device MAC address. </summary>
		__int64 Address;
		/// <summary> Service's UUID. </summary>
		GUID Service;
		/// <summary> Virtual COM port number. </summary>
		unsigned short Number;
		/// <summary> Indicates outgoing vCOM. </summary>
		/// <remarks> If this member is <c>True</c> the vCOM is outgoing. If this
		///   member is <c>False</c> the vCOM is incoming. </remarks>
		bool Outgoing;
	} wclVirtualComPort;
	/// <summary> Virtual COM ports array. </summary>
	/// <seealso cref="wclVirtualComPort" />
	typedef std::vector<wclVirtualComPort> wclVirtualComPorts;

	/// <summary> The <c>wclBluetoothDiscoverKind</c> enumeration describes
	///   Bluetooth devices discovering methods. </summary>
	typedef enum
	{
		/// <summary> Discover only Classic Bluetooth devices. </summary>
		dkClassic,
		/// <summary> Discovers only Bluetooth Low Energy devices. </summary>
		dkBle
	} wclBluetoothDiscoverKind;

	/// <summary> The type describes the array of the additional protocols list
	///   for a server service record. </summary>
	typedef std::vector<unsigned short> wclBluetoothSdpProtocols;

	/// <summary> The structure describes the Bluetooth Profile for the server
	///   service record. </summary>
	typedef struct
	{
		/// <summary> The 16 buts profile's UUID. </summary>
		unsigned short Uuid;
		/// <summary> The profile's version number. </summary>
		unsigned short Version;
	} wclBluetoothSdpProfile;
	/// <summary> The type describes the array of the additional profiles
	///   list for a server service record. </summary>
	/// <seealso cref="wclBluetoothSdpProfile" />
	typedef std::vector<wclBluetoothSdpProfile> wclBluetoothSdpProfiles;

	/// <summary> The type describes the byte stream that used for adding
	///   additional supported formats for a server service record. </summary>
	typedef std::vector<unsigned char> wclBluetoothSdpFormats;

	/// <summary> The structure contains information about a Bluetooth Low
	///   Energy (LE) Universally Unique Identifier (UUID). </summary>
	typedef struct
	{
		/// <summary> Indicates if the Low Energy (LE) UUID a 16-bit shortened
		///   value, or if it is the long 128-bit value. </summary>
		bool IsShortUuid;
		/// <summary> The short 16-bit value of the UUID. This member applies only
		///   if <c>IsShortUuid</c> is <c>True</c>. </summary>
		unsigned short ShortUuid;
		/// <summary> The long 128-bit value of the UUID. This member applies only
		///   if <c>IsShortUuid</c> is <c>False</c>. </summary>
		GUID LongUuid;
	} wclGattUuid;

	/// <summary> Compares <see cref="wclGattUuid" /> structures. </summary>
	/// <param name="u1"> First <see cref="wclGattUuid" /> structure. </param>
	/// <param name="u2"> Second <see cref="wclGattUuid" /> structure. </param>
	/// <returns> Returns <c>true</c> if the structures are equal. Returns <c>false</c>
	///   otherwise. </returns>
	/// <seealso cref="wclGattUuid" />
	bool operator ==(const wclGattUuid& u1, const wclGattUuid& u2);
	/// <summary> Compares <see cref="wclGattUuid" /> structures. </summary>
	/// <param name="u1"> First <see cref="wclGattUuid" /> structure. </param>
	/// <param name="u2"> Second <see cref="wclGattUuid" /> structure. </param>
	/// <returns> Returns <c>false</c> if the structures are equal. Returns <c>true</c>
	///   otherwise. </returns>
	/// <seealso cref="wclGattUuid" />
	bool operator !=(const wclGattUuid& u1, const wclGattUuid& u2);

	/// <summary> The structure describes a Bluetooth Low Energy (LE) generic
	///   attribute (GATT) profile service. </summary>
	typedef struct
	{
		/// <summary> The Universally Unique ID (UUID) of the Bluetooth LE GATT
		///   profile service. </summary>
		/// <seealso cref="wclGattUuid" />
		wclGattUuid Uuid;
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   attributes. </summary>
		unsigned short Handle;
	} wclGattService;
	/// <summary> The list of GATT services. </summary>
	/// <seealso cref="wclGattService" />
	typedef std::vector<wclGattService> wclGattServices;

	/// <summary> The structure describes a Bluetooth Low Energy (LE) generic
	///   attribute (GATT) profile characteristic. </summary>
	typedef struct
	{
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   service. </summary>
		unsigned short ServiceHandle;
		/// <summary> The Universally Unique ID (UUID) of the
		///   characteristic. </summary>
		/// <seealso cref="wclGattUuid" />
		wclGattUuid Uuid;
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   attributes. </summary>
		unsigned short Handle;
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   characteristic value. </summary>
		unsigned short ValueHandle;
		/// <summary> The characteristic can be broadcast. </summary>
		bool IsBroadcastable;
		/// <summary> The characteristic can be read. </summary>
		bool IsReadable;
		/// <summary> The characteristic can be written to. </summary>
		bool IsWritable;
		/// <summary> The characteristic can be written to without requiring
		///   a response. </summary>
		bool IsWritableWithoutResponse;
		/// <summary> The characteristic can be signed writable. </summary>
		bool IsSignedWritable;
		/// <summary> The characteristic can be updated by the device through
		///   Handle Value Notifications, and the new value will be returned
		///   through the event. </summary>
		bool IsNotifiable;
		/// <summary> The characteristic can be updated by the device through
		///   Handle Value Indications, and the new value will be returned through
		///   the event. </summary>
		bool IsIndicatable;
		/// <summary> The characteristic has extended properties, which will be
		///   presented through a Characteristic Extended Properties
		///   descriptor. </summary>
		bool HasExtendedProperties;
	} wclGattCharacteristic;
	/// <summary> The list of GATT characteristics. </summary>
	/// <seealso cref="wclGattCharacteristic" />
	typedef std::vector<wclGattCharacteristic> wclGattCharacteristics;

	/// <summary> The enumeration describes the different types of Bluetooth LE
	///   generic attributes (GATT). </summary>
	typedef enum
	{
		/// <summary> The characteristic value has additional properties that
		///   describe how it can be used, or how it can be accessed. </summary>
		dtCharacteristicExtendedProperties,
		/// <summary> The characteristic value contains a string that is a user
		///   textual description. </summary>
		dtCharacteristicUserDescription,
		/// <summary> The characteristic value may be configured by the
		///   client. </summary>
		dtClientCharacteristicConfiguration,
		/// <summary> The characteristic value may be configured for the
		///   server. </summary>
		dtServerCharacteristicConfiguration,
		/// <summary> The format of the characteristic value. </summary>
		dtCharacteristicFormat,
		/// <summary> The format of an aggregated characteristic value. </summary>
		dtCharacteristicAggregateFormat,
		/// <summary> The characteristic value is customized. </summary>
		dtCustomDescriptor
	} wclGattDescriptorType;

	/// <summary> The structure describes a Bluetooth Low Energy (LE) generic
	///   attribute (GATT) profile descriptor. </summary>
	typedef struct
	{
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   service. </summary>
		unsigned short ServiceHandle;
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   characteristic. </summary>
		unsigned short CharacteristicHandle;
		/// <summary> The type of the Bluetooth LE GATT descriptor. </summary>
		/// <seealso cref="wclGattDescriptorType" />
		wclGattDescriptorType DescriptorType;
		/// <summary> The Universally Unique ID (UUID) of the Bluetooth LE GATT
		///   descriptor. </summary>
		/// <seealso cref="wclGattUuid" />
		wclGattUuid Uuid;
		/// <summary> The handle to the Bluetooth LE GATT profile
		///   attributes. </summary>
		unsigned short Handle;
	} wclGattDescriptor;
	/// <summary> The list of GATT descriptors. </summary>
	/// <seealso cref="wclGattDescriptor" />
	typedef std::vector<wclGattDescriptor> wclGattDescriptors;

	/// <summary> The structure contains of the different characteristic
	///   extended property members. </summary>
	typedef struct
	{
		/// <summary> The parent characteristic value is reliable write
		///   enabled. </summary>
		bool IsReliableWriteEnabled;
		/// <summary> The characteristic user description descriptor
		///   is writable. </summary>
		bool IsAuxiliariesWritable;
	} wclGattCharacteristicExtendedProperties;

	/// <summary> The structure describes the different client characteristic
	///   configuration members. </summary>
	typedef struct
	{
		/// <summary> Whether the characteristic has been registered with the device
		///   to receive Handle Value Notifications. <c>True</c> if the
		///   characteristic has been registered. Otherwise,
		///   <c>False</c>. </summary>
		bool IsSubscribeToNotification;
		/// <summary> Whether the characteristic has been registered with the device
		///   to receive Handle Value Indications. <c>true</c> if the characteristic
		///   has been registered. Otherwise, <c>False</c>. </summary>
		bool IsSubscribeToIndication;
	} wclGattClientCharacteristicConfiguration;

	/// <summary> The structure describes the different server characteristic
	///   configuration members. </summary>
	typedef struct
	{
		/// <summary> The parent characteristic value can be broadcast. </summary>
		bool IsBroadcast;
	} wclGattServerCharacteristicConfiguration;

	/// <summary> The characteristic presentation formats. </summary>
	typedef enum
	{
		/// <summary> Reserved for future use. </summary>
		fmtRfu = 0x00,
		/// <summary> Boolean. </summary>
		fmtBoolean = 0x01,
		/// <summary> Unsigned 2-bit integer. </summary>
		fmt2Bit = 0x02,
		/// <summary> Unsigned 4-bit integer. </summary>
		fmtNibble = 0x03,
		/// <summary> Unsigned 8-bit integer. </summary>
		fmtUInt8 = 0x04,
		/// <summary> Unsigned 12-bit integer. </summary>
		fmtUInt12 = 0x05,
		/// <summary> Unsigned 16-bit integer. </summary>
		fmtUInt16 = 0x06,
		/// <summary> Unsigned 24-bit integer. </summary>
		fmtUInt24 = 0x07,
		/// <summary> Unsigned 32-bit integer. </summary>
		fmtUInt32 = 0x08,
		/// <summary> Unsigned 48-bit integer. </summary>
		fmtUInt48 = 0x09,
		/// <summary> Unsigned 64-bit integer. </summary>
		fmtUInt64 = 0x0A,
		/// <summary> Unsigned 128-bit integer. </summary>
		fmtUInt128 = 0x0B,
		/// <summary> Signed 8-bit integer. </summary>
		fmtSInt8 = 0x0C,
		/// <summary> Signed 12-bit integer. </summary>
		fmtSInt12 = 0x0D,
		/// <summary> Signed 16-bit integer. </summary>
		fmtSInt16 = 0x0E,
		/// <summary> Signed 24-bit integer. </summary>
		fmtSInt24 = 0x0F,
		/// <summary> Signed 32-bit integer. </summary>
		fmtSInt32 = 0x10,
		/// <summary> Signed 48-bit integer. </summary>
		fmtSInt48 = 0x11,
		/// <summary> Signed 64-bit integer. </summary>
		fmtSInt64 = 0x12,
		/// <summary> Signed 128-bit integer. </summary>
		fmtSInt128 = 0x13,
		/// <summary> IEEE-754 32-bit floating point. </summary>
		fmtFloat32 = 0x14,
		/// <summary> IEEE-754 64-bit floating point. </summary>
		fmtFloat64 = 0x15,
		/// <summary> IEEE-11073 16-bit SFLOAT. </summary>
		fmtSFloat = 0x16,
		/// <summary> IEEE-11073 32-bit FLOAT. </summary>
		fmtFloat = 0x17,
		/// <summary> IEEE-20601 format. </summary>
		fmtDUint16 = 0x18,
		/// <summary> UTF-8 string. </summary>
		fmtUtf8S = 0x19,
		/// <summary> UTF-16 string. </summary>
		fmtUtf16S = 0x1A,
		/// <summary> Opaque Structure. </summary>
		fmtStruct = 0x1B
	} wclGattPresentationFormat;

	/// <summary> The structure describes the different characteristic format
	///   members. </summary>
	typedef struct
	{
		/// <summary> The format of the parent characteristic value. </summary>
		/// <seealso cref="wclGattPresentationFormat" />
		wclGattPresentationFormat Format;
		/// <summary> The exponent value to use to determine how the value of the
		///   characteristic value is further formatted. </summary>
		unsigned char Exponent;
		/// <summary> The unit of the characteristic value as defined in the
		///   Assigned Numbers specification. </summary>
		unsigned short AUnit;
		/// <summary> The name-space where the unit is defined in the Assigned
		///   Numbers specification. </summary>
		unsigned char NameSpace;
		/// <summary> The Universally Unique ID (UUID) that describes the format of
		///   the parent characteristic value. </summary>
		unsigned short Description;
	} wclGattCharacteristicFormat;
	/// <summary> The <see cref="wclGattCharacteristicFormat" /> array. </summary>
	/// <seealso cref="wclGattCharacteristicFormat" />
	typedef std::vector<wclGattCharacteristicFormat> wclGattCharacteristicFormats;

	/// <summary> The structure contains a GATT characteristic user description
	///   descriptor data. </summary>
	typedef struct
	{
		/// <summary> The characteristic's user description. </summary>
		tstring Description;
	} wclGattCharactertisticUserDescription;

	/// <summary> The structure contains a GATT characteristic aggregate format
	///   data. </summary>
	typedef struct
	{
		/// <summary> The GATT characteristic presentation format descriptor
		///   handles array. </summary>
		std::vector<unsigned short> Handles;
	} wclGattCharacteristicAggregateFormat;

	/// <summary> The structure contains a descriptor value. </summary>
	typedef struct
	{
		/// <summary> The type of the descriptor value. </summary>
		/// <seealso cref="wclGattDescriptorType" />
		wclGattDescriptorType AType;
		/// <summary> The Universally Unique ID (UUID) of the descriptor
		///   value. </summary>
		/// <seealso cref="wclGattUuid"/>
		wclGattUuid Uuid;
		/// <summary> Container structure for the different characteristic
		///   extended property members. This member is valid only if <c>AType</c>
		///   is <c>dtCharacteristicExtendedProperties</c></summary>
		/// <seealso cref="wclGattCharacteristicExtendedProperties" />
		wclGattCharacteristicExtendedProperties CharacteristicExtendedProperties;
		/// <summary> Container structure for the different client characteristic
		///   configuration members. This member is valid only if <c>AType</c> is
		///   <c>dtClientCharacteristicConfiguration</c>. </summary>
		/// <seealso cref="wclGattClientCharacteristicConfiguration" />
		wclGattClientCharacteristicConfiguration ClientCharacteristicConfiguration;
		/// <summary> Container structure for the different server characteristic
		///   configuration members. This member is valid only if <c>AType</c> is
		///   <c>dtServerCharacteristicConfiguration</c>. </summary>
		/// <seealso cref="wclGattServerCharacteristicConfiguration" />
		wclGattServerCharacteristicConfiguration ServerCharacteristicConfiguration;
		/// <summary> Container structure for the different characteristic format
		///   members. This member is valid only if <c>AType</c> is
		///   <c>dtCharacteristicFormat</c>. </summary>
		/// <seealso cref="wclGattCharacteristicFormat" />
		wclGattCharacteristicFormat CharacteristicFormat;
		/// <summary> Contains data structure of a characteristic's aggregate
		///   format descriptor. This member is valid only if <c>AType</c> is
		///   <c>dtCharacteristicAggregateFormat</c> </summary>
		/// <seealso cref="wclGattCharacteristicAggregateFormat" />
		wclGattCharacteristicAggregateFormat CharacteristicAggregateFormat;
		/// <summary> Container structure for the characteristic's user description
		///   descriptor data. This member is valid only if <c>AType</c> is
		///   <c>dtCharacteristicUserDescription</c>. </summary>
		/// <seealso cref="wclGattCharactertisticUserDescription" />
		wclGattCharactertisticUserDescription UserDescription;
		/// <summary> The descriptor value data. An application is
		///   responsible to free a memory allocated for this dynamic array.
		///   If there is no data the member is <c>NULL</c>. </summary>
		unsigned char* Data;
		/// <summary> The descriptor value length in bytes. </summary>
		unsigned long Length;
	} wclGattDescriptorValue;

	/// <summary> This enumeration describes how a GATT reading operation
	///   should be executed. </summary>
	typedef enum
	{
		/// <summary> Use default behavior. </summary>
		goNone,
		/// <summary> The value is to be read directly from the device. This
		///   overwrites the one in the cache if one is already
		///   present. </summary>
		goReadFromDevice,
		/// <summary> The value is to be read from the cache (regardless of whether
		///   it is present in the cache or not). </summary>
		goReadFromCache
	} wclGattOperationFlag;

	/// <summary> Represents the desired security level for GATT communication. </summary>
	typedef enum
	{
		/// <summary> Uses the default protection level. </summary>
		plNone,
		/// <summary> Require the link to be authenticated. </summary>
		plAuthentication,
		/// <summary> Require the link to be encrypted. </summary>
		plEncryption,
		/// <summary> Require the link to be encrypted and authenticated. </summary>
		plEncryptionAndAuthentication
	} wclGattProtectionLevel;

	/// <summary> The GATT write operation mode. </summary>
	typedef enum
	{
		/// <summary> Execute write operation as Write With Response. </summary>
		wkWithResponse,
		/// <summary> Execute write operation as Write Without Response if a
		///   characteristic supports such method. If a characteristic does not
		///   support Write Without Response the
		///   <see cref="WCL_E_BLUETOOTH_LE_WRITE_WITHOUT_RESPONSE_NOT_SUPPORTED" />
		///   error returned. </summary>
		wkWithoutResponse,
		/// <summary> Automatic detection of write operation mode. If a
		///   characteristic supports Write Without Response then this method will
		///   be used. Otherwise the Write With Response operation
		///   executes. The default write operation mode. </summary>
		wkAuto
	} wclGattWriteKind;

	/// <summary> The GATT subscription method. </summary>
	typedef enum
	{
		/// <summary> Subscribe to notifications. </summary>
		skNotification,
		/// <summary> Subscribe to indication. </summary>
		skIndication,
		/// <summary> A subscription method is controlled by a characteristic
		///   properties. </summary>
		skManual
	} wclGattSubscribeKind;

	/// <summary> The enumeration represents the GATT local characteristic
	///   properties, as defined by the GATT profile. </summary>
	typedef enum
	{
		/// <summary> The characteristic supports signed writes. </summary>
		cpAuthenticatedSignedWritable,
		/// <summary> The characteristic supports broadcasting. </summary>
		cpBroadcastable,
		/// <summary> The ExtendedProperties Descriptor is present. </summary>
		cpExtendedProperties,
		/// <summary> The characteristic is indicatable. </summary>
		cpIndicatable,
		/// <summary> The characteristic is notifiable. </summary>
		cpNotifiable,
		/// <summary> The characteristic is readable. </summary>
		cpReadable,
		/// <summary> The characteristic supports reliable writes. </summary>
		cpReliableWritable,
		/// <summary> The characteristic has writable auxiliaries. </summary>
		cpWritableAuxiliaries,
		/// <summary> The characteristic is writable. </summary>
		cpWritable,
		/// <summary> The characteristic supports Write Without Response. </summary>
		cpWritableWithoutResponse
	} wclGattLocalCharacteristicProperty;
	/// <summary> The set of GATT local characteristic properties, as defined by
	///   the GATT profile. </summary>
	/// <seealso cref="wclGattLocalCharacteristicProperty" />
	typedef std::set<wclGattLocalCharacteristicProperty> wclGattLocalCharacteristicProperties;

	/// <summary> The structure describes the local GATT descriptor. </summary>
	typedef struct
	{
		/// <summary> The descriptor's UUID. </summary>
		unsigned short Uuid;
		/// <summary> The read protection level of the descriptor. </summary>
		/// <seealso cref="wclGattProtectionLevel" />
		wclGattProtectionLevel ReadProtectionLevel;
		/// <summary> The write protection level of the descriptor. </summary>
		/// <seealso cref="wclGattProtectionLevel" />
		wclGattProtectionLevel WriteProtectionLevel;
		/// <summary> The descriptor's data. </summary>
		unsigned char* Data;
		/// <summary> The descriptor's data size. </summary>
		unsigned char Size;
	} wclGattLocalDescriptor;
	/// <summary> GATT local descriptors array. </summary>
	/// <seealso cref="wclGattLocalDescriptor" />
	typedef std::vector<wclGattLocalDescriptor> wclGattLocalDescriptors;

	/// <summary> The structure represents a GATT local characteristic
	///   parameters. </summary>
	typedef struct
	{
		/// <summary> Custom descriptors. </summary>
		/// <remarks> This array must not include Presentation Format, Aggregate
		///   Format, Client Configuration, Server Configuration and User
		///   Description descriptors. </remarks>
		/// <seealso cref="wclGattLocalDescriptors" />
		wclGattLocalDescriptors Descriptors;
		/// <summary> The characteristic's presentation formats. </summary>
		/// <remarks> If this field is set the Characteristic Presentation Format
		///   descriptor (one ore more) will be added. </remarks>
		/// <seealso cref="TwclGattCharacteristicFormat" />
		wclGattCharacteristicFormats PresentationFormats;
		/// <summary> The characteristic's properties. </summary>
		/// <seealso cref="wclGattLocalCharacteristicProperties" />
		wclGattLocalCharacteristicProperties Props;
		/// <summary> The read protection level of a local
		///   characteristic. </summary>
		/// <seealso cref="wclGattProtectionLevel" />
		wclGattProtectionLevel ReadProtectionLevel;
		/// <summary> The characteristic's user-friendly description. </summary>
		/// <remarks> If this property is set the Characteristic User Description
		///   descriptor will be added. </remarks>
		tstring UserDescription;
		/// <summary> The write protection level of a local
		///   characteristic. </summary>
		/// <seealso cref="wclGattProtectionLevel" />
		wclGattProtectionLevel WriteProtectionLevel;
	} wclGattLocalCharacteristicParameters;

	/// <summary> Specifies the Bluetooth LE scanning mode. </summary>
	typedef enum
	{
		/// <summary> Scanning mode is active. This indicates that scan request
		///   packets will be sent from the platform to actively query for more
		///   advertisement data of type ScanResponse. </summary>
		smActive,
		/// <summary> Scanning mode is passive. </summary>
		smPassive
	} wclBluetoothLeScanningMode;

	/// <summary> The bytes array of the Bluetooth LE advertisement frame raw data. </summary>
	typedef std::vector<unsigned char> wclBluetoothLeAdvertisementFrameRawData;

	/// <summary> Types of the Bluetooth LE advertisement packet. </summary>
	typedef enum
	{
		/// <summary> <para> The advertisement is undirected and indicates that the
		///   device is connectable and scannable. This advertisement type can carry
		///   data. </para>
		///   <para> This corresponds with the <c>ADV_IND</c> type defined in the
		///   Bluetooth LE specifications. </para> </summary>
		atConnectableUndirected,
		/// <summary> <para> The advertisement is directed and indicates that the
		///   device is connectable but not scannable. This advertisement type
		///   cannot carry data. </para>
		///   <para> This corresponds with the <c>ADV_DIRECT_IND</c> type defined in
		///   the Bluetooth LE specifications. </para> </summary>
		atConnectableDirected,
		/// <summary> <para> The advertisement is undirected and indicates that the
		///   device is scannable but not connectable. This advertisement type can
		///   carry data. </para>
		///   <para> This corresponds with the <c>ADV_SCAN_IND</c> type defined in
		///   the Bluetooth LE specifications. </para> </summary>
		atScannableUndirected,
		/// <summary> <para> The advertisement is undirected and indicates that the
		///   device is not connectable nor scannable. This advertisement type can
		///   carry data. </para>
		///   <para> This corresponds with the <c>ADV_NONCONN_IND</c> type defined
		///   in the Bluetooth LE specifications. </para> </summary>
		atNonConnectableUndirected,
		/// <summary> <para> This advertisement is a scan response to a scan request
		///   issued for a scannable advertisement. This advertisement type can
		///   carry data. </para>
		///   <para> This corresponds with the <c>SCAN_RSP</c> type defined in the
		///   Bluetooth LE specifications. </para> </summary>
		atScanResponse,
		/// <summary> This advertisement is a 5.0 extended advertisement. This
		///   advertisement type may have different properties, and is not
		///   necessarily directed, connected, scannable, nor a scan
		///   response. </summary>
		atExtended,
		/// <summary> Unknown advertisement packet type. </summary>
		atUnknown
	} wclBluetoothLeAdvertisementType;

	/// <summary> Flags used to match flags contained inside a Bluetooth LE
	///   advertisement payload. </summary>
	typedef enum
	{
		/// <summary> Bluetooth LE Limited Discoverable Mode. </summary>
		afLimitedDiscoverableMode,
		/// <summary> Bluetooth LE General Discoverable Mode. </summary>
		afGeneralDiscoverableMode,
		/// <summary> Bluetooth BR/EDR not supported. </summary>
		afClassicNotSupported,
		/// <summary> Simultaneous Bluetooth LE and BR/EDR to same device
		///   capable (controller). </summary>
		afDualModeControllerCapable,
		/// <summary> Simultaneous Bluetooth LE and BR/EDR to same device capable
		///   (host). </summary>
		afDualModeHostCapable
	} wclBluetoothLeAdvertisementFlag;
	/// <summary> Set of the
	///   <see cref="wclBluetooth::wclBluetoothLeAdvertisementFlag" />. </summary>
	/// <seealso cref="wclBluetooth::wclBluetoothLeAdvertisementFlag" />
	typedef std::set<wclBluetoothLeAdvertisementFlag> wclBluetoothLeAdvertisementFlags;

	/// <summary> Extended advertisement frame flags. </summary>
	typedef enum
	{
		/// <summary> Indicates whether a Bluetooth Address was omitted from the
		///   received advertisement. </summary>
		efAnonymous,
		/// <summary> Indicates whether the received advertisement is
		///   connectable. </summary>
		efConnectable,
		/// <summary> Indicates whether the received advertisement is
		///   directed. </summary>
		efDirected,
		/// <summary> Indicates whether the received advertisement is
		///   scannable. </summary>
		efScannable,
		/// <summary> Indicates whether the received advertisement is a scan
		///   response. </summary>
		efScanResponse
	} wclBluetoothLeExtendedFrameFlag;
	/// <summary> Set of the
	///   <see cref="TwclBluetoothLeExtendedFrameFlag" />. </summary>
	/// <seealso cref="TwclBluetoothLeExtendedFrameFlag" />
	typedef std::set<wclBluetoothLeExtendedFrameFlag> wclBluetoothLeExtendedFrameFlags;

	/// <summary> The array of Eddystone encoded URL bytes. </summary>
	/// <remarks> For internal use only. </remarks>
	typedef std::vector<unsigned char> wclEddystoneEncodedUrl;

	/// <summary> The enumeration specifies the "Man in the Middle" protection
	///   required for authentication. </summary>
	typedef enum
	{
		/// <summary> Protection against a "Man in the Middle" attack is not
		///   required for authentication. </summary>
		mitmProtectionNotRequired,
		/// <summary> Protection against a "Man in the Middle" attack is required
		///   for authentication. </summary>
		mitmProtectionRequired,
		/// <summary> Protection against a "Man in the Middle" attack is not
		///   required for bonding. </summary>
		mitmProtectionNotRequiredBonding,
		/// <summary> Protection against a "Man in the Middle" attack is required
		///   for bonding. </summary>
		mitmProtectionRequiredBonding,
		/// <summary> Protection against a "Man in the Middle" attack is not
		///   required for General Bonding. </summary>
		mitmProtectionNotRequiredGeneralBonding,
		/// <summary> Protection against a "Man in the Middle" attack is required
		///   for General Bonding. </summary>
		mitmProtectionRequiredGeneralBonding,
		/// <summary> Protection against "Man in the Middle" attack is not
		///   defined. </summary>
		mitmProtectionNotDefined
	} wclBluetoothMitmProtection;

	/// <summary> The Bluetooth LE pairing protection levels. </summary>
	typedef enum
	{
		/// <summary> Use default protection level. </summary>
		pplDefault,
		/// <summary> Pair the device using no levels of protection. (Mode 1,
		///   Level 1). </summary>
		pplNone,
		/// <summary> Pair the device using encryption. (Mode 1,
		///   Level 2). </summary>
		pplEncryption,
		/// <summary> Pair the device using encryption and authentication. (Mode 1,
		///   Level 3). </summary>
		pplEncryptionAndAuthentication
	} wclBluetoothLeProtectionLevel;

	/// <summary> The enumeration defines the input/output capabilities of a
	///   Bluetooth Device. </summary>
	typedef enum
	{
		/// <summary> The Bluetooth device is capable of output via display
		///   only. </summary>
		iocapDisplayOnly,
		/// <summary> The Bluetooth device is capable of output via a display, and
		///   has the additional capability to presenting a yes/no question to the
		///   user. </summary>
		iocapDisplayYesNo,
		/// <summary> The Bluetooth device is capable of input via
		///   keyboard. </summary>
		iocapKeyboardOnly,
		/// <summary> The Bluetooth device is not capable of
		///   input/output. </summary>
		iocapNoInputNoOutput,
		/// <summary> The Bluetooth device is capable of input via
		///   keyboard and of output via display. </summary>
		iocapDisplayKeyboard,
		/// <summary> The input/output capabilities for the Bluetooth device are
		///   undefined. </summary>
		iocapNotDefined
	} wclBluetoothIoCapability;

	/// <summary> The structure contains data used to authenticate prior to
	///   establishing an Out-of-Band device pairing. </summary>
	typedef struct
	{
		/// <summary> A 128-bit cryptographic key used for two-way
		///   authentication. </summary>
		unsigned char C[16];
		/// <summary> A randomly generated number used for one-way authentication.
		///   If this number is not provided by the device initiating the OOB
		///   session, this value is 0. </summary>
		unsigned char R[16];
	} wclBluetoothOobData;

	/// <summary> Describes the Bluetooth address type. </summary>
	typedef enum
	{
		/// <summary> Classic Bluetooth device (public static address). </summary>
		atClassic,
		/// <summary> Public address. </summary>
		atPublic,
		/// <summary> Random address. </summary>
		atRandom,
		/// <summary> Unspecified address. </summary>
		atUnspecified
	} wclBluetoothAddressType;

	/// <summary> The pairing methods. </summary>
	/// <remarks> The pairing method allows your application to force Classic or
	///   BLE pairing when needed. </remarks>
	typedef enum
	{
		/// <summary> Bluetooth Framework automatically selects the pairing
		///   method based on Bluetooth device type. </summary>
		pmAuto,
		/// <summary> Bluetooth Framework forces Classic pairing. </summary>
		pmClassic,
		/// <summary> Bluetooth Framework forces LE pairing. </summary>
		pmLe
	} wclBluetoothPairingMethod;

	/// <summary> The structure represents a single Bluetooth LE advertisement
	///   data section. </summary>
	/// <remarks> This structure is used internally by the Bluetooth LE
	///   advertiser. </remarks>
	typedef struct
	{
		/// <summary> The manufacturer ID as defined in the Bluetooth SIG
		///   Assigned Numbers. </summary>
		/// <remarks> This member is valid only when the advertisement data type is
		///   <c>LE_GAP_AD_TYPE_MANUFACTURER</c>. </remarks>
		unsigned short CompanyId;
		/// <summary> The advertisement data type. </summary>
		unsigned char DataType;
		/// <summary> The advertisement data. </summary>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData Data;
	} wclBluetoothLeAdvertisementFrame;
	/// <summary> The array of the Bluetooth LE advertisement data
	///   sections. </summary>
	/// <seealso cref="wclBluetoothLeAdvertisementFrame" />
	typedef std::vector<wclBluetoothLeAdvertisementFrame> wclBluetoothLeAdvertisementFrames;

	/// <summary> The structure describes the current Bluetooth LE GATT connection
	///   parameters. </summary>
	typedef struct
	{
		/// <summary> The connection interval. </summary>
		/// <remarks> The connection interval is defined as 1.25ms increments,
		///   ranging from 6 to 3200. Time(ms) = Interval * 1.25ms. </remarks>
		unsigned short Interval;
		/// <summary> The connection latency. </summary>
		/// <remarks> The connection latency is defined in connection events,
		///   ranging from 0 to 499. </remarks>
		unsigned short Latency;
		/// <summary> The connection link supervision timeout. </summary>
		/// <remarks> The connection link supervision timeout is defined in 10ms
		///   increments, ranging from 10 to 3200.
		///   Time(ms) = LinkTimeout * 10ms. </remarks>
		unsigned short LinkTimeout;
	} wclBluetoothLeConnectionParameters;

	/// <summary> The enumeration defines the Bluetooth LE GATT preferred
	///   connection parameters. </summary>
	typedef enum
	{
		/// <summary> The balanced set of connection parameters, offering a balance
		///   between throughput and power usage. </summary>
		ppBalanced,
		/// <summary> The more power-efficient set of connection parameters.
		///   Optimized for power usage at the expense of throughput. Also allows
		///   for more simultaneous connections to other Bluetooth
		///   devices. </summary>
		ppPowerOptimized,
		/// <summary> The more aggressive set of connection parameters, optimized
		///   for faster throughput at the expense of power usage. Also reduces the
		///   number of simultaneous connections that can be made to other Bluetooth
		///   devices. </summary>
		ppThroughputOptimized
	} wclBluetoothLeConnectionParametersType;

	/// <summary> The structure represents the Bluetooth LE GATT preferred connection
	///   parameters. </summary>
	typedef struct
	{
		/// <summary> The minimum connection interval. </summary>
		/// <remarks> The connection interval is defined as 1.25ms increments,
		///   ranging from 6 to 3200. Time(ms) = Interval * 1.25ms. </remarks>
		unsigned short MinInterval;
		/// <summary> The maximum connection interval. </summary>
		/// <remarks> The connection interval is defined as 1.25ms increments,
		///   ranging from 6 to 3200. Time(ms) = Interval * 1.25ms. </remarks>
		unsigned short MaxInterval;
		/// <summary> The connection latency. </summary>
		/// <remarks> The connection latency is defined in connection events,
		///   ranging from 0 to 499. </remarks>
		unsigned short Latency;
		/// <summary> The connection link supervision timeout. </summary>
		/// <remarks> The connection link supervision timeout is defined in 10ms
		///   increments, ranging from 10 to 3200.
		///   Time(ms) = LinkTimeout * 10ms. </remarks>
		unsigned short LinkTimeout;
	} wclBluetoothLeConnectionParametersValue;

	/// <summary> Represents a LE connection PHY information. </summary>
	typedef struct
	{
		/// <summary> Indicates whether or not the Bluetooth LE physical layer (PHY)
		///   is LE Coded. </summary>
		bool IsCoded;
		/// <summary> Indicates whether or not the Bluetooth LE physical layer (PHY)
		///   is (uncoded) LE 1M. </summary>
		bool IsUncoded1MPhy;
		/// <summary> Indicates whether or not the Bluetooth LE physical layer (PHY)
		///   is (uncoded) LE 2M. </summary>
		bool IsUncoded2MPhy;
	} wclBluetoothLeConnectionPhyInfo;

	/// <summary> Represents the Bluetooth LE physical layer (PHY)
	///   information. </summary>
	typedef struct
	{
		/// <summary> The info about the Bluetooth LE physical layer (PHY) for
		///   receive. </summary>
		/// <seealso cref="wclBluetoothLeConnectionPhyInfo" />
		wclBluetoothLeConnectionPhyInfo Receive;
		/// <summary> The info about the Bluetooth LE physical layer (PHY) for
		///   transmit. </summary>
		/// <seealso cref="wclBluetoothLeConnectionPhyInfo" />
		wclBluetoothLeConnectionPhyInfo Transmit;
	} wclBluetoothLeConnectionPhy;

	/// <summary> The record contains basic information about Bluetooth LE
	///   advertisement frame. </summary>
	typedef struct
	{
		/// <summary> The Bluetooth LE advertiser's MAC address. </summary>
		__int64 Address;
		/// <summary> The frame's timestamp in Universal Time format. </summary>
		__int64 Timestamp;
		/// <summary> The measured RSSI value in dBm at range between -100 dBm and
		///   +20 dBm at 1 dBm resolution. </summary>
		char Rssi;
	} wclBluetoothLeAdvertisementInfo;

	/// <summary> The record contains Apple Airdrop Bluetooth LE advertisement
	///   data. </summary>
	typedef struct
	{
		/// <summary> Message prefix. </summary>
		unsigned char Prefix[8];
		/// <summary> Version. </summary>
		unsigned char Version;
		/// <summary> Truncated SHA256 hash of apple ID. </summary>
		unsigned short AppleId;
		/// <summary> Truncated SHA256 hash of phone number. </summary>
		unsigned short PhoneNumber;
		/// <summary> Truncated SHA256 hash of E-Mail. </summary>
		unsigned short Email;
		/// <summary> Truncated SHA256 hash of E-Mail 2. </summary>
		unsigned short Email2;
		/// <summary> Suffix. </summary>
		unsigned char Suffix;
	} wclBluetoothLeAppleAirdropFrameData;
	
	/// <summary> The record contains Apple Airplay source Bluetooth LE
	///   advertisement data. </summary>
	typedef struct
	{
		/// <summary> The data byte. </summary>
		unsigned char Data;
	} wclBluetoothLeAppleAirplaySourceFrameData;
	
	/// <summary> The record contains Apple Airplay target Bluetooth LE
	///   advertisement data. </summary>
	typedef struct
	{
		/// <summary> AirPlay flags. </summary>
		unsigned char Flags;
		/// <summary> AirPlay configuration seed. </summary>
		unsigned char Seed;
		/// <summary> IPv4 address. </summary>
		unsigned long Address;
	} wclBluetoothLeAppleAirplayTargetFrameData;

	/// <summary> The record contains Apple Airprint Bluetooth LE advertisement
	///   data. </summary>
	typedef struct
	{
		/// <summary> Address type. </summary>
		unsigned char AddressType;
		/// <summary> Path resource type. </summary>
		unsigned char ResourceType;
		/// <summary> Security type. </summary>
		unsigned char SecurityType;
		/// <summary> QID or TCP port. </summary>
		unsigned short Port;
		/// <summary> IPv4 or IPv6 address. </summary>
		unsigned char Address[16];
		/// <summary> Measured Power. </summary>
		char Power;
	} wclBluetoothLeAppleAirprintFrameData;

	/// <summary> The record contains Apple Find My Bluetooth LE advertisement
	///   data. </summary>
	/// <remarks> The Find My message is broadcast by apple devices that are
	///   marked as lost by the user or that do not have internet connectivity.
	///   This message includes the x-coordinate of the currently active elliptic
	///   curve public key for the disconnected device. Because BLE advertisements
	///   are limited to 31 total bytes, some of which are used to encode the
	///   company identifier and other metadata, Apple encodes part of the key in
	///   the BLE Advertising Address, with the remaining public key included in
	///   the advertisement payload. When a nearby internet-connected apple device
	///   sees this BLE message, it sends a location report using its own GPS to
	///   Apple Servers. This location report is encrypted with the advertised
	///   public key so that only the device owner can decrypt the location
	///   report. The owner of the lost device will then see the lost device's
	///   location appear on their Find My app.  </remarks>
	typedef struct
	{
		/// <summary> <para> Find My status: </para>
		///   <para> 0x00 - Owner did not connect within key rotation
		///                 period (15 min.) </para>
		///   <para> 0x24 - Owner connected with key roation period,
		///                 Battery Full </para>
		///   <para> 0x64 - Owner connected with key roation period,
		///                 Battery Medium </para>
		///   <para> 0xA4 - Owner connected with key roation period,
		///                 Battery Low </para>
		///   <para> 0xE4 - Owner connected with key roation period,
		///                 Battery Critically Low </para> </summary>
		unsigned char Status;
		/// <summary> Public key. </summary>
		unsigned char Key[22];
		/// <summary> <para> Public key bits: </para>
		///   <para> 0x00 - bits 6 and 7 not set in public key </para>
		///   <para> 0x01 - bit 6 set in public key </para>
		///   <para> 0x02 - bit 7 set in public key </para>
		///   <para> 0x03 - bits 6 and 7 set in public key </para> </summary>
		unsigned char KeyBits;
		/// <summary> Byte 5 of BT_ADDR of the primary key. </summary>
		unsigned char Hint;
	} wclBluetoothLeAppleFindMyFrameData;

	/// <summary> The record contains Apple Handoff Bluetooth LE advertisement
	///   data. </summary>
	/// <remarks> Handoff Messages enable users to start tasks on one iOS or macOS
	///   device and finish them on another. Handoff is supported with the Apple
	///   Calendar, Contacts, Mail, Maps, Messages, Notes, Reminders, Safari,
	///   Pages, Numbers, Keynote applications, as well as certain third-party
	///   applications that are designed to support Handoff by their
	///   developers. </remarks>
	typedef struct
	{
		/// <summary> A clipboard status. Indicates copy/cut operation. </summary>
		bool Clipboard;
		/// <summary> Sequence number. </summary>
		unsigned short Sequence;
		/// <summary> AES-GCM Auth Tag. </summary>
		unsigned char AuthTag;
		/// <summary> Encrypted Handoff data. </summary>
		unsigned char Data[10];
	} wclBluetoothLeAppleHandoffFrameData;

	/// <summary> The record contains Apple Hey Siri Bluetooth LE
	///   advertisement data. </summary>
	/// <remarks> 'Hey Siri' messages are emitted by a device when the voice
	///   assistant Siri is used. Of note, a perceptual hash of the voice command
	///   is included in the packet. </remarks>
	typedef struct
	{
		/// <summary> Perceptual Hash. </summary>
		unsigned short Hash;
		/// <summary> Signal-to-Noise Ration. </summary>
		char Snr;
		/// <summary> <para> Wrist confidence level: </para>
		///   <para> 0x03 - Not on Wrist </para>
		///   <para> 0x1F - Wrist detection disabled </para>
		///   <para> 0x3F - On Wrist </para> </summary>
		unsigned char Confidence;
		/// <summary> <para> Device Class: </para>
		///   <para> 0x0002 - iPhone </para>
		///   <para> 0x0003 - iPad </para>
		///   <para> 0x0007 - HomePod </para>
		///   <para> 0x0009 - MacBook </para>
		///   <para> 0x000A - Watch </para> </summary>
		unsigned short DeviceClass;
		/// <summary> Random byte. </summary>
		unsigned char Rand;
	} wclBluetoothLeAppleHeySiriFrameData;

	/// <summary> The record contains Apple Home Kit Bluetooth LE advertisement
	///   data. </summary>
	typedef struct
	{
		/// <summary> Status flags. </summary>
		unsigned char Status;
		/// <summary> A device ID. </summary>
		unsigned char DeviceId[6];
		/// <summary> <para> HomeKit device category: </para>
		///   <para> 0x0000 - Unknown </para>
		///   <para> 0x0001 - Other </para>
		///   <para> 0x0002 - Bridge </para>
		///   <para> 0x0003 - Fan </para>
		///   <para> 0x0004 - Garage Door Opener </para>
		///   <para> 0x0005 - Lightbulb </para>
		///   <para> 0x0006 - Door Lock </para>
		///   <para> 0x0007 - Outlet </para>
		///   <para> 0x0008 - Switch </para>
		///   <para> 0x0009 - Thermostat </para>
		///   <para> 0x000A - Sensor </para>
		///   <para> 0x000B - Security System </para>
		///   <para> 0x000C - Door </para>
		///   <para> 0x000D - Window </para>
		///   <para> 0x000E - Window Covering </para>
		///   <para> 0x000F - Programmable Switch </para>
		///   <para> 0x0010 - Range Extender </para>
		///   <para> 0x0011 - IP Camera </para>
		///   <para> 0x0012 - Video Doorbell </para>
		///   <para> 0x0013 - Air Purifier </para>
		///   <para> 0x0014 - Heater </para>
		///   <para> 0x0015 - Air Conditioner </para>
		///   <para> 0x0016 - Humidifier </para>
		///   <para> 0x0017 - Dehumidifier </para>
		///   <para> 0x001C - Sprinklers </para>
		///   <para> 0x001D - Faucets </para>
		///   <para> 0x001E - Shower Systems </para> </summary>
		unsigned short Category;
		/// <summary> State number. </summary>
		unsigned short StateNumber;
		/// <summary> Config number. </summary>
		unsigned char ConfigNumber;
		/// <summary> Compatible version. </summary>
		unsigned char Version;
	} wclBluetoothLeAppleHomeKitFrameData;

	/// <summary> The record contains Apple iBeacon Bluetooth LE advertisement
	///   data. </summary>
	typedef struct
	{
		/// <summary> The beacon's UUID. </summary>
		GUID Uuid;
		/// <summary> The beacon's Minor value. </summary>
		unsigned short Minor;
		/// <summary> The beacon's Major value. </summary>
		unsigned short Major;
		/// <summary> The beacon's RSSI value in dBm at range between -100 dBm and
		///   +20 dBm at 1 dBm resolution measured at 1 meter distance. </summary>
		char TxRssi;
	} wclBluetoothLeAppleiBeaconFrameData;

	/// <summary> The record contains Apple Magic Switch Bluetooth LE
	///   advertisement data. </summary>
	typedef struct
	{
		/// <summary> Message data. </summary>
		unsigned short Data;
		/// <summary> <para> Wrist confidence level: </para>
		///   <para> 0x03 - Not on Wrist </para>
		///   <para> 0x1F - Wrist detection disabled </para>
		///   <para> 0x3F - On Wrist </para> </summary>
		unsigned char Confidence;
	} wclBluetoothLeAppleMagicSwitchFrameData;

	/// <summary> The record contains Apple Nearby Action Bluetooth LE
	///   advertisement data. </summary>
	typedef struct
	{
		/// <summary> Action flags. </summary>
		unsigned char Flags;
		/// <summary> <para> Action type. Known values: </para>
		///   <para> 0x01 - Apple TV Setup </para>
		///   <para> 0x04 - Mobile Backup </para>
		///   <para> 0x05 - Watch Setup </para>
		///   <para> 0x06 - Apple TV Pair </para>
		///   <para> 0x07 - Internet Relay </para>
		///   <para> 0x08 - WiFi Password </para>
		///   <para> 0x09 - iOS Setup </para>
		///   <para> 0x0A - Repair </para>
		///   <para> 0x0B - Speaker Setupd </para>
		///   <para> 0x0C - Apple Pay </para>
		///   <para> 0x0D - Whole Home Audio Setup </para>
		///   <para> 0x0E - Developer Tools Pairing Request </para>
		///   <para> 0x0F - Answered Call </para>
		///   <para> 0x10 - Ended Call </para>
		///   <para> 0x11 - DD Ping </para>
		///   <para> 0x12 - DD Pong </para>
		///   <para> 0x13 - Remote Auto Fill </para>
		///   <para> 0x14 - Companion Link Proximity </para>
		///   <para> 0x15 - Remote Management </para>
		///   <para> 0x16 - Remote Auto Fill Pong </para>
		///   <para> 0x17 - Remote Display </para> </summary>
		unsigned char Action;
		/// <summary> Authentication tag. </summary>
		unsigned long Tag;
		/// <summary> <para> Action device class. Known values: </para>
		///   <para> 0x02 - iPhone </para>
		///   <para> 0x04 - iPod </para>
		///   <para> 0x06 - iPad </para>
		///   <para> 0x08 - Audio accessory (HomePod) </para>
		///   <para> 0x0A - Mac </para>
		///   <para> 0x0C - AppleTV </para>
		///   <para> 0x0E - Watch </para> </summary>
		unsigned char Device;
		/// <summary> Action parameters. The structure of the Nearby Action
		///   Parameters field is dependent upon the Action Type value. </summary>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData Params;
	} wclBluetoothLeAppleNearbyActionFrameData;

	/// <summary> The record contains Apple Nearby Info Bluetooth LE advertisement
	///   data. </summary>
	typedef struct
	{
		/// <summary> <para> Status flags. Used as a bitmask, more than one may be
		///   enabled at any time. Known values: </para>
		///   <para> 0x01 - Indicates if this is the primary iCloud account
		///                 device </para>
		///   <para> 0x04 - Indicates whether AirDrop Receiving is
		///                 enabled </para> </summary>
		unsigned char Status;
		/// <summary> <para> Action flags. Indicates the action state of the
		///   device. Known values: </para>
		///   <para> 0x00 - Activity level unknown </para>
		///   <para> 0x01 - Activity reporting disabled </para>
		///   <para> 0x03 - Idle user </para>
		///   <para> 0x05 - Audio playing while screen locked </para>
		///   <para> 0x07 - Active user (screen on) </para>
		///   <para> 0x09 - Screen on with video playing </para>
		///   <para> 0x0A - Watch on wrist and unlocked </para>
		///   <para> 0x0B - Recent user interaction </para>
		///   <para> 0x0D - User is driving a vehicle </para>
		///   <para> 0x0E - Phone or Facetime Call </para> </summary>
		unsigned char Action;
		/// <summary> <para> Indicates current device state. Used as a bitmask, more
		///   than one may be enabled at any time. Known values: </para>
		///   <para> 0x01 - Indicates if AirPods are connected and the screen is
		///                 on </para>
		///   <para> 0x02 - Indicates if the Authentication Tag is 4 bytes </para>
		///   <para> 0x04 - Indicates whether WiFi is on or off </para>
		///   <para> 0x10 - Indicates whether the Authentication Tag is present or
		///                 not </para>
		///   <para> 0x20 - Indicates whether the Apple Watch is locked or not </para>
		///   <para> 0x40 - Indicates whether Auto Unlock on the Apple Watch is
		///                 enabled or not </para>
		///   <para> 0x80 - Indicates whether Auto Unlock is enabled or
		///                 not </para> </summary>
		unsigned char Flags;
		/// <summary> Authentication tag. </summary>
		unsigned long Tag;
	} wclBluetoothLeAppleNearbyInfoFrameData;

	/// <summary> The record contains Apple Proximity Pairing Bluetooth LE
	///   advertisement data. </summary>
	/// <remarks> Proximity Pairing is an Apple technology that is used to pair
	///   AirPods and iOS devices. These messages carry unencrypted information
	///   detailing the status, model, and color of the audio device as well as
	///   the power and charging status. </remarks>
	typedef struct
	{
		/// <summary> Proximity Pairing message prefix. </summary>
		unsigned char Prefix;
		/// <summary> <para> Device model: </para>
		///   <para> 0x2002 - AirPods </para>
		///   <para> 0x2003 - Powerbeats 3 </para>
		///   <para> 0x2005 - BeatsX </para>
		///   <para> 0x2006 - Beats Solo 3 </para>
		///   <para> 0x2007 - Beats Studio 3 </para>
		///   <para> 0x2009 - Beats Studio 3 </para>
		///   <para> 0x200A - AirPods Max </para>
		///   <para> 0x200B - Powerbeats Pro </para>
		///   <para> 0x200C - Beats Solo Pro </para>
		///   <para> 0x200D - Powerbeats 4 </para>
		///   <para> 0x200E - AirPods Pro </para>
		///   <para> 0x200F - AirPods 2 </para>
		///   <para> 0x2010 - Beats Flex </para>
		///   <para> 0x2011 - Beats Studio Buds </para>
		///   <para> 0x2012 - Beats Fit Pro </para>
		///   <para> 0x2013 - AirPods 3 </para>
		///   <para> 0x2014 - AirPods Pro 2 </para> </summary>
		unsigned short DeviceModel;
		/// <summary> <para> Device status: </para>
		///   <para> 0x01 - AirPods: Both out of case, not in ear </para>
		///   <para> 0x02 - Right in ear, Left in case </para>
		///   <para> 0x03 - AirPods: Right in ear, Left out of case </para>
		///   <para> 0x0B - Both AirPods in ear </para>
		///   <para> 0x11 - AirPods: Right out of case, Left in case </para>
		///   <para> 0x13 - AirPods: Right in ear, Left in case </para>
		///   <para> 0x21 - Both taken out of ears, Pause Audio </para>
		///   <para> 0x22 - Left in ear, Right in case </para>
		///   <para> 0x23 - AirPods: Left in ear, Right out of case </para>
		///   <para> 0x2B - Both AirPods in ear </para>
		///   <para> 0x31 - AirPods: Left out of case, Right in case </para>
		///   <para> 0x33 - AirPods: Left in ear, Right in case </para>
		///   <para> 0x51 - Case: Left out of case, Right in case </para>
		///   <para> 0x53 - Case: Left in ear, Right in case </para>
		///   <para> 0x55 - Case: Both AirPods in case </para>
		///   <para> 0x71 - Case: Right out of case, Left in case </para>
		///   <para> 0x73 - Case: Right in ear, Left in case </para>
		///   <para> 0x75 - Case: Both AirPods in case </para> </summary>
		unsigned char Status;
		/// <summary> Battery of left pod. </summary>
		unsigned char LeftBattery;
		/// <summary> Battery of right pod. </summary>
		unsigned char RightBattery;
		/// <summary> Whether the case is charging. </summary>
		bool CaseCharging;
		/// <summary> Whether right pod is charging. </summary>
		bool RightCharging;
		/// <summary> Whether left pod is charging. </summary>
		bool LeftCharging;
		/// <summary> Case battery. </summary>
		unsigned char CaseBattery;
		/// <summary> Lid open counter. </summary>
		unsigned char Counter;
		/// <summary> <para> Device color: </para>
		///   <para> 0x00 - White </para>
		///   <para> 0x01 - Black </para>
		///   <para> 0x02 - Red </para>
		///   <para> 0x03 - Blue </para>
		///   <para> 0x04 - Pink </para>
		///   <para> 0x05 - Gray </para>
		///   <para> 0x06 - Silver </para>
		///   <para> 0x07 - Gold </para>
		///   <para> 0x08 - Rose Gold </para>
		///   <para> 0x09 - Space Gray </para>
		///   <para> 0x0A - Dark Blue </para>
		///   <para> 0x0B - Light Blue </para>
		///   <para> 0x0C - Yellow </para> </summary>
		unsigned char Color;
		/// <summary> Proximity Pairing message suffix. </summary>
		unsigned char Suffix;
		/// <summary> Encrypted data. </summary>
		unsigned char Data[16];
	} wclBluetoothLeAppleProximityPairingFrameData;

	/// <summary> The record contains Apple Tethering Source Bluetooth LE
	///   advertisement data. </summary>
	/// <remarks> The Tethering Source Continuity message is broadcast in response
	///   to a Tethering Target message generated by another device (typically a
	///   MacBook) linked to the same iCloud account as the iPhone or iPad that is
	///   to be used as a hotspot. The Tethering Source message contains
	///   information pertaining to the battery life, and type and quality of
	///   cellular service the hotspot device has. Some of this information is
	///   listed in the 'available WiFi networks' listed on the Tethering Target
	///   device when searching for the hotspot. </remarks>
	typedef struct
	{
		/// <summary> Version. </summary>
		unsigned char Version;
		/// <summary> Flags. </summary>
		unsigned char Flags;
		/// <summary> Battery status. </summary>
		unsigned char Battery;
		/// <summary> <para> Cell service type: </para>
		///   <para> 0x0000 - 4G (GSM) </para>
		///   <para> 0x0001 - 1xRTT </para>
		///   <para> 0x0002 - GPRS </para>
		///   <para> 0x0003 - EDGE </para>
		///   <para> 0x0004 - 3G (EV-DO) </para>
		///   <para> 0x0005 - 3G </para>
		///   <para> 0x0006 - 4G </para>
		///   <para> 0x0007 - LTE </para> </summary>
		unsigned short CellType;
		/// <summary> Cell Service Quality (Bars). </summary>
		unsigned char Bars;
	} wclBluetoothLeAppleTetheringSourceFrameData;
	
	/// <summary> The record contains Apple Tethering Target Bluetooth LE
	///   advertisement data. </summary>
	/// <remarks> The Tethering Target Continuity message is broadcast in order to
	///   elicit a response from a device to be used as a hotspot, which will
	///   reply with a Tethering Source message. In a typical usage example, a
	///   user clicks on the menu button that displays the list of available WiFi
	///   networks on a MacBook. This action generates a stream of Tethering
	///   Target messages that continue for the duration of the period in which
	///   the available networks tab is opened. In response, a hotspot-capable
	///   device linked to the same iCloud account (an iPhone or iPad with
	///   cellular connection) responds with Tethering Source messages to
	///   advertise its presence and connection capabilities, including battery
	///   status, type of cellular connection, and strength of cellular
	///   signal.  </remarks>
	typedef struct
	{
		/// <summary> iCloud ID. </summary>
		/// <remarks> Derived from user's iCloud DSID. Rotates every 24 hours.
		///   Constant across all devices on same iCloud Account </remarks>
		unsigned long Id;
	} wclBluetoothLeAppleTetheringTargetFrameData;

	/// <summary> The record contains an unknown Apple specified Bluetooth LE
	///   advertisement data. </summary>
	typedef struct
	{
		/// <summary> An Apple message ID. </summary>
		unsigned char Id;
		/// <summary> An Apple message payload. </summary>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData Payload;
	} wclBluetoothLeAppleUnknownFrameData;
	
	/// <summary> The Microsoft CDP Beacon device type. </summary>
	typedef enum
	{
		/// <summary> Xbox One. </summary>
		dtXboxOne = 1,
		/// <summary> Apple iPhone. </summary>
		dtiPhone = 6,
		/// <summary> Apple iPad. </summary>
		dtiPad = 7,
		/// <summary> Android device. </summary>
		dtAndroid = 8,
		/// <summary> Windows 10 Desktop. </summary>
		dtWindowsDesktop = 9,
		/// <summary> Windows 10 Phone. </summary>
		dtWindowsPhone = 11,
		/// <summary> Linux device. </summary>
		dtLinux = 12,
		/// <summary> Windows IoT. </summary>
		dtWindowsIoT = 13,
		/// <summary> Surface Hub. </summary>
		dtSurfaceHub = 14,
		/// <summary> Windows laptop. </summary>
		dtWindowsLaptop = 15,
		/// <summary> Windows tablet. </summary>
		dtWindowsTablet = 16
	} wclBluetoothLeCdpBeaconDeviceType;
	
	/// <summary> The Microsoft CDP Beacon scenario type. </summary>
	typedef enum
	{
		/// <summary> Bluetooth scenario. </summary>
		stBluetooth = 1
	} wclBluetoothLeCdpBeaconScenarioType;
	
	/// <summary> The Microsoft CDP Beacon extended device status. </summary>
	typedef enum
	{
		/// <summary> Hosted by remote session. </summary>
		edsRemoteSessionsHosted,
		/// <summary> Indicates the device does not have session hosting status
		///   available. </summary>
		edsRemoteSessionsNotHosted,
		/// <summary> Indicates the device supports NearShare if the user is the
		///   same for the other device. </summary>
		edsNearShareAuthPolicySameUser,
		/// <summary> Indicates the device supports NearShare. </summary>
		edsNearShareAuthPolicyPermissive
	} wclBluetoothLeCdpBeaconExtendedDeviceStatus;
	/// <summary> The Microsoft CDP Beacon extended device statuses
	///   set. </summary>
	/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatus" />
	typedef std::set<wclBluetoothLeCdpBeaconExtendedDeviceStatus> wclBluetoothLeCdpBeaconExtendedDeviceStatuses;
	
	/// <summary> The Microsoft CDP Beacon salt. </summary>
	typedef std::vector<unsigned char> wclBluetoothLeCdpBeaconSalt;
	/// <summary> The Microsoft CDP Beacon SHA256 Hash of Salt plus Device
	///   Thumbprint. </summary>
	typedef std::vector<unsigned char> wclBluetoothLeCdpBeaconHash;
	
	/// <summary> The structure represents a Wii Remote accelerometer calibration
	///   data. </summary>
	typedef struct
	{
		/// <summary> A minimum X value. </summary>
		unsigned short MinX;
		/// <summary> A minimum Y value. </summary>
		unsigned short MinY;
		/// <summary> A minimum Z value. </summary>
		unsigned short MinZ;
		/// <summary> A maximum X value. </summary>
		unsigned short MaxX;
		/// <summary> A maximum Y value. </summary>
		unsigned short MaxY;
		/// <summary> A maximum Z value. </summary>
		unsigned short MaxZ;
	} wclWiiRemoteAccelCalibration;

	/// <summary> The structure contains the Wii Remote LEDs states. </summary>
	typedef struct
	{
		/// <summary> <c>True</c> if the first LED is turned ON. </summary>
		bool Led1;
		/// <summary> <c>True</c> if the second LED is turned ON. </summary>
		bool Led2;
		/// <summary> <c>True</c> if the third LED is turned ON. </summary>
		bool Led3;
		/// <summary> <c>True</c> if the fourth LED is turned ON. </summary>
		bool Led4;
	} wclWiiRemoteLeds;

	/// <summary> The Wii Remote IR sensor modes. </summary>
	typedef enum
	{
		/// <summary> The IR sensor is turned off. </summary>
		wiiIrOff,
		/// <summary> The basic mode. </summary>
		wiiIrBasicMode,
		/// <summary> The extended mode. </summary>
		wiiIrExtendedMode,
		/// <summary> The full mode. </summary>
		wiiIrFullMode
	} wclWiiRemoteIrMode;

	/// <summary> The Wii Remote IR sensor sensitivity. </summary>
	typedef enum
	{
		/// <summary> The IR sensor is turned off. </summary>
		wiiIrLevelOff,
		/// <summary> The Level 1. </summary>
		wiiIrLevel1,
		/// <summary> The Level 2. </summary>
		wiiIrLevel2,
		/// <summary> The Level 3. </summary>
		wiiIrLevel3,
		/// <summary> The Level 4. </summary>
		wiiIrLevel4,
		/// <summary> The Level 5. </summary>
		wiiIrLevel5,
		/// <summary> The maximum sensitivity. </summary>
		wiiIrLevelMax
	} wclWiiRemoteIrSensitivity;

	/// <summary> The Wii Remote extension types. </summary>
	typedef enum
	{
		/// <summary> No extension is connected. </summary>
		wiiNoExtension,
		/// <summary> The Nunchuk extension. </summary>
		wiiNunchuk,
		/// <summary> The Classic Controller extension. </summary>
		wiiClassicController,
		/// <summary> The Guitar extension. </summary>
		wiiGuitar,
		/// <summary> The Drums extension. </summary>
		wiiDrums,
		/// <summary> The Balance Board extension. </summary>
		wiiBalanceBoard
	} wclWiiRemoteExtension;

	/// <summary> The structure contains information about the Wii Remote
	///   buttons. </summary>
	typedef struct
	{
		/// <summary> <c>True</c> if the "A" button is pressed. </summary>
		bool A;
		/// <summary> <c>True</c> if the "B" button is pressed. </summary>
		bool B;
		/// <summary> <c>True</c> if the "+" button is pressed. </summary>
		bool Plus;
		/// <summary> <c>True</c> if the "Home" button is pressed. </summary>
		bool Home;
		/// <summary> <c>True</c> if the "-" button is pressed. </summary>
		bool Minus;
		/// <summary> The "1" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool One;
		/// <summary> The "2" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Two;
		/// <summary> The "Up" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Up;
		/// <summary> The "Down" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Down;
		/// <summary> The "Left" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Left;
		/// <summary> The "Right" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Right;
	} wclWiiRemoteButtons;

	/// <summary> The structure represents a 3D coordinate. </summary>
	typedef struct
	{
		/// <summary> An X coordinate. </summary>
		unsigned short X;
		/// <summary> An Y coordinate. </summary>
		unsigned short Y;
		/// <summary> A Z coordinate. </summary>
		unsigned short Z;
	} wclWiiRemote3D;

	/// <summary> The structure describes a Wii Remote accelerometer
	///   data. </summary>
	typedef struct
	{
		/// <summary> Calibration data. </summary>
		/// <seealso cref="wclWiiRemoteAccelCalibration" />
		wclWiiRemoteAccelCalibration Calibration;
		/// <summary> Values. </summary>
		/// <seealso cref="wclWiiRemote3D" />
		wclWiiRemote3D Values;
	} wclWiiRemoteAccel;

	/// <summary> The structure represents a 2D coordinate </summary>
	typedef struct
	{
		/// <summary> An X coordinate. </summary>
		unsigned short X;
		/// <summary> An Y coordinate. </summary>
		unsigned short Y;
	} wclWiiRemote2D;

	/// <summary> The structure contains a single IR sensor values. </summary>
	typedef struct
	{
		/// <summary> The IR sensor coordinates. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D Position;
		/// <summary> Indicates the size of the detected object. </summary>
		unsigned char Size;
		/// <summary> <c>True</c> is the object detected. </summary>
		bool Found;
	} wclWiiRemoteIrSensor;

	/// <summary> The structure contains the Wii Remote IR sensors
	///   values. </summary>
	typedef struct
	{
		/// <summary> The IR sensor mode. </summary>
		/// <seealso cref="wclWiiRemoteIrMode" />
		wclWiiRemoteIrMode Mode;
		/// <summary> The IR sensitivity. </summary>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		wclWiiRemoteIrSensitivity Sensitivity;
		/// <summary> The array of the IR sensors. </summary>
		/// <seealso cref="wclWiiRemoteIrSensor" />
		wclWiiRemoteIrSensor Sensors[4];
	} wclWiiRemoteIrSensors;

	/// <summary> The structure represents a Wii Remote Nunchuk extension
	///   accelerometer calibration data. </summary>
	typedef struct
	{
		/// <summary> The nunchuk accelerometer calibration data. </summary>
		/// <seealso cref="wclWiiRemoteAccelCalibration" />
		wclWiiRemoteAccelCalibration Accel;
		/// <summary>The joystick minimum X value. </summary>
		unsigned char MinX;
		/// <summary>The joystick center X value. </summary>
		unsigned char MidX;
		/// <summary>The joystick maximum X value. </summary>
		unsigned char MaxX;
		/// <summary>The joystick minimum Y value. </summary>
		unsigned char MinY;
		/// <summary>The joystick center Y value. </summary>
		unsigned char MidY;
		/// <summary>The joystick maximum Y value. </summary>
		unsigned char MaxY;
	} wclWiiRemoteNunchukCalibration;

	/// <summary> The structure describes a Wii Remote Nunchuk
	///   extension. </summary>
	typedef struct
	{
		/// <summary> The Nunchuk extension calibration values. </summary>
		/// <seealso cref="wclWiiRemoteNunchukCalibration" />
		wclWiiRemoteNunchukCalibration Calibration;
		/// <summary> The Nunchuk extension accelerometer values. </summary>
		/// <seealso cref="wclWiiRemoteAccel" />
		wclWiiRemoteAccel Accel;
		/// <summary> The Nunchuk extension joystick calculated values. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D Joystick;
		/// <summary> The Nunchuk extension "C" button state. <c>True</c> if
		///   button is pressed. </summary>
		bool C;
		/// <summary> The Nunchuk extension "Z" button state. <c>True</c> if
		///   button is pressed. </summary>
		bool Z;
	} wclWiiRemoteNunchuk;

	/// <summary> The structure contains information about the Wii Remote Classic
	///   Controller extension buttons. </summary>
	typedef struct
	{
		/// <summary> The "A" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool A;
		/// <summary> The "B" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool B;
		/// <summary> The "+" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Plus;
		/// <summary> The "Home" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Home;
		/// <summary> The "-" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Minus;
		/// <summary> The "Up" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Up;
		/// <summary> The "Down" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Down;
		/// <summary> The "Left" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Left;
		/// <summary> The "Right" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Right;
		/// <summary> The "X" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool X;
		/// <summary> The "Y" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Y;
		/// <summary> The "ZL" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool ZL;
		/// <summary> The "ZR" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool ZR;
		/// <summary> The "L" (Left Trigger) button state. <c>True</c> if the button
		///   is pressed. </summary>
		bool L;
		/// <summary> The "R" (Right Trigger) button state. <c>True</c> if the
		///   button is pressed. </summary>
		bool R;
	} wclWiiRemoteClassicControllerButtons;

	/// <summary> The structure represents a Wii Remote Classic Controller
	///   accelerometer calibration data. </summary>
	typedef struct
	{
		/// <summary> The left joystick minimum X value. </summary>
		unsigned char LeftMinX;
		/// <summary> The left joystick center X value. </summary>
		unsigned char LeftMidX;
		/// <summary> The left joystick maximum X value. </summary>
		unsigned char LeftMaxX;
		/// <summary> The left joystick minimum Y value. </summary>
		unsigned char LeftMinY;
		/// <summary> The left joystick center Y value. </summary>
		unsigned char LeftMidY;
		/// <summary> The left joystick maximum Y value. </summary>
		unsigned char LeftMaxY;
		/// <summary> The right joystick minimum X value. </summary>
		unsigned char RightMinX;
		/// <summary> The right joystick center X value. </summary>
		unsigned char RightMidX;
		/// <summary> The right joystick maximum X value. </summary>
		unsigned char RightMaxX;
		/// <summary> The right joystick minimum Y value. </summary>
		unsigned char RightMinY;
		/// <summary> The right joystick center Y value. </summary>
		unsigned char RightMidY;
		/// <summary> The right joystick maximum Y value. </summary>
		unsigned char RightMaxY;
		/// <summary> The left trigger minimum value. </summary>
		unsigned char LeftTriggerMin;
		/// <summary> The left trigger maximum value. </summary>
		unsigned char LeftTriggerMax;
		/// <summary> The right trigger minimum value. </summary>
		unsigned char RightTriggerMin;
		/// <summary> The right trigger maximum value. </summary>
		unsigned char RightTriggerMax;
	} wclWiiRemoteClassicControllerCalibration;

	/// <summary> The structure describes a Wii Remote Classic controller
	///   extension. </summary>
	typedef struct
	{
		/// <summary> The Wii Remote Classic controller calibration data. </summary>
		/// <seealso cref="wclWiiRemoteClassicControllerCalibration" />
		wclWiiRemoteClassicControllerCalibration Calibration;
		/// <summary> The Wii Remote Classic controller buttons states. </summary>
		/// <seealso cref="wclWiiRemoteClassicControllerButtons" />
		wclWiiRemoteClassicControllerButtons Buttons;
		/// <summary> The Wii Remote Classic controller left joystick
		///   value. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D LeftJoystick;
		/// <summary> The Wii Remote Classic controller right joystick
		///   value. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D RightJoystick;
		/// <summary> The Wii Remote Classic controller left trigger
		///   value. </summary>
		unsigned char LeftTrigger;
		/// <summary> The Wii Remote Classic controller right trigger
		///   value. </summary>
		unsigned char RightTrigger;
	} wclWiiRemoteClassicController;

	/// <summary> The Wii Remote Guitar extension type. </summary>
	typedef enum
	{
		/// <summary> The Guitar extension is the Hero 3 model. </summary>
		wiiGuitarHero3,
		/// <summary> The Guitar extension is the Hero World Tour model. </summary>
		wiiGuitarHeroWorldTour
	} wclWiiRemoteGuitarType;

	/// <summary> The structure contains information about the Wii Remote Guitar
	///   extension buttons. </summary>
	typedef struct
	{
		/// <summary> The "Strum Up" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool StrumUp;
		/// <summary> The "Strum Down" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool StrumDown;
		/// <summary> The "-" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Minus;
		/// <summary> The "+" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Plus;
	} wclWiiRemoteGuitarButtons;

	/// <summary> The structure contains the Wii Remote Guitar extension fret
	///   buttons states. </summary>
	typedef struct
	{
		/// <summary> The "Green" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Green;
		/// <summary> The "Red" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Red;
		/// <summary> The "Yellow" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Yellow;
		/// <summary> The "Blue" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Blue;
		/// <summary> The "Orange" button state. <c>True</c> if the button is
		///   pressed. </summary>
		bool Orange;
	} wclWiiRemoteGuitarFretButtons;

	/// <summary> The structure describes a Wii Remote Guitar extension
	///   data. </summary>
	typedef struct
	{
		/// <summary> The Wii Remote Guitar extension type. </summary>
		/// <seealso cref="wclWiiRemoteGuitarType" />
		wclWiiRemoteGuitarType GuitarType;
		/// <summary> The Wii Remote Guitar extension buttons data. </summary>
		/// <seealso cref="wclWiiRemoteGuitarButtons" />
		wclWiiRemoteGuitarButtons Buttons;
		/// <summary> The Wii Remote Guitar extension fret buttons data. </summary>
		/// <seealso cref="wclWiiRemoteGuitarFretButtons" />
		wclWiiRemoteGuitarFretButtons FretButtons;
		/// <summary> The Wii Remote Guitar extension touchbar data. </summary>
		/// <seealso cref="wclWiiRemoteGuitarFretButtons" />
		wclWiiRemoteGuitarFretButtons Touchbar;
		/// <summary> The Wii Remote Guitar extension joystick data. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D Joystick;
		/// <summary> The Wii Remote Guitar extension whammy bar data. </summary>
		unsigned char WhammyBar;
	} wclWiiRemoteGuitar;

	/// <summary> The structure describes the Wii Remote Drums
	///   extension </summary>
	typedef struct
	{
		/// <summary> <c>True</c> if the "Red" drum is touched. </summary>
		bool Red;
		/// <summary> <c>True</c> if the "Green" drum is touched. </summary>
		bool Green;
		/// <summary> <c>True</c> if the "Blue" drum is touched. </summary>
		bool Blue;
		/// <summary> <c>True</c> if the "Orange" drum is touched. </summary>
		bool Orange;
		/// <summary> <c>True</c> if the "Yellow" drum is touched. </summary>
		bool Yellow;
		/// <summary> <c>True</c> if the Pedal is pressed. </summary>
		bool Pedal;
		/// <summary> The "Red" drum velocity. </summary>
		unsigned char RedVelocity;
		/// <summary> The "Green" drum velocity. </summary>
		unsigned char GreenVelocity;
		/// <summary> The "Blue" drum velocity. </summary>
		unsigned char BlueVelocity;
		/// <summary> The "Orange" drum velocity. </summary>
		unsigned char OrangeVelocity;
		/// <summary> The "Yellow" drum velocity. </summary>
		unsigned char YellowVelocity;
		/// <summary> The Pedal velocity. </summary>
		unsigned char PedalVelocity;
		/// <summary> <c>True</c> if the "+" button is pressed. </summary>
		bool Plus;
		/// <summary> <c>True</c> if the "-" button is pressed. </summary>
		bool Minus;
		/// <summary> The drum joystick data. </summary>
		/// <seealso cref="wclWiiRemote2D" />
		wclWiiRemote2D Joystick;
	} wclWiiRemoteDrums;

	/// <summary> The structure describes the Wii Remote Balance Board extension
	///   sensors data. </summary>
	typedef struct
	{
		/// <summary> Top right sensor value. </summary>
		unsigned short TopRight;
		/// <summary> Top left sensor value. </summary>
		unsigned short TopLeft;
		/// <summary> Bottom right sensor value. </summary>
		unsigned short BottomRight;
		/// <summary> Bottom left sensor value. </summary>
		unsigned short BottomLeft;
	} wclWiiRemoteBalanceBoardSensors;

	/// <summary> The structure describes the Wii Remote Balance Board extension
	///   sensors weight. </summary>
	typedef struct
	{
		/// <summary> Top right sensor value. </summary>
		double TopRight;
		/// <summary> Top left sensor value. </summary>
		double TopLeft;
		/// <summary> Bottom right sensor value. </summary>
		double BottomRight;
		/// <summary> Bottom left sensor value. </summary>
		double BottomLeft;
	} wclWiiRemoteBalanceBoardSensorsWeight;

	/// <summary> The structure describes the Wii Remote Balance Board extension
	///   sensors calibration data. </summary>
	typedef struct
	{
		/// <summary> The 0-17 KG calibration data. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensors" />
		wclWiiRemoteBalanceBoardSensors Kg0;
		/// <summary> The 17-34 KG calibration data. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensors" />
		wclWiiRemoteBalanceBoardSensors Kg17;
		/// <summary> The 34 and above KG calibration data. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensors" />
		wclWiiRemoteBalanceBoardSensors Kg34;
	} wclWiiRemoteBalanceBoardCalibration;

	/// <summary> The structure represents the Balance Board extension center of
	///   gravity. </summary>
	typedef struct
	{
		/// <summary> An X coordinate. </summary>
		double X;
		/// <summary> An Y coordinate. </summary>
		double Y;
	} wclWiiRemoteBalanceBoardGC;

	/// <summary> The structure describes the Wii Remote Balance Board
	///   extension. </summary>
	typedef struct
	{
		/// <summary> The Wii Remote Balance Board extension calibration
		///   data. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardCalibration" />
		wclWiiRemoteBalanceBoardCalibration Calibration;
		/// <summary> The Wii Remote Balance Board extension sensors
		///   values. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensors" />
		wclWiiRemoteBalanceBoardSensors Sensors;
		/// <summary> The Wii Remote Balance Board extension sensors values
		///   (KG). </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensorsWeight" />
		wclWiiRemoteBalanceBoardSensorsWeight SensorsKg;
		/// <summary> The Wii Remote Balance Board extension sensors values
		///   (Lb). </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardSensorsWeight" />
		wclWiiRemoteBalanceBoardSensorsWeight SensorsLb;
		/// <summary> The Wii Remote Balance Board extension detected weight
		///   (KG). </summary>
		double WeightKg;
		/// <summary> The Wii Remote Balance Board extension detected weight
		///   (Lb). </summary>
		double WeightLb;
		/// <summary> The center of gravity coordinate. </summary>
		/// <seealso cref="wclWiiRemoteBalanceBoardGC" />
		wclWiiRemoteBalanceBoardGC CenterOfGravity;
	} wclWiiRemoteBalanceBoard;

	/// <summary> The Bluetooth LE packet header. </summary>
	typedef struct
	{
		/// <summary> The access address. </summary>
		unsigned long AccessAddress;
		/// <summary> The channel number. </summary>
		unsigned char Channel;
		/// <summary> The CRC value. The CRC is 3 bytes long so hight byte is
		///   always 0x00. </summary>
		unsigned long Crc;
		/// <summary> The RSSI value in dBm. </summary>
		char Rssi;
		/// <summary> The time stamp value. </summary>
		unsigned long Timestamp;
		/// <summary> The packed valid status (<c>True</c> if the packet
		///   is valid. <c>False</c> otherwise. </summary>
		bool Valid;
	} wclBluetoothLePacketHeader;

	/// <summary> The Bluetooth LE advertising packet PDU types. </summary>
	typedef enum
	{
		/// <summary> The <c>ADV_IND</c> PDU type. </summary>
		ptAdvInd,
		/// <summary> The <c>ADV_DIRECT_IND</c> PDU type. </summary>
		ptAdvDirectInd,
		/// <summary> The <c>ADV_NONCONN_IND</c> PDU type. </summary>
		ptAdvNonConnInd,
		/// <summary> The <c>SCAN_REQ</c> PDU type. </summary>
		ptScanReq,
		/// <summary> The <c>AUX_SCAN_REQ</c> PDU type. </summary>
		ptAuxScanReq,
		/// <summary> The <c>SCAN_RSP</c> PDU type. </summary>
		ptScanRsp,
		/// <summary> The <c>CONNECT_IND</c> PDU type. </summary>
		ptConnectInd,
		/// <summary> The <c>AUX_CONNECT_REQ</c> PDU type. </summary>
		ptAuxConnectReq,
		/// <summary> The <c>ADV_SCAN_IND</c> PDU type. </summary>
		ptAdvScanInd,
		/// <summary> The <c>ADV_EXT_IND</c> PDU type. </summary>
		ptAdvExtInd,
		/// <summary> The <c>AUX_ADV_IND</c> PDU type. </summary>
		ptAuxAdvInd,
		/// <summary> The <c>AUX_SCAN_RSP</c> PDU type. </summary>
		ptAuxScanRsp,
		/// <summary> The <c>AUX_SYNC_IND</c> PDU type. </summary>
		ptAuxSyncInd,
		/// <summary> The <c>AUX_CHAIN_IND</c> PDU type. </summary>
		ptAuxChainInd,
		/// <summary> The <c>AUX_CONNECT_RSP</c> PDU type. </summary>
		ptAuxConnectRsp
	} wclBluetoothLeAdvertisingPduType;

	/// <summary> The record describes the Bluetooth LE advertising packet PDU
	///   header. </summary>
	typedef struct
	{
		/// <summary> The Bluetooth LE captured packet header. </summary>
		/// <seealso cref="wclBluetoothLePacketHeader" />
		wclBluetoothLePacketHeader Header;
		/// <summary> The Bluetooth LE advertising PDU type. </summary>
		/// <seealso cref="wclBluetoothLeAdvertisingPduType" />
		wclBluetoothLeAdvertisingPduType PduType;
		/// <summary> The <c>ChSel</c> header's bit state. </summary>
		/// <remarks> The meaning of this field (bit) depends on the PDU type.
		///   If the value of this field is <c>True</c> the <c>ChSel</c> bit is
		///   <c>1</c>. If the value of this field is <c>Flase</c> the <c>ChSel</c>
		///   bit is <c>0</c>. </remarks>
		bool ChSel;
		/// <summary> The <c>TxAdd</c> header's bit state. </summary>
		/// <remarks> The meaning of this field (bit) depends on the PDU type.
		///   If the value of this field is <c>True</c> the <c>TxAdd</c> bit is
		///   <c>1</c>. If the value of this field is <c>Flase</c> the <c>TxAdd</c>
		///   bit is <c>0</c>. </remarks>
		bool TxAdd;
		/// <summary> The <c>RxAdd</c> header's bit state. </summary>
		/// <remarks> The meaning of this field (bit) depends on the PDU type.
		///   If the value of this field is <c>True</c> the <c>RxAdd</c> bit is
		///   <c>1</c>. If the value of this field is <c>Flase</c> the <c>RxAdd</c>
		///   bit is <c>0</c>. </remarks>
		bool RxAdd;
	} wclBluetoothLeAdvertisingPduHeader;

	/// <summary> The record contains the Link Layer data captured by the
	///   Bluetooth LE sniffer and used in the <c>CONNECT_IND</c>
	///  advertisement packet. </summary>
	typedef struct
	{
		/// <summary> The field contains the ACL connection’s Access Address
		///   determined by the Link Layer. </summary>
		unsigned long Aa;
		/// <summary> The field contains the initialization value for the CRC
		///   calculation for the ACL connection. It shall be a random value,
		///   generated by the Link Layer. The seed for the random number
		///   generator is from a physical source of entropy and has at least 20
		///   bits of entropy. </summary>
		unsigned long CrcInit;
		/// <summary> The field indicates the transmit window size value in the
		///   following manner: <c>WindowSize = WinSize * 1.25ms</c>. </summary>
		unsigned char WinSize;
		/// <summary> The field indicates the transmit window offset value in the
		///   following manner: <c>WindowOffset = WinOffset * 1.25ms</c>. </summary>
		unsigned short WinOffset;
		/// <summary> The field indicates the connection interval in the following
		///   manner: <c>ConnectionInterval = Interval * 1.25ms</c>. </summary>
		unsigned short Interval;
		/// <summary> The field indicates the peripheral latency value. </summary>
		unsigned short Latency;
		/// <summary> The field indicates the connection supervision timeout value
		///   in the following manner:
		///   <c>SupervisionTimeout = Timeout * 10ms</c>. </summary>
		unsigned short Timeout;
		/// <summary> The field contains the channel map indicating Used and Unused
		///   data channels. Every channel is represented with a bit positioned as
		///   per the data channel index. The <c>LSB</c> represents data channel
		///   index 0 and the bit in position 36 represents data channel index 36.
		///   A bit value of 0 indicates that the channel is Unused. A bit value of
		///   1 indicates that the channel is Used. The bits in positions 37, 38 and
		///   39 are reserved for future use. </summary>
		/// <remarks> The <c>ChM</c> value is 5 bytes long. The high 3 bytes are not
		///   used. </remarks>
		unsigned __int64 ChM;
		/// <summary> The field indicates the hop increment used in the data
		///   channel selection algorithm. It has a random value in the range 5 to
		///   16. </summary>
		unsigned char Hop;
		/// <summary> <p>The field indicates the central SCA used to determine the
		///   Central's worst case sleep clock accuracy. The value of the SCA
		///   are:</p>
		///   <p>0 - 251ppm to 500ppm</p>
		///   <p>1 - 151ppm to 250ppm</p>
		///   <p>2 - 101ppm to 150ppm</p>
		///   <p>3 - 76ppm to 100ppm</p>
		///   <p>4 - 51ppm to 75ppm</p>
		///   <p>5 - 31ppm to 50ppm</p>
		///   <p>6 - 21ppm to 30ppm</p>
		///   <p>7 - 0ppm to 20ppm</p> </summary>
		unsigned char Sca;
	} wclBleSnifferLlData;

	/* Event handler prototypes */

	/// <summary> The <c>OnConfirm</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Confirm"> An application must set this parameter to
	///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
	///   pairing. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothConfirmEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, bool& Confirm)
	/// <summary> The common event for notifications when a remote device's
	///   MAC address required. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothDeviceEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address)
	/// <summary> The common event handler prototype used for a remote
	///   Bluetooth device's operations result notifications. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Error"> An operation result code. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothDeviceResultEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, const int Error)
	/// <summary> The <c>OnIoCapabilityRequest</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Mitm"> An application sets this parameter to specify the
	///   "Man in the Middle" protection required for authentication. </param>
	/// <param name="IoCapability"> An application sets this parameter to define
	///   the input/output capabilities of a Bluetooth Device. </param>
	/// <param name="OobPresent"> An application sets this parameter to
	///   <c>True</c> to force Out Of Band authentication. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="wclBluetoothMitmProtection" />
	/// <seealso cref="wclBluetoothIoCapability" />
	#define wclBluetoothIoCapabilityRequestEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, wclBluetoothMitmProtection& Mitm, \
			wclBluetoothIoCapability& IoCapability, bool& OobPresent)
	/// <summary> The common Bluetooth event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio)
	/// <summary> The <c>OnNumericComparison</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Number"> A number sent by a remote device to display and
	///   compare. </param>
	/// <param name="Confirm"> An application must set this parameter to
	///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
	///   pairing. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothNumericComparisonEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, const unsigned long Number, bool& Confirm)
	/// <summary> The <c>OnOobDataRequest</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="OobData"> An application must set this parameter to
	///   the Out Of Band data received from peer device. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="wclBluetoothOobData" />
	#define wclBluetoothOobDataRequestEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, wclBluetoothOobData& OobData)
	/// <summary> The <c>OnPasskeyNotification</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Passkey"> A Passkey provided by a remote
	///   Bluetooth device. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothPasskeyNotificationEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, const unsigned long Passkey)
	/// <summary> The <c>OnPasskeyRequest</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Passkey"> A Passkey provided by an application. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothPasskeyRequestEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, unsigned long& Passkey)
	/// <summary> The <c>OnPinRequest</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Pin"> A PIN code provided by an application. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothPinRequestEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, tstring& Pin)
	/// <summary> The <c>OnProtectionLevelRequest</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Address"> A remote device's MAC address. </param>
	/// <param name="Protection"> Describes the required protection
	///   level provided by an application. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="wclBluetoothLeProtectionLevel" />
	#define wclBluetoothProtectionLevelRequestEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const __int64 Address, wclBluetoothLeProtectionLevel& Protection)
	/// <summary> The common Bluetooth result even handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
	///   represents a Bluetooth driver that fired the event. </param>
	/// <param name="Error"> An operation result code. </param>
	/// <seealso cref="CwclBluetoothRadio" />
	#define wclBluetoothResultEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclBluetoothRadio* const Radio, \
			const int Error)

	/// <summary> The <c>GetSdpAttributes</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Protocols"> The additional protocol descriptors array that
	///   should be added to SDP record. </param>
	/// <param name="Profiles"> The profile descriptors list that should be added
	///   to SDP record. </param>
	/// <param name="Formats"> Other attributes that should be added to SDP
	///   record. </param>
	/// <param name="Cod"> <para> Class of device (COD) information. A 32-bit
	///   parameter of COD_SERVICE_* class of device bits associated with this
	///   SDP record. The system combines these bits with COD bits from other
	///   service records and system characteristics. The resulting class of
	///   device for the local radio is advertised when the radio is found during
	///   device inquiry. When the last SDP record associated with a particular
	///   service bit is deleted, that service bit is no longer reported in
	///   responses to future device inquiries. </para>
	///   <para> The format and possible values for the COD value are defined in
	///   the Bluetooth Assigned Numbers 1.1 portion of the Bluetooth
	///   specification, Section 1.2. (This resource may not be available in some
	///   languages and countries.) </para> </param>
	/// <seealso cref="wclBluetoothSdpProtocols" />
	/// <seealso cref="wclBluetoothSdpProfiles" />
	/// <seealso cref="wclBluetoothSdpFormats" />
	#define wclBluetoothGetSdpAttributesEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, wclBluetoothSdpProtocols& Protocols, \
			wclBluetoothSdpProfiles& Profiles, wclBluetoothSdpFormats& Formats, \
			unsigned long& Cod)

	/// <summary> The prototype of the <c>OnConnect</c> event handler for RFCOMM
	///   server. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> The
	///   <see cref="CwclRfCommServerClientConnection" /> represents a remote
	///   connected client. </param>
	/// <param name="Error"> The connection operation result code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
	///   device was established and the remote device is connected. Otherwise
	///   the connection was not established and the remote device is
	///   not connected. </param>
	/// <seealso cref="CwclRfCommServerClientConnection" />
	#define wclRfCommServerConnectEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclRfCommServerClientConnection* const Client, \
			const int Error)
	/// <summary> A server connection <c>OnData</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> A
	///   <see cref="CwclRfCommServerClientConnection" /> object
	///   represents a remote client connection. </param>
	/// <param name="Data"> The pointer to the received data buffer.
	///   It is guaranteed that the parameter points to a valid data buffer.
	///   The data buffer is valid only inside the event handler. If an
	///   application needs to use the data outside the event handle it must
	///   allocate own buffer and copy data into it. </param>
	/// <param name="Size"> The data buffer size. It is guaranteed that the size
	///   is greater than 0. </param>
	/// <seealso cref="CwclRfCommServerClientConnection" />
	#define wclRfCommServerDataEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclRfCommServerClientConnection* const Client, \
			const void* const Data, const unsigned long Size)
	/// <summary> The prototype of the <c>OnDisconnect</c> event handler for
	///   server connections. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Client"> The
	///   <see cref="CwclRfCommServerClientConnection" /> represents a remote
	///   connected client. </param>
	/// <param name="Reason"> The disconnection code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
	///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
	///   reason. </param>
	/// <seealso cref="CwclRfCommServerClientConnection" />
	#define wclRfCommServerDisconnectEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclRfCommServerClientConnection* const Client, \
			const int Reason)

	/// <summary> The <c>OnCharacteristicChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Handle"> A changed characteristic handle. </param>
	/// <param name="Value"> A pointer to the characteristic value. </param>
	/// <param name="Length"> A characteristic value length in bytes. </param>
	/// <remarks> The <c>Value</c> parameter is valid only inside the event
	///   handler. If an application needs to use it outside the event handler
	///   it must be copied. </remarks>
	#define wclGattCharacteristicChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const unsigned short Handle, \
			const unsigned char* const Value, unsigned long const Length)

	/// <summary> The <c>OnAdvertisementAppearanceFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Appearance"> The Bluetooth LE device appearance
	///   value. </param>
	#define wclBluetoothLeAdvertisementAppearanceFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned short Appearance)
	/// <summary> The <c>OnAdvertisementFrameInformation</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Name"> The Bluetooth LE advertiser's name. </param>
	/// <param name="PacketType"> The Bluetooth LE advertisement data packet
	///   type. </param>
	/// <param name="Flags"> The Bluetooth LE advertisement packet payload
	///   flags. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementType" />
	/// <seealso cref="wclBluetoothLeAdvertisementFlags" />
	#define wclBluetoothLeAdvertisementFrameInformationEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const tstring& Name, \
			const wclBluetoothLeAdvertisementType PacketType, \
			const wclBluetoothLeAdvertisementFlags& Flags)
	/// <summary> The <c>OnAdvertisementExtFrameInformation</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="AddressType"> The Bluetooth LE address type. </param>
	/// <param name="TxPower"> The received transmit power of the
	///   advertisement. Ranges from -127 dBm to 20 dBm. -128 indicates
	///   "no value". </param>
	/// <param name="Flags"> The Bluetooth LE advertisement extended frame
	///   flags. </param>
	/// <seealso cref="wclBluetoothAddressType" />
	/// <seealso cref="wclBluetoothLeExtendedFrameFlags" />
	#define wclBluetoothLeAdvertisementExtFrameInformationEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, const __int64 Timestamp, \
			const char Rssi, const wclBluetoothAddressType AddressType, const char TxPower, \
			const wclBluetoothLeExtendedFrameFlags& Flags)
	/// <summary> The <c>OnAdvertisementRawFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="DataType"> The frame's data type. </param>
	/// <param name="Data"> The frame's raw bytes data. If there is no data the
	///   value is <c>NULL</c>. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAdvertisementRawFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned char DataType, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnAdvertisementReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Data"> The frame's raw bytes data. If there is no data the
	///   value is <c>nil</c>. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAdvertisementReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnService16DataFrame</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 16 bits service UUID. </param>
	/// <param name="Data"> The service data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAdvertisementService16DataFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnService32DataFrame</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 32 bits service UUID. </param>
	/// <param name="Data"> The service data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAdvertisementService32DataFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnService128DataFrame</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 128 bits service UUID. </param>
	/// <param name="Data"> The service data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAdvertisementService128DataFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const GUID& Uuid, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnServiceSol16Frame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 16 bits service UUID. </param>
	#define wclBluetoothLeAdvertisementServiceSol16FrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid)
	/// <summary> The <c>OnServiceSol32Frame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 32 bits service UUID. </param>
	#define wclBluetoothLeAdvertisementServiceSol32FrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid)
	/// <summary> The <c>OnServiceSol128Frame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The 128 bits service UUID. </param>
	#define wclBluetoothLeAdvertisementServiceSol128FrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const GUID& Uuid)
	/// <summary> The <c>OnAdvertisementTxPowerLevelFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="TxPower"> The TX power level in range from -127 to 128
	///   dBm. </param>
	#define wclBluetoothLeAdvertisementTxPowerLevelFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const char TxPower)
	/// <summary> The <c>OnAdvertisementUuidFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Uuid"> The advertised UUID value. </param>
	#define wclBluetoothLeAdvertisementUuidFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const GUID& Uuid)
	/// <summary> The <c>OnAltBeaconFrame</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
	///   Bluetooth SIG Assigned Numbers. </param>
	/// <param name="Major"> The beacon's Major value. </param>
	/// <param name="Minor"> The beacon's Minor value. </param>
	/// <param name="Uuid"> The beacon's UUID. </param>
	/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution measured at 1 meter
	///   distance. </param>
	/// <param name="Reserved"> A 1-byte value from 0x00 to 0xFF. Interpretation
	///   of this value is to be defined by the manufacturer and is to be
	///   evaluated based on the CompanyId value. </param>
	/// <param name="Data"> The additional frame data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeAltBeaconFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned short CompanyId, \
			const unsigned short Major, const unsigned short Minor, const GUID& Uuid, \
			const char TxRssi, const unsigned char Reserved, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnDriAsdMessage</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The drone's MAC address. </param>
	/// <param name="Timestamp"> The message's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="Raw"> The raw DRI ASD messages data. </param>
	#define wclBluetoothLeDriAsdMessageEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const wclDriRawData& Raw)
	/// <summary> The <c>OnEddystoneTlmFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="AdvCnt"> The running count of advertisement frames of all
	///   types emitted by the beacon since power-up or reboot, useful for
	///   monitoring performance metrics that scale per broadcast frame.
	///   If this value is reset (e.g. on reboot), the current time field is
	///   also reset. </param>
	/// <param name="Batt"> The current battery charge in millivolts, expressed as
	///   1 mV per bit. If not supported (for example in a USB-powered beacon) the
	///   value should be zeroed. </param>
	/// <param name="SecCnt"> The 0.1 second resolution counter that represents
	///   time since beacon power-up or reboot. If this value is reset (e.g. on
	///   a reboot), the AdvCnt count field is also reset. </param>
	/// <param name="Temp"> The beacon temperature in degrees Celsius sensed by
	///   the beacon. If not supported the value is -128 °C. </param>
	/// <param name="Data"> The additional frame data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeEddystoneTlmFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned long AdvCnt, \
			const unsigned short Batt, const unsigned long SecCnt, const double Temp, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnEddystoneUidFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
	///   distance. </param>
	/// <param name="Uuid"> The Eddystone ID: 10 bytes - Namespace ID and 6
	///   bytes - Instance ID. </param>
	/// <param name="Data"> The additional frame data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeEddystoneUidFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const char TxRssi, const GUID& Uuid, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnEddystoneUrlFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
	///   distance. </param>
	/// <param name="Url"> The Eddystone URL. </param>
	#define wclBluetoothLeEddystoneUrlFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const char TxRssi, \
			const tstring& Url)
	/// <summary> The <c>OnManufacturerRawFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
	///   Bluetooth SIG Assigned Numbers. </param>
	/// <param name="Data"> The frame raw data. The value can be <c>NULL</c> if
	///   there is no any data available in the frame. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
	#define wclBluetoothLeManufacturerRawFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, const unsigned short CompanyId, \
			const wclBluetoothLeAdvertisementFrameRawData& Data)
	/// <summary> The <c>OnAppleAirdropFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleAirdropFrameData" />
	#define wclBluetoothLeAppleAirdropFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleAirdropFrameData& Data)
	/// <summary> The <c>OnAppleAirplaySourceFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleAirplaySourceFrameData" />
	#define wclBluetoothLeAppleAirplaySourceFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleAirplaySourceFrameData& Data)
	/// <summary> The <c>OnAppleAirplayTargetFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleAirplayTargetFrameData" />
	#define wclBluetoothLeAppleAirplayTargetFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleAirplayTargetFrameData& Data)
	/// <summary> The <c>OnAppleAirprintFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleAirprintFrameData" />
	#define wclBluetoothLeAppleAirprintFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleAirprintFrameData& Data)
	/// <summary> The <c>OnAppleFindMyFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleFindMyFrameData" />
	#define wclBluetoothLeAppleFindMyFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleFindMyFrameData& Data)
	/// <summary> The <c>OnAppleHandoffFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleHandoffFrameData" />
	#define wclBluetoothLeAppleHandoffFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleHandoffFrameData& Data)
	/// <summary> The <c>OnAppleHeySiriFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="TwclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
	#define wclBluetoothLeAppleHeySiriFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleHeySiriFrameData& Data)
	/// <summary> The <c>OnAppleHomeKitFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleHomeKitFrameData" />
	#define wclBluetoothLeAppleHomeKitFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleHomeKitFrameData& Data)
	/// <summary> The <c>OnAppleiBeaconFrame</c> event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleiBeaconFrameData" />
	#define wclBluetoothLeAppleiBeaconFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleiBeaconFrameData& Data)
	/// <summary> The <c>OnAppleMagicSwitchFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleMagicSwitchFrameData" />
	#define wclBluetoothLeAppleMagicSwitchFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleMagicSwitchFrameData& Data);
	/// <summary> The <c>OnAppleNearbyActionFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleNearbyActionFrameData" />
	#define wclBluetoothLeAppleNearbyActionFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleNearbyActionFrameData& Data)
	/// <summary> The <c>OnAppleNearbyInfoFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleNearbyInfoFrameData" />
	#define wclBluetoothLeAppleNearbyInfoFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleNearbyInfoFrameData& Data)
	/// <summary> The <c>OnApplePriximityPairingFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleProximityPairingFrameData" />
	#define wclBluetoothLeAppleProximityPairingFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleProximityPairingFrameData& Data)
	/// <summary> The <c>OnAppleTetheringSourceFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleTetheringSourceFrameData" />
	#define wclBluetoothLeAppleTetheringSourceFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleTetheringSourceFrameData& Data)
	/// <summary> The <c>OnAppleTetheringTargetFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleTetheringTargetFrameData" />
	#define wclBluetoothLeAppleTetheringTargetFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleTetheringTargetFrameData& Data);
	/// <summary> The <c>OnAppleUnknownFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Info"> The Bluetooth LE advertisement information. </param>
	/// <param name="Data"> The advertisement frame decoded data. </param>
	/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
	/// <seealso cref="wclBluetoothLeAppleUnknownFrameData" />
	#define wclBluetoothLeAppleUnknownFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisementInfo& Info, \
			const wclBluetoothLeAppleUnknownFrameData& Data)
	/// <summary> The <c>OnMicrosoftCdpBeaconFrame</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
	/// <param name="Timestamp"> The frame's timestamp in Universal Time
	///   format. </param>
	/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
	///   dBm and +20 dBm at 1 dBm resolution. </param>
	/// <param name="ScenarioType"> The beacon scenario. </param>
	/// <param name="Version"> The protocol version. </param>
	/// <param name="DeviceType"> The device type. </param>
	/// <param name="SubVersion"> The protocol subversion. </param>
	/// <param name="ShareNearBy"> If <c>True</c> then the NearBy share setting is
	///   everyone rather than only my devices. </param>
	/// <param name="AddressAsDeviceId"> <c>True</c> indicates that the Bluetooth
	///   address can be used as the device ID. </param>
	/// <param name="ExtendedDeviceStatus"> The extended device status. </param>
	/// <param name="Salt"> The beacon salt (4 random bytes). </param>
	/// <param name="Hash"> SHA256 Hash of Salt plus Device Thumbprint. </param>
	/// <seealso cref="wclBluetoothLeCdpBeaconScenarioType" />
	/// <seealso cref="wclBluetoothLeCdpBeaconDeviceType" />
	/// <seealso cref="wclBluetoothLeCdpBeaconSalt" />
	/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatuses" />
	/// <seealso cref="wclBluetoothLeCdpBeaconHash" />
	#define wclBluetoothLeMicrosoftCdpBeaconFrameEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const __int64 Address, \
			const __int64 Timestamp, const char Rssi, \
			const wclBluetoothLeCdpBeaconScenarioType ScenarioType, \
			const unsigned char Version, const wclBluetoothLeCdpBeaconDeviceType DeviceType, \
			const unsigned char SubVersion, const bool ShareNearBy, const bool AddressAsDeviceId, \
			const wclBluetoothLeCdpBeaconExtendedDeviceStatuses& ExtendedDeviceStatus, \
			const wclBluetoothLeCdpBeaconSalt& Salt, const wclBluetoothLeCdpBeaconHash& Hash)

	/// <summary> The GATT server client event handlers prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
	///   represents a GATT server client. </param>
	/// <remarks> This event handler prototype is used for
	///   <c>OnClientConnected</c> and <c>OnClientDisconnected</c> events of the
	///   GATT server. </remarks>
	/// <seealso cref="CwclGattServerClient" />
	#define wclGattServerClientEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclGattServerClient* const Client)
	/// <summary> The <c>OnRead</c> characteristic's event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
	///   requested read. </param>
	/// <param name="Characteristic"> The characteristic object for which writes
	///   is executing. </param>
	/// <param name="Request"> The GATT read request object. </param>
	/// <seealso cref="CwclGattServerClient" />
	/// <seealso cref="CwclGattLocalCharacteristic" />
	/// <seealso cref="TwclGattLocalCharacteristicReadRequest" />
	#define wclGattLocalCharacteristicReadEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclGattServerClient* const Client, \
			CwclGattLocalCharacteristic* const Characteristic, \
			CwclGattLocalCharacteristicReadRequest* const Request)
	/// <summary> The <c>OnWrite</c> characteristic's event handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
	///   requested write. </param>
	/// <param name="Characteristic"> The characteristic object for which writes
	///   is executing. </param>
	/// <param name="Request"> The GATT characteristic write request object. </param>
	/// <seealso cref="CwclGattServerClient" />
	/// <seealso cref="CwclGattLocalCharacteristic" />
	/// <seealso cref="TwclGattLocalCharacteristicWriteRequest" />
	#define wclGattLocalCharacteristicWriteEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclGattServerClient* const Client, \
			CwclGattLocalCharacteristic* const Characteristic, \
			CwclGattLocalCharacteristicWriteRequest* const Request)
	/// <summary> The <c>OnClientSubscribed</c> and <c>OnClientUnsubscribed</c>
	///   events handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
	///   subscribed or unsubscribed. </param>
	/// <param name="Characteristic"> The characteristic object for which writes
	///   is executing. </param>
	/// <seealso cref="CwclGattServerClient" />
	/// <seealso cref="CwclGattLocalCharacteristic" />
	#define wclGattLocalCharacteristicSubscribedClientsChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, CwclGattServerClient* const Client, \
			CwclGattLocalCharacteristic* const Characteristic)

	/// <summary> The Wii Remote <c>OnAccelChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Accel"> The current accelerometer data. </param>
	/// <seealso cref="wclWiiRemoteAccel" />
	#define wclWiiRemoteAccelChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteAccel& Accel)
	/// <summary> The Wii Remote <c>OnBalanceBoardChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Board"> The new Balance Board extension
	///   state. </param>
	/// <seealso cref="wclWiiRemoteBalanceBoard" />
	#define wclWiiRemoteBalanceBoardChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteBalanceBoard& Board)
	/// <summary> The Wii Remote <c>OnButtonsChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Buttons"> The current state of the Wii Remote controller
	///   buttons. </param>
	/// <seealso cref="wclWiiRemoteButtons" />
	#define wclWiiRemoteButtonsChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteButtons& Buttons)
	/// <summary> The Wii Remote <c>OnClassicControllerChanged</c> event
	///   handler prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Controller"> The current state of the Wii Remote Classic
	///   Controller extension. </param>
	/// <seealso cref="wclWiiRemoteClassicController" />
	#define wclWiiRemoteClassicControllerChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteClassicController& Controller)
	/// <summary> The Wii Remote <c>OnDrumsChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Drums"> The current state of the Drums extension. </param>
	/// <seealso cref="wclWiiRemoteDrums" />
	#define wclWiiRemoteDrumsChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteDrums& Drums)
	/// <summary> The Wii Remote <c>OnGuitarChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Guitar"> The current Guitar extension state. </param>
	/// <seealso cref="wclWiiRemoteGuitar" />
	#define wclWiiRemoteGuitarChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteGuitar& Guitar)
	/// <summary> The Wii Remote <c>OnIrChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Ir"> The IR sensor data. </param>
	/// <seealso cref="wclWiiRemoteIrSensors" />
	#define wclWiiRemoteIrChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteIrSensors& Ir)
	/// <summary> The Wii Remote <c>OnNunchukChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Nunchuk"> The current Nunchuk extension state. </param>
	/// <seealso cref="wclWiiRemoteNunchuk" />
	#define wclWiiRemoteNunchukChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclWiiRemoteNunchuk& Nunchuk)
	/// <summary> The Wii Remote <c>OnStatusChanged</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Batt"> The WeDo Remote battery level. </param>
	/// <param name="Leds"> The We Do Remote LEDs state. </param>
	/// <seealso cref="wclWiiRemoteLeds" />
	#define wclWiiRemoteStatusChangedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const double Batt, const wclWiiRemoteLeds& Leds)

	/// <summary> The BLE sniffer <c>OnAdvDirectIndReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="AdvA"> The advertiser address. </param>
	/// <param name="TargetA"> The address of the device to which this PDU
	///   is addressed. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>AdvA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True).
	///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
	///   whether the target’s address in the <c>TargetA</c> parameter is
	///   public (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c> field
	///   in the <c>PduHeader</c> parameter is <c>True</c> if the advertiser
	///   supports the LE Channel Selection Algorithm #2 feature. </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferAdvDirectIndReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 AdvA, const __int64 TargetA)
	/// <summary> The BLE sniffer <c>OnAdvIndReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="AdvA"> The advertiser address. </param>
	/// <param name="AdvData"> The pointer to the advertisement data.
	///   Can be <c>NULL</c>. The pointer is valid only inside the event
	///   handler. </param>
	/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>AdvA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True). The
	///   <c>ChSel</c> field in the <c>PduHeader</c> parameter is <c>True</c>
	///   if the advertiser supports the LE Channel Selection Algorithm #2
	///   feature. </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferAdvIndReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 AdvA, const unsigned char* const AdvData, \
			const unsigned char AdvDataLen)
	/// <summary> The BLE sniffer <c>OnAdvNonConnIndReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="AdvA"> The advertiser address. </param>
	/// <param name="AdvData"> The pointer to the advertisement data.
	///   Can be <c>NULL</c>. The pointer is valid only inside the event
	///   handler. </param>
	/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>AdvA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferAdvNonConnIndReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 AdvA, const unsigned char* const AdvData, \
			const unsigned char AdvDataLen)
	/// <summary> The BLE sniffer <c>OnAdvScanIndReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="AdvA"> The advertiser address. </param>
	/// <param name="AdvData"> The pointer to the advertisement data.
	///   Can be <c>NULL</c>. The pointer is valid only inside the event
	///   handler. </param>
	/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>AdvA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferAdvScanIndReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 AdvA, const unsigned char* const AdvData, \
			const unsigned char AdvDataLen)
	/// <summary> The BLE sniffer <c>OnConnectIndReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="InitA"> The Initiator’s device address. </param>
	/// <param name="AdvA"> The advertiser’s device address. </param>
	/// <param name="LlData"> The Link Layer data. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>InitA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True). The
	///   <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates whether
	///   the advertiser’s device address in the <c>AdvA</c> parameter is public
	///   (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c> field in the
	///   <c>PduHeader</c> parameter is <c>True</c> if the advertiser supports the
	///   LE Channel Selection Algorithm #2 feature. </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	/// <seealso cref="wclBleSnifferLlData" />
	#define wclBleSnifferConnectIndReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 InitA, const __int64 AdvA, const wclBleSnifferLlData& LlData)
	/// <summary> The BLE sniffer <c>OnScanReqReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="ScanA"> The scanner's address. </param>
	/// <param name="AdvA"> The address of the device to which this PDU
	///   is addressed. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the scanner’s address in the <c>ScanA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True).
	///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
	///   whether the target’s address in the <c>AdvA</c> parameter is
	///   public (RxAdd = False) or random (RxAdd = True). </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferScanReqReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 ScanA, const __int64 AdvA)
	/// <summary> The BLE sniffer <c>OnScanRspReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="PduHeader"> The PDU header. </param>
	/// <param name="AdvA"> The advertiser address. </param>
	/// <param name="ScanRspData"> The pointer to the advertisement data.
	///   Can be <c>NULL</c>. The pointer is valid only inside the event
	///   handler. </param>
	/// <param name="ScanRspDataLen"> The advertisement data length in
	///   bytes. </param>
	/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
	///   indicates whether the advertiser’s address in the <c>AdvA</c>
	///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
	/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
	#define wclBleSnifferScanRspReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLeAdvertisingPduHeader& PduHeader, \
			const __int64 AdvA, const unsigned char* const ScanRspData, \
			const unsigned char ScanRspDataLen)
	/// <summary> The BLE sniffer <c>OnRawPacketReceived</c> event handler
	///   prototype. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Header"> The Bluetooth LE packet header. </param>
	/// <param name="Payload"> The pointer to the packet's payload raw bytes.
	///   The pointer is valid only inside an event handler. If an application
	///   needs to use the data outside the event handler it must copy the
	///   payload. </param>
	/// <param name="Size"> The payload size (length) in bytes. </param>
	/// <seealso cref="wclBluetoothLePacketHeader" />
	#define wclBleSnifferRawPacketReceivedEvent(_event_name_) \
		__event void _event_name_( \
			void* Sender, const wclBluetoothLePacketHeader& Header, \
			const unsigned char* const Payload, const unsigned short Size)

	/* General Bluetooth classes and components */

	/// <summary> Supported connection types. </summary>
	typedef enum
	{
		/// <summary> RFCOMM client connection. </summary>
		ctRfCommClient,
		/// <summary> RFCOMM server connection. </summary>
		ctRfCommServer,
		/// <summary> BLE GATT client connection. </summary>
		ctGattClient,
		/// <summary> BLE GATT server connection. </summary>
		ctGattServer,
		/// <summary> BLE beacon watcher connection. </summary>
		ctBeaconWatcher,
		/// <summary> Bluetooth LE advertiser connection. </summary>
		ctLeAdvertiser,
		/// <summary> Wii Remote controller client connection. </summary>
		ctWiiRemote
	} wclBluetoothConnectionType;

	/// <summary> The class represents a local Bluetooth radio module. </summary>
	/// <remarks> <para> An application must never create or destroy this class
	///   directly. Instead of that an application must use methods of the
	///   <see cref="CwclBluetoothManager" /> component. </para>
	///   <para> The class is thread safe. </para>
	///   <para> The only single instance of the class for each supported
	///   Bluetooth driver can be created. </para> </remarks>
	/// <seealso cref="CwclBluetoothManager" />
	class CwclBluetoothRadio
	{
		DISABLE_COPY(CwclBluetoothRadio);

	private:
		friend class CwclRfCommClientConnection;
		friend class CwclRfCommServerConnection;
		friend class CwclGattClientConnection;
		friend class CwclGattServerConnection;
		friend class CwclBluetoothLeBeaconWatcherConnection;
		friend class CwclBluetoothLeAdvertiserConnection;
		friend class CwclWiiRemoteClientConnection;

		friend class CwclRfCommClient;
		friend class CwclRfCommServer;
		friend class CwclGattClient;
		friend class CwclGattServer;
		friend class CwclBluetoothLeAdvertiser;
		friend class CwclBluetoothLeBeaconWatcher;
		friend class CwclWiiRemoteClient;
		
		typedef std::list<CwclCustomConnection*>	CONNECTIONS;

		friend class CwclBluetoothManager;

		// This flag used internally when processing radio state changes messages
		// to protect from same state processing.
		bool						FAvailable;
		// This critical section used as synchronization object for
		// the Radio members and the API manages local Radio settings.
		// It is initialized in the constructor and releases in the destructor.
		RTL_CRITICAL_SECTION		FCS;
		// Discovering flag.
		bool						FDiscovering;
		// Indicates that discovering started message has been received.
		bool						FDiscoveringStarted;
		// The Radio instance protection mutex handle. This mutex created during
		// a Radio object initialization. The mutex is unique per process. If other
		// instance of the Radio class already exists the mutex creation fails and a
		// Bluetooth driver supported by the Radio object will not be initialized.
		HANDLE						FInstance;
		// Indicates LE discovering.
		bool						FLeDiscovering;
		// The loaded flag set when a Bluetooth driver supported by the Radio
		// object has been loaded and initialized.
		bool						FLoaded;
		// The Bluetooth Manager object that owns the Radio.
		CwclBluetoothManager*		FManager;
		// The address of manually pairing device.
		__int64						FPairAddress;
		// The manual pairing operation flag.
		bool						FPairing;
		// Internal flag indicates if the radio hardware is plugged.
		bool						FPlugged;
		// This message receiver created in the constructor. The message receiver is
		// used by the Radio object to receive notifications from a supported
		// Bluetooth driver.
		CwclMessageReceiver*		FReceiver;
		// Used during discovering to filter duplicated devices.
		wclBluetoothAddresses		FFoundDevices;
		// Flag indicates that paired devices must be reported as found even they
		// are not available.
		bool						FIncludePaired;

		CONNECTIONS*				FConnections;
		wclVirtualComPorts			FComPorts;

		// This function initializes the global radio instance mutex.
		int InitializeGlobalInstanceMutex();
		// The function checks if radio supports Bluetooth LE functions. Returns
		// WCL_E_SUCCESS if yes, error otherwise.
		int IsBluetoothLeSupported();

		// Tests if the classic device with given MAC was not found.
		bool DeviceNotFound(const __int64 Address);

		/* Cleanup */

		void CloseAllConnections(const int Reason);
		void DestroyComPorts();

		/* Connections management. */
		
		int CreateConnection(const wclBluetoothConnectionType ConnectionType,
			CwclCustomConnection*& Connection);
		void RegisterConnection(CwclCustomConnection* const Connection, const int Result);
		void RemoveConnection(CwclCustomConnection* const Connection);
		
		/* Radio control methods. */
		
		// This method is called by the Bluetooth Manager when releasing the Radio
		// object. It is guaranteed by the Bluetooth Manager that call to this
		// method is synchronized.
		int Close();
		// This method is called by the Bluetooth Manager to initialize the Radio
		// object and load the supported Bluetooth driver. If call to this method
		// failed the Bluetooth Manager must immediately destroy the Radio object.
		// It is guaranteed by the Bluetooth Manager that call to this method
		// is synchronized.
		int Open();

		/* Message processing. */

		void ProcessStatusChangedMessage();
		void ProcessDiscoveringStartedMessage();
		void ProcessDiscoveringCompletedMessage(const int Error);
		void ProcessDeviceFoundMessage(const CwclMessage* const Message);
		void ProcessIoCapRequestMessage(const __int64 Address);
		void ProcessProtectionRequestMessage(const __int64 Address);
		void ProcessPinRequestMessage(const __int64 Address);
		void ProcessNumericComparisonMessage(const __int64 Address,
			const unsigned long Number);
		void ProcessPasskeyRequestMessage(const __int64 Address);
		void ProcessPasskeyNotificationMessage(const __int64 Address,
			const unsigned long Passkey);
		void ProcessConfirmOnlyMessage(const __int64 Address);
		void ProcessOobDataRequestMessage(const __int64 Address);
		void ProcessAuthCompletedMessage(const __int64 Address, const int Error);
		
	protected:
		/* Internal methods. */
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/// <summary> Fires the <c>OnAuthenticationCompleted</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Error"> An operation result code. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoAuthenticationCompleted(const __int64 Address, const int Error);
		/// <summary> Fires the <c>OnConfirm</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		virtual void DoConfirm(const __int64 Address, bool& Confirm);
		/// <summary> Fires the <c>OnDeviceFound</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		virtual void DoDeviceFound(const __int64 Address);
		/// <summary> Fires the <c>OnDiscoveringCompleted</c> event. </summary>
		/// <param name="Error"> An operation result code. </param>
		virtual void DoDiscoveringCompleted(const int Error);
		/// <summary> Fires the <c>OnDiscoveringStarted</c> event. </summary>
		virtual void DoDiscoveringStarted();
		/// <summary> Fires the <c>OnIoCapabilityRequest</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Mitm"> An application sets this parameter to specify the
		///   "Man in the Middle" protection required for authentication. </param>
		/// <param name="IoCapability"> An application sets this parameter to define
		///   the input/output capabilities of a Bluetooth Device. </param>
		/// <param name="OobPresent"> An application sets this parameter to
		///   <c>True</c> to force Out Of Band authentication. </param>
		/// <seealso cref="wclBluetoothMitmProtection" />
		/// <seealso cref="wclBluetoothIoCapability" />
		virtual void DoIoCapabilityRequest(const __int64 Address,
			wclBluetoothMitmProtection& Mitm, wclBluetoothIoCapability& IoCapability,
			bool& OobPresent);
		/// <summary> Fires the <c>OnNumericComparison</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Number"> A number sent by a remote device to display and
		///   compare. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		virtual void DoNumericComparison(const __int64 Address,
			const unsigned long Number, bool& Confirm);
		/// <summary> Fires the <c>OnOobDataRequest</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="OobData"> An application must set this parameter to
		///   the Out Of Band data received from peer device. </param>
		/// <seealso cref="wclBluetoothOobData" />
		virtual void DoOobDataRequest(const __int64 Address, wclBluetoothOobData& OobData);
		/// <summary> Fores the <c>OnPasskeyNotification</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A Passkey provided by a remote
		///   Bluetooth device. </param>
		virtual void DoPasskeyNotification(const __int64 Address, const unsigned long Passkey);
		/// <summary> Fires the <c>OnPasskeyRequest</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A passkey provided by an application. </param>
		virtual void DoPasskeyRequest(const __int64 Address, unsigned long& Passkey);
		/// <summary> Fires the <c>OnPinRequest</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Pin"> A PIN code provided by an application. </param>
		virtual void DoPinRequest(const __int64 Address, tstring& Pin);
		/// <summary> Fires the <c>OnProtectionLevelRequest</c> event. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Protection"> Describes the required protection
		///   level provided by an application. </param>
		/// <remarks> This method is used only during BLE pairing. </remarks>
		/// <seealso cref="wclBluetoothLeProtectionLevel" />
		virtual void DoProtectionLevelRequest(const __int64 Address,
			wclBluetoothLeProtectionLevel& Protection);
		/// <summary> Fires the <c>OnStatusChanged</c> event. </summary>
		virtual void DoStatusChanged();
		
		/* HAL initialization. */
		
		/// <summary> Implements a driver-dependent code for getting API
		///   functions pointers. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalGetFunctions() = 0;
		/// <summary> Implements a driver-dependent code for API
		///   initialization. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalInitialize() = 0;
		/// <summary> Implements a driver-dependent code for loading API
		///   DLLs. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalLoadApi() = 0;
		/// <summary> Implements a driver-dependent code for callback
		///   registration. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalRegisterCallbacks() = 0;
		/// <summary> Implements a driver-dependent code for setting the Radio object
		///   global instance variable. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalSetGlobalInstance() = 0;

		/* HAL finalization. */
		
		/// <summary> Implements a driver-dependent code for API functions
		///   clearing. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalClearFunctions() = 0;
		/// <summary> Implements a driver-dependent code for clearing the
		///   global instance of the Radio object. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalClearGlobalInstance() = 0;
		/// <summary> Implements a driver-dependent code for pending operation
		///   termination. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalTerminateOperations() = 0;
		/// <summary> Implements a driver-dependent code for driver
		///   uninitialization. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalUninitialize() = 0;
		/// <summary> Implements a driver-dependent code for API
		///   unloading. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalUnloadApi() = 0;
		/// <summary> Implements a driver-dependent code for callbacks
		///   unregistering. </summary>
		/// <remarks> A derived class must override this method. </remarks>
		virtual void HalUnregisterCallbacks() = 0;

		/* HAL local Radio methods. */
		
		/// <summary> Implements a hardware-dependent code for Local Bluetooth
		///   Radio module MAC address reading. </summary>
		/// <param name="Address"> On output the local Bluetooth Radio
		///   address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetAddress(__int64& Address) = 0;
		/// <summary> Implements a hardware-dependent code for Local Bluetooth
		///   Radio module Class Of Device (COD) reading. </summary>
		/// <param name="Cod"> On output the local Bluetooth Radio COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalGetCod(unsigned long& Cod) = 0;
		/// <summary> Implements a hardware-dependent code for reading the local
		///   Bluetooth Radio connectable state. </summary>
		/// <param name="Connectable"> On output the local Bluetooth Radio
		///   connectable state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetConnectable(bool& Connectable) = 0;
		/// <summary> Implements a hardware-dependent code to read the local
		///   Bluetooth Radio discoverable state. </summary>
		/// <param name="Discoverable"> On output the local Bluetooth Radio
		///   discoverable state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetDiscoverable(bool& Discoverable) = 0;
		/// <summary> Implements a hardware-dependent code to reads the HCI version
		///   of the local Radio module. </summary>
		/// <param name="Version"> On output the HCI version number. </param>
		/// <param name="Revision"> On output the HCI revision number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetHciVersion(unsigned char& Version, unsigned short& Revision) = 0;
		/// <summary> Implements a hardware-dependent code to reading the LMP version
		///   of the local Radio module. </summary>
		/// <param name="Version"> On output the LMP version number. </param>
		/// <param name="Subversion"> On output the LMP subversion number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetLmpVersion(unsigned char& Version, unsigned short& Subversion) = 0;
		/// <summary> Implements a hardware-dependent code to read the Bluetooth
		///   Radio manufacturer ID. </summary>
		/// <param name="Manu"> On output the manufacturer ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetManufacturer(unsigned short& Manu) = 0;
		/// <summary> Implements a hardware-dependent code for reading the local
		///   Radio name. </summary>
		/// <param name="Name"> On output the local Bluetooth Radio
		///   name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetName(tstring& Name) = 0;
		
		/// <summary> Implements a hardware-dependent code to changing the
		///   local Bluetooth Radio Class Of Device (COD). </summary>
		/// <param name="Cod"> The new local Bluetooth Radio COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalSetCod(const unsigned long Cod) = 0;
		/// <summary> Implements a hardware-dependent code to changing the
		///   connectable state of the local Bluetooth Radio. </summary>
		/// <param name="Connectable"> The new connectable state for the
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalSetConnectable(const bool Connectable) = 0;
		/// <summary> Implements a hardware-dependent code for changing the
		///   discoverable state of the local Bluetooth Radio. </summary>
		/// <param name="Discoverable"> The new discoverable state for the
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalSetDiscoverable(const bool Discoverable) = 0;
		/// <summary> Implements a hardware-dependent code for changing the local
		///   Bluetooth Radio module name. </summary>
		/// <param name="Name"> The new Radio name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalSetName(const tstring& Name) = 0;

		/// <summary> The method turns the local Bluetooth radio ON. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalTurnOn() = 0;
		/// <summary> The method turns the local Bluetooth radio OFF. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalTurnOff() = 0;

		/* HAL remote devices discovering. */
		
		/// <summary> Implements a hardware-dependent code to start discovering for a
		///   remote Classic Bluetooth devices. </summary>
		/// <param name="Timeout"> Specifies the maximum amount of time before
		///   the inquiry is halted (in seconds). </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalDiscoverClassic(const unsigned char Timeout) = 0;
		/// <summary> Implements a hardware-dependent code to start discovering for a
		///   remote Low Energy Bluetooth devices. </summary>
		/// <param name="Timeout"> Specifies the maximum amount of time before
		///   the inquiry is halted (in seconds). </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalDiscoverBle(const unsigned char Timeout) = 0;
		/// <summary> Implements a hardware-dependent code for discovering
		///   termination. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalTerminate() = 0;

		/// <summary> Implements a hardware-dependent code for paired devices
		///   enumerating. </summary>
		/// <param name="Devices"> On output the dynamic array will be filled with
		///   pared devices MACs. A caller is responsible to free the memory
		///   allocated (if was) for this parameter. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalEnumPairedDevices(wclBluetoothAddresses& Devices) = 0;
		/// <summary> Implements a hardware-dependent code for connected devices
		///   enumerating. </summary>
		/// <param name="Devices"> On output the dynamic array will be filled with
		///   connected devices MACs. A caller is responsible to free the memory
		///   allocated (if was) for this parameter. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalEnumConnectedDevices(wclBluetoothAddresses& Devices) = 0;

		/// <summary> Implements a hardware-dependent code for reading the available
		///   services from a remote Bluetooth device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Uuid"> The pointer to a service's UUID. If an application
		///   need to get information about specific service it set this
		///   parameter to a valid pointer to the required service's UUID.
		///   If this parameter is <c>NULL</c> the information about all available
		///   services will be returned. </param>
		/// <param name="Services"> On output the remote Bluetooth device
		///   services list. An application is responsible to free a memory
		///   allocated for the array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalEnumRemoteServices(const __int64 Address, const GUID* const Uuid,
			wclBluetoothServices& Services) = 0;

		/// <summary> Implements a hardware-dependent code to check if a remote
		///   device is in range. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="InRange"> If the function completed with success
		///   indicates if a remote device is in range. <c>True</c> if a remote
		///   device is in range. <c>False</c> otherwise. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalIsRemoteDeviceInRange(const __int64 Address, bool& InRange) = 0;

		/// <summary> Implements a hardware-dependent code to disconnect a remote
		///   device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalRemoteDisconnect(const __int64 Address) = 0;

		/* HAL remote device functions. */

		/// <summary> Implements a hardware-dependent code for reading a remote
		///   device address type. </summary>
		/// <param name="Address"> A remote Bluetooth enabled device's MAC
		///   address. </param>
		/// <param name="AddrType"> On output a remote device's Address
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothAddressType" />
		virtual int HalGetRemoteAddressType(const __int64 Address,
			wclBluetoothAddressType& AddrType) = 0;
		/// <summary> Implements a hardware-dependent code for reading a remote
		///   device COD (Class Of Device). </summary>
		/// <param name="Address"> A remote Bluetooth enabled device's MAC
		///   address. </param>
		/// <param name="Cod"> On output a remote device's COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetRemoteCod(const __int64 Address, unsigned long& Cod) = 0;
		/// <summary> Implements a hardware-dependent code to reading a remote
		///   Bluetooth device type. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="DevType"> On output a remote Bluetooth device
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothDeviceType" />
		virtual int HalGetRemoteDeviceType(const __int64 Address,
			wclBluetoothDeviceType& DevType) = 0;
		/// <summary> Implements a hardware-dependent code for querying a remote
		///   device's name. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Name"> On output a remote device's name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetRemoteName(const __int64 Address, tstring& Name) = 0;
		/// <summary> Implements a hardware-dependent code for reading a remote
		///   Bluetooth device paired status. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Paired"> On output a remote Bluetooth device paired status.
		///   if <c>True</c> a remote device has been paired with this
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetRemotePaired(const __int64 Address, bool& Paired) = 0;

		/// <summary> The function checks if the specified remote device is
		///   currently connected. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Connected"> On output the connected status of the
		///   remote device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetRemoteConnectedStatus(const __int64 Address, bool& Connected) = 0;
		/// <summary> Reads RSSI value from a remote device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Rssi"> On output contains the RSSI value in dBm. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalGetRemoteRssi(const __int64 Address, char& Rssi) = 0;

		/* HAL Authentication reply. */
		
		/// <summary> Implements a hardware-dependent code to reply on a
		///   confirm only pairing request. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalConfirmReply(const __int64 Address, const bool Confirm) = 0;
		/// <summary> Implements a hardware-dependent code to reply on an
		///   IO capability request. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Mitm"> Specifies the "Man in the Middle" protection
		///   required for authentication. </param>
		/// <param name="IoCapability"> Defines the input/output capabilities of a
		///   Bluetooth Device. </param>
		/// <param name="OobPresent"> If this parameter is <c>True</c> the Out Of
		///   Band authentication will be executed. </param>
		/// <seealso cref="wclBluetoothMitmProtection" />
		/// <seealso cref="wclBluetoothIoCapability" />
		virtual int HalIoCapabilityReply(const __int64 Address,
			const wclBluetoothMitmProtection Mitm,
			const wclBluetoothIoCapability IoCapability, const bool OobPresent) = 0;
		/// <summary> Implements a hardware-dependent code to reply on a
		///   numeric comparison request. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Value"> The numeric value reply. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalNumericComparisonReply(const __int64 Address,
			const unsigned long Value, const bool Confirm) = 0;
		/// <summary> Implements a hardware-dependent code to reply on a
		///   Out Of Band pairing request. </summary>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="OobData"> An Out Of Band pairing data. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothOobData" />
		virtual int HalOobDataReply(const __int64 Address,
			const wclBluetoothOobData& OobData) = 0;
		/// <summary> Implements a hardware-dependent code to reply for a
		///   passkey request event. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Passkey"> A Passkey provided by an application. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalPasskeyReply(const __int64 Address, const unsigned long Passkey) = 0;
		/// <summary> Implements a hardware-dependent code to reply for a
		///   PIN request event. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Pin"> A PIN code provided by an application. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalPinReply(const __int64 Address, const tstring& Pin) = 0;
		/// <summary> Implements a hardware-dependent code to reply for a
		///   pairing protection level request event. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Protection"> A pairing protection level. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothLeProtectionLevel" />
		virtual int HalProtectionLevelReply(const __int64 Address,
			const wclBluetoothLeProtectionLevel Protection) = 0;

		/* HAL authentication. */
		
		/// <summary> Implements a hardware-dependent code for pairing with a remote
		///   Bluetooth device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Method"> The pairing method. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothPairingMethod" />
		virtual int HalRemotePair(const __int64 Address,
			const wclBluetoothPairingMethod Method) = 0;
		/// <summary> Implements a hardware-dependent code to unpair a remote
		///   Bluetooth device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Method"> The unpairing method. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		/// <seealso cref="wclBluetoothPairingMethod" />
		virtual int HalRemoteUnpair(const __int64 Address,
			const wclBluetoothPairingMethod Method) = 0;
		
		/* HAL Secure Simple Pairing management. */
		
		/// <summary> Implements a hardware-dependent code that reads a radio
		///   Secure Simple Pairing mode. </summary>
		/// <param name="Enabled"> If the function completed with success on output
		///   contains a boolean that indicates the current Secure Simple Pairing
		///   (SSP) mode. <c>True</c> if SSP is enabled. <c>False</c> if SSP is
		///   disabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalGetSimplePairingMode(bool& Enabled) = 0;
		/// <summary> Implements a hardware-dependent code that writes a radio
		///   Secure Simple Pairing mode. </summary>
		/// <param name="Enable"> A boolean that indicates the new Secure Simple
		///   Pairing (SSP) mode. Set this parameter to <c>True</c> to enable SSP.
		///   Set this parameter to <c>False</c> to disable SSP. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver-dependent code. </remarks>
		virtual int HalSetSimplePairingMode(const bool Enable) = 0;

		/* HAL connections management. */
		
		/// <summary> Creates a hardware-dependent connection object based on
		///   connection type. </summary>
		/// <param name="ConnectionType"> A type of the required connection
		///   object. </param>
		/// <param name="Connection"> If the function completed with success on
		///   output contains the connection object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothConnectionType" />
		/// <seealso cref="CwclCustomConnection" />
		virtual int HalCreateConnection(const wclBluetoothConnectionType ConnectionType,
			CwclCustomConnection*& Connection) = 0;
		
		/* Virtual COM ports management. */

		/// <summary> Creates new virtual COM port. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <param name="Number"> If function completed with success the
		///   <c>Number</c> parameter contains a just created virtual COM port
		///   number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver (API). </remarks>
		virtual int HalCreateComPort(const __int64 Address, const GUID& Service,
			unsigned short& Number) = 0;
		/// <summary> Destroys the virtual COM port. </summary>
		/// <param name="Number"> The virtual COM port number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver (API). </remarks>
		virtual int HalDestroyComPort(const unsigned short Number) = 0;
		/// <summary> Enumerates already installed Bluetooth virtual COM
		///   ports. </summary>
		/// <param name="ComPorts"> If the function completed with success contains
		///   array of all installed Bluetooth virtual COM ports. If not one vCOM
		///   was found the value of the <c>ComPorts</c> parameter can be
		///   <c>NULL</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The function enumerates all installed Bluetooth virtual
		///   COM ports. The list includes vCOMs created by the application and
		///   vCOMs created by an user outside the application. </para>
		///   <para> A derived class must override this method to provide
		///   information about supported Bluetooth driver (API). </para> </remarks>
		/// <seealso cref="wclVirtualComPorts" />
		virtual int HalEnumComPorts(wclVirtualComPorts& ComPorts) = 0;

		/* Remote Bluetooth device drivers management. */
		
		/// <summary> Enumerates services installed for specified Bluetooth
		///   device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Services"> If the method completed with success on output
		///   contains GUID array of the installed services. If there is no services
		///   installed for the specified device the <c>Services</c> parameter is
		///   an empty array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   hardware dependent code that enumerates installed services. </remarks>
		/// <seealso cref="wclBluetoothInstalledServices" />
		virtual int HalEnumInstalledServices(const __int64 Address,
			wclBluetoothInstalledServices& Services) = 0;
		/// <summary> Install drivers for specified Bluetooth device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   hardware dependent code that installs driver. </remarks>
		virtual int HalInstallDevice(const __int64 Address, const GUID& Service) = 0;
		/// <summary> Uninstall drivers for specified Bluetooth device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   hardware dependent code that uninstalls driver. </remarks>
		virtual int HalUninstallDevice(const __int64 Address, const GUID& Service) = 0;

		/* HAL property getters. */
		
		/// <summary> Returns a Bluetooth API supported by the Radio
		///   object. </summary>
		/// <returns> The <see cref="wclBluetoothApi" /> describes a Bluetooth
		///   driver supported by this object. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver (API). </remarks>
		/// <seealso cref="wclBluetoothApi" />
		virtual wclBluetoothApi HalGetApi() const = 0;
		/// <summary> Returns a supported Bluetooth API name. </summary>
		/// <returns> A name of the supported Bluetooth API. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver (API) name. </remarks>
		virtual tstring HalGetApiName() const = 0;
		/// <summary> Implements a hardware-dependent code to check a Bluetooth
		///   hardware state. </summary>
		/// <returns> Returns <c>True</c> if a Bluetooth hardware is available.
		///   <c>False</c> otherwise. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver. </remarks>
		virtual bool HalGetAvailable() const = 0;
		/// <summary> Implements a hardware-dependent code to check a Bluetooth
		///   hardware physical state. </summary>
		/// <returns> Returns <c>True</c> if a Bluetooth hardware is physically
		///   available. <c>False</c> otherwise. </returns>
		/// <remarks> A derived class must override this method to provide
		///   information about supported Bluetooth driver. </remarks>
		virtual bool HalGetPlugged() const = 0;
		
		/* Helper methods and properties. */
		
		/// <summary> The method checks that a Bluetooth driver and a hardware is
		///   available. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> Any call to this method must be protected by
		///   the local radio Critical Section. </remarks>
		int CheckAvailable() const;
		
		/// <summary> Gets the devices discovering modification flag. </summary>
		/// <returns> The <c>bool</c> value indicates if paired devices must be
		///   returned as found during devices discovering even if they are not
		///   available. <c>true</c> if paired devices must be returned.
		///   <c>false</c> if only available devices must be returned. </returns>
		bool GetIncludePaired() const;
		/// <summary> Gets the devices discovering modification flag. </summary>
		/// <value> The <c>bool</c> value indicates if paired devices must be
		///   returned as found during devices discovering even if they are not
		///   available. <c>true</c> if paired devices must be returned.
		///   <c>false</c> if only available devices must be returned. </value>
		__declspec(property(get = GetIncludePaired)) bool IncludePaired;

		/// <summary> Gets the discovering type flag. </summary>
		/// <returns> <c>True</c> if LE discovering is executing. <c>False</c> if
		///   classic discovering is executing. </returns>
		bool GetLeDiscovering() const;
		/// <summary> Gets the discovering type flag. </summary>
		/// <value> <c>True</c> if LE discovering is executing. <c>False</c> if
		///   classic discovering is executing. </value>
		__declspec(property(get = GetLeDiscovering)) bool LeDiscovering;

		/// <summary> Gets the message processing method used by the
		///   Radio. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Gets the message processing method used by the
		///   Radio. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		__declspec(property(get = GetMessageProcessing)) wclMessageProcessingMethod MessageProcessing;

		/// <summary> Gets the message receiver object. </summary>
		/// <returns> A <see cref="CwclMessageReceiver" /> object used in
		///   radio. </returns>
		/// <remarks> For internal use only. </remarks>
		/// <seealso cref="CwclMessageReceiver" />
		CwclMessageReceiver* GetReceiver() const;
		/// <summary> Gets the message receiver object. </summary>
		/// <value> A <see cref="CwclMessageReceiver" /> object used in
		///   radio. </value>
		/// <remarks> For internal use only. </remarks>
		/// <seealso cref="CwclMessageReceiver" />
		__declspec(property(get = GetReceiver)) CwclMessageReceiver* Receiver;

		/// <summary> Gets the ID of the thread in which Radio was created. It is
		///   the same thread that was used to call BluetoothManager.Open()
		///   method. </summary>
		/// <returns> The thread ID. </returns>
		UINT GetThreadId() const;
		/// <summary> Gets the ID of the thread in which Radio was created. It is
		///   the same thread that was used to call BluetoothManager.Open()
		///   method. </summary>
		/// <value> The thread ID. </value>
		__declspec(property(get = GetThreadId)) UINT ThreadId;

		/// <summary> Gets the pairing device address for manual pairing. </summary>
		/// <returns> A pairing device address. </returns>
		/// <remarks> For internal use only. </remarks>
		__int64 GetPairAddress() const;
		/// <summary> Gets the pairing device address for manual pairing. </summary>
		/// <value> A pairing device address. </value>
		/// <remarks> For internal use only. </remarks>
		__declspec(property(get = GetPairAddress)) __int64 PairAddress;

	public:
		/// <summary> Creates a new radio object. </summary>
		/// <param name="Manager"> The <see cref="CwclBluetoothManager" /> object
		///   that creates and owns the Radio. </param>
		/// <remarks> An application must never create the Radio objects directly.
		///   Instead of that an application must use methods of the
		///   <c>CwclBluetoothManager</c> component. </remarks>
		/// <seealso cref="CwclBluetoothManager" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothRadio(CwclBluetoothManager* const Manager);
		/// <summary> Frees the Radio object. </summary>
		/// <remarks> An application must never destroy a Radio object directly.
		///   Instead of that an application must use methods of the
		///   <c>CwclBluetoothManager</c> component. </remarks>
		virtual ~CwclBluetoothRadio();

		/* Local radio methods. */
		
		/// <summary> Reads the local Bluetooth Radio MAC address. </summary>
		/// <param name="Address"> On output the local Bluetooth Radio
		///   address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetAddress(__int64& Address);
		/// <summary> Gets the radio Bluetooth version. </summary>
		/// <param name="Version"> If the method completed with success on output
		///   contains the Radio's Bluetooth version. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothVersion" />
		int GetBluetoothVersion(wclBluetoothVersion& Version);
		/// <summary> Reads the local Bluetooth Radio Class Of Device
		///   (COD). </summary>
		/// <param name="Cod"> On output the local Bluetooth Radio COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetCod(unsigned long& Cod);
		/// <summary> Read the local Bluetooth Radio connectable state. </summary>
		/// <param name="Connectable"> On output the local Bluetooth Radio
		///   connectable state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> If the returned <c>Connectable</c> parameter value
		///   is <c>True</c> remote Bluetooth enabled devices can connect to
		///   this Radio. </para>
		///   <para> If the value of the <c>Connectable</c> parameter is
		///   <c>False</c> remote Bluetooth enabled devices can not connect to the
		///   Radio. </para> </remarks>
		int GetConnectable(bool& Connectable);
		/// <summary> Read the local Bluetooth Radio discoverable state. </summary>
		/// <param name="Discoverable"> On output the local Bluetooth Radio
		///   discoverable state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> If the returned <c>Discoverable</c> parameter value
		///   is <c>True</c> remote Bluetooth enabled devices can discover this
		///   Radio. </para>
		///   <para> If the value of the <c>Discoverable</c> parameter is
		///   <c>False</c> remote Bluetooth enabled devices can not discover the
		///   Radio. </para> </remarks>
		int GetDiscoverable(bool& Discoverable);
		/// <summary> Reads the HCI version of the local Radio module. </summary>
		/// <param name="Version"> On output the HCI version number. </param>
		/// <param name="Revision"> On output the HCI revision number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The HCI version assignment numbers: </para>
		///           <para> 0 - Bluetooth Core Specification 1.0b </para>
		///           <para> 1 - Bluetooth Core Specification 1.1 </para>
		///           <para> 2 - Bluetooth Core Specification 1.2 </para>
		///           <para> 3 - Bluetooth Core Specification 2.0 + EDR </para>
		///           <para> 4 - Bluetooth Core Specification 2.1 + EDR </para>
		///           <para> 5 - Bluetooth Core Specification 3.0 + HS </para>
		///           <para> 6 - Bluetooth Core Specification 4.0 </para>
		///           <para> 7 - Bluetooth Core Specification 4.1 </para>
		///           <para> 8 - Bluetooth Core Specification 4.2 </para>
		///           <para> 9 - Bluetooth Core Specification 5.0 </para>
		///           <para> 10 - Bluetooth Core Specification 5.1 </para>
		///           <para> 11 - Bluetooth Core Specification 5.2 </para>
		///           <para> 12 - Bluetooth Core Specification 5.3 </para>
		///           <para> 13 - Bluetooth Core Specification 5.4 </para>
		///           <para> 14-255 - Reserved </para> </remarks>
		int GetHciVersion(unsigned char& Version, unsigned short& Revision);
		/// <summary> Reads the LMP version of the local Radio module. </summary>
		/// <param name="Version"> On output the LMP version number. </param>
		/// <param name="Subversion"> On output the LMP subversion number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The LMP version assignment numbers: </para>
		///           <para> 0 - Bluetooth Core Specification 1.0b </para>
		///           <para> 1 - Bluetooth Core Specification 1.1 </para>
		///           <para> 2 - Bluetooth Core Specification 1.2 </para>
		///           <para> 3 - Bluetooth Core Specification 2.0 + EDR </para>
		///           <para> 4 - Bluetooth Core Specification 2.1 + EDR </para>
		///           <para> 5 - Bluetooth Core Specification 3.0 + HS </para>
		///           <para> 6 - Bluetooth Core Specification 4.0 </para>
		///           <para> 7 - Bluetooth Core Specification 4.1 </para>
		///           <para> 8 - Bluetooth Core Specification 4.2 </para>
		///           <para> 9 - Bluetooth Core Specification 5.0 </para>
		///           <para> 10 - Bluetooth Core Specification 5.1 </para>
		///           <para> 11 - Bluetooth Core Specification 5.2 </para>
		///           <para> 12 - Bluetooth Core Specification 5.3 </para>
		///           <para> 13 - Bluetooth Core Specification 5.4 </para>
		///           <para> 14-255 - Reserved </para> </remarks>
		int GetLmpVersion(unsigned char& Version, unsigned short& Subversion);
		/// <summary> Reads the Bluetooth Radio manufacturer ID. </summary>
		/// <param name="Manu"> On output the manufacturer ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The full list of the manufacturers ID can be found on the
		///   Bluetooth SIG website by this link
		///   https://www.bluetooth.com/specifications/assigned-numbers/company-Identifiers </remarks>
		int GetManufacturer(unsigned short& Manu);
		/// <summary> Reads the local Radio name. </summary>
		/// <param name="Name"> On output the local Bluetooth Radio
		///   name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetName(tstring& Name);

		/// <summary> Changes the local Bluetooth Radio Class Of Device
		///   (COD). </summary>
		/// <param name="Cod"> The new local Bluetooth Radio COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetCod(const unsigned long Cod);
		/// <summary> Changes the connectable state of the local Bluetooth
		///   Radio. </summary>
		/// <param name="Connectable"> The new connectable state for the
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Setting the <c>Conenctable</c> parameter to <c>True</c>
		///   allows remote Bluetooth enabled devices to connect to this
		///   Radio. </para>
		///   <para> Setting the <c>Conenctable</c> parameter to <c>False</c>
		///   blocks the Radio from remote Bluetooth enabled devices
		///   connecting. </para>
		///   <para> <c>Microsoft</c>: A radio that is non-connectable is
		///   non-discoverable. The radio must be made non-discoverable prior to
		///   making a radio non-connectable. Failure to make a radio
		///   non-discoverable prior to making it non-connectable will result in
		///   failure of this method call. </para> </remarks>
		int SetConnectable(const bool Connectable);
		/// <summary> Changes the discoverable state of the local Bluetooth
		///   Radio. </summary>
		/// <param name="Discoverable"> The new discoverable state for the
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Setting the <c>Discoverable</c> parameter to
		///   <c>True</c> allows remote Bluetooth enabled devices to discover this
		///   Radio. </para>
		///   <para> Setting the <c>Discoverable</c> parameter to <c>False</c>
		///   blocks the Radio from discovering by remote Bluetooth enabled
		///   devices. </para>
		///   <para> <c>Microsoft</c>: Use the <c>GetDiscoverable</c> method to
		///   determine the current state of a Bluetooth radio. Windows ensures that
		///   a discoverable system is connectable, and as such, the radio must
		///   allow incoming connections prior to making a radio discoverable.
		///   Failure to allow incoming connections results in the
		///   <c>SetDiscoverable</c> method call failing. </para>
		///   <para> When <c>SetDiscoverable</c> changes the discovery state, the
		///   new state is valid for the lifetime of the calling application.
		///   Additionally, if a Bluetooth radio previously made discoverable with
		///   this function is disabled and re-enabled via the application,
		///   discoverability will not persist. Once the calling application
		///   terminates, the discovery state of the specified Bluetooth radio
		///   reverts to the state it was in before <c>SetDiscoverable</c> was
		///   called. </para> </remarks>
		int SetDiscoverable(const bool Discoverable);
		/// <summary> Sets a new name for the local Bluetooth Radio
		///   module. </summary>
		/// <param name="Name"> The new Radio name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetName(const tstring& Name);

		/// <summary> The method turns the local Bluetooth radio ON. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int TurnOn();
		/// <summary> The method turns the local Bluetooth radio OFF. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int TurnOff();

		/* Remote devices discovering. */

		/// <summary> Starts discovering for a remote Bluetooth enabled
		///   devices. </summary>
		/// <param name="Timeout"> Specifies the maximum amount of time before
		///   the inquiry is halted (in seconds). </param>
		/// <param name="Kind"> Specifies the discovered Bluetooth device
		///   types. </param>
		/// <param name="IncludePaired"> Set this parameter to <c>true</c> if you
		///   need to get paired devices reported as just found even such devices
		///   are not available. If this parameter is <c>false</c> only available
		///   devices will be returned. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> If the discovering started the
		///   <c>OnDiscoveringStarted</c> event of the
		///   <see cref="CwclBluetoothManager" /> component fires. </para>
		///   <para> When the discovering for the remote Bluetooth enabled devices
		///   completed (with or without success) the <c>OnDiscoveringCompleted</c>
		///   event of the <see cref="CwclBluetoothManager" /> component
		///   fires. </para> </remarks>
		/// <seealso cref="wclBluetoothDiscoverKind" />
		int Discover(const unsigned char Timeout, const wclBluetoothDiscoverKind Kind,
			const bool IncludePaired = false);
		/// <summary> Terminates the discovering of remote Bluetooth enabled
		///   devices. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> On legacy Windows (Windows XP, Vista, 7, 8 and 8.1) platforms
		///   with Microsoft Bluetooth drivers the Terminate method does not
		///   terminate discovering but simple indicates that the discovering result
		///   should be ignored and keeps discovering thread runs in background.
		///   If you call the <c>Close</c> method right after Terminate call and
		///   the discovering has not been completed yet you may get delay with the
		///   <c>Close</c> method return because it has to wait for the discovering
		///   thread completion. </remarks>
		int Terminate();
		
		/// <summary> The method enumerates already paired devices. </summary>
		/// <param name="Devices"> On output the dynamic array will be filled with
		///   pared devices MACs. A caller is responsible to free the memory
		///   allocated (if was) for this parameter. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnumPairedDevices(wclBluetoothAddresses& Devices);
		/// <summary> The method enumerates already paired devices. </summary>
		/// <param name="Kind"> Enumeration method: LE or Classic. </param>
		/// <param name="Devices"> On output the dynamic array will be filled with
		///   pared devices MACs. A caller is responsible to free the memory
		///   allocated (if was) for this parameter. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothDiscoverKind" />
		int EnumPairedDevices(const wclBluetoothDiscoverKind Kind,
			wclBluetoothAddresses& Devices);
		/// <summary> The method enumerates connected devices. </summary>
		/// <param name="Devices"> On output the dynamic array will be filled with
		///   connected devices MACs. A caller is responsible to free the memory
		///   allocated (if was) for this parameter. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnumConnectedDevices(wclBluetoothAddresses& Devices);

		/// <summary> Reads the available services from a remote Bluetooth
		///   device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Uuid"> The pointer to a service's UUID. If an application
		///   need to get information about specific service it set this
		///   parameter to a valid pointer to the required service's UUID.
		///   If this parameter is <c>NULL</c> the information about all available
		///   services will be returned. </param>
		/// <param name="Services"> On output the remote Bluetooth device
		///   services list. An application is responsible to free a memory
		///   allocated for the array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnumRemoteServices(const __int64 Address, const GUID* const Uuid,
			wclBluetoothServices& Services);

		/// <summary> Checks if a remote device is in range. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="InRange"> If the function completed with success
		///   indicates if a remote device is in range. <c>True</c> if a remote
		///   device is in range. <c>False</c> otherwise. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This function supports Classic Bluetooth devices
		///   only. </remarks>
		int IsRemoteDeviceInRange(const __int64 Address, bool& InRange);

		/// <summary> Forces a remote device disconnection. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC address. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This method can be used to disconnect a remote Bluetooth
		///   enabled device with the given MAC address. It can disconnect any
		///   Bluetooth enabled device even a connection was made by the system and
		///   outside Bluetooth Framework. </remarks>
		int RemoteDisconnect(const __int64 Address);

		/* Remote device functions. */

		/// <summary> Reads a remote device address type. </summary>
		/// <param name="Address"> A remote Bluetooth enabled device's MAC
		///   address. </param>
		/// <param name="AddrType"> On output a remote device's Address
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothAddressType" />
		int GetRemoteAddressType(const __int64 Address, wclBluetoothAddressType& AddrType);
		/// <summary> Reads a remote device COD (Class Of Device). </summary>
		/// <param name="Address"> A remote Bluetooth enabled device's MAC
		///   address. </param>
		/// <param name="Cod"> On output a remote device's COD. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetRemoteCod(const __int64 Address, unsigned long& Cod);
		/// <summary> Read a remote Bluetooth device type. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="DevType"> On output a remote Bluetooth device
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothDeviceType" />
		int GetRemoteDeviceType(const __int64 Address, wclBluetoothDeviceType& DevType);
		/// <summary> Queries a remote device's name. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Name"> On output a remote device's name. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetRemoteName(const __int64 Address, tstring& Name);
		/// <summary> Reads a remote Bluetooth device paired status. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Paired"> On output a remote Bluetooth device paired status.
		///   if <c>True</c> a remote device has been paired with this
		///   Radio. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetRemotePaired(const __int64 Address, bool& Paired);

		/// <summary> The function checks if the specified remote device is
		///   currently connected. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Connected"> On output the connected status of the
		///   remote device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetRemoteConnectedStatus(const __int64 Address, bool& Connected);
		/// <summary> Reads RSSI value from a remote device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Rssi"> On output contains the RSSI value in dBm. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> Some devices require active connection to measure RSSI. If the method
		///   returns error an application can try to enumerate a device's services
		///   and immediately after that query RSSI once again. </remarks>
		int GetRemoteRssi(const __int64 Address, char& Rssi);

		/* Authentication. */

		/// <summary> Starts pairing with a remote Bluetooth device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Method"> The pairing method. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothPairingMethod" />
		int RemotePair(const __int64 Address,
			const wclBluetoothPairingMethod Method = pmAuto);
		/// <summary> Unpair a remote Bluetooth device. </summary>
		/// <param name="Address"> The remote Bluetooth device's MAC
		///   address. </param>
		/// <param name="Method"> The unpairing method. </param>
		/// <param name="Force"> Set this parameter to <c>true</c> to disable device
		///   pairing state and force unpairing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothPairingMethod" />
		int RemoteUnpair(const __int64 Address,
			const wclBluetoothPairingMethod Method = pmAuto,
			const bool Force = false);

		/* Secure Simple Pairing management. */
		
		/// <summary> Gets the radio Secure Simple Pairing mode. </summary>
		/// <param name="Enabled"> If the function completed with success on output
		///   contains a boolean that indicates the current Secure Simple Pairing
		///   (SSP) mode. <c>True</c> if SSP is enabled. <c>False</c> if SSP is
		///   disabled. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetSimplePairingMode(bool& Enabled);
		/// <summary> Sets the radio Secure Simple Pairing mode. </summary>
		/// <param name="Enable"> A boolean that indicates the new Secure Simple
		///   Pairing (SSP) mode. Set this parameter to <c>True</c> to enable SSP.
		///   Set this parameter to <c>False</c> to disable SSP. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetSimplePairingMode(const bool Enable);

		/* Virtual COM ports management. */

		/// <summary> Creates new virtual COM port. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <param name="Number"> If function completed with success the
		///   <c>Number</c> parameter contains a just created virtual COM port
		///   number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> A created vCOM is valid only while radio object is
		///   available. </para>
		///   <para> The <c>Service</c> parameter can be Serial Port Profile or
		///   DialUp Networking Profile UUID. </para> </remarks>
		int CreateComPort(const __int64 Address, const GUID& Service, unsigned short& Number);
		/// <summary> Destroys the virtual COM port. </summary>
		/// <param name="Number"> The virtual COM port number. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The function can destroy a vCOM created by the application
		///   only. It can not destroy the vCOM created outside the
		///   application. </remarks>
		int DestroyComPort(const unsigned short Number);
		/// <summary> Enumerates already installed Bluetooth virtual COM
		///   ports. </summary>
		/// <param name="ComPorts"> If the function completed with success contains
		///   array of all installed Bluetooth virtual COM ports. If not one vCOM
		///   was found the value of the <c>ComPorts</c> parameter can be
		///   <c>NULL</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The function enumerates all installed Bluetooth virtual COM
		///   ports. The list includes vCOMs created by the application and vCOMs
		///   created by an user outside the application. </remarks>
		/// <seealso cref="wclVirtualComPorts" />
		int EnumComPorts(wclVirtualComPorts& ComPorts);
		
		/* Remote Bluetooth device drivers management. */
		
		/// <summary> Enumerates services installed for specified Bluetooth
		///   device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Services"> If the method completed with success on output
		///   contains GUID array of the installed services. If there is no services
		///   installed for the specified device the <c>Services</c> parameter is
		///   an empty array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothInstalledServices" />
		int EnumInstalledServices(const __int64 Address, wclBluetoothInstalledServices& Services);
		/// <summary> Install drivers for specified Bluetooth device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported with Microsoft Bluetooth
		///   drivers only. </remarks>
		int InstallDevice(const __int64 Address, const GUID& Service);
		/// <summary> Uninstall drivers for specified Bluetooth device. </summary>
		/// <param name="Address"> Remote device address. </param>
		/// <param name="Service"> A service's UUID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported with Microsoft Bluetooth
		///   drivers only. </remarks>
		int UninstallDevice(const __int64 Address, const GUID& Service);
			
		/* Properties. */

		/// <summary> Gets a Bluetooth driver (API) supported by this Bluetooth
		///   object. </summary>
		/// <returns> The Bluetooth API value. </returns>
		/// <seealso cref="wclBluetoothApi" />
		wclBluetoothApi GetApi() const;
		/// <summary> Gets a Bluetooth driver (API) supported by this Bluetooth
		///   object. </summary>
		/// <value> The Bluetooth API value. </value>
		/// <seealso cref="wclBluetoothApi" />
		__declspec(property(get = GetApi)) wclBluetoothApi Api;
	    
		/// <summary> Gets a supported Bluetooth API name. </summary>
		/// <returns> A string representation of the supported Bluetooth API. </returns>
		tstring GetApiName() const;
		/// <summary> Gets a supported Bluetooth API name. </summary>
		/// <value> A string representation of the supported Bluetooth API. </value>
		__declspec(property(get = GetApiName)) tstring ApiName;
	    
		/// <summary> Gets a Radio hardware state. </summary>
		/// <returns> <c>True</c> if a Bluetooth hardware represented by this Radio
		///   is available. <c>False</c> otherwise. </returns>
		bool GetAvailable() const;
		/// <summary> Gets a Radio hardware state. </summary>
		/// <value> <c>True</c> if a Bluetooth hardware represented by this Radio
		///   is available. <c>False</c> otherwise. </value>
		__declspec(property(get = GetAvailable)) bool Available;

		/// <summary> Gets the Classic Bluetooth support status. </summary>
		/// <returns> Returns <c>true</c> if the Radio is available and supports
		///   Classic Bluetooth. Returns <c>false</c> otherwise. </returns>
		/// <remarks> If the Radio supports Classic Bluetooth but is not available a
		///   returning value is <c>false</c>. </remarks>
		bool GetClassicSupported() const;
		/// <summary> Gets the Classic Bluetooth support status. </summary>
		/// <value> Returns <c>true</c> if the Radio is available and supports
		///   Classic Bluetooth. Returns <c>false</c> otherwise. </value>
		/// <remarks> If the Radio supports Classic Bluetooth but is not available a
		///   returning value is <c>false</c>. </remarks>
		__declspec(property(get = GetClassicSupported)) bool ClassicSupported;
		
		/// <summary> Gets the array of the created virtual COM ports. </summary>
		/// <returns> The virtual COM ports array. </returns>
		/// <seealso cref="wclVirtualComPorts" />
		wclVirtualComPorts GetComPorts() const;
		/// <summary> Gets the array of the created virtual COM ports. </summary>
		/// <value> The virtual COM ports array. </value>
		/// <seealso cref="wclVirtualComPorts" />
		__declspec(property(get = GetComPorts)) wclVirtualComPorts ComPorts;
	    
		/// <summary> Gets discovering state. </summary>
		/// <returns> <c>True</c> if discovering is executing on this Radio. </returns>
		bool GetDiscovering() const;
		/// <summary> Gets discovering state. </summary>
		/// <value> <c>True</c> if discovering is executing on this Radio. </value>
		__declspec(property(get = GetDiscovering)) bool Discovering;

		/// <summary> Gets the Bluetooth Low Energy support status. </summary>
		/// <returns> Returns <c>true</c> if the Radio is available and supports
		///   Bluetooth Low Energy. Returns <c>false</c> otherwise. </returns>
		/// <remarks> If the Radio supports BLE but is not available a returning
		///   value is <c>false</c>. </remarks>
		bool GetLeSupported() const;
		/// <summary> Gets the Bluetooth Low Energy support status. </summary>
		/// <value> Returns <c>true</c> if the Radio is available and supports
		///   Bluetooth Low Energy. Returns <c>false</c> otherwise. </returns>
		/// <remarks> If the Radio supports BLE but is not available a returning
		///   value is <c>false</c>. </value>
		__declspec(property(get = GetLeSupported)) bool LeSupported;
		
		/// <summary> Gets the <see cref="CwclBluetoothManager" /> object that owns
		///   the Radio. </summary>
		/// <returns> The <see cref="CwclBluetoothManager" /> object. </returns>
		/// <seealso cref="CwclBluetoothManager" />
		CwclBluetoothManager* GetManager() const;
		/// <summary> Gets the <see cref="CwclBluetoothManager" /> object that owns
		///   the Radio. </summary>
		/// <value> The <see cref="CwclBluetoothManager" /> object. </value>
		/// <seealso cref="CwclBluetoothManager" />
		__declspec(property(get = GetManager)) CwclBluetoothManager* Manager;
		
		/// <summary> Gets a manual pairing state. </summary>
		/// <returns> <c>True</c> if manual remote device pairing operation is
		///   executing. <c>False</c> otherwise. </returns>
		bool GetPairing() const;
		/// <summary> Gets a manual pairing state. </summary>
		/// <value> <c>True</c> if manual remote device pairing operation is
		///   executing. <c>False</c> otherwise. </value>
		__declspec(property(get = GetPairing)) bool Pairing;

		/// <summary> Gets a Radio hardware physical state. </summary>
		/// <returns> <c>True</c> if a Bluetooth hardware represented by this Radio
		///   is physically connected. <c>False</c> otherwise. </returns>
		bool GetPlugged() const;
		/// <summary> Gets a Radio hardware physical state. </summary>
		/// <value> <c>True</c> if a Bluetooth hardware represented by this Radio
		///   is physically connected. <c>False</c> otherwise. </value>
		__declspec(property(get = GetPlugged)) bool Plugged;
	};

	/// <summary> The Bluetooth Manager component. </summary>
	/// <remarks> <para> The <c>CwclBluetoothManager</c> is the main component of
	///   the Bluetooth Framework. Each application that uses the Bluetooth
	///   Framework must have one and only one active instance of the
	///   Bluetooth Manager. </para>
	///   <para> This component must be created and opened in an application's
	///   main thread only. </para> </remarks>
	class CwclBluetoothManager
	{
		DISABLE_COPY(CwclBluetoothManager);

	private:
		friend class CwclBluetoothRadio;

		typedef std::list<CwclBluetoothRadio*>	RADIOS;

		bool						FActive;
		RTL_CRITICAL_SECTION		FCS;
		bool						FHandlePairing;
		HANDLE						FInstance;
		wclMessageProcessingMethod	FMessageProcessing;
		RADIOS*						FRadios;
		CwclMessageReceiver*		FReceiver;
		UINT						FThreadId;
		bool						FUseBled112;

		void MessageReceived(const CwclMessage* const Message);

		// Opens the radio and adds it into the radios list (if success).
		void AddRadio(CwclBluetoothRadio* const Radio);
		
	protected:
		/// <summary> Fires the <c>AfterOpen</c> event. </summary>
		virtual void DoAfterOpen();
		/// <summary> Fires the <c>OnAuthenticationCompleted</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Error"> An operation result code. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoAuthenticationCompleted(CwclBluetoothRadio* const Radio,
			const __int64 Address, const int Error);
		/// <summary> Fires the <c>BeforeClose</c> event. </summary>
		virtual void DoBeforeClose();
		/// <summary> Fires the <c>OnClosed</c> event. </summary>
		virtual void DoClosed();
		/// <summary> Fires the <c>OnConfirm</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoConfirm(CwclBluetoothRadio* const Radio, const __int64 Address,
			bool& Confirm);
		/// <summary> Fires the <c>OnDeviceFound</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoDeviceFound(CwclBluetoothRadio* const Radio, const __int64 Address);
		/// <summary> Fires the <c>OnDiscoveringCompleted</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Error"> An operation result code. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoDiscoveringCompleted(CwclBluetoothRadio* const Radio, const int Error);
		/// <summary> Fires the <c>OnDiscoveringStarted</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoDiscoveringStarted(CwclBluetoothRadio* const Radio);
		/// <summary> Fires the <c>OnIoCapabilityRequest</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Mitm"> An application sets this parameter to specify the
		///   "Man in the Middle" protection required for authentication. </param>
		/// <param name="IoCapability"> An application sets this parameter to define
		///   the input/output capabilities of a Bluetooth Device. </param>
		/// <param name="OobPresent"> An application sets this parameter to
		///   <c>True</c> to force Out Of Band authentication. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <seealso cref="wclBluetoothMitmProtection" />
		/// <seealso cref="wclBluetoothIoCapability" />
		virtual void DoIoCapabilityRequest(CwclBluetoothRadio* const Radio,
			const __int64 Address, wclBluetoothMitmProtection& Mitm,
			wclBluetoothIoCapability& IoCapability, bool& OobPresent);
		/// <summary> Fires the <c>OnNumericComparison</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Number"> A number sent by a remote device to display and
		///   compare. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoNumericComparison(CwclBluetoothRadio* const Radio, const __int64 Address,
			const unsigned long Number, bool& Confirm);
		/// <summary> Fires the <c>OnOobDataRequest</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="OobData"> An application must set this parameter to
		///   the Out Of Band data received from peer device. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <seealso cref="wclBluetoothOobData" />
		virtual void DoOobDataRequest(CwclBluetoothRadio* const Radio, const __int64 Address,
			wclBluetoothOobData& OobData);
		/// <summary> Fores the <c>OnPasskeyNotification</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A Passkey provided by a remote
		///   Bluetooth device. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoPasskeyNotification(CwclBluetoothRadio* const Radio, const __int64 Address,
			const unsigned long Passkey);
		/// <summary> Fires the <c>OnPasskeyRequest</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A passkey provided by an application. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoPasskeyRequest(CwclBluetoothRadio* const Radio, const __int64 Address,
			unsigned long& Passkey);
		/// <summary> Fires the <c>OnPinRequest</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Pin"> A PIN code provided by an application. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoPinRequest(CwclBluetoothRadio* const Radio, const __int64 Address,
			tstring& Pin);
		/// <summary> Fires the <c>OnProtectionLevelRequest</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Protection"> Describes the required protection
		///   level provided by an application. </param>
		/// <remarks> This method is used only during BLE pairing. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <seealso cref="wclBluetoothLeProtectionLevel" />
		virtual void DoProtectionLevelRequest(CwclBluetoothRadio* const Radio,
			const __int64 Address, wclBluetoothLeProtectionLevel& Protection);
		/// <summary> Fires the <c>OnStatusChanged</c> event. </summary>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		virtual void DoStatusChanged(CwclBluetoothRadio* const Radio);

	public:
		/// <summary> Creates a new Bluetooth Manager component. </summary>
		/// <remarks> The component must always be created in an application's
		///   main thread. </remarks>
		CwclBluetoothManager();
		/// <summary> Frees the component. </summary>
		/// <remarks> The component must always be destroyed in an application's
		///   main thread. </remarks>
		virtual ~CwclBluetoothManager();

		/// <summary> Closes the Bluetooth Manager and releases all allocated
		///   resources. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> After calling this method an application should not use
		///   any of the Bluetooth Framework features. All instances of the
		///   <see cref="CwclBluetoothRadio" /> class are not valid after
		///   calling this method. </para>
		///   <para> An application must call this method from its main thread
		///   only. </para>
		///   <para> The call to this method may take some time because it requires
		///   to release all allocated resources and terminate all the running
		///   threads. The common case when the delay may appear is when your
		///   application started discovering for remote devices and right after
		///   that the Close was called. In this case Bluetooth Manager has to wait
		///   for discovering thread completion. </para> </remarks>
		int Close();
		/// <summary> Opens the Bluetooth Manager and allocated required
		///   hardware resources. </summary>
		/// <param name="Apis"> The set of APIs the should be used by Bluetooth
		///   Framework. </param>
		/// <param name="HandlePairing"> Allows to disable pairing handling by
		///   Bluetooth Framework. Set this to <c>false</c> to disable Bluetooth
		///   Framework pairing. Set to <c>true</c> (the default value) to enable
		///   Bluetooth Framework pairing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application must call this method before using any
		///   of the Bluetooth Framework features. </para>
		///   <para> An application must call this method from its main thread
		///   only. </para> </remarks>
		/// <seealso cref="wclBluetoothApis" />
		int Open(const wclBluetoothApis Apis, const bool HandlePairing = true);
		/// <summary> Opens the Bluetooth Manager and allocated required
		///   hardware resources. </summary>
		/// <param name="HandlePairing"> Allows to disable pairing handling by
		///   Bluetooth Framework. Set this to <c>false</c> to disable Bluetooth
		///   Framework pairing. Set to <c>true</c> (the default value) to enable
		///   Bluetooth Framework pairing. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application must call this method before using any
		///   of the Bluetooth Framework features. </para>
		///   <para> An application must call this method from its main thread
		///   only. </para> </remarks>
		int Open(const bool HandlePairing = true);

		/// <summary> Gets the first available Radio object. </summary>
		/// <param name="Radio"> If the function completed with success on output
		///   contains the first found available Bluetooth Radio object. Otherwise
		///   the parameter contains <c>NULL</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int GetRadio(CwclBluetoothRadio*& Radio) const;
		/// <summary> Gets the first available Radio object that supports Bluetooth
		///   Low Energy features. </summary>
		/// <param name="Radio"> If the function completed with success on output
		///   contains the first found available Bluetooth Radio object. Otherwise
		///   the parameter contains <c>NULL</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int GetLeRadio(CwclBluetoothRadio*& Radio) const;
		/// <summary> Gets the first available Radio object that supports Classic
		///   Bluetooth features. </summary>
		/// <param name="Radio"> If the function completed with success on output
		///   contains the first found available Bluetooth Radio object. Otherwise
		///   the parameter contains <c>NULL</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int GetClassicRadio(CwclBluetoothRadio*& Radio) const;

		/// <summary> Gets the Bluetooth Manager state. </summary>
		/// <returns> <c>True</c> if the Bluetooth Manager is active
		///   (opened). </returns>
		bool GetActive() const;
		/// <summary> Gets the Bluetooth Manager state. </summary>
		/// <value> <c>True</c> if the Bluetooth Manager is active
		///   (opened). </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets the number of available Bluetooth Radios. </summary>
		/// <returns> The number of available Bluetooth Radios. </returns>
		size_t GetCount() const;
		/// <summary> Gets the number of available Bluetooth Radios. </summary>
		/// <value> The number of available Bluetooth Radios. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets the discovering state. </summary>
		/// <returns> <c>True</c> if at least one radio is in discovering state.
		///   <c>False</c> otherwise. </returns>
		bool GetDiscovering();
		/// <summary> Gets the discovering state. </summary>
		/// <value> <c>True</c> if at least one radio is in discovering state.
		///   <c>False</c> otherwise. </value>
		__declspec(property(get = GetDiscovering)) bool Discovering;

		/// <summary> Gets the pairing handling flag. </summary>
		/// <returns> The pairing handling state. <c>True</c> if the pairing is
		///   handled by Bluetooth Framework. <c>False</c> if the pairing is handled
		///   by the system. </returns>
		/// <remarks> This flag doe snot affect <c>Bled112</c> USB dongle because
		///   it does not have any support from the OS. </remarks>
		bool GetHandlePairing() const;
		/// <summary> Gets the pairing handling flag. </summary>
		/// <value> The pairing handling state. <c>True</c> if the pairing is
		///   handled by Bluetooth Framework. <c>False</c> if the pairing is handled
		///   by the system. </value>
		/// <remarks> This flag doe snot affect <c>Bled112</c> USB dongle because
		///   it does not have any support from the OS. </remarks>
		__declspec(property(get = GetHandlePairing)) bool HandlePairing;

		/// <summary> Gets message processing method used by the Bluetooth
		///  Framework. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Gets and sets message processing method used by the Bluetooth
		///  Framework. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEBluetoothManager"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets message processing method used by the Bluetooth
		///  Framework. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEBluetoothManager"></exception>
		__declspec(property(get = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/// <summary> Gets the Bluetooth Radio by its index. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object. </returns>
		CwclBluetoothRadio* GetRadios(const size_t Index) const;
		/// <summary> Gets the Bluetooth Radio by its index. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object. </value>
		__declspec(property(get = GetRadios)) CwclBluetoothRadio* Radios[];

		/// <summary> The event fires after the Bluetooth Manager has been
		///   successfully opened. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(AfterOpen);
		/// <summary> The event fires before the Bluetooth Manager will be
		///   closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(BeforeClose);
		/// <summary> The event fires when authentication (pairing) with a remote
		///   Bluetooth device has completed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Error"> An operation result code. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothDeviceResultEvent(OnAuthenticationCompleted);
		/// <summary> The event fires when a remote Bluetooth device requires
		///   a pairing confirmation. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothConfirmEvent(OnConfirm);
		/// <summary> The event fires when the Bluetooth Manager has completely
		///   been closed. </summary>
		wclNotifyEvent(OnClosed);
		/// <summary> The event fires when a new remote Bluetooth device found
		///   during discovering. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothDeviceEvent(OnDeviceFound);
		/// <summary> The event fires when discovering for remote Bluetooth
		///   devices has been completed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Error"> An operation result code. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothResultEvent(OnDiscoveringCompleted);
		/// <summary> The event fires when discovering for remote Bluetooth
		///   devices has been started. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothEvent(OnDiscoveringStarted);
		/// <summary> The event fires when a remote device requests an IO capability
		///   of the local Bluetooth device. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Mitm"> An application sets this parameter to specify the
		///   "Man in the Middle" protection required for authentication. </param>
		/// <param name="IoCapability"> An application sets this parameter to define
		///   the input/output capabilities of a Bluetooth Device. </param>
		/// <param name="OobPresent"> An application sets this parameter to
		///   <c>True</c> to force Out Of Band authentication. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <seealso cref="wclBluetoothMitmProtection" />
		/// <seealso cref="wclBluetoothIoCapability" />
		wclBluetoothIoCapabilityRequestEvent(OnIoCapabilityRequest);
		/// <summary> The event fires when a remote Bluetooth device requires
		///   a numeric comparison pairing. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Number"> A number sent by a remote device to display and
		///   compare. </param>
		/// <param name="Confirm"> An application must set this parameter to
		///   <c>True</c> to confirm pairing. Set it to <c>False</c> to reject
		///   pairing. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothNumericComparisonEvent(OnNumericComparison);
		/// <summary> The event fires when a remote device requests an Out Of Band
		///   pairing data. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="OobData"> An application must set this parameter to
		///   the Out Of Band data received from peer device. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothOobDataRequestEvent(OnOobDataRequest);
		/// <summary> The event fires when a remote Bluetooth device notifies
		///   an application about its passkey. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A Passkey provided by a remote
		///   Bluetooth device. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothPasskeyNotificationEvent(OnPasskeyNotification);
		/// <summary> The event fires when a remote Bluetooth device requires
		///   a passkey for pairing. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Passkey"> A Passkey provided by an application. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothPasskeyRequestEvent(OnPasskeyRequest);
		/// <summary> The event fires when a remote Bluetooth device requires
		///   a legacy PIN pairing. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Pin"> A PIN code provided by an application. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothPinRequestEvent(OnPinRequest);
		/// <summary> The event fires during BLE pairing to request required
		///   pairing protection level. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <param name="Address"> A remote device's MAC address. </param>
		/// <param name="Protection"> Describes the required protection
		///   level provided by an application. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <seealso cref="wclBluetoothLeProtectionLevel" />
		wclBluetoothProtectionLevelRequestEvent(OnProtectionLevelRequest);
		/// <summary> The event fires when a status of a Bluetooth hardware or
		///   driver has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Radio"> A <see cref="CwclBluetoothRadio" /> object
		///   represents a Bluetooth driver that fired the event. </param>
		/// <seealso cref="CwclBluetoothRadio" />
		wclBluetoothEvent(OnStatusChanged);
	};

	/* Connections */

	/// <summary> The base class for all Classic Bluetooth (RFCOMM) client
	///   connections. </summary>
	/// <remarks> An application must never create instances of this class
	///   directly. Instead of that an application must use related methods
	///   from the <see cref="CwclBluetoothRadio" /> object. </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclClientDataConnection" />
	class CwclRfCommClientConnection : public CwclClientDataConnection
	{
		DISABLE_COPY(CwclRfCommClientConnection);

	private:
		friend class CwclBluetoothRadio;

		// The radio that owns the connection.
		CwclBluetoothRadio*	FRadio;

		__int64				FAddress;
		bool				FAuthentication;
		unsigned char		FChannel;
		bool				FEncryption;
		GUID				FService;

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

	public:
		/// <summary> Create new Classic Bluetooth client connection. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclRfCommClientConnection(CwclBluetoothRadio* const Radio);

		/// <summary> Connects to a remote device. </summary>
		/// <param name="Address"> The remote Bluetooth device address. </param>
		/// <param name="Service"> The Bluetooth Service UUID. If the <c>Channel</c>
		///   parameter is zero, the system attempts to use <c>Service</c> to
		///   resolve the remote channel corresponding to the service. The service
		///   class is a normalized 128-bit GUID, defined by the Bluetooth
		///   specification. Common GUIDs are defined by the Bluetooth Assigned
		///   Numbers document. Alternatively, a unique GUID may be used for a
		///   domain-specific application. </param>
		/// <param name="Channel"> The RFCOMM channel number. If zero the
		///   <c>Service</c> UUID will be used. </param>
		/// <param name="Authentication"> Specifies that authentication is required
		///   for a connect operation to complete successfully. Setting this option
		///   actively initiates authentication during connection establishment,
		///   if the two Bluetooth devices were not previously
		///   authenticated. </param>
		/// <param name="Encryption"> The option enforces encryption to establish a
		///   connection. Encryption is only available for authenticated
		///   connections. </param>
		/// <param name="Timeout"> The connect timeout in milliseconds. The
		///   default value is 10000 milliseconds. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts a connection operation to a remote
		///   device. If the method success that does not mean that the connection
		///   was established. That just means that the connection operation was
		///   started. The real connection result will be passed to the
		///   <c>OnConnect</c> event handler. </para>
		///   <para> NOTE: BlueSoleil does not support <c>Authentication</c>
		///   and <c>Encryption</c> parameters per connection. </para> </remarks>
		int Connect(const __int64 Address, const GUID& Service, const unsigned char Channel,
			const bool Authentication, const bool Encryption, const unsigned long Timeout);

		/// <summary> Gets a remote device MAC address. </summary>
		/// <returns> The remote device MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Gets a remote device MAC address. </summary>
		/// <value> The remote device MAC address. </value>
		__declspec(property(get = GetAddress)) __int64 Address;

		/// <summary> Gets the authentication value. </summary>
		/// <returns> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </returns>
		bool GetAuthentication() const;
		/// <summary> Gets the authentication value. </summary>
		/// <value> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </value>
		__declspec(property(get = GetAuthentication)) bool Authentication;

		/// <summary> Gets the target service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <returns> The RFCOMM channel number used for connection. </returns>
		unsigned char GetChannel() const;
		/// <summary> Gets the target service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <value> The RFCOMM channel number used for connection. </value>
		__declspec(property(get = GetChannel)) unsigned char Channel;

		/// <summary> Gets the encryption state of the connection. </summary>
		/// <returns> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </returns>
		bool GetEncryption() const;
		/// <summary> Gets the encryption state of the connection. </summary>
		/// <value> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetEncryption)) bool Encryption;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the target Bluetooth service UUID used for
		///   connection. </summary>
		/// <returns> A Bluetooth service UUID. </returns>
		GUID GetService() const;
		/// <summary> Gets the target Bluetooth service UUID used for
		///   connection. </summary>
		/// <value> A Bluetooth service UUID. </value>
		__declspec(property(get = GetService)) GUID Service;
	};

	/// <summary> The Bluetooth RFCOMM server client connection base class. </summary>
	/// <seealso cref="CwclServerDataConnection" />
	class CwclRfCommServerClientConnection : public CwclServerClientDataConnection
	{
		DISABLE_COPY(CwclRfCommServerClientConnection);

	private:
		__int64	FAddress;

	protected:
		/// <summary> Sets the connected device MAC address. </summary>
		/// <remarks> For internal use only. </remarks>
		void SetAddress(const __int64 Address);

	public:
		/// <summary> Create the new RFCOMM server client connection. </summary>
		CwclRfCommServerClientConnection();

		/// <summary> Gets the connected remote device's address. </summary>
		/// <returns> The remote device's MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Gets the connected remote device's address. </summary>
		/// <value> The remote device's MAC address. </value>
		__declspec(property(get = GetAddress)) __int64 Address;
	};

	/// <summary> The base class for all WCL Bluetooth RFCOMM based
	///   server connections. </summary>
	/// <remarks> An application must never create instances of this class
	///   directly. Instead of that an application must use related methods
	///   from the <see cref="CwclBluetoothRadio" /> object. </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclServerDataConnection" />
	class CwclRfCommServerConnection : public CwclServerDataConnection
	{
		DISABLE_COPY(CwclRfCommServerConnection);

	private:
		friend class CwclBluetoothRadio;

		// The radio that owns the connection.
		CwclBluetoothRadio*	FRadio;

		bool				FAuthentication;
		unsigned char		FAssignedChannel;
		unsigned char		FChannel;
		bool				FEncryption;
		GUID				FService;
		tstring				FServiceName;

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

		/// <summary> Sets the assigned RFCOMM channel number. </summary>
		/// <remarks> For internal use only. </remarks>
		void SetAssignedChannel(const unsigned char Channel);

		/// <summary> Fires the <c>GetSdpAttributes</c> event. </summary>
		/// <param name="Protocols"> The additional protocol descriptors array that
		///   should be added to SDP record. </param>
		/// <param name="Profiles"> The profile list that should be added to SDP
		///   record. </param>
		/// <param name="Formats"> Other attributes that should be added to SDP
		///   record. </param>
		/// <param name="Cod"> <para> Class of device (COD) information. A 32-bit
		///   parameter of COD_SERVICE_* class of device bits associated with this
		///   SDP record. The system combines these bits with COD bits from other
		///   service records and system characteristics. The resulting class of
		///   device for the local radio is advertised when the radio is found during
		///   device inquiry. When the last SDP record associated with a particular
		///   service bit is deleted, that service bit is no longer reported in
		///   responses to future device inquiries. </para>
		///   <para> The format and possible values for the COD field are defined in
		///   the Bluetooth Assigned Numbers 1.1 portion of the Bluetooth
		///   specification, Section 1.2. (This resource may not be available in some
		///   languages and countries.) </para> </param>
		/// <remarks> <para> The HAL Radio implementation calls this method when
		///   needs to add custom attributes into the SDP record. </para>
		///   <para> BlueSoleil driver does not support custom SDP records and this
		///   method does not work with BlueSoleil Bluetooth driver. </para>
		///   <para> A derived class must always call the inherited
		///   method.  </para> </remarks>
		/// <seealso cref="wclBluetoothSdpProtocols" />
		/// <seealso cref="wclBluetoothSdpProfiles" />
		/// <seealso cref="wclBluetoothSdpFormats" />
		virtual void DoGetSdpAttributes(wclBluetoothSdpProtocols& Protocols,
			wclBluetoothSdpProfiles& Profiles, wclBluetoothSdpFormats& Formats,
			unsigned long& Cod);

	public:
		/// <summary> Create new Classic Bluetooth server connection. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclRfCommServerConnection(CwclBluetoothRadio* const Radio);

		/// <summary> The method starts listening for client connections. </summary>
		/// <param name="Service"> The Bluetooth Service UUID. If the <c>Channel</c>
		///   parameter is zero, the system attempts to use <c>Service</c> to
		///   resolve the remote channel corresponding to the service. The service
		///   class is a normalized 128-bit GUID, defined by the Bluetooth
		///   specification. Common GUIDs are defined by the Bluetooth Assigned
		///   Numbers document. Alternatively, a unique GUID may be used for a
		///   domain-specific application. </param>
		/// <param name="ServiceName"> The option service name. </param>
		/// <param name="Channel"> The RFCOMM channel number. If zero the
		///   <c>Service</c> UUID will be used. </param>
		/// <param name="Authentication"> Specifies that authentication is required
		///   for a connect operation to complete successfully. Setting this option
		///   actively initiates authentication during connection establishment,
		///   if the two Bluetooth devices were not previously
		///   authenticated. </param>
		/// <param name="Encryption"> The option enforces encryption to establish a
		///   connection. Encryption is only available for authenticated
		///   connections. </param>
 		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> NOTE: BlueSoleil has limited support for <c>Authentication</c>
		///   and <c>Encryption.</c>. Also it doe snot support user-defined RFCOMM
		///   channel number. </remarks>
		int Listen(const GUID& Service, const tstring& ServiceName,
			const unsigned char Channel, const bool Authentication,
			const bool Encryption);
		
		/// <summary> Gets the authentication value. </summary>
		/// <returns> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </returns>
		bool GetAuthentication() const;
		/// <summary> Gets the authentication value. </summary>
		/// <value> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </value>
		__declspec(property(get = GetAuthentication)) bool Authentication;

		/// <summary> Gets the assigned RFCOMM channel number. </summary>
		/// <returns> The RFCOMM channel number. </returns>
		unsigned char GetAssignedChannel() const;
		/// <summary> Gets the assigned RFCOMM channel number. </summary>
		/// <value> The RFCOMM channel number. </value>
		__declspec(property(get = GetAssignedChannel)) unsigned char AssignedChannel;

		/// <summary> Gets the service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <returns> The RFCOMM channel number used for connection. </returns>
		unsigned char GetChannel() const;
		/// <summary> Gets the service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <value> The RFCOMM channel number used for connection. </value>
		__declspec(property(get = GetChannel)) unsigned char Channel;

		/// <summary> Gets the encryption state of the connection. </summary>
		/// <returns> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </returns>
		bool GetEncryption() const;
		/// <summary> Gets the encryption state of the connection. </summary>
		/// <value> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetEncryption)) bool Encryption;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the Bluetooth service UUID used for
		///   connection. </summary>
		/// <returns> A Bluetooth service UUID. </returns>
		GUID GetService() const;
		/// <summary> Gets the Bluetooth service UUID used for
		///   connection. </summary>
		/// <value> A Bluetooth service UUID. </value>
		__declspec(property(get = GetService)) GUID Service;

		/// <summary> Gets the service name. </summary>
		/// <returns> The service name. </returns>
		tstring GetServiceName() const;
		/// <summary> Gets the service name. </summary>
		/// <value> The service name. </value>
		__declspec(property(get = GetServiceName)) tstring ServiceName;

		/// <summary> The event fires when the server builds SDP record for
		///   the service it runs. If an application needs to provide
		///   additional attributes it should handle the event. By default no
		///   additional attributes is added for the SDP record. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Protocols"> The additional protocol descriptors array that
		///   should be added to SDP record. </param>
		/// <param name="Profiles"> The profile descriptors list that should be added
		///   to SDP record. </param>
		/// <param name="Formats"> Other attributes that should be added to SDP
		///   record. </param>
		/// <param name="Cod"> <para> Class of device (COD) information. A 32-bit
		///   parameter of COD_SERVICE_* class of device bits associated with this
		///   SDP record. The system combines these bits with COD bits from other
		///   service records and system characteristics. The resulting class of
		///   device for the local radio is advertised when the radio is found during
		///   device inquiry. When the last SDP record associated with a particular
		///   service bit is deleted, that service bit is no longer reported in
		///   responses to future device inquiries. </para>
		///   <para> The format and possible values for the COD value are defined in
		///   the Bluetooth Assigned Numbers 1.1 portion of the Bluetooth
		///   specification, Section 1.2. (This resource may not be available in some
		///   languages and countries.) </para> </param>
		/// <seealso cref="wclBluetoothSdpProtocols" />
		/// <seealso cref="wclBluetoothSdpProfiles" />
		/// <seealso cref="wclBluetoothSdpFormats" />
		wclBluetoothGetSdpAttributesEvent(GetSdpAttributes);
	};

	/// <summary> The class represents a Bluetooth LE GATT client
	///   connection. </summary>
	/// <remarks> An application must never create instances of this class
	///   directly. Instead of that an application must use related methods
	///   from the <see cref="CwclBluetoothRadio" /> object. </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclClientConnection" />
	class CwclGattClientConnection : public CwclClientConnection
	{
		DISABLE_COPY(CwclGattClientConnection);

	private:
		friend class CwclBluetoothRadio;

		typedef std::list<void*> VOID_LIST;

		__int64									FAddress; // Remote device address.
		bool									FConnectOnRead; // Connection flag.
		bool									FForceNotifications;
		CwclBluetoothRadio*						FRadio; // The owner.
		bool									FRemoteDisconnected;
		VOID_LIST*								FSubscriptions; // Subscriptions.
		VOID_LIST*								FSubscribedDescriptors;
		
		/* Message processing. */

		void ProcessCharacteristicChangeMessage(const unsigned short Handle,
			void* const Value, const unsigned long Size);

	protected:
		/// <summary> The method called internally before connection. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class may override this method to process some
		///   connection pre-requirements that should be executed in the main
		///   thread UI. Used by BLED112 to be able to get protection
		///   parameters. </remarks>
		virtual int PrepareForConnection();

		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;

		/// <summary> Implements a hardware-dependent code that connects to a
		///   remote device. </summary>
		/// <param name="Event"> The system even object handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Derived classes must override this method to implement
		///   a hardware-dependent code that connects to a remote device. </para>
		///   <para> The method executes in a separate thread. </para>
		///   <para> The method implementation must monitor the <c>Event</c>
		///   parameter. The <c>Event</c> parameter is set if the
		///   <c>Disconnect</c> method was called. If the termination event was set
		///   the method must terminate connection operation. </para>
		///   <para> If connection to a remote device was terminated the method
		///   must release all allocated resources because the <c>HalDisconnect</c>
		///   will not be called. </para>
		///   <para> A derived class must always call inherited
		///   method. </para> </remarks>
		virtual int HalConnect(const HANDLE Event) override;
		/// <summary> Implements a hardware-dependent code that disconnects from the
		///   connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method is called only if a connection to a remote
		///   device was established with success (the <c>Connect</c> method was
		///   success). </para>
		///   <para> The method will not be called if the connection to the  remote
		///   device was terminated in the middle of the <c>HalConnect</c>
		///   method. </para>
		///   <para> A derived class must always call inherited
		///   method. </para> </remarks>
		virtual int HalDisconnect() override;

		/// <summary> Fires the <c>OnCharacteristicChanged</c> event. </summary>
		/// <param name="Handle"> A changed characteristic handle. </param>
		/// <param name="Value"> A pointer to the characteristic value. </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <remarks> The <c>Value</c> parameter is valid only inside the event
		///   handler. If an application needs to use it outside the event handler
		///   it must be copied. </remarks>
		virtual void DoCharacteristicChanged(const unsigned short Handle,
			const unsigned char* const Value, const unsigned long Length);
		/// <summary> Fires the <c>OnConnectionParamsChanged</c> event. </summary>
		virtual void DoConnectionParamsChanged();
		/// <summary> Fires the <c>OnConnectionPhyChanged</c> event. </summary>
		virtual void DoConnectionPhyChanged();
		/// <summary> Fires the <c>OnPduMaxSizeChanged</c> event. </summary>
		virtual void DoMaxPduSizeChanged();

		/* HAL GATT methods. */

		/// <summary> Implements a hardware-dependent code for reading the
		///   characteristics available for the specified service. </summary>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Characteristics"> On output a list of the service's
		///   characteristics. An application is responsible to clean up a memory
		///   allocated for the dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattCharacteristics" />
		virtual int HalReadCharacteristics(const wclGattService& Service, const wclGattOperationFlag Flag,
			wclGattCharacteristics& Characteristics) = 0;
		/// <summary> Implements a hardware-dependent code for reading the value of
		///   the specified characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> On output contains a pointer to the characteristic's value.
		///   An application is responsible to clean up a memory allocated for the value. </param>
		/// <param name="Length"> On output contains a characteristic value length in
		///   bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		virtual int HalReadCharacteristicValue(const wclGattCharacteristic& Characteristic,
			const wclGattOperationFlag Flag, const wclGattProtectionLevel Protection,
			unsigned char*& Value, unsigned long& Length) = 0;
		/// <summary> The method reads all the descriptors available for the
		///   specified characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Descriptors"> On output contains the list of the
		///   characteristic's descriptors. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattDescriptors" />
		virtual int HalReadDescriptors(const wclGattCharacteristic& Characteristic,
			const wclGattOperationFlag Flag, wclGattDescriptors& Descriptors) = 0;
		/// <summary> Implements a hardware-dependent code for reading the value of
		///   the specified descriptor. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattDescriptorValue" />
		virtual int HalReadDescriptorValue(const wclGattDescriptor& Descriptor,
			const wclGattOperationFlag Flag, const wclGattProtectionLevel Protection,
			wclGattDescriptorValue& Value) = 0;
		/// <summary> Implements a hardware-dependent code for reading the included
		///   services available for a given service. </summary>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		virtual int HalReadIncludedServices(const wclGattService& Service,
			const wclGattOperationFlag Flag, wclGattServices& Services) = 0;
		/// <summary> Implements a hardware-dependent code for reading available
		///   services from a remote Bluetooth LE device. </summary>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		virtual int HalReadServices(const wclGattOperationFlag Flag,
			wclGattServices& Services) = 0;

		/// <summary> Implements a hardware-dependent code to write the specified
		///   characteristic value to the Bluetooth device. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A pointer to the characteristic's value data. </param>
		/// <param name="Length"> A characteristic value length in bytes. </value>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattProtectionLevel" />
		virtual int HalWriteCharacteristicValue(const wclGattCharacteristic& Characteristic,
			const wclGattProtectionLevel Protection, const unsigned char* const Value,
			const unsigned long Length) = 0;
		/// <summary> Implements a hardware-dependent code to write the specified
		///   descriptor value to the Bluetooth device. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattDescriptorValue" />
		virtual int HalWriteDescriptorValue(const wclGattDescriptor& Descriptor,
			const wclGattProtectionLevel Protection, const wclGattDescriptorValue& Value) = 0;

		/* HAL characteristics changes notifications. */

		/// <summary> Implements a hardware-dependent code to subscribes for the
		///   characteristic changes notifications. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="Hdl"> On output the subscription handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		virtual int HalSubscribe(const wclGattCharacteristic& Characteristic, HANDLE& Hdl) = 0;
		/// <summary> Implements a hardware-dependent code to unsubscribes from the
		///   characteristic changes notifications. </summary>
		/// <param name="Hdl"> The subscription handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		virtual int HalUnsubscribe(const HANDLE Hdl) = 0;

		/* Connection parameters. */
		
		/// <summary> Implements a hardware-dependent code to get the current
		///   connection parameters. </summary>
		/// <param name="Params"> If the function completed with success on output
		///   contains the current connection parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParameters" />
		virtual int HalGetConnectionParams(wclBluetoothLeConnectionParameters& Params) = 0;
		/// <summary> Implements a hardware-dependent code to request the connection
		///   parameters change to the specified preferred connection
		///   parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersType" />
		virtual int HalSetConnectionParams(
			const wclBluetoothLeConnectionParametersType Params) = 0;
		/// <summary> Implements a hardware-dependent code to request the connection
		///   parameters change to the specified preferred connection
		///   parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersValue" />
		virtual int HalSetConnectionParams(
			const wclBluetoothLeConnectionParametersValue& Params) = 0;

		/// <summary> Implements a hardware-dependent code to reads the maximum PDU
		///   size for the current connection. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum PDU size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalGetMaxPduSize(unsigned short& Size) = 0;

		/// <summary> Implements a hardware-dependent code to reads the Bluetooth LE
		///   physical layer (PHY) information. </summary>
		/// <param name="Info"> If the method completed with success on output
		///   contains the connection PHY information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionPhy" />
		virtual int HalGetConnectionPhyInfo(wclBluetoothLeConnectionPhy& Info) = 0;

	public:
		/// <summary> Creates a new GATT client connection object. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattClientConnection(CwclBluetoothRadio* const Radio);

		/// <summary> The method reads all the characteristics available for the
		///   specified service. </summary>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Characteristics"> On output a list of the service's
		///   characteristics. An application is responsible to clean up a memory
		///   allocated for the dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattCharacteristics" />
		int ReadCharacteristics(const wclGattService& Service, const wclGattOperationFlag Flag,
			wclGattCharacteristics& Characteristics);
		/// <summary> The method reads the value of the specified
		///   characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> On output contains a pointer to the characteristic's value.
		///   An application is responsible to clean up a memory allocated for the value. </param>
		/// <param name="Length"> On output contains a characteristic value length in
		///   bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		int ReadCharacteristicValue(const wclGattCharacteristic& Characteristic, const wclGattOperationFlag Flag,
			const wclGattProtectionLevel Protection, unsigned char*& Value, unsigned long& Length);
		/// <summary> The method reads all the descriptors available for the
		///   specified characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Descriptors"> On output contains the list of the
		///   characteristic's descriptors. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattDescriptors" />
		int ReadDescriptors(const wclGattCharacteristic& Characteristic, const wclGattOperationFlag Flag,
			wclGattDescriptors& Descriptors);
		/// <summary> The method reads the value of the specified
		///   descriptor. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattDescriptorValue" />
		int ReadDescriptorValue(const wclGattDescriptor& Descriptor, const wclGattOperationFlag Flag,
			const wclGattProtectionLevel Protection, wclGattDescriptorValue& Value);
		/// <summary> The method reads all the included services available for a
		///   given service. </summary>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		int ReadIncludedServices(const wclGattService& Service, const wclGattOperationFlag Flag,
			wclGattServices& Services);
		/// <summary> Reads available services from a remote Bluetooth LE
		///   device. </summary>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		int ReadServices(const wclGattOperationFlag Flag, wclGattServices& Services);

		/// <summary> The method writes the specified characteristic value to the
		///   Bluetooth device. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A pointer to the characteristic's value </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <param name="WriteKind"> The write operation mode. </param>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattWriteKind" />
		int WriteCharacteristicValue(wclGattCharacteristic Characteristic,
			const wclGattProtectionLevel Protection, const unsigned char* const Value,
			const unsigned long Length, const wclGattWriteKind WriteKind);
		/// <summary> The method writes the specified descriptor value to the
		///   Bluetooth device. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattDescriptorValue" />
		int WriteDescriptorValue(const wclGattDescriptor& Descriptor, const wclGattProtectionLevel Protection,
			const wclGattDescriptorValue& Value);

		/// <summary> Writes the client configuration descriptor to the
		///   device. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="Subscribe"> The value indicates should we subscribe
		///   or unsubscribe from the characteristic value changes. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> In order to receive notifications about characteristic
		///   value changes the client must set the Client Configuration Descriptor.
		///   An application can use this method to do it in easy way. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		int WriteClientConfiguration(const wclGattCharacteristic& Characteristic,
			const bool Subscribe, const wclGattOperationFlag Flag,
			const wclGattProtectionLevel Protection);

		/// <summary> Subscribes for the characteristic changes
		///   notifications. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method does not change Client Configuration Descriptor
		///   value. Application must do it by itself or by calling
		///   the <c>WriteClientConfiguration</c> method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		int Subscribe(const wclGattCharacteristic& Characteristic);
		/// <summary> Unsubscribes from the characteristic changes
		///   notifications. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is not interested any more. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method does not change Client Configuration Descriptor
		///   value. Application must do it by itself or by calling
		///   the <c>WriteClientConfiguration</c> method. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		int Unsubscribe(const wclGattCharacteristic& Characteristic);

		/// <summary> Connects to a remote device. </summary>
		/// <param name="Address"> A remote device MAC address. </param>
		/// <param name="ConnectOnRead"> A Boolean indicates whether a connection
		///   should made during <c>Connect</c> call or on first services
		///   read. <c>True</c> indicates that the connection should be executed
		///   on first services read on when OS decided to do that. </param>
		/// <param name="ForceNotifications"> A Boolean indicates that the
		///   notifications (and/or indications) should be forced. This should be
		///   set to <c>True</c> for some boards (such as <c>Bluno</c>, <c>Bluno
		///   Mega</c> and some others) that do not have <c>Characteristic
		///   Client Configuration Descriptor</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method starts a connection operation to a remote device.
		///   If the method success that does not mean that the connection was
		///   established. That just means that the connection operation was
		///   started. The real connection result will be passed to the
		///   <c>OnConnect</c> event handler. </remarks>
		int Connect(const __int64 Address, const bool ConnectOnRead,
			const bool ForceNotifications);
		
		/// <summary> Gets the current connection parameters. </summary>
		/// <param name="Params"> If the function completed with success on output
		///   contains the current connection parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParameters" />
		int GetConnectionParams(wclBluetoothLeConnectionParameters& Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> When performing firmware updates, higher throughput is
		///   necessary to complete the operation swiftly for the user. In those
		///   scenarios, you should request <c>ppThroughputOptimized</c> connection
		///   parameters for the duration of the firmware update. That will reduce
		///   the number of concurrent connections to other Bluetooth peripherals,
		///   and should be used sparingly. </para>
		///   <para> Conversely, when connecting to multiple LE devices
		///   concurrently, you should use <c>ppPowerOptimized</c>. That will
		///   increase the acceptable peripheral latency for the connection,
		///   reducing the interval at which the LE device must respond to the
		///   host OS. That allows the local Bluetooth radio to schedule more
		///   connections concurrently, and reduces power usage on both the host OS
		///   and on the peripheral device. </para>
		///   <para> If the connection parameters were changed successfully the
		///   <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersType" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersType Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks><para> If the connection parameters were changed successfully
		///   the <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersValue" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersValue& Params);

		/// <summary> Reads the maximum PDU size for the current connection. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum PDU size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The PDU size includes header and payload. For example if
		///   PDU size is 23 bytes the allowed payload is 20 bytes. </remarks>
		int GetMaxPduSize(unsigned short& Size);
		
		/// <summary> Reads the Bluetooth LE physical layer (PHY)
		///   information. </summary>
		/// <param name="Info"> If the method completed with success on output
		///   contains the connection PHY information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 11 and above. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionPhy" />
		int GetConnectionPhyInfo(wclBluetoothLeConnectionPhy& Info);

		/// <summary> Gets a remote device MAC address. </summary>
		/// <returns> The remote device MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Gets a remote device MAC address. </summary>
		/// <value> The remote device MAC address. </value>
		__declspec(property(get = GetAddress)) __int64 Address;

		/// <summary> Gets connection mode. </summary>
		/// <returns> The Boolean indicates the connection mode. </returns>
		/// <remarks> If this property set to <c>True</c> the connection to a target
		///   device will be executed on first services read or when the OS decided
		///   to do that. If the property is <c>False</c> the connection will be
		///   executed (if possible) on <c>Connect</c> call. </remarks>
		bool GetConnectOnRead() const;
		/// <summary> Gets connection mode. </summary>
		/// <value> The Boolean indicates the connection mode. </value>
		/// <remarks> If this property set to <c>True</c> the connection to a target
		///   device will be executed on first services read or when the OS decided
		///   to do that. If the property is <c>False</c> the connection will be
		///   executed (if possible) on <c>Connect</c> call. </remarks>
		__declspec(property(get = GetConnectOnRead)) bool ConnectOnRead;

		/// <summary> Gets the notifications mode. </summary>
		/// <returns> The Boolean indicates the notifications mode. </returns>
		/// <remarks> If this property set to <c>True</c> the characteristic value
		///   changes notification (and/or indication) will work correctly with
		///   some boards (such as <c>Bluno</c>, <c>Bluno Meag</c> and some others)
		///   that do not have <c>Characteristic Client Configucation
		///   Descriptor</c>. </remarks>
		bool GetForceNotifications() const;
		/// <summary> Gets the notifications mode. </summary>
		/// <value> The Boolean indicates the notifications mode. </value>
		/// <remarks> If this property set to <c>True</c> the characteristic value
		///   changes notification (and/or indication) will work correctly with
		///   some boards (such as <c>Bluno</c>, <c>Bluno Meag</c> and some others)
		///   that do not have <c>Characteristic Client Configucation
		///   Descriptor</c>. </remarks>
		__declspec(property(get = GetForceNotifications)) bool ForceNotifications;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> The event fires when a subscribed characteristic value has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Handle"> A changed characteristic handle. </param>
		/// <param name="Value"> A pointer to the characteristic value. </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <remarks> <para> The <c>Value</c> parameter is valid only inside the event
		///   handler. If an application needs to use it outside the event handler
		///   it must be copied. </para>
		///   <para> To receive characteristic value change events an application
		///   must first subscribe for characteristic changes notification
		///   by calling <c>Subscribe</c> method. </para> </remarks>
		wclGattCharacteristicChangedEvent(OnCharacteristicChanged);
		/// <summary> The event fires when the connection parameters
		///   changed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		wclNotifyEvent(OnConnectionParamsChanged);
		/// <summary> The event fires when the connection PHY changed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		wclNotifyEvent(OnConnectionPhyChanged);
		/// <summary> The event fires when the maximum PDU size changed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <remarks> Once the event fires an application can use the
		///   <c>GetMaxPduSize</c> method to read the current maximum PDU
		///   size. </remarks>
		wclNotifyEvent(OnMaxPduSizeChanged);
	};

	/// <summary> The base class for local GATT attributes (characteristics,
	///   services). </summary>
	class CwclGattLocalAttribute
	{
		DISABLE_COPY(CwclGattLocalAttribute);
		
	private:
		RTL_CRITICAL_SECTION	FCS;
		wclGattUuid				FUuid;

	protected:
		/// <summary> Enters the GATT local attribute protection critical
		///   section. </summary>
		void Enter() const;
		/// <summary> Leaves the GATT local attribute protection critical
		///   section. </summary>
		void Leave() const;

	public:
		/// <summary> Creates new local GATT attribute. </summary>
		/// <param name="Uuid"> The attribute's UUID. </param>
		/// <seealso cref="wclGattUuid" />
		CwclGattLocalAttribute(const wclGattUuid& Uuid);
		/// <summary> Frees the object. </summary>
		virtual ~CwclGattLocalAttribute();
		
		/// <summary> Gets the attribute's UUID. </summary>
		/// <returns> The attribute's UUID. </returns>
		/// <seealso cref="wclGattUuid" />
		wclGattUuid GetUuid() const;
		/// <summary> Gets the attribute's UUID. </summary>
		/// <value> The attribute's UUID. </value>
		/// <seealso cref="wclGattUuid" />
		__declspec(property(get = GetUuid)) wclGattUuid Uuid;
	};

	/// <summary> This class represents a local GATT characteristic. </summary>
	/// <remarks> An application must not create or destroy this class directly.
	///   Instead of that an application must use methods of the
	///   <seealso cref="CwclGattLocalService" /> class. </remarks>
	/// <seealso cref="CwclGattLocalAttribute" />
	class CwclGattLocalCharacteristic : public CwclGattLocalAttribute
	{
		DISABLE_COPY(CwclGattLocalCharacteristic);
		
	private:
		friend class CwclGattLocalService;
		friend class CwclGattServerClient;

		typedef std::list<CwclGattServerClient*> CLIENTS;
		
		bool									FAdded;
		CLIENTS*								FClients;
		int										FError;
		wclGattLocalCharacteristicParameters	FParams;
		CwclGattLocalService*					FService;

		bool IsNotifiable() const;

		void AddClient(CwclGattServerClient* const Client);
		void RemoveClient(CwclGattServerClient* const Client);
		
		// This method called by the local GATT service object to add the
		// characteristic. This method is called in separate thread.
		int Add();
		// This method called by the local GATT service object to remove the
		// characteristic. It is guaranteed that this method will be called only
		// if characteristic has been added (cal; to the Add method was success).
		// This method is called in separate thread.
		int Remove();
		
	protected:
		/* HAL methods. */

		/// <summary> The method implements a driver specific code to add
		///   characteristic to the local GATT service. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that adds the GATT characteristic. </remarks>
		virtual int HalAdd() = 0;
		/// <summary> The method implements a driver specific code to remove
		///   characteristic from the local GATT service. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that removes the GATT characteristic. </remarks>
		virtual int HalRemove() = 0;
		/// <summary> The function implements a driver specific code to send
		///   notification to the given subscribed client. </summary>
		/// <param name="Address"> The client's MAC address. If the address
		///   parameter is <c>0</c> the notification must be sent to all
		///   subscribed clients. </param>
		/// <param name="Data"> The pointer to the notification data. </param>
		/// <param name="Size"> The notification data size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that sends notification to the given subscribed
		///   client. </remarks>
		virtual int HalNotify(const __int64 Address, const unsigned char* const Data,
			const unsigned long Size) const = 0;

	public:
		/// <summary> Creates new local GATT characteristic. </summary>
		/// <param name="Service"> The local GATT service object that owns the
		///   characteristic. </param>
		/// <param name="Uuid"> The characteristic's UUID. </param>
		/// <param name="Params"> The characteristic's parameters. </param>
		/// <remarks> An application must not create this class directly.
		///   Instead of that an application must use methods of the
		///   <see cref="CwclGattLocalService" /> class. </remarks>
		/// <seealso cref="CwclGattLocalService" />
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="wclGattLocalCharacteristicParameters" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattLocalCharacteristic(CwclGattLocalService* const Service,
			const wclGattUuid& Uuid, const wclGattLocalCharacteristicParameters& Params);
		/// <summary> Frees the object. </summary>
		virtual ~CwclGattLocalCharacteristic();
		
		/// <summary> Sends notification to all subscribed clients. </summary>
		/// <param name="Data"> The pointer to the notification data. </param>
		/// <param name="Size"> The notification data size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Notify(const unsigned char* const Data, const unsigned long Size) const;
		/// <summary> Sends notification to the given subscribed client. </summary>
		/// <param name="Address"> The client's MAC address. </param>
		/// <param name="Data"> The pointer to the notification data. </param>
		/// <param name="Size"> The notification data size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Notify(const __int64 Address, const unsigned char* const Data,
			const unsigned long Size) const;
		
		/// <summary> Gets the characteristic's status. </summary>
		/// <returns> <c>True</c> if the characteristic has been successfully added to
		///   the local GATT service, <c>False</c> otherwise. </returns>
		bool GetAdded() const;
		/// <summary> Gets the characteristic's status. </summary>
		/// <value> <c>True</c> if the characteristic has been successfully added to
		///   the local GATT service, <c>False</c> otherwise. </value>
		__declspec(property(get = GetAdded)) bool Added;

		/// <summary> Gets the subscribed client by its index. </summary>
		/// <param name="Index"> The client's index. The <c>Index</c> parameter
		///   must be in range between <c>0</c> and <c>Count - 1</c>. If the
		///   <c>Index</c> is out of range the <see cref="wclEInvalidArgument" />
		///   exception raises. </param>
		/// <returns> The <see cref="CwclGattServerClient" /> object. </returns>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattServerClient* GetClients(const size_t Index) const;
		/// <summary> Gets the subscribed client by its index. </summary>
		/// <value> The <see cref="CwclGattServerClient" /> object. </value>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetClients)) CwclGattServerClient* Clients[];

		/// <summary> Gets the subscribed clients count. </summary>
		/// <returns> The subscribed clients count. </returns>
		size_t GetCount() const;
		/// <summary> Gets the subscribed clients count. </summary>
		/// <value> The subscribed clients count. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets the characteristic's publishing error. </summary>
		/// <returns> One of the WCL error code that indicates why characteristic
		///   has not been added. </returns>
		/// <remarks> If adding characteristic to the service was failed this
		///   property contains the failure reason code. </remarks>
		int GetError() const;
		/// <summary> Gets the characteristic's publishing error. </summary>
		/// <value> One of the WCL error code that indicates why characteristic
		///   has not been added. </value>
		/// <remarks> If adding characteristic to the service was failed this
		///   property contains the failure reason code. </remarks>
		__declspec(property(get = GetError)) int Error;

		/// <summary> Gets the characteristic's parameters. </summary>
		/// <returns> The characteristic's parameters. </returns>
		/// <seealso cref="wclGattLocalCharacteristicParameters" />
		wclGattLocalCharacteristicParameters GetParams() const;
		/// <summary> Gets the characteristic's parameters. </summary>
		/// <value> The characteristic's parameters. </value>
		/// <seealso cref="wclGattLocalCharacteristicParameters" />
		__declspec(property(get = GetParams)) wclGattLocalCharacteristicParameters Params;

		/// <summary> Gets the GATT service object that owns the
		///   characteristic. </summary>
		/// <returns> The local GATT service object. </returns>
		/// <seealso cref="CwclGattLocalService" />
		CwclGattLocalService* GetService() const;
		/// <summary> Gets the GATT service object that owns the
		///   characteristic. </summary>
		/// <value> The local GATT service object. </value>
		/// <seealso cref="CwclGattLocalService" />
		__declspec(property(get = GetService)) CwclGattLocalService* Service;
	};

	/// <summary> This class represents a local GATT service. </summary>
	/// <remarks> An application must not create or destroy this class directly.
	///   Instead of that an application must use methods of the
	///   <see cref="CwclGattServerConnection" /> classes. </remarks>
	/// <seealso cref="CwclGattLocalAttribute" />
	class CwclGattLocalService : public CwclGattLocalAttribute
	{
		DISABLE_COPY(CwclGattLocalService);

	private:
		friend class CwclGattServerConnection;

		typedef std::list<CwclGattLocalCharacteristic*> CHARS;

		bool						FAdded;
		int							FError;
		CHARS*						FCharacteristics;
		CwclGattServerConnection*	FServer;

		bool					FConnectable;
		bool					FDiscoverable;

		// Internal helper methods.
		int AddAllCharacteristics();
		void ClearAllCharacteristics();
		void DeleteSelectedCharacteristic(const size_t Index);
		void RemoveAddedCharacteristics();
		void RemoveAllCharacteristics();

		// This method called by the GATT server connection object to create and add
		// the service. This method is called in separate thread.
		int Add();
		// This method called by the GATT server connection to remove and destroy
		// the service. It is guaranteed that this method will be called only
		// if characteristic has been added (cal; to the Add method was success).
		// This method is called in separate thread.
		int Remove();
		
	protected:
		/* HAL methods. */

		/// <summary> The method implements a driver specific code to add
		///   local GATT service to the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that adds the GATT service. </remarks>
		virtual int HalAdd() = 0;
		/// <summary> The method implements a driver specific code to create
		///   local GATT service to the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that creates the GATT service. </remarks>
		virtual int HalCreate() = 0;
		/// <summary> The method implements a driver specific code to destroy
		///   local GATT service from the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that destroys the GATT service. </remarks>
		virtual int HalDestroy() = 0;
		/// <summary> The method implements a driver specific code to remove
		///   local GATT service from the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to implement a
		///   driver specified code that removes the GATT service. </remarks>
		virtual int HalRemove() = 0;
		
		/// <summary> The function creates a driver specific GATT characteristic
		///   object. </summary>
		/// <param name="Uuid"> The characteristic UUID. </param>
		/// <param name="Params"> The characteristic parameters. </param>
		/// <param name="Characteristic"> If the function completed with success
		///   the parameter contains just created characteristic object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to create a
		///   GATT characteristic. </remarks>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="wclGattLocalCharacteristicParameters" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual int HalCreateCharacteristic(const wclGattUuid& Uuid,
			const wclGattLocalCharacteristicParameters& Params,
			CwclGattLocalCharacteristic*& Characteristic) = 0;
		
	public:
		/// <summary> Creates new Local GATT service. </summary>
		/// <param name="Server"> The GATT server connection object that owns
		///   the service. </param>
		/// <param name="Uuid"> The service's UUID. </param>
		/// <remarks> An application must not create this class directly.
		///   Instead of that an application must use methods of high-level
		///   classes. </remarks>
		/// <seealso cref="CwclGattServerConnection" />
		/// <seealso cref="wclGattUuid" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattLocalService(CwclGattServerConnection* const Server, const wclGattUuid& Uuid);
		/// <summary> Frees the object. </summary>
		/// <remarks> An application must not destroy this class directly.
		///   Instead of that an application must use methods of high-level
		///   classes. </remarks>
		virtual ~CwclGattLocalService();
		
		/// <summary> Creates new characteristic and adds it to the service
		///   characteristics list. </summary>
		/// <param name="Uuid"> The characteristic UUID. </param>
		/// <param name="Params"> The characteristic parameters. </param>
		/// <param name="Characteristic"> If the method completed with success the
		///   parameters contains a just created GATT characteristic
		///   object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="wclGattLocalCharacteristicParameters" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		int AddCharacteristic(const wclGattUuid& Uuid, const wclGattLocalCharacteristicParameters& Params,
			CwclGattLocalCharacteristic*& Characteristic);
		/// <summary> Clears the characteristics list. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int ClearCharacteristics();
		/// <summary> Deletes the characteristic with given index. </summary>
		/// <param name="Index"> The service's index. The parameter must be in range
		///   between 0 and ServicesCount - 1. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DeleteCharacteristic(const size_t Index);

		/// <summary> Gets a boolean that indicates if the GATT service is
		///   connectable. </summary>
		/// <returns> A boolean that indicates if the GATT service is
		///   connectable. </returns>
		bool GetConnectable() const;
		/// <summary> Sets a boolean that indicates if the GATT service is
		///   connectable. </summary>
		/// <param name="Value"> A boolean that indicates if the GATT service is
		///   connectable. </param>
		/// <remarks> If the service has been published and an application
		///   changes the property the <see cref="wclEGattServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattServer"></exception>
		void SetConnectable(const bool Value);
		/// <summary> Gets or sets a boolean that indicates if the GATT service is
		///   connectable. </summary>
		/// <value> A boolean that indicates if the GATT service is
		///   connectable. </value>
		/// <remarks> If the service has been published and an application
		///   changes the property the <see cref="wclEGattServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattServer"></exception>
		__declspec(property(get = GetConnectable, put = SetConnectable)) bool Connectable;

		/// <summary> Gets a boolean indicating that the GATT service is
		///   discoverable. </summary>
		/// <returns> A boolean indicating that the GATT service is
		///   discoverable. </returns>
		bool GetDiscoverable() const;
		/// <summary> Sets a boolean indicating that the GATT service is
		///   discoverable. </summary>
		/// <param name="Value"> A boolean indicating that the GATT service is
		///   discoverable. </param>
		/// <remarks> If the service has been published and an application
		///   changes the property the <see cref="wclEGattServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattServer"></exception>
		void SetDiscoverable(const bool Value);
		/// <summary> Gets or sets a boolean indicating that the GATT service is
		///   discoverable. </summary>
		/// <value> A boolean indicating that the GATT service is
		///   discoverable. </value>
		/// <remarks> If the service has been published and an application
		///   changes the property the <see cref="wclEGattServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattServer"></exception>
		__declspec(property(get = GetDiscoverable, put = SetDiscoverable)) bool Discoverable;
		
		/// <summary> Gets the service state. </summary>
		/// <returns> <c>True</c> if the service is added and published. <c>False</c>
		///   otherwise. </returns>
		bool GetAdded() const;
		/// <summary> Gets the service state. </summary>
		/// <value> <c>True</c> if the service is added and published. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetAdded)) bool Added;

		/// <summary> Gets the GATT characteristic by its index. </summary>
		/// <param name="Index"> The characteristic's index. The parameter must be
		///   in range between 0 and CharacteristicsCount - 1. If the parameter is
		///   out of range the <see cref="wclEInvalidArgument" /> exception
		///   raises. </param>
		/// <returns> The local GATT characteristic. </returns>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattLocalCharacteristic* GetCharacteristics(const size_t Index) const;
		/// <summary> Gets the GATT characteristic by its index. </summary>
		/// <value> The local GATT characteristic. </value>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetCharacteristics)) CwclGattLocalCharacteristic* Characteristics[];

		/// <summary> Gets the characteristics count. </summary>
		/// <returns> The characteristics count. </returns>
		size_t GetCharacteristicsCount() const;
		/// <summary> Gets the characteristics count. </summary>
		/// <value> The characteristics count. </value>
		__declspec(property(get = GetCharacteristicsCount)) size_t CharacteristicsCount;

		/// <summary> Gets the service's publishing result code. </summary>
		/// <returns> One of WCL errors code indicates the publishing result. </returns>
		/// <remarks> If publishing the service was failed this property contains the
		///   failure reason code. </remarks>
		int GetError() const;
		/// <summary> Gets the service's publishing result code. </summary>
		/// <value> One of WCL errors code indicates the publishing result. </value>
		/// <remarks> If publishing the service was failed this property contains the
		///   failure reason code. </remarks>
		__declspec(property(get = GetError)) int Error;

		/// <summary> Gets the GATT server object that owns the service. </summary>
		/// <returns> The GATT server object. </returns>
		/// <seealso cref="CwclGattServerConnection" />
		CwclGattServerConnection* GetServer() const;
		/// <summary> Gets the GATT server object that owns the service. </summary>
		/// <value> The GATT server object. </value>
		/// <seealso cref="CwclGattServerConnection" />
		__declspec(property(get = GetServer)) CwclGattServerConnection* Server;
	};

	/// <summary> The base class for local GATT characteristic operation
	///   requests. </summary>
	/// <remarks> An application must never create or destroy this class.
	///   The class is created and released internally when needed. </remarks>
	class CwclGattLocalCharacteristicRequest
	{
		DISABLE_COPY(CwclGattLocalCharacteristicRequest);

	private:
		unsigned long	FOffset;
		bool			FProcessed;
		__int64			FTimestamp;
		
	protected:
		/// <summary> Sets the processed flag. </summary>
		/// <param name="Error"> The operation result code. </param>
		void SetProcessed(const int Error);
		/// <summary> Checks if the request has already been processed. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int CheckProcessed();
		
		/// <summary> Responds to the request with an error. </summary>
		/// <param name="Error"> The GATT operation error code. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> A derived class must override this method to provide
		///   hardware dependent code that sends a error respond. </para>
		///   <para> An application must call this method in case if there
		///   is an error appeared during request processing. The <c>Error</c> is
		///   one of the Wireless Communication Library GATT error. </para>
		///   <para> The <see cref="WCL_E_INVALID_ARGUMENT" /> result indicates that
		///   the error code passed to the method is not one from the GATT errors
		///   list. </para>
		///   <para> Valid error codes are: </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_HANDLE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_READ_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_WRITE_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_PDU" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHENTICATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_REQUEST_NOT_SUPPORTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_OFFSET" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHORIZATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_PREPARE_QUEUE_FULL" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_FOUND" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_LONG" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION_KEYSIZE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_ATTRIBUTE_VALUE_LENGTH" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNLIKELY" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNSUPPORTED_GROUP_TYPE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_RESOURCES" /> </para>
		/// </remarks>
		virtual int HalRespondWithError(const int Error) = 0;
		
	public:
		/// <summary> Creates new object. </summary>
		/// <param name="Timestamp"> A high resolution (less than 1us) time stamp
		///   when the request was received. </param>
		/// <param name="Offset"> A data offset. </param>
		/// <remarks> An application must not create this class. It is created
		///   internally when needed. </remarks>
		CwclGattLocalCharacteristicRequest(const __int64 Timestamp,
			const unsigned long Offset);
		/// <summary> Frees the object. </summary>
		/// <remarks> An application must not destroy this class. Instead of
		///   calling destructor an application must call the <c>Release</c>
		///   method. </remarks>
		virtual ~CwclGattLocalCharacteristicRequest();

		/// <summary> Responds to the request with an error. </summary>
		/// <param name="Error"> The GATT operation error code. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application must call this method in case if there
		///   is an error appeared during request processing. The <c>Error</c> is
		///   one of the Wireless Communication Library GATT error. </para>
		///   <para> The <see cref="WCL_E_INVALID_ARGUMENT" /> result indicates that
		///   the error code passed to the method is not one from the GATT errors
		///   list. </para>
		///   <para> Valid error codes are: </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_HANDLE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_READ_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_WRITE_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_PDU" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHENTICATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_REQUEST_NOT_SUPPORTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_OFFSET" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHORIZATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_PREPARE_QUEUE_FULL" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_FOUND" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_LONG" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION_KEYSIZE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_ATTRIBUTE_VALUE_LENGTH" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNLIKELY" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNSUPPORTED_GROUP_TYPE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_RESOURCES" /> </para>
		/// </remarks>
		virtual int RespondWithError(const int Error);
		
		/// <summary> Gets the data offset. </summary>
		/// <returns> The data offset. </returns>
		unsigned long GetOffset() const;
		/// <summary> Gets the data offset. </summary>
		/// <value> The data offset. </value>
		__declspec(property(get = GetOffset)) unsigned long Offset;

		/// <summary> Gets the request time stamp. </summary>
		/// <returns> A high resolution (<1us) time stamp when the request was
		///   received. </returns>
		__int64 GetTimestamp() const;
		/// <summary> Gets the request time stamp. </summary>
		/// <value> A high resolution (less than 1us) time stamp when the request was
		///   received. </value>
		__declspec(property(get = GetTimestamp)) __int64 Timestamp;
	};

	/// <summary> The class represents a GATT characteristic read
	///   requests. </summary>
	/// <remarks> An application must never create or destroy this class.
	///   The class is created and released internally when needed. </remarks>
	/// <seealso cref="CwclGattLocalCharacteristicRequest" />
	class CwclGattLocalCharacteristicReadRequest : public CwclGattLocalCharacteristicRequest
	{
		DISABLE_COPY(CwclGattLocalCharacteristicReadRequest);

	private:
		unsigned long	FSize;
		
	protected:
		/// <summary> Sends the specified data to the connected client in respond to
		///   a read request. </summary>
		/// <param name="Data"> The pointer to the data. </param>
		/// <param name="Size"> The data length. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide hardware
		///   dependent code that sends a data to a remote connected GATT
		///   client. </remarks>
		virtual int HalRespond(void* const Data, const unsigned long Size) = 0;
		
	public:
		/// <summary> Creates new object. </summary>
		/// <param name="Timestamp"> A high resolution (less than 1us) time stamp when the
		///   request was received. </param>
		/// <param name="Offset"> A data offset. </param>
		/// <param name="Size"> A read buffer size. </param>
		/// <remarks> An application must not create this class. It is created
		///   internally when needed. </remarks>
		CwclGattLocalCharacteristicReadRequest(const __int64 Timestamp,
			const unsigned long Offset, const unsigned long Size);
		
		/// <summary> Sends the specified data to the connected client in respond to
		///   a read request. </summary>
		/// <param name="Data"> The pointer to the data. </param>
		/// <param name="Size"> The data length. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Respond(void* const Data, const unsigned long Size);

		/// <summary> Gets the read buffer size. </summary>
		/// <returns> The read buffer size. </returns>
		unsigned long GetSize() const;
		/// <summary> Gets the read buffer size. </summary>
		/// <value> The read buffer size. </value>
		__declspec(property(get = GetSize)) unsigned long Size;
	};

	/// <summary> The class represents a GATT characteristic write
	///   requests. </summary>
	/// <remarks> An application must never create or destroy this class.
	///   The class is created and released internally when needed. </remarks>
	/// <seealso cref="CwclGattLocalCharacteristicRequest" />
	class CwclGattLocalCharacteristicWriteRequest : public CwclGattLocalCharacteristicRequest
	{
		DISABLE_COPY(CwclGattLocalCharacteristicWriteRequest);
		
	private:
		void*			FData;
		unsigned long	FSize;
		bool			FWithResponse;
		
	protected:
		/// <summary> Sends a response to the connected client in respond to a write
		///   request. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide hardware
		///   dependent code that sends a data to a remote connected GATT
		///   client. </remarks>
		virtual int HalRespond() = 0;
		
	public:
		/// <summary> Creates new object. </summary>
		/// <param name="Timestamp"> A high resolution (less than 1us) time stamp when the
		///   request was received. </param>
		/// <param name="Offset"> A data offset. </param>
		/// <param name="Data"> The pointer to the data. </param>
		/// <param name="Size"> The data length. </param>
		/// <param name="WithResponse"> The GATT write operation flag. </param>
		/// <remarks> An application must not create this class. It is created
		///   internally when needed. </remarks>
		CwclGattLocalCharacteristicWriteRequest(const __int64 Timestamp,
			const unsigned long Offset, void* const Data, const unsigned long Size,
			const bool WithResponse);
		
		/// <summary> Sends a response to the connected client in respond to a write
		///   request. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This method must be called only in case the write operation
		///   was made with required response (the <c>WithResponse</c> property is
		///   <c>True</c>. </remarks>
		int Respond();
		/// <summary> Responds to the request with an error. </summary>
		/// <param name="Error"> The GATT operation error code. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application must call this method in case if there
		///   is an error appeared during request processing. The <c>Error</c> is
		///   one of the Wireless Communication Library GATT error. </para>
		///   <para> The <see cref="WCL_E_INVALID_ARGUMENT" /> result indicates that
		///   the error code passed to the method is not one from the GATT errors
		///   list. </para>
		///   <para> Valid error codes are: </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_HANDLE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_READ_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_WRITE_NOT_PERMITTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_PDU" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHENTICATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_REQUEST_NOT_SUPPORTED" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_OFFSET" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_AUTHORIZATION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_PREPARE_QUEUE_FULL" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_FOUND" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_ATTRIBUTE_NOT_LONG" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION_KEYSIZE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INVALID_ATTRIBUTE_VALUE_LENGTH" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNLIKELY" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_ENCRYPTION" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_UNSUPPORTED_GROUP_TYPE" /> </para>
		///   <para> <see cref="WCL_E_BLUETOOTH_LE_INSUFFICIENT_RESOURCES" /> </para>
		/// </remarks>
		virtual int RespondWithError(const int Error) override;
		
		/// <summary> Gets the pointer to the data. </summary>
		/// <returns> The pointer to the data bytes. </returns>
		/// <remarks> This pointer is valid only inside an event handler. If an
		///   application needs to process the data outside the event handler it must
		///   copy the data. </remarks>
		void* GetData() const;
		/// <summary> Gets the pointer to the data. </summary>
		/// <value> The pointer to the data bytes. </value>
		/// <remarks> This pointer is valid only inside an event handler. If an
		///   application needs to process the data outside the event handler it must
		///   copy the data. </remarks>
		__declspec(property(get = GetData)) void* Data;

		/// <summary> Gets the data size. </summary>
		/// <returns> The data size in bytes. </returns>
		unsigned long GetSize() const;
		/// <summary> Gets the data size. </summary>
		/// <value> The data size in bytes. </value>
		__declspec(property(get = GetSize)) unsigned long Size;
		
		/// <summary> Gets the write operation flag. </summary>
		/// <returns> The GATT write operation flag. </returns>
		/// <remarks> If this property is <c>True</c> an application must response
		///   to the write request with <c>Respond</c> or <c>RespondWithError</c>
		///   method. </remarks>
		bool GetWithResponse() const;
		/// <summary> Gets the write operation flag. </summary>
		/// <value> The GATT write operation flag. </value>
		/// <remarks> If this property is <c>True</c> an application must response
		///   to the write request with <c>Respond</c> or <c>RespondWithError</c>
		///   method. </remarks>
		__declspec(property(get = GetWithResponse)) bool WithResponse;
	};

	/// <summary> The base class for a driver specific GATT server client
	///   implementation parameters. </summary>
	class CwclBluetoothGattServerClientParams
	{
		DISABLE_COPY(CwclBluetoothGattServerClientParams);
		
	public:
		/// <summary> Creates new parameters object. </summary>
		CwclBluetoothGattServerClientParams();
		/// <summary> Frees the object. </summary>
		virtual ~CwclBluetoothGattServerClientParams();
	};

	/// <summary> The class represents a GATT client connected to the GATT
	///   server. </summary>
	/// <remarks> An application must not create and destroy objects of this
	///   class directly. The objects of this class managed by the
	///   <see cref="CwclGattServerConnection" />. </remarks>
	/// <seealso cref="CwclGattServerConnection" />
	class CwclGattServerClient
	{
		DISABLE_COPY(CwclGattServerClient);
		
	private:
		typedef std::list<CwclGattLocalCharacteristic*> CHARACTERISTICS;

		friend class CwclGattServerConnection;

		__int64						FAddress;
		CHARACTERISTICS*			FCharacteristics;
		CwclGattServerConnection*	FConnection;

		/* Characteristics management. */
		
		void AddCharacteristic(CwclGattLocalCharacteristic* const Characteristic);
		void RemoveCharacteristic(CwclGattLocalCharacteristic* const Characteristic);

	protected:
		/// <summary> The method called right after client connected. </summary>
		/// <param name="Params"> The additional driver-specific parameters that
		///   can be used during client initialization. Can be <c>nil</c> if
		///   the driver specific implementation does not need this. </param>
		/// <remarks> A derived class may override this method to provide additional
		///   initialization after the client connected to a GATT server. </remarks>
		/// <seealso cref="CwclBluetoothGattServerClientParams" />
		virtual void AfterConnect(
			CwclBluetoothGattServerClientParams* const Params);
		/// <summary> The method right after a client disconnected from the server
		///   and before the client will be destroyed. </summary>
		/// <remarks> A derived class may override this method to provide additional
		///   finalization after client disconnected from a GATT server. </remarks>
		virtual void AfterDisconnect();
		
		/// <summary> The method called right after the client subscribed to a
		///   characteristic. </summary>
		/// <param name="Characteristic"> A
		///   <see cref="CwclGattLocalCharacteristic" /> object represents the
		///   subscribed characteristic. </param>
		/// <remarks> A derived class may override this method to provide additional
		///   initialization after client subscribed to the
		///   characteristic. </remarks>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void AfterSubscribed(CwclGattLocalCharacteristic* const Characteristic);
		/// <summary> The method called right after the client unsubscribed from a
		///   characteristic. </summary>
		/// <param name="Characteristic"> A
		///   <see cref="CwclGattLocalCharacteristic" /> object represents the
		///   unsubscribed characteristic. </param>
		/// <remarks> A derived class may override this method to provide additional
		///   finalization after client unsubscribed from the
		///   characteristic. </remarks>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void AfterUnsubscribed(CwclGattLocalCharacteristic* const Characteristic);
		
		/// <summary> Provide a driver specific code to disconnect the client from a
		///   server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide a driver
		///   specific code. </remarks>
		virtual int HalDisconnect() = 0;

		/* Connection parameters. */
		
		/// <summary> Implements a hardware-dependent code to get the current
		///   connection parameters. </summary>
		/// <param name="Params"> If the function completed with success on output
		///   contains the current connection parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParameters" />
		virtual int HalGetConnectionParams(wclBluetoothLeConnectionParameters& Params) = 0;
		/// <summary> Implements a hardware-dependent code to request the connection
		///   parameters change to the specified preferred connection
		///   parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersType" />
		virtual int HalSetConnectionParams(const wclBluetoothLeConnectionParametersType Params) = 0;
		/// <summary> Implements a hardware-dependent code to request the connection
		///   parameters change to the specified preferred connection
		///   parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersValue" />
		virtual int HalSetConnectionParams(const wclBluetoothLeConnectionParametersValue& Params) = 0;

		/// <summary> Provides a driver specific code to read the maximum
		///   notification size. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum notification size. If the method failed the
		///   value is undefined. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide a driver
		///   specific code. </remarks>
		virtual int HalGetMaxNotificationSize(unsigned short& Size) = 0;
		/// <summary> Implements a hardware-dependent code to read the maximum PDU
		///   size for the current connection. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum PDU size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		virtual int HalGetMaxPduSize(unsigned short& Size) = 0;
		
		/// <summary> Implements a hardware-dependent code to reads the Bluetooth LE
		///   physical layer (PHY) information. </summary>
		/// <param name="Info"> If the method completed with success on output
		///   contains the connection PHY information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionPhy" />
		virtual int HalGetConnectionPhyInfo(wclBluetoothLeConnectionPhy& Info) = 0;
		
	public:
		/// <summary> Creates new client object. </summary>
		/// <param name="Address"> The client's address. If the <c>Address</c> is
		///   <c>0</c> the <see cref="wclEInvalidArgument" /> raises. </param>
		/// <param name="Connection"> The <see cref="CwclGattServerConnection" />
		///   object that owns the client. If the <c>Connection</c> is <c>nil</c>
		///   the <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <remarks> An application must not create the objects of this class
		///   directly. </remarks>
		/// <seealso cref="CwclGattServerConnection" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattServerClient(const __int64 Address,
			CwclGattServerConnection* const Connection);
		/// <summary> Frees the object. </summary>
		/// <remarks> An application must not destroy objects of this class
		///   directly. </remarks>
		virtual ~CwclGattServerClient();

		/// <summary> Disconnects the client from a server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();

		/// <summary> Gets the current connection parameters. </summary>
		/// <param name="Params"> If the function completed with success on output
		///   contains the current connection parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParameters" />
		int GetConnectionParams(wclBluetoothLeConnectionParameters& Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> When performing firmware updates, higher throughput is
		///   necessary to complete the operation swiftly for the user. In those
		///   scenarios, you should request <c>ppThroughputOptimized</c> connection
		///   parameters for the duration of the firmware update. That will reduce
		///   the number of concurrent connections to other Bluetooth peripherals,
		///   and should be used sparingly. </para>
		///   <para> Conversely, when connecting to multiple LE devices
		///   concurrently, you should use <c>ppPowerOptimized</c>. That will
		///   increase the acceptable peripheral latency for the connection,
		///   reducing the interval at which the LE device must respond to the
		///   host OS. That allows the local Bluetooth radio to schedule more
		///   connections concurrently, and reduces power usage on both the host OS
		///   and on the peripheral device. </para>
		///   <para> If the connection parameters were changed successfully the
		///   <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersType" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersType Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks><para> If the connection parameters were changed successfully
		///   the <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersValue" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersValue& Params);
		
		/// <summary> Reads the maximum notification size. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum notification size. If the method failed the
		///   value is undefined. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetMaxNotificationSize(unsigned short& Size);
		/// <summary> Reads the maximum PDU size for the current
		///   connection. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum PDU size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The PDU size includes header and payload. For example if
		///   PDU size is 23 bytes the allowed payload is 20 bytes. </remarks>
		int GetMaxPduSize(unsigned short& Size);

		/// <summary> Reads the Bluetooth LE physical layer (PHY)
		///   information. </summary>
		/// <param name="Info"> If the method completed with success on output
		///   contains the connection PHY information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 11 and above. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionPhy" />
		int GetConnectionPhyInfo(wclBluetoothLeConnectionPhy& Info);
		
		/// <summary> Gets the client's address. </summary>
		/// <returns> The client's address. </returns>
		__int64 GetAddress() const;
		/// <summary> Gets the client's address. </summary>
		/// <value> The client's address. </value>
		__declspec(property(get = GetAddress)) __int64 Address;

		/// <summary> Gets the subscribed characteristic by its index. </summary>
		/// <param name="Index"> The characteristic's index. The <c>Index</c>
		///   parameter must be in range between <c>0</c> and <c>Count - 1</c>.
		///   If the <c>Index</c> is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <returns> The <see cref="CwclGattLocalCharacteristic" /> object. </returns>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattLocalCharacteristic* GetCharacteristics(const size_t Index) const;
		/// <summary> Gets the subscribed characteristic by its index. </summary>
		/// <value> The <see cref="CwclGattLocalCharacteristic" /> object. </value>
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetCharacteristics)) CwclGattLocalCharacteristic* Characteristics[];

		/// <summary> Gets the <see cref="CwclGattServerConnection" /> object that
		///   owns the client. </summary>
		/// <returns> The <see cref="CwclGattServerConnection" /> object. </returns>
		/// <seealso cref="CwclGattServerConnection" />
		CwclGattServerConnection* GetConnection() const;
		/// <summary> Gets the <see cref="CwclGattServerConnection" /> object that
		///   owns the client. </summary>
		/// <value> The <see cref="CwclGattServerConnection" /> object. </value>
		/// <seealso cref="CwclGattServerConnection" />
		__declspec(property(get = GetConnection)) CwclGattServerConnection* Connection;

		/// <summary> Gets the subscribed characteristics count. </summary>
		/// <returns> The subscribed characteristics count. </returns>
		size_t GetCount() const;
		/// <summary> Gets the subscribed characteristics count. </summary>
		/// <value> The subscribed characteristics count. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets the client subscribed status. </summary>
		/// <returns> <c>True</c> if the client is subscribed to at least one
		///   characteristic. <c>False</c> otherwise. </returns>
		bool GetSubscribed() const;
		/// <summary> Gets the client subscribed status. </summary>
		/// <value> <c>True</c> if the client is subscribed to at least one
		///   characteristic. <c>False</c> otherwise. </value>
		__declspec(property(get = GetSubscribed)) bool Subscribed;
	};

	/// <summary> The "virtual" connection for the Bluetooth GATT Server </summary>
	/// <remarks> An application must not create or use this class directly.
	///   Instead of that an application must use high-level Bluetooth
	///   components. </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclGattServerConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclGattServerConnection);
		
	private:
		typedef std::list<CwclGattLocalService*> SERVICES;
		typedef std::list<CwclGattServerClient*> CLIENTS;

		CLIENTS*			FClients;
		HANDLE				FMutex;
		CwclBluetoothRadio*	FRadio;
		SERVICES*			FServices;
		
		/* Communication thread management. */

		// Communication thread.
		HANDLE	FThread;
		// Thread initialization result.
		int		FInitResult;
		// Thread initialization event.
		HANDLE	FInitEvent;
		// Thread termination event.
		HANDLE	FTermEvent;
		
		static UINT __stdcall _ThreadProc(LPVOID Param);
		void ThreadProc();

		/* Bulk notifications. */

		void NotifyDisconnected();
		void NotifyUnsubscribed();

		/* Clients management. */
		
		// Adds the client with given address to the clients list. Returns true
		// if client was created and added. Returns false if client was not created
		// but found in the list or if the client was not found and was not found in
		// the list. If the client was added or found the Client parameter is the
		// client object.
		bool AddClient(const __int64 Address, CwclGattServerClient*& Client);
		// Looks for the client with the given address in the clients list. Returns
		// the client object if found. Returns nil if not found.
		CwclGattServerClient* FindClient(const __int64 Address) const;
		// Deletes the client with the given address from the clients list. DOES NOT
		// destroy the found client object. Returns the client object that was
		// removed from the list. A caller is responsible to destroy the client
		// object!!!
		CwclGattServerClient* RemoveClient(const __int64 Address);
		
		// Called when connect/read/write/subscribe event received to simulate (or
		// process real) connection. Not all drivers provide event (in fact, no one
		// does) when remote client connected to the server. So we have to emulate
		// this. To do that we use read/write/subscribe events. Returns new
		// GATT server client object that can be used in other events.
		CwclGattServerClient* ClientConnected(const __int64 Address,
			CwclBluetoothGattServerClientParams* const Params);
		// Called when disconnect event received. Removes client from the list.
		void ClientDisconnected(const __int64 Address);

	protected:
		/* Internal methods. */
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message);
		
		/* Events. */
		
		/// <summary> Fires the <c>OnClientConnected</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a connected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoClientConnected(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnClientDisconnected</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoClientDisconnected(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnConnectionParamsChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoConnectionParamsChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnConnectionPhyChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoConnectionPhyChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnMaxPduSizeChanged</c> event. </summary>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoMaxPduSizeChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnNotificationSizeChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a client which changed the maximum notification
		///   size. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoNotificationSizeChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnRead</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that requested read. </param>
		/// <param name="Characteristic"> The local GATT characteristic object
		///   that requested the read operation. </param>
		/// <param name="Request"> The GATT read request object. </param>
		/// <remarks> This method is called when a remote GATT client requests
		///   read from the characteristic. </remarks>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="CwclGattLocalCharacteristicReadRequest" />
		virtual void DoRead(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicReadRequest* const Request);
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		/// <summary> Fires the <c>OnSubscribed</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that subscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void DoSubscribed(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		/// <summary> Fires the <c>OnUnsubscribed</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void DoUnsubscribed(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		/// <summary> Fires the <c>OnWrite</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that requested write. </param>
		/// <param name="Characteristic"> The local GATT characteristic object
		///   that requested the write operation. </param>
		/// <param name="Request"> The GATT characteristic write request
		///   object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="CwclGattLocalCharacteristicWriteRequest" />
		virtual void DoWrite(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicWriteRequest* const Request);
		
		/* HAL methods. */
		
		/// <summary> Implements a driver specific code to initialize Bluetooth LE
		///   GATT Server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver specific code. </remarks>
		virtual int HalInitialize() = 0;
		/// <summary> Implements a driver specific code to uninitialize Bluetooth LE
		///   GATT Server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver specific code. </remarks>
		virtual int HalUninitialize() = 0;
		
		/// <summary> Creates a driver specific local GATT service
		///   object. </summary>
		/// <param name="Uuid"> The service's UUID. </param>
		/// <param name="Service"> If the function completed with success this
		///   parameter includes just create local GATT service object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver specific code. </remarks>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="CwclGattLocalService" />
		virtual int HalCreateService(const wclGattUuid& Uuid, CwclGattLocalService*& Service) = 0;
		/// <summary> Creates a driver specific GATT server client
		///   object. </summary>
		/// <param name="Address"> The client's address. </param>
		/// <returns> If the method completed with success the returning value is
		///   just created <see cref="CwclGattServerClient" /> object. If the method
		///   failed the returning value is <c>nil</c>. </returns>
		/// <remarks> A derived class must override this method to provide
		///   driver specific code. </remarks>
		/// <seealso cref="CwclGattServerClient" />
		virtual CwclGattServerClient* HalCreateClient(const __int64 Address) = 0;
		
	public:
		/// <summary> Creates a new "virtual" GATT Server connection
		///   object. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattServerConnection(CwclBluetoothRadio* const Radio);
		/// <summary> Frees the GATT Server connection. </summary>
		virtual ~CwclGattServerConnection();
		
		/// <summary> Starts the Bluetooth LE GATT Server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 and above with the Microsoft
		///   Bluetooth drivers or on any other Windows platform with BlueSoleil
		///   Bluetooth drivers. </remarks>
		int Start();
		/// <summary> Stops the Bluetooth LE GATT Server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers or on any other Windows platform with BlueSoleil
		///   Bluetooth drivers. </remarks>
		int Stop();
		
		/// <summary> Creates new local GATT service and adds it to the services
		///   list. </summary>
		/// <param name="Uuid"> The service's UUID. </param>
		/// <param name="Service"> If the function completed with success this
		///   parameter receives a just created GATT local service object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="CwclGattLocalService" />
		int AddService(const wclGattUuid& Uuid, CwclGattLocalService*& Service);
		/// <summary> Clears the local services list. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int ClearServices();
		/// <summary> Deletes the service with given index. </summary>
		/// <param name="Index"> The service's index. The parameter must be in range
		///   between 0 and ServicesCount - 1. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DeleteService(const size_t Index);
		
		/// <summary> Gets the GATT server state. </summary>
		/// <returns> <c>True</c> if the GATT server is running. </returns>
		bool GetActive() const;
		/// <summary> Gets the GATT server state. </summary>
		/// <value> <c>True</c> if the GATT server is running. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets the GATT server client by its index. </summary>
		/// <param name="Index"> The client's index. The parameter must be in range
		///   between 0 and ClientsCount - 1. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <returns> The GATT server client object. </returns>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattServerClient* GetClients(const size_t Index) const;
		/// <summary> Gets the GATT server client by its index. </summary>
		/// <value> The GATT server client object. </value>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetClients)) CwclGattServerClient* Clients[];

		/// <summary> Gets the clients count. </summary>
		/// <returns> The clients count. </returns>
		size_t GetClientsCount() const;
		/// <summary> Gets the clients count. </summary>
		/// <value> The clients count. </value>
		__declspec(property(get = GetClientsCount)) size_t ClientsCount;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the local GATT service by its index. </summary>
		/// <param name="Index"> The service's index. The parameter must be in range
		///   between 0 and ServicesCount - 1. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <returns> The local GATT service object. </returns>
		/// <remarks> If server has not been initialized the
		///   <see cref="wclEGattServer" /> exception raises. </remarks>
		/// <seealso cref="CwclGattLocalService" />
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEGattServer"></exception>
		CwclGattLocalService* GetServices(const size_t Index) const;
		/// <summary> Gets the local GATT service by its index. </summary>
		/// <value> The local GATT service object. </value>
		/// <remarks> If server has not been initialized the
		///   <see cref="wclEGattServer" /> exception raises. </remarks>
		/// <seealso cref="CwclGattLocalService" />
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEGattServer"></exception>
		__declspec(property(get = GetServices)) CwclGattLocalService* Services[];

		/// <summary> Gets the services count. </summary>
		/// <returns> The services count. </returns>
		size_t GetServicesCount() const;
		/// <summary> Gets the services count. </summary>
		/// <value> The services count. </value>
		__declspec(property(get = GetServicesCount)) size_t ServicesCount;
		
		/// <summary> The event fires when a client connected to the
		///   server. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnClientConnected);
		/// <summary> The event fires when a client disconnected from
		///   the server. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnClientDisconnected);
		/// <summary> The event fires when the connection parameters changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth drivers on
		///   <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnConnectionParamsChanged);
		/// <summary> The event fires when the connection PHY changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionPhyInfo</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnConnectionPhyChanged);
		/// <summary> The event fires when maximum PDU size changed for the
		///   connected client. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnMaxPduSizeChanged);
		/// <summary> The event fires when a maximum notification size of a
		///   subscribed client has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnNotificationSizeChanged);
		/// <summary> The event fires when a remote GATT client requests
		///   characteristic's data read. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   requested read. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <param name="Request"> The GATT read request object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="TwclGattLocalCharacteristicReadRequest" />
		wclGattLocalCharacteristicReadEvent(OnRead);
		/// <summary> The event fires when the Bluetooth LE GATT Server has been
		///   successfully started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Bluetooth LE GATT Server has been
		///   stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
		/// <summary> The event fires when a remote GATT client subscribes to the
		///   characteristic changes notifications or indications. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   subscribed or unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		wclGattLocalCharacteristicSubscribedClientsChangedEvent(OnSubscribed);
		/// <summary> The event fires when a remote GATT client unsubscribes from
		///   the characteristic changes notifications or indications. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   subscribed or unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		wclGattLocalCharacteristicSubscribedClientsChangedEvent(OnUnsubscribed);
		/// <summary> The event fires when a remote device writes data to the
		///   characteristic. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   requested write. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <param name="Request"> The GATT characteristic write request object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="TwclGattLocalCharacteristicWriteRequest" />
		wclGattLocalCharacteristicWriteEvent(OnWrite);
	};

	/// <summary> The "virtual" connection for the Bluetooth LE Beacon Watcher. </summary>
	/// <remarks> An application must not create or use this class directly.
	///   Instead of that an application must use high-level Bluetooth
	///   components. </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclBluetoothLeBeaconWatcherConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclBluetoothLeBeaconWatcherConnection);
		
	private:
		bool						FAllowExtendedAdvertisements;
		bool						FMonitoring;
		CwclBluetoothRadio*			FRadio;
		unsigned short				FScanInterval;
		wclBluetoothLeScanningMode	FScanningMode;
		unsigned short				FScanWindow;

		void ResetScanParams();

		/* Apple frame parsers. */
		
		void ParseAppleAirdrop(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleAirplaySource(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleAirplayTarget(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleAirprint(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleFindMy(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleHandoff(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleHeySiri(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleHomeKit(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleiBeacon(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleMagicSwitch(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleNearbyAction(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleNearbyInfo(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleProximityPairing(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleTetheringSource(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleTetheringTarget(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseAppleUnknownFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const size_t Ndx, const wclBluetoothLeAdvertisementFrameRawData& Data);

		void ParseAppleAdvertisement(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);

		/* Microsoft frame parsers. */

		void ParseMsCdpBeacon(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);

		/* Manufacturer frame parsers. */

		void ParseAltBeacon(__int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);

		void ParseManufacturerRawFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);

		/* Other frame parsers. */

		void ParseDriAsdMessage(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void ParseEddystoneBeacons(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);

	protected:
		/* Internal methods. */
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;

		/* Event routines. */

		/// <summary> Fires the <c>OnAdvertisementAppearanceFrame</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Appearance"> The Bluetooth LE device appearance
		///   value. </param>
		virtual void DoAdvertisementAppearanceFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short Appearance);
		/// <summary> Fires the <c>OnAdvertisementFrameInformation</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Name"> The Bluetooth LE advertiser's name. </param>
		/// <param name="PacketType"> The Bluetooth LE advertisement data packet
		///   type. </param>
		/// <param name="Flags"> The Bluetooth LE advertisement packet payload
		///   flags. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementType" />
		/// <seealso cref="wclBluetoothLeAdvertisementFlags" />
		virtual void DoAdvertisementFrameInformation(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const tstring& Name, const wclBluetoothLeAdvertisementType PacketType,
			const wclBluetoothLeAdvertisementFlags& Flags);
		/// <summary> Fires the <c>OnAdvertisementExtFrameInformation</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AddressType"> The Bluetooth LE address type. </param>
		/// <param name="TxPower"> The received transmit power of the
		///   advertisement. Ranges from -127 dBm to 20 dBm. -128 indicates
		///   "no value". </param>
		/// <param name="Flags"> The Bluetooth LE advertisement extended frame
		///   flags. </param>
		/// <seealso cref="wclBluetoothAddressType" />
		/// <seealso cref="wclBluetoothLeExtendedFrameFlags" />
		virtual void DoAdvertisementExtFrameInformation(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothAddressType AddressType, const char TxPower,
			const wclBluetoothLeExtendedFrameFlags& Flags);
		/// <summary> Fires the <c>OnAdvertisementRawFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="DataType"> The frame's data type. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>NULL</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementRawFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned char DataType,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnAdvertisementReceived</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>nil</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementReceived(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService16DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService16DataFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService32DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService32DataFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned long Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService128DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService128DataFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const GUID& Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnServiceSol16Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol16Frame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short Uuid);
		/// <summary> Fires the <c>OnServiceSol32Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol32Frame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned long Uuid);
		/// <summary> Fires the <c>OnServiceSol128Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol128Frame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const GUID& Uuid);
		/// <summary> Fires the <c>OnAdvertisementTxPowerLevelFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxPower"> The TX power level in range from -127 to 128
		///   dBm. </param>
		virtual void DoAdvertisementTxPowerLevelFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxPower);
		/// <summary> Fires the <c>OnAdvertisementUuidFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The advertised UUID value. </param>
		virtual void DoAdvertisementUuidFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const GUID& Uuid);
		/// <summary> Fires the <c>OnAltBeaconFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Major"> The beacon's Major value. </param>
		/// <param name="Minor"> The beacon's Minor value. </param>
		/// <param name="Uuid"> The beacon's UUID. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Reserved"> A 1-byte value from 0x00 to 0xFF. Interpretation
		///   of this value is to be defined by the manufacturer and is to be
		///   evaluated based on the CompanyId value. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAltBeaconFrame(const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned short CompanyId, const unsigned short Major, const unsigned short Minor,
			const GUID& Uuid, const char TxRssi, const unsigned char Reserved,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnAppleAirdropFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirdropFrameData" />
		virtual void DoAppleAirdropFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirdropFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirplaySourceFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplaySourceFrameData" />
		virtual void DoAppleAirplaySourceFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplaySourceFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirplayTargetFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplayTargetFrameData" />
		virtual void DoAppleAirplayTargetFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplayTargetFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirprintFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirprintFrameData" />
		virtual void DoAppleAirprintFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirprintFrameData& Data);
		/// <summary> Fires the <c>OnAppleFindMyFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleFindMyFrameData" />
		virtual void DoAppleFindMyFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleFindMyFrameData& Data);
		/// <summary> Fires the <c>OnAppleHandoffFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		virtual void DoAppleHandoffFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHandoffFrameData& Data);
		/// <summary> Fires the <c>OnAppleHeySiriFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		virtual void DoAppleHeySiriFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHeySiriFrameData& Data);
		/// <summary> Fires the <c>OnAppleHomeKitFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHomeKitFrameData" />
		virtual void DoAppleHomeKitFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHomeKitFrameData& Data);
		/// <summary> Fires the <c>OnAppleiBeaconFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleiBeaconFrameData" />
		virtual void DoAppleiBeaconFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleiBeaconFrameData& Data);
		/// <summary> Fires the <c>OnAppleMagicSwitchFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleMagicSwitchFrameData" />
		virtual void DoAppleMagicSwitchFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleMagicSwitchFrameData& Data);
		/// <summary> Fires the <c>OnAppleNearbyActionFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyActionFrameData" />
		virtual void DoAppleNearbyActionFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyActionFrameData& Data);
		/// <summary> Fires the <c>OnAppleNearbyInfoFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyInfoFrameData" />
		virtual void DoAppleNearbyInfoFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyInfoFrameData& Data);
		/// <summary> Fires the <c>OnAppleProximityPairingFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleProximityPairingFrameData" />
		virtual void DoAppleProximityPairingFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleProximityPairingFrameData& Data);
		/// <summary> Fires the <c>OnAppleTetheringSourceFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringSourceFrameData" />
		virtual void DoAppleTetheringSourceFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringSourceFrameData& Data);
		/// <summary> Fires the <c>OnAppleTetheringTargetFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringTargetFrameData" />
		virtual void DoAppleTetheringTargetFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringTargetFrameData& Data);
		/// <summary> Fires the <c>OnAppleUnknownFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleUnknownFrameData" />
		virtual void DoAppleUnknownFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleUnknownFrameData& Data);
		/// <summary> Fires the <c>OnDriAsdMessage</c> event. </summary>
		/// <param name="Address"> The drone's MAC address. </param>
		/// <param name="Timestamp"> The message's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Raw"> The raw DRI ASD messages data. </param>
		virtual void DoDriAsdMessage(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclDriRawData& Raw);
		/// <summary> Fires the <c>OnEddystoneTlmFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AdvCnt"> The running count of advertisement frames of all
		///   types emitted by the beacon since power-up or reboot, useful for
		///   monitoring performance metrics that scale per broadcast frame.
		///   If this value is reset (e.g. on reboot), the current time field is
		///   also reset. </param>
		/// <param name="Batt"> The current battery charge in millivolts, expressed
		///   as 1 mV per bit. If not supported (for example in a USB-powered
		///   beacon) the value should be zeroed. </param>
		/// <param name="SecCnt"> The 0.1 second resolution counter that represents
		///   time since beacon power-up or reboot. If this value is reset (e.g. on
		///   a reboot), the AdvCnt count field is also reset. </param>
		/// <param name="Temp"> The beacon temperature in degrees Celsius sensed by
		///   the beacon. If not supported the value is -128 °C. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoEddystoneTlmFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned long AdvCnt, const unsigned short Batt,
			const unsigned long SecCnt, const double Temp,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnEddystoneUidFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Uuid"> The Eddystone ID: 10 bytes - Namespace ID and 6
		///   bytes - Instance ID. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoEddystoneUidFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnEddystoneUrlFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Url"> The Eddystone URL. </param>
		virtual void DoEddystoneUrlFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const tstring& Url);
		/// <summary> Fires the <c>OnManufacturerRawFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Data"> The frame raw data. The value can be <c>NULL</c> if
		///   there is no any data available in the frame. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoManufacturerRawFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnMicrosoftCdpBeaconFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="ScenarioType"> The beacon scenario. </param>
		/// <param name="Version"> The protocol version. </param>
		/// <param name="DeviceType"> The device type. </param>
		/// <param name="SubVersion"> The protocol subversion. </param>
		/// <param name="ShareNearBy"> If <c>True</c> then the NearBy share setting
		///   is everyone rather than only my devices. </param>
		/// <param name="AddressAsDeviceId"> <c>True</c> indicates that the
		///   Bluetooth address can be used as the device ID. </param>
		/// <param name="ExtendedDeviceStatus"> The extended device status. </param>
		/// <param name="Salt"> The beacon salt (4 random bytes). </param>
		/// <param name="Hash"> SHA256 Hash of Salt plus Device Thumbprint. </param>
		/// <seealso cref="wclBluetoothLeCdpBeaconScenarioType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconDeviceType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconSalt" />
		/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatuses" />
		/// <seealso cref="wclBluetoothLeCdpBeaconHash" />
		virtual void DoMicrosoftCdpBeaconFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeCdpBeaconScenarioType ScenarioType,
			const unsigned char Version, const wclBluetoothLeCdpBeaconDeviceType DeviceType,
			const unsigned char SubVersion, const bool ShareNearBy,
			const bool AddressAsDeviceId,
			const wclBluetoothLeCdpBeaconExtendedDeviceStatuses& ExtendedDeviceStatus,
			const wclBluetoothLeCdpBeaconSalt& Salt, const wclBluetoothLeCdpBeaconHash& Hash);
		
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();

		/* HAL methods. */

		/// <summary> Implements a hardware-dependent code to start Bluetooth LE
		///   Beacon monitoring. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalStart() = 0;
		/// <summary> Implements a hardware-dependent code to stop Bluetooth LE
		///   Beacon monitoring. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalStop() = 0;

	public:
		/// <summary> Creates a new "virtual" Beacon Watcher connection
		///   object. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeBeaconWatcherConnection(CwclBluetoothRadio* const Radio);
		/// <summary> Frees the Beacon Watcher. </summary>
		virtual ~CwclBluetoothLeBeaconWatcherConnection();

		/// <summary> Starts monitoring for Bluetooth LE Beacons. </summary>
		/// <param name="AllowExtendedAdvertisements"> Set this parameter to
		///   <c>true</c> to enable receiving advertisements of the Extended
		///   Advertising format can be received. If this parameter set to
		///   <c>true</c> and a hardware or OS does not support Extended
		///   Advertisements the
		///   <see cref="WCL_E_BLUETOOTH_LE_EXT_ADV_NOT_SUPPORTED" /> error will
		///   be returned. </param>
		/// <param name="ScanInterval"> Specifies the Bluetooth LE scan in 0.625 ms
		///   units. The value must be in range between 4 and 16384. </param>
		/// <param name="ScanningMode"> Specifies the Bluetooth LE scanning
		///   mode. </param>
		/// <param name="ScanWindow"> Specifies the Bluetooth LE scan window in
		///   0.625 ms units. The value must be in range between 4 and 16384. The
		///   scan window must be less or equal to <c>ScanInterval</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		int Start(const bool AllowExtendedAdvertisements, const unsigned short ScanInterval,
			const wclBluetoothLeScanningMode ScanningMode, const unsigned short ScanWindow);
		/// <summary> Stops monitoring for Bluetooth LE Beacons. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers only. </remarks>
		int Stop();

		/// <summary> Gets the Extended Advertisement receiving flag. </summary>
		/// <returns> <c>true</c> if the receiving the Extended Advertisement is
		///   enabled. <c>false</c> otherwise. </returns>
		bool GetAllowExtendedAdvertisements() const;
		/// <summary> Gets the Extended Advertisement receiving flag. </summary>
		/// <value> <c>true</c> if the receiving the Extended Advertisement is
		///   enabled. <c>false</c> otherwise. </value>
		__declspec(property(get = GetAllowExtendedAdvertisements)) bool AllowExtendedAdvertisements;

		/// <summary> Gets Beacon Monitoring state. </summary>
		/// <returns> <c>True</c> if the Beacon monitoring is running. </returns>
		bool GetMonitoring() const;
		/// <summary> Gets Beacon Monitoring state. </summary>
		/// <value> <c>True</c> if the Beacon monitoring is running. </value>
		__declspec(property(get = GetMonitoring)) bool Monitoring;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the current scan interval value. </summary>
		/// <returns> The current scan interval. </returns>
		unsigned short GetScanInterval() const;
		/// <summary> Gets the current scan interval value. </summary>
		/// <value> The current scan interval. </value>
		__declspec(property(get = GetScanInterval)) unsigned short ScanInterval;

		/// <summary> Gets the current scanning mode. </summary>
		/// <returns> The Bluetooth LE scanning mode. </returns>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		wclBluetoothLeScanningMode GetScanningMode() const;
		/// <summary> Gets the current scanning mode. </summary>
		/// <value> The Bluetooth LE scanning mode. </value>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		__declspec(property(get = GetScanningMode)) wclBluetoothLeScanningMode ScanningMode;

		/// <summary> Gets the current scan window value. </summary>
		/// <returns> The current scan window. </returns>
		unsigned short GetScanWindow() const;
		/// <summary> Gets the current scan window value. </summary>
		/// <value> The current scan window. </value>
		__declspec(property(get = GetScanWindow)) unsigned short ScanWindow;

		/// <summary> The event fires when an appearance advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Appearance"> The Bluetooth LE device appearance
		///   value. </param>
		wclBluetoothLeAdvertisementAppearanceFrameEvent(OnAdvertisementAppearanceFrame);
		/// <summary> The event fires when new Bluetooth LE advertisement frame
		///   has been received and provides the common basic information about
		///   the frame. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Name"> The Bluetooth LE advertiser's name. </param>
		/// <param name="PacketType"> The Bluetooth LE advertisement data packet
		///   type. </param>
		/// <param name="Flags"> The Bluetooth LE advertisement packet payload
		///   flags. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementType" />
		/// <seealso cref="wclBluetoothLeAdvertisementFlags" />
		wclBluetoothLeAdvertisementFrameInformationEvent(OnAdvertisementFrameInformation);
		/// <summary> The event fires when new Bluetooth LE advertisement
		///   extended frame has been received and provides the common basic
		///   information about the frame. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AddressType"> The Bluetooth LE address type. </param>
		/// <param name="TxPower"> The received transmit power of the
		///   advertisement. Ranges from -127 dBm to 20 dBm. -128 indicates
		///   "no value". </param>
		/// <param name="Flags"> The Bluetooth LE advertisement extended frame
		///   flags. </param>
		/// <seealso cref="wclBluetoothAddressType" />
		/// <seealso cref="wclBluetoothLeExtendedFrameFlags" />
		wclBluetoothLeAdvertisementExtFrameInformationEvent(OnAdvertisementExtFrameInformation);
		/// <summary> The <c>OnAdvertisementRawFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="DataType"> The frame's data type. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>NULL</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementRawFrameEvent(OnAdvertisementRawFrame);
		/// <summary> The event fires when any Bluetooth LE advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>nil</c>. </param>
		/// <remarks> Unlike the <c>OnAdvertisementRawFrame</c> and the
		///   <c>OnManufacturerRawFrame</c> this even fires for any Bluetooth LE
		///   advertisement and contains unparsed raw frame data. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementReceivedEvent(OnAdvertisementReceived);
		/// <summary> The event fires when a Bluetooth LE 16 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService16DataFrameEvent(OnAdvertisementService16DataFrame);
		/// <summary> The event fires when a Bluetooth LE 32 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bits service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService32DataFrameEvent(OnAdvertisementService32DataFrame);
		/// <summary> The event fires when a Bluetooth LE 128 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bits service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService128DataFrameEvent(OnAdvertisementService128DataFrame);
		/// <summary> The event fires when a Bluetooth LE 16 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol16FrameEvent(OnAdvertisementServiceSol16Frame);
		/// <summary> The event fires when a Bluetooth LE 32 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol32FrameEvent(OnAdvertisementServiceSol32Frame);
		/// <summary> The event fires when a Bluetooth LE 128 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol128FrameEvent(OnAdvertisementServiceSol128Frame);
		/// <summary> The event fires when a TX power level advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxPower"> The TX power level in range from -127 to 128
		///   dBm. </param>
		wclBluetoothLeAdvertisementTxPowerLevelFrameEvent(OnAdvertisementTxPowerLevelFrame);
		/// <summary> The event fires when an UUID advertisement frame has been
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The advertised UUID value. </param>
		wclBluetoothLeAdvertisementUuidFrameEvent(OnAdvertisementUuidFrame);
		/// <summary> The event fires when a Bluetooth LE Alt beacon
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Major"> The beacon's Major value. </param>
		/// <param name="Minor"> The beacon's Minor value. </param>
		/// <param name="Uuid"> The beacon's UUID. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Reserved"> A 1-byte value from 0x00 to 0xFF. Interpretation
		///   of this value is to be defined by the manufacturer and is to be
		///   evaluated based on the CompanyId value. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAltBeaconFrameEvent(OnAltBeaconFrame);
		/// <summary> The event fires when an Apple Airdrop advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirdropFrameData" />
		wclBluetoothLeAppleAirdropFrameEvent(OnAppleAirdropFrame);
		/// <summary> The event fires when an Apple Airplay Source advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplaySourceFrameData" />
		wclBluetoothLeAppleAirplaySourceFrameEvent(OnAppleAirplaySourceFrame);
		/// <summary> The event fires when an Apple Airplay Target advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplayTargetFrameData" />
		wclBluetoothLeAppleAirplayTargetFrameEvent(OnAppleAirplayTargetFrame);
		/// <summary> The event fires when an Apple Airprint advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirprintFrameData" />
		wclBluetoothLeAppleAirprintFrameEvent(OnAppleAirprintFrame);
		/// <summary> The event fires when an Apple Find My advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleFindMyFrameData" />
		wclBluetoothLeAppleFindMyFrameEvent(OnAppleFindMyFrame);
		/// <summary> The event fires when an Apple Handoff advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHandoffFrameData" />
		wclBluetoothLeAppleHandoffFrameEvent(OnAppleHandoffFrame);
		/// <summary> The event fires when an Apple Hey Siri advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="TwclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		wclBluetoothLeAppleHeySiriFrameEvent(OnAppleHeySiriFrame);
		/// <summary> The event fires when an Apple HomeKit advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHomeKitFrameData" />
		wclBluetoothLeAppleHomeKitFrameEvent(OnAppleHomeKitFrame);
		/// <summary> The event fires when an Apple iBeacon advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleiBeaconFrameData" />
		wclBluetoothLeAppleiBeaconFrameEvent(OnAppleiBeaconFrame);
		/// <summary> The event fires when an Apple Magic Switch advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleMagicSwitchFrameData" />
		wclBluetoothLeAppleMagicSwitchFrameEvent(OnAppleMagicSwitchFrame);
		/// <summary> The event fires when an Apple Nearby Action advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyActionFrameData" />
		wclBluetoothLeAppleNearbyActionFrameEvent(OnAppleNearbyActionFrame);
		/// <summary> The event fires when an Apple Nearby Info advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyInfoFrameData" />
		wclBluetoothLeAppleNearbyInfoFrameEvent(OnAppleNearbyInfoFrame);
		/// <summary> The event fires when an Apple Proximity Pairing advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleProximityPairingFrameData" />
		wclBluetoothLeAppleProximityPairingFrameEvent(OnAppleProximityPairingFrame);
		/// <summary> The event fires when an Tethering Source advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringSourceFrameData" />
		wclBluetoothLeAppleTetheringSourceFrameEvent(OnAppleTetheringSourceFrame);
		/// <summary> The event fires when an Tethering Target advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringTargetFrameData" />
		wclBluetoothLeAppleTetheringTargetFrameEvent(OnAppleTetheringTargetFrame);
		/// <summary> The event fires when an unknown Apple advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleUnknownFrameData" />
		wclBluetoothLeAppleUnknownFrameEvent(OnAppleUnknownFrame);
		/// <summary> The event fires when a Drone Remote ID ASD message
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The drone's MAC address. </param>
		/// <param name="Timestamp"> The message's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Raw"> The raw DRI ASD messages data. </param>
		wclBluetoothLeDriAsdMessageEvent(OnDriAsdMessage);
		/// <summary> The <c>OnEddystoneTlmFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AdvCnt"> The running count of advertisement frames of all
		///   types emitted by the beacon since power-up or reboot, useful for
		///   monitoring performance metrics that scale per broadcast frame.
		///   If this value is reset (e.g. on reboot), the current time field is
		///   also reset. </param>
		/// <param name="Batt"> The current battery charge in millivolts, expressed as
		///   1 mV per bit. If not supported (for example in a USB-powered beacon) the
		///   value should be zeroed. </param>
		/// <param name="SecCnt"> The 0.1 second resolution counter that represents
		///   time since beacon power-up or reboot. If this value is reset (e.g. on
		///   a reboot), the AdvCnt count field is also reset. </param>
		/// <param name="Temp"> The beacon temperature in degrees Celsius sensed by
		///   the beacon. If not supported the value is -128 °C. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeEddystoneTlmFrameEvent(OnEddystoneTlmFrame);
		/// <summary> The <c>OnEddystoneUidFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Uuid"> The Eddystone ID: 10 bytes - Namespace ID and 6
		///   bytes - Instance ID. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeEddystoneUidFrameEvent(OnEddystoneUidFrame);
		/// <summary> The <c>OnEddystoneUrlFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Url"> The Eddystone URL. </param>
		wclBluetoothLeEddystoneUrlFrameEvent(OnEddystoneUrlFrame);
		/// <summary> The <c>OnManufacturerRawFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Data"> The frame raw data. The value can be <c>NULL</c> if
		///   there is no any data available in the frame. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeManufacturerRawFrameEvent(OnManufacturerRawFrame);
		/// <summary> The event fires when Microsoft CDP Beacon frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="ScenarioType"> The beacon scenario. </param>
		/// <param name="Version"> The protocol version. </param>
		/// <param name="DeviceType"> The device type. </param>
		/// <param name="SubVersion"> The protocol subversion. </param>
		/// <param name="ShareNearBy"> If <c>True</c> then the NearBy share setting is
		///   everyone rather than only my devices. </param>
		/// <param name="AddressAsDeviceId"> <c>True</c> indicates that the Bluetooth
		///   address can be used as the device ID. </param>
		/// <param name="ExtendedDeviceStatus"> The extended device status. </param>
		/// <param name="Salt"> The beacon salt (4 random bytes). </param>
		/// <param name="Hash"> SHA256 Hash of Salt plus Device Thumbprint. </param>
		/// <seealso cref="wclBluetoothLeCdpBeaconScenarioType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconDeviceType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconSalt" />
		/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatuses" />
		/// <seealso cref="wclBluetoothLeCdpBeaconHash" />
		wclBluetoothLeMicrosoftCdpBeaconFrameEvent(OnMicrosoftCdpBeaconFrame);
		/// <summary> The event fires when the Bluetooth LE beacon monitoring
		///   started. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Bluetooth LE beacon monitoring
		///   stopped. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The base class for Bluetooth LE advertisement. </summary>
	class CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisement);

	private:
		RTL_CRITICAL_SECTION	FCS;

	protected:
		/// <summary> Enters the advertisement data protection critical
		///   section. </summary>
		void Enter() const;
		/// <summary> Leaves the advertisement data protection critical
		///   section. </summary>
		void Leave() const;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		CwclBluetoothLeAdvertisement();
		/// <summary> Frees the object. </summary>
		virtual ~CwclBluetoothLeAdvertisement();

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const = 0;
	};

	/// <summary> The base class for Bluetooth LE advertisements that include
	///   calibrated RSSI value. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLeTxRssiAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeTxRssiAdvertisement);
		
	private:
		char	FTxRssi;

	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeTxRssiAdvertisement(const char TxRssi);
		
		/// <summary> Gets the calibrated RSSI value. </summary>
		/// <returns> The calibrated RSSI value in dBm. </returns>
		char GetTxRssi() const;
		/// <summary> Gets the calibrated RSSI value. </summary>
		/// <value> The calibrated RSSI value in dBm. </value>
		__declspec(property(get = GetTxRssi)) char TxRssi;
	};

	/// <summary> The base class for Bluetooth LE advertisements that include
	///   IDs. </summary>
	/// <seealso cref="CwclBluetoothLeTxRssiAdvertisement" />
	class CwclBluetoothLeIdAdvertisement : public CwclBluetoothLeTxRssiAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeIdAdvertisement);
		
	private:
		unsigned short	FMajor;
		unsigned short	FMinor;
		GUID			FUuid;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Major"> The major value. </param>
		/// <param name="Minor"> The minor value. </param>
		/// <param name="Uuid"> The UUID. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeIdAdvertisement(const char TxRssi, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid);

		/// <summary> Gets the major value. </summary>
		/// <returns> The major value. </returns>
		unsigned short GetMajor() const;
		/// <summary> Gets the major value. </summary>
		/// <value> The major value. </value>
		__declspec(property(get = GetMajor)) unsigned short Major;

		/// <summary> Gets the minor value. </summary>
		/// <returns> The minor value. </returns>
		unsigned short GetMinor() const;
		/// <summary> Gets the minor value. </summary>
		/// <value> The minor value. </value>
		__declspec(property(get = GetMinor)) unsigned short Minor;

		/// <summary> Gets the UUID. </summary>
		/// <returns> The UUID. </returns>
		GUID GetUuid() const;
		/// <summary> Gets the UUID. </summary>
		/// <value> The UUID. </value>
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	/// <summary> The Bluetooth LE iBeacon advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeIdAdvertisement" />
	class CwclBluetoothLeiBeaconAdvertisement : public CwclBluetoothLeIdAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeiBeaconAdvertisement);
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Major"> The major value. </param>
		/// <param name="Minor"> The minor value. </param>
		/// <param name="Uuid"> The UUID. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeiBeaconAdvertisement(const char TxRssi, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
	};

	/// <summary> The base class for Bluetooth LE advertisements that include
	///   company (manufacturer) ID. </summary>
	/// <seealso cref="CwclBluetoothLeIdAdvertisement" />
	class CwclBluetoothLeCompanyIdAdvertisement : public CwclBluetoothLeIdAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeCompanyIdAdvertisement);
		
	private:
		unsigned short	FCompanyId;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Major"> The major value. </param>
		/// <param name="Minor"> The minor value. </param>
		/// <param name="Uuid"> The UUID. </param>
		/// <param name="CompanyId"> The manufacturer ID as defined in the Bluetooth
		///   SIG Assigned Numbers. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeCompanyIdAdvertisement(const char TxRssi, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid, const unsigned short CompanyId);
		
		/// <summary> Gets the manufacturer ID. </summary>
		/// <returns> The manufacturer ID as defined in the Bluetooth SIG
		///   Assigned Numbers. </returns>
		unsigned short GetCompanyId() const;
		/// <summary> Gets the manufacturer ID. </summary>
		/// <value> The manufacturer ID as defined in the Bluetooth SIG
		///   Assigned Numbers. </value>
		__declspec(property(get = GetCompanyId)) unsigned short CompanyId;
	};

	/// <summary> The Bluetooth LE proximity beacon advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeCompanyIdAdvertisement" />
	class CwclBluetoothLeProximityBeaconAdvertisement : public CwclBluetoothLeCompanyIdAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeProximityBeaconAdvertisement);
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Major"> The major value. </param>
		/// <param name="Minor"> The minor value. </param>
		/// <param name="Uuid"> The UUID. </param>
		/// <param name="CompanyId"> The manufacturer ID as defined in the Bluetooth
		///   SIG Assigned Numbers. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeProximityBeaconAdvertisement(const char TxRssi, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid, const unsigned short CompanyId);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
	};

	/// <summary> The Bluetooth LE Alt beacon advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeCompanyIdAdvertisement" />
	class CwclBluetoothLeAltBeaconAdvertisement : public CwclBluetoothLeCompanyIdAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeAltBeaconAdvertisement);
		
	private:
		unsigned char	FReserved;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Major"> The major value. </param>
		/// <param name="Minor"> The minor value. </param>
		/// <param name="Uuid"> The UUID. </param>
		/// <param name="CompanyId"> The manufacturer ID as defined in the Bluetooth
		///   SIG Assigned Numbers. </param>
		/// <param name="Reserved"> The beacon's manufacturer reserved
		///   value. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeAltBeaconAdvertisement(const char TxRssi, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid, const unsigned short CompanyId,
			const unsigned char Reserved);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the beacon's manufacturer reserved value. </summary>
		/// <returns> A 1-byte value from 0x00 to 0xFF. Interpretation of this value
		///   is to be defined by the manufacturer and is to be evaluated based on
		///   the <c>CompanyId</c> value. </returns>
		unsigned char GetReserved() const;
		/// <summary> Gets the beacon's manufacturer reserved value. </summary>
		/// <value> A 1-byte value from 0x00 to 0xFF. Interpretation of this value
		///   is to be defined by the manufacturer and is to be evaluated based on
		///   the <c>CompanyId</c> value. </value>
		__declspec(property(get = GetReserved)) unsigned char Reserved;
	};

	/// <summary> The Bluetooth LE Eddystone UID beacon advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeTxRssiAdvertisement" />
	class CwclBluetoothLeEddystoneUidBeaconAdvertisement : public CwclBluetoothLeTxRssiAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeEddystoneUidBeaconAdvertisement);
		
	private:
		GUID	FUuid;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Uuid"> The beacon's UUID. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeEddystoneUidBeaconAdvertisement(const char TxRssi, const GUID& Uuid);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the beacon's UUID. </summary>
		/// <returns> The beacon's UUID. </returns>
		GUID GetUuid() const;
		/// <summary> Gets the beacon's UUID. </summary>
		/// <value> The beacon's UUID. </value>
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	/// <summary> The Bluetooth LE Eddystone URL beacon advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeTxRssiAdvertisement" />
	class CwclBluetoothLeEddystoneUrlBeaconAdvertisement : public CwclBluetoothLeTxRssiAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeEddystoneUrlBeaconAdvertisement);
		
	private:
		tstring					FUrl;
		
		wclEddystoneEncodedUrl	FUrlEncoded;
		unsigned char			FUrlScheme;
		
		int ParseUrl(const tstring& Value);
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="TxRssi"> The calibrated RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Url"> The beacon's URL. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeEddystoneUrlBeaconAdvertisement(const char TxRssi,
			const tstring& Url);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the beacon's URL. </summary>
		/// <returns> The beacon's URL. </returns>
		tstring GetUrl() const;
		/// <summary> Gets the beacon's URL. </summary>
		/// <value> The beacon's URL. </value>
		__declspec(property(get = GetUrl)) tstring Url;
	};

	/// <summary> The Bluetooth LE 16 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLe16ServiceAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe16ServiceAdvertisement);
		
	private:
		unsigned short	FUuid;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 16 bit service's UUID. </param>
		CwclBluetoothLe16ServiceAdvertisement(const unsigned short Uuid);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's UUID. </summary>
		/// <returns> The 16 bit UUID. </returns>
		unsigned short GetUuid() const;
		/// <summary> Gets the service's UUID. </summary>
		/// <value> The 16 bit UUID. </value>
		__declspec(property(get = GetUuid)) unsigned short Uuid;
	};

	/// <summary> The Bluetooth LE 32 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLe32ServiceAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe32ServiceAdvertisement);
		
	private:
		unsigned long	FUuid;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 32 bit service's UUID. </param>
		CwclBluetoothLe32ServiceAdvertisement(const unsigned long Uuid);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's UUID. </summary>
		/// <returns> The 32 bit UUID. </returns>
		unsigned long GetUuid() const;
		/// <summary> Gets the service's UUID. </summary>
		/// <value> The 32 bit UUID. </value>
		__declspec(property(get = GetUuid)) unsigned long Uuid;
	};

	/// <summary> The Bluetooth LE 128 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLe128ServiceAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe128ServiceAdvertisement);
		
	private:
		GUID	FUuid;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 128 bit service's UUID. </param>
		CwclBluetoothLe128ServiceAdvertisement(const GUID& Uuid);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's UUID. </summary>
		/// <returns> The 128 bit UUID. </returns>
		GUID GetUuid() const;
		/// <summary> Gets the service's UUID. </summary>
		/// <value> The 128 bit UUID. </value>
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	/// <summary> The Bluetooth LE 16 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLe16ServiceAdvertisement" />
	class CwclBluetoothLe16ServiceDataAdvertisement : public CwclBluetoothLe16ServiceAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe16ServiceDataAdvertisement);
		
	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 16 bit service's UUID. </param>
		/// <param name="Data"> The service's data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLe16ServiceDataAdvertisement(const unsigned short Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's data. </summary>
		/// <returns> The service's data. </returns>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the service's data. </summary>
		/// <value> The service's data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	/// <summary> The Bluetooth LE 32 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLe32ServiceAdvertisement" />
	class CwclBluetoothLe32ServiceDataAdvertisement : public CwclBluetoothLe32ServiceAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe32ServiceDataAdvertisement);
		
	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 32 bit service's UUID. </param>
		/// <param name="Data"> The service's data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLe32ServiceDataAdvertisement(const unsigned long Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's data. </summary>
		/// <returns> The service's data. </returns>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the service's data. </summary>
		/// <value> The service's data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	/// <summary> The Bluetooth LE 128 bit UUID service advertisement. </summary>
	/// <seealso cref="CwclBluetoothLe32ServiceAdvertisement" />
	class CwclBluetoothLe128ServiceDataAdvertisement : public CwclBluetoothLe128ServiceAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLe128ServiceDataAdvertisement);

	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Uuid"> The 128 bit service's UUID. </param>
		/// <param name="Data"> The service's data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLe128ServiceDataAdvertisement(const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the service's data. </summary>
		/// <returns> The service's data. </returns>
		/// <seealso cref="TwclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the service's data. </summary>
		/// <value> The service's data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	/// <summary> The Bluetooth LE custom advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLeCustomAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeCustomAdvertisement);
		
	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		unsigned char							FDataType;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="DataType"> <para> The Bluetooth LE advertisement data type.
		///   This is one of the data type defined in the wclUUIDs. </para>
		///   <para> The following advertisement types <c>are reserved and
		///   are not allowed</c>: </para>
		///   <para> * Empty flags (LE_GAP_AD_TYPE_NONE [0x00]) </para>
		///   <para> * Flags (LE_GAP_AD_TYPE_FLAGS [0x01]) </para>
		///   <para> * Shortened Local Name
		///            (LE_GAP_AD_TYPE_LOCAL_NAME_SHORT [0x08]) </para>
		///   <para> * Complete Local Name
		///            (LE_GAP_AD_TYPE_LOCAL_NAME_COMPLETE [0x09]) </para>
		///   <para> * LE Bluetooth Device Address
		///            (LE_GAP_AD_TYPE_ADDRESS [0x1B]) </para>
		///   <para> * LE Role (LE_GAP_AD_TYPE_ROLE [0x1C]) </para>
		///   <para> * Manufacturer Specific Information
		///            (LE_GAP_AD_TYPE_MANUFACTURER [0xFF]) </para>
		///   <para> The following advertisement types <c>are system-reserved and
		///   are not allowed</c> if the advertisement is used with <c>Microsoft</c>
		///   Bluetooth driver: </para>
		///   <para> * Incomplete List of 16-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_16_MORE [0x02]) </para>
		///   <para> * Complete List of 16-bit Service Class UUIDs
		///          * (LE_GAP_AD_TYPE_SERVICES_16_ALL [0x03]) </para>
		///   <para> * Incomplete List of 32-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_32_MORE [0x04]) </para>
		///   <para> * Complete List of 32-bit Service Class UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_32_ALL [0x05]) </para>
		///   <para> * Incomplete List of 128-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_128_MORE [0x06]) </para>
		///   <para> * Complete List of 128-bit Service Class UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_128_ALL [0x07]) </para>
		///   <para> * TX Power Level (LE_GAP_AD_TYPE_TXPOWER [0x0A]) </para>
		///   <para> * Class of Device (LE_GAP_AD_TYPE_COD [0x0D]) </para>
		///   <para> * Simple Pairing Hash C192
		///            (LE_GAP_AD_TYPE_PAIRING_HASH_C [0x0E]) </para>
		///   <para> * Simple Pairing Randomizer R192
		///            (LE_GAP_AD_TYPE_PAIRING_RAND_R [0x0F]) </para>
		///   <para> * Security Manager TK Values
		///            (LE_GAP_AD_TYPE_DEVICE_ID [0x10]) </para>
		///   <para> * Security Manager Out-of-Band Flags
		///            (LE_GAP_AD_TYPE_SM_OOB_FLAGS [0x11]) </para>
		///   <para> * Slave Connection Interval Range
		///            (LE_GAP_AD_TYPE_CON_INTERVALS [0x12]) </para>
		///   <para> * Public Target Address
		///            (LE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS [0x17]) </para>
		///   <para> * Random Target Address
		///            (LE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS [0x18]) </para>
		///   <para> * Appearance (LE_GAP_AD_TYPE_APPEARANCE [0x19]) </para>
		///   <para> * Advertising Interval
		///            (LE_GAP_AD_TYPE_ADV_INTERVAL [0x1A]) </para>
		///   <para> * Simple Pairing Hash C256
		///            (LE_GAP_AD_TYPE_PAIRING_HASH_C_256 [0x1D]) </para>
		///   <para> * Simple Pairing Randomizer R256
		///            (LE_GAP_AD_TYPE_PAIRING_RAND_R_256 [0x1E]) </para>
		///   <para> * 3D Information Data
		///            (LE_GAP_AD_TYPE_3D_INFO [0x3D]) </para> </param>
		/// <param name="Data"> The Bluetooth LE advertisement raw data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeCustomAdvertisement(const unsigned char DataType,
			const wclBluetoothLeAdvertisementFrameRawData& Data);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the advertisement raw data. </summary>
		/// <returns> The Bluetooth LE advertisement raw data. </returns>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the advertisement raw data. </summary>
		/// <value> The Bluetooth LE advertisement raw data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;

		/// <summary> Gets the advertisement data type. </summary>
		/// <returns> The Bluetooth LE advertisement data type as defined in
		///   wclUUIDs. </returns>
		unsigned char GetDataType() const;
		/// <summary> Gets the advertisement data type. </summary>
		/// <value> The Bluetooth LE advertisement data type as defined in
		///   wclUUIDs. </value>
		__declspec(property(get = GetDataType)) unsigned char DataType;
	};

	/// <summary> The Bluetooth LE custom manufacturer specific
	///   advertisement. </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLeManufacturerAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeManufacturerAdvertisement);
		
	private:
		unsigned short							FCompanyId;
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="CompanyId"> The manufacturer company ID. </param>
		/// <param name="Data"> The Bluetooth LE advertisement raw data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeManufacturerAdvertisement(const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);

		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the manufacturer company ID. </summary>
		/// <returns> The manufacturer company ID. </returns>
		unsigned short GetCompanyId() const;
		__declspec(property(get = GetCompanyId)) unsigned short CompanyId;

		/// <summary> Gets the advertisement raw data. </summary>
		/// <returns> The Bluetooth LE advertisement raw data. </returns>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the advertisement raw data. </summary>
		/// <value> The Bluetooth LE advertisement raw data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	/// <summary> The Bluetooth LE custom raw advertisement. </summary>
	/// <remarks> This class allows to build a Bluetooth LE advertisement from raw
	///   data bytes stream. </remarks>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	class CwclBluetoothLeRawAdvertisement : public CwclBluetoothLeAdvertisement
	{
		DISABLE_COPY(CwclBluetoothLeRawAdvertisement);

	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
		unsigned char GetFramesCount(const wclBluetoothLeAdvertisementFrameRawData& Data) const;

	public:
		/// <summary> Creates new Bluetooth LE advertisement object. </summary>
		/// <param name="Data"> The Bluetooth LE advertisement raw data. </param>
		/// <remarks> <para> The following advertisement data types <c>are reserved
		///   and are not allowed</c>: </para>
		///   <para> * Empty flags (LE_GAP_AD_TYPE_NONE [0x00]) </para>
		///   <para> * Flags (LE_GAP_AD_TYPE_FLAGS [0x01]) </para>
		///   <para> * Shortened Local Name
		///            (LE_GAP_AD_TYPE_LOCAL_NAME_SHORT [0x08]) </para>
		///   <para> * Complete Local Name
		///            (LE_GAP_AD_TYPE_LOCAL_NAME_COMPLETE [0x09]) </para>
		///   <para> * LE Bluetooth Device Address
		///            (LE_GAP_AD_TYPE_ADDRESS [0x1B]) </para>
		///   <para> * LE Role (LE_GAP_AD_TYPE_ROLE [0x1C]) </para>
		///   <para> * Incomplete List of 16-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_16_MORE [0x02]) </para>
		///   <para> * Complete List of 16-bit Service Class UUIDs
		///          * (LE_GAP_AD_TYPE_SERVICES_16_ALL [0x03]) </para>
		///   <para> * Incomplete List of 32-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_32_MORE [0x04]) </para>
		///   <para> * Complete List of 32-bit Service Class UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_32_ALL [0x05]) </para>
		///   <para> * Incomplete List of 128-bit Service UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_128_MORE [0x06]) </para>
		///   <para> * Complete List of 128-bit Service Class UUIDs
		///            (LE_GAP_AD_TYPE_SERVICES_128_ALL [0x07]) </para>
		///   <para> * TX Power Level (LE_GAP_AD_TYPE_TXPOWER [0x0A]) </para>
		///   <para> * Class of Device (LE_GAP_AD_TYPE_COD [0x0D]) </para>
		///   <para> * Simple Pairing Hash C192
		///            (LE_GAP_AD_TYPE_PAIRING_HASH_C [0x0E]) </para>
		///   <para> * Simple Pairing Randomizer R192
		///            (LE_GAP_AD_TYPE_PAIRING_RAND_R [0x0F]) </para>
		///   <para> * Security Manager TK Values
		///            (LE_GAP_AD_TYPE_DEVICE_ID [0x10]) </para>
		///   <para> * Security Manager Out-of-Band Flags
		///            (LE_GAP_AD_TYPE_SM_OOB_FLAGS [0x11]) </para>
		///   <para> * Slave Connection Interval Range
		///            (LE_GAP_AD_TYPE_CON_INTERVALS [0x12]) </para>
		///   <para> * Public Target Address
		///            (LE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS [0x17]) </para>
		///   <para> * Random Target Address
		///            (LE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS [0x18]) </para>
		///   <para> * Appearance (LE_GAP_AD_TYPE_APPEARANCE [0x19]) </para>
		///   <para> * Advertising Interval
		///            (LE_GAP_AD_TYPE_ADV_INTERVAL [0x1A]) </para>
		///   <para> * Simple Pairing Hash C256
		///            (LE_GAP_AD_TYPE_PAIRING_HASH_C_256 [0x1D]) </para>
		///   <para> * Simple Pairing Randomizer R256
		///            (LE_GAP_AD_TYPE_PAIRING_RAND_R_256 [0x1E]) </para>
		///   <para> * 3D Information Data
		///            (LE_GAP_AD_TYPE_3D_INFO [0x3D]) </para> </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeRawAdvertisement(const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		/// <summary> Builds the Bluetooth LE advertisement frames array that
		///   contains raw data of the Bluetooth LE advertisement. </summary>
		/// <param name="Frames"> On output contains the Bluetooth LE advertisement
		///   frames array representing the current advertisement data. </param>
		/// <remarks> A derived class must override this method. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrames" />
		virtual void GetFrames(wclBluetoothLeAdvertisementFrames& Frames) const override;
		
		/// <summary> Gets the advertisement raw data. </summary>
		/// <returns> The Bluetooth LE advertisement raw data. </returns>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		/// <summary> Gets the advertisement raw data. </summary>
		/// <value> The Bluetooth LE advertisement raw data. </value>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	/// <summary> The type represents a Bluetooth LE advertisements list, </summary>
	/// <seealso cref="CwclBluetoothLeAdvertisement" />
	typedef std::list<CwclBluetoothLeAdvertisement*>	WCL_BLE_ADV_LIST;

	/// <summary> The virtual connection class enables Bluetooth LE
	///   advertising feature. </summary>
	/// <remarks> <para> The class provides methods to enable Bluetooth LE
	///   advertising. </para>
	///   <para> The feature is supported only on Windows 10 platform with
	///   <c>Microsoft</c> Bluetooth drivers or on any Windows platform with
	///   <c>BLED112</c> Bluetooth dongle. </para> </remarks>
	/// <seealso cref="CwclCustomConnection" />
	class CwclBluetoothLeAdvertiserConnection : public CwclCustomConnection
	{
		DISABLE_COPY(CwclBluetoothLeAdvertiserConnection);
		
	private:
		WCL_BLE_ADV_LIST*	FAdvertisements;
		bool				FAdvertising;
		unsigned short		FInterval;
		CwclBluetoothRadio*	FRadio;

		/* Extended advertisement properties. */
		
		bool				FAnonymous;
		bool				FIncludeTxRssi;
		char				FPreferredTxRssi;
		bool				FUseExtendedAdvertisement;
		
		int CheckAdvertisements(const WCL_BLE_ADV_LIST* const Advertisements) const;

	protected:
		/* Internal methods. */

		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;

		/* Event routines. */
		
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();

		/* HAL methods. */

		/// <summary> Implements a hardware-dependent code to start Bluetooth LE
		///   advertising. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalStart() = 0;
		/// <summary> Implements a hardware-dependent code to stop Bluetooth LE
		///   advertising. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> A derived class must override this method to provide
		///   a driver-dependent code. </remarks>
		virtual int HalStop() = 0;

	public:
		/// <summary> Creates a new "virtual" Bluetooth LE Advertising connection
		///   object. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeAdvertiserConnection(CwclBluetoothRadio* const Radio);
		/// <summary> Frees the Bluetooth LE Advertiser. </summary>
		virtual ~CwclBluetoothLeAdvertiserConnection();

		/// <summary> Starts Bluetooth LE Advertising. </summary>
		/// <param name="Advertisements"> The Bluetooth LE Advertisements
		///   list. </param>
		/// <param name="Interval"> An advertising interval in 0.625 ms
		///   units. The value must be in range between 32 and 16384. </param>
		/// <param name="UseExtendedAdvertisement"> Specifies that the advertisement
		///   publisher should use the Extended Advertising format. </param>
		/// <param name="Anonymous"> Specifies whether or not the device address is
		///   included in the advertisement header. </param>
		/// <param name="IncludeTxRssi"> Specifies whether the transmit power level
		///   is included in the advertisement header. </param>
		/// <param name="PreferredTxRssi"> If specified, requests that the radio use
		///   the indicated transmit power level for the advertisement. The
		///   requested power level in dDm at range between -100 dBm and +20 for the
		///   radio transmission. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="WCL_BLE_ADV_LIST" />
		int Start(WCL_BLE_ADV_LIST* const Advertisements, const unsigned short Interval,
			const bool UseExtendedAdvertisement, const bool Anonymous,
			const bool IncludeTxRssi, const char PreferredTxRssi);
		/// <summary> Stops Bluetooth LE Advertising. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers only. </remarks>
		int Stop();

		/// <summary> Gets the Bluetooth LE advertisements list. </summary>
		/// <returns> The Bluetooth LE advertisements list. </returns>
		/// <seealso cref="WCL_BLE_ADV_LIST" />
		WCL_BLE_ADV_LIST* GetAdvertisements() const;
		/// <summary> Gets the Bluetooth LE advertisements list. </summary>
		/// <value> The Bluetooth LE advertisements list. </value>
		/// <seealso cref="WCL_BLE_ADV_LIST" />
		__declspec(property(get = GetAdvertisements)) WCL_BLE_ADV_LIST* Advertisements;

		/// <summary> Gets advertising state. </summary>
		/// <returns> <c>True</c> if advertising is running. </returns>
		bool GetAdvertising() const;
		/// <summary> Gets advertising state. </summary>
		/// <value> <c>True</c> if advertising is running. </value>
		__declspec(property(get = GetAdvertising)) bool Advertising;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the advertising interval. </summary>
		/// <returns> The advertising interval in 0.625ms units. </returns>
		unsigned short GetInterval() const;
		/// <summary> Gets the advertising interval. </summary>
		/// <value> The advertising interval in 0.625ms units. </value>
		__declspec(property(get = GetInterval)) unsigned short Interval;

		/// <summary> Gets if the device address is included in the advertisement
		///   header. </summary>
		/// <returns> Indicates whether the device address is hidden. </returns>
		bool GetAnonymous() const;
		/// <summary> Gets if the device address is included in the advertisement
		///   header. </summary>
		/// <value> Indicates whether the device address is hidden. </value>
		__declspec(property(get = GetAnonymous)) bool Anonymous;
		
		/// <summary> Gets if the transmit power level is included in the
		///   advertisement header. </summary>
		/// <returns> Indicates whether the transmit power level is included. </returns>
		bool GetIncludeTxRssi() const;
		/// <summary> Gets if the transmit power level is included in the
		///   advertisement header. </summary>
		/// <value> Indicates whether the transmit power level is included. </value>
		__declspec(property(get = GetIncludeTxRssi)) bool IncludeTxRssi;
		
		/// <summary> If specified, requests that the radio use the indicated
		///   transmit power level for the advertisement. </summary>
		/// <returns> The requested power level in dDm at range between -100
		///   dBm and +20 for the radio transmission. </returns>
		char GetPreferredTxRssi() const;
		/// <summary> If specified, requests that the radio use the indicated
		///   transmit power level for the advertisement. </summary>
		/// <value> The requested power level in dDm at range between -100
		///   dBm and +20 for the radio transmission. </value>
		__declspec(property(get = GetPreferredTxRssi)) char PreferredTxRssi;
		
		/// <summary> Specifies that the advertisement publisher should use the
		///   Extended Advertising format. </summary>
		/// <returns> Indicates whether or not the Extended Advertising format should
		///   be used. </returns>
		bool GetUseExtendedAdvertisement() const;
		/// <summary> Specifies that the advertisement publisher should use the
		///   Extended Advertising format. </summary>
		/// <value> Indicates whether or not the Extended Advertising format should
		///   be used. </value>
		__declspec(property(get = GetUseExtendedAdvertisement)) bool UseExtendedAdvertisement;

		/// <summary> The event fires when the Bluetooth LE advertising
		///   started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Bluetooth LE advertising
		///   stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The virtual connection represents a Wii Remote
	///   client. </summary>
	/// <remarks> <para> The class provides methods to receive data from
	///   the Wii Remote controller. </para>
	///   <para> An application must never create instances of this class
	///   directly. Instead of that an application must use related methods
	///   from the <see cref="CwclBluetoothRadio" /> object. </para>
	///   <para> The feature is supported only on Windows 10 platform with
	///   Microsoft Bluetooth drivers. </para> </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclClientConnection" />
	class CwclWiiRemoteClientConnection : public CwclClientConnection
	{
		DISABLE_COPY(CwclWiiRemoteClientConnection);
		
	private:
		// Remote device address.
		__int64				FAddress;
		// Initialization indication.
		bool				FInitialized;
		// The owner.
		CwclBluetoothRadio*	FRadio;
		
		/* Event objects. */
		
		HANDLE	FDisconnectEvent;
		HANDLE	FReadMemoryEvent;
		HANDLE	FWriteMemoryEvent;
		
		/* Read memory buffers. */
		
		unsigned char*	FReadBuffer;
		unsigned short	FReadOffset;
		unsigned short	FReadSize;
		
		/* Calibration data. */
		
		wclWiiRemoteAccelCalibration				FAccelCalibration;
		wclWiiRemoteBalanceBoardCalibration			FBalanceBoardCalibration;
		wclWiiRemoteClassicControllerCalibration	FClassicControllerCalibration;
		wclWiiRemoteNunchukCalibration				FNunchukCalibration;
		
		/* States. */
		
		// Indicates if accelerometer is enabled.
		bool						FAccelEnabled;
		wclWiiRemoteExtension		FExtension;
		wclWiiRemoteIrMode			FIrMode;
		wclWiiRemoteIrSensitivity	FIrSensitivity;
		wclWiiRemoteLeds			FLeds;
		bool						FRumble;
		
		/* Helper functions. */
		
		int CheckInitialized();
		wclWiiRemoteExtension DecodeExtensionType(const unsigned char* const Report) const;
		double GetBalanceBoardSensorValue(const unsigned short Sensor, const unsigned short Min,
			const unsigned short Mid, const unsigned short Max) const;
		unsigned char GetReportId(const bool Accel, const bool Ir, const bool Ext) const;
		unsigned char GetRumbleBit() const;
		int Wait(const HANDLE Event) const;
		
		/* Read functions. */
		
		int ReadCalibration();
		int ReadMemory(const unsigned long Address, const unsigned short Size,
			unsigned char*& Data);
		
		/* Write functions. */
		
		int WriteMemory(const unsigned long Address, const unsigned char Size, const unsigned char* const Data);
		int WriteMemory(const unsigned long Address, const unsigned char Data);
		int WriteReport(const unsigned char* const Report, const unsigned char Size);
		
		/* IR control functions. */
		
		int DisableIr();
		int EnableIr();
		int EnableIr(const wclWiiRemoteIrMode Mode, const wclWiiRemoteIrSensitivity Sensitivity);
		int SetIrLevel1();
		int SetIrLevel2();
		int SetIrLevel3();
		int SetIrLevel4();
		int SetIrLevel5();
		int SetIrLevelMax();
		
		/* Report control functions. */
		
		int SetReportType(const unsigned char ReportType, const bool Continuous);
		int SetReportType(unsigned char ReportType, const wclWiiRemoteIrSensitivity Sensitivity,
			const bool Continuous);
		
		/* Initialization functions. */
		
		int InitializeBalanceBoard();
		int InitializeClassicController();
		int InitializeMusicExtensions();
		int InitializeNunchuk();
		
		int InitializeExtension();
		
		/* Report parsers. */
		
		void ParseBalanceBoardExtension(const unsigned char* const Report, const unsigned char Offset) const;
		void ParseClassicControllerExtension(const unsigned char* Report, const unsigned char Offset) const;
		void ParseDrumsExtension(const unsigned char* const Report, const unsigned char Offset) const;
		void ParseGuitarExtension(const unsigned char* const Report, const unsigned char Offset) const;
		void ParseNunchukExtension(const unsigned char* const Report, const unsigned char Offset) const;
		
		void ParseExtensions(const unsigned char* const Report, const unsigned char Offset) const;
		
		void ParseAccel(const unsigned char* const Report) const;
		void ParseButtons(const unsigned char* const Report) const;
		void ParseIr(const unsigned char* const Report) const;
		void ParseReadMemory(const unsigned char* const Report);
		void ParseStatus(const unsigned char* const Report);
		
		void ParseInputReport(const unsigned char* const Report);
		
		/* Cleanup. */
		
		void ResetCalibrations();
		void ResetExtensionCalibration();
		void ResetStates();
		
	protected:
		/// <summary> The function parses the received report. </summary>
		/// <param name="Report"> A pointer to the report data. </param>
		/// <remarks> The method must be called from the communication thread
		///   to process received reports. </remarks>
		void ProcessReport(const unsigned char* const Report);
		
		/// <summary> The method called when a new notification message
		///   received. </summary>
		/// <param name="Message"> A <see cref="CwclMessage" /> object
		///   represents a notification message. </param>
		/// <remarks> <para> This method is for internal use only. </para>
		///   <para> If a derived class overrides this method it must always call
		///   the inherited implementation first. </para> </remarks>
		/// <seealso cref="CwclMessage" />
		virtual void MessageReceived(const CwclMessage* const Message) override;
		
		/// <summary> Implements a hardware-dependent code that connects to a
		///   remote device. </summary>
		/// <param name="Event"> The system even object handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Derived classes must override this method to implement
		///   a hardware-dependent code that connects to a remote device. </para>
		///   <para> The method executes in a separate thread. </para>
		///   <para> The method implementation must monitor the <c>Event</c>
		///   parameter. The <c>Event</c> parameter is set if the
		///   <c>Disconnect</c> method was called. If the termination event was set
		///   the method must terminate connection operation. </para>
		///   <para> If connection to a remote device was terminated the method
		///   must release all allocated resources because the <c>HalDisconnect</c>
		///   will not be called. </para>
		///   <para> A derived class must always call inherited
		///   method. </para> </remarks>
		virtual int HalConnect(const HANDLE Event) override;
		/// <summary> Implements a hardware-dependent code that disconnects from the
		///   connected remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method is called only if a connection to a remote
		///   device was established with success (the <c>Connect</c> method was
		///   success). </para>
		///   <para> The method will not be called if the connection to the  remote
		///   device was terminated in the middle of the <c>HalConnect</c>
		///   method. </para>
		///   <para> A derived HalConnect implementation <c>must</c> always call
		///   the <c>HalConnect</c> method first, before any other connection
		///   operation. If the connection is failed the derived implementation
		///   <c>must</c> always call inherited <c>HalDisconnect</c> method. </para>
		///   <para> A derived class must always call inherited
		///   method. </para> </remarks>
		virtual int HalDisconnect() override;
		/// <summary> Implements a hardware-dependent code that writes data report
		///   to the connected Wii Remote controller. </summary>
		/// <param name="Report"> The pointer to the report data buffer. </param>
		/// <param name="Size"> The report data size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> A derived class must override this method to implement
		///   a hardware-dependent code that sends data to the connected device.
		///   The method executes in the main thread and must be
		///   synchronous. </para>
		///   <para> A derived implementation must always call this method in case
		///   of the derived <c>HalConnect</c> failed. </para> </remarks>
		virtual int HalWrite(const unsigned char* const Report, const unsigned char Size) = 0;
		
		/// <summary> Fire the <c>OnAccelChanged</c> event. </summary>
		/// <param name="Accel"> The current accelerometer data. </param>
		/// <seealso cref="wclWiiRemoteAccel" />
		virtual void DoAccelChanged(const wclWiiRemoteAccel& Accel);
		/// <summary> Fires the <c>OnBalanceBoardChanged</c> event </summary>
		/// <param name="Board"> The new Balance Board extension
		///   state. </param>
		/// <seealso cref="wclWiiRemoteBalanceBoard" />
		virtual void DoBalanceBoardChanged(const wclWiiRemoteBalanceBoard& Board);
		/// <summary> Fires the <c>OnButtonsChanged</c> event. </summary>
		/// <param name="Buttons"> The new buttons state. </param>
		/// <seealso cref="wclWiiRemoteButtons" />
		virtual void DoButtonsChanged(const wclWiiRemoteButtons& Buttons);
		/// <summary> Fires the <c>OnClassicControllerChanged</c> event. </summary>
		/// <param name="Controller"> The current state of the Wii Remote Classic
		///   Controller extension. </param>
		/// <seealso cref="wclWiiRemoteClassicController" />
		virtual void DoClassicControllerChanged(const wclWiiRemoteClassicController& Controller);
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		virtual void DoDisconnect(const int Reason);
		/// <summary> Fires the <c>OnDrumsChanged</c> event. </summary>
		/// <param name="Drums"> The current state of the Drums extension. </param>
		/// <seealso cref="wclWiiRemoteDrums" />
		virtual void DoDrumsChanged(const wclWiiRemoteDrums& Drums);
		/// <summary> Fires the <c>OnExtensionAttached</c> event. </summary>
		virtual void DoExtensionAttached();
		/// <summary> Fires the <c>OnExtensionDetached</c> event. </summary>
		virtual void DoExtensionDetached();
		/// <summary> Fires the <c>OnGuitarChanged</c> event. </summary>
		/// <param name="Guitar"> The current Guitar extension state. </param>
		/// <seealso cref="wclWiiRemoteGuitar" />
		virtual void DoGuitarChanged(const wclWiiRemoteGuitar& Guitar);
		/// <summary> Fires the <c>OnIrChanged</c> event. </summary>
		/// <param name="Ir"> The IR sensor data. </param>
		/// <seealso cref="wclWiiRemoteIrSensors" />
		virtual void DoIrChanged(const wclWiiRemoteIrSensors& Ir);
		/// <summary> Fires the <c>OnNunchukChanged</c> event. </summary>
		/// <param name="Nunchuk"> The current Nunchuk extension state. </param>
		/// <seealso cref="wclWiiRemoteNunchuk" />
		virtual void DoNunchukChanged(const wclWiiRemoteNunchuk& Nunchuk);
		/// <summary> Fires the <c>OnStatusChanged</c> event. </summary>
		/// <param name="Batt"> The WeDo Remote battery level. </param>
		/// <param name="Leds"> The We Do Remote LEDs state. </param>
		/// <seealso cref="wclWiiRemoteLeds" />
		virtual void DoStatusChanged(const double Batt, const wclWiiRemoteLeds& Leds);
		
		/// <summary> Gets the disconnect event object. </summary>
		/// <returns> The disconnect event object. </returns>
		HANDLE GetDisconnectEvent() const;
		/// <summary> Gets the disconnect event object. </summary>
		/// <value> The disconnect event object. </value>
		__declspec(property(get = GetDisconnectEvent)) HANDLE DisconnectEvent;
		
	public:
		/// <summary> Create new Wii Remote client connection. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclWiiRemoteClientConnection(CwclBluetoothRadio* const Radio);
		
		/// <summary> Connects to a remote device. </summary>
		/// <param name="Address"> The remote Bluetooth device address. </param>
		/// <param name="Timeout"> The connect timeout in milliseconds. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> The method starts a connection operation to a remote
		///   device. If the method success that does not mean that the connection
		///   was established. That just means that the connection operation was
		///   started. The real connection result will be passed to the
		///   <c>OnConnect</c> event handler. </para>
		///   <para> NOTE: BlueSoleil does not support <c>Authentication</c>
		///   and <c>Encryption</c> parameters per connection. </para> </remarks>
		int Connect(const __int64 Address, const unsigned long Timeout);
		
		/// <summary> Requests the Wii Remote status. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This is asynchronous method. When operation completes the
		///   <c>OnStatusChanged</c> event fires. </remarks>
		int GetStatus();
		
		/// <summary> Changes the Wii Remote LEDs state. </summary>
		/// <param name="Leds"> The new LEDs state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiiRemoteLeds" />
		int SetLeds(const wclWiiRemoteLeds& Leds);
		/// <summary> Changes the Wii Remote LEDs state. </summary>
		/// <param name="Led1"> The new LED 1 state. </param>
		/// <param name="Led2"> The new LED 2 state. </param>
		/// <param name="Led3"> The new LED 3 state. </param>
		/// <param name="Led4"> The new LED 4 state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetLeds(const bool Led1, const bool Led2, const bool Led3, const bool Led4);
		/// <summary> Turns the Rumble On and Off. </summary>
		/// <param name="TurnOn"> Set to <c>True</c> to turn the Rumble On. Set
		///   to <c>False</c> to turn the Rumble Off. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetRumble(const bool TurnOn);
		
		/// <summary> Enables accelerometer. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnableAccel();
		/// <summary> Disables accelerometer. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DisableAccel();
		
		/// <summary> Sets IR IR sensor sensitivity (and turns it ON or
		///   OFF). </summary>
		/// <param name="Sensitivity"> The IR sensor sensitivity. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		int SetIrSensitivity(const wclWiiRemoteIrSensitivity Sensitivity);
		
		/// <summary> Gets a remote device MAC address. </summary>
		/// <returns> The remote device MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Gets a remote device MAC address. </summary>
		/// <value> The remote device MAC address. </value>
		__declspec(property(get = GetAddress)) __int64 Address;

		/// <summary> Gets the current accelerometer status. </summary>
		/// <returns> <c>True</c> if the accelerometer is enabled. <c>False</c>
		///   otherwise. </returns>
		bool GetAccelEnabled() const;
		/// <summary> Gets the current accelerometer status. </summary>
		/// <value> <c>True</c> if the accelerometer is enabled. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetAccelEnabled)) bool AccelEnabled;

		/// <summary> Gets the current connected extension type. </summary>
		/// <returns> The currently connected extension. </returns>
		/// <seealso cref="wclWiiRemoteExtension " />
		wclWiiRemoteExtension GetExtension() const;
		/// <summary> Gets the current connected extension type. </summary>
		/// <value> The currently connected extension. </value>
		/// <seealso cref="wclWiiRemoteExtension " />
		__declspec(property(get = GetExtension)) wclWiiRemoteExtension Extension;

		/// <summary> Gets the current IR sensor mode. </summary>
		/// <returns> The IR sensor mode. </returns>
		/// <seealso cref="wclWiiRemoteIrMode" />
		wclWiiRemoteIrMode GetIrMode() const;
		/// <summary> Gets the current IR sensor mode. </summary>
		/// <value> The IR sensor mode. </value>
		/// <seealso cref="wclWiiRemoteIrMode" />
		__declspec(property(get = GetIrMode)) wclWiiRemoteIrMode IrMode;

		/// <summary> Gets the current IR sensor sensitivity. </summary>
		/// <returns> The IR sensor sensitivity. </returns>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		wclWiiRemoteIrSensitivity GetIrSensitivity() const;
		/// <summary> Gets the current IR sensor sensitivity. </summary>
		/// <value> The IR sensor sensitivity. </value>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		__declspec(property(get = GetIrSensitivity)) wclWiiRemoteIrSensitivity IrSensitivity;

		/// <summary> Gets the current LEDs state. </summary>
		/// <returns> The LEDs state. </returns>
		/// <seealso cref="wclWiiRemoteLeds " />
		wclWiiRemoteLeds GetLeds() const;
		/// <summary> Gets the current LEDs state. </summary>
		/// <value> The LEDs state. </value>
		/// <seealso cref="wclWiiRemoteLeds " />
		__declspec(property(get = GetLeds)) wclWiiRemoteLeds Leds;

		/// <summary> Gets the connection owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the current Rumble status. </summary>
		/// <returns> <c>True</c> if the Rumble is turned ON. </returns>
		bool GetRumble() const;
		/// <summary> Gets the current Rumble status. </summary>
		/// <value> <c>True</c> if the Rumble is turned ON. </value>
		__declspec(property(get = GetRumble)) bool Rumble;

		/// <summary> The event fires when the accelerometer state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Accel"> The current accelerometer data. </param>
		/// <seealso cref="wclWiiRemoteAccel" />
		wclWiiRemoteAccelChangedEvent(OnAccelChanged);
		/// <summary> The event fires when the stat eof the Balance Board extension
		///   has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Board"> The new Balance Board extension
		///   state. </param>
		/// <seealso cref="wclWiiRemoteBalanceBoard" />
		wclWiiRemoteBalanceBoardChangedEvent(OnBalanceBoardChanged);
		/// <summary> The event fires when the buttons state of the Wii Remote
		///   controller has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Buttons"> The current state of the Wii Remote controller
		///   buttons. </param>
		/// <seealso cref="wclWiiRemoteButtons" />
		wclWiiRemoteButtonsChangedEvent(OnButtonsChanged);
		/// <summary> The event fires when a Classic Controller extension state has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Controller"> The current state of the Wii Remote Classic
		///   Controller extension. </param>
		/// <seealso cref="wclWiiRemoteClassicController" />
		wclWiiRemoteClassicControllerChangedEvent(OnClassicControllerChanged);
		/// <summary> The event fires when the Drums extension state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Drums"> The current state of the Drums extension. </param>
		/// <seealso cref="wclWiiRemoteDrums" />
		wclWiiRemoteDrumsChangedEvent(OnDrumsChanged);
		/// <summary> The event fires when the extension is attached. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnExtensionAttached);
		/// <summary> The event fires when the extension has been
		///   detached. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnExtensionDetached);
		/// <summary> The event fires when the Guitar extension state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Guitar"> The current Guitar extension state. </param>
		/// <seealso cref="wclWiiRemoteGuitar" />
		wclWiiRemoteGuitarChangedEvent(OnGuitarChanged);
		/// <summary> The event fires when the IR sensor data has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Ir"> The IR sensor data. </param>
		/// <seealso cref="wclWiiRemoteIrSensors" />
		wclWiiRemoteIrChangedEvent(OnIrChanged);
		/// <summary> The event fires when the state of the Nunchuk extension has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Nunchuk"> The current Nunchuk extension state. </param>
		/// <seealso cref="wclWiiRemoteNunchuk" />
		wclWiiRemoteNunchukChangedEvent(OnNunchukChanged);
		/// <summary> The event fires when the WeDo Remote status
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Batt"> The WeDo Remote battery level. </param>
		/// <param name="Leds"> The We Do Remote LEDs state. </param>
		/// <seealso cref="wclWiiRemoteLeds" />
		wclWiiRemoteStatusChangedEvent(OnStatusChanged);
	};

	/// <summary> The virtual connection represents a Wii Remote HID
	///   client. </summary>
	/// <remarks> <para> The class provides methods to receive data from
	///   the Wii Remote controller. </para>
	///   <para> An application must never create instances of this class
	///   directly. Instead of that an application must use related methods
	///   from the <see cref="CwclBluetoothRadio" /> object. </para>
	///   <para> The feature is supported only on Windows 10 platform with
	///   Microsoft Bluetooth drivers. </para> </remarks>
	/// <seealso cref="CwclBluetoothRadio" />
	/// <seealso cref="CwclWiiRemoteClientConnection" />
	class CwclWiiRemoteHidClientConnection : public CwclWiiRemoteClientConnection
	{
		DISABLE_COPY(CwclWiiRemoteHidClientConnection);
		
	private:
		typedef std::list<tstring> WIIS;

		// HID device handle.
		HANDLE	FHandle;
		// Overlapped communication (read) event.
		HANDLE	FReadEvent;
		// Overlapped write event.
		HANDLE	FWriteEvent;
		// True of Wii Remote was paired by user.
		bool	FWasInstalled;
		
		// Enumerates installed (paired) Wii Remote devices.
		int EnumWiis(WIIS& Wiis);
		// Return device path for the Wii Remote with given MAC.
		int GetPath(tstring& Path);
		// Install Wii Remote device as HID one.
		int InstallDevice(const HANDLE Event, tstring& Path);
		// Removed Wii Remote device.
		int UninstallDevice();
		// Wait for timeout or disconnect.
		int CheckTimeout(const HANDLE Event, const DWORD Ticks);
		
		void TerminateIo(OVERLAPPED& Over);
		
		// Clears HID function pointers.
		void ClearHid();
		// Loads HID API.
		int LoadHid();
		// Unloads HID API.
		int UnloadHid();
		
	protected:
		/// <summary> Connects to the Wii Remote as to HID device. </summary>
		/// <param name="Event"> The system even object handle. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int HalConnect(const HANDLE Event) override;
		/// <summary> Communicates with the Wii Remote as with HID
		///   device. </summary>
		/// <param name="Event"> The system even object handle (disconnect
		///   event). </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int HalCommunicate(const HANDLE Event) override;
		/// <summary> Disconnects from the Wii Remote as from HID device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int HalDisconnect() override;
		/// <summary> Sends data to the Wii Remote as to HID device. </summary>
		/// <param name="Report"> The pointer to the report data buffer. </param>
		/// <param name="Size"> The report data size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		virtual int HalWrite(const unsigned char* const Report, const unsigned char Size) override;
		
	public:
		/// <summary> Create new Wii Remote HID client connection. </summary>
		/// <param name="Radio"> The Radio object that owns the connection. </param>\
		/// <remarks> An application must never create this class directly.
		///   Instead of that an application must use upper-level methods and
		///   classes. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclWiiRemoteHidClientConnection(CwclBluetoothRadio* const Radio);
	};

	/* Components */

	/// <summary> The base class for all Bluetooth Components. </summary>
	/// <remarks> The class implements the basic methods to prevent the
	///   Bluetooth Connections from self-destruction. </remarks>
	class CwclBluetoothComponent
	{
		DISABLE_COPY(CwclBluetoothComponent);

	private:
		CwclCustomConnection*	FCopy;
		RTL_CRITICAL_SECTION	FCS;

		void UnhookEvents();
		void DeleteCopy();
		
	protected:
		/// <summary> The method sets new copy of the current connection. </summary>
		/// <param name="NewConnection"> The current connection used in Bluetooth
		///   communication. </param>
		/// <seealso cref="CwclCustomConnection" />
		void SetCopy(CwclCustomConnection* const NewConnection);
		
		/// <summary> Enters the Bluetooth component protection critical
		///   section. </summary>
		void Enter() const;
		/// <summary> Leaves the Bluetooth component protection critical
		///   section. </summary>
		void Leave() const;
		
	public:
		/// <summary> Creates a new component. </summary>
		CwclBluetoothComponent();
		/// <summary> Frees the component. </summary>
		virtual ~CwclBluetoothComponent();
	};

	/// <summary> The Bluetooth RFCOMM Client component. </summary>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclRfCommClient : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclRfCommClient);

	private:
		__int64			FAddress;
		bool			FAuthentication;
		unsigned char	FChannel;
		bool			FEncryption;
		GUID			FService;
		unsigned long	FTimeout;

		bool							FActive;
		CwclRfCommClientConnection*		FClient;

		void ClientConnect(void* Sender, const int Error);
		void ClientData(void* Sender, const void* const Data, const unsigned long Size);
		void ClientDisconnect(void* Sender, const int Reason);

	protected:
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires the <c>OnCreateProcessor</c> event. </summary>
		/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
		///   object that requires a data processor. </param>
		/// <seealso cref="CwclClientDataConnection" />
		virtual void DoCreateProcessor(CwclClientDataConnection* const Connection);
		/// <summary> Fires the <c>OnData</c> event. </summary>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		virtual void DoData(const void* const Data, const unsigned long Size);
		/// <summary> Fires the <c>OnDestroyProcessor</c> event. </summary>
		/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
		///   object that requires a data processor. </param>
		/// <seealso cref="CwclClientDataConnection" />
		virtual void DoDestroyProcessor(CwclClientDataConnection* const Connection);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		virtual void DoDisconnect(const int Reason);

	public:
		/// <summary> Creates new RFCOMM client component. </summary>
		CwclRfCommClient();
		/// <summary> Frees the component. </summary>
		virtual ~CwclRfCommClient();

		/// <summary> Starts connecting to a remote Bluetooth device. </summary>
		/// <param name="Radio"> The <see cref="CwclBluetoothRadio" /> object
		///   that handles the connection. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int Connect(CwclBluetoothRadio* const Radio);
		/// <summary> Disconnects from the connection remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();

		/// <summary> Reads the read buffer size. </summary>
		/// <param name="Size"> On output he read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetReadBufferSize(unsigned long& Size);
		/// <summary> Reads the write buffer size. </summary>
		/// <param name="Size"> On output the write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetWriteBufferSize(unsigned long& Size);

		/// <summary> Sets the read buffer size. </summary>
		/// <param name="Size"> The new read buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetReadBufferSize(const unsigned long Size);
		/// <summary> Sets the write buffer size. </summary>
		/// <param name="Size"> The new write buffer size in bytes. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetWriteBufferSize(const unsigned long Size);

		/// <summary> Sends data to the connected device. </summary>
		/// <param name="Data"> The pointer to the data buffer that should be sent
		///   to the connected device. </param>
		/// <param name="Size"> The data buffer size. </param>
		/// <param name="Written"> The amount of bytes actually written to the
		///   device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The write is synchronous operation. </remarks>
		int Write(const void* const Data, const unsigned long Size, unsigned long& Written);

		/// <summary> Gets the Data Processor created for the connection. </summary>
		/// <returns> The <see cref="CwclCustomClientDataProcessor" />
		///   object. </returns>
		/// <seealso cref="CwclCustomClientDataProcessor" />
		CwclCustomClientDataProcessor* GetProcessor() const;
		/// <summary> Gets the Data Processor created for the connection. </summary>
		/// <value> The <see cref="CwclCustomClientDataProcessor" />
		///   object. </value>
		/// <seealso cref="CwclCustomClientDataProcessor" />
		__declspec(property(get = GetProcessor)) CwclCustomClientDataProcessor* Processor;

		/// <summary> Gets the radio object used for connection. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the radio object used for connection. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the service's UUID that should be used
		///   for connection. </summary>
		/// <returns> The Bluetooth service's UUID. </returns>
		GUID GetService() const;
		/// <summary> Sets the service's UUID that should be used
		///   for connection. </summary>
		/// <param name="Value"> The Bluetooth service's UUID. </param>
		/// <remarks> If an application changes the property when connection is
		///   active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		void SetService(const GUID& Value);
		/// <summary> Gets and sets the service's UUID that should be used
		///   for connection. </summary>
		/// <value> The Bluetooth service's UUID. </value>
		/// <remarks> If an application changes the property when connection is
		///   active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		__declspec(property(get = GetService, put = SetService)) GUID Service;

		/// <summary> Gets the current client state. </summary>
		/// <returns> The client state. </returns>
		/// <seealso cref="wclClientState" />
		wclClientState GetState() const;
		/// <summary> Gets the current client state. </summary>
		/// <value> The client state. </value>
		/// <seealso cref="wclClientState" />
		__declspec(property(get = GetState)) wclClientState State;

		/// <summary> Gets a target Bluetooth device's MAC
		///   address. </summary>
		/// <returns> The Bluetooth MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Sets a target Bluetooth device's MAC
		///   address. </summary>
		/// <param name="Value"> The Bluetooth MAC address. </param>
		/// <remarks> If an application changes the property when connection is
		///   active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		void SetAddress(const __int64 Value);
		/// <summary> Gets and sets a target Bluetooth device's MAC
		///   address. </summary>
		/// <value> The Bluetooth MAC address. </value>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		__declspec(property(get = GetAddress, put = SetAddress)) __int64 Address;

		/// <summary> Gets the authentication property for the
		///   connection. </summary>
		/// <returns> <c>True</c> if the authentication is enabled. </returns>
		bool GetAuthentication() const;
		/// <summary> Sets the authentication property for the
		///   connection. </summary>
		/// <param name="Value"> <c>True</c> if the authentication is enabled. </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		void SetAuthentication(const bool Value);
		/// <summary> Gets and sets the authentication property for the
		///   connection. </summary>
		/// <value> <c>True</c> if the authentication is enabled. </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		__declspec(property(get = GetAuthentication, put = SetAuthentication))
			bool Authentication;

		/// <summary> Gets the RFCOMM channel number used for
		///   connection. </summary>
		/// <returns> The RF COMM channel number. The value must be between 0 and 33
		///   (including 0 and 32). </returns>
		unsigned char GetChannel() const;
		/// <summary> Sets the RFCOMM channel number used for
		///   connection. </summary>
		/// <param name="Value"> The RF COMM channel number. The value must be between 0 and 33
		///   (including 0 and 32). </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> If the <c>Channel</c> value is 0 a Bluetooth driver try to
		///   resolve required channel number by querying a target devices SDP
		///   using the service's UUID. In this case it will use the first found
		///   service that matches the UUID. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetChannel(const unsigned char Value);
		/// <summary> Gets and sets the RFCOMM channel number used for
		///   connection. </summary>
		/// <value> The RF COMM channel number. The value must be between 0 and 33
		///   (including 0 and 32). </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> If the <c>Channel</c> value is 0 a Bluetooth driver try to
		///   resolve required channel number by querying a target devices SDP
		///   using the service's UUID. In this case it will use the first found
		///   service that matches the UUID. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetChannel, put = SetChannel)) unsigned char Channel;

		/// <summary> Gets the Encryption property for the
		///   connection. </summary>
		/// <returns> <c>True</c> if Encryption is enabled for the
		///   connection. </returns>
		bool GetEncryption() const;
		/// <summary> Sets the Encryption property for the connection. </summary>
		/// <param name="Value"> <c>True</c> if Encryption is enabled for the
		///   connection. </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> The Encryption can be turned on (<c>True</c>) only if
		///   the <c>Authentication</c> property is also set to
		///   <c>True</c>. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetEncryption(const bool Value);
		/// <summary> Gets and sets the Encryption property for the
		///   connection. </summary>
		/// <value> <c>True</c> if Encryption is enabled for the
		///   connection. </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </para>
		///   <para> The Encryption can be turned on (<c>True</c>) only if
		///   the <c>Authentication</c> property is also set to
		///   <c>True</c>. </para> </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetEncryption, put = SetEncryption)) bool Encryption;

		/// <summary> Gets the connect timeout value. </summary>
		/// <returns> The connect timeout value in milliseconds. </returns>
		unsigned long GetTimeout() const;
		/// <summary> Sets the connect timeout value. </summary>
		/// <param name="Value"> The connect timeout value in milliseconds. </param>
		/// <remarks> If an application changes the property when client is
		///   connected the <see cref="wclEClientActive" /> exception
		///   raises. If new value of the <c>Timeout</c> is <c>0</c> the
		///   <see cref="wclEInvalidArgument" /> exception raises. </remarks>
		/// <exception cref="wclEClientActive"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetTimeout(const unsigned long Value);
		/// <summary> Gets and sets the connect timeout value. </summary>
		/// <value> The connect timeout value in milliseconds. </value>
		/// <remarks> If an application changes the property when client is
		///   connected the <see cref="wclEClientActive" /> exception
		///   raises. If new value of the <c>Timeout</c> is <c>0</c> the
		///   <see cref="wclEInvalidArgument" /> exception raises. </remarks>
		/// <exception cref="wclEClientActive"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetTimeout, put = SetTimeout)) unsigned long Timeout;

		/// <summary> The event fires when a connection to a remote device
		///   has been completed (with or without success). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <remarks> If the <c>Error</c> parameter of the event is not
		///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
		///   method again from inside the event handler. </remarks>
		wclClientConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when connection to a remote device has
		///   been established with success to allow application provide a
		///   data processor for the connection. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
		///   object that requires a Data Processor. </param>
		/// <remarks> If an application needs an additional data processing it
		///   can use Data Processors. An application must create a Data Processor
		///   inside this event handler. If a Data Processor created for the
		///   connection the <c>OnData</c> event will NOT fire. </remarks>
		/// <seealso cref="CwclClientDataConnection" />
		/// <seealso cref="CwclCustomClientDataProcessor" />
		wclClientConnectionProcessorEvent(OnCreateProcessor);
		/// <summary> The event fires when new data is received from the
		///   connected remote device. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		wclConnectionDataEvent(OnData);
		/// <summary> The event fires when connection to a remote device has
		///   been terminated. An application must destroy the Data Processor
		///   created for the connection. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
		///   object that requires a Data Processor. </param>
		/// <seealso cref="CwclClientDataConnection" />
		/// <seealso cref="CwclCustomClientDataProcessor" />
		wclClientConnectionProcessorEvent(OnDestroyProcessor);
		/// <summary> The event fires when the remote connected device has been
		///   disconnected. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnDisconnect);
	};

	/// <summary> Bluetooth RFCOMM server. </summary>
	/// <remarks> The <c>TwclRfCommClient</c> component enables an
	///   application to accept connections from Bluetooth devices through RFCOMM
	///   protocol and work with RFCOMM based profiles (SPP, OBEX,
	///   others). </remarks>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclRfCommServer : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclRfCommServer);

	private:
		bool			FAuthentication;
		unsigned char	FChannel;
		bool			FEncryption;
		GUID			FService;
		tstring			FServiceName;

		bool						FActive;
		CwclRfCommServerConnection*	FServer;
	    
		void ServerClosed(void* Sender, const int Reason);
		void ServerConnect(void* Sender, CwclServerClientConnection* const Client, const int Error);
		void ServerData(void* Sender, CwclServerClientDataConnection* const Client, const void* const Data,
			const unsigned long Size);
		void ServerDisconnect(void* Sender, CwclServerClientConnection* const Client, const int Reason);
		void ServerListen(void* Sender);
			void ServerGetSdpAttributes(void* Sender, wclBluetoothSdpProtocols& Protocols,
			wclBluetoothSdpProfiles& Profiles, wclBluetoothSdpFormats& Formats, unsigned long& Cod);

	protected:
		/// <summary> Fires the <c>OnClosed</c> event. </summary>
		/// <param name="Reason"> Indicates closing reason. </param>
		virtual void DoClosed(const int Reason);
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		virtual void DoConnect(CwclRfCommServerClientConnection* const Client, const int Error);
		/// <summary> Fires the <c>OnCreateProcessor</c> event. </summary>
		/// <param name="Connection"> The
		///   <see cref="CwclServerClientDataConnection" /> object that requires a
		///   data processor. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		virtual void DoCreateProcessor(CwclServerClientDataConnection* const Connection);
		/// <summary> Fires the <c>OnData</c> event. </summary>
		/// <param name="Client"> A
		///   <see cref="CwclRfCommServerClientConnection" /> object
		///   represents a remote client connection. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		virtual void DoData(CwclRfCommServerClientConnection* const Client, const void* const Data,
			const unsigned long Size);
		/// <summary> Fires the <c>OnDestroyProcessor</c> event. </summary>
		/// <param name="Connection"> The
		///   <see cref="CwclServerClientDataConnection" /> object that requires a
		///   data processor. </param>
		/// <seealso cref="CwclServerClientDataConnection" />
		virtual void DoDestroyProcessor(CwclServerClientDataConnection* const Connection);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Client"> The
		///   <see cref="CwclServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		virtual void DoDisconnect(CwclRfCommServerClientConnection* const Client, const int Reason);
		/// <summary> Fires the <c>OnListen</c> event. </summary>
		virtual void DoListen();
		/// <summary> Fires the <c>GetSdpAttributes</c> event. </summary>
		/// <param name="Protocols"> The additional protocol descriptors array that
		///   should be added to SDP record. </param>
		/// <param name="Profiles"> The profile list that should be added to SDP
		///   record. </param>
		/// <param name="Formats"> Other attributes that should be added to SDP
		///   record. </param>
		/// <param name="Cod"> <para> Class of device (COD) information. A 32-bit
		///   parameter of COD_SERVICE_* class of device bits associated with this
		///   SDP record. The system combines these bits with COD bits from other
		///   service records and system characteristics. The resulting class of
		///   device for the local radio is advertised when the radio is found during
		///   device inquiry. When the last SDP record associated with a particular
		///   service bit is deleted, that service bit is no longer reported in
		///   responses to future device inquiries. </para>
		///   <para> The format and possible values for the COD field are defined in
		///   the Bluetooth Assigned Numbers 1.1 portion of the Bluetooth
		///   specification, Section 1.2. (This resource may not be available in some
		///   languages and countries.) </para> </param>
		/// <remarks> <para> The HAL Radio implementation calls this method when
		///   needs to add custom attributes into the SDP record. </para>
		///   <para> BlueSoleil driver does not support custom SDP records and this
		///   method does not work with BlueSoleil Bluetooth driver. </para>
		///   <para> A derived class must always call the inherited
		///   method.  </para> </remarks>
		/// <seealso cref="wclBluetoothSdpProtocols" />
		/// <seealso cref="wclBluetoothSdpProfiles" />
		/// <seealso cref="wclBluetoothSdpFormats" />
		virtual void DoGetSdpAttributes(wclBluetoothSdpProtocols& Protocols, wclBluetoothSdpProfiles& Profiles,
			wclBluetoothSdpFormats& Formats, unsigned long& Cod);

	public:
		/// <summary> Creates a new component. </summary>
		CwclRfCommServer();
		/// <summary> Frees the component. </summary>
		virtual ~CwclRfCommServer();

		/// <summary> Closes the server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> The method starts listening for client connections. </summary>
		/// <param name="Radio"> The Bluetooth Radio that should handle the
		///   connection. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio"/>
		int Listen(CwclBluetoothRadio* const Radio);

		/// <summary> Gets the RFCOMM assigned channel number. </summary>
		/// <returns> The RFCOMM assigned channel number. </returns>
		unsigned char GetAssignedChannel() const;
		/// <summary> Gets the RFCOMM assigned channel number. </summary>
		/// <value> The RFCOMM assigned channel number. </value>
		__declspec(property(get = GetAssignedChannel)) unsigned char AssignedChannel;

		/// <summary> Gets the number of the connected clients. </summary>
		/// <returns> The number of the connected clients. </returns>
		size_t GetCount() const;
		/// <summary> Gets the number of the connected clients. </summary>
		/// <value> The number of the connected clients. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets the connected client by its index. </summary>
		/// <returns> The <see cref="CwclRfCommServerClientConnection" /> represents
		///   the connected client. </returns>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		CwclRfCommServerClientConnection* GetClients(const size_t Index) const;
		/// <summary> Gets the connected client by its index. </summary>
		/// <value> The <see cref="CwclRfCommServerClientConnection" /> represents
		///   the connected client. </value>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		__declspec(property(get = GetClients)) CwclRfCommServerClientConnection* Clients[];

		/// <summary> Gets the connection radio object. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object that handles
		///   the connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the connection radio object. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object that handles
		///   the connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;
	    
		/// <summary> Gets the Bluetooth service UUID used for
		///   connection. </summary>
		/// <returns> A Bluetooth service UUID. </returns>
		GUID GetService() const;
		/// <summary> Sets the Bluetooth service UUID used for
		///   connection. </summary>
		/// <param name="Value"> A Bluetooth service UUID. </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		void SetService(const GUID& Value);
		/// <summary> Gets and sets the Bluetooth service UUID used for
		///   connection. </summary>
		/// <value> A Bluetooth service UUID. </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		__declspec(property(get = GetService, put = SetService)) GUID Service;

		/// <summary> Gets the current connection state. </summary>
		/// <returns> The client connection state. </returns>
		/// <seealso cref="wclServerState" />
		wclServerState GetState() const;
		/// <summary> Gets the current connection state. </summary>
		/// <value> The client connection state. </value>
		/// <seealso cref="wclServerState" />
		__declspec(property(get = GetState)) wclServerState State;

		/// <summary> Gets the authentication value. </summary>
		/// <returns> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </returns>
		bool GetAuthentication() const;
		/// <summary> Sets the authentication value. </summary>
		/// <param name="Value"> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		void SetAuthentication(const bool Value);
		/// <summary> Gets and sets the authentication value. </summary>
		/// <value> <c>True</c> if the connection required authentication.
		///   <c>False</c> otherwise. </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> If the Authentication if switched off (<c>False</c>) the
		///   <c>Encryption</c> is also switched off. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		__declspec(property(get = GetAuthentication, put = SetAuthentication))
			bool Authentication;

		/// <summary> Gets the service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <returns> The RFCOMM channel number used for connection. </returns>
		unsigned char GetChannel() const;
		/// <summary> Sets the service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <param name="Value"> The RFCOMM channel number used for connection. </param>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetChannel(const unsigned char Value);
		/// <summary> Gets and sets the service RFCOMM channel number. <c>0</c> to
		///   auto detection. </summary>
		/// <value> The RFCOMM channel number used for connection. </value>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetChannel, put = SetChannel)) unsigned char Channel;

		/// <summary> Gets the encryption state of the connection. </summary>
		/// <returns> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </returns>
		bool GetEncryption() const;
		/// <summary> Sets the encryption state of the connection. </summary>
		/// <param name="Value"> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </param>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> The Encryption can be turned on (<c>True</c>) only if
		///   the <c>Authentication</c> property is also set to
		///   <c>True</c>. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetEncryption(const bool Value);
		/// <summary> Gets and sets the encryption state of the
		///   connection. </summary>
		/// <value> <c>True</c> if the connection is encrypted. <c>False</c>
		///   otherwise. </value>
		/// <remarks> <para> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </para>
		///   <para> The Encryption can be turned on (<c>True</c>) only if
		///   the <c>Authentication</c> property is also set to
		///   <c>True</c>. </para> </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetEncryption, put = SetEncryption)) bool Encryption;

		/// <summary> Gets the service name. </summary>
		/// <returns> The service name. </returns>
		tstring GetServiceName() const;
		/// <summary> Sets the service name. </summary>
		/// <param name="Value"> The service name. </param>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		void SetServiceName(const tstring& Value);
		/// <summary> Gets and sets the service name. </summary>
		/// <value> The service name. </value>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothServer" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothServer"></exception>
		__declspec(property(get = GetServiceName, put = SetServiceName))
			tstring ServiceName;

		/// <summary> The event fires when the server builds SDP record for
		///   the service it runs. If an application needs to provide
		///   additional attributes it should handle the event. By default no
		///   additional attributes is added for the SDP record. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Protocols"> The additional protocol descriptors array that
		///   should be added to SDP record. </param>
		/// <param name="Profiles"> The profile descriptors list that should be added
		///   to SDP record. </param>
		/// <param name="Formats"> Other attributes that should be added to SDP
		///   record. </param>
		/// <param name="Cod"> <para> Class of device (COD) information. A 32-bit
		///   parameter of COD_SERVICE_* class of device bits associated with this
		///   SDP record. The system combines these bits with COD bits from other
		///   service records and system characteristics. The resulting class of
		///   device for the local radio is advertised when the radio is found during
		///   device inquiry. When the last SDP record associated with a particular
		///   service bit is deleted, that service bit is no longer reported in
		///   responses to future device inquiries. </para>
		///   <para> The format and possible values for the COD value are defined in
		///   the Bluetooth Assigned Numbers 1.1 portion of the Bluetooth
		///   specification, Section 1.2. (This resource may not be available in some
		///   languages and countries.) </para> </param>
		/// <remarks> This event will not fire with BlueSoleil Bluetooth
		///   driver. BlueSoleil does not support custom SDP records. </remarks>
		/// <seealso cref="wclBluetoothSdpProtocols" />
		/// <seealso cref="wclBluetoothSdpProfiles" />
		/// <seealso cref="wclBluetoothSdpFormats" />
		wclBluetoothGetSdpAttributesEvent(GetSdpAttributes);
		/// <summary> The event fires when the server is closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnClosed);
		/// <summary> The event fires when a remote client is connected to
		///   the server. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> The
		///   <see cref="CwclRfCommServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		wclRfCommServerConnectEvent(OnConnect);
		/// <summary> The event fires when connection to a remote device has
		///   been established with success to allow application provide a
		///   data processor for the connection. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Connection"> The
		///   <see cref="CwclServerClientDataConnection" /> object that requires a
		///   Data Processor. </param>
		/// <remarks> If an application needs an additional data processing it
		///   can use Data Processors. An application must create a Data Processor
		///   inside this event handler. If a Data Processor created for the
		///   connection the <c>OnData</c> event will NOT fire. </remarks>
		/// <seealso cref="CwclCustomServerClientDataProcessor" />
		/// <seealso cref="CwclServerDataConnection" />
		/// <seealso cref="CwclServerClientDataConnection" />
		wclServerConnectionProcessorEvent(OnCreateProcessor);
		/// <summary> The event fires when new data is received from the
		///   connected remote device. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> A
		///   <see cref="CwclRfCommServerClientConnection" /> object
		///   represents a remote client connection. </param>
		/// <param name="Data"> The pointer to the received data buffer.
		///   It is guaranteed that the parameter points to a valid data buffer.
		///   The data buffer is valid only inside the event handler. If an
		///   application needs to use the data outside the event handle it must
		///   allocate own buffer and copy data into it. </param>
		/// <param name="Size"> The data buffer size. It is guaranteed that the size
		///   is greater than 0. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		wclRfCommServerDataEvent(OnData);
		/// <summary> The event fires when connection to a remote device has
		///   been terminated. An application must destroy the Data Processor
		///   created for the connection. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Connection"> The
		///   <see cref="CwclServerClientDataConnection" /> object that requires a
		///   Data Processor. </param>
		/// <seealso cref="CwclCustomServerClientDataProcessor" />
		/// <seealso cref="CwclServerDataConnection" />
		/// <seealso cref="CwclServerClientDataConnection" />
		wclServerConnectionProcessorEvent(OnDestroyProcessor);
		/// <summary> The event fires when a remote client has disconnected from the
		///   server. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Client"> The
		///   <see cref="CwclRfCommServerClientConnection" /> represents a remote
		///   connected client. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		/// <seealso cref="CwclRfCommServerClientConnection" />
		wclRfCommServerDisconnectEvent(OnDisconnect);
		/// <summary> The event fires when the server is ready to accept incoming
		///   connections (is in listening state). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnListen);
	};

	/// <summary> Bluetooth Low Energy GATT client. </summary>
	/// <remarks> The <c>TwclGattClient</c> component enables an
	///   application to connect to a Bluetooth Low Energy device and work
	///   with GATT profiles. </remarks>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclGattClient : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclGattClient);

	private:
		__int64	FAddress;
		bool	FConnectOnRead;
		bool	FForceNotifications;

		bool						FActive;
		CwclGattClientConnection*	FClient;
		
		int CheckSubscriptionMethod(const wclGattSubscribeKind SubscribeKind,
			wclGattCharacteristic& Characteristic);
		
		// Client events.
		void ClientCharacteristicChanged(void* Sender, const unsigned short Handle,
			const unsigned char* const Value, const unsigned long Length);
		void ClientConnect(void* Sender, const int Error);
		void ClientConnectionParamsChanged(void* Sender);
		void ClientConnectionPhyChanged(void* Sender);
		void ClientDisconnect(void* Sender, const int Reason);
		void ClientMaxPduSizeChanged(void* Sender);

	protected:
		/// <summary> Fires the <c>OnCharacteristicChanged</c> event. </summary>
		/// <param name="Handle"> A changed characteristic handle. </param>
		/// <param name="Value"> A pointer to the characteristic value. </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <remarks> The <c>Value</c> parameter is valid only inside the event
		///   handler. If an application needs to use it outside the event handler
		///   it must be copied. </remarks>
		virtual void DoCharacteristicChanged(const unsigned short Handle,
			const unsigned char* const Value, const unsigned long Length);
		/// <summary> Fires the <c>OnConnectionParamsChanged</c> event. </summary>
		virtual void DoConnectionParamsChanged();
		/// <summary> Fires the <c>OnConnectionPhyChanged</c> event. </summary>
		virtual void DoConnectionPhyChanged();
		/// <summary> Fires the <c>OnMaxPduSizeChanged</c> event. </summary>
		virtual void DoMaxPduSizeChanged();

		/// <summary> Fires the <c>OnConnected</c> event. </summary>
		/// <param name="Error"> The operation result. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires then <c>OnDisconnected</c> event. </summary>
		virtual void DoDisconnect(const int Reason);

	public:
		/// <summary> Creates new <c>TwclGattClient</c>
		///   component. </summary>
		CwclGattClient();
		/// <summary> Frees the component. </summary>
		/// <remarks> The component must always be destroyed in the same thread it
		///   was created. </remarks>
		virtual ~CwclGattClient();

		/// <summary> Connects to a remote Bluetooth LE device. </summary>
		/// <param name="Radio"> The <see cref="CwclBluetoothRadio" /> object used
		///   to communicate with a remote Bluetooth device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The method starts connection to a remote Bluetooth LE device.
		///   When connection operation completed the <c>OnConnected</c> event will
		///   fire. The operation result will be passed into the <c>OnConnected</c>
		///   event. </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		int Connect(CwclBluetoothRadio* const Radio);
		/// <summary> Disconnects from a remote device. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();

		/// <summary> The method searches the characteristic in given service with
		///   the specified UUID. </summary>
		/// <param name="Service"> The GATT services. </param>
		/// <param name="Uuid"> The required characteristic's UUID. </param>
		/// <param name="Characteristic"> If the method completed with success on
		///   output contains the required characteristic. If the method failed the
		///   value is undefined. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		int FindCharacteristic(const wclGattService& Service, const wclGattUuid& Uuid,
			wclGattCharacteristic& Characteristic, const wclGattOperationFlag Flag = goNone);
		/// <summary> The method searches the service with specified UUID. </summary>
		/// <param name="Uuid"> The required service's UUID. </param>
		/// <param name="Service"> If the method completed with success on output
		///   contains the required service. If the method failed the value is
		///   undefined. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		int FindService(const wclGattUuid& Uuid, wclGattService& Service,
			const wclGattOperationFlag Flag = goNone);

		/// <summary> The method reads all the characteristics available for the
		///   specified service. </summary>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Characteristics"> On output a list of the service's
		///   characteristics. An application is responsible to clean up a memory
		///   allocated for the dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattCharacteristics" />
		int ReadCharacteristics(const wclGattService& Service, const wclGattOperationFlag Flag,
			wclGattCharacteristics& Characteristics);
		/// <summary> The method reads the value of the specified
		///   characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Value"> On output contains a pointer to the characteristic's value.
		///   An application is responsible to clean up a memory allocated for the value. </param>
		/// <param name="Length"> On output contains a characteristic value length in
		///   bytes. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		int ReadCharacteristicValue(const wclGattCharacteristic& Characteristic,
			const wclGattOperationFlag Flag, unsigned char*& Value, unsigned long& Length,
			const wclGattProtectionLevel Protection = plNone);
		/// <summary> The method reads all the descriptors available for the
		///   specified characteristic. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Descriptors"> On output contains the list of the
		///   characteristic's descriptors. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattDescriptors" />
		int ReadDescriptors(const wclGattCharacteristic& Characteristic, const wclGattOperationFlag Flag,
			wclGattDescriptors& Descriptors);
		/// <summary> The method reads the value of the specified
		///   descriptor. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattDescriptorValue" />
		/// <seealso cref="wclGattProtectionLevel" />
		int ReadDescriptorValue(const wclGattDescriptor& Descriptor, const wclGattOperationFlag Flag,
			wclGattDescriptorValue& Value, const wclGattProtectionLevel Protection = plNone);
		/// <summary> The method reads all the included services available for a
		///   given service. </summary>
		/// <param name="Service"> Parent service returned by the call to
		///   the <c>ReadServices</c> method. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattService" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		int ReadIncludedServices(const wclGattService& Service, const wclGattOperationFlag Flag,
			wclGattServices& Services);
		/// <summary> Reads available services from a remote Bluetooth LE
		///   device. </summary>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Services"> On output a list of available GATT services.
		///   An application is responsible to clean up a memory allocated for the
		///   dynamic array. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattServices" />
		int ReadServices(const wclGattOperationFlag Flag, wclGattServices& Services);

		/// <summary> The method writes the specified characteristic value to the
		///   Bluetooth device. </summary>
		/// <param name="Characteristic"> A <see cref="wclGattCharacteristic" />
		///   structure obtained by previous call to the <c>ReadCaracteristics</c>
		///   method. </param>
		/// <param name="Value"> A pointer to the characteristic's value. </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="WriteKind"> The write operation mode. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattWriteKind" />
		int WriteCharacteristicValue(const wclGattCharacteristic& Characteristic,
			const unsigned char* const Value, const unsigned long Length,
			const wclGattProtectionLevel Protection = plNone,
			const wclGattWriteKind WriteKind = wkAuto);
		/// <summary> The method writes the specified descriptor value to the
		///   Bluetooth device. </summary>
		/// <param name="Descriptor"> A <see cref="wclGattDescriptor" /> obtained
		///   by previous call to the <c>ReadDescriptors</c> method. </param>
		/// <param name="Value"> A descriptor's value. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattDescriptor" />
		/// <seealso cref="wclGattDescriptorValue" />
		/// <seealso cref="wclGattProtectionLevel" />
		int WriteDescriptorValue(const wclGattDescriptor& Descriptor,
			const wclGattDescriptorValue& Value,
			const wclGattProtectionLevel Protection = plNone);
		
		/// <summary> Writes the client configuration descriptor to the
		///   device. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="Subscribe"> The value indicates should we subscribe
		///   or unsubscribe from the characteristic value changes. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="SubscribeKind"> Indicates a characteristic value change
		///   notification method that should be used. If a characteristic has both
		///   <c>IsIndicatable</c> and <c>IsNotifiable</c> properties set then this
		///   parameter allows to control which notification method should be
		///   used. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> In order to receive notifications about characteristic
		///   value changes the client must set the Client Configuration Descriptor.
		///   An application can use this method to do it in easy way. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattSubscribeKind" />
		int WriteClientConfiguration(const wclGattCharacteristic& Characteristic,
			const bool Subscribe, const wclGattOperationFlag Flag,
			const wclGattProtectionLevel Protection = plNone,
			const wclGattSubscribeKind SubscribeKind = skManual);

		/// <summary> Subscribes for the characteristic changes
		///   notifications. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="SubscribeKind"> Indicates a characteristic value change
		///   notification method that should be used. If a characteristic has both
		///   <c>IsIndicatable</c> and <c>IsNotifiable</c> properties set then this
		///   parameter allows to control which notification method should be
		///   used. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattSubscribeKind" />
		int Subscribe(const wclGattCharacteristic& Characteristic,
			wclGattSubscribeKind SubscribeKind = skManual);
		/// <summary> Unsubscribes from the characteristic changes
		///   notifications. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is not interested any more. </param>
		/// <param name="SubscribeKind"> Indicates a characteristic value change
		///   notification method that should be used. If a characteristic has both
		///   <c>IsIndicatable</c> and <c>IsNotifiable</c> properties set then this
		///   parameter allows to control which notification method should be
		///   used. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattSubscribeKind" />
		int Unsubscribe(const wclGattCharacteristic& Characteristic,
			const wclGattSubscribeKind SubscribeKind = skManual);
		
		/// <summary> Subscribes for the characteristic changes
		///   notifications and writes the client configuration descriptor to the
		///   device. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="SubscribeKind"> Indicates a characteristic value change
		///   notification method that should be used. If a characteristic has both
		///   <c>IsIndicatable</c> and <c>IsNotifiable</c> properties set then this
		///   parameter allows to control which notification method should be
		///   used. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> You can use this method to replace calls to the
		///   <c>Subscribe</c> and to the <c>WriteClientConfiguration</c>
		///   methods. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattSubscribeKind" />
		int SubscribeForNotifications(const wclGattCharacteristic& Characteristic,
			const wclGattOperationFlag Flag = goNone,
			const wclGattProtectionLevel Protection = plNone,
			const wclGattSubscribeKind SubscribeKind = skManual);
		/// <summary> Unsubscribes from the characteristic changes
		///   notifications and writes the client configuration descriptor to the
		///   device. </summary>
		/// <param name="Characteristic"> A characteristic object in that changes
		///   an application is interested. </param>
		/// <param name="Flag"> Operation behavior flag. </param>
		/// <param name="Protection"> Describes the required protection
		///   level. </param>
		/// <param name="SubscribeKind"> Indicates a characteristic value change
		///   notification method that should be used. If a characteristic has both
		///   <c>IsIndicatable</c> and <c>IsNotifiable</c> properties set then this
		///   parameter allows to control which notification method should be
		///   used. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> You can use this method to replace calls to the
		///   <c>Unsubscribe</c> and to the <c>WriteClientConfiguration</c>
		///   methods. </remarks>
		/// <seealso cref="wclGattCharacteristic" />
		/// <seealso cref="wclGattOperationFlag" />
		/// <seealso cref="wclGattProtectionLevel" />
		/// <seealso cref="wclGattSubscribeKind" />
		int UnsubscribeFromNotifications(const wclGattCharacteristic& Characteristic,
			const wclGattOperationFlag Flag = goNone,
			const wclGattProtectionLevel Protection = plNone,
			const wclGattSubscribeKind SubscribeKind = skManual);

		/// <summary> Gets the current connection parameters. </summary>
		/// <param name="Params"> If the function completed with success on output
		///   contains the current connection parameters. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParameters" />
		int GetConnectionParams(wclBluetoothLeConnectionParameters& Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   type. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> When performing firmware updates, higher throughput is
		///   necessary to complete the operation swiftly for the user. In those
		///   scenarios, you should request <c>ppThroughputOptimized</c> connection
		///   parameters for the duration of the firmware update. That will reduce
		///   the number of concurrent connections to other Bluetooth peripherals,
		///   and should be used sparingly. </para>
		///   <para> Conversely, when connecting to multiple LE devices
		///   concurrently, you should use <c>ppPowerOptimized</c>. That will
		///   increase the acceptable peripheral latency for the connection,
		///   reducing the interval at which the LE device must respond to the
		///   host OS. That allows the local Bluetooth radio to schedule more
		///   connections concurrently, and reduces power usage on both the host OS
		///   and on the peripheral device. </para>
		///   <para> If the connection parameters were changed successfully the
		///   <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersType" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersType Params);
		/// <summary> Request the connection parameters change to the specified
		///   preferred connection parameters. </summary>
		/// <param name="Params"> The preferred Bluetooth LE connection parameters
		///   value. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks><para> If the connection parameters were changed successfully
		///   the <c>OnConnectionParamsChanged</c> even fires. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		/// <seealso cref="wclBluetoothLeConnectionParametersValue" />
		int SetConnectionParams(const wclBluetoothLeConnectionParametersValue& Params);

		/// <summary> Reads the maximum PDU size for the current connection. </summary>
		/// <param name="Size"> If the method completed with success on output
		///   contains the maximum PDU size. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> The PDU size includes header and payload. For example if
		///   PDU size is 23 bytes the allowed payload is 20 bytes. </remarks>
		int GetMaxPduSize(unsigned short& Size);

		/// <summary> Reads the Bluetooth LE physical layer (PHY)
		///   information. </summary>
		/// <param name="Info"> If the method completed with success on output
		///   contains the connection PHY information. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclBluetoothLeConnectionPhy" />
		int GetConnectionPhyInfo(wclBluetoothLeConnectionPhy& Info);

		/// <summary> Gets the Radio used for connection. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object that used for
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the Radio used for connection. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object that used for
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the client state. </summary>
		/// <returns> The client state. </returns>
		/// <seealso cref="wclClientState" />
		wclClientState GetState() const;
		/// <summary> Gets the client state. </summary>
		/// <value> The client state. </value>
		/// <seealso cref="wclClientState" />
		__declspec(property(get = GetState)) wclClientState State;

		/// <summary> Gets a target Bluetooth device's MAC
		///   address. </summary>
		/// <returns> The Bluetooth MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Sets a target Bluetooth device's MAC
		///   address. </summary>
		/// <param name="Value"> The Bluetooth MAC address. </param>
		/// <remarks> If an application changes the property when connection is
		///   active the <see cref="wclEGattClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattClient"></exception>
		void SetAddress(const __int64 Value);
		/// <summary> Gets and sets a target Bluetooth device's MAC
		///   address. </summary>
		/// <value> The Bluetooth MAC address. </value>
		/// <remarks> If an application changes the property when connection is
		///   active the <see cref="wclEGattClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEGattClient"></exception>
		__declspec(property(get = GetAddress, put = SetAddress)) __int64 Address;

		/// <summary> Gets connection mode. </summary>
		/// <returns> The Boolean indicates the connection mode. </returns>
		/// <remarks> If this property set to <c>True</c> the connection to a target
		///   device will be executed on first services read or when the OS decided
		///   to do that. If the property is <c>False</c> the connection will be
		///   executed (if possible) on <c>Connect</c> call. </remarks>
		bool GetConnectOnRead() const;
		/// <summary> Sets connection mode. </summary>
		/// <param name="Value"> The Boolean indicates the connection mode. </param>
		/// <remarks> If this property set to <c>True</c> the connection to a target
		///   device will be executed on first services read or when the OS decided
		///   to do that. If the property is <c>False</c> the connection will be
		///   executed (if possible) on <c>Connect</c> call. </remarks>
		/// <exception cref="wclEGattClient"></exception>
		void SetConnectOnRead(const bool Value);
		/// <summary> Gets and sets connection mode. </summary>
		/// <value> The Boolean indicates the connection mode. </value>
		/// <remarks> If this property set to <c>True</c> the connection to a target
		///   device will be executed on first services read or when the OS decided
		///   to do that. If the property is <c>False</c> the connection will be
		///   executed (if possible) on <c>Connect</c> call. </remarks>
		/// <exception cref="wclEGattClient"></exception>
		__declspec(property(get = GetConnectOnRead, put = SetConnectOnRead))
			bool ConnectOnRead;

		/// <summary> Gets the notifications mode. </summary>
		/// <returns> The Boolean indicates the notifications mode. </returns>
		/// <remarks> If this property set to <c>True</c> the characteristic value
		///   changes notification (and/or indication) will work correctly with
		///   some boards (such as <c>Bluno</c>, <c>Bluno Meag</c> and some others)
		///   that do not have <c>Characteristic Client Configucation
		///   Descriptor</c>. </remarks>
		bool GetForceNotifications() const;
		/// <summary> Sets the notifications mode. </summary>
		/// <param name="Value"> The Boolean indicates the notifications mode. </param>
		/// <remarks> If this property set to <c>True</c> the characteristic value
		///   changes notification (and/or indication) will work correctly with
		///   some boards (such as <c>Bluno</c>, <c>Bluno Meag</c> and some others)
		///   that do not have <c>Characteristic Client Configucation
		///   Descriptor</c>. </remarks>
		void SetForceNotifications(const bool Value);
		/// <summary> Gets and sets the notifications mode. </summary>
		/// <value> The Boolean indicates the notifications mode. </value>
		/// <remarks> If this property set to <c>True</c> the characteristic value
		///   changes notification (and/or indication) will work correctly with
		///   some boards (such as <c>Bluno</c>, <c>Bluno Meag</c> and some others)
		///   that do not have <c>Characteristic Client Configucation
		///   Descriptor</c>. </remarks>
		/// <exception cref="wclEGattClient"></exception>
		__declspec(property(get = GetForceNotifications, put = SetForceNotifications))
			bool ForceNotifications;

		/// <summary> The event fires when a subscribed characteristic value has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Handle"> A changed characteristic handle. </param>
		/// <param name="Value"> A pointer to the characteristic value. </param>
		/// <param name="Length"> A characteristic value length in bytes. </param>
		/// <remarks> <para> The <c>Value</c> parameter is valid only inside the event
		///   handler. If an application needs to use it outside the event handler
		///   it must be copied. </para>
		///   <para> To receive characteristic value change events an application
		///   must first subscribe for characteristic changes notification
		///   by calling <c>Subscribe</c> method. </para> </remarks>
		wclGattCharacteristicChangedEvent(OnCharacteristicChanged);
		/// <summary> The event fires when a connection to a remote device has been
		///   established. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <remarks> If the <c>Error</c> parameter of the event is not
		///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
		///   method again from inside the event handler. </remarks>
		wclClientConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when the connection parameters
		///   changed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to retrieve the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>BLED112</c> dongle and with
		///   <c>Microsoft</c> Bluetooth drivers on <c>Windows 11</c> and
		///   above. </para> </remarks>
		wclNotifyEvent(OnConnectionParamsChanged);
		/// <summary> The event fires when the connection PHY changed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		wclNotifyEvent(OnConnectionPhyChanged);
		/// <summary> The even fires when a connection to a remote device has been
		///   closed. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnDisconnect);
		/// <summary> The event fires when the maximum PDU size changed. </summary>
		/// <remarks> Once the event fires an application can use the
		///   <c>GetMaxPduSize</c> method to read the current maximum PDU
		///   size. </remarks>
		wclNotifyEvent(OnMaxPduSizeChanged);
	};

	/// <summary> Bluetooth Low Energy GATT server. </summary>
	/// <remarks> The <c>TwclGattServer</c> component enables an
	///   application to act as GATT peripheral device. </remarks>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclGattServer : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclGattServer);
		
	private:
		CwclGattServerConnection* FServer;
		
		void CharacteristicRead(void* Sender, CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicReadRequest* const Request);
		void CharacteristicWrite(void* Sender, CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicWriteRequest* const Request);
		void ClientConnected(void* Sender, CwclGattServerClient* const Client);
		void ClientDisconnected(void* Sender, CwclGattServerClient* const Client);
		void ClientSubscribed(void* Sender, CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		void ClientUnsubscribed(void* Sender, CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		void ConnectionParamsChanged(void* Sender, CwclGattServerClient* const Client);
		void ConnectionPhyChanged(void* Sender, CwclGattServerClient* const Client);
		void MaxPduSizeChanged(void* Sender, CwclGattServerClient* const Client);
		void NotificationSizeChanged(void* Sender, CwclGattServerClient* const Client);
		void ServerStarted(void* Sender);
		void ServerStopped(void* Sender);
		
	protected:
		/// <summary> Fires the <c>OnClientConnected</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a connected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoClientConnected(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnClientDisconnected</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoClientDisconnected(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnConnectionParamsChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoConnectionParamsChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnConnectionPhyChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a disconnected client. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoConnectionPhyChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnMaxPduSizeChanged</c> event. </summary>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoMaxPduSizeChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnNotificationSizeChanged</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that represents a client which changed the maximum notification
		///   size. </param>
		/// <seealso cref="CwclGattServerClient" />
		virtual void DoNotificationSizeChanged(CwclGattServerClient* const Client);
		/// <summary> Fires the <c>OnRead</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that requested read. </param>
		/// <param name="Characteristic"> The local GATT characteristic object
		///   that requested the write operation. </param>
		/// <param name="Request"> The GATT read request object. </param>
		/// <remarks> This method is called when a remote GATT client requests
		///   read from the characteristic. An application must call the
		///   <c>Respond</c> method to send a data back to the device. </remarks>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="CwclGattLocalCharacteristicReadRequest" />
		virtual void DoRead(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicReadRequest* const Request);
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		/// <summary> Fires the <c>OnSubscribed</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that subscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void DoSubscribed(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		/// <summary> Fires the <c>OnUnsubscribed</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		virtual void DoUnsubscribed(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic);
		/// <summary> Fires the <c>OnWrite</c> event. </summary>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object
		///   that requested write. </param>
		/// <param name="Characteristic"> The local GATT characteristic object
		///   that requested the write operation. </param>
		/// <param name="Request"> The GATT characteristic write request
		///   object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="CwclGattLocalCharacteristicWriteRequest" />
		virtual void DoWrite(CwclGattServerClient* const Client,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclGattLocalCharacteristicWriteRequest* const Request);
		
	public:
		/// <summary> Creates new component. </summary>
		CwclGattServer();
		/// <summary> Frees the component. </summary>
		/// <remarks> The component must always be destroyed in the same thread it
		///   was created. </remarks>
		virtual ~CwclGattServer();
		
		/// <summary> Initializes Bluetooth LE GATT Server. </summary>
		/// <param name="Radio"> The <see cref="CwclBluetoothRadio" /> object used
		///   to communicate with a remote Bluetooth device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> Before adding services and characteristics an
		///   application must initialize the server by calling this method. </para>
		///   <para> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers or on any other Windows platform with BlueSoleil
		///   Bluetooth drivers. </para> </remarks>
		/// <seealso cref="CwclBluetoothRadio" />
		int Initialize(CwclBluetoothRadio* const Radio);
		/// <summary> Uninitializes the Bluetooth LE GATT Server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> <para> An application must call this method after stopping the
		///   server to release all allocated resources. </para>
		///   <para> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers or on any other Windows platform with BlueSoleil
		///   Bluetooth drivers. </para> </remarks>
		int Uninitialize();
		
		/// <summary> Starts the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start();
		/// <summary> Stops the GATT server. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Creates new local GATT service and adds it to the services
		///   list. </summary>
		/// <param name="Uuid"> The service's UUID. </param>
		/// <param name="Service"> If the function completed with success this
		///   parameter receives a just created GATT local service object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclGattUuid" />
		/// <seealso cref="CwclGattLocalService" />
		int AddService(const wclGattUuid& Uuid, CwclGattLocalService*& Service);
		/// <summary> Clears the local services list. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int ClearServices();
		/// <summary> Deletes the service with given index. </summary>
		/// <param name="Index"> The service's index. The parameter must be in range
		///   between 0 and ServicesCount - 1. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DeleteService(const size_t Index);
		
		/// <summary> Gets the server's state. </summary>
		/// <returns> <c>True</c> if the server is running. </returns>
		bool GetInitialized() const;
		/// <summary> Gets the server's state. </summary>
		/// <value> <c>True</c> if the server is running. </value>
		__declspec(property(get = GetInitialized)) bool Initialized;

		/// <summary> Gets the server's owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the server's owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the server running status. </summary>
		/// <returns> <c>True</c> if the server is advertising. </returns>
		bool GetStarted() const;
		/// <summary> Gets the server running status. </summary>
		/// <value> <c>True</c> if the server is advertising. </value>
		__declspec(property(get = GetStarted)) bool Started;
		
		/// <summary> Gets the local GATT service by its index. </summary>
		/// <param name="Index"> The service's index. The parameter must be in range
		///   between 0 and ServicesCount - 1. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <returns> The local GATT service object. </returns>
		/// <seealso cref="CwclGattLocalService" />
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEGattServer"></exception>
		CwclGattLocalService* GetServices(const size_t Index) const;
		/// <summary> Gets the local GATT service by its index. </summary>
		/// <value> The local GATT service object. </value>
		/// <seealso cref="CwclGattLocalService" />
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEGattServer"></exception>
		__declspec(property(get = GetServices)) CwclGattLocalService* Services[];

		/// <summary> Gets the services count. </summary>
		/// <returns> The services count. </returns>
		size_t GetServicesCount() const;
		/// <summary> Gets the services count. </summary>
		/// <value> The services count. </value>
		__declspec(property(get = GetServicesCount)) size_t ServicesCount;

		/// <summary> Gets the GATT server client by its index. </summary>
		/// <param name="Index"> The client's index. The parameter must be in range
		///   between 0 and ClientsCount - 1. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <returns> The GATT server client object. </returns>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclGattServerClient* GetClients(const size_t Index) const;
		/// <summary> Gets the GATT server client by its index. </summary>
		/// <value> The GATT server client object. </value>
		/// <seealso cref="CwclGattServerClient" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetClients)) CwclGattServerClient* Clients[];

		/// <summary> Gets the clients count. </summary>
		/// <returns> The clients count. </returns>
		size_t GetClientsCount() const;
		/// <summary> Gets the clients count. </summary>
		/// <value> The clients count. </value>
		__declspec(property(get = GetClientsCount)) size_t ClientsCount;

		/// <summary> The event fires when a client connected to the
		///   server. </summary>
		/// <summary> The GATT server client event handlers prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnClientConnected);
		/// <summary> The event fires when a client disconnected from
		///   the server. </summary>
		/// <summary> The GATT server client event handlers prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnClientDisconnected);
		/// <summary> The event fires when the connection parameters
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionParams</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnConnectionParamsChanged);
		/// <summary> The event fires when the connection PHY changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <remarks> <para> Once this event received an application can use the
		///   <c>GetConnectionPhyInfo</c> method to get the current connection
		///   parameters. </para>
		///   <para> This feature is supported with <c>Microsoft</c> Bluetooth
		///   drivers on <c>Windows 11</c> and above. </para> </remarks>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnConnectionPhyChanged);
		/// <summary> The event fires when maximum PDU size changed for the
		///   connected client. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnMaxPduSizeChanged);
		/// <summary> The event fires when a maximum notification size of a
		///   subscribed client has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   represents a GATT server client. </param>
		/// <seealso cref="CwclGattServerClient" />
		wclGattServerClientEvent(OnNotificationSizeChanged);
		/// <summary> The event fires when a remote GATT client requests
		///   characteristic's data read. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   requested read. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <param name="Request"> The GATT read request object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="TwclGattLocalCharacteristicReadRequest" />
		wclGattLocalCharacteristicReadEvent(OnRead);
		/// <summary> The event fires when the Bluetooth LE GATT Server has been
		///   successfully started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Bluetooth LE GATT Server has been
		///   stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
		/// <summary> The event fires when a remote GATT client subscribes to the
		///   characteristic changes notifications or indications. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   subscribed or unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		wclGattLocalCharacteristicSubscribedClientsChangedEvent(OnSubscribed);
		/// <summary> The event fires when a remote GATT client unsubscribes from
		///   the characteristic changes notifications or indications. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   subscribed or unsubscribed. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		wclGattLocalCharacteristicSubscribedClientsChangedEvent(OnUnsubscribed);
		/// <summary> The event fires when a remote device writes data to the
		///   characteristic. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Client"> The <see cref="CwclGattServerClient" /> object that
		///   requested write. </param>
		/// <param name="Characteristic"> The characteristic object for which writes
		///   is executing. </param>
		/// <param name="Request"> The GATT characteristic write request object. </param>
		/// <seealso cref="CwclGattServerClient" />
		/// <seealso cref="CwclGattLocalCharacteristic" />
		/// <seealso cref="TwclGattLocalCharacteristicWriteRequest" />
		wclGattLocalCharacteristicWriteEvent(OnWrite);
	};

	/// <summary> The Bluetooth LE Beacon watcher. </summary>
	/// <remarks> The component allows to monitor Bluetooth LE Beacon advertisement
	///   packets. </remarks>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclBluetoothLeBeaconWatcher : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclBluetoothLeBeaconWatcher);

	private:
		bool									FActive;
		bool									FAllowExtendedAdvertisements;
		unsigned short							FScanInterval;
		wclBluetoothLeScanningMode				FScanningMode;
		unsigned short							FScanWindow;
		CwclBluetoothLeBeaconWatcherConnection*	FWatcher;
		
		void WatcherAdvertisementAppearanceFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Appearance);
		void WatcherAdvertisementFrameInformation(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const tstring& Name,
			const wclBluetoothLeAdvertisementType PacketType,
			const wclBluetoothLeAdvertisementFlags& Flags);
		void WatcherAdvertisementExtFrameInformation(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const wclBluetoothAddressType AddressType,
			const char TxPower, const wclBluetoothLeExtendedFrameFlags& Flags);
		void WatcherAdvertisementRawFrame(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned char DataType,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAdvertisementReceived(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAdvertisementService16DataFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAdvertisementService32DataFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAdvertisementService128DataFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAdvertisementServiceSol16Frame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid);
		void WatcherAdvertisementServiceSol32Frame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid);
		void WatcherAdvertisementServiceSol128Frame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const GUID& Uuid);
		void WatcherAdvertisementTxPowerLevelFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const char TxPower);
		void WatcherAdvertisementUuidFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const GUID& Uuid);
		void WatcherAltBeaconFrame(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short CompanyId, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid, const char TxRssi,
			const unsigned char Reserved, const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherAppleAirdropFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirdropFrameData& Data);
		void WatcherAppleAirplaySourceFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplaySourceFrameData& Data);
		void WatcherAppleAirplayTargetFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplayTargetFrameData& Data);
		void WatcherAppleAirprintFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirprintFrameData& Data);
		void WatcherAppleFindMyFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleFindMyFrameData& Data);
		void WatcherAppleHandoffFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHandoffFrameData& Data);
		void WatcherAppleHeySiriFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHeySiriFrameData& Data);
		void WatcherAppleHomeKitFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHomeKitFrameData& Data);
		void WatcherAppleiBeaconFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleiBeaconFrameData& Data);
		void WatcherAppleMagicSwitchFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleMagicSwitchFrameData& Data);
		void WatcherAppleNearbyActionFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyActionFrameData& Data);
		void WatcherAppleNearbyInfoFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyInfoFrameData& Data);
		void WatcherAppleProximityPairingFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleProximityPairingFrameData& Data);
		void WatcherAppleTetheringSourceFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringSourceFrameData& Data);
		void WatcherAppleTetheringTargetFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringTargetFrameData& Data);
		void WatcherAppleUnknownFrame(void* Sender, const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleUnknownFrameData& Data);
		void WatcherDriAsdMessage(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclDriRawData& Raw);
		void WatcherEddystoneTlmFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned long AdvCnt,
			const unsigned short Batt, const unsigned long SecCnt, const double Temp,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherEddystoneUidFrame(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherEddystoneUrlFrame(void* Sender, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const tstring& Url);
		void WatcherManufacturerRawFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		void WatcherMicrosoftCdpBeaconFrame(void* Sender, const __int64 Address,
			const __int64 Timestamp, const char Rssi,
			const wclBluetoothLeCdpBeaconScenarioType ScenarioType, const unsigned char Version,
			const wclBluetoothLeCdpBeaconDeviceType DeviceType, const unsigned char SubVersion,
			const bool ShareNearBy, const bool AddressAsDeviceId,
			const wclBluetoothLeCdpBeaconExtendedDeviceStatuses& ExtendedDeviceStatus,
			const wclBluetoothLeCdpBeaconSalt& Salt, const wclBluetoothLeCdpBeaconHash& Hash);
		
		void WatcherStarted(void* Sender);
		void WatcherStopped(void* Sender);

	protected:
		/// <summary> Fires the <c>OnAdvertisementAppearanceFrame</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Appearance"> The Bluetooth LE device appearance
		///   value. </param>
		virtual void DoAdvertisementAppearanceFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Appearance);
		/// <summary> Fires the <c>OnAdvertisementFrameInformation</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Name"> The Bluetooth LE advertiser's name. </param>
		/// <param name="PacketType"> The Bluetooth LE advertisement data packet
		///   type. </param>
		/// <param name="Flags"> The Bluetooth LE advertisement packet payload
		///   flags. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementType" />
		/// <seealso cref="wclBluetoothLeAdvertisementFlags" />
		virtual void DoAdvertisementFrameInformation(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const tstring& Name,
			const wclBluetoothLeAdvertisementType PacketType,
			const wclBluetoothLeAdvertisementFlags& Flags);
		/// <summary> Fires the <c>OnAdvertisementExtFrameInformation</c>
		///   event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AddressType"> The Bluetooth LE address type. </param>
		/// <param name="TxPower"> The received transmit power of the
		///   advertisement. Ranges from -127 dBm to 20 dBm. -128 indicates
		///   "no value". </param>
		/// <param name="Flags"> The Bluetooth LE advertisement extended frame
		///   flags. </param>
		/// <seealso cref="wclBluetoothAddressType" />
		/// <seealso cref="wclBluetoothLeExtendedFrameFlags" />
		virtual void DoAdvertisementExtFrameInformation(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const wclBluetoothAddressType AddressType,
			const char TxPower, const wclBluetoothLeExtendedFrameFlags& Flags);
		/// <summary> Fires the <c>OnAdvertisementRawFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="DataType"> The frame's data type. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>NULL</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementRawFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned char DataType,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnAdvertisementReceived</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>nil</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementReceived(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService16DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService16DataFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService32DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService32DataFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnService128DataFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAdvertisementService128DataFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnServiceSol16Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol16Frame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Uuid);
		/// <summary> Fires the <c>OnServiceSol32Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol32Frame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned long Uuid);
		/// <summary> Fires the <c>OnServiceSol128Frame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bit service UUID. </param>
		virtual void DoAdvertisementServiceSol128Frame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const GUID& Uuid);
		/// <summary> Fires the <c>OnAdvertisementTxPowerLevelFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxPower"> The TX power level in range from -127 to 128
		///   dBm. </param>
		virtual void DoAdvertisementTxPowerLevelFrame(const __int64 Address,
			const __int64 Timestamp, const char Rssi, const char TxPower);
		/// <summary> Fires the <c>OnAdvertisementUuidFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The advertised UUID value. </param>
		virtual void DoAdvertisementUuidFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const GUID& Uuid);
		/// <summary> Fires the <c>OnAltBeaconFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Major"> The beacon's Major value. </param>
		/// <param name="Minor"> The beacon's Minor value. </param>
		/// <param name="Uuid"> The beacon's UUID. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Reserved"> A 1-byte value from 0x00 to 0xFF. Interpretation
		///   of this value is to be defined by the manufacturer and is to be
		///   evaluated based on the CompanyId value. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoAltBeaconFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short CompanyId, const unsigned short Major,
			const unsigned short Minor, const GUID& Uuid, const char TxRssi,
			const unsigned char Reserved, const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnAppleAirdropFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirdropFrameData" />
		virtual void DoAppleAirdropFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirdropFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirplaySourceFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplaySourceFrameData" />
		virtual void DoAppleAirplaySourceFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplaySourceFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirplayTargetFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplayTargetFrameData" />
		virtual void DoAppleAirplayTargetFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirplayTargetFrameData& Data);
		/// <summary> Fires the <c>OnAppleAirprintFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirprintFrameData" />
		virtual void DoAppleAirprintFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleAirprintFrameData& Data);
		/// <summary> Fires the <c>OnAppleFindMyFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleFindMyFrameData" />
		virtual void DoAppleFindMyFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleFindMyFrameData& Data);
		/// <summary> Fires the <c>OnAppleHandoffFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		virtual void DoAppleHandoffFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHandoffFrameData& Data);
		/// <summary> Fires the <c>OnAppleHeySiriFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		virtual void DoAppleHeySiriFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHeySiriFrameData& Data);
		/// <summary> Fires the <c>OnAppleHomeKitFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHomeKitFrameData" />
		virtual void DoAppleHomeKitFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleHomeKitFrameData& Data);
		/// <summary> Fires the <c>OnAppleiBeaconFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleiBeaconFrameData" />
		virtual void DoAppleiBeaconFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleiBeaconFrameData& Data);
		/// <summary> Fires the <c>OnAppleMagicSwitchFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleMagicSwitchFrameData" />
		virtual void DoAppleMagicSwitchFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleMagicSwitchFrameData& Data);
		/// <summary> Fires the <c>OnAppleNearbyActionFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyActionFrameData" />
		virtual void DoAppleNearbyActionFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyActionFrameData& Data);
		/// <summary> Fires the <c>OnAppleNearbyInfoFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyInfoFrameData" />
		virtual void DoAppleNearbyInfoFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleNearbyInfoFrameData& Data);
		/// <summary> Fires the <c>OnAppleProximityPairingFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleProximityPairingFrameData" />
		virtual void DoAppleProximityPairingFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleProximityPairingFrameData& Data);
		/// <summary> Fires the <c>OnAppleTetheringSourceFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringSourceFrameData" />
		virtual void DoAppleTetheringSourceFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringSourceFrameData& Data);
		/// <summary> Fires the <c>OnAppleTetheringTargetFrame</c>
		///   event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringTargetFrameData" />
		virtual void DoAppleTetheringTargetFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleTetheringTargetFrameData& Data);
		/// <summary> Fires the <c>OnAppleUnknownFrame</c> event. </summary>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleUnknownFrameData" />
		virtual void DoAppleUnknownFrame(const wclBluetoothLeAdvertisementInfo& Info,
			const wclBluetoothLeAppleUnknownFrameData& Data);
		/// <summary> Fires the <c>OnDriAsdMessage</c> event. </summary>
		/// <param name="Address"> The drone's MAC address. </param>
		/// <param name="Timestamp"> The message's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Raw"> The raw DRI ASD messages data. </param>
		virtual void DoDriAsdMessage(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclDriRawData& Raw);
		/// <summary> Fires the <c>OnEddystoneTlmFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AdvCnt"> The running count of advertisement frames of all
		///   types emitted by the beacon since power-up or reboot, useful for
		///   monitoring performance metrics that scale per broadcast frame.
		///   If this value is reset (e.g. on reboot), the current time field is
		///   also reset. </param>
		/// <param name="Batt"> The current battery charge in millivolts, expressed
		///   as 1 mV per bit. If not supported (for example in a USB-powered
		///   beacon) the value should be zeroed. </param>
		/// <param name="SecCnt"> The 0.1 second resolution counter that represents
		///   time since beacon power-up or reboot. If this value is reset (e.g. on
		///   a reboot), the AdvCnt count field is also reset. </param>
		/// <param name="Temp"> The beacon temperature in degrees Celsius sensed by
		///   the beacon. If not supported the value is -128 °C. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoEddystoneTlmFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned long AdvCnt, const unsigned short Batt,
			const unsigned long SecCnt, const double Temp,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnEddystoneUidFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Uuid"> The Eddystone ID: 10 bytes - Namespace ID and 6
		///   bytes - Instance ID. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoEddystoneUidFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const GUID& Uuid,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnEddystoneUrlFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between
		///   -100 dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Url"> The Eddystone URL. </param>
		virtual void DoEddystoneUrlFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const char TxRssi, const tstring& Url);
		/// <summary> Fires the <c>OnManufacturerRawFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Data"> The frame raw data. The value can be <c>NULL</c> if
		///   there is no any data available in the frame. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		virtual void DoManufacturerRawFrame(const __int64 Address, const __int64 Timestamp,
			const char Rssi, const unsigned short CompanyId,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
		/// <summary> Fires the <c>OnMicrosoftCdpBeaconFrame</c> event. </summary>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC
		///   address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="ScenarioType"> The beacon scenario. </param>
		/// <param name="Version"> The protocol version. </param>
		/// <param name="DeviceType"> The device type. </param>
		/// <param name="SubVersion"> The protocol subversion. </param>
		/// <param name="ShareNearBy"> If <c>True</c> then the NearBy share setting
		///   is everyone rather than only my devices. </param>
		/// <param name="AddressAsDeviceId"> <c>True</c> indicates that the
		///   Bluetooth address can be used as the device ID. </param>
		/// <param name="ExtendedDeviceStatus"> The extended device status. </param>
		/// <param name="Salt"> The beacon salt (4 random bytes). </param>
		/// <param name="Hash"> SHA256 Hash of Salt plus Device Thumbprint. </param>
		/// <seealso cref="wclBluetoothLeCdpBeaconScenarioType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconDeviceType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconSalt" />
		/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatuses" />
		/// <seealso cref="wclBluetoothLeCdpBeaconHash" />
		virtual void DoMicrosoftCdpBeaconFrame(__int64 Address, __int64 Timestamp,
			const char Rssi, const wclBluetoothLeCdpBeaconScenarioType ScenarioType,
			const unsigned char Version, const wclBluetoothLeCdpBeaconDeviceType DeviceType,
			const unsigned char SubVersion, const bool ShareNearBy, const bool AddressAsDeviceId,
			const wclBluetoothLeCdpBeaconExtendedDeviceStatuses& ExtendedDeviceStatus,
			const wclBluetoothLeCdpBeaconSalt& Salt, const wclBluetoothLeCdpBeaconHash& Hash);
		
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();

	public:
		/// <summary> Creates new component. </summary>
		CwclBluetoothLeBeaconWatcher();
		/// <summary> Frees the component. </summary>
		/// <remarks> The component must always be destroyed in the same thread it
		///   was created. </remarks>
		virtual ~CwclBluetoothLeBeaconWatcher();
		
		/// <summary> Starts monitoring for Bluetooth LE Beacons. </summary>
		/// <param name="Radio"> The <see cref="CwclBluetoothRadio" /> object used
		///   to communicate with a remote Bluetooth device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> If the method returns error try to call this method with
		///   default scan parameters. </remarks>
		/// <seealso cref="TwclBluetoothRadio" />
		int Start(CwclBluetoothRadio* const Radio);
		/// <summary> Stops monitoring for Bluetooth LE Beacons. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers only. </remarks>
		int Stop();

		/// <summary> Restores the default scan parameters. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int RestoreDefaults();

		/// <summary> Gets the Extended Advertisement receiving flag. </summary>
		/// <returns> <c>True</c> if the Extended Advertising format enabled. </returns>
		bool GetAllowExtendedAdvertisements() const;
		/// <summary> Sets the Extended Advertisement receiving flag. </summary>
		/// <param name="Value"> Set this parameter to <c>True</c> to enable receiving
		///   advertisements of the Extended Advertising format can be
		///   received. </param>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetAllowExtendedAdvertisements(const bool Value);
		/// <summary> Gets and sets the Extended Advertisement receiving
		///   flag. </summary>
		/// <value> Set this parameter to <c>True</c> to enable receiving
		///   advertisements of the Extended Advertising format can be
		///   received. </value>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetAllowExtendedAdvertisements, put = SetAllowExtendedAdvertisements))
			bool AllowExtendedAdvertisements;

		/// <summary> Gets Beacon Monitoring state. </summary>
		/// <returns> <c>True</c> if the Beacon monitoring is running. </returns>
		bool GetMonitoring() const;
		/// <summary> Gets Beacon Monitoring state. </summary>
		/// <value> <c>True</c> if the Beacon monitoring is running. </value>
		__declspec(property(get = GetMonitoring)) bool Monitoring;

		/// <summary> Gets the watcher owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the watcher owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the current scan interval value. </summary>
		/// <returns> The Bluetooth LE scan interval in 0.625 ms units </returns>
		unsigned short GetScanInterval() const;
		/// <summary> Sets scan interval value. </summary>
		/// <param name="Value"> Specifies the Bluetooth LE scan in 0.625 ms units. The value
		///   must be in range between 4 and 16384. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetScanInterval(unsigned short Value);
		/// <summary> Gets and sets the current scan interval value. </summary>
		/// <value> Specifies the Bluetooth LE scan in 0.625 ms units. The value
		///   must be in range between 4 and 16384. </value>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetScanInterval, put = SetScanInterval))
			unsigned short ScanInterval;

		/// <summary> Gets the current scanning mode. </summary>
		/// <returns> The Bluetooth LE scanning mode. </returns>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		wclBluetoothLeScanningMode GetScanningMode() const;
		/// <summary> Sets the current scanning mode. </summary>
		/// <param name="Value"> The Bluetooth LE scanning mode. </param>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetScanningMode(const wclBluetoothLeScanningMode Value);
		/// <summary> Gets and sets the current scanning mode. </summary>
		/// <value> The Bluetooth LE scanning mode. </value>
		/// <seealso cref="wclBluetoothLeScanningMode" />
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetScanningMode, put = SetScanningMode))
			wclBluetoothLeScanningMode ScanningMode;

		/// <summary> Gets the current scan window value. </summary>
		/// <returns> The scan window in 0.625 ms units. </returns>
		unsigned short GetScanWindow() const;
		/// <summary> Sets the current scan window value. </summary>
		/// <param name="Value"> Specifies the Bluetooth LE scan window in 0.625 ms units.
		///   The value must be in range between 4 and 16384. The scan window must
		///   be less or equal to <c>ScanInterval</c>. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetScanWindow(const unsigned short Value);
		/// <summary> Gets and sets the current scan window value. </summary>
		/// <value> Specifies the Bluetooth LE scan window in 0.625 ms units.
		///   The value must be in range between 4 and 16384. The scan window must
		///   be less or equal to <c>ScanInterval</c>. </value>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetScanWindow, put = SetScanWindow))
			unsigned short ScanWindow;

		/// <summary> The event fires when an appearance advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Appearance"> The Bluetooth LE device appearance
		///   value. </param>
		wclBluetoothLeAdvertisementAppearanceFrameEvent(OnAdvertisementAppearanceFrame);
		/// <summary> The event fires when new Bluetooth LE advertisement frame
		///   has been received and provides the common basic information about
		///   the frame. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Name"> The Bluetooth LE advertiser's name. </param>
		/// <param name="PacketType"> The Bluetooth LE advertisement data packet
		///   type. </param>
		/// <param name="Flags"> The Bluetooth LE advertisement packet payload
		///   flags. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementType" />
		/// <seealso cref="wclBluetoothLeAdvertisementFlags" />
		wclBluetoothLeAdvertisementFrameInformationEvent(OnAdvertisementFrameInformation);
		/// <summary> The event fires when new Bluetooth LE advertisement
		///   extended frame has been received and provides the common basic
		///   information about the frame. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AddressType"> The Bluetooth LE address type. </param>
		/// <param name="TxPower"> The received transmit power of the
		///   advertisement. Ranges from -127 dBm to 20 dBm. -128 indicates
		///   "no value". </param>
		/// <param name="Flags"> The Bluetooth LE advertisement extended frame
		///   flags. </param>
		/// <seealso cref="wclBluetoothAddressType" />
		/// <seealso cref="wclBluetoothLeExtendedFrameFlags" />
		wclBluetoothLeAdvertisementExtFrameInformationEvent(OnAdvertisementExtFrameInformation);
		/// <summary> The <c>OnAdvertisementRawFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="DataType"> The frame's data type. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>NULL</c>. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementRawFrameEvent(OnAdvertisementRawFrame);
		/// <summary> The event fires when any Bluetooth LE advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Data"> The frame's raw bytes data. If there is no data the
		///   value is <c>nil</c>. </param>
		/// <remarks> Unlike the <c>OnAdvertisementRawFrame</c> and the
		///   <c>OnManufacturerRawFrame</c> this even fires for any Bluetooth LE
		///   advertisement and contains unparsed raw frame data. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementReceivedEvent(OnAdvertisementReceived);
		/// <summary> The event fires when a Bluetooth LE 16 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bit service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService16DataFrameEvent(OnAdvertisementService16DataFrame);
		/// <summary> The event fires when a Bluetooth LE 32 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bits service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService32DataFrameEvent(OnAdvertisementService32DataFrame);
		/// <summary> The event fires when a Bluetooth LE 128 bit Service Data
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bits service UUID. </param>
		/// <param name="Data"> The service data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAdvertisementService128DataFrameEvent(OnAdvertisementService128DataFrame);
		/// <summary> The event fires when a Bluetooth LE 16 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 16 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol16FrameEvent(OnAdvertisementServiceSol16Frame);
		/// <summary> The event fires when a Bluetooth LE 32 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 32 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol32FrameEvent(OnAdvertisementServiceSol32Frame);
		/// <summary> The event fires when a Bluetooth LE 128 bit Service
		///   Solicitation advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The 128 bits service UUID. </param>
		wclBluetoothLeAdvertisementServiceSol128FrameEvent(OnAdvertisementServiceSol128Frame);
		/// <summary> The event fires when a TX power level advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxPower"> The TX power level in range from -127 to 128
		///   dBm. </param>
		wclBluetoothLeAdvertisementTxPowerLevelFrameEvent(OnAdvertisementTxPowerLevelFrame);
		/// <summary> The event fires when an UUID advertisement frame has been
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Uuid"> The advertised UUID value. </param>
		wclBluetoothLeAdvertisementUuidFrameEvent(OnAdvertisementUuidFrame);
		/// <summary> The event fires when a Bluetooth LE Alt beacon
		///   advertisement frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Major"> The beacon's Major value. </param>
		/// <param name="Minor"> The beacon's Minor value. </param>
		/// <param name="Uuid"> The beacon's UUID. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 1 meter
		///   distance. </param>
		/// <param name="Reserved"> A 1-byte value from 0x00 to 0xFF. Interpretation
		///   of this value is to be defined by the manufacturer and is to be
		///   evaluated based on the CompanyId value. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeAltBeaconFrameEvent(OnAltBeaconFrame);
		/// <summary> The event fires when an Apple Airdrop advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirdropFrameData" />
		wclBluetoothLeAppleAirdropFrameEvent(OnAppleAirdropFrame);
		/// <summary> The event fires when an Apple Airplay Source advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplaySourceFrameData" />
		wclBluetoothLeAppleAirplaySourceFrameEvent(OnAppleAirplaySourceFrame);
		/// <summary> The event fires when an Apple Airplay Target advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirplayTargetFrameData" />
		wclBluetoothLeAppleAirplayTargetFrameEvent(OnAppleAirplayTargetFrame);
		/// <summary> The event fires when an Apple Airprint advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleAirprintFrameData" />
		wclBluetoothLeAppleAirprintFrameEvent(OnAppleAirprintFrame);
		/// <summary> The event fires when an Apple Find My advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleFindMyFrameData" />
		wclBluetoothLeAppleFindMyFrameEvent(OnAppleFindMyFrame);
		/// <summary> The event fires when an Apple Handoff advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHandoffFrameData" />
		wclBluetoothLeAppleHandoffFrameEvent(OnAppleHandoffFrame);
		/// <summary> The event fires when an Apple Hey Siri advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="TwclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHeySiriFrameData" />
		wclBluetoothLeAppleHeySiriFrameEvent(OnAppleHeySiriFrame);
		/// <summary> The event fires when an Apple HomeKit advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleHomeKitFrameData" />
		wclBluetoothLeAppleHomeKitFrameEvent(OnAppleHomeKitFrame);
		/// <summary> The event fires when an Apple iBeacon advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleiBeaconFrameData" />
		wclBluetoothLeAppleiBeaconFrameEvent(OnAppleiBeaconFrame);
		/// <summary> The event fires when an Apple Magic Switch advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleMagicSwitchFrameData" />
		wclBluetoothLeAppleMagicSwitchFrameEvent(OnAppleMagicSwitchFrame);
		/// <summary> The event fires when an Apple Nearby Action advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyActionFrameData" />
		wclBluetoothLeAppleNearbyActionFrameEvent(OnAppleNearbyActionFrame);
		/// <summary> The event fires when an Apple Nearby Info advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleNearbyInfoFrameData" />
		wclBluetoothLeAppleNearbyInfoFrameEvent(OnAppleNearbyInfoFrame);
		/// <summary> The event fires when an Apple Proximity Pairing advertisement
		///   frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleProximityPairingFrameData" />
		wclBluetoothLeAppleProximityPairingFrameEvent(OnAppleProximityPairingFrame);
		/// <summary> The event fires when an Tethering Source advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringSourceFrameData" />
		wclBluetoothLeAppleTetheringSourceFrameEvent(OnAppleTetheringSourceFrame);
		/// <summary> The event fires when an Tethering Target advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleTetheringTargetFrameData" />
		wclBluetoothLeAppleTetheringTargetFrameEvent(OnAppleTetheringTargetFrame);
		/// <summary> The event fires when an unknown Apple advertisement frame
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Info"> The Bluetooth LE advertisement information. </param>
		/// <param name="Data"> The advertisement frame decoded data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementInfo" />
		/// <seealso cref="wclBluetoothLeAppleUnknownFrameData" />
		wclBluetoothLeAppleUnknownFrameEvent(OnAppleUnknownFrame);
		/// <summary> The event fires when a Drone Remote ID ASD message
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The drone's MAC address. </param>
		/// <param name="Timestamp"> The message's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="Raw"> The raw DRI ASD messages data. </param>
		wclBluetoothLeDriAsdMessageEvent(OnDriAsdMessage);
		/// <summary> The <c>OnEddystoneTlmFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="AdvCnt"> The running count of advertisement frames of all
		///   types emitted by the beacon since power-up or reboot, useful for
		///   monitoring performance metrics that scale per broadcast frame.
		///   If this value is reset (e.g. on reboot), the current time field is
		///   also reset. </param>
		/// <param name="Batt"> The current battery charge in millivolts, expressed as
		///   1 mV per bit. If not supported (for example in a USB-powered beacon) the
		///   value should be zeroed. </param>
		/// <param name="SecCnt"> The 0.1 second resolution counter that represents
		///   time since beacon power-up or reboot. If this value is reset (e.g. on
		///   a reboot), the AdvCnt count field is also reset. </param>
		/// <param name="Temp"> The beacon temperature in degrees Celsius sensed by
		///   the beacon. If not supported the value is -128 °C. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeEddystoneTlmFrameEvent(OnEddystoneTlmFrame);
		/// <summary> The <c>OnEddystoneUidFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Uuid"> The Eddystone ID: 10 bytes - Namespace ID and 6
		///   bytes - Instance ID. </param>
		/// <param name="Data"> The additional frame data. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeEddystoneUidFrameEvent(OnEddystoneUidFrame);
		/// <summary> The <c>OnEddystoneUrlFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="TxRssi"> The beacon's RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution measured at 0 meter
		///   distance. </param>
		/// <param name="Url"> The Eddystone URL. </param>
		wclBluetoothLeEddystoneUrlFrameEvent(OnEddystoneUrlFrame);
		/// <summary> The <c>OnManufacturerRawFrame</c> event handler
		///   prototype. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="CompanyId"> The beacon's manufacturer ID as defined in the
		///   Bluetooth SIG Assigned Numbers. </param>
		/// <param name="Data"> The frame raw data. The value can be <c>NULL</c> if
		///   there is no any data available in the frame. </param>
		/// <seealso cref="wclBluetoothLeAdvertisementFrameRawData" />
		wclBluetoothLeManufacturerRawFrameEvent(OnManufacturerRawFrame);
		/// <summary> The event fires when Microsoft CDP Beacon frame received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Address"> The Bluetooth LE advertiser's MAC address. </param>
		/// <param name="Timestamp"> The frame's timestamp in Universal Time
		///   format. </param>
		/// <param name="Rssi"> The measured RSSI value in dBm at range between -100
		///   dBm and +20 dBm at 1 dBm resolution. </param>
		/// <param name="ScenarioType"> The beacon scenario. </param>
		/// <param name="Version"> The protocol version. </param>
		/// <param name="DeviceType"> The device type. </param>
		/// <param name="SubVersion"> The protocol subversion. </param>
		/// <param name="ShareNearBy"> If <c>True</c> then the NearBy share setting is
		///   everyone rather than only my devices. </param>
		/// <param name="AddressAsDeviceId"> <c>True</c> indicates that the Bluetooth
		///   address can be used as the device ID. </param>
		/// <param name="ExtendedDeviceStatus"> The extended device status. </param>
		/// <param name="Salt"> The beacon salt (4 random bytes). </param>
		/// <param name="Hash"> SHA256 Hash of Salt plus Device Thumbprint. </param>
		/// <seealso cref="wclBluetoothLeCdpBeaconScenarioType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconDeviceType" />
		/// <seealso cref="wclBluetoothLeCdpBeaconSalt" />
		/// <seealso cref="wclBluetoothLeCdpBeaconExtendedDeviceStatuses" />
		/// <seealso cref="wclBluetoothLeCdpBeaconHash" />
		wclBluetoothLeMicrosoftCdpBeaconFrameEvent(OnMicrosoftCdpBeaconFrame);
		/// <summary> The event fires when the Bluetooth LE beacon monitoring
		///   started. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Bluetooth LE beacon monitoring
		///   stopped. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The Bluetooth LE advertiser components. </summary>
	/// <remarks> The feature is supported only on Windows 10 platform with
	///   <c>Microsoft</c> Bluetooth drivers or on any Windows platform with
	///   <c>BLED112</c> Bluetooth dongle. </remarks>
	/// <seealso cref="CwclBluetoothComponent" />
	class CwclBluetoothLeAdvertiser : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclBluetoothLeAdvertiser);

	private:
		bool									FActive;
		WCL_BLE_ADV_LIST*						FAdvertisements;
		CwclBluetoothLeAdvertiserConnection*	FAdvertiser;
		unsigned short							FInterval;
		
		/* Extended advertisement properties. */
		
		bool									FAnonymous;
		bool									FIncludeTxRssi;
		char									FPreferredTxRssi;
		bool									FUseExtendedAdvertisement;

		int CheckAdvertisement(const CwclBluetoothLeAdvertisement* const Advertisement) const;
		void DeleteAllAdvertisements();
		void DeleteAdvertisement(const size_t Index);

		/* Advertiser connection events. */

		void AdvertiserStarted(void* Sender);
		void AdvertiserStopped(void* Sender);
		
	protected:
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		
	public:
		/// <summary> Creates new component. </summary>
		CwclBluetoothLeAdvertiser();
		/// <summary> Frees the component. </summary>
		/// <remarks> The component must always be destroyed in the same thread it
		///   was created. </remarks>
		virtual ~CwclBluetoothLeAdvertiser();

		/// <summary> Adds Bluetooth LE advertisement to the advertisements
		///   list. </summary>
		/// <param name="Advertisement"> The Bluetooth LE advertisement
		///   object. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothLeAdvertisement" />
		int Add(CwclBluetoothLeAdvertisement* const Advertisement);
		/// <summary> Clears the advertisements list. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Clear();
		/// <summary> Deletes the Bluetooth LE advertisement from the advertisements
		///   list. </summary>
		/// <param name="Index"> The advertisement index. The <c>Index</c> must be
		///   in range between <c>0</c> and <c>Count - 1</c>. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Delete(const size_t Index);
		
		/// <summary> Starts advertising. </summary>
		/// <param name="Radio"> The <see cref="CwclBluetoothRadio" /> object used
		///   to communicate with a remote Bluetooth device. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int Start(CwclBluetoothRadio* const Radio);
		/// <summary> Stops advertising. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This feature is supported on Windows 10 with the Microsoft
		///   Bluetooth drivers only. </remarks>
		int Stop();

		/// <summary> Restores the default advertising parameters. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int RestoreDefaults();
		
		/// <summary> Gets the Bluetooth LE advertisement object by its index. </summary>
		/// <param name="Index"> The advertisement index. The <c>Index</c> must be
		///   in range between <c>0</c> and <c>Count - 1</c>. </param>
		/// <returns> The Bluetooth LE advertisement object. </returns>
		/// <seealso cref="CwclBluetoothLeAdvertisement" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclBluetoothLeAdvertisement* GetAdvertisements(const size_t Index) const;
		/// <summary> Gets the Bluetooth LE advertisement object by its index. </summary>
		/// <value> The Bluetooth LE advertisement object. </value>
		/// <seealso cref="CwclBluetoothLeAdvertisement" />
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetAdvertisements)) CwclBluetoothLeAdvertisement* Advertisements[];

		/// <summary> Gets Advertiser state. </summary>
		/// <returns> <c>True</c> if the Bluetooth LE advertising is running. </returns>
		bool GetAdvertising() const;
		/// <summary> Gets Advertiser state. </summary>
		/// <value> <c>True</c> if the Bluetooth LE advertising is running. </value>
		__declspec(property(get = GetAdvertising)) bool Advertising;

		/// <summary> Gets the advertisements count. </summary>
		/// <returns> The number of the Bluetooth LE advertisements. </returns>
		size_t GetCount() const;
		/// <summary> Gets the advertisements count. </summary>
		/// <value> The number of the Bluetooth LE advertisements. </value>
		__declspec(property(get = GetCount)) size_t Count;

		/// <summary> Gets the advertising interval. </summary>
		/// <returns> The advertising interval in 0.625ms units. </returns>
		unsigned short GetInterval() const;
		/// <summary> Sets the advertising interval. </summary>
		/// <param name="Value"> The advertising interval in 0.625ms units. The value must be in
		///   range between 32 and 16384. </param>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetInterval(const unsigned short Value);
		/// <summary> Gets and sets the advertising interval. </summary>
		/// <value> The advertising interval in 0.625ms units. The value must be in
		///   range between 32 and 16384. </value>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetInterval, put = SetInterval)) unsigned short Interval;

		/// <summary> Gets the advertiser owner. </summary>
		/// <returns> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the advertiser owner. </summary>
		/// <value> The <see cref="CwclBluetoothRadio" /> object owns the
		///   connection. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/* Extended advertisement properties. */
		
		/// <summary> Specifies whether or not the device address is included in the
		///   advertisement header. By default, the address is included. </summary>
		/// <returns> The value indicates whether the device address is hidden. </returns>
		bool GetAnonymous() const;
		/// <summary> Specifies whether or not the device address is included in the
		///   advertisement header. By default, the address is included. </summary>
		/// <param name="value"> Indicates whether the device address is hidden. The default
		///   value is <c>False</c>, indicating that the address is
		///   included. </param>
		/// <remarks> <para> The Extended Advertising format must be enabled by
		///   setting the <c>UseExtendedAdvertisement</c> to <c>True</c> to use this
		///   property. If the <c>UseExtendedAdvertisement</c> is <c>False</c> the
		///   value of this property is ignored. </para>
		///   <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetAnonymous(const bool value);
		/// <summary> Specifies whether or not the device address is included in the
		///   advertisement header. By default, the address is included. </summary>
		/// <value> Indicates whether the device address is hidden. The default
		///   value is <c>False</c>, indicating that the address is
		///   included. </value>
		/// <remarks> <para> The Extended Advertising format must be enabled by
		///   setting the <c>UseExtendedAdvertisement</c> to <c>True</c> to use this
		///   property. If the <c>UseExtendedAdvertisement</c> is <c>False</c> the
		///   value of this property is ignored. </para>
		///   <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetAnonymous, put = SetAnonymous)) bool Anonymous;

		/// <summary> Specifies whether the transmit power level is included in
		///   the advertisement header. </summary>
		/// <returns> The value indicates whether the transmit power level is
		///   included. </returns>
		bool GetIncludeTxRssi() const;
		/// <summary> Specifies whether the transmit power level is included in
		///   the advertisement header. </summary>
		/// <param name="value"> Indicates whether the transmit power level is included.
		///   The default value is <c>False</c>. </param>
		/// <remarks> <para> The Extended Advertising format must be enabled by
		///   setting the <c>UseExtendedAdvertisement</c> to <c>True</c> to use this
		///   property. If the <c>UseExtendedAdvertisement</c> is <c>False</c> the
		///   value of this property is ignored. </para>
		///   <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetIncludeTxRssi(const bool value);
		/// <summary> Specifies whether the transmit power level is included in
		///   the advertisement header. </summary>
		/// <value> Indicates whether the transmit power level is included. The
		///   default value is <c>False</c>. </value>
		/// <remarks> <para> The Extended Advertising format must be enabled by
		///   setting the <c>UseExtendedAdvertisement</c> to <c>True</c> to use this
		///   property. If the <c>UseExtendedAdvertisement</c> is <c>False</c> the
		///   value of this property is ignored. </para>
		///   <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetIncludeTxRssi, put = SetIncludeTxRssi))
			bool IncludeTxRssi;

		/// <summary> If specified, requests that the radio use the indicated
		///   transmit power level for the advertisement. </summary>
		/// <returns> The requested power level in dDm at range between -100
		///   dBm and +20 for the radio transmission. </returns>
		char GetPreferredTxRssi() const;
		/// <summary> If specified, requests that the radio use the indicated
		///   transmit power level for the advertisement. </summary>
		/// <param name="value"> The requested power level in dDm at range between -100
		///   dBm and +20 for the radio transmission. The default is -127 indicating
		///   that this feature is disabled. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <remarks> <para> Enabling the Extended Advertising format is necessary
		///   to enable several other related properties. </para>
		///  <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetPreferredTxRssi(const char value);
		/// <summary> If specified, requests that the radio use the indicated
		///   transmit power level for the advertisement. </summary>
		/// <value> The requested power level in dDm at range between -100
		///   dBm and +20 for the radio transmission. The default is -127 indicating
		///   that this feature is disabled. If the parameter is out of range the
		///   <see cref="wclEInvalidArgument" /> exception raises.</value>
		/// <remarks> <para> Enabling the Extended Advertising format is necessary
		///   to enable several other related properties. </para>
		///  <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEInvalidArgument"></exception>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetPreferredTxRssi, put = SetPreferredTxRssi))
			char PreferredTxRssi;

		/// <summary> Specifies that the advertisement publisher should use the
		///   Extended Advertising format. </summary>
		/// <returns> The value indicates whether or not the Extended Advertising format
		///   should be used. </returns>
		bool GetUseExtendedAdvertisement() const;
		/// <summary> Specifies that the advertisement publisher should use the
		///   Extended Advertising format. </summary>
		/// <param name="value"> Indicates whether or not the Extended Advertising format
		///   should be used. The default value is <c>False</c>. </param>
		/// <remarks> <para> Enabling the Extended Advertising format is necessary
		///   to enable several other related properties. </para>
		///  <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		void SetUseExtendedAdvertisement(const bool value);
		/// <summary> Specifies that the advertisement publisher should use the
		///   Extended Advertising format. </summary>
		/// <value> Indicates whether or not the Extended Advertising format should
		///   be used. The default value is <c>False</c>. </value>
		/// <remarks> <para> Enabling the Extended Advertising format is necessary
		///   to enable several other related properties. </para>
		///  <para> If the advertiser is running and an application changes the
		///   property the <see cref="wclEBluetoothLeBeacon" /> exception
		///   raises. </para> </remarks>
		/// <exception cref="wclEBluetoothLeBeacon"></exception>
		__declspec(property(get = GetUseExtendedAdvertisement, put = SetUseExtendedAdvertisement))
			bool UseExtendedAdvertisement;

		/// <summary> The event fires when the advertising started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the advertising stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> The class provides methods to communicate with Wii Remote
	///   controller. </summary>
	class CwclWiiRemoteClient : public CwclBluetoothComponent
	{
		DISABLE_COPY(CwclWiiRemoteClient);
		
	private:
		bool			FActive;
		__int64			FAddress;
		unsigned long	FTimeout;
		
		CwclWiiRemoteClientConnection* FClient;
		
		/* Client events. */
		
		void ClientAccelChanged(void* Sender, const wclWiiRemoteAccel& Accel);
		void ClientBalanceBoardChanged(void* Sender, const wclWiiRemoteBalanceBoard& Board);
		void ClientButtonsChanged(void* Sender, const wclWiiRemoteButtons& Buttons);
		void ClientClassicControllerChanged(void* Sender,
			const wclWiiRemoteClassicController& Controller);
		void ClientConnect(void* Sender, const int Error);
		void ClientDisconnect(void* Sender, const int Reason);
		void ClientDrumsChanged(void* Sender, const wclWiiRemoteDrums& Drums);
		void ClientExtensionAttached(void* Sender);
		void ClientExtensionDetached(void* Sender);
		void ClientGuitarChanged(void* Sender, const wclWiiRemoteGuitar& Guitar);
		void ClientIrChanged(void* Sender, const wclWiiRemoteIrSensors& Ir);
		void ClientNunchukChanged(void* Sender, const wclWiiRemoteNunchuk& Nunchuk);
		void ClientStatusChanged(void* Sender, const double Batt, const wclWiiRemoteLeds& Leds);
		
	protected:
		/// <summary> Fire the <c>OnAccelChanged</c> event. </summary>
		/// <param name="Accel"> The current accelerometer data. </param>
		/// <seealso cref="wclWiiRemoteAccel" />
		virtual void DoAccelChanged(const wclWiiRemoteAccel& Accel);
		/// <summary> Fires the <c>OnBalanceBoardChanged</c> event </summary>
		/// <param name="Board"> The new Balance Board extension
		///   state. </param>
		/// <seealso cref="wclWiiRemoteBalanceBoard" />
		virtual void DoBalanceBoardChanged(const wclWiiRemoteBalanceBoard& Board);
		/// <summary> Fires the <c>OnButtonsChanged</c> event. </summary>
		/// <param name="Buttons"> The new buttons state. </param>
		/// <seealso cref="wclWiiRemoteButtons" />
		virtual void DoButtonsChanged(const wclWiiRemoteButtons& Buttons);
		/// <summary> Fires the <c>OnClassicControllerChanged</c> event. </summary>
		/// <param name="Controller"> The current state of the Wii Remote Classic
		///   Controller extension. </param>
		/// <seealso cref="wclWiiRemoteClassicController" />
		virtual void DoClassicControllerChanged(const wclWiiRemoteClassicController& Controller);
		/// <summary> Fires the <c>OnConnect</c> event. </summary>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		virtual void DoConnect(const int Error);
		/// <summary> Fires the <c>OnDisconnect</c> event. </summary>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		virtual void DoDisconnect(const int Reason);
		/// <summary> Fires the <c>OnDrumsChanged</c> event. </summary>
		/// <param name="Drums"> The current state of the Drums extension. </param>
		/// <seealso cref="wclWiiRemoteDrums" />
		virtual void DoDrumsChanged(const wclWiiRemoteDrums& Drums);
		/// <summary> Fires the <c>OnExtensionAttached</c> event. </summary>
		virtual void DoExtensionAttached();
		/// <summary> Fires the <c>OnExtensionDetached</c> event. </summary>
		virtual void DoExtensionDetached();
		/// <summary> Fires the <c>OnGuitarChanged</c> event. </summary>
		/// <param name="Guitar"> The current Guitar extension state. </param>
		/// <seealso cref="wclWiiRemoteGuitar" />
		virtual void DoGuitarChanged(const wclWiiRemoteGuitar& Guitar);
		/// <summary> Fires the <c>OnIrChanged</c> event. </summary>
		/// <param name="Ir"> The IR sensor data. </param>
		/// <seealso cref="wclWiiRemoteIrSensors" />
		virtual void DoIrChanged(const wclWiiRemoteIrSensors& Ir);
		/// <summary> Fires the <c>OnNunchukChanged</c> event. </summary>
		/// <param name="Nunchuk"> The current Nunchuk extension state. </param>
		/// <seealso cref="wclWiiRemoteNunchuk" />
		virtual void DoNunchukChanged(const wclWiiRemoteNunchuk& Nunchuk);
		/// <summary> Fires the <c>OnStatusChanged</c> event. </summary>
		/// <param name="Batt"> The WeDo Remote battery level. </param>
		/// <param name="Leds"> The We Do Remote LEDs state. </param>
		/// <seealso cref="wclWiiRemoteLeds" />
		virtual void DoStatusChanged(const double Batt, const wclWiiRemoteLeds& Leds);
		
	public:
		/// <summary> Creates new Wii Remote client component. </summary>
		CwclWiiRemoteClient();
		/// <summary> Frees the component. </summary>
		virtual ~CwclWiiRemoteClient();
		
		/// <summary> Starts connecting to a Wii Remote device. </summary>
		/// <param name="Radio"> The <see cref="TwclBluetoothRadio" /> object
		///   that handles the connection. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		int Connect(CwclBluetoothRadio* const Radio);
		/// <summary> Disconnects from the Wii Remote. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Disconnect();
		
		/// <summary> Requests the Wii Remote status. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <remarks> This is asynchronous method. When operation completes the
		///   <c>OnStatusChanged</c> event fires. </remarks>
		int GetStatus();
		
		/// <summary> Changes the Wii Remote LEDs state. </summary>
		/// <param name="Leds"> The new LEDs state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiiRemoteLeds" />
		int SetLeds(const wclWiiRemoteLeds& Leds);
		/// <summary> Changes the Wii Remote LEDs state. </summary>
		/// <param name="Led1"> The new LED 1 state. </param>
		/// <param name="Led2"> The new LED 2 state. </param>
		/// <param name="Led3"> The new LED 3 state. </param>
		/// <param name="Led4"> The new LED 4 state. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetLeds(const bool Led1, const bool Led2, const bool Led3, const bool Led4);
		/// <summary> Turns the Rumble On and Off. </summary>
		/// <param name="TurnOn"> Set to <c>True</c> to turn the Rumble On. Set
		///   to <c>False</c> to turn the Rumble Off. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int SetRumble(const bool TurnOn);
		
		/// <summary> Enables accelerometer. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int EnableAccel();
		/// <summary> Disables accelerometer. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int DisableAccel();
		
		/// <summary> Sets IR IR sensor sensitivity (and turns it ON or
		///   OFF). </summary>
		/// <param name="Sensitivity"> The IR sensor sensitivity. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		int SetIrSensitivity(const wclWiiRemoteIrSensitivity& Sensitivity);

		/// <summary> Gets the current accelerometer status. </summary>
		/// <returns> <c>True</c> if the accelerometer is enabled. <c>False</c>
		///   otherwise. </returns>
		bool GetAccelEnabled() const;
		/// <summary> Gets the current accelerometer status. </summary>
		/// <value> <c>True</c> if the accelerometer is enabled. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetAccelEnabled)) bool AccelEnabled;

		/// <summary> Gets the current connected extension type. </summary>
		/// <returns> The currently connected extension. </returns>
		/// <seealso cref="wclWiiRemoteExtension " />
		wclWiiRemoteExtension GetExtension() const;
		/// <summary> Gets the current connected extension type. </summary>
		/// <value> The currently connected extension. </value>
		/// <seealso cref="wclWiiRemoteExtension " />
		__declspec(property(get = GetExtension)) wclWiiRemoteExtension Extension;

		/// <summary> Gets the current IR sensor mode. </summary>
		/// <returns> The IR sensor mode. </returns>
		/// <seealso cref="wclWiiRemoteIrMode" />
		wclWiiRemoteIrMode GetIrMode() const;
		/// <summary> Gets the current IR sensor mode. </summary>
		/// <value> The IR sensor mode. </value>
		/// <seealso cref="wclWiiRemoteIrMode" />
		__declspec(property(get = GetIrMode)) wclWiiRemoteIrMode IrMode;

		/// <summary> Gets the current IR sensor sensitivity. </summary>
		/// <returns> The IR sensor sensitivity. </returns>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		wclWiiRemoteIrSensitivity GetIrSensitivity() const;
		/// <summary> Gets the current IR sensor sensitivity. </summary>
		/// <value> The IR sensor sensitivity. </value>
		/// <seealso cref="wclWiiRemoteIrSensitivity" />
		__declspec(property(get = GetIrSensitivity)) wclWiiRemoteIrSensitivity IrSensitivity;

		/// <summary> Gets the current LEDs state. </summary>
		/// <returns> The LEDs state. </returns>
		/// <seealso cref="wclWiiRemoteLeds " />
		wclWiiRemoteLeds GetLeds() const;
		/// <summary> Gets the current LEDs state. </summary>
		/// <value> The LEDs state. </value>
		/// <seealso cref="wclWiiRemoteLeds " />
		__declspec(property(get = GetLeds)) wclWiiRemoteLeds Leds;

		/// <summary> Gets the radio object used for connection. </summary>
		/// <returns> The <see cref="TwclBluetoothRadio" /> object. </returns>
		/// <seealso cref="CwclBluetoothRadio" />
		CwclBluetoothRadio* GetRadio() const;
		/// <summary> Gets the radio object used for connection. </summary>
		/// <value> The <see cref="TwclBluetoothRadio" /> object. </value>
		/// <seealso cref="CwclBluetoothRadio" />
		__declspec(property(get = GetRadio)) CwclBluetoothRadio* Radio;

		/// <summary> Gets the current Rumble status. </summary>
		/// <returns> <c>True</c> if the Rumble is turned ON. </returns>
		bool GetRumble() const;
		/// <summary> Gets the current Rumble status. </summary>
		/// <value> <c>True</c> if the Rumble is turned ON. </value>
		__declspec(property(get = GetRumble)) bool Rumble;

		/// <summary> Gets the current client state. </summary>
		/// <returns> The client state. </returns>
		/// <seealso cref="wclClientState" />
		wclClientState GetState() const;
		/// <summary> Gets the current client state. </summary>
		/// <value> The client state. </value>
		/// <seealso cref="wclClientState" />
		__declspec(property(get = GetState)) wclClientState State;
		
		/// <summary> Gets a target WiiRemote device's MAC
		///   address. </summary>
		/// <returns> The Bluetooth MAC address. </returns>
		__int64 GetAddress() const;
		/// <summary> Sets a target WiiRemote device's MAC address. </summary>
		/// <param name="Address"> The Bluetooth MAC address. </param>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		void SetAddress(const __int64 Address);
		/// <summary> Gets and sets a target WiiRemote device's MAC
		///   address. </summary>
		/// <value> The Bluetooth MAC address. </value>
		/// <remarks> If an application changes the property when connection
		///   is active the <see cref="wclEBluetoothClient" /> exception
		///   raises. </remarks>
		/// <exception cref="wclEBluetoothClient"></exception>
		__declspec(property(get = GetAddress, put = SetAddress)) __int64 Address;
		
		/// <summary> Gets the connect timeout value. </summary>
		/// <returns> The connect timeout value in milliseconds. </returns>s>
		/// <exception cref="wclEClientActive"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		unsigned long GetTimeout() const;
		/// <summary> Sets the connect timeout value. </summary>
		/// <param name="Timeout"> The connect timeout value in milliseconds. </param>
		/// <remarks> If an application changes the property when client is
		///   connected the <see cref="wclEClientActive" /> exception
		///   raises. If new value of the <c>Timeout</c> is <c>0</c> the
		///   <see cref="wclEInvalidArgument" /> exception raises. </remarks>
		/// <exception cref="wclEClientActive"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		void SetTimeout(const unsigned long Timeout);
		/// <summary> Gets and sets the connect timeout value. </summary>
		/// <value> The connect timeout value in milliseconds. </value>
		/// <remarks> If an application changes the property when client is
		///   connected the <see cref="wclEClientActive" /> exception
		///   raises. If new value of the <c>Timeout</c> is <c>0</c> the
		///   <see cref="wclEInvalidArgument" /> exception raises. </remarks>
		/// <exception cref="wclEClientActive"></exception>
		/// <exception cref="wclEInvalidArgument"></exception>
		__declspec(property(get = GetTimeout, put = SetTimeout)) unsigned long Timeout;

		/// <summary> The event fires when the accelerometer state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Accel"> The current accelerometer data. </param>
		/// <seealso cref="wclWiiRemoteAccel" />
		wclWiiRemoteAccelChangedEvent(OnAccelChanged);
		/// <summary> The event fires when the stat eof the Balance Board extension
		///   has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Board"> The new Balance Board extension
		///   state. </param>
		/// <seealso cref="wclWiiRemoteBalanceBoard" />
		wclWiiRemoteBalanceBoardChangedEvent(OnBalanceBoardChanged);
		/// <summary> The event fires when the buttons state of the Wii Remote
		///   controller has been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Buttons"> The current state of the Wii Remote controller
		///   buttons. </param>
		/// <seealso cref="wclWiiRemoteButtons" />
		wclWiiRemoteButtonsChangedEvent(OnButtonsChanged);
		/// <summary> The event fires when a Classic Controller extension state has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Controller"> The current state of the Wii Remote Classic
		///   Controller extension. </param>
		/// <seealso cref="wclWiiRemoteClassicController" />
		wclWiiRemoteClassicControllerChangedEvent(OnClassicControllerChanged);
		/// <summary> The event fires when a connection to a remote device
		///   has been completed (with or without success). </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Error"> The connection operation result code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
		///   device was established and the remote device is connected. Otherwise
		///   the connection was not established and the remote device is
		///   not connected. </param>
		/// <remarks> If the <c>Error</c> parameter of the event is not
		///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
		///   method again from inside the event handler. </remarks>
		wclClientConnectionConnectEvent(OnConnect);
		/// <summary> The event fires when the remote connected device has been
		///   disconnected. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		/// <param name="Reason"> The disconnection code. If the
		///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
		///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
		///   reason. </param>
		wclClientConnectionDisconnectEvent(OnDisconnect);
		/// <summary> The event fires when the Drums extension state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Drums"> The current state of the Drums extension. </param>
		/// <seealso cref="wclWiiRemoteDrums" />
		wclWiiRemoteDrumsChangedEvent(OnDrumsChanged);
		/// <summary> The event fires when the extension is attached. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnExtensionAttached);
		/// <summary> The event fires when the extension has been
		///   detached. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnExtensionDetached);
		/// <summary> The event fires when the Guitar extension state has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Guitar"> The current Guitar extension state. </param>
		/// <seealso cref="wclWiiRemoteGuitar" />
		wclWiiRemoteGuitarChangedEvent(OnGuitarChanged);
		/// <summary> The event fires when the IR sensor data has been
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Ir"> The IR sensor data. </param>
		/// <seealso cref="wclWiiRemoteIrSensors" />
		wclWiiRemoteIrChangedEvent(OnIrChanged);
		/// <summary> The event fires when the state of the Nunchuk extension has
		///   been changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Nunchuk"> The current Nunchuk extension state. </param>
		/// <seealso cref="wclWiiRemoteNunchuk" />
		wclWiiRemoteNunchukChangedEvent(OnNunchukChanged);
		/// <summary> The event fires when the WeDo Remote status
		///   changed. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Batt"> The WeDo Remote battery level. </param>
		/// <param name="Leds"> The We Do Remote LEDs state. </param>
		/// <seealso cref="wclWiiRemoteLeds" />
		wclWiiRemoteStatusChangedEvent(OnStatusChanged);
	};

	/// <summary> The Bluetooth LE packets sniffer. </summary>
	class CwclBleSniffer
	{
		DISABLE_COPY(CwclBleSniffer);
		
	private:
		unsigned char				FChannel;
		tstring						FDevicePath;
		HANDLE						FInitEvent;
		int							FInitResult;
		wclMessageProcessingMethod	FMessageProcessing;
		CwclMessageReceiver*		FReceiver;
		HANDLE						FTermEvent;
		HANDLE						FThread;

		tstring FindDevice();

		__int64 DecodeAddress(const unsigned char* const Pdu, const unsigned char Ndx,
			const unsigned char Len) const;

		/* Packet parsers. */

		// Advertising PDU parsers
		bool ParseConnectIndPdu(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const unsigned char* const Pdu, const unsigned char PduLen) const;
		bool ParseSingleAddrAdvertisingPdu(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const unsigned char* const Pdu, const unsigned char PduLen) const;
		bool ParseTwoAddrAdvertisingPdu(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const unsigned char* const Pdu, const unsigned char PduLen) const;
		bool ParseAdvertisingPacket(const wclBluetoothLePacketHeader& Header,
			const unsigned char* const Payload, const unsigned short Len) const;

		bool ParseDataPacket(const wclBluetoothLePacketHeader& Header,
			const unsigned char* const Payload, const unsigned short Len) const;
		void ParsePacket(const unsigned char* const Packet,
			const unsigned short Size);

		static UINT __stdcall _SnifferThread(LPVOID Param);
		void SnifferThread();

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
		
		/// <summary> Fires the <c>OnAdvDirectIndReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="TargetA"> The address of the device to which this PDU
		///   is addressed. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True).
		///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
		///   whether the target’s address in the <c>TargetA</c> parameter is
		///   public (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c>
		///   field in the <c>PduHeader</c> parameter is <c>True</c> if the
		///   advertiser supports the LE Channel Selection Algorithm #2
		///   feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoAdvDirectIndReceived(
			const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 AdvA, const __int64 TargetA);
		/// <summary> Fires the <c>OnAdvIndReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). The
		///   <c>ChSel</c> field in the <c>PduHeader</c> parameter is <c>True</c>
		///   if the advertiser supports the LE Channel Selection Algorithm #2
		///   feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoAdvIndReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 AdvA, const unsigned char* const AdvData,
			const unsigned char AdvDataLen);
		/// <summary> Fires the <c>OnAdvNonConnIndReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoAdvNonConnIndReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 AdvA, const unsigned char* const AdvData,
			const unsigned char AdvDataLen);
		/// <summary> Fires the <c>OnAdvScanIndReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoAdvScanIndReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 AdvA, const unsigned char* const AdvData,
			const unsigned char AdvDataLen);
		/// <summary> Fires the <c>OnConnectIndReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="InitA"> The Initiator’s device address. </param>
		/// <param name="AdvA"> The advertiser’s device address. </param>
		/// <param name="LlData"> The Link Layer data. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>InitA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). The
		///   <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates whether
		///   the advertiser’s device address in the <c>AdvA</c> parameter is public
		///   (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c> field in
		///   the <c>PduHeader</c> parameter is <c>True</c> if the advertiser
		///   supports the LE Channel Selection Algorithm #2 feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		/// <seealso cref="wclBleSnifferLlData" />
		virtual void DoConnectIndReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 InitA, const __int64 AdvA, const wclBleSnifferLlData& LlData);
		/// <summary> Fires the <c>OnScanReqReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="ScanA"> The scanner's address. </param>
		/// <param name="AdvA"> The address of the device to which this PDU
		///   is addressed. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the scanner’s address in the <c>ScanA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True).
		///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
		///   whether the target’s address in the <c>AdvA</c> parameter is
		///   public (RxAdd = False) or random (RxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoScanReqReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 ScanA, const __int64 AdvA);
		/// <summary> Fires the <c>OnScanRspReceived</c> event. </summary>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="ScanRspData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="ScanRspDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random
		///   (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		virtual void DoScanRspReceived(const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 AdvA, const unsigned char* const ScanRspData,
			const unsigned char ScanRspDataLen);
		/// <summary> Fires the <c>OnRawPacketReceived</c> event. </summary>
		/// <param name="Header"> The Bluetooth LE packet header. </param>
		/// <param name="Payload"> The pointer to the packet's payload raw bytes.
		///   The pointer is valid only inside an event handler. If an application
		///   needs to use the data outside the event handler it must copy the
		///   payload. </param>
		/// <param name="Size"> The payload size (length) in bytes. </param>
		/// <seealso cref="wclBluetoothLePacketHeader" />
		virtual void DoRawPacketReceived(const wclBluetoothLePacketHeader& Header,
			const unsigned char* const Payload, const unsigned short Size);
		/// <summary> Fires the <c>OnStarted</c> event. </summary>
		virtual void DoStarted();
		/// <summary> Fires the <c>OnStopped</c> event. </summary>
		virtual void DoStopped();
		
	public:
		/// <summary> Creates new BLE sniffer component. </summary>
		CwclBleSniffer();
		/// <summary> Frees the component. </summary>
		virtual ~CwclBleSniffer();
		
		/// <summary> Starts capturing the BLE packets. </summary>
		/// <param name="DevicePath"> The device's path. If the parameter is an
		///   empty string first found device will be used. </param>
		/// <param name="Channel"> The channel number. Only channels 37, 38 and 39
		///   are supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start(const tstring& DevicePath, const unsigned char Channel);
		/// <summary> Starts capturing the BLE packets. </summary>
		/// <param name="Channel"> The channel number. Only channels 37, 38 and 39
		///   are supported. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Start(const unsigned char Channel);
		/// <summary> Stops capturing the BLE packets. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Stop();
		
		/// <summary> Gets the sniffer's status. </summary>
		/// <returns> <c>True</c> if the sniffer is running. <c>False</c>
		///   otherwise. </returns>
		bool GetActive() const;
		/// <summary> Gets the sniffer's status. </summary>
		/// <value> <c>True</c> if the sniffer is running. <c>False</c>
		///   otherwise. </value>
		__declspec(property(get = GetActive)) bool Active;

		/// <summary> Gets the radio channel. </summary>
		/// <returns> The channel number. </returns>
		unsigned char GetChannel() const;
		/// <summary> Gets the radio channel. </summary>
		/// <value> The channel number. </value>
		__declspec(property(get = GetChannel)) unsigned char Channel;

		/// <summary> Gets the current device's path. </summary>
		/// <returns> The device's path. </returns>
		tstring GetDevicePath() const;
		/// <summary> Gets the current device's path. </summary>
		/// <value> The device's path. </value>
		__declspec(property(get = GetDevicePath)) tstring DevicePath;

		/// <summary> Gets a message processing method used by the
		///   Sniffer. </summary>
		/// <returns> The message processing method. </returns>
		/// <seealso cref="wclMessageProcessingMethod" />
		wclMessageProcessingMethod GetMessageProcessing() const;
		/// <summary> Sets a message processing method used by the
		///   Sniffer. </summary>
		/// <param name="Value"> The message processing method. </param>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEBluetoothLeSniffer"></exception>
		void SetMessageProcessing(const wclMessageProcessingMethod Value);
		/// <summary> Gets and sets a message processing method used by the
		///   Sniffer. </summary>
		/// <value> The message processing method. </value>
		/// <seealso cref="wclMessageProcessingMethod" />
		/// <exception cref="wclEBluetoothLeSniffer"></exception>
		__declspec(property(get  = GetMessageProcessing, put = SetMessageProcessing))
			wclMessageProcessingMethod MessageProcessing;

		/// <summary> The event fires when the <c>ADV_DIRECT_IND</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="TargetA"> The address of the device to which this PDU
		///   is addressed. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True).
		///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
		///   whether the target’s address in the <c>TargetA</c> parameter is
		///   public (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c> field
		///   in the <c>PduHeader</c> parameter is <c>True</c> if the advertiser
		///   supports the LE Channel Selection Algorithm #2 feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferAdvDirectIndReceivedEvent(OnAdvDirectIndReceived);
		/// <summary> The event fires when the <c>ADV_IND</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). The
		///   <c>ChSel</c> field in the <c>PduHeader</c> parameter is <c>True</c>
		///   if the advertiser supports the LE Channel Selection Algorithm #2
		///   feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferAdvIndReceivedEvent(OnAdvIndReceived);
		/// <summary> The event fires when the <c>ADV_NONCONN_IND</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferAdvNonConnIndReceivedEvent(OnAdvNonConnIndReceived);
		/// <summary> The event fires when the <c>ADV_SCAN_IND</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="AdvData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="AdvDataLen"> The advertisement data length in bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferAdvScanIndReceivedEvent(OnAdvScanIndReceived);
		/// <summary> The event fires when the <c>CONNECT_IND</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="InitA"> The Initiator’s device address. </param>
		/// <param name="AdvA"> The advertiser’s device address. </param>
		/// <param name="LlData"> The Link Layer data. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>InitA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). The
		///   <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates whether
		///   the advertiser’s device address in the <c>AdvA</c> parameter is public
		///   (RxAdd = False) or random (RxAdd = True). The <c>ChSel</c> field in the
		///   <c>PduHeader</c> parameter is <c>True</c> if the advertiser supports the
		///   LE Channel Selection Algorithm #2 feature. </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		/// <seealso cref="wclBleSnifferLlData" />
		wclBleSnifferConnectIndReceivedEvent(OnConnectIndReceived);
		/// <summary> The event fires when the <c>SCAN_REQ</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="ScanA"> The scanner's address. </param>
		/// <param name="AdvA"> The address of the device to which this PDU
		///   is addressed. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the scanner’s address in the <c>ScanA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True).
		///   The <c>RxAdd</c> field of the <c>PduHeader</c> parameter indicates
		///   whether the target’s address in the <c>AdvA</c> parameter is
		///   public (RxAdd = False) or random (RxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferScanReqReceivedEvent(OnScanReqReceived);
		/// <summary> The event fires when the <c>SCAN_RSP</c> PDU
		///   received. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="PduHeader"> The PDU header. </param>
		/// <param name="AdvA"> The advertiser address. </param>
		/// <param name="ScanRspData"> The pointer to the advertisement data.
		///   Can be <c>NULL</c>. The pointer is valid only inside the event
		///   handler. </param>
		/// <param name="ScanRspDataLen"> The advertisement data length in
		///   bytes. </param>
		/// <remarks> The <c>TxAdd</c> field of the <c>PduHeader</c> parameter
		///   indicates whether the advertiser’s address in the <c>AdvA</c>
		///   parameter is public (TxAdd = False) or random (TxAdd = True). </remarks>
		/// <seealso cref="wclBluetoothLeAdvertisingPduHeader" />
		wclBleSnifferScanRspReceivedEvent(OnScanRspReceived);
		/// <summary> The event fires when a Bluetooth LE packet
		///   captured. </summary>
		/// <param name="Sender"> The object initiates the event. </param>
		/// <param name="Header"> The Bluetooth LE packet header. </param>
		/// <param name="Payload"> The pointer to the packet's payload raw bytes.
		///   The pointer is valid only inside an event handler. If an application
		///   needs to use the data outside the event handler it must copy the
		///   payload. </param>
		/// <param name="Size"> The payload size (length) in bytes. </param>
		/// <seealso cref="wclBluetoothLePacketHeader" />
		wclBleSnifferRawPacketReceivedEvent(OnRawPacketReceived);
		/// <summary> The event fires when the Sniffer was successfully
		///   started. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStarted);
		/// <summary> The event fires when the Sniffer was successfully
		///   stopped. </summary>
		/// <param name="Sender"> The object that initiated the event. </param>
		wclNotifyEvent(OnStopped);
	};

	/// <summary> Creates new <see cref="wclGattUuid"/> structure that represents
	///   GATT short (16-bit) UUID. </summary>
	/// <param name="Uuid"> A GATT short UUID. </param>
	/// <returns> Returns new <see cref="wclGattUuid"/> structure that represents
	///   GATT short (16-bit) UUID. </summary>
	/// <seealso cref="wclGattUuid" />
	wclGattUuid wclGattMakeUuid(const unsigned short Uuid);
	/// <summary> Creates new <see cref="wclGattUuid"/> structure that represents
	///   GATT long (128-bit) UUID. </summary>
	/// <param name="Uuid"> A GATT long UUID. </param>
	/// <returns> Returns new <see cref="wclGattUuid"/> structure that represents
	///   GATT long (128-bit) UUID. </summary>
	/// <seealso cref="wclGattUuid" />
	wclGattUuid wclGattMakeUuid(const GUID& Uuid);
}