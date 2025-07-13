#!/bin/bash

# Lista de arquivos a serem processados
arquivos=(
    "./tests/Belote.class"
    "./tests/cafebabe.class"
    "./tests/Carta.class"
    "./tests/double_aritmetica.class"
    "./tests/double_cast.class"
    "./tests/double_logico.class"
    "./tests/fatorial.class"
    "./tests/fibonacci.class"
    "./tests/FibonacciRec.class"
    "./tests/interface_test.class"
    "./tests/Jogador.class"
    "./tests/lookupswitch.class"
    "./tests/method_test.class"
    "./tests/multi.class"
    "./tests/soma_certo.class"
    "./tests/soma_errado.class"
    "./tests/Somar.class"
    "./tests/tableswitch.class"
    "./tests/vetor2.class"
    "./tests/vetor_8.class"
)

# Executa o LeitorExibidor para cada arquivo

for arq in "${arquivos[@]}"; do
    echo "Processando: $arq"
    ./build/JVM -e "$arq"
    echo "----------------------------------------"
done

# Executa o Interpretador para cada arquivo

for arq in "${arquivos[@]}"; do
    echo "Processando: $arq"
    ./build/JVM -i "$arq"
    echo "----------------------------------------"
done

echo "Todos os arquivos foram processados!"
