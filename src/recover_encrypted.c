#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../lib/util.h"
#include "../lib/crypto.h"
#include "../lib/recover_encrypted.h"

int recover_encrypted_lsb1(FILE* in);
int recover_encrypted_lsb4(FILE* in);
int recover_encrypted_lsbe(FILE* in);

char * recover_encrypted_msg(const char* filename, char algorithm,
		const char * encrypt_algorithm, const char *encrypt_mode, const char * pass) {
	char* msg;
	FILE* in = fopen(filename, "rb");

	//Skip header bytes
	fseek(in, HEADER_BYTES, SEEK_SET);

	unsigned long encrypted_size = 0;
	switch (algorithm) {
	case LSB1:
		encrypted_size = recover_encrypted_lsb1(in);
		break;
	case LSB4:
		encrypted_size = recover_encrypted_lsb4(in);
		break;
	case LSBE:
		encrypted_size = recover_encrypted_lsbe(in);
		break;
	}
	//return msg
	 decrypt(in, encrypted_size, encrypt_algorithm, encrypt_mode, pass);
	fclose(in);
	return msg;
}

int recover_encrypted_lsb1(FILE* in) {
	char hidden;
	int i = 0;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSB1_RECOVER(hidden, i);
	}
	size = htonl(size);
	return size;
}
int recover_encrypted_lsb4(FILE* in) {
	char hidden;
	int i = 0;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSB4_RECOVER(hidden, i);
	}
	size = htonl(size);
	return size;
}
int recover_encrypted_lsbe(FILE* in) {
	char hidden;
	int i = 0;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSBE_RECOVER(hidden, i);
	}
	size = htonl(size);
	return size;
}
