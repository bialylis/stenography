stegobmp: src/args.c src/hide.c src/stenography.c src/crypto.c
	gcc -o stegobmp src/args.c src/hide.c src/stenography.c src/crypto.c -lm -lmcrypt -largtable2