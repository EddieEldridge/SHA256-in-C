// Author: Edward Eldridge 
// Program: SHA-256 Algorithm implentation in C
// Resources: https://github.com/EddieEldridge/SHA256-in-C/blob/master/README.md
// Section Reference: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function decleration
__uint32_t sig0(__uint32_t x);
__uint32_t sig1(__uint32_t x);

__uint32_t rotr(__uint32_t n, __uint16_t x);
__uint32_t shr(__uint32_t n, __uint16_t x);


// ==== Main ===
int main(int argc, char *argv[]) 
{
     // Print header
     printf("\n======== SHA256 - HASHING ALGORITHM ========\n");

     // Function calls
     sha256();
    
     // Main return method
     return 0;
}

// === Functions ===

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

    // For loop variable
    int t;

    for(t=0; t<16; t++)
    {
        // Add the current message block to our messag schedule
        W[t] = M[t];
    }

    for (t=16; t<64; t++)
    {
        sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

        // Initalize a..h
        a=H[0];
        b=H[1];
        c=H[2];
        d=H[3];
        e=H[4];
        f=H[5];
        g=H[6];
        h=H[7];

        // For loop
        for(t = 0; t < 64; t++)
        {
            T1 = h + SIG_1(e) + Ch(e,f,g) + K[t] + W[t];
            T2 = SIG_0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        };
    };

};

// Section 4.1.2  
__uint32_t sig0(__uint32_t x)
{
    // Section 3.2
    // ROTR = Rotate Right 
    // SHR = Shift Right
    // ROTR_n(x) = (x >> n) | (x << (32-n))
    // SHR_n(x) = (x >> n)
    return (rotr(7,x) ^ rotr(18, x) ^ shr(3,x));

};

__uint32_t sig1(__uint32_t x)
{
    return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x));
};

// Rotate bits right
__uint32_t rotr(__uint32_t n, __uint16_t x)
{
    return (x >> n) | (x << (32-n));
};

// Shift bits right
__uint32_t shr(__uint32_t n, __uint16_t x)
{
    return (x >> n);
};