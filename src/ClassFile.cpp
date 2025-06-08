/*!
 * \file ClassFile.cpp
 * \brief Classe que irá realizar a leitura do bytecode e salvar as informações do class file
 */

#include "ClassFile.h"


ClassFile::ClassFile()
    : magic(0),
      minor_version(0),
      major_version(0),
      constant_pool_count(0),
      constant_pool(nullptr),
      access_flags(0),
      this_class(0),
      super_class(0),
      interfaces_count(0),
      interfaces(nullptr),
      fields_count(0),
      fields(nullptr),
      methods_count(0),
      methods(nullptr),
      attributes_count(0),
      attributes(nullptr) {
}
