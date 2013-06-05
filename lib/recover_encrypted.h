#ifndef __RECOVERENCRYPTED__
#define __RECOVERENCRYPTED__

char * recover_encrypted_msg(const char* filename, char algorithm, unsigned long *size);
char * parse_decrypted(char * decrypted, unsigned long size);

#endif
