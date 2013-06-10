#include <argtable2.h>
#include "string.h"
#include <stdio.h>
#include "../lib/stenography.h"

int main(int argc, char **argv){

	/*Required parameters*/
	struct arg_lit 	* extract = arg_lit0(NULL,"extract",						"Indica que se va a extraer información.");
	struct arg_lit 	* embed	= arg_lit0(NULL,"embed",							"Indica que se va a ocultar información.");
	struct arg_file * in 	= arg_file0("i", "in", "<input hide file>",			"Archivo que se va a ocultar");
	struct arg_file * p 	= arg_file1("p", NULL, "<input bmp>",				"Archivo bmp portador");
	struct arg_file * out	= arg_file1("o", "out", "<output bmp>",				"Archivo de salida");
	struct arg_rex 	* steg 	= arg_rex1("s", "steg", "LSB1|LSB4|LSBE", NULL, 1,	"Algoritmo de esteganografiado");

	/*Optional parameters*/
	struct arg_rex 	* a 	= arg_rex0("a", NULL, "aes128|aes192|aes256|des", NULL,	1,	"Algoritmo de encriptación/desencriptación");
	struct arg_rex * m 	= arg_rex0("m", NULL, "ecb|cfb|ofb|cbc", NULL, 1,				"Modo de encriptación/desencriptación");
	struct arg_str 	* pass 	= arg_str0("P", "pass", "<char>",							"Contraseña para la encriptación");

	struct arg_end  * end    = arg_end(20);

	void * argtable[] = {extract, embed, in, p, out, steg, a, m, pass, end};

	const char* progname = "stegobmp";
	int exitcode = 0;
	int nerrors;

	if (arg_nullcheck(argtable) != 0){
		exitcode = 1;
	}

	/* Set default argument values */
	a->sval[0] = "aes128";
	m->sval[0] = "cbc";

	nerrors = arg_parse(argc,argv,argtable);

	if(extract->count > 0 && embed->count > 0) {
		nerrors = 1;
	}

	if (nerrors > 0){
		printf("Parametro/s inválidos. Los parametros son los siguientes: \n");
		arg_print_syntax(stdout,argtable,"\n");
		exitcode = 1;
		return exitcode;
	}


	if(extract->count > 0) {
		exitcode = ext(p->filename[0], out->filename[0], steg->sval[0], a->sval[0], m->sval[0], pass->sval[0]);
	}

	if(embed->count > 0) {
		exitcode = emb(in->filename[0], p->filename[0], out->filename[0], steg->sval[0], a->sval[0], m->sval[0], pass->sval[0]);
	}


	arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));

	return exitcode;

}
