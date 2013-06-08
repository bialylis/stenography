#!/bin/bash 
echo "Este script corre lo necesario para generar los archivos de salida a partir de aquellos dados por la catedra\n\n"

rm -rf ./resources/example2/out/*

echo "1) Extrayendo de ironlady.bmp utilizando LSB4\n\n"
#//PNG 42852 bytes => .zip => .txt with instructions
./stegobmp --extract  -p resources/example2/ironlady.bmp -o resources/example2/out/salida2 -s LSB4

echo "2) Extrayendo de hugo.bmp utilizando LSBE\n\n"
#//PDF 6KB
./stegobmp --extract  -p resources/example2/hugo.bmp -o resources/example2/out/salida2 -s LSBE

echo "3) Extrayendo de loimposible.bmp utilizando DES - CBC - pass -> desafio y LSB1\n\n"
./stegobmp --extract -p resources/example2/loimposible.bmp -o resources/example2/out/video  -s LSB1 -a des -m cbc --pass desafio
