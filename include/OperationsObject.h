#ifndef operationsobject_h
#define operationsobject_h

#include "BasicTypes.h"

/** @class OperationsObject
 * @brief Handles object and method operations (invoke, new, fields, etc.)
 */
class OperationsObject {
public:
	/**
	 * @brief Constructor that takes a reference to the _isWide flag.
	 */
	explicit OperationsObject(bool &isWideRef);

	void getstatic();
	void putstatic();
	void getfield();
	void putfield();
	void invokevirtual();
	void invokespecial();
	void invokestatic();
	void invokeinterface();
	void func_new();
	void newarray();
	void anewarray();
	void arraylength();
	void athrow();
	void checkcast();
	void instanceof();
	void monitorenter();
	void monitorexit();
	void multianewarray();

private:
	bool &_isWide; // Reference to the shared _isWide flag
};

#endif /* operationsobject_h */
