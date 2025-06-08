#include "LeitorExibidor.h"
#include "ClassVisao.h"
#include <cstdio>

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
    std::string output_name = std::string(argv[1]) + ".resultado.txt";
    
    // Salva o stdout original
    FILE* original_stdout = stdout;
    
    // Redireciona stdout para o arquivo
    stdout = freopen(output_name.c_str(), "w", stdout);
    if (!stdout) {
        perror("Erro ao redirecionar stdout");
        stdout = original_stdout; // restaura antes de sair
        return 1;
    }
    
    // Executa a exibição (agora vai para o arquivo)
    exibeClassFile(cf);
    
    // Fecha e restaura o stdout original
    fclose(stdout);
    stdout = original_stdout;
    
    printf("Resultado salvo em: %s\n", output_name.c_str());
    return 0;
}
