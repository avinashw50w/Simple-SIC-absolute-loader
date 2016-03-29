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

#define INPUT_NAME

int main() {
	try {
		int MEM_SZ = 0x8000;
		string FileName = "OBJECT.txt";
		string MemoryName = "COPY";

		#ifdef INPUT_NAME
		cout << "\nEnter the object file name : ";
		cin >> FileName;
		cout << "\nEnter the name of the program : ";
		cin >> MemoryName;
		#endif

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
