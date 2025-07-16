#include "OperationsArithmetic.h"
#include "Frame.h"
#include "PilhaJVM.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

// Stack manipulation operations

void OperationsArithmetic::pop() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type != ValueType::LONG);
	assert(value.type != ValueType::DOUBLE);

	topFrame->pc += 1;
}

void OperationsArithmetic::pop2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();

	topFrame->pc += 1;
}

void OperationsArithmetic::dup() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type != ValueType::LONG);
	assert(value.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value);
	topFrame->empilharOperandStack(value);

	topFrame->pc += 1;
}

void OperationsArithmetic::dup_x1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	assert(value_1.type != ValueType::LONG);
	assert(value_1.type != ValueType::DOUBLE);
	Value value_2 = topFrame->desempilhaOperandStack();
	assert(value_2.type != ValueType::LONG);
	assert(value_2.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void OperationsArithmetic::dup_x2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_3 = topFrame->desempilhaOperandStack();

	assert(value_1.type != ValueType::LONG);
	assert(value_1.type != ValueType::DOUBLE);
	assert(value_3.type != ValueType::LONG);
	assert(value_3.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_3);
	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void OperationsArithmetic::dup2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	Value value_2 = topFrame->desempilhaOperandStack();
	assert(value_2.type != ValueType::LONG);
	assert(value_2.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void OperationsArithmetic::dup2_x1() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_3 = topFrame->desempilhaOperandStack();

	assert(value_2.type != ValueType::LONG);
	assert(value_2.type != ValueType::DOUBLE);
	assert(value_3.type != ValueType::LONG);
	assert(value_3.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_3);
	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void OperationsArithmetic::dup2_x2() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_3 = topFrame->desempilhaOperandStack();
	Value value_4 = topFrame->desempilhaOperandStack();

	assert(value_2.type != ValueType::LONG);
	assert(value_2.type != ValueType::DOUBLE);
	assert(value_4.type != ValueType::LONG);
	assert(value_4.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_4);
	topFrame->empilharOperandStack(value_3);
	topFrame->empilharOperandStack(value_2);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void OperationsArithmetic::swap() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	Value value_2 = topFrame->desempilhaOperandStack();

	assert(value_1.type != ValueType::LONG);
	assert(value_1.type != ValueType::DOUBLE);
	assert(value_2.type != ValueType::LONG);
	assert(value_2.type != ValueType::DOUBLE);

	topFrame->empilharOperandStack(value_1);
	topFrame->empilharOperandStack(value_2);

	topFrame->pc += 1;
}

// Arithmetic operations

void OperationsArithmetic::iadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value soma;
	soma.type = ValueType::INT;
	soma.printType = ValueType::INT;
	soma.data.intValue = value_1.data.intValue + value_2.data.intValue;

	topFrame->empilharOperandStack(soma);

	topFrame->pc += 1;
}

void OperationsArithmetic::ladd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value soma;
	soma.type = ValueType::LONG;
	soma.printType = ValueType::LONG;
	soma.data.longValue = value_1.data.longValue + value_2.data.longValue;

	topFrame->empilharOperandStack(soma);

	topFrame->pc += 1;
}

void OperationsArithmetic::fadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value soma;
	soma.type = ValueType::FLOAT;
	soma.printType = ValueType::FLOAT;
	soma.data.floatValue = value_1.data.floatValue + value_2.data.floatValue;

	topFrame->empilharOperandStack(soma);

	topFrame->pc += 1;
}

void OperationsArithmetic::dadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value soma;
	soma.type = ValueType::DOUBLE;
	soma.printType = ValueType::DOUBLE;
	soma.data.doubleValue = value_1.data.doubleValue + value_2.data.doubleValue;

	topFrame->empilharOperandStack(soma);

	topFrame->pc += 1;
}

void OperationsArithmetic::isub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value subtracao;
	subtracao.type = ValueType::INT;
	subtracao.printType = ValueType::INT;
	subtracao.data.intValue = value_1.data.intValue - value_2.data.intValue;

	topFrame->empilharOperandStack(subtracao);

	topFrame->pc += 1;
}

void OperationsArithmetic::lsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value subtracao;
	subtracao.type = ValueType::LONG;
	subtracao.printType = ValueType::LONG;
	subtracao.data.longValue = value_1.data.longValue - value_2.data.longValue;

	topFrame->empilharOperandStack(subtracao);

	topFrame->pc += 1;
}

void OperationsArithmetic::fsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value subtracao;
	subtracao.type = ValueType::FLOAT;
	subtracao.printType = ValueType::FLOAT;
	subtracao.data.floatValue = value_1.data.floatValue - value_2.data.floatValue;

	topFrame->empilharOperandStack(subtracao);

	topFrame->pc += 1;
}

void OperationsArithmetic::dsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value subtracao;
	subtracao.type = ValueType::DOUBLE;
	subtracao.printType = ValueType::DOUBLE;
	subtracao.data.doubleValue = value_1.data.doubleValue - value_2.data.doubleValue;

	topFrame->empilharOperandStack(subtracao);

	topFrame->pc += 1;
}

void OperationsArithmetic::imul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value multiplicacao;
	multiplicacao.type = ValueType::INT;
	multiplicacao.printType = ValueType::INT;
	multiplicacao.data.intValue = value_1.data.intValue * value_2.data.intValue;

	topFrame->empilharOperandStack(multiplicacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::lmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value multiplicacao;
	multiplicacao.type = ValueType::LONG;
	multiplicacao.printType = ValueType::LONG;
	multiplicacao.data.longValue = value_1.data.longValue * value_2.data.longValue;

	topFrame->empilharOperandStack(multiplicacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::fmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value multiplicacao;
	multiplicacao.type = ValueType::FLOAT;
	multiplicacao.printType = ValueType::FLOAT;
	multiplicacao.data.floatValue = value_1.data.floatValue * value_2.data.floatValue;

	topFrame->empilharOperandStack(multiplicacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::dmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value multiplicacao;
	multiplicacao.type = ValueType::DOUBLE;
	multiplicacao.printType = ValueType::DOUBLE;
	multiplicacao.data.doubleValue = value_1.data.doubleValue * value_2.data.doubleValue;

	topFrame->empilharOperandStack(multiplicacao);

	topFrame->pc += 1;
}

// Division operations

void OperationsArithmetic::idiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	if (value_2.data.intValue == 0) {
		cout << "ArithmeticException: / by zero" << endl;
		exit(1);
	}

	Value divisao;
	divisao.type = ValueType::INT;
	divisao.printType = ValueType::INT;
	divisao.data.intValue = value_1.data.intValue / value_2.data.intValue;

	topFrame->empilharOperandStack(divisao);

	topFrame->pc += 1;
}

void OperationsArithmetic::ldiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	if (value_2.data.longValue == 0) {
		cout << "ArithmeticException: / by zero" << endl;
		exit(1);
	}

	Value divisao;
	divisao.type = ValueType::LONG;
	divisao.printType = ValueType::LONG;
	divisao.data.longValue = value_1.data.longValue / value_2.data.longValue;

	topFrame->empilharOperandStack(divisao);

	topFrame->pc += 1;
}

void OperationsArithmetic::fdiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value divisao;
	divisao.type = ValueType::FLOAT;
	divisao.printType = ValueType::FLOAT;
	divisao.data.floatValue = value_1.data.floatValue / value_2.data.floatValue;

	topFrame->empilharOperandStack(divisao);

	topFrame->pc += 1;
}

void OperationsArithmetic::ddiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value divisao;
	divisao.type = ValueType::DOUBLE;
	divisao.printType = ValueType::DOUBLE;
	divisao.data.doubleValue = value_1.data.doubleValue / value_2.data.doubleValue;

	topFrame->empilharOperandStack(divisao);

	topFrame->pc += 1;
}

// Remainder operations

void OperationsArithmetic::irem() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	if (value_2.data.intValue == 0) {
		cout << "ArithmeticException: / by zero" << endl;
		exit(1);
	}

	Value resto;
	resto.type = ValueType::INT;
	resto.printType = ValueType::INT;
	resto.data.intValue = value_1.data.intValue % value_2.data.intValue;

	topFrame->empilharOperandStack(resto);

	topFrame->pc += 1;
}

void OperationsArithmetic::lrem() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	if (value_2.data.longValue == 0) {
		cout << "ArithmeticException: / by zero" << endl;
		exit(1);
	}

	Value resto;
	resto.type = ValueType::LONG;
	resto.printType = ValueType::LONG;
	resto.data.longValue = value_1.data.longValue % value_2.data.longValue;

	topFrame->empilharOperandStack(resto);

	topFrame->pc += 1;
}

void OperationsArithmetic::frem() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resto;
	resto.type = ValueType::FLOAT;
	resto.printType = ValueType::FLOAT;
	resto.data.floatValue = fmod(value_1.data.floatValue, value_2.data.floatValue);

	topFrame->empilharOperandStack(resto);

	topFrame->pc += 1;
}

void OperationsArithmetic::drem() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resto;
	resto.type = ValueType::DOUBLE;
	resto.printType = ValueType::DOUBLE;
	resto.data.doubleValue = fmod(value_1.data.doubleValue, value_2.data.doubleValue);

	topFrame->empilharOperandStack(resto);

	topFrame->pc += 1;
}

// Negation operations

void OperationsArithmetic::ineg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value negacao;
	negacao.type = ValueType::INT;
	negacao.printType = ValueType::INT;
	negacao.data.intValue = -value.data.intValue;

	topFrame->empilharOperandStack(negacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::lneg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value negacao;
	negacao.type = ValueType::LONG;
	negacao.printType = ValueType::LONG;
	negacao.data.longValue = -value.data.longValue;

	topFrame->empilharOperandStack(negacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::fneg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value negacao;
	negacao.type = ValueType::FLOAT;
	negacao.printType = ValueType::FLOAT;
	negacao.data.floatValue = -value.data.floatValue;

	topFrame->empilharOperandStack(negacao);

	topFrame->pc += 1;
}

void OperationsArithmetic::dneg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value negacao;
	negacao.type = ValueType::DOUBLE;
	negacao.printType = ValueType::DOUBLE;
	negacao.data.doubleValue = -value.data.doubleValue;

	topFrame->empilharOperandStack(negacao);

	topFrame->pc += 1;
}

// Shift operations

void OperationsArithmetic::ishl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = value_1.data.intValue << (value_2.data.intValue & 0x1f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::lshl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = value_1.data.longValue << (value_2.data.intValue & 0x3f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::ishr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = value_1.data.intValue >> (value_2.data.intValue & 0x1f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::lshr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = value_1.data.longValue >> (value_2.data.intValue & 0x3f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::iushr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = (uint32_t)value_1.data.intValue >> (value_2.data.intValue & 0x1f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::lushr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = (uint64_t)value_1.data.longValue >> (value_2.data.intValue & 0x3f);

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

// Bitwise operations

void OperationsArithmetic::iand() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = value_1.data.intValue & value_2.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::land() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = value_1.data.longValue & value_2.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::ior() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = value_1.data.intValue | value_2.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::lor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = value_1.data.longValue | value_2.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::ixor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = value_1.data.intValue ^ value_2.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::lxor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = value_1.data.longValue ^ value_2.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

// Increment operation

void OperationsArithmetic::iinc() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	const u1 *code = topFrame->getCode(topFrame->pc);
	u1 index, constant;

	if (_isWide) {
		index = (code[1] << 8) | code[2];
		constant = (code[3] << 8) | code[4];
		topFrame->pc += 5;
		_isWide = false;
	} else {
		index = code[1];
		constant = (int8_t)code[2];
		topFrame->pc += 3;
	}

	Value currentValue = topFrame->obterLocalVariableValue(index);
	currentValue.data.intValue += constant;
	topFrame->trocaLocalVariable(currentValue, index);
}

// Type conversion operations

void OperationsArithmetic::i2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = (int64_t)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::i2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::FLOAT;
	resultado.printType = ValueType::FLOAT;
	resultado.data.floatValue = (float)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::i2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::DOUBLE;
	resultado.printType = ValueType::DOUBLE;
	resultado.data.doubleValue = (double)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::l2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = (int32_t)value.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::l2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::FLOAT;
	resultado.printType = ValueType::FLOAT;
	resultado.data.floatValue = (float)value.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::l2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::DOUBLE;
	resultado.printType = ValueType::DOUBLE;
	resultado.data.doubleValue = (double)value.data.longValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::f2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = (int32_t)value.data.floatValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::f2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = (int64_t)value.data.floatValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::f2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::DOUBLE;
	resultado.printType = ValueType::DOUBLE;
	resultado.data.doubleValue = (double)value.data.floatValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::d2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;
	resultado.data.intValue = (int32_t)value.data.doubleValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::d2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::LONG;
	resultado.printType = ValueType::LONG;
	resultado.data.longValue = (int64_t)value.data.doubleValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::d2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::FLOAT;
	resultado.printType = ValueType::FLOAT;
	resultado.data.floatValue = (float)value.data.doubleValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::i2b() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::BYTE;
	resultado.printType = ValueType::BYTE;
	resultado.data.byteValue = (int8_t)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::i2c() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::CHAR;
	resultado.printType = ValueType::CHAR;
	resultado.data.charValue = (uint8_t)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::i2s() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::SHORT;
	resultado.printType = ValueType::SHORT;
	resultado.data.shortValue = (int16_t)value.data.intValue;

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

// Comparison operations

void OperationsArithmetic::lcmp() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;

	if (value_1.data.longValue > value_2.data.longValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.longValue == value_2.data.longValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::fcmpl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;

	if (isnan(value_1.data.floatValue) || isnan(value_2.data.floatValue)) {
		resultado.data.intValue = -1;
	} else if (value_1.data.floatValue > value_2.data.floatValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue == value_2.data.floatValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::fcmpg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;

	if (isnan(value_1.data.floatValue) || isnan(value_2.data.floatValue)) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue > value_2.data.floatValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue == value_2.data.floatValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::dcmpl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;

	if (isnan(value_1.data.doubleValue) || isnan(value_2.data.doubleValue)) {
		resultado.data.intValue = -1;
	} else if (value_1.data.doubleValue > value_2.data.doubleValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue == value_2.data.doubleValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void OperationsArithmetic::dcmpg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	Value resultado;
	resultado.type = ValueType::INT;
	resultado.printType = ValueType::INT;

	if (isnan(value_1.data.doubleValue) || isnan(value_2.data.doubleValue)) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue > value_2.data.doubleValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue == value_2.data.doubleValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}