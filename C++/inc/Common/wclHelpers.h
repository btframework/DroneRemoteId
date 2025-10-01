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

#include <string>

#include <windows.h>

namespace wclCommon
{
	/// <summary> Defines the string type as UNICODE string. </summary>
	typedef std::wstring tstring;

	/// <summary> The macro disable the copy constructor of a class. </summary>
	#define DISABLE_COPY(Class) \
		private: Class(const Class&); Class& \
		operator=(const Class&)

	/// <summary> The common event handler prototype. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	#define wclNotifyEvent(_event_name_) \
		__event void _event_name_(void* Sender)

	/// <summary> Converts UTF8 string to WCL string. </summary>
	/// <param name="lpszUTF8"> UTF8 encoded string. </param>
	/// <param name="Len"> The UTF8 encoded string length. </param>
	/// <returns> WCL (UNICODE) string. </returns>
	tstring wclUTF8Decode(const PCHAR lpszUTF8, const DWORD Len);
	/// <summary> Converts UTF8 string to WCL string. </summary>
	/// <param name="lpszUTF8"> UTF8 encoding string. </param>
	/// <returns> WCL (UNICODE) string. </returns>
	tstring wclUTF8Decode(const PCHAR lpszUTF8);

	/// <summary> Converts WCL (UNICODE) string to UTF8 encoded string. </summary>
	/// <param name="str"> WCL string that should be converted to UTF8. </param>
	/// <param name="lpszUTF8"> Pointer to a buffer that receives UTF8 encoded string. </param>
	/// <param name="dwUTF8Len"> Size of UTF8 buffer. </param>
	void wclUTF8Encode(const tstring& str, const PCHAR lpszUTF8,
		const DWORD dwUTF8Len);

	/// <summary> Converts UNICODE string to ANSI string. </summary>
	/// <param name="s"> The UNICODE string. </param>
	/// <returns> The ANSI string. </returns>
	std::string wclUnicodeToAnsi(const std::wstring& s);

	/// <summary> Converts ANSI string to UNICODE string. </summary>
	/// <param name="s"> The ANSI string. </param>
	/// <returns> The UNICODE string. </returns>
	std::wstring wclAnsiToUnicode(const std::string& s);

	/// <summary> Stream origins. </summary>
	typedef enum
	{
		/// <summary> From stream beginning. </summary>
		soBeginning,
		/// <summary> From current position. </summary>
		soCurrent,
		/// <summary> From stream end. </summary>
		soEnd
	} wclSeekOrigin;

	/// <summary> The base class for WCL streams. </summary>
	class CwclStream
	{
		DISABLE_COPY(CwclStream);
		
	public:
		/// <summary> Creates new stream object. </summary>
		CwclStream();
		/// <summary> Frees the stream object. </summary>
		virtual ~CwclStream();

		/// <summary> Reads from stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to read. </param>
		/// <returns> Number of read bytes. </returns>
		virtual unsigned long Read(void* const Buffer, const unsigned long Count) = 0;
		/// <summary> Writes to the stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to write. </param>
		/// <returns> Number of written bytes. </returns>
		virtual unsigned long Write(const void* const Buffer,
			const unsigned long Count) = 0;
		/// <summary> Changes current position. </summary>
		/// <param name="Offset"> The offset. </param>
		/// <param name="Origin"> Seek origin. </param>
		/// <returns> Current position. </returns>
		/// <seealso cref="wclSeekOrigin" />
		virtual unsigned long Seek(const long Offset, const wclSeekOrigin Origin) = 0;
		/// <summary> Copies data from other stream. </summary>
		/// <param name="Source"> The source stream. </param>
		/// <param name="Count"> Amount of bytes to copy. </param>
		/// <seealso cref="CwclStream" />
		unsigned long CopyFrom(CwclStream* const Source,
			unsigned long Count);
		
		/// <summary> Gets the stream size. </summary>
		/// <returns> The current stream size. </returns>
		unsigned long GetSize();
		/// <summary> Sets the stream size. </summary>
		/// <param name="NewSize"> The new stream size. </param>
		virtual void SetSize(const unsigned long NewSize) = 0;
		
		/// <summary> Gets the current position. </summary>
		/// <returns> The current position. </returns>
		unsigned long GetPosition();
		/// <summary> Sets the current position. </summary>
		/// <param name="Pos"> The new position. </param>
		void SetPosition(const unsigned long Pos);
	};

	/// <summary> The base class for handle based streams. </summary>
	/// <seealso cref="CwclStream" />
	class CwclHandleStream : public CwclStream
	{
		DISABLE_COPY(CwclHandleStream);
		
	protected:
		HANDLE	FHandle;

	public:	
		/// <summary> Creates new stream. </summary>
		CwclHandleStream();
		/// <summary> Frees the stream object. </summary>
		virtual ~CwclHandleStream();

		/// <summary> Sets the stream size. </summary>
		/// <param name="NewSize"> The new stream size. </param>
		virtual void SetSize(const unsigned long NewSize) override;
		
		/// <summary> Reads from stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to read. </param>
		/// <returns> Number of read bytes. </returns>
		virtual unsigned long Read(void* const Buffer, const unsigned long Count) override;
		/// <summary> Writes to the stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to write. </param>
		/// <returns> Number of written bytes. </returns>
		virtual unsigned long Write(const void* const Buffer,
			const unsigned long Count) override;
		/// <summary> Changes current position. </summary>
		/// <param name="Offset"> The offset. </param>
		/// <param name="Origin"> Seek origin. </param>
		/// <returns> Current position. </returns>
		/// <seealso cref="wclSeekOrigin" />
		virtual unsigned long Seek(const long Offset,
			const wclSeekOrigin Origin) override;

		/// <summary> Gets the handle. </summary>
		/// <returns> The handle. </returns>
		HANDLE GetHandle() const;
	};

	/// <summary> The class represents a file stream. </summary>
	/// <seealso cref="CwclHandleStream" />
	class CwclFileStream : public CwclHandleStream
	{
		DISABLE_COPY(CwclFileStream);
		
	public:
		/// <summary> Creates new file stream object. </summary>
		/// <param name="FileName"> The file name. </param>
		/// <param name="CreationDisposition"> An action to take on a file or device that exists
		///   or does not exist. </param>
		/// <param name="DesiredAccess"> The requested access to the file or device, which can be
		///   summarized as read, write, both or neither zero). </param>
		/// <param name="ShareMode"> The requested sharing mode of the file or device, which
		///   can be read, write, both, delete, all of these, or none (refer to the following table).
		///   Access requests to attributes or extended attributes are not affected by this
		///   flag. </param>
		/// <remarks> If the open or create file failed the <see cref="wclEFileOpenFailed" />
		///   exception raises. </remarks>
		/// <exception cref="wclEFileOpenFailed"></exception>
		CwclFileStream(const tstring& FileName, const unsigned long CreationDisposition,
			const unsigned long DesiredAccess, const unsigned long ShareMode);
		/// <summary> Frees the file. </summary>
		virtual ~CwclFileStream();
	};

	// Forward declaration.
	class CwclMemoryStream;

	/// <summary> The base class for memory streams. </summary>
	/// <seealso cref="CwclStream" />
	class CwclCustomMemoryStream : public CwclStream
	{
		DISABLE_COPY(CwclCustomMemoryStream);

	private:
		friend class CwclMemoryStream;

		void*			FMemory;
		unsigned long	FSize;
		unsigned long	FPosition;

	protected:
		/// <summary> Sets new memory pointer and size. </summary>
		/// <param name="Ptr"> The new pointer. </param>
		/// <param name="Size"> The new size. </param>
		void SetPointer(void* const Ptr, const unsigned long Size);

	public:
		/// <summary> Creates new memory stream. </summary>
		CwclCustomMemoryStream();
		/// <summary> Frees the stream. </summary>
		virtual ~CwclCustomMemoryStream();

		/// <summary> Reads from stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to read. </param>
		/// <returns> Number of read bytes. </returns>
		virtual unsigned long Read(void* const Buffer,
			const unsigned long Count) override;
		/// <summary> Changes current position. </summary>
		/// <param name="Offset"> The offset. </param>
		/// <param name="Origin"> Seek origin. </param>
		/// <returns> Current position. </returns>
		/// <seealso cref="wclSeekOrigin" />
		virtual unsigned long Seek(const long Offset,
			const wclSeekOrigin Origin) override;
		/// <summary> Saves the data into the stream. </summary>
		/// <param name="Stream"> The stream object. </param>
		/// <seealso cref="CwclStream" />
		void SaveToStream(CwclStream* const Stream);
		
		/// <summary> Gets the pointer to the memory used by the stream. </summary>
		/// <returns> The pointer to the memory. </returns>
		void* GetMemory() const;
	};

	/// <summary> The memory stream. </summary>
	/// <seealso cref="CwclCustomMemoryStream" />
	class CwclMemoryStream : public CwclCustomMemoryStream
	{
		DISABLE_COPY(CwclMemoryStream);
		
	private:
		unsigned long	FCapacity;
		
	protected:
		/// <summary> Reallocates memory. </summary>
		/// <param name="NewCapacity"> New capacity. </param>
		virtual void* Realloc(unsigned long& NewCapacity);
		
		/// <summary> Sets the stream capacity. </summary>
		/// <param name="NewCapacity"> New capacity. </param>
		void SetCapacity(unsigned long NewCapacity);
		/// <summary> Gets the stream capacity. </summary>
		/// <returns> The stream capacity. </returns>
		unsigned long GetCapacity() const;

	public:
		/// <summary> Creates new memory stream. </summary>
		CwclMemoryStream();
		/// <summary> Frees the stream. </summary>
		virtual ~CwclMemoryStream();

		/// <summary> Clears the memory. </summary>
		void Clear();
		/// <summary> Loads data from stream. </summary>
		/// <param name="Stream"> The source stream. </param>
		/// <seealso cref="CwclStream" />
		void LoadFromStream(CwclStream* const Stream);
		/// <summary> Sets the stream size. </summary>
		/// <param name="NewSize"> The new stream size. </param>
		virtual void SetSize(const unsigned long NewSize) override;
		/// <summary> Writes to the stream. </summary>
		/// <param name="Buffer"> The pointer to the memory buffer. </param>
		/// <param name="Count"> Amount of bytes to write. </param>
		/// <returns> Number of written bytes. </returns>
		virtual unsigned long Write(const void* const Buffer,
			const unsigned long Count) override;
	};

	/// <summary> The enumeration indicates whether a stream object should be
	///   freed by the object that uses it. </summary>
	typedef enum
	{
		/// <summary> The stream is an independent object with a different Owner.
		///   The object that uses the stream does not free it when it is
		///   destroyed. </summary>
		soReference,
		/// <summary> The stream is owned by the object that uses it (and exists solely
		///   for that object). The object that uses the stream frees the associated
		///   stream when it no longer needs to use the stream. </summary>
		soOwned
	} wclStreamOwnership;

	/// <summary> The class implements the <c>IStream</c> interface on a
	///   <see cref="CwclStream" /> object. </summary>
	class CwclStreamAdapter : public IStream
	{
		DISABLE_COPY(CwclStreamAdapter);

	private:
		CwclStream*			FStream;
		wclStreamOwnership	FOwnership;

		LONG				FRefCount;

	public:
		/* IUnknown */	
		
		/// <summary> Queries a COM object for a pointer to one of its interface; identifying
		///   the interface by a reference to its interface identifier (IID). If the COM object
		///   implements the interface, then it returns a pointer to that interface after calling 
		///   <c>AddRef</c> on it. </summary>
		/// <param name="riid"> A reference to the interface identifier (IID) of the interface
		///   being queried for. </param>
		/// <param name="ppvObject"> The address of a pointer to an interface with the IID specified
		///   in the <c>riid</c> parameter. Because you pass the address of an interface pointer, the
		///   method can overwrite that address with the pointer to the interface being queried for.
		///   Upon successful return, <c>*ppvObject</c> (the dereferenced address) contains a pointer to
		///   the requested interface. If the object doesn't support the interface, the method sets
		///   <c>*ppvObject</c> (the dereferenced address) to <c>NULL</c>. </param>
		/// <returns> This method returns <c>S_OK</c> if the interface is supported, and
		///   <c>E_NOINTERFACE</c> otherwise. If <c>ppvObject</c> (the address) is <c>NULL</c>,
		///   then this method returns <c>E_POINTER</c>. </returns>
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
		/// <summary> Increments the reference count for an interface pointer to a COM object.
		///   You should call this method whenever you make a copy of an interface pointer </summary>
		/// <returns> The method returns the new reference count. This value is intended to be used
		///   only for test purposes. </returns>
		virtual ULONG STDMETHODCALLTYPE AddRef() override;
		/// <summary> Decrements the reference count for an interface on a COM object. </summary>
		/// <returns> The method returns the new reference count. This value is intended to be used
		///   only for test purposes. </returns>
		virtual ULONG STDMETHODCALLTYPE Release() override;
		
		/* ISequentialStream */

		/// <summary> The method reads a specified number of bytes from the stream object
		///   into memory, starting at the current seek pointer. </summary>
		/// <param name="pv"> A pointer to the buffer which the stream data is read into. </param>
		/// <param name="cb"> The number of bytes of data to read from the stream object. </param>
		/// <param name="pcbRead"> A pointer to a <c>ULONG</c> variable that receives the actual
		///   number of bytes read from the stream object. <c>Note:</c> The number of bytes read may
		///   be zero. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Read(void *pv, ULONG cb, ULONG *pcbRead) override;
		/// <summary> The method writes a specified number of bytes into the stream object
		///   starting at the current seek pointer. </summary>
		/// <param name="pv"> A pointer to the buffer that contains the data that is to be written
		///   to the stream. A valid pointer must be provided for this parameter even when
		///   <c>cb</c> is zero. </param>
		/// <param name="cb"> The number of bytes of data to attempt to write into the stream.
		///   This value can be zero. </param>
		/// <param name="pcbWritten"> A pointer to a <c>ULONG</c> variable where this method writes
		///   the actual number of bytes written to the stream object. The caller can set this
		///   pointer to <c>NULL</c>, in which case this method does not provide the actual number of
		///   bytes written. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Write(const void *pv, ULONG cb, ULONG *pcbWritten) override;

		/* IStream */

		/// <summary> The method changes the seek pointer to a new location. The new location is
		///   relative to either the beginning of the stream, the end of the stream, or the current
		///   seek pointer. </summary>
		/// <param name="dlibMove"> The displacement to be added to the location indicated by the
		///   <c>dwOrigin</c> parameter. If <c>dwOrigin</c> is <c>STREAM_SEEK_SET</c>, this is
		///   interpreted as an unsigned value rather than a signed value. </param>
		/// <param name="dwOrigin"> The origin for the displacement specified in <c>dlibMove</c>. The
		///   origin can be the beginning of the file (<c>STREAM_SEEK_SET</c>), the current seek pointer
		///   (<c>STREAM_SEEK_CUR</c>), or the end of the file (<c>STREAM_SEEK_END</c>). </param>
		/// <param name="plibNewPosition"> A pointer to the location where this method writes the value
		///   of the new seek pointer from the beginning of the stream. You can set this pointer to
		///   <c>NULL</c>. In this case, this method does not provide the new seek pointer. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
			ULARGE_INTEGER *plibNewPosition) override;
		/// <summary> The method changes the size of the stream object. </summary>
		/// <param name="libNewSize"> Specifies the new size, in bytes, of the stream. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER libNewSize) override;
		/// <summary> The method copies a specified number of bytes from the current seek
		///   pointer in the stream to the current seek pointer in another stream. </summary>
		/// <param name="pstm"> A pointer to the destination stream. The stream pointed to by <c>pstm</c>
		///   can be a new stream or a clone of the source stream. </param>
		/// <param name="cb"> The number of bytes to copy from the source stream. </param>
		/// <param name="pcbRead"> A pointer to the location where this method writes the actual
		///   number of bytes read from the source. You can set this pointer to <c>NULL</c>. In this case,
		///   this method does not provide the actual number of bytes read. </param>
		/// <param name="pcbWritten"> A pointer to the location where this method writes the actual
		///   number of bytes written to the destination. You can set this pointer to <c>NULL</c>.
		///   In this case, this method does not provide the actual number of bytes written. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE CopyTo(IStream *pstm, ULARGE_INTEGER cb,
			ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten) override;
		/// <summary> The method ensures that any changes made to a stream object open in transacted mode
		///   are reflected in the parent storage. If the stream object is open in direct mode, <c>Commit</c>
		///   has no effect other than flushing all memory buffers to the next-level storage object.
		///   The COM compound file implementation of streams does not support opening streams in transacted
		///   mode. </summary>
		/// <param name="grfCommitFlags"> Controls how the changes for the stream object are committed. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Commit(DWORD grfCommitFlags) override;
		/// <summary> The method discards all changes that have been made to a transacted stream since
		///   the last <c>Commit</c> call. On streams open in direct mode and streams using the COM compound
		///   file implementation of IStream::Revert, this method has no effect. </summary>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Revert() override;
		/// <summary> The method restricts access to a specified range of bytes in the stream. Supporting this
		///   functionality is optional since some file systems do not provide it. </summary>
		/// <param name="libOffset"> Integer that specifies the byte offset for the beginning of the
		///   range. </param>
		/// <param name="cb"> Integer that specifies the length of the range, in bytes, to be
		///   restricted. </param>
		/// <param name="dwLockType"> Specifies the restrictions being requested on accessing the
		///   range. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER libOffset,
			ULARGE_INTEGER cb, DWORD dwLockType) override;
		/// <summary> The method removes the access restriction on a range of bytes previously
		///   restricted with <c>LockRegion</c>. </summary>
		/// <param name="libOffset"> Specifies the byte offset for the beginning of the range. </param>
		/// <param name="cb"> Specifies, in bytes, the length of the range to be restricted. </param>
		/// <param name="dwLockType"> Specifies the access restrictions previously placed on the
		///   range. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER libOffset,
			ULARGE_INTEGER cb, DWORD dwLockType) override;
		/// <summary> The method retrieves the <c>STATSTG</c> structure for this
		///   stream. </summary>
		/// <param name="pstatstg"> Pointer to a <c>STATSTG</c> structure where this method places
		///   information about this stream object. </param>
		/// <param name="grfStatFlag"> Specifies that this method does not return some of the members
		///   in the <c>STATSTG</c> structure, thus saving a memory allocation operation. Values are
		///   taken from the <c>STATFLAG</c> enumeration. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Stat(STATSTG *pstatstg, DWORD grfStatFlag) override;
		/// <summary> The method creates a new stream object with its own seek pointer that
		///   references the same bytes as the original stream. </summary>
		/// <param name="ppstm"> When successful, pointer to the location of an <c>IStream</c> pointer
		///   to the new stream object. If an error occurs, this parameter is <c>NULL</c>. </param>
		/// <returns> <c>S_OK</c> if operation completed with success. </returns>
		virtual HRESULT STDMETHODCALLTYPE Clone(IStream **ppstm) override;

	public:
		/// <summary> Creates new Stream Adapter object. </summary>
		/// <param name="Stream"> The <see cref="CwclStream" /> object that needs to be "converted" to
		///   the <c>IStream</c> interface. If this parameter is <c>NULL</c> the 
		///   <see cref="wclEInvalidArgument" /> exception raises. </param>
		/// <param name="Ownership"> Indicates how the Stream Adapter owns the <c>Stream</c> object. </param>
		/// <seealso cref="CwclStream" />
		/// <seealso cref="wclStreamOwnership" />
		/// <exception cref="wclEInvalidArgument"></exception>
		CwclStreamAdapter(CwclStream* const Stream,
			const wclStreamOwnership Ownership = soReference);
		/// <summary> Frees the Stream Adapter object. </summary>
		virtual ~CwclStreamAdapter();

		/// <summary> Gets the <see cref="CwclStream" /> object that is owned by the Stream
		///   Adapter. </summary>
		/// <returns> The <see cref="CwclStream" /> object. </returns>
		/// <seealso cref="CwclStream" />
		CwclStream* GetStream() const;

		/// <summary> Gets the associated <c>Stream</c> ownership. </summary>
		/// <returns> The current ownership of the associated <c>Stream</c>. </returns>
		/// <seealso cref="wclStreamOwnership" />
		wclStreamOwnership GetStreamOwnership() const;
		/// <summary> Sets the associated <c>Stream</c> ownership. </summary>
		/// <param name="Value"> The new ownership of the associated <c>Stream</c>. </param>
		/// <seealso cref="wclStreamOwnership" />
		void SetStreamOwnership(const wclStreamOwnership Value);
	};
}
