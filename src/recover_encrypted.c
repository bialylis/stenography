#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../lib/util.h"
#include "../lib/crypto.h"
#include "../lib/recover_encrypted.h"

char * recover_encrypted_lsb1(FILE* in);
char * recover_encrypted_lsb4(FILE* in);
char * recover_encrypted_lsbe(FILE* in);

char * recover_encrypted_msg(const char* filename, int algorithm) {

	char* msg;
	FILE* in = fopen(filename, "rb");

	//Skip header bytes
	fseek(in, HEADER_BYTES, SEEK_SET);

	switch (algorithm) {
	case LSB1:
		msg = recover_encrypted_lsb1(in);
		break;
	case LSB4:
		msg = recover_encrypted_lsb4(in);
		break;
	case LSBE:
		msg = recover_encrypted_lsbe(in);
		break;
	}
	fclose(in);
	return msg;
}

char * recover_encrypted_lsb1(FILE* in) {
	char hidden;
	int i = 0;
	char * msg;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSB1_RECOVER(hidden, i);
	}
	size = ntohl(size);
	msg = calloc(size+FILE_LENGTH_SIZE, sizeof(char));
	memcpy(msg, &size, FILE_LENGTH_SIZE);
	msg += FILE_LENGTH_SIZE;

	//Recover the hidden encrypted message
	for (i = 0; i < size * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		if(feof(in)) {
			printf("Oops! This might not be the method that the file was encrypted with!\n");
			exit(1);
		}
		*(msg + i / 8) |= LSB1_RECOVER(hidden,i);
	}
	msg[i / 8] = 0;
	return msg - FILE_LENGTH_SIZE;
}

char * recover_encrypted_lsb4(FILE* in) {
	char hidden, *msg;
	int i = 0;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * 2; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 2) |= LSB4_RECOVER(hidden, i)
		;
	}
	size = ntohl(size);
	msg = calloc(size+FILE_LENGTH_SIZE + 1, sizeof(char));
	memcpy(msg, &size, FILE_LENGTH_SIZE);
	msg += FILE_LENGTH_SIZE;

	//Recover the hidden encrypted message
	for (i = 0; i < size * 2; i++) {
		hidden = fgetc(in);
		if(feof(in)) {
			printf("Oops! This might not be the method that the file was encrypted with!\n");
			exit(1);
		}
		*(msg + i / 2) |= LSB4_RECOVER(hidden, i);
	}
	msg[i / 2] = 0;
	return msg - FILE_LENGTH_SIZE;
}

char * recover_encrypted_lsbe(FILE* in) {
	char *msg;
	unsigned char hidden;
	int i = 0;
	unsigned long size = 0;

	//Recovers encrypted size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSBE_RECOVER(hidden, i)
		;
	}
	size = ntohl(size);
	msg = calloc(size+FILE_LENGTH_SIZE, sizeof(char));
	memcpy(msg, &size, FILE_LENGTH_SIZE);
		msg += FILE_LENGTH_SIZE;

	//Recover the hidden encrypted message
	i = 0;
	while (i < size * BITS_PER_BYTE) {
		hidden = fgetc(in);
		if(feof(in)) {
			printf("Oops! This might not be the method that the file was encrypted with!\n");
			exit(1);
		}
		if (hidden == LSBE_BYTE_SET_1 || hidden == LSBE_BYTE_SET_2) {
			*(msg + i / 8) |= LSBE_RECOVER(hidden,i);
			i++;
		}
	}
	msg[i / 8] = 0;
	return msg - FILE_LENGTH_SIZE;
}

char * parse_decrypted(char * decrypted, char **extension, int *extension_size,
		unsigned long size) {
	char c, *msg;
	int i = 0;
	int msg_size = *((int *)decrypted);
	msg_size = ntohl(msg_size);
	msg = calloc(msg_size + FILE_LENGTH_SIZE,sizeof(char));
	memcpy(msg, &msg_size, FILE_LENGTH_SIZE*sizeof(char));

	// msg = calloc(msg_size, sizeof(char));

	decrypted = decrypted + FILE_LENGTH_SIZE;

	memcpy(msg + FILE_LENGTH_SIZE, decrypted, (msg_size)*sizeof(char));

	*extension_size = size - msg_size;
	decrypted = decrypted + msg_size;
	*extension = calloc(*extension_size,sizeof(char));
	memcpy(*extension, decrypted, (*extension_size)*sizeof(char));

	return msg;
}
