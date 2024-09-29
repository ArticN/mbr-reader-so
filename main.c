#include <stdio.h>
#include "mbr_reader.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_mbr>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    unsigned char mbr[TAMANHO_MBR];
    if (fread(mbr, 1, TAMANHO_MBR, file) != TAMANHO_MBR) {
        perror("Falha em ler arquivo MBR");
        fclose(file);
        return 1;
    }
    fclose(file);

    PartitionEntry partition_table[NUM_PARTICOES];
    for (int i = 0; i < NUM_PARTICOES; i++) {
        int offset = DESLOCAMENTO_TABELA_PARTICOES + i * TAMANHO_ENTRADA_PARTICAO;
        extrair_entrada_particao(mbr, offset, &partition_table[i]);
    }

    imprimir_tabela_particoes(partition_table);

    return 0;
}

