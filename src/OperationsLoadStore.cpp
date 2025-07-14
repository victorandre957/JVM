#include "OperationsLoadStore.h"
#include "Frame.h"
#include "PilhaJVM.h"
#include "Object.h"
#include <iostream>
#include <cassert>

using namespace std;

// Load operations for local variables

// Pode ser modificado pelo wide
void OperationsLoadStore::iload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::INT);

	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::lload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > (index + 1)));

	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::LONG);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::fload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::dload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > (index + 1)));

	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::DOUBLE);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::aload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);
}

// Fast load operations for specific indices

void OperationsLoadStore::iload_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(0);
	assert(value.type == ValueType::INT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::iload_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::INT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::iload_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::INT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::iload_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::INT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::lload_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(0);
	assert(value.type == ValueType::LONG);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::lload_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::LONG);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::lload_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::LONG);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::lload_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(4);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::LONG);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::fload_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(0);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::fload_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::fload_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::fload_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::dload_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(0);
	assert(value.type == ValueType::DOUBLE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::dload_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::DOUBLE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::dload_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::DOUBLE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::dload_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value;

	value = topFrame->obterLocalVariableValue(4);
	assert(value.type == ValueType::PADDING);
	topFrame->empilharOperandStack(value);

	value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::DOUBLE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::aload_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(0);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::aload_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(1);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::aload_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(2);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsLoadStore::aload_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->obterLocalVariableValue(3);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

// Array load operations

void OperationsLoadStore::iaload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	topFrame->empilharOperandStack(array->getValue(index.data.intValue));
	topFrame->pc += 1;
}

void OperationsLoadStore::laload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if ((signed) index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(array->getValue(index.data.intValue));
	topFrame->pc += 1;
}

void OperationsLoadStore::faload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	topFrame->empilharOperandStack(array->getValue(index.data.intValue));
	topFrame->pc += 1;
}

void OperationsLoadStore::daload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(array->getValue(index.data.intValue));
	topFrame->pc += 1;
}

void OperationsLoadStore::aaload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	topFrame->empilharOperandStack(array->getValue(index.data.intValue));
	topFrame->pc += 1;
}

void OperationsLoadStore::baload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	Value value = array->getValue(index.data.intValue);
	assert(value.type == ValueType::BOOLEAN || value.type == ValueType::BYTE);

	if (value.type == ValueType::BOOLEAN) {
		value.data.intValue = (uint32_t) value.data.booleanValue;
		value.printType = ValueType::BOOLEAN;
	} else {
		value.data.intValue = (int32_t) value.data.byteValue;
		value.printType = ValueType::BYTE;
	}
	value.type = ValueType::INT;

	topFrame->empilharOperandStack(value);
	topFrame->pc += 1;
}

void OperationsLoadStore::caload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	Value charValue = array->getValue(index.data.intValue);
	charValue.data.intValue = (uint32_t) charValue.data.charValue;
	charValue.printType = ValueType::CHAR;
	charValue.type = ValueType::INT;

	topFrame->empilharOperandStack(charValue);
	topFrame->pc += 1;
}

void OperationsLoadStore::saload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	Value shortValue = array->getValue(index.data.intValue);
	shortValue.data.intValue = (int32_t) shortValue.data.shortValue;
	shortValue.printType = ValueType::SHORT;
	shortValue.type = ValueType::INT;

	topFrame->empilharOperandStack(shortValue);
	topFrame->pc += 1;
}

// Store operations for local variables

// Pode ser modificado pelo wide
void OperationsLoadStore::istore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::lstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->desempilhaOperandStack(); //padding

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->trocaLocalVariable(value, index);
	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->trocaLocalVariable(padding, index + 1);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::fstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::dstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->desempilhaOperandStack(); //padding

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->trocaLocalVariable(value, index);
	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->trocaLocalVariable(padding, index + 1);
}

// Pode ser modificado pelo wide
void OperationsLoadStore::astore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

// Fast store operations for specific indices

void OperationsLoadStore::istore_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	topFrame->trocaLocalVariable(value, 0);

	topFrame->pc += 1;
}

void OperationsLoadStore::istore_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	topFrame->trocaLocalVariable(value, 1);

	topFrame->pc += 1;
}

void OperationsLoadStore::istore_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	topFrame->trocaLocalVariable(value, 2);

	topFrame->pc += 1;
}

void OperationsLoadStore::istore_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	topFrame->trocaLocalVariable(value, 3);

	topFrame->pc += 1;
}

void OperationsLoadStore::lstore_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->trocaLocalVariable(value, 0);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 1);

	topFrame->pc += 1;
}

void OperationsLoadStore::lstore_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->trocaLocalVariable(value, 1);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 2);

	topFrame->pc += 1;
}

void OperationsLoadStore::lstore_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->trocaLocalVariable(value, 2);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 3);

	topFrame->pc += 1;
}

void OperationsLoadStore::lstore_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->trocaLocalVariable(value, 3);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 4);

	topFrame->pc += 1;
}

void OperationsLoadStore::fstore_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);
	topFrame->trocaLocalVariable(value, 0);

	topFrame->pc += 1;
}

void OperationsLoadStore::fstore_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);
	topFrame->trocaLocalVariable(value, 1);

	topFrame->pc += 1;
}

void OperationsLoadStore::fstore_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);
	topFrame->trocaLocalVariable(value, 2);

	topFrame->pc += 1;
}

void OperationsLoadStore::fstore_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);
	topFrame->trocaLocalVariable(value, 3);

	topFrame->pc += 1;
}

void OperationsLoadStore::dstore_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->trocaLocalVariable(value, 0);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 1);

	topFrame->pc += 1;
}

void OperationsLoadStore::dstore_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->trocaLocalVariable(value, 1);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 2);

	topFrame->pc += 1;
}

void OperationsLoadStore::dstore_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->trocaLocalVariable(value, 2);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 3);

	topFrame->pc += 1;
}

void OperationsLoadStore::dstore_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->trocaLocalVariable(value, 3);

	value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::PADDING);
	topFrame->trocaLocalVariable(value, 4);

	topFrame->pc += 1;
}

void OperationsLoadStore::astore_0() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);
	topFrame->trocaLocalVariable(value, 0);

	topFrame->pc += 1;
}

void OperationsLoadStore::astore_1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);
	topFrame->trocaLocalVariable(value, 1);

	topFrame->pc += 1;
}

void OperationsLoadStore::astore_2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);
	topFrame->trocaLocalVariable(value, 2);

	topFrame->pc += 1;
}

void OperationsLoadStore::astore_3() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);
	topFrame->trocaLocalVariable(value, 3);

	topFrame->pc += 1;
}

// Array store operations

void OperationsLoadStore::iastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue >= (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	value.printType = ValueType::INT;

	assert(value.type == array->arrayContentType());
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::lastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	Value padding = topFrame->desempilhaOperandStack();
	assert(padding.type == ValueType::PADDING);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue >= (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	assert(value.type == array->arrayContentType());
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::fastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue >= (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	assert(value.type == array->arrayContentType());
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::dastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	Value padding = topFrame->desempilhaOperandStack();
	assert(padding.type == ValueType::PADDING);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue >= (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	assert(value.type == array->arrayContentType());
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::aastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack(); // Valor armazenado no index do array
	assert(value.type == ValueType::REFERENCE);
	Value index = topFrame->desempilhaOperandStack(); // Index do arary
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack(); // Referência ao array
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue >= (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::bastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;
	assert(array->arrayContentType() == ValueType::BOOLEAN || array->arrayContentType() == ValueType::BYTE);

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	if (array->arrayContentType() == ValueType::BOOLEAN) {
		value.data.booleanValue = (value.data.intValue != 0) ? true : false;
		value.type = ValueType::BOOLEAN;
		value.printType = ValueType::BOOLEAN;
	} else {
		value.data.byteValue = (uint8_t) value.data.intValue;
		value.type = ValueType::BYTE;
		value.printType = ValueType::BYTE;
	}

	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::castore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	value.data.charValue = (uint8_t) value.data.intValue;
	value.printType = ValueType::CHAR;
	value.type = ValueType::CHAR;
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}

void OperationsLoadStore::sastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	Value index = topFrame->desempilhaOperandStack();
	assert(index.type == ValueType::INT);
	Value arrayref = topFrame->desempilhaOperandStack();
	assert(arrayref.type == ValueType::REFERENCE);
	assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

	array = (ArrayObject *) arrayref.data.object;

	if (array == NULL) {
		cerr << "NullPointerException" << endl;
		exit(1);
	}
	if (index.data.intValue > (signed) array->getSize() || index.data.intValue < 0) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(2);
	}

	value.data.shortValue = (int16_t) value.data.intValue;
	value.printType = ValueType::SHORT;
	value.type = ValueType::SHORT;
	array->changeValueAt(index.data.intValue, value);

	topFrame->pc += 1;
}
