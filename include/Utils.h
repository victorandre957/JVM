#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "BasicTypes.h"
#include "LeitorExibidor.h"

using namespace std;

/**
 * @file Utils.h
 * @brief Utilitários gerais para manipulação de dados
 */

/**
 * @class Utils
 * @brief Classe com funções utilitárias para formatação e conversão
 */
class Utils {
public:
    /**
     * @brief Mapeia a versão do arquivo .class para versão do JDK
     * 
     * Conversão baseada na especificação:
     * - 52 = J2SE 8
     * - 51 = J2SE 7
     * - 50 = J2SE 6.0
     * - 49 = J2SE 5.0
     * - 48 = JDK 1.4
     * - 47 = JDK 1.3
     * - 46 = JDK 1.2
     * - 45 = JDK 1.1
     * 
     * @param classFile Ponteiro para a estrutura ClassFile
     * @return Versão equivalente do JDK (ex: 1.8 para major_version=52)
     */
    static double verificarVersao(const ClassFile *classFile);

    /**
     * @brief Compara string C com conteúdo de CONSTANT_Utf8_info
     * 
     * @param constant Entrada da constant pool do tipo UTF-8
     * @param str String C-style para comparação
     * @return true se conteúdos forem iguais, false caso contrário
     */
    static bool compararUtf8String(CONSTANT_Utf8_info constant, const char *str);

    /**
     * @brief Imprime tabs de indentação em arquivo
     * 
     * @param out Arquivo de destino
     * @param n Quantidade de tabs a imprimir
     */
    static void imprintTabs(FILE *out, uint8_t n);

    /**
     * @brief Exibe tabs de indentação no console
     * 
     * @param n Quantidade de tabs a exibir
     */
    static void exibeTabs(uint8_t n);

    /**
     * @brief Converte stringstream para string C-style
     * 
     * @param ss Stream de entrada com conteúdo
     * @return const char* String alocada dinamicamente (caller deve liberar memória)
     */
    static const char* converterStreamToCString(const stringstream &ss);

    /**
     * @brief Exibe tabs de indentação em arquivo (sobrecarga)
     * 
     * @param out Arquivo de destino
     * @param n Quantidade de tabs a exibir
     */
    static void exibeTabs(FILE *out, uint8_t n);

    /**
     * @brief Alternativa para mapear versão do arquivo .class
     * @note Parece ser duplicada de verificarVersao(), pode ser consolidada
     * 
     * @param classFile Ponteiro para a estrutura ClassFile
     * @return Versão equivalente do JDK
     */
    static double verificarVersaoClass(const ClassFile *classFile);

    static const char* getFormattedConstant(cp_info* constantPool, u2 index);
	/**
	 * Imprime informações básicas dos atributos e as específicas de um dos 
	 * 9 elementos da unios, onde Synthetic e Deprecated são ignorados por
	 * não possuirem informações extras.
	 * @param attributeInfo sctruct do atributo
	 * @param index é o índice do atributo
	 * @param constantPool é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
	 * @param indentation é o número de tabs que deve ser imprimido na linha
	 */
};

#endif /* UTILS_H */