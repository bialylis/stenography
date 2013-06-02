#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/recover.h"

char* recover_lsb1(FILE* in);
char* recover_lsb4(FILE* in);
char* recover_lsbe(FILE* in);

char* recover_msg(const char* filename, char algorithm) {
	char* msg;
	FILE* in = fopen(filename, "rb");
	fseek(in, 54, SEEK_SET);
	switch (algorithm) {
	case LSB1:
		msg = recover_lsb1(in);
		break;
	case LSB4:
		msg = recover_lsb4(in);
		break;
	case LSBE:
		msg = recover_lsbe(in);
		break;
	}
	fclose(in);
	return msg;
}

char* recover_lsb1(FILE* in){
	char c, hidden, *msg;
	unsigned long size=0, i;
	for(i=0; i<4*8; i++){
		hidden = fgetc(in);
		*(((char*)&size)+i/8)|=((hidden&1)<<7-(i%8));
	}
	msg = calloc(size+4, sizeof(char));
	memcpy(msg, &size, 4);
	msg+=4;
	for(i=0; i<(size-4)*8; i++){
		hidden = fgetc(in);
		*(msg+i/8)|=((hidden&1)<<7-(i%8));
	}
	msg[i/8]=0;
	return msg-4;
}

char* recover_lsb4(FILE* in){
	char c, hidden, *msg;
	unsigned long size=0, i;
	for(i=0; i<4*2; i++){
		hidden = fgetc(in);
		*(((char*)&size)+i/2)|=((hidden&0x0F)<<(4*((i+1)%2)));
	}
	msg = calloc(size+4, sizeof(char));
	memcpy(msg, &size, 4);
	msg+=4;
	for(i=0; i<(size-4)*2; i++){
		hidden = fgetc(in);
		*(msg+i/2)|=((hidden&0x0F)<<(4*((i+1)%2)));
	}
	msg[i/2]=0;
	return msg-4;
}

char* recover_lsbe(FILE* in){
	unsigned char c, hidden, *msg;
	unsigned long size=0, i=0;
	while(i<4*8){
		hidden = fgetc(in);
		if(hidden==255 || hidden==254){
			*(((char*)&size)+i/8)|=((hidden&1)<<7-(i%8));
			i++;
		}
	}
	msg = calloc(size+4, sizeof(char));
	memcpy(msg, &size, 4);
	msg+=4;
	i=0;
	while(i<(size-4)*8){
		hidden = fgetc(in);
		if(hidden==255 || hidden==254){
			*(msg+i/8)|=((hidden&1)<<7-(i%8));
			i++;
		}
	}
	msg[i/8]=0;
	return msg-4;
}
