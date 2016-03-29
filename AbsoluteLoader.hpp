   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

#ifndef __ABSOLUTE_LOADER_HPP__
#define __ABSOLUTE_LOADER_HPP__

#include "ADDR_CONVERTER.hpp"
#include "MemoryMock.hpp"
#include "ByteCode.hpp"

typedef vector<string> VS;

class AbsoluteLoader {
private:
	MemoryMock memory;
	int memSize;
	string record, Addr, progLen, text;
	int StartAddr;
	string fileName, memoryName;
	unsigned char* ViewPtr;
	ifstream Inp;
	ofstream Out;

public:
	/* Constructors */
	AbsoluteLoader(int memSize, const string& filename,
				   const string& memoryname) : 
				   	memory(static_cast<size_t>(memSize), memoryname),
				   	memSize(memSize), fileName(filename), 
					memoryName(memoryname) {
				   		Inp.open(filename.c_str(), ifstream::in);
				        if(!Inp.is_open()){
					    throw "Unable to open object file.";
						} 
					}

	AbsoluteLoader(const string& filename, const string&
		           memoryname) : 
					memory(static_cast<size_t>(0x8000), memoryname),
					memSize(0x8000), fileName(filename), 
					memoryName(memoryname) {
						Inp.open(filename.c_str(), ifstream::in);
						if(!Inp.is_open()){
							throw "Unable to open object file.";
						} 
					}

	AbsoluteLoader(const string& memoryname) :
				   memory(static_cast<size_t>(0x8000), memoryname),
				   memSize(0x8000), memoryName(memoryname) {
				   		fileName = "OBJECT.txt";
				   		Inp.open(fileName.c_str(), ifstream::in);
						if(!Inp.is_open()){
							throw "Unable to open object file.";
						} 
				   }	

	/* read the object program from the 
	 * object file */
	void LoadIntoMemory() {	
		ViewPtr = memory.GetMemory();
		if(Inp.is_open()){
			getline(Inp, record);
			if(record[0] == 'H'){
				string progName = record.substr(1,6);
				for(int i=0;i<progName.size();++i) {
					if(progName[i] == ' '){
						progName = progName.substr(0,i);
						break;
					}
				}
			
				if(progName.compare(memoryName)) {
					throw "Invalid program name.";
				}

				Addr = record.substr(7,6);
				StartAddr = toDec(Addr);
				if(StartAddr > memSize) {
					throw "OUT OF MEMORY SPACE...";
				}
				
				progLen = record.substr(13,6);			
				if(toDec(progLen) >= memSize)
					throw "OUT OF MEMORY SPACE...";
			}	
			else
				throw "NO HEADER RECORD...";

			getline(Inp, record);
			
			while(record[0] != 'E'){
				if(record[0] == 'T'){
					StartAddr = toDec(record.substr(1,6)); 
					text = record.substr(9,record.size()-9);
					for(int i=0;i<text.size() and IsValid(text[i],text[i+1]);i+=2){
						ViewPtr[StartAddr+(i/2)] = ConstructByte(text[i], text[i+1]);
						if(text[i]=='0' and text[i+1]=='0')
							ViewPtr[StartAddr+(i/2)] = 0;
					}
				}
				getline(Inp,record);
			}
		}
	}

	/* Display the obect program which has been loaded 
	 * into the memory */
	void DisplayMemoryMapping() {
		Out.open("OUTPUT.txt");

		OutputStyle();
		int SZ = toDec(Addr);
		int progEndSize = SZ + toDec(progLen);
		while(SZ < progEndSize+progEndSize%16){
			Out << "    " << extendTo(4,toHex(SZ)) << "\t\t" ;
			for(int i=0;i!=16;++i){
				if(i!=0 and i%4 == 0) Out << "  ";
				if(ViewPtr[i+SZ]==0) Out << "00";
				else if(1<=ViewPtr[i+SZ] and ViewPtr[i+SZ]<=15) Out << "0";  
				Out << toHex((int)ViewPtr[i+SZ]);
			}
			Out << endl;
			SZ += 16;
		}
	}

	void OutputStyle() {
		Out << "|=============================================================|\n";
		Out << "  Memory\t\t\tContents\n  Address\n";
		Out << "|=============================================================|\n";
	}

	/* Destructor */
	~AbsoluteLoader() {
		Inp.close();
		Out.close();
	}

};

#endif


