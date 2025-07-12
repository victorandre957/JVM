#ifndef object_h
#define object_h

#include <string>
#include <vector>
#include "BasicTypes.h"

using namespace std;

//------------------- Base Object -------------------
/** @class Object
 * @brief n classe utilizada para todos elementos que se caracterizam como objetos, como: instância de classe e arrays.
 */
class Object {
public:
	/**
	 * @brief Método utilizado para declaração do tipo de objeto.
	 * @return O tipo de objeto.
	 */
    virtual ObjectType objectType() const = 0;
	virtual ObjectType object_type() const = 0;
    virtual ~Object() {}
};

//------------------- StringObject -------------------
class StringObject : public Object {
public:

	/**
     * @brief Construtor padrão.
     * @param s O valor inicial da string.
     */
    StringObject(string s = "");

	/**
     * @brief Destrutor padrão.
     */
    ~StringObject();

	/**
	 * @brief Obtém o tipo do objeto (string).
	 * @return O tipo do objeto.
	 */
    ObjectType object_type();

	/**
     * @brief Obtém a sequência de caracteres presente na string.
     * @return Retorna a string como uma std::string.
     */
    string getString() const;

	/**
     * @brief Substitui o valor da string.
     * @param s O novo valor da string.
     */
    void setString(string s);

private:
/**
     * A string interna.
     */
    string _internalString;
};

//------------------- ArrayObject -------------------

/**
 * @class ArrayObject
 * @brief Estrutura de armazenamento
 * @brief Representa um objeto do tipo array..
*/

class ArrayObject : public Object {
public:

	/**
	 * @brief Construtor padrão.
	 * @param type O tipo de dado que o array irá armazenar.
	 */
    ArrayObject(ValueType type);

	/**
	 * @brief Destrutor padrão.
	 */
    ~ArrayObject();

	/**
	 * @brief Representa o tipo de objeto (ObjectType::ARRAY).
	 * @return O tipo de objeto.
	 */
    ObjectType objectType() const override;

	/**
	 * @brief Obtém o tipo de conteúdo do array.
	 * @return O tipo que o array armazena.
	 */
    ValueType arrayContentType() const;


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
    uint32_t getSize() const;

	/**
	 * @brief Obtém o elemento dado o seu índice.
	 * @param index O índice do elemento.
	 * @return O elemento do array de índice index.
	 */
    Value getValue(uint32_t index) const;

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

#endif // object_h