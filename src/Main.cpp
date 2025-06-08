#include "LeitorExibidor.h"
#include "ClassVisao.h"

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

    exibeClassFile(cf);
    return 0;
}
