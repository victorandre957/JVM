#ifndef CLASSVISAO_H
#define CLASSVISAO_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "BasicTypes.h"
#include "LeitorExibidor.h"
#include "ClassFile.h"

/**
 * @brief Imprime informações detalhadas de um arquivo .class para um arquivo
 * @param classFile Ponteiro para estrutura ClassFile
 * @param output Ponteiro para FILE de destino
 */
void printArquivoClassFile(ClassFile* classFile, FILE* output);

/**
 * @brief Exibe informações resumidas de um arquivo .class no console
 * @param classFile Ponteiro para estrutura ClassFile
 */
void exibeClassFile(ClassFile* classFile);

#endif // CLASSVISAO_H
