#ifndef __UTIL__
#define __UTIL__

#define LSB1 1
#define LSB4 2
#define LSBE 3
#define LSBE_BYTE_SET_1 255
#define LSBE_BYTE_SET_2 254
#define LSB1_NECESSARY_SPACE 8
#define LSB4_NECESSARY_SPACE 2
#define LSBE_NECESSARY_SPACE 8

#define HEADER_BYTES 54
#define FILE_LENGTH_SIZE 4
#define BITS_PER_BYTE 8

#define AES_128 "aes128"
#define AES_192 "aes192"
#define AES_256 "aes256"
#define DES "des"

#define ECB "ecb"
#define CFB "cfb"
#define OFB "ofb"
#define CBC "cbc"

#define LSB1_RECOVER(hidden, i) ((hidden & 1) << 7 - (i % 8));
#define LSB4_RECOVER(hidden, i) ((hidden & 0x0F) << (4 * ((i + 1) % 2)));
#define LSBE_RECOVER(hidden, i) LSB1_RECOVER(hidden,i);

/* Get  methods */
char get_bit(char* bytes, int n);
char get_nibble(char* bytes, int n);

/* Parse methods */

int get_algorithm(const char* string);
char* parse_message(const char* filename, int* length);
char* preappend_size(char* msg);
int get_lsbe_bytes(const char* filename);

#endif
