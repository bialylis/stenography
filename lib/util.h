#ifndef __UTIL__
#define __UTIL__

#include <mcrypt.h>

#define LSB1 1
#define LSB4 2
#define LSBE 3
#define AES_128 MCRYPT_RIJNDAEL_128
#define DES MCRYPT_3DES

/* Get  methods */
char get_bit(char* bytes, int n);
char get_nibble(char* bytes, int n);

/* Parse methods */

int get_algorithm(const char* string);
char* parse_message(const char* filename);
char* preappend_size(char* msg);

#endif
