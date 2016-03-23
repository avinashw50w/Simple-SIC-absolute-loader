   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

/*============================= A SIMPLE ABSOLUTE LOADER FOR SIC MACHINE ==============================*/
#include <iostream>
#include <fstream>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

#include "AbsoluteLoader.hpp"

int main() {
	try {
		const int MEM_SZ = 32768;
		AbsoluteLoader Loader(MEM_SZ);

		Loader.ReadObjectCode();

		Loader.LoadIntoMemory();
	}
	catch(const string* msg) {
		cerr << msg;
	}
	
	cout << "\nPROGRAM EXECUTED SUCCESSFULLY !!!\n";

	return 0;
}
/*========================================================================================================*/
