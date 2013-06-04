#ifndef __RECOVERENCRYPTED__
#define __RECOVERENCRYPTED__

char * recover_encrypted_msg(const char* filename, char algorithm,
		const char * encrypt_algorithm, const char *encrypt_mode, const char * pass);

#endif
