#include <stdio.h>
#include "mbr_reader.h"

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_mbr>\n", argv[0]);
        return 1;
    }

    // Abrindo o arquivo contendo a MBR
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // Lendo os 512 bytes da MBR
    unsigned char mbr[TAMANHO_MBR];
    if (fread(mbr, 1, TAMANHO_MBR, file) != TAMANHO_MBR) {
        perror("Falha em ler arquivo MBR");
        fclose(file);
        return 1;
    }
    fclose(file);

    // Extraindo as entradas da tabela de partições
    PartitionEntry partition_table[NUM_PARTICOES];
    for (int i = 0; i < NUM_PARTICOES; i++) {
        int offset = TABELA_PARTICOES_OFFSET + i * TAMANHO_ENTRADA_PARTICAO;
        extrair_entrada_particao(mbr, offset, &partition_table[i]);
    }

    // Imprimindo a tabela de partições
    imprimir_tabela_particoes(partition_table);

    return 0;
}
