#include "BasicTypes.h"
#include "Object.h"


/*------------------------------------------------------------------------------------
 * Implementação do ArrayObject
 * Esta classe representa um objeto de array, encapsulando um vetor de valores
 * de um tipo específico.
 * Ela fornece métodos para manipular os valores do array, como adicionar, remover
 * e acessar elementos, além de retornar o tipo do objeto e o tipo dos valores
 * contidos no array.
 *------------------------------------------------------------------------------------*/

Object::ArrayObject(ValueType type) :
		_arrayType(type) {

}

Object::~ArrayObject() {

}

ObjectType Object::objectType() {
	return ObjectType::ARRAY;
}

ValueType Object::arrayContentType() {
	return _arrayType;
}

void Object::pushValue(Value value) {
	assert(value.type == _arrayType);

	_elements.push_back(value);
}

Value Object::removeAt(uint32_t index) {
	assert(_elements.size() > 0);
	assert(index < _elements.size());

	Value value = _elements[index];
	_elements.erase(_elements.begin() + index);
	return value;
}

Value Object::removeLast() {
	assert(_elements.size() > 0);

	Value value = _elements.back();
	_elements.pop_back();
	return value;
}

Value Object::removeFirst() {
	assert(_elements.size() > 0);

	Value value = _elements.front();
	_elements.erase(_elements.begin());
	return value;
}

uint32_t Object::getSize() {
	return _elements.size();
}

Value Object::getValue(uint32_t index) {
	assert(_elements.size() > 0);
//    assert(index < _elements.size());

	if (index >= _elements.size()) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(1);
	}

	return _elements[index];
}

void Object::changeValueAt(uint32_t index, Value value) {
	_elements[index] = value;
}

/*------------------------------------------------------------------------------------
 * Implementação do StringObject
 * Esta classe representa um objeto de string, encapsulando uma string interna.
 * Ela fornece métodos para obter e definir o valor da string,
 * além de retornar o tipo do objeto.
 *------------------------------------------------------------------------------------*/

Object::StringObject(string s) :
		_internalString(s) {
}

Object::~StringObject() {
}

ObjectType Object::object_type() {
	return ObjectType::STRING_INSTANCE;
}

string Object::getString() {
	return _internalString;
}

void Object::setString(string s) {
	_internalString = s;
}