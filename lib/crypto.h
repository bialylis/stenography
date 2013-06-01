#ifndef __CRYPTO__
#define __CRYPTO__

int encrypt(
    void* buffer,
    int buffer_len, /* Because the plaintext could include null bytes*/
    char* IV,
    char* key,
    int key_len,
    char* alg,
    char* chain
);

int decrypt(
    void* buffer,
    int buffer_len,
    char* IV,
    char* key,
    int key_len,
    char* alg,
    char* chain
);

#endif
