   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

/*============================= A SIMPLE ABSOLUTE LOADER FOR SIC MACHINE ==============================*/
#include <windows.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

#include "AbsoluteLoader.hpp"

int main() {
	try {
		int MEM_SZ = 0x8000;              // total memory of an SIC machine is 2^15 ,i.e.,0x8000
		string FileName = "OBJECT.txt";   //  default file name
		string MemoryName = "COPY";       // default program name

		cout << "\nEnter the object file name : ";
		cin >> FileName;
		cout << "\nEnter the name of the program : ";
		cin >> MemoryName;

		AbsoluteLoader Loader(MEM_SZ,FileName,MemoryName);

		Loader.LoadIntoMemory();

		Loader.DisplayMemoryMapping();

		cout << "\nPROGRAM EXECUTED SUCCESSFULLY !!!\n\n";
		cout << "Check the OUTPUT.txt file.\n";
		
	}
	catch(const char* msg) {
		cerr << msg << endl;
	}
	
	return 0;
	
}
/*========================================================================================================*/
