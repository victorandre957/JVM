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
  g++ -MT bin/ClassFile.o -MMD -MP -MF dep/ClassFile.d -c -o bin/ClassFile.o src/ClassFile.cpp -std=c++11 -c -I include -Wall -Wextra
  g++ -MT bin/ClassVisao.o -MMD -MP -MF dep/ClassVisao.d -c -o bin/ClassVisao.o src/ClassVisao.cpp -std=c++11 -c -I include -Wall -Wextra
  g++ -MT bin/LeitorExibidor.o -MMD -MP -MF dep/LeitorExibidor.d -c -o bin/LeitorExibidor.o src/LeitorExibidor.cpp -std=c++11 -c -I include -Wall -Wextra
  g++ -MT bin/Main.o -MMD -MP -MF dep/Main.d -c -o bin/Main.o src/Main.cpp -std=c++11 -c -I include -Wall -Wextra
  g++ -MT bin/Utils.o -MMD -MP -MF dep/Utils.d -c -o bin/Utils.o src/Utils.cpp -std=c++11 -c -I include -Wall -Wextra
  g++ -o build/LeitorExibidor bin/ClassFile.o bin/ClassVisao.o bin/LeitorExibidor.o bin/Main.o bin/Utils.o -lm
```

Depois de compilar, o executável será gerado na pasta `build`.

## Como testar

Para executar os testes disponíveis, execute o seguinte comando no terminal:

```
  chmod +x ./run_tests.sh           
  ./run_tests.sh
```

## Analisador de código estático Cppcheck

## Analisador de código dinâmico Valgrind

Como o analisador trabalha encima de binários gerados pela compilação dos códigos, é necessário fazer a compilação de todos os códigos com as flags -g e -O0, sendo essas alterações feitas sobre o makefile.

Em seguida, no terminal linke os binários .o em um binário principal executável com o comando:

```
  g++ bin/*.o -o JVM_B
```

Assim, é possível rodar o Valgrind para fazer as análises dinâmicas:

```
  valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./JVM_B
```

Resultados:

```
  ==104227== Memcheck, a memory error detector
==104227== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==104227== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==104227== Command: ./JVM_B
==104227==
Uso: ./JVM_B arquivo.class
==104227==
==104227== HEAP SUMMARY:
==104227==     in use at exit: 0 bytes in 0 blocks
==104227==   total heap usage: 2 allocs, 2 frees, 73,728 bytes allocated
==104227==
==104227== All heap blocks were freed -- no leaks are possible
==104227==
==104227== For lists of detected and suppressed errors, rerun with: -s
==104227== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

