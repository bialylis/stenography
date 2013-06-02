#ifndef __CRYPTO__
#define __CRYPTO__

int encrypt(
    void* buffer,
    int buffer_len,
    char* IV,
    char* key,
    int key_len,
    char* algorithm,
    char* mode
);

int decrypt(
    void* buffer,
    int buffer_len,
    char* IV,
    char* key,
    int key_len,
    char* algorithm,
    char* mode
);

#endif
