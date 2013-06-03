#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/util.h"

/**
 * Return the file size in bytes.
 */
int get_file_size(const char* filename);

/**
 * Returns the extension of the file. (Example: ".txt")
 */
char *parse_extension(const char *filename);

char* parse_message(const char* filename) {
	FILE* in = fopen(filename, "r");
	char* extension = parse_extension(filename);
	int size = get_file_size(filename);

	// Length = 4 (para el tamaño) + longitud archivo + longitud extension + 1 ('\0')
	int length = FILE_LENGTH_SIZE + size + strlen(extension) + 1;

	char* msg = malloc(length);
	char c;
	char *p = msg;
	char i;

	//First part of the message is the length
	memcpy(msg, &length, FILE_LENGTH_SIZE);

	p += FILE_LENGTH_SIZE;

	//Copy rest of the message
	while ((c = fgetc(in)) != -1) {
		*(p++) = c;
	}
	fclose(in);

	//Add extension at the end.
	strcpy(p, extension);
	return msg;
}

char get_bit(char* bytes, int n) {
	return (bytes[n / 8] >> (7 - (n % 8))) & 1;
}

char get_nibble(char* bytes, int n) {
	return (bytes[n / 2] >> (4 * ((n + 1) % 2))) & 0x0F;
}

char *parse_extension(const char *filename) {
	char *dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot;
}

int get_file_size(const char* filename) {
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fclose(f);
	return size;
}

int get_algorithm(const char* string) {
	if (strcmp(string, "LSBE") == 0) {
		return LSBE;
	} else if (strcmp(string, "LSB4") == 0) {
		return LSB4;
	} else {
		return LSB1;
	}
}

char* preappend_size(char* msg) {
	int length = strlen(msg) + 4;
	char* out = malloc(length);
	char c, *p = out, i;
	p += FILE_LENGTH_SIZE;
	memcpy(out, &length, FILE_LENGTH_SIZE);
	strcpy(out+FILE_LENGTH_SIZE, msg);
	return out;
}
