#ifndef operationsconstants_h
#define operationsconstants_h

#include "BasicTypes.h"

/** @class OperationsConstants
 * @brief Handles constant loading operations (iconst, fconst, ldc, etc.)
 */
class OperationsConstants {
public:
	/**
	 * @brief Implementa a funcionalidade da instrução aconst_null.
	 */
	void aconst_null();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_m1.
	 */
	void iconst_m1();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_0.
	 */
	void iconst_0();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_1.
	 */
	void iconst_1();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_2.
	 */
	void iconst_2();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_3.
	 */
	void iconst_3();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_4.
	 */
	void iconst_4();

	/**
	 * @brief Implementa a funcionalidade da instrução iconst_5.
	 */
	void iconst_5();

	/**
	 * @brief Implementa a funcionalidade da instrução lconst_0.
	 */
	void lconst_0();

	/**
	 * @brief Implementa a funcionalidade da instrução lconst_1.
	 */
	void lconst_1();

	/**
	 * @brief Implementa a funcionalidade da instrução fconst_0.
	 */
	void fconst_0();

	/**
	 * @brief Implementa a funcionalidade da instrução fconst_1.
	 */
	void fconst_1();

	/**
	 * @brief Implementa a funcionalidade da instrução fconst_2.
	 */
	void fconst_2();

	/**
	 * @brief Implementa a funcionalidade da instrução dconst_0.
	 */
	void dconst_0();

	/**
	 * @brief Implementa a funcionalidade da instrução dconst_1.
	 */
	void dconst_1();

	/**
	 * @brief Implementa a funcionalidade da instrução bipush.
	 */
	void bipush();

	/**
	 * @brief Implementa a funcionalidade da instrução sipush.
	 */
	void sipush();

	/**
	 * @brief Implementa a funcionalidade da instrução ldc.
	 */
	void ldc();

	/**
	 * @brief Implementa a funcionalidade da instrução ldc_w.
	 */
	void ldc_w();

	/**
	 * @brief Implementa a funcionalidade da instrução ldc2_w.
	 */
	void ldc2_w();
};

#endif /* operationsconstants_h */
