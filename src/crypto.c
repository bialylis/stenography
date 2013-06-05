#include <openssl/evp.h>
#include "string.h"
#include <stdio.h>
#include "../lib/util.h"
#include "../lib/crypto.h"

EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode);

int encrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass) {

unsigned char key[16];
	//hacer malloc de lo que deuvle la context->key length
	unsigned char iv[16];

	// EVP_get_cipherbyname()

	EVP_CIPHER *cipher = get_evp_algorithm(algorithm,mode);

	EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass),1, key, iv);

	unsigned char *out = calloc(size+16+1,sizeof(char));
	int out_partial_size = 0;
	int out_size = 0;
	char * in2;
	int enc = 0;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, cipher, NULL, key,iv, enc);
	EVP_CipherUpdate(&ctx, out, &out_partial_size, in2, size);
	EVP_CipherFinal_ex(&ctx, out+out_partial_size, &out_size);

	EVP_CIPHER_CTX_cleanup(&ctx);
	return 0;
}

int decrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass) {
	//hacer malloc de lo que deuvle la context->key length
	unsigned char key[16];
	//hacer malloc de lo que deuvle la context->key length
	unsigned char iv[16];

	// EVP_get_cipherbyname()

	EVP_CIPHER *cipher = get_evp_algorithm(algorithm,mode);

	EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass),1, key, iv);

	unsigned char *out = calloc(size+16+1,sizeof(char));
	int out_partial_size = 0;
	int out_size = 0;
	char * in2;
	int enc = 1;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, cipher, NULL, key,iv, enc);
	EVP_CipherUpdate(&ctx, out, &out_partial_size, in2, size);
	EVP_CipherFinal_ex(&ctx, out+out_partial_size, &out_size);

	EVP_CIPHER_CTX_cleanup(&ctx);

	return 0;
}

EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode){
	if(strcmp(algorithm, AES_128)==0){
		if(strcmp(mode, ECB)){
			return EVP_get_cipherbyname("aes_128_cbc");
		}else if(strcmp(mode, CFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, OFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, CBC)){
			return EVP_get_cipherbyname("aes_128_des");
		}
	}else if(strcmp(algorithm, AES_192)==0){
		if(strcmp(mode, ECB)){
			return EVP_get_cipherbyname("aes_128_cbc");
		}else if(strcmp(mode, CFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, OFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, CBC)){
			return EVP_get_cipherbyname("aes_128_des");
		}
	}else if(strcmp(algorithm, AES_256)==0){
		if(strcmp(mode, ECB)){
			return EVP_get_cipherbyname("aes_128_cbc");
		}else if(strcmp(mode, CFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, OFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, CBC)){
			return EVP_get_cipherbyname("aes_128_des");
		}
	}else if(strcmp(algorithm, DES)==0){
		if(strcmp(mode, ECB)){
			return EVP_get_cipherbyname("aes_128_cbc");
		}else if(strcmp(mode, CFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, OFB)){
			return EVP_get_cipherbyname("aes_128_des");
		}else if(strcmp(mode, CBC)){
			return EVP_get_cipherbyname("aes_128_des");
		}
	}
}
