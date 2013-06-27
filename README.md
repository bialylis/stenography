Stenography
============================

Final project for Cryptography and Security course at ITBA. Year 2013.

## Instructions

- The `libargtable2-dev` library must be installed:

        apt-get install libargtable2-dev 
	
- In the root of the project the following scripts can be found:
	- `desafio.sh` with the commands to get the hidden video.
	- `test.sh` with several tests


- To run the previously mentioned scripts, run:
        
        sh scriptname.sh

- Arguments are:

        [--extract] [--embed] [-i <input hide file>] -p <input bmp> -o <output bmp> -s LSB1|LSB4|LSBE [-a aes128|aes192|aes256|des] [-m ecb|cfb|ofb|cbc] [-P <char>]

- Required parameters:
	- `--extract` Indicates that information will be extract
	- `--embed` Indicates the information to be hidden
	- `-i o --in` File that will be hidden
	- `-p` Carrier bmp file
	- `-o o --out` Output file
	- `-s o --steg LSB1|LSB4|LSBE` Stenography algorithm

- Optional parameters:
	- `-a aes128|aes192|aes256|des` Encryption/Decryption algorithm
	- `-m ecb|cfb|ofb|cbc` Encryption/Decryption mode
	- `-P o --pass` Encryption password





