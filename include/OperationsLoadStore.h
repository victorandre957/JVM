#ifndef operationsloadstore_h
#define operationsloadstore_h

#include "OperationsBase.h"

/** @class OperationsLoadStore
 * @brief Handles load and store operations (iload, istore, etc.)
 */
class OperationsLoadStore {
public:
	/**
	 * @brief Constructor that takes reference to isWide flag
	 */
	OperationsLoadStore(bool& isWide) : _isWide(isWide) {}

private:
	bool& _isWide;  // Reference to the _isWide flag from main Operations class

public:
	/**
	 * @brief Implementa a funcionalidade da instrução iload.
	 */
	void iload();

	/**
	 * @brief Implementa a funcionalidade da instrução lload.
	 */
	void lload();

	/**
	 * @brief Implementa a funcionalidade da instrução fload.
	 */
	void fload();

	/**
	 * @brief Implementa a funcionalidade da instrução dload.
	 */
	void dload();

	/**
	 * @brief Implementa a funcionalidade da instrução aload.
	 */
	void aload();

	/**
	 * @brief Implementa a funcionalidade da instrução iload_0.
	 */
	void iload_0();

	/**
	 * @brief Implementa a funcionalidade da instrução iload_1.
	 */
	void iload_1();

	/**
	 * @brief Implementa a funcionalidade da instrução iload_2.
	 */
	void iload_2();

	/**
	 * @brief Implementa a funcionalidade da instrução iload_3.
	 */
	void iload_3();

	/**
	 * @brief Implementa a funcionalidade da instrução lload_0.
	 */
	void lload_0();

	/**
	 * @brief Implementa a funcionalidade da instrução lload_1.
	 */
	void lload_1();

	/**
	 * @brief Implementa a funcionalidade da instrução lload_2.
	 */
	void lload_2();

	/**
	 * @brief Implementa a funcionalidade da instrução lload_3.
	 */
	void lload_3();

	/**
	 * @brief Implementa a funcionalidade da instrução fload_0.
	 */
	void fload_0();

	/**
	 * @brief Implementa a funcionalidade da instrução fload_1.
	 */
	void fload_1();

	/**
	 * @brief Implementa a funcionalidade da instrução fload_2.
	 */
	void fload_2();

	/**
	 * @brief Implementa a funcionalidade da instrução fload_3.
	 */
	void fload_3();

	/**
	 * @brief Implementa a funcionalidade da instrução dload_0.
	 */
	void dload_0();
	void dload_1();
	void dload_2();
	void dload_3();
	void aload_0();
	void aload_1();
	void aload_2();
	void aload_3();
	void iaload();
	void laload();
	void faload();
	void daload();
	void aaload();
	void baload();
	void caload();
	void saload();
	void istore();
	void lstore();
	void fstore();
	void dstore();
	void astore();
	void istore_0();
	void istore_1();
	void istore_2();
	void istore_3();
	void lstore_0();
	void lstore_1();
	void lstore_2();
	void lstore_3();
	void fstore_0();
	void fstore_1();
	void fstore_2();
	void fstore_3();
	void dstore_0();
	void dstore_1();
	void dstore_2();
	void dstore_3();
	void astore_0();
	void astore_1();
	void astore_2();
	void astore_3();
	void iastore();
	void lastore();
	void fastore();
	void dastore();
	void aastore();
	void bastore();
	void castore();
	void sastore();
};

#endif /* operationsloadstore_h */
