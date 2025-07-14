
#include "Heap.h"

using namespace std;

Heap::Heap() : _objectCount(0), _capacity(INITIAL_CAPACITY) {
	// Aloca o array inicial usando malloc
	_objectArray = static_cast<Object**>(malloc(_capacity * sizeof(Object*)));
	if (!_objectArray) {
		cerr << "OutOfMemoryError" << endl;
		exit(1);
	}
}

Heap::~Heap() {
	// Libera todos os objetos armazenados
	for (size_t i = 0; i < _objectCount; i++) {
		delete _objectArray[i];
	}
	
	// Libera o array de ponteiros
	free(_objectArray);
}

void Heap::addObject(Object *object) {
	// Verifica se precisa expandir o array
	if (_objectCount >= _capacity) {
		size_t newCapacity = _capacity * GROWTH_FACTOR;
		Object** newArray = static_cast<Object**>(realloc(_objectArray, newCapacity * sizeof(Object*)));
		
		if (!newArray) {
			cerr << "OutOfMemoryError" << endl;
			exit(1);
		}
		
		_objectArray = newArray;
		_capacity = newCapacity;
	}
	
	// Adiciona o objeto ao array
	_objectArray[_objectCount] = object;
	_objectCount++;
}
