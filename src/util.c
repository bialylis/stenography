#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/util.h"

char get_bit(char* bytes, int n) {
	return (bytes[n / 8] >> (7 - (n % 8))) & 1;
}

char get_nibble(char* bytes, int n) {
	return (bytes[n / 2] >> (4 * ((n + 1) % 2))) & 0x0F;
}

char *parse_extension(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot;
}

int get_file_size(const char* filename){
	FILE* f = fopen(filename,"rb");
	fseek(f,0,SEEK_END);
	int size = ftell(f);
	fclose(f);
	return size;
}

int steg_from_string(const char* string){
	if(strcmp(string,"LSBE")==0){
		return LSBE;
	}else if(strcmp(string,"LSB4")==0){
		return LSB4;
	}else{
		return LSB1;
	}
}



char* parse_message_to_hide(const char* filename){
	FILE* in = fopen(filename,"r");
	char* extension = parse_extension(filename);
	int size = get_file_size(filename);

	// Length = 4 (del tamaño) + longitud archivo + e (extensión)
	int length = 4+ size + strlen(extension)+1;

	printf("Size: %d, Extension: %s\n",length,extension);
	char* msg = malloc(length);
	char c, *p=msg, i;
	p+=4;
	memcpy(msg, &length, 4);
	while((c=fgetc(in))!=-1){
		*p = c;
		p++;
	}
	fclose(in);
	strcpy(p,extension);
	return msg;
}

char* preappend_size(char* msg){
	int length = strlen(msg)+4;
	char* out = malloc(length);
	char c, *p=out, i;
	p+=4;
	memcpy(out, &length, 4);
	strcpy(out+4,msg);
	return out;
}
