// Author: Edward Eldridge 
// Program: SHA-256 Algorithm implentation in C
// Resources: https://github.com/EddieEldridge/SHA256-in-C/blob/master/README.md
// Section Reference: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tell our preprocessor to create a variable MAXCHAR with value of 100000
#define MAXCHAR 100000

// Function decleration
// See Section 4.1.2
__uint32_t sig0(__uint32_t x);
__uint32_t sig1(__uint32_t x);

__uint32_t rotr(__uint32_t n, __uint16_t x);
__uint32_t shr(__uint32_t n, __uint16_t x);

__uint32_t SIG0(__uint32_t x);
__uint32_t SIG1(__uint32_t x);

__uint32_t Ch(__uint32_t x,__uint32_t y,__uint32_t z);
__uint32_t Maj(__uint32_t x,__uint32_t y,__uint32_t z);

// ==== Main ===
int main(int argc, char *argv[]) 
{
     // Print header
     printf("\n======== SHA256 - HASHING ALGORITHM ========\n\n");
    // Test to make sure the user is inputting a filename
    if(argc==0)
    {
        printf("Please supply a file to hash.");
        exit;
    }
    else if(argc>=1)
    {
        printf("\n Correct arguments. Attemping to read file.. \n");
        int argumentCount = argc;
        char *fileName = argv[1];
        char fileContents;
        // Function calls
        //sha256();
        fileContents = openFile(argumentCount, fileName);
        printf("\n -- File Contents -- \n");
        printf("%s", fileContents);
    }
    else
    {
        printf("Invalid arguments, please recheck your spelling.");
        exit;
    }
    
     return 0;

}

// === Functions ===

void sha256()
{
    printf("\n Starting SHA256 algorithm....\n");

    // Declare the K constant
    // Defined in Section 4.2.2
    __uint32_t K[] =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f
    };

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

    // For loop to iterate through the message block 
    int t;
    int o;

    printf("\n Initalized variables... Entering loops\n");


    for(t=0; t<16; t++)
    {
        // Add the current message block to our messag schedule
        W[t] = M[t];
    }

    for (t=16; t<64; t++)
    {
        // Step 1
        sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

        // Initalize a..h
        // Step 2
        a=H[0];
        b=H[1];
        c=H[2];
        d=H[3];
        e=H[4];
        f=H[5];
        g=H[6];
        h=H[7];

        // For loop
        // Step 3
        for(t = 0; t < 64; t++)
        {
            // Creating new variables
            // Need to write 'K', 
            T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
            T2 = SIG0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        };

        // Step 4
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];
        
     printf("\n====== HASH OUTPUT ======\n\n");
        printf("%x", H[0]);
        printf("%x", H[1]);
        printf("%x", H[2]);
        printf("%x", H[3]);
        printf("%x", H[4]);
        printf("%x", H[5]);
        printf("%x", H[6]);
        printf("%x", H[7]);
        printf("%x", H[8]);
        

     printf("\n\n======== HASH SUCCESSFUL ========\n\n");

    };

};

// This function is used to handle the opening and reading of files

char openFile(int argumentCount, char *fileName)
{
    // Variables
    FILE *file;
    char fileContents[MAXCHAR];
    char fileContentsAsString[MAXCHAR];
    long fileSize;

    // Open a file, specifiying which file using command line arguments
    file = fopen(fileName, "r");

    // First check to make sure the file could be found
    if (file == NULL){
        printf("\n Could not open file %s\n", fileName);
    }
    else
    {
        // Calculate the size of the file
        fileSize = calcFileSize(file);

        printf("\n File Size (characters): %d \n", fileSize);

        printf("\n --- File Contents --- \n");

        // While there is still stuff to read from the file
        while(fgets(fileContents, MAXCHAR, file) != NULL)
        {
            // Print the contents of the file
            //printf("%s", fileContents);
        };

        // Close the file 
        fclose(file);
        return fileContents;
    }
    
};

// Simple function that calcuates the size of a file
int calcFileSize(FILE *file)
{
    int prev=ftell(file);
    fseek(file, 0L, SEEK_END);
    int size=ftell(file);
    fseek(file,prev,SEEK_SET); 
    return size;
}

void padding()
{
    // 
};

// Section 4.1.2  
// ROTR = Rotate Right 
// SHR = Shift Right
// ROTR_n(x) = (x >> n) | (x << (32-n))
// SHR_n(x) = (x >> n)
__uint32_t sig0(__uint32_t x)
{
    // Section 3.2
   
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

__uint32_t SIG0(__uint32_t x)
{
    return (rotr(2,x) ^ rotr(13, x) ^ rotr(22,x));
};

__uint32_t SIG1(__uint32_t x)
{
    return (rotr(6,x) ^ rotr(11, x) ^ rotr(25,x));
};

// Choose
__uint32_t Ch(__uint32_t x,__uint32_t y,__uint32_t z)
{
    return ((x & y) ^ ((!x) & z));
};

// Majority decision
__uint32_t Maj(__uint32_t x,__uint32_t y,__uint32_t z)
{
    return ((x & y) ^ (x & z) ^ (y & z));
};
