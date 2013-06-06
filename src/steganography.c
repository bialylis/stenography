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
	int length =0;
	char* msg = parse_message(in,&length);

	//Message new size
	int size = *((int*) msg);
	printf("Hidden size: %d\n", ntohl(size));
	if (*pass) {
		int encrypted_size = 0;
		char * encrypted = (unsigned char*)encrypt(msg, &encrypted_size, a, m, pass,length);
		msg = calloc(encrypted_size + FILE_LENGTH_SIZE, sizeof(char));
		encrypted_size = ntohl(encrypted_size);
		memcpy(msg, &encrypted_size, FILE_LENGTH_SIZE*sizeof(char));
		encrypted_size = ntohl(encrypted_size);
		memcpy(msg+FILE_LENGTH_SIZE, encrypted, encrypted_size*sizeof(char));
		length = encrypted_size;
	}
	hide_message(p, msg, out, get_algorithm(steg), length);
	return 0;
}

// 15 || texto a ocultar || .txt ok ==> 24
// pepe || enc(15 || texto a ocultar ||  .txt) => encrypted_size

int ext(const char * p, const char * out, const char * steg, const char * a,
		const char * m, const char * pass) {
	char* IV = "AAAAAAAAAAAAAAAA";
	int keysize = 16; /* 128 bits */
	char* buffer;
	int parsed_steg = get_algorithm(steg);
	int extension_size = 0;
	char * extension;
	char * output;
	char * recovered;
	if (*pass) {

		//Stenograph the encrypted message
		char * recovered_encrypted = recover_encrypted_msg(p, parsed_steg);

		//Desencrypt the recovered message
		int decrypted_size = 0;
		char * decrypted = (unsigned char*)decrypt(recovered_encrypted, &decrypted_size, a, m,
				pass);

		//Parse desencrypted message
		recovered = parse_decrypted(decrypted, &extension, &extension_size,
				decrypted_size);
		output = recovered;
	} else {
		recovered = recover_msg(p, parsed_steg, &extension_size, &extension);
		output = recovered + FILE_LENGTH_SIZE;
	}

	// printf("Size recovered: %d - Extension: %s\n", *((int*) recovered),
	// 		extension);

	char * new_out = calloc(strlen(out) + extension_size, sizeof(char*));
	memcpy(new_out, out, strlen(out)*sizeof(char*));
	strcat(new_out, extension);
	FILE* out_file = fopen(new_out, "w");
	fwrite(output, 1, *((int*) recovered), out_file);
	fclose(out_file);

	return 0;
}
