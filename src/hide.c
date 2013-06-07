#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/util.h"
#include "../lib/hide.h"
#include "../lib/stenography.h"
#include "../lib/crypto.h"

void hide_lsb1(char* msg, FILE*p, FILE* out,int size);
void hide_lsb4(char* msg, FILE*p, FILE* out,int size);
void hide_lsbe(char* msg, FILE*p, FILE* out,int size);

void hide_message(const char* p_filename, char* msg, const char* out_filename,
		char algorithm, int size) {
	FILE* p = fopen(p_filename, "rb");
	FILE* out = fopen(out_filename, "wb");

	//Read and write header bytes in out
	int i;
	for (i = 0; i < HEADER_BYTES; i++) {
		fputc(fgetc(p), out);
	}

	switch (algorithm) {
	case LSB1:
		hide_lsb1(msg, p, out,size);
		break;
	case LSB4:
		hide_lsb4(msg, p, out,size);
		break;
	case LSBE:
		hide_lsbe(msg, p, out,size);
		break;
	}

	fclose(p);
	fclose(out);
}

void hide_lsb1(char* msg, FILE*p, FILE* out, int size) {
	char c, hidden;
	unsigned long i = 0;
	unsigned long bits_qty = size * BITS_PER_BYTE;
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < bits_qty) {
			hidden = (c & ~1) | get_bit(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			//If the text has been hidden, the rest of the image must be copied identically
			fputc(c, out);
		}

	}
}

void hide_lsb4(char* msg, FILE*p, FILE* out, int size) {
	char c, hidden;
	unsigned long i = 0;
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < size * 2) {
			hidden = c & 0xF0;
			hidden |= get_nibble(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			//If the text has been hidden, the rest of the image must be copied identically
			fputc(c, out);
		}

	}
}

void hide_lsbe(char* msg, FILE*p, FILE* out, int size) {
	unsigned char c, hidden;
	unsigned long i = 0;
	unsigned long bits_qty = size * BITS_PER_BYTE;
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < bits_qty && (c == LSBE_BYTE_SET_1 || c == LSBE_BYTE_SET_2)) {
			hidden = (c & ~1) | get_bit(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			//If the text has been hidden, the rest of the image must be copied identically
			fputc(c, out);
		}
	}
}
