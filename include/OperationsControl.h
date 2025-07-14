#ifndef operationscontrol_h
#define operationscontrol_h

#include "BasicTypes.h"

/** @class OperationsControl
 * @brief Handles control flow operations (if, goto, return, etc.)
 */
class OperationsControl {
public:
	/**
	 * @brief Constructor that takes a reference to the _isWide state variable.
	 * @param isWide Reference to the shared _isWide state variable.
	 */
	OperationsControl(bool& isWide);

	void ifeq();
	void ifne();
	void iflt();
	void ifge();
	void ifgt();
	void ifle();
	void if_icmpeq();
	void if_icmpne();
	void if_icmplt();
	void if_icmpge();
	void if_icmpgt();
	void if_icmple();
	void if_acmpeq();
	void if_acmpne();
	void func_goto();
	void jsr();
	void ret();
	void tableswitch();
	void lookupswitch();
	void ireturn();
	void lreturn();
	void freturn();
	void dreturn();
	void areturn();
	void func_return();
	void ifnull();
	void ifnonnull();
	void goto_w();
	void jsr_w();

private:
	bool& _isWide; ///< Reference to shared _isWide state variable
};

#endif /* operationscontrol_h */
