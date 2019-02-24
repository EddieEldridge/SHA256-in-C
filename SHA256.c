// Author: Edward Eldridge 
// Program: SHA-256 Algorithm implentation in C
// Resources: https://github.com/EddieEldridge/SHA256-in-C/blob/master/README.md

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sha256();

// Main method
int main(int argc, char *argv[]) 
{
     // Print header
     printf("\n======== SHA256 - HASHING ALGORITHM ========\n");

     // Function calls
     sha256();
    
     // Main return method
     return 0;
}

void sha256()
{
    // Message schedule
    __uint32_t W[64];

    // Working variables
    __uint32_t a, b, c, d, e, f, g, h;

    // Temp variables
    __uint32_t T1;
    __uint32_t T2;

    // Hash values
    // Taken from https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
    // Section 5.3.3
    __uint32_t H[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };

    // The current message block
    __uint32_t M[16];

}
