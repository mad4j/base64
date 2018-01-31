/**
 * base64.cpp
 * RFC4648 Base64 conveterer
 * 2017, Daniele Olmisani <daniele.olmisani@gmail.com>
 * 
 * see LINCENSE file
 * 
 * References:
 *  + https://tools.ietf.org/html/rfc4648
 * 
 */

#include <cstdio>
#include <cstdint>
#include <cstring>

using namespace std;

//standard Base64 padding char
const char PAD_CHAR = '=';

//byte to charather convetion table
uint8_t toChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//character to byte conversion table (to be initialized)
uint8_t toByte[256];

/**
 * initialization of internal structures
 */
void init()
{

	//zeroize each array element
	memset(toByte, 0, 256);

	//build a reverse map of toChar array
	for (int i = 0; i < 64; i++)
	{
		toByte[toChar[i]] = i;
	}
}

/**
 * reads bytes from standard input 
 * and writes base64 encoded chars on standard outuput
 */
void encode()
{

	//residual bits form input
	uint8_t bits = 0;

	//number of bytes read from input stream
	uint32_t k = 0;

	//last byte on input stream
	auto c = 0;

	//read bytes until end of stream
	while ((c = getchar()) != EOF)
	{

		//increment couter and process input byte
		switch (k++ % 3)
		{

		case 0:
			//output first 6 input bits
			putchar(toChar[c >> 2]);

			//store residual 2 bits
			bits = (c & 0b00000011) << 4;
			break;

		case 1:
			//output residual 2 bits and first 4 input bits
			putchar(toChar[bits | (c >> 4)]);

			//store residual 4 bits
			bits = (c & 0b00001111) << 2;
			break;

		case 2:
			//output residual 4 bits and first 2 bits
			putchar(toChar[bits | (c >> 6)]);

			//output last 6 input bits
			putchar(toChar[c & 0b00111111]);

			//no residual bit each 3 input bytes
			bits = 0;
			break;
		}
	}

	//flush residual bits if any
	if (bits > 0)
	{
		putchar(toChar[bits]);
	}

	//write padding until 4 chars alignment achived
	//i.e. B1 B2 B3  ->  A   B   C   D
	//     B1 B2     ->  A   B   C  '='
	//     B1        ->  A   B  '=' '='
	while (k++ % 3 > 0)
	{
		putchar(PAD_CHAR);
	}
}

/**
 * reads base64 encoded chars from standard input
 * and writes bytes to standard output
 */
void decode()
{

	//residual bits form input
	uint8_t bits = 0;

	//number of chars read from input stream
	uint32_t k = 0;

	//last character on input stream
	auto c = 0;

	//read chars until end of stream or a pad char
	while (((c = getchar()) != EOF) && (c != PAD_CHAR))
	{

		//conver input char in corresponding 6 bits
		uint8_t b = toByte[c & 0b11111111];

		//increment couter and process input byte
		switch (k++ % 4)
		{

		case 0:
			//store residual 6 bits
			bits = b << 2;
			break;

		case 1:
			//output residual 6 bits and first 2 input bits
			putchar(bits | ((b & 0b00110000) >> 4));

			//store residual 4 bits
			bits = (b & 0b00001111) << 4;
			break;

		case 2:
			//output residual 4 bits and first 4 input bits
			putchar(bits | ((b & 0b00111100) >> 2));

			//store residual 2 bits
			bits = (b & 0b00000011) << 6;
			break;

		case 3:
			//output residual 2 bits and last 6 input bits
			putchar(bits | (b & 0b00111111));

			//no residual bit each 4 input chars
			bits = 0;
			break;
		}
	}
}

int main(int argc, char *argv[])
{

	init();

	if (argc == 1)
	{
		encode();
	}
	else if ((argc == 2) && (strncmp(argv[1], "-d", 16) == 0))
	{
		decode();
	}
	else
	{
		printf("usage: %s [-d] < input > output\n", argv[0]);
		return -1;
	}

	return 0;
}
