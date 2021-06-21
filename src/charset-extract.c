/*

    Description:
    - 8 bit Character ROM visualizer for the original ZX Spectrum
 
    Features:
    - Extract the charset to a single binary file 

    Author:
    - Jorge Barrientos Poisson

    Requirements:

    Library:	Provides:
    ---------------------
    stdlib	exit() function
    stbbool	boolean data type
    unistd	getopt() function

    ChangeLog:
    
    - 2021.06.21 | Added getopt support
    - 2021.06.20 | C language port
    - 2017.01.19 | Last revision written in Processing
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define CHARSET_OFFSET	15616	// position of the CHARSET within the ZX Spectrum ROM
#define CHARSET_SIZE	96*8	// 96 characters, 8 bytes each 

FILE *romfile,*charset;
int count = CHARSET_SIZE;
char character;

void usage() {
    printf("Usage: charset-extractor -f <infile> <outfile>\n");
    printf("   -t,   --text          Outputs a plain ASCII text representation of the charset to the standard output\n");
    printf("   -r,   --raw           Extracts the raw binary charset from the ROM file, without modification");
    printf("   -h,   --help          Show this help message\n");
}

void drawbytes(char b) {
    char n;
    for (int i=8; i>0 ; i-- ) {
	n = b >> i;
	if ( n & 1 )
	    printf("X");
	else
	    printf("·");
    }
    printf("\n");
}

int main( int argc, char **argv ) {

    int cli;
    bool outAscii = false;
    bool outBinaryFile = false;

    while ( ( cli = getopt(argc,argv,"frth?") ) != -1 ) {
	switch(cli) {
	    case 'f':
		//if ( argv[] )
		//romfile = fopen
		break;
	    case 't':
		outAscii = true;
		break;
	    case 'r':
		outBinaryFile = true;
		break;
	    case 'h':
		usage();
		exit(0);
	    case '?':
		usage();
		exit(0);
	    default:
		usage();
		exit(0);	
	} 
    }

    if ( argc >= 2 ) {

	//romfile = fopen(argv[1],"rb");
	romfile = fopen("48.rom","rb");

	if ( outBinaryFile )
	    charset = fopen(argv[2],"wb");

	if ( romfile == NULL ) {
	    printf("Error opening file\n");
	    return -1;
	} else {
	    printf("ROM file: %s\n", argv[1]);
	}

	printf("Offset %i",CHARSET_OFFSET) ;
	fseek(romfile, CHARSET_OFFSET, SEEK_CUR);

	while ( count > 0 ) {

	    if ( count % 8 == 0 )
	       printf("\n");	

	    printf("Byte: %3i \t",count);

	    character = fgetc(romfile);

	    if ( outBinaryFile )
		fputc(character,charset);

	    if ( outAscii)
		drawbytes(character);
	    
	    count--;
	    //if ( count == 0 )
	    //	break;
	}	

	printf("\n");

	// close the ROM input file
	fclose(romfile);
	// close the CHARSET output file
	fclose(charset);
    }

    return 0;
}
