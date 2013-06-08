#!/bin/bash 

# remove stegobmp and build its latest version
echo "Building program's latest version\n"
rm stegobmp
make

#clear tests folder
echo "Clearing tests folder\n"
rm -rf ./resources/tests/*

echo "Test #1: encrypt message with AES128 - LSB1 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/ocultadoLSB1.bmp -s LSB1 -a aes128 -m cbc --pass cripto
echo "Ok... message hidden... now decrypting it...\n"
./stegobmp --extract -p resources/tests/ocultadoLSB1.bmp -o resources/tests/mensajeoutLSB1  -s LSB1 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"


echo "Test #2: encrypt message with AES128 - LSB4 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/ocultadoLSB4.bmp -s LSB4 -a aes128 -m cbc --pass cripto
echo "Ok... message hidden... now decrypting it...\n"
./stegobmp --extract -p resources/tests/ocultadoLSB4.bmp -o resources/tests/mensajeoutLSB4  -s LSB4 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"



echo "Test #3: encrypt message with AES128 - LSBE - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/ocultadoLSBE.bmp -s LSBE -a aes128 -m cbc --pass cripto
echo "Ok... message hidden... now decrypting it...\n"
./stegobmp --extract -p resources/tests/ocultadoLSBE.bmp -o resources/tests/mensajeoutLSBE  -s LSBE -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"
