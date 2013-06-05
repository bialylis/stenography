#ifndef __CRYPTO__
#define __CRYPTO__

char *  encrypt(char * original, unsigned long * encrypted_size, const char* algorithm, const char * mode,
		const char * pass);

char *  decrypt(char * encrypted, unsigned long *decrypted_size, const char* algorithm, const char * mode,
		const char * pass);

#endif
