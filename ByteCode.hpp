   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//
#ifndef __BYTE_CODE_HPP__
#define __BYTE_CODE_HPP__

/* to check the validity of the object file */
bool IsValid(int Digit1, int Digit2) {
	return (('0'<=Digit1 and Digit1<='9') or 
		('A'<=Digit1 and Digit1<='F'))
			     and
	       (('0'<=Digit2 and Digit2<='9') or 
		('A'<=Digit2 and Digit2<='F'));
}

/* convert each hexadecimal character to its
 * equivalent decimal number and mask each 
 * digit with 0xf, i.e. with 1111 */
unsigned char ConstructHalfByte(int Digit) {
	assert(('0'<=Digit and Digit<='9') 
			   or
	       ('A'<=Digit and Digit<='F'));

	if('0'<=Digit and Digit<='9')
		return (Digit - 48) & 0xf;
	else
		return (Digit - 48 - 7) & 0xf;
}

/* convert two consecutive digits of the obect file
 * into 4-bit binary and combine them to make 1 byte */
unsigned char ConstructByte(int Digit1, int Digit2) {

	unsigned char High = ConstructHalfByte(Digit1);
	unsigned char Low  = ConstructHalfByte(Digit2);

	return (High << 4) | Low;
}


#endif
