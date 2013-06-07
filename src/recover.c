#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../lib/util.h"
#include "../lib/recover.h"

char* recover_lsb1(FILE* in, int *extension_size, char** extension);
char* recover_lsb4(FILE* in, int *extension_size, char** extension);
char* recover_lsbe(FILE* in, int *extension_size, char** extension);
int recover_extension(FILE *in, char **extension, char algorithm);
char * preappend_recovered_size(unsigned long *size);

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

	//Recovers file size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 8) |= LSB1_RECOVER(hidden,i)
		;
	}
	msg = preappend_recovered_size(&size);

	//Recover the hidden message
	for (i = 0; i < size * BITS_PER_BYTE; i++) {
		hidden = fgetc(in);
		*(msg + i / 8) |= LSB1_RECOVER(hidden,i)
		;
	}
	msg[i / 8] = 0;

	//Recovers the extension
	*extension_size = recover_extension(in, extension, LSB1);
	return msg - FILE_LENGTH_SIZE;
}

char* recover_lsb4(FILE* in, int *extension_size, char** extension) {
	char c, hidden, *msg;
	unsigned long size = 0, i;

	//Recovers file size: Reads the first FILE_LENGTH_SIZE
	for (i = 0; i < FILE_LENGTH_SIZE * 2; i++) {
		hidden = fgetc(in);
		*(((char*) &size) + i / 2) |= LSB4_RECOVER(hidden, i)
		;
	}

	msg = preappend_recovered_size(&size);

	//Recover the hidden message
	for (i = 0; i < size * 2; i++) {
		hidden = fgetc(in);
		*(msg + i / 2) |= LSB4_RECOVER(hidden, i)
		;
	}
	msg[i / 2] = 0;

	//Recovers the extension
	*extension_size = recover_extension(in, extension, LSB4);
	return msg - FILE_LENGTH_SIZE;
}

char* recover_lsbe(FILE* in, int *extension_size, char** extension) {
	unsigned char c, hidden, *msg;
	unsigned long size = 0, i = 0;

	//Recovers file size: Reads the first FILE_LENGTH_SIZE
	while (i < FILE_LENGTH_SIZE * BITS_PER_BYTE) {
		hidden = fgetc(in);
		if (hidden == LSBE_BYTE_SET_1 || hidden == LSBE_BYTE_SET_2) {
			*(((char*) &size) + i / 8) |= LSBE_RECOVER(hidden,i)
			;
			i++;
		}
	}

	msg = preappend_recovered_size(&size);

	//Recover the hidden message
	i = 0;
	while (i < size * BITS_PER_BYTE) {
		hidden = fgetc(in);
		if (hidden == LSBE_BYTE_SET_1 || hidden == LSBE_BYTE_SET_2) {
			*(msg + i / 8) |= LSBE_RECOVER(hidden,i)
			;
			i++;
		}
	}
	msg[i / 8] = 0;

	//Recovers the extension
	*extension_size = recover_extension(in, extension, LSBE);
	return msg - FILE_LENGTH_SIZE;
}

int recover_extension(FILE *in, char **extension, char algorithm) {
	int j = 0, ended = 0, counter = 0;
	char *auxExtension = calloc(30, sizeof(char));
	unsigned char hidden;
	while (!ended) {
		if (j % 30 == 0) {
			auxExtension = realloc(auxExtension, (30 + j) * sizeof(char));
		}
		hidden = fgetc(in);
		unsigned char bit;
		switch (algorithm) {
		case LSB1:
			bit = LSB1_RECOVER(hidden, j)
			;
			*(auxExtension + j / 8) |= bit;
			j++;
			break;
		case LSB4:
			bit = LSB4_RECOVER(hidden, j)
			;
			*(auxExtension + j / 2) |= bit;
			j++;
			break;
		case LSBE:
			if (hidden == LSBE_BYTE_SET_1 || hidden == LSBE_BYTE_SET_2) {
				bit = LSBE_RECOVER(hidden, j)
				;
				*(auxExtension + j / 8) |= bit;
				j++;
			}
			break;
		}

		//Searchs for 8 consecute 0, that means for the '\0'
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

	}
	*extension = auxExtension;
	return j;
}

char * preappend_recovered_size(unsigned long *size) {
	char *msg;

	//Changes size to little endian
	*size = ntohl(*size);
	msg = calloc(*size + FILE_LENGTH_SIZE, sizeof(char));
	memcpy(msg, size, FILE_LENGTH_SIZE);
	msg += FILE_LENGTH_SIZE;
	return msg;
}
