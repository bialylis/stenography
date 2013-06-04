#ifndef __CRYPTO__
#define __CRYPTO__

int encrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass);

int decrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass);

#endif
