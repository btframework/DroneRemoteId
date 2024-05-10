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

namespace wclCommon
{
	namespace WinUsb
	{
		// Helper class represents a WinUSB device.
		class CwclWinUsbDevice
		{
			DISABLE_COPY(CwclWinUsbDevice);
			
		private:
			RTL_CRITICAL_SECTION	FCS;
			tstring					FDevicePath;
			HANDLE					FDevHandle;
			HANDLE					FUsbHandle;
			
		protected:
			void Enter();
			void Leave();
			
		public:
			CwclWinUsbDevice();
			virtual ~CwclWinUsbDevice();
			
			int Close();
			int Open(const tstring& DevicePath);
			
			int ConstrolTranser(const unsigned char RequestType,
				const unsigned char Request, const unsigned short Value,
				const unsigned short Index, const unsigned short Length,
				void* const Data, unsigned long& Transferred);
			int ReadPipe(const unsigned char PipeId, void* const Data,
				const unsigned long Length, unsigned long& Received);
			
			bool GetActive();
			__declspec(property(get = GetActive)) bool Active;

			tstring GetDevicePath();
			__declspec(property(get = GetDevicePath)) tstring DevicePath;
		};
	}
}