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