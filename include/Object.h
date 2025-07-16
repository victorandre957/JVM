#ifndef object_h
#define object_h

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "BasicTypes.h"

using namespace std;

/** @class Object
 * @brief Classe base utilizada para todos elementos que se caracterizam como objetos, como: instância de classe e arrays.
 */
class Object {
public:
	/**
	 * @brief Destrutor virtual para permitir destruição polimórfica segura.
	 */
	virtual ~Object() = default;

	/**
	 * @brief Método utilizado para declaração do tipo de objeto.
	 * @return O tipo de objeto.
	 */
	virtual ObjectType objectType() = 0;
};

/** @class ArrayObject
 * @brief Estrutura de armazenamento
 * @brief Representa um objeto do tipo array.
 */
class ArrayObject: public Object {
public:
	/**
	 * @brief Construtor padrão.
	 * @param type O tipo de dado que o array irá armazenar.
	 */
	explicit ArrayObject(ValueType type);

	/**
	 * @brief Destrutor padrão.
	 */
	~ArrayObject() override;

	/**
	 * @brief Representa o tipo de objeto (ObjectType::ARRAY).
	 * @return O tipo de objeto.
	 */
	ObjectType objectType() override;

	/**
	 * @brief Obtém o tipo de conteúdo do array.
	 * @return O tipo que o array armazena.
	 */
	ValueType arrayContentType();

	/**
	 * @brief Realiza a adição de um valor no array.
	 * @param value O valor que será inserido no array.
	 */
	void pushValue(Value value);

	/**
	 * @brief Remove um elemento do array dado o seu índice.
	 * @param index O índice do elemento que será removido.
	 * @return O valor removido.
	 */
	Value removeAt(uint32_t index);

	/**
	 * @brief Remove o último elemento do array.
	 * @return O valor removido.
	 */
	Value removeLast();

	/**
	 * @brief Remove o primeiro elemento do array.
	 * @return O valor removido.
	 */
	Value removeFirst();

	/**
	 * @brief Obtém o tamanho atual do array.
	 * @return O tamanho atual do array.
	 */
	uint32_t getSize();

	/**
	 * @brief Obtém o elemento dado o seu índice.
	 * @param index O índice do elemento.
	 * @return O elemento do array de índice index.
	 */
	Value getValue(uint32_t index);

	/**
	 * @brief Substitui um elemento do array.
	 * @param index O índice do elemento que será substituído.
	 * @param value O novo valor que será colocado.
	 */
	void changeValueAt(uint32_t index, Value value);

private:
	/**
	 * O tipo de valor que o array armazena.
	 */
	ValueType _arrayType;

	/**
	 * O vetor interno que armazena os elementos.
	 */
	vector<Value> _elements;
};

/** @class StringObject
 * @brief Representa um objeto do tipo String.
 */
class StringObject : public Object {
public:
	/**
	 * @brief Construtor padrão.
	 * @param s O valor inicial da string.
	 */
	explicit StringObject(const string& s = "");

	/**
	 * @brief Destrutor padrão.
	 */
	~StringObject() override;

	/**
	 * @brief Obtém o tipo do objeto (string).
	 * @return O tipo do objeto.
	 */
	ObjectType objectType() override;

	/**
	 * @brief Obtém a sequência de caracteres presente na string.
	 * @return Retorna a string como uma std::string.
	 */
	const string& getString() const;

	/**
	 * @brief Substitui o valor da string.
	 * @param s O novo valor da string.
	 */
	void setString(const string& s);

private:
	/**
	 * A string interna.
	 */
	string _internalString;
};

// ============================================================================
// IMPLEMENTATION - ArrayObject
// ============================================================================

inline ArrayObject::ArrayObject(ValueType type) : _arrayType(type) {
}

inline ArrayObject::~ArrayObject() {
}

inline ObjectType ArrayObject::objectType() {
	return ObjectType::ARRAY;
}

inline ValueType ArrayObject::arrayContentType() {
	return _arrayType;
}

inline void ArrayObject::pushValue(Value value) {
        assert(value.type == _arrayType);
        value.printType = value.type;
        _elements.push_back(value);
}

inline Value ArrayObject::removeAt(uint32_t index) { // @suppress("unused function")
	assert(_elements.size() > 0);
	assert(index < _elements.size());

	Value value = _elements[index];
	_elements.erase(_elements.begin() + index);
	return value;
}

inline Value ArrayObject::removeLast() { // @suppress("unused function")
	assert(_elements.size() > 0);

	Value value = _elements.back();
	_elements.pop_back();
	return value;
}

inline Value ArrayObject::removeFirst() { // @suppress("unused function")
	assert(_elements.size() > 0);

	Value value = _elements.front();
	_elements.erase(_elements.begin());
	return value;
}

inline uint32_t ArrayObject::getSize() {
	return _elements.size();
}

inline Value ArrayObject::getValue(uint32_t index) {
	assert(_elements.size() > 0);

	if (index >= _elements.size()) {
		cerr << "ArrayIndexOutOfBoundsException" << endl;
		exit(1);
	}

	return _elements[index];
}

inline void ArrayObject::changeValueAt(uint32_t index, Value value) {
	_elements[index] = value;
}

// ============================================================================
// IMPLEMENTATION - StringObject
// ============================================================================

inline StringObject::StringObject(const string& s) : _internalString(s) {
}

inline StringObject::~StringObject() {
}

inline ObjectType StringObject::objectType() {
	return ObjectType::STRING_INSTANCE;
}

inline const string& StringObject::getString() const {
	return _internalString;
}

inline void StringObject::setString(const string& s) { // @suppress("unused function")
	_internalString = s;
}

#endif // object_h
