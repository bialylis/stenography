#ifndef __UTIL__
#define __UTIL__


#define LSB1 1
#define LSB4 2
#define LSBE 3
#define LSBE_BYTE_SET_1 255
#define LSBE_BYTE_SET_2 254

#define HEADER_BYTES 54
#define FILE_LENGTH_SIZE 4
#define BITS_PER_BYTE 8

/* Get  methods */
char get_bit(char* bytes, int n);
char get_nibble(char* bytes, int n);

/* Parse methods */

int get_algorithm(const char* string);
char* parse_message(const char* filename);
char* preappend_size(char* msg);

#endif
