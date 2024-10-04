#ifndef MBR_READER_H
#define MBR_READER_H

#define TAMANHO_MBR 512
#define TAMANHO_ENTRADA_PARTICAO 16
#define DESLOCAMENTO_TABELA_PARTICOES 446
#define NUM_PARTICOES 4
#define TAMANHO_SETOR 512

typedef struct {
    unsigned char boot_flag;
    unsigned char partition_type;
    unsigned int start_lba;
    unsigned int sectors_count;
} PartitionEntry;

const char* obter_tipo_particao(unsigned char partition_type);
void extrair_entrada_particao(const unsigned char *mbr, int offset, PartitionEntry *entry);
void imprimir_entrada_particao(int index, const PartitionEntry *p);
void imprimir_tabela_particoes(const PartitionEntry *partition_table);
void imprimir_informacoes_disco(unsigned int total_sectors, unsigned int *disk_id);

#endif
