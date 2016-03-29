   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//
#ifndef __MEMORY_MOCK_HPP__
#define __MEMORY_MOCK_HPP__

#if CHAR_BIT != 8
#error "This platform does not support 8-bit character size."
#endif

class MemoryMock{
private:
	void* ViewPtr;
	string MemoryFile;
	HANDLE mFile, mFileMappingObject;

public:
	/* constructor */
	MemoryMock(size_t MemorySize, 
		       const string& File) :
			   MemoryFile(File){
			   /* */
			   mFile = CreateFileA(MemoryFile.c_str(),             // path of the file
								   GENERIC_READ | GENERIC_WRITE,   // allow access to read or write
								   FILE_SHARE_READ,				   // share fole to read
								   NULL,						   // no security attributes
								   CREATE_ALWAYS,				   // open the existing file
								   FILE_ATTRIBUTE_NORMAL,		   // default attribute
								   NULL);

			if(mFile == NULL){
				throw string("Unable to call CreateFileA()");
			}					

			mFileMappingObject = CreateFileMapping(mFile,			  				// File handle
												   NULL,			  				// default security
												   PAGE_READWRITE,    				// allow memory read-write permission
												   0,								// maximum object size (high-order DWORD)
												   static_cast<DWORD>(MemorySize),  // maximum object size (low-order DWORD)
												   NULL);							// no name for the mapping object


			if(mFileMappingObject == NULL){
				CloseHandle(mFile);
				throw string("Unable to call CreateFileMapping()");
			}

			ViewPtr = MapViewOfFile(mFileMappingObject,		// the file Mapping object handler
									FILE_MAP_WRITE,			// to map a read-write view of the file
									0,						// A high-order DWORD of the file offset where the view begins
									0,						// A low-order DWORD of the file offset where the view is to begin
									0); 					// no of bytes to map to the view, here 0 means all the bytes of the file

			if(ViewPtr == NULL){
				CloseHandle(mFileMappingObject);
				CloseHandle(mFile);
				throw string("Unable to call MapViewOfFile()");
			}
		}

	/* returns the file name */
	string GetFileName() const{
		return MemoryFile;
	}

	/* returns a pointer to the mapped memory */
	unsigned char* GetMemory() const{
		return static_cast<unsigned char*>(ViewPtr);
	}

	/* destructor */
	~MemoryMock(){
		UnmapViewOfFile(ViewPtr);
		CloseHandle(mFileMappingObject);
		CloseHandle(mFile);
	}
};

#endif
