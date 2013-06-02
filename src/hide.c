#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/util.h"
#include "../lib/hide.h"
#include "../lib/stenography.h"
#include "../lib/crypto.h"

void hide_lsb1(char* msg, FILE*p, FILE* out);
void hide_lsb4(char* msg, FILE*p, FILE* out);
void hide_lsbe(char* msg, FILE*p, FILE* out);

void hide_message(const char* p_filename, char* msg, const char* out_filename,
		char alg) {
	FILE* p = fopen(p_filename, "rb");
	FILE* out = fopen(out_filename, "wb");
	int i;
	for (i = 0; i < 54; i++) {
		fputc(fgetc(p), out);
	}
	i = 0;
	switch (alg) {
	case LSB1:
		hide_lsb1(msg, p, out);
		break;
	case LSB4:
		hide_lsb4(msg, p, out);
		break;
	case LSBE:
		hide_lsbe(msg, p, out);
		break;
	}
	fclose(p);
	fclose(out);
}

void hide_lsb1(char* msg, FILE*p, FILE* out) {
	char c, hidden;
	unsigned long i, size = *((int*) msg);
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < size * 8) {
			hidden = (c & ~1) | get_bit(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			fputc(c, out);
		}

	}
}

void hide_lsb4(char* msg, FILE*p, FILE* out) {
	char c, hidden;
	unsigned long i, size = *((int*) msg);
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < size * 2) {
			hidden = c & 0xF0;
			hidden |= get_nibble(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			fputc(c, out);
		}

	}
}

void hide_lsbe(char* msg, FILE*p, FILE* out) {
	unsigned char c, hidden;
	unsigned long i, size = *((int*) msg);
	while (((c = fgetc(p)) || 1) && !feof(p)) {
		if (i < size * 8 && (c == 254 || c == 255)) {
			hidden = (c & ~1) | get_bit(msg, i);
			fputc(hidden, out);
			i++;
		} else {
			fputc(c, out);
		}
	}
}
