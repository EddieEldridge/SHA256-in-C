# SHA256-in-C
An implementation of the SHA256 Hashing Algorithm in C

# What is the SHA256 Hashing Algorithm? 
SHA-2 (Secure Hash Algorithm 2) is a set of cryptographic hash functions designed by the United States National Security Agency (NSA).

The standard for the algorithm can be found [here](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf).

# Setup/Install
The only thing you need to compile and/or run the script is a copy of the C compiler.

* Windows - `www.mingw.org`
* Linux - `sudo apt-get install build-essential`
* Solus - `sudo eopkg install -c system.devel`


1. Compile - `gcc SHA256.c -o SHA256`
2. Execute - `./SHA256 testFile1.txt`

# Implementation
The project was done under the guidance of video lectures uploaded by Ian McLoughlin.

During the implementation of the project, research about the algorthim and it's standards was undertaken to try
and better understand the intricacies of the algorthim. 

![image](https://user-images.githubusercontent.com/22448079/55245841-e4ff5e80-523b-11e9-96b1-277ee6f65d2d.png)

The program does not calculate the correct hash, however the length of the hash is correct (124 characters).

Check correctHashes.txt for more info.

# Research
* [How Does SHA256 Work?](https://www.youtube.com/watch?v=mbekM2ErHfM)

* [How secure is 256 bit security?](https://www.youtube.com/watch?v=mbekM2ErHfM)

* [What is a Bitcoin hash and SHA-256?](https://www.youtube.com/watch?v=9mNgeTA13Gc)

* [US Government SHA256 Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

* [Little Endian vs Big Endian](https://www.geeksforgeeks.org/little-and-big-endian-mystery/)
