#include <cstdlib>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>
#include <ctype.h>
#include "ClassVisao.h"
#include "Utils.h"
#include "Heap.h"
#include "InstanceClass.h"
#include "LeitorExibidor.h"
#include "MethodArea.h"
#include "Operations.h"
#include "StaticClass.h"


int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	const char *file_className = argv[2];

	// Carregamento da classe de entrada.
	MethodArea &methodArea = MethodArea::getInstance();
	StaticClass *classRuntime = methodArea.carregarClassNamed(file_className);
	// Fim do carregamento.

	// Verificação se o nome da classe de entrada é igual ao nome do arquivo.
	string className = Utils::getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->this_class);

	string fileName(file_className);

	int TamStr = fileName.length(), i;
	for (i = 0; i < TamStr; i++) {                            // Converte cada caracter de Str
		fileName[i] = toupper(fileName[i]);  // para maiusculas
	}

	TamStr = className.length();
	for (i = 0; i < TamStr; i++) {                            // Converte cada caracter de Str
		className[i] = toupper(className[i]);  // para maiusculas
	}
	if (!Utils::verificarThisClass(fileName, className)) {
		cerr << "Nome do arquivo diferente do nome da classe." << endl;
		exit(1);
	}

	// Fim da verificação
	if (argv[1][1] == 'e') { //exibidor
		//const char *file_output = (argc < 3) ? NULL : argv[2];
		string nome = StaticClass::extrairNomeArquivo(argv);
		FILE *output = fopen(nome.append(".txt").c_str(), "w+");
		if (output == NULL) {
			cerr << "Erro ao abrir arquivo " << nome << "." << endl;
			exit(2);
		}
		printArquivoClassFile(classRuntime->getClassFile(), output);
		exibeClassFile(classRuntime->getClassFile());
		fclose(output);
	} else if (argv[1][1] == 'i') { //interpretador

		Operations &operations = Operations::getInstance();
		bool existeMain = operations.verificarMetodoExiste(classRuntime, "main", "([Ljava/lang/String;)V");
		if (!existeMain) {
			cerr << "O arquivo não possui metodo main" << "." << endl;
			exit(2);
		}
		operations.executarMetodos(classRuntime);
	}

	else {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	//cout << "Fim do programa JVM" << endl;
	return 0;
}
