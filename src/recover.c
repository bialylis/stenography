#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../lib/util.h"
#include "../lib/recover.h"

char* recover_lsb1(FILE* in, int *extension_size, char** extension);
char* recover_lsb4(FILE* in, int *extension_size, char** extension);
char* recover_lsbe(FILE* in, int *extension_size, char** extension);

char* recover_msg(const char* filename, char algorithm, int * extension_size,
		char ** extension) {
	char* msg;
	FILE* in = fopen(filename, "rb");

	//Skip header bytes
	fseek(in, HEADER_BYTES, SEEK_SET);

	switch (algorithm) {
	case LSB1:
		msg = recover_lsb1(in, extension_size, extension);
		break;
	case LSB4:
		msg = recover_lsb4(in, extension_size, extension);
		break;
	case LSBE:
		msg = recover_lsbe(in, extension_size, extension);
		break;
	}
	fclose(in);
	return msg;
}

char* recover_lsb1(FILE* in, int *extension_size, char **extension) {
	char c, hidden, *msg;
	unsigned long size = 0, i;
	int ended = 0;
	int counter = 0;

	//Recovers file size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		unsigned char bit = ((hidden & 1) << 7 - (i % 8));
		*(((char*) &size) + i / 8) |= bit;
	}
	//changes size to little endian
	size = htonl(size);
	msg = calloc(size + FILE_LENGTH_SIZE, sizeof(char));
	memcpy(msg, &size, FILE_LENGTH_SIZE);
	msg += 4;
	for (i = 0; i < size * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(msg + i / 8) |= ((hidden & 1) << 7 - (i % 8));
	}
	msg[i / 8] = 0;
	int j = 0;
	char *auxExtension = calloc(30, sizeof(char));
	while (!ended) {
		if (j % 30 == 0) {
			auxExtension = realloc(auxExtension, (30 + j) * sizeof(char));
		}
		hidden = fgetc(in);
		unsigned char bit = ((hidden & 1) << 7 - (j % 8));
		*(auxExtension + j / 8) |= bit;
		if (bit == 0) {
			counter++;
		} else {
			counter = 0;
		}
		if (counter == 8) {
			ended = 1;
		}
		if (j % 8 == 0) {
			counter = 0;
		}
		j++;
	}
	*extension = auxExtension;
	*extension_size = j;
	return msg - FILE_LENGTH_SIZE;
}

char* recover_lsb4(FILE* in, int *extension_size, char** extension) {
	char c, hidden, *msg;
	unsigned long size = 0, i;
	for (i = 0; i < 4 * 2; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 2) |= ((hidden & 0x0F) << (4 * ((i + 1) % 2)));
	}

	//changes size to little endian
	size = htonl(size);
	msg = calloc(size + FILE_LENGTH_SIZE, sizeof(char));
	memcpy(msg, &size, FILE_LENGTH_SIZE);
	msg += 4;
	for (i = 0; i < size * 2; i++) {
		hidden = fgetc(in);
		*(msg + i / 2) |= ((hidden & 0x0F) << (4 * ((i + 1) % 2)));
	}
	msg[i / 2] = 0;
	return msg - FILE_LENGTH_SIZE;
}

char* recover_lsbe(FILE* in, int *extension_size, char** extension) {
	unsigned char c, hidden, *msg;
	unsigned long size = 0, i = 0;
	while (i < 4 * 8) {
		hidden = fgetc(in);
		if (hidden == 255 || hidden == 254) {
			*(((char*) &size) + i / 8) |= ((hidden & 1) << 7 - (i % 8));
			i++;
		}
	}

	//changes size to little endian
	size = htonl(size);
	msg = calloc(size + BITS_PER_BYTE, sizeof(char));
	memcpy(msg, &size, BITS_PER_BYTE);
	msg += BITS_PER_BYTE;
	i = 0;
	while (i < size * BITS_PER_BYTE) {
		hidden = fgetc(in);
		if (hidden == 255 || hidden == 254) {
			*(msg + i / 8) |= ((hidden & 1) << 7 - (i % 8));
			i++;
		}
	}
	msg[i / 8] = 0;
	return msg - FILE_LENGTH_SIZE;
}
