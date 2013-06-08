stegobmp: src/args.c src/hide.c src/steganography.c src/crypto.c src/util.c src/recover.c src/recover_encrypted.c
	gcc -g -o stegobmp src/args.c src/hide.c src/steganography.c src/crypto.c src/util.c src/recover.c src/recover_encrypted.c -lm -lssl -largtable2 -lcrypto
