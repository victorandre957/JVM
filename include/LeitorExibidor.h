#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdbool>
#include <iostream>
#include "BasicTypes.h"
#include "ClassFile.h"

using namespace std;

/**
 * @file ClassLoader.h
 * @brief Leitor e carregador de arquivos .class
 */

/**
 * @class LeitorExibidor
 * @brief Classe singleton responsável por ler e carregar arquivos .class
 * 
 * Implementa funcionalidades para:
 * - Carregar arquivos .class verificando integridade
 * - Decodificar a estrutura do arquivo .class
 * - Gerenciar endianness
 * - Preencher a estrutura ClassFile
 */
class LeitorExibidor {
public:
    /**
     * @brief Obtém a única instância do LeitorExibidor
     * @return Referência para a instância singleton
     */
    static LeitorExibidor& getInstance() {
        static LeitorExibidor instance;
        return instance;
    }

    /**
     * @brief Destrutor padrão
     */
    ~LeitorExibidor();

    /**
     * @brief Carrega e decodifica um arquivo .class
     * 
     * Realiza:
     * 1. Verificação do magic number (0xCAFEBABE)
     * 2. Checagem da versão do arquivo
     * 3. Leitura e decodificação de todas as seções
     * 
     * @param file Ponteiro para o arquivo .class aberto
     * @return Ponteiro para ClassFile carregado (deve ser desalocado pelo caller)
     */
    ClassFile* readClassFile(FILE *file);

private:
    LeitorExibidor(); ///< Construtor privado (singleton)
    LeitorExibidor(LeitorExibidor const&); ///< Bloqueia cópia
    void operator=(LeitorExibidor const&); ///< Bloqueia atribuição

    bool isLittleEndian; ///< Flag de endianness do sistema

    /**
     * @brief Detecta a endianness do sistema
     * @return true se little-endian, false se big-endian
     */
    bool testEndianess();

    // Funções de leitura primitivas
    u1 readU1(FILE *file); ///< Lê 1 byte
    u2 readU2(FILE *file); ///< Lê 2 bytes (converte endianness)
    u4 readU4(FILE *file); ///< Lê 4 bytes (converte endianness)

    // Métodos de carregamento de seções
    void setMagic(FILE *fp, ClassFile *classFile);
    bool isMagicValid(const ClassFile *classFile);
    void setVersion(FILE *fp, ClassFile *classFile);
    bool isVersionValid(const ClassFile *classFile, uint16_t major);
    void setConstantPoolSize(FILE *fp, ClassFile *classFile);
    void setConstantPool(FILE *fp, ClassFile *classFile);
    void setAccessFlags(FILE *fp, ClassFile *classFile);
    void setThisClass(FILE *fp, ClassFile *classFile);
    void setSuperClass(FILE *fp, ClassFile *classFile);
    void setInterfacesCount(FILE *fp, ClassFile *classFile);
    void setInterfaces(FILE *fp, ClassFile *classFile);
    void setFieldsCount(FILE *fp, ClassFile *classFile);
    void setFields(FILE *fp, ClassFile *classFile);
    void setMethodsCount(FILE *fp, ClassFile *classFile);
    void setMethods(FILE *fp, ClassFile *classFile);
    void setAttributesCount(FILE *fp, ClassFile *classFile);
    void setAttributes(FILE *fp, ClassFile *classFile);

    // Métodos de decodificação da constant pool
    CONSTANT_Class_info getConstantClassInfo(FILE *fp);
    CONSTANT_Fieldref_info getConstantFieldRefInfo(FILE *fp);
    CONSTANT_Methodref_info getConstantMethodRefInfo(FILE *fp);
    CONSTANT_InterfaceMethodref_info getConstantInterfaceMethodRefInfo(FILE *fp);
    CONSTANT_String_info getConstantStringInfo(FILE *fp);
    CONSTANT_Integer_info getConstantIntegerInfo(FILE *fp);
    CONSTANT_Float_info getConstantFloatInfo(FILE *fp);
    CONSTANT_Long_info getConstantLongInfo(FILE *fp);
    CONSTANT_Double_info getConstantDoubleInfo(FILE *fp);
    CONSTANT_NameAndType_info getConstantNameAndTypeInfo(FILE *fp);
    CONSTANT_Utf8_info getConstantUtf8Info(FILE *fp);
    
    // Métodos de decodificação de atributos
    attribute_info getAttributeInfo(FILE *fp, ClassFile *classFile);
    ConstantValue_attribute getAttributeConstantValue(FILE *fp);
    ExceptionTable getExceptionTable(FILE *fp);
    Code_attribute getAttributeCode(FILE *fp, ClassFile *classFile);
    Exceptions_attribute getAttributeExceptions(FILE *fp);
    Class getClass(FILE *fp);
    InnerClasses_attribute getAttributeInnerClasses(FILE *fp);
    Synthetic_attribute getAttributeSynthetic();
    SourceFile_attribute getAttributeSourceFile(FILE *fp);
    LineNumberTable getLineNumberTable(FILE *fp);
    LineNumberTable_attribute getAttributeLineNumberTable(FILE *fp);
    LocalVariableTable getLocalVariableTable(FILE *fp);
    LocalVariableTable_attribute getAttributeLocalVariable(FILE *fp);
    Deprecated_attribute getAttributeDeprecated();
    
    // Utilitários
    CONSTANT_Utf8_info getUtf8FromConstantPool(u2 index, ClassFile *classFile);
};

#endif