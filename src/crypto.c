#include <openssl/evp.h>
#include "string.h"
#include <stdio.h>
#include "../lib/util.h"
#include "../lib/crypto.h"

#define INBUFSIZE 512
#define OUTBUFSIZE (1024*1024)

int encrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass) {

//	switch (algorithm) {
//	case AES_128:
//		break;
//	case AES_192:
//		break;
//	case AES_256:
//		break;
//	case DES:
//		break;
//	}
//
//	switch (mode) {
//	case ECB:
//		break;
//	case CFB:
//		break;
//	case OFB:
//		break;
//	case CBC:
//		break;
//	}

//	const EVP_CIPHER *EVP_des_ede3_ecb(void);
//	const EVP_CIPHER *EVP_des_ede3_cfb64(void);
//	const EVP_CIPHER *EVP_des_ede3_cfb1(void);
//	const EVP_CIPHER *EVP_des_ede3_cfb8(void);
//	const EVP_CIPHER *EVP_des_ede3_ofb(void);
//	const EVP_CIPHER *EVP_des_ede3_cbc(void);
//	const EVP_CIPHER *EVP_aes_128_ecb(void);
//	const EVP_CIPHER *EVP_aes_128_cbc(void);
//	const EVP_CIPHER *EVP_aes_128_cfb1(void);
//	const EVP_CIPHER *EVP_aes_128_cfb8(void);
//	const EVP_CIPHER *EVP_aes_128_cfb128(void);
//	const EVP_CIPHER *EVP_aes_128_ofb(void);
//	const EVP_CIPHER *EVP_aes_192_ecb(void);
//	const EVP_CIPHER *EVP_aes_192_cbc(void);
//	const EVP_CIPHER *EVP_aes_192_cfb1(void);
//	const EVP_CIPHER *EVP_aes_192_cfb8(void);
//	const EVP_CIPHER *EVP_aes_192_cfb128(void);
//	const EVP_CIPHER *EVP_aes_192_ofb(void);
//	const EVP_CIPHER *EVP_aes_256_ecb(void);
//	const EVP_CIPHER *EVP_aes_256_cbc(void);
//	const EVP_CIPHER *EVP_aes_256_cfb1(void);
//	const EVP_CIPHER *EVP_aes_256_cfb8(void);
//	const EVP_CIPHER *EVP_aes_256_cfb128(void);
//	const EVP_CIPHER *EVP_aes_256_ofb(void);


//unsigned char key[16];
//	unsigned char iv[16];

	//EVP_BytesToKey(EVP_aes_256_ofb(), EVP_md5(), NULL, pass, strlen(pass),1, key, iv);
//	EVP_CIPHER_CTX ctx = EVP_des_cbc();
	EVP_CIPHER_CTX ctx;
//	EVP_CIPHER_CTX_init(&ctx);
//	if (EVP_EncryptInit_ex(&ctx, EVP_aes_256_ofb(), NULL, key, IV) != 0) {
//		return 1;
//	}
//	if (EVP_EncryptUpdate(&ctx, buffer, &buffer_len, buffer, sizeof(buffer))
//			!= 0) {
//		return 1;
//	}
//	if (EVP_EncryptFinal(&ctx, buffer + buffer_len, &buffer_len) != 0) {
//		return 1;
//	}
//	buffer_len += buffer_len;
//	EVP_CIPHER_CTX_cleanup(&ctx);
	return 0;
}

int decrypt(FILE* in, unsigned long size, const char* algorithm, const char * mode,
		const char * pass) {
//	int cipherBlockSize, cipherKeyLength, cipherIvLength;
//	int outBytes, inBytes, tmpOutBytes, bytesInBuf, i;
//	unsigned char buf2crypt[INBUFSIZE];
//	unsigned char outBuf[OUTBUFSIZE];
//
	int tmpl, outl, inl;
	unsigned char key[16];
	unsigned char iv[16];

	//EVP_BytesToKey(EVP_aes_256_ofb(), EVP_md5(), NULL, pass, strlen(pass),1, key, iv);

//	EVP_CIPHER_CTX ctx;
//	EVP_CIPHER_CTX_init(&ctx);
//	EVP_DecryptInit_ex(&ctx, EVP_aes_256_ofb(), NULL, key, IV);
//
//	cipherBlockSize = EVP_CIPHER_CTX_block_size(&ctx);
//	cipherKeyLength = EVP_CIPHER_CTX_key_length(&ctx);
//	cipherIvLength = EVP_CIPHER_CTX_iv_length(&ctx);
//
//	inBytes = outBytes = 0;
//
//	while ((bytesInBuf = fread(buf2crypt, sizeof(char), INBUFSIZE, stdin)) > 0) {
//		fprintf(stderr, ".");
//		if ((OUTBUFSIZE - ((bytesInBuf + cipherBlockSize - 1) + outBytes)) <= 0)
//			prtErrAndExit(1,
//					"ERROR: Buffer was not big enough to hold decrypted data!!\n");
//		if (!EVP_DecryptUpdate(&ctx, outBuf + outBytes, &tmpOutBytes, buf2crypt,
//				bytesInBuf))
//			prtErrAndExit(1, "ERROR: EVP_DecryptUpdate didn't work...\n");
//		outBytes += tmpOutBytes;
//		inBytes += bytesInBuf;
//	}
//
//	EVP_DecryptFinal_ex(&ctx, outBuf + outBytes, &tmpOutBytes)
//
//	EVP_CIPHER_CTX_cleanup(&ctx);

	return 0;
}
