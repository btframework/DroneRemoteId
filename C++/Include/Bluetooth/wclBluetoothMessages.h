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

#include "..\Common\wclMessaging.h"

#include "wclBluetooth.h"

namespace wclBluetooth
{
	/* Bluetooth Message IDs. */

	#define WCL_MSG_ID_BLUETOOTH_BASE									0

	// Common messages.
	#define WCL_MSG_ID_BLUETOOTH_STATUS_CHANGED							(WCL_MSG_ID_BLUETOOTH_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_RADIO_UNAVAILABLE						(WCL_MSG_ID_BLUETOOTH_BASE + 2)

	// Discovering messages.
	#define WCL_MSG_ID_BLUETOOTH_DISCOVERING_BASE						(WCL_MSG_ID_BLUETOOTH_BASE + 10)
	#define WCL_MSG_ID_BLUETOOTH_DISCOVERING_STARTED					(WCL_MSG_ID_BLUETOOTH_DISCOVERING_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_DISCOVERING_COMPLETED					(WCL_MSG_ID_BLUETOOTH_DISCOVERING_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_DEVICE_FOUND							(WCL_MSG_ID_BLUETOOTH_DISCOVERING_BASE + 2)

	// Authentication messages.
	#define WCL_MSG_ID_BLUETOOTH_AUTH_BASE								(WCL_MSG_ID_BLUETOOTH_BASE + 20)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_IO_CAP_REQUEST					(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_PROTECTION_REQUEST				(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_PIN_REQUEST						(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_NUMERIC_COMPARISON				(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_PASSKEY_REQUEST					(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 4)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_PASSKEY_NOTIFICATION				(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 5)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_CONFIRM_ONLY						(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 6)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_OOB_DATA_REQUEST					(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 7)
	#define WCL_MSG_ID_BLUETOOTH_AUTH_COMPLETED							(WCL_MSG_ID_BLUETOOTH_AUTH_BASE + 8)

	// GATT client messages.
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE					(WCL_MSG_ID_BLUETOOTH_BASE + 30)
	#define WCL_MSG_ID_BLUETOOTH_LE_CHARACTERISTIC_CHANGE				(WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_LE_DEVICE_DISCONNECTED					(WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_LE_CONNECTION_PARAMS_CHANGED			(WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_LE_MAX_PDU_SIZE_CHANGED				(WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_LE_CONNECTION_PHY_CHANGED				(WCL_MSG_ID_BLUETOOTH_LE_GATT_CLIENT_BASE + 4)
		
	// Bluetooth LE advertiser messages.
	#define WCL_MSG_ID_BLUETOOTH_LE_ADVERTISER_BASE						(WCL_MSG_ID_BLUETOOTH_BASE + 40)

	// Bluetooth LE advertisement watcher messages.
	#define WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE						(WCL_MSG_ID_BLUETOOTH_BASE + 50)
	#define WCL_MSG_ID_BLUETOOTH_LE_MANUFACTURER_RAW_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_LE_ADVERTISEMENT_RAW_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_LE_FRAME_INFORMATION					(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_LE_UUID_FRAME							(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_LE_EXT_FRAME_INFORMATION				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 4)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_16_DATA_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 5)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_32_DATA_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 6)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_128_DATA_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 7)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_SOL_16_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 8)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_SOL_32_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 9)
	#define WCL_MSG_ID_BLUETOOTH_LE_SERVICE_SOL_128_FRAME				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 10)
	#define WCL_MSG_ID_BLUETOOTH_LE_ADVERTISEMENT_RECEIVED				(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 11)
	#define WCL_MSG_ID_BLUETOOTH_LE_TX_POWER_FRAME						(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 12)
	#define WCL_MSG_ID_BLUETOOTH_LE_APPEARANCE_FRAME					(WCL_MSG_ID_BLUETOOTH_LE_WATCHER_BASE + 13)

	// GATT server messages.
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE					(WCL_MSG_ID_BLUETOOTH_BASE + 70)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_WRITE					(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_READ					(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_CLIENT_SUBSCRIBED		(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_CLIENT_UNSUBSCRIBED		(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_CLIENT_CONNECTED		(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 4)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_CLIENT_DISCONNECTED		(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 5)
	#define WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_NOTIFY_SIZE_CHANGED		(WCL_MSG_ID_BLUETOOTH_LE_GATT_SERVER_BASE + 6)

	// Microsoft BLE specific authentication messages IDs.
	#define WCL_MSG_ID_BLUETOOTH_MS_BASE								(WCL_MSG_ID_BLUETOOTH_BASE + 80)
	#define WCL_MSG_ID_BLUETOOTH_MS_BLE_AUTH_PIN_REQUEST				(WCL_MSG_ID_BLUETOOTH_MS_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_MS_BLE_AUTH_NUMERIC_COMPARISON			(WCL_MSG_ID_BLUETOOTH_MS_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_MS_BLE_AUTH_PASSKEY_REQUEST			(WCL_MSG_ID_BLUETOOTH_MS_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_MS_BLE_AUTH_CONFIRM_ONLY				(WCL_MSG_ID_BLUETOOTH_MS_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_MS_AUTH_PROTECTION_REQUEST				(WCL_MSG_ID_BLUETOOTH_MS_BASE + 4)
	#define WCL_MSG_ID_BLUETOOTH_MS_AUTH_IO_CAP_REQUEST					(WCL_MSG_ID_BLUETOOTH_MS_BASE + 5)
	#define WCL_MSG_ID_BLUETOOTH_MS_AUTH_OOB_DATA						(WCL_MSG_ID_BLUETOOTH_MS_BASE + 6)

	// Silicon Labs BLED112 message IDs.
	#define WCL_MSG_ID_BLUETOOTH_BLED112_BASE							(WCL_MSG_ID_BLUETOOTH_BASE + 90)
	#define WCL_MSG_ID_BLUETOOTH_BLED112_DISCONNECT						(WCL_MSG_ID_BLUETOOTH_BLED112_BASE + 0)

	// BLE sniffer message IDs.
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE						(WCL_MSG_ID_BLUETOOTH_BASE + 100)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_DEVICE_DISCONNECTED			(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 0)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_RAW_PACKET_RECEIVED			(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 1)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_ADV_IND_RECEIVED			(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 2)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_ADV_DIRECT_IND_RECEIVED		(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 3)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_ADV_NON_CONN_IND_RECEIVED	(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 4)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_ADV_SCAN_IND_RECEIVED		(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 5)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_SCAN_REQ_RECEIVED			(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 6)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_SCAN_RSP_RECEIVED			(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 7)
	#define WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_CONNECT_IND_RECEIVED		(WCL_MSG_ID_BLUETOOTH_LE_SNIFFER_BASE + 8)

	/* Wii Remote Message IDs. */
		
	#define WCL_MSG_ID_WII_BASE							0
	#define WCL_MSG_ID_WII_BUTTONS_CHANGED				(WCL_MSG_ID_WII_BASE + 1)
	#define WCL_MSG_ID_WII_ACCEL_CHANGED				(WCL_MSG_ID_WII_BASE + 2)
	#define WCL_MSG_ID_WII_IR_CHANGED					(WCL_MSG_ID_WII_BASE + 3)
	#define WCL_MSG_ID_WII_NUNCHUK_CHANGED				(WCL_MSG_ID_WII_BASE + 4)
	#define WCL_MSG_ID_WII_CLASSIC_CONTROLLER_CHANGED	(WCL_MSG_ID_WII_BASE + 5)
	#define WCL_MSG_ID_WII_GUITAR_CHANGED				(WCL_MSG_ID_WII_BASE + 6)
	#define WCL_MSG_ID_WII_DRUMS_CHANGED				(WCL_MSG_ID_WII_BASE + 7)
	#define WCL_MSG_ID_WII_BALANCE_BOARD_CHANGED		(WCL_MSG_ID_WII_BASE + 8)
	#define WCL_MSG_ID_WII_STATUS_CHANGED				(WCL_MSG_ID_WII_BASE + 9)
	#define WCL_MSG_ID_WII_EXTENSION_STATE_CHANGED		(WCL_MSG_ID_WII_BASE + 10)

	/* Common Bluetooth Messages. */

	class CwclBluetoothMessage : public CwclBluetoothCategoryMessage
	{
		DISABLE_COPY(CwclBluetoothMessage);

	private:
		wclBluetoothApi	FApi;

	public:
		CwclBluetoothMessage(const unsigned char Id,
			const wclBluetoothApi Api);

		wclBluetoothApi GetApi() const;
		__declspec(property(get = GetApi)) wclBluetoothApi Api;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothStatusChangedMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothStatusChangedMessage);

	public:
		CwclBluetoothStatusChangedMessage(const wclBluetoothApi Api);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothRadioUnavailableMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothRadioUnavailableMessage);

	private:
		int	FReason;

	public:
		CwclBluetoothRadioUnavailableMessage(const wclBluetoothApi Api,
			const int Reason);

		int GetReason() const;
		__declspec(property(get = GetReason)) int Reason;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothDiscoveringStartedMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothDiscoveringStartedMessage);

	public:
		CwclBluetoothDiscoveringStartedMessage(const wclBluetoothApi Api);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothResultMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothResultMessage);

	private:
		int	FError;

	public:
		CwclBluetoothResultMessage(const unsigned char Id, const wclBluetoothApi Api,
			const int Error);

		int GetError() const;
		__declspec(property(get = GetError)) int Error;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothDiscoveringCompletedMessage : public CwclBluetoothResultMessage
	{
		DISABLE_COPY(CwclBluetoothDiscoveringCompletedMessage);

	public:
		CwclBluetoothDiscoveringCompletedMessage(const wclBluetoothApi Api,
			const int Error);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothRemoteDeviceMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothRemoteDeviceMessage);

	private:
		__int64	FAddress;

	protected:
		virtual __int64 UpdateAddress();

	public:
		CwclBluetoothRemoteDeviceMessage(const unsigned char Id,
			const wclBluetoothApi Api,  const __int64 Address);

		__int64 GetAddress();
		__declspec(property(get = GetAddress)) __int64 Address;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothDeviceFoundMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothDeviceFoundMessage);

	public:
		CwclBluetoothDeviceFoundMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothIoCapRequestMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothIoCapRequestMessage);

	public:
		CwclBluetoothIoCapRequestMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothProtectionRequestMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothProtectionRequestMessage);

	public:
		CwclBluetoothProtectionRequestMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothPinRequestMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothPinRequestMessage);

	public:
		CwclBluetoothPinRequestMessage(const wclBluetoothApi Api, const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothNumericComparisonMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothNumericComparisonMessage);

	private:
		long	FNumber;

	public:
		CwclBluetoothNumericComparisonMessage(const wclBluetoothApi Api, const
			__int64 Address, const unsigned long Number);
		
		unsigned long GetNumber() const;
		__declspec(property(get = GetNumber)) unsigned long Number;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothPasskeyRequestMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothPasskeyRequestMessage);

	public:
		CwclBluetoothPasskeyRequestMessage(const wclBluetoothApi Api, const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothPasskeyNotificationMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothPasskeyNotificationMessage);

	private:
		unsigned long FPasskey;

	public:
		CwclBluetoothPasskeyNotificationMessage(const wclBluetoothApi Api,
			const __int64 Address, const unsigned long Passkey);

		unsigned long GetPasskey() const;
		__declspec(property(get = GetPasskey)) unsigned long Passkey;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothConfirmOnlyMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothConfirmOnlyMessage);

	public:
		CwclBluetoothConfirmOnlyMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothOobDataRequestMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothOobDataRequestMessage);

	public:
		CwclBluetoothOobDataRequestMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothRemoteResultMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothRemoteResultMessage);

	private:
		int	FError;

	public:
		CwclBluetoothRemoteResultMessage(const unsigned char Id, const wclBluetoothApi Api,
			const __int64 Address, const int Error);

		int GetError() const;
		__declspec(property(get = GetError)) int Error;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothAuthenticationCompletedMessage : public CwclBluetoothRemoteResultMessage
	{
		DISABLE_COPY(CwclBluetoothAuthenticationCompletedMessage);

	public:
		CwclBluetoothAuthenticationCompletedMessage(const wclBluetoothApi Api,
			const __int64 Address, const int Error);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeCharacteristicChangedMessage : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothLeCharacteristicChangedMessage);

	private:
		unsigned short	FHandle;
		unsigned long	FSize;
		void*			FValue;

	public:
		CwclBluetoothLeCharacteristicChangedMessage(const wclBluetoothApi Api,
			const unsigned short Handle, const void* const Value,
			const unsigned long Size);
		virtual ~CwclBluetoothLeCharacteristicChangedMessage();

		unsigned short GetHandle() const;
		__declspec(property(get = GetHandle)) unsigned short Handle;

		unsigned long GetSize() const;
		__declspec(property(get = GetSize)) unsigned long Size;

		void* const GetValue() const;
		__declspec(property(get = GetValue)) void* Value;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeConnectionParamsChangedMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothLeConnectionParamsChangedMessage);

	public:
		CwclBluetoothLeConnectionParamsChangedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeMaxPduSizeChangedMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothLeMaxPduSizeChangedMessage);
		
	public:
		CwclBluetoothLeMaxPduSizeChangedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeConnectionPhyChangedMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothLeConnectionPhyChangedMessage);
		
	public:
		CwclBluetoothLeConnectionPhyChangedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeDeviceDisconnectedMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothLeDeviceDisconnectedMessage);

	public:
		CwclBluetoothLeDeviceDisconnectedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementFrameMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementFrameMessage);

	private:
		__int64	FTimestamp;
		char	FRssi;

	public:
		CwclBluetoothLeAdvertisementFrameMessage(const unsigned char Id,
			const wclBluetoothApi Api, const __int64 Address,
			const __int64 Timestamp, const char Rssi);

		__int64 GetTimestamp() const;
		__declspec(property(get = GetTimestamp)) __int64 Timestamp;

		char GetRssi() const;
		__declspec(property(get = GetRssi)) char Rssi;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementDataFrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementDataFrameMessage);
		
	private:
		wclBluetoothLeAdvertisementFrameRawData	FData;
		
	public:
		CwclBluetoothLeAdvertisementDataFrameMessage(const unsigned char Id,
			const wclBluetoothApi Api, const __int64 Address, const __int64 Timestamp,
			const char Rssi, const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		wclBluetoothLeAdvertisementFrameRawData GetData() const;
		__declspec(property(get = GetData)) wclBluetoothLeAdvertisementFrameRawData Data;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeManufacturerRawFrameMessage : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeManufacturerRawFrameMessage);

	private:
		unsigned short	FCompanyId;
		
	public:
		CwclBluetoothLeManufacturerRawFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned short CompanyId, const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		unsigned short GetCompanyId() const;
		__declspec(property(get = GetCompanyId)) unsigned short CompanyId;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementRawFrameMessage : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementRawFrameMessage);
		
	private:
		unsigned char	FDataType;

	public:
		CwclBluetoothLeAdvertisementRawFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned char DataType, const wclBluetoothLeAdvertisementFrameRawData& Data);

		unsigned char GetDataType() const;
		__declspec(property(get = GetDataType)) unsigned char DataType;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementFrameInformationMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementFrameInformationMessage);

	private:
		tstring								FName;
		wclBluetoothLeAdvertisementType		FPacketType;
		wclBluetoothLeAdvertisementFlags	FFlags;
		
	public:
		CwclBluetoothLeAdvertisementFrameInformationMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const tstring& Name, const wclBluetoothLeAdvertisementType PacketType,
			const wclBluetoothLeAdvertisementFlags Flags);
		
		tstring GetName() const;
		__declspec(property(get = GetName)) tstring Name;

		wclBluetoothLeAdvertisementType GetPacketType() const;
		__declspec(property(get = GetPacketType)) wclBluetoothLeAdvertisementType PacketType;

		wclBluetoothLeAdvertisementFlags GetFlags() const;
		__declspec(property(get = GetFlags)) wclBluetoothLeAdvertisementFlags Flags;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementUuidFrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementUuidFrameMessage);

	private:
		GUID	FUuid;
		
	public:
		CwclBluetoothLeAdvertisementUuidFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const GUID& Uuid);
		
		GUID GetUuid() const;
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementExtFrameInformationMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementExtFrameInformationMessage);
			
	private:
		wclBluetoothAddressType				FAddressType;
		char								FTxPower;
		wclBluetoothLeExtendedFrameFlags	FFlags;
		
	public:
		CwclBluetoothLeAdvertisementExtFrameInformationMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const wclBluetoothAddressType AddressType, const char TxPower,
			const wclBluetoothLeExtendedFrameFlags Flags);
		
		wclBluetoothAddressType GetAddressType() const;
		__declspec(property(get = GetAddressType)) wclBluetoothAddressType AddressType;

		char GetTxPower() const;
		__declspec(property(get = GetTxPower)) char TxPower;

		wclBluetoothLeExtendedFrameFlags GetFlags() const;
		__declspec(property(get = GetFlags)) wclBluetoothLeExtendedFrameFlags Flags;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeService16DataFrameMessage : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeService16DataFrameMessage);
		
	private:
		unsigned short	FUuid;
		
	public:
		CwclBluetoothLeService16DataFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned short Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		unsigned short GetUuid() const;
		__declspec(property(get = GetUuid)) unsigned short Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeService32DataFrameMessage : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeService32DataFrameMessage);
		
	private:
		unsigned long	FUuid;
		
	public:
		CwclBluetoothLeService32DataFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned long Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		unsigned long GetUuid() const;
		__declspec(property(get = GetUuid)) unsigned long Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeService128DataFrameMessage : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeService128DataFrameMessage);
		
	private:
		GUID	FUuid;
		
	public:
		CwclBluetoothLeService128DataFrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const GUID& Uuid, const wclBluetoothLeAdvertisementFrameRawData& Data);
		
		GUID GetUuid() const;
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeServiceSol16FrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeServiceSol16FrameMessage);

	private:
		unsigned short FUuid;
		
	public:
		CwclBluetoothLeServiceSol16FrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned short Uuid);
		
		unsigned short GetUuid() const;
		__declspec(property(get = GetUuid)) unsigned short Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeServiceSol32FrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeServiceSol32FrameMessage);
		
	private:
		unsigned long	FUuid;
		
	public:
		CwclBluetoothLeServiceSol32FrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const unsigned long Uuid);
		
		unsigned long GetUuid() const;
		__declspec(property(get = GetUuid)) unsigned long Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeServiceSol128FrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeServiceSol128FrameMessage);
		
	private:
		GUID	FUuid;
		
	public:
		CwclBluetoothLeServiceSol128FrameMessage(const wclBluetoothApi Api,
			const __int64 Address, const __int64 Timestamp, const char Rssi,
			const GUID& Uuid);
		
		GUID GetUuid() const;
		__declspec(property(get = GetUuid)) GUID Uuid;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAdvertisementReceived : public CwclBluetoothLeAdvertisementDataFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAdvertisementReceived);
		
	public:
		CwclBluetoothLeAdvertisementReceived(const wclBluetoothApi Api, const __int64 Address,
			const __int64 Timestamp, const char Rssi,
			const wclBluetoothLeAdvertisementFrameRawData& Data);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeTxPowerFrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeTxPowerFrameMessage);
		
	private:
		char	FTxPower;
		
	public:
		CwclBluetoothLeTxPowerFrameMessage(const wclBluetoothApi Api, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const char TxPower);
		
		char GetTxPower() const;
		__declspec(property(get = GetTxPower)) char TxPower;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeAppearanceFrameMessage : public CwclBluetoothLeAdvertisementFrameMessage
	{
		DISABLE_COPY(CwclBluetoothLeAppearanceFrameMessage);

	private:
		unsigned short	FAppearance;
		
	public:
		CwclBluetoothLeAppearanceFrameMessage(const wclBluetoothApi Api, const __int64 Address,
			const __int64 Timestamp, const char Rssi, const unsigned short Appearance);
		
		unsigned short GetAppearance() const;
		__declspec(property(get = GetAppearance)) unsigned short Appearance;
	};

	/* GATT server messages. */

	// The base class for the GATT server messages.
	class CwclBluetoothGattServerMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothGattServerMessage);

	public:
		CwclBluetoothGattServerMessage(const unsigned char Id, const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothGattServerParamsMessage : public CwclBluetoothGattServerMessage
	{
		DISABLE_COPY(CwclBluetoothGattServerParamsMessage);
		
	private:
		CwclBluetoothGattServerClientParams*	FParams;
		
	public:
		CwclBluetoothGattServerParamsMessage(const unsigned char Id,
			const wclBluetoothApi Api, const __int64 Address,
			CwclBluetoothGattServerClientParams* const Params);
		virtual ~CwclBluetoothGattServerParamsMessage();

		CwclBluetoothGattServerClientParams* GetParams() const;
		__declspec(property(get = GetParams)) CwclBluetoothGattServerClientParams* Params;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothGattServerCharMessage : public CwclBluetoothGattServerParamsMessage
	{
		DISABLE_COPY(CwclBluetoothGattServerCharMessage);
		
	private:
		CwclGattLocalCharacteristic* FCharacteristic;
		
	public:
		CwclBluetoothGattServerCharMessage(const unsigned char Id, const wclBluetoothApi Api,
			const __int64 Address, CwclBluetoothGattServerClientParams* const Params,
			CwclGattLocalCharacteristic* const Characteristic);
		
		CwclGattLocalCharacteristic* GetCharacteristic() const;
		__declspec(property(get = GetCharacteristic)) CwclGattLocalCharacteristic* Characteristic;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothGattServerCharSyncMessage : public CwclBluetoothGattServerCharMessage
	{
		DISABLE_COPY(CwclBluetoothGattServerCharSyncMessage);
		
	private:
		CwclEvent*	FEvent;
		
	public:
		CwclBluetoothGattServerCharSyncMessage(const unsigned char Id, const wclBluetoothApi Api,
			const __int64 Address, CwclBluetoothGattServerClientParams* const Params,
			CwclGattLocalCharacteristic* const Characteristic, CwclEvent* const Event);
		virtual ~CwclBluetoothGattServerCharSyncMessage();
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerWriteMessage : public CwclBluetoothGattServerCharSyncMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerWriteMessage);
		
	private:
		CwclGattLocalCharacteristicWriteRequest*	FRequest;
		
	public:
		CwclBluetoothLeGattServerWriteMessage(const wclBluetoothApi Api, const __int64 Address,
			CwclBluetoothGattServerClientParams* const Params,
			CwclGattLocalCharacteristic* const Characteristic, CwclEvent* const Event,
			CwclGattLocalCharacteristicWriteRequest* const Request);
		virtual ~CwclBluetoothLeGattServerWriteMessage();
		
		CwclGattLocalCharacteristicWriteRequest* GetRequest() const;
		__declspec(property(get = GetRequest)) CwclGattLocalCharacteristicWriteRequest* Request;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerReadMessage : public CwclBluetoothGattServerCharSyncMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerReadMessage);

	private:
		CwclGattLocalCharacteristicReadRequest*	FRequest;

	public:
		CwclBluetoothLeGattServerReadMessage(const wclBluetoothApi Api, const __int64 Address,
			CwclBluetoothGattServerClientParams* const Params,
			CwclGattLocalCharacteristic* const Characteristic,
			CwclEvent* const Event, CwclGattLocalCharacteristicReadRequest* const Request);
		virtual ~CwclBluetoothLeGattServerReadMessage();
		
		CwclGattLocalCharacteristicReadRequest* GetRequest() const;
		__declspec(property(get = GetRequest)) CwclGattLocalCharacteristicReadRequest* Request;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerClientSubscribedMessage : public CwclBluetoothGattServerCharMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerClientSubscribedMessage);
		
	public:
		CwclBluetoothLeGattServerClientSubscribedMessage(const wclBluetoothApi Api,
			const __int64 Address, CwclBluetoothGattServerClientParams* const Params,
			CwclGattLocalCharacteristic* const Characteristic);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerClientUnsubscribedMessage : public CwclBluetoothGattServerCharMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerClientUnsubscribedMessage);
		
	public:
		CwclBluetoothLeGattServerClientUnsubscribedMessage(const wclBluetoothApi Api,
			const __int64 Address, CwclGattLocalCharacteristic* const Characteristic);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerClientConnectedMessage : public CwclBluetoothGattServerParamsMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerClientConnectedMessage);
		
	public:
		CwclBluetoothLeGattServerClientConnectedMessage(const wclBluetoothApi Api,
			const __int64 Address, CwclBluetoothGattServerClientParams* const Params);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerClientDisconnectedMessage : public CwclBluetoothGattServerMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerClientDisconnectedMessage);
		
	public:
		CwclBluetoothLeGattServerClientDisconnectedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeGattServerMaxNotifySizeChangedMessage : public CwclBluetoothGattServerMessage
	{
		DISABLE_COPY(CwclBluetoothLeGattServerMaxNotifySizeChangedMessage);
		
	public:
		CwclBluetoothLeGattServerMaxNotifySizeChangedMessage(const wclBluetoothApi Api,
			const __int64 Address);
	};

	/* Microsoft BLE specific authentication messages params. */

	class CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsBlePairParams);
		
	private:
		CwclEvent*	FEvent;
		LONG		FRefCount;
		bool		FProcessed;
		
	public:
		CwclBluetoothMsBlePairParams(CwclEvent* const Event);
		virtual ~CwclBluetoothMsBlePairParams();
		
		void AddRef();
		void Release();
		
		void Signal();
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBlePinRequestParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsBlePinRequestParams);
		
	private:
		tstring	FPin;
		
	public:
		CwclBluetoothMsBlePinRequestParams(CwclEvent* const Event);
		
		tstring GetPin() const;
		void SetPin(const tstring& Pin);
		__declspec(property(get = GetPin, put = SetPin)) tstring Pin;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBleConfirmParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsBleConfirmParams);
		
	private:
		bool	FConfirm;
		
	public:
		CwclBluetoothMsBleConfirmParams(CwclEvent* const Event);
		
		bool GetConfirm() const;
		void SetConfirm(const bool Value);
		__declspec(property(get = GetConfirm, put = SetConfirm)) bool Confirm;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBlePasskeyRequestParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsBlePasskeyRequestParams);
		
	private:
		unsigned long	FPasskey;
		
	public:
		CwclBluetoothMsBlePasskeyRequestParams(CwclEvent* const Event);
		
		unsigned long GetPasskey() const;
		void SetPasskey(const unsigned long value);
		__declspec(property(get = GetPasskey, put = SetPasskey)) unsigned long Passkey;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBleProtectionRequestParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsBleProtectionRequestParams);
		
	private:
		wclBluetoothLeProtectionLevel FProtection;
		
	public:
		CwclBluetoothMsBleProtectionRequestParams(CwclEvent* const Event);
		
		wclBluetoothLeProtectionLevel GetProtection() const;
		void SetProtection(const wclBluetoothLeProtectionLevel value);
		__declspec(property(get = GetProtection, put = SetProtection))
			wclBluetoothLeProtectionLevel Protection;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsIoCapRequestParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsIoCapRequestParams);
		
	private:
		wclBluetoothMitmProtection	FMitm;
		wclBluetoothIoCapability	FIoCap;
		bool						FOobPresent;

	public:
		CwclBluetoothMsIoCapRequestParams(CwclEvent* const Event);
		
		wclBluetoothMitmProtection GetMitm() const;
		void SetMitm(const wclBluetoothMitmProtection value);
		__declspec(property(get = GetMitm, put = SetMitm)) wclBluetoothMitmProtection Mitm;

		wclBluetoothIoCapability GetIoCap() const;
		void SetIoCap(const wclBluetoothIoCapability value);
		__declspec(property(get = GetIoCap, put = SetIoCap)) wclBluetoothIoCapability IoCap;

		bool GetOobPresent() const;
		void SetOobPresent(const bool value);
		__declspec(property(get = GetOobPresent, put = SetOobPresent)) bool OobPresent;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsOobDataRequestParams : public CwclBluetoothMsBlePairParams
	{
		DISABLE_COPY(CwclBluetoothMsOobDataRequestParams);

	private:
		wclBluetoothOobData FOobData;
		
	public:
		CwclBluetoothMsOobDataRequestParams(CwclEvent* const Event);
		
		wclBluetoothOobData GetOobData() const;
		void SetOobData(const wclBluetoothOobData& Value);
		__declspec(property(get = GetOobData, put = SetOobData)) wclBluetoothOobData OobData;
	};

	/* Microsoft BLE pairing specific messages. */

	class CwclBluetoothMsBlePairMessage : public CwclBluetoothRemoteDeviceMessage
	{
		DISABLE_COPY(CwclBluetoothMsBlePairMessage);

	private:
		CwclBluetoothMsBlePairParams* FParams;
		
	protected:
		CwclBluetoothMsBlePairParams* GetParams() const;
		__declspec(property(get = GetParams)) CwclBluetoothMsBlePairParams* Params;
		
	public:
		CwclBluetoothMsBlePairMessage(const unsigned char Id, const __int64 Address,
			CwclBluetoothMsBlePairParams* const Params);
		virtual ~CwclBluetoothMsBlePairMessage();
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBlePinRequestMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsBlePinRequestMessage);
		
	public:
		CwclBluetoothMsBlePinRequestMessage(const __int64 Address,
			CwclBluetoothMsBlePinRequestParams* const Params);
		
		void SetPin(const tstring& Pin);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBleNumericComparisonMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsBleNumericComparisonMessage);
		
	private:
		unsigned long	FNumber;
		
	public:
		CwclBluetoothMsBleNumericComparisonMessage(const __int64 Address,
			const unsigned long Number, CwclBluetoothMsBleConfirmParams* const Params);
		
		void SetConfirm(const bool Value);
		
		unsigned long GetNumber() const;
		__declspec(property(get = GetNumber)) unsigned long Number;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBlePasskeyRequestMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsBlePasskeyRequestMessage);
		
	public:
		CwclBluetoothMsBlePasskeyRequestMessage(const __int64 Address,
			CwclBluetoothMsBlePasskeyRequestParams* const Params);
		
		void SetPasskey(const unsigned long Passkey);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBleConfirmOnlyMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsBleConfirmOnlyMessage);
		
	public:
		CwclBluetoothMsBleConfirmOnlyMessage(const __int64 Address,
			CwclBluetoothMsBleConfirmParams* const Params);
		
		void SetConfirm(const bool Value);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsBleProtectionRequestMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsBleProtectionRequestMessage);
		
	public:
		CwclBluetoothMsBleProtectionRequestMessage(const __int64 Address,
			CwclBluetoothMsBleProtectionRequestParams* const Params);
		
		void SetProtection(const wclBluetoothLeProtectionLevel Value);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsIoCapRequestMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsIoCapRequestMessage);
		
	public:
		CwclBluetoothMsIoCapRequestMessage(const __int64 Address,
			CwclBluetoothMsIoCapRequestParams* const Params);
		
		void SetIoCaps(const wclBluetoothMitmProtection Mitm,
			const wclBluetoothIoCapability Cap, const bool Oob);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothMsOobDataRequestMessage : public CwclBluetoothMsBlePairMessage
	{
		DISABLE_COPY(CwclBluetoothMsOobDataRequestMessage);

	public:
		CwclBluetoothMsOobDataRequestMessage(const __int64 Address,
			CwclBluetoothMsOobDataRequestParams* const Params);
		
		void SetOobData(const wclBluetoothOobData& Value);
	};

	/* Silicon Labs BLED112 messages. */

	class CwclBluetoothBled112Message : public CwclBluetoothMessage
	{
		DISABLE_COPY(CwclBluetoothBled112Message);
		
	private:
		tstring	FPort;
		
	public:
		CwclBluetoothBled112Message(const unsigned char Id, const tstring& Port);
		
		tstring GetPort() const;
		__declspec(property(get = GetPort)) tstring Port;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothBled112DisconnectMessage : public CwclBluetoothBled112Message
	{
		DISABLE_COPY(CwclBluetoothBled112DisconnectMessage);
		
	private:
		int	FReason;
		
	public:
		CwclBluetoothBled112DisconnectMessage(const tstring& Port, const int Reason);
		
		int GetReason() const;
		__declspec(property(get = GetReason)) int Reason;
	};

	/* Wii Remote Messages. */
		
	class CwclWiiRemoteMessage : public CwclWiiRemoteCategoryMessage
	{
		DISABLE_COPY(CwclWiiRemoteMessage);
		
	public:
		CwclWiiRemoteMessage(const unsigned char Id);
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteButtonsChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteButtonsChangedMessage);
		
	private:
		wclWiiRemoteButtons FButtons;
		
	public:
		CwclWiiRemoteButtonsChangedMessage(const wclWiiRemoteButtons& Buttons);
		
		wclWiiRemoteButtons GetButtons() const;
		__declspec(property(get = GetButtons)) wclWiiRemoteButtons Buttons;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteAccelChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteAccelChangedMessage);
		
	private:
		wclWiiRemoteAccel FAccel;
		
	public:
		CwclWiiRemoteAccelChangedMessage(const wclWiiRemoteAccel& Accel);
		
		wclWiiRemoteAccel GetAccel() const;
		__declspec(property(get = GetAccel)) wclWiiRemoteAccel Accel;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteIrChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteIrChangedMessage);
		
	private:
		wclWiiRemoteIrSensors FIr;
		
	public:
		CwclWiiRemoteIrChangedMessage(const wclWiiRemoteIrSensors& Ir);
		
		wclWiiRemoteIrSensors GetIr() const;
		__declspec(property(get = GetIr)) wclWiiRemoteIrSensors Ir;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteNunchukChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteNunchukChangedMessage);
		
	private:
		wclWiiRemoteNunchuk FNunchuk;
		
	public:
		CwclWiiRemoteNunchukChangedMessage(const wclWiiRemoteNunchuk& Nunchuk);
		
		wclWiiRemoteNunchuk GetNunchuk() const;
		__declspec(property(get = GetNunchuk)) wclWiiRemoteNunchuk Nunchuk;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteClassicControllerChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteClassicControllerChangedMessage);
		
	private:
		wclWiiRemoteClassicController FController;
		
	public:
		CwclWiiRemoteClassicControllerChangedMessage(
			const wclWiiRemoteClassicController& Controller);
		
		wclWiiRemoteClassicController GetController() const;
		__declspec(property(get = GetController)) wclWiiRemoteClassicController Controller;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteGuitarChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteGuitarChangedMessage);
		
	private:
		wclWiiRemoteGuitar FGuitar;

	public:
		CwclWiiRemoteGuitarChangedMessage(const wclWiiRemoteGuitar& Guitar);
		
		wclWiiRemoteGuitar GetGuitar() const;
		__declspec(property(get = GetGuitar)) wclWiiRemoteGuitar Guitar;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteDrumsChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteDrumsChangedMessage);

	private:
		wclWiiRemoteDrums FDrums;
		
	public:
		CwclWiiRemoteDrumsChangedMessage(const wclWiiRemoteDrums& Drums);
		
		wclWiiRemoteDrums GetDrums() const;
		__declspec(property(get = GetDrums)) wclWiiRemoteDrums Drums;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteBalanceBoardChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteBalanceBoardChangedMessage);
		
	private:
		wclWiiRemoteBalanceBoard FBoard;
		
	public:
		CwclWiiRemoteBalanceBoardChangedMessage(const wclWiiRemoteBalanceBoard& Board);
		
		wclWiiRemoteBalanceBoard GetBoard() const;
		__declspec(property(get = GetBoard)) wclWiiRemoteBalanceBoard Board;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteStatusChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteStatusChangedMessage);
		
	private:
		double				FBatt;
		wclWiiRemoteLeds	FLeds;
		
	public:
		CwclWiiRemoteStatusChangedMessage(const double Batt, const wclWiiRemoteLeds& Leds);
		
		double GetBatt() const;
		__declspec(property(get = GetBatt)) double Batt;

		wclWiiRemoteLeds GetLeds() const;
		__declspec(property(get = GetLeds)) wclWiiRemoteLeds Leds;
	};

	// -----------------------------------------------------------------------------------------

	class CwclWiiRemoteExtensionStateChangedMessage : public CwclWiiRemoteMessage
	{
		DISABLE_COPY(CwclWiiRemoteExtensionStateChangedMessage);
		
	private:
		bool FAttached;
		
	public:
		CwclWiiRemoteExtensionStateChangedMessage(const bool Attached);
		
		bool GetAttached() const;
		__declspec(property(get = GetAttached)) bool Attached;
	};

	/* Bluetooth LE Sniffer messages. */

	class CwclBluetoothLeSnifferMessage : public CwclBluetoothCategoryMessage
	{
	public:
		CwclBluetoothLeSnifferMessage(const unsigned char Id);
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferDeviceDisconnectedMessage : public CwclBluetoothLeSnifferMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferDeviceDisconnectedMessage);
		
	public:
		CwclBluetoothLeSnifferDeviceDisconnectedMessage();
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferRawPacketReceivedMessage : public CwclBluetoothLeSnifferMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferRawPacketReceivedMessage);
		
	private:
		wclBluetoothLePacketHeader	FHeader;
		unsigned char*	FPayload;
		unsigned short	FSize;
		
	public:
		CwclBluetoothLeSnifferRawPacketReceivedMessage(const wclBluetoothLePacketHeader& Header,
			const unsigned char* const Payload, const unsigned short Size);
		virtual ~CwclBluetoothLeSnifferRawPacketReceivedMessage();

		wclBluetoothLePacketHeader GetHeader() const;
		__declspec(property(get = GetHeader)) wclBluetoothLePacketHeader Header;

		unsigned char* GetPayload() const;
		__declspec(property(get = GetPayload)) unsigned char* Payload;
		
		unsigned short GetSize() const;
		__declspec(property(get = GetSize)) unsigned short Size;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferAdvertisingPacketReceivedMessage : public CwclBluetoothLeSnifferMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferAdvertisingPacketReceivedMessage);
		
	private:
		wclBluetoothLeAdvertisingPduHeader	FPduHeader;
		
	public:
		CwclBluetoothLeSnifferAdvertisingPacketReceivedMessage(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader);

		wclBluetoothLeAdvertisingPduHeader GetPduHeader() const;
		__declspec(property(get = GetPduHeader)) wclBluetoothLeAdvertisingPduHeader PduHeader;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferAdvertisingAddressMessage : public CwclBluetoothLeSnifferAdvertisingPacketReceivedMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferAdvertisingAddressMessage);
		
	private:
		__int64	FAddress;

	public:
		CwclBluetoothLeSnifferAdvertisingAddressMessage(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader, const __int64 Address);

		__int64 GetAddress() const;
		__declspec(property(get = GetAddress)) __int64 Address;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferAdvertisingTwoAddressMessage : public CwclBluetoothLeSnifferAdvertisingAddressMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferAdvertisingTwoAddressMessage);
		
	private:
		__int64	FTargetAddress;

	public:
		CwclBluetoothLeSnifferAdvertisingTwoAddressMessage(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader, const __int64 Address,
			const __int64 TargetAddress);

		__int64 GetTargetAddress() const;
		__declspec(property(get = GetTargetAddress)) __int64 TargetAddress;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferAdvertisingDataMessage : public CwclBluetoothLeSnifferAdvertisingAddressMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferAdvertisingDataMessage);
		
	private:
		unsigned char*	FData;
		unsigned char	FLen;
		
	public:
		CwclBluetoothLeSnifferAdvertisingDataMessage(const unsigned char Id,
			const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 Address, const unsigned char* const Data,
			const unsigned char Len);
		virtual ~CwclBluetoothLeSnifferAdvertisingDataMessage();

 		unsigned char* GetData() const;
		__declspec(property(get = GetData)) unsigned char* Data;
		
		unsigned char GetLen() const;
		__declspec(property(get = GetLen)) unsigned char Len;
	};

	// -----------------------------------------------------------------------------------------

	class CwclBluetoothLeSnifferAdvertisingConnectIndReceivedMessage : public CwclBluetoothLeSnifferAdvertisingTwoAddressMessage
	{
		DISABLE_COPY(CwclBluetoothLeSnifferAdvertisingConnectIndReceivedMessage);
		
	private:
		wclBleSnifferLlData	FLlData;
		
	public:
		CwclBluetoothLeSnifferAdvertisingConnectIndReceivedMessage(
			const wclBluetoothLeAdvertisingPduHeader& PduHeader,
			const __int64 Address, const __int64 TargetAddress,
			const wclBleSnifferLlData& LlData);

		wclBleSnifferLlData GetLlData() const;
		__declspec(property(get = GetLlData)) wclBleSnifferLlData LlData;
	};
}