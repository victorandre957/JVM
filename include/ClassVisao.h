#ifndef CLASSVIEWER_H
#define CLASSVIEWER_H

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include "BasicTypes.h"
#include "LeitorExibidor.h"
#include "ClassFile.h"

#define UNUSED(x) ((void)(x))
using namespace std;

/**
 * @file ClassViewer.h
 * @brief Declarações para visualização de arquivos .class
 */

/**
 * @brief Exibe toda a estrutura de um ClassFile no console
 * 
 * Ordem de exibição:
 * 1. Informações gerais
 * 2. Pool de constantes
 * 3. Interfaces
 * 4. Campos (fields)
 * 5. Métodos
 * 6. Atributos
 * 
 * @param classFile Ponteiro para a estrutura ClassFile a ser exibida
 */
void exibeClassFile(ClassFile *classFile);

/**
 * @brief Imprime toda a estrutura de um ClassFile em arquivo
 * 
 * Ordem de exibição idêntica à exibeClassFile()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile a ser impressa
 * @param output Arquivo de destino para a impressão
 */
void printArquivoClassFile(ClassFile *classFile, FILE *output);

/**
 * @brief Exibe informações gerais do ClassFile no console
 * 
 * Inclui:
 * - Versão do Java
 * - Flags de acesso
 * - This/Super class
 * - Contadores de constantes/interfaces/campos/métodos/atributos
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_GeneralInformation(ClassFile *classFile);

/**
 * @brief Imprime informações gerais do ClassFile em arquivo
 * 
 * @copydetails exibe_GeneralInformation()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_GeneralInformation(ClassFile *classFile);

/**
 * @brief Exibe a constant pool no console
 * 
 * Exibe cada entrada da pool com seu tipo e valor formatado.
 * Resolve referências entre entradas da pool.
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_ConstantPool(ClassFile *classFile);

/**
 * @brief Imprime a constant pool em arquivo
 * 
 * @copydetails exibe_ConstantPool()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_ConstantPool(ClassFile *classFile);

/**
 * @brief Exibe as interfaces implementadas no console
 * 
 * Mostra as interfaces e suas referências na constant pool.
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_Interfaces(ClassFile *classFile);

/**
 * @brief Imprime as interfaces implementadas em arquivo
 * 
 * @copydetails exibe_Interfaces()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_Interfaces(ClassFile *classFile);

/**
 * @brief Exibe os campos (fields) da classe no console
 * 
 * Para cada campo exibe:
 * - Flags de acesso decodificadas
 * - Nome e descritor
 * - Atributos associados
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_Fields(ClassFile *classFile);

/**
 * @brief Imprime os campos (fields) da classe em arquivo
 * 
 * @copydetails exibe_Fields()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_Fields(ClassFile *classFile);

/**
 * @brief Exibe os métodos da classe no console
 * 
 * Para cada método exibe:
 * - Flags de acesso
 * - Nome e descritor
 * - Atributos (incluindo código bytecode)
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_Methods(ClassFile *classFile);

/**
 * @brief Imprime os métodos da classe em arquivo
 * 
 * @copydetails exibe_Methods()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_Methods(ClassFile *classFile);

/**
 * @brief Exibe os atributos da classe no console
 * 
 * Chama exibe_AttributeInfo() para cada atributo.
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void exibe_Attributes(ClassFile *classFile);

/**
 * @brief Imprime os atributos da classe em arquivo
 * 
 * @copydetails exibe_Attributes()
 * 
 * @param classFile Ponteiro para a estrutura ClassFile
 */
void printArquivo_Attributes(ClassFile *classFile);

/**
 * @brief Decodifica flags de acesso em string legível
 * 
 * @param accessFlags Valor numérico das flags (ex: 0x0001)
 * @return String contendo as flags decodificadas (ex: "ACC_PUBLIC")
 */
const char* getAccessFlags(u2 accessFlags);

/**
 * @brief Formata uma constante da pool para exibição
 * 
 * Resolve referências e formata valores de acordo com o tipo:
 * - Strings UTF-8
 * - Valores numéricos (int, float, double, long)
 * - Referências a outras entradas
 * 
 * @param constantPool Ponteiro para a constant pool
 * @param index Índice da entrada na pool
 * @return String formatada com o valor da constante
 */
const char* Utils::getFormattedConstant(cp_info* constantPool, u2 index);

/**
 * @brief Exibe informações detalhadas de um atributo no console
 * 
 * Trata especificamente:
 * - Code_attribute
 * - Exceptions
 * - InnerClasses
 * - SourceFile
 * - LineNumberTable
 * - LocalVariableTable
 * 
 * @param attributeInfo Estrutura do atributo a ser exibido
 * @param index Índice do atributo (para numeração)
 * @param constantPool Ponteiro para a constant pool (resolução de nomes)
 * @param indentation Nível de indentação (tabs) para formatação
 */
void exibe_AttributeInfo(const attribute_info &attributeInfo, uint32_t index, cp_info *constantPool, uint8_t indentation);

/**
 * @brief Imprime informações detalhadas de um atributo em arquivo
 * 
 * @copydetails exibe_AttributeInfo()
 */
void print_AttributeInfo(const attribute_info &attributeInfo, uint32_t index, cp_info *constantPool, uint8_t indentation);

/**
 * @brief Exibe o bytecode de um método no console
 * 
 * Decodifica as instruções usando a tabela de mnemônicos.
 * Formata com indentação e resolução de constantes.
 * 
 * @param codeAttribute Estrutura contendo o bytecode
 * @param constantPool Ponteiro para a constant pool (resolução de operandos)
 * @param indentation Nível de indentação (tabs)
 */
void exibeByteCode(const Code_attribute &codeAttribute, cp_info *constantPool, uint8_t indentation);

/**
 * @brief Imprime o bytecode de um método em arquivo
 * 
 * @copydetails exibeByteCode()
 */
void printArquivoByteCode(const Code_attribute &codeAttribute, cp_info *constantPool, uint8_t indentation);

/**
 * @brief Tabela de mnemônicos das instruções JVM
 * 
 * Mapeia opcodes para strings representando as instruções.
 * Indexada diretamente pelo valor do opcode.
 */
static  const string  vetorNomeFuncao[] = {
    "nop",
    "aconst_null",
    "iconst_m1",
    "iconst_0",
    "iconst_1",
    "iconst_2",
    "iconst_3",
    "iconst_4",
    "iconst_5",
    "lconst_0",
    "lconst_1",
    "fconst_0",
    "fconst_1",
    "fconst_2",
    "dconst_0",
    "dconst_1",
    "bipush",
    "sipush",
    "ldc",
    "ldc_w",
    "ldc2_w",
    "iload",
    "lload",
    "fload",
    "dload",
    "aload",
    "iload_0",
    "iload_1",
    "iload_2",
    "iload_3",
    "lload_0",
    "lload_1",
    "lload_2",
    "lload_3",
    "fload_0",
    "fload_1",
    "fload_2",
    "fload_3",
    "dload_0",
    "dload_1",
    "dload_2",
    "dload_3",
    "aload_0",
    "aload_1",
    "aload_2",
    "aload_3",
    "iaload",
    "laload",
    "faload",
    "daload",
    "aaload",
    "baload",
    "caload",
    "saload",
    "istore",
    "lstore",
    "fstore",
    "dstore",
    "astore",
    "istore_0",
    "istore_1",
    "istore_2",
    "istore_3",
    "lstore_0",
    "lstore_1",
    "lstore_2",
    "lstore_3",
    "fstore_0",
    "fstore_1",
    "fstore_2",
    "fstore_3",
    "dstore_0",
    "dstore_1",
    "dstore_2",
    "dstore_3",
    "astore_0",
    "astore_1",
    "astore_2",
    "astore_3",
    "iastore",
    "lastore",
    "fastore",
    "dastore",
    "aastore",
    "bastore",
    "castore",
    "sastore",
    "pop",
    "pop2",
    "dup",
    "dup_x1",
    "dup_x2",
    "dup2",
    "dup2_x1",
    "dup2_x2",
    "swap",
    "iadd",
    "ladd",
    "fadd",
    "dadd",
    "isub",
    "lsub",
    "fsub",
    "dsub",
    "imul",
    "lmul",
    "fmul",
    "dmul",
    "idiv",
    "ldiv",
    "fdiv",
    "ddiv",
    "irem",
    "lrem",
    "frem",
    "drem",
    "ineg",
    "lneg",
    "fneg",
    "dneg",
    "ishl",
    "lshl",
    "ishr",
    "lshr",
    "iushr",
    "lushr",
    "iand",
    "land",
    "ior",
    "lor",
    "ixor",
    "lxor",
    "iinc",
    "i2l",
    "i2f",
    "i2d",
    "l2i",
    "l2f",
    "l2d",
    "f2i",
    "f2l",
    "f2d",
    "d2i",
    "d2l",
    "d2f",
    "i2b",
    "i2c",
    "i2s",
    "lcmp",
    "fcmpl",
    "fcmpg",
    "dcmpl",
    "dcmpg",
    "ifeq",
    "ifne",
    "iflt",
    "ifge",
    "ifgt",
    "ifle",
    "if_icmpeq",
    "if_icmpne",
    "if_icmplt",
    "if_icmpge",
    "if_icmpgt",
    "if_icmple",
    "if_acmpeq",
    "if_acmpne",
    "goto",
    "jsr",
    "ret",
    "tableswitch",
    "lookupswitch",
    "ireturn",
    "lreturn",
    "freturn",
    "dreturn",
    "areturn",
    "return",
    "getstatic",
    "putstatic",
    "getfield",
    "putfield",
    "invokevirtual",
    "invokespecial",
    "invokestatic",
    "invokeinterface",
    "UNUSED",
    "new",
    "newarray",
    "anewarray",
    "arraylength",
    "athrow",
    "checkcast",
    "instanceof",
    "monitorenter",
    "monitorexit",
    "wide",
    "multianewarray",
    "ifnull",
    "ifnonnull",
    "goto_w",
    "jsr_w"
};

#endif
