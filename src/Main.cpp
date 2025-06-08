#include "LeitorExibidor.h"
#include "ClassVisao.h"
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo.class\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    LeitorExibidor &leitor = LeitorExibidor::getInstance();
    ClassFile *cf = leitor.readClassFile(fp);
    fclose(fp);

    // Gera o nome do arquivo de saída
    std::string input_name(argv[1]);
    std::string output_name = input_name + ".resultado.txt";
    
    // Abre o arquivo de saída
    std::ofstream out_file(output_name);
    if (!out_file) {
        std::cerr << "Erro ao criar arquivo de saída: " << output_name << std::endl;
        return 1;
    }
    
    // Redireciona a saída para o arquivo
    std::streambuf *coutbuf = std::cout.rdbuf(); // salva o buffer original
    std::cout.rdbuf(out_file.rdbuf()); // redireciona cout para o arquivo
    
    // Executa a exibição (agora vai para o arquivo)
    exibeClassFile(cf);
    
    // Restaura a saída padrão
    std::cout.rdbuf(coutbuf);
    
    std::cout << "Resultado salvo em: " << output_name << std::endl;
    return 0;
}