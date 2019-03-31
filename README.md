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

The script correctly calculates the correct hash, this can be seen here. To fix the problem of the algorthim giving an incorrect hash, I had to add a missing 2 to my `K` constant variable and change some of the SIG functions.

![Screenshot from 2019-03-31 14-33-18](https://user-images.githubusercontent.com/22448079/55289790-16eefd00-53c3-11e9-8221-f0813ea398d2.png)

Check correctHashes.txt for more info.


The correct hashes for the given strings are as follows

* `abc` = `ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad`
* ` ` = `e3b0c442 98fc1c14 9afbf4c8 996fb924 27ae41e4 649b934c a495991b 7852b855`
* `abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq` = `248d6a61 d20638b8 e5c02693 0c3e6039 a33ce459 64ff2167 f6ecedd4 19db06c1`
  

# Research
* [How Does SHA256 Work?](https://www.youtube.com/watch?v=mbekM2ErHfM)

* [How secure is 256 bit security?](https://www.youtube.com/watch?v=mbekM2ErHfM)

* [What is a Bitcoin hash and SHA-256?](https://www.youtube.com/watch?v=9mNgeTA13Gc)

* [US Government SHA256 Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

* [Little Endian vs Big Endian](https://www.geeksforgeeks.org/little-and-big-endian-mystery/)

* [Converting Little to Big Endian and Vice Versaa](https://stackoverflow.com/questions/19275955/convert-little-endian-to-big-endian)
