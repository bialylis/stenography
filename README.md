TP2 Criptografía y Segunidad
============================

The libargtable2-dev library must be installed:
	apt-get install libargtable2-dev 
	
In the root of the project the following scripts can be found:
	1) desafio.sh with the commands to get the hidden video.
	2) test.sh with several tests


To run the previously mentioned scripts, run "sh scriptname.sh"

Arguments are:
 [--extract] [--embed] [-i <input hide file>] -p <input bmp> -o <output bmp> -s LSB1|LSB4|LSBE [-a aes128|aes192|aes256|des] [-m ecb|cfb|ofb|cbc] [-P <char>]

Required parameteres:
 --extract:	Indica que se va a extraer información.
 --embed: Indica que se va a ocultar información.
 -i o --in: Archivo que se va a ocultar.
 -p: Archivo bmp portador.
 -o o --out: Archivo de salida.
 -s o --steg LSB1|LSB4|LSBE: Algoritmo de esteganografiado.

Optional parameters:
 -a aes128|aes192|aes256|des: Algoritmo de encriptación/desencriptación.
 -m ecb|cfb|ofb|cbc: Modo de encriptación/desencriptación.
 -P o --pass: Contraseña para la encriptación.





