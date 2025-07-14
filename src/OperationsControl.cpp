#include "OperationsControl.h"
#include "Frame.h"
#include "PilhaJVM.h"
#include <iostream>
#include <cassert>

using namespace std;

OperationsControl::OperationsControl(bool& isWide) : _isWide(isWide) {
}

// Single value conditional operations

void OperationsControl::ifeq() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue == 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::ifne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue != 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::iflt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue < 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::ifge() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue >= 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::ifgt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue > 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::ifle() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	if (value.data.intValue <= 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

// Integer comparison operations

void OperationsControl::if_icmpeq() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue == value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_icmpne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue != value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_icmplt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue < value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_icmpge() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue >= value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_icmpgt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue > value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_icmple() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);

	if (value1.data.intValue <= value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

// Reference comparison operations

void OperationsControl::if_acmpeq() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::REFERENCE);
	assert(value2.type == ValueType::REFERENCE);

	if (value1.data.object == value2.data.object) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::if_acmpne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::REFERENCE);
	assert(value2.type == ValueType::REFERENCE);

	if (value1.data.object != value2.data.object) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
	}
}

// Unconditional jump operations

void OperationsControl::func_goto() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	topFrame->pc += branchOffset;
}

void OperationsControl::jsr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	int16_t branchOffset = (byte1 << 8) | byte2;

	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 3;
	topFrame->empilharOperandStack(returnAddr);

	topFrame->pc += branchOffset;
}

void OperationsControl::ret() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	uint16_t index = (uint16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
	}

	assert(((int16_t )(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);

	assert(value.type == ValueType::RETURN_ADDR);
	topFrame->trocaLocalVariable(value, index);

	topFrame->pc = value.data.returnAddress;
	_isWide = false;
}

// Switch operations

void OperationsControl::tableswitch() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1* code = topFrame->getCode(topFrame->pc);
	u1 padding = 4 - (topFrame->pc + 1) % 4;
	padding = (padding == 4) ? 0 : padding;

	u1 defaultbyte1 = code[padding + 1];
	u1 defaultbyte2 = code[padding + 2];
	u1 defaultbyte3 = code[padding + 3];
	u1 defaultbyte4 = code[padding + 4];
	int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;

	u1 lowbyte1 = code[padding + 5];
	u1 lowbyte2 = code[padding + 6];
	u1 lowbyte3 = code[padding + 7];
	u1 lowbyte4 = code[padding + 8];
	uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;

	u1 highbyte1 = code[padding + 9];
	u1 highbyte2 = code[padding + 10];
	u1 highbyte3 = code[padding + 11];
	u1 highbyte4 = code[padding + 12];
	uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;

	Value keyValue = topFrame->desempilhaOperandStack();
	assert(keyValue.type == ValueType::INT);
	int32_t key = keyValue.data.intValue;

	uint32_t i;
	uint32_t baseIndex = padding + 13;
	int32_t offsets = highbytes - lowbytes + 1;
	bool matched = false;
	for (i = 0; i < (unsigned) offsets; i++) {
		if ((unsigned) key == (unsigned) lowbytes) {
			int32_t offset = (code[baseIndex] << 24) | (code[baseIndex + 1] << 16) | (code[baseIndex + 2] << 8) | code[baseIndex + 3];
			topFrame->pc += offset;
			matched = true;
			break;
		}
		lowbytes++;
		baseIndex += 4;
	}

	if (!matched) {
		topFrame->pc += defaultBytes; // salto default
	}
}

void OperationsControl::lookupswitch() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1* code = topFrame->getCode(topFrame->pc);
	u1 padding = 4 - (topFrame->pc + 1) % 4;
	padding = (padding == 4) ? 0 : padding;

	u1 defaultbyte1 = code[padding + 1];
	u1 defaultbyte2 = code[padding + 2];
	u1 defaultbyte3 = code[padding + 3];
	u1 defaultbyte4 = code[padding + 4];
	int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;

	u1 npairs1 = code[padding + 5];
	u1 npairs2 = code[padding + 6];
	u1 npairs3 = code[padding + 7];
	u1 npairs4 = code[padding + 8];
	uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

	Value keyValue = topFrame->desempilhaOperandStack();
	assert(keyValue.type == ValueType::INT);
	int32_t key = keyValue.data.intValue;

	uint32_t i;
	uint32_t baseIndex = padding + 9;
	bool matched = false;
	for (i = 0; i < npairs; i++) {
		int32_t match = (code[baseIndex] << 24) | (code[baseIndex + 1] << 16) | (code[baseIndex + 2] << 8) | code[baseIndex + 3];

		if (key == match) {
			int32_t offset = (code[baseIndex + 4] << 24) | (code[baseIndex + 5] << 16) | (code[baseIndex + 6] << 8) | code[baseIndex + 7];
			topFrame->pc += offset;
			matched = true;
			break;
		}
		baseIndex += 8;
	}

	if (!matched) {
		topFrame->pc += defaultBytes; // salto default
	}
}

// Return operations

void OperationsControl::ireturn() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value returnValue = topFrame->desempilhaOperandStack();
	assert(returnValue.type == ValueType::INT);

	stackFrame.destroyTopFrame();

	Frame *newTopFrame = stackFrame.getTopFrame();
	newTopFrame->empilharOperandStack(returnValue);
}

void OperationsControl::lreturn() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value returnValue = topFrame->desempilhaOperandStack();
	assert(returnValue.type == ValueType::LONG);
	assert(topFrame->desempilhaOperandStack().type == ValueType::PADDING); // o debaixo precisa ser padding

	stackFrame.destroyTopFrame();

	Frame *newTopFrame = stackFrame.getTopFrame();
	Value padding;
	padding.type = ValueType::PADDING;
	newTopFrame->empilharOperandStack(padding);
	newTopFrame->empilharOperandStack(returnValue);
}

void OperationsControl::freturn() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value returnValue = topFrame->desempilhaOperandStack();
	assert(returnValue.type == ValueType::FLOAT);

	stackFrame.destroyTopFrame();

	Frame *newTopFrame = stackFrame.getTopFrame();
	newTopFrame->empilharOperandStack(returnValue);
}

void OperationsControl::dreturn() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value returnValue = topFrame->desempilhaOperandStack();
	assert(returnValue.type == ValueType::DOUBLE);
	assert(topFrame->desempilhaOperandStack().type == ValueType::PADDING); // o debaixo precisa ser padding

	stackFrame.destroyTopFrame();

	Frame *newTopFrame = stackFrame.getTopFrame();

	Value padding;
	padding.type = ValueType::PADDING;
	newTopFrame->empilharOperandStack(padding);
	newTopFrame->empilharOperandStack(returnValue);
}

void OperationsControl::areturn() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value returnValue = topFrame->desempilhaOperandStack();
	assert(returnValue.type == ValueType::REFERENCE);

	stackFrame.destroyTopFrame();

	Frame *newTopFrame = stackFrame.getTopFrame();
	newTopFrame->empilharOperandStack(returnValue);
}

void OperationsControl::func_return() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	stackFrame.destroyTopFrame();
}

// Null reference operations

void OperationsControl::ifnull() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value referenceValue = topFrame->desempilhaOperandStack();
	assert(referenceValue.type == ValueType::REFERENCE);

	if (referenceValue.data.object == NULL) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branch = (byte1 << 8) | byte2;
		topFrame->pc += branch;
	} else {
		topFrame->pc += 3;
	}
}

void OperationsControl::ifnonnull() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value referenceValue = topFrame->desempilhaOperandStack();
	assert(referenceValue.type == ValueType::REFERENCE);

	if (referenceValue.data.object != NULL) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branch = (byte1 << 8) | byte2;
		topFrame->pc += branch;
	} else {
		topFrame->pc += 3;
	}
}

// Wide jump operations

void OperationsControl::goto_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u1 byte3 = code[3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topFrame->pc += branchOffset;
}

void OperationsControl::jsr_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u1 byte3 = code[3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 5;
	topFrame->empilharOperandStack(returnAddr);

	topFrame->pc += branchOffset;
	assert((int32_t )topFrame->pc < (int32_t )topFrame->sizeCode());
}
