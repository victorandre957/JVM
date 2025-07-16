#include "OperationsConstants.h"

#include <cmath>
#include "Frame.h"
#include "PilhaJVM.h"
#include "StaticClass.h"
#include "Utils.h"
#include "Object.h"

void OperationsConstants::aconst_null() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::REFERENCE;
	value.printType = ValueType::REFERENCE;
	value.data.object = NULL;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_m1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = -1;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 0;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 1;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 2;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 3;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_4() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 4;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::iconst_5() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::INT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = 5;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::lconst_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::LONG;
	value.type = ValueType::LONG;
	value.printType = ValueType::LONG;
	value.data.longValue = 0;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::lconst_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.printType = ValueType::LONG;
	value.type = ValueType::LONG;
	value.printType = ValueType::LONG;
	value.data.longValue = 1;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::fconst_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::FLOAT;
	value.printType = ValueType::FLOAT;
	value.data.floatValue = 0.0f;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::fconst_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::FLOAT;
	value.printType = ValueType::FLOAT;
	value.data.floatValue = 1.0f;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::fconst_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::FLOAT;
	value.printType = ValueType::FLOAT;
	value.data.floatValue = 2.0f;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::dconst_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::DOUBLE;
	value.printType = ValueType::DOUBLE;
	value.data.doubleValue = 0.0;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::dconst_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;
	value.type = ValueType::DOUBLE;
	value.printType = ValueType::DOUBLE;
	value.data.doubleValue = 1.0;

	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsConstants::bipush() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte = code[1];

	Value value;
	value.printType = ValueType::BYTE;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = (int32_t) (int8_t) byte; // convertendo para inteiro e estendendo o sinal

	topFrame->empilharOperandStack(value);

	topFrame->pc += 2;
}

void OperationsConstants::sipush() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	const u1 *code = topFrame->getCode(topFrame->pc);

	u1 byte1 = code[1];
	u1 byte2 = code[2];

	uint16_t shortValue = (byte1 << 8) | byte2;
	Value value;
	value.printType = ValueType::SHORT;
	value.type = ValueType::INT;
	value.printType = ValueType::INT;
	value.data.intValue = (int32_t) (int16_t) shortValue; // convertendo para inteiro e estendendo o sinal

	topFrame->empilharOperandStack(value);

	topFrame->pc += 3;
}

void OperationsConstants::ldc() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 index = code[1];

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	cp_info entry = constantPool[index - 1];

	Value value;

	if (entry.tag == CONSTANT_String) {
		cp_info utf8Entry = constantPool[entry.info.string_info.string_index - 1];
		assert(utf8Entry.tag == CONSTANT_Utf8);

		const u1* bytes = utf8Entry.info.utf8_info.bytes;
		char utf8String[utf8Entry.info.utf8_info.length + 1];
		int i;
		for (i = 0; i < utf8Entry.info.utf8_info.length; i++) {
			utf8String[i] = bytes[i];
		}
		utf8String[i] = '\0';

		value.type = ValueType::REFERENCE;
		value.printType = ValueType::REFERENCE;
		value.data.object = new StringObject(utf8String);
	} else if (entry.tag == CONSTANT_Integer) {
		value.printType = ValueType::INT;
		value.type = ValueType::INT;
		value.printType = ValueType::INT;
		value.data.intValue = (int32_t) entry.info.integer_info.bytes;
	} else if (entry.tag == CONSTANT_Float) {
		u4 floatBytes = entry.info.float_info.bytes;
		int s = ((floatBytes >> 31) == 0) ? 1 : -1;
		int e = ((floatBytes >> 23) & 0xff);
		int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;

		float number = s * m * pow(2, e - 150);
		value.type = ValueType::FLOAT;
		value.printType = ValueType::FLOAT;
		value.data.floatValue = number;
	} else {
		cerr << "ldc tentando acessar um elemento da CP invalido: " << entry.tag << endl;
		exit(1);
	}

	topFrame->empilharOperandStack(value);
	topFrame->pc += 2;
}

void OperationsConstants::ldc_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u2 index = (byte1 << 8) | byte2;

	const cp_info *constantPool = *(topFrame->obterConstantPool());
	cp_info entry = constantPool[index - 1];

	Value value;

	if (entry.tag == CONSTANT_String) {
		cp_info utf8Entry = constantPool[entry.info.string_info.string_index - 1];
		assert(utf8Entry.tag == CONSTANT_Utf8);

		const u1* bytes = utf8Entry.info.utf8_info.bytes;
		char utf8String[utf8Entry.info.utf8_info.length + 1];
		int i;
		for (i = 0; i < utf8Entry.info.utf8_info.length; i++) {
			utf8String[i] = bytes[i];
		}
		utf8String[i] = '\0';

		value.type = ValueType::REFERENCE;
		value.printType = ValueType::REFERENCE;
		value.data.object = new StringObject(utf8String);
	} else if (entry.tag == CONSTANT_Integer) {
		value.printType = ValueType::INT;
		value.type = ValueType::INT;
		value.printType = ValueType::INT;
		value.data.intValue = entry.info.integer_info.bytes;
	} else if (entry.tag == CONSTANT_Float) {
		u4 floatBytes = entry.info.float_info.bytes;
		int s = ((floatBytes >> 31) == 0) ? 1 : -1;
		int e = ((floatBytes >> 23) & 0xff);
		int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;

		float number = s * m * pow(2, e - 150);
		value.type = ValueType::FLOAT;
		value.printType = ValueType::FLOAT;
		value.data.floatValue = number;
	} else {
		cerr << "ldc_w tentando acessar um elemento da CP invalido: " << entry.tag << endl;
		exit(1);
	}

	topFrame->empilharOperandStack(value);
	topFrame->pc += 3;
}

void OperationsConstants::ldc2_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u2 index = (byte1 << 8) | byte2;

	const cp_info *classFile = *(topFrame->obterConstantPool());
	cp_info entry = classFile[index - 1];

	Value value;

	if (entry.tag == CONSTANT_Long) {
		u4 highBytes = entry.info.long_info.high_bytes;
		u4 lowBytes = entry.info.long_info.low_bytes;

		int64_t longNumber = ((int64_t) highBytes << 32) + lowBytes;
		value.type = ValueType::LONG;
		value.printType = ValueType::LONG;
		value.data.longValue = longNumber;

		Value padding;
		padding.type = ValueType::PADDING;
		padding.printType = ValueType::PADDING;

		topFrame->empilharOperandStack(padding);
	} else if (entry.tag == CONSTANT_Double) {
		u4 highBytes = entry.info.double_info.high_bytes;
		u4 lowBytes = entry.info.double_info.low_bytes;

		int64_t longNumber = ((int64_t) highBytes << 32) + lowBytes;

		int32_t s = (((uint64_t)longNumber >> 63) == 0) ? 1 : -1;
		int32_t e = (int32_t) ((longNumber >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (longNumber & 0xfffffffffffffL) << 1 : (longNumber & 0xfffffffffffffL) | 0x10000000000000L;

		double doubleNumber = s * m * pow(2, e - 1075);
		value.type = ValueType::DOUBLE;
		value.printType = ValueType::DOUBLE;
		value.data.doubleValue = doubleNumber;

		Value padding;
		padding.type = ValueType::PADDING;
		padding.printType = ValueType::PADDING;

		topFrame->empilharOperandStack(padding);
	} else {
		cerr << "ldc2_w tentando acessar um elemento da CP invalido: " << entry.tag << endl;
		exit(1);
	}

	topFrame->empilharOperandStack(value);
	topFrame->pc += 3;
}