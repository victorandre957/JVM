# Leitor/Exibidor JVM java 8

## Sobre o projeto

Projeto para a disciplina de Software Básico.

Projetado por:

  - Anita Garcia Lagos Oliveira - 211068243
  - Giovanni Nogueira Catelli - 211043502
  - Luan Crisley Gomes Guedes - 211026628
  - Victor André de Moraes - 211026664
  
## Como compilar

Para compilar o projeto, execute o seguinte comando no terminal:

  - Execute o comando abaixo para compilar o projeto:

```
  mkdir -p build
  g++ -std=c++11 -g -O0 -I include -Wall -Wextra -o build/THE_JVM src/*.cpp -lm
```

Depois de compilar, o executável será gerado na pasta `build`.

## Como testar

Para executar os testes disponíveis, execute o seguinte comando no terminal:

```
  chmod +x ./run_tests.sh           
  ./run_tests.sh
```

Para executar o programa com exibidor utilize, use o comando:

```
  ./THE_JVM -E arquivo.class
```

Para executar o programa com interpretador, use o comando:

```
  ./THE_JVM -I arquivo.class
```


## Analisador de código estático Cppcheck

Para a verficação do cppcheck, execute o seguinte comando no terminal:

```
  cppcheck --enable=all --suppress=missingIncludeSystem --std=c++11 --check-level=exhaustive -I include  --output-file=analysis.txt ./
```
E verifique o arquivo `analysis.txt` para os resultados.

## Analisador de código dinâmico Valgrind

Assim, é possível rodar o Valgrind para fazer as análises dinâmicas:

```
  valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./build/THE_JVM
```

Resultados:

```
==139868== Memcheck, a memory error detector
==139868== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==139868== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==139868== Command: ./build/THE_JVM
==139868== 
Invalido, deve ser executado com: ./build/THE_JVM -exhibitor ou -interpreter arquivo.class
==139868== 
==139868== HEAP SUMMARY:
==139868==     in use at exit: 0 bytes in 0 blocks
==139868==   total heap usage: 2 allocs, 2 frees, 74,752 bytes allocated
==139868== 
==139868== All heap blocks were freed -- no leaks are possible
==139868== 
==139868== For lists of detected and suppressed errors, rerun with: -s
==139868== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

