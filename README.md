TP2 Criptografía y Segunidad
============================

The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Example1:

//JPG 135054 bytes
./stegobmp --extract  -p resources/example/loimposibleE.bmp -o resources/example/out/salida1 -s LSBE


//MP3 2348246 bytes
./stegobmp --extract -p resources/example/sherlock1.bmp -o resources/example/out/salida2  -s LSB1


//MP3 2348246 bytes
./stegobmp --extract -p resources/example/sherlock4.bmp -o resources/example/out/salida3  -s LSB4

//MP3 2348246 bytes
Encripción: 2348255 bytes
./stegobmp --extract -p resources/example/sherlock4aes256ofb.bmp -o resources/example/out/salida4  -s LSB4 -a aes256 -m ofb --pass secreto

Example2:

//WMV 908KB
./stegobmp --extract  -p resources/example2/loimposible.bmp -o resources/example2/out/salida1 -s LSB1

//PNG 42852 bytes => .zip => .txt with instructions
./stegobmp --extract  -p resources/example2/ironlady.bmp -o resources/example2/out/salida2 -s LSB4

//PDF 6KB
./stegobmp --extract  -p resources/example2/hugo.bmp -o resources/example2/out/salida2 -s LSBE

Our examples:

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB1
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSB1

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB4
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSB4

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSBE
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSBE

//NO ANDA
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB4 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/ocultado.bmp -o resources/mensajeout  -s LSB4 -a aes128 -m cbc --pass cripto



