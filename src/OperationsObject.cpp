#include "OperationsObject.h"

#include "Frame.h"
#include "Object.h"
#include "Utils.h"
#include "MethodArea.h"
#include "PilhaJVM.h"
#include "StaticClass.h"
#include "InstanceClass.h"
#include <ClassVisao.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

OperationsObject::OperationsObject(bool &isWideRef) : _isWide(isWideRef) {
}

void OperationsObject::getstatic() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t fieldIndex = (byte1 << 8) | byte2;
	cp_info fieldCP = constantPool[fieldIndex - 1];
	assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

	CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldRef.class_index);

	cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

	string fieldName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.name_index);
	string fieldDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.descriptor_index);

	// caso especial
	if (className == "java/lang/System" && fieldDescriptor == "Ljava/io/PrintStream;") {
		topFrame->pc += 3;
		return;
	}
	// fim do caso especial

	MethodArea &methodArea = MethodArea::getInstance();
	StaticClass *classRuntime = methodArea.carregarClassNamed(className);

	while (classRuntime != NULL) {
		if (classRuntime->fieldExists(fieldName) == false) {
			if (classRuntime->getClassFile()->super_class == 0) {
				classRuntime = NULL;
			} else {
				string superClassName = Utils::getFormattedConstant(classRuntime->getClassFile()->constant_pool,
						classRuntime->getClassFile()->super_class);
				classRuntime = methodArea.carregarClassNamed(superClassName);
			}
		} else {
			break;
		}
	}

	if (classRuntime == NULL) {
		cerr << "NoSuchFieldError" << endl;
		exit(1);
	}

	// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
	if (stackFrame.getTopFrame() != topFrame)
		return;

	Value staticValue = classRuntime->getValueFromField(fieldName);
	switch (staticValue.type) {
	case ValueType::BOOLEAN:
		staticValue.type = ValueType::INT;
		staticValue.printType = ValueType::BOOLEAN;
		break;
	case ValueType::BYTE:
		staticValue.type = ValueType::INT;
		staticValue.printType = ValueType::BYTE;
		break;
	case ValueType::SHORT:
		staticValue.type = ValueType::INT;
		staticValue.printType = ValueType::SHORT;
		break;
	case ValueType::INT:
		staticValue.type = ValueType::INT;
		staticValue.printType = ValueType::INT;
		break;
	default:
		break;
	}

	if (staticValue.type == ValueType::DOUBLE || staticValue.type == ValueType::LONG) {
		Value paddingValue;
		paddingValue.type = ValueType::PADDING;
		topFrame->empilharOperandStack(paddingValue);
	}

	topFrame->empilharOperandStack(staticValue);

	topFrame->pc += 3;
}

void OperationsObject::putstatic() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t fieldIndex = (byte1 << 8) | byte2;
	cp_info fieldCP = constantPool[fieldIndex - 1];
	assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

	CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldRef.class_index);

	cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

	string fieldName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.name_index);
	string fieldDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.descriptor_index);

	MethodArea &methodArea = MethodArea::getInstance();
	StaticClass *classRuntime = methodArea.carregarClassNamed(className);

	while (classRuntime != NULL) {
		if (classRuntime->fieldExists(fieldName) == false) {
			if (classRuntime->getClassFile()->super_class == 0) {
				classRuntime = NULL;
			} else {
				string superClassName = Utils::getFormattedConstant(classRuntime->getClassFile()->constant_pool,
						classRuntime->getClassFile()->super_class);
				classRuntime = methodArea.carregarClassNamed(superClassName);
			}
		} else {
			break;
		}
	}

	if (classRuntime == NULL) {
		cerr << "NoSuchFieldError" << endl;
		exit(1);
	}

	// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
	if (stackFrame.getTopFrame() != topFrame)
		return;

	Value topValue = topFrame->desempilhaOperandStack();
	if (topValue.type == ValueType::DOUBLE || topValue.type == ValueType::LONG) {
		topFrame->desempilhaOperandStack(); // removendo padding
	} else {
		switch (fieldDescriptor[0]) {
		case 'B':
			topValue.type = ValueType::BYTE;
			topValue.printType = ValueType::BYTE;
			break;
		case 'C':
			topValue.type = ValueType::CHAR;
			topValue.printType = ValueType::CHAR;
			break;
		case 'S':
			topValue.type = ValueType::SHORT;
			topValue.printType = ValueType::SHORT;
			break;
		case 'Z':
			topValue.type = ValueType::BOOLEAN;
			topValue.printType = ValueType::BOOLEAN;
			break;
		}
	}

	classRuntime->putValueIntoField(topValue, fieldName);

	topFrame->pc += 3;
}

void OperationsObject::getfield() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t fieldIndex = (byte1 << 8) | byte2;
	cp_info fieldCP = constantPool[fieldIndex - 1];
	assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

	CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldRef.class_index);

	cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

	string fieldName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.name_index);
	string fieldDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.descriptor_index);

	Value objectValue = topFrame->desempilhaOperandStack();
	assert(objectValue.type == ValueType::REFERENCE);
	Object *object = objectValue.data.object;
	assert(object->objectType() == ObjectType::CLASS_INSTANCE);
	InstanceClass *classInstance = static_cast<InstanceClass *>(object);

	if (!classInstance->fieldExists(fieldName)) {
		cerr << "NoSuchFieldError" << endl;
		exit(1);
	}

	Value fieldValue = classInstance->getValueFromField(fieldName);
	switch (fieldValue.type) {
	case ValueType::BOOLEAN:
		fieldValue.type = ValueType::INT;
		fieldValue.printType = ValueType::BOOLEAN;
		break;
	case ValueType::BYTE:
		fieldValue.type = ValueType::INT;
		fieldValue.printType = ValueType::BYTE;
		break;
	case ValueType::SHORT:
		fieldValue.type = ValueType::INT;
		fieldValue.printType = ValueType::SHORT;
		break;
	case ValueType::INT:
		fieldValue.type = ValueType::INT;
		fieldValue.printType = ValueType::INT;
		break;
	default:
		break;
	}

	if (fieldValue.type == ValueType::DOUBLE || fieldValue.type == ValueType::LONG) {
		Value paddingValue;
		paddingValue.type = ValueType::PADDING;
		topFrame->empilharOperandStack(paddingValue);
	}

	topFrame->empilharOperandStack(fieldValue);

	topFrame->pc += 3;
}

void OperationsObject::putfield() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t fieldIndex = (byte1 << 8) | byte2;
	cp_info fieldCP = constantPool[fieldIndex - 1];
	assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

	CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldRef.class_index);

	cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

	string fieldName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.name_index);
	string fieldDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), fieldNameAndType.descriptor_index);

	Value valueToBeInserted = topFrame->desempilhaOperandStack();
	if (valueToBeInserted.type == ValueType::DOUBLE || valueToBeInserted.type == ValueType::LONG) {
		topFrame->desempilhaOperandStack(); // removendo padding
	} else {
		switch (fieldDescriptor[0]) {
		case 'B':
			valueToBeInserted.type = ValueType::BYTE;
			valueToBeInserted.printType = ValueType::BYTE;
			break;
		case 'C':
			valueToBeInserted.type = ValueType::CHAR;
			valueToBeInserted.printType = ValueType::CHAR;
			break;
		case 'S':
			valueToBeInserted.type = ValueType::SHORT;
			valueToBeInserted.printType = ValueType::SHORT;
			break;
		case 'Z':
			valueToBeInserted.type = ValueType::BOOLEAN;
			valueToBeInserted.printType = ValueType::BOOLEAN;
			break;
		}
	}

	Value objectValue = topFrame->desempilhaOperandStack();
	assert(objectValue.type == ValueType::REFERENCE);
	Object *object = objectValue.data.object;
	assert(object->objectType() == ObjectType::CLASS_INSTANCE);
	InstanceClass *classInstance = static_cast<InstanceClass *>(object);

	classInstance->putValueIntoField(valueToBeInserted, fieldName);

	topFrame->pc += 3;
}

void OperationsObject::invokevirtual() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	stack<Value> operandStackBackup = topFrame->backupOperandStack();

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t methodIndex = (byte1 << 8) | byte2;
	cp_info methodCP = constantPool[methodIndex - 1];
	assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

	CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodInfo.class_index);

	cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

	string methodName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.name_index);
	string methodDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.descriptor_index);

	if (className.find("java/") != string::npos) {
		// simulando println ou print
		if (className == "java/io/PrintStream" && (methodName == "print" || methodName == "println")) {
			if (methodDescriptor != "()V") {
				Value printValue = topFrame->desempilhaOperandStack();

				if (printValue.type == ValueType::INT) {
					switch (printValue.printType) {
					case ValueType::BOOLEAN:
						printf("%s", printValue.data.booleanValue == 0 ? "false" : "true");
						break;
					case ValueType::BYTE:
						printf("%d", printValue.data.byteValue);
						break;
					case ValueType::CHAR:
						printf("%c", printValue.data.charValue);
						break;
					case ValueType::SHORT:
						printf("%d", printValue.data.shortValue);
						break;
					default:
						printf("%d", printValue.data.intValue);
						break;
					}
				} else {
					switch (printValue.type) {
					case ValueType::DOUBLE:
						topFrame->desempilhaOperandStack(); // removendo padding
						printf("%f", printValue.data.doubleValue);
						break;
					case ValueType::FLOAT:
						printf("%f", printValue.data.floatValue);
						break;
					case ValueType::LONG:
						topFrame->desempilhaOperandStack(); // removendo padding
						printf("%lld", (long long) printValue.data.longValue);

						break;
					case ValueType::REFERENCE:
						assert(printValue.data.object->objectType() == ObjectType::STRING_INSTANCE);
						printf("%s", static_cast<StringObject *>(printValue.data.object)->getString().c_str());
						break;
					case ValueType::BOOLEAN:
						printf("%s", printValue.data.booleanValue == 0 ? "false" : "true");
						break;
					case ValueType::BYTE:
						printf("%d", printValue.data.byteValue);
						break;
					case ValueType::CHAR:
						printf("%c", printValue.data.charValue);
						break;
					case ValueType::SHORT:
						printf("%d", printValue.data.shortValue);
						break;
					default:
						cerr << "Tentando printar tipo de dado invalido: " << printValue.type << endl;
						exit(1);
						break;
					}
				}
			}

			if (methodName == "println")
				printf("\n");
		} else if (className == "java/lang/String" && methodName == "equals") {
			Value strValue1 = topFrame->desempilhaOperandStack();
			Value strValue2 = topFrame->desempilhaOperandStack();
			assert(strValue1.type == ValueType::REFERENCE);
			assert(strValue2.type == ValueType::REFERENCE);
			assert(strValue1.data.object->objectType() == ObjectType::STRING_INSTANCE);
			assert(strValue2.data.object->objectType() == ObjectType::STRING_INSTANCE);

			const StringObject *str1 = static_cast<const StringObject*>(strValue1.data.object);
			const StringObject *str2 = static_cast<const StringObject*>(strValue2.data.object);

			Value result;
			result.printType = ValueType::INT;
			result.type = ValueType::INT;
			if (str1->getString() == str2->getString()) {
				result.data.intValue = 1;
			} else {
				result.data.intValue = 0;
			}
			topFrame->empilharOperandStack(result);
		} else if (className == "java/lang/String" && methodName == "length") {
			Value strValue = topFrame->desempilhaOperandStack();
			assert(strValue.type == ValueType::REFERENCE);
			assert(strValue.data.object->objectType() == ObjectType::STRING_INSTANCE);

			const StringObject *str = static_cast<const StringObject*>(strValue.data.object);

			Value result;
			result.printType = ValueType::INT;
			result.type = ValueType::INT;
			result.data.intValue = (str->getString()).size();
			topFrame->empilharOperandStack(result);
		} else {
			cerr << "Tentando invocar metodo de instancia invalido: " << methodName << endl;
			exit(1);
		}
	} else {
		uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (methodDescriptor[i] != ')') {
			char baseType = methodDescriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				nargs += 2;
			} else if (baseType == 'L') {
				nargs++;
				while (methodDescriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				nargs++;
				while (methodDescriptor[++i] == '[')
					;
				if (methodDescriptor[i] == 'L')
					while (methodDescriptor[++i] != ';')
						;
			} else {
				nargs++;
			}
			i++;
		}

		vector<Value> args;
		for (int i = 0; i < nargs; i++) {
			Value value = topFrame->desempilhaOperandStack();
			if (value.type == ValueType::PADDING) {
				args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
			} else {
				args.insert(args.begin(), value);
			}
		}

		Value objectValue = topFrame->desempilhaOperandStack();
		assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
		args.insert(args.begin(), objectValue);

		Object *object = objectValue.data.object;
		assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
		InstanceClass *instance = static_cast<InstanceClass *>(object);

		MethodArea &methodArea = MethodArea::getInstance();
		StaticClass *classRuntime = methodArea.carregarClassNamed(className);

		Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

		// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
		if (stackFrame.getTopFrame() != topFrame) {
			topFrame->setOperandStackFromBackup(operandStackBackup);
			delete newFrame;
			return;
		}

		stackFrame.addFrame(newFrame);
	}

	topFrame->pc += 3;
}

void OperationsObject::invokespecial() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	stack<Value> operandStackBackup = topFrame->backupOperandStack();

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t methodIndex = (byte1 << 8) | byte2;
	cp_info methodCP = constantPool[methodIndex - 1];
	assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

	CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodInfo.class_index);

	cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

	string methodName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.name_index);
	string methodDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.descriptor_index);

	// casos especiais
	if ((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>") {
		if (className == "java/lang/String") {
			topFrame->desempilhaOperandStack();
		}

		topFrame->pc += 3;
		return;
	}
	// fim dos casos especiais

	if (className.find("java/") != string::npos) {
		cerr << "Tentando invocar metodo especial invalido: " << methodName << endl;
		exit(1);
	} else {
		uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (methodDescriptor[i] != ')') {
			char baseType = methodDescriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				nargs += 2;
			} else if (baseType == 'L') {
				nargs++;
				while (methodDescriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				nargs++;
				while (methodDescriptor[++i] == '[')
					;
				if (methodDescriptor[i] == 'L')
					while (methodDescriptor[++i] != ';')
						;
			} else {
				nargs++;
			}
			i++;
		}

		vector<Value> args;
		for (int i = 0; i < nargs; i++) {
			Value value = topFrame->desempilhaOperandStack();
			if (value.type == ValueType::PADDING) {
				args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
			} else {
				args.insert(args.begin(), value);
			}
		}

		Value objectValue = topFrame->desempilhaOperandStack();
		assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
		args.insert(args.begin(), objectValue);

		Object *object = objectValue.data.object;
		assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
		InstanceClass *instance = static_cast<InstanceClass *>(object);

		MethodArea &methodArea = MethodArea::getInstance();
		StaticClass *classRuntime = methodArea.carregarClassNamed(className);

		Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

		// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
		if (stackFrame.getTopFrame() != topFrame) {
			topFrame->setOperandStackFromBackup(operandStackBackup);
			delete newFrame;
			return;
		}

		stackFrame.addFrame(newFrame);
	}

	topFrame->pc += 3;
}

void OperationsObject::invokestatic() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	stack<Value> operandStackBackup = topFrame->backupOperandStack();

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t methodIndex = (byte1 << 8) | byte2;
	cp_info methodCP = constantPool[methodIndex - 1];
	assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

	CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodInfo.class_index);

	cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

	string methodName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.name_index);
	string methodDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.descriptor_index);

	if (className == "java/lang/Object" && methodName == "registerNatives") {
		topFrame->pc += 3;
		return;
	}

	if (className.find("java/") != string::npos) {
		cerr << "Tentando invocar metodo estatico invalido: " << methodName << endl;
		exit(1);
	} else {
		uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (methodDescriptor[i] != ')') {
			char baseType = methodDescriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				nargs += 2;
			} else if (baseType == 'L') {
				nargs++;
				while (methodDescriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				nargs++;
				while (methodDescriptor[++i] == '[')
					;
				if (methodDescriptor[i] == 'L')
					while (methodDescriptor[++i] != ';')
						;
			} else {
				nargs++;
			}
			i++;
		}

		vector<Value> args;
		for (int i = 0; i < nargs; i++) {
			Value value = topFrame->desempilhaOperandStack();
			if (value.type == ValueType::PADDING) {
				args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
			} else {
				args.insert(args.begin(), value);
			}
		}

		MethodArea &methodArea = MethodArea::getInstance();
		StaticClass *classRuntime = methodArea.carregarClassNamed(className);
		Frame *newFrame = new Frame(classRuntime, methodName, methodDescriptor, args);

		// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
		if (stackFrame.getTopFrame() != topFrame) {
			topFrame->setOperandStackFromBackup(operandStackBackup);
			delete newFrame;
			return;
		}

		stackFrame.addFrame(newFrame);
	}

	topFrame->pc += 3;
}

void OperationsObject::invokeinterface() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	stack<Value> operandStackBackup = topFrame->backupOperandStack();

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t methodIndex = (byte1 << 8) | byte2;
	cp_info methodCP = constantPool[methodIndex - 1];
	assert(methodCP.tag == CONSTANT_Methodref || methodCP.tag == CONSTANT_InterfaceMethodref); // precisa referenciar um método

	CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodInfo.class_index);

	cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index - 1];
	assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

	CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

	string methodName = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.name_index);
	string methodDescriptor = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), methodNameAndType.descriptor_index);

	if (className.find("java/") != string::npos) {
		cerr << "Tentando invocar metodo de interface invalido: " << methodName << endl;
		exit(1);
	} else {
		uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (methodDescriptor[i] != ')') {
			char baseType = methodDescriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				nargs += 2;
			} else if (baseType == 'L') {
				nargs++;
				while (methodDescriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				nargs++;
				while (methodDescriptor[++i] == '[')
					;
				if (methodDescriptor[i] == 'L')
					while (methodDescriptor[++i] != ';')
						;
			} else {
				nargs++;
			}
			i++;
		}

		vector<Value> args;
		for (int i = 0; i < nargs; i++) {
			Value value = topFrame->desempilhaOperandStack();
			if (value.type == ValueType::PADDING) {
				args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
			} else {
				args.insert(args.begin(), value);
			}
		}

		Value objectValue = topFrame->desempilhaOperandStack();
		assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
		args.insert(args.begin(), objectValue);

		Object *object = objectValue.data.object;
		assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
		InstanceClass *instance = static_cast<InstanceClass *>(object);

		MethodArea &methodArea = MethodArea::getInstance();
		methodArea.carregarClassNamed(className); // carregando a interface (caso ainda não foi carregada).

		Frame *newFrame = new Frame(instance, instance->getClassRuntime(), methodName, methodDescriptor, args);

		// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
		if (stackFrame.getTopFrame() != topFrame) {
			topFrame->setOperandStackFromBackup(operandStackBackup);
			delete newFrame;
			return;
		}

		stackFrame.addFrame(newFrame);
	}

	topFrame->pc += 5;
}

void OperationsObject::func_new() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t classIndex = (byte1 << 8) | byte2;
	cp_info classCP = constantPool[classIndex - 1];
	assert(classCP.tag == CONSTANT_Class);

	CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), classInfo.name_index);

	Object *object;
	if (className == "java/lang/String") {
		object = new StringObject();
	} else {
		MethodArea &methodArea = MethodArea::getInstance();
		StaticClass *classRuntime = methodArea.carregarClassNamed(className);
		object = new InstanceClass(classRuntime); // Cria instancia da classe e coloca na heap
	}

	// Armazena referência na pilha
	Value objectref;
	objectref.data.object = object;
	objectref.type = ValueType::REFERENCE;
	topFrame->empilharOperandStack(objectref);

	topFrame->pc += 3;
}

void OperationsObject::newarray() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value count = topFrame->desempilhaOperandStack(); // Número de elementos no array
	assert(count.type == ValueType::INT);

	if (count.data.intValue < 0) {
		cerr << "NegativeArraySizeException" << endl;
		exit(1);
	}

	ArrayObject *array; // array que será criado
	Value value; // elemento que irá popular o array
	value.data.longValue = 0; // inicializando Value com 0s

	Value padding;
	UNUSED(padding);
	padding.type = ValueType::PADDING;

	const u1 *code = topFrame->getCode(topFrame->pc);
	switch (code[1]) { // argumento representa tipo do array
	case 4:
		array = new ArrayObject(ValueType::BOOLEAN);
		value.type = ValueType::BOOLEAN;
	value.printType = value.type;
		value.printType = ValueType::BOOLEAN;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 5:
		array = new ArrayObject(ValueType::CHAR);
		value.type = ValueType::CHAR;
	value.printType = value.type;
		value.printType = ValueType::CHAR;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 6:
		array = new ArrayObject(ValueType::FLOAT);
		value.type = ValueType::FLOAT;
	value.printType = value.type;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 7:
		array = new ArrayObject(ValueType::DOUBLE);
		value.type = ValueType::DOUBLE;
	value.printType = value.type;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 8:
		array = new ArrayObject(ValueType::BYTE);
		value.type = ValueType::BYTE;
	value.printType = value.type;
		value.printType = ValueType::BYTE;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 9:
		array = new ArrayObject(ValueType::SHORT);
		value.type = ValueType::SHORT;
	value.printType = value.type;
		value.printType = ValueType::SHORT;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 10:
		array = new ArrayObject(ValueType::INT);
		value.type = ValueType::INT;
	value.printType = value.type;
		value.printType = ValueType::INT;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	case 11:
		array = new ArrayObject(ValueType::LONG);
		value.type = ValueType::LONG;
	value.printType = value.type;
		for (int i = 0; i < count.data.intValue; i++) {
			array->pushValue(value);
		}
		break;
	}

	Value arrayref; // Referencia pro array na pilha de operandos
	arrayref.type = ValueType::REFERENCE;
	arrayref.data.object = array;

	topFrame->empilharOperandStack(arrayref);
	topFrame->pc += 2;
}

void OperationsObject::anewarray() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value count = topFrame->desempilhaOperandStack(); // Número de elementos no array
	assert(count.type == ValueType::INT);
	if (count.data.intValue < 0) {
		cerr << "NegativeArraySizeException" << endl;
		exit(1);
	}

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t classIndex = (byte1 << 8) | byte2; // Índice na pool de constantes
	cp_info classCP = constantPool[classIndex - 1];
	assert(classCP.tag == CONSTANT_Class);

	CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), classInfo.name_index);

	if (className != "java/lang/String") {
		int i = 0;
		while (className[i] == '[')
			i++;
		if (className[i] == 'L') {
			MethodArea &methodArea = MethodArea::getInstance();
			methodArea.carregarClassNamed(className.substr(i + 1, className.size() - i - 2)); // carrega a classe de referência (se ainda não foi).
		}
	}

	// criando objeto da classe instanciada
	Value objectref;
	objectref.type = ValueType::REFERENCE;
	objectref.data.object = new ArrayObject(ValueType::REFERENCE);

	// populando array com NULL
	Value nullValue;
	nullValue.type = ValueType::REFERENCE;
	nullValue.data.object = NULL;
	for (int i = 0; i < count.data.intValue; i++) {
		static_cast<ArrayObject *>(objectref.data.object)->pushValue(nullValue);
	}

	topFrame->empilharOperandStack(objectref);

	topFrame->pc += 3;
}

void OperationsObject::arraylength() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	if (arrayref.data.object == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}

	Value length;
	length.type = ValueType::INT;
	length.data.intValue = static_cast<ArrayObject *>(arrayref.data.object)->getSize();

	topFrame->empilharOperandStack(length);
	topFrame->pc += 1;
}

void OperationsObject::athrow() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->pc += 1;
}

void OperationsObject::checkcast() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	MethodArea &methodArea = MethodArea::getInstance();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];

	u2 cpIndex = (byte1 << 8) | byte2;
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	cp_info cpElement = constantPool[cpIndex - 1];
	assert(cpElement.tag == CONSTANT_Class);
	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), cpIndex);

	Value objectrefValue = topFrame->desempilhaOperandStack();
	assert(objectrefValue.type == ValueType::REFERENCE);

	Value resultValue;
	resultValue.type = ValueType::INT;

	if (objectrefValue.data.object == NULL) {
		cerr << "ClassCastException" << endl;
		exit(1);
	} else {
		Object *obj = objectrefValue.data.object;

		if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
			InstanceClass *classInstance = static_cast<InstanceClass *>(obj);
			StaticClass *classRuntime = classInstance->getClassRuntime();

			bool found = false;
			while (!found) {
				ClassFile *classFile = classRuntime->getClassFile();
				string currClassName = Utils::getFormattedConstant(classFile->constant_pool, classFile->this_class);

				if (currClassName == className) {
					found = true;
				} else {
					if (classFile->super_class == 0) {
						break;
					} else {
						string superClassName = Utils::getFormattedConstant(classFile->constant_pool, classFile->this_class);
						classRuntime = methodArea.carregarClassNamed(superClassName);
					}
				}
			}

			resultValue.data.intValue = found ? 1 : 0;
		} else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
			resultValue.data.intValue = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
		} else {
			if (className == "java/lang/Object") {
				resultValue.data.intValue = 1;
			} else {
				resultValue.data.intValue = 0;
			}
		}
	}

	topFrame->empilharOperandStack(resultValue);

	topFrame->pc += 3;
}

void OperationsObject::instanceof() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	MethodArea &methodArea = MethodArea::getInstance();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];

	u2 cpIndex = (byte1 << 8) | byte2;
	const cp_info *constantPool = *(topFrame->obterConstantPool());
	cp_info cpElement = constantPool[cpIndex - 1];
	assert(cpElement.tag == CONSTANT_Class);
	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), cpIndex);

	Value objectrefValue = topFrame->desempilhaOperandStack();
	assert(objectrefValue.type == ValueType::REFERENCE);

	Value resultValue;
	resultValue.type = ValueType::INT;

	if (objectrefValue.data.object == NULL) {
		resultValue.data.intValue = 0;
	} else {
		Object *obj = objectrefValue.data.object;

		if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
			InstanceClass *classInstance = static_cast<InstanceClass *>(obj);
			StaticClass *classRuntime = classInstance->getClassRuntime();

			bool found = false;
			while (!found) {
				ClassFile *classFile = classRuntime->getClassFile();
				string currClassName = Utils::getFormattedConstant(classFile->constant_pool, classFile->this_class);

				if (currClassName == className) {
					found = true;
				} else {
					if (classFile->super_class == 0) {
						break;
					} else {
						string superClassName = Utils::getFormattedConstant(classFile->constant_pool, classFile->this_class);
						classRuntime = methodArea.carregarClassNamed(superClassName);
					}
				}
			}

			resultValue.data.intValue = found ? 1 : 0;
		} else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
			resultValue.data.intValue = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
		} else {
			if (className == "java/lang/Object") {
				resultValue.data.intValue = 1;
			} else {
				resultValue.data.intValue = 0;
			}
		}
	}

	topFrame->empilharOperandStack(resultValue);

	topFrame->pc += 3;
}

void OperationsObject::monitorenter() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->pc += 1;
}

void OperationsObject::monitorexit() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->pc += 1;
}

void OperationsObject::multianewarray() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u1 dimensions = code[3];
	assert(dimensions >= 1);

	uint16_t classIndex = (byte1 << 8) | byte2;
	cp_info classCP = constantPool[classIndex - 1];
	assert(classCP.tag == CONSTANT_Class);

	CONSTANT_Class_info classInfo = classCP.info.class_info;
	string className = Utils::getFormattedConstant(const_cast<cp_info*>(constantPool), classInfo.name_index);

	// obter o tipo dentro de className:
	ValueType valueType;
	int i = 0;
	while (className[i] == '[')
		i++;

	string multiArrayType = className.substr(i + 1, className.size() - i - 2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)

	switch (className[i]) {
	case 'L':
		if (multiArrayType != "java/lang/String") {
			MethodArea &methodArea = MethodArea::getInstance();
			methodArea.carregarClassNamed(multiArrayType); // verifica se existe classe com esse nome
		}
		valueType = ValueType::REFERENCE;
		break;
	case 'B':
		valueType = ValueType::BYTE;
		break;
	case 'C':
		valueType = ValueType::CHAR;
		break;
	case 'D':
		valueType = ValueType::DOUBLE;
		break;
	case 'F':
		valueType = ValueType::FLOAT;
		break;
	case 'I':
		valueType = ValueType::INT;
		break;
	case 'J':
		valueType = ValueType::LONG;
		break;
	case 'S':
		valueType = ValueType::SHORT;
		break;
	case 'Z':
		valueType = ValueType::BOOLEAN;
		break;
	default:
		cerr << "Descritor invalido em multianewarray" << endl;
		exit(1);
	}

	stack<int> count;
	for (int i = 0; i < dimensions; i++) {
		Value dimLength = topFrame->desempilhaOperandStack();
		assert(dimLength.type == ValueType::INT);
		count.push(dimLength.data.intValue);
	}

	ArrayObject *array = new ArrayObject((dimensions > 1) ? ValueType::REFERENCE : valueType);
	
	// Since we can't call Operations::populateMultiarray due to circular dependency,
	// we implement the multianewarray logic directly here
	int currCount = count.top();
	count.pop();

	ValueType arrayType = (count.size() > 1) ? ValueType::REFERENCE : valueType;

	if (count.size() == 0) {
		Value value;
		value.data.longValue = 0; // initialize with zeros
		value.type = arrayType;
		for (int i = 0; i < currCount; i++) {
			array->pushValue(value);
		}
	} else {
		for (int i = 0; i < currCount; i++) {
			ArrayObject *subArray = new ArrayObject(arrayType);
			
			// Recursively populate sub-arrays
			stack<int> subCount = count; // copy remaining dimensions
			ValueType subArrayType = (subCount.size() > 1) ? ValueType::REFERENCE : valueType;
			
			// Simple recursive population for sub-arrays
			int subCurrCount = subCount.top();
			subCount.pop();
			
			if (subCount.size() == 0) {
				Value value;
				value.data.longValue = 0;
				value.type = subArrayType;
				for (int j = 0; j < subCurrCount; j++) {
					subArray->pushValue(value);
				}
			} else {
				// For deeper nesting, create null references
				Value nullValue;
				nullValue.type = ValueType::REFERENCE;
				nullValue.data.object = NULL;
				for (int j = 0; j < subCurrCount; j++) {
					subArray->pushValue(nullValue);
				}
			}
			
			Value subArrayValue;
			subArrayValue.type = ValueType::REFERENCE;
			subArrayValue.data.object = subArray;
			array->pushValue(subArrayValue);
		}
	}

	Value arrayValue;
	arrayValue.type = ValueType::REFERENCE;
	arrayValue.data.object = array;

	topFrame->empilharOperandStack(arrayValue);

	topFrame->pc += 4;
}
