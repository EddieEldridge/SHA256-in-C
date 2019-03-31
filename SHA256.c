// Author: Edward Eldridge 
// Program: SHA-256 Algorithm implentation in C
// Resources: https://github.com/EddieEldridge/SHA256-in-C/blob/master/README.md
// Section Reference: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

// Define a union for easy reference
// Union represents a message block
union messageBlock
{
    __uint8_t e[64];
    __uint32_t t[16];
    __uint64_t s[8];
};

// ENUM to control state of the program
enum status{READ, 
            PAD0,
            PAD1,
            FINISH
            };

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

void printFileContents();
int calcFileSize();
void endianCheckPrint();
_Bool endianCheck();
int fillMessageBlock();
void calculateHash(FILE *file);
int nextMessageBlock(FILE *file, union messageBlock *msgBlock, enum status *state, __uint64_t *numBits);
__uint32_t byteSwap32(__uint32_t x);
__uint64_t byteSwap64(__uint64_t x);

// ==== Main ===
int main(int argc, char *argv[]) 
{   
     // Variables
    FILE *file;
    char* fileName;
    int argumentCount = argc;

    // Print header
    printf("\n======== SHA256 - HASHING ALGORITHM ========");

    // Test to make sure the user is inputting a filename
    if(argumentCount == 0)
    {
        printf("Please supply a file to hash as command line arguments.");
        exit;
    }
    else if(argumentCount >= 1)
    {
        printf("\n Correct arguments. Attemping to read file.. \n");

        fileName = argv[1];
            
        // Open a file, specifiying which file using command line arguments
        file = fopen(fileName, "r");

         // First check to make sure the file could be found
        if (file == NULL){
            printf("\n Could not open file %s\n", fileName);
        }
        else
        {
            // Function calls
            printf("\n File ok, executing functions.. \n");
            endianCheckPrint();
            //printFileContents(file);
            calculateHash(file);

            // Close the file 
            fclose(file);
        }
    }
    else
    {
        printf("Invalid arguments, please recheck your spelling.");
        exit;
    }
    
    return 0;

}

// === Functions ===
void calculateHash(FILE *file)
{   
    // Variables
    // The current message block
    union messageBlock msgBlock;

    // The number of bits read from the file
    __uint64_t numBits = 0;

    // The state of the program
    enum status state = READ;

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

    // For loop to iterate through the message block 
    int j;
    int o;

    printf("\n Initalized variables... Entering loops\n");

    while(fillMessageBlock(file, &msgBlock, &state, &numBits))
    {
        for(j=0; j<16; j++)
        {   
            // Fist check for big or little endian
            // If our system is big endian we dont need to do any conversion
            if(endianCheck()==true)
            {
                W[j] = msgBlock.t[j];
            }
            else
            {
                // Add the current message block to our messag schedule
                // Convert to big endian first
                W[j] = byteSwap32(msgBlock.t[j]);
            }
           
        }

        for (j=16; j<64; j++)
        {
            // Step 1
            W[j] = sig1(W[j-2]) + W[j-7] + sig0(W[j-15]) + W[j-16];
        }


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
        for(j = 0; j < 64; j++)
        {
            // Creating new variables
            T1 = h + SIG1(e) + Ch(e,f,g) + K[j] + W[j];
            T2 = SIG0(a) + Maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // Step 4
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];
    
    }// end while
    
    // Print the results
    printf("\n=================== HASH OUTPUT ==================================\n\n");
    printf("%08llx", H[0]);
    printf("%08llx", H[1]);
    printf("%08llx", H[2]);
    printf("%08llx", H[3]);
    printf("%08llx", H[4]);
    printf("%08llx", H[5]);
    printf("%08llx", H[6]);
    printf("%08llx", H[7]);
    
    printf("\n\n==================================================================\n\n");

}

// This function is used to handle the opening and reading of files
int fillMessageBlock(FILE *file, union messageBlock *msgBlock, enum status *state, __uint64_t *numBits)
{   
    // Variables
    __uint64_t numBytes;
    int i;

    // If we've finished padding and processing all the message blocks, exit
    if(*state == FINISH)
    {
        printf("\n State = FINISH.\n");
        return 0;
    }

    // Handle our PAD0 and PAD1 states
    // Check if we need another block full of padding
    if(*state == PAD0 || *state == PAD1)
    {
        printf("\n State = PAD0 or PAD1.\n");

        // Set the first 56 bytes to all zero bits
        for(i=0; i<56; i++)
        {
            msgBlock->e[i] = 0x00;
        }

        // Set the last 64 bits to an integer (should be big endian)
        msgBlock->s[7] = byteSwap64(*numBits);

        // Set the state to finish
        *state = FINISH;

        // If state is PAD1, set the first bit of msgBlock to 1
        if(*state == PAD1)
        {
            // 0x80 = 10000000
            msgBlock->e[0] = 0x01;
        }

        // keep the loop in SHA256 going for one more iteration
        return 1;
    }

    // Read bytes instead of characters
    // Read until the end of the file
    numBytes = fread(msgBlock->e, 1, 64, file);
    
    // Keep track of the number of bytes we've read
    *numBits = *numBits + (numBytes * 8);
    
    // If theres enough room to finish the padding
    if(numBytes < 56)
    {
        // 0x80 = 10000000
        // Add the one bit, as per the standard before padding with 0s
        msgBlock->e[numBytes] = 0x80;

        // Add 0 bits until the last 64 bits
        while(numBytes < 56)
        {
            // Add the index into our block
            numBytes = numBytes +1;
            
            // Add enough zeroes so that there are 64 bits left at the end
            msgBlock->e[numBytes] = 0x00;
        }

        // Store the length of the file in bits as a (Should be big endian) unsigned 64 bit int
        msgBlock->s[7] = byteSwap64(*numBits);

        // Change the state of our program
        *state = FINISH;
    }
    // Otherwise, check if we can put some padding into this message block
    else if(numBytes < 64)
    {   
        // Set the state to PAD0
        *state = PAD0;
        
        // 0x80 = 10000000
        // Add the one bit into the current message block
        msgBlock->e[numBytes] = 0x80;

        // Pad the rest of the message block with 0 bits
        while(numBytes < 64)
        {
            numBytes = numBytes + 1;
            msgBlock->e[numBytes] = 0x00;
        }
    }
    // Otherwise if we're at the end of the file, need to create a new message block full of padding
    else if(feof(file))
    {
        // Set the state to PAD1
        // We need a message Block full of padding
        *state = PAD1;
    }
    
    // Print padding
    /*
    printf("\n--- PADDING --- \n");
    for (int i=0; i<64; i++)
    {
       printf("%x", msgBlock.e[i]);
    }
    printf("\n");
    */
    return 1;
}
    
// This function is used to read the contents of the file and return them as an array of chars
void printFileContents(FILE *file)
{
    // Variables
    char fileContents[MAXCHAR];
    char fileContentsAsString[MAXCHAR];
    long fileSize;

    // First check to make sure the file could be found
    if (file == NULL){
        printf("\n Could not open file");
    }
    else
    {
        // Calculate the size of the file
        fileSize = calcFileSize(file);

        printf("\n File Size (characters): %d \n", fileSize);

        printf("\n ============= File Contents ============= \n");

        // While there is still stuff to read from the file
        while(fgets(fileContents, MAXCHAR, file) != NULL)
        {
            // Print the contents of the file
            printf(" %s\n", fileContents);
        };
        
        printf("\n ========================================= \n");

        // Close the file 
        return;
    }
    
}
// Simple function that calcuates the size of a file
int calcFileSize(FILE *file)
{
    int prev=ftell(file);
    fseek(file, 0L, SEEK_END);
    int size=ftell(file);
    fseek(file,prev,SEEK_SET); 
    return size;
}

void endianCheckPrint()
{
    int num = 1;
        if(*(char *)&num == 1) {
                printf("\n Your system is Little-Endian!\n");
        } else {
                printf("Your system is Big-Endian!\n");
        }
}

_Bool endianCheck()
{
    int num = 1 ;
        if(*(char *)&num == 1) {
                return false;
        } else {
                return true;
        }
}
// Reference - http://www.firmcodes.com/write-c-program-convert-little-endian-big-endian-integer/
// Converts a little endian integer to big endian and vice versa (32 bit version)
__uint32_t byteSwap32(__uint32_t x)
{
    x = (x & 0xffff0000) >> 16 | (x & 0x0000ffff) << 16;
    x = (x & 0xff00ff00) >>  8 | (x & 0x00ff00ff) <<  8;
    return x;
}


// Reference - https://stackoverflow.com/questions/21507678/reverse-bytes-for-64-bit-value
// Converts a little endian integer to big endian and vice versa (64 bit version)
__uint64_t byteSwap64(__uint64_t integer)
{
    uint64_t x = (uint64_t) integer;
    x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
    x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
    x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
    return x;
}

// Section 4.1.2  
// ROTR = Rotate Right 
// SHR = Shift Right
// ROTR_n(x) = (x >> n) | (x << (32-n))
// SHR_n(x) = (x >> n)
__uint32_t sig0(__uint32_t x)
{
    // Section 3.2
    return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3);
};

__uint32_t sig1(__uint32_t x)
{
    return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10);
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
    return (rotr(x,2) ^ rotr(x, 13) ^ rotr(x,22));
};

__uint32_t SIG1(__uint32_t x)
{
    return (rotr(x,6) ^ rotr(x, 11) ^ rotr(x,25));
};

// Choose
__uint32_t Ch(__uint32_t x,__uint32_t y,__uint32_t z)
{
    return ((x & y) ^ ((~x) & z));
};

// Majority decision
__uint32_t Maj(__uint32_t x,__uint32_t y,__uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
};
