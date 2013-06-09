#!/bin/bash 

# remove stegobmp and build its latest version
echo "Building program's latest version\n"
rm stegobmp
make

#clear tests folder
echo "Clearing tests folder\n"

rm -rf ./resoureces/tests/tests1/*
rm -rf ./resoureces/tests/tests2/*
rm -rf ./resoureces/tests/tests3/*

echo "Test #1: encrypt message with AES128 - LSB1 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests1/ocultadoLSB1.bmp -s LSB1 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests1/ocultadoLSB1.bmp -o resources/tests/tests1/mensajeoutLSB1  -s LSB1 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"


echo "Test #2: encrypt message with AES128 - LSB4 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests1/ocultadoLSB4.bmp -s LSB4 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests1/ocultadoLSB4.bmp -o resources/tests/tests1/mensajeoutLSB4  -s LSB4 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"



echo "Test #3: encrypt message with AES128 - LSBE - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests1/ocultadoLSBE.bmp -s LSBE -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests1/ocultadoLSBE.bmp -o resources/tests/tests1/mensajeoutLSBE  -s LSBE -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"



echo "Done with AES128!\n"

echo "Test #1: encrypt message with AES256 - LSB1 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests2/ocultadoLSB1.bmp -s LSB1 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests2/ocultadoLSB1.bmp -o resources/tests/tests2/mensajeoutLSB1  -s LSB1 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"


echo "Test #2: encrypt message with AES256 - LSB4 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests2/ocultadoLSB4.bmp -s LSB4 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests2/ocultadoLSB4.bmp -o resources/tests/tests2/mensajeoutLSB4  -s LSB4 -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"



echo "Test #3: encrypt message with AES256 - LSBE - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests2/ocultadoLSBE.bmp -s LSBE -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests2/ocultadoLSBE.bmp -o resources/tests/tests2/mensajeoutLSBE  -s LSBE -a aes128 -m cbc --pass cripto
echo "Done!\n\n\n\n"

echo "Done with AES 256!\n"

echo "Test #1: encrypt message with DES - LSB1 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests4/ocultadoLSB1.bmp -s LSB1 -a des -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests4/ocultadoLSB1.bmp -o resources/tests/tests4/mensajeoutLSB1  -s LSB1 -a des -m cbc --pass cripto
echo "Done!\n\n\n\n"


echo "Test #2: encrypt message with DES - LSB4 - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests4/ocultadoLSB4.bmp -s LSB4 -a des -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests4/ocultadoLSB4.bmp -o resources/tests/tests4/mensajeoutLSB4  -s LSB4 -a des -m cbc --pass cripto
echo "Done!\n\n\n\n"



echo "Test #3: encrypt message with AES256 - LSBE - CBC - pass -> cripto\n"
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/tests/tests4/ocultadoLSBE.bmp -s LSBE -a des -m cbc --pass cripto
./stegobmp --extract -p resources/tests/tests4/ocultadoLSBE.bmp -o resources/tests/tests4/mensajeoutLSBE  -s LSBE -a des -m cbc --pass cripto
echo "Done!\n\n\n\n"


echo "Done with personal tests!\n"
echo "Now testing with external examples\n\n"

echo "Recovering unecrypted file with LSBE"
./stegobmp --extract  -p resources/example/loimposibleE.bmp -o resources/tests/tests3/salida1 -s LSBE
echo "Done! \n\n"


echo "Recovering unencryped file with LSB1"
./stegobmp --extract -p resources/example/sherlock1.bmp -o resources/tests/tests3/salida2  -s LSB1
echo "Done!\n\n"

echo "Recovering unencrypted file with LSB4"
./stegobmp --extract -p resources/example/sherlock4.bmp -o resources/tests/tests3/salida3  -s LSB4
echo "Done!\n\n"

echo "Recovering encrypted file with AES256 - OFB - pass -> secreto and steganographed with LSB4"
./stegobmp --extract -p resources/example/sherlock4aes256ofb.bmp -o resources/tests/tests3/salida4  -s LSB4 -a aes256 -m ofb --pass secreto
echo "Done!\n\n"


echo "Done with all tests. Please check in ./resources/tests all the folders\n"
echo "	Folders 1 and 2 must contain 3 files each with the text \"Texto a ocultar\"\n"
echo "	Folder 3 must contain one JPG file and two .mp3 files\n"
