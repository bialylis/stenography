#include <openssl/evp.h>
#include "string.h"
#include <stdio.h>
#include "../lib/crypto.h"

int encrypt(void* buffer, int buffer_len, char* IV, char* key, int key_len,
		char* algorithm, char* mode) {
//	MCRYPT td = mcrypt_module_open(algorithm, NULL, mode, NULL);
//	int blocksize = mcrypt_enc_get_block_size(td);
//	if (buffer_len % blocksize != 0) {
//		return 1;
//	}
//
//	mcrypt_generic_init(td, key, key_len, IV);
//	mcrypt_generic(td, buffer, buffer_len);
//	mcrypt_generic_deinit(td);
//	mcrypt_module_close(td);

//	switch (algorithm) {
//	case AES_128:
//		break;
//	case
//}

//	EVP_CIPHER_CTX ctx = EVP_des_cbc();
	EVP_CIPHER_CTX ctx;
	if (EVP_EncryptInit(&ctx, NULL, key, IV) != 0) {
		return 1;
	}
	if (EVP_EncryptUpdate(&ctx, buffer, &buffer_len, buffer, sizeof(buffer))
			!= 0) {
		return 1;
	}
	if (EVP_EncryptFinal(&ctx, buffer + buffer_len, &buffer_len) != 0) {
		return 1;
	}
	return 0;
}

int decrypt(void* buffer, int buffer_len, char* IV, char* key, int key_len,
		char* algorithm, char* mode) {
//	MCRYPT td = mcrypt_module_open(algorithm, NULL, mode, NULL);
//	int blocksize = mcrypt_enc_get_block_size(td);
//	if (buffer_len % blocksize != 0) {
//		return 1;
//	}
//
//	mcrypt_generic_init(td, key, key_len, IV);
//	mdecrypt_generic(td, buffer, buffer_len);
//	mcrypt_generic_deinit(td);
//	mcrypt_module_close(td);

	return 0;
}
