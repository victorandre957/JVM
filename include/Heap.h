#ifndef Heap_h
#define Heap_h

#include <iostream>
#include <cstdlib>

#include "Object.h"

using namespace std;

/**  @class Heap
 *  @brief Gerencia as operações do heap
 * @brief Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class Heap {
public:
	/**
	 * @brief Obter a única instância da Heap.
	 * @return A instância da Heap.
	 */
	static Heap& getInstance() {
		static Heap instance;
		return instance;
	}

	/**
	 * @brief Destrutor padrão.
	 */
	~Heap();

	/**
	 * @brief Adiciona um objeto à heap.
	 */
	void addObject(Object *object);

private:
	/**
	 * Construtor padrão.
	 */
	Heap();

	Heap(Heap const&); // não permitir implementação do construtor de cópia
	void operator=(Heap const&); // não permitir implementação do operador de igual

	/**
	 * Array dinâmico que armazena todos os objetos usando malloc/free.
	 */
	Object** _objectArray;
	
	/**
	 * Número atual de objetos armazenados.
	 */
	size_t _objectCount;
	
	/**
	 * Capacidade atual do array.
	 */
	size_t _capacity;
	
	/**
	 * Capacidade inicial do array.
	 */
	static const size_t INITIAL_CAPACITY = 16;
	
	/**
	 * Fator de crescimento quando o array precisa ser expandido.
	 */
	static const size_t GROWTH_FACTOR = 2;
};

#endif // Heap_h
