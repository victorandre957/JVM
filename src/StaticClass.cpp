#include "BasicTypes.h"
#include "StaticClass.h"
#include "ClassVisao.h"
#include "Utils.h"

StaticClass::StaticClass(ClassFile *classFile) : _classFile(classFile) {
	if (!classFile) {
		cerr << "Erro: ClassFile nulo fornecido para StaticClass" << endl;
		exit(1);
	}

	const field_info *fields = classFile->fields;
	const u2 STATIC_FLAG = 0x0008;
	const u2 FINAL_FLAG = 0x0010;

	for (int i = 0; i < classFile->fields_count; i++) {
		const field_info& field = fields[i];

		// Verifica se é campo estático e não final
		if ((field.access_flags & STATIC_FLAG) != 0 && (field.access_flags & FINAL_FLAG) == 0) {
			string fieldName = Utils::getFormattedConstant(classFile->constant_pool, field.name_index);
			string fieldDescriptor = Utils::getFormattedConstant(classFile->constant_pool, field.descriptor_index);

			if (!fieldDescriptor.empty()) {
				Value value = criarValorPadrao(fieldDescriptor[0]);
				putValueIntoField(value, fieldName);
			}
		}
	}
}

ClassFile* StaticClass::getClassFile() const noexcept {
	return _classFile;
}

void StaticClass::putValueIntoField(const Value& value, const string& fieldName) {
	_staticFields[fieldName] = value;
}

const Value& StaticClass::getValueFromField(const string& fieldName) const {
	auto it = _staticFields.find(fieldName);
	if (it == _staticFields.end()) {
		cerr << "NoSuchFieldError: Campo '" << fieldName << "' não encontrado" << endl;
		exit(1);
	}

	return it->second;
}

bool StaticClass::fieldExists(const string& fieldName) const noexcept {
	return _staticFields.find(fieldName) != _staticFields.end();
}

string StaticClass::extrairNomeArquivo(const char * const argv[]) {
	if (!argv || !argv[2]) {
		cerr << "Erro: Argumentos inválidos fornecidos" << endl;
		exit(1);
	}

	string str(argv[2]);
	const string EXTENSAO_CLASS = ".class";
	
	if (str.length() <= EXTENSAO_CLASS.length()) {
		cerr << "Erro: Nome de arquivo muito curto" << endl;
		exit(1);
	}

	// Remove a extensão .class
	return str.substr(0, str.length() - EXTENSAO_CLASS.length());
}

size_t StaticClass::getNumeroFieldsEstaticos() const noexcept {
	return _staticFields.size();
}

Value StaticClass::criarValorPadrao(char fieldType) noexcept {
	Value value;
	
	switch (fieldType) {
	case 'B':
		value.type = ValueType::BYTE;
		value.data.byteValue = 0;
		break;
	case 'C':
		value.type = ValueType::CHAR;
		value.data.charValue = 0;
		break;
	case 'D':
		value.type = ValueType::DOUBLE;
		value.data.doubleValue = 0.0;
		break;
	case 'F':
		value.type = ValueType::FLOAT;
		value.data.floatValue = 0.0f;
		break;
	case 'I':
		value.type = ValueType::INT;
		value.data.intValue = 0;
		break;
	case 'J':
		value.type = ValueType::LONG;
		value.data.longValue = 0;
		break;
	case 'S':
		value.type = ValueType::SHORT;
		value.data.shortValue = 0;
		break;
	case 'Z':
		value.type = ValueType::BOOLEAN;
		value.data.charValue = false;
		break;
	default:
		// Referências (arrays, objetos, etc.)
		value.type = ValueType::REFERENCE;
		value.data.object = nullptr;
		break;
	}

	return value;
}
