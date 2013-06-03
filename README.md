The following libraries must be installed:
  apt-get install libmcrypt-dev
  apt-get install libargtable2-dev

and then build executing make


Examples:

./stegobmp --embed -i resources/mensaje.txt -p resources/example/loimposibleE.bmp -o resources/example/out/loimposibleE.bmp -s LSBE
./stegobmp --extract  -p resources/example/out/loimposibleE.bmp -o resources/out/mensaje1.txt -s LSBE


./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock1.bmp -o resources/example/out/sherlock1.bmp -s LSB1
./stegobmp --extract -p resources/example/out/sherlock1.bmp -o resources/out/mensaje2.txt  -s LSB1

./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock4.bmp -o resources/example/out/sherlock4.bmp -s LSB4
./stegobmp --extract -p resources/example/out/sherlock4.bmp -o resources/out/mensaje3.txt  -s LSB4

./stegobmp --embed -i resources/mensaje.txt -p resources/example/sherlock4aes256ofb.bmp -o resources/example/out/sherlock4aes256ofb.bmp -s LSB4 -a aes256 -m ofb --pass secreto


