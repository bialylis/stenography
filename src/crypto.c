#include <openssl/evp.h>
#include "string.h"
#include <stdio.h>
#include "../lib/util.h"
#include "../lib/crypto.h"

EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode);

char * encrypt(char * original, int * encrypted_size, const char* algorithm, const char * mode,
		const char * pass) {

	unsigned char key[16];
	//hacer malloc de lo que deuvle la context->key length
	unsigned char iv[16];

	EVP_CIPHER *cipher = get_evp_algorithm(algorithm,mode);

	EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass),1, key, iv);

	char *out = calloc(strlen(original)+16+1,sizeof(char));
	int out_partial_size = 0;
	int out_size = 0;

	int enc = 0;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, cipher, NULL, key,iv, enc);
	EVP_CipherUpdate(&ctx, out, &out_partial_size, original, strlen(original));
	EVP_CipherFinal_ex(&ctx, out+out_partial_size, encrypted_size);

	EVP_CIPHER_CTX_cleanup(&ctx);
	return out;
}

char * decrypt(char * encrypted,int * decrypted_size, const char* algorithm, const char * mode,
		const char * pass) {
	//hacer malloc de lo que deuvle la context->key length
	unsigned char key[16];
	//hacer malloc de lo que deuvle la context->key length
	unsigned char iv[16];

	EVP_CIPHER *cipher = get_evp_algorithm(algorithm,mode);

	EVP_BytesToKey(cipher, EVP_md5(), NULL, pass, strlen(pass),1, key, iv);

	char *out = calloc(strlen(encrypted)+16+1,sizeof(char));
	int out_partial_size = 0;
	int out_size = 0;
	int enc = 1;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, cipher, NULL, key,iv, enc);
	EVP_CipherUpdate(&ctx, out, &out_partial_size, encrypted, strlen(encrypted));
	EVP_CipherFinal_ex(&ctx, out+out_partial_size, decrypted_size);

	EVP_CIPHER_CTX_cleanup(&ctx);

	return out;
}

EVP_CIPHER * get_evp_algorithm(const char*algorithm, const char * mode){
	if(strcmp(algorithm, AES_128)==0){
		if(strcmp(mode, ECB)==0){
			return EVP_get_cipherbyname("aes_128_ecb");
		}else if(strcmp(mode, CFB)==0){
			return EVP_get_cipherbyname("aes_128_cfb");
		}else if(strcmp(mode, OFB)==0){
			return EVP_get_cipherbyname("aes_128_ofb");
		}else if(strcmp(mode, CBC)==0){
			return EVP_get_cipherbyname("aes_128_cbc");
		}
	}else if(strcmp(algorithm, AES_192)==0){
		if(strcmp(mode, ECB)==0){
			return EVP_get_cipherbyname("aes_192_ecb");
		}else if(strcmp(mode, CFB)==0){
			return EVP_get_cipherbyname("aes_192_cfb");
		}else if(strcmp(mode, OFB)==0){
			return EVP_get_cipherbyname("aes_192_ofb");
		}else if(strcmp(mode, CBC)==0){
			return EVP_get_cipherbyname("aes_192_cbc");
		}
	}else if(strcmp(algorithm, AES_256)==0){
		if(strcmp(mode, ECB)==0){
			return EVP_get_cipherbyname("aes_256_ecb");
		}else if(strcmp(mode, CFB)==0){
			return EVP_get_cipherbyname("aes_256_cfb");
		}else if(strcmp(mode, OFB)==0){
			return EVP_get_cipherbyname("aes_256_ofb");
		}else if(strcmp(mode, CBC)){
			return EVP_get_cipherbyname("aes_256_cbc");
		}
	}else if(strcmp(algorithm, DES)==0){
		if(strcmp(mode, ECB)==0){
			return EVP_get_cipherbyname("des_ecb");
		}else if(strcmp(mode, CFB)==0){
			return EVP_get_cipherbyname("des_cfb");
		}else if(strcmp(mode, OFB)==0){
			return EVP_get_cipherbyname("des_ofb");
		}else if(strcmp(mode, CBC)==0){
			return EVP_get_cipherbyname("des_cbc");
		}
	}
}
