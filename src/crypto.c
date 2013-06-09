#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include "string.h"
#include <stdio.h>
#include "../lib/util.h"
#include "../lib/crypto.h"

#define SUCCESS 1
#define ERROR 0

const EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode);

char * encrypt(char * original, int * encrypted_size, const char* algorithm,
		const char * mode, const char * pass, int original_size) {

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);

	const EVP_CIPHER *cipher = get_evp_algorithm(algorithm, mode);

	unsigned char *key = malloc(sizeof(unsigned char) * EVP_CIPHER_key_length(cipher));
	unsigned char *iv = malloc(sizeof(unsigned char) * EVP_CIPHER_iv_length(cipher));
	EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass), 1, key, iv);

	char *out = calloc(original_size+ 16 + 1, sizeof(char));
	int length_partial = 0, length = 0;

	if (EVP_EncryptInit_ex(&ctx, cipher, NULL, key, iv) == ERROR) {
		printf("error");
	}
	if (EVP_EncryptUpdate(&ctx, out, &length_partial, original, original_size) == ERROR) {
		printf("error");
	}

	// length = length_partial;

	if (EVP_EncryptFinal_ex(&ctx, out + length_partial, &length) == ERROR) {
		printf("error");
	}

	length += length_partial;
	*encrypted_size = length;
	if (EVP_CIPHER_CTX_cleanup(&ctx) == ERROR) {
		printf("error");
	}

	return out;
}

char * decrypt(char * encrypted, int * decrypted_size, const char* algorithm,
		const char * mode, const char * pass, char * result) {

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);

	const EVP_CIPHER *cipher = get_evp_algorithm(algorithm, mode);
	//char *out = malloc(*((int*) encrypted)* sizeof(char)+200*sizeof(char?));

	unsigned char *key = malloc(sizeof(unsigned char) * EVP_CIPHER_key_length(cipher));
	unsigned char *iv = malloc(sizeof(unsigned char) * EVP_CIPHER_iv_length(cipher));

	if (EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass), 1, key,
			iv)==ERROR) {
		printf("error");
	}

	int length_partial = 0, length = 0;
	
	if (EVP_DecryptInit_ex(&ctx, cipher, NULL, key, iv) == ERROR) {
		printf("error");
	}


	if (EVP_DecryptUpdate(&ctx, result, &length_partial, encrypted+FILE_LENGTH_SIZE, *((int*) encrypted)) == ERROR) {
		printf("error");
	}

	// length = length_partial;
	if (EVP_DecryptFinal_ex(&ctx, result + length_partial, &length) == ERROR) {
		printf("error");
	}
	length += length_partial;
	*decrypted_size = length;
	if (EVP_CIPHER_CTX_cleanup(&ctx) == ERROR) {
		printf("error");
	}

	return result;
}

const EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode) {
	OpenSSL_add_all_ciphers();

	if (strcmp(algorithm, AES_128) == 0) {
		if (strcmp(mode, ECB) == 0) {
			return EVP_get_cipherbyname("aes-128-ecb");
		} else if (strcmp(mode, CFB) == 0) {
			return EVP_get_cipherbyname("aes-128-cfb");
		} else if (strcmp(mode, OFB) == 0) {
			return EVP_get_cipherbyname("aes-128-ofb");
		} else if (strcmp(mode, CBC) == 0) {
			return EVP_get_cipherbyname("aes-128-cbc");
		}
	} else if (strcmp(algorithm, AES_192) == 0) {
		if (strcmp(mode, ECB) == 0) {
			return EVP_get_cipherbyname("aes-192-ecb");
		} else if (strcmp(mode, CFB) == 0) {
			return EVP_get_cipherbyname("aes-192-cfb");
		} else if (strcmp(mode, OFB) == 0) {
			return EVP_get_cipherbyname("aes-192-ofb");
		} else if (strcmp(mode, CBC) == 0) {
			return EVP_get_cipherbyname("aes-192-cbc");
		}
	} else if (strcmp(algorithm, AES_256) == 0) {
		if (strcmp(mode, ECB) == 0) {
			return EVP_get_cipherbyname("aes-256-ecb");
		} else if (strcmp(mode, CFB) == 0) {
			return EVP_get_cipherbyname("aes-256-cfb");
		} else if (strcmp(mode, OFB) == 0) {
			return EVP_get_cipherbyname("aes-256-ofb");
		} else if (strcmp(mode, CBC)) {
			return EVP_get_cipherbyname("aes-256-cbc");
		}
	} else if (strcmp(algorithm, DES) == 0) {
		if (strcmp(mode, ECB) == 0) {
			return EVP_get_cipherbyname("des-ecb");
		} else if (strcmp(mode, CFB) == 0) {
			return EVP_get_cipherbyname("des-cfb");
		} else if (strcmp(mode, OFB) == 0) {
			return EVP_get_cipherbyname("des-ofb");
		} else if (strcmp(mode, CBC) == 0) {
			return EVP_get_cipherbyname("des-cbc");
		}
	}

	return EVP_get_cipherbyname("aes-128-ccb");
}
