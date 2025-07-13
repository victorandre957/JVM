#ifndef classruntime_h
#define classruntime_h

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <unordered_map>

#include "LeitorExibidor.h"
#include "ClassFile.h"

using namespace std;

/** @class StaticClass
 * @brief Representação de uma classe carregada durante o runtime.
 * @brief Gerencia os campos estáticos e metadados da classe.
 */
class StaticClass {
public:
	/**
	 * @brief Construtor padrão.
	 * @param classFile A ClassFile correspondente à classe.
	 */
	explicit StaticClass(ClassFile *classFile);

	/**
	 * @brief Destrutor padrão.
	 */
	~StaticClass() = default;

	/**
	 * @brief Copy constructor (deleted para evitar cópias desnecessárias).
	 */
	StaticClass(const StaticClass&) = delete;

	/**
	 * @brief Assignment operator (deleted para evitar cópias desnecessárias).
	 */
	StaticClass& operator=(const StaticClass&) = delete;

	/**
	 * @brief Obtém a ClassFile associada.
	 * @return Ponteiro para a ClassFile.
	 */
	ClassFile* getClassFile() const noexcept;

	/**
	 * @brief Insere um valor no field estático informado.
	 * @param value O valor que será inserido.
	 * @param fieldName O nome do field estático.
	 */
	void putValueIntoField(const Value& value, const string& fieldName);

	/**
	 * @brief Obtém o valor de um field estático.
	 * @param fieldName O nome do field que será obtido.
	 * @return Referência constante ao valor correspondente ao field estático.
	 * @throws NoSuchFieldError se o campo não existir.
	 */
	const Value& getValueFromField(const string& fieldName) const;

	/**
	 * @brief Verifica se o field informado existe.
	 * @param fieldName O nome do field que será verificado a existência.
	 * @return true caso o field exista, false caso contrário.
	 */
	bool fieldExists(const string& fieldName) const noexcept;

	/**
	 * @brief Extrai o nome do arquivo sem extensão.
	 * @param argv Array de argumentos da linha de comando.
	 * @return Nome do arquivo sem a extensão .class.
	 */
	static string extrairNomeArquivo(char *argv[]);

	/**
	 * @brief Obtém o número de campos estáticos.
	 * @return Número de campos estáticos na classe.
	 */
	size_t getNumeroFieldsEstaticos() const noexcept;

private:
	/**
	 * @brief Inicializa um valor padrão baseado no tipo do campo.
	 * @param fieldType Tipo do campo (primeiro caractere do descritor).
	 * @return Valor padrão inicializado.
	 */
	static Value criarValorPadrao(char fieldType) noexcept;

	/**
	 * A ClassFile correspondente à classe.
	 */
	ClassFile *_classFile;

	/**
	 * Os fields estáticos da classe (usando unordered_map para melhor performance).
	 */
	unordered_map<string, Value> _staticFields;
};

#endif /* classruntime_h */
