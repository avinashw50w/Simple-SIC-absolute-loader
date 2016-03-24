   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

#ifndef __ABSOLUTE_LOADER_HPP__
#define __ABSOLUTE_LOADER_HPP__

#include "ADDR_CONVERTER.hpp"

typedef pair<string,string> PSS;
typedef vector<string> VS;

class AbsoluteLoader {
private:
	VS memory;
	string record, startAddr, progLen, text;
	int Addr;
	const int MEM_SZ;
	ifstream Inp;
	ofstream Out;

public:
	/* Constructor */
	AbsoluteLoader(const int& size) : 
			MEM_SZ(size) {
				/* 32 KB memory for SIC machine */
				memory.assign(MEM_SZ,"xx");  
			}

	/* Default Constructor */
	AbsoluteLoader() : 
			MEM_SZ(32768) {
				memory.assign(MEM_SZ,"xx");
			}

	/* read the object program from the 
	 * object file */
	void ReadObjectCode() const {
		Inp.open("OBJECT.txt");
		Out.open("OUTPUT.txt");
		
		if(Inp.is_open()){
			getline(Inp, record);
			if(record[0] == 'H'){
				startAddr = record.substr(9,4);
				Addr = toDec(startAddr);
				progLen = record.substr(13,6);
				
				if(toDec(progLen) >= MEM_SZ)
					throw string("\nOUT OF MEMORY SPACE...\n");
			}	
			else
				throw string("\nNO HEADER RECORD...\n");

			getline(Inp, record);
			
			while(record[0] != 'E'){
				if(record[0] == 'T'){
					Addr = toDec(record.substr(1,6)); 
					text = record.substr(9,record.size()-9);
					for(int i=0;i<text.size();i+=2){
						memory[Addr] = text.substr(i,2);
						Addr++;
					}
				}
				getline(Inp,record);
			}
		}
	}

	/* load the obect program into the memory */
	void LoadIntoMemory() const {

		OutputStyle();

		int SZ = toDec(startAddr);
		Addr--;
		while(SZ < Addr+Addr%16){
			Out << "    " << extendTo(4,toHex(SZ)) << "\t\t" ;
			for(int i=0;i!=16;++i){
				if(i!=0 and i%4 == 0) Out << "  ";  
				Out << memory[i+SZ];
			}
			Out << endl;
			SZ+= 16;
		}
	}

	void OutputStyle() {
		Out << "|=============================================================|\n";
		Out << "  Memory\t\t\tContents\n  Address\n";
		Out << "|=============================================================|\n";
	}

	/* Destructor */
	~AbsoluteLoader() {
		memory.clear();
		Inp.close();
		Out.close();
	}

};

#endif


