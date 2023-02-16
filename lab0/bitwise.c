#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[]){

	char a=argv[1][0];	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n=strtoul(argv[2], NULL, 16); // value to convert must be smaller than 256
	int bit=atoi(argv[3]); // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
 
	// Validate command line arguments

    if(argc!=4) return 1;
    if(!(a=='h' || a=='l' || a=='s' || a=='r' || a=='t')) return 1;
    if(strlen(argv[2])>2) return 1;


	
	// Print to stdout the binary representation of n
    printf("action: %c\n", a);
    printf("byte: %s\n", byte2bin(n, binary));
    printf("bit no: %d\n", bit);

	// Do what the user asked and print the result
	
    return 0;
}

