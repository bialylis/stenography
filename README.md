The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Examples:

./stegobmp --embed -i resources/mensaje.txt -p resources/example/loimposibleE.bmp -o resources/example/loimposibleE1.bmp -s LSBE
./stegobmp --extract  -p resources/example/loimposibleE1.bmp -o resources/mensaje1.txt -s LSBE


./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock1.bmp -o resources/example/sherlock1out.bmp -s LSB1
./stegobmp --extract -p resources/example/sherlock1out.bmp -o resources/mensaje2.txt  -s LSB1

./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock4.bmp -o resources/example/sherlock4out.bmp -s LSB4
./stegobmp --extract -p resources/example/sherlock4out.bmp -o resources/mensaje3.txt  -s LSB4

./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock4aes128cbc.bmp -o resources/example/sherlock4aes128cbcout.bmp -s LSB4 -a aes128 -m ecb --pass secreto


