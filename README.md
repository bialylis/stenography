The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Example:

./stegobmp --embed -i resources/mensaje.txt -p resources/example/loimposibleE.bmp -o resources/example/loimposibleE1.bmp -s LSBE
./stegobmp --extract  -p resources/example/loimposibleE1.bmp -o resources/mensaje1.txt -s LSBE
