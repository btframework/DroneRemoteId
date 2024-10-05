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

#include "wclHelpers.h"

namespace wclCommon
{
	/// <summary> Operating System type. </summary>
	typedef enum
	{
		/// <summary> Unknown OS. </summary>
		osUnknown = 0,
		/// <summary> Mac OS. </summary>
		osMacOS = 1,
		/// <summary> Windows XP. </summary>
		osWinXP = 2,
		/// <summary> Windows Vista. </summary>
		osWinVista = 3,
		/// <summary> Windows 7. </summary>
		osWin7 = 4,
		/// <summary> Windows 8. </summary>
		osWin8 = 5,
		/// <summary> Windows 8.1. </summary>
		osWin81 = 6,
		/// <summary> Windows 10. </summary>
		osWin10 = 7,
		/// <summary> Windows 11. </summary>
		osWin11 = 8
	} wclOsType;

	/// <summary> The class provides information about OS version. </summary>
	class CwclOsVersion
	{
		DISABLE_COPY(CwclOsVersion);

	private:
		bool			FIsWinIot;
		wclOsType		FOsType;
		unsigned short	FOsBuild;
		unsigned short	FOsMajor;
		unsigned short	FOsMinor;
		
		void ReadIsWinIot();
		void CheckWin10orAbove();
		void ReadOsVersion();

	public:
		/// <summary> Creates new object of the version reading class. </summary>
		CwclOsVersion();
		
		/// <summary> Checks if software runs on Windows 10 IoT. </summary>
		/// <returns> The function returns <c>true</c> if it runs on Windows 10 IoT.
		///   Otherwise returns <c>false</c>. </returns>
		bool GetIsWinIot() const;
		/// <summary> Checks if software runs on Windows 10 IoT. </summary>
		/// <value> The function returns <c>true</c> if it runs on Windows 10 IoT.
		///   Otherwise returns <c>false</c>. </value>
		__declspec(property(get = GetIsWinIot)) bool IsWinIot;

		/// <summary> Gets OS type. </summary>
		/// <returns> The OS type. </returns>
		/// <seealso cref="wclOsType" />
		wclOsType GetOsType() const;
		/// <summary> Gets OS type. </summary>
		/// <value> The OS type. </value>
		/// <seealso cref="wclOsType" />
		__declspec(property(get = GetOsType)) wclOsType OsType;

		/// <summary> Gets the OS build number. </summary>
		/// <returns> The OS build number. </returns>
		/// <remarks> <para> For Win 10 <c>Build</c> can be translated to OS version
		///   (release) using the table below. </para>
		///   <para><c> Build </c> <c> Release </c></para>
		///   <para><c>=======</c> <c>=========</c></para>
		///   <para><c> 10240 </c> <c>   1507  </c></para>
		///   <para><c> 10586 </c> <c>   1511  </c></para>
		///   <para><c> 14393 </c> <c>   1607  </c></para>
		///   <para><c> 15063 </c> <c>   1703  </c></para>
		///   <para><c> 16299 </c> <c>   1709  </c></para>
		///   <para><c> 17134 </c> <c>   1803  </c></para>
		///   <para><c> 17763 </c> <c>   1809  </c></para>
		///   <para><c> 18362 </c> <c>   1903  </c></para>
		///   <para><c> 18363 </c> <c>   1909  </c></para>
		///   <para><c> 19041 </c> <c>   2004  </c></para>
		///   <para><c> 19042 </c> <c>   20H2  </c></para>
		///   <para><c> 19043 </c> <c>   21H1  </c></para>
		///   <para><c> 19044 </c> <c>   21H2  </c></para>
		///   <para><c> 19045 </c> <c>   22H2  </c></para>
		///   <para></para>
		/// <para> For Win 11 <c>Build</c> can be translated to OS version
		///   (release) using the table below. </para>
		///   <para><c> Build </c> <c> Release </c></para>
		///   <para><c>=======</c> <c>=========</c></para>
		///   <para><c> 22000 </c> <c>   21H2  </c></para>
		///   <para><c> 22621 </c> <c>   22H2  </c></para>
		///   <para><c> 22631 </c> <c>   23H2  </c></para>
		///   <para><c> 26100 </c> <c>   24H2  </c></para>
		///   <para></para>
		/// <para> For Mac OS check the <c>OsMajor</c> and <c>OsMinor</c>
		///   numbers. </para> </remarks>
		unsigned short GetOsBuild() const;
		/// <remarks> <para> For Win 10 <c>Build</c> can be translated to OS version
		///   (release) using the table below. </para>
		///   <para><c> Build </c> <c> Release </c></para>
		///   <para><c>=======</c> <c>=========</c></para>
		///   <para><c> 10240 </c> <c>   1507  </c></para>
		///   <para><c> 10586 </c> <c>   1511  </c></para>
		///   <para><c> 14393 </c> <c>   1607  </c></para>
		///   <para><c> 15063 </c> <c>   1703  </c></para>
		///   <para><c> 16299 </c> <c>   1709  </c></para>
		///   <para><c> 17134 </c> <c>   1803  </c></para>
		///   <para><c> 17763 </c> <c>   1809  </c></para>
		///   <para><c> 18362 </c> <c>   1903  </c></para>
		///   <para><c> 18363 </c> <c>   1909  </c></para>
		///   <para><c> 19041 </c> <c>   2004  </c></para>
		///   <para><c> 19042 </c> <c>   20H2  </c></para>
		///   <para><c> 19043 </c> <c>   21H1  </c></para>
		///   <para><c> 19044 </c> <c>   21H2  </c></para>
		///   <para><c> 19045 </c> <c>   22H2  </c></para>
		///   <para></para>
		/// <para> For Win 11 <c>Build</c> can be translated to OS version
		///   (release) using the table below. </para>
		///   <para><c> Build </c> <c> Release </c></para>
		///   <para><c>=======</c> <c>=========</c></para>
		///   <para><c> 22000 </c> <c>   21H2  </c></para>
		///   <para><c> 22621 </c> <c>   22H2  </c></para>
		///   <para><c> 22631 </c> <c>   23H2  </c></para>
		///   <para><c> 26100 </c> <c>   24H2  </c></para>
		///   <para></para>
		/// <para> For Mac OS check the <c>OsMajor</c> and <c>OsMinor</c>
		///   numbers. </para> </remarks>
		__declspec(property(get = GetOsBuild)) unsigned short OsBuild;

		/// <summary> Gets the OS major version. </summary>
		/// <returns> The OS major version. </returns>
		/// <remarks> For Mac OS this is the OS version </remarks>
		unsigned short GetOsMajor() const;
		/// <summary> Gets the OS major version. </summary>
		/// <value> The OS major version. </value>
		/// <remarks> For Mac OS this is the OS version </remarks>
		__declspec(property(get = GetOsMajor)) unsigned short OsMajor;

		/// <summary> Get the OS minor version. </summary>
		/// <returns> The OS minor version. </returns>
		unsigned short GetOsMinor() const;
		/// <summary> Get the OS minor version. </summary>
		/// <value> The OS minor version. </value>
		__declspec(property(get = GetOsMinor)) unsigned short OsMinor;
	};

	/// <summary> Global instance of the OS version reader class. </summary>
	extern CwclOsVersion wclOsVersion;
}