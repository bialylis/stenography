The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Example:

./stegobmp --embed -i resources/mensaje.txt -P resources/example/loimposibleE.bmp -o "loimposibleE1.bmp" -s LSBE
