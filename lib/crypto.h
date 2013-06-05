#ifndef __CRYPTO__
#define __CRYPTO__

char *  encrypt(char * original, int * encrypted_size, const char* algorithm, const char * mode,
		const char * pass);

char *  decrypt(char * encrypted, int *decrypted_size, const char* algorithm, const char * mode,
		const char * pass);

#endif
