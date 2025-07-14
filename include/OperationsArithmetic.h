#ifndef operationsarithmetic_h
#define operationsarithmetic_h

#include "BasicTypes.h"

/** @class OperationsArithmetic
 * @brief Handles arithmetic and stack manipulation operations
 */
class OperationsArithmetic {
public:
	/**
	 * @brief Constructor that takes reference to isWide flag
	 */
	OperationsArithmetic(bool& isWide) : _isWide(isWide) {}

private:
	bool& _isWide;  // Reference to the _isWide flag from main Operations class

public:
	void pop();
	void pop2();
	void dup();
	void dup_x1();
	void dup_x2();
	void dup2();
	void dup2_x1();
	void dup2_x2();
	void swap();
	void iadd();
	void ladd();
	void fadd();
	void dadd();
	void isub();
	void lsub();
	void fsub();
	void dsub();
	void imul();
	void lmul();
	void fmul();
	void dmul();
	void idiv();
	void ldiv();
	void fdiv();
	void ddiv();
	void irem();
	void lrem();
	void frem();
	void drem();
	void ineg();
	void lneg();
	void fneg();
	void dneg();
	void ishl();
	void lshl();
	void ishr();
	void lshr();
	void iushr();
	void lushr();
	void iand();
	void land();
	void ior();
	void lor();
	void ixor();
	void lxor();
	void iinc();
	void i2l();
	void i2f();
	void i2d();
	void l2i();
	void l2f();
	void l2d();
	void f2i();
	void f2l();
	void f2d();
	void d2i();
	void d2l();
	void d2f();
	void i2b();
	void i2c();
	void i2s();
	void lcmp();
	void fcmpl();
	void fcmpg();
	void dcmpl();
	void dcmpg();
};

#endif /* operationsarithmetic_h */
