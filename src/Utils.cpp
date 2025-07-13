
#include "Utils.h"

using namespace std;

double Utils::verificarVersao(const ClassFile *classFile) {
	if (classFile->major_version < 45 || classFile->major_version > 52) {
		return 0;
	}

	if (classFile->major_version <= 48) {
		return 1.0 + (classFile->major_version - 44) * 0.1;
	}

	return 5 + (classFile->major_version - 49);
}

/**	@fn double Utils::verificarVersaoClass(ClassFile *classFile)
 * Converte os dados de versão obtidos da struct classFile para a convenção encontrada em https://en.wikipedia.org/wiki/Java_class_file#General_layout
 *
 * Não Tratados
 * Java SE 14 = 58
 * Java SE 13 = 57
 * Java SE 12 = 56
 * Java SE 11 = 55
 * Java SE 10 = 54
 * Java SE 9 = 53
 *
 * Tratados
 * J2SE 8 = 52
 * J2SE 7 = 51
 * J2SE 6.0 = 50
 * J2SE 5.0 = 49
 * JDK 1.4 = 48
 * JDK 1.3 = 47
 * JDK 1.2 = 46
 * JDK 1.1 = 45
 * @return O valor equivalente à versão lida em *classFile.
 */

double Utils::verificarVersaoClass(const ClassFile *classFile) {
	if (classFile->major_version < 45 || classFile->major_version > 52) {
		return 5 + (classFile->major_version - 49);
	}

	/*
	 if (classFile->major_version <= 48) {
	 return 1.0 + (classFile->major_version - 44)*0.1;
	 }
	 */

	return 0;
}

bool Utils::compararUtf8String(CONSTANT_Utf8_info constant, const char *str) {
	if (constant.length != strlen(str)) {
		return false;
	}

	for (int i = 0; i < constant.length; i++) {
		if (constant.bytes[i] != str[i])
			return false;
	}

	return true;
}

void Utils::imprintTabs(FILE *out, uint8_t n) {
	for (uint8_t i = 0; i < n; i++)
		fprintf(out, "\t");
}
void Utils::exibeTabs(uint8_t n) {
	for (uint8_t i = 0; i < n; i++)
		printf("\t");
}
const char* Utils::converterStreamToCString(const stringstream &ss) {
	string tmp = ss.str();
        char *result = static_cast<char*>(malloc(sizeof(char) * (tmp.size() + 1)));
	tmp.copy(result, tmp.size());
	result[tmp.size()] = '\0';

	return result;
}

const char* Utils::getFormattedConstant(cp_info* constantPool, u2 index) {
	cp_info constant = constantPool[index - 1];

	if (constant.tag == CONSTANT_Class) {
		CONSTANT_Class_info classInfo = constant.info.class_info;
		return Utils::getFormattedConstant(constantPool, classInfo.name_index);
	} else if (constant.tag == CONSTANT_Fieldref) {
		CONSTANT_Fieldref_info fieldRefInfo = constant.info.fieldref_info;
		CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[fieldRefInfo.name_and_type_index - 1].info.nameAndType_info;

		const char *className = Utils::getFormattedConstant(constantPool, fieldRefInfo.class_index);
		const char *name = Utils::getFormattedConstant(constantPool, nameAndTypeInfo.name_index);

		stringstream ss;
		ss << className << "." << name;
		return Utils::converterStreamToCString(ss);
	} else if (constant.tag == CONSTANT_Methodref) {
		CONSTANT_Methodref_info methodRefInfo = constant.info.methodref_info;
		CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[methodRefInfo.name_and_type_index - 1].info.nameAndType_info;

		const char *className = Utils::getFormattedConstant(constantPool, methodRefInfo.class_index);
		const char *name = Utils::getFormattedConstant(constantPool, nameAndTypeInfo.name_index);

		stringstream ss;
		ss << className << "." << name;
		return Utils::converterStreamToCString(ss);
	} else if (constant.tag == CONSTANT_InterfaceMethodref) {
		CONSTANT_InterfaceMethodref_info interfaceMethodRefInfo = constant.info.interfaceMethodref_info;
		CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[interfaceMethodRefInfo.name_and_type_index - 1].info.nameAndType_info;

		const char *className = Utils::getFormattedConstant(constantPool, interfaceMethodRefInfo.class_index);
		const char *name = Utils::getFormattedConstant(constantPool, nameAndTypeInfo.name_index);

		stringstream ss;
		ss << className << "." << name;
		return Utils::converterStreamToCString(ss);
	} else if (constant.tag == CONSTANT_String) {
		CONSTANT_String_info stringInfo = constant.info.string_info;
		return Utils::getFormattedConstant(constantPool, stringInfo.string_index);
	} else if (constant.tag == CONSTANT_Integer) {
		CONSTANT_Integer_info intInfo = constant.info.integer_info;
		int32_t number = intInfo.bytes;
                char *s = static_cast<char*>(malloc(sizeof(char) * 100));
		sprintf(s, "%d", number);
		return s;
	} else if (constant.tag == CONSTANT_Float) {
		CONSTANT_Float_info floatInfo = constant.info.float_info;

		int32_t s = ((floatInfo.bytes >> 31) == 0) ? 1 : -1;
		int32_t e = ((floatInfo.bytes >> 23) & 0xff);
		int32_t m = (e == 0) ? (floatInfo.bytes & 0x7fffff) << 1 : (floatInfo.bytes & 0x7fffff) | 0x800000;
		float number = s * m * pow(2, e - 150);

                char *str = static_cast<char*>(malloc(sizeof(char) * 100));
		sprintf(str, "%f", number);
		return str;
	} else if (constant.tag == CONSTANT_Long) {
		CONSTANT_Long_info longInfo = constant.info.long_info;
		int64_t number = ((int64_t) longInfo.high_bytes << 32) + longInfo.low_bytes;

                char *str = static_cast<char*>(malloc(sizeof(char) * 100));
		sprintf(str, "%lld", (long long) number);
		return str;
	} else if (constant.tag == CONSTANT_Double) {
		CONSTANT_Double_info doubleInfo = constant.info.double_info;
		int64_t bytes = ((int64_t) doubleInfo.high_bytes << 32) + doubleInfo.low_bytes;

                int32_t s = ((static_cast<uint64_t>(bytes) >> 63) == 0) ? 1 : -1;
		int32_t e = (int32_t) ((bytes >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
		double number = s * m * pow(2, e - 1075);

                char *str = static_cast<char*>(malloc(sizeof(char) * 100));
		sprintf(str, "%f", number);
		return str;
	} else if (constant.tag == CONSTANT_NameAndType) {
		CONSTANT_NameAndType_info nameAndTypeInfo = constant.info.nameAndType_info;

		const char *name = Utils::getFormattedConstant(constantPool, nameAndTypeInfo.name_index);
		const char *descriptor = Utils::getFormattedConstant(constantPool, nameAndTypeInfo.descriptor_index);

                char *result = static_cast<char*>(malloc(sizeof(char) * (strlen(name) + strlen(descriptor)) + 1));
		strcpy(result, name);
		strcat(result, descriptor);

		return result;
	} else if (constant.tag == CONSTANT_Utf8) {
		CONSTANT_Utf8_info utf8_info = constant.info.utf8_info;
                char *str = static_cast<char*>(malloc((utf8_info.length + 1) * sizeof(char)));

		uint16_t j = 0;
		for (uint16_t i = 0; i < utf8_info.length; i++) {
			if (isprint(utf8_info.bytes[i]))
				str[j++] = utf8_info.bytes[i];
		}
		str[j] = '\0';

		return str;
	} else {
		cerr << "Arquivo .class possui uma tag " << constant.tag << " invalida no pool de constantes." << endl;
		exit(5);
	}

	return NULL;
}

bool Utils::verificarThisClass(string auxFilename, string auxClass) {
	int auxPos;

	//remove extensao .class
	auxFilename = auxFilename.substr(0, auxFilename.size() - 6);

	//remove nomes de pastas no Windows
	auxPos = auxFilename.find("\\");

	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxFilename.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("/");
	}
	//..
	//remove nomes de pastas no Windows
	auxPos = auxClass.find("\\");

	while (auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos + 1);
		auxPos = auxClass.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxClass.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos + 1);
		auxPos = auxClass.find("/");
	}

	return (auxClass == auxFilename);
}