#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/stenography.h"
#include "../lib/recover.h"
#include "../lib/recover_encrypted.h"
#include "../lib/hide.h"

void verify_size(const char *in, const char * p, int steg);

int emb(const char* in, const char * p, const char * out, const char * steg,
		const char * a, const char * m, const char * pass) {
	int length =0;
	int parsed_steg = get_algorithm(steg);
	verify_size(in,p,parsed_steg);

	char* msg = parse_message(in,&length);

	//Message new size
	int size = *((int*) msg);
	if (*pass) {
		int encrypted_size = 0;
		char * encrypted = (unsigned char*)encrypt(msg, &encrypted_size, a, m, pass,length);
		msg = calloc(encrypted_size + FILE_LENGTH_SIZE, sizeof(char));
		encrypted_size = ntohl(encrypted_size);
		memcpy(msg, &encrypted_size, FILE_LENGTH_SIZE*sizeof(char));
		encrypted_size = ntohl(encrypted_size);
		memcpy(msg+FILE_LENGTH_SIZE, encrypted, encrypted_size*sizeof(char));
		length = encrypted_size+FILE_LENGTH_SIZE;
	}
	hide_message(p, msg, out, parsed_steg, length);
	return 0;
}

int ext(const char * p, const char * out, const char * steg, const char * a,
		const char * m, const char * pass) {
	int parsed_steg = get_algorithm(steg);
	int extension_size = 0;
	char * extension;
	char * output;
	char * recovered;
	if (*pass) {

		//Stenograph the encrypted message
		char * recovered_encrypted = recover_encrypted_msg(p, parsed_steg);

		//Decrypt the recovered message
		int decrypted_size = 0;
		char *out = malloc(*((int*) recovered_encrypted)* sizeof(char)+200*sizeof(char));
		char * decrypted = (char*)decrypt(recovered_encrypted, &decrypted_size, a, m,
				pass, out);

		//Parse desencrypted message
		recovered = parse_decrypted(out, &extension, &extension_size, decrypted_size);
		output = recovered + FILE_LENGTH_SIZE * sizeof(char);
	} else {
		recovered = recover_msg(p, parsed_steg, &extension_size, &extension);
		output = recovered + FILE_LENGTH_SIZE * sizeof(char);
	}
	char * new_out = calloc(strlen(out) + extension_size, sizeof(char*));
	memcpy(new_out, out, strlen(out)*sizeof(char*));
	strcat(new_out, extension);
	FILE* out_file = fopen(new_out, "w");
	fwrite(output, 1, *((int*) recovered), out_file);
	fclose(out_file);

	return 0;
}

void verify_size(const char *in, const char * p, int steg){
	int in_necessary_size = get_file_size(in);
	int p_available_size = 0;
	switch(steg){
	case LSB1:
				p_available_size = (get_file_size(p)-HEADER_BYTES)/LSB1_NECESSARY_SPACE;
				break;
	case LSB4:
				p_available_size = (get_file_size(p)-HEADER_BYTES)/LSB4_NECESSARY_SPACE;
				break;
	case LSBE:
				p_available_size = get_lsbe_bytes(p)/LSBE_NECESSARY_SPACE;
				break;
	}

	if(in_necessary_size > p_available_size ){
		printf("Tamaño de BMP portador insuficiente:\nTamaño a ocultar: %d\nTamaño disponible: %d\n",in_necessary_size,p_available_size);
		exit(EXIT_FAILURE);
	}
}
