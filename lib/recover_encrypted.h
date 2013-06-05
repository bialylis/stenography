#ifndef __RECOVERENCRYPTED__
#define __RECOVERENCRYPTED__

char * recover_encrypted_msg(const char* filename, int algorithm);
char * parse_decrypted(char * decrypted, char**extension, int *extension_size, unsigned long size);

#endif
