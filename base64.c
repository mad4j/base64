
/**
 * base64.c
 * Base64 conveterer
 * 2017, Daniele Olmisani <daniele.olmisani@gmail.com>
 */

#include <stdio.h>
#include <string.h>


#define MASK_00000011 0x03
#define MASK_00001111 0x0F
#define MASK_00110000 0x30
#define MASK_00111100 0x3C
#define MASK_00111111 0x3F
#define MASK_11111111 0xFF

#define PAD_CHAR '='


//Base64 char table - used internally for encoding
unsigned char b64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
unsigned char b64_byte[256];

void init() {

	memset(b64_byte, 0, 256);

	for (int i=0; i<64; i++) {
		b64_byte[b64_char[i]] = i;
	}
}

void b64Encode() {

	//number of bytes read from input stream
	unsigned int k = 0;

	//residual bits form input
	unsigned char bits = 0;

	//last character on input stream
    int c=0;

	//write encoded chars until end of stream
	while((c = getchar()) != EOF) {
		
		//increment couter and process input byte
		switch (k++ % 3) {

			case 0:
				//output first 6 input bits
				putchar(b64_char[c >> 2]);

				//store residual 2 bits
				bits = (c & MASK_00000011) << 4;
				break;

			case 1:
				//output residual 2 bits and first 4 input bits
				putchar(b64_char[bits | (c >> 4)]);

				//store residual 4 bits
				bits = (c & MASK_00001111) << 2;
				break;

			case 2:
				//output residual 4 bits and first 2 bits
				putchar(b64_char[bits | (c >> 6)]);

				//output last 6 input bits
				putchar(b64_char[c & MASK_00111111]);

				//no residual bit each 3 input bytes
				bits = 0;
				break;
		}
	}

	//flush residual bits if any
	if (bits > 0) {
		putchar(b64_char[bits]);
	}

	//padding chars until TBD
	while (k++ % 3 > 0) {
		putchar(PAD_CHAR);
	}
}


int b64Decode() {

	//number of chars read from input stream
	unsigned int k = 0;

	//residual bits form input
	unsigned char bits = 0;

	//last character on input stream
	int c = 0;

	//write decoded byte until end of stream or a pad char
	while(((c = getchar()) != EOF) && (c != PAD_CHAR)){

		//conver input char in corresponding byte
		unsigned char b = b64_byte[c & MASK_11111111];

		//increment couter and process input byte
		switch (k++ % 4) {

			case 0:
				//store residual 6 bits
				bits = b << 2;
				break;

			case 1:
				//output residual 6 bits and first 2 input bits
				putchar(bits | ((b & MASK_00110000) >> 4));

				//store residual 4 bits
				bits = (b & MASK_00001111) << 4;
				break;

			case 2:
				//output residual 4 bits and first 4 input bits
				putchar(bits | ((b & MASK_00111100) >> 2));

				//store residual 2 bits
				bits = (b & MASK_00000011) << 6;
				break;

			case 3:
				//output residual 2 bits and last 6 input bits
				putchar(bits | b);

				//no residual bit each 4 input chars
				bits = 0;
				break;
		}
	}
}

int main(int argc, char *argv[]) {

	init();

	if (argc == 1) {
		b64Encode();
	} else if ((argc == 2) && (strcmp(argv[1], "-d") == 0)) {
		b64Decode();
	} else {
		printf("usage: base64 [-d] < input > output\n", argv[0]);
		return -1;
	}

    return 0;
}