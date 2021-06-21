/*

    Description:
    - 8 bit Character ROM visualizer for the original ZX Spectrum

    Author:
    - Jorge Barrientos Poisson
 
    Features:
    - Extract the charset to a single binary file 

    Requirements:

    Library:	Provides:
    ---------------------
    stdlib	exit() function
    stbbool	boolean data type
    unistd	getopt() function
    ctype	isprint() function

    ChangeLog:
    
    - 2021.06.21 | Added getopt support
    - 2021.06.20 | C language port
    - 2017.01.19 | Last revision written in Processing
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define CHARSET_OFFSET	15616	// position of the CHARSET within the ZX Spectrum ROM
#define CHARSET_SIZE	96*8	// 96 characters, 8 bytes each 

FILE *romfile,*charset;
int count = CHARSET_SIZE;
char character;

void usage() {
    printf("Usage: charset-extractor [options] [-i infile] <outfile>\n");
    printf("   -a,   --ascii         Outputs a plain ASCII text representation of the charset to the standard output\n");
    printf("   -r,   --raw           Extracts the raw binary charset from the ROM file, without modification\n");
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

    char * filename;
    int cli;
    bool out_ascii = false;
    bool out_raw = false;

    if ( argc < 2 ) {
	usage();
	exit(0);
    } else {
	while ( ( cli = getopt(argc,argv,"ahi:r") ) != -1 ) {
	    switch(cli) {
		case 'i':
		    printf("--> ROM file : %s\n", optarg);
		    filename = optarg;
		    break;
		case 'a':
		    out_ascii = true;
		    break;
		case 'r':
		    out_raw = true;
		    break;
		case 'h':
		    usage();
		    exit(0);
		case '?':
		    switch(optopt) {
			case 'i':
			    printf("ERROR: A valid ROM file path must be provided with the -%c function\n",optopt);
			    break;
			default:
			    if ( isprint(optopt) ) 
				printf("ERROR: Option -%c not recognized\n",optopt);
			    else
				printf("ERROR: Option contains non-printable characters\n");
			    break;
		    }
		    usage();
		    exit(-1);	
	    } 
	}
    }

    printf("Opening ROM file %s\n", filename);
    romfile = fopen(filename,"rb");

    if ( out_raw )
	charset = fopen(argv[2],"wb");

    if ( romfile == NULL ) {
	printf("Error opening file\n");
	return -1;
    } else {
	printf("ROM file: %s\n", filename);
    }

    printf("Offset %i",CHARSET_OFFSET) ;
    fseek(romfile, CHARSET_OFFSET, SEEK_CUR);

    while ( count > 0 ) {

	if ( count % 8 == 0 )
	   printf("\n");	

	printf("%3i ",count);

	character = fgetc(romfile);

	if ( out_raw )
	    fputc(character,charset);

	if ( out_ascii)
	    drawbytes(character);
	
	count--;
    }	

    printf("\n");

    // close the ROM input file
    fclose(romfile);
    // close the CHARSET output file
    fclose(charset);

    return 0;
}
