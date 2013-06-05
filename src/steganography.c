#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/stenography.h"
#include "../lib/recover.h"
#include "../lib/recover_encrypted.h"
#include "../lib/hide.h"

int emb(const char* in, const char * p, const char * out, const char * steg,
		const char * a, const char * m, const char * pass) {
	char* IV = "AAAAAAAAAAAAAAAA";
	int keysize = 16; /* 128 bits */
	char* msg = parse_message(in);

	//Message new size
	int size = *((int*) msg);
	printf("Hidden size: %d\n", size);

	if (*pass) {
		char* buffer;
		int buffer_len = ceil(size / 16.0) * 16;
		buffer = calloc(1, buffer_len);
		memcpy(buffer, msg, buffer_len);

		encrypt(buffer, buffer_len, IV, pass, keysize, a, m);
		char* encrypted = preappend_size(buffer);
		printf("Encrypted:%d %s\n", *((int*) encrypted), encrypted + 4);
		msg = encrypted;
	}
	hide_message(p, msg, out, get_algorithm(steg));
	return 0;
}

int ext(const char * p, const char * out, const char * steg, const char * a,
		const char * m, const char * pass) {
	char* IV = "AAAAAAAAAAAAAAAA";
	int keysize = 16; /* 128 bits */
	char* buffer;
	int parsed_steg = get_algorithm(steg);
	int extension_size = 0;
	char * extension;
	if(*pass){
		int decrypted_size = 0;

		//Stenograph the encrypted message
		char * recovered_encrypted = recovered_encrypted(p,parsed_steg);

		//Desencrypt the recovered message
		int decrypted_size = 0;
		char * decrypted = decrypt(recovered_encrypted, &decrypted_size, a, m, pass);
		
		//Parse desencrypted message
		output = parse_decrypted(decrypted, decrypted_size);
	}else{
		char* recovered = recover_msg(p, parsed_steg, &extension_size, &extension);
		output = recovered + FILE_LENGTH_SIZE;
	}

	printf("Size recovered: %d - Extension: %s\n", *((int*) recovered),
			extension);

	char * new_out = calloc(strlen(out) + extension_size, sizeof(char*));
	memcpy(new_out, out, strlen(out)*sizeof(char*));
	strcat(new_out, extension);
	FILE* out_file = fopen(new_out, "w");
	fwrite(output, 1, encrypted_size, out_file);
	fclose(out_file);

	return 0;
}
