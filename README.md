The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Examples:

//JPG
./stegobmp --extract  -p resources/example/loimposibleE.bmp -o resources/example/out/salida1 -s LSBE


//MP3
./stegobmp --extract -p resources/example/sherlock1.bmp -o resources/example/out/salida2  -s LSB1


//MP3
./stegobmp --extract -p resources/example/sherlock4.bmp -o resources/example/out/salida3  -s LSB4

