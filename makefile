stegobmp: args.c hide.c stenography.c crypto.c
	gcc -o resources/stegobmp src/args.c src/hide.c src/stenography.c src/crypto.c -lm -lmcrypt -largtable2