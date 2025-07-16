#ifndef operationsbase_h
#define operationsbase_h

#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <cstdlib>

#include "Object.h"
#include "BasicTypes.h"
#include "InstanceClass.h"

using namespace std;

class StaticClass;

/** @class OperationsBase
 * @brief Base class for JVM operations containing core functionality
 */
class OperationsBase {
public:
	/**
	 * @brief Destrutor padrão.
	 */
	virtual ~OperationsBase();

	/**
	 * @brief Inicia a Execution Engine com a classe passada.
	 *
	 * Esse método irá iniciar execução através do método estático main.
	 * @param classRuntime  classe que a pesquisa irá ser realizada.
	 */
	void executarMetodos(StaticClass *classRuntime);

	/**
	 * @brief Verifica se o método informado existe na classe atual.
	 * @param classRuntime A classe que a pesquisa irá ser realizada.
	 * @param name O nome do método.
	 * @param descriptor O descritor do método.
	 * @return Retorna \c true caso o método exista, ou \c false caso contrário.
	 */
	bool verificarMetodoExiste(const StaticClass *classRuntime, const string& name, const string& descriptor);

	/**
	 * @brief Popula os vetores de um multiarray
	 * @param array Cada array que representa uma dimansão
	 * @param value Referência à uma classe
	 * @param count Número de elementos em um array
	 */
	void populateMultiarray(ArrayObject *array, ValueType value, stack<int> count);

protected:
	/**
	 * @brief Construtor padrão.
	 */
	OperationsBase();

	/**
	 * Armazena \c true se a última instrução foi um wide, e \c false caso contrário.
	 */
	bool _isWide;

	/**
	 * @brief Implementa a funcionalidade da instrução nop.
	 */
	void nop();

	/**
	 * @brief Implementa a funcionalidade da instrução wide.
	 */
	void wide();

	/**
	 * @brief Inicializa a tabela de ponteiros para funções de instruções.
	 */
	virtual void initInstructions() = 0;

	/**
	 * @brief Virtual method to execute instruction based on opcode.
	 * @param opcode The bytecode instruction opcode.
	 */
	virtual void executeInstruction(u1 opcode) = 0;
};

#endif /* operationsbase_h */
