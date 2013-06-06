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


./stegobmp --extract -p resources/example/sherlock4aes256ofb.bmp -o resources/example/out/salida4  -s LSB4 -a aes256 -m ofb --pass secreto

Example2:

//WMV
./stegobmp --extract  -p resources/example2/loimposible.bmp -o resources/example2/out/salida1 -s LSB1

Our examples:

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB1
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSB1

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB4
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSB4


//NO ANDA
./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSBE
./stegobmp --extract  -p resources/ocultado.bmp -o resources/mensajeout -s LSBE

./stegobmp --embed --in resources/mensaje.txt  -p resources/example/loimposibleE.bmp -o resources/ocultado.bmp -s LSB1 -a aes128 -m cbc --pass cripto
./stegobmp --extract -p resources/ocultado.bmp -o resources/mensajeout  -s LSB1 -a aes128 -m cbc --pass cripto



