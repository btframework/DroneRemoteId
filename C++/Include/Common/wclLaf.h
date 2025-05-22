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

#include "wclHelpers.h"
#include "wclSync.h"

using namespace std;

using namespace wclSync;

namespace wclLaf
{
	/// <summary> The Limited Access Feature (LAF) Manager class. </summary>
	/// <remarks> The LAF Manager allows to work with the Limited Access
	///   Features. </remarks>
	class CwclLafManager
	{
		DISABLE_COPY(CwclLafManager);
		
	private:
		bool					FActive;
		CwclCriticalSection*	FCS;
		
		CwclManualResetEvent*	FInitEvent;
		int						FInitResult;
		CwclManualResetEvent*	FTermEvent;
		HANDLE					FThread;
		
		static UINT __stdcall _WinRtThread(LPVOID Param);
		void WinRtThread();

		
	public:
		/// <summary> Creates new LAF manager object. </summary>
		CwclLafManager();
		/// <summary> Closes the LAF manager and releases all allocated
		///   resources. </summary>
		virtual ~CwclLafManager();
		
		/// <summary> Closes the LAF manager and releases all allocated
		///   resources. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Close();
		/// <summary> Opens the LAF manager. </summary>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Open();
		
		/// <summary> Enumerates available LAF. </summary>
		/// <param name="Laf"> The list that will be fulfilled with found
		///   LAF. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Enum(list<tstring>& Laf);
		/// <summary> Gets the application LAF identity details. </summary>
		/// <param name="Pfn"> If the method completed with success on output
		///   contains the LAF identity Package Full Name (PFN). </param>
		/// <param name="AppName"> If the method completed with success on output
		///   contains the LAF identity application name. </param>
		/// <param name="Publisher"> If the method completed with success on
		///   output contains the LAF identity publisher ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int GetIdentity(tstring& Pfnm, tstring& AppName, tstring& Publisher);
		
		/// <summary> Unlocks the specified LAF. </summary>
		/// <param name="Laf"> The Limited Access Feature ID. </param>
		/// <returns> If the function succeed the return value is
		///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
		///   the WCL error codes. </returns>
		int Unlock(const tstring& Laf);
		
		/// <summary> Gets the LAF manager state. </summary>
		/// <returns> <c>True</c> if the LAF manager is opened. <c>False</c> if the
		///   LAF manager is closed. </returns>
		bool GetActive() const;
		/// <summary> Gets the LAF manager state. </summary>
		/// <value> <c>True</c> if the LAF manager is opened. <c>False</c> if the
		///   LAF manager is closed. </value>
		__declspec(property(get = GetActive)) bool Active;
	};
}